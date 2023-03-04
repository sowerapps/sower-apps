///////////////////////////////////////////////////////////////////
// Name:        css_attributes.cpp
// Purpose:     CssAttributes - identify selector, class, attributes,
//              and scope in a style.
//              CssAttributeList - list of attributes in a style.
//              CssSpacedList - break space separated attributes
//              into individual strings.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/css/css_attributes.h"
#include "../../include/html/html.h"
#include "../../include/html/html_color.h"
#include "../../include/string/string.h"
#include "../../include/string/strparser.h"

struct CSS_ATTRIBUTE
{
    const char *  name;
    swUI8       id;
};

static const swI8 cssAttributeIndex[] =
{
    -1, CSS_ATTR_BACKGROUND_COLOR, CSS_ATTR_COLOR, CSS_ATTR_DIRECTION, -1,
    CSS_ATTR_FLOAT, -1, CSS_ATTR_HEIGHT, -1, -1, -1, CSS_ATTR_LIST_STYLE,
    CSS_ATTR_MARGIN, -1, -1, CSS_ATTR_PADDING, -1, -1, -1, CSS_ATTR_TEXT_ALIGN,
    -1, CSS_ATTR_VERTICAL_ALIGN, CSS_ATTR_WHITE_SPACE, -1, -1, -1
};

static const CSS_ATTRIBUTE CssAttributeData[] =
{
    "unknown",                  CSS_ATTR_UNKNOWN,
    "background-color",         CSS_ATTR_BACKGROUND_COLOR,
    "border",                   CSS_ATTR_BORDER,
    "border-collapse",          CSS_ATTR_BORDER_COLLAPSE,
    "border-color",             CSS_ATTR_BORDER_COLOR,
    "border-style",             CSS_ATTR_BORDER_STYLE,
    "border-width",             CSS_ATTR_BORDER_WIDTH,
    "border-spacing",           CSS_ATTR_BORDER_SPACING,
    "border-bottom",            CSS_ATTR_BORDER_BOTTOM,
    "border-bottom-color",      CSS_ATTR_BORDER_BOTTOM_COLOR,
    "border-bottom-style",      CSS_ATTR_BORDER_STYLE,
    "border-bottom-width",      CSS_ATTR_BORDER_BOTTOM_WIDTH,
    "border-left",              CSS_ATTR_BORDER_LEFT,
    "border-left-color",        CSS_ATTR_BORDER_LEFT_COLOR,
    "border-left-style",        CSS_ATTR_BORDER_LEFT_STYLE,
    "border-left-width",        CSS_ATTR_BORDER_LEFT_WIDTH,
    "border-right",             CSS_ATTR_BORDER_RIGHT,
    "border-right-color",       CSS_ATTR_BORDER_RIGHT_COLOR,
    "border-right-style",       CSS_ATTR_BORDER_RIGHT_STYLE,
    "border-right-width",       CSS_ATTR_BORDER_RIGHT_WIDTH,
    "border-top",               CSS_ATTR_BORDER_TOP,
    "border-top-color",         CSS_ATTR_BORDER_TOP_COLOR,
    "border-top-style",         CSS_ATTR_BORDER_TOP_STYLE,
    "border-top-width",         CSS_ATTR_BORDER_TOP_WIDTH,
    "color",                    CSS_ATTR_COLOR,
    "direction",                CSS_ATTR_DIRECTION,
    "display",                  CSS_ATTR_DISPLAY,
    "float",                    CSS_ATTR_FLOAT,
    "font",                     CSS_ATTR_FONT,
    "font-family",              CSS_ATTR_FONT_FAMILY,
    "font-size",                CSS_ATTR_FONT_SIZE,
    "font-style",               CSS_ATTR_FONT_STYLE,
    "font-variant",             CSS_ATTR_FONT_VARIANT,
    "font-weight",              CSS_ATTR_FONT_WEIGHT,
    "height",                   CSS_ATTR_HEIGHT,
    "list-style",               CSS_ATTR_LIST_STYLE,
    "list-style-type",          CSS_ATTR_LIST_STYLE_TYPE,
    "margin",                   CSS_ATTR_MARGIN,
    "margin-bottom",            CSS_ATTR_MARGIN_BOTTOM,
    "margin-left",              CSS_ATTR_MARGIN_LEFT,
    "margin-right",             CSS_ATTR_MARGIN_RIGHT,
    "margin-top",               CSS_ATTR_MARGIN_TOP,
    "padding",                  CSS_ATTR_PADDING,
    "padding-bottom",           CSS_ATTR_PADDING_BOTTOM,
    "padding-left",             CSS_ATTR_PADDING_LEFT,
    "padding-right",            CSS_ATTR_PADDING_RIGHT,
    "padding-top",              CSS_ATTR_PADDING_TOP,
    "text-align",               CSS_ATTR_TEXT_ALIGN,
    "text-decoration",          CSS_ATTR_TEXT_DECORATION,
    "text-indent",              CSS_ATTR_TEXT_INDENT,
    "text-transform",           CSS_ATTR_TEXT_TRANSFORM,
    "vertical-align",           CSS_ATTR_VERTICAL_ALIGN,
    "white-space",              CSS_ATTR_WHITE_SPACE,
    "width",                    CSS_ATTR_WIDTH
};

