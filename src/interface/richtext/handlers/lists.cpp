///////////////////////////////////////////////////////////////////
// Name:        lists.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"
#include "../../../../include/appi/appifa.h"
#include "../../../../include/html/html_css.h"
#include "../../../../include/thml/thml_css.h"

swUI32 SwRichTextInterface::Onl(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ondd(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (m_richAttr.GetLeftIndent() <= 0)
            m_richAttr.SetLeftIndent(SwApplicationInterface::GetPPI() * .75, 0);
        else
            m_richAttr.SetLeftIndent(m_richAttr.GetLeftIndent(), 0);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ondl(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        //   Paragraph();

        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ondt(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ondir(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
//        Paragraph();

        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onli(swUI32 node)
{
    SwString raw, output;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        // Paragraph();
        m_inListItem = true;

        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));

        if (m_listnodePos)
        {
            switch (m_listData[m_listnodePos - 1].listType)
            {
            case LIST_STYLE_TYPE_CIRCLE :
            case LIST_STYLE_TYPE_DISC :
            case LIST_STYLE_TYPE_SQUARE :
                WriteSymbol(m_listData[m_listnodePos - 1].listType);
                break;
            case LIST_STYLE_TYPE_DECIMAL :
            case LIST_STYLE_TYPE_LOWER_ALPHA :
            case LIST_STYLE_TYPE_UPPER_ALPHA :
            case LIST_STYLE_TYPE_LOWER_ROMAN :
            case LIST_STYLE_TYPE_UPPER_ROMAN :
                SwHtml::FormatListNumber(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, m_listData[m_listnodePos - 1].listType, raw);
                output.Copy(raw);
                m_rich->WriteText(output.GetArray());
                break;
            }
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_inListItem = false;

        if (m_listnodePos)
        {
            m_listData[m_listnodePos - 1].itemCount ++;
        }

        Paragraph();
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onol(swUI32 node)
{
    int subIndent = SwApplicationInterface::GetPPI() * .50;
    int leftIndent = (SwApplicationInterface::GetPPI() * .25) * m_listnodePos;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (AssignListDataNode() != NODE_ID_INVALID_16)
        {
            m_listData[m_listnodePos - 1].listType = m_richAttr.m_listStyle;
            m_listData[m_listnodePos - 1].start = m_richAttr.GetBulletNumber();
        }

        m_inListItem = false;
        //  Paragraph();

        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));

        if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_DECIMAL)
        {
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
        else if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_UPPER_ALPHA)
        {
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
        else if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_LOWER_ALPHA)
        {
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
        else if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_UPPER_ROMAN)
        {
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
        else if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_LOWER_ROMAN)
        {
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        //    Paragraph();
        EndBlockStyle(node);

        if (m_listnodePos)
        {
            m_listnodePos --;
            EndNumberedBullet();
        }
    }

    return node;
}

swUI32 SwRichTextInterface::Onul(swUI32 node)
{
    int subIndent = SwApplicationInterface::GetPPI() * .50;
    int leftIndent = (SwApplicationInterface::GetPPI() * .25) * m_listnodePos;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (AssignListDataNode() != NODE_ID_INVALID_16)
        {
            m_listData[m_listnodePos - 1].listType = m_richAttr.m_listStyle;

            // LIST_STYLE_TYPE_DECIMAL is default in SwRichTextAttr.
            // Correct this if a style has not been specified.
            if (m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_DECIMAL)
                m_listData[m_listnodePos - 1].listType = LIST_STYLE_TYPE_DISC;

            m_listData[m_listnodePos - 1].start = m_richAttr.GetBulletNumber();
        }

        m_inListItem = false;
        //  Paragraph();


        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        SetEndStyleFlag(node, BeginBlockStyle(node));

        if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_CIRCLE)
        {
            subIndent = SwApplicationInterface::GetPPI() * .33;
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
        else if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_DISC)
        {
            subIndent = SwApplicationInterface::GetPPI() * .33;
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
        else if (m_listnodePos && m_listData[m_listnodePos - 1].listType == LIST_STYLE_TYPE_SQUARE)
        {
            subIndent = SwApplicationInterface::GetPPI() * .33;
            BeginNumberedBullet(m_listData[m_listnodePos - 1].start + m_listData[m_listnodePos - 1].itemCount, leftIndent, subIndent);
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        // Paragraph();
        EndBlockStyle(node);

        if (m_listnodePos)
        {
            m_listnodePos --;
            EndNumberedBullet();
        }
    }

    return node;
}

void SwRichTextInterface::BeginNumberedBullet(int number, int leftIndent, int subIndent)
{
    m_rich->BeginLeftIndent(leftIndent, subIndent);
}

void SwRichTextInterface::EndNumberedBullet()
{
    m_rich->EndLeftIndent();
}

void SwRichTextInterface::WriteSymbol(swUI8 listType)
{
    m_rich->WriteText(L"  ");
    switch (listType)
    {
    case LIST_STYLE_TYPE_CIRCLE :
        m_rich->WriteImage(SwApplicationInterface::GetStockImage(IMG_CIRCLE_HOLLOW), wxBITMAP_TYPE_PNG);
        break;
    case LIST_STYLE_TYPE_DISC :
        m_rich->WriteImage(SwApplicationInterface::GetStockImage(IMG_CIRCLE_SOLID), wxBITMAP_TYPE_PNG);
        break;
    case LIST_STYLE_TYPE_SQUARE :
        m_rich->WriteImage(SwApplicationInterface::GetStockImage(IMG_SQUARE_SOLID), wxBITMAP_TYPE_PNG);
        break;
    }

    m_rich->WriteText(L" ");
}
