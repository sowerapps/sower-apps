///////////////////////////////////////////////////////////////////
// Name:        thml_elements.h
// Purpose:     ThML element array for SwThMLParser.
//              Including HTML, ThML elements.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thml_elements.h"
#include "../../include/thml/thml_parser.h"

swI16 ThMLElementIdx[26] =
{
    THML_A, THML_B, THML_CANVAS, THML_DATALIST, THML_EDITORIALCOMMENTS, THML_FIELDSET,
    THML_GENERALINFO, THML_HEAD, THML_I, -1, THML_KBD, THML_L, THML_MAP, THML_NAME,
    THML_OBJECT, THML_P, THML_Q, THML_REVISIONHISTORY, THML_S, THML_TABLE, THML_U,
    THML_VAR, THML_WBR, THML_XML, -1, -1
};

SwElement ThMLElements[N_THML_ELEMENTS] =
{
    {"!", THML_COMMENT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"!DOCTYPE", THML_DOCTYPE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"a", THML_A, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"abbr", THML_ABBR, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"acronym", THML_ACRONYM, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"added", THML_ADDED, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"address", THML_ADDRESS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"applet", THML_APPLET, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"area", THML_AREA, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"argument", THML_ARGUMENT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"article", THML_ARTICLE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"aside", THML_ASIDE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"attlist", THML_ATTLIST, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"attr", THML_ATTR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"audio", THML_AUDIO, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"author", THML_AUTHOR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"authorid", THML_AUTHORID, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"autodef.body", THML_AUTODEF_BODY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"b", THML_B, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"base", THML_BASE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"basefont", THML_BASEFONT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"bdi", THML_BDI, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"bdo", THML_BDO, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"big", THML_BIG, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"blockquote", THML_BLOCKQUOTE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"body", THML_BODY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"bookid", THML_BOOKID, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"br", THML_BR, ELEMENT_TYPE_BREAK, WHITE_SPACE_NORMAL},
    {"button", THML_BUTTON, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"canvas", THML_CANVAS, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"caption", THML_CAPTION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"cdata", THML_CDATA, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"center", THML_CENTER, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"christ", THML_CHRIST, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"citation", THML_CITATION, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"cite", THML_CITE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"code", THML_CODE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_PRE},
    {"col", THML_COL, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"colgroup", THML_COLGROUP, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"command", THML_COMMAND, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"comments", THML_COMMENTS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"composer", THML_COMPOSER, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"copylocation", THML_COPYLOCATION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"datalist", THML_DATALIST, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"date", THML_DATE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc", THML_DC, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.contributor", THML_DC_CONTRIBUTOR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.coverage", THML_DC_COVERAGE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.creator", THML_DC_CREATOR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.date", THML_DC_DATE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.description", THML_DC_DESCRIPTION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.format", THML_DC_FORMAT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.identifier", THML_DC_IDENTIFIER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.language", THML_DC_LANGUAGE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.publisher", THML_DC_PUBLISHER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.relation", THML_DC_RELATION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.rights", THML_DC_RIGHTS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.source", THML_DC_SOURCE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.subject", THML_DC_SUBJECT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.title", THML_DC_TITLE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc.type", THML_DC_TYPE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dd", THML_DD, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"def", THML_DEF, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"del", THML_DEL, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"deleted", THML_DELETED, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"description", THML_DESCRIPTION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"details", THML_DETAILS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dfn", THML_DFN, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"dialog", THML_DIALOG, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"dir", THML_DIR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div", THML_DIV, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div1", THML_DIV1, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div2", THML_DIV2, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div3", THML_DIV3, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div4", THML_DIV4, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div5", THML_DIV5, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"div6", THML_DIV6, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dl", THML_DL, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dt", THML_DT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"editorialcomments", THML_EDITORIALCOMMENTS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"electronicedinfo", THML_ELECTRONICEDINFO, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"element", THML_ELEMENT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"em", THML_EM, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"embed", THML_EMBED, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"entity", THML_ENTITY, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"fieldset", THML_FIELDSET, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"figcaption", THML_FIGCAPTION, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"figure", THML_FIGURE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"file", THML_FILE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"firstpublished", THML_FIRSTPUBLISHED, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"font", THML_FONT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"footer", THML_FOOTER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"foreign", THML_FOREIGN, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"form", THML_FORM, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"frame", THML_FRAME, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"frameset", THML_FRAMESET, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"generalinfo", THML_GENERALINFO, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"glossary", THML_GLOSSARY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"glossary.item", THML_GLOSSARY_ITEM, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"head", THML_HEAD, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"header", THML_HEADER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"hr", THML_HR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"html", THML_HTML, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"hymn", THML_HYMN, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"h1", THML_H1, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"h2", THML_H2, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"h3", THML_H3, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"h4", THML_H4, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"h5", THML_H5, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"h6", THML_H6, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"i", THML_I, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"iframe", THML_IFRAME, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"image", THML_IMAGE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"img", THML_IMG, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"incipit", THML_INCIPIT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"index", THML_INDEX, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"input", THML_INPUT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"ins", THML_INS, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"insertindex", THML_INSERTINDEX, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"interface", THML_INTERFACE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"kbd", THML_KBD, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"keygen", THML_KEYGEN, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"l", THML_L, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"label", THML_LABEL, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"legend", THML_LEGEND, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"li", THML_LI, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"link", THML_LINK, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"map", THML_MAP, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"mark", THML_MARK, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"menu", THML_MENU, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"meta", THML_META, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"meter", THML_METER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"module", THML_MODULE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"music", THML_MUSIC, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"name", THML_NAME, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"nav", THML_NAV, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"noframes", THML_NOFRAMES, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"noscript", THML_NOSCRIPT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"note", THML_NOTE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"object", THML_OBJECT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"ol", THML_OL, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"optgroup", THML_OPTGROUP, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"option", THML_OPTION, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"output", THML_OUTPUT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"p", THML_P, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"param", THML_PARAM, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"pb", THML_PB, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"pre", THML_PRE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"printsourceinfo", THML_PRINTSOURCEINFO, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"progress", THML_PROGRESS, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"property", THML_PROPERTY, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"pubhistory", THML_PUBHISTORY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"published", THML_PUBLISHED, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"publisherid", THML_PUBLISHERID, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"q", THML_Q, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"revisionhistory", THML_REVISIONHISTORY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"rp", THML_RP, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"rt", THML_RT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"ruby", THML_RUBY, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"s", THML_S, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"samp", THML_SAMP, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"scripCom", THML_SCRIPCOM, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"scripContext", THML_SCRIPCONTEXT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"scripRef", THML_SCRIPREF, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"script", THML_SCRIPT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"scripture", THML_SCRIPTURE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"section", THML_SECTION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"select", THML_SELECT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"selector", THML_SELECTOR, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"series", THML_SERIES, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"small", THML_SMALL, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"source", THML_SOURCE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"span", THML_SPAN, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"status", THML_STATUS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"strike", THML_STRIKE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"strong", THML_STRONG, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"style", THML_STYLE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"sub", THML_SUB, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"summary", THML_SUMMARY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"sup", THML_SUP, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"sync", THML_SYNC, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"table", THML_TABLE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"tbody", THML_TBODY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"td", THML_TD, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"term", THML_TERM, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"term.strongs", THML_TERM_STRONGS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"textarea", THML_TEXTAREA, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"tfoot", THML_TFOOT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"th", THML_TH, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"thead", THML_THEAD, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"thml", THML_THML, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"thml.body", THML_THML_BODY, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"thml.head", THML_THML_HEAD, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"time", THML_TIME, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"title", THML_TITLE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"tr", THML_TR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"track", THML_TRACK, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"tt", THML_TT, ELEMENT_TYPE_INLINE, WHITE_SPACE_PRE},
    {"tune", THML_TUNE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"u", THML_U, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"ul", THML_UL, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"unclear", THML_UNCLEAR, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"var", THML_VAR, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"verse", THML_VERSE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"version", THML_VERSION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"video", THML_VIDEO, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"wbr", THML_WBR, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"xml", THML_XML, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"xml-stylesheet", THML_XML_STYLESHEET, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL}
};

