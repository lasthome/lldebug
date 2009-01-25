/*
 * Copyright (c) 2005-2008  cielacanth <cielacanth AT s60.xrea.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "precomp.h"
#include "visual/event.h"

namespace lldebug {
namespace visual {

DEFINE_EVENT_TYPE(wxEVT_DEBUG_END_DEBUG)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_CHANGED_STATE)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_UPDATE_SOURCE)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_ADDED_SOURCE)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_CHANGED_BREAKPOINTS)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_OUTPUT_LOG)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_OUTPUT_INTERACTIVEVIEW)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_FOCUS_ERRORLINE)
DEFINE_EVENT_TYPE(wxEVT_DEBUG_FOCUS_BACKTRACELINE)

} // end of namespace visual
} // end of namespace lldebug