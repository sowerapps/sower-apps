///////////////////////////////////////////////////////////////////
// Name:        referenceparser.cpp
// Purpose:     Parser for text, or html documents, with functionality
//              specific to ThML markup of scripture references.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/bible/referenceparser.h"
#include "../../include/bible/standard_bible.h"
#include "../../include/thml/thml_utility.h"

#include <sys/types.h>

#if defined __MSWIN__
#include <io.h>
#elif defined __linux__
#include <sys/io.h>
#include <unistd.h>
#elif defined __OSX__
#include <sys/uio.h>
#endif

#include <stdio.h>

SwReferenceParser::SwReferenceParser()
{
    m_parserNodeData = NULL;
    m_parserNodePos = 0;
    m_parserNodesAllocated = 0;
    m_parserInc = 100;

    m_cvdiv = L':';
    m_span = L'-';
    m_div = L',';
    m_break = L';';
    m_romanforchapters = false;
    m_romanforverses = false;
    m_romanlowercase = false;
    m_linebreakisspace = false;
    m_firstletteruc = false;

    m_handlers[NODE_TYPE_REF_CVDIV] = &SwReferenceParser::Oncvdiv;
    m_handlers[NODE_TYPE_REF_DIV] = &SwReferenceParser::Ondiv;
    m_handlers[NODE_TYPE_REF_CV_DIV_COMP] = &SwReferenceParser::Oncvdivcomp;
    m_handlers[NODE_TYPE_REF_SPAN] = &SwReferenceParser::Onspan;
    m_handlers[NODE_TYPE_REF_BREAK] = &SwReferenceParser::Onbreak;
    m_handlers[NODE_TYPE_SPACE] = &SwReferenceParser::Onspace;
    m_handlers[NODE_TYPE_ALPHA] = &SwReferenceParser::Onalpha;
    m_handlers[NODE_TYPE_ALPHA_ROMAN] = &SwReferenceParser::Onalpharoman;
    m_handlers[NODE_TYPE_NUMERIC] = &SwReferenceParser::Onnumeric;
    m_handlers[NODE_TYPE_SYMBOL] = &SwReferenceParser::Onsymbol;
    m_handlers[NODE_TYPE_LINE_BREAK] = &SwReferenceParser::Onlinebreak;
}

SwReferenceParser::~SwReferenceParser()
{
    if (m_parserNodeData)
        free(m_parserNodeData);
}

void SwReferenceParser::Reset()
{
    m_parserNodePos = 0;
    m_referenceArray.Reset();
}

void SwReferenceParser::SetArrayIncrement(swUI16 increment)
{
    if (increment < 25)
        m_parserInc = 25;
    else
        m_parserInc = increment;
}

bool SwReferenceParser::IncreaseParserNodeArray()
{
    swUI32 increase = m_parserInc;

    if (!m_parserInc)
        increase = 100;

    return SizeParserNodeArray(m_parserNodesAllocated + increase);
}

bool SwReferenceParser::SizeParserNodeArray(swUI32 nodes)
{
    if (!nodes && m_parserNodeData)
    {
        free(m_parserNodeData);
        m_parserNodeData = NULL;
        m_parserNodePos = 0;
        m_parserNodesAllocated = 0;
        return true;
    }

    if (nodes >= NODE_ID_INVALID)
        return false;

    SwReferenceParserNodeData * p = (SwReferenceParserNodeData *) realloc((void *) m_parserNodeData, nodes * sizeof(SwReferenceParserNodeData));

    if (p)
    {
        m_parserNodesAllocated = nodes;
        m_parserNodeData = p;
        return true;
    }

    return false;
}

bool SwReferenceParser::VerifyParserNode()
{
    if (m_parserNodePos >= m_parserNodesAllocated && !IncreaseParserNodeArray())
        return false;

    return true;
}

bool SwReferenceParser::VerifyParserNodes(swUI32 nodes)
{
    if (nodes + m_parserNodePos + 1 > m_parserNodesAllocated && !SizeParserNodeArray(nodes + m_parserNodePos + 1 + m_parserInc))
        return false;

    return true;
}

