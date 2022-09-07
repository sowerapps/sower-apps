///////////////////////////////////////////////////////////////////
// Name:        SwTextRangeArray.h
// Purpose:     SwTextRange array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef TEXTRANGEARRAY_H
#define TEXTRANGEARRAY_H

#include "../sowerbase.h"

class SOWERBASEEXP SwTextRangeArray
{
public:
    SwTextRangeArray();
    SwTextRangeArray(SwTextRangeArray& other);
    virtual ~SwTextRangeArray();

    operator SwTextRange * ();
    bool operator += (SwTextRange range);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    SwTextRange * GetArray();
    bool Copy(const SwTextRange * src, swUI32 length);
    void SetAt(swUI32 pos, SwTextRange range);
    const SwTextRange GetAt(swUI32 pos);
    SwTextRange * Get(swUI32 pos);
    bool Find(SwTextRange range);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    SwTextRange * m_array;
    swUI32        m_size;
    swUI32        m_count;
};

#endif // TEXTRANGEARRAY_H
