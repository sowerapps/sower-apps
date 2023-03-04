///////////////////////////////////////////////////////////////////
// Name:        string.cpp
// Purpose:     String class, and text buffer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/string/string.h"

swUI8 SwString::GetUtf8CharByteLength(unsigned char uch)
{
    if (uch >= 0XF1)
        return 4;

    if (uch >= 0XE1)
        return 3;

    if (uch >= 0XC2)
        return 2;

    return 1;
}

bool SwString::IsRoman(char ch)
{
    switch(ch)
    {
    case 'i' :
    case 'I' :
    case 'v' :
    case 'V' :
    case 'x' :
    case 'X' :
    case 'l' :
    case 'L' :
    case 'c' :
    case 'C' :
    case 'm' :
    case 'M' :
        return true;
        break;
    default :
        return false;
    }

    return false;
}

swUI16 SwString::GetRomanValue(char ch)
{
    switch(ch)
    {
    case 'i' :
    case 'I' :
        return 1;
        break;
    case 'v' :
    case 'V' :
        return 5;
        break;
    case 'x' :
    case 'X' :
        return 10;
        break;
    case 'l' :
    case 'L' :
        return 50;
        break;
    case 'c' :
    case 'C' :
        return 100;
        break;
    case 'm' :
    case 'M' :
        return 1000;
        break;
    }

    return 0;
}

void SwString::ToRoman(SwString & dest, swUI16 number, bool upperCase)
{
    dest.Reset();
    while (number >= 1000)
    {
        dest += "m";
        number -= 1000;
    }

    if (number >= 900)
    {
        dest += "cm";
        number -= 900;
    }

    if (number >= 500)
    {
        dest += "d";
        number -= 500;
    }

    if (number >= 400)
    {
        dest += "cd";
        number -= 400;
    }

    while (number >= 100)
    {
        dest += "c";
        number -= 100;
    }

    if (number >= 90)
    {
        dest += "xc";
        number -= 90;
    }

    if (number >= 50)
    {
        dest += "l";
        number -= 50;
    }

    if (number >= 40)
    {
        dest += "xl";
        number -= 40;
    }

    while (number >= 10)
    {
        dest += "x";
        number -= 10;
    }

    if (number == 9)
    {
        dest += "ix";
        number -= 9;
    }

    if (number >= 5)
    {
        dest += "v";
        number -= 5;
    }

    if (number == 4)
    {
        dest += "iv";
        number -= 4;
    }

    while (number >= 1)
    {
        dest += "i";
        number -= 1;
    }

    if (upperCase)
        strupr(dest);
}

swUI16 SwString::ConvertRoman(const char * str)
{
    swUI32 pos = 0;
    swUI16 number = 0;
    swI32 value;

    while (str[pos] != '\0')
    {
        value = GetRomanValue(str[pos]);
        if (!value)
            break;
        if (value >= GetRomanValue(str[pos + 1]))
            number += value;
        else
            number -= value;

        pos ++;
    }

    return (swUI16) number;
}

swUI16 SwString::ConvertRoman(const char * str, swUI32 & startPos, swUI32 & endPos)
{
    swUI32 pos = startPos;
    swUI16 number = 0;
    swI32 value;

    while (str[pos] != '\0')
    {
        value = GetRomanValue(str[pos]);
        if (!value)
            break;
        if (value >= GetRomanValue(str[pos + 1]))
            number += value;
        else
            number -= value;

        pos ++;
    }


    endPos = pos - 1;

    return (swUI16) number;
}

bool SwString::IsStrDigit(const char * source)
{
    if (!source)
        return false;

    int len = strlen(source);

    for (int pos = 0; pos < len; pos ++)
    {
        if (!isdigit(source[pos]) && source[pos] != '.')
            return false;
    }

    return true;
}

void SwString::Delete(char * str, swUI32 startPos, swUI32 del)
{
    swUI32 move, size;

    if (str == NULL)
        return;

    size = strlen(str);

    if (startPos > size)
        return;

    // If deletion exceeds length of string, insert '\0' at
    // deletion point.
    if (startPos + del >= size)
    {
        str[startPos] = '\0';
        return;
    }

    // Move all characters from deletion point, and to the right of
    // deletion point to the left, including null terminator.
    move = size + 1 - (startPos + del);
    memmove(str + startPos, str + startPos + del, move);
}

