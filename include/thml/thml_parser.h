///////////////////////////////////////////////////////////////////
// Name:        thml_parser.h
// Purpose:     Parser for xml/html documents, with functionality
//              specific to ThML.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLPARSER_H
#define THMLPARSER_H

#include <wx/choice.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/listctrl.h>
#include "../module/category.h"
#include "../html/html.h"
#include "../css/css_units.h"
#include "../html/html_color.h"
#include "../string/string.h"
#include "../thml/thml_elements.h"
#include "../filesys/file.h"
#include "../bible/bibledatacontainers.h"
#include <wx/gauge.h>
#include "../array/stringarray.h"

struct SwProgressData
{
    swUI32 range;
    swUI32 pos;
    bool docontinue;
    SwString data;
};

struct SwNodeRange
{
    void Reset()
    {
        startNode = endNode = NODE_ID_INVALID;
    }
    swUI32 startNode;
    swUI32 endNode;
};

#define MODE_MEMORY     1
#define MODE_FS_CONT    2
#define MODE_FS_CONTWR  3
#define MODE_FS_INT     4

struct SOWERBASEEXP SwParserNodeData
{
    swUI32      beginPos;
    swUI32      endPos;
    swUI16      elementIdentifier;
    swUI8       nodeType;
    swUI32      nodeMate;
    swUI32      nodeParent;
    swUI32      nodeFirstChild;
    swUI32      nodeNextSibling;
    swUI16      param1;
    swUI16      param2;
    bool        param3;
    swUI32      xmlId;
};

class SOWERBASEEXP SwThMLParser
{
public:
    SwThMLParser();
    virtual ~SwThMLParser();

    void Reset();
    virtual bool OpenFile(const char * path, swUI8 mode = MODE_MEMORY, bool processtableData = true);
    virtual bool Load(const char * source, swUI32 size);
    virtual bool Load(FILE * source, swUI32 size);
    virtual bool CloseFile(bool freeResources = false);
    virtual bool VerifyClose();
    bool SaveFile();
    bool SaveFile(const char * path);
    bool GetModified();
    void SetModified(bool modified);
    bool SizeBuffer(swUI32 bytes);
    void SetArrayIncrement(swUI16 increment);
    swUI32 PrecountTags(const char * src);
    bool IncreaseParserNodeArray();
    bool SizeParserNodeArray(swUI32 nodes);

    bool VerifyParserNode()
    {
        if (m_parserNodePos >= m_parserNodesAllocated && !IncreaseParserNodeArray())
            return false;

        return true;
    }

    bool VerifyParserNodes(swUI32 nodes);
    bool Parse(const char * source = NULL, swUI32 size = 0);

    swUI16 IdentifyElement(const char * source, bool isTag = true)
    {
        if (!source || !m_elementArray || !m_elementItems || !m_elementAlphaIdx)
            return INT_UNKNOWN;

        if (isTag && source[0] != '<')
            return INT_TEXT_RUN;

        char buf[256];
        int bufPos = 0;

        const char * p = source;

        p ++;

        if (*p == '/' || *p == '?')
            p ++;

        while (*p != '\0' && *p != '>' && !isspace(*p) && *p != '/' && bufPos < 256)
        {
            buf[bufPos] = *p;
            p ++;
            bufPos ++;
        }

        buf[bufPos] = '\0';

        int idxPos;
        char ch = *buf;

        if (isalpha(ch))
        {
            if (stricmp("binary", buf) == 0)
                return INT_BINARY;
            if (stricmp("module", buf) == 0)
                return INT_MODULE;

            ch = tolower(*buf);

            if (ch < 'a' || ch > 'z')
                return INT_UNKNOWN;

            idxPos = m_elementAlphaIdx[ch - 'a'];

            if (idxPos < 0)
                return INT_UNKNOWN;

            while (idxPos < m_elementItems)
            {
                if (m_elementArray[idxPos].name[0] > ch)
                    return INT_UNKNOWN;

                if (stricmp(m_elementArray[idxPos].name, buf) == 0)
                    return m_elementArray[idxPos].elementId;

                idxPos ++;
            }
        }
        else
        {
            idxPos = 0;
            while (idxPos < m_elementItems)
            {
                if (stricmp(m_elementArray[idxPos].name, buf) == 0)
                    return m_elementArray[idxPos].elementId;

                idxPos ++;
            }
        }

        return INT_UNKNOWN;
    }

