///////////////////////////////////////////////////////////////////
// Name:        thml_parser.cpp
// Purpose:     Parser for xml/html documents, with functionality
//              specific to ThML.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thml_parser.h"
#include "../../include/thml/thml_utility.h"
#include "../../include/filesys/file.h"
#include "../../include/string/string.h"
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

SwThMLParser::SwThMLParser()
{
    m_extraBytes = 2048;
    m_modified = false;
    m_parserNodeData = NULL;
    m_parserNodePos = 0;
    m_parserNodesAllocated = 0;
    m_parserInc = 100;
    m_buffer = NULL;
    m_bufferSize = 0;
    m_dataSize = 0;
    m_sourceBuffer = NULL;
    m_file = NULL;
    m_path = NULL;
    m_base = NULL;
    m_mode = MODE_MEMORY;
    m_elementAlphaIdx = NULL;
    m_elementArray = NULL;
    m_elementItems = 0;
    m_processtableData = false;
    m_processXmlId = false;
    m_markupType = MARKUP_UNKNOWN;
    SetThML_ElementArray();

    m_progress = NULL;
    m_window = NULL;
}

SwThMLParser::~SwThMLParser()
{
    if (m_buffer)
        free(m_buffer);

    if (m_parserNodeData)
        free(m_parserNodeData);

    if (m_path)
        free(m_path);

    if (m_file)
        fclose(m_file);

    if (m_base)
        free(m_base);
}

bool SwThMLParser::OpenFile(const char * path, swUI8 mode, bool processtableData)
{
    if (!path || !CloseFile())
        return false;

    m_mode = mode;
    m_modified = false;

    if (!SwFile::DoesExist(path))
        return false;

    if (mode == MODE_FS_CONTWR)
        m_file = SwFopen(path, FMD_RW);
    else if (mode == MODE_FS_INT || mode == MODE_MEMORY || mode == MODE_FS_CONT)
        m_file = SwFopen(path, FMD_R);

    if (!m_file)
        return false;

    swUI32 fileSize = SwFile::GetSize(path);
    if (m_bufferSize <= fileSize && !SizeBuffer(fileSize + 1 + m_extraBytes))
        return false;

    if (fread((void *) m_buffer, 1, fileSize, m_file) != fileSize)
    {
        fclose(m_file);
        m_file = NULL;
        return false;
    }

    m_buffer[fileSize] = '\0';
    m_sourceBuffer = m_buffer;
    m_dataSize = fileSize;

    if (!Parse(NULL))
        return false;

    if (mode == MODE_FS_CONT || mode == MODE_FS_CONTWR || mode == MODE_FS_INT)
        SizeBuffer(0);

    if (mode == MODE_MEMORY || mode == MODE_FS_INT)
    {
        fclose(m_file);
        m_file = NULL;
    }

    m_processtableData = processtableData;

    if (!UpdateNodeData())
        return false;

    SetPath(path);
    SetBasePath(path);
    SwClipFileName(m_base);

    return true;
}

bool SwThMLParser::Load(const char * source, swUI32 size)
{
    if (!source || !CloseFile())
        return false;

    if (m_bufferSize <=  size && !SizeBuffer(size + 1 + m_extraBytes))
        return false;

    memcpy(m_buffer, source, size);
    m_buffer[size] = '\0';
    m_sourceBuffer = m_buffer;
    m_dataSize = size;
    m_mode = MODE_MEMORY;
    m_modified = false;
    m_processtableData = true;

    if (!Parse(NULL))
        return false;

    if (!UpdateNodeData())
        return false;

    return true;
}

bool SwThMLParser::Load(FILE * source, swUI32 size)
{
    if (!source || !CloseFile())
        return false;

    if (m_bufferSize <=  size && !SizeBuffer(size + 1 + m_extraBytes))
        return false;

    if (fread(m_buffer, 1, size, source) != size)
        return false;

    m_buffer[size] = '\0';
    m_sourceBuffer = m_buffer;
    m_dataSize = size;
    m_mode = MODE_MEMORY;
    m_modified = false;
    m_processtableData = true;

    if (!Parse(NULL))
        return false;

    if (!UpdateNodeData())
        return false;

    return true;
}

bool SwThMLParser::CloseFile(bool freeResources)
{
    if (!VerifyClose())
        return false;

    if (freeResources)
    {
        SizeBuffer(0);
        SizeParserNodeArray(0);
    }
    else if (m_buffer)
        m_buffer[0] = '\0';

    m_parserNodePos = 0;
    m_dataSize = 0;
    m_sourceBuffer = NULL;

    // File access functions may not be setting m_file to NULL after closing file.
    if (m_file && m_mode != MODE_FS_INT)
        fclose(m_file);

    if (m_path)
        free(m_path);

    if (m_base)
        free(m_base);

    m_path = NULL;
    m_base = NULL;
    m_file = NULL;
    m_mode = MODE_MEMORY;
    m_modified = false;
    m_processtableData = false;
    Reset();
    return true;
}

bool SwThMLParser::VerifyClose()
{
    return true;
}

void SwThMLParser::Reset()
{
    m_parserNodePos = 0;
    SetPath("");
    SetBasePath("");
}

bool SwThMLParser::SaveFile()
{
    if (!GetPath())
        return false;

    return SaveFile(GetPath());
}

// This does not set the path variable for SwThMLParser. If that is required call SetPath, SetBasePath.
bool SwThMLParser::SaveFile(const char * path)
{
    FILE * file = NULL;

    if (m_mode != MODE_MEMORY)
        return false;

    if (path)
    {
        file = SwFopen(path, FMD_WC);
    }

    if (!file)
        return false;

    if (fwrite(m_sourceBuffer, 1, m_dataSize, file) != m_dataSize)
    {
        fclose(file);
        return false;
    }

    fclose(file);

    return true;
}

bool SwThMLParser::GetModified()
{
    return m_modified;
}

void SwThMLParser::SetModified(bool modified)
{
    m_modified = modified;
}

bool SwThMLParser::SizeBuffer(swUI32 bytes)
{
    if (!bytes && m_buffer)
    {
        if (m_sourceBuffer == m_buffer)
            m_sourceBuffer = NULL;

        free(m_buffer);
        m_buffer = NULL;
        m_bufferSize = 0;
        return true;
    }

    char * p = (char *) realloc((void *) m_buffer, bytes);

    if (p)
    {
        if (m_sourceBuffer == m_buffer)
            m_sourceBuffer = p;

        m_bufferSize = bytes;
        m_buffer = p;
        return true;
    }

    return false;
}

void SwThMLParser::SetArrayIncrement(swUI16 increment)
{
    if (increment < 25)
        m_parserInc = 25;
    else
        m_parserInc = increment;
}

swUI32 SwThMLParser::PrecountTags(const char * src)
{
    if (!src)
        return 0;

    swUI32 tags = 0, pos = 0;
    bool lastwasend = false;
    while (src[pos] != '\0')
    {
        if (src[pos] == '<')
        {
            tags ++;
            lastwasend = false;
        }
        else if (src[pos] == '>')
        {
            lastwasend = true;
        }
        else if (lastwasend && !isspace(src[pos]))
        {
            lastwasend = false;
            tags ++;
        }

        pos ++;
    }

    return tags;
}

bool SwThMLParser::IncreaseParserNodeArray()
{
    swUI32 increase = m_parserInc;

    if (!m_parserInc)
        increase = 100;

    return SizeParserNodeArray(m_parserNodesAllocated + increase);
}

bool SwThMLParser::SizeParserNodeArray(swUI32 nodes)
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

    SwParserNodeData * p = (SwParserNodeData *) realloc((void *) m_parserNodeData, nodes * sizeof(SwParserNodeData));

    if (p)
    {
        m_parserNodesAllocated = nodes;
        m_parserNodeData = p;
        return true;
    }

    return false;
}

bool SwThMLParser::VerifyParserNodes(swUI32 nodes)
{
    if (nodes + m_parserNodePos + 1 > m_parserNodesAllocated && !SizeParserNodeArray(nodes + m_parserNodePos + 1 + m_parserInc))
        return false;

    return true;
}

