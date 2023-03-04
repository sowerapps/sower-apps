///////////////////////////////////////////////////////////////////
// Name:        SwProjectMlParser.h
// Purpose:     Process project files for ThML Builder.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SWPROJECTMLPARSER_H
#define SWPROJECTMLPARSER_H

#include "../thml/thml_parser.h"
#include "../bible/referenceparser.h"
#include "../bible/standard_bible.h"
#include <wx/listctrl.h>

enum SWPRJML_ELEMENTS
{
    SWPRJML_BODY,
    SWPRJML_DIV1, SWPRJML_DIV2, SWPRJML_DIV3, SWPRJML_DIV4,
    SWPRJML_DIV5, SWPRJML_DIV6, SWPRJML_FILE, SWPRJML_HEAD,
    SWPRJML_INFO, SWPRJML_PROJECT, SWPRJML_REFERENCES,
    SWPRJML_STYLE, SWPRJML_VERBATIM,
    N_SWPRJML_ELEMENTS
};

class SwProjectMlParser;
typedef swUI32 (SwProjectMlParser::*SwPrjMLTagHandler)(swUI32 node);

class SOWERBASEEXP SwProjectMlParser : public SwThMLParser
{
public:
    SwProjectMlParser();
    virtual ~SwProjectMlParser();

    static void GetPrjMlList(wxListCtrl * listCtrl);
    static bool GetPrjMlElementData(swUI16 id, SwString & name, SwString & attributes);
    void Run();
    virtual swUI32 Handle(swUI16 id, swUI32 node);
    virtual swUI32 Onbinary(swUI32 node);
    virtual swUI32 Onbody(swUI32 node);
    virtual swUI32 Ondiv1(swUI32 node);
    virtual swUI32 Ondiv2(swUI32 node);
    virtual swUI32 Ondiv3(swUI32 node);
    virtual swUI32 Ondiv4(swUI32 node);
    virtual swUI32 Ondiv5(swUI32 node);
    virtual swUI32 Ondiv6(swUI32 node);
    virtual swUI32 Onfile(swUI32 node);
    virtual swUI32 Onhead(swUI32 node);
    virtual swUI32 Oninfo(swUI32 node);
    virtual swUI32 Onproject(swUI32 node);
    virtual swUI32 Onreferences(swUI32 node);
    virtual swUI32 Onstyle(swUI32 node);
    virtual swUI32 Onverbatim(swUI32 node);
    virtual swUI32 Onvoid(swUI32 node);
    void CollectPageData();
    void GetTagData(swUI32 node);
    swUI32 FindInPages(const char * str);
    void RepairLinks(SwThMLParser * parser);
    void ProcessReferences(SwThMLParser * parser);
    bool IsSkipElement(swUI16 element);
    void SetIds(SwThMLParser * parser, swUI32 page);
    const char * GenerateId(SwThMLParser * parser, swUI32 node, const char * divId);
    void ProcessFile(const char * divstr, swUI32 node);
    bool IsDivN(swUI32 node);
    void GenerateTag(SwStringW & tag, SwReferenceData & data);
    void SetProcessReferences(bool process);

protected:
    SwPrjMLTagHandler    m_prjMLHandlers[N_SWPRJML_ELEMENTS];
    SwString             m_nodeBuffer;
    SwFile               m_output;
    bool                 m_status;
    SwStringTripletArray m_pageData;
    SwThMLParser         m_parser;
    SwReferenceParser    m_referenceParser;
    bool                 m_processreferences;
};

#endif // SWPROJECTMLPARSER_H