    bool DoesNodeBeginThMLDiv(swUI32 node);
    bool IsNodeThMLDiv(swUI32 node);
    swUI32 GetThMLDivBreakNode(swUI32 nodeStart);
    bool IsTableRow(swUI16 element);
    bool IsTableHeader(swUI16 element);
    bool IsTableFooter(swUI16 element);
    bool IsTableCell(swUI16 element);
    bool IsTableBody(swUI16 element);
    bool IsTable(swUI16 element);
    bool IsImage(swUI16 element);
    bool IsAudio(swUI16 element);
    bool IsVideo(swUI16 element);
    bool IsPre(swUI16 element);
    bool IsParagraph(swUI16 element);
    bool IsBlockQuote(swUI16 element);
    bool IsStandardDiv(swUI16 element);
    bool IsStyle(swUI16 element);
    bool IsInformation(swUI16 element);
    bool IsList(swUI16 element);
    bool IsNote(swUI16 element);
    bool IsHeading(swUI16 element);
    bool CountRowCells();
    bool CountRowCells(swUI32 node);
    bool CountTableRows();
    bool CountTableRows(swUI32 node);
    bool CollectTableData();

    swUI32 GetLastParserNode()
    {
        return m_parserNodePos -1;
    }

    swUI32 GetParserNodes()
    {
        return m_parserNodePos;
    }

    bool ResetNodeData();
    bool UpdateNodeData();

    void UpdateNodePosData(swUI32 nodeStart, swUI32 change, bool type)
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

    virtual void OnNodeDataUpdate() {};
    void ShiftNodesUp(swUI32 startNode);
    void ShiftNodesUp(swUI32 startNode, swUI32 nodes);
    bool ShiftNodesDown(swUI32 startNode);
    bool ShiftNodesDown(swUI32 startNode, swUI32 nodes);
    bool MateElements();
    bool FixMissingMates();
    bool ParentElements();
    bool SetFirstChild();
    bool SetNextSibling();

    swUI16 GetNodeElementIdentifier(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_ID_INVALID_16;

        return m_parserNodeData[node].elementIdentifier;
    }

    swUI8 GetNodeType(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_TYPE_INVALID;

        return m_parserNodeData[node].nodeType;
    }

    swUI8 GetNodeType(const char * nodeData)
    {
        if (!nodeData)
            return NODE_TYPE_INVALID;

        const char * tag = strchr(nodeData, '<');

        if (tag)
        {
            if (tag[1] == '/')
                return NODE_TYPE_END_TAG;
            else if (strstr(tag, "/>") || strstr(tag, "?>"))
                return NODE_TYPE_UNPAIRED_TAG;
            else
                return NODE_TYPE_BEGIN_TAG;
        }

        return NODE_TYPE_TEXT_RUN;
    }

    void SetNodeType(swUI32 node, swUI8 type)
    {
        if (node >= m_parserNodePos)
            return;

        m_parserNodeData[node].nodeType = type;
    }

    swUI32 GetNodeStreamPosition(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return 0;

        return m_parserNodeData[node].beginPos;
    }

    swUI32 GetNodeDataSize(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return 0;

        return (m_parserNodeData[node].endPos - m_parserNodeData[node].beginPos) + 1;
    }

    swUI32 GetNodesDataSize(swUI32 nodeBegin, swUI32 nodeEnd);
    swUI32 GetDataSizeBetweenMates(swUI32 node, bool includeMates = true);

    SwParserNodeData * GetNode(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NULL;

        return &m_parserNodeData[node];
    }

