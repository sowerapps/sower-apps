///////////////////////////////////////////////////////////////////
// Name:        html_color.cpp
// Purpose:     Get color value from HTML color name.
//              Conversion from HSL, Hue to rgb.
//              Conversion from rgb to bgr.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/html_color.h"
#include "../../include/string/string.h"
#include "../../include/appi/appifa.h"

struct HTML_NAMED_COLOR
{
    const char * name;
    swUI32       value;
};

static const swI16 ColorNameAlphabeticIdx [] =
{
    0, 5, 13, 21, -1, 42, 46, 53, 55, -1, 58, 59, 79, 94, 95, 102, -1, 113, 116, 129,
    -1, 134, 135, -1, 138, -1
};

static const HTML_NAMED_COLOR NamedColors [] =
{
    {"aliceblue",               15792383},
    {"antiquewhite",            16444375},
    {"aqua",                       65535},
    {"aquamarine",               8388564},
    {"azure",                   15794175},
    {"beige",                   16119260},
    {"bisque",                  16770244},
    {"black",                          0},
    {"blanchedalmond",          16772045},
    {"blue",                         255},
    {"blueviolet",               9055202},
    {"brown",                   10824234},
    {"burlywood",               14596231},
    {"cadetblue",                6266528},
    {"chartreuse",               8388352},
    {"chocolate",               13789470},
    {"coral",                   16744272},
    {"cornflowerblue",           6591981},
    {"cornsilk",                16775388},
    {"crimson",                 14423100},
    {"cyan",                       65535},
    {"darkblue",                     139},
    {"darkcyan",                   35723},
    {"darkgoldenrod",           12092939},
    {"darkgray",                11119017},
    {"darkgreen",                  25600},
    {"darkkhaki",               12433259},
    {"darkmagenta",              9109643},
    {"darkolivegreen",           5597999},
    {"darkorange",              16747520},
    {"darkorchid",              10040012},
    {"darkred",                  9109504},
    {"darksalmon",              15308410},
    {"darkseagreen",             9419919},
    {"darkslateblue",            4734347},
    {"darkslategray",            3100495},
    {"darkturquoise",              52945},
    {"darkviolet",               9699539},
    {"deeppink",                16716947},
    {"deepskyblue",                49151},
    {"dimgray",                  6908265},
    {"dodgerblue",               2003199},
    {"firebrick",               11674146},
    {"floralwhite",             16775920},
    {"forestgreen",              2263842},
    {"fuchsia",                 16711935},
    {"gainsboro",               14474460},
    {"ghostwhite",              16316671},
    {"gold",                    16766720},
    {"goldenrod",               14329120},
    {"gray",                     8421504},
    {"green",                      32768},
    {"greenyellow",             11403055},
    {"honeydew",                15794160},
    {"hotpink",                 16738740},
    {"indianred",               13458524},
    {"indigo",                   4915330},
    {"ivory",                   16777200},
    {"khaki",                   15787660},
    {"lavender",                15132410},
    {"lavenderblush",           16773365},
    {"lawngreen",                8190976},
    {"lemonchiffon",            16775885},
    {"lightblue",               11393254},
    {"lightcoral",              15761536},
    {"lightcyan",               14745599},
    {"lightgoldenrodyellow",    16448210},
    {"lightgray",               13882323},
    {"lightgreen",               9498256},
    {"lightpink",               16758465},
    {"lightsalmon",             16752762},
    {"lightseagreen",            2142890},
    {"lightskyblue",             8900346},
    {"lightslategray",           7833753},
    {"lightsteelblue",          11584734},
    {"lightyellow",             16777184},
    {"lime",                       65280},
    {"limegreen",                3329330},
    {"linen",                   16445670},
    {"magenta",                 16711935},
    {"maroon",                   8388608},
    {"mediumauqamarine",         6737322},
    {"mediumblue",                   205},
    {"mediumorchid",            12211667},
    {"mediumpurple",             9662680},
    {"mediumseagreen",           3978097},
    {"mediumslateblue",          8087790},
    {"mediumspringgreen",          64154},
    {"mediumturquoise",          4772300},
    {"mediumvioletred",         13047173},
    {"midnightblue",             1644912},
    {"mintcream",               16121850},
    {"mistyrose",               16770273},
    {"moccasin",                16770229},
    {"navajowhite",             16768685},
    {"navy",                         128},
    {"oldlace",                 16643558},
    {"olive",                    8421376},
    {"olivedrab",                6852131},
    {"orange",                  16753920},
    {"orangered",               16729344},
    {"orchid",                  14315734},
    {"palegoldenrod",           15657130},
    {"palegreen",               10025880},
    {"paleturquoise",           11529966},
    {"palevioletred",           14184595},
    {"papayawhip",              16773077},
    {"peachpuff",               16767673},
    {"peru",                    13468991},
    {"pink",                    16761035},
    {"plum",                    14524637},
    {"powderblue",              11591910},
    {"purple",                   8388736},
    {"red",                     16711680},
    {"rosybrown",               12357519},
    {"royalblue",                4286945},
    {"saddlebrown",              9127187},
    {"salmon",                  16416882},
    {"sandybrown",              16032864},
    {"seagreen",                 3050327},
    {"seashell",                16774638},
    {"sienna",                  10506797},
    {"silver",                  12632256},
    {"skyblue",                  8900331},
    {"slateblue",                6970061},
    {"slategray",                7372944},
    {"snow",                    16775930},
    {"springgreen",                65407},
    {"steelblue",                4620980},
    {"tan",                     13808780},
    {"teal",                       32896},
    {"thistle",                 14204888},
    {"tomato",                  16737095},
    {"turquoise",                4251856},
    {"violet",                  15631086},
    {"wheat",                   16113331},
    {"white",                   16777215},
    {"whitesmoke",              16119285},
    {"yellow",                  16776960},
    {"yellowgreen",             10145074}
};

