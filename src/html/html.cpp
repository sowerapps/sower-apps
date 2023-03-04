///////////////////////////////////////////////////////////////////
// Name:        html.cpp
// Purpose:     Primary file for working with HTML.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/html.h"
#include "../../include/html/html_color.h"
#include "../../include/css/css_units.h"
#include "../../include/html/html_encoded_char.h"
#include "../../include/string/strparser.h"

int GetUtf8Char(wchar_t ch, char * buff, int size)
{
    wchar_t ws[2];
    ws[0] = ch;
    ws[1] = L'\0';
    buff[0] = '\0';

    strncpy(buff, wxString(ws).utf8_str(), size);

    return strlen(buff);
}

swUI8 SwHtml::GetMethodType(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "get") == 0)
        return METHOD_TYPE_GET;
    else if (stricmp(value, "post") == 0)
        return METHOD_TYPE_POST;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetBorderCollapse(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "collapse") == 0)
        return BORDER_COLLAPSE_COLLAPSE;
    else if (stricmp(value, "separate") == 0)
        return BORDER_COLLAPSE_SEPARATE;

    return ATTRIBUTE_UNSPECIFIED;
}

void SwHtml::GetBorderSpacing(const char * value, float & hspacing, swUI8 & hunit, float & vspacing, swUI8 & vunit)
{
    const char * p = value;
    char buf[100];
    int pos = 0;

    if (!value)
        return;

    if (strstr(value, "inherit"))
    {
        hspacing = ATTRIBUTE_INHERIT;
        hunit = UNIT_PREDEFINED;
        return;
    }

    hspacing = 0;
    hunit = 0;
    vspacing = 0;
    vunit = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, hspacing, hunit);

    p += ScanPastWhiteSpace(p);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, vspacing, vunit);
}

void SwHtml::GetBorder(const char * value, float & borderWidth, swUI8 & borderUnit, swUI8 & borderStyle, swUI32 & borderColor)
{
    char * p, * p1, * p2 = NULL, * p3 = NULL, * p4;

    if (!value)
        return;

    p = strdup(value);
    p1 = p;

    while (isspace(*p1))
        p1 ++;

    p2 = strchr(p1, ' ');
    if (p2)
    {
        *p2 = '\0';
        p2 ++;
        p3 = strchr(p2, ' ');
        if (p3)
        {
            *p3 = '\0';
            p3 ++;
        }
    }

    p4 = strchr(p1, ';');
    if (p4)
        *p4 = '\0';

    if (p2)
    {
        p4 = strchr(p2, ';');
        if (p4)
            *p4 = '\0';
    }

    if (p3)
    {
        p4 = strchr(p3, ';');
        if (p4)
            *p4 = '\0';
    }

    swUI8 type = GetBorderValueType(p1);

    if (type == 1)
        GetBorderWidth(p1, borderWidth, borderUnit);
    else if (type == 2)
        borderStyle = GetBorderStyle(p1);
    else
        borderColor = SwHtmlColor::GetColor(p1);

    if (p2)
    {
        type = GetBorderValueType(p2);
        if (type == 2)
            borderStyle = GetBorderStyle(p2);
        else
            borderColor = SwHtmlColor::GetColor(p2);
    }

    if (p3)
        borderColor = SwHtmlColor::GetColor(p3);

    free(p);
}

swUI8 SwHtml::GetBorderValueType(const char * value)
{
    float v;
    swUI8 u;

    if (!value)
        return 1;

    GetBorderWidth(value, v, u);

    // Has width.
    if (u != UNIT_NONE)
        return 1;

    u = GetBorderStyle(value);

    // Has border style, but no width.
    if (u != ATTRIBUTE_UNSPECIFIED)
        return 2;

    // Does not have width or style.
    return 3;
}

