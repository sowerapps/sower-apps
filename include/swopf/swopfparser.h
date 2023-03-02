///////////////////////////////////////////////////////////////////
// Name:        swopfparser.h
// Purpose:     Parse OPF files, and create Sower Project Files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SWOPFPARSER_H
#define SWOPFPARSER_H

#include "../thml/thml_parser.h"
#include "../bible/referenceparser.h"
#include "../bible/standard_bible.h"

enum SWOPF_ELEMENTS
{
    SWOPF_DC_CONTRIBUTOR, SWOPF_DC_COVERAGE, SWOPF_DC_CREATOR, SWOPF_DC_DATE, SWOPF_DC_DESCRIPTION,
    SWOPF_DC_FORMAT, SWOPF_DC_IDENTIFIER, SWOPF_DC_LANGUAGE, SWOPF_DC_PUBLISHER, SWOPF_DC_RELATION,
    SWOPF_DC_RIGHTS, SWOPF_DC_SOURCE, SWOPF_DC_SUBJECT, SWOPF_DC_TITLE, SWOPF_DC_TYPE,
    SWOPF_GUIDE, SWOPF_ITEM, SWOPF_ITEMREF, SWOPF_MANIFEST, SWOPF_META, SWOPF_METADATA,
    SWOPF_PACKAGE, SWOPF_REFERENCE, SWOPF_SPINE, SWOPF_XML,
    N_SWOPF_ELEMENTS
};

class SwOPFParser;
typedef swUI32 (SwOPFParser::*SwGuiTagHandler)(swUI32 node);

class SOWERBASEEXP SwOPFParser : public SwThMLParser
{
public:
    SwOPFParser();
    virtual ~SwOPFParser();

    bool Run(const char * filename);
    void SetOptions(bool processReferences, wchar_t _cvdiv, wchar_t _span, wchar_t _div, wchar_t _break, bool romanforchapters, bool romanforverses, bool linebreakisspace);
    void SetProcessReferences(bool state);
    void SetCVDivMarker(wchar_t marker);
    void SetSpanMarker(wchar_t marker);
    void SetDivMarker(wchar_t marker);
    void SetBreakMarker(wchar_t marker);
    void SetRomanForChapters(bool state);
    void SetRomanForVerses(bool state);
    void SetRomanLowerCase(bool state);
    void SetBookNamesUpperCase(bool state);
    void SetLineBreakIsSpace(bool state);
    void CollectPageData();
    void WriteDublinCore();
    void WriteCss();
    void WritePages();
    swUI32 FindInPages(const char * str);

protected:
    bool                 m_processReferences;
    wchar_t              m_cvdiv;
    wchar_t              m_span;
    wchar_t              m_div;
    wchar_t              m_break;
    bool                 m_romanforchapters;
    bool                 m_romanforverses;
    bool                 m_romanlowercase;
    bool                 m_booknamesuppercase;
    bool                 m_linebreakisspace;
    SwFile               m_output;
    SwStringTripletArray m_pageData;
};

#endif // SWOPFPARSER_H