bool SwThMLParser::Parse(const char * source, swUI32 size)
{
    SwString value;
    bool binaryFlag = false;
    m_parserNodePos = 0;
    int dataPos = 0;
    swUI32 i;

    swUI8 elementType = 0;
    swUI8 whiteSpace = 0;

    if (!m_dataSize && !source)
        return false;

    if (!m_elementArray || !m_elementItems || !m_elementAlphaIdx)
        return false;

    if (source)
    {
        m_mode = MODE_MEMORY;
        m_sourceBuffer = source;

        if (size)
            m_dataSize = size;
        else
            m_dataSize = strlen(source);
    }
    else
        m_sourceBuffer = m_buffer;

    swUI32 tags = PrecountTags(m_sourceBuffer);

    SetRange(tags);

    tags += tags / 3;

    if (m_parserNodesAllocated < tags)
        SizeParserNodeArray(tags);

    while(m_sourceBuffer[dataPos] != '\0' && isspace(m_sourceBuffer[dataPos]))
        dataPos ++;

    while (m_sourceBuffer[dataPos] != '\0')
    {
        if (!VerifyParserNode())
            return false;

        m_parserNodeData[m_parserNodePos].xmlId = 0;
        m_parserNodeData[m_parserNodePos].param1 = 0;
        m_parserNodeData[m_parserNodePos].param2 = 0;
        m_parserNodeData[m_parserNodePos].param3 = false;
        m_parserNodeData[m_parserNodePos].nodeMate = NODE_ID_INVALID;
        m_parserNodeData[m_parserNodePos].nodeParent = NODE_ID_INVALID;
        m_parserNodeData[m_parserNodePos].nodeFirstChild = NODE_ID_INVALID;
        m_parserNodeData[m_parserNodePos].nodeNextSibling = NODE_ID_INVALID;

        // Identifies White Space
        if (m_sourceBuffer[dataPos] == '<' && m_parserNodePos > 0 && m_parserNodeData[m_parserNodePos - 1].nodeType == NODE_TYPE_TEXT_RUN)
        {
            m_parserNodeData[m_parserNodePos - 1].endPos = dataPos - 1;
            i = m_parserNodeData[m_parserNodePos - 1].beginPos;

            while (i <= m_parserNodeData[m_parserNodePos - 1].endPos)
            {
                if (!isspace(m_sourceBuffer[i]))
                    break;

                i ++;
            }

            if (i > m_parserNodeData[m_parserNodePos - 1].endPos)
            {
                m_parserNodeData[m_parserNodePos - 1].elementIdentifier = INT_WHITE_SPACE;
                m_parserNodeData[m_parserNodePos - 1].nodeType = NODE_TYPE_WHITE_SPACE;
            }
        }

        m_parserNodeData[m_parserNodePos].beginPos = dataPos;
        m_parserNodeData[m_parserNodePos].endPos = dataPos;
        // Tags
        if (m_sourceBuffer[dataPos] == '<')
        {
            if (!UpdateUI(m_parserNodePos))
                return false;

            m_parserNodeData[m_parserNodePos].elementIdentifier = IdentifyElement(&m_sourceBuffer[dataPos]);

            while (m_sourceBuffer[dataPos] != '>' && m_sourceBuffer[dataPos] != '\0')
                dataPos ++;

            if (m_sourceBuffer[m_parserNodeData[m_parserNodePos].beginPos + 1] == '/')
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_END_TAG;
            else if (m_sourceBuffer[dataPos -1] == '/' || m_sourceBuffer[dataPos -1] == '?' || m_sourceBuffer[dataPos -1] == '-')
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_UNPAIRED_TAG;
            else
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_BEGIN_TAG;

            // INT_BINARY
            if (m_parserNodeData[m_parserNodePos].elementIdentifier == INT_BINARY && m_parserNodeData[m_parserNodePos].nodeType == NODE_TYPE_BEGIN_TAG)
            {
                binaryFlag = true;
                m_parserNodeData[m_parserNodePos].endPos = dataPos;
                if (m_processXmlId)
                    m_parserNodeData[m_parserNodePos].xmlId = GetXmlId(m_parserNodeData[m_parserNodePos].beginPos, m_parserNodeData[m_parserNodePos].endPos);
                m_parserNodePos ++;

                if (m_parserNodePos == 0 || !GetNamedValueFromNode(m_parserNodePos - 1, "size", value))
                    return false;

                if (!VerifyParserNode())
                    return false;

                m_parserNodeData[m_parserNodePos].elementIdentifier = INT_BINARY;
                m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_BINARY;
                m_parserNodeData[m_parserNodePos].beginPos = dataPos + 1;
                m_parserNodeData[m_parserNodePos].endPos = dataPos + atoi(value);
                dataPos = m_parserNodeData[m_parserNodePos].endPos;
                m_parserNodePos ++;
            }
            else
            {
                // Treat unknown tags as inline.
                if (m_parserNodeData[m_parserNodePos].elementIdentifier >= INT_UNKNOWN)
                {
                    elementType = ELEMENT_TYPE_INLINE;
                    whiteSpace = WHITE_SPACE_NORMAL;
                }
                else
                {
                    elementType = m_elementArray[m_parserNodeData[m_parserNodePos].elementIdentifier].elementType;
                    whiteSpace = m_elementArray[m_parserNodeData[m_parserNodePos].elementIdentifier].whiteSpace;
                }

                if (elementType != ELEMENT_TYPE_INLINE && (((m_parserNodeData[m_parserNodePos].nodeType == NODE_TYPE_END_TAG ||
                        m_parserNodeData[m_parserNodePos].nodeType == NODE_TYPE_UNPAIRED_TAG) &&
                        (elementType == ELEMENT_TYPE_BLOCK || elementType ==  ELEMENT_TYPE_BREAK)) ||
                        (m_parserNodeData[m_parserNodePos].nodeType == NODE_TYPE_BEGIN_TAG && whiteSpace == WHITE_SPACE_NORMAL)))
                    while (isspace(m_sourceBuffer[dataPos+1]) && m_sourceBuffer[dataPos] != '\0')
                        dataPos ++;
            }

            if (!binaryFlag)
            {
                m_parserNodeData[m_parserNodePos].endPos = dataPos;
                if (m_processXmlId)
                    m_parserNodeData[m_parserNodePos].xmlId = GetXmlId(m_parserNodeData[m_parserNodePos].beginPos, m_parserNodeData[m_parserNodePos].endPos);
                m_parserNodePos ++;
            }

            binaryFlag = false;
        } // Text Runs
        else if (m_parserNodePos == 0 || (m_parserNodePos > 0 && m_parserNodeData[m_parserNodePos - 1].nodeType != NODE_TYPE_TEXT_RUN))
        {
            m_parserNodeData[m_parserNodePos].elementIdentifier = INT_TEXT_RUN;
            m_parserNodeData[m_parserNodePos].beginPos = dataPos;
            m_parserNodeData[m_parserNodePos].endPos = dataPos;
            m_parserNodeData[m_parserNodePos].nodeType = NODE_TYPE_TEXT_RUN;
            m_parserNodePos ++;
        }

        if (m_sourceBuffer[dataPos] == '\0')
            break;

        dataPos ++;
    }

    SetRange(m_parserNodePos);
    return true;
}

bool SwThMLParser::DoesNodeBeginThMLDiv(swUI32 node)
{
    if (m_markupType != MARKUP_THML || node >= m_parserNodePos)
        return false;

    if (m_parserNodeData[node].nodeType != NODE_TYPE_BEGIN_TAG)
        return false;

    return IsNodeThMLDiv(node);
}

bool SwThMLParser::IsNodeThMLDiv(swUI32 node)
{
    if (m_markupType != MARKUP_THML || node >= m_parserNodePos)
        return false;

    switch (m_parserNodeData[node].elementIdentifier)
    {
    case THML_DIV1 :
    case THML_DIV2 :
    case THML_DIV3 :
    case THML_DIV4 :
    case THML_DIV5 :
    case THML_DIV6 :
        return true;
        break;
    }

    return false;
}

swUI32 SwThMLParser::GetThMLDivBreakNode(swUI32 nodeStart)
{
    if (m_markupType != MARKUP_THML)
        return nodeStart;

    swUI32 i;
    for (i = nodeStart + 1; i < GetParserNodes(); i ++)
    {
        if (GetNodeElementIdentifier(i) >= THML_DIV1 && GetNodeElementIdentifier(i) <= THML_DIV6)
            break;
    }

    if (IsNodeThMLDiv(i) && GetNodeType(i) == NODE_TYPE_BEGIN_TAG)
        i --;

    return i;
}

bool SwThMLParser::IsTableRow(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)&& element == THML_TR)
        return true;

    return false;
}

bool SwThMLParser::IsTableHeader(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_THEAD)
        return true;

    return false;
}

bool SwThMLParser::IsTableFooter(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_TFOOT)
        return true;

    return false;
}

bool SwThMLParser::IsTableCell(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && (element == THML_TD || element == THML_TH))
        return true;

    return false;
}

bool SwThMLParser::IsTableBody(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_TBODY)
        return true;

    return false;
}

bool SwThMLParser::IsTable(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_TABLE)
        return true;

    return false;
}

bool SwThMLParser::IsImage(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_IMG)
        return true;
    else if (m_markupType == MARKUP_THML && element == THML_IMAGE)
        return true;

    return false;
}

bool SwThMLParser::IsAudio(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_AUDIO)
        return true;

    return false;
}

bool SwThMLParser::IsVideo(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_VIDEO)
        return true;

    return false;
}

bool SwThMLParser::IsPre(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_PRE)
        return true;

    return false;
}

bool SwThMLParser::IsParagraph(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_P)
        return true;

    return false;
}

bool SwThMLParser::IsBlockQuote(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_BLOCKQUOTE)
        return true;

    return false;
}

bool SwThMLParser::IsStandardDiv(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_DIV)
        return true;

    return false;
}

bool SwThMLParser::IsStyle(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && element == THML_STYLE)
        return true;

    return false;
}

bool SwThMLParser::IsInformation(swUI16 element)
{
    if (m_markupType == MARKUP_THML &&
            (element == THML_GENERALINFO ||
             element == THML_PRINTSOURCEINFO ||
             element == THML_ELECTRONICEDINFO))
        return true;

    return false;
}

bool SwThMLParser::IsList(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) && (element == THML_UL ||element == THML_OL ))
        return true;
    else if (m_markupType == MARKUP_THML && element == THML_VERSE)
        return true;

    return false;
}

bool SwThMLParser::IsNote(swUI16 element)
{
    if (m_markupType == MARKUP_THML && element == THML_NOTE)
        return true;

    return false;
}

bool SwThMLParser::IsHeading(swUI16 element)
{
    if ((m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML) &&
            (element == THML_H1 || element == THML_H2 || element == THML_H3 ||
             element == THML_H4 || element == THML_H5 || element == THML_H6))
        return true;
    else if (m_markupType == MARKUP_THML && element == THML_ARGUMENT)
        return true;

    return false;
}

bool SwThMLParser::CountRowCells()
{
    swUI32 indexPos = 0;
    SetRange(m_parserNodePos);

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        CountRowCells(indexPos);

        indexPos ++;
    }

    return true;
}

bool SwThMLParser::CountRowCells(swUI32 node)
{
    if (!IsTableRow(GetNodeElementIdentifier(node)) || GetNodeType(node) != NODE_TYPE_BEGIN_TAG)
        return false;

    swUI32 mate = GetNodeMate(node);
    swUI32 cells = 0;

    m_parserNodeData[node].param1 = 0;

    for (swUI32 nodePos = node + 1; nodePos < mate; nodePos ++)
    {
        if (IsTable(GetNodeElementIdentifier(nodePos)) && GetNodeType(nodePos) == NODE_TYPE_BEGIN_TAG)
        {
            nodePos = GetNodeMate(nodePos);
        }
        else if (IsTableCell(GetNodeElementIdentifier(nodePos)) && GetNodeType(nodePos) == NODE_TYPE_BEGIN_TAG)
        {
            cells ++;
        }
    }

    m_parserNodeData[node].param1 = cells;

    return true;
}

bool SwThMLParser::CountTableRows()
{
    swUI32 indexPos = 0;

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        CountTableRows(indexPos);

        indexPos ++;
    }

    return true;
}

bool SwThMLParser::CountTableRows(swUI32 node)
{
    if (!IsTable(GetNodeElementIdentifier(node)) || GetNodeType(node) != NODE_TYPE_BEGIN_TAG)
        return false;

    swUI32 mate = GetNodeMate(node);
    swUI32 rows = 0;
    swUI32 cells = 0;

    m_parserNodeData[node].param1 = 0;
    m_parserNodeData[node].param2 = 0;

    for (swUI32 nodePos = node + 1; nodePos < mate; nodePos ++)
    {
        if (IsTable(GetNodeElementIdentifier(nodePos)) && GetNodeType(nodePos) == NODE_TYPE_BEGIN_TAG)
        {
            nodePos = GetNodeMate(nodePos);
        }
        else if (IsTableRow(GetNodeElementIdentifier(nodePos)) && GetNodeType(nodePos) == NODE_TYPE_BEGIN_TAG)
        {
            if (m_parserNodeData[nodePos].param1 > cells)
                cells = m_parserNodeData[nodePos].param1;

            rows ++;
        }
    }

    m_parserNodeData[node].param1 = rows;
    m_parserNodeData[node].param2 = cells;

    return true;
}

bool SwThMLParser::CollectTableData()
{
    SetRange(m_parserNodePos);

    if (!CountRowCells())
        return false;

    if (!CountTableRows())
        return false;

    return true;
}

bool SwThMLParser::ResetNodeData()
{
    // Reset parts of node data that will be modified
    swUI32 pos = 0;
    SetRange(m_parserNodePos);

    while (pos < m_parserNodePos)
    {
        if (!UpdateUI(pos))
            return false;

        m_parserNodeData[pos].nodeMate = NODE_ID_INVALID;
        m_parserNodeData[pos].nodeParent = NODE_ID_INVALID;
        m_parserNodeData[pos].nodeFirstChild = NODE_ID_INVALID;
        m_parserNodeData[pos].nodeNextSibling = NODE_ID_INVALID;

        pos ++;
    }

    return true;
}

bool SwThMLParser::UpdateNodeData()
{
    if (!Defragment())
        return false;

    if (!ResetNodeData())
        return false;

    if (!MateElements())
        return false;

    if (!ParentElements())
        return false;

    if (!SetFirstChild())
        return false;

    if (!SetNextSibling())
        return false;

    if (m_processtableData)
    {
        if (!CountRowCells())
            return false;

        if (!CountTableRows())
            return false;

        if (!CollectTableData())
            return false;
    }

    OnNodeDataUpdate();
    return true;
}

void SwThMLParser::ShiftNodesUp(swUI32 startNode)
{
    if (m_parserNodePos <= 1)
    {
        m_parserNodePos = 0;
        return;
    }
    else if (startNode == 0)
        return;
    else if (startNode > GetLastParserNode())
    {
        return;
    }

    swUI32 pos = startNode;

    while(pos < m_parserNodePos)
    {
        m_parserNodeData[pos - 1] = m_parserNodeData[pos];
        pos ++;
    }

    m_parserNodePos --;
}

