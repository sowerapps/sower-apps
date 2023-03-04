///////////////////////////////////////////////////////////////////
// Name:        swopfparser.cpp
// Purpose:     Parse OPF files, and create Sower Project Files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/swopf/swopfparser.h"
#include "../../include/appi/appifa.h"
#include "../../include/thml/thml_utility.h"

swI16 SWOPFElementIdx[26] =
{
    -1, -1, -1, SWOPF_DC_CONTRIBUTOR, -1, -1, SWOPF_GUIDE, -1,
        SWOPF_ITEM, -1, -1, -1, SWOPF_MANIFEST, -1, -1, SWOPF_PACKAGE,
        -1, SWOPF_REFERENCE, SWOPF_SPINE, -1, -1, -1, -1, SWOPF_XML, -1, -1
    };

SwElement SWOPFElementArray[N_SWOPF_ELEMENTS] =
{
    {"dc:contributor", SWOPF_DC_CONTRIBUTOR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:coverage", SWOPF_DC_COVERAGE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:creator", SWOPF_DC_CREATOR, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:date", SWOPF_DC_DATE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:description", SWOPF_DC_DESCRIPTION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:format", SWOPF_DC_FORMAT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:identifier", SWOPF_DC_IDENTIFIER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:language", SWOPF_DC_LANGUAGE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:publisher", SWOPF_DC_PUBLISHER, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:relation", SWOPF_DC_RELATION, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:rights", SWOPF_DC_RIGHTS, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:source", SWOPF_DC_SOURCE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:subject", SWOPF_DC_SUBJECT, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:title", SWOPF_DC_TITLE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"dc:type", SWOPF_DC_TYPE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"guide", SWOPF_GUIDE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"item", SWOPF_ITEM, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"itemref", SWOPF_ITEMREF, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"manifest", SWOPF_MANIFEST, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"meta", SWOPF_META, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"metadata", SWOPF_METADATA, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"package", SWOPF_PACKAGE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"reference", SWOPF_REFERENCE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"spine", SWOPF_SPINE, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
    {"xml", SWOPF_XML, ELEMENT_TYPE_BLOCK, WHITE_SPACE_NORMAL},
};

SwOPFParser::SwOPFParser()
{
    m_elementArray = SWOPFElementArray;
    m_elementAlphaIdx = SWOPFElementIdx;
    m_elementItems = N_SWOPF_ELEMENTS;
    m_markupType = MARKUP_SWOPF;
    m_cvdiv = L':';
    m_span = L'-';
    m_div = L',';
    m_break = L';';
    m_romanforchapters = false;
    m_romanforverses = false;
    m_romanlowercase = false;
    m_booknamesuppercase = false;
    m_linebreakisspace = true;
    m_processReferences = true;
}

SwOPFParser::~SwOPFParser()
{
}

bool SwOPFParser::Run(const char * filename)
{
    if (!filename)
        return false;

    SwFilePath path;
    SwString buffer;

    path.Copy(GetBasePath());
    path += PATH_SEP;
    path += filename;
    path += ".swprj";

    if (!m_output.Open(path, FMD_WC))
        return false;

    CollectPageData();

    // Project
    buffer = "<project target=\"";
    buffer += filename;
    buffer += ".thm";
    buffer += "\"/>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());

    // Reference processing options-
    if (!m_processReferences)
        buffer = "<references process=\"false\"/>";
    else
    {
        buffer = "<references process=\"true\" cvdiv=\"";
        buffer += m_cvdiv;
        buffer += "\" span=\"";
        buffer += m_span;
        buffer += "\" div=\"";
        buffer += m_div;
        buffer += "\" break=\"";
        buffer += m_break;
        if (m_romanforchapters)
            buffer += "\" romanforchapters=\"true\"";
        else
            buffer += "\" romanforchapters=\"false\"";
        if (m_romanforverses)
            buffer += " romanforverses=\"true\"";
        else
            buffer += " romanforverses=\"false\"";
        if (m_romanlowercase)
            buffer += " romanlowercase=\"true\"";
        else
            buffer += " romanlowercase=\"false\"";
        if (m_booknamesuppercase)
            buffer += " booknameuppercase=\"true\"";
        else
            buffer += " booknameuppercase=\"false\"";
        if (m_linebreakisspace)
            buffer += " linebreakisspace=\"true\"/>\n";
        else
            buffer += " linebreakisspace=\"false\"/>\n";
    }

    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    // Reference processing options- End

    // Head
    buffer = "<head>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());

    // Dublin Core
    buffer = "<info>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    buffer = "<verbatim>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    buffer = "<dc>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    WriteDublinCore();
    buffer = "</dc>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    buffer = "</verbatim>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    buffer = "</info>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    // Dublin Core End

    // Style
    buffer = "<style>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    WriteCss();
    buffer = "\n</style>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    // Style End

    buffer = "</head>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    // Head End

    // Body
    buffer = "<body>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());

    // Pages
    WritePages();
    // End Pages

    buffer = "</body>\n";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    // Body End

    buffer = "</project>";
    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
    // Project End

    m_output.Close();

    return true;
}

void SwOPFParser::SetOptions(bool processReferences, wchar_t _cvdiv, wchar_t _span, wchar_t _div, wchar_t _break, bool romanforchapters, bool romanforverses, bool linebreakisspace)
{
    m_processReferences = processReferences;
    m_cvdiv = _cvdiv;
    m_span = _span;
    m_div = _div;
    m_break = _break;
    m_romanforchapters = romanforchapters;
    m_romanforverses = romanforverses;
    m_linebreakisspace = linebreakisspace;
}

void SwOPFParser::CollectPageData()
{
    m_pageData.Reset();

    SwString href, id, title, media_type, abs;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (GetNodeElementIdentifier(i) == SWOPF_ITEM)
        {
            title.Reset();
            if (GetNamedValueFromNode(i, "href", href) && GetNamedValueFromNode(i, "id", id) && GetNamedValueFromNode(i, "media-type", media_type) && media_type.StrCmp("application/xhtml+xml") == 0)
            {
                SwGetPathFromRelative(GetBasePath(), href, abs);
                SwThMLUtility::GetTitle(title, abs);
                title.Replace("\"", 1, "", 0);
                m_pageData.Add(href, id, title);
            }
        }
    }
}