swUI32 SwHtmlColor::GetColorIndexFromName(const char * name)
{
    swUI8 IdxPos;

    if (!name || name[0] < 'a' ||name[0] > 'z')
        return NO_COLOR;

    IdxPos = ColorNameAlphabeticIdx[name[0] - 'a'];

    if (IdxPos == -1)
        return NO_COLOR;

    while (IdxPos < NAMED_COLORS)
    {
        if (strcmp(NamedColors[IdxPos].name, name) == 0)
        {
            return IdxPos;
        }

        if (NamedColors[IdxPos].name[0] > name[0])
            break;

        IdxPos ++;
    }

    return NO_COLOR;
};

swUI32 SwHtmlColor::GetColorValueFromIdxPos(swUI8 indexPos)
{
    if (indexPos >= NAMED_COLORS)
        return NO_COLOR;

    return NamedColors[indexPos].value;
}

swUI32 SwHtmlColor::GetColorFromName(const char * name)
{
    swUI8 IdxPos;

    if (!name)
        return NO_COLOR;

    SwString buffer;
    buffer = name;
    buffer.ToLower();

    if (buffer.GetAt(0) < 'a' || buffer.GetAt(0) > 'z')
        return NO_COLOR;

    IdxPos = ColorNameAlphabeticIdx[buffer.GetAt(0) - 'a'];

    if (IdxPos == -1)
        return NO_COLOR;

    while (IdxPos < NAMED_COLORS)
    {
        if (stricmp(NamedColors[IdxPos].name, buffer) == 0)
        {
            return NamedColors[IdxPos].value;
        }

        if (NamedColors[IdxPos].name[0] > buffer.GetAt(0))
            break;

        IdxPos ++;
    }

    return NO_COLOR;
};

bool SwHtmlColor::GetRGBFromColorIdxPos(swUI8 IndexPos, swUI8 & red, swUI8 & green, swUI8 & blue)
{
    if (IndexPos >= NAMED_COLORS)
        return false;

    swUI32 value;
    swUI8 * p = (swUI8 *) &value;

    value = NamedColors[IndexPos].value;

    red = p[2];
    green = p[1];
    blue = p[0];

    return true;
}