void SwString::Insert(char * str, const char * insertString, swUI32 insertPos)
{
    if (!str || !insertString)
        return;

    // String insertion.
    swUI32 move, insertSize;

    insertSize = strlen(insertString);

    move = strlen(str) + 1 - insertPos;

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    memmove(str + insertPos + insertSize, str + insertPos, move);

    // Insert the string.
    memcpy(str + insertPos, insertString, insertSize);
}

void SwString::Insert(SwString & stringBuffer, const char * insertString, swUI32 insertPos)
{
    if (!insertString)
        return;

    // String insertion.
    swUI32 move, insertSize, currentSize;

    insertSize = strlen(insertString);
    currentSize = stringBuffer.Strlen();

    if (!stringBuffer.Size(currentSize + insertSize + 1))
        return;

    move = currentSize + 1 - insertPos;

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    memmove(stringBuffer + insertPos + insertSize, stringBuffer.GetArray() + insertPos, move);

    // Insert the string.
    memcpy(stringBuffer + insertPos, insertString, insertSize);
}

swUI32 SwString::Replace(char * str, char chOld, char chNew)
{
    if (!str)
        return 0;

    swUI32 pos = 0, count = 0;
    // Scan string replacing chA with chB.
    while (str[pos] != '\0')
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

swUI32 SwString::Replace(char * str, swUI32 sizeString, swUI32 sizeBuffer, const char * strOld, swUI32 sizeOld, const char * strNew, swUI32 sizeNew)
{
    swUI32 delinsPos = 0, sizeDif;
    char * strPos;

    if (!str || ! strOld || ! strNew)
        return 0;

    if (sizeNew <= sizeOld)
    {
        sizeDif = sizeOld - sizeNew;
        strPos = str;

        for(;;)
        {
            strPos = strstr(strPos, strOld);

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
            strPos = strstr(strPos, strOld);

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

swUI32 SwString::Replace(SwString & stringBuffer, swUI32 sizeString, const char * strOld, swUI32 sizeOld, const char * strNew, swUI32 sizeNew)
{
    swUI32 delinsPos = 0, sizeDif;
    char * strPos;

    if (!strOld || !strNew)
        return 0;

    if (sizeNew <= sizeOld)
    {
        sizeDif = sizeOld - sizeNew;
        strPos = stringBuffer.GetArray();

        for(;;)
        {
            strPos = strstr(strPos, strOld);

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
            strPos = strstr(strPos, strOld);

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

void SwString::TrimLeft(char * str, char ch)
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

void SwString::TrimRight(char * str, char ch)
{
    if (!str)
        return;

    for (int i = strlen(str) - 1; i > 0; i--)
    {
        if (str[i] == ch)
            str[i] = '\0';
        else
            break;
    }
}

swUI32 SwString::CopyN(const char * source, char * dest, swUI32 number)
{
    if (!source || !dest)
        return 0;

    swUI32 length = strlen(source);

    if (length > number)
        length = number;

    memcpy((void *) dest, (void *) source, length);
    dest[length] = '\0';

    return length;
}

void SwString::Despace(char * source)
{
    if (!source)
        return;

    swUI32 len = strlen(source), writePos = 0;
    bool lastwasSpace = false;

    for (swUI32 readPos = 0; readPos < len; readPos ++)
    {
        if (source[readPos] == ' ' && lastwasSpace)
        {
            continue;
        }
        else if (source[readPos] == ' ')
        {
            lastwasSpace = true;
        }
        else
        {
            lastwasSpace = false;
        }

        source[writePos] = source[readPos];
        writePos ++;
    }

    source[writePos] = '\0';
}

bool SwString::BoolFromString(const char * value)
{
    if (!value)
        return false;

    if (stricmp(value, "true") == 0 || stricmp(value, "1") == 0)
        return true;
    else if (stricmp(value, "false") == 0 || stricmp(value, "0") == 0)
        return false;

    return (bool) atoi(value);
}

swUI32 SwString::ScanToDigit(const char * source)
{
    swUI32 pos = 0;

    if (!source)
        return 0;

    while (source[pos] != '\0' && !isdigit(source[pos]))
        pos ++;

    return pos;
}

swUI32 SwString::CountRepetitions(const char * source, const char * str)
{
    if (!source || !str)
        return 0;

    swUI32 count = 0;
    const char * p = source;

    for (;;)
    {
        p = strstr(source, str);
        if (!p)
            break;
        p ++;
        count ++;
    }

    return count;
}

SwString::SwString()
{
    Init();
}

SwString::SwString(const wchar_t * str)
{
    Init();

    if (!str)
        return;

    Copy(str);
}

SwString::SwString(const char * str)
{
    Init();

    if (!str)
        return;

    Copy(str);
}

SwString::~SwString()
{
    if (m_array)
        free(m_array);
}

void SwString::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(21))
        return;
    m_array[0] = '\0';
}

void SwString::Zero()
{
    if (!m_array)
        return;

    memset((void *) m_array, 0, m_size);
    m_count = 0;
}

void SwString::Reset()
{
    Size(21);
    SetAt(0, '\0');
    m_count = 0;
}

swUI32 SwString::Size(swUI32 size, bool shrink)
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

    char * p = (char *) realloc((void *) m_array, size * sizeof(char));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual array size because operation failed.
    return 0;
}

swUI32 SwString::GetSize()
{
    return m_size;
}

char * SwString::GetArray()
{
    // Ensure that array exists.
    Size(21);

    return m_array;
}

SwString::operator void * ()
{
    return (void *) m_array;
}

SwString::operator char * ()
{
    return m_array;
}

bool SwString::operator += (char ch)
{
    swUI32 pos = Strlen();

    if (pos + 2 >= m_size && !Size(m_size + 7))
        return false;

    SetAt(pos, ch);
    SetAt(pos + 1, '\0');
    m_count = pos;

    return true;
}

bool SwString::operator = (SwString & str)
{
    return Copy(str.GetArray());
}

bool SwString::operator = (SwString * str)
{
    return Copy(str->GetArray());
}

bool SwString::operator = (const char * str)
{
    if (!str)
        return false;

    swUI32 len = strlen(str);

    if (!Size(len + 7))
        return false;

    strcpy(m_array, str);
    m_count = len;

    return true;
}

bool SwString::operator += (const char * str)
{
    return Strcat(str);
}

swUI32 SwString::Strlen()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';
    m_count = strlen(m_array);

    return m_count;
}

void SwString::SetAt(swUI32 pos, char ch)
{
    if (pos >= m_size)
        return;

    m_array[pos] = ch;
}

char SwString::GetAt(swUI32 pos)
{
    if (pos >= m_size)
        return '\0';

    return m_array[pos];
}

bool SwString::Strcat(const char * str)
{
    if (!str)
        return false;

    int len = strlen(str), pos = Strlen();

    if (!Size(len + pos + 7))
        return false;

    strcat(m_array, str);
    m_count += len;

    return true;
}

bool SwString::Copy(const char * str)
{
    if (!str)
        return false;

    int len = strlen(str);

    if (!Size(len + 7))
        return false;

    strcpy(m_array, str);
    m_count = len;

    return true;
}

bool SwString::Copy(const char * str, swUI32 length)
{
    if (!str)
        return false;

    if (!Size(length + 7))
        return false;

    memcpy(m_array, (void *) str, length);

    SetAt(length, '\0');
    m_count = length;

    return true;
}

bool SwString::Copy(const wchar_t * str)
{
    if (!str)
        return false;

    Copy(wxString(str).utf8_str());
    Strlen();

    return true;
}

void SwString::Delete(swUI32 startPos, swUI32 del)
{
    if (startPos + del >= Strlen())
        return;

    Delete(m_array, startPos, del);
    m_count -= del;

    return;
}

bool SwString::Insert(swUI32 pos, const char * str)
{
    if (!str)
        return false;

    if (pos >= m_size)
    {
        return Strcat(str);
    }

    swUI32 ins = strlen(str);
    Size(Strlen() + ins + 7);
    Insert(m_array, str, pos);
    m_count += ins;

    return true;
}

swUI32 SwString::Replace(const char * strOld, swUI32 sizeOld, const char * strNew, swUI32 sizeNew)
{
    Replace(*this, Strlen(), strOld, sizeOld, strNew, sizeNew);
    return Strlen();
}

void SwString::TrimLeft(char ch)
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    TrimLeft(m_array, ch);
}

void SwString::TrimRight(char ch)
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    TrimRight(m_array, ch);
}

void SwString::Despace()
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    Despace(m_array);
}

