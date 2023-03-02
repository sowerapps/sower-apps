///////////////////////////////////////////////////////////////////
// Name:        html.h
// Purpose:     Primary file for working with HTML.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HTML_H
#define HTML_H

#include "../sowerbase.h"
#include "../string/string.h"

#define LINK_COLOR  128
#define HILITE_COLOR  16776960

enum CssOperator {CSS_OP_NONE, CSS_OP_SPACE, CSS_OP_GT, CSS_OP_TILDE, CSS_OP_PLUS, CSS_OP_ASTK};

// For Table class
enum CellType {CELLTYPE_TEXT, CELLTYPE_AUDIO, CELLTYPE_IMAGE, CELLTYPE_VIDEO};
//

enum AREA_TYPE
{
    // AREA_TYPE_PATH, & AREA_TYPE_IMAGE -- Not html, Sower extension.
    AREA_TYPE_RECTANGLE = 2, AREA_TYPE_CIRCLE, AREA_TYPE_POLYGON, AREA_TYPE_PATH,
    AREA_TYPE_IMAGE, N_AREA_TYPE
};

enum BORDER_COLLAPSE
{
    BORDER_COLLAPSE_COLLAPSE = 3, BORDER_COLLAPSE_SEPARATE, N_BORDER_COLLAPSE
};

enum BORDER_STYLE
{
    BORDER_STYLE_NONE = 3, BORDER_STYLE_HIDDEN, BORDER_STYLE_DOTTED, BORDER_STYLE_DASHED,
    BORDER_STYLE_SOLID, BORDER_STYLE_DOUBLE, BORDER_STYLE_GROOVE, BORDER_STYLE_RIDGE,
    BORDER_STYLE_INSET, BORDER_STYLE_OUTSET, N_BORDER_STYLE
};

enum BORDER_WIDTH
{
    BORDER_WIDTH_THIN = 3, BORDER_WIDTH_MEDIUM, BORDER_WIDTH_THICK, N_BORDER_WIDTH
};

enum TEXT_DIRECTION
{
    TEXT_DIRECTION_LTR = 3, TEXT_DIRECTION_RTL, N_TEXT_DIRECTION
};

enum FLOAT_DIRECTION
{
    FLOAT_DIRECTION_NONE = 3, FLOAT_DIRECTION_LEFT, FLOAT_DIRECTION_RIGHT, N_FLOAT_DIRECTION
};

enum FONT_FAMILY
{
    FONT_FAMILY_SERIFF = 3, FONT_FAMILY_SANS_SERIFF, FONT_FAMILY_FANTASY,
    FONT_FAMILY_DECORATIVE, FONT_FAMILY_MONOSPACE, FONT_FAMILY_CURSIVE, FONT_FAMILY_SCRIPT,
    FONT_FAMILY_TELETYPE, FONT_FAMILY_ROMAN, FONT_FAMILY_TIMES,
    N_FONT_FAMILY
};

enum FONT_SIZE
{
    FONT_SIZE_XX_SMALL = 3, FONT_SIZE_X_SMALL, FONT_SIZE_SMALL, FONT_SIZE_MEDIUM,
    FONT_SIZE_LARGE, FONT_SIZE_X_LARGE, FONT_SIZE_XX_LARGE,
    FONT_SIZE_SMALLER, FONT_SIZE_LARGER, N_FONT_SIZE
};

enum FONT_STYLE
{
    FONT_STYLE_NORMAL = 3, FONT_STYLE_ITALIC, FONT_STYLE_OBLIQUE, N_FONT_STYLE
};

enum FONT_VARIANT
{
    FONT_VARIANT_NORMAL = 3, FONT_VARIANT_SMALLCAPS, N_FONT_VARIANT
};

enum FONT_WEIGHT
{
    FONT_WEIGHT_NORMAL = 3, FONT_WEIGHT_BOLD, FONT_WEIGHT_BOLDER, FONT_WEIGHT_LIGHTER,
    FONT_WEIGHT_100, FONT_WEIGHT_200, FONT_WEIGHT_300, FONT_WEIGHT_400, FONT_WEIGHT_500,
    FONT_WEIGHT_600, FONT_WEIGHT_700, FONT_WEIGHT_800, FONT_WEIGHT_900, N_FONT_WEIGHT
};

