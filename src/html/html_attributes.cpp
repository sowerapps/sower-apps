///////////////////////////////////////////////////////////////////
// Name:        html_attributes.cpp
// Purpose:     Identify HTML attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/html_attributes.h"
#include "../../include/html/html_color.h"
#include "../../include/css/css_attributes.h"
#include <stdlib.h>

struct HTML_ATTRIBUTE
{
    const char *  name;
    swUI8       id;
};

static const swI8 HtmlAttributesIndex[] =
{
    HTML_ATTRIBUTE_ACTION, HTML_ATTRIBUTE_BACKGROUND, HTML_ATTRIBUTE_CELLPADDING,
    HTML_ATTRIBUTE_DIR, -1, HTML_ATTRIBUTE_FACE, -1,
    HTML_ATTRIBUTE_HEIGHT, HTML_ATTRIBUTE_ID, -1, -1, HTML_ATTRIBUTE_LABEL,
    HTML_ATTRIBUTE_MAX, HTML_ATTRIBUTE_N, HTML_ATTRIBUTE_OSISID, HTML_ATTRIBUTE_PARSED, -1,
    HTML_ATTRIBUTE_READONLY, HTML_ATTRIBUTE_SCHEME, HTML_ATTRIBUTE_TARGET,
    -1, HTML_ATTRIBUTE_VALIGN, HTML_ATTRIBUTE_WIDTH, -1, -1, -1
};