bool SwReferenceParser::Parse()
{
    SwString value;
    m_parserNodePos = 0;
    swUI32 dataPos = 0;
    swUI32 size = Strlen();

    while (dataPos < size)
    {
        if (!VerifyParserNode())
            return false;

        m_parserNodeData[m_parserNodePos].beginPos = dataPos;
        m_parserNodeData[m_parserNodePos].endPos = dataPos;
        m_parserNodeData[m_parserNodePos].nodeType = 0;

        if (m_array[dataPos] == m_cvdiv && m_cvdiv == m_div)
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_REF_CV_DIV_COMP;
            dataPos ++;
            m_parserNodePos ++;
            continue;
        }
        else if (m_array[dataPos] == m_cvdiv)
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_REF_CVDIV;
            dataPos ++;
            m_parserNodePos ++;
            continue;
        }
        else if (m_array[dataPos] == m_div)
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_REF_DIV;
            dataPos ++;
            m_parserNodePos ++;
            continue;
        }
        else if (m_array[dataPos] == m_span)
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_REF_SPAN;
            dataPos ++;
            m_parserNodePos ++;
            continue;
        }
        else if (m_array[dataPos] == m_break)
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_REF_BREAK;
            dataPos ++;
            m_parserNodePos ++;
            continue;
        }
        else if (m_array[dataPos] == L'\n' || m_array[dataPos] == L'\r')
        {
            if (!m_linebreakisspace)
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_LINE_BREAK;
            else
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_SPACE;

            for (; dataPos < m_size; dataPos ++)
            {
                if (m_array[dataPos] != L'\n' && m_array[dataPos] != L'\r')
                    break;
            }

            m_parserNodeData[m_parserNodePos].endPos = dataPos - 1;
            m_parserNodePos ++;
            continue;
        }
        else if (iswspace(m_array[dataPos]))
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_SPACE;

            for (; dataPos < m_size; dataPos ++)
            {
                if (!iswspace(m_array[dataPos]))
                    break;
            }

            m_parserNodeData[m_parserNodePos].endPos = dataPos - 1;
            m_parserNodePos ++;
            continue;
        }
        else if (iswdigit(m_array[dataPos]))
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_NUMERIC;

            for (; dataPos < m_size; dataPos ++)
            {
                if (!iswdigit(m_array[dataPos]))
                    break;
            }

            m_parserNodeData[m_parserNodePos].endPos = dataPos - 1;
            m_parserNodePos ++;
            continue;
        }
        else if (iswalpha(m_array[dataPos]))
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_ALPHA;

            for (; dataPos < m_size; dataPos ++)
            {
                if (!iswalpha(m_array[dataPos]))
                    break;
            }

            m_parserNodeData[m_parserNodePos].endPos = dataPos - 1;

            bool isroman = true;
            for (swUI32 i = m_parserNodeData[m_parserNodePos].beginPos; i <= m_parserNodeData[m_parserNodePos].endPos; i ++)
            {
                if (!IsRoman(i))
                {
                    isroman = false;
                    break;
                }
            }

            if (isroman)
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_ALPHA_ROMAN;

            m_parserNodePos ++;
            continue;
        }
        else
        {
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_SYMBOL;

            for (; dataPos < size; dataPos ++)
            {
                if (IsMarker(m_array[dataPos]) || iswspace(m_array[dataPos]) || iswdigit(m_array[dataPos]) || iswalpha(m_array[dataPos]))
                    break;
            }

            m_parserNodeData[m_parserNodePos].endPos = dataPos - 1;
            m_parserNodePos ++;
            continue;
        }
    }

    return true;
}

swUI32 SwReferenceParser::GetLastParserNode()
{
    return m_parserNodePos -1;
}

swUI32 SwReferenceParser::GetParserNodes()
{
    return m_parserNodePos;
}

void SwReferenceParser::UpdateNodePosData(swUI32 nodeStart, swUI32 change, bool type)
{
    // type == true for increase, type == false for decrease
    swUI32 pos = 0;
    pos = nodeStart;
    if (type)
    {
        while (pos < m_parserNodePos)
        {
            m_parserNodeData[pos].beginPos += change;
            m_parserNodeData[pos].endPos += change;

            pos ++;
        }
    }
    else
    {
        while (pos < m_parserNodePos)
        {
            m_parserNodeData[pos].beginPos -= change;
            m_parserNodeData[pos].endPos -= change;

            pos ++;
        }
    }
}

swUI8 SwReferenceParser::GetNodeType(swUI32 node)
{
    if (node >= m_parserNodePos)
        return NODE_TYPE_INVALID;

    return m_parserNodeData[node].nodeType;
}

void SwReferenceParser::SetNodeType(swUI32 node, swUI8 type)
{
    if (node >= m_parserNodePos)
        return;

    m_parserNodeData[node].nodeType = type;
}

