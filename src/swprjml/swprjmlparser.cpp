///////////////////////////////////////////////////////////////////
// Name:        SwProjectMlParser.cpp
// Purpose:     Process project files for ThML Builder.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/swprjml/swprjmlparser.h"
#include "../../include/appi/appifa.h"
#include "../../include/thml/thml_utility.h"

swI16 SWPRJMLElementIdx[26] =
{
    -1, SWPRJML_BODY, -1, SWPRJML_DIV1, -1, SWPRJML_FILE, -1, SWPRJML_HEAD,
        SWPRJML_INFO, -1, -1, -1, -1, -1, -1, SWPRJML_PROJECT, -1,SWPRJML_REFERENCES, SWPRJML_STYLE, -1, -1, SWPRJML_VERBATIM, -1, -1, -1, -1
    };

SwElement SWPRJMLElementArray[N_SWPRJML_ELEMENTS] =
{
    {"body", SWPRJML_BODY, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"div1", SWPRJML_DIV1, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"div2", SWPRJML_DIV2, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"div3", SWPRJML_DIV3, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"div4", SWPRJML_DIV4, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"div5", SWPRJML_DIV5, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"div6", SWPRJML_DIV6, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"file", SWPRJML_FILE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"head", SWPRJML_HEAD, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"info", SWPRJML_INFO, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"project", SWPRJML_PROJECT, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"references", SWPRJML_REFERENCES, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"style", SWPRJML_STYLE, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL},
    {"verbatim", SWPRJML_VERBATIM, ELEMENT_TYPE_INLINE, WHITE_SPACE_NORMAL}
};

SwElementData SWPRJMLElementData[] =
{
    {"body", SWPRJML_BODY, ""},
    {"div1", SWPRJML_DIV1, "src=\"\" title=\"\" id=\"\""},
    {"div2", SWPRJML_DIV2, "src=\"\" title=\"\" id=\"\""},
    {"div3", SWPRJML_DIV3, "src=\"\" title=\"\" id=\"\""},
    {"div4", SWPRJML_DIV4, "src=\"\" title=\"\" id=\"\""},
    {"div5", SWPRJML_DIV5, "src=\"\" title=\"\" id=\"\""},
    {"div6", SWPRJML_DIV6, "src=\"\" title=\"\" id=\"\""},
    {"file", SWPRJML_FILE, "src=\"\""},
    {"head", SWPRJML_HEAD, ""},
    {"info", SWPRJML_INFO, ""},
    {"project", SWPRJML_PROJECT, "target=\"\""},
    {"references", SWPRJML_REFERENCES, "process=\"\" cvdiv=\"\" span=\"\" div=\"\" break=\"\" romanforchapters=\"\" romanforverses=\"\" romanlowercase=\"\" booknameuppercase=\"\" linebreakisspace=\"\""},
    {"style", SWPRJML_STYLE, ""},
    {"verbatim", SWPRJML_VERBATIM, ""},
    {"", INT_UNKNOWN, ""}
};

SwProjectMlParser::SwProjectMlParser()
{
    m_status = false;

    for (swUI16 i = 0; i < N_SWPRJML_ELEMENTS; i++)
    {
        m_prjMLHandlers[i] = &SwProjectMlParser::Onvoid;
    }

    m_prjMLHandlers[SWPRJML_BODY] = &SwProjectMlParser::Onbody;
    m_prjMLHandlers[SWPRJML_DIV1] = &SwProjectMlParser::Ondiv1;
    m_prjMLHandlers[SWPRJML_DIV2] = &SwProjectMlParser::Ondiv2;
    m_prjMLHandlers[SWPRJML_DIV3] = &SwProjectMlParser::Ondiv3;
    m_prjMLHandlers[SWPRJML_DIV4] = &SwProjectMlParser::Ondiv4;
    m_prjMLHandlers[SWPRJML_DIV5] = &SwProjectMlParser::Ondiv5;
    m_prjMLHandlers[SWPRJML_DIV6] = &SwProjectMlParser::Ondiv6;
    m_prjMLHandlers[SWPRJML_FILE] = &SwProjectMlParser::Onfile;
    m_prjMLHandlers[SWPRJML_HEAD] = &SwProjectMlParser::Onhead;
    m_prjMLHandlers[SWPRJML_INFO] = &SwProjectMlParser::Oninfo;
    m_prjMLHandlers[SWPRJML_PROJECT] = &SwProjectMlParser::Onproject;
    m_prjMLHandlers[SWPRJML_REFERENCES] = &SwProjectMlParser::Onreferences;
    m_prjMLHandlers[SWPRJML_STYLE] = &SwProjectMlParser::Onstyle;
    m_prjMLHandlers[SWPRJML_VERBATIM] = &SwProjectMlParser::Onverbatim;

    m_elementArray = SWPRJMLElementArray;
    m_elementAlphaIdx = SWPRJMLElementIdx;
    m_elementItems = N_SWPRJML_ELEMENTS;
    m_markupType = MARKUP_SWPRJ;
}

