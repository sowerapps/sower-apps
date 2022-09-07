///////////////////////////////////////////////////////////////////
// Name:        paragraphlist.cpp
// Purpose:     List for sections of text written to a wxRichTextCtrl.
//              Storing xml id, begin position, and extent so that it is
//              possible to scroll to, and/or hilite a specific section
//              specified by it's xml id.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/objects/paragraphlist.h"
#include "../../../include/html/html.h"
#include "../../../include/thml/thml_elements.h"
#include "../../../include/appi/appifa.h"

SwParagraphList::SwParagraphList()
{
    m_rich = NULL;
}

SwParagraphList::~SwParagraphList()
{
}

bool SwParagraphList::HiliteParagraph(const char * id)
{
    if (!m_rich || !id)
        return false;

    swUI32 node = FindParagraph(id);

    if (node == NODE_ID_INVALID)
    {
        return false;
    }

    if (GetNodeElementIdentifier(node) == THML_PB)
    {
        m_rich->SetInsertionPoint(GetNodeStreamPosition(node));
        m_rich->WriteImage(SwApplicationInterface::GetStockImage(IMG_RHOMBUS_SOLID_RED), wxBITMAP_TYPE_PNG);
        UpdatePositionData(node + 1, 1);
        return true;
    }

    wxTextAttr attr;
    wxRichTextRange range(GetNodeStreamPosition(node), GetParagraphExtent(node));
    m_rich->SetFocusObject((wxRichTextParagraphLayoutBox *)GetNodeData(node));
    m_rich->GetStyleForRange(range, attr);
    attr.SetBackgroundColour(*wxYELLOW);
    m_rich->SetStyle(range, attr);

    return true;
}

bool SwParagraphList::SelectParagraph(const char * id)
{
    if (!m_rich || !id)
        return false;

    swUI32 node = FindParagraph(id);

    if (node == NODE_ID_INVALID)
        return false;

    m_rich->SetSelection(GetNodeStreamPosition(node), GetParagraphExtent(node));

    return true;
}

bool SwParagraphList::ShowParagraph(const char * id)
{
    if (!m_rich || !id)
        return false;

    swUI32 node = FindParagraph(id);

    if (node == NODE_ID_INVALID)
        return false;

    m_rich->LayoutContent();
    long showPosition = m_rich->GetFirstVisiblePosition();

    if (showPosition > (long) GetNodeStreamPosition(node))
    {
        m_rich->ShowPosition(GetNodeStreamPosition(node));
    }

    else
    {
        m_rich->ShowPosition(GetParagraphExtent(node));
    }


    return true;
}

bool SwParagraphList::SetCaretAtParagraph(const char * id)
{
    if (!m_rich || !id)
        return false;

    swUI32 node = FindParagraph(id);

    if (node == NODE_ID_INVALID)
        return false;

    long showPosition = m_rich->GetFirstVisiblePosition();

    if (showPosition > (long) GetNodeStreamPosition(node))
    {
        m_rich->SetCaretPosition(GetNodeStreamPosition(node));
    }
    else
    {
        m_rich->SetCaretPosition(GetParagraphExtent(node));
    }

    return true;
}

swUI32 SwParagraphList::FindParagraph(const char * id)
{
    if (!m_rich || !id)
        return false;

    swUI32 pos = 0;

    while (pos < m_nodePos)
    {
        if ((m_nodeData[pos].nodeType == NODE_TYPE_BEGIN_TAG ||
             m_nodeData[pos].nodeType == NODE_TYPE_UNPAIRED_TAG)
            && stricmp(id, m_nodeData[pos].xmlId) == 0)
            {
                return pos;
            }


        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwParagraphList::GetParagraphExtent(swUI32 node)
{
    if (!m_rich || node >= m_nodePos)
        return 0;

    swUI32 mate;

    mate = GetNodeMate(node);

    if ((GetNodeElementIdentifier(node) == THML_TERM || GetNodeElementIdentifier(node) == THML_TERM_STRONGS) && mate != NODE_ID_INVALID)
    {
        if (GetNodeElementIdentifier(mate + 1) == THML_DEF && GetNodeType(mate + 1) == NODE_TYPE_BEGIN_TAG)
        {
            mate = GetNodeMate(mate + 1);
            return GetNodeStreamPosition(mate);
        }
    }
    else if (GetNodeElementIdentifier(node) == THML_SCRIPCOM && mate == NODE_ID_INVALID)
    {
        mate = FindElement(node + 1, THML_SCRIPCOM, NODE_TYPE_UNPAIRED_TAG);
        if (mate != NODE_ID_INVALID)
        {
            return GetNodeStreamPosition(mate);
        }

        return m_rich->GetLastPosition();
    }
    else if (GetNodeElementIdentifier(node) == THML_SCRIPTURE && mate == NODE_ID_INVALID)
    {
        mate = FindElement(node + 1, THML_SCRIPTURE, NODE_TYPE_UNPAIRED_TAG);
        if (mate != NODE_ID_INVALID)
        {
            return GetNodeStreamPosition(mate);
        }

        mate = FindElement(node + 1, THML_P, NODE_TYPE_BEGIN_TAG);

        if (mate != NODE_ID_INVALID)
        {
            return GetNodeStreamPosition(mate);
        }

        return m_rich->GetLastPosition();
    }
    else if (GetNodeElementIdentifier(node) == THML_PB && mate == NODE_ID_INVALID)
    {
        mate = FindElement(node + 1, THML_PB, NODE_TYPE_UNPAIRED_TAG);
        if (mate != NODE_ID_INVALID)
        {
            return GetNodeStreamPosition(mate);
        }

        return m_rich->GetLastPosition();
    }

    if (mate != NODE_ID_INVALID)
        return GetNodeStreamPosition(mate);

    if (node + 1 < m_nodePos)
        return GetNodeStreamPosition(node + 1);

    return m_rich->GetLastPosition();
}

void SwParagraphList::SetView(wxRichTextCtrl * rich)
{
    m_rich = rich;
}
