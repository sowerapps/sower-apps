///////////////////////////////////////////////////////////////////
// Name:        uintarray.cpp
// Purpose:     Unsigned 8, 16 & 32 bit arrays.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/uintarray.h"

Swui8Array::Swui8Array()
{
    Init();
}

Swui8Array::Swui8Array(Swui8Array& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

Swui8Array::~Swui8Array()
{
    if (m_array)
        free(m_array);
}

Swui8Array::operator swUI8 * ()
{
    return m_array;
}

bool Swui8Array::operator += (swUI8 n)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, n);
    m_count ++;

    return true;
}

void Swui8Array::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void Swui8Array::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void Swui8Array::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(swUI8));
}

swUI32 Swui8Array::Size(swUI32 size, bool shrink)
{
    if (!size && m_array && shrink)
    {
        free(m_array);
        m_array = NULL;
        m_size = 0;
        m_count = 0;
        return 0;
    }

    if (size < 7)
        size = 7;

    if (m_array && m_size >= size && !shrink)
        return m_size;

    swUI8 * p = (swUI8 *) realloc((void *) m_array, size * sizeof(swUI8));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 Swui8Array::GetSize()
{
    return m_size;
}

swUI8 * Swui8Array::GetArray()
{
    return m_array;
}

bool Swui8Array::Copy(const swUI8 * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(swUI8));

    m_count = length;

    return true;
}

void Swui8Array::SetAt(swUI32 pos, swUI8 n)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = n;
}

swUI8 Swui8Array::GetAt(swUI32 pos)
{
    if (pos >= GetSize())
        return 0;

    return m_array[pos];
}

swUI8 * Swui8Array::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

void Swui8Array::SetCount(swUI32 pos)
{
    m_count = pos;
}

void Swui8Array::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void Swui8Array::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}

swUI32 Swui8Array::GetCount()
{
    return m_count;
}


Swui16Array::Swui16Array()
{
    Init();
}

Swui16Array::Swui16Array(Swui16Array& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

Swui16Array::~Swui16Array()
{
    if (m_array)
        free(m_array);
}

Swui16Array::operator swUI16 * ()
{
    return m_array;
}

bool Swui16Array::operator += (swUI16 n)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, n);
    m_count ++;

    return true;
}

void Swui16Array::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void Swui16Array::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void Swui16Array::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(swUI16));
}

swUI32 Swui16Array::Size(swUI32 size, bool shrink)
{
    if (!size && m_array && shrink)
    {
        free(m_array);
        m_array = NULL;
        m_size = 0;
        m_count = 0;
        return 0;
    }

    if (size < 7)
        size = 7;

    if (m_array && m_size >= size && !shrink)
        return m_size;

    swUI16 * p = (swUI16 *) realloc((void *) m_array, size * sizeof(swUI16));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 Swui16Array::GetSize()
{
    return m_size;
}

swUI16 * Swui16Array::GetArray()
{
    return m_array;
}

bool Swui16Array::Copy(const swUI16 * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(swUI16));

    m_count = length;

    return true;
}

void Swui16Array::SetAt(swUI32 pos, swUI16 n)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = n;
}

swUI16 Swui16Array::GetAt(swUI32 pos)
{
    if (pos >= GetSize())
        return 0;

    return m_array[pos];
}

swUI16 * Swui16Array::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

void Swui16Array::SetCount(swUI32 pos)
{
    m_count = pos;
}

void Swui16Array::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void Swui16Array::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}

swUI32 Swui16Array::GetCount()
{
    return m_count;
}


Swui32Array::Swui32Array()
{
    Init();
}

Swui32Array::Swui32Array(Swui32Array& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

Swui32Array::~Swui32Array()
{
    if (m_array)
        free(m_array);
}

Swui32Array::operator swUI32 * ()
{
    return m_array;
}

bool Swui32Array::operator += (swUI32 n)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, n);
    m_count ++;

    return true;
}

void Swui32Array::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void Swui32Array::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void Swui32Array::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(swUI32));
}

swUI32 Swui32Array::Size(swUI32 size, bool shrink)
{
    if (!size && m_array && shrink)
    {
        free(m_array);
        m_array = NULL;
        m_size = 0;
        m_count = 0;
        return 0;
    }

    if (size < 7)
        size = 7;

    if (m_array && m_size >= size && !shrink)
        return m_size;

    swUI32 * p = (swUI32 *) realloc((void *) m_array, size * sizeof(swUI32));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 Swui32Array::GetSize()
{
    return m_size;
}

swUI32 * Swui32Array::GetArray()
{
    return m_array;
}

bool Swui32Array::Copy(const swUI32 * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(swUI32));

    m_count = length;

    return true;
}

void Swui32Array::SetAt(swUI32 pos, swUI32 n)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = n;
}

swUI32 Swui32Array::GetAt(swUI32 pos)
{
    if (pos >= GetSize())
        return 0;

    return m_array[pos];
}

swUI32 * Swui32Array::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

void Swui32Array::SetCount(swUI32 count)
{
    m_count = count;
}

void Swui32Array::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void Swui32Array::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}

swUI32 Swui32Array::GetCount()
{
    return m_count;
}