void SwThMLParser::ShiftNodesUp(swUI32 startNode, swUI32 nodes)
{
    if (m_parserNodePos <= nodes)
    {
        m_parserNodePos = 0;
        return;
    }
    else if (startNode == 0)
        return;
    else if (startNode > GetLastParserNode() || nodes > startNode)
        return;

    swUI32 pos = startNode;

    while(pos < m_parserNodePos)
    {
        m_parserNodeData[pos - nodes] = m_parserNodeData[pos];
        pos ++;
    }

    m_parserNodePos -= nodes;
}

bool SwThMLParser::ShiftNodesDown(swUI32 startNode)
{
    if (startNode > GetLastParserNode())
        return false;

    if (!VerifyParserNode())
        return false;

    swUI32 pos = m_parserNodePos;

    while(pos > startNode)
    {
        m_parserNodeData[pos] = m_parserNodeData[pos - 1];
        pos --;
    }

    m_parserNodePos ++;
    return true;
}

bool SwThMLParser::ShiftNodesDown(swUI32 startNode, swUI32 nodes)
{
    if (startNode > GetLastParserNode())
        return false;

    if (!VerifyParserNodes(nodes))
        return false;

    m_parserNodePos += nodes;
    swUI32 pos = m_parserNodePos;

    while(pos >= startNode + nodes)
    {
        m_parserNodeData[pos] = m_parserNodeData[pos - nodes];
        pos --;
    }

    return true;
}

bool SwThMLParser::MateElements()
{
    swUI32 indexPos = 0, indexPosB, numOpen;
    SetRange(m_parserNodePos);

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        if (m_parserNodeData[indexPos].nodeType == NODE_TYPE_BEGIN_TAG)
        {
            numOpen = 1;
            indexPosB = indexPos + 1;
            while (indexPosB < m_parserNodePos)
            {
                if (m_parserNodeData[indexPosB].elementIdentifier == m_parserNodeData[indexPos].elementIdentifier && m_parserNodeData[indexPosB].nodeType != NODE_TYPE_UNPAIRED_TAG)
                {
                    if (m_parserNodeData[indexPosB].nodeType == NODE_TYPE_BEGIN_TAG)
                        numOpen ++;
                    else if (m_parserNodeData[indexPosB].nodeType == NODE_TYPE_END_TAG && numOpen > 1)
                        numOpen --;
                    else if (m_parserNodeData[indexPosB].nodeType == NODE_TYPE_END_TAG && numOpen == 1)
                    {
                        m_parserNodeData[indexPos].nodeMate = indexPosB;
                        m_parserNodeData[indexPosB].nodeMate = indexPos;
                        break;
                    }
                }

                indexPosB ++;
            }
        }

        indexPos ++;
    }

    if (!FixMissingMates())
        return false;

    return true;
}

bool SwThMLParser::FixMissingMates()
{
    swUI32 indexPos = 0;
    SetRange(m_parserNodePos);

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        if (m_parserNodeData[indexPos].nodeType == NODE_TYPE_BEGIN_TAG && m_parserNodeData[indexPos].nodeMate == NODE_ID_INVALID)
            m_parserNodeData[indexPos].nodeType = NODE_TYPE_UNPAIRED_TAG;

        indexPos ++;
    }

    return true;
}

bool SwThMLParser::ParentElements()
{
    swUI32 indexPos = 0, indexPosB;
    SetRange(m_parserNodePos);

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        if (m_parserNodeData[indexPos].nodeType == NODE_TYPE_BEGIN_TAG && m_parserNodeData[indexPos].nodeMate != NODE_ID_INVALID)
        {
            indexPosB = indexPos + 1;
            m_parserNodeData[m_parserNodeData[indexPos].nodeMate].nodeParent = indexPos;

            while (indexPosB < m_parserNodeData[indexPos].nodeMate)
            {
                m_parserNodeData[indexPosB].nodeParent = indexPos;

                if (m_parserNodeData[indexPosB].nodeType == NODE_TYPE_BEGIN_TAG && m_parserNodeData[indexPosB].nodeMate != NODE_ID_INVALID)
                    indexPosB = m_parserNodeData[indexPosB].nodeMate;

                indexPosB ++;
            }
        }
        indexPos ++;
    }

    return true;
}

bool SwThMLParser::SetFirstChild()
{
    swUI32 indexPos = 0;
    SetRange(m_parserNodePos);

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        if (m_parserNodeData[indexPos].nodeParent != NODE_ID_INVALID && m_parserNodeData[m_parserNodeData[indexPos].nodeParent].nodeFirstChild == NODE_ID_INVALID)
            m_parserNodeData[m_parserNodeData[indexPos].nodeParent].nodeFirstChild = indexPos;

        indexPos ++;
    }

    return true;
}

bool SwThMLParser::SetNextSibling()
{
    swUI32 indexPos = 0, indexPosB;
    SetRange(m_parserNodePos);

    while (indexPos < m_parserNodePos)
    {
        if (!UpdateUI(indexPos))
            return false;

        indexPosB = indexPos + 1;
        while (indexPosB < m_parserNodePos)
        {
            if (m_parserNodeData[indexPos].nodeParent == m_parserNodeData[indexPosB].nodeParent)
            {
                m_parserNodeData[indexPos].nodeNextSibling = indexPosB;
                break;
            }

            indexPosB ++;
        }

        indexPos ++;
    }

    return true;
}

swUI32 SwThMLParser::GetNodesDataSize(swUI32 nodeBegin, swUI32 nodeEnd)
{
    if (nodeBegin >= m_parserNodePos || nodeEnd >= m_parserNodePos || nodeBegin > nodeEnd)
        return 0;

    return (m_parserNodeData[nodeEnd].endPos - m_parserNodeData[nodeBegin].beginPos) + 1;
}

swUI32 SwThMLParser::GetDataSizeBetweenMates(swUI32 node, bool includeMates)
{
    if (node >= m_parserNodePos)
        return 0;

    swUI32 mate = GetNodeMate(node), start, end;

    if (mate == NODE_ID_INVALID)
        return 0;

    if (includeMates)
    {
        start = GetNode(node)->beginPos;
        end = GetNode(mate)->endPos;
    }
    else
    {
        start = GetNode(node)->endPos;
        end = GetNode(mate)->beginPos;
        start ++;
        end --;
    }

    return (end - start) + 1;
}

bool SwThMLParser::GetNodeData(swUI32 node, SwString & dest)
    {
        if (node >= m_parserNodePos)
            return false;

        if (!dest.Size(GetNodeDataSize(node) + 1))
            return false;

        dest.SetAt(0, '\0');

        if (m_mode == MODE_MEMORY)
        {
            memcpy(dest, m_sourceBuffer + m_parserNodeData[node].beginPos, GetNodeDataSize(node));
            dest.SetAt(GetNodeDataSize(node), '\0');
        }
        else if (m_mode == MODE_FS_CONT || m_mode == MODE_FS_CONTWR)
        {
            if (!m_file)
                return false;

            fseek(m_file, m_parserNodeData[node].beginPos, SEEK_SET);

            if (fread(dest, 1, GetNodeDataSize(node), m_file) != GetNodeDataSize(node))
                return false;

            dest.SetAt(GetNodeDataSize(node), '\0');
        }
        else if (m_mode == MODE_FS_INT)
        {
            if (!m_path)
                return false;

            m_file = SwFopen(m_path, FMD_R);

            if (!m_file)
                return false;

            fseek(m_file, m_parserNodeData[node].beginPos, SEEK_SET);

            if (fread(dest, 1, GetNodeDataSize(node), m_file) != GetNodeDataSize(node))
            {
                fclose(m_file);
                m_file = NULL;
                return false;
            }

            dest.SetAt(GetNodeDataSize(node), '\0');
            fclose(m_file);
            m_file = NULL;
        }
        else
            return false;

        return true;
    }

bool SwThMLParser::GetNodesData(SwNodeRange & nr, SwString & dest)
{
    return GetNodesData(nr.startNode, nr.endNode, dest);
}

bool SwThMLParser::GetNodesData(swUI32 nodeBegin, swUI32 nodeEnd, SwString & dest)
{
    if (nodeBegin >= m_parserNodePos || nodeEnd > m_parserNodePos || nodeBegin > nodeEnd)
        return false;

    if (!dest.Size(GetNodesDataSize(nodeBegin, nodeEnd) + 1))
        return false;

    dest.SetAt(0, '\0');

    if (m_mode == MODE_MEMORY)
    {
        memcpy(dest, m_sourceBuffer + m_parserNodeData[nodeBegin].beginPos, GetNodesDataSize(nodeBegin, nodeEnd));
        dest.SetAt(GetNodesDataSize(nodeBegin, nodeEnd), '\0');
    }
    else if (m_mode == MODE_FS_CONT || m_mode == MODE_FS_CONTWR)
    {
        if (!m_file)
            return false;

        fseek(m_file, m_parserNodeData[nodeBegin].beginPos, SEEK_SET);
        fread(dest, 1, GetNodesDataSize(nodeBegin, nodeEnd), m_file);
        dest.SetAt(GetNodesDataSize(nodeBegin, nodeEnd), '\0');
    }
    else if (m_mode == MODE_FS_INT)
    {
        if (!m_path)
            return false;

        m_file = SwFopen(m_path, FMD_R);

        if (!m_file)
            return false;

        fseek(m_file, m_parserNodeData[nodeBegin].beginPos, SEEK_SET);
        fread(dest, 1, GetNodesDataSize(nodeBegin, nodeEnd), m_file);
        dest.SetAt(GetNodesDataSize(nodeBegin, nodeEnd), '\0');
        fclose(m_file);
        m_file = NULL;
    }
    else
        return false;

    return true;
}

bool SwThMLParser::GetDataBetweenMates(swUI32 node, SwString & dest, bool includeMates)
{
    if (node >= m_parserNodePos)
        return false;

    swUI32 start;
    swUI32 dsize = GetDataSizeBetweenMates(node, includeMates);

    if (includeMates)
        start = GetNode(node)->beginPos;
    else
        start = GetNode(node)->endPos + 1;

    if (!dsize)
        return false;

    if (!dest.Size(dsize + 1))
        return false;

    dest.SetAt(0, '\0');

    if (m_mode == MODE_MEMORY)
    {
        memcpy(dest, m_sourceBuffer + start, dsize);
        dest.SetAt(dsize, '\0');
    }
    else if (m_mode == MODE_FS_CONT || m_mode == MODE_FS_CONTWR)
    {
        if (!m_file)
            return false;

        fseek(m_file, start, SEEK_SET);
        fread(dest, 1, dsize, m_file);
        dest.SetAt(dsize, '\0');
    }
    else if (m_mode == MODE_FS_INT)
    {
        if (!m_path)
            return false;

        m_file = SwFopen(m_path, FMD_R);

        if (!m_file)
            return false;

        fseek(m_file, start, SEEK_SET);
        fread(dest, 1, dsize, m_file);
        dest.SetAt(dsize, '\0');
        fclose(m_file);
        m_file = NULL;
    }
    else
        return false;

    return true;
}