swUI32 SwReferenceParser::GetNodeStreamPosition(swUI32 node)
{
    if (node >= m_parserNodePos)
        return 0;

    return m_parserNodeData[node].beginPos;
}

swUI32 SwReferenceParser::GetNodeDataSize(swUI32 node)
{
    if (node >= m_parserNodePos)
        return 0;

    return (m_parserNodeData[node].endPos - m_parserNodeData[node].beginPos) + 1;
}

swUI32 SwReferenceParser::GetNodesDataSize(swUI32 nodeBegin, swUI32 nodeEnd)
{
    if (nodeBegin >= m_parserNodePos || nodeEnd >= m_parserNodePos || nodeBegin > nodeEnd)
        return 0;

    return (m_parserNodeData[nodeEnd].endPos - m_parserNodeData[nodeBegin].beginPos) + 1;
}

SwReferenceParserNodeData * SwReferenceParser::GetNode(swUI32 node)
{
    if (node >= m_parserNodePos)
        return NULL;

    return &m_parserNodeData[node];
}

bool SwReferenceParser::GetNodeData(swUI32 node, SwStringW & dest)
{
    if (node >= m_parserNodePos)
        return false;

    if (!dest.Size(GetNodeDataSize(node) + 1))
        return false;

    dest.SetAt(0, L'\0');

    wmemcpy(dest, m_array + m_parserNodeData[node].beginPos, GetNodeDataSize(node));
    dest.SetAt(GetNodeDataSize(node), L'\0');

    return true;
}

bool SwReferenceParser::GetNodesData(swUI32 nodeBegin, swUI32 nodeEnd, SwStringW & dest)
{
    if (nodeBegin >= m_parserNodePos || nodeEnd > m_parserNodePos || nodeBegin > nodeEnd)
        return false;

    if (!dest.Size(GetNodesDataSize(nodeBegin, nodeEnd) + 1))
        return false;

    dest.SetAt(0, L'\0');

    wmemcpy(dest, m_array + m_parserNodeData[nodeBegin].beginPos, GetNodesDataSize(nodeBegin, nodeEnd));
    dest.SetAt(GetNodesDataSize(nodeBegin, nodeEnd), L'\0');

    return true;
}

swUI32 SwReferenceParser::FindNodeByStreamPos(swUI32 streamPos)
{
    if (streamPos >= m_size)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (streamPos >= GetNodeStreamPosition(i) && streamPos < GetNodeStreamPosition(i) + GetNodeDataSize(i))
            return i;
    }

    return NODE_ID_INVALID;
}

void SwReferenceParser::SetOptions(wchar_t _cvdiv, wchar_t _span, wchar_t _div, wchar_t _break, bool romanforchapters, bool romanforverses, bool romanlowercase, bool linebreakisspace, bool firstletteruc)
{
    m_cvdiv = _cvdiv;
    m_span = _span;
    m_div = _div;
    m_break = _break;
    m_romanforchapters = romanforchapters;
    m_romanforverses = romanforverses;
    m_romanlowercase = romanlowercase;
    m_linebreakisspace = linebreakisspace;
    m_firstletteruc = firstletteruc;
}

void SwReferenceParser::SetCVDivMarker(wchar_t marker)
{
    m_cvdiv = marker;
}

void SwReferenceParser::SetSpanMarker(wchar_t marker)
{
    m_span = marker;
}

void SwReferenceParser::SetDivMarker(wchar_t marker)
{
    m_div = marker;
}

void SwReferenceParser::SetBreakMarker(wchar_t marker)
{
    m_break = marker;
}

void SwReferenceParser::SetRomanForChapters(bool state)
{
    m_romanforchapters = state;
}

void SwReferenceParser::SetRomanForVerses(bool state)
{
    m_romanforverses = state;
}

void SwReferenceParser::SetRomanLowerCase(bool state)
{
    m_romanlowercase = state;
}

void SwReferenceParser::SetLineBreakIsSpace(bool state)
{
    m_linebreakisspace = state;
}

void SwReferenceParser::SetFirstLetterUpperCase(bool state)
{
    m_firstletteruc = state;
}

swUI8 SwReferenceParser::GetValue(swUI32 node)
{
    SwStringW buffer;

    if (!GetNodeData(node, buffer))
        return 0;

    if (GetNodeType(node) == NODE_TYPE_ALPHA_ROMAN)
        return (swUI8) buffer.ConvertRoman();
    else if (GetNodeType(node) == NODE_TYPE_NUMERIC)
        return (swUI8) buffer.Strtoul();

    return 0;
}