swUI8 SwHtml::GetBorderStyle(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "none") == 0)
        return BORDER_STYLE_NONE;
    else if (stricmp(value, "hidden") == 0)
        return BORDER_STYLE_HIDDEN;
    else if (stricmp(value, "dotted") == 0)
        return BORDER_STYLE_DOTTED;
    else if (stricmp(value, "dashed") == 0)
        return BORDER_STYLE_DASHED;
    else if (stricmp(value, "solid") == 0)
        return BORDER_STYLE_SOLID;
    else if (stricmp(value, "double") == 0)
        return BORDER_STYLE_DOUBLE;
    else if (stricmp(value, "groove") == 0)
        return BORDER_STYLE_GROOVE;
    else if (stricmp(value, "ridge") == 0)
        return BORDER_STYLE_RIDGE;
    else if (stricmp(value, "inset") == 0)
        return BORDER_STYLE_INSET;
    else if (stricmp(value, "outset") == 0)
        return BORDER_STYLE_OUTSET;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetFloatDirection(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "none") == 0)
        return FLOAT_DIRECTION_NONE;
    else if (stricmp(value, "left") == 0)
        return FLOAT_DIRECTION_LEFT;
    else if (stricmp(value, "right") == 0)
        return FLOAT_DIRECTION_RIGHT;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetTextAlign(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "none") == 0)
        return TEXT_ALIGN_NONE;
    else if (stricmp(value, "left") == 0)
        return TEXT_ALIGN_LEFT;
    else if (stricmp(value, "right") == 0)
        return TEXT_ALIGN_RIGHT;
    else if (stricmp(value, "center") == 0)
        return TEXT_ALIGN_CENTER;
    else if (stricmp(value, "justify") == 0)
        return TEXT_ALIGN_JUSTIFY;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetVerticalAlign(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "baseline") == 0)
        return VERTICAL_ALIGN_BASELINE;
    else if (stricmp(value, "sub") == 0)
        return VERTICAL_ALIGN_SUB;
    else if (stricmp(value, "super") == 0)
        return VERTICAL_ALIGN_SUPER;
    else if (stricmp(value, "top") == 0)
        return VERTICAL_ALIGN_TOP;
    else if (stricmp(value, "text-top") == 0)
        return VERTICAL_ALIGN_TEXT_TOP;
    else if (stricmp(value, "middle") == 0)
        return VERTICAL_ALIGN_MIDDLE;
    else if (stricmp(value, "bottom") == 0)
        return VERTICAL_ALIGN_BOTTOM;
    else if (stricmp(value, "text-bottom") == 0)
        return VERTICAL_ALIGN_TEXT_BOTTOM;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI16 SwHtml::GetTextDecoration(const char * value)
{
    swUI16 textDecoration = ATTRIBUTE_UNSPECIFIED;

    if (!value)
        return textDecoration;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "none") == 0)
        return TEXT_DECORATION_NONE;

    if (strstr(value, "overline"))
        textDecoration |= TEXT_DECORATION_OVERLINE ;
    if (strstr(value, "underline"))
        textDecoration |= TEXT_DECORATION_UNDERLINE;
    if (strstr(value, "line-through"))
        textDecoration |= TEXT_DECORATION_LINE_THROUGH;

    return textDecoration;
}

void SwHtml::TextDecoration(swUI8 & textDecoration, swUI8 decoration)
{
    if (textDecoration == ATTRIBUTE_INHERIT ||
            textDecoration == TEXT_DECORATION_NONE)
    {
        textDecoration = decoration;
        return;
    }

    if (TextDecorationHas(textDecoration, decoration))
        return;

    textDecoration += decoration;
}

void SwHtml::TextDecorationRemove(swUI8 & textDecoration, swUI8 decoration)
{
    if (!TextDecorationHas(textDecoration, decoration))
        return;

    textDecoration -= decoration;
}

bool SwHtml::TextDecorationHas(swUI8 textDecoration, swUI8 decoration)
{
    if (decoration == TEXT_DECORATION_OVERLINE)
    {
        if (textDecoration == TEXT_DECORATION_OVERLINE ||
                textDecoration == TEXT_DECORATION_OVERLINE + TEXT_DECORATION_UNDERLINE ||
                textDecoration == TEXT_DECORATION_OVERLINE + TEXT_DECORATION_LINE_THROUGH ||
                textDecoration == TEXT_DECORATION_OVERLINE + TEXT_DECORATION_UNDERLINE + TEXT_DECORATION_LINE_THROUGH)
            return true;
    }
    else if (decoration == TEXT_DECORATION_UNDERLINE)
    {
        if (textDecoration == TEXT_DECORATION_UNDERLINE ||
                textDecoration == TEXT_DECORATION_UNDERLINE + TEXT_DECORATION_OVERLINE ||
                textDecoration == TEXT_DECORATION_UNDERLINE + TEXT_DECORATION_LINE_THROUGH ||
                textDecoration == TEXT_DECORATION_UNDERLINE + TEXT_DECORATION_OVERLINE + TEXT_DECORATION_LINE_THROUGH)
            return true;
    }
    else if (decoration == TEXT_DECORATION_LINE_THROUGH)
    {
        if (textDecoration == TEXT_DECORATION_LINE_THROUGH ||
                textDecoration == TEXT_DECORATION_LINE_THROUGH + TEXT_DECORATION_OVERLINE ||
                textDecoration == TEXT_DECORATION_LINE_THROUGH + TEXT_DECORATION_UNDERLINE ||
                textDecoration == TEXT_DECORATION_LINE_THROUGH + TEXT_DECORATION_OVERLINE + TEXT_DECORATION_UNDERLINE)
            return true;
    }

    return false;
}