CssAttributes::CssAttributes()
{
}

CssAttributes::~CssAttributes()
{
}

swUI8 CssAttributes::IdentifyAttribute(const char * source)
{
    if (!source)
        return CSS_ATTR_UNKNOWN;

    swI16 attPos;
    char ch = tolower(*source);

    if (ch < 'a' || ch > 'z')
        return CSS_ATTR_UNKNOWN;

    attPos = cssAttributeIndex[ch - 'a'];

    if (attPos < 0)
        return CSS_ATTR_UNKNOWN;

    while (attPos < N_CSS_ATTRS)
    {
        if (CssAttributeData[attPos].name[0] > ch)
            return CSS_ATTR_UNKNOWN;

        if (stricmp(CssAttributeData[attPos].name, source) == 0)
            return CssAttributeData[attPos].id;

        attPos ++;
    }

    return CSS_ATTR_UNKNOWN;
}

const char * CssAttributes::GetAttributeString(swUI8 attribute)
{
    if (attribute >= N_CSS_ATTRS)
        return "";

    return CssAttributeData[attribute].name;
}

bool CssAttributes::HasStyle(const char * source)
{
    if (!source)
        return false;

    if (strstr(source, "style") == 0)
        return true;

    return false;
}

swUI32 CssAttributes::GetStyleData(const char * source, char * dest)
{
    if (!source || !dest)
        return 0;

    dest[0] = '\0';

    const char * startPos = strchr(source, '{');
    int destPos = 0;

    if (!startPos)
        return 0;

    startPos ++;

    while(*startPos != '}' && *startPos != '\0')
    {
        dest[destPos] = *startPos;
        destPos ++;
        startPos ++;
    }

    dest[destPos] = '\0';
    return destPos;
}

swUI32 CssAttributes::GetClassName(const char * source, char * dest)
{
    if (!source || !dest)
        return 0;

    dest[0] = '\0';

    const char * startPos = strchr(source, '.');
    int destPos = 0;

    if (!startPos)
        return 0;

    startPos ++;

    while (isspace(*startPos))
        startPos ++;

    while(!isspace(*startPos) && *startPos != ',' &&
            *startPos != ':' && *startPos != '{' &&
            *startPos != '\0')
    {
        dest[destPos] = *startPos;
        destPos ++;
        startPos ++;
    }

    dest[destPos] = '\0';
    return destPos;
}

swUI32 CssAttributes::GetElement(const char * source, char * dest)
{
    if (!source || !dest)
        return 0;

    dest[0] = '\0';
    int destPos = 0;

    const char * startPos = source;

    while (isspace(*startPos))
        startPos ++;

    while(!isspace(*startPos) && *startPos != ',' &&
            *startPos != '.' && *startPos != '{' &&
            *startPos != '\0')
    {
        dest[destPos] = *startPos;
        destPos ++;
        startPos ++;
    }

    dest[destPos] = '\0';
    return destPos;
}

swUI32 CssAttributes::GetScope(const char * source, char * dest)
{
    if (!source || !dest)
        return 0;

    int destPos = 0;
    dest[0] = '\0';

    const char * startPos = strchr(source, ':');

    if (!startPos)
        return 0;

    startPos ++;

    if (*startPos == ':')
        startPos ++;

    if (isspace(*startPos))
        startPos ++;

    while(isalnum(*startPos) || *startPos == '-')
    {
        dest[destPos] = *startPos;
        destPos ++;
        startPos ++;
    }

    dest[destPos] = '\0';
    return destPos;
}

swUI32 CssAttributes::GetSelector(const char * source, char * dest)
{
    if (!source || !dest)
        return 0;

    dest[0] = '\0';
    int pos = 0;

    const char * startPos = source;

    if (*startPos == '<')
        startPos ++;

    while (isspace(*startPos))
        startPos ++;

    while (*startPos != '{' && *startPos != '\0')
    {
        dest[pos] = *startPos;
        pos ++;
        startPos ++;
    }

    dest[pos] = '\0';
    return pos;
}

