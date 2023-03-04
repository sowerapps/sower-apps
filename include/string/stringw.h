///////////////////////////////////////////////////////////////////
// Name:        string.h
// Purpose:     Wide character string class.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRINGW_H
#define STRINGW_H

#include "../sowerbase.h"

class SOWERBASEEXP SwStringW
{
public:
    static bool IsRoman(wchar_t ch);
    static swUI16 GetRomanValue(wchar_t ch);
    static void ToRoman(SwStringW & dest, swUI16 number, bool upperCase);
    static swUI16 ConvertRoman(const wchar_t * str);
    static swUI16 ConvertRoman(const wchar_t * str, swUI32 & startPos, swUI32 & endPos);
    static bool IsStrDigit(const wchar_t * str);
    static void Delete(wchar_t * stringBuffer, swUI32 startPos, swUI32 del);
    static void Insert(wchar_t * stringBuffer, const wchar_t * insertString, swUI32 insertPos);
    static void Insert(SwStringW & stringBuffer, const wchar_t * insertString, swUI32 insertPos);
    static swUI32 Replace(wchar_t * stringBuffer, wchar_t chOld, wchar_t chNew);
    static swUI32 Replace(wchar_t * stringBuffer, swUI32 sizeString, swUI32 sizeBuffer, const wchar_t * strOld, swUI32 sizeOld, const wchar_t * strNew, swUI32 sizeNew);
    static swUI32 Replace(SwStringW & stringBuffer, swUI32 sizeString, const wchar_t * strOld, swUI32 sizeOld, const wchar_t * strNew, swUI32 sizeNew);
    static void TrimLeft(wchar_t * stringBuffer, wchar_t ch);
    static void TrimRight(wchar_t * stringBuffer, wchar_t ch);
    static swUI32 CopyN(const wchar_t * source, wchar_t * dest, swUI32 number);
    static void Despace(wchar_t * source);
    static bool BoolFromString(const wchar_t * value);
    static swUI32 ScanToDigit(const wchar_t * source);
     static swUI32 CountRepetitions(const wchar_t * source, const wchar_t * str);

    SwStringW();
    SwStringW(const char * str);
    SwStringW(const wchar_t * str);
    virtual ~SwStringW();

    void Init();
    void Reset();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    wchar_t * GetArray();

    operator wchar_t * ();
    bool operator += (wchar_t ch);
    bool operator = (SwStringW & str);
    bool operator = (SwStringW * str);
    bool operator = (const wchar_t * str);
    bool operator += (const wchar_t * str);

    swUI32 Strlen();
    void SetAt(swUI32 pos, wchar_t ch);
    wchar_t GetAt(swUI32 pos);
    bool Strcat(const wchar_t * str);
    bool Copy(const wchar_t * str);
    bool Copy(const wchar_t * str, swUI32 length);
    bool Copy(const char * str);
    bool Delete(swUI32 startPos, swUI32 del);
    bool Insert(swUI32 pos, const wchar_t * str);
    swUI32 Replace(const wchar_t * strOld, swUI32 sizeOld, const wchar_t * strNew, swUI32 sizeNew);
    void TrimLeft(wchar_t ch);
    void TrimRight(wchar_t ch);
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
    wchar_t * StrChr(wchar_t ch);
    wchar_t * StrRevChr(wchar_t ch);
    wchar_t * StrStr(const wchar_t * str);
    int StrCmp(const wchar_t * str);
    void GetTextRange(swUI32 start, swUI32 end, SwStringW & buffer);
    bool FindInRange(swUI32 start, swUI32 end, wchar_t ch, swUI32 * pos);

protected:
    wchar_t * m_array;
    swUI32    m_size;
    swUI32    m_count;
};

#endif // STRINGW_H
