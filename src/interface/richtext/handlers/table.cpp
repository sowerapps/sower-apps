///////////////////////////////////////////////////////////////////
// Name:        table.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"
#include "../../../../include/appi/appifa.h"
#include "../../../../include/html/html_css.h"

swUI32 SwRichTextInterface::Oncaption(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        wxRichTextCell* cell = m_matrixArray.Get()->GetTable()->GetCell(0, 0);
        cell->SetColSpan(m_matrixArray.Get()->GetTable()->GetColumnCount());
        m_rich->SetFocusObject(cell);

        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (cell)
        {
            cell->GetBuffer()->SetDefaultStyle(m_richAttr);
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_matrixArray.Get()->IncRowPos();
    }

    return node;
}

swUI32 SwRichTextInterface::Oncol(swUI32 node)
{
    SwString value;

    if (!m_matrixArray.GetCount())
    {
        return node;
    }

    SwRichTextAttr attr;
    GetNodeData(node, m_style);
    m_attrList.ParseTag(m_style);
    attr.SetHtmlAttributes(m_attrList, m_basefontsize, true);

    swUI32 span = 1;

    if (GetNamedValueFromNode(node, "span", value))
    {
        span = value.Strtoul();
    }

    int startCol = m_matrixArray.Get()->GetColGroupPos();
    int endCol = m_matrixArray.Get()->GetColGroupPos() + span;
    int startRow = 0;

    if (m_matrixArray.Get()->GetHasCaption())
    {
        startRow = 1;
    }

    wxRichTextCell * cell;
    for (int col = startCol; col < endCol; col ++)
    {
        if (col >= m_matrixArray.Get()->GetTable()->GetColumnCount())
        {
            break;
        }

        for (int row = startRow; row < m_matrixArray.Get()->GetTable()->GetRowCount(); row ++)
        {
            cell = m_matrixArray.Get()->GetTable()->GetCell(row, col);
            if (cell)
                cell->SetAttributes(attr);
        }
    }

    m_matrixArray.Get()->SetColGroupPos(m_matrixArray.Get()->GetColGroupPos() + span);
    return node;
}