swUI8 SwHtml::GetTextTransform(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "none") == 0)
        return TEXT_TRANSFORM_NONE;
    else if (stricmp(value, "capitalize") == 0)
        return TEXT_TRANSFORM_CAPITALIZE;
    else if (stricmp(value, "uppercase") == 0)
        return TEXT_TRANSFORM_UPPERCASE;
    else if (stricmp(value, "lowercase") == 0)
        return TEXT_TRANSFORM_LOWERCASE;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetFontVariant(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "normal") == 0)
        return FONT_VARIANT_NORMAL;
    else if (stricmp(value, "small-caps") == 0)
        return FONT_VARIANT_SMALLCAPS;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetTextDirection(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "rtl") == 0)
        return TEXT_DIRECTION_LTR;
    else if (stricmp(value, "ltr") == 0)
        return TEXT_DIRECTION_RTL;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetFontWeight(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "normal") == 0)
        return FONT_WEIGHT_NORMAL;
    else if (stricmp(value, "bold") == 0)
        return FONT_WEIGHT_BOLD;
    else if (stricmp(value, "bolder") == 0)
        return FONT_WEIGHT_BOLDER;
    else if (stricmp(value, "lighter") == 0)
        return FONT_WEIGHT_LIGHTER;
    else if (stricmp(value, "100") == 0)
        return FONT_WEIGHT_100;
    else if (stricmp(value, "200") == 0)
        return FONT_WEIGHT_200;
    else if (stricmp(value, "300") == 0)
        return FONT_WEIGHT_300;
    else if (stricmp(value, "400") == 0)
        return FONT_WEIGHT_400;
    else if (stricmp(value, "500") == 0)
        return FONT_WEIGHT_500;
    else if (stricmp(value, "600") == 0)
        return FONT_WEIGHT_600;
    else if (stricmp(value, "700") == 0)
        return FONT_WEIGHT_700;
    else if (stricmp(value, "800") == 0)
        return FONT_WEIGHT_800;
    else if (stricmp(value, "900") == 0)
        return FONT_WEIGHT_900;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetListStyle(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "armenian") == 0)
        return LIST_STYLE_TYPE_ARMENIAN;
    else if (stricmp(value, "circle") == 0)
        return LIST_STYLE_TYPE_CIRCLE;
    else if (stricmp(value, "decimal") == 0)
        return LIST_STYLE_TYPE_DECIMAL;
    else if (stricmp(value, "decimal-leading-zero") == 0)
        return LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO;
    else if (stricmp(value, "disc") == 0)
        return LIST_STYLE_TYPE_DISC;
    else if (stricmp(value, "hebrew") == 0)
        return LIST_STYLE_TYPE_HEBREW;
    else if (stricmp(value, "lower-alpha") == 0)
        return LIST_STYLE_TYPE_LOWER_ALPHA;
    else if (stricmp(value, "upper-alpha") == 0)
        return LIST_STYLE_TYPE_UPPER_ALPHA;
    else if (stricmp(value, "lower-roman") == 0)
        return LIST_STYLE_TYPE_LOWER_ROMAN;
    else if (stricmp(value, "upper-roman") == 0)
        return LIST_STYLE_TYPE_UPPER_ROMAN;
    else if (stricmp(value, "lower-greek") == 0)
        return LIST_STYLE_TYPE_LOWER_GREEK;
    else if (stricmp(value, "upper-greek") == 0)
        return LIST_STYLE_TYPE_UPPER_GREEK;
    else if (stricmp(value, "lower-latin") == 0)
        return LIST_STYLE_TYPE_LOWER_LATIN;
    else if (stricmp(value, "upper-latin") == 0)
        return LIST_STYLE_TYPE_UPPER_LATIN;
    else if (stricmp(value, "square") == 0)
        return LIST_STYLE_TYPE_SQUARE;

    if (strcmp(value, "A") == 0)
        return LIST_STYLE_TYPE_UPPER_ALPHA;
    else if (strcmp(value, "a") == 0)
        return LIST_STYLE_TYPE_LOWER_ALPHA;
    else if (strcmp(value, "I") == 0)
        return LIST_STYLE_TYPE_UPPER_ROMAN;
    else if (strcmp(value, "i") == 0)
        return LIST_STYLE_TYPE_LOWER_ROMAN;
    else if (strcmp(value, "1") == 0)
        return LIST_STYLE_TYPE_DECIMAL;

    return ATTRIBUTE_UNSPECIFIED;
}

