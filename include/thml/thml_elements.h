///////////////////////////////////////////////////////////////////
// Name:        thml_elements.cpp
// Purpose:     ThML element array for SwThMLParser.
//              Including HTML, ThML elements.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THML_ELEMENTS_H
#define THML_ELEMENTS_H

#include "../html/html.h"

// Any additions or deletions to this file
// must also be made to htmlcss.cpp
enum STANDARD_ELEMENTS
{
    THML_COMMENT, THML_DOCTYPE, THML_A, THML_ABBR,
    THML_ACRONYM, THML_ADDED, THML_ADDRESS, THML_APPLET,
    THML_AREA, THML_ARGUMENT, THML_ARTICLE, THML_ASIDE,
    THML_ATTLIST, THML_ATTR, THML_AUDIO, THML_AUTHOR, THML_AUTHORID, THML_AUTODEF_BODY,
    THML_B, THML_BASE, THML_BASEFONT, THML_BDI, THML_BDO, THML_BIG,
    THML_BLOCKQUOTE, THML_BODY, THML_BOOKID, THML_BR, THML_BUTTON,
    THML_CANVAS, THML_CAPTION, THML_CDATA, THML_CENTER, THML_CHRIST, THML_CITATION,
    THML_CITE, THML_CODE, THML_COL, THML_COLGROUP,
    THML_COMMAND, THML_COMMENTS, THML_COMPOSER, THML_COPYLOCATION,
    THML_DATALIST, THML_DATE, THML_DC, THML_DC_CONTRIBUTOR, THML_DC_COVERAGE,
    THML_DC_CREATOR, THML_DC_DATE, THML_DC_DESCRIPTION, THML_DC_FORMAT,
    THML_DC_IDENTIFIER, THML_DC_LANGUAGE, THML_DC_PUBLISHER, THML_DC_RELATION,
    THML_DC_RIGHTS, THML_DC_SOURCE, THML_DC_SUBJECT, THML_DC_TITLE, THML_DC_TYPE,
    THML_DD, THML_DEF, THML_DEL, THML_DELETED, THML_DESCRIPTION,
    THML_DETAILS, THML_DFN, THML_DIALOG, THML_DIR,
    THML_DIV, THML_DIV1, THML_DIV2, THML_DIV3, THML_DIV4, THML_DIV5, THML_DIV6,
    THML_DL, THML_DT, THML_EDITORIALCOMMENTS, THML_ELECTRONICEDINFO, THML_ELEMENT,
    THML_EM, THML_EMBED, THML_ENTITY, THML_FIELDSET, THML_FIGCAPTION, THML_FIGURE,
    THML_FILE, THML_FIRSTPUBLISHED, THML_FONT, THML_FOOTER, THML_FOREIGN, THML_FORM,
    THML_FRAME, THML_FRAMESET, THML_GENERALINFO, THML_GLOSSARY, THML_GLOSSARY_ITEM,
    THML_HEAD, THML_HEADER, THML_HR, THML_HTML, THML_HYMN,
    THML_H1, THML_H2, THML_H3, THML_H4, THML_H5, THML_H6,
    THML_I, THML_IFRAME, THML_IMAGE, THML_IMG, THML_INCIPIT, THML_INDEX,
    THML_INPUT, THML_INS, THML_INSERTINDEX, THML_INTERFACE, THML_KBD, THML_KEYGEN,
    THML_L, THML_LABEL, THML_LEGEND, THML_LI, THML_LINK, THML_MAP, THML_MARK,
    THML_MENU, THML_META, THML_METER, THML_MODULE, THML_MUSIC, THML_NAME, THML_NAV, THML_NOFRAMES,
    THML_NOSCRIPT, THML_NOTE, THML_OBJECT, THML_OL, THML_OPTGROUP,
    THML_OPTION, THML_OUTPUT, THML_P, THML_PARAM, THML_PB,
    THML_PRE, THML_PRINTSOURCEINFO, THML_PROGRESS, THML_PROPERTY,
    THML_PUBHISTORY, THML_PUBLISHED, THML_PUBLISHERID, THML_Q,
    THML_REVISIONHISTORY, THML_RP, THML_RT, THML_RUBY, THML_S,
    THML_SAMP, THML_SCRIPCOM, THML_SCRIPCONTEXT, THML_SCRIPREF, THML_SCRIPT,
    THML_SCRIPTURE, THML_SECTION, THML_SELECT, THML_SELECTOR, THML_SERIES, THML_SMALL,
    THML_SOURCE, THML_SPAN, THML_STATUS, THML_STRIKE, THML_STRONG,
    THML_STYLE, THML_SUB, THML_SUMMARY, THML_SUP, THML_SYNC,
    THML_TABLE, THML_TBODY, THML_TD, THML_TERM, THML_TERM_STRONGS, THML_TEXTAREA,
    THML_TFOOT, THML_TH, THML_THEAD, THML_THML, THML_THML_BODY, THML_THML_HEAD,
    THML_TIME, THML_TITLE, THML_TR, THML_TRACK, THML_TT, THML_TUNE,
    THML_U, THML_UL, THML_UNCLEAR, THML_VAR, THML_VERSE, THML_VERSION,
    THML_VIDEO, THML_WBR, THML_XML, THML_XML_STYLESHEET,
    N_THML_ELEMENTS
};

#endif // THML_ELEMENTS_H
