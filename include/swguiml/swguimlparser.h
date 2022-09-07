///////////////////////////////////////////////////////////////////
// Name:        swguimlparser.h
// Purpose:     Save and restore gui perspective, and options.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SWGUIMLPARSER_H
#define SWGUIMLPARSER_H

#include "../thml/thml_parser.h"
#include "../framework/guipanel.h"
#include "../framework/frame.h"

enum SWGUIML_ELEMENTS
{
    SWGUIML_BOOK, SWGUIML_OPTION, SWGUIML_PERSPECTIVE, SWGUIML_TAB,
    N_SWGUIML_ELEMENTS
};

class SwGuiMlParser;
typedef swUI32 (SwGuiMlParser::*SwGuiTagHandler)(swUI32 node);

class SOWERBASEEXP SwGuiMlParser : public SwThMLParser
{
public:
    SwGuiMlParser();
    virtual ~SwGuiMlParser();

    void Run();
    virtual swUI32 Handle(swUI16 id, swUI32 node);
    virtual swUI32 Onvoid(swUI32 node);
    virtual swUI32 Onbinary(swUI32 node);
    virtual swUI32 Onbook(swUI32 node);
    virtual swUI32 Onoption(swUI32 node);
    virtual swUI32 Onperspective(swUI32 node);
    virtual swUI32 Ontab(swUI32 node);
    void SetGuiPanel(SwGuiPanel * guipanel);
    void SetFrame(SwFrame * frame);
    static void CreateBookTag(SwBookMarkClientData & data, const char * ctrlId, SwString & buffer);
    static void CreateOptionTag(const char * id, const char * value, SwString & buffer);

protected:
    SwGuiTagHandler m_guiHandlers[N_SWGUIML_ELEMENTS];
    SwString        m_nodeBuffer;
    SwGuiPanel *    m_guipanel;
    SwFrame *       m_frame;
};

#endif // SWGUIMLPARSER_H