static const HTML_ATTRIBUTE HtmlAttributesData[] =
{
    "unknown",          HTML_ATTRIBUTE_UNKNOWN,
    "action",           HTML_ATTRIBUTE_ACTION,
    "align",            HTML_ATTRIBUTE_ALIGN,
    "alt",              HTML_ATTRIBUTE_ALT,
    "anchored",         HTML_ATTRIBUTE_ANCHORED,             // -- thml
    "authorid",         HTML_ATTRIBUTE_AUTHORID,             // -- thml
    "autocomplete",     HTML_ATTRIBUTE_AUTOCOMPLETE,
    "background",       HTML_ATTRIBUTE_BACKGROUND,
    "bgcolor",          HTML_ATTRIBUTE_BGCOLOR,
    "border",           HTML_ATTRIBUTE_BORDER,
    "cellpadding",      HTML_ATTRIBUTE_CELLPADDING,
    "cellspacing",      HTML_ATTRIBUTE_CELLSPACING,
    "checked",          HTML_ATTRIBUTE_CHECKED,
    "cite",             HTML_ATTRIBUTE_CITE,
    "class",            HTML_ATTRIBUTE_CLASS,
    "code",             HTML_ATTRIBUTE_CODE,
    "color",            HTML_ATTRIBUTE_COLOR,
    "cols",             HTML_ATTRIBUTE_COLS,
    "colspan",          HTML_ATTRIBUTE_COLSPAN,
    "composerid",       HTML_ATTRIBUTE_COMPOSERID,           // -- thml
    "coords",           HTML_ATTRIBUTE_COORDS,
    "dir",              HTML_ATTRIBUTE_DIR,
    "face",             HTML_ATTRIBUTE_FACE,
    "filebreak",        HTML_ATTRIBUTE_FILEBREAK,            // -- thml
    "form",             HTML_ATTRIBUTE_FORM,
    "formaction",       HTML_ATTRIBUTE_FORMACTION,
    "formenctype",      HTML_ATTRIBUTE_FORMENCTYPE,
    "formmethod",       HTML_ATTRIBUTE_FORMMETHOD,
    "formnovalidate",   HTML_ATTRIBUTE_FORMNOVALIDATE,
    "formtarget",       HTML_ATTRIBUTE_FORMTARGET,
    "height",           HTML_ATTRIBUTE_HEIGHT,
    "href",             HTML_ATTRIBUTE_HREF,
    "id",               HTML_ATTRIBUTE_ID,                   // -- css
    "label",            HTML_ATTRIBUTE_LABEL,
    "lang",             HTML_ATTRIBUTE_LANG,                 // -- thml
    "level",            HTML_ATTRIBUTE_LEVEL,                // -- thml
    "list",             HTML_ATTRIBUTE_LIST,
    "loop",             HTML_ATTRIBUTE_LOOP,
    "max",              HTML_ATTRIBUTE_MAX,
    "maxlength",        HTML_ATTRIBUTE_MAXLENGTH,
    "min",              HTML_ATTRIBUTE_MIN,
    "multiple",         HTML_ATTRIBUTE_MULTIPLE,
    "muted",            HTML_ATTRIBUTE_MUTED,
    "n",                HTML_ATTRIBUTE_N,                    // -- thml
    "name",             HTML_ATTRIBUTE_NAME,
    "osisId",           HTML_ATTRIBUTE_OSISID,
    "osisRef",          HTML_ATTRIBUTE_OSISREF,
    "parsed",           HTML_ATTRIBUTE_PARSED,               // -- thml
    "passage",          HTML_ATTRIBUTE_PASSAGE,              // -- thml
    "pattern",          HTML_ATTRIBUTE_PATTERN,
    "place",            HTML_ATTRIBUTE_PLACE,                // -- thml
    "placeholder",      HTML_ATTRIBUTE_PLACEHOLDER,
    "readonly",         HTML_ATTRIBUTE_READONLY,
    "required",         HTML_ATTRIBUTE_REQUIRED,
    "resp",             HTML_ATTRIBUTE_RESP,                 // -- thml
    "rows",             HTML_ATTRIBUTE_ROWS,
    "rowspan",          HTML_ATTRIBUTE_ROWSPAN,
    "scheme",           HTML_ATTRIBUTE_SCHEME,               // -- thml
    "scoped",           HTML_ATTRIBUTE_SCOPED,
    "selected",         HTML_ATTRIBUTE_SELECTED,
    "shape",            HTML_ATTRIBUTE_SHAPE,
    "size",             HTML_ATTRIBUTE_SIZE,
    "span",             HTML_ATTRIBUTE_SPAN,
    "src",              HTML_ATTRIBUTE_SRC,
    "start",            HTML_ATTRIBUTE_START,
    "step",             HTML_ATTRIBUTE_STEP,
    "style",            HTML_ATTRIBUTE_STYLE,
    "sub",              HTML_ATTRIBUTE_SUB,                  // -- thml
    "subject1",         HTML_ATTRIBUTE_SUBJECT1,             // -- thml
    "subject2",         HTML_ATTRIBUTE_SUBJECT2,             // -- thml
    "subject3",         HTML_ATTRIBUTE_SUBJECT3,             // -- thml
    "subject4",         HTML_ATTRIBUTE_SUBJECT4,             // -- thml
    "target",           HTML_ATTRIBUTE_TARGET,               // -- thml
    "targetend",        HTML_ATTRIBUTE_TARGETEND,            // -- thml
    "title",            HTML_ATTRIBUTE_TITLE,
    "tuneid",           HTML_ATTRIBUTE_TUNEID,               // -- thml
    "type",             HTML_ATTRIBUTE_TYPE,
    "valign",           HTML_ATTRIBUTE_VALIGN,
    "value",            HTML_ATTRIBUTE_VALUE,
    "version",          HTML_ATTRIBUTE_VERSION,              // -- thml
    "width",            HTML_ATTRIBUTE_WIDTH,
    "wrap",             HTML_ATTRIBUTE_WRAP
};

swUI8 SwHtmlAttributes::IdentifyAttribute(const char * source)
{
    if (!source)
        return HTML_ATTRIBUTE_UNKNOWN;

    swI16 pos;
    char ch = tolower(*source);

    if (ch < 'a' || ch > 'z')
        return HTML_ATTRIBUTE_UNKNOWN;

    pos = HtmlAttributesIndex[ch - 'a'];

    if (pos < 0)
        return HTML_ATTRIBUTE_UNKNOWN;

    while (pos < N_HTML_ATTRIBUTES)
    {
        if (HtmlAttributesData[pos].name[0] > ch)
            return HTML_ATTRIBUTE_UNKNOWN;

        if (stricmp(HtmlAttributesData[pos].name, source) == 0)
            return HtmlAttributesData[pos].id;

        pos ++;
    }

    return HTML_ATTRIBUTE_UNKNOWN;
}

const char * SwHtmlAttributes::GetAttributeString(swUI8 property)
{
    if (property >= N_HTML_ATTRIBUTES)
        return "";

    return HtmlAttributesData[property].name;
}
