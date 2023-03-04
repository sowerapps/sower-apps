///////////////////////////////////////////////////////////////////
// Name:        bookidentifier.cpp
// Purpose:     Data container for biblical book names, and
//              abbreviations. This container can import it's
//              data from a file created by Sower Table Editor,
//              and save it's data as a Sower Binary Object and
//              load it's data without the need for import.
//              In the data file identifiers can be standard book
//              names (Genesis, Exodus). The data parameter can
//              be multiple entries separated with '|' (Genesis|Gen|Ge).
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/bible/bookidentifier.h"
#include "../../include/bible/standard_bible.h"
#include "../../include/string/string.h"
#include "../../include/string/strparser.h"
#include "../../include/module/moduleinterface.h"

static const char * bookobjectid = "bidf";

void SwBookIdNode::Reset()
{
    identifier = NODE_ID_INVALID_8;
    bufferPos = 0;
}

SwBookIdentifier::SwBookIdentifier()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_Inc = 25;
    m_buffer = NULL;
    m_bufferSize = 0;
    m_dataSize = 0;
    m_alphaIndex = NULL;
    m_alphaIndexSize = 0;
    m_alphaIndexPos = 0;
}

SwBookIdentifier::~SwBookIdentifier()
{
    if (m_nodeData)
        free(m_nodeData);

    if (m_buffer)
        free(m_buffer);

    if (m_alphaIndex)
        free(m_alphaIndex);
}

void SwBookIdentifier::SetIncrement(swUI8 increment)
{
    if (increment < 25)
        m_Inc = 25;
    else
        m_Inc = increment;
}

bool SwBookIdentifier::IncreaseAlphaIdx()
{
    swUI8 increase = m_Inc;

    if (!m_Inc)
        increase = 12;

    return SizeAlphaIdx(m_alphaIndexSize + increase);
}

bool SwBookIdentifier::SizeAlphaIdx(swUI16 size)
{
    if (!size && m_alphaIndex)
    {
        free(m_alphaIndex);
        m_alphaIndex = NULL;
        m_alphaIndexSize = 0;
        return true;
    }

    SwAlphaData * p = (SwAlphaData *) realloc((void *) m_alphaIndex, size * sizeof(SwAlphaData));

    if (p)
    {
        m_alphaIndex = p;
        m_alphaIndexSize = size;

        for (swUI32 i = m_alphaIndexPos; i < m_alphaIndexSize; i++)
            m_alphaIndex[i].Reset();

        return true;
    }

    return false;
}

bool SwBookIdentifier::SizeBuffer(swUI32 size)
{
    if (!size && m_buffer)
    {
        free(m_buffer);
        m_buffer = NULL;
        m_bufferSize = 0;
        return true;
    }

    wchar_t * p = (wchar_t *) realloc((void *) m_buffer, size * sizeof(wchar_t));

    if (p)
    {
        m_bufferSize = size;
        m_buffer = p;
        return true;
    }

    return false;
}

bool SwBookIdentifier::IncreaseNodeArray()
{
    swUI16 increase = m_Inc;

    if (!m_Inc)
        increase = 100;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwBookIdentifier::SizeNodeArray(swUI16 nodes)
{
    if (!nodes && m_nodeData)
    {
        free(m_nodeData);
        m_nodeData = NULL;
        m_nodePos = 0;
        m_nodesAllocated = 0;
        return true;
    }

    if (nodes >= NODE_ID_INVALID_16)
        return false;

    SwBookIdNode * p = (SwBookIdNode *) realloc((void *) m_nodeData, nodes * sizeof(SwBookIdNode));

    if (p)
    {
        m_nodesAllocated = nodes;
        m_nodeData = p;

        for (swUI32 i = m_nodePos; i < m_nodesAllocated; i++)
            m_nodeData[i].Reset();

        return true;
    }

    return false;
}

bool SwBookIdentifier::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    m_nodeData[m_nodePos].Reset();

    return true;
}

