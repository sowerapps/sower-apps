///////////////////////////////////////////////////////////////////
// Name:        stringarray.cpp
// Purpose:     SwString, SwStringW & SwStringPair arrays.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/array/stringarray.h"

SwStringArray::SwStringArray()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;
}

SwStringArray::~SwStringArray()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
        m_array[pos].Size(0, true);

    free(m_array);
}

void SwStringArray::Reset()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
        m_array[pos].Reset();

    m_count = 0;
}

void SwStringArray::ShiftUp(swUI32 start)
{
    if (m_count <= 1)
    {
        m_count = 0;
        return;
    }
    else if (start >= m_count)
        return;

    for (swUI32 pos = start; pos < m_count; pos ++)
        m_array[pos - 1].Copy(m_array[pos]);

    m_count --;

    return;
}

bool SwStringArray::ShiftDown(swUI32 start)
{
    if (start >= m_count)
        return false;

    if (m_count >= m_size && !Grow())
        return false;

    for (swUI32 pos = m_count - 1; pos > start; pos --)
        m_array[pos].Copy(m_array[pos - 1]);

    m_count ++;

    return true;
}

swUI32 SwStringArray::operator += (const char * str)
{
    return Add(str);
}

swUI32 SwStringArray::Add(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    if (m_count >= m_size && !Grow())
        return NODE_ID_INVALID;

    m_array[m_count].Copy(str);
    m_count ++;

    return m_count - 1;
}

bool SwStringArray::Delete(swUI32 pos)
{
    if (pos >= m_count)
        return false;

    if (pos != m_count - 1)
        ShiftUp(pos + 1);
    else
    {
        m_count --;
        m_array[m_count].Reset();
    }

    return true;
}

bool SwStringArray::Insert(swUI32 pos, const char * str)
{
    if (!str)
        return false;

    if (!m_count || pos >= m_count)
    {
        Add(str);
        return true;
    }

    if (!ShiftDown(pos))
        return false;

    m_array[pos].Copy(str);

    return true;
}


SwString & SwStringArray::GetAt(swUI32 pos)
{
    if (m_count < 1)
        Add("");

    if (pos >= m_count)
        return m_array[m_count - 1];

    return m_array[pos];
}

