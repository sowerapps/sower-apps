///////////////////////////////////////////////////////////////////
// Name:        richtexttablematrix.cpp
// Purpose:     Array for keeping track of proper cell to
//              write content to in a table.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/objects/richtexttablematrix.h"

SwRichTextTableMatrix::SwRichTextTableMatrix()
{
    m_rows = 0;
    m_columns = 0;
    m_array = NULL;
}

SwRichTextTableMatrix::~SwRichTextTableMatrix()
{
    if (m_array)
    {
        free(m_array);
    }
}

void SwRichTextTableMatrix::Init()
{
    m_array = NULL;
    Reset();
}

void SwRichTextTableMatrix::Reset()
{
    m_table = NULL;
    m_parent = NULL;
    m_curRow = 0;
    m_colgroupPos = 0;
    m_hasCaption = false;

    Clear();
}

void SwRichTextTableMatrix::Copy(SwRichTextTableMatrix & matrix)
{
    Reset();
    m_table = matrix.GetTable();
    m_parent = matrix.GetParent();
    m_curRow = matrix.GetRowPos();
    m_colgroupPos = matrix.GetColGroupPos();
    m_hasCaption = matrix.GetHasCaption();

    SizeMatrix(matrix.GetRows(), matrix.GetColumns());

    for (swUI16 row = 0; row < m_rows; row ++)
    {
        for (swUI16 column = 0; column < m_columns; column ++)
        {
            SetValue(row, column, matrix.GetValue(row, column));
        }
    }
}

swUI32 SwRichTextTableMatrix::GetValue(swUI16 row, swUI16 column)
{
    if (row >= m_rows || column >= m_columns)
        return NODE_ID_INVALID;

    return m_array[(row * m_columns) + column];
}

swUI32 SwRichTextTableMatrix::SetValue(swUI16 row, swUI16 column, swUI8 value)
{
    if (row >= m_rows || column >= m_columns)
        return NODE_ID_INVALID;

    m_array[(row * m_columns) + column] = value;

    return value;
}

swUI32 SwRichTextTableMatrix::SetQuadrant(swUI16 row, swUI16 column, swUI16 rowspan, swUI16 columnspan, swUI8 value)
{
    swUI32 result;

    for (swUI16 rowpos = row; rowpos < row + rowspan; rowpos ++)
    {
        for (swUI16 columnpos = column; columnpos < column + columnspan; columnpos ++)
        {
            result = SetValue(rowpos, columnpos, value);

            if (result != value)
                return NODE_ID_INVALID;
        }
    }

    return value;
}

swUI32 SwRichTextTableMatrix::FindInRow(swUI16 row, swUI16 column, swUI8 value)
{
    swUI32 result;

    for (swUI16 columnpos = column; columnpos < m_columns; columnpos ++)
    {
        result = GetValue(row, columnpos);

        if (result == NODE_ID_INVALID)
            break;

        if (result == value)
            return columnpos;
    }

    return NODE_ID_INVALID;
}

swUI32 SwRichTextTableMatrix::FindInColumn(swUI16 column, swUI16 row, swUI8 value)
{
    swUI32 result;

    for (swUI16 rowpos = row; rowpos < m_rows; rowpos ++)
    {
        result = GetValue(rowpos, column);

        if (result == NODE_ID_INVALID)
            break;

        if (result == value)
            return rowpos;
    }

    return NODE_ID_INVALID;
}

bool SwRichTextTableMatrix::SizeMatrix(swUI16 rows, swUI16 columns)
{
    if (rows * columns < 1)
    {
        free(m_array);
        m_array = NULL;
        m_rows = 0;
        m_columns = 0;
        return true;
    }

    swUI8 * p = (swUI8 *) realloc((void *) m_array, rows * columns);

    if (p)
    {
        m_rows = rows;
        m_columns = columns;
        m_array = p;
        return true;
    }

    return false;
}

void SwRichTextTableMatrix::Clear()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_rows * m_columns);
}

swUI16 SwRichTextTableMatrix::GetRows()
{
    return m_rows;
}

swUI16 SwRichTextTableMatrix::GetColumns()
{
    return m_columns;
}

void SwRichTextTableMatrix::SetTable(wxRichTextTable * table)
{
    m_table = table;
}

wxRichTextTable * SwRichTextTableMatrix::GetTable()
{
    return m_table;
}

void SwRichTextTableMatrix::SetParent(wxRichTextParagraphLayoutBox * parent)
{
    m_parent = parent;
}

wxRichTextParagraphLayoutBox * SwRichTextTableMatrix::GetParent()
{
    return m_parent;
}