bool SwBookIdentifier::VerifyNodes(swUI16 nodes)
{
    if (nodes + m_nodePos + 1 > m_nodesAllocated && !SizeNodeArray(nodes + m_nodePos + 1 + m_Inc))
        return false;

    for (swUI32 i = m_nodePos; i < m_nodePos + nodes; i++)
        m_nodeData[i].Reset();

    return true;
}

bool SwBookIdentifier::VerifyAlphaNode()
{
    if (m_alphaIndexPos >= m_alphaIndexSize && !IncreaseAlphaIdx())
        return false;

    m_alphaIndex[m_alphaIndexPos].Reset();
    return true;
}

bool SwBookIdentifier::VerifyAlphaNodes(swUI16 nodes)
{
    if (nodes + m_alphaIndexPos + 1 > m_alphaIndexSize && !SizeAlphaIdx(nodes + m_alphaIndexPos + 1 + m_Inc))
        return false;

    for (swUI32 i = m_alphaIndexPos; i < m_alphaIndexPos + nodes; i++)
        m_alphaIndex[i].Reset();

    return true;
}

swUI16 SwBookIdentifier::GetLastNode()
{
    return m_nodePos -1;
}

swUI16 SwBookIdentifier::GetNodes()
{
    return m_nodePos;
}

void SwBookIdentifier::Reset()
{
    ResetNodeData();
    ResetAlphaIdx();
    m_nodePos = 0;
}

void SwBookIdentifier::ResetNodeData()
{
    // Reset parts of node data that will be modified
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].Reset();

        pos ++;
    }
}

void SwBookIdentifier::ResetAlphaIdx()
{
    swUI16 pos = 0;

    while (pos < m_alphaIndexSize)
    {
        m_alphaIndex[pos].Reset();

        pos ++;
    }

    m_alphaIndexPos = 0;
}

bool SwBookIdentifier::AddToAlphaIndex(wchar_t wc, swUI16 identifier)
{
    if (!VerifyAlphaNode())
        return false;

    m_alphaIndex[m_alphaIndexPos].character = towlower(wc);
    m_alphaIndex[m_alphaIndexPos].indexpos = identifier;

    m_alphaIndexPos ++;

    return true;
}

swUI16 SwBookIdentifier::FindInIndex(wchar_t wc)
{
    wchar_t lwc = towlower(wc);
    for (swUI16 i = 0; i < m_alphaIndexPos; i ++)
    {
        if (m_alphaIndex[i].character == lwc)
            return i;
    }

    return NODE_ID_INVALID_16;
}

bool SwBookIdentifier::UpdateAlphaIdx()
{
    swUI16 pos = 0;

    ResetAlphaIdx();

    while (pos < m_nodePos)
    {

        if (FindInIndex(m_buffer[m_nodeData[pos].bufferPos]) == NODE_ID_INVALID_16)
        {
            AddToAlphaIndex(m_buffer[m_nodeData[pos].bufferPos], pos);
        }

        pos ++;
    }

    return true;
}

void SwBookIdentifier::UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type)
{
    // type == true for increase, type == false for decrease
    swUI16 pos = 0;
    pos = nodeStart;

    if (type)
    {
        while (pos < m_nodePos)
        {
            m_nodeData[pos].bufferPos += change;
            pos ++;
        }
    }
    else
    {
        while (pos < m_nodePos)
        {
            m_nodeData[pos].bufferPos -= change;
            pos ++;
        }
    }
}

void SwBookIdentifier::ShiftNodesUp(swUI16 startNode)
{
    if (m_nodePos <= 1)
    {
        m_nodePos = 0;
        return;
    }
    else if (startNode == 0)
        return;
    else if (startNode > GetLastNode())
    {
        return;
    }

    swUI16 pos = startNode;

    while(pos < m_nodePos)
    {
        m_nodeData[pos - 1] = m_nodeData[pos];
        pos ++;
    }

    m_nodePos --;
}

bool SwBookIdentifier::ShiftNodesDown(swUI16 startNode)
{
    if (startNode > GetLastNode())
        return false;

    if (!VerifyNode())
        return false;

    swUI16 pos = m_nodePos;

    while(pos > startNode)
    {
        m_nodeData[pos] = m_nodeData[pos - 1];
        pos --;
    }

    m_nodePos ++;
    return true;
}