bool CssAttributes::Test()
{
    for (swUI16 i = 0; i < N_CSS_ATTRS; i ++)
    {
        if (CssAttributeData[i].id != i)
            return false;
    }

    return true;
}

CssAttributeList::CssAttributeList()
{
}

CssAttributeList::~CssAttributeList()
{
}

void CssAttributeList::Reset()
{
    m_attribute.Reset();
    m_value.Reset();
    m_specificity.Reset();
}

void CssAttributeList::CreateStyleString(SwString & buffer)
{
    buffer.Reset();
    buffer = "style=\"";

    for (swUI32 i = 0; i < m_value.GetCount(); i ++)
    {
        m_value.GetAt(i).Replace("\"", 1, "'", 1);
    }

    for (swUI32 pos = 0; pos < m_attribute.GetCount() && pos < m_value.GetCount(); pos ++)
    {
        if (pos > 0)
            buffer += " ";

        buffer += m_attribute.GetAt(pos);
        buffer += ":";
        buffer += m_value.GetAt(pos);
        buffer += ";";
    }

    buffer += "\"";
}

void CssAttributeList::ParseStyle(const char * style, swUI16 specificity)
{
    SwStrParser listStyle, listAttributes;
    listStyle.SetDeliminator(';');
    listAttributes.SetDeliminator(':');
    listStyle.ParseString(style);

    for (swUI32 i = 0; i < listStyle.GetItems(); i ++)
    {
        listAttributes.ParseString(listStyle.GetItem(i));
        for (swUI32 n = 0; n < listAttributes.GetItems() - 1; n += 2)
        {
            Add(listAttributes.GetItem(n), listAttributes.GetItem(n + 1), specificity);
        }
    }
}

void CssAttributeList::ParseTag(const char * tag)
{
//   Reset();
    int len = strlen(tag);
    bool inattr = false;
    bool invalue = false;
    bool inquote = false;
    SwString attr;
    SwString value;
    attr.Size(17);
    value.Size(17);

    const char * pos = strchr(tag, ' ');

    if (!pos)
        return;

    for(int i = pos - tag; i < len; i++)
    {
        if (!inattr)
        {
            if (!isspace(tag[i]))
            {
                attr += tag[i];
                inattr = true;
            }
        }
        else
        {
            if (!invalue)
            {
                if (tag[i] == '=')
                    invalue = true;
                else
                    attr += tag[i];
            }
            else
            {
                if (!inquote)
                {
                    if (tag[i] == '\"')
                        inquote = true;
                }
                else
                {
                    if (tag[i] == '\"')
                    {
                        attr.TrimLeft(' ');
                        attr.TrimRight(' ');
                        value.TrimLeft(' ');
                        value.TrimRight(' ');

                        if (attr.Strlen() && value.Strlen())
                        {
                            Add(attr, value);
                        }

                        attr.Reset();
                        value.Reset();

                        inattr = false;
                        invalue = false;
                        inquote = false;
                    }
                    else
                        value += tag[i];
                }
            }
        }
    }
}

CssSpacedList::CssSpacedList()
{
}

CssSpacedList::~CssSpacedList()
{
}

void CssSpacedList::Reset()
{
    m_value.Reset();
}

void CssSpacedList::ParseValue(const char * value)
{
    int len = strlen(value);
    bool invalue = false;
    bool inquote = false;
    SwString attribute;
    attribute.Size(17);

    Reset();
    for(int i = 0; i < len; i++)
    {
        if (!invalue)
        {
            if (!isspace(value[i]))
            {
                invalue = true;

                if (value[i] == '\'')
                {
                    inquote = true;
                }
                else
                    attribute += value[i];
            }

            continue;
        }
        else
        {
            if (!inquote)
            {
                if (value[i] == ' ' || value[i] == '\0')
                {
                    if (attribute.Strlen())
                        Add(attribute);

                    invalue = false;
                    inquote = false;
                    attribute.Reset();
                }
                else
                    attribute += value[i];

                continue;
            }
            else
            {
                if (value[i] == '\'')
                {
                    if (attribute.Strlen())
                        Add(attribute);

                    invalue = false;
                    inquote = false;
                    attribute.Reset();
                }
                else
                    attribute += value[i];

                continue;
            }
        }
    }
}

void CssSpacedList::Add(const char * value)
{
    if ( !value)
        return;

    m_value.Add(value);
}

swUI32 CssSpacedList::GetItems()
{
    return m_value.GetCount();
}

const char * CssSpacedList::GetValue(swUI32 pos)
{
    if (pos >= GetItems())
        return "";

    return m_value.GetAt(pos);
}
