///////////////////////////////////////////////////////////////////
// Name:        html_encoded_char.h
// Purpose:     Handle encoding/decoding of characters in HTML/XML.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HTML_ENCODED_CHAR_H
#define HTML_ENCODED_CHAR_H

#include "../sowerbase.h"
#include "../string/string.h"

#define N_ENCODED_CHARS 252

class SOWERBASEEXP SwHtmlEncodedChar
{
public:
    static swUI32 GetEncodedCharValue(const char * encodedValue, char * dest, swUI32 bufferLen);
    static bool IsReservedChar(char ch);
    static swUI8 GetCharSize(char ch);
    static swUI32 CalcEncodedStringSize(const char * source);
    static swUI32 EncodeString(const char * source, SwString & dest, bool prevSpace = false);
    static bool IsXmlReservedChar(char ch);
    static swUI8 GetXmlCharSize(char ch);
    static swUI32 CalcXmlEncodedStringSize(const char * source);
    static swUI32 XmlEncodeString(const char * source, SwString & dest);
};

#endif // HTML_ENCODED_CHAR_H