bool SwThMLParser::GetNamedValueFromNode(swUI32 node, const char * name, char * dest, swUI32 bufferLen)
{
    if (!name || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
        return false;

    SwString tag, data;
    swUI32 result = GetNodeDataSize(node);

    dest[0] = '\0';

    if (result < 1)
        return false;

    if (!GetNodeData(node, tag))
        return false;

    if (!data.Size(result))
        return false;

    if (!GetNamedValue(name, tag, data) || data.Strlen() >= bufferLen)
        return false;

    strcpy(dest, data);
    return true;
}


bool SwThMLParser::InsertAttributeInNode(swUI32 node, const char * attribute)
{
    if (!attribute || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
        return false;

    SwString buffer, format;
    swUI32 insertPos;

    if (!GetNodeData(node, buffer))
        return false;

    insertPos = FindInsertPosition(buffer);

    if(insertPos == 0)
        return false;

    format.Size(3 + strlen(attribute));
    sprintf(format, " %s ", attribute);
    buffer.Insert(insertPos, format);

    buffer.Despace();

    SwString::Replace(buffer, strlen(buffer), " >", 2, ">", 1);

    return ReplaceNode(node, buffer, true);
}

bool SwThMLParser::GetElementStrFromNode(swUI32 node, char * dest, swUI32 bufferLen)
{
    if (!dest || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
        return false;

    SwString data;

    if (node > GetLastParserNode())
        return false;

    if (!GetNodeData(node, data))
        return false;

    swUI32 pos = 0;
    // First char should be <.
    int start = 1;

    if (data.GetAt(1) == '/')
        start ++;

    while (!isspace(data.GetAt(pos)) && data.GetAt(pos) != '\0' && data.GetAt(pos) != '/' && data.GetAt(pos) != '>')
        pos ++;

    data.SetAt(pos, '\0');

    if (bufferLen <= data.Strlen())
        return false;

    strcpy(dest, data.GetArray() + start);

    return true;
}

swUI32 SwThMLParser::GetNextSiblingOfType(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType)
{
    swUI32 next = nodeOrigin;
    for(;;)
    {
        next = GetNextSibling(next);

        if (next == NODE_ID_INVALID)
            return NODE_ID_INVALID;

        if (nodeType == 0 && m_parserNodeData[next].elementIdentifier == elementId)
            return next;

        if (m_parserNodeData[next].elementIdentifier == elementId)
            return next;
    }
}

swUI32 SwThMLParser::FindElement(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType)
{
    swUI32 pos = nodeOrigin;

    while (pos < m_parserNodePos)
    {
        if (m_parserNodeData[pos].elementIdentifier == elementId && m_parserNodeData[pos].nodeType == nodeType)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLParser::FindElementUpWard(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType)
{
    swUI32 pos = nodeOrigin;

    while (pos && pos < m_parserNodePos)
    {
        if (m_parserNodeData[pos].elementIdentifier == elementId && m_parserNodeData[pos].nodeType == nodeType)
            return pos;

        pos --;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLParser::FindElementXN(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType, swUI32 count, swUI32 * found)
{
    swUI32 pos = nodeOrigin;
    swUI32 lastFound = NODE_ID_INVALID;
    swUI32 numberFound = 0;

    if (found)
    {
        *found = 0;
    }

    while (pos < m_parserNodePos && numberFound < count)
    {
        if (m_parserNodeData[pos].elementIdentifier == elementId && m_parserNodeData[pos].nodeType == nodeType)
        {
            lastFound = pos;
            numberFound ++;
        }

        pos ++;
    }

    if (found)
    {
        *found = numberFound;
    }

    return lastFound;
}

swUI32 SwThMLParser::FindWithInElement(swUI32 nodeParent, swUI32 nodeOffset, swUI16 elementId, swUI8 nodeType)
{
    swUI32 pos = nodeParent;
    swUI32 endPos = GetNodeMate(nodeParent);

    if (endPos == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    pos += nodeOffset;

    while (pos < m_parserNodePos && pos < endPos)
    {
        if (m_parserNodeData[pos].elementIdentifier == elementId && m_parserNodeData[pos].nodeType == nodeType)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLParser::GetTitle(SwString & dest)
{
    SwString buffer;
    swUI32 dsize;
    swUI8 lastChar = LCH_BREAK;

    swUI32 node = NODE_ID_INVALID;

    if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
        node = FindElement(0, THML_TITLE, NODE_TYPE_BEGIN_TAG);

    if (node == NODE_ID_INVALID)
        return 0;

    node = FindWithInElement(node, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

    if (node == NODE_ID_INVALID)
        return 0;

    dsize = GetNodeDataSize(node) + 1;

    if (!buffer.Size(dsize) || !dest.Size(dsize))
        return 0;

    if (!GetNodeData(node, buffer))
        return 0;

    dsize = SwHtml::Html2Text((char *) buffer, (char *) dest, dsize, lastChar, true);

    return dsize;
}

swUI32 SwThMLParser::GetTitle(char * dest, swUI32 bufferLen)
{
    swUI32 dsize;
    swUI8 lastChar = LCH_BREAK;

    if (!dest)
        return 0;

    swUI32 node = NODE_ID_INVALID;

    if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
        node = FindElement(0, THML_TITLE, NODE_TYPE_BEGIN_TAG);

    if (node == NODE_ID_INVALID)
        return 0;

    node = FindWithInElement(node, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

    if (node == NODE_ID_INVALID)
        return 0;

    dsize = GetNodeDataSize(node);

    if (dsize >= bufferLen)
        return 0;

    SwString p;

    p.Size(dsize + 1);

    if (!GetNodeData(node, p))
        return 0;

    dsize = SwHtml::Html2Text(p, dest, bufferLen, lastChar, true);

    return dsize;
}

void SwThMLParser::SetPath(const char * path)
{
    if (!path)
        return;

    if (m_path)
        free(m_path);

    m_path = strdup(path);
}

const char * SwThMLParser::GetPath()
{
    return m_path;
}

void SwThMLParser::SetBasePath(const char * path)
{
    if (!path)
        return;

    if (m_base)
        free(m_base);

    m_base = strdup(path);
}

const char * SwThMLParser::GetBasePath()
{
    return m_base;
}

bool SwThMLParser::SetElementArray(SwElement * elementArray, swI16 * alphaIndex, swI16 elementItems, swUI8 markupType)
{
    if (!elementArray || !alphaIndex || elementItems < 1)
        return false;

    m_elementArray = elementArray;
    m_elementAlphaIdx = alphaIndex;
    m_elementItems = elementItems;
    m_markupType = markupType;
    return true;
}

bool SwThMLParser::FileAppend(const char * data, swUI32 bytes)
{
    if (!data || !bytes)
        return false;

    if (m_mode == MODE_FS_CONTWR)
    {
        if (!m_file)
            return false;
    }
    else if (m_mode == MODE_FS_INT)
    {
        if (!m_path)
            return false;

        m_file = SwFopen(m_path, FMD_RW);

        if (!m_file)
            return false;
    }
    else
        return false;

    fseek(m_file, 0, SEEK_END);

    bool status = true;

    if (fwrite(data, 1, bytes, m_file) != bytes)
    {
#if defined __MSWIN__
        chsize(m_file->_file, m_dataSize);
#else
        ftruncate(fileno(m_file), m_dataSize);
#endif
        status = false;
    }

    if (m_mode == MODE_FS_INT)
    {
        fflush(m_file);
        fclose(m_file);
        m_file = NULL;
    }

    return status;
}

swUI32 SwThMLParser::AppendNode(const char * nodeData, bool update, swUI32 size)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || !nodeData || !VerifyParserNode())
        return NODE_ID_INVALID;

    swUI32 bytes;

    if (size == 0)
        bytes = strlen(nodeData);
    else
        bytes = size;

    bool status;

    if (m_mode == MODE_MEMORY)
        status = BufferAppend(nodeData, bytes);
    else
        status = FileAppend(nodeData, bytes);

    if (!status)
        return NODE_ID_INVALID;

    m_parserNodeData[m_parserNodePos].beginPos = m_dataSize;
    m_parserNodeData[m_parserNodePos].endPos = m_dataSize + bytes - 1;

    m_parserNodeData[m_parserNodePos].nodeType = GetNodeType(nodeData);
    if (m_parserNodeData[m_parserNodePos].nodeType != NODE_TYPE_TEXT_RUN)
    {
        m_parserNodeData[m_parserNodePos].elementIdentifier = IdentifyElement(nodeData);
        m_parserNodeData[m_parserNodePos].xmlId = GetXmlId(nodeData);
    }
    else
    {
        m_parserNodeData[m_parserNodePos].xmlId = 0;
        m_parserNodeData[m_parserNodePos].elementIdentifier = INT_TEXT_RUN;
    }

    m_dataSize += bytes;
    m_parserNodePos ++;

    if (update)
        UpdateNodeData();

    m_modified = true;
    return m_parserNodePos - 1;
}

swUI32 SwThMLParser::AppendNodes(const char * nodeData, bool update, swUI32 size)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || !nodeData)
        return NODE_ID_INVALID;

    SwThMLParser parser;
    parser.SetElementArray(m_elementArray, m_elementAlphaIdx, m_elementItems, m_markupType);
    parser.Parse(nodeData, size);
    parser.UpdateNodeData();

    if (!VerifyParserNodes(parser.GetLastParserNode() + 1))
        return NODE_ID_INVALID;

    swUI32 bytes;

    if (size == 0)
        bytes = strlen(nodeData);
    else
        bytes = size;

    bool status;

    if (m_mode == MODE_MEMORY)
        status = BufferAppend(nodeData, bytes);
    else
        status = FileAppend(nodeData, bytes);

    if (!status)
        return NODE_ID_INVALID;

    swUI32 pos = 0;
    while (pos <= parser.GetLastParserNode())
    {

        m_parserNodeData[m_parserNodePos] = *parser.GetNode(pos);
        m_parserNodeData[m_parserNodePos].beginPos = m_dataSize;
        m_parserNodeData[m_parserNodePos].endPos = m_dataSize + parser.GetNodeDataSize(pos) - 1;
        m_dataSize += parser.GetNodeDataSize(pos);
        m_parserNodePos ++;
        pos ++;
    }

    if (update)
        UpdateNodeData();

    m_modified = true;
    return m_parserNodePos - 1;
}

swUI32 SwThMLParser::AppendBinaryNodes(const char * name, const char * nodeData, bool update, swUI32 size)
{
    char format[] = "<binary name=\"%s\" size=\"%u\">";
    SwString buffer;

    if (!name || ! nodeData || !buffer.Size(strlen(format) + strlen(name) + 10 + size + 9))
        return NODE_ID_INVALID;

    sprintf(buffer, &format[0], name, size);
    buffer.SetCount(strlen(buffer));
    memcpy((void *) nodeData, buffer.GetArray() + buffer.GetCount(), size);
    buffer.IncrementCount(size);
    buffer += "</binary>";

    return AppendNodes(buffer, true, buffer.GetCount());
}

bool SwThMLParser::FileInsert(swUI32 pos, const char * data, swUI32 bytes)
{
    // Insertion.

    if (!data)
        return false;

    if (m_mode == MODE_FS_CONTWR)
    {
        if (!m_file)
            return false;

    }
    else if (m_mode == MODE_FS_INT)
    {
        if (!m_path)
            return false;

        m_file = SwFopen(m_path, FMD_RW);

        if (!m_file)
            return false;
    }
    else
        return false;

#if defined __MSWIN__
    if (chsize(m_file->_file, m_dataSize + bytes) != 0)
#else
    if (ftruncate(fileno(m_file), m_dataSize + bytes) != 0)
#endif
    {
        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            fclose(m_file);
            m_file = NULL;
        }


        return false;
    }

    swUI32 moveBytes = (m_dataSize - pos);
    char * buff = (char *) malloc(moveBytes);

    if (!buff)
    {
#if defined __MSWIN__
        chsize(m_file->_file, m_dataSize);
#else
        ftruncate(fileno(m_file), m_dataSize);
#endif

        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            fclose(m_file);
            m_file = NULL;
        }

        return false;
    }

    fseek(m_file, pos, SEEK_SET);
    fread(buff, 1, moveBytes, m_file);
    fseek(m_file, pos + bytes, SEEK_SET);
    fwrite(buff, 1, moveBytes, m_file);

    fseek(m_file, pos, SEEK_SET);
    fwrite(data, 1, bytes, m_file);

    if (m_mode == MODE_FS_INT)
    {
        fflush(m_file);
        fclose(m_file);
        m_file = NULL;
    }

    free(buff);
    return true;
}

bool SwThMLParser::InsertNode(swUI32 nodePos, const char * nodeData, bool update, swUI32 size)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || !nodeData || !ShiftNodesDown(nodePos))
        return false;

    if (nodePos > m_parserNodePos - 1)
        return AppendNode(nodeData, update);

    swUI32 bytes;

    if (size == 0)
        bytes = strlen(nodeData);
    else
        bytes = size;

    bool status;

    if (m_mode == MODE_MEMORY)
        status = BufferInsert(m_parserNodeData[nodePos].beginPos, nodeData, bytes);
    else
        status = FileInsert(m_parserNodeData[nodePos].beginPos, nodeData, bytes);

    if (!status)
    {
        ShiftNodesUp(nodePos + 1);
        return false;
    }

    m_parserNodeData[nodePos].endPos = m_parserNodeData[nodePos].beginPos + bytes -1;
    m_parserNodeData[nodePos].nodeType = GetNodeType(nodeData);

    if (m_parserNodeData[nodePos].nodeType != NODE_TYPE_TEXT_RUN)
    {
        m_parserNodeData[nodePos].elementIdentifier = IdentifyElement(nodeData);
        m_parserNodeData[nodePos].xmlId = GetXmlId(nodeData);
    }
    else
    {
        m_parserNodeData[nodePos].xmlId = 0;
        m_parserNodeData[nodePos].elementIdentifier = INT_TEXT_RUN;
    }

    m_dataSize += bytes;
    UpdateNodePosData(nodePos + 1, bytes, true);

    if (update)
        UpdateNodeData();

    m_modified = true;
    return true;
}

bool SwThMLParser::InsertNodes(swUI32 nodePos, const char * nodeData, bool update, swUI32 size)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || !nodeData)
        return false;

    if (nodePos > m_parserNodePos - 1)
        return AppendNodes(nodeData, update);

    SwThMLParser parser;
    parser.SetElementArray(m_elementArray, m_elementAlphaIdx, m_elementItems, m_markupType);
    parser.Parse(nodeData, size);
    parser.UpdateNodeData();

    swUI32 bytes;

    if (size == 0)
        bytes = strlen(nodeData);
    else
        bytes = size;

    if (!ShiftNodesDown(nodePos, parser.GetLastParserNode() + 1))
        return false;

    bool status;

    swUI32 writePos = m_parserNodeData[nodePos].beginPos;
    if (m_mode == MODE_MEMORY)
        status = BufferInsert(m_parserNodeData[nodePos].beginPos, nodeData, bytes);
    else
        status = FileInsert(m_parserNodeData[nodePos].beginPos, nodeData, bytes);

    if (!status)
    {
        ShiftNodesUp(nodePos + parser.GetLastParserNode() + 1, parser.GetLastParserNode() + 1);
        return false;
    }

    swUI32 pos = 0;
    while (pos <= parser.GetLastParserNode())
    {
        m_parserNodeData[nodePos + pos] = *parser.GetNode(pos);
        m_parserNodeData[nodePos + pos].beginPos = writePos;
        m_parserNodeData[nodePos + pos].endPos = writePos + parser.GetNodeDataSize(pos) - 1;
        writePos += parser.GetNodeDataSize(pos);
        pos ++;
    }

    m_dataSize += bytes;
    UpdateNodePosData(nodePos + parser.GetLastParserNode() + 1, bytes, true);

    if (update)
        UpdateNodeData();

    m_modified = true;
    return true;
}

bool SwThMLParser::FileDelete(swUI32 pos, swUI32 bytes)
{
    if (pos >= m_dataSize)
        return false;

    if (m_mode == MODE_FS_CONTWR)
    {
        if (!m_file)
            return false;
    }
    else if (m_mode == MODE_FS_INT)
    {
        if (!m_path)
            return false;

        m_file = SwFopen(m_path, FMD_RW);

        if (!m_file)
            return false;
    }
    else
        return false;

    if (pos + bytes >= m_dataSize)
    {
#if defined __MSWIN__
        chsize(m_file->_file, pos);
#else
        ftruncate(fileno(m_file), pos);
#endif

        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            m_file = NULL;
            fclose(m_file);
        }

        return true;
    }

    swUI32 moveBytes = (m_dataSize - (pos + bytes));
    char * buff = (char *) malloc(moveBytes);

    if (!buff)
    {
        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            fclose(m_file);
            m_file = NULL;
        }

        return false;
    }

    fseek(m_file, pos + bytes, SEEK_SET);
    fread(buff, 1, moveBytes, m_file);
    fseek(m_file, pos, SEEK_SET);
    fwrite(buff, 1, moveBytes, m_file);

    fseek(m_file, 0, SEEK_SET);

#if defined __MSWIN__
    chsize(m_file->_file, m_dataSize - bytes);
#else
    ftruncate(fileno(m_file), m_dataSize - bytes);
#endif

    if (m_mode == MODE_FS_INT)
    {
        fflush(m_file);
        fclose(m_file);
        m_file = NULL;
    }

    free(buff);
    return true;
}

