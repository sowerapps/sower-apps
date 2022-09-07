///////////////////////////////////////////////////////////////////
// Name:        moduleitemarray.cpp
// Purpose:     SwModuleItem array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/moduleitemarray.h"

SwModuleItemArray::SwModuleItemArray()
{
    Init();
}

SwModuleItemArray::SwModuleItemArray(SwModuleItemArray& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

SwModuleItemArray::~SwModuleItemArray()
{
    if (m_array)
        free(m_array);
}

SwModuleItemArray::operator SwModuleItem * ()
{
    return m_array;
}

bool SwModuleItemArray::operator += (SwModuleItem mi)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, mi);
    m_count ++;

    return true;
}

void SwModuleItemArray::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void SwModuleItemArray::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void SwModuleItemArray::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(SwModuleItem));
}

swUI32 SwModuleItemArray::Size(swUI32 size, bool shrink)
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

    SwModuleItem * p = (SwModuleItem *) realloc((void *) m_array, size * sizeof(SwModuleItem));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 SwModuleItemArray::GetSize()
{
    return m_size;
}

SwModuleItem * SwModuleItemArray::GetArray()
{
    return m_array;
}

bool SwModuleItemArray::Copy(const SwModuleItem * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(SwModuleItem));

    m_count = length;

    return true;
}

void SwModuleItemArray::SetAt(swUI32 pos, SwModuleItem mi)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = mi;
}

const SwModuleItem SwModuleItemArray::GetAt(swUI32 pos)
{
    SwModuleItem dummy;
    dummy.Reset();

    if (pos >= GetSize())
        return dummy;

    return m_array[pos];
}

SwModuleItem * SwModuleItemArray::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

void SwModuleItemArray::SetCount(swUI32 count)
{
    m_count = count;
}

swUI32 SwModuleItemArray::GetCount()
{
    return m_count;
}

void SwModuleItemArray::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwModuleItemArray::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}

