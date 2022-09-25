///////////////////////////////////////////////////////////////////
// Name:        cardarray.cpp
// Purpose:     SwCatalogCard array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/cardarray.h"

SwCatalogCardArray::SwCatalogCardArray()
{
    Init();
}

SwCatalogCardArray::SwCatalogCardArray(SwCatalogCardArray& other)
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    Size(other.GetSize());
    Copy(other.GetArray(), other.GetSize());
}

SwCatalogCardArray::~SwCatalogCardArray()
{
    if (m_array)
        free(m_array);
}

SwCatalogCardArray::operator SwCatalogCard * ()
{
    return m_array;
}

bool SwCatalogCardArray::operator += (SwCatalogCard card)
{

    if (m_count >= GetSize() && !Size(m_count + 7))
        return false;

    SetAt(m_count, card);
    m_count ++;

    return true;
}

void SwCatalogCardArray::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(7))
        return;

    Zero();
}

void SwCatalogCardArray::Reset()
{
    Size(7);
    Zero();
    SetCount(0);
}

void SwCatalogCardArray::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size * sizeof(SwCatalogCard));
}

swUI32 SwCatalogCardArray::Size(swUI32 size, bool shrink)
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

    SwCatalogCard * p = (SwCatalogCard *) realloc((void *) m_array, size * sizeof(SwCatalogCard));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 SwCatalogCardArray::GetSize()
{
    return m_size;
}

SwCatalogCard * SwCatalogCardArray::GetArray()
{
    return m_array;
}

bool SwCatalogCardArray::Copy(const SwCatalogCard * src, swUI32 length)
{
    if (!src)
        return false;

    if (!Size(length))
        return false;

    memcpy(m_array, (void *) src, length * sizeof(SwCatalogCard));

    m_count = length;

    return true;
}

void SwCatalogCardArray::SetAt(swUI32 pos, SwCatalogCard card)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = card;
}

const SwCatalogCard SwCatalogCardArray::GetAt(swUI32 pos)
{
    SwCatalogCard dummy;
    dummy.Zero();

    if (pos >= GetSize())
        return dummy;

    return m_array[pos];
}

SwCatalogCard * SwCatalogCardArray::Get(swUI32 pos)
{
    if (pos >= GetSize())
        return NULL;

    return &m_array[pos];
}

swUI16 SwCatalogCardArray::FindByAbbrev(const char * abbrev)
{
    swUI16 pos = 0;

    if (!abbrev)
        return NODE_ID_INVALID_16;

    while (pos < m_count)
    {
        if (strcmp(abbrev, m_array[pos].moduleAbbreviation) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwCatalogCardArray::FindById(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_count)
    {
        if (strcmp(id, m_array[pos].moduleIdentifier) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwCatalogCardArray::FindByTitle(const char * title)
{
    swUI16 pos = 0;

    if (!title)
        return NODE_ID_INVALID_16;

    while (pos < m_count)
    {
        if (strcmp(title, m_array[pos].moduleTitle) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwCatalogCardArray::FindByCcelFileName(const char * name)
{
    swUI16 pos = 0;

    if (!name)
        return NODE_ID_INVALID_16;

    while (pos < m_count)
    {
        if (strcmp(name, m_array[pos].ccelFileName) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

void SwCatalogCardArray::GetGroupList(wxChoice * choice)
{
    if (!choice)
        return;

    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < m_count; i++)
    {
        if (m_array[i].GetGroupLength() && (choice->FindString(m_array[i].GetGroup()) == wxNOT_FOUND))
        {
            data = new SwClientData(i);
            buffer.Copy(m_array[i].GetGroup());
            choice->Append(buffer.GetArray(), data);
        }
    }
}


void SwCatalogCardArray::GetGroupList(wxComboBox * choice)
{
    if (!choice)
        return;

    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < m_count; i++)
    {
        if (m_array[i].GetGroupLength() && (choice->FindString(m_array[i].GetGroup()) == wxNOT_FOUND))
        {
            data = new SwClientData(i);
            buffer.Copy(m_array[i].GetGroup());
            choice->Append(buffer.GetArray(), data);
        }
    }
}

void SwCatalogCardArray::SetCount(swUI32 count)
{
    m_count = count;
}

swUI32 SwCatalogCardArray::GetCount()
{
    return m_count;
}

void SwCatalogCardArray::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwCatalogCardArray::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}
