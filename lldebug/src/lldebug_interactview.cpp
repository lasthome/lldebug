//---------------------------------------------------------------------------
//
// Name:        MainFrame.cpp
// Author:      �딎
// Created:     2007/11/23 0:05:33
// Description: MainFrame class implementation
//
//---------------------------------------------------------------------------

#include "lldebug_prec.h"
#include "lldebug_interactview.h"
#include "lldebug_context.h"

namespace lldebug {

class InteractView::RunButton : public wxButton {
public:
	explicit RunButton(InteractView *parent, wxPoint pos, wxSize size)
		: wxButton(parent, wxID_ANY, wxT("Run"), pos, size)
		, m_parent(parent) {
	}

	virtual ~RunButton() {
	}

protected:
	virtual void OnButton(wxCommandEvent &event) {
		m_parent->Run();
	}

private:
	InteractView *m_parent;

	DECLARE_EVENT_TABLE();
};

class InteractView::TextInput : public wxTextCtrl {
public:
	explicit TextInput(InteractView *parent, wxPoint pos, wxSize size)
		: wxTextCtrl(parent, wxID_ANY, wxT(""), pos, size
			, wxTE_MULTILINE)
		, m_parent(parent) {
		Clear();
	}

	virtual ~TextInput() {
	}

private:
	void OnChar(wxKeyEvent &event) {
		if (!event.ShiftDown() && event.GetKeyCode() == WXK_RETURN) {
			m_parent->Run();
		}
		else {
			event.Skip();
		}
	}

private:
	InteractView *m_parent;

	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(InteractView::RunButton, wxButton)
	EVT_BUTTON(wxID_ANY, InteractView::RunButton::OnButton)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(InteractView::TextInput, wxTextCtrl)
	EVT_CHAR(InteractView::TextInput::OnChar)
END_EVENT_TABLE()


/*-----------------------------------------------------------------*/
BEGIN_EVENT_TABLE(InteractView, wxPanel)
	EVT_LLDEBUG_CHANGED_STATE(ID_INTERACTVIEW, InteractView::OnChangedState)
END_EVENT_TABLE()

InteractView::InteractView(Context *ctx, wxWindow *parent)
	: wxPanel(parent, ID_INTERACTVIEW + ctx->GetId()
	, wxDefaultPosition, wxDefaultSize)
	, m_ctx(ctx) {
	CreateGUIControls();
}

InteractView::~InteractView() {
}

void InteractView::CreateGUIControls() {
	scoped_lock lock(m_mutex);
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	m_text = new wxTextCtrl(this, wxID_ANY, wxT("output")
		, wxPoint(0,0), wxSize(400,300)
		, wxTE_READONLY | wxTE_MULTILINE | wxVSCROLL);
	sizer->Add(m_text, 1, wxALIGN_TOP | wxEXPAND);

	wxBoxSizer *sizer2 = new wxBoxSizer(wxHORIZONTAL);
	m_input = new TextInput(this, wxPoint(0,200), wxSize(300,GetCharHeight() + 8));
	sizer2->Add(m_input, 1, wxALIGN_LEFT | wxEXPAND | wxALL, 4);

	RunButton *m_run = new RunButton(this, wxPoint(300,300), wxSize(64, 1));
	sizer2->Add(m_run, 0, wxALIGN_RIGHT | wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 4);

	sizer->Add(sizer2, 0, wxALIGN_BOTTOM | wxEXPAND);

	SetAutoLayout(true);
	SetSizer(sizer);
	sizer->Layout();
	sizer->Fit(this);
	sizer->SetSizeHints(this);
}

void InteractView::OnChangedState(wxChangedStateEvent &event) {
	scoped_lock lock(m_mutex);

	Enable(event.GetValue());
}

void InteractView::Run() {
	scoped_lock lock(m_mutex);
	wxString str = m_input->GetValue();
	wxString result;

	if (str.IsEmpty()) {
		return;
	}

	if (str[0] == wxT('$')) {
		str.Remove(0, 1);
		str = str.Strip(wxString::both);

		std::string stdstr = wxConvToUTF8(str);
		LuaVar var; // = m_ctx->LuaGetVar(stdstr);

		result.Append(wxT("\n> '") + str + wxT("'"));
		if (var.IsOk()) {
			wxString value = wxConvFromUTF8(var.GetValue());
			result.Append(wxT(" = ") + value);
		}
		else {
			result.Append(wxT(" is not found."));
		}
	}
	else {
		std::string stdstr = wxConvToUTF8(str);
		result.Append(wxT("\n> "));
		result.Append(str);
		result.Append(wxT("\n"));

		if (m_ctx->LuaEval(stdstr) == 0) {
			result.Append(wxT("success"));
		}
		else {
			result.Append(wxT("error"));
		}
	}

	m_text->AppendText(result);
	m_input->SetFocus();
	m_input->Clear();
}

}