    bool GetNodeData(swUI32 node, SwString & dest);
    bool GetNodesData(SwNodeRange & nr, SwString & dest);
    bool GetNodesData(swUI32 nodeBegin, swUI32 nodeEnd, SwString & dest);
    bool GetDataBetweenMates(swUI32 node, SwString & dest, bool includeMates = true);

    bool GetNamedValueFromNode(swUI32 node, const char * name, SwString & dest)
    {
        if (!name || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
            return false;

        SwString tag;

        swUI32 result = GetNodeDataSize(node);

        if (result < 1)
            return false;

        if (!dest.Size(result + 1))
            return false;

        dest.SetAt(0, '\0');

        if (!GetNodeData(node, tag))
            return false;

        if (!GetNamedValue(name, tag, dest))
            return false;

        return true;
    }

    bool GetNamedValueFromNode(swUI32 node, const char * name, char * dest, swUI32 bufferLen);

    bool InsertNamedValueInNode(swUI32 node, const char * name, const char * value)
    {
        if (!name || !value || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
            return false;

        SwString buffer, format;
        swUI32 insertPos;

        if (!name || !value || !GetNodeData(node, buffer))
            return false;

        insertPos = FindInsertPosition(buffer);

        if(insertPos == 0)
            return false;

        format.Size(5 + strlen(value) + strlen(name));
        sprintf(format, " %s=\"%s\" ", name, value);
        SwString::Insert(buffer, format, insertPos);
        buffer.Despace();
        SwString::Replace(buffer, strlen(buffer), " >", 2, ">", 1);

        return ReplaceNode(node, buffer);
    }

    bool InsertAttributeInNode(swUI32 node, const char * attribute);

    bool SetNamedValueInNode(swUI32 node, const char * name, const char * value)
    {
        if (!name || !value || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
            return false;

        if (!name || !value || !DeleteNamedValueFromNode(node, name))
            return false;

        return InsertNamedValueInNode(node, name, value);
    }

    bool DeleteNamedValueFromNode(swUI32 node, const char * name)
    {
        if (!name || GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
            return false;

        SwString buffer;
        swUI32 begin, end;

        if (!name || !GetNodeData(node, buffer))
            return false;

        if (!GetNamedValuePos(buffer, name, begin, end))
            return false;

        if (begin > 0 && buffer.GetAt(begin - 1) == ' ')
            begin --;

        SwString::Delete(buffer, begin, (end - begin) + 1);
        buffer.Despace();
        return ReplaceNode(node, buffer, true);
    }

    swUI8 GetElementType(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_ID_INVALID_8;

        return m_elementArray[m_parserNodeData[node].elementIdentifier].elementType;
    }

    bool GetElementStrFromNode(swUI32 node, SwString & dest)
    {
        if (GetNodeType(node) == NODE_TYPE_BINARY || GetNodeType(node) == NODE_TYPE_TEXT_RUN)
            return false;

        SwString data;

        if (node > GetLastParserNode())
            return false;

        if (!GetNodeData(node, data))
            return false;

        int pos = 0;
        // First char should be <.
        int start = 1;

        if (data.GetAt(1) == '/')
            start ++;

        while (!isspace(data.GetAt(pos)) && data.GetAt(pos) != '\0' && data.GetAt(pos) != '/' && data.GetAt(pos) != '>')
            pos ++;

        data.SetAt(pos, '\0');
        dest.Copy(data + start);

        return true;
    }

    bool GetElementStrFromNode(swUI32 node, char * dest, swUI32 bufferLen);

    swUI32 GetNodeMate(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_ID_INVALID;

        return m_parserNodeData[node].nodeMate;
    }

    swUI32 GetNodeParent(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_ID_INVALID;

        return m_parserNodeData[node].nodeParent;
    }

    swUI32 GetFirstChild(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_ID_INVALID;

        return m_parserNodeData[node].nodeFirstChild;
    }

    swUI32 GetNextSibling(swUI32 node)
    {
        if (node >= m_parserNodePos)
            return NODE_ID_INVALID;

        return m_parserNodeData[node].nodeNextSibling;
    }

    swUI32 GetNextSiblingOfType(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType);
    swUI32 FindElement(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType);
    swUI32 FindElementUpWard(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType);
    swUI32 FindElementXN(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType, swUI32 count, swUI32 * found = NULL);
    swUI32 FindWithInElement(swUI32 nodeParent, swUI32 nodeOffSet, swUI16 elementId, swUI8 nodeType);
    swUI32 GetTitle(SwString & dest);
    swUI32 GetTitle(char * dest, swUI32 bufferLen);
    void SetPath(const char * path);
    const char * GetPath();
    void SetBasePath(const char * path);
    const char * GetBasePath();
    bool SetElementArray(SwElement * elementArray, swI16 * alphaIndex, swI16 elementItems, swUI8 markupType);
    bool SetThML_ElementArray();

    bool BufferAppend(const char * data, swUI32 bytes)
    {
        if (!data || !bytes)
            return false;

        if (m_bufferSize <= m_dataSize + bytes && !SizeBuffer(m_dataSize + bytes + 1 + m_extraBytes))
            return false;

        memcpy(m_buffer+m_dataSize, data, bytes);
        m_buffer[m_dataSize + bytes] = '\0';
        return true;
    }

    bool FileAppend(const char * data, swUI32 bytes);
    swUI32 AppendNode(const char * nodeData, bool update = true, swUI32 size = 0);
    swUI32 AppendNodes(const char * nodeData, bool update = true, swUI32 size = 0);
    swUI32 AppendBinaryNodes(const char * name, const char * nodeData, bool update = true, swUI32 size = 0);

    bool BufferInsert(swUI32 pos, const char * data, swUI32 bytes)
    {
        // Insertion.

        if (!data || (m_dataSize + bytes >= m_bufferSize && !SizeBuffer(m_dataSize + bytes + 1 + m_extraBytes)))
            return false;

        swUI32 moveBytes = (m_dataSize + 1 - pos);

        // Move characters from position point, and right of insertion
        // position, the required number of char's to the right.
        memmove(m_buffer + pos + bytes, m_buffer + pos, moveBytes);
        memcpy(m_buffer + pos, data, bytes);

        return true;
    }

    bool FileInsert(swUI32 pos, const char * data, swUI32 length);
    bool InsertNode(swUI32 nodePos, const char * nodeData, bool update = true, swUI32 size = 0);
    bool InsertNodes(swUI32 nodePos, const char * nodeData, bool update = true, swUI32 size = 0);

    bool BufferDelete(swUI32 pos, swUI32 bytes)
    {
        if (m_buffer == NULL || pos >= m_dataSize)
            return false;

        // If deletion exceeds length of data, insert '\0' at
        // deletion point.
        if (pos + bytes >= m_dataSize)
        {
            m_buffer[pos] = '\0';
            //m_dataSize = pos;
            return true;
        }

        // Move all characters from deletion point, and to the right of
        // deletion point to the left, including null terminator.
        swUI32 moveBytes = (m_dataSize + 1 - (pos + bytes));
        memmove(m_buffer + pos, m_buffer + pos + bytes, moveBytes);

        return true;
    }

    bool FileDelete(swUI32 pos, swUI32 bytes);
    bool DeleteNode(swUI32 nodePos, bool update = true);
    bool DeleteNodes(swUI32 nodeBegin, swUI32 nodeEnd, bool update = true);

    bool BufferReplace(swUI32 pos, swUI32 bytes, const char * data, swUI32 newBytes)
    {
        if (m_buffer == NULL || !data)
            return false;

        if (bytes == newBytes)
        {
            memcpy(m_buffer + pos, data, newBytes);
            return true;
        }
        else if (newBytes > bytes && m_dataSize + (newBytes - bytes) >= m_bufferSize && !SizeBuffer(m_dataSize + (newBytes - bytes) + 1 + m_extraBytes))
            return false;

        swUI32 moveBytes = (m_dataSize + 1 - (pos + bytes));

        memmove(m_buffer + pos + newBytes, m_buffer + pos + bytes, moveBytes);
        memcpy(m_buffer + pos, data, newBytes);

        return true;
    }

    bool FileReplace(swUI32 pos, swUI32 bytes, const char * data, swUI32 newBytes);

    bool ReplaceNode(swUI32 nodePos, const char * nodeData, bool update = true, swUI32 size = 0)
    {
        if ((m_mode == MODE_MEMORY && m_sourceBuffer != m_buffer) || m_mode == MODE_FS_CONT || !nodeData || nodePos > GetLastParserNode())
            return false;

        swUI32 bytes;

        if (size == 0)
            bytes = strlen(nodeData);
        else
            bytes = size;

        bool status;

        if (m_mode == MODE_MEMORY)
            status = BufferReplace(m_parserNodeData[nodePos].beginPos, GetNodeDataSize(nodePos), nodeData, bytes);
        else
            status = FileReplace(m_parserNodeData[nodePos].beginPos, GetNodeDataSize(nodePos), nodeData, bytes);

        if (!status)
            return false;

        if (bytes < GetNodeDataSize(nodePos))
        {
            m_dataSize -= GetNodeDataSize(nodePos) - bytes;
            if (nodePos != GetLastParserNode())
                UpdateNodePosData(nodePos + 1, GetNodeDataSize(nodePos) - bytes, false);
        }
        else if (bytes > GetNodeDataSize(nodePos))
        {
            m_dataSize += bytes - GetNodeDataSize(nodePos);
            if (nodePos != GetLastParserNode())
                UpdateNodePosData(nodePos + 1, bytes - GetNodeDataSize(nodePos), true);
        }

        m_parserNodeData[nodePos].endPos = m_parserNodeData[nodePos].beginPos + bytes - 1;

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
            if (GetNodeMate(nodePos) != NODE_ID_INVALID)
                m_parserNodeData[GetNodeMate(nodePos)].nodeType = NODE_TYPE_UNPAIRED_TAG;

        }

        if (update)
            UpdateNodeData();

        m_modified = true;
        return true;
    }

    bool ReplaceNodes(swUI32 nodeBegin, swUI32 nodeEnd, const char * nodeData, bool update = true, swUI32 size = 0);
    bool MoveNode(swUI32 node, swUI32 newPos, bool update = true);
    bool MoveNodes(swUI32 nodeBegin, swUI32 nodeEnd, swUI32 newPos, bool update = true);
    bool Defragment();
    bool CollectThMLDivNotes(swUI32 divNode, SwString & buffer);
    bool ReplaceThMLDivNotes(swUI32 divNode);
    bool ProcessThMLNotes();
    size_t WriteParserSizeToFile(FILE & file);
    size_t ReadParserSizeFromFile(FILE & file, swUI32 & nodes);
    size_t WriteParserToFile(FILE & file);
    size_t ReadParserNodeDataFromFile(FILE & file, swUI32 nodes);
    bool LoadParserFromFile(const char * dataFile, const char * sourceFile);
    swUI32 FindNodeById(swUI32 nodeOrigin, swUI32 nodeBreak, char * id);
    swUI32 FindNodeByStreamPos(swUI32 streamPos);
    swUI32 GetXmlId(swUI32 startPos, swUI32 endPos);
    swUI32 GetXmlId(const char * src);
    static swUI32 GenerateId(const char * name);
    bool GetInnerText(swUI32 node, SwString & buffer);
    swUI8 GetInnerMediaPath(swUI32 node, SwString & buffer);
    bool GetCaseSensitive();
    void SetCaseSensitive(bool caseSensitive);
    bool GetCleanWhiteSpace();
    void SetCleanWhiteSpace(bool cleanwhiteSpace);
    bool GetThMLScriptureIdFromNode(swUI32 node, swUI8 & book, swUI8 & chapter, swUI8 & verse);
    bool DoesThMLDivHaveChildDiv(swUI32 nodePos);
    const char * GetElementString(swUI32 node);
    swUI32 GetTrailingLineBreaks(swUI32 node);
    bool IsWithIn(swUI32 node, swUI16 element);
    bool IsChildOf(swUI32 node, swUI16 element);
    bool IsNext(swUI32 node, swUI16 element);
    bool IsFirstChild(swUI32 node);
    bool IsPreceededBy(swUI32 node, swUI16 element);
    void Containorize(swUI16 element, const char * namestr);
    swUI8 GetMarkupType();
    void SetMarkupType(swUI8 markup);
    void SetExtraBytes(swUI16 extra);
    swUI32 FindDataList(const char * id);
    void ReplaceDataList(const char * id, const char * data);
    void FixEndPos();
    bool CheckParserIntegrity();
    swI16 GetListItems(swUI32 node);
    void Restructure();
    swUI32 FindFirstChildDivision(swUI32 node);
    void RemoveTags(swUI16 element);
    void SetProcessXmlId(bool process);
    void SetProcessTableData(bool process);

    char * GetBuffer()
    {
        return m_buffer;
    }

    const char * GetSourceBuffer()
    {
        return m_sourceBuffer;
    }

    swUI32 GetDataSize();
    void SetDataSize(swUI32 size);
    bool HaveNotesBeenProcessed();
    virtual void SetRange(swUI32 range);
    virtual bool UpdateUI(swUI32 pos);
    void SetProgressData(SwProgressData * data);
    void SetProgressTextData(const char * data);
    void SetWindow(wxWindow * window);
    bool WriteNodeData(swUI32 node, wxRichTextCtrl & ctrl);
    void GetDataListItems(wxListCtrl * listctrl, const char * id);
    swUI8 GetPassageData(swUI32 node, SwScriptureRange & scriptRange);
    bool FindScriptureRange(SwScriptureRange & scriptRange, SwNodeRange & nodeRange);

    static bool GetNamedValue(const char * name, const char * source, SwString & dest);
    static bool GetNamedValuePos(const char * source, const char * name, swUI32 & begin, swUI32 & end);
    static bool DeleteNamedValue(SwString & tag, const char * name, bool despace);
    static bool InsertNamedValue(SwString & tag, const char * name, const char * value, bool despace);
    static bool InsertAttribute(SwString & tag, const char * attribute, bool despace);
    static swUI32 FindInsertPosition(const char * tag);

protected:
    SwParserNodeData *          m_parserNodeData;
    swUI32                      m_parserNodePos;
    char *                      m_base;
    SwElement *                 m_elementArray;
    swI16 *                     m_elementAlphaIdx;
    swI16                       m_elementItems;
    swUI8                       m_markupType;
    bool                        m_processXmlId;
    char *                      m_buffer;
    swUI32                      m_bufferSize;
    swUI32                      m_dataSize;
    const char *                m_sourceBuffer;
    bool                        m_processtableData;
    bool                        m_modified;
    swUI32                      m_parserNodesAllocated;
    swUI16                      m_parserInc;
    char *                      m_path;
    swUI8                       m_mode;
    swUI16                      m_extraBytes;
    FILE *                      m_file;

    SwProgressData * m_progress;
    wxWindow * m_window;
};

enum MARKUP_TYPE
{
    MARKUP_UNKNOWN, MARKUP_NONE, MARKUP_HTML,
    MARKUP_THML, MARKUP_SWGUI,
    N_MARKUP
};

class SOWERBASEEXP SwMarkUpType
{
public:
    SwMarkUpType();
    virtual ~SwMarkUpType();
    static const char * GetId(swUI8 mkl);
    static const char * GetString(swUI8 mkl);
    static const wchar_t * GetStringW(swUI8 mkl);
    static swUI8 GetMarkUpTypeType(wxChoice * choice);
    static swUI8 GetMarkUpType(const char * value);
    static void GetMarkUpTypeList(wxChoice * choice);
};

#endif // THMLPARSER_H