swUI32 SwStringArray::Find(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (strcmp(str, GetAt(i)) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringArray::AddAlphabetically(const char * str)
{
    if (!str)
        return 0;

    swUI32 pos = FindAlphabeticInsertionPosition(str);

    if (pos == NODE_ID_INVALID)
        return Add(str);

    Insert(pos, str);

    return pos;
}

swUI32 SwStringArray::FindAlphabeticInsertionPosition(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    int result;

    for (swUI32 i = 0; i < m_count; i ++)
    {
        result = stricmp(str, m_array[i]);

        if (result < 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringArray::GetCount()
{
    return m_count;
}

bool SwStringArray::Size(swUI32 size)
{
    swUI32 pos = m_size;

    if (m_size > size || m_size >= NODE_ID_INVALID - 11)
        return false;

    SwString * p = (SwString *) realloc((void *) m_array, size * sizeof(SwString));

    if (p)
    {
        m_size = size;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

bool SwStringArray::Grow()
{
    swUI32 pos = m_size;

    if (m_size >= NODE_ID_INVALID - 11)
        return false;

    SwString * p = (SwString *) realloc((void *) m_array, (m_size + 10) * sizeof(SwString));

    if (p)
    {
        m_size += 10;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}


SwStringWArray::SwStringWArray()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;
}

SwStringWArray::~SwStringWArray()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
        m_array[pos].Size(0, true);

    free(m_array);
}

void SwStringWArray::Reset()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
        m_array[pos].Reset();

    m_count = 0;
}

void SwStringWArray::ShiftUp(swUI32 start)
{
    if (m_count <= 1)
    {
        m_count = 0;
        return;
    }
    else if (start >= m_count)
        return;

    for (swUI32 pos = start; pos < m_count; pos ++)
        m_array[pos - 1].Copy(m_array[pos]);

    m_count --;

    return;
}

bool SwStringWArray::ShiftDown(swUI32 start)
{
    if (start >= m_count)
        return false;

    if (m_count >= m_size && !Grow())
        return false;

    for (swUI32 pos = m_count - 1; pos > start; pos --)
        m_array[pos].Copy(m_array[pos - 1]);

    m_count ++;

    return true;
}

swUI32 SwStringWArray::operator += (const wchar_t * str)
{
    return Add(str);
}

swUI32 SwStringWArray::Add(const wchar_t * str)
{
    if (!str)
        return NODE_ID_INVALID;

    if (m_count >= m_size && !Grow())
        return NODE_ID_INVALID;

    m_array[m_count].Copy(str);
    m_count ++;

    return m_count - 1;
}

bool SwStringWArray::Delete(swUI32 pos)
{
    if (pos >= m_count)
        return false;

    if (pos != m_count - 1)
        ShiftUp(pos + 1);
    else
    {
        m_count --;
        m_array[m_count].Reset();
    }

    return true;
}

bool SwStringWArray::Insert(swUI32 pos, const wchar_t * str)
{
    if (!str)
        return false;

    if (!m_count || pos >= m_count)
    {
        Add(str);
        return true;
    }

    if (!ShiftDown(pos))
        return false;

    m_array[pos].Copy(str);

    return true;
}


SwStringW & SwStringWArray::GetAt(swUI32 pos)
{
    if (m_count < 1)
        Add(L"");

    if (pos >= m_count)
        return m_array[m_count - 1];

    return m_array[pos];
}

swUI32 SwStringWArray::Find(const wchar_t * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (wcscmp(str, GetAt(i)) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringWArray::AddAlphabetically(const wchar_t * str)
{
    if (!str)
        return 0;

    swUI32 pos = FindAlphabeticInsertionPosition(str);

    if (pos == NODE_ID_INVALID)
        return Add(str);

    Insert(pos, str);

    return pos;
}

swUI32 SwStringWArray::FindAlphabeticInsertionPosition(const wchar_t * str)
{
    if (!str)
        return NODE_ID_INVALID;

    int result;

    for (swUI32 i = 0; i < m_count; i ++)
    {
        result = wcsicmp(str, m_array[i]);

        if (result < 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringWArray::GetCount()
{
    return m_count;
}

bool SwStringWArray::Size(swUI32 size)
{
    swUI32 pos = m_size;

    if (m_size > size || m_size >= NODE_ID_INVALID - 11)
        return false;

    SwStringW * p = (SwStringW *) realloc((void *) m_array, (size) * sizeof(SwStringW));

    if (p)
    {
        m_size = size;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

bool SwStringWArray::Grow()
{
    swUI32 pos = m_size;

    if (m_size >= NODE_ID_INVALID - 11)
        return false;

    SwStringW * p = (SwStringW *) realloc((void *) m_array, (m_size + 10) * sizeof(SwStringW));

    if (p)
    {
        m_size += 10;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

SwStringPairArray::SwStringPairArray()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;
}

SwStringPairArray::~SwStringPairArray()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
    {
        m_array[pos].GetStrA().Size(0, true);
        m_array[pos].GetStrB().Size(0, true);
    }

    free(m_array);
}

void SwStringPairArray::Reset()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
        m_array[pos].Reset();

    m_count = 0;
}

void SwStringPairArray::ShiftUp(swUI32 start)
{
    if (m_count <= 1)
    {
        m_count = 0;
        return;
    }
    else if (start >= m_count)
        return;

    for (swUI32 pos = start; pos < m_count; pos ++)
    {
        m_array[pos - 1].GetStrA().Copy(m_array[pos].GetStrA());
        m_array[pos - 1].GetStrB().Copy(m_array[pos].GetStrB());
    }


    m_count --;

    return;
}

bool SwStringPairArray::ShiftDown(swUI32 start)
{
    if (start >= m_count)
        return false;

    if (m_count >= m_size && !Grow())
        return false;

    for (swUI32 pos = m_count - 1; pos > start; pos --)
    {
        m_array[pos].GetStrA().Copy(m_array[pos - 1].GetStrA());
        m_array[pos].GetStrB().Copy(m_array[pos - 1].GetStrB());
    }

    m_count ++;

    return true;
}

swUI32 SwStringPairArray::Add(const char * strA, const char * strB)
{
   if (!strA || !strB)
        return NODE_ID_INVALID;

    if (m_count >= m_size && !Grow())
        return NODE_ID_INVALID;

    m_array[m_count].GetStrA().Copy(strA);
    m_array[m_count].GetStrB().Copy(strB);
    m_count ++;

    return m_count - 1;
}

bool SwStringPairArray::Delete(swUI32 pos)
{
    if (pos >= m_count)
        return false;

    if (pos != m_count - 1)
        ShiftUp(pos + 1);
    else
    {
        m_count --;
        m_array[m_count].Reset();
    }

    return true;
}

bool SwStringPairArray::Insert(swUI32 pos, const char * strA, const char * strB)
{
    if (!strA || !strB)
        return false;

    if (!m_count || pos >= m_count)
    {
        Add(strA, strB);
        return true;
    }

    if (!ShiftDown(pos))
        return false;

    m_array[pos].GetStrA().Copy(strA);
    m_array[pos].GetStrB().Copy(strB);

    return true;
}


SwStringPair & SwStringPairArray::GetAt(swUI32 pos)
{
    if (m_count < 1)
        Add("", "");

    if (pos >= m_count)
        return m_array[m_count - 1];

    return m_array[pos];
}

swUI32 SwStringPairArray::FindInA(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (strcmp(str, GetAt(i).GetStrA()) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringPairArray::FindInB(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (strcmp(str, GetAt(i).GetStrB()) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringPairArray::GetCount()
{
    return m_count;
}

bool SwStringPairArray::Size(swUI32 size)
{
    swUI32 pos = m_size;

    if (m_size > size || m_size >= NODE_ID_INVALID - 11)
        return false;

    SwStringPair * p = (SwStringPair *) realloc((void *) m_array, size * sizeof(SwStringPair));

    if (p)
    {
        m_size = size;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

bool SwStringPairArray::Grow()
{
    swUI32 pos = m_size;

    if (m_size >= NODE_ID_INVALID - 11)
        return false;

    SwStringPair * p = (SwStringPair *) realloc((void *) m_array, (m_size + 10) * sizeof(SwStringPair));

    if (p)
    {
        m_size += 10;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

SwStringTripletArray::SwStringTripletArray()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;
}

SwStringTripletArray::~SwStringTripletArray()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
    {
        m_array[pos].GetStrA().Size(0, true);
        m_array[pos].GetStrB().Size(0, true);
        m_array[pos].GetStrC().Size(0, true);
    }

    free(m_array);
}

void SwStringTripletArray::Reset()
{
    if (!m_array)
        return;

    for (swUI32 pos = 0; pos < m_size; pos ++)
        m_array[pos].Reset();

    m_count = 0;
}

void SwStringTripletArray::ShiftUp(swUI32 start)
{
    if (m_count <= 1)
    {
        m_count = 0;
        return;
    }
    else if (start >= m_count)
        return;

    for (swUI32 pos = start; pos < m_count; pos ++)
    {
        m_array[pos - 1].GetStrA().Copy(m_array[pos].GetStrA());
        m_array[pos - 1].GetStrB().Copy(m_array[pos].GetStrB());
        m_array[pos - 1].GetStrC().Copy(m_array[pos].GetStrC());
    }


    m_count --;

    return;
}

bool SwStringTripletArray::ShiftDown(swUI32 start)
{
    if (start >= m_count)
        return false;

    if (m_count >= m_size && !Grow())
        return false;

    for (swUI32 pos = m_count - 1; pos > start; pos --)
    {
        m_array[pos].GetStrA().Copy(m_array[pos - 1].GetStrA());
        m_array[pos].GetStrB().Copy(m_array[pos - 1].GetStrB());
        m_array[pos].GetStrC().Copy(m_array[pos - 1].GetStrC());
    }

    m_count ++;

    return true;
}

swUI32 SwStringTripletArray::Add(const char * strA, const char * strB, const char * strC)
{
   if (!strA || !strB)
        return NODE_ID_INVALID;

    if (m_count >= m_size && !Grow())
        return NODE_ID_INVALID;

    m_array[m_count].GetStrA().Copy(strA);
    m_array[m_count].GetStrB().Copy(strB);
    m_array[m_count].GetStrC().Copy(strC);
    m_count ++;

    return m_count - 1;
}

bool SwStringTripletArray::Delete(swUI32 pos)
{
    if (pos >= m_count)
        return false;

    if (pos != m_count - 1)
        ShiftUp(pos + 1);
    else
    {
        m_count --;
        m_array[m_count].Reset();
    }

    return true;
}

bool SwStringTripletArray::Insert(swUI32 pos, const char * strA, const char * strB, const char * strC)
{
    if (!strA || !strB)
        return false;

    if (!m_count || pos >= m_count)
    {
        Add(strA, strB, strC);
        return true;
    }

    if (!ShiftDown(pos))
        return false;

    m_array[pos].GetStrA().Copy(strA);
    m_array[pos].GetStrB().Copy(strB);
    m_array[pos].GetStrC().Copy(strC);

    return true;
}


SwStringTriplet & SwStringTripletArray::GetAt(swUI32 pos)
{
    if (m_count < 1)
        Add("", "", "");

    if (pos >= m_count)
        return m_array[m_count - 1];

    return m_array[pos];
}

swUI32 SwStringTripletArray::FindInA(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (strcmp(str, GetAt(i).GetStrA()) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringTripletArray::FindInB(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (strcmp(str, GetAt(i).GetStrB()) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringTripletArray::FindInC(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < GetCount(); i ++)
    {
        if (strcmp(str, GetAt(i).GetStrC()) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwStringTripletArray::GetCount()
{
    return m_count;
}

bool SwStringTripletArray::Size(swUI32 size)
{
    swUI32 pos = m_size;

    if (m_size > size || m_size >= NODE_ID_INVALID - 11)
        return false;

    SwStringTriplet * p = (SwStringTriplet *) realloc((void *) m_array, size * sizeof(SwStringTriplet));

    if (p)
    {
        m_size = size;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

bool SwStringTripletArray::Grow()
{
    swUI32 pos = m_size;

    if (m_size >= NODE_ID_INVALID - 11)
        return false;

    SwStringTriplet * p = (SwStringTriplet *) realloc((void *) m_array, (m_size + 10) * sizeof(SwStringTriplet));

    if (p)
    {
        m_size += 10;
        m_array = p;

        while (pos < m_size)
        {
            m_array[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}