void SwRichTextTableMatrix::SetHasCaption(bool hascaption)
{
    m_hasCaption = hascaption;
}

bool SwRichTextTableMatrix::GetHasCaption()
{
    return m_hasCaption;
}

swUI16 SwRichTextTableMatrix::GetRowPos()
{
    return m_curRow;
}

bool SwRichTextTableMatrix::IncRowPos()
{
    if (m_curRow + 1 >= m_rows)
        return false;

    m_curRow ++;

    return true;
}

swUI16 SwRichTextTableMatrix::GetColGroupPos()
{
    return m_colgroupPos;
}

void SwRichTextTableMatrix::SetColGroupPos(swUI16 pos)
{
    m_colgroupPos = pos;
}

void SwRichTextTableMatrix::IncColGroupPos(swUI16 inc)
{
    m_colgroupPos += inc;
}

SwRichTextTableMatrixArray::SwRichTextTableMatrixArray()
{
    m_array = NULL;
    m_arrayPos = 0;
    m_objectsAllocated = 0;
}

SwRichTextTableMatrixArray::~SwRichTextTableMatrixArray()
{
    ReleaseArray();
}

void SwRichTextTableMatrixArray::Reset()
{
    swUI32 pos = 0;

    if (!m_array)
        return;

    while(pos < m_objectsAllocated)
    {
        m_array[pos].Reset();

        pos ++;
    }

    m_arrayPos = 0;
}

swUI32 SwRichTextTableMatrixArray::Add()
{
    swUI32 id = AssignObject();

    if (id == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    m_array[id].Reset();

    return id;
}

swUI32 SwRichTextTableMatrixArray::AssignObject()
{
    if (m_arrayPos >= m_objectsAllocated && !IncreaseArray())
        return NODE_ID_INVALID;

    m_arrayPos ++;

    return m_arrayPos - 1;
}

bool SwRichTextTableMatrixArray::IncreaseArray()
{
    swUI32 pos = m_objectsAllocated;

    if (m_objectsAllocated >= NODE_ID_INVALID - 11)
        return false;

    SwRichTextTableMatrix * p = (SwRichTextTableMatrix *) realloc((void *) m_array, (m_objectsAllocated + 10) * sizeof(SwRichTextTableMatrix));

    if (p)
    {
        m_objectsAllocated += 10;
        m_array = p;

        while (pos < m_objectsAllocated)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

void SwRichTextTableMatrixArray::ReleaseArray()
{
    swUI32 pos = 0;

    if (m_array)
    {
        while (pos < m_objectsAllocated)
        {
            m_array[pos].SizeMatrix(0, 0);
            pos ++;
        }

        free(m_array);
    }

    m_array = NULL;
    m_objectsAllocated = 0;
    m_arrayPos = 0;
}

SwRichTextTableMatrix * SwRichTextTableMatrixArray::Get()
{
    if (!m_arrayPos)
    {
        return NULL;
    }

    return Get(m_arrayPos - 1);
}

bool SwRichTextTableMatrixArray::Delete()
{
    if (!m_arrayPos)
        return false;

    return Delete(m_arrayPos - 1);
}

bool SwRichTextTableMatrixArray::Delete(swUI32 pos)
{
    if (pos >= m_arrayPos)
        return false;

    if (pos != m_arrayPos - 1)
    {
        ShiftNodesUp(pos + 1);
    }
    else
    {
        m_arrayPos --;
        m_array[m_arrayPos].Reset();
    }

    return true;
}

SwRichTextTableMatrix * SwRichTextTableMatrixArray::Get(swUI32 pos)
{
    if (m_arrayPos < 1)
    {
        return NULL;
    }

    if (pos >= m_arrayPos)
        return NULL;

    return &m_array[pos];
}

void SwRichTextTableMatrixArray::ShiftNodesUp(swUI32 startNode)
{
    if (m_arrayPos <= 1)
    {
        m_arrayPos = 0;
        return;
    }
    else if (startNode == 0)
        return;
    else if (startNode > m_arrayPos - 1)
    {
        return;
    }

    swUI32 pos = startNode;

    while(pos < m_arrayPos)
    {
        m_array[pos - 1].Copy(m_array[pos]);
        pos ++;
    }

    m_arrayPos --;

    return;
}

swUI32 SwRichTextTableMatrixArray::GetCount()
{
    return m_arrayPos;
}

swUI32 SwRichTextTableMatrixArray::GetActiveTablePos()
{
    if (!m_arrayPos)
        return NODE_ID_INVALID;

    return m_arrayPos - 1;
}
