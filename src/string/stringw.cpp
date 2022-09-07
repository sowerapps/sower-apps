///////////////////////////////////////////////////////////////////
// Name:        string.cpp
// Purpose:     Wide character string class.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/string/stringw.h"

bool SwStringW::IsRoman(wchar_t ch)
{
    switch(ch)
    {
    case L'i' :
    case L'I' :
    case L'v' :
    case L'V' :
    case L'x' :
    case L'X' :
    case L'l' :
    case L'L' :
    case L'c' :
    case L'C' :
        return true;
        break;
    default :
        return false;
    }

    return false;
}

void SwStringW::ToRoman(SwStringW & dest, swUI16 number, bool upperCase)
{
    dest.Reset();

    while (number >= 1000)
    {
        dest += L"m";
        number -= 1000;
    }

    if (number >= 900)
    {
        dest += L"cm";
        number -= 900;
    }

    if (number >= 500)
    {
        dest += L"d";
        number -= 500;
    }

    if (number >= 400)
    {
        dest += L"cd";
        number -= 400;
    }

    while (number >= 100)
    {
        dest += L"c";
        number -= 100;
    }

    if (number >= 90)
    {
        dest += L"xc";
        number -= 90;
    }

    if (number >= 50)
    {
        dest += L"l";
        number -= 50;
    }

    if (number >= 40)
    {
        dest += L"xl";
        number -= 40;
    }

    while (number >= 10)
    {
        dest += L"x";
        number -= 10;
    }

    if (number == 9)
    {
        dest += L"ix";
        number -= 9;
    }

    if (number >= 5)
    {
        dest += L"v";
        number -= 5;
    }

    if (number == 4)
    {
        dest += L"iv";
        number -= 4;
    }

    while (number >= 1)
    {
        dest += L"i";
        number -= 1;
    }

    if (upperCase)
        wcsupr(dest);
}

swUI16 SwStringW::ConvertRoman(const wchar_t * str)
{
    swUI32 pos = 0;
    swUI16 number = 0;

    while (str[pos] == L'M' || str[pos] == L'm')
    {
        number += 1000;
        pos ++;
    }

    if ((str[pos] == L'C' || str[pos] == L'c') && (str[pos +1] == L'M' || str[pos + 1] == L'm'))
    {
        number += 900;
        pos += 2;
    }

    if (str[pos] == L'D' || str[pos] == L'd')
    {
        number += 500;
        pos ++;
    }

    if ((str[pos] == L'C' || str[pos] == L'c') && (str[pos +1] == L'D' || str[pos + 1] == L'd'))
    {
        number += 400;
        pos += 2;
    }

    while (str[pos] == L'C' || str[pos] == L'c')
    {
        number += 100;
        pos ++;
    }

    if ((str[pos] == L'X' || str[pos] == L'x') && (str[pos +1] == L'C' || str[pos + 1] == L'c'))
    {
        number += 90;
        pos += 2;
    }

    if (str[pos] == L'L' || str[pos] == L'l')
    {
        number += 50;
        pos ++;
    }

    if ((str[pos] == L'X' || str[pos] == L'x') && (str[pos +1] == L'L' || str[pos + 1] == L'l'))
    {
        number += 40;
        pos ++;
    }

    while (str[pos] == L'X' || str[pos] == L'x')
    {
        number += 10;
        pos ++;
    }

    if ((str[pos] == L'I' || str[pos] == L'i') && (str[pos +1] == L'X' || str[pos + 1] == L'x'))
    {
        number += 9;
        pos ++;
    }

    if (str[pos] == L'V' || str[pos] == L'v')
    {
        number += 5;
        pos ++;
    }

    if ((str[pos] == L'I' || str[pos] == L'i') && (str[pos +1] == L'V' || str[pos + 1] == L'v'))
    {
        number += 4;
        pos += 2;
    }

    while (str[pos] == L'I' || str[pos] == L'i')
    {
        number += 1;
        pos ++;
    }

    return number;
}