void SwString::ToUpper()
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    strupr(m_array);
}

void SwString::ToLower()
{
    if (!m_array)
        return;

    m_array[m_size - 1] = '\0';

    strlwr(m_array);
}

float SwString::Atof()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';

    return atof(m_array);
}

bool SwString::Ftoa(float value)
{
    if (!Size(21))
        return false;

    sprintf(m_array, "%f", value);

    return true;
}

swI32 SwString::Atoi()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';

    return atoi(m_array);
}

bool SwString::Itoa(swI32 value)
{
    if (!Size(21))
        return false;

    sprintf(m_array, "%i", value);

    return true;
}

swUI32 SwString::Strtoul()
{
    if (!m_array)
        return 0;

    m_array[m_size - 1] = '\0';

    return strtoul(m_array, NULL, 10);
}

swUI16 SwString::ConvertRoman()
{
    if (!m_array)
        return 0;

    return ConvertRoman(m_array);
}

bool SwString::IsRoman(swUI32 pos)
{
    if (pos >= m_size)
        return false;

    return IsRoman(m_array[pos]);
}

bool SwString::IsDigit(swUI32 pos)
{
    if (pos >= m_size)
        return false;

    return (bool) isdigit(m_array[pos]);
}

bool SwString::IsAlpha(swUI32 pos)
{
    if (pos >= m_size)
        return false;

    return (bool) isalpha(m_array[pos]);
}