bool SwHtmlColor::GetRGBFromStringValue(const char * source, swUI8 & red, swUI8 & green, swUI8 & blue, swUI8 & alpha)
{
    if (!source)
        return false;

    const char * pdigit = source;

    while (!isdigit(*pdigit) && *pdigit != '\0')
        pdigit ++;

    if (*pdigit == '\0')
        return false;

    swUI32 value = strtoul(pdigit, NULL, 10);
    swUI8 * p = (swUI8 *) &value;

    alpha = p[3];
    red = p[2];
    green = p[1];
    blue = p[0];

    return true;
}

swUI32 SwHtmlColor::GetColorFromStringValue(const char * source)
{
    if (!source)
        return NO_COLOR;

    const char * pdigit = source;

    while (!isdigit(*pdigit) && *pdigit != '\0')
        pdigit ++;

    return strtoul(pdigit, NULL, 10);
}

swUI32 SwHtmlColor::CombineRGB(swUI8 red, swUI8 green, swUI8 blue, swUI8 alpha)
{
    swUI32 value;
    swUI8 * p = (swUI8 *) &value;

    p[3] = alpha;
    p[2] = red;
    p[1] = green;
    p[0] = blue;

    return value;
}

void SwHtmlColor::SplitRGB(swUI32 color, swUI8 & red, swUI8 & green, swUI8 & blue, swUI8 & alpha)
{
    swUI8 * p = (swUI8 *) &color;

    alpha = p[3];
    red = p[2];
    green = p[1];
    blue = p[0];

}

swUI32 SwHtmlColor::GetColorFromRGB(const char * value)
{
    if (!value)
        return NO_COLOR;

    swUI8 r, g, b, a = 1;
    swFloat aswFloat;
    const char * p;

    p = strchr(value, '(');

    if (!p)
        return NO_COLOR;

    while (!isdigit(*p) && *p != '\0')
        p++;

    if (!isdigit(*p))
        return NO_COLOR;

    r = (swUI8) strtoul(p, NULL, 10);

    while (isdigit(*p))
        p++;

    if (*p == '%')
    {
        r = r * 2.55;
        p++;
    }


    while (!isdigit(*p) && *p != '\0')
        p++;

    if (!isdigit(*p))
        return NO_COLOR;

    g = (swUI8) strtoul(p, NULL, 10);

    while (isdigit(*p))
        p++;

    if (*p == '%')
    {
        g = g * 2.55;
        p++;
    }


    while (!isdigit(*p) && *p != '\0')
        p++;

    if (!isdigit(*p))
        return NO_COLOR;

    b = (swUI8) strtoul(p, NULL, 10);

    while (isdigit(*p))
        p++;

    if (*p == '%')
    {
        b = b * 2.55;
        p++;
    }

    while (!isdigit(*p) && *p != '\0')
        p++;

    if (!isdigit(*p))
        aswFloat = 1;
    else
    {
        aswFloat = strtod(p, NULL);

        while (isdigit(*p))
            p++;

        if (*p == '%')
        {
            aswFloat = aswFloat / 100;
            p++;
        }

        a = aswFloat * 100;
    }

    return CombineRGB(r, g, b, a);
}

