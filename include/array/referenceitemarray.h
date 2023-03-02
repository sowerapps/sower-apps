///////////////////////////////////////////////////////////////////
// Name:        referenceitemarray.h
// Purpose:     SwReferenceItem array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef REFERENCEITEMARRAY_H
#define REFERENCEITEMARRAY_H

#include "../sowerbase.h"

struct SwReferenceItem
{
    swUI32      begin;
    swUI32      end;
    swUI8       book;
    swUI8       chapter;
    swUI8       verseStart;
    swUI8       verseEnd;
    void Reset() { begin = 0; end = 0;  book = 0; chapter = 0; verseStart = 0; verseEnd = 0; }
};

class SOWERBASEEXP SwReferenceItemArray
{
public:
    SwReferenceItemArray();
    SwReferenceItemArray(SwReferenceItemArray& other);
    virtual ~SwReferenceItemArray();

    operator SwReferenceItem * ();
    bool operator += (SwReferenceItem item);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    SwReferenceItem * GetArray();
    bool Add(SwReferenceItem item);
    bool Copy(const SwReferenceItem * src, swUI32 length);
    void SetAt(swUI32 pos, SwReferenceItem item);
    const SwReferenceItem GetAt(swUI32 pos);
    SwReferenceItem * Get(swUI32 pos);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    SwReferenceItem * m_array;
    swUI32            m_size;
    swUI32            m_count;
};

#endif // TEXTRANGEARRAY_H