bool SwThMLParser::DeleteNode(swUI32 nodePos, bool update)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || nodePos > GetLastParserNode())
        return false;

    swUI32 change = GetNodeDataSize(nodePos);

    bool status;

    if (m_mode == MODE_MEMORY)
        status = BufferDelete(m_parserNodeData[nodePos].beginPos, change);
    else
        status = FileDelete(m_parserNodeData[nodePos].beginPos, change);

    if (!status)
        return false;

    m_dataSize -= change;

    if (nodePos != GetLastParserNode())
    {
        ShiftNodesUp(nodePos + 1);
        UpdateNodePosData(nodePos, change, false);
    }
    else
        m_parserNodePos --;

    if (update)
        UpdateNodeData();

    m_modified = true;
    return true;
}

bool SwThMLParser::DeleteNodes(swUI32 nodeBegin, swUI32 nodeEnd, bool update)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || nodeBegin > GetLastParserNode() || nodeEnd > GetLastParserNode() || nodeBegin > nodeEnd)
        return false;

    swUI32 change = GetNodesDataSize(nodeBegin, nodeEnd);
    swUI32 nodes = (nodeEnd - nodeBegin) + 1;
    bool status;

    if (m_mode == MODE_MEMORY)
        status = BufferDelete(m_parserNodeData[nodeBegin].beginPos, change);
    else
        status = FileDelete(m_parserNodeData[nodeBegin].beginPos, change);

    if (!status)
        return false;

    m_dataSize -= change;

    if (nodeEnd != GetLastParserNode())
    {
        UpdateNodePosData(nodeEnd + 1, change, false);
        ShiftNodesUp(nodeEnd + 1, nodes);
    }
    else
        m_parserNodePos -= ((nodeEnd - nodeBegin) + 1);

    if (update)
        UpdateNodeData();

    m_modified = true;
    return true;
}

bool SwThMLParser::FileReplace(swUI32 pos, swUI32 bytes, const char * data, swUI32 newBytes)
{
    if (!data)
        return false;

    if (m_mode == MODE_FS_CONTWR)
    {
        if (!m_file)
            return false;
    }
    else if (m_mode == MODE_FS_INT)
    {
        if (!m_path)
            return false;

        m_file = SwFopen(m_path, FMD_RW);

        if (!m_file)
            return false;
    }
    else
        return false;

    if (bytes == newBytes)
    {
        fseek(m_file, pos, SEEK_SET);
        fwrite(data, 1, newBytes, m_file);

        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            fclose(m_file);
            m_file = NULL;
        }

        return true;
    }

    swUI32 moveBytes = (m_dataSize - (pos + bytes));
    char * buff = (char *) malloc(moveBytes);

    if (!buff)
    {
        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            fclose(m_file);
            m_file = NULL;
        }

        return false;
    }

#if defined __MSWIN__
    if (newBytes > bytes && chsize(m_file->_file, m_dataSize + (newBytes - bytes)) != 0)
#else
    if (newBytes > bytes && ftruncate(fileno(m_file), m_dataSize + (newBytes - bytes)) != 0)
#endif
    {
        free(buff);

        if (m_mode == MODE_FS_INT)
        {
            fflush(m_file);
            fclose(m_file);
            m_file = NULL;
        }

        return false;
    }

    fseek(m_file, pos + bytes, SEEK_SET);
    fread(buff, 1, moveBytes, m_file);
    fseek(m_file, pos + newBytes, SEEK_SET);
    fwrite(buff, 1, moveBytes, m_file);

    fseek(m_file, pos, SEEK_SET);
    fwrite(data, 1, newBytes, m_file);
    fseek(m_file, 0, SEEK_SET);

    if (newBytes < bytes)
    {
#if defined __MSWIN__
        chsize(m_file->_file, m_dataSize - (bytes - newBytes));
#else
        ftruncate(fileno(m_file), m_dataSize - (bytes - newBytes));
#endif
    }

    if (m_mode == MODE_FS_INT)
    {
        fflush(m_file);
        fclose(m_file);
        m_file = NULL;
    }

    free(buff);
    return true;
}

bool SwThMLParser::ReplaceNodes(swUI32 nodeBegin, swUI32 nodeEnd, const char * nodeData, bool update, swUI32 size)
{
    if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || !nodeData || nodeBegin > GetLastParserNode() || nodeEnd > GetLastParserNode() || nodeBegin > nodeEnd)
        return false;

    SwThMLParser parser;

    parser.SetElementArray(m_elementArray, m_elementAlphaIdx, m_elementItems, m_markupType);
    parser.Parse(nodeData, size);
    parser.UpdateNodeData();

    swUI32 nodesOriginal = (nodeEnd - nodeBegin) + 1;
    swUI32 nodesNew = parser.GetLastParserNode() + 1;

    swUI32 bytes;

    if (size == 0)
        bytes = strlen(nodeData);
    else
        bytes = size;

    swUI32 bytesOriginal = GetNodesDataSize(nodeBegin, nodeEnd);
    bool status;

    if (nodesOriginal < nodesNew && !ShiftNodesDown(nodeEnd + 1, nodesNew - nodesOriginal))
    {
        return false;
    }
    else if (nodesOriginal > nodesNew)
        ShiftNodesUp(nodeEnd + 1, nodesOriginal - nodesNew);

    swUI32 writePos = m_parserNodeData[nodeBegin].beginPos;
    if (m_mode == MODE_MEMORY)
        status = BufferReplace(m_parserNodeData[nodeBegin].beginPos, bytesOriginal, nodeData, bytes);
    else
        status = FileReplace(m_parserNodeData[nodeBegin].beginPos, bytesOriginal, nodeData, bytes);

    if (!status)
    {
        // This does not repair damage to node structure
        if (nodesOriginal < nodesNew)
            ShiftNodesUp(nodeEnd, nodesNew - nodesOriginal);
        else if (nodesOriginal > nodesNew)
            ShiftNodesDown(nodeEnd, nodesOriginal - nodesNew);

        return false;
    }

    if (bytes < bytesOriginal)
    {
        m_dataSize -= bytesOriginal - bytes;
        if (nodeBegin  + nodesNew < GetLastParserNode())//?
            UpdateNodePosData(nodeBegin + nodesNew, bytesOriginal - bytes, false);
    }
    else if (bytes > bytesOriginal)
    {
        m_dataSize += bytes - bytesOriginal;
        if (nodeBegin + nodesNew < GetLastParserNode())//?
            UpdateNodePosData(nodeBegin + nodesNew, bytes - bytesOriginal, true);
    }

    swUI32 pos = 0;
    while (pos <= parser.GetLastParserNode())
    {
        m_parserNodeData[nodeBegin + pos] = *parser.GetNode(pos);
        m_parserNodeData[nodeBegin + pos].beginPos = writePos;
        m_parserNodeData[nodeBegin + pos].endPos = writePos + parser.GetNodeDataSize(pos) - 1;
        writePos += parser.GetNodeDataSize(pos);
        pos ++;
    }

    if (update)
        UpdateNodeData();

    m_modified = true;
    return true;
}

