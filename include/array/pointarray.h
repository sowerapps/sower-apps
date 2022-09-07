///////////////////////////////////////////////////////////////////
// Name:        pointarray.h
// Purpose:     SwPoint array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef POINTARRAY_H
#define POINTARRAY_H

#include "../sowerbase.h"

class SOWERBASEEXP SwPointArray
{
public:
    SwPointArray();
    SwPointArray(SwPointArray& other);
    virtual ~SwPointArray();

    operator SwPoint * ();
    bool operator += (SwPoint pt);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    SwPoint * GetArray();
    bool Copy(const SwPoint * src, swUI32 length);
    void SetAt(swUI32 pos, SwPoint pt);
    const SwPoint GetAt(swUI32 pos);
    SwPoint * Get(swUI32 pos);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    SwPoint * m_array;
    swUI32    m_size;
    swUI32    m_count;
};

#endif // POINTARRAY_H