void SwOPFParser::SetProcessReferences(bool state)
{
    m_processReferences = state;
}

void SwOPFParser::SetCVDivMarker(wchar_t marker)
{
    m_cvdiv = marker;
}

void SwOPFParser::SetSpanMarker(wchar_t marker)
{
    m_span = marker;
}

void SwOPFParser::SetDivMarker(wchar_t marker)
{
    m_div = marker;
}

void SwOPFParser::SetBreakMarker(wchar_t marker)
{
    m_break = marker;
}

void SwOPFParser::SetRomanForChapters(bool state)
{
    m_romanforchapters = state;
}

void SwOPFParser::SetRomanForVerses(bool state)
{
    m_romanforverses = state;
}

void SwOPFParser::SetRomanLowerCase(bool state)
{
    m_romanlowercase = state;
}

void SwOPFParser::SetBookNamesUpperCase(bool state)
{
    m_booknamesuppercase = state;
}

void SwOPFParser::SetLineBreakIsSpace(bool state)
{
    m_linebreakisspace = state;
}

void SwOPFParser::WriteDublinCore()
{
    swUI32 mate;
    SwString buffer;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (GetNodeElementIdentifier(i) >= SWOPF_DC_CONTRIBUTOR && GetNodeElementIdentifier(i) <= SWOPF_DC_TYPE && (GetNodeType(i) == NODE_TYPE_BEGIN_TAG || GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG))
        {
            mate = GetNodeMate(i);

            if (mate != NODE_ID_INVALID)
                GetNodesData(i, mate, buffer);
            else
                GetNodeData(i, buffer);

            buffer.TrimLeft('\t');
            buffer.TrimRight('\t');
            buffer.TrimLeft(' ');
            buffer.TrimRight(' ');
            buffer.Replace("dc:", 3, "dc.", 3);
            m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
        }
    }
}

void SwOPFParser::WriteCss()
{
    swUI32 parent;
    SwString href, media_type, buffer;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (GetNodeElementIdentifier(i) == SWOPF_ITEM)
        {
            parent = GetNodeParent(i);
            if (parent != NODE_ID_INVALID && GetNodeElementIdentifier(parent) == SWOPF_MANIFEST)
            {
                if (GetNamedValueFromNode(i, "href", href) && GetNamedValueFromNode(i, "media-type", media_type) && media_type.StrCmp("text/css") == 0)
                {
                    buffer = "<file src=\"";
                    buffer += href;
                    buffer += "\"/>";
                    m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
                }
            }
        }
    }
}

void SwOPFParser::WritePages()
{
    SwString buffer;
    swUI32 pageItem;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (GetNodeElementIdentifier(i) == SWOPF_ITEMREF && GetNamedValueFromNode(i, "idref", buffer))
        {
            pageItem = FindInPages(buffer);
            if (pageItem != NODE_ID_INVALID)
            {
                buffer = "<div1 src=\"";
                m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
                m_output.Write(m_pageData.GetAt(pageItem).GetStrA().GetArray(), 1, m_pageData.GetAt(pageItem).GetStrA().Strlen());
                buffer = "\" id=\"";
                m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
                m_output.Write(m_pageData.GetAt(pageItem).GetStrB().GetArray(), 1, m_pageData.GetAt(pageItem).GetStrB().Strlen());
                buffer = "\" title=\"";
                m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
                m_output.Write(m_pageData.GetAt(pageItem).GetStrC().GetArray(), 1, m_pageData.GetAt(pageItem).GetStrC().Strlen());
                buffer = "\"/>\n";
                m_output.Write(buffer.GetArray(), 1, buffer.Strlen());
            }
        }
    }
}

swUI32 SwOPFParser::FindInPages(const char * str)
{
    if (!str)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_pageData.GetCount(); i ++)
    {
        if (stricmp(m_pageData.GetAt(i).GetStrB(), str) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}
