///////////////////////////////////////////////////////////////////
// Name:        cardarray.h
// Purpose:     SwCatalogCard array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CATALOGCARDARRAY_H
#define CATALOGCARDARRAY_H

#include "../sowerbase.h"
#include "../module/modulebase.h"

class SOWERBASEEXP SwCatalogCardArray
{
public:
    SwCatalogCardArray();
    SwCatalogCardArray(SwCatalogCardArray& other);
    virtual ~SwCatalogCardArray();

    operator SwCatalogCard * ();
    bool operator += (SwCatalogCard card);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    SwCatalogCard * GetArray();
    bool Copy(const SwCatalogCard * src, swUI32 length);
    void SetAt(swUI32 pos, SwCatalogCard card);
    const SwCatalogCard GetAt(swUI32 pos);
    SwCatalogCard * Get(swUI32 pos);
    swUI16 FindByAbbrev(const char * abbrev);
    swUI16 FindById(const char * id);
    swUI16 FindByTitle(const char * title);
    swUI16 FindByCcelFileName(const char * name);
    void GetGroupList(wxChoice * choice);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    SwCatalogCard * m_array;
    swUI32          m_size;
    swUI32          m_count;
};

#endif // CATALOGCARDARRAY_H
