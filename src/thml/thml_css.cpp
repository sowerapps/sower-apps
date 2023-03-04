///////////////////////////////////////////////////////////////////
// Name:       thml_css.cpp
// Purpose:    Standard CSS to be applied to a ThML file.
//             From ThML 1.04 CSS.
// Copyright:  David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thml_css.h"
#include "../../include/thml/thml_elements.h"

struct THML_CSS_ELEMENT_CONST
{
    swUI16 m_element;
    const char * m_attribute1;
    const char * m_value1;
    const char * m_attribute2;
    const char * m_value2;
    const char * m_attribute3;
    const char * m_value3;
    const char * m_attribute4;
    const char * m_value4;
    const char * m_attribute5;
    const char * m_value5;
    const char * m_attribute6;
    const char * m_value6;
    const char * m_attribute7;
    const char * m_value7;
    const char * m_attribute8;
    const char * m_value8;
};

// This array must have all of the elements in ThMLElements
// array, and be in the precise order or it will not provide
// the correct style data.
static THML_CSS_ELEMENT_CONST thmlelementCss [N_THML_ELEMENTS] =
{
    {THML_COMMENT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DOCTYPE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_A, "text-decoration", "underline", "color", "blue", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ABBR,  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ACRONYM, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ADDED, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ADDRESS, "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_APPLET, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_AREA, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ARGUMENT, "text-align", "center", "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ARTICLE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ASIDE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ATTLIST, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ATTR, "text-align", "right", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_AUDIO, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_AUTHOR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_AUTHORID, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_AUTODEF_BODY, "font-family", "Times", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_B, "font-weight", "bolder", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BASE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BASEFONT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BDI, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BDO, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BIG, "font-size", "1.31em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BLOCKQUOTE, "margin-left", "0.5in", "margin-right", "0.5in", "margin-top", "12pt", "margin-bottom", "12pt", "", "", "", "", "", "", "", ""},
    {THML_BODY, "margin", "8px", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BOOKID, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_BUTTON, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CANVAS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CAPTION, "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CDATA, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CENTER, "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CHRIST, "color", "red", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CITATION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CITE, "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_CODE, "font-family", "monospace", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_COL, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_COLGROUP, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_COMMAND, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_COMMENTS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_COMPOSER, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_COPYLOCATION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DATALIST, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DATE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_CONTRIBUTOR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_COVERAGE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_CREATOR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_DATE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_DESCRIPTION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_FORMAT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_IDENTIFIER, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_LANGUAGE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_PUBLISHER, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_RELATION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_RIGHTS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_SOURCE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_SUBJECT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_TITLE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DC_TYPE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DD, "margin-left", "40px", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DEF, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DEL, "text-decoration", "line-through", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DELETED, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DESCRIPTION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DETAILS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DFN, "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIALOG, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIR, "margin-left", "40px", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV1, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV2, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV3, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV4, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV5, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DIV6, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DL, "margin", "1.12em 0", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_DT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_EDITORIALCOMMENTS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ELECTRONICEDINFO, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ELEMENT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_EM, "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_EMBED, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_ENTITY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FIELDSET, "margin", "1.12em 0", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FIGCAPTION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FIGURE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FILE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FIRSTPUBLISHED, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FONT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FOOTER, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FOREIGN, "color", "#003300", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FORM, "margin", "1.12em 0", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FRAME, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_FRAMESET, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_GENERALINFO, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_GLOSSARY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_GLOSSARY_ITEM, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_HEAD, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_HEADER, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_HR, "text-align", "center", "width", "100%", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_HTML, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_HYMN, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_H1, "text-align", "center", "font-weight", "bold", "font-size", "150%", "margin-top", "18pt", "", "", "", "", "", "", "", ""},
    {THML_H2, "text-align", "center", "font-weight", "bold", "font-size", "125%", "margin-top", "12pt", "", "", "", "", "", "", "", ""},
    {THML_H3, "text-align", "center", "font-weight", "bold", "font-size", "100%", "margin-top", "9pt", "", "", "", "", "", "", "", ""},
    {THML_H4, "text-align", "center", "font-weight", "bold", "font-size", "75%", "margin-top", "6pt", "", "", "", "", "", "", "", ""},
    {THML_H5, "font-weight", "normal", "font-style", "italic", "text-align", "left", "margin-top", "6pt", "", "", "", "", "", "", "", ""},
    {THML_H6, "font-weight", "normal", "font-style", "italic", "text-align", "left", "margin-top", "6pt", "", "", "", "", "", "", "", ""},
    {THML_I, "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_IFRAME, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_IMAGE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_IMG, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_INCIPIT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_INDEX, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_INPUT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_INS, "text-decoration", "underline", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_INSERTINDEX, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_INTERFACE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_KBD, "font-family", "monospace", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_KEYGEN, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_L, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_LABEL, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_LEGEND, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_LI, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_LINK, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_MAP, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_MARK, "background-color", "yellow", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_MENU, "margin-left", "40px", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_META, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_METER, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_MODULE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_MUSIC, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_NAME, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_NAV, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_NOFRAMES, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_NOSCRIPT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_NOTE, "font-size", "88%", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_OBJECT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_OL, "margin-left", "40px", "list-style-type", "decimal", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_OPTGROUP, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_OPTION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_OUTPUT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_P, "text-indent", "0.25in", "margin-top", "0pt", "margin-bottom", "0pt", "", "", "", "", "", "", "", "", "", ""},
    {THML_PARAM, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PB, "position", "absolute", "left", "0.1in", "padding-left", "1pt", "text-indent", "0in", "font-family", "sans-serif", "font-size", "8pt", "background-color", "#660000", "color", "#FFFFFF"},
    {THML_PRE, "font-family", "monospace", "white-space", "pre", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PRINTSOURCEINFO, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PROGRESS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PROPERTY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PUBHISTORY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PUBLISHED, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_PUBLISHERID, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_Q, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_REVISIONHISTORY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_RP, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_RT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_RUBY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_S, "text-decoration", "line-through", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SAMP, "font-family", "monospace", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SCRIPCOM, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SCRIPCONTEXT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SCRIPREF, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SCRIPT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SCRIPTURE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SECTION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SELECT, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SELECTOR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SERIES, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SMALL, "font-size", ".83em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SOURCE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SPAN, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_STATUS, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_STRIKE, "text-decoration", "line-through", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_STRONG, "font-weight", "bolder", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_STYLE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SUB, "font-size", ".90em", "vertical-align", "sub", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SUMMARY, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SUP, "font-size", ".90em", "vertical-align", "super", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_SYNC, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TABLE, "border-spacing", "2px", "border-width", "1px", "border-style", "solid", "", "", "", "", "", "", "", "", "", ""},
    {THML_TBODY, "vertical-align", "middle", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TD, "vertical-align", "inherit", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TERM, "font-weight", "bold", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TERM_STRONGS, "font-weight", "bold", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TEXTAREA, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TFOOT, "vertical-align", "middle", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TH, "font-weight", "bolder", "text-align", "center", "vertical-align", "inherit", "", "", "", "", "", "", "", "", "", ""},
    {THML_THEAD, "vertical-align", "middle", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_THML, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_THML_BODY, "margin-left", "0.65in", "margin-right", "0.65in", "margin-top", "0pt", "margin-bottom", "0pt", "font-family", "Times", "", "", "", "", "", ""},
    {THML_THML_HEAD, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TIME, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TITLE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TRACK, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TT, "font-family", "monospace", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_TUNE, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_U, "text-decoration", "underline", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_UL, "margin-left", "40px", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_UNCLEAR, "color", "#808080", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_VAR, "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_VERSE, "text-indent", "0.25in", "margin-top", "0pt", "margin-bottom", "0pt", "", "", "", "", "", "", "", "", "", ""},
    {THML_VERSION, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_VIDEO, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_WBR, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_XML, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {THML_XML_STYLESHEET, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}
};

void SwThMLCss::GetElementStyle(swUI16 element, CssAttributeList & styleList)
{
    if (element >= N_THML_ELEMENTS)
        return;

    if (thmlelementCss[element].m_attribute1[0] != '\0' && thmlelementCss[element].m_value1[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute1, thmlelementCss[element].m_value1, 1);
    }

    if (thmlelementCss[element].m_attribute2[0] != '\0' && thmlelementCss[element].m_value2[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute2, thmlelementCss[element].m_value2, 1);
    }

    if (thmlelementCss[element].m_attribute3[0] != '\0' && thmlelementCss[element].m_value3[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute3, thmlelementCss[element].m_value3, 1);
    }

    if (thmlelementCss[element].m_attribute4[0] != '\0' && thmlelementCss[element].m_value4[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute4, thmlelementCss[element].m_value4, 1);
    }

    if (thmlelementCss[element].m_attribute5[0] != '\0' && thmlelementCss[element].m_value5[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute5, thmlelementCss[element].m_value5, 1);
    }

    if (thmlelementCss[element].m_attribute6[0] != '\0' && thmlelementCss[element].m_value6[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute6, thmlelementCss[element].m_value6, 1);
    }

    if (thmlelementCss[element].m_attribute7[0] != '\0' && thmlelementCss[element].m_value7[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute7, thmlelementCss[element].m_value7, 1);
    }

    if (thmlelementCss[element].m_attribute8[0] != '\0' && thmlelementCss[element].m_value8[0] != '\0')
    {
        styleList.Add(thmlelementCss[element].m_attribute8, thmlelementCss[element].m_value8, 1);
    }
}

static swUI32 m_thmlcssItems = 0;

struct THML_CSS_CONST
{
    swUI16 m_specificity;
    swUI8  m_opcode;
    swUI16 m_selelement;
    swUI16 m_element;
    swUI16 m_scope;
    const char * m_class;
    const char * m_attribute1;
    const char * m_value1;
    const char * m_attribute2;
    const char * m_value2;
    const char * m_attribute3;
    const char * m_value3;
    const char * m_attribute4;
    const char * m_value4;
    const char * m_attribute5;
    const char * m_value5;
    const char * m_attribute6;
    const char * m_value6;
    const char * m_attribute7;
    const char * m_value7;
    const char * m_attribute8;
    const char * m_value8;
    const char * m_attribute9;
    const char * m_value9;
};

static THML_CSS_CONST thmlCss [] =
{
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "blockquote", "margin-left", "0.5in", "margin-right", "0.5in", "text-indent", "0in", "margin-top", "12pt", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "sc", "font-variant", "small-caps", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "Continue", "text-indent", "0in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "ChapterSummary", "text-align", "center", "font-style", "italic", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "Attribution", "text-align", "right", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "meter", "text-align", "right", "margin-top", "-12pt", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "SectionInfo", "margin-left", "1.0in", "text-indent", "-0.5in", "margin-right", "0.5in", "font-style", "italic", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "footnote", "text-indent", "0.25in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "endnote", "text-indent", "0.25in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "pagebreak", "page-break-before", "always", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_SUP, 0, "Note", "font-size", "75%", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_SUP, 0, "NoteRef", "font-size", "85%", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "noteMark", "text-indent", "0in", "margin-bottom", "-12pt", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List1", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "0.5in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List2", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "0.75in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List3", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "1.0in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List4", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "1.25in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List5", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "1.5in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List6", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "1.75in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "List7", "text-indent", "-0.25in", "margin-right", "0.25in", "margin-left", "2.0in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "ListCont1", "text-indent", "0in", "margin-right", "0.5in", "margin-left", "0.5in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "ListCont2", "text-indent", "0in", "margin-right", "0.5in", "margin-left", "0.75in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "ListCont3", "text-indent", "0in", "margin-right", "0.5in", "margin-left", "1.0in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "ListCont4", "text-indent", "0in", "margin-right", "0.5in", "margin-left", "1.25in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "ListCont5", "text-indent", "0in", "margin-right", "0.5in", "margin-left", "1.5in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "ListCont6", "text-indent", "0in", "margin-right", "0.5in", "margin-left", "1.75in", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_LI, 0, "wwec", "margin-left", "16pt", "text-indent", "-16pt", "font-face", "Arial", "font-size", "10pt", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_DIV, 0, "verse", "margin-top", "12pt", "margin-left", "1.25in", "margin-right", "0.5in", "border-top-width", "24pt", "borderColor", "#FFE0B0", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t0", "margin-left", "5em", "text-indent", "-5em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t1", "margin-left", "5em", "text-indent", "-4em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t", "margin-left", "5em", "text-indent", "-4em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t2", "margin-left", "5em", "text-indent", "-3em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t3", "margin-left", "5em", "text-indent", "-2em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t4", "margin-left", "5em", "text-indent", "-1em", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "t5", "margin-left", "5em", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_A, 0, "TOC", "text-decoration", "none", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_A, 0, "Note", "text-decoration", "none", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_A, 0, "scripRef", "text-decoration", "none", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "TOC1", "text-indent", "-0.3in", "text-align", "left", "margin-left", "0.3in", "font-weight", "bold", "font-size", "110%", "margin-top", "4pt", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "TOC2", "text-indent", "-0.3in", "text-align", "left", "margin-left", "0.6in", "font-size", "100%", "margin-top", "3pt", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "TOC3", "text-indent", "-0.3in", "text-align", "left", "margin-left", "0.9in", "font-size", "90%", "margin-top", "2pt", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "TOC4", "text-indent", "-0.3in", "text-align", "left", "margin-left", "1.2in", "font-size", "90%", "margin-top", "1pt", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "TOC5", "text-indent", "-0.3in", "text-align", "left", "margin-left", "1.5in", "font-size", "90%", "margin-top", "0pt", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "TOC6", "text-indent", "-0.3in", "text-align", "left", "margin-left", "1.8in", "font-size", "90%", "margin-top", "0pt", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "editbox", "font-family", "sans-serif", "font-size", "10pt", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {12, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "Center", "text-indent", "0in", "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {12, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "Centered", "text-indent", "0in", "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {12, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "Center", "text-indent", "0in", "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {12, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "Centered", "text-indent", "0in", "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "left", "text-align", "left", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_UL, 0, "Index1", "font-weight", "bold", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_UL, 0, "Index2", "font-weight", "normal", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "index1", "text-indent", "-2em", "margin-top", "0in", "margin-left", "2em", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "index2", "text-indent", "-2em", "margin-top", "0in", "margin-left", "3em", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "index3", "text-indent", "-2em", "margin-top", "0in", "margin-left", "4em", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "index4", "text-indent", "-2em", "margin-top", "0in", "margin-left", "5em", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "bbook", "font-weight", "bold", "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "bref", "text-align", "center", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "by", "text-align", "center", "font-size", "100%", "margin-top", "12pt", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "hl", "background-color", "yellow", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "whitehead", "font-family", "sans-serif", "font-size", "83%", "color", "#FFFFFF", "font-weight", "bold", "margin-top", "0pt", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_TABLE, 0, "marg", "position", "absolute", "left", "0.1in", "padding-left", "1pt", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "thin", "font-size", "1pt", "margin-top", "0pt", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "page", "text-indent", "0in", "font-family", "sans-serif", "font-size", "8pt", "color", "#FFFFFF", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "chap", "position", "absolute", "margin-left", "-0.3in", "float", "left", "font-size", "200% ", "display", "none", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_SPAN, 0, "Note", "color", "blue", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_HR, 0, "W30", "width", "30%", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_HR, 0, "Note", "text-align", "left", "width", "30%", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_IMG, 0, "page", "margin-left", "-0.5in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "bib", "margin-left", "0.5in", "text-indent", "-0.25in", "font-size", "10p", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "mnote", "display", "inline", "clear", "right", "font-size", "smaller", "float", "right", "margin-top", "0pt", "background-color", "#FFFFB0", "padding", "6pt", "width", "33%", "text-indent", "0in"},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "argument", "text-align", "center", "font-style", "italic", "text-indent", "0in", "margin-bottom", "12pt", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "Greek", "font-family", "Times New Roman", "font-size", "111%", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "Hebrew", "font-family", "Times New Roman", "font-size", "111%", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {10, CSS_OP_NONE, INT_UNKNOWN, INT_UNKNOWN, 0, "meter", "text-align", "right", "margin-top", "-12pt", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "First", "text-indent", "0.0in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {21, CSS_OP_NONE, INT_UNKNOWN, THML_P, CSS_SCOPE_FIRST_LETTER, "First", "font-size", "270%", "float", "left", "margin-top", "-10px", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "dropcap", "text-indent", "0in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {21, CSS_OP_NONE, INT_UNKNOWN, THML_P, CSS_SCOPE_FIRST_LETTER, "dropcap", "font-size", "200%", "float", "left", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {11, CSS_OP_NONE, INT_UNKNOWN, THML_P, 0, "smallcap", "text-indent", "0.0in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {21, CSS_OP_NONE, INT_UNKNOWN, THML_P, CSS_SCOPE_FIRST_LETTER, "smallcap", "font-variant", "small-caps", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {21, CSS_OP_NONE, INT_UNKNOWN, THML_P, CSS_SCOPE_FIRST_WORD, "smallcap", "font-size", "200%", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    {12, CSS_OP_SPACE, THML_TD, THML_P, 0, "", "text-indent", "0in", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""},
    // Used as unique identifer to mark end of array.
    // not actual number of elements in array.
    {0, CSS_OP_NONE, INT_UNKNOWN, N_THML_ELEMENTS, 0, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}
};

void SwThMLCss::Init()
{
    if (m_thmlcssItems > 0)
        return;

    for (;;)
    {
        if (thmlCss[m_thmlcssItems].m_element == N_THML_ELEMENTS)
            break;

        m_thmlcssItems ++;
    }
}

swUI32 SwThMLCss::Find(const char * classname, swUI32 start)
{
    if (!classname)
        return NODE_ID_INVALID;

    Init();

    swUI32 idx = start;

    while (idx < m_thmlcssItems)
    {
        if (strcmp(classname, thmlCss[idx].m_class) == 0)
            return idx;

        idx ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLCss::Find(swUI16 elementId, swUI32 start)
{
    Init();

    for (swUI32 i = start; i < m_thmlcssItems; i ++)
    {
        if (thmlCss[i].m_element == elementId)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLCss::Find(swUI16 elementId, const char * classname, swUI32 start)
{
    if (!classname)
        return NODE_ID_INVALID;

    Init();

    for (swUI32 i = start; i < m_thmlcssItems; i ++)
    {
        if ((thmlCss[i].m_element == INT_UNKNOWN || thmlCss[i].m_element == elementId) &&
                strcmp(classname, thmlCss[i].m_class) == 0)
           {
               return i;
           }
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLCss::Find(SwThMLParser & parser, swUI32 node, const char * name, swUI32 start)
{
    if (!name)
        return NODE_ID_INVALID;

    Init();

    swUI16 elementId = parser.GetNodeElementIdentifier(node);

    for (swUI32 i = start; i < m_thmlcssItems; i ++)
    {
        bool nameMatch = true;
        if (strcmp(thmlCss[i].m_class, name) != 0)
            nameMatch = false;
        if (thmlCss[i].m_element == INT_UNKNOWN)
        {
            if (!nameMatch)
                continue;
        }
        else if (thmlCss[i].m_element != elementId)
        {
            continue;
        }
        else if (thmlCss[i].m_class[0] != '\0')
        {
            if (!nameMatch)
                continue;
        }

        if (thmlCss[i].m_selelement != INT_UNKNOWN)
        {
            if (thmlCss[i].m_opcode == CSS_OP_SPACE && parser.IsWithIn(node, thmlCss[i].m_selelement))
                return i;
            else if (thmlCss[i].m_opcode == CSS_OP_GT && parser.IsChildOf(node, thmlCss[i].m_selelement))
                return i;
            else if (thmlCss[i].m_opcode == CSS_OP_PLUS && parser.IsNext(node, thmlCss[i].m_selelement))
                return i;
            else if (thmlCss[i].m_opcode == CSS_OP_TILDE && parser.IsPreceededBy(node, thmlCss[i].m_selelement))
                return i;
        }
        else
        {
            return i;
        }
    }

    return NODE_ID_INVALID;
}

swUI16 SwThMLCss::GetSpecificity(swUI32 pos)
{
    if (pos >= m_thmlcssItems)
        return 0;

    return thmlCss[pos].m_specificity;
}

swUI16 SwThMLCss::GetScope(swUI32 pos)
{
    if (pos >= m_thmlcssItems)
        return 0;

    return thmlCss[pos].m_scope;
}

swUI16 SwThMLCss::GetItems()
{
    Init();
    return m_thmlcssItems;
}

void SwThMLCss::GetStyle(swUI8 style, CssAttributeList & styleList)
{
    if (style >= N_THML_ELEMENTS)
        return;

    if (thmlCss[style].m_attribute1[0] != '\0' && thmlCss[style].m_value1[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute1, thmlCss[style].m_value1, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute2[0] != '\0' && thmlCss[style].m_value2[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute2, thmlCss[style].m_value2, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute3[0] != '\0' && thmlCss[style].m_value3[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute3, thmlCss[style].m_value3, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute4[0] != '\0' && thmlCss[style].m_value4[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute4, thmlCss[style].m_value4, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute5[0] != '\0' && thmlCss[style].m_value5[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute5, thmlCss[style].m_value5, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute6[0] != '\0' && thmlCss[style].m_value6[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute6, thmlCss[style].m_value6, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute7[0] != '\0' && thmlCss[style].m_value7[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute7, thmlCss[style].m_value7, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute8[0] != '\0' && thmlCss[style].m_value8[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute8, thmlCss[style].m_value8, thmlCss[style].m_specificity + 100);
    }

    if (thmlCss[style].m_attribute9[0] != '\0' && thmlCss[style].m_value9[0] != '\0')
    {
        styleList.Add(thmlCss[style].m_attribute9, thmlCss[style].m_value9, thmlCss[style].m_specificity + 100);
    }
}