swUI16 SwStringW::ConvertRoman(const wchar_t * str, swUI32 & startPos, swUI32 & endPos)
{
    swUI32 pos = startPos;
    swUI16 number = 0;

    while(!IsRoman(str[pos]) && str[pos] != L'\0')
    {
        pos ++;
    }

    startPos = pos;

    while (str[pos] == L'M' || str[pos] == L'm')
    {
        number += 1000;
        pos ++;
    }

    if ((str[pos] == L'C' || str[pos] == L'c') && (str[pos +1] == L'M' || str[pos + 1] == L'm'))
    {
        number += 900;
        pos += 2;
    }

    if (str[pos] == L'D' || str[pos] == L'd')
    {
        number += 500;
        pos ++;
    }

    if ((str[pos] == L'C' || str[pos] == L'c') && (str[pos +1] == L'D' || str[pos + 1] == L'd'))
    {
        number += 400;
        pos += 2;
    }

    while (str[pos] == L'C' || str[pos] == L'c')
    {
        number += 100;
        pos ++;
    }

    if ((str[pos] == L'X' || str[pos] == L'x') && (str[pos +1] == L'C' || str[pos + 1] == L'c'))
    {
        number += 90;
        pos += 2;
    }

    if (str[pos] == L'L' || str[pos] == L'l')
    {
        number += 50;
        pos ++;
    }

    if ((str[pos] == L'X' || str[pos] == L'x') && (str[pos +1] == L'L' || str[pos + 1] == L'l'))
    {
        number += 40;
        pos ++;
    }

    while (str[pos] == L'X' || str[pos] == L'x')
    {
        number += 10;
        pos ++;
    }

    if ((str[pos] == L'I' || str[pos] == L'i') && (str[pos +1] == L'X' || str[pos + 1] == L'x'))
    {
        number += 9;
        pos ++;
    }

    if (str[pos] == L'V' || str[pos] == L'v')
    {
        number += 5;
        pos ++;
    }

    if ((str[pos] == L'I' || str[pos] == L'i') && (str[pos +1] == L'V' || str[pos + 1] == L'v'))
    {
        number += 4;
        pos += 2;
    }

    while (str[pos] == L'I' || str[pos] == L'i')
    {
        number += 1;
        pos ++;
    }

    endPos = pos - 1;

    return number;
}

bool SwStringW::IsStrDigit(const wchar_t * str)
{
    if (!str)
        return false;

    int len = wcslen(str);

    for (int pos = 0; pos < len; pos ++)
    {
        if (!iswdigit(str[pos]) && str[pos] != L'.')
            return false;
    }

    return true;
}

void SwStringW::Delete(wchar_t * str, swUI32 startPos, swUI32 del)
{
    swUI32 move, size;

    if (str == NULL)
        return;

    size = wcslen(str);

    if (startPos > size)
        return;

    // If deletion exceeds length of string, insert '\0' at
    // deletion point.
    if (startPos + del >= size)
    {
        str[startPos] = L'\0';
        return;
    }

    // Move all characters from deletion point, and to the right of
    // deletion point to the left, including null terminator.
    move = size + 1 - (startPos + del);
    wmemmove(str + startPos, str + startPos + del, move);
}

void SwStringW::Insert(wchar_t * str, const wchar_t * insertString, swUI32 insertPos)
{
    if (!str || !insertString)
        return;

    // String insertion.
    swUI32 move, insertSize;

    insertSize = wcslen(insertString);

    move = wcslen(str) + 1 - insertPos;

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    wmemmove(str + insertPos + insertSize, str + insertPos, move);

    // Insert the string.
    wmemcpy(str + insertPos, insertString, insertSize);
}

void SwStringW::Insert(SwStringW & stringBuffer, const wchar_t * insertString, swUI32 insertPos)
{
    if (!insertString)
        return;

    // String insertion.
    swUI32 move, insertSize, currentSize;

    insertSize = wcslen(insertString);
    currentSize = stringBuffer.Strlen();

    if (!stringBuffer.Size(currentSize + insertSize + 1))
        return;

    move = currentSize + 1 - insertPos;

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    wmemmove(stringBuffer + insertPos + insertSize, stringBuffer.GetArray() + insertPos, move);

    // Insert the string.
    wmemcpy(stringBuffer + insertPos, insertString, insertSize);
}

