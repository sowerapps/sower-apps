///////////////////////////////////////////////////////////////////
// Name:        events.cpp
// Purpose:     Events emitted by wxRichTextCtr that are bound to
//              'this' control but are unused by SwRichTextCtrl.
//              Derived objects can override these functions to
//              handle these events. The advantage is that derived
//              objects do not have to do bind/unbind these events.
//              Similarly named functions in richtextctrlext.h without
//              'This' in the function name is for controls that have
//              been embedded in 'this' control.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"

void SwRichTextCtrl::OnThisRichTextLeftClick(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextRightClick(wxRichTextEvent& event)
{
   event.Skip();
}

void SwRichTextCtrl::OnThisRichTextMiddleClick(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextLeftDClick(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextReturn(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextCharacter(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextDelete(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextSelectionChanged(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextFocusObjectChanged(wxRichTextEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextText(wxCommandEvent& event)
{
    event.Skip();
}

void SwRichTextCtrl::OnThisRichTextTextEnter(wxCommandEvent& event)
{
    event.Skip();
}