bool SwThMLParser::SetThML_ElementArray()
{
    m_elementArray = ThMLElements;
    m_elementAlphaIdx = ThMLElementIdx;
    m_elementItems = N_THML_ELEMENTS;
    m_markupType = MARKUP_THML;
    return true;
}

SwElementData ThMLElementData[] =
{
    {"added", THML_ADDED, "reason=\"\" resp=\"\" date=\"\""},
    {"argument", THML_ARGUMENT, ""},
    {"attr", THML_ATTR, ""},
    {"author", THML_AUTHOR, "authorID=\"\" composerID=\"\" type=\"\""},
    {"authorid", THML_AUTHORID, ""},
    {"bookid", THML_BOOKID, ""},
    {"citation", THML_CITATION, "title=\"\" href=\"\""},
    {"comments", THML_COMMENTS, ""},
    {"composer", THML_COMPOSER, "authorID=\"\" composerID=\"\" type=\"\""},
    {"copyLocation", THML_COPYLOCATION, ""},
    {"date", THML_DATE, "value=\"\""},
    {"DC", THML_DC, ""},
    {"DC.Contributor", THML_DC_CONTRIBUTOR, "scheme=\"\""},
    {"DC.Coverage", THML_DC_COVERAGE, ""},
    {"DC.Creator", THML_DC_CREATOR, ""},
    {"DC.Date", THML_DC_DATE, ""},
    {"DC.Description", THML_DC_DESCRIPTION, ""},
    {"DC.Format", THML_DC_FORMAT, ""},
    {"DC.Identifier", THML_DC_IDENTIFIER, "scheme=\"\""},
    {"DC.Language", THML_DC_LANGUAGE, "scheme=\"\""},
    {"DC.Publisher", THML_DC_PUBLISHER, "scheme=\"\""},
    {"DC.Relation", THML_DC_RELATION, ""},
    {"DC.Rights", THML_DC_RIGHTS, ""},
    {"DC.Source", THML_DC_SOURCE, ""},
    {"DC.Subject", THML_DC_SUBJECT, "scheme=\"\""},
    {"DC.Title", THML_DC_TITLE, ""},
    {"DC.Type", THML_DC_TYPE, "scheme=\"\""},
    {"def", THML_DEF, ""},
    {"deleted", THML_DELETED, "reason=\"\" resp=\"\" date=\"\""},
    {"description", THML_DESCRIPTION, ""},
    {"div1", THML_DIV1, "type=\"\" n=\"\" title=\"\""},
    {"div2", THML_DIV2, "type=\"\" n=\"\" title=\"\""},
    {"div3", THML_DIV3, "type=\"\" n=\"\" title=\"\""},
    {"div4", THML_DIV4, "type=\"\" n=\"\" title=\"\""},
    {"div5", THML_DIV5, "type=\"\" n=\"\" title=\"\""},
    {"div6", THML_DIV6, "type=\"\" n=\"\" title=\"\""},
    {"editorialComments", THML_EDITORIALCOMMENTS, ""},
    {"electronicEdInfo", THML_ELECTRONICEDINFO, ""},
    {"firstpublished", THML_FIRSTPUBLISHED, ""},
    {"foreign", THML_FOREIGN, "lang=\"\" dir=\"\""},
    {"generalinfo", THML_GENERALINFO, ""},
    {"glossary", THML_GLOSSARY, "type=\"\""},
    {"hymn", THML_HYMN, ""},
    {"image", THML_IMAGE, "type=\"\" href=\"\""},
    {"incipit", THML_INCIPIT, "value=\"\""},
    {"index", THML_INDEX, "type=\"\" subjectID=\"\" title=\"\""},
    {"insertindex", THML_INSERTINDEX, "type=\"\""},
    {"l", THML_L, ""},
    {"meter", THML_METER, ""},
    {"music", THML_MUSIC, "href=\"\" type\"\""},
    {"name", THML_NAME, "title\"\""},
    {"note", THML_NOTE, "n=\"\""},
    {"pb", THML_PB, "n=\"\" href=\"\""},
    {"printsourceinfo", THML_PRINTSOURCEINFO, ""},
    {"pubhistory", THML_PUBHISTORY, ""},
    {"published", THML_PUBLISHED, ""},
    {"publisherid", THML_PUBLISHERID, ""},
    {"revisionhistory", THML_REVISIONHISTORY, ""},
    {"scripCom", THML_SCRIPCOM, "passage=\"\""},
    {"scripContext", THML_SCRIPCONTEXT, "passage=\"\""},
    {"scripRef", THML_SCRIPREF, "passage=\"\""},
    {"scripture", THML_SCRIPTURE, "passage=\"\""},
    {"status", THML_STATUS, ""},
    {"sync", THML_SYNC, "type=\"\" value\"\""},
    {"term", THML_TERM, ""},
    {"ThML", THML_THML, ""},
    {"ThML.body", THML_THML_BODY, ""},
    {"ThML.head", THML_THML_HEAD, ""},
    {"tune", THML_TUNE, "tuneID=\"\""},
    {"unclear", THML_UNCLEAR, ""},
    {"verse", THML_VERSE, ""},
    {"version", THML_VERSION, ""},
    {"", INT_UNKNOWN, ""}
};