SwProjectMlParser::~SwProjectMlParser()
{
}

void SwProjectMlParser::GetPrjMlList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;

    for (swUI16 i = 0; SWPRJMLElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(i);
        buffer.Copy(SWPRJMLElementData[i].name);
        lItem.SetText(buffer.GetArray());
        lItem.SetData(SWPRJMLElementData[i].elementId);
        listCtrl->InsertItem(lItem);
    }
}

bool SwProjectMlParser::GetPrjMlElementData(swUI16 id, SwString & name, SwString & attributes)
{
    name.Reset();
    attributes.Reset();

    for (swUI16 i = 0; SWPRJMLElementData[i].elementId != INT_UNKNOWN; i ++)
    {
        if (SWPRJMLElementData[i].elementId == id)
        {
            name = SWPRJMLElementData[i].name;
            attributes = SWPRJMLElementData[i].attributes;
            return true;
        }
    }

    return false;
}

swUI32 SwProjectMlParser::Handle(swUI16 id, swUI32 node)
{
    return (this->*m_prjMLHandlers[id])(node);
}

void SwProjectMlParser::Run()
{
    swUI16 id;
    CollectPageData();

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
            if (id < N_SWPRJML_ELEMENTS)
                node = Handle(id, node);
            else
                node = Onvoid(node);
        }
    }
}