bool SwReferenceParser::IsMarker(wchar_t ch)
{
    if (ch == m_cvdiv || ch == m_span || ch == m_div || ch == m_break)
        return true;

    return false;
}

bool SwReferenceParser::IsNodeWhiteSpace(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_SPACE)
        return true;
    if (m_linebreakisspace && GetNodeType(node) == NODE_TYPE_LINE_BREAK)
        return true;

    return false;
}

swUI32 SwReferenceParser::FindWhiteSpaceEnd(swUI32 node)
{
    for (swUI32 n = node; n < GetParserNodes(); n ++)
    {
        if (!IsNodeWhiteSpace(n))
            return n;
    }

    return node;
}

bool SwReferenceParser::CouldNodeBeNumber(swUI32 node)
{
    if (((m_romanforchapters || m_romanforverses) && GetNodeType(node) == NODE_TYPE_ALPHA_ROMAN) || GetNodeType(node) == NODE_TYPE_NUMERIC)
        return true;

    return false;
}

bool SwReferenceParser::IsValidForChapterNumber(swUI32 node)
{
    if (m_romanforchapters && GetNodeType(node) == NODE_TYPE_ALPHA_ROMAN)
    {
        if (m_romanlowercase)
            return IsLowerRoman(node);

        return true;
    }
    else if (!m_romanforchapters && GetNodeType(node) == NODE_TYPE_NUMERIC)
        return true;

    return false;
}

bool SwReferenceParser::IsValidForVerseNumber(swUI32 node)
{
    if (m_romanforverses && GetNodeType(node) == NODE_TYPE_ALPHA_ROMAN)
    {
        if (m_romanlowercase)
            return IsLowerRoman(node);

        return true;
    }
    else if (!m_romanforverses && GetNodeType(node) == NODE_TYPE_NUMERIC)
        return true;

    return false;
}

bool SwReferenceParser::IsLowerRoman(swUI32 node)
{
    SwStringW buffer;

    if (GetNodeType(node) != NODE_TYPE_ALPHA_ROMAN)
        return false;

    GetNodeData(node, buffer);

    for (swUI32 i = 0; i < buffer.Strlen(); i ++)
    {
        if (!iswlower(buffer.GetAt(i)))
            return false;
    }

    return true;
}

swUI8 SwReferenceParser::IdentifyBook(swUI32 & node)
{
    SwStringW buffer;
    GetNodeData(node, buffer);

    if (m_firstletteruc && !iswupper(buffer.GetAt(0)))
        return 0;

    buffer.ToLower();
    swUI8 book = SwStandardBible::IdentifyBibleBookName(buffer);

    if (!book)
    {
        // For books with numbers preceding the name.
        if (node == 0)
            return 0;
        else if (node == 1)
        {
            node = 0;
            GetNodesData(0, 1, buffer);
            buffer.ToLower();
            return SwStandardBible::IdentifyBibleBookName(buffer);
        }
        else
        {
            GetNodesData(node - 2, node, buffer);
            node = node - 2;
            if (m_linebreakisspace)
                buffer.Replace(L"\r\n", 2, L" ", 1);
            buffer.Replace(L"  ", 2, L" ", 1);
            buffer.ToLower();
            return SwStandardBible::IdentifyBibleBookName(buffer);
        }
    }

    return book;
}

swUI32 SwReferenceParser::Oncvdiv(swUI32 node)
{
    return node;
}

swUI32 SwReferenceParser::Ondiv(swUI32 node)
{
    if (m_hasRef && m_hasAdditions)
    {
        m_refItem.end = GetNode(node)->beginPos;
        m_referenceArray.Add(m_refItem);
        m_primaryRefAdded = true;
        m_refItem.verseStart = 0;
        m_refItem.verseEnd = 0;
        m_hasSpan = false;
        m_hasAdditions = false;
    }

    return node;
}

swUI32 SwReferenceParser::Oncvdivcomp(swUI32 node)
{
    if (m_hasRef && m_refItem.chapter && m_refItem.verseStart)
    {
        m_refItem.end = GetNode(node)->beginPos;
        m_referenceArray.Add(m_refItem);
        m_primaryRefAdded = true;
        m_refItem.verseStart = 0;
        m_refItem.verseEnd = 0;
        m_hasSpan = false;
        m_hasAdditions = false;
    }

    return node;
}

swUI32 SwReferenceParser::Onspan(swUI32 node)
{
    if (m_hasRef)
        m_hasSpan = true;

    return node;
}