SwElementData HtmlElementData[] =
{
    {"a", THML_A, "href=\"\""},
    {"abbr", THML_ABBR, "title=\"\""},
    {"address", THML_ADDRESS, ""},
    {"article", THML_ARTICLE, ""},
    {"audio", THML_AUDIO, "controls"},
    {"b", THML_B, ""},
    {"blockquote", THML_BLOCKQUOTE, ""},
    {"body", THML_BODY, ""},
    {"br", THML_BR, ""},
    {"caption", THML_CAPTION, ""},
    {"cite", THML_CITE, ""},
    {"col", THML_COL, "span=\"\""},
    {"colgroup", THML_COLGROUP, ""},
    {"dd", THML_DD, ""},
    {"del", THML_DEL, ""},
    {"details", THML_DETAILS, ""},
    {"dfn", THML_DFN, ""},
    {"div", THML_DIV, ""},
    {"dl", THML_DL, ""},
    {"dt", THML_DT, ""},
    {"em", THML_EM, ""},
    {"figcaption", THML_FIGCAPTION, ""},
    {"figure", THML_FIGURE, ""},
    {"footer", THML_FOOTER, ""},
    {"head", THML_HEAD, ""},
    {"header", THML_HEADER, ""},
    {"hr", THML_HR, ""},
    {"html", THML_HTML, ""},
    {"h1", THML_H1, ""},
    {"h2", THML_H2, ""},
    {"h3", THML_H3, ""},
    {"h4", THML_H4, ""},
    {"h5", THML_H5, ""},
    {"h6", THML_H6, ""},
    {"i", THML_I, ""},
    {"img", THML_IMG, "src=\"\" alt=\"\""},
    {"ins", THML_INS, ""},
    {"li", THML_LI, ""},
    {"mark", THML_MARK, ""},
    {"ol", THML_OL, ""},
    {"p", THML_P, ""},
    {"pre", THML_PRE, ""},
    {"q", THML_Q, ""},
    {"s", THML_S, ""},
    {"samp", THML_SAMP, ""},
    {"section", THML_SECTION, ""},
    {"small", THML_SMALL, ""},
    {"source", THML_SOURCE, "src=\"\" type=\"\""},
    {"span", THML_SPAN, ""},
    {"strike", THML_STRIKE, ""},
    {"strong", THML_STRONG, ""},
    {"sub", THML_SUB, ""},
    {"summary", THML_SUMMARY, ""},
    {"sup", THML_SUP, ""},
    {"table", THML_TABLE, ""},
    {"tbody", THML_TBODY, ""},
    {"td", THML_TD, ""},
    {"tfoot", THML_TFOOT, ""},
    {"th", THML_TH, ""},
    {"thead", THML_THEAD, ""},
    {"time", THML_TIME, ""},
    {"title", THML_TITLE, ""},
    {"tr", THML_TR, ""},
    {"u", THML_U, ""},
    {"ul", THML_UL, ""},
    {"video", THML_VIDEO, "controls"},
    {"", INT_UNKNOWN, ""}
};

