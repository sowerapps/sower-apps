///////////////////////////////////////////////////////////////////
// Name:        anchor.cpp
// Purpose:     Set or remove style settings, properties for anchors.
//              Jump to anchors from links. SwHtmlAnchor class is used
//              only for read only controls.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"
#include "../../include/appi/appifa.h"
#include <wx/listctrl.h>

// SwHtmlAnchor class anchors.
void SwRichTextCtrl::JumpToAnchorPosition(swUI32 id)
{
    if (!m_anchor.VerifyAnchorId(id))
        return;

    if (GetCaretPosition() < (signed) m_anchor.GetAnchorTarget(id))
    {
        if (m_anchor.GetAnchorTargetExtent(id) > m_anchor.GetAnchorTarget(id))
        {
            ShowPosition(m_anchor.GetAnchorTargetExtent(id));
            MoveCaret(m_anchor.GetAnchorTarget(id));
        }
        else
        {
            ShowPosition(m_anchor.GetAnchorTarget(id) + 1);
            MoveCaret(m_anchor.GetAnchorTarget(id));
        }
    }
    else
    {
        ShowPosition(m_anchor.GetAnchorOrigin(id));
        MoveCaret(m_anchor.GetAnchorOrigin(id) - 1);
    }

    m_mouseCount = 0;
}

// RichText property anchors.
void SwRichTextCtrl::JumpToAnchorPosition(const wchar_t * name)
{
    if (!name)
        return;

    wxPoint pt;
    wxString propertyValue;
    wxRichTextObjectList::compatibility_iterator node = GetBuffer().GetChildren().GetFirst();

    while (node)
    {
        wxRichTextParagraph* para = wxDynamicCast(node->GetData(), wxRichTextParagraph);

        if (para)
        {
            wxRichTextObjectList::compatibility_iterator node2 = para->GetChildren().GetFirst();
            while (node2)
            {
                wxRichTextObject* obj = node2->GetData();
                if (obj->GetProperties().HasProperty("rtx:anchor:"))
                {
                    propertyValue = obj->GetProperties().GetPropertyString("rtx:anchor:");
                    if (propertyValue.IsSameAs(name))
                    {
                        pt = obj->GetAbsolutePosition();
                        SetScrollPos(wxVERTICAL, pt.x+10);
                        m_mouseCount = 0;
                    }
                }

                node2 = node2->GetNext();
            }
        }

        node = node->GetNext();
    }
}

int SwRichTextCtrl::GetAnchorList(wxListCtrl * listBox)
{
    int anchors = 0;
    wxListItem lItem;

    if (!listBox)
        return 0;

    wxRichTextObjectList::compatibility_iterator node = GetBuffer().GetChildren().GetFirst();

    while (node)
    {
        wxRichTextParagraph* para = wxDynamicCast(node->GetData(), wxRichTextParagraph);

        if (para)
        {
            wxRichTextObjectList::compatibility_iterator node2 = para->GetChildren().GetFirst();
            while (node2)
            {
                wxRichTextObject* obj = node2->GetData();
                if (obj->GetProperties().HasProperty("rtx:anchor:"))
                {
                    lItem.Clear();
                    lItem.SetStateMask(wxLIST_MASK_TEXT);
                    lItem.SetColumn(0);
                    lItem.SetId(listBox->GetItemCount());
                    lItem.SetText(obj->GetProperties().GetPropertyString("rtx:anchor:"));
                    listBox->InsertItem(lItem);
                    anchors ++;
                }

                node2 = node2->GetNext();
            }
        }

        node = node->GetNext();
    }

    return anchors;
}