bool SwThMLParser::MoveNode(swUI32 node, swUI32 newPos, bool update)
{
    SwString buffer;

    if (!GetNodeData(node, buffer))
        return false;

    if(!DeleteNode(node, update))
        return false;

    return InsertNode(newPos, buffer, update);
}

bool SwThMLParser::MoveNodes(swUI32 nodeBegin, swUI32 nodeEnd, swUI32 newPos, bool update)
{
    SwString buffer;

    if (!GetNodesData(nodeBegin, nodeEnd, buffer))
        return false;

    if(!DeleteNodes(nodeBegin, nodeEnd, update))
        return false;

    return InsertNodes(newPos, buffer, update);
}

bool SwThMLParser::Defragment()
{
    if (GetParserNodes() < 2)
        return true;

    swUI32 pos = 0, beginPos;
    SetRange(m_parserNodePos);

    while (pos < GetLastParserNode())
    {
        if (!UpdateUI(pos))
            return false;

        if (m_parserNodeData[pos].elementIdentifier == INT_TEXT_RUN && m_parserNodeData[pos + 1].elementIdentifier == INT_TEXT_RUN)
        {
            beginPos = m_parserNodeData[pos].beginPos;
            ShiftNodesUp(pos + 1);
            m_parserNodeData[pos].beginPos = beginPos;
            continue;
        }
        pos ++;
    }

    return true;
}

bool SwThMLParser::CollectThMLDivNotes(swUI32 divNode, SwString & buffer)
{
    if (m_markupType != MARKUP_THML)
        return false;

    SwString tempBuffer;
    swUI32 offSet = 0, noteBegin, noteEnd;
    buffer.Reset();
    bool foundNotes = false;
    bool containinP;

    swUI32 breakNode = GetThMLDivBreakNode(divNode);

    for (;;)
    {
        noteBegin = FindWithInElement(divNode, offSet, THML_NOTE, NODE_TYPE_BEGIN_TAG);
        if (noteBegin == NODE_ID_INVALID || noteBegin > breakNode)
            break;
        noteEnd = GetNodeMate(noteBegin);
        if (noteEnd != NODE_ID_INVALID)
        {
            containinP = false;
            if (FindWithInElement(noteBegin, 0, THML_P, NODE_TYPE_BEGIN_TAG) == NODE_ID_INVALID)
                containinP = true;
            foundNotes = true;
            if (containinP)
                buffer += "<p>";
            GetNodesData(noteBegin, noteEnd, tempBuffer);
            buffer += tempBuffer;
            if (containinP)
                buffer += "</p>";
        }

        offSet = (noteBegin - divNode) + 1;
    }

    return foundNotes;
}

bool SwThMLParser::ReplaceThMLDivNotes(swUI32 divNode)
{
    if (m_markupType != MARKUP_THML)
        return false;

    swUI32 noteBegin, noteEnd;
    SwString noteBuffer, noteFormat, noteNValue;
    char noteFormatString[] = "<note n=\"%s\"/>";

    for (swUI32 i = divNode + 1; i < m_parserNodePos; i ++)
    {
        if (IsNodeThMLDiv(i))
            break;

        if (GetNodeElementIdentifier(i) == THML_NOTE && GetNodeType(i) == NODE_TYPE_BEGIN_TAG)
        {
            noteBegin = FindWithInElement(divNode, 0, THML_NOTE, NODE_TYPE_BEGIN_TAG);
            if (noteBegin == NODE_ID_INVALID)
                break;
            noteEnd = FindWithInElement(divNode, 0, THML_NOTE, NODE_TYPE_END_TAG);

            if (noteEnd != NODE_ID_INVALID)
            {
                if (GetNamedValueFromNode(noteBegin, "n", noteNValue))
                {
                    noteFormat.Size(24 + strlen(noteNValue));
                    sprintf(noteFormat, noteFormatString,  (char *) noteNValue);
                    ReplaceNodes(noteBegin, noteEnd, noteFormat, true);
                    SetNodeType(noteBegin, NODE_TYPE_UNPAIRED_TAG);
                }
            }
        }
    }

    return true;
}

bool SwThMLParser::ProcessThMLNotes()
{
    if (m_markupType != MARKUP_THML)
        return false;

    if (HaveNotesBeenProcessed())
        return true;

    SwString buffer;
    SetRange(m_parserNodePos);

    for (swUI32 i = 0; i < m_parserNodePos; i++)
    {
        if (!UpdateUI(i))
            return false;

        if (GetNodeElementIdentifier(i) >= THML_DIV1 && GetNodeElementIdentifier(i) <= THML_DIV6 && GetNodeType(i) == NODE_TYPE_BEGIN_TAG)
        {
            if (!CollectThMLDivNotes(i, buffer))
                continue;

            if (!ReplaceThMLDivNotes(i))
                return false;

            if (!InsertNodes(GetThMLDivBreakNode(i), "<hr width=\"100%\" align=\"center\" color=\"lightblue\"/><br/>", true))
                return false;

            if (!InsertNodes(GetThMLDivBreakNode(i), buffer, true))
                return false;
        }
    }

    UpdateNodeData();
    return true;
}

size_t SwThMLParser::WriteParserSizeToFile(FILE & file)
{
    return fwrite((void *) &m_parserNodePos, sizeof(swUI32), 1, &file);
}

size_t SwThMLParser::ReadParserSizeFromFile(FILE & file, swUI32 & nodes)
{
    return fread((void *) &nodes, sizeof(swUI32), 1, &file);
}

size_t SwThMLParser::WriteParserToFile(FILE & file)
{
    return fwrite((void *) m_parserNodeData, sizeof(SwParserNodeData), m_parserNodePos, &file);
}

size_t SwThMLParser::ReadParserNodeDataFromFile(FILE & file, swUI32 nodes)
{
    SizeParserNodeArray(nodes);
    return fread((void *) m_parserNodeData, sizeof(SwParserNodeData), nodes, &file);
}

bool SwThMLParser::LoadParserFromFile(const char * dataFile, const char * sourceFile)
{
    if (!dataFile || !sourceFile)
        return false;

    if (!CloseFile())
        return false;

    FILE * file = NULL;
    swUI32 nodes;
    m_parserNodePos = 0;
    m_modified = false;

    file = SwFopen(dataFile, FMD_R);

    if (!file)
        return false;

    m_mode = MODE_FS_INT;
    if (ReadParserSizeFromFile(*file, nodes) != 1)
    {
        fclose(file);
        return false;
    }

    if (!SizeParserNodeArray(nodes))
    {
        fclose(file);
        return false;
    }

    if (ReadParserNodeDataFromFile(*file, nodes) != nodes)
    {
        fclose(file);
        return false;
    }

    m_parserNodePos = nodes;
    fclose(file);
    SetPath(sourceFile);
    SetBasePath(sourceFile);
    SwClipFileName(m_base);
    return true;
}