void SwHtml::FormatListNumber(long value, swUI8 listType, SwString & buffer)
{
    if (listType == LIST_STYLE_TYPE_DECIMAL)
    {
        buffer.Itoa(value);

        while (buffer.Strlen() < 3)
            buffer.Insert(0, " ");
    }
    else if (listType == LIST_STYLE_TYPE_LOWER_ALPHA)
    {
        buffer += (char) value;
    }
    else if (listType == LIST_STYLE_TYPE_UPPER_ALPHA)
    {
        buffer += (char) value;
    }
    else if (listType == LIST_STYLE_TYPE_LOWER_ROMAN)
    {
        SwString::ToRoman(buffer, value, false);
        while (buffer.Strlen() < 4)
            buffer.Insert(0, " ");
    }
    else if (listType == LIST_STYLE_TYPE_UPPER_ROMAN)
    {
        SwString::ToRoman(buffer, value, true);
        while (buffer.Strlen() < 4)
            buffer.Insert(0, " ");
    }

    buffer += ".  ";
}

void SwHtml::GetFont(const char * value, SwFont & font)
{
    if (!value)
        return;

    font.Reset();

    const char *pslash = strchr(value, '/');
    const char *plcomma = strrchr(value, ',');
    const char *pface = strchr(&pslash[3], ' ');

    if (!pslash || !plcomma || !pface)
        return;

    // Font Family
    while (*plcomma == ' ')
        plcomma ++;

    font.family = GetFontFamily(plcomma);
    //

    // Font Size
    while (pslash <= value)
    {
        if (*pslash == ' ')
            break;

        pslash --;
    }

    if (*pslash == ' ')
        pslash ++;

    GetFontSize(pslash, font.size, font.unit);
    //

    // Font Style
    font.style = GetFontStyle(value);
    //
    const char *p = value;
    swUI32 pos = strlen(value);

    while (pos > 0)
    {
        if (p[pos] == '\'')
            break;

        pos --;
    }

    if (p[pos] == '\'')
    {
        pos ++;

        while (p[pos] == ' ')
            pos ++;
    }

    while (*p != '\0' && !isdigit(*p))
        p++;

    if (*p == '\0')
        p = value;

    font.variant = GetFontVariant(p);
    font.weight = GetFontWeight(p);
}

swUI8 SwHtml::GetFontStyle(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "normal") == 0)
        return FONT_STYLE_NORMAL;
    else if (stricmp(value, "italic") == 0)
        return FONT_STYLE_ITALIC;
    else if (stricmp(value, "oblique") == 0)
        return FONT_STYLE_OBLIQUE;

    return ATTRIBUTE_UNSPECIFIED;
}

const char * SwHtml::GetFontFace(const char * value)
{
    if (!value)
        return "";

    // Return value must be freed by calling function.
    const char * src = value;
    swUI32 pos = 0;
    char * p = NULL;

    while (*src != '"' && *src != '\'' && *src != ',' && *src != '\0')
    {
        src ++;
        pos ++;
    }

    if (pos)
    {
        p = (char *) malloc(pos + 1);

        if (p)
        {
            memcpy(p, value, pos);
            p[pos] = '\0';
        }
    }

    return p;
}