swUI32 SwProjectMlParser::Onbinary(swUI32 node)
{
    SwFile file;
    SwString path, abspath;
    char buffer[4096];
    size_t bytes_in;
    char binary_close[] = "\n</binary>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        GetNamedValueFromNode(node, "src", path);
        SwGetPathFromRelative(GetBasePath(), path, abspath);

        if (!file.Open(abspath, FMD_R))
            return node;

        fprintf(m_output.m_file, "<binary id=\"%s\" size=\"%lu\">", path.GetArray(), (unsigned long) file.GetSize());

        for (;;)
        {
            bytes_in = file.Read((void *) &buffer, 1, 4096);

            if (bytes_in < 1)
                break;

            m_output.Write((void *) & buffer, 1, bytes_in);
        }

        file.Close();
        m_output.Write(binary_close, 1, strlen(binary_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Onbody(swUI32 node)
{
    char body_open[] = "\n<ThML.body>\n";
    char body_close[] = "\n</ThML.body>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_output.Write(body_open, 1, strlen(body_open));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(body_close, 1, strlen(body_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Ondiv1(swUI32 node)
{
    char div_open[] = "div1";
    char div_close[] = "</div1>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        ProcessFile(div_open, node);
    }

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(div_close, 1, strlen(div_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Ondiv2(swUI32 node)
{
    char div_open[] = "div2";
    char div_close[] = "</div2>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        ProcessFile(div_open, node);
    }

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(div_close, 1, strlen(div_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Ondiv3(swUI32 node)
{
    char div_open[] = "div3";
    char div_close[] = "</div3>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        ProcessFile(div_open, node);
    }

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(div_close, 1, strlen(div_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Ondiv4(swUI32 node)
{
    char div_open[] = "div4";
    char div_close[] = "</div4>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        ProcessFile(div_open, node);
    }

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(div_close, 1, strlen(div_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Ondiv5(swUI32 node)
{
    char div_open[] = "div5";
    char div_close[] = "</div5>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        ProcessFile(div_open, node);
    }

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(div_close, 1, strlen(div_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Ondiv6(swUI32 node)
{
    char div_open[] = "div6";
    char div_close[] = "</div6>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        ProcessFile(div_open, node);
    }

    if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(div_close, 1, strlen(div_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Onfile(swUI32 node)
{
    SwFile file;
    SwString path, abspath;
    char buffer[4096];
    size_t bytes_in;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        GetNamedValueFromNode(node, "src", path);
        SwGetPathFromRelative(GetBasePath(), path, abspath);

        if (!file.Open(abspath, FMD_R))
            return node;

        for (;;)
        {
            bytes_in = file.Read((void *) &buffer, 1, 4096);

            if (bytes_in < 1)
                break;

            m_output.Write((void *) & buffer, 1, bytes_in);
        }

        file.Close();
    }

    return node;
}

swUI32 SwProjectMlParser::Onhead(swUI32 node)
{
    char head_open[] = "\n<ThML.head>\n";
    char head_close[] = "\n</ThML.head>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_output.Write(head_open, 1, strlen(head_open));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(head_close, 1, strlen(head_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Oninfo(swUI32 node)
{
    char info_open[] = "\n<electronicEdInfo>\n";
    char info_close[] = "\n</electronicEdInfo>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_output.Write(info_open, 1, strlen(info_open));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(info_close, 1, strlen(info_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Onproject(swUI32 node)
{
    SwString target, path;
    char xml_declare[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<?xml-stylesheet type=\"text/xsl\" href=\"../../../../ss/thml.html.xsl\"?>\n";
    char thml_open[] = "<ThML>\n";
    char thml_close[] = "\n</ThML>";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        CollectPageData();
        GetNamedValueFromNode(node, "target", target);
        SwGetPathFromRelative(GetBasePath(), target, path);

        if (!m_output.Open(path, FMD_WC))
        {
            wxMessageBox(SwApplicationInterface::GetControlString("SID_FAILEDTOCREATEFILE", L"Failed to create file."));
            return GetLastParserNode();
        }

        m_output.Write(xml_declare, 1, strlen(xml_declare));
        m_output.Write(thml_open, 1, strlen(thml_open));
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(thml_close, 1, strlen(thml_close));
        m_status = true;
        m_output.Close();
        return GetLastParserNode();
    }

    return node;
}

swUI32 SwProjectMlParser::Onreferences(swUI32 node)
{
    SwString buffer;
    SwStringW wbuffer;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        if (GetNamedValueFromNode(node, "process", buffer))
            SetProcessReferences(buffer.BoolFromString());

        if (GetNamedValueFromNode(node, "cvdiv", buffer))
        {
            wbuffer.Copy(buffer);
            m_referenceParser.SetCVDivMarker(wbuffer.GetAt(0));
        }

        if (GetNamedValueFromNode(node, "span", buffer))
        {
            wbuffer.Copy(buffer);
            m_referenceParser.SetSpanMarker(wbuffer.GetAt(0));
        }

        if (GetNamedValueFromNode(node, "div", buffer))
        {
            wbuffer.Copy(buffer);
            m_referenceParser.SetDivMarker(wbuffer.GetAt(0));
        }

        if (GetNamedValueFromNode(node, "break", buffer))
        {
            wbuffer.Copy(buffer);
            m_referenceParser.SetBreakMarker(wbuffer.GetAt(0));
        }

        if (GetNamedValueFromNode(node, "romanforchapters", buffer))
        {
            m_referenceParser.SetRomanForChapters(buffer.BoolFromString());
        }

        if (GetNamedValueFromNode(node, "romanforverses", buffer))
        {
            m_referenceParser.SetRomanForVerses(buffer.BoolFromString());
        }

        if (GetNamedValueFromNode(node, "romanlowercase", buffer))
        {
            m_referenceParser.SetRomanLowerCase(buffer.BoolFromString());
        }

        if (GetNamedValueFromNode(node, "booknameuppercase", buffer))
        {
            m_referenceParser.SetFirstLetterUpperCase(buffer.BoolFromString());
        }

        if (GetNamedValueFromNode(node, "linebreakisspace", buffer))
        {
            m_referenceParser.SetLineBreakIsSpace(buffer.BoolFromString());
        }
    }

    return node;
}

swUI32 SwProjectMlParser::Onstyle(swUI32 node)
{
    char css_open[] = "\n<style type=\"text/css\">\n";
    char css_close[] = "\n</style>\n";

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_output.Write(css_open, 1, strlen(css_open));

    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_output.Write(css_close, 1, strlen(css_close));
    }

    return node;
}

swUI32 SwProjectMlParser::Onverbatim(swUI32 node)
{
    SwString buffer;
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        if (GetDataBetweenMates(node, buffer, false))
            m_output.Write(buffer, 1, buffer.Strlen());

        return GetNodeMate(node);
    }

    return node;
}

swUI32 SwProjectMlParser::Onvoid(swUI32 node)
{
    return node;
}

void SwProjectMlParser::CollectPageData()
{
    m_pageData.Reset();

    for (swUI32 i = 0; i < GetParserNodes(); i ++)
    {
        if (!IsDivN(i) || (GetNodeType(i) != NODE_TYPE_BEGIN_TAG && GetNodeType(i) != NODE_TYPE_UNPAIRED_TAG))
            continue;

        GetTagData(i);
    }
}

void SwProjectMlParser::GetTagData(swUI32 node)
{
    SwString path, abspath;
    SwString id, title;
    GetNamedValueFromNode(node, "src", path);
    GetNamedValueFromNode(node, "title", title);
    GetNamedValueFromNode(node, "id", id);

    SwGetPathFromRelative(GetBasePath(), path, abspath);
    m_pageData.Add(abspath, id, title);
}

swUI32 SwProjectMlParser::FindInPages(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_pageData.GetCount(); i ++)
    {
        if (stricmp(m_pageData.GetAt(i).GetStrA(), str) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

void SwProjectMlParser::RepairLinks(SwThMLParser * parser)
{
    SwString anchor, value, tag, abs;
    SwFilePath path;
    swUI32 page;
    swUI32 start = parser->FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);

    if (start == NODE_ID_INVALID)
        return;

    swUI32 end = parser->GetNodeMate(start);

    if (end == NODE_ID_INVALID)
        return;

    start ++;

    for (swUI32 i = start; i < end; i ++)
    {
        if (parser->GetNodeType(i) == NODE_TYPE_END_TAG)
            continue;

        if (parser->GetNodeElementIdentifier(i) != THML_A)
            continue;

        if (!parser->GetNamedValueFromNode(i, "href", path))
            continue;

        parser->GetNodeData(i, tag);
        parser->DeleteNamedValue(tag, "href", true);

        anchor = path.GetAnchor();
        path.ClipAnchor();

        SwGetPathFromRelative(parser->GetBasePath(), path, abs);

        page = FindInPages(abs.GetArray());

        if (page == NODE_ID_INVALID)
            continue;

        value = "href=\"";
        value += "#";
        value += m_pageData.GetAt(page).GetStrB().GetArray();

        if (anchor.Strlen())
        {
            value += "-";
            value += anchor.GetArray();
        }

        value += "\"";
        parser->InsertAttribute(tag, value, true);
        parser->ReplaceNode(i, tag, true);
    }
}

void SwProjectMlParser::ProcessReferences(SwThMLParser * parser)
{
    SwString tag;

    swUI32 start = parser->FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);

    if (start == NODE_ID_INVALID)
        return;

    swUI32 end = parser->GetNodeMate(start);

    if (end == NODE_ID_INVALID)
        return;

    start ++;

    for (swUI32 i = start; i < end; i ++)
    {
        if (parser->GetNodeType(i) != NODE_TYPE_TEXT_RUN)
            continue;

        if (parser->GetNodeElementIdentifier(parser->GetNodeParent(i)) == THML_A)
            continue;

        parser->GetNodeData(i, tag);

        m_referenceParser.Reset();
        m_referenceParser.Copy(tag);

        m_referenceParser.Parse();

        if (m_referenceParser.Run())
        {
            m_referenceParser.WriteReferenceMarkUp();
            tag.Copy(m_referenceParser.GetArray());

            swUI32 nodes = GetParserNodes();
            parser->ReplaceNode(i, tag);
            swUI32 diff = GetParserNodes() - nodes;
            i += diff;
            end += diff;
        }
    }
}

bool SwProjectMlParser::IsSkipElement(swUI16 element)
{
    if (element >= INT_UNKNOWN)
        return true;

    switch (element)
    {
    case THML_B :
    case THML_I :
    case THML_EM :
    case THML_S :
    case THML_STRIKE :
    case THML_STRONG :
    case THML_U :
    case THML_FONT :
    case THML_Q :
    case THML_STYLE :
    case THML_TR :
    case THML_TBODY :
    case THML_BR :
        return true;
    default :
        return false;
    }

    return false;
}

void SwProjectMlParser::SetIds(SwThMLParser * parser, swUI32 page)
{
    SwString tag, genId, value;
    bool hasId;

    swUI32 start = parser->FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);
    if (start == NODE_ID_INVALID)
        return;

    swUI32 end = parser->GetNodeMate(start);

    start ++;

    for (swUI32 i = start; i < end; i ++)
    {
        if (parser->GetNodeType(i) != NODE_TYPE_BEGIN_TAG && parser->GetNodeType(i) != NODE_TYPE_UNPAIRED_TAG)
            continue;

        hasId = parser->GetNamedValueFromNode(i, "id", genId);
        if (!hasId && IsSkipElement(parser->GetNodeElementIdentifier(i)))
            continue;

        if (!hasId)
            genId = GenerateId(parser, i, m_pageData.GetAt(page).GetStrB().GetArray());

        parser->GetNodeData(i, tag);
        parser->DeleteNamedValue(tag, "id", true);

        value = "id=\"";

        if (hasId)
        {
            value += m_pageData.GetAt(page).GetStrB().GetArray();
            value += "-";
        }

        value += genId.GetArray();
        value += "\"";

        parser->InsertAttribute(tag, value, true);
        parser->ReplaceNode(i, tag, true);
    }
}

const char * SwProjectMlParser::GenerateId(SwThMLParser * parser, swUI32 node, const char * divId)
{
    static char id[200];
    swUI32 par = 0;
    swUI32 item = 0;

    id[0] = '\0';

    for (swUI32 i = 0; i <= node; i ++)
    {
        if (parser->GetNodeElementIdentifier(i) == THML_P)
        {
            par ++;
            item = 0;
        }
        else if (!IsSkipElement(parser->GetNodeElementIdentifier(i)))
        {
            item ++;
        }
    }

    if (parser->GetNodeElementIdentifier(node) == THML_P)
    {
        sprintf(id, "%s-p%u", divId, par);
    }
    else if (!IsSkipElement(parser->GetNodeElementIdentifier(node)))
    {
        sprintf(id, "%s-p%u.%u", divId, par, item);
    }

    return id;
}

void SwProjectMlParser::ProcessFile(const char * divstr, swUI32 node)
{
    if (!divstr)
        return;

    SwString path, abspath, data;
    GetNamedValueFromNode(node, "src", path);
    SwGetPathFromRelative(GetBasePath(), path, abspath);
    swUI32 index = FindInPages(abspath);

    if (index == NODE_ID_INVALID)
        return;

    swUI32 startNode;

    if (!m_parser.OpenFile(m_pageData.GetAt(index).GetStrA(), MODE_MEMORY, false))
        return;

    fprintf(m_output.m_file, "\n<%s title=\"%s\" id=\"%s\">\n", divstr, m_pageData.GetAt(index).GetStrC().GetArray(), m_pageData.GetAt(index).GetStrB().GetArray());

    startNode = m_parser.FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);

    if (m_processreferences)
        ProcessReferences(&m_parser);

    SetIds(&m_parser, index);
    RepairLinks(&m_parser);

    if (startNode != NODE_ID_INVALID && m_parser.GetNodeMate(startNode) != NODE_ID_INVALID)
    {
        m_parser.GetDataBetweenMates(startNode, data, false);
        m_output.Write(data.GetArray(), 1, data.Strlen());
    }

    m_parser.CloseFile();
}

bool SwProjectMlParser::IsDivN(swUI32 node)
{
    if (GetNodeElementIdentifier(node) >= SWPRJML_DIV1 && GetNodeElementIdentifier(node) <= SWPRJML_DIV6)
        return true;

    return false;
}

void SwProjectMlParser::SetProcessReferences(bool process)
{
    m_processreferences = process;
}