swUI16 SwBookIdentifier::GetNodeTextSize(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_16;

    return wcslen(&m_buffer[m_nodeData[node].bufferPos]) + 1;
}

SwBookIdNode * SwBookIdentifier::GetNode(swUI16 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

bool SwBookIdentifier::GetNodeText(swUI16 node, SwStringW & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetNodeTextSize(node)))
        return false;

    dest.SetAt(0, L'\0');

    wmemcpy(dest, m_buffer + m_nodeData[node].bufferPos, GetNodeTextSize(node));

    return true;
}

bool SwBookIdentifier::GetNodeText(swUI16 node, wchar_t * dest)
{
    if (node >= m_nodePos)
        return false;

    *dest = L'\0';

    wmemcpy(dest, m_buffer + m_nodeData[node].bufferPos, GetNodeTextSize(node));

    return true;
}

bool SwBookIdentifier::SetNodeText(swUI16 node, const char * itemText, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return SetNodeText(node, buffer, update);
}

bool SwBookIdentifier::SetNodeText(swUI16 node, const wchar_t * itemText, bool update)
{
    if (!itemText || node > GetLastNode())
        return false;

    swUI8 identifier = GetNodeIdentifier(node);

    swUI32 size = wcslen(itemText);

    bool status = BufferReplace(m_nodeData[node].bufferPos, GetNodeTextSize(node), itemText, size);

    if (!status)
        return false;

    if (size < GetNodeTextSize(node))
    {
        m_dataSize -= GetNodeTextSize(node) - size;

        if (node != GetLastNode())
            UpdateNodePosData(node + 1, GetNodeTextSize(node) - size, false);
    }
    else if (size > GetNodeTextSize(node))
    {
        m_dataSize += size - GetNodeTextSize(node);

        if (node != GetLastNode())
            UpdateNodePosData(node + 1, size - GetNodeTextSize(node), true);
    }

    m_nodeData[node].identifier = identifier;

    if (update)
        UpdateAlphaIdx();

    return true;
}

swUI8 SwBookIdentifier::GetNodeIdentifier(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_8;

    return m_nodeData[node].identifier;
}

bool SwBookIdentifier::SetNodeIdentifier(swUI16 node, swUI8 identifier)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].identifier = identifier;

    return true;
}

bool SwBookIdentifier::BufferAppend(const wchar_t * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_bufferSize <= m_dataSize + size && !SizeBuffer(m_dataSize + size))
        return false;

    wmemcpy(m_buffer + m_dataSize, data, size);

    return true;
}

swUI16 SwBookIdentifier::AppendNode(const char * itemText, swUI8 identifier, bool update)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    SwStringW buffer;
    buffer.Copy(itemText);

    return AppendNode(buffer, identifier, update);
}

swUI16 SwBookIdentifier::AppendNode(const wchar_t * itemText, swUI8 identifier, bool update)
{
    if (!itemText || !VerifyNode())
        return NODE_ID_INVALID_16;

    swUI16 size = wcslen(itemText) + 1;

    bool status = BufferAppend(itemText, size);

    if (!status)
        return NODE_ID_INVALID_16;

    m_nodeData[m_nodePos].bufferPos = m_dataSize;
    m_nodeData[m_nodePos].identifier = identifier;

    m_dataSize += size;
    m_nodePos ++;

    if (update)
        UpdateAlphaIdx();

    return m_nodePos - 1;
}


bool SwBookIdentifier::BufferInsert(swUI32 pos, const wchar_t * data, swUI16 size)
{
    // Insertion.
    if (m_dataSize + size >= m_bufferSize && !SizeBuffer(m_dataSize + size))
        return false;

    swUI32 moveSize = (m_dataSize - pos);

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    wmemmove(m_buffer + pos + size, m_buffer + pos, moveSize);
    wmemcpy(m_buffer + pos, data, size);

    return true;
}

bool SwBookIdentifier::InsertNode(swUI16 nodePos, const char * itemText, swUI8 identifier, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return InsertNode(nodePos, buffer, identifier, update);
}