swUI8 SwHtml::GetFontFamily(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "serif") == 0)
        return FONT_FAMILY_SERIFF;
    else if (stricmp(value, "sans-serif") == 0)
        return FONT_FAMILY_SANS_SERIFF;
    else if (stricmp(value, "fantasy") == 0)
        return FONT_FAMILY_FANTASY;
    else if (stricmp(value, "decorative") == 0)
        return FONT_FAMILY_DECORATIVE;
    else if (stricmp(value, "monospace") == 0)
        return FONT_FAMILY_MONOSPACE;
    else if (stricmp(value, "cursive") == 0)
        return FONT_FAMILY_CURSIVE;
    else if (stricmp(value, "script") == 0)
        return FONT_FAMILY_SCRIPT;
    else if (stricmp(value, "teletype") == 0)
        return FONT_FAMILY_TELETYPE;
    else if (stricmp(value, "roman") == 0)
        return FONT_FAMILY_ROMAN;
    else if (stricmp(value, "times") == 0)
        return FONT_FAMILY_TIMES;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetWhiteSpace(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "normal") == 0)
        return WHITE_SPACE_NORMAL;
    else if (stricmp(value, "nowrap") == 0)
        return WHITE_SPACE_NOWRAP;
    else if (stricmp(value, "pre") == 0)
        return WHITE_SPACE_PRE;
    else if (stricmp(value, "pre-line") == 0)
        return WHITE_SPACE_PRE_LINE;
    else if (stricmp(value, "pre-wrap") == 0)
        return WHITE_SPACE_PRE_WRAP;

    return ATTRIBUTE_UNSPECIFIED;
}

void SwHtml::GetMargins(const char * value, SwBoxAttr & box)
{
    if (!value)
        return;

    const char * p = value;
    char buf[100];
    int pos = 0;

    box.Reset();

    if (strstr(value, "inherit"))
    {
        box.left = ATTRIBUTE_INHERIT;
        box.leftUnit = UNIT_PREDEFINED;
        return;
    }

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.top, box.topUnit);

    p += ScanPastWhiteSpace(p);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.right, box.rightUnit);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.bottom, box.bottomUnit);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.left, box.leftUnit);
}

void SwHtml::GetPadding(const char * value, SwBoxAttr & box)
{
    if (!value)
        return;

    const char * p = value;
    char buf[100];
    int pos = 0;

    box.Reset();

    if (strstr(value, "inherit"))
    {
        box.left = ATTRIBUTE_INHERIT;
        box.leftUnit = UNIT_PREDEFINED;
        return;
    }

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.top, box.topUnit);

    p += ScanPastWhiteSpace(p);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.right, box.rightUnit);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.bottom, box.bottomUnit);

    pos = 0;

    while (pos < 99 && *p != '\0' && *p != ' ' && *p != ';')
    {
        buf[pos] = *p;
        p++;
        pos ++;
    }

    if (pos < 3)
        return;

    GetFloatData(buf, box.left, box.leftUnit);
}

void SwHtml::GetBorderWidth(const char * value, float & borderWidth, swUI8 & borderUnit)
{
    if (!value)
        return;

    if (isdigit(*value))
    {
        GetFloatData(value, borderWidth, borderUnit);
        return;
    }

    if (stricmp(value, "inherit") == 0)
    {
        borderWidth = ATTRIBUTE_INHERIT;
        borderUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "thick") == 0)
    {
        borderWidth = BORDER_WIDTH_THICK;
        borderUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "thin") == 0)
    {
        borderWidth = BORDER_WIDTH_THIN;
        borderUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "medium") == 0)
    {
        borderWidth = BORDER_WIDTH_MEDIUM;
        borderUnit = UNIT_PREDEFINED;
        return;
    }

    borderWidth = ATTRIBUTE_UNSPECIFIED;
    borderUnit = UNIT_NONE;
}

void SwHtml::GetFontSize(const char * value, float & fontSize, swUI8 & fontUnit)
{
    if (!value)
        return;

    if (isdigit(*value) || value[0] == '.')
    {
        GetFloatData(value, fontSize, fontUnit);
        if (fontUnit == UNIT_PERCENT)
        {
            fontSize = fontSize / 100;
        }
        else if (fontUnit == UNIT_EM)
        {
            // Nothing to do here.
        }

        return;
    }

    if (stricmp(value, "inherit") == 0)
    {
        fontSize = ATTRIBUTE_INHERIT;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "xx-small") == 0)
    {
        fontSize = FONT_SIZE_XX_SMALL;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "x-small") == 0)
    {
        fontSize = FONT_SIZE_X_SMALL;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "small") == 0)
    {
        fontSize = FONT_SIZE_SMALL;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "medium") == 0)
    {
        fontSize = FONT_SIZE_MEDIUM;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "large") == 0)
    {
        fontSize = FONT_SIZE_LARGE;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "x-large") == 0)
    {
        fontSize = FONT_SIZE_X_LARGE;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "xx-large") == 0)
    {
        fontSize = FONT_SIZE_XX_LARGE;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "smaller") == 0)
    {
        fontSize = FONT_SIZE_SMALLER;
        fontUnit = UNIT_PREDEFINED;
        return;
    }
    else if (stricmp(value, "larger") == 0)
    {
        fontSize = FONT_SIZE_LARGER;
        fontUnit = UNIT_PREDEFINED;
        return;
    }

    fontSize = ATTRIBUTE_UNSPECIFIED;
    fontUnit = UNIT_NONE;
}