swUI32 SwStringW::Replace(wchar_t * str, wchar_t chOld, wchar_t chNew)
{
    if (!str)
        return 0;

    swUI32 pos = 0, count = 0;
    // Scan string replacing chA with chB.
    while (str[pos] != L'\0')
    {
        if (str[pos] == chOld)
        {
            str[pos] = chNew;
            count ++;
        }

        pos ++;
    }

    return count;
}

swUI32 SwStringW::Replace(wchar_t * str, swUI32 sizeString, swUI32 sizeBuffer, const wchar_t * strOld, swUI32 sizeOld, const wchar_t * strNew, swUI32 sizeNew)
{
    swUI32 delinsPos = 0, sizeDif;
    wchar_t * strPos;

    if (!str || ! strOld || ! strNew)
        return 0;

    if (sizeNew <= sizeOld)
    {
        sizeDif = sizeOld - sizeNew;
        strPos = str;

        for(;;)
        {
            strPos = wcsstr(strPos, strOld);

            if (!strPos)
                break;

            delinsPos = strPos - str;
            Delete(str, delinsPos, sizeOld);
            sizeString -= sizeDif;

            if (sizeNew != 0)
                Insert(str, strNew, delinsPos);

            strPos += sizeNew;
        }
    }
    else
    {
        sizeDif = sizeNew - sizeOld;
        strPos = str;

        for (;;)
        {
            strPos = wcsstr(strPos, strOld);

            if (!strPos)
                break;

            sizeString += sizeDif;

            if (sizeBuffer <= sizeString)
                return 0;

            delinsPos = strPos - str;
            Delete(str, delinsPos, sizeOld);
            Insert(str, strNew, delinsPos);
            strPos += sizeNew;
        }
    }

    return sizeString;
}

swUI32 SwStringW::Replace(SwStringW & stringBuffer, swUI32 sizeString, const wchar_t * strOld, swUI32 sizeOld, const wchar_t * strNew, swUI32 sizeNew)
{
    swUI32 delinsPos = 0, sizeDif;
    wchar_t * strPos;

    if (!strOld || !strNew)
        return 0;

    if (sizeNew <= sizeOld)
    {
        sizeDif = sizeOld - sizeNew;
        strPos = stringBuffer.GetArray();

        for(;;)
        {
            strPos = wcsstr(strPos, strOld);

            if (!strPos)
                break;

            delinsPos = strPos - stringBuffer.GetArray();
            Delete(stringBuffer.GetArray(), delinsPos, sizeOld);
            sizeString -= sizeDif;

            if (sizeNew != 0)
                Insert(stringBuffer, strNew, delinsPos);

            strPos += sizeNew;
        }
    }
    else
    {
        sizeDif = sizeNew - sizeOld;
        strPos = stringBuffer.GetArray();

        for (;;)
        {
            strPos = wcsstr(strPos, strOld);

            if (!strPos)
                break;

            sizeString += sizeDif;

            if (!stringBuffer.Size(sizeString + 1))
                return 0;

            delinsPos = strPos - stringBuffer;
            Delete(stringBuffer.GetArray(), delinsPos, sizeOld);
            Insert(stringBuffer, strNew, delinsPos);
            strPos += sizeNew;
        }
    }

    return sizeString;
}

void SwStringW::TrimLeft(wchar_t * str, wchar_t ch)
{
    if (!str)
        return;

    swUI32 pos = 0;

    // If first character on the left is not == ch, end here.
    if (str[pos] != ch)
        return;

    pos ++;

    while (str[pos] == ch)
        pos ++;

    // Pos is pointing at a character which is != ch,
    // Decrement to place at last character that is == ch.
    pos --;
    Delete(str, 0, pos + 1);
}

void SwStringW::TrimRight(wchar_t * str, wchar_t ch)
{
    if (!str)
        return;

    for (int i = wcslen(str) - 1; i > 0; i--)
    {
        if (str[i] == ch)
            str[i] = L'\0';
        else
            break;
    }
}

swUI32 SwStringW::CopyN(const wchar_t * source, wchar_t * dest, swUI32 number)
{
    if (!source || !dest)
        return 0;

    swUI32 length = wcslen(source);

    if (length > number)
        length = number;

    memcpy((void *) dest, (void *) source, sizeof(wchar_t) * length);
    dest[length] = L'\0';

    return length;
}