enum LIST_STYLE_TYPE
{
    LIST_STYLE_TYPE_ARMENIAN = 3, LIST_STYLE_TYPE_CIRCLE, LIST_STYLE_TYPE_DECIMAL, LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO,
    LIST_STYLE_TYPE_DISC, LIST_STYLE_TYPE_HEBREW, LIST_STYLE_TYPE_LOWER_ALPHA, LIST_STYLE_TYPE_UPPER_ALPHA,
    LIST_STYLE_TYPE_LOWER_ROMAN, LIST_STYLE_TYPE_UPPER_ROMAN, LIST_STYLE_TYPE_LOWER_GREEK,
    LIST_STYLE_TYPE_UPPER_GREEK, LIST_STYLE_TYPE_LOWER_LATIN, LIST_STYLE_TYPE_UPPER_LATIN,
    LIST_STYLE_TYPE_SQUARE, N_LIST_STYLE_TYPE
};

enum TEXT_ALIGN
{
    TEXT_ALIGN_NONE = 3, TEXT_ALIGN_LEFT, TEXT_ALIGN_RIGHT,
    TEXT_ALIGN_CENTER, TEXT_ALIGN_JUSTIFY, N_TEXT_ALIGN
};

enum TEXT_DECORATION
{
    TEXT_DECORATION_NONE = 4, TEXT_DECORATION_OVERLINE = 8,
    TEXT_DECORATION_UNDERLINE = 16, TEXT_DECORATION_LINE_THROUGH = 32,
    N_TEXT_DECORATION
};

enum TEXT_TRANSFORM
{
    TEXT_TRANSFORM_NONE = 3, TEXT_TRANSFORM_CAPITALIZE,
    TEXT_TRANSFORM_UPPERCASE, TEXT_TRANSFORM_LOWERCASE,
    N_TEXT_TRANSFORM
};

enum VERTICAL_ALIGN
{
    VERTICAL_ALIGN_BASELINE = 3, VERTICAL_ALIGN_SUB, VERTICAL_ALIGN_SUPER,
    VERTICAL_ALIGN_TOP, VERTICAL_ALIGN_TEXT_TOP, VERTICAL_ALIGN_MIDDLE,
    VERTICAL_ALIGN_BOTTOM, VERTICAL_ALIGN_TEXT_BOTTOM, N_VERTICAL_ALIGN
};

enum WHITE_SPACE
{
    WHITE_SPACE_NORMAL = 3, WHITE_SPACE_NOWRAP, WHITE_SPACE_PRE,
    WHITE_SPACE_PRE_LINE, WHITE_SPACE_PRE_WRAP, N_WHITE_SPACE
};

enum HTML_METHOD_TYPE
{
    METHOD_TYPE_GET = 3, METHOD_TYPE_POST, N_METHOD_TYPES
};

enum SYNC_TYPE
{
    SYNC_TYPE_GREEK = 1, SYNC_TYPE_HEBREW, N_SYNC_TYPE
};

enum CSS_COMMON
{
    ATTRIBUTE_UNSPECIFIED = 0, ATTRIBUTE_INHERIT, ATTRIBUTE_UNKNOWN, N_CSS_COMMON
};

enum CSS_NODE_TYPE
{
    CSS_TYPE_INVALID, CSS_TYPE_ATTRIBUTE, CSS_TYPE_CLASS,
    CSS_TYPE_ELEMENT, CSS_TYPE_PSDCLASS, CSS_TYPE_SELECTOR,
    CSS_TYPE_SET, CSS_TYPE_STYLE, CSS_TYPE_ID, CSS_TYPE_VALUE
};

enum CSS_SCOPE
{
    CSS_SCOPE_FIRST_LETTER = 3, CSS_SCOPE_FIRST_WORD,
    N_CSS_SCOPE
};

enum ENUM_ATTRIBUTE_VALUES
{
    AREA_TYPE_ITEMS         =   N_AREA_TYPE       - N_CSS_COMMON,
    BORDER_COLLAPSE_ITEMS   =   N_BORDER_COLLAPSE - N_CSS_COMMON,
    BORDER_STYLE_ITEMS      =   N_BORDER_STYLE    - N_CSS_COMMON,
    BORDER_WIDTH_ITEMS      =   N_BORDER_WIDTH    - N_CSS_COMMON,
    TEXT_DIRECTION_ITEMS    =   N_TEXT_DIRECTION  - N_CSS_COMMON,
    FLOAT_DIRECTION_ITEMS   =   N_FLOAT_DIRECTION - N_CSS_COMMON,
    FONT_FAMILY_ITEMS       =   N_FONT_FAMILY     - N_CSS_COMMON,
    FONT_SIZE_ITEMS         =   N_FONT_SIZE       - N_CSS_COMMON,
    FONT_STYLE_ITEMS        =   N_FONT_STYLE      - N_CSS_COMMON,
    FONT_VARIANT_ITEMS      =   N_FONT_VARIANT    - N_CSS_COMMON,
    FONT_WEIGHT_ITEMS       =   N_FONT_WEIGHT     - N_CSS_COMMON,
    LIST_STYLE_TYPE_ITEMS   =   N_LIST_STYLE_TYPE - N_CSS_COMMON,
    TEXT_ALIGN_ITEMS        =   N_TEXT_ALIGN      - N_CSS_COMMON,
    TEXT_DECORATION_ITEMS   =   4,
    TEXT_TRANSFORM_ITEMS    =   N_TEXT_TRANSFORM  - N_CSS_COMMON,
    VERTICAL_ALIGN_ITEMS    =   N_VERTICAL_ALIGN  - N_CSS_COMMON,
    WHITE_SPACE_ITEMS       =   N_WHITE_SPACE     - N_CSS_COMMON,
    METHOD_TYPE_ITEMS       =   N_METHOD_TYPES    - N_CSS_COMMON,
    SYNC_TYPE_ITEMS         =   N_SYNC_TYPE       - N_CSS_COMMON
};