void SwThMLElements::GetThMLList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;

    for (swUI16 i = 0; ThMLElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(i);
        buffer.Copy(ThMLElementData[i].name);
        lItem.SetText(buffer.GetArray());
        lItem.SetData(ThMLElementData[i].elementId);
        listCtrl->InsertItem(lItem);
    }
}

void SwThMLElements::GetElementList(SwString & buffer)
{
    for (swUI16 i = 0; HtmlElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        if (i)
            buffer += ' ';

        buffer += HtmlElementData[i].name;
    }

    for (swUI16 i = 0; ThMLElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        buffer += ' ';
        buffer += ThMLElementData[i].name;
    }
}

bool SwThMLElements::GetThMLElementData(swUI16 id, SwString & name, SwString & attributes)
{
    name.Reset();
    attributes.Reset();

    for (swUI16 i = 0; ThMLElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        if (ThMLElementData[i].elementId == id)
        {
            name = ThMLElementData[i].name;
            attributes = ThMLElementData[i].attributes;
            return true;
        }
    }

    return false;
}

void SwThMLElements::GetHtmlList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;

    for (swUI16 i = 0; HtmlElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(i);
        buffer.Copy(HtmlElementData[i].name);
        lItem.SetText(buffer.GetArray());
        lItem.SetData(HtmlElementData[i].elementId);
        listCtrl->InsertItem(lItem);
    }
}

bool SwThMLElements::GetHtmlElementData(swUI16 id, SwString & name, SwString & attributes)
{
    name.Reset();
    attributes.Reset();

    for (swUI16 i = 0; HtmlElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        if (HtmlElementData[i].elementId == id)
        {
            name = HtmlElementData[i].name;
            attributes = HtmlElementData[i].attributes;
            return true;
        }
    }

    return false;
}

