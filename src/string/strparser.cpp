///////////////////////////////////////////////////////////////////
// Name:        strparser.cpp
// Purpose:     SwStrParser, SwStrParserW - parse a deliminated string
//              into multiple individual strings.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/string/strparser.h"

SwStrParser::SwStrParser()
{
    SetDeliminator(',');
}

SwStrParser::~SwStrParser()
{
}

void SwStrParser::ParseString(const char * dataString)
{
    if (!dataString)
        return;

    m_stringBuffer.Copy(dataString);

    swUI32 len = strlen(dataString);

    if (!len)
        return;

    swUI32 items = 1;
    bool instr = false;

    for (swUI32 i = 0; i < len; i++)
    {
        if (m_stringBuffer.GetAt(i) == m_deliminator)
            items ++;
    }

    m_indexArray.Size(items + 1);
    m_indexArray.SetAt(0, 0);
    m_indexArray.SetCount(0);

    for(swUI32 i = 0; i < len; i++)
    {
        if (!instr && isspace(m_stringBuffer.GetAt(i)))
        {
            continue;
        }
        else if (!instr && !isspace(m_stringBuffer.GetAt(i)) && m_stringBuffer.GetAt(i) != m_deliminator)
        {
            instr = true;
            m_indexArray += i;
            continue;
        }
        else if (instr && m_stringBuffer.GetAt(i) == m_deliminator)
        {
            m_stringBuffer.SetAt(i, '\0');
            instr = false;
            continue;
        }

    }

    for(swUI32 i = 0; i < m_indexArray.GetCount(); i++)
    {
        SwString::TrimRight(&m_stringBuffer[m_indexArray.GetAt(i)], ' ');
    }
}

void SwStrParser::ParseStringStrict(const char * dataString)
{
    if (!dataString)
        return;

    m_stringBuffer.Copy(dataString);

    swUI32 len = strlen(dataString);

    if (!len)
        return;

    swUI32 items = 1;
    bool instr = false;

    for (swUI32 i = 0; i < len; i++)
    {
        if (m_stringBuffer.GetAt(i) == m_deliminator)
            items ++;
    }

    m_indexArray.Size(items + 1);
    m_indexArray.SetAt(0, 0);
    m_indexArray.SetCount(0);

    for(swUI32 i = 0; i < len; i++)
    {
        if (!instr && m_stringBuffer.GetAt(i) != m_deliminator)
        {
            instr = true;
            m_indexArray += i;
            continue;
        }
        else if (instr && m_stringBuffer.GetAt(i) == m_deliminator)
        {
            m_stringBuffer.SetAt(i, '\0');
            instr = false;
            continue;
        }

    }
}

swUI32 SwStrParser::GetItems()
{
    return m_indexArray.GetCount();
}

const char * SwStrParser::GetItem(swUI32 item)
{
    if (item >= m_indexArray.GetCount())
        return "";

    return &m_stringBuffer[m_indexArray.GetAt(item)];
}

void SwStrParser::SetDeliminator(char ch)
{
    m_deliminator = ch;
}

swUI32 SwStrParser::Find(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_indexArray.GetCount(); i ++)
    {
        if (stricmp(str, &m_stringBuffer[m_indexArray.GetAt(i)]) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

SwStrParserW::SwStrParserW()
{
    SetDeliminator(L',');
}

SwStrParserW::~SwStrParserW()
{
}

void SwStrParserW::ParseString(const char * dataString)
{
    if (!dataString)
        return;

    SwString buffer;
    buffer.Copy(dataString);

    return ParseString(buffer);
}

void SwStrParserW::ParseString(const wchar_t * dataString)
{
    if (!dataString)
        return;

    m_stringBuffer.Copy(dataString);

    swUI32 len = wcslen(dataString);
    swUI32 items = 1;
    bool instr = false;

    for (swUI32 i = 0; i < len; i++)
    {
        if (m_stringBuffer.GetAt(i) == m_deliminator)
            items ++;
    }

    m_indexArray.Size(items + 1);
    m_indexArray.SetAt(0, 0);
    m_indexArray.SetCount(0);

    for(swUI32 i = 0; i < len; i++)
    {
        if (!instr && iswspace(m_stringBuffer.GetAt(i)))
        {
            continue;
        }
        else if (!instr && !iswspace(m_stringBuffer.GetAt(i)) && m_stringBuffer.GetAt(i) != m_deliminator)
        {
            instr = true;
            m_indexArray += i;
            continue;
        }
        else if (instr && m_stringBuffer.GetAt(i) == m_deliminator)
        {
            m_stringBuffer.SetAt(i, L'\0');
            instr = false;
            continue;
        }

    }

    for(swUI32 i = 0; i < m_indexArray.GetCount(); i++)
    {
        SwStringW::TrimRight(&m_stringBuffer[m_indexArray.GetAt(i)], L' ');
    }
}

swUI32 SwStrParserW::GetItems()
{
    return m_indexArray.GetCount();
}

const wchar_t * SwStrParserW::GetItem(swUI32 item)
{
    if (item >= m_indexArray.GetCount())
        return L"";

    return &m_stringBuffer[m_indexArray.GetAt(item)];
}

void SwStrParserW::SetDeliminator(wchar_t ch)
{
    m_deliminator = ch;
}

swUI32 SwStrParserW::Find(const wchar_t * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_indexArray.GetCount(); i ++)
    {
        if (wcsicmp(str, &m_stringBuffer[m_indexArray.GetAt(i)]) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}