void SwStringW::Despace(wchar_t * str)
{
    if (!str)
        return;

    swUI32 len = wcslen(str), writePos = 0;
    bool lastwasSpace = false;

    for (swUI32 readPos = 0; readPos < len; readPos ++)
    {
        if (str[readPos] == L' ' && lastwasSpace)
        {
            continue;
        }
        else if (str[readPos] == L' ')
        {
            lastwasSpace = true;
        }
        else
        {
            lastwasSpace = false;
        }

        str[writePos] = str[readPos];
        writePos ++;
    }

    str[writePos] = L'\0';
}

bool SwStringW::BoolFromString(const wchar_t * value)
{
    if (!value)
        return false;

    if (wcsicmp(value, L"true") == 0 || wcsicmp(value, L"1") == 0)
        return true;
    else if (wcsicmp(value, L"false") == 0 || wcsicmp(value, L"0") == 0)
        return false;

    return (bool) wcstoul(value, NULL, 10);
}

swUI32 SwStringW::ScanToDigit(const wchar_t * source)
{
    swUI32 pos = 0;

    if (!source)
        return 0;

    while (source[pos] != L'\0' && !iswdigit(source[pos]))
        pos ++;

    return pos;
}

SwStringW::SwStringW()
{
    Init();
}

SwStringW::SwStringW(const char * str)
{
    Init();

    if (!str)
        return;

    Copy(str);
}

SwStringW::SwStringW(const wchar_t * str)
{
    Init();

    if (!str)
        return;

    Copy(str);
}

SwStringW::~SwStringW()
{
    if (m_array)
        free(m_array);
}

void SwStringW::Init()
{
    m_array = NULL;
    m_size = 0;

    if (!Size(21))
        return;

    memset((void *) m_array, 0, 21);
    m_count = 0;
}

void SwStringW::Reset()
{
    Size(21);
    SetAt(0, L'\0');
    m_count = 0;
}

swUI32 SwStringW::Size(swUI32 size, bool shrink)
{
    if (!size && m_array && shrink)
    {
        free(m_array);
        m_array = NULL;
        m_size = 0;
        return 0;
    }

    if (size < 21)
        size = 21;

    if (m_array && m_size >= size && !shrink)
        return m_size;

    wchar_t * p = (wchar_t *) realloc((void *) m_array, size * sizeof(wchar_t));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual array size because operation failed.
    return 0;
}

swUI32 SwStringW::GetSize()
{
    return m_size;
}

wchar_t * SwStringW::GetArray()
{
    // Ensure that array exists.
    Size(21);

    return m_array;
}

SwStringW::operator wchar_t * ()
{
    return m_array;
}

bool SwStringW::operator += (wchar_t ch)
{
    swUI32 pos = Strlen();

    if (pos + 2 >= m_size && !Size(m_size + 7))
        return false;

    SetAt(pos, ch);
    SetAt(pos + 1, L'\0');
    m_count = pos;

    return true;
}

bool SwStringW::operator = (const wchar_t * str)
{
    if (!str)
        return false;

    swUI32 len = wcslen(str);

    if (!Size(len + 7))
        return false;

    wcscpy(m_array, str);
    m_count = len;

    return true;
}

bool SwStringW::operator += (const wchar_t * str)
{
    return Strcat(str);
}

swUI32 SwStringW::Strlen()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = L'\0';
    m_count = wcslen(m_array);
    return m_count;
}

void SwStringW::SetAt(swUI32 pos, wchar_t ch)
{
    if (pos >= m_size)
        return;

    m_array[pos] = ch;
}

wchar_t SwStringW::GetAt(swUI32 pos)
{
    if (pos >= m_size)
        return L'\0';

    return m_array[pos];
}

bool SwStringW::Strcat(const wchar_t * str)
{
    if (!str)
        return false;

    int len = wcslen(str), pos = Strlen();

    if (!Size(pos + len + 7))
        return false;

    wcscat(m_array, str);
    m_count += len;

    return true;
}