swUI8 SwHtml::GetMapType(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "html") == 0)
        return MAP_TYPE_HTML;
    else if (stricmp(value, "regional") == 0)
        return MAP_TYPE_REGIONAL;

    return ATTRIBUTE_UNSPECIFIED;
}

swUI8 SwHtml::GetAreaType(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "inherit") == 0)
        return ATTRIBUTE_INHERIT;
    else if (stricmp(value, "rect") == 0)
        return AREA_TYPE_RECTANGLE;
    else if (stricmp(value, "circle") == 0)
        return AREA_TYPE_CIRCLE;
    else if (stricmp(value, "poly") == 0)
        return AREA_TYPE_POLYGON;
    else if (stricmp(value, "path") == 0)
        return AREA_TYPE_PATH;
    else if (stricmp(value, "image") == 0)
        return AREA_TYPE_IMAGE;

    return ATTRIBUTE_UNSPECIFIED;
}

const char * SwHtml::GetUnitString(swUI8 unit)
{
    if (unit == UNIT_CM)
        return "cm";
    else if (unit == UNIT_EM)
        return "em";
    else if (unit == UNIT_EX)
        return "ex";
    else if (unit == UNIT_INCH)
        return "in";
    else if (unit == UNIT_PC)
        return "pc";
    else if (unit == UNIT_PERCENT)
        return "%";
    else if (unit == UNIT_PT)
        return "pt";
    else if (unit == UNIT_PX)
        return "px";
    else if (unit == UNIT_MM)
        return "mm";

    return "";
}

void SwHtml::GetFloatData(const char * value, float & data, swUI8 & unit)
{
    if (!value)
        return;

    const char * p = value;
    if (!isdigit(value[0]) && value[0] != '-' && value[0] != '.')
    {
        unit = UNIT_PREDEFINED;
    }

    while (isdigit(*p) || *p == '-' || *p == '.')
        p++;

    data = strtof(value, NULL);

    for (swUI8 i = 1; i < N_UNIT; i++)
    {
        // Skip over predefined to avoid false results.
        if (i == UNIT_PREDEFINED)
            continue;
        if (stricmp(p, GetUnitString(i)) == 0)
        {
            unit = i;
            return;
        }
    }

    unit = UNIT_PX;
}

swUI32 SwHtml::Html2Text(const char * source, char * dest, swUI32 bufferLen, swUI8 & lastChar, bool strip)
{
    if (!source || !dest)
        return 0;

    swUI32 posDest = 0, posSource = 0, encodedLength = 0;
    wchar_t uniChar;
    char encoded[32];

    while (source[posSource] != '\0' && posDest < bufferLen - 1)
    {
        if (source[posSource] == '<')
        {
            while (source[posSource] != '\0')
            {
                if (source[posSource] == '>')
                {
                    posSource ++;
                    break;
                }

                posSource ++;
            }
        }

        if (source[posSource] == '\r')
        {
            posSource ++;
            continue;
        }

        if (strip && (source[posSource] == '\n' || source[posSource] == '\t' || source[posSource] == ' '))
        {
            if (lastChar != LCH_CHAR)
            {
                posSource ++;
                continue;
            }

            dest[posDest] = ' ';
            posSource ++;
            posDest ++;
            lastChar = LCH_SPACE;
            continue;
        }

        if (source[posSource] == '&' && source[posSource + 1] == '#')
        {
            posSource += 2;
            uniChar = (wchar_t) strtoul(&source[posSource], NULL, 10);

            if (posDest + 4 < bufferLen - 1)
                posDest += GetUtf8Char(uniChar, &dest[posDest], bufferLen - (posDest + 5));

            while (source[posSource] != ';' && source[posSource] != '\0')
                posSource ++;

            if (source[posSource] == ';')
                posSource ++;

            lastChar = LCH_CHAR;
            continue;
        }

        if (source[posSource] == '&')
        {
            posSource ++;
            encodedLength = 0;

            while (source[posSource + encodedLength] != ';' && source[posSource] != '\0' && encodedLength < 32)
            {
                encoded[encodedLength] = source[posSource + encodedLength];
                encodedLength ++;
            }

            posSource += encodedLength;
            while (source[posSource] != ';' && source[posSource] != '\0')
                posSource ++;

            if (source[posSource] == ';')
                posSource ++;

            encoded[encodedLength] = '\0';
            posDest += SwHtmlEncodedChar::GetEncodedCharValue(encoded, &dest[posDest], bufferLen - posDest);
            lastChar = LCH_CHAR;
            continue;
        }

        dest[posDest] = source[posSource];
        lastChar = LCH_CHAR;
        posSource ++;
        posDest ++;
    }

    dest[posDest] = '\0';
    return posDest;
}

