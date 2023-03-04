///////////////////////////////////////////////////////////////////
// Name:        historylist.cpp
// Purpose:     Non-Gui SwHistoryItem list.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/controls/historylist.h"

SwHistoryList::SwHistoryList()
{
    m_array = NULL;
    m_count = 0;
    m_size = 0;
    m_position = 0;
}

SwHistoryList::~SwHistoryList()
{
    if (m_array)
        free(m_array);
}

bool SwHistoryList::Size(swUI32 size)
{
    if (!size && m_array)
    {
        free(m_array);
        m_array = NULL;
        m_count = 0;
        m_size = 0;
        return true;
    }

    if (size == NODE_ID_INVALID)
        return false;

    SwHistoryItem * p = (SwHistoryItem *) realloc((void *) m_array, size * sizeof(SwHistoryItem));

    if (p)
    {
        m_size = size;
        m_array = p;
        return true;
    }

    return false;
}

swUI32 SwHistoryList::GetCount()
{
    return m_count;
}

void SwHistoryList::Reset()
{
    for (swUI32 pos = 0; pos < m_count; pos ++)
    {
        m_array[pos].id.Unset();
        m_array[pos].scrolldata.Reset();
    }

    m_count = 0;
    m_position = 0;
}

SwHistoryItem * SwHistoryList::GetAt(swUI32 pos)
{
    if (pos >= m_count)
        return NULL;

    return &m_array[pos];
}

void SwHistoryList::SetLastItemScrollData(SwScrollData scrolldata)
{
    if (!m_count)
        return;

    m_array[m_count - 1].scrolldata = scrolldata;
}

swUI32 SwHistoryList::Append(wxTreeItemId id)
{
   if (m_count >= m_size && !Size(m_size + 100))
        return NODE_ID_INVALID;

    m_array[m_count].id = id;
    m_array[m_count].scrolldata.Reset();
    m_position = m_count;

    m_count ++;

    return m_count - 1;
}

bool SwHistoryList::SetData(swUI32 pos, wxTreeItemId id, SwScrollData scrolldata)
{
    if (pos >= m_count)
        return false;

    m_array[pos].id = id;
    m_array[pos].scrolldata = scrolldata;

    return true;
}

swUI32 SwHistoryList::GetPosition()
{
    return m_position;
}

bool SwHistoryList::SetPosition(swUI32 pos)
{
    if (m_position >= m_count)
        return false;

    m_position = pos;

    return true;
}

bool SwHistoryList::CanMoveForward()
{
    if (!m_count)
        return false;
    if (m_position >= m_count - 1)
        return false;

    return true;
}

bool SwHistoryList::CanMoveBack()
{
    if (m_position > 0)
        return true;

    return false;
}

bool SwHistoryList::IncrementPosition()
{
    if (!CanMoveForward())
        return false;

    m_position ++;

    return true;
}

bool SwHistoryList::DecrementPosition()
{
    if (!CanMoveBack())
        return false;

    m_position --;

    return true;
}