swUI32 SwThMLParser::FindNodeById(swUI32 nodeOrigin, swUI32 nodeBreak, char * id)
{
    swUI32 pos = nodeOrigin;
    SwString buffer, buffer2;
    swUI32 numericId = GenerateId(id);

    if (nodeOrigin > m_parserNodePos || nodeBreak < nodeOrigin)
        return NODE_ID_INVALID;

    while (pos <= nodeBreak)
    {
        if (numericId == m_parserNodeData[pos].xmlId && GetNodeData(pos, buffer))
        {
            buffer2.Size(GetNodeDataSize(pos) + 1);

            if (GetNamedValue("id", buffer, buffer2) && strcmp(id, buffer2) == 0)
                return pos;
        }

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLParser::FindNodeByStreamPos(swUI32 streamPos)
{
    if (streamPos >= m_dataSize)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (streamPos >= GetNodeStreamPosition(i) && streamPos < GetNodeStreamPosition(i) + GetNodeDataSize(i))
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwThMLParser::GetXmlId(swUI32 startPos, swUI32 endPos)
{
    swUI32 pos = 0, cnt = 1;
    swUI32 id = 0;

    while (pos + startPos < endPos - 5  && m_sourceBuffer[pos + startPos] != '\0')
    {
        if (m_sourceBuffer[pos + startPos] == 'i' && m_sourceBuffer[pos + startPos + 1] == 'd' &&
                m_sourceBuffer[pos + startPos + 2] == '=' && m_sourceBuffer[pos + startPos + 3] == '"')
        {
            pos += 4;
            while (pos + startPos < endPos && m_sourceBuffer[pos + startPos] != '"')
            {
                id += m_sourceBuffer[pos + startPos] * cnt;
                cnt ++;
                pos ++;
            }

            return id;
        }

        pos ++;
    }

    return 0;
}

swUI32 SwThMLParser::GetXmlId(const char * src)
{
    swUI32 pos = 0, cnt = 1;
    swUI32 id = 0;

    if (src)
        return 0;

    while (src[pos] != '\0')
    {
        if (src[pos] == 'i' && src[pos + 1] == 'd' &&
                src[pos + 2] == '=' && src[pos + 3] == '"')
        {
            pos += 4;
            while (src[pos] != '\0' && src[pos] != '"')
            {
                id += src[pos] * cnt;
                cnt ++;
                pos ++;
            }

            return id;
        }

        pos ++;
    }

    return 0;
}

swUI32 SwThMLParser::GenerateId(const char * name)
{
    if (!name)
        return 0;

    swUI32 id = 0, pos = 0, len = strlen(name);

    while (pos < len)
    {
        id += name[pos] * (pos + 1);
        pos ++;
    }

    return id;
}

bool SwThMLParser::GetInnerText(swUI32 node, SwString & buffer)
{
    swUI32 textNode = FindWithInElement(node, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

    if (textNode != NODE_ID_INVALID)
        return GetNodeData(textNode, buffer);

    return false;
}

swUI8 SwThMLParser::GetInnerMediaPath(swUI32 node, SwString & buffer)
{
    swUI8 type = CELLTYPE_TEXT;
    swUI32 mediaNode = NODE_ID_INVALID;

    if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
        mediaNode = FindWithInElement(node, 0, THML_IMG, NODE_TYPE_UNPAIRED_TAG);
    else
        return CELLTYPE_TEXT;

    if (mediaNode != NODE_ID_INVALID)
    {
        type = CELLTYPE_IMAGE;
    }

    if (mediaNode == NODE_ID_INVALID)
    {
        if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
            mediaNode = FindWithInElement(node, 0, THML_IMG, NODE_TYPE_BEGIN_TAG);

        type = CELLTYPE_IMAGE;
    }

    if (mediaNode == NODE_ID_INVALID)
    {
        if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
            mediaNode = FindWithInElement(node, 0, THML_AUDIO, NODE_TYPE_UNPAIRED_TAG);

        type = CELLTYPE_AUDIO;
    }

    if (mediaNode == NODE_ID_INVALID)
    {
        if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
            mediaNode = FindWithInElement(node, 0, THML_AUDIO, NODE_TYPE_BEGIN_TAG);

        type = CELLTYPE_AUDIO;
    }

    if (mediaNode == NODE_ID_INVALID)
    {
        if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
            mediaNode = FindWithInElement(node, 0, THML_VIDEO, NODE_TYPE_UNPAIRED_TAG);

        type = CELLTYPE_VIDEO;
    }

    if (mediaNode == NODE_ID_INVALID)
    {
        if (m_markupType == MARKUP_THML || m_markupType == MARKUP_HTML)
            mediaNode = FindWithInElement(node, 0, THML_VIDEO, NODE_TYPE_BEGIN_TAG);

        type = CELLTYPE_VIDEO;
    }

    if (mediaNode != NODE_ID_INVALID && GetNamedValueFromNode(mediaNode, "src", buffer))
        return type;

    return CELLTYPE_TEXT;
}

bool SwThMLParser::GetThMLScriptureIdFromNode(swUI32 node, swUI8 & book, swUI8 & chapter, swUI8 & verse)
{
    SwString buffer;

    if (m_markupType != MARKUP_THML)
        return false;

    if (!GetNamedValueFromNode(node, "id", buffer))
        return false;

    return SwThMLUtility::ParseScriptureId(buffer, book, chapter, verse);
}

bool SwThMLParser::DoesThMLDivHaveChildDiv(swUI32 nodePos)
{
    if (m_markupType != MARKUP_THML)
        return false;

    for (swUI16 i = GetNodeElementIdentifier(nodePos) + 1; i <= THML_DIV6; i++)
    {
        if (FindWithInElement(nodePos, 0, i, NODE_TYPE_BEGIN_TAG) != NODE_ID_INVALID)
            return true;
    }

    return false;
}

const char * SwThMLParser::GetElementString(swUI32 node)
{
    swUI16 id;

    if (node >= m_parserNodePos)
        id = INT_UNKNOWN;
    else
        id = GetNodeElementIdentifier(node);

    if (id >= INT_UNKNOWN)
        return SwHtml::GetInternalElementName(id);

    return m_elementArray[id].name;
}

swUI32 SwThMLParser::GetTrailingLineBreaks(swUI32 node)
{
    if (node >= m_parserNodePos)
        return 0;

    SwString buffer;

    GetNodeData(node, buffer);

    swUI8 inc = 0;
    swUI32 count = 0;

    for (swUI32 i = 0; buffer[i] != '\0'; i ++)
    {
        if (buffer[i] == '>')
            inc = 1;
        else if (buffer[i] == '\n')
            count += inc;
    }

    return count;
}

bool SwThMLParser::IsWithIn(swUI32 node, swUI16 element)
{
    if (node >= m_parserNodePos)
        return false;

    swUI32 parent = node;

    for (;;)
    {
        parent = GetNodeParent(parent);

        if (parent == NODE_ID_INVALID)
            break;

        if (GetNodeType(parent) == element)
            return true;
    }

    return false;
}

bool SwThMLParser::IsChildOf(swUI32 node, swUI16 element)
{
    if (node >= m_parserNodePos)
        return false;

    swUI32 parent = GetNodeParent(node);

    if (parent == NODE_ID_INVALID)
        return false;

    if (GetNodeElementIdentifier(parent) == element)
        return true;

    return false;
}

bool SwThMLParser::IsNext(swUI32 node, swUI16 element)
{
    if (node >= m_parserNodePos || node < 1)
        return false;

    if (!IsWithIn(node, element) && node > 0 && GetNodeElementIdentifier(node - 1) == element)
        return true;

    return false;
}

bool SwThMLParser::IsFirstChild(swUI32 node)
{
    if (node >= m_parserNodePos)
        return false;

    swUI32 parent = GetNodeParent(node);

    if (parent == NODE_ID_INVALID)
        return false;

    swUI32 firstChild = GetFirstChild(parent);

    if (firstChild == NODE_ID_INVALID)
        return false;

    if (firstChild == node)
        return true;

    return false;
}

bool SwThMLParser::IsPreceededBy(swUI32 node, swUI16 element)
{
    if (node >= m_parserNodePos)
        return false;

    swUI32 parent = GetNodeParent(node);

    if (parent == NODE_ID_INVALID)
        return false;

    swUI32 pos = 0;
    swUI32 found;
    for (;;)
    {
        found = FindWithInElement(parent, pos, element, NODE_TYPE_BEGIN_TAG);

        if (found == NODE_ID_INVALID)
            break;

        if (GetNodeParent(found) == parent && found < node)
            return true;

        pos = (found - parent) + 1;
    }

    return false;
}

void SwThMLParser::Containorize(swUI16 element, const char * namestr)
{
    if (!namestr)
        return;

    SwString data, buffer, tagBuffer, composite;

    SetRange(m_parserNodePos);
    swUI32 current = 0, inspos, strpos, count;

    buffer += "</";
    buffer += namestr;
    buffer += ">";

    for (swUI32 i = 0; i < GetParserNodes(); i ++)
    {
        UpdateUI(current);

        if (GetNodeElementIdentifier(i) == element && GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG)
        {
            inspos = NODE_ID_INVALID;
            for(swUI32 n = i + 1; n < GetParserNodes(); n ++)
            {
                if (GetNodeElementIdentifier(n) == element || IsNodeThMLDiv(n))
                {
                    inspos = n;
                    break;
                }
                else if (GetNodeElementIdentifier(n) == THML_P && GetNodeType(n) == NODE_TYPE_END_TAG)
                {
                    inspos = n;
                    break;
                }
            }

            if (inspos != NODE_ID_INVALID && IsNodeThMLDiv(inspos) && GetNodeElementIdentifier(inspos - 1) == THML_P)
            {
                inspos --;
            }

            if (inspos != NODE_ID_INVALID)
            {
                GetNodeData(i, data);
                data.Replace("/>", 2, ">", 1);
                ReplaceNode(i, data, false, data.Strlen());

                if (GetNodeElementIdentifier(inspos) == element)
                {
                    GetNodeData(inspos - 1, data);

                    count = 0;
                    for (strpos = data.Strlen() - 1; strpos > 0; strpos --)
                    {
                        if (data[strpos] != '\r' && data[strpos] != '\n')
                            break;
                        count ++;
                    }

                    if (count)
                        data.Insert(data.Strlen() - count, buffer);
                    else
                        data += buffer;

                    ReplaceNode(inspos - 1, data);
                }
                else
                    InsertNode(inspos, buffer, true, buffer.Strlen());
            }
        }
    }
}

swUI8 SwThMLParser::GetMarkupType()
{
    return m_markupType;
}

void SwThMLParser::SetMarkupType(swUI8 markup)
{
    m_markupType = markup;
}

void SwThMLParser::SetExtraBytes(swUI16 extra)
{
    m_extraBytes = extra;
}

swUI32 SwThMLParser::FindDataList(const char * id)
{
    if (!id)
        return NODE_ID_INVALID;

    SwString buffer;

    for (swUI32 i = 0; i < m_parserNodePos; i ++)
    {
        if (m_parserNodeData[i].elementIdentifier == THML_DATALIST && m_parserNodeData[i].nodeType == NODE_TYPE_BEGIN_TAG)
        {
            if (!GetNamedValueFromNode(i, "id", buffer) ||
                    strcmp(buffer, id) != 0)
            {
                continue;
            }

            return i;
        }

    }

    return NODE_ID_INVALID;
}

void SwThMLParser::ReplaceDataList(const char * id, const char * data)
{
    if (!id || !data)
        return;

    swUI32 node = FindDataList(id);
    swUI32 mate;

    if (node != NODE_ID_INVALID)
    {
        mate = GetNodeMate(node);
        if (mate == NODE_ID_INVALID)
            ReplaceNode(node, data, true, strlen(data));
        else
            ReplaceNodes(node, mate, data, true, strlen(data));
    }
    else
    {
        node = FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);
        if (node != NODE_ID_INVALID)
            InsertNodes(node, data, true, strlen(data));
    }
}

void SwThMLParser::FixEndPos()
{
    for (swUI32 i = 0; i < m_parserNodePos - 1; i ++)
    {
        m_parserNodeData[i].endPos = m_parserNodeData[i+1].beginPos - 1;
    }

    m_parserNodeData[m_parserNodePos - 1].endPos = m_dataSize - 1;
}

bool SwThMLParser::CheckParserIntegrity()
{
    for (swUI32 i = 0; i < m_parserNodePos - 1; i ++)
    {
        if (m_parserNodeData[i].endPos != m_parserNodeData[i+1].beginPos - 1)
            return false;
    }

    if (m_parserNodeData[m_parserNodePos - 1].endPos != m_dataSize - 1)
        return false;

    return true;
}

swI16 SwThMLParser::GetListItems(swUI32 node)
{
    swI16 items = 0;

    if (node >= m_parserNodePos)
        return 0;

    if (!IsList(GetNodeElementIdentifier(node)))
        return 0;

    if (GetNodeType(node) != NODE_TYPE_BEGIN_TAG)
        return 0;

    for (swUI32 i = node + 1; i < GetNodeMate(node); i ++)
    {
        if (IsList(i) && GetNodeType(i) == NODE_TYPE_BEGIN_TAG)
        {
            i = GetNodeMate(i);
            continue;
        }

        if (GetNodeElementIdentifier(i) == THML_LI)
            items ++;
    }

    return items;
}

swUI32 SwThMLParser::FindFirstChildDivision(swUI32 node)
{
    swUI32 child;

    child = FindWithInElement(node, 0, THML_DIV1, NODE_TYPE_BEGIN_TAG);
    if (child != NODE_ID_INVALID)
    {
        return child;
    }

    child = FindWithInElement(node, 0, THML_DIV2, NODE_TYPE_BEGIN_TAG);
    if (child != NODE_ID_INVALID)
    {
        return child;
    }

    child = FindWithInElement(node, 0, THML_DIV3, NODE_TYPE_BEGIN_TAG);
    if (child != NODE_ID_INVALID)
    {
        return child;
    }

    child = FindWithInElement(node, 0, THML_DIV4, NODE_TYPE_BEGIN_TAG);
    if (child != NODE_ID_INVALID)
    {
        return child;
    }

    child = FindWithInElement(node, 0, THML_DIV5, NODE_TYPE_BEGIN_TAG);
    if (child != NODE_ID_INVALID)
    {
        return child;
    }

    child = FindWithInElement(node, 0, THML_DIV6, NODE_TYPE_BEGIN_TAG);
    if (child != NODE_ID_INVALID)
    {
        return child;
    }

    return NODE_ID_INVALID;
}

void SwThMLParser::RemoveTags(swUI16 element)
{
    for (swUI32 i = 0; i < m_parserNodePos - 1; i ++)
    {
        if (GetNodeElementIdentifier(i) == element)
        {
            DeleteNode(i, true);
        }
    }
}

void SwThMLParser::SetProcessXmlId(bool process)
{
    m_processXmlId = process;
}

void SwThMLParser::SetProcessTableData(bool process)
{
    m_processtableData = process;
}

swUI32 SwThMLParser::GetDataSize()
{
    return m_dataSize;
}

void SwThMLParser::SetDataSize(swUI32 size)
{
    m_dataSize = size;
}


bool SwThMLParser::HaveNotesBeenProcessed()
{
    for (swUI32 i = 0; i < GetParserNodes(); i ++)
    {
        if (GetNodeElementIdentifier(i) == THML_NOTE && GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG)
            return true;
    }

    return false;
}

void SwThMLParser::SetRange(swUI32 range)
{
    if (m_progress && m_window)
    {
        wxThreadEvent * e = new wxThreadEvent();
        e->SetInt(0);
        m_progress->range = range;
        wxQueueEvent(m_window->GetEventHandler(), e);
    }
}

bool SwThMLParser::UpdateUI(swUI32 pos)
{
    if (m_progress && m_window)
    {
        wxThreadEvent * e = new wxThreadEvent();
        e->SetInt(1);
        m_progress->pos = pos;
        wxQueueEvent(m_window->GetEventHandler(), e);
        return m_progress->docontinue;
    }

    return true;
}

void SwThMLParser::SetProgressData(SwProgressData * data)
{
    m_progress = data;
}

void SwThMLParser::SetProgressTextData(const char * data)
{
    if (m_progress)
        m_progress->data = data;
}

void SwThMLParser::SetWindow(wxWindow * window)
{
    m_window = window;
}

bool SwThMLParser::WriteNodeData(swUI32 node, wxRichTextCtrl & ctrl)
{
    SwString buffer;

    GetNodeData(node, buffer);
    ctrl.WriteText(buffer.GetArray());

    return true;
}

void SwThMLParser::GetDataListItems(wxListCtrl * listctrl, const char * id)
{
    if (!listctrl || !id)
        return;

    swUI32 startNode = FindDataList(id);

    if (startNode == NODE_ID_INVALID)
        return;

    swUI32 endNode = GetNodeMate(startNode);

    if (endNode == NODE_ID_INVALID)
        return;

    SwString buffer;
    SwStringW buffer2;
    for (swUI32 i = startNode; i < endNode; i ++)
    {
        if (GetNodeElementIdentifier(i) == THML_OPTION && GetNamedValueFromNode(i, "value", buffer))
        {
            buffer2.Copy(buffer);
            listctrl->InsertItem(listctrl->GetItemCount(), buffer2.GetArray());
        }
    }
}

swUI8 SwThMLParser::GetPassageData(swUI32 node, SwScriptureRange & scriptRange)
{
    SwString buffer;
    bool identifyState = false;

    scriptRange.Reset();

    if (GetNodeElementIdentifier(node) == THML_SCRIPTURE)
    {
        if (GetNamedValueFromNode(node, "id", buffer))
        {
            buffer.Replace(" ", 1, "", 0);
            identifyState = SwThMLUtility::ParseScriptureId(buffer, scriptRange);
        }

        if (!identifyState && GetNamedValueFromNode(node, "passage", buffer))
        {
            identifyState =  SwThMLUtility::ParsePassageId(buffer, scriptRange);
        }

        if (!identifyState && GetNamedValueFromNode(node, "osisID", buffer))
        {
            SwOsisId osid;
            identifyState = osid.Parse(buffer);
            scriptRange.m_book = osid.m_book;
            scriptRange.m_chapter = osid.m_chapter;
            scriptRange.m_verseStart = osid.m_verse;
            scriptRange.m_verseEnd = 0;
        }
    }
    else if (GetNodeElementIdentifier(node) == THML_SCRIPCOM)
    {
        if (GetNamedValueFromNode(node, "passage", buffer))
        {
            identifyState =  SwThMLUtility::ParsePassageId(buffer, scriptRange);
        }

        if (!identifyState && GetNamedValueFromNode(node, "osisRef", buffer))
        {
            OsisRef osref;
            identifyState = osref.Parse(buffer);

            scriptRange.m_book = osref.m_start.m_book;
            scriptRange.m_chapter = osref.m_start.m_chapter;
            scriptRange.m_verseStart = osref.m_start.m_verse;
            scriptRange.m_verseEnd = osref.m_end.m_verse;
        }
    }

    return identifyState;
}

bool SwThMLParser::FindScriptureRange(SwScriptureRange & scriptRange, SwNodeRange & nodeRange)
{
    nodeRange.Reset();
    SwScriptureRange sr;

    for (swUI32 node = 0; node < m_parserNodePos; node ++)
    {
        if (GetNodeElementIdentifier(node) != THML_SCRIPTURE && GetNodeElementIdentifier(node) != THML_SCRIPCOM)
            continue;

        if (!GetPassageData(node, sr))
            continue;

        if (sr.m_book < scriptRange.m_book)
            continue;

        if (sr.m_book > scriptRange.m_book)
            return false;

        if (sr.m_chapter < scriptRange.m_chapter)
            continue;

        if (sr.m_chapter > scriptRange.m_chapter)
            return false;

        if (nodeRange.startNode == NODE_ID_INVALID)
        {
            if (!sr.IsInRange(scriptRange.m_verseStart))
                continue;

            nodeRange.startNode = node;
        }

        if (scriptRange.m_verseEnd == 0)
        {
            nodeRange.endNode = GetNodeMate(node);
            return true;
        }
        else
        {
            if (sr.IsInRange(scriptRange.m_verseEnd))
            {
                nodeRange.endNode = GetNodeMate(node);
                return true;
            }
        }
    }

    return false;
}

bool SwThMLParser::GetNamedValue(const char * name, const char * source, SwString & dest)
{
    if (!name || !source)
        return false;

    const char *p = source;
    int len = strlen(name);
    dest.Size(strlen(source + 1));
    dest.SetAt(0, '\0');

    for (;;)
    {
        p = strstr(p, name);

        if (!p)
            return false;

        if ((p == source || isspace(p[-1])) && (p[len] == '=' || isspace(p[len])))
            break;

        p++;
    }

    swUI32 n = 0;

    while (*p != '\0' && *p != '\"' && *p != '>')
        p++;

    if (*p != '\"' )
        return false;

    p++;

    while (isspace(*p))
        p++;

    while (*p != '\0' && *p != '\"' && *p != '>')
    {
        dest.SetAt(n, *p);
        n++;
        p++;
    }

    dest.SetAt(n, '\0');

    if (*p != '\"')
        return false;

    return true;
}

bool SwThMLParser::DeleteNamedValue(SwString & tag, const char * name, bool despace)
{
    swUI32 begin, end;

    if (!name)
        return false;

    if (!GetNamedValuePos(tag, name, begin, end))
        return false;

    if (begin > 0 && tag.GetAt(begin - 1) == ' ')
        begin --;

    tag.Delete(tag, begin, (end - begin) + 1);

    if (despace)
        tag.Despace();

    return true;
}

bool SwThMLParser::GetNamedValuePos(const char * source, const char * name, swUI32 & begin, swUI32 & end)
{
    if (!name || !source)
        return false;

    int len = strlen(name);
    const char *p = source;

    for (;;)
    {
        p = strstr(p, name);

        if (!p)
            return false;

        if ((p == source || isspace(p[-1])) && (p[len] == '=' || isspace(p[len])))
            break;

        p++;
    }

    begin = p - source;

    while (*p != '\0' && *p != '\"' && *p != '>')
        p++;
// This is first ";
    if (*p != '\"' )
        return false;

    p++;
    while (*p != '\0' && *p != '\"' && *p != '>')
        p++;

    end = p - source;

    return true;
}

bool SwThMLParser::InsertAttribute(SwString & tag, const char * attribute, bool despace)
{
    if (!attribute)
        return false;

    SwString format;
    swUI32 insertPos;

    insertPos = FindInsertPosition(tag);

    if(insertPos == 0)
        return false;

    format.Size(3 + strlen(attribute));
    sprintf(format, " %s ", attribute);
    tag.Insert(insertPos, format);

    if (despace)
    {
        tag.Despace();
        tag.Replace(tag, strlen(tag), " >", 2, ">", 1);
    }

    return true;
}

swUI32 SwThMLParser::FindInsertPosition(const char * tag)
{
    if (!tag)
        return 0;

    const char * p = NULL, * p1, * p2, * p3;

    p1 = strchr(tag, ' ');
    p2 = strstr(tag, "/>");
    p3 = strchr(tag, '>');

    if (!p3)
        return 0;

    if (p1 && p1 < p3)
        p = p1;
    else if (p2)
        p = p2;
    else
        p = p3;

    return p - tag;
}

struct MARKUP_DATA
{
    const char * sid;
    const char * name;
    const wchar_t * wname;
    const int id;
};

static const MARKUP_DATA MarkUpData[] =
{
    "SID_MKTYPE_UNKNOWN", "Unknown", L"Unknown", MARKUP_UNKNOWN,
    "SID_MKTYPE_NONE", "None", L"None", MARKUP_NONE,
    "SID_MKTYPE_HTML", "HTML", L"HTML", MARKUP_HTML,
    "SID_MKTYPE_THML", "ThML", L"ThML", MARKUP_THML,
    "SID_MKTYPE_SWGUIML", "SWGUIML", L"SWGUIML", MARKUP_SWGUI,
    "SID_MKTYPE_SWOPF", "SWOPF", L"SWOPF", MARKUP_SWOPF,
    "SID_MKTYPE_SWPRJ", "SWPRJML", L"SWPRJML", MARKUP_SWPRJ,
    "", "", L"", 0
};

SwMarkUpType::SwMarkUpType()
{
}

SwMarkUpType::~SwMarkUpType()
{
}

const char * SwMarkUpType::GetId(swUI8 mkl)
{
    swUI32 pos = 0;

    while (MarkUpData[pos].sid[0] != '\0')
    {
        if (MarkUpData[pos].id == mkl)
            return MarkUpData[pos].sid;

        pos ++;
    }

    return "";
}

const char * SwMarkUpType::GetString(swUI8 mkl)
{
    swUI32 pos = 0;

    while (MarkUpData[pos].sid[0] != '\0')
    {
        if (MarkUpData[pos].id == mkl)
            return MarkUpData[pos].name;

        pos ++;
    }

    return "";
}

const wchar_t * SwMarkUpType::GetStringW(swUI8 mkl)
{
    swUI32 pos = 0;

    while (MarkUpData[pos].sid[0] != '\0')
    {
        if (MarkUpData[pos].id == mkl)
            return MarkUpData[pos].wname;

        pos ++;
    }

    return L"";
}

swUI8 SwMarkUpType::GetMarkUpTypeType(wxChoice * choice)
{
    SwClientData * data;

    if (choice->GetSelection() == wxNOT_FOUND)
        return MARKUP_UNKNOWN;

    data = (SwClientData *) choice->GetClientObject(choice->GetSelection());

    if (!data)
        return MARKUP_UNKNOWN;

    return (swUI8) data->m_data;
}

swUI8 SwMarkUpType::GetMarkUpType(const char * value)
{
    swUI32 pos = 0;

    while (MarkUpData[pos].sid[0] != '\0')
    {
        if (stricmp(value, MarkUpData[pos].name) == 0)
            return MarkUpData[pos].id;

        pos ++;
    }

    return MARKUP_UNKNOWN;
}

void SwMarkUpType::GetMarkUpTypeList(wxChoice * choice)
{
    if (!choice)
        return;

    swUI32 pos = 0;
    SwClientData * data;

    for(;;)
    {
        if (SwMarkUpType::GetString(pos)[0] == '\0')
            break;

        data = new SwClientData();
        data->m_data = pos;
        choice->Append(SwMarkUpType::GetStringW(pos), data);

        pos ++;
    }
}