swUI32 SwHtml::Html2Text(swUI32 count, const char * source, char * dest, swUI32 bufferLen, swUI8 & lastChar, bool strip)
{
    if (!source || !dest)
        return 0;

    swUI32 posDest = 0, posSource = 0, encodedLength = 0;
    wchar_t uniChar;
    char encoded[32];


    while (posSource < count && posDest < bufferLen - 1)
    {
        if (source[posSource] == '<')
        {
            while (posSource < count)
            {
                if (source[posSource] == '>')
                {
                    posSource ++;
                    break;
                }

                posSource ++;
            }
        }

        if (source[posSource] == '\r')
        {
            posSource ++;
            continue;
        }

        if (strip && (source[posSource] == '\n' || source[posSource] == '\t' || source[posSource] == ' '))
        {
            if (lastChar != LCH_CHAR)
            {
                posSource ++;
                continue;
            }

            dest[posDest] = ' ';
            posSource ++;
            posDest ++;
            lastChar = LCH_SPACE;
            continue;
        }

        if (source[posSource] == '&' && source[posSource + 1] == '#')
        {
            posSource += 2;
            uniChar = (wchar_t) strtoul(&source[posSource], NULL, 10);

            if (posDest + 4 < bufferLen - 1)
                posDest += GetUtf8Char(uniChar, &dest[posDest], bufferLen - (posDest + 5));

            while (source[posSource] != ';' && source[posSource] != '\0')
                posSource ++;

            if (source[posSource] == ';')
                posSource ++;

            lastChar = LCH_CHAR;
            continue;
        }

        if (source[posSource] == '&')
        {
            posSource ++;
            encodedLength = 0;

            while (source[posSource + encodedLength] != ';' && source[posSource] != '\0' && encodedLength < 32)
            {
                encoded[encodedLength] = source[posSource + encodedLength];
                encodedLength ++;
            }

            posSource += encodedLength;
            while (source[posSource] != ';' && source[posSource] != '\0')
                posSource ++;

            if (source[posSource] == ';')
                posSource ++;

            encoded[encodedLength] = '\0';
            posDest += SwHtmlEncodedChar::GetEncodedCharValue(encoded, &dest[posDest], bufferLen - posDest);
            lastChar = LCH_CHAR;
            continue;
        }

        dest[posDest] = source[posSource];
        lastChar = LCH_CHAR;
        posSource ++;
        posDest ++;
    }

    dest[posDest] = '\0';
    return posDest;
}

swUI8 SwHtml::GetScope(const char * value)
{
    if (!value)
        return ATTRIBUTE_UNSPECIFIED;

    if (stricmp(value, "first-letter") == 0)
        return CSS_SCOPE_FIRST_LETTER;
    else if (stricmp(value, "first-word") == 0)
        return CSS_SCOPE_FIRST_WORD;

    return ATTRIBUTE_UNSPECIFIED;
}

void SwHtml::ConvertRectangleFromHtml(SwPoint pointLeft, SwPoint & pointRight)
{
    // Convert from html rectangle, where 2nd point represents coordinates,
    // to wx rectangle where 2nd point represents width, and height.
    // Use polygon in html to prevent problems from this.
    if (pointRight.x > pointLeft.x)
        pointRight.x = pointRight.x - pointLeft.x;
    else
        pointRight.x = pointLeft.x - pointRight.x;

    if (pointRight.y > pointLeft.y)
        pointRight.y = pointRight.y - pointLeft.y;
    else
        pointRight.y = pointLeft.y - pointRight.y;
}

