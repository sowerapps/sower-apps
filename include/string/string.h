///////////////////////////////////////////////////////////////////
// Name:        string.h
// Purpose:     String class, and text buffer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRING_H
#define STRING_H

#include "../sowerbase.h"
#include "stringw.h"

class SOWERBASEEXP SwString
{
public:
    static swUI8 GetUtf8CharByteLength(unsigned char uch);
    static bool IsRoman(char ch);
    static swUI16 GetRomanValue(char ch);
    static void ToRoman(SwString & dest, swUI16 number, bool upperCase);
    static swUI16 ConvertRoman(const char * str);
    static swUI16 ConvertRoman(const char * str, swUI32 & startPos, swUI32 & endPos);
    static bool IsStrDigit(const char * source);
    static void Delete(char * str, swUI32 startPos, swUI32 del);
    static void Insert(char * str, const char * insertString, swUI32 insertPos);
    static void Insert(SwString & stringBuffer, const char * insertString, swUI32 insertPos);
    static swUI32 Replace(char * str, char chOld, char chNew);
    static swUI32 Replace(char * str, swUI32 sizeString, swUI32 sizeBuffer, const char * strOld, swUI32 sizeOld, const char * strNew, swUI32 sizeNew);
    static swUI32 Replace(SwString & stringBuffer, swUI32 sizeString, const char * strOld, swUI32 sizeOld, const char * strNew, swUI32 sizeNew);
    static void TrimLeft(char * str, char ch);
    static void TrimRight(char * str, char ch);
    static swUI32 CopyN(const char * source, char * dest, swUI32 number);
    static void Despace(char * source);
    static bool BoolFromString(const char * value);
    static swUI32 ScanToDigit(const char * source);

    SwString();
    SwString(const wchar_t * str);
    SwString(const char * str);
    virtual ~SwString();

    void Init();
    void Zero();
    void Reset();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    char * GetArray();

    operator void * ();
    operator char * ();
    bool operator += (char c);
    bool operator = (const char * str);
    bool operator += (const char * str);

    swUI32 Strlen();
    void SetAt(swUI32 pos, char ch);
    char GetAt(swUI32 pos);
    bool Strcat(const char * str);
    bool Copy(const char * str);
    bool Copy(const char * str, swUI32 length);
    bool Copy(const wchar_t * str);
    void Delete(swUI32 startPos, swUI32 del);
    bool Insert(swUI32 pos, const char * src);
    swUI32 Replace(const char * strOld, swUI32 sizeOld, const char * strNew, swUI32 sizeNew);
    void TrimLeft(char ch);
    void TrimRight(char ch);
    void Despace();
    void ToUpper();
    void ToLower();
    float Atof();
    bool Ftoa(float value);
    swI32 Atoi();
    bool Itoa(swI32 value);
    swUI32 Strtoul();
    swUI16 ConvertRoman();
    bool IsRoman(swUI32 pos);
    bool IsDigit(swUI32 pos);
    bool IsAlpha(swUI32 pos);
    bool BoolFromString();
    char * StrChr(char ch);
    char * StrRevChr(char ch);
    char * StrStr(const char * str);
    int StrCmp(const char * str);
    void GetTextRange(swUI32 start, swUI32 end, SwString & buffer);
    bool FindInRange(swUI32 start, swUI32 end, char ch, swUI32 * pos);
    wchar_t * GetWideFromUtf8();
    void SetCount(swUI32 pos);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);
    void CleanNewLines();

protected:
    char *    m_array;
    swUI32    m_size;
    swUI32    m_count;
};

#endif // STRING_H
