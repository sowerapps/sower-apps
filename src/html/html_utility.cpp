///////////////////////////////////////////////////////////////////
// Name:        html_utility.cpp
// Purpose:     Various utility functions for working with HTML.
// Copyright:   David Reynolds
///////////////////////////////////////////////////////////////////

#include "../../include/html/html_utility.h"
#include "../../include/utility/strutility.h"
#include <ctype.h>

swUI32 ScanToDigit(const char * source)
{
    swUI32 pos = 0;

    if (!source)
        return 0;

    while (source[pos] != '\0' && !isdigit(source[pos]))
        pos ++;

    return pos;
}

swUI32 ScanToAttribute(const char * source)
{
    swUI32 pos = 0;

    if (!source)
        return 0;

    while (source[pos] == ' ' || source[pos] == '\"' || source[pos] == '\'')
        pos ++;

    return pos;
}

swUI32 ScanPastWhiteSpace(const char * source)
{
    swUI32 pos = 0;

    if (!source)
        return 0;

    while (source[pos] == ' ' || source[pos] == '\t' || source[pos] == '\r' || source[pos] == '\n')
        pos ++;

    return pos;
}

int CopyBetweenElements(const char * source, char * dest, swUI32 bufferLen)
{
    if (!dest || !source)
        return false;

    const char * p = strchr(source, '>');

    if (!p)
        return 0;

    swUI32 n = 0;
    p++;

    while (*p != '\0' && *p != '<' && n < bufferLen -1)
    {
        dest[n] = *p;
        n++;
        p++;
    }

    dest[n] = '\0';

    if (*p != '<')
        return -1;

    return n;
}

int CopyElement(const char * source, char * dest, swUI32 bufferLen)
{
    if (!dest || !source)
        return false;

    const char * p = strchr(source, '<');

    if (!p)
        return 0;

    swUI32 n = 0;
    p++;

    while (*p != '\0' && *p != '>' && n < bufferLen -1)
    {
        dest[n] = *p;
        n++;
        p++;
    }

    dest[n] = '\0';

    if (*p != '>')
        return -1;

    return n;
}

inline bool GetNamedValue(const char * name, const char * source, BasicBuffer & dest)
{
    if (!name || !source)
        return false;

    const char *p = source;
    int len = strlen(name);
    dest.SizeBuffer(strlen(source + 1));
    dest.SetAt(0, '\0');

    for (;;)
    {
        p = strstr(p, name);

        if (!p)
            return false;

        if ((p == source || isspace(p[-1])) && (p[len] == '=' || isspace(p[len])))
            break;

        p++;
    }

    swUI32 n = 0;

    while (*p != '\0' && *p != '\"' && *p != '>')
        p++;

    if (*p != '\"' )
        return false;

    p++;

    while (isspace(*p))
        p++;

    while (*p != '\0' && *p != '\"' && *p != '>')
    {
        dest.SetAt(n, *p);
        n++;
        p++;
    }

    dest.SetAt(n, '\0');

    if (*p != '\"')
        return false;

    return true;
}

inline bool DeleteNamedValue(BasicBuffer & tag, const char * name, bool despace)
{
    swUI32 begin, end;

    if (!name)
        return false;

    if (!GetNamedValuePos(tag, name, begin, end))
        return false;

    if (begin > 0 && tag.GetAt(begin - 1) == ' ')
        begin --;

    StrUtility::Delete(tag.GetBuffer(), begin, (end - begin) + 1);

    if (despace)
        tag.Despace();

    return true;
}

inline bool GetNamedValuePos(const char * source, const char * name, swUI32 & begin, swUI32 & end)
{
    if (!name || !source)
        return false;

    int len = strlen(name);
    const char *p = source;

    for (;;)
    {
        p = strstr(p, name);

        if (!p)
            return false;

        if ((p == source || isspace(p[-1])) && (p[len] == '=' || isspace(p[len])))
            break;

        p++;
    }

    begin = p - source;

    while (*p != '\0' && *p != '\"' && *p != '>')
        p++;
// This is first ";
    if (*p != '\"' )
        return false;

    p++;
    while (*p != '\0' && *p != '\"' && *p != '>')
        p++;

    end = p - source;

    return true;
}

bool InsertAttribute(BasicBuffer & tag, const char * attribute, bool despace)
{
    if (!attribute)
        return false;

    BasicBuffer format;
    swUI32 insertPos;

    insertPos = FindInsertPosition(tag.GetBuffer());

    if(insertPos == 0)
        return false;

    format.SizeBuffer(3 + strlen(attribute));
    sprintf(format, " %s ", attribute);
    tag.Insert(insertPos, format.GetBuffer());

    if (despace)
    {
        tag.Despace();
        StrUtility::Replace(tag, strlen(tag), " >", 2, ">", 1);
    }

    return true;
}

swUI32 FindInsertPosition(const char * tag)
{
    if (!tag)
        return 0;

    const char * p = NULL, * p1, * p2, * p3;

    p1 = strchr(tag, ' ');
    p2 = strstr(tag, "/>");
    p3 = strchr(tag, '>');

    if (!p3)
        return 0;

    if (p1 && p1 < p3)
        p = p1;
    else if (p2)
        p = p2;
    else
        p = p3;

    return p - tag;
}