swUI32 SwReferenceParser::Onbreak(swUI32 node)
{
    if (m_hasRef && m_hasAdditions && m_refItem.chapter)
    {
        m_refItem.end = GetNode(node)->beginPos;
        m_referenceArray.Add(m_refItem);
        m_primaryRefAdded = true;
        m_refItem.begin = GetNode(node)->endPos + 1;
        if (GetNodeType(node + 1) == NODE_TYPE_SPACE)
            m_refItem.begin = GetNode(node + 1)->endPos + 1;
        m_refItem.chapter = 0;
        m_refItem.verseStart = 0;
        m_refItem.verseEnd = 0;
        m_hasSpan = false;
        m_hasAdditions = false;
    }

    return node;
}

swUI32 SwReferenceParser::Onspace(swUI32 node)
{
    return node;
}

swUI32 SwReferenceParser::Onalpha(swUI32 node)
{
    swUI32 node2;

    if (m_hasRef && m_hasAdditions && m_refItem.chapter)
    {
        if (GetNodeType(node - 1) == NODE_TYPE_SPACE)
            m_refItem.end = GetNode(node - 1)->beginPos;
        else
            m_refItem.end = GetNode(node)->beginPos;

        m_referenceArray.Add(m_refItem);
        m_refItem.Reset();
        m_hasRef = false;
        m_hasSpan = false;
        m_primaryRefAdded = false;
        m_hasAdditions = false;
    }

    if (IsNodeWhiteSpace(node + 1))
    {
        node2 = FindWhiteSpaceEnd(node + 1);
        if (CouldNodeBeNumber(node2))
        {
            swUI32 start = node;
            swUI8 book = IdentifyBook(start);

            if (book)
            {
                if (/* Assume unrecognized books have more than one chapter */ book <= 66 && SwStandardBible::IsSingleChapterBook(book))
                {
                    if (!IsValidForVerseNumber(node2))
                        return node;

                    m_refItem.chapter = 1;
                }
                else
                {
                    if (!IsValidForChapterNumber(node2))
                        return node;
                }

                m_hasRef = true;
                m_hasSpan = false;
                m_primaryRefAdded = false;
                m_hasAdditions = false;
                m_refItem.book = book;
                m_refItem.begin = GetNode(start)->beginPos;
            }
            else
            {
                m_refItem.Reset();
                m_hasRef = false;
                m_hasSpan = false;
                m_primaryRefAdded = false;
                m_hasAdditions = false;
            }
        }
    }
    else
    {
        m_refItem.Reset();
        m_hasRef = false;
        m_hasSpan = false;
        m_primaryRefAdded = false;
        m_hasAdditions = false;
    }

    return node;
}

swUI32 SwReferenceParser::Onalpharoman(swUI32 node)
{
    if (!m_hasRef)
    {
        return node;
    }
    else if (m_romanforchapters && !m_refItem.chapter)
    {
        m_hasAdditions = true;
        m_refItem.chapter = GetValue(node);
        if (m_primaryRefAdded)
        {
            m_refItem.begin = GetNode(node)->beginPos;
            m_primaryRefAdded = false;
        }
        m_refItem.end = GetNode(node)->endPos + 1;
    }
    else if (m_romanforverses && !m_refItem.verseStart)
    {
        m_hasAdditions = true;
        m_refItem.verseStart = GetValue(node);
        if (m_primaryRefAdded)
            m_refItem.begin = GetNode(node)->beginPos;
        m_refItem.end = GetNode(node)->endPos + 1;
    }
    else if (m_romanforverses && !m_refItem.verseEnd && m_hasSpan)
    {
        m_hasAdditions = true;
        m_refItem.verseEnd = GetValue(node);
        m_refItem.end = GetNode(node)->endPos + 1;
    }

    return node;
}

swUI32 SwReferenceParser::Onnumeric(swUI32 node)
{
    if (!m_hasRef)
    {
        return node;
    }
    else if (!m_romanforchapters && !m_refItem.chapter)
    {
        m_hasAdditions = true;
        m_refItem.chapter = GetValue(node);
        if (m_primaryRefAdded)
        {
            m_refItem.begin = GetNode(node)->beginPos;
            m_primaryRefAdded = false;
        }

        m_refItem.end = GetNode(node)->endPos + 1;
    }
    else if (!m_romanforverses && !m_refItem.verseStart)
    {
        m_hasAdditions = true;
        m_refItem.verseStart = GetValue(node);
        if (m_primaryRefAdded)
            m_refItem.begin = GetNode(node)->beginPos;
        m_refItem.end = GetNode(node)->endPos + 1;
    }
    else if (!m_romanforverses && !m_refItem.verseEnd && m_hasSpan)
    {
        m_hasAdditions = true;
        m_refItem.verseEnd = GetValue(node);
        m_refItem.end = GetNode(node)->endPos + 1;
    }

    return node;
}

