///////////////////////////////////////////////////////////////////
// Name:        html_color.h
// Purpose:     Get color value from HTML color name.
//              Conversion from HSL, Hue to rgb.
//              Conversion from rgb to bgr.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HTML_COLOR_H
#define HTML_COLOR_H

#include "../sowerbase.h"
#include <wx/choice.h>

#define NO_COLOR           0xFF000000

enum HTML_COLORS
{
    COL_ALICEBLUE, COL_ANTIQUEWHITE, COL_AQUA, COL_AQUAMARINE, COL_AZURE,
    COL_BEIGE, COL_BISQUE, COL_BLACK, COL_BLANCHEDALMOND, COL_BLUE,
    COL_BLUEVIOLET, COL_BROWN, COL_BURLYWOOD, COL_CADETBLUE, COL_CHARTREUSE,
    COL_CHOCOLATE, COL_CORAL, COL_CORNFLOWERBLUE, COL_CORNSILK, COL_CRIMSON,
    COL_CYAN, COL_DARKBLUE, COL_DARKCYAN, COL_DARKGOLDENROD, COL_DARKGRAY,
    COL_DARKGREEN, COL_DARKKHAKI, COL_DARKMAGENTA, COL_DARKOLIVEGREEN, COL_DARKORANGE,
    COL_DARKORCHID, COL_DARKRED, COL_DARKSALMON, COL_DARKSEAGREEN, COL_DARKSLATEBLUE,
    COL_DARKSLATEGRAY, COL_DARKTURQUOISE, COL_DARKVIOLET, COL_DEEPPINK, COL_DEEPSKYBLUE,
    COL_DIMGRAY, COL_DODGERBLUE, COL_FIREBRICK, COL_FLORALWHITE, COL_FORESTGREEN,
    COL_FUCHSIA, COL_GAINSBORO, COL_GHOSTWHITE, COL_GOLD, COL_GOLDENROD,
    COL_GRAY, COL_GREEN, COL_GREENYELLOW, COL_HONEYDEW, COL_HOTPINK,
    COL_INDIANRED, COL_INDIGO, COL_IVORY, COL_KHAKI, COL_LAVENDER,
    COL_LAVENDERBLUSH, COL_LAWNGREEN, COL_LEMONCHIFFON, COL_LIGHTBLUE, COL_LIGHTCORAL,
    COL_LIGHTCYAN, COL_LIGHTGOLDENRODYELLOW, COL_LIGHTGRAY, COL_LIGHTGREEN, COL_LIGHTPINK,
    COL_LIGHTSALMON, COL_LIGHTSEAGREEN, COL_LIGHTSKYBLUE, COL_LIGHTSLATEGRAY, COL_LIGHTSTEELBLUE,
    COL_LIGHTYELLOW, COL_LIME, COL_LIMEGREEN, COL_LINEN, COL_MAGENTA,
    COL_MAROON, COL_MEDIUMAUQAMARINE, COL_MEDIUMBLUE, COL_MEDIUMORCHID, COL_MEDIUMPURPLE,
    COL_MEDIUMSEAGREEN, COL_MEDIUMSLATEBLUE, COL_MEDIUMSPRINGGREEN, COL_MEDIUMTURQUOISE, COL_MEDIUMVIOLETRED,
    COL_MIDNIGHTBLUE, COL_MINTCREAM, COL_MISTYROSE, COL_MOCCASIN, COL_NAVAJOWHITE,
    COL_NAVY, COL_OLDLACE, COL_OLIVE, COL_OLIVEDRAB, COL_ORANGE,
    COL_ORANGERED, COL_ORCHID, COL_PALEGOLDENROD, COL_PALEGREEN, COL_PALETURQUOISE,
    COL_PALEVIOLETRED, COL_PAPAYAWHIP, COL_PEACHPUFF, COL_PERU, COL_PINK,
    COL_PLUM, COL_POWDERBLUE, COL_PURPLE, COL_RED, COL_ROSYBROWN,
    COL_ROYALBLUE, COL_SADDLEBROWN, COL_SALMON, COL_SANDYBROWN, COL_SEAGREEN,
    COL_SEASHELL, COL_SIENNA, COL_SILVER, COL_SKYBLUE, COL_SLATEBLUE,
    COL_SLATEGRAY, COL_SNOW, COL_SPRINGGREEN, COL_STEELBLUE, COL_TAN,
    COL_TEAL, COL_THISTLE, COL_TOMATO, COL_TURQUOISE, COL_VIOLET,
    COL_WHEAT, COL_WHITE, COL_WHITESMOKE, COL_YELLOW, COL_YELLOWGREEN,
    NAMED_COLORS
};

class SOWERBASEEXP SwHtmlColor
{
public:
    static swUI32 GetColorIndexFromName(const char * name);
    static swUI32 GetColorFromName(const char * name);
    static bool GetRGBFromColorIdxPos(swUI8 IndexPos, swUI8 & red, swUI8 & green, swUI8 & blue);
    static swUI32 GetColorValueFromIdxPos(swUI8 indexPos);
    static bool GetRGBFromStringValue(const char * source, swUI8 & red, swUI8 & green, swUI8 & blue, swUI8 & alpha);
    static swUI32 GetColorFromStringValue(const char * source);
    static swUI32 CombineRGB(swUI8 red, swUI8 green, swUI8 blue, swUI8 alpha);
    static void SplitRGB(swUI32 color, swUI8 & red, swUI8 & green, swUI8 & blue, swUI8 & alpha);
    static swUI32 GetColorFromRGB(const char * value);
    static swUI32 GetColorFromHSL(const char * value);
    static swUI32 GetBGR(swUI32 color);
    static swUI32 GetColor(const char * value);
    static void HSLtoRGB(swFloat h, swFloat s, swFloat l, swUI8 & r, swUI8 & g, swUI8 & b);
    static swFloat HuetoRgb(swFloat v1, swFloat v2, swFloat h);
    static void GetColorList(wxChoice * choice);
    static void SetColor(wxChoice * choice, swUI32 color);
    static swUI32 GetColorValue(wxChoice * choice);
};

#endif // HTML_COLOR_H