swUI32 SwRichTextInterface::Ontable(swUI32 node)
{
    swUI32 captionNode;
    wxRichTextCell * cell;
    wxRichTextAttr cellAttr;
    swUI32 rows = 0, columns = 0;
    swUI32 tableId;
    SwString a;
    SwString b;
    SwString c;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {

        if (GetNamedValueFromNode(node, "border", a) && a.GetAt(0) == '1')
        {
            if (m_markupType == MARKUP_THML)
                SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
            else
                SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        }

        GetBlockStyle(node);
        cellAttr = m_richAttr;

        cellAttr.GetTextBoxAttr().GetMargins() = m_richAttr.GetTextBoxAttr().GetMargins();
        cellAttr.GetTextBoxAttr().GetPadding() = m_richAttr.GetTextBoxAttr().GetPadding();
        cellAttr.GetTextBoxAttr().GetBorder() = m_richAttr.GetTextBoxAttr().GetBorder();

        tableId = m_matrixArray.Add();
        if (tableId != NODE_ID_INVALID)
        {
            captionNode = FindWithInElement(node, 0, THML_CAPTION, NODE_TYPE_BEGIN_TAG);
            m_matrixArray.Get()->SetParent(m_rich->GetFocusObject());
            rows = m_parserNodeData[node].param1;
            columns = m_parserNodeData[node].param2;

            if (captionNode == NODE_ID_INVALID)
            {
                m_matrixArray.Get()->SetHasCaption(false);
            }
            else
            {
                rows ++;
                m_matrixArray.Get()->SetHasCaption(true);
            }

            swUI32 width = 100/columns;
            cellAttr.GetTextBoxAttr().GetWidth().SetValue(width, wxTEXT_ATTR_UNITS_PERCENTAGE);
            m_matrixArray.Get()->SizeMatrix(rows, columns);
            m_matrixArray.Get()->Clear();
            m_matrixArray.Get()->SetTable(m_rich->WriteTable(rows, columns, m_richAttr, cellAttr));

            for (int col = 0; col < m_matrixArray.Get()->GetTable()->GetColumnCount(); col ++)
            {
                for (int row = 0; row < m_matrixArray.Get()->GetTable()->GetRowCount(); row ++)
                {
                    cell = m_matrixArray.Get()->GetTable()->GetCell(row, col);
                    if (cell)
                    {
                        cell->Clear();
                        cell->GetBuffer()->SetDefaultStyle(m_richAttr);
                    }
                }
            }

            m_rich->SetInsertionPointEnd();
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        if (m_matrixArray.GetCount())
        {
            m_rich->SetFocusObject(m_matrixArray.Get()->GetParent());
            m_matrixArray.Delete();
            m_rich->SetInsertionPointEnd();
        }
    }

    return node;
}

swUI32 SwRichTextInterface::Ontd(swUI32 node)
{
    SwString buffer;
    wxRichTextCell* cell;
    swUI16 rowPos = 0, columnPos = 0;
    swI32 rowSpan = 1;
    swI32 columnSpan = 1;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (m_matrixArray.Get())
        {
            rowPos = m_matrixArray.Get()->GetRowPos();
            columnPos = m_matrixArray.Get()->FindInRow(rowPos, 0, 0);
            cell = m_matrixArray.Get()->GetTable()->GetCell(rowPos, columnPos);

            if (cell)
            {
                m_rich->SetFocusObject(cell);

                if (GetNamedValueFromNode(node, "colspan", buffer))
                {
                    columnSpan = buffer.Atoi();
                    if (cell)
                        cell->SetColSpan(columnSpan);
                }

                if (GetNamedValueFromNode(node, "rowspan", buffer))
                {
                    rowSpan = buffer.Atoi();
                    if (cell)
                        cell->SetRowSpan(rowSpan);
                }
            }
        }

        m_matrixArray.Get()->SetQuadrant(rowPos, columnPos, rowSpan, columnSpan, 255);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ontfoot(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        GetBlockStyle(node);
        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onth(swUI32 node)
{
    SwString buffer;
    wxRichTextCell* cell = NULL;
    swUI16 rowPos = 0, columnPos = 0;
    swI32 rowSpan = 1;
    swI32 columnSpan = 1;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (m_markupType == MARKUP_THML)
            SwThMLCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        else
            SwHtmlCss::GetElementStyle(GetNodeElementIdentifier(node), m_attrList);
        GetBlockStyle(node);

        if (m_matrixArray.Get())
        {
            rowPos = m_matrixArray.Get()->GetRowPos();
            columnPos = m_matrixArray.Get()->FindInRow(rowPos, 0, 0);
            cell = m_matrixArray.Get()->GetTable()->GetCell(rowPos, columnPos);

            if (cell)
            {
                m_rich->SetFocusObject(cell);

                if (GetNamedValueFromNode(node, "colspan", buffer))
                {
                    columnSpan = buffer.Atoi();
                    if (cell)
                        cell->SetColSpan(columnSpan);
                }
                if (GetNamedValueFromNode(node, "rowspan", buffer))
                {
                    rowSpan = buffer.Atoi();
                    if (cell)
                        cell->SetRowSpan(rowSpan);
                }
            }
        }

        m_matrixArray.Get()->SetQuadrant(rowPos, columnPos, rowSpan, columnSpan, 255);
        m_richAttr.SetAlignment(wxTEXT_ALIGNMENT_CENTER);
        m_richAttr.SetFontWeight(wxFONTWEIGHT_BOLD);

        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onthead(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        GetBlockStyle(node);
        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Ontr(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        GetBlockStyle(node);
        SetEndStyleFlag(node, BeginBlockStyle(node));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_matrixArray.Get()->IncRowPos();
        EndBlockStyle(node);
    }

    return node;
}
