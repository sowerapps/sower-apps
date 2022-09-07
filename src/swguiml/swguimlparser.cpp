///////////////////////////////////////////////////////////////////
// Name:        swguimlparser.cpp
// Purpose:     Save and restore gui perspective, and options.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/swguiml/swguimlparser.h"

swI16 SWGUIMLElementIdx[26] =
{
    -1, SWGUIML_BOOK, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, SWGUIML_OPTION, SWGUIML_PERSPECTIVE,
    -1, -1, -1, SWGUIML_TAB, -1, -1, -1, -1, -1, -1
};

SwElement SWGUIMLElementArray[N_SWGUIML_ELEMENTS] =
{
    {"book", SWGUIML_BOOK, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"option", SWGUIML_OPTION, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"perspective", SWGUIML_PERSPECTIVE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"tab", SWGUIML_TAB, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL}
};

SwGuiMlParser::SwGuiMlParser()
{
    m_guipanel = NULL;
    m_frame = NULL;

    for (swUI16 i = 0; i < N_SWGUIML_ELEMENTS; i++)
    {
        m_guiHandlers[i] = &SwGuiMlParser::Onvoid;
    }

    m_guiHandlers[SWGUIML_BOOK] = &SwGuiMlParser::Onbook;
    m_guiHandlers[SWGUIML_OPTION] = &SwGuiMlParser::Onoption;
    m_guiHandlers[SWGUIML_PERSPECTIVE] = &SwGuiMlParser::Onperspective;
    m_guiHandlers[SWGUIML_TAB] = &SwGuiMlParser::Ontab;

    m_elementArray = SWGUIMLElementArray;
    m_elementAlphaIdx = SWGUIMLElementIdx;
    m_elementItems = N_SWGUIML_ELEMENTS;
    m_markupType = MARKUP_SWGUI;
}

SwGuiMlParser::~SwGuiMlParser()
{
}

swUI32 SwGuiMlParser::Handle(swUI16 id, swUI32 node)
{
    return (this->*m_guiHandlers[id])(node);
}

void SwGuiMlParser::Run()
{
    swUI16 id;

    if (!m_guipanel && !m_frame)
        return;

    for (swUI32 node = 0; node < GetParserNodes(); node ++)
    {

        id = GetNodeElementIdentifier(node);

        if (id >= INT_UNKNOWN)
        {
            if (id == INT_UNKNOWN)
            {
                node = Onvoid(node);
            }
            else if (id == INT_BINARY)
            {
                node = Onbinary(node);
            }
            else if (id == INT_MODULE)
            {
                node = Onvoid(node);
            }
            else if (id == INT_TEXT_RUN)
            {
                node = Onvoid(node);
            }
        }
        else
        {
            if (id < N_SWGUIML_ELEMENTS)
                node = Handle(id, node);
            else
                node = Onvoid(node);
        }
    }
}

swUI32 SwGuiMlParser::Onbinary(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
        return GetNodeMate(node);

    return node;
}

swUI32 SwGuiMlParser::Onvoid(swUI32 node)
{
    return node;
}

swUI32 SwGuiMlParser::Onbook(swUI32 node)
{
    SwBookMarkClientData data;
    SwString buffer;

    if (!GetNamedValueFromNode(node, "bookid", data.m_bookId))
        return node;

    if (!GetNamedValueFromNode(node, "pageid", data.m_pageId))
        return node;

    if (GetNamedValueFromNode(node, "selbegin", buffer))
    {
        data.m_selBegin = buffer.Atoi();
    }

    if (GetNamedValueFromNode(node, "selend", buffer))
    {
        data.m_selEnd = buffer.Atoi();
    }

    if (GetNamedValueFromNode(node, "scrollhpos", buffer))
    {
        data.m_scrollHPos = buffer.Atoi();
    }

    if (GetNamedValueFromNode(node, "scrollvpos", buffer))
    {
        data.m_scrollVPos = buffer.Atoi();
    }

    GetNamedValueFromNode(node, "type", data.m_type);

    buffer.Reset();
    GetNamedValueFromNode(node, "ctrlid", buffer);

    if (m_frame)
        m_frame->ActivateBookMark(data, buffer);
    else if (m_guipanel)
        m_guipanel->ActivateBookMark(data, buffer);

    return node;
}

swUI32 SwGuiMlParser::Onoption(swUI32 node)
{
    SwString id, value;

    GetNamedValueFromNode(node, "id", id);
    GetNamedValueFromNode(node, "value", value);

    if (m_frame)
        m_frame->SetOption(id, value);
    else if (m_guipanel)
        m_guipanel->SetOption(id, value);

    return node;
}

swUI32 SwGuiMlParser::Onperspective(swUI32 node)
{
    if (GetNodeType(node) != NODE_TYPE_BEGIN_TAG)
        return node;

    SwString id, perspective;
    GetNamedValueFromNode(node, "id", id);
    GetDataBetweenMates(node, perspective, false);

    if (m_frame)
        m_frame->LoadPerspective(id, perspective);
    else if (m_guipanel)
        m_guipanel->LoadPerspective(id, perspective);

    return node;
}

swUI32 SwGuiMlParser::Ontab(swUI32 node)
{
    SwString path;

    if (!GetNamedValueFromNode(node, "target", path))
        return node;

    if (m_frame)
        m_frame->SelectTab(path);
    else if (m_guipanel)
        m_guipanel->SelectTab(path);

    return node;
}

void SwGuiMlParser::SetGuiPanel(SwGuiPanel * guipanel)
{
    m_guipanel = guipanel;
}

void SwGuiMlParser::SetFrame(SwFrame * frame)
{
    m_frame = frame;
}

void SwGuiMlParser::CreateBookTag(SwBookMarkClientData & data, const char * ctrlId, SwString & buffer)
{
    buffer.Size(2000);

    sprintf(buffer, "<book bookid=\"%s\" pageid=\"%s\" selbegin=\"%i\" selend=\"%i\" scrollhpos=\"%i\" scrollvpos=\"%i\" type=\"%s\" ctrlid=\"%s\"/>",
            data.m_bookId.GetArray(), data.m_pageId.GetArray(), data.m_selBegin, data.m_selEnd, data.m_scrollHPos, data.m_scrollVPos, data.m_type.GetArray(), ctrlId);
}

void SwGuiMlParser::CreateOptionTag(const char * id, const char * value, SwString & buffer)
{
    buffer.Size(2000);

    sprintf(buffer, "<option id=\"%s\" value=\"%s\"\"/>", id, value);
}