bool SwStringW::Copy(const wchar_t * str)
{
    if (!str)
        return false;

    int len = wcslen(str);

    if (!Size(len + 7))
        return false;

    wcscpy(m_array, str);
    m_count = len;

    return true;
}

bool SwStringW::Copy(const wchar_t * str, swUI32 length)
{
    if (!str)
        return false;

    if (!Size(length + 7))
        return false;

    wmemcpy(m_array, str, length);

    SetAt(length, L'\0');
    m_count = length;

    return true;
}

bool SwStringW::Copy(const char * str)
{
    if (!str)
        return false;

    Copy(wxString::FromUTF8(str).t_str());
    Strlen();

    return true;
}

bool SwStringW::Delete(swUI32 startPos, swUI32 del)
{
    if (startPos + del >= Strlen())
        return false;

    Delete(m_array, startPos, del);
    m_count -= del;

    return true;
}

bool SwStringW::Insert(swUI32 pos, const wchar_t * str)
{
    if (!str)
        return false;

    if (pos >= m_size)
        return Strcat(str);

    swUI32 ins = wcslen(str);
    Size(Strlen() + ins + 7);
    Insert(m_array, str, pos);
    m_count += ins;

    return true;
}

swUI32 SwStringW::Replace(const wchar_t * strOld, swUI32 sizeOld, const wchar_t * strNew, swUI32 sizeNew)
{
    Replace(*this, Strlen(), strOld, sizeOld, strNew, sizeNew);

    return Strlen();
}

void SwStringW::TrimLeft(wchar_t ch)
{
    if (!m_array)
        return;

    m_array[m_size - 1] = L'\0';

    TrimLeft(m_array, ch);
}

void SwStringW::TrimRight(wchar_t ch)
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    TrimRight(m_array, ch);
}

void SwStringW::Despace()
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    Despace(m_array);
}

void SwStringW::ToUpper()
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    wcsupr(m_array);
}

void SwStringW::ToLower()
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    wcslwr(m_array);
}

float SwStringW::Atof()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';

    return wcstof(m_array, NULL);
}

bool SwStringW::Ftoa(float value)
{
    if (!Size(21))
        return false;

#if defined __MSWIN__
    wsprintf(m_array, L"%f", value);
#else
    swprintf(m_array, 21, L"%f", value);
    #endif // defined

    return true;
}

swI32 SwStringW::Atoi()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';

    return (swI32) wcstol(m_array, NULL, 10);
}

bool SwStringW::Itoa(swI32 value)
{
    if (!Size(21))
        return false;

#if defined __MSWIN__
    wsprintf(m_array, L"%i", value);
#else
    swprintf(m_array, 21, L"%i", value);
#endif // defined

    return true;
}

swUI32 SwStringW::Strtoul()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';

    return wcstoul(m_array, NULL, 10);
}

bool SwStringW::BoolFromString()
{
    if (!m_array)
        return false;

    m_array[m_size - 1] = '\0';

    return BoolFromString(m_array);;
}

wchar_t * SwStringW::StrChr(wchar_t ch)
{
    if (!m_array)
        return NULL;

    m_array[m_size - 1] = '\0';

    return wcschr(m_array, ch);
}

wchar_t * SwStringW::StrRevChr(wchar_t ch)
{
    if (!m_array)
        return NULL;

    m_array[m_size - 1] = '\0';

    for (swUI32 i = Strlen(); i > 0; i --)
    {
        if (m_array[i] == ch)
            return m_array + i;
    }

    return NULL;
}

wchar_t * SwStringW::StrStr(const wchar_t * str)
{
    if (!m_array || !str)
        return NULL;

    m_array[m_size - 1] = '\0';

    return wcsstr(m_array, str);
}

int SwStringW::StrCmp(const wchar_t * str)
{
    if (!m_array || !str)
        return -1;

    m_array[m_size - 1] = '\0';

    return wcscmp(m_array, str);
}

void SwStringW::GetTextRange(swUI32 start, swUI32 end, SwStringW & buffer)
{
    swUI32 len = Strlen();
    buffer.Reset();

    if (start >= len || end >= len)
        return;

    for (swUI32 i = start; i <= end; i ++)
    {
        buffer += GetAt(i);
    }
}