enum CSS_ATTRIBUTES
{
    CSS_ATTR_UNKNOWN, CSS_ATTR_BACKGROUND_COLOR, CSS_ATTR_BORDER,
    CSS_ATTR_BORDER_COLLAPSE,
    CSS_ATTR_BORDER_COLOR, CSS_ATTR_BORDER_STYLE, CSS_ATTR_BORDER_WIDTH,
    CSS_ATTR_BORDER_SPACING, CSS_ATTR_BORDER_BOTTOM, CSS_ATTR_BORDER_BOTTOM_COLOR,
    CSS_ATTR_BORDER_BOTTOM_STYLE, CSS_ATTR_BORDER_BOTTOM_WIDTH, CSS_ATTR_BORDER_LEFT,
    CSS_ATTR_BORDER_LEFT_COLOR, CSS_ATTR_BORDER_LEFT_STYLE, CSS_ATTR_BORDER_LEFT_WIDTH,
    CSS_ATTR_BORDER_RIGHT, CSS_ATTR_BORDER_RIGHT_COLOR, CSS_ATTR_BORDER_RIGHT_STYLE,
    CSS_ATTR_BORDER_RIGHT_WIDTH, CSS_ATTR_BORDER_TOP, CSS_ATTR_BORDER_TOP_COLOR,
    CSS_ATTR_BORDER_TOP_STYLE, CSS_ATTR_BORDER_TOP_WIDTH, CSS_ATTR_COLOR,
    CSS_ATTR_DIRECTION, CSS_ATTR_DISPLAY, CSS_ATTR_FLOAT, CSS_ATTR_FONT, CSS_ATTR_FONT_FAMILY,
    CSS_ATTR_FONT_SIZE, CSS_ATTR_FONT_STYLE, CSS_ATTR_FONT_VARIANT,
    CSS_ATTR_FONT_WEIGHT, CSS_ATTR_HEIGHT, CSS_ATTR_LIST_STYLE,
    CSS_ATTR_LIST_STYLE_TYPE, CSS_ATTR_MARGIN, CSS_ATTR_MARGIN_BOTTOM,
    CSS_ATTR_MARGIN_LEFT, CSS_ATTR_MARGIN_RIGHT, CSS_ATTR_MARGIN_TOP,
    CSS_ATTR_PADDING, CSS_ATTR_PADDING_BOTTOM, CSS_ATTR_PADDING_LEFT,
    CSS_ATTR_PADDING_RIGHT, CSS_ATTR_PADDING_TOP, CSS_ATTR_TEXT_ALIGN,
    CSS_ATTR_TEXT_DECORATION, CSS_ATTR_TEXT_INDENT, CSS_ATTR_TEXT_TRANSFORM,
    CSS_ATTR_VERTICAL_ALIGN, CSS_ATTR_WHITE_SPACE, CSS_ATTR_WIDTH,
    N_CSS_ATTRS
};

