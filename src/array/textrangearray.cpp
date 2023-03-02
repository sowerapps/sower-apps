///////////////////////////////////////////////////////////////////
// Name:        textrangearray.cpp
// Purpose:     SwTextRange array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/textrangearray.h"

SwTextRangeArray::SwTextRangeArray()
{
    Init();
}

SwTextRangeArray::SwTextRangeArray(SwTextRangeArray& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

SwTextRangeArray::~SwTextRangeArray()
{
    if (m_array)
        free(m_array);
}

SwTextRangeArray::operator SwTextRange * ()
{
    return m_array;
}

bool SwTextRangeArray::operator += (SwTextRange range)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, range);
    m_count ++;

    return true;
}

void SwTextRangeArray::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void SwTextRangeArray::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void SwTextRangeArray::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(SwTextRange));
}

swUI32 SwTextRangeArray::Size(swUI32 size, bool shrink)
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

    SwTextRange * p = (SwTextRange *) realloc((void *) m_array, size * sizeof(SwTextRange));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 SwTextRangeArray::GetSize()
{
    return m_size;
}

SwTextRange * SwTextRangeArray::GetArray()
{
    return m_array;
}

bool SwTextRangeArray::Copy(const SwTextRange * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(SwTextRange));

    m_count = length;

    return true;
}

void SwTextRangeArray::SetAt(swUI32 pos, SwTextRange range)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = range;
}

const SwTextRange SwTextRangeArray::GetAt(swUI32 pos)
{
    SwTextRange dummy;
    dummy.begin = dummy.end = -1;

    if (pos >= GetSize())
        return dummy;

    return m_array[pos];
}

SwTextRange * SwTextRangeArray::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

bool SwTextRangeArray::Find(SwTextRange range)
{
    for (swUI32 i = 0; i < m_count; i ++)
    {
        if (GetAt(i).begin == range.begin &&
            GetAt(i).end == range.end)
        {
            return true;
        }
    }

    return false;
}

void SwTextRangeArray::SetCount(swUI32 count)
{
    m_count = count;
}

swUI32 SwTextRangeArray::GetCount()
{
    return m_count;
}

void SwTextRangeArray::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwTextRangeArray::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}
