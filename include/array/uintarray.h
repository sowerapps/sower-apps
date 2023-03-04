///////////////////////////////////////////////////////////////////
// Name:        uintarray.h
// Purpose:     Unsigned 8, 16 & 32 bit arrays.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef UINTARRAY_H
#define UINTARRAY_H

#include "../sowerbase.h"

class SOWERBASEEXP Swui8Array
{
public:
    Swui8Array();
    Swui8Array(Swui8Array& other);
    virtual ~Swui8Array();

    operator swUI8 * ();
    bool operator += (swUI8 n);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    swUI8 * GetArray();
    bool Copy(const swUI8 * src, swUI32 length);
    void SetAt(swUI32 pos, swUI8 n);
    swUI8 GetAt(swUI32 pos);
    swUI8 * Get(swUI32 pos);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    swUI8 * m_array;
    swUI32   m_size;
    swUI32   m_count;
};

class SOWERBASEEXP Swui16Array
{
public:
    Swui16Array();
    Swui16Array(Swui16Array& other);
    virtual ~Swui16Array();

    operator swUI16 * ();
    bool operator += (swUI16 n);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    swUI16 * GetArray();
    bool Copy(const swUI16 * src, swUI32 length);
    void SetAt(swUI32 pos, swUI16 n);
    swUI16 GetAt(swUI32 pos);
    swUI16 * Get(swUI32 pos);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    swUI16 * m_array;
    swUI32   m_size;
    swUI32   m_count;
};


class SOWERBASEEXP Swui32Array
{
public:
    Swui32Array();
    Swui32Array(Swui32Array& other);
    virtual ~Swui32Array();

    operator swUI32 * ();
    bool operator += (swUI32 n);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    swUI32 * GetArray();
    bool Copy(const swUI32 * src, swUI32 length);
    void SetAt(swUI32 pos, swUI32 n);
    swUI32 GetAt(swUI32 pos);
    swUI32 * Get(swUI32 pos);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    swUI32 * m_array;
    swUI32   m_size;
    swUI32   m_count;
};

#endif // UINTARRAY_H