enum HTML_ATTRIBUTES
{
    HTML_ATTRIBUTE_UNKNOWN,
    HTML_ATTRIBUTE_ACTION,
    HTML_ATTRIBUTE_ALIGN,
    HTML_ATTRIBUTE_ALT,
    HTML_ATTRIBUTE_ANCHORED,
    HTML_ATTRIBUTE_AUTHORID,
    HTML_ATTRIBUTE_AUTOCOMPLETE,
    HTML_ATTRIBUTE_BACKGROUND,
    HTML_ATTRIBUTE_BGCOLOR,
    HTML_ATTRIBUTE_BORDER,
    HTML_ATTRIBUTE_CELLPADDING,
    HTML_ATTRIBUTE_CELLSPACING,
    HTML_ATTRIBUTE_CHECKED,
    HTML_ATTRIBUTE_CITE,
    HTML_ATTRIBUTE_CLASS,
    HTML_ATTRIBUTE_CODE,
    HTML_ATTRIBUTE_COLOR,
    HTML_ATTRIBUTE_COLS,
    HTML_ATTRIBUTE_COLSPAN,
    HTML_ATTRIBUTE_COMPOSERID,
    HTML_ATTRIBUTE_COORDS,
    HTML_ATTRIBUTE_DIR,
    HTML_ATTRIBUTE_FACE,
    HTML_ATTRIBUTE_FILEBREAK,
    HTML_ATTRIBUTE_FORM,
    HTML_ATTRIBUTE_FORMACTION,
    HTML_ATTRIBUTE_FORMENCTYPE,
    HTML_ATTRIBUTE_FORMMETHOD,
    HTML_ATTRIBUTE_FORMNOVALIDATE,
    HTML_ATTRIBUTE_FORMTARGET,
    HTML_ATTRIBUTE_HEIGHT,
    HTML_ATTRIBUTE_HREF,
    HTML_ATTRIBUTE_ID,
    HTML_ATTRIBUTE_LABEL,
    HTML_ATTRIBUTE_LANG,
    HTML_ATTRIBUTE_LEVEL,
    HTML_ATTRIBUTE_LIST,
    HTML_ATTRIBUTE_LOOP,
    HTML_ATTRIBUTE_MAX,
    HTML_ATTRIBUTE_MAXLENGTH,
    HTML_ATTRIBUTE_MIN,
    HTML_ATTRIBUTE_MULTIPLE,
    HTML_ATTRIBUTE_MUTED,
    HTML_ATTRIBUTE_N,
    HTML_ATTRIBUTE_NAME,
    HTML_ATTRIBUTE_OSISID,
    HTML_ATTRIBUTE_OSISREF,
    HTML_ATTRIBUTE_PARSED,
    HTML_ATTRIBUTE_PASSAGE,
    HTML_ATTRIBUTE_PATTERN,
    HTML_ATTRIBUTE_PLACE,
    HTML_ATTRIBUTE_PLACEHOLDER,
    HTML_ATTRIBUTE_READONLY,
    HTML_ATTRIBUTE_REQUIRED,
    HTML_ATTRIBUTE_RESP,
    HTML_ATTRIBUTE_ROWS,
    HTML_ATTRIBUTE_ROWSPAN,
    HTML_ATTRIBUTE_SCHEME,
    HTML_ATTRIBUTE_SCOPED,
    HTML_ATTRIBUTE_SELECTED,
    HTML_ATTRIBUTE_SHAPE,
    HTML_ATTRIBUTE_SIZE,
    HTML_ATTRIBUTE_SPAN,
    HTML_ATTRIBUTE_SRC,
    HTML_ATTRIBUTE_START,
    HTML_ATTRIBUTE_STEP,
    HTML_ATTRIBUTE_STYLE,
    HTML_ATTRIBUTE_SUB,
    HTML_ATTRIBUTE_SUBJECT1,
    HTML_ATTRIBUTE_SUBJECT2,
    HTML_ATTRIBUTE_SUBJECT3,
    HTML_ATTRIBUTE_SUBJECT4,
    HTML_ATTRIBUTE_TARGET,
    HTML_ATTRIBUTE_TARGETEND,
    HTML_ATTRIBUTE_TITLE,
    HTML_ATTRIBUTE_TUNEID,
    HTML_ATTRIBUTE_TYPE,
    HTML_ATTRIBUTE_VALIGN,
    HTML_ATTRIBUTE_VALUE,
    HTML_ATTRIBUTE_VERSION,
    HTML_ATTRIBUTE_WIDTH,
    HTML_ATTRIBUTE_WRAP,
    N_HTML_ATTRIBUTES
};

enum MAP_TYPE
{
    MAP_TYPE_HTML, MAP_TYPE_REGIONAL, N_MAP_TYPE
};

enum HTML_2_TEXT_STATE_FLAGS
{
    LCH_BREAK = 1, LCH_SPACE, LCH_CHAR
};

enum ELEMENT_TYPES
{
    ELEMENT_TYPE_INLINE, ELEMENT_TYPE_BLOCK, ELEMENT_TYPE_BREAK, N_ELEMENT_TYPE
};

enum NODE_TYPES
{
    NODE_TYPE_INVALID, NODE_TYPE_BEGIN_TAG, NODE_TYPE_END_TAG, NODE_TYPE_UNPAIRED_TAG,
    NODE_TYPE_TEXT_RUN, NODE_TYPE_BINARY, NODE_TYPE_WHITE_SPACE
};

