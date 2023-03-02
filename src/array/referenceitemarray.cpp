///////////////////////////////////////////////////////////////////
// Name:        referenceitemarray.cpp
// Purpose:     SwReferenceItem array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/referenceitemarray.h"

SwReferenceItemArray::SwReferenceItemArray()
{
    Init();
}

SwReferenceItemArray::SwReferenceItemArray(SwReferenceItemArray& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

SwReferenceItemArray::~SwReferenceItemArray()
{
    if (m_array)
        free(m_array);
}

SwReferenceItemArray::operator SwReferenceItem * ()
{
    return m_array;
}

bool SwReferenceItemArray::operator += (SwReferenceItem item)
{

    if (m_count >= GetSize() && !Size(m_count + 21))
        return false;

    SetAt(m_count, item);
    m_count ++;

    return true;
}

void SwReferenceItemArray::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(21))
        return;

    Zero();
}

void SwReferenceItemArray::Reset()
{
    Size(21);
    Zero();
    SetCount(0);
}

void SwReferenceItemArray::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(SwReferenceItem));
}

swUI32 SwReferenceItemArray::Size(swUI32 size, bool shrink)
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

    SwReferenceItem * p = (SwReferenceItem *) realloc((void *) m_array, size * sizeof(SwReferenceItem));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 SwReferenceItemArray::GetSize()
{
    return m_size;
}

SwReferenceItem * SwReferenceItemArray::GetArray()
{
    return m_array;
}

bool SwReferenceItemArray::Add(SwReferenceItem item)
{

    if (m_count >= GetSize() && !Size(m_count + 21))
        return false;

    SetAt(m_count, item);
    m_count ++;

    return true;
}

bool SwReferenceItemArray::Copy(const SwReferenceItem * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(SwReferenceItem));

    m_count = length;

    return true;
}

void SwReferenceItemArray::SetAt(swUI32 pos, SwReferenceItem item)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = item;
}

const SwReferenceItem SwReferenceItemArray::GetAt(swUI32 pos)
{
    SwReferenceItem dummy;
    dummy.begin = dummy.end = -1;

    if (pos >= GetSize())
        return dummy;

    return m_array[pos];
}

SwReferenceItem * SwReferenceItemArray::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

void SwReferenceItemArray::SetCount(swUI32 count)
{
    m_count = count;
}

swUI32 SwReferenceItemArray::GetCount()
{
    return m_count;
}

void SwReferenceItemArray::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwReferenceItemArray::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}