bool SwString::BoolFromString()
{
    if (!m_array)
        return false;

    m_array[m_size - 1] = '\0';

    return BoolFromString(m_array);
}

char * SwString::StrChr(char ch)
{
    if (!m_array)
        return NULL;

    m_array[m_size - 1] = '\0';

    return strchr(m_array, ch);
}

char * SwString::StrRevChr(char ch)
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

char * SwString::StrStr(const char * str)
{
    if (!m_array || !str)
        return NULL;

    m_array[m_size - 1] = '\0';

    return strstr(m_array, str);
}

int SwString::StrCmp(const char * str)
{
    if (!m_array || !str)
        return -1;

    m_array[m_size - 1] = '\0';

    return strcmp(m_array, str);
}

void SwString::GetTextRange(swUI32 start, swUI32 end, SwString & buffer)
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

bool SwString::FindInRange(swUI32 start, swUI32 end, char ch, swUI32 * pos)
{
    if (!m_array || start >= m_size || end >= m_size)
        return NODE_ID_INVALID;

    for (swUI32 i = start; i <= end; i ++)
    {
        if (m_array[i] == ch)
        {
            if (pos)
                *pos = i;

            return true;
        }
    }

    return false;
}

wchar_t * SwString::GetWideFromUtf8()
{
    if (!m_array)
        Copy("");

    m_array[m_size - 1] = '\0';

    static SwStringW converted;
    converted.Copy(m_array);

    return converted;
}

void SwString::SetCount(swUI32 pos)
{
    m_count = pos;
}

swUI32 SwString::GetCount()
{
    return m_count;
}

void SwString::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwString::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}

void SwString::CleanNewLines()
{
    if (!m_array)
        return;

    swUI32 len = Strlen();
    for (swUI32 i = 0; i < len; i ++)
    {
        if (m_array[i] == '\r' || m_array[i] == '\n')
            m_array[i] = ' ';
    }

    Replace("  ", 2, " ", 1);
}