enum INTERNAL_PARSER_ID
{
    INT_UNKNOWN = 32000, INT_WHITE_SPACE, INT_TEXT_RUN, INT_BINARY, INT_MODULE
};

struct SwFont
{
    swUI8 family;
    float size;
    swUI8 unit;
    swUI8 style;
    swUI8 variant;
    swUI8 weight;

    void Reset()
    {
        family = 0;
        size = 0;
        unit = 0;
        style = 0;
        variant = 0;
        weight = 0;
    }
};

struct SwBoxAttr
{
    float left;
    swUI8 leftUnit;
    float right;
    swUI8 rightUnit;
    float top;
    swUI8 topUnit;
    float bottom;
    swUI8 bottomUnit;

    void Reset ()
    {
        left = 0;
        leftUnit = 0;
        right = 0;
        rightUnit = 0;
        top = 0;
        topUnit = 0;
        bottom = 0;
        bottomUnit = 0;
    }
};

struct SwElement
{
    const char *  name;
    swUI16        elementId;
    swUI8         elementType;
    swUI8         whiteSpace;
};

struct SwElementData
{
    const char *  name;
    swUI16        elementId;
    const char *  attributes;
};

class SOWERBASEEXP SwHtml
{
public:
    static swUI8 GetMethodType(const char * value);
    static swUI8 GetBorderCollapse(const char * value);
    static void GetBorderSpacing(const char * value, float & hspacing, swUI8 & hunit, float & vspacing, swUI8 & vunit);
    static void GetBorder(const char * value, float & borderWidth, swUI8 & borderUnit, swUI8 & borderStyle, swUI32 & borderColor);
    static swUI8 GetBorderValueType(const char * value);
    static swUI8 GetBorderStyle(const char * value);
    static swUI8 GetFloatDirection(const char * value);
    static swUI8 GetTextAlign(const char * value);
    static swUI8 GetVerticalAlign(const char * value);
    static const char * GetTextDecorationString(swUI8 textDecoration);
    static swUI16 GetTextDecoration(const char * value);
    static void TextDecoration(swUI8 & textDecoration, swUI8 decoration);
    static void TextDecorationRemove(swUI8 & textDecoration, swUI8 decoration);
    static bool TextDecorationHas(swUI8 textDecoration, swUI8 decoration);
    static swUI8 GetTextTransform(const char * value);
    static swUI8 GetFontVariant(const char * value);
    static swUI8 GetTextDirection(const char * value);
    static swUI8 GetFontWeight(const char * value);
    static swUI8 GetListStyle(const char * value);
    static void FormatListNumber(long value, swUI8 listType, SwString & buffer);
    static void GetFont(const char * value, SwFont & font);
    static swUI8 GetFontStyle(const char * value);
    static const char * GetFontFace(const char * value);
    static swUI8 GetFontFamily(const char * value);
    static swUI8 GetWhiteSpace(const char * value);
    static void GetMargins(const char * value, SwBoxAttr & box);
    static void GetPadding(const char * value, SwBoxAttr & box);
    static void GetBorderWidth(const char * value, float & width, swUI8 & unit);
    static void GetFontSize(const char * value, float & fontSize, swUI8 & fontUnit);
    static swUI8 GetMapType(const char * value);
    static swUI8 GetAreaType(const char * value);
    static const char * GetUnitString(swUI8 unit);
    static void GetFloatData(const char * value, float & data, swUI8 & unit);
    static swUI32 Html2Text(const char * source, char * dest, swUI32 bufferLen, swUI8 & lastChar, bool strip);
    static swUI32 Html2Text(swUI32 count, const char * source, char * dest, swUI32 bufferLen, swUI8 & lastChar, bool strip);
    static swUI8 GetScope(const char * value);
    static void ConvertRectangleFromHtml(SwPoint pointLeft, SwPoint & pointRight);
    static void ConvertRectangleToHtml(SwPoint pointLeft, SwPoint & pointRight);
    static swUI32 CalculatePointsNeededForCoords(swUI32 nCoords);
    static void GetVector(const char * value, float & x, float & y, float & z);
    static void GetBoxVector(const char * value, float & nx, float & fx, float & ny,  float & fy, float & nz, float & fz);
    static void GetDimension2d(const char * value, float & width, float & height);
    static void GetDimension2d(const char * value, swUI32 & width, swUI32 & height);
    static const char * GetInternalElementName(swUI16 id);
    static swUI32 ScanPastWhiteSpace(const char * source);
};

#endif // HTML_H
