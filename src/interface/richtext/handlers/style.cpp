///////////////////////////////////////////////////////////////////
// Name:        table.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"
#include "../../../../include/appi/appifa.h"
#include "../../../../include/html/html_css.h"

void SwRichTextInterface::GetBlockStyle(swUI32 node)
{
    m_richAttr.Reset();
    m_richAttr.Copy((wxTextAttr &) m_rich->GetBasicStyle());
    m_richAttr.SetFontPointSize(m_basefontsize);
    m_richAttr.SetBackgroundColour(*wxWHITE);
    m_richAttr.SetTextColour(*wxBLACK);
    //- m_richAttr.SetAlignment(wxTEXT_ALIGNMENT_LEFT);
    //+
    wxRichTextAttr attr = m_rich->GetDefaultStyle();
    //
    m_richAttr.SetAlignment(attr.GetAlignment());
    m_richAttr.SetHtmlAttributes(m_attrList, m_basefontsize, IsTableCell(GetNodeElementIdentifier(node)));
}

void SwRichTextInterface::GetInlineStyle(swUI32 node)
{
    m_richAttr.Reset();
    m_richAttr.Copy(m_rich->GetDefaultStyle());
    m_richAttr.SetHtmlAttributes(m_attrList, m_basefontsize, IsTableCell(GetNodeElementIdentifier(node)));
}

bool SwRichTextInterface::GetEndStyleFlag(swUI32 node)
{
    if (node < m_parserNodePos)
    {
        if (GetNodeType(node) == NODE_TYPE_END_TAG)
        {
            return m_parserNodeData[node].param3;
        }
    }

    return false;
}

void SwRichTextInterface::SetEndStyleFlag(swUI32 node, bool state)
{
    if (node < m_parserNodePos)
    {
        if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
        {
            m_parserNodeData[GetNodeMate(node)].param3 = state;
        }
    }
}

bool SwRichTextInterface::BeginBlockStyle(swUI32 node, bool force)
{
    if (m_rich)
    {
        if (force || m_attrList.GetItems() || m_richAttr.GetCssAttributes().GetItems())
        {
            SetEndStyleFlag(node, m_rich->BeginStyle(m_richAttr));
            return true;
        }
    }

    SetEndStyleFlag(node, false);
    return false;
}

bool SwRichTextInterface::BeginInlineStyle(swUI32 node, bool force)
{
    if (m_rich)
    {
        if (force || m_attrList.GetItems() || m_richAttr.GetCssAttributes().GetItems())
        {
            SetEndStyleFlag(node, m_rich->BeginStyle(m_richAttr));
            return true;
        }
    }

    SetEndStyleFlag(node, false);
    return false;
}

void SwRichTextInterface::EndBlockStyle(swUI32 node)
{
    if (m_rich && GetEndStyleFlag(node))
    {
        m_rich->EndStyle();
    }
}

void SwRichTextInterface::EndInlineStyle(swUI32 node)
{
    if (m_rich && GetEndStyleFlag(node))
    {
        m_rich->EndStyle();
    }
}