void SwHtml::ConvertRectangleToHtml(SwPoint pointLeft, SwPoint & pointRight)
{
    // Convert to html rectangle, where 2nd point represents coordinates,
    // from wx rectangle where 2nd point represents width, and height.
    // Use polygon in html to prevent problems from this.

    pointRight.x = pointRight.x + pointLeft.x;
    pointRight.y = pointRight.y + pointLeft.y;
}

swUI32 SwHtml::CalculatePointsNeededForCoords(swUI32 nCoords)
{
    swUI32 pointsNeeded = nCoords / 2;
    if (pointsNeeded * 2 != nCoords)
        pointsNeeded ++;

    return pointsNeeded;
}

void SwHtml::GetVector(const char * value, float & x, float & y, float & z)
{
    if (!value)
        return;

    SwStrParser strList;
    strList.ParseString(value);

    x = 0;
    y = 0;
    z = 0;

    if (strList.GetItems() < 3)
        return;

    const char * p = strList.GetItem(0);
    p += ScanPastWhiteSpace(p);

    x = strtod(p, NULL);

    p = strList.GetItem(1);
    p += ScanPastWhiteSpace(p);

    y = strtod(p, NULL);

    p = strList.GetItem(2);
    p += ScanPastWhiteSpace(p);

    z = strtod(p, NULL);
}

void SwHtml::GetBoxVector(const char * value, float & nx, float & fx, float & ny,  float & fy, float & nz, float & fz)
{
    if (!value)
        return;

    SwStrParser strList;
    strList.ParseString(value);

    nx = 0;
    fx = 0;
    ny = 0;
    fy = 0;
    nz = 0;
    fz = 0;

    if (strList.GetItems() < 6)
        return;

    const char * p = strList.GetItem(0);
    p += ScanPastWhiteSpace(p);

    nx = strtod(p, NULL);

    p = strList.GetItem(1);
    p += ScanPastWhiteSpace(p);

    fx = strtod(p, NULL);

    p = strList.GetItem(2);
    p += ScanPastWhiteSpace(p);

    ny = strtod(p, NULL);

    p = strList.GetItem(3);
    p += ScanPastWhiteSpace(p);

    fy = strtod(p, NULL);

    p = strList.GetItem(4);
    p += ScanPastWhiteSpace(p);

    nz = strtod(p, NULL);

    p = strList.GetItem(5);
    p += ScanPastWhiteSpace(p);

    fz = strtod(p, NULL);
}

void SwHtml::GetDimension2d(const char * value, float & width, float & height)
{
    if (!value)
        return;

    SwStrParser strList;
    strList.ParseString(value);

    width = 0;
    height = 0;

    if (strList.GetItems() < 2)
        return;

    const char * p = strList.GetItem(0);
    p += ScanPastWhiteSpace(p);

    width = strtod(p, NULL);

    p = strList.GetItem(1);
    p += ScanPastWhiteSpace(p);

    height = strtod(p, NULL);
}

void SwHtml::GetDimension2d(const char * value, swUI32 & width, swUI32 & height)
{
    if (!value)
        return;

    SwStrParser strList;
    strList.ParseString(value);

    width = 0;
    height = 0;

    if (strList.GetItems() < 2)
        return;

    const char * p = strList.GetItem(0);
    p += ScanPastWhiteSpace(p);

    width = strtoul(p, NULL, 10);

    p = strList.GetItem(1);
    p += ScanPastWhiteSpace(p);

    height = strtoul(p, NULL, 10);
}

const char * SwHtml::GetInternalElementName(swUI16 id)
{
    if (id == INT_UNKNOWN)
        return "unknown";
    else if (id == INT_TEXT_RUN)
        return "text-run";
    else if (id == INT_BINARY)
        return "binary";
    else if (id == INT_MODULE)
        return "module";
    else if (id == INT_WHITE_SPACE)
        return "whitespace";

    return "";
}

swUI32 SwHtml::ScanPastWhiteSpace(const char * source)
{
    swUI32 pos = 0;

    if (!source)
        return 0;

    while (source[pos] == ' ' || source[pos] == '\t' || source[pos] == '\r' || source[pos] == '\n')
        pos ++;

    return pos;
}
