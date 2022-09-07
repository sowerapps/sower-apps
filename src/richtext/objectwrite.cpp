///////////////////////////////////////////////////////////////////
// Name:        objectwrite.cpp
// Purpose:     Register handlers needed for embedded controls.
//              Write controls to SwRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"
#include "../../include/richtext/objects/horizontalrule.h"
#include "../../include/appi/appifa.h"

void SwRichTextCtrl::RegisterHandlers()
{
    wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
    wxRichTextXMLHandler::RegisterNodeName(L"horizontalrule", L"SwHorizontalRule");
}

SwHorizontalRule * SwRichTextCtrl::WriteHorizontalRule(wxRichTextAttr& textAttr)
{
    wxRichTextAction* action = new wxRichTextAction(NULL, SwApplicationInterface::GetControlString("SID_INSERTHORIZONTALRULE", L"Insert Horizontal Rule"), wxRICHTEXT_INSERT, GetFocusObject()->GetBuffer(), GetFocusObject(), this, false);
    wxRichTextParagraph* newPara = new wxRichTextParagraph(GetFocusObject(), &textAttr);


    SwHorizontalRule * object = new SwHorizontalRule(newPara);

    newPara->AppendChild(object);
    object->SetAttributes(textAttr);
    action->GetNewParagraphs().AppendChild(newPara);
    action->GetNewParagraphs().UpdateRanges();

    action->GetNewParagraphs().SetPartialParagraph(true);
    long pos = GetInsertionPoint();
    action->SetPosition(pos);

    action->SetRange(wxRichTextRange(pos, pos));

    GetFocusObject()->GetBuffer()->SubmitAction(action);
    SwHorizontalRule * obj = (SwHorizontalRule *) GetFocusObject()->GetBuffer()->GetLeafObjectAtPosition(pos);

    return obj;
}