swUI32 SwReferenceParser::Onsymbol(swUI32 node)
{
    if (m_hasRef && m_hasAdditions)
    {
        if (GetNodeType(node - 1) == NODE_TYPE_SPACE)
            m_refItem.end = GetNode(node - 1)->beginPos;
        else
            m_refItem.end = GetNode(node)->beginPos;

        m_referenceArray.Add(m_refItem);
        m_refItem.Reset();
        m_hasRef = false;
        m_hasSpan = false;
        m_primaryRefAdded = false;
        m_hasAdditions = false;
    }

    return node;
}

swUI32 SwReferenceParser::Onlinebreak(swUI32 node)
{
    if (m_hasRef && m_hasAdditions && !m_linebreakisspace)
    {
        m_refItem.end = GetNode(node)->beginPos;
        m_referenceArray.Add(m_refItem);
        m_refItem.Reset();
        m_hasRef = false;
        m_hasSpan = false;
        m_primaryRefAdded = false;
        m_hasAdditions = false;
    }

    return node;
}

bool SwReferenceParser::Run()
{
    m_refItem.Reset();
    m_hasRef = false;
    m_hasSpan = false;
    m_hasAdditions = false;
    m_primaryRefAdded = false;

    for (swUI32 node = 0; node < GetParserNodes(); node ++)
    {
        (this->*m_handlers[GetNode(node)->nodeType])(node);
    }

    if (m_hasRef && m_hasAdditions)
        m_referenceArray.Add(m_refItem);

    return (bool) m_referenceArray.GetCount();
}

void SwReferenceParser::WriteReferenceMarkUp()
{
    Size(Strlen() + 4096);
    wchar_t buff[1024];

    for (swI64 i = m_referenceArray.GetCount() - 1; i >= 0; i --)
    {
        Insert(m_referenceArray.GetAt(i).end, L"</scripRef>");

        if (m_referenceArray.GetAt(i).chapter && m_referenceArray.GetAt(i).verseStart && m_referenceArray.GetAt(i).verseEnd)
        {
#if defined __MSWIN__
            swprintf(buff, L"<scripRef passage=\"%S %u:%u-%u\">", SwThMLUtility::GetThMLBookIdStringW(m_referenceArray.GetAt(i).book), m_referenceArray.GetAt(i).chapter, m_referenceArray.GetAt(i).verseStart, m_referenceArray.GetAt(i).verseEnd);
#else
            swprintf(buff, 1024, L"<scripRef id=\"%S %u:%u-%u\">", SwThMLUtility::GetThMLBookIdStringW(m_referenceArray.GetAt(i).book), m_referenceArray.GetAt(i).chapter, m_referenceArray.GetAt(i).verseStart, m_referenceArray.GetAt(i).verseEnd);
#endif
        }
        else if (m_referenceArray.GetAt(i).chapter && m_referenceArray.GetAt(i).verseStart)
        {
#if defined __MSWIN__
            swprintf(buff, L"<scripRef passage=\"%S %u:%u\">", SwThMLUtility::GetThMLBookIdStringW(m_referenceArray.GetAt(i).book), m_referenceArray.GetAt(i).chapter, m_referenceArray.GetAt(i).verseStart);
#else
            swprintf(buff, 1024, L"<scripRef id=\"%S %u:%u-%u\">", SwThMLUtility::GetThMLBookIdStringW(m_referenceArray.GetAt(i).book), m_referenceArray.GetAt(i).chapter, m_referenceArray.GetAt(i).verseStart);
#endif
        }
        else
        {
#if defined __MSWIN__
            swprintf(buff, L"<scripRef passage=\"%S %u\">", SwThMLUtility::GetThMLBookIdStringW(m_referenceArray.GetAt(i).book), m_referenceArray.GetAt(i).chapter);
#else
            swprintf(buff, 1024, L"<scripRef id=\"%S %u\">", SwThMLUtility::GetThMLBookIdStringW(m_referenceArray.GetAt(i).book), m_referenceArray.GetAt(i).chapter);
#endif
        }

        Insert(m_referenceArray.GetAt(i).begin, buff);
    }
}
