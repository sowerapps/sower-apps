///////////////////////////////////////////////////////////////////
// Name:        pointarray.cpp
// Purpose:     SwPoint array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/pointarray.h"

SwPointArray::SwPointArray()
{
    Init();
}

SwPointArray::SwPointArray(SwPointArray& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

SwPointArray::~SwPointArray()
{
    if (m_array)
        free(m_array);
}

SwPointArray::operator SwPoint * ()
{
    return m_array;
}

bool SwPointArray::operator += (SwPoint pt)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, pt);
    m_count ++;

    return true;
}

void SwPointArray::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void SwPointArray::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void SwPointArray::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(SwPoint));
}

swUI32 SwPointArray::Size(swUI32 size, bool shrink)
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

    SwPoint * p = (SwPoint *) realloc((void *) m_array, size * sizeof(SwPoint));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 SwPointArray::GetSize()
{
    return m_size;
}

SwPoint * SwPointArray::GetArray()
{
    return m_array;
}

bool SwPointArray::Copy(const SwPoint * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(SwPoint));

    m_count = length;

    return true;
}

void SwPointArray::SetAt(swUI32 pos, SwPoint pt)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = pt;
}

const SwPoint SwPointArray::GetAt(swUI32 pos)
{
    SwPoint dummy;
    dummy.x = dummy.y = 0;

    if (pos >= GetSize())
        return dummy;

    return m_array[pos];
}

SwPoint * SwPointArray::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

void SwPointArray::SetCount(swUI32 count)
{
    m_count = count;
}

void SwPointArray::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwPointArray::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}

swUI32 SwPointArray::GetCount()
{
    return m_count;
}