bool SwBookIdentifier::InsertNode(swUI16 nodePos, const wchar_t * itemText, swUI8 identifier, bool update)
{
    if (!itemText)
        return false;

    if (nodePos > m_nodePos - 1)
    {
        if (AppendNode(itemText, identifier, update) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    if (!ShiftNodesDown(nodePos))
        return false;

    swUI16 size = wcslen(itemText) + 1;

    bool status = BufferInsert(m_nodeData[nodePos].bufferPos, itemText, size);

    if (!status)
    {
        ShiftNodesUp(nodePos + 1);
        return false;
    }

    m_nodeData[nodePos].identifier = identifier;

    m_dataSize += size;
    UpdateNodePosData(nodePos + 1, size, true);

    if (update)
        UpdateAlphaIdx();

    return true;
}

bool SwBookIdentifier::BufferDelete(swUI32 pos, swUI16 size)
{
    if (m_buffer == NULL || pos >= m_dataSize)
        return false;

    // If deletion exceeds length of data, insert '\0' at
    // deletion point.
    if (pos + size >= m_dataSize)
    {
        m_buffer[pos] = L'\0';
//        m_dataSize = pos;
        return true;
    }

    // Move all characters from deletion point, and to the right of
    // deletion point to the left, including null terminator.
    swUI32 moveSize = (m_dataSize - (pos + size));
    wmemmove(m_buffer + pos, m_buffer + pos + size, moveSize);

    return true;
}

bool SwBookIdentifier::DeleteNode(swUI16 node, bool update)
{
    if (node > GetLastNode())
        return false;

    swUI32 change = GetNodeTextSize(node);

    bool status = BufferDelete(m_nodeData[node].bufferPos, change);

    if (!status)
        return false;

    m_dataSize -= change;

    if (node != GetLastNode())
    {
        ShiftNodesUp(node + 1);
        UpdateNodePosData(node, change, false);
    }
    else
        m_nodePos --;

    if (update)
        UpdateAlphaIdx();

    return true;
}

bool SwBookIdentifier::BufferReplace(swUI32 pos, swUI16 size, const wchar_t * data, swUI16 newSize)
{
    if (m_buffer == NULL || !data)
        return false;

    if (size == newSize)
    {
        wmemcpy(m_buffer + pos, data, newSize);
        return true;
    }
    else if (newSize > size && m_dataSize + (newSize - size) >= m_bufferSize && !SizeBuffer(m_dataSize + (newSize - size) + 1))
        return false;

    swUI32 moveSize = (m_dataSize - (pos + size));

    wmemmove(m_buffer + pos + newSize, m_buffer + pos + size, moveSize);
    wmemcpy(m_buffer + pos, data, newSize);

    return true;
}

bool SwBookIdentifier::ReplaceNode(swUI16 node, const char * itemText, swUI8 identifier, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return ReplaceNode(node, buffer, identifier, update);
}

bool SwBookIdentifier::ReplaceNode(swUI16 node, const wchar_t * itemText, swUI8 identifier, bool update)
{
    if (!itemText || node > GetLastNode())
        return false;

    swUI16 size = wcslen(itemText);

    bool status = BufferReplace(m_nodeData[node].bufferPos, GetNodeTextSize(node), itemText, size);

    if (!status)
        return false;

    if (size < GetNodeTextSize(node))
    {
        m_dataSize -= GetNodeTextSize(node) - size;

        if (node != GetLastNode())
            UpdateNodePosData(node + 1, GetNodeTextSize(node) - size, false);
    }
    else if (size > GetNodeTextSize(node))
    {
        m_dataSize += size - GetNodeTextSize(node);

        if (node != GetLastNode())
            UpdateNodePosData(node + 1, size - GetNodeTextSize(node), true);
    }

    m_nodeData[node].identifier = identifier;

    if (update)
        UpdateAlphaIdx();

    return true;
}

bool SwBookIdentifier::MoveNode(swUI16 node, swUI16 newPos, bool update)
{
    SwStringW buffer;

    if (!GetNodeText(node, buffer))
        return false;

    swUI16 identifier = GetNodeIdentifier(node);

    if(!DeleteNode(node, update))
        return false;

    return InsertNode(newPos, buffer, identifier, update);
}


swUI16 SwBookIdentifier::LocatePosition(wchar_t ch)
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        if (m_buffer[m_nodeData[pos].bufferPos] >= ch)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwBookIdentifier::AddNode(const char * itemText, swUI8 identifier, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return AddNode(buffer, identifier, update);
}

bool SwBookIdentifier::AddNode(const wchar_t * itemText, swUI8 identifier, bool update)
{
    if (!itemText)
        return false;

    swUI16 pos = LocatePosition(*itemText);

    if (pos == NODE_ID_INVALID_16)
    {
        if (AppendNode(itemText, identifier, update) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    return InsertNode(pos, itemText, identifier, update);
}

swUI8 SwBookIdentifier::FindItem(const char * itemText)
{
    if (!itemText)
        return 0;

    SwStringW buffer;
    buffer.Copy(itemText);

    return FindItem(buffer);
}

swUI8 SwBookIdentifier::FindItem(const wchar_t * itemText)
{
    if (!itemText)
        return NODE_ID_INVALID_8;

    swUI16 idx = FindInIndex(*itemText);

    if (idx == NODE_ID_INVALID_8)
        return NODE_ID_INVALID_8;

    idx = m_alphaIndex[idx].indexpos;

    wchar_t a, b;
    a = towlower(*itemText);

    while (idx < m_nodePos)
    {
        b = towlower(m_buffer[m_nodeData[idx].bufferPos]);
        if (a != b)
            break;

        if (wcsicmp(itemText, &m_buffer[m_nodeData[idx].bufferPos]) == 0)
        {
            return m_nodeData[idx].identifier;
        }

        idx ++;
    }

    return NODE_ID_INVALID_8;
}

bool SwBookIdentifier::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    if (fwrite((void *) bookobjectid, sizeof(char), 4, file) != 4)
        return false;

    if (fwrite((void *) &m_dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!SwModuleInterface::WriteUtf16Data(file, m_dataSize, m_buffer))
        return false;
    if (m_nodePos && fwrite((void *) m_nodeData, sizeof(SwBookIdNode), m_nodePos, file) != m_nodePos)
        return false;

    return true;
}

bool SwBookIdentifier::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 dataSize = 0;
    swUI16 nodePos = 0;
    char s[5];

    if (fread((void *) &s, sizeof(char), 4, file) != 4)
        return false;
    s[4] = '\0';

    if (strcmp(s, bookobjectid) != 0)
        return false;

    if (fread((void *) &dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fread((void *) &nodePos, sizeof(swUI16), 1, file) != 1)
        return false;

    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
    if (!SwModuleInterface::ReadUtf16Data(file, dataSize, m_buffer))
        return false;
    if (nodePos && fread((void *) m_nodeData, sizeof(SwBookIdNode), nodePos, file) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;

    UpdateAlphaIdx();

    return true;
}

void SwBookIdentifier::Import(SwDataFile & datafile)
{
    SwString id;
    SwString data;
    swUI8 bookId;
    SwStrParser list;
    list.SetDeliminator('|');

    for (swUI32 table = 0; table < datafile.GetTableCount(); table ++)
    {
        datafile.FillTable(table);
        for (swUI32 item = 0; item < datafile.GetTable().GetItems(); item ++)
        {
            if (!datafile.GetTable().GetNode(item)->HasId() || !datafile.GetTable().GetNode(item)->HasData())
                continue;

            id = datafile.GetTable().GetNodeId(item);
            data = datafile.GetTable().GetNodeData(item);

            bookId = SwStandardBible::IdentifyBibleBookName(id);
            if (!bookId && SwString::IsStrDigit(id))
            {
                bookId = strtoul(id, NULL, 10);
            }

            if (!bookId)
                continue;

            SwString::Replace(data, strlen(data), " ", 1, "", 0);
            list.ParseString(data);

            for (swUI32 n = 0; n < list.GetItems(); n ++)
            {
                if (!FindItem(list.GetItem(n)))
                    AddNode(list.GetItem(n), bookId);
            }
        }
    }
}
