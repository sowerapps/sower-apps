///////////////////////////////////////////////////////////////////
// Name:        strparser.h
// Purpose:     SwStrParser, SwStrParserW - parse a deliminated string
//              into multiple individual strings.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRPARSER_H
#define STRPARSER_H

#include "string.h"
#include "stringw.h"
#include "../array/uintarray.h"

class SOWERBASEEXP SwStrParser
{
public:
    SwStrParser();
    virtual ~SwStrParser();

    void ParseString(const char * dataString);
    void ParseStringStrict(const char * dataString);
    swUI32 GetItems();
    const char * GetItem(swUI32 item);
    void SetDeliminator(char ch);
    swUI32 Find(const char * str);

protected:
    SwString  m_stringBuffer;
    Swui32Array m_indexArray;
    char      m_deliminator;
};

class SOWERBASEEXP SwStrParserW
{
public:
    SwStrParserW();
    virtual ~SwStrParserW();

    void ParseString(const char * dataString);
    void ParseString(const wchar_t * dataString);
    swUI32 GetItems();
    const wchar_t * GetItem(swUI32 item);
    void SetDeliminator(wchar_t ch);
    swUI32 Find(const wchar_t * str);

protected:
    SwStringW m_stringBuffer;
    Swui32Array m_indexArray;
    wchar_t   m_deliminator;
};

#endif // STRPARSER_H