swUI32 SwHtmlColor::GetColorFromHSL(const char * value)
{
    if (!value)
        return NO_COLOR;

    swFloat h, s, l, ahsl;

    const char * p;

    p = strchr(value, '(');

    if (!p)
        return NO_COLOR;

    while (!isdigit(*p) && *p != '\0' && *p != '.')
        p++;

    if (!isdigit(*p) && *p != '.')
        return NO_COLOR;

    h = strtod(p, NULL);

    while (isdigit(*p) && *p != '.')
        p++;

    if (*p == '%')
    {
        h = h * 3.6;
        p++;
    }


    while (!isdigit(*p) && *p != '\0' && *p != '.')
        p++;

    if (!isdigit(*p) && *p != '.')
        return NO_COLOR;

    s = strtod(p, NULL);

    while (isdigit(*p))
        p++;

    if (*p == '%')
    {
        s = s / 100;
        p++;
    }


    while (!isdigit(*p) && *p != '\0' && *p != '.')
        p++;

    if (!isdigit(*p) && *p != '.')
        return NO_COLOR;

    l = strtod(p, NULL);

    while (isdigit(*p))
        p++;

    if (*p == '%')
    {
        l = l / 100;
        p++;
    }

    while (!isdigit(*p) && *p != '\0')
        p++;

    if (!isdigit(*p))
        ahsl = 1;
    else
    {
        ahsl = strtod(p, NULL);

        while (isdigit(*p))
            p++;

        if (*p == '%')
        {
            ahsl = ahsl / 100;
            p++;
        }
    }

    swUI8 r, g, b, a;
    a = ahsl * 100;
    HSLtoRGB(h, s, l, r, g, b);

    return CombineRGB(r, g, b, a);
}

swUI32 SwHtmlColor::GetBGR(swUI32 color)
{
    swUI8 r, g, b, a;
    SplitRGB(color, r, g, b, a);
    return CombineRGB(b, g, r, a);
}

swUI32 SwHtmlColor::GetColor(const char * value)
{
    if (!value)
        return NO_COLOR;
    else if (*value == '#')
        return strtoul(value + 1, NULL, 16);
    else if (strstr(value, "rgb"))
        return GetColorFromRGB(value);
    else if (strstr(value, "hsl"))
        return GetColorFromHSL(value);
    else if (isdigit(*value))
        return GetColorFromStringValue(value);

    return GetColorFromName(value);
}

void SwHtmlColor::HSLtoRGB(swFloat h, swFloat s, swFloat l, swUI8 & r, swUI8 & g, swUI8 & b)
{
    swFloat var_1, var_2 = 0;

    if (s == 0)
    {
        r = l * 255;
        g = l * 255;
        b = l * 255;
    }
    else if (l < .5)
    {
        var_2 = l * (1 + s);
    }
    else
    {
        var_2 = (l + s) - (s * l);
    }

    var_1 = 2 * l - var_2;

    r = 255 * HuetoRgb(var_1, var_2, h + (1 / 3));
    g = 255 * HuetoRgb(var_1, var_2, h);
    b = 255 * HuetoRgb(var_1, var_2, h - (1 / 3));
}

swFloat SwHtmlColor::HuetoRgb(swFloat v1, swFloat v2, swFloat h)
{
    if (h < 0)
        h += 1;

    if (h > 1)
        h -= 1;

    if ((6 * h) < 1)
        return (v1 + (v2 - v1) * 6 * h);

    if ((2 * h) < 1)
        return v2;

    if ((3 * h) < 2)
        return (v1 + (v2 - v1) * ((2 / 3) - h) * 6);

    return v1;
}

void SwHtmlColor::GetColorList(wxChoice * choice)
{
    if (!choice)
        return;

    SwClientData * data;
    SwStringW buffer;

    data = new SwClientData(NO_COLOR);
    choice->Append(SwApplicationInterface::GetControlString("SID_TRANSPARENT", L"transparent"), data);

    for (swUI32 i = 0; i < NAMED_COLORS; i++)
    {
        data = new SwClientData(NamedColors[i].value);
        buffer.Copy(NamedColors[i].name);
        choice->Append(buffer.GetArray(), data);
    }
}

void SwHtmlColor::SetColor(wxChoice * choice, swUI32 color)
{
    SwClientData * data;

    for (unsigned int i = 0; i < choice->GetCount(); i ++)
    {
        data = (SwClientData *) choice->GetClientObject(i);
        if (data->m_data == color)
        {
            choice->SetSelection(i);
            break;
        }
    }
}

swUI32 SwHtmlColor::GetColorValue(wxChoice * choice)
{
    SwClientData * data;

    data = (SwClientData *) choice->GetClientObject(choice->GetSelection());
    if (data)
    {
        return data->m_data;
    }

    return NODE_ID_INVALID;
}

