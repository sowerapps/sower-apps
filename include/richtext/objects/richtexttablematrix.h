///////////////////////////////////////////////////////////////////
// Name:        richtexttablematrix.h
// Purpose:     Array for keeping track of proper cell to
//              write content to in a table.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef RICHTEXTTABLEMATRIX_H
#define RICHTEXTTABLEMATRIX_H

#include "../richtextctrlext.h"

class SOWERBASEEXP SwRichTextTableMatrix
{
public:
    SwRichTextTableMatrix();
    virtual ~SwRichTextTableMatrix();

    void Init();
    void Reset();
    void Copy(SwRichTextTableMatrix & matrix);
    swUI32 GetValue(swUI16 row, swUI16 column);
    swUI32 SetValue(swUI16 row, swUI16 column, swUI8 value);
    swUI32 SetQuadrant(swUI16 row, swUI16 column, swUI16 rowspan, swUI16 columnspan, swUI8 value);
    swUI32 FindInRow(swUI16 row, swUI16 column, swUI8 value);
    swUI32 FindInColumn(swUI16 column, swUI16 row, swUI8 value);
    bool SizeMatrix(swUI16 rows, swUI16 columns);
    void Clear();
    swUI16 GetRows();
    swUI16 GetColumns();
    void SetTable(wxRichTextTable * table);
    wxRichTextTable * GetTable();
    void SetParent(wxRichTextParagraphLayoutBox * parent);
    wxRichTextParagraphLayoutBox * GetParent();
    void SetHasCaption(bool hascaption);
    bool GetHasCaption();
    swUI16 GetRowPos();
    bool IncRowPos();
    swUI16 GetColGroupPos();
    void SetColGroupPos(swUI16 pos);
    void IncColGroupPos(swUI16 inc);

protected:
    wxRichTextTable * m_table;
    wxRichTextParagraphLayoutBox * m_parent;
    swUI16  m_curRow;
    swUI16  m_colgroupPos;
    bool    m_hasCaption;
    swUI16  m_rows;
    swUI16  m_columns;
    swUI8 * m_array;
};

class SOWERBASEEXP SwRichTextTableMatrixArray
{
public:
    SwRichTextTableMatrixArray();
    virtual ~SwRichTextTableMatrixArray();

    void Reset();
    swUI32 Add();
    void ShiftNodesUp(swUI32 startNode);
    bool Delete();
    bool Delete(swUI32 pos);
    SwRichTextTableMatrix * Get();
    SwRichTextTableMatrix * Get(swUI32 pos);
    swUI32 GetCount();
    swUI32 GetActiveTablePos();

protected:
    SwRichTextTableMatrix * m_array;
    bool IncreaseArray();
    void ReleaseArray();
    swUI32 AssignObject();
    swUI32 m_arrayPos;
    swUI32 m_objectsAllocated;
};
#endif // RICHTEXTTABLEMATRIX_H
