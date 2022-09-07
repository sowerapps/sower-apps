///////////////////////////////////////////////////////////////////
// Name:        autodefterm.cpp
// Purpose:     AutodefTerm - locates/retrieves entries from dictionaries,
//              encyclopedias, topical indexes, etc.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/autodefterm.h"
#include "../../include/module/transcryptor.h"

void SwADNodeData::Reset()
{
    identifier = MITEMIDINVALID;
    bufferPos = 0;
}

bool SwADNodeData::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size + 1);

    if (!encrypted)
    {
        fseek(f, contentOffset + data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, contentOffset + (data.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.SetAt(buffer.GetCount() + data.size, '\0');
    buffer.IncrementCount(data.size);

    return true;
}

SwAutoDefTerm::SwAutoDefTerm()
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

SwAutoDefTerm::~SwAutoDefTerm()
{
    if (m_nodeData)
        free(m_nodeData);

    if (m_buffer)
        free(m_buffer);

    if (m_alphaIndex)
        free(m_alphaIndex);
}

void SwAutoDefTerm::SetIncrement(swUI8 increment)
{
    if (increment < 25)
        m_Inc = 25;
    else
        m_Inc = increment;
}

bool SwAutoDefTerm::IncreaseAlphaIdx()
{
    swUI8 increase = m_Inc;

    if (!m_Inc)
        increase = 12;

    return SizeAlphaIdx(m_alphaIndexSize + increase);
}

bool SwAutoDefTerm::SizeAlphaIdx(swUI16 size)
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

bool SwAutoDefTerm::SizeBuffer(swUI32 size)
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

bool SwAutoDefTerm::IncreaseNodeArray()
{
    swUI16 increase = m_Inc;

    if (!m_Inc)
        increase = 100;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwAutoDefTerm::SizeNodeArray(swUI16 nodes)
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

    SwADNodeData * p = (SwADNodeData *) realloc((void *) m_nodeData, nodes * sizeof(SwADNodeData));

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

bool SwAutoDefTerm::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    m_nodeData[m_nodePos].Reset();

    return true;
}

bool SwAutoDefTerm::VerifyNodes(swUI16 nodes)
{
    if (nodes + m_nodePos + 1 > m_nodesAllocated && !SizeNodeArray(nodes + m_nodePos + 1 + m_Inc))
        return false;

    for (swUI32 i = m_nodePos; i < m_nodePos + nodes; i++)
        m_nodeData[i].Reset();

    return true;
}

bool SwAutoDefTerm::VerifyAlphaNode()
{
    if (m_alphaIndexPos >= m_alphaIndexSize && !IncreaseAlphaIdx())
        return false;

    m_alphaIndex[m_alphaIndexPos].Reset();
    return true;
}

bool SwAutoDefTerm::VerifyAlphaNodes(swUI16 nodes)
{
    if (nodes + m_alphaIndexPos + 1 > m_alphaIndexSize && !SizeAlphaIdx(nodes + m_alphaIndexPos + 1 + m_Inc))
        return false;

    for (swUI32 i = m_alphaIndexPos; i < m_alphaIndexPos + nodes; i++)
        m_alphaIndex[i].Reset();

    return true;
}

swUI16 SwAutoDefTerm::GetLastNode()
{
    return m_nodePos -1;
}

swUI16 SwAutoDefTerm::GetNodes()
{
    return m_nodePos;
}

void SwAutoDefTerm::Reset()
{
    ResetNodeData();
    ResetAlphaIdx();
    m_nodePos = 0;
}

void SwAutoDefTerm::ResetNodeData()
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].Reset();

        pos ++;
    }
}

void SwAutoDefTerm::ResetAlphaIdx()
{
    swUI16 pos = 0;

    while (pos < m_alphaIndexSize)
    {
        m_alphaIndex[pos].Reset();

        pos ++;
    }

    m_alphaIndexPos = 0;
}

void SwAutoDefTerm::UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type)
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

void SwAutoDefTerm::ShiftNodesUp(swUI16 startNode)
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

bool SwAutoDefTerm::ShiftNodesDown(swUI16 startNode)
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

swUI16 SwAutoDefTerm::GetNodeTextSize(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_16;

    return wcslen(&m_buffer[m_nodeData[node].bufferPos]) + 1;
}

SwADNodeData * SwAutoDefTerm::GetNode(swUI16 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

bool SwAutoDefTerm::GetNodeText(swUI16 node, SwStringW & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetNodeTextSize(node)))
        return false;

    dest.SetAt(0, L'\0');

    wmemcpy(dest.GetArray(), m_buffer + m_nodeData[node].bufferPos, GetNodeTextSize(node));

    return true;
}

bool SwAutoDefTerm::SetNodeText(swUI16 node, const char * itemText, bool update)
{
    if (!itemText)
        return false;

    SwString buffer;
    buffer.Copy(itemText);

    return SetNodeText(node, buffer.GetArray(), update);
}

bool SwAutoDefTerm::SetNodeText(swUI16 node, const wchar_t * itemText, bool update)
{
    if (!itemText || node > GetLastNode())
        return false;

    SwModuleItemId identifier = GetNodeIdentifier(node);

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

SwModuleItemId SwAutoDefTerm::GetNodeIdentifier(swUI16 node)
{
    if (node >= m_nodePos)
        return MITEMIDINVALID;

    return m_nodeData[node].identifier;
}

bool SwAutoDefTerm::SetNodeIdentifier(swUI16 node, SwModuleItemId identifier)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].identifier = identifier;

    return true;
}

bool SwAutoDefTerm::BufferAppend(const wchar_t * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_bufferSize <= m_dataSize + size && !SizeBuffer(m_dataSize + size))
        return false;

    wmemcpy(m_buffer + m_dataSize, data, size);

    return true;
}

swUI16 SwAutoDefTerm::AppendNode(const char * itemText, SwModuleItemId identifier, bool update)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    SwStringW buffer;
    buffer.Copy(itemText);

    return AppendNode(buffer, identifier, update);
}

swUI16 SwAutoDefTerm::AppendNode(const wchar_t * itemText, SwModuleItemId identifier, bool update)
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


bool SwAutoDefTerm::BufferInsert(swUI32 pos, const wchar_t * data, swUI16 size)
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

bool SwAutoDefTerm::InsertNode(swUI16 nodePos, const char * itemText, SwModuleItemId identifier, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return InsertNode(nodePos, buffer, identifier, update);
}

bool SwAutoDefTerm::InsertNode(swUI16 nodePos, const wchar_t * itemText, SwModuleItemId identifier, bool update)
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

bool SwAutoDefTerm::BufferDelete(swUI32 pos, swUI16 size)
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

bool SwAutoDefTerm::DeleteNode(swUI16 node, bool update)
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

bool SwAutoDefTerm::BufferReplace(swUI32 pos, swUI16 size, const wchar_t * data, swUI16 newSize)
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

bool SwAutoDefTerm::ReplaceNode(swUI16 node, const char * itemText, SwModuleItemId identifier, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return ReplaceNode(node, buffer, identifier, update);
}

bool SwAutoDefTerm::ReplaceNode(swUI16 node, const wchar_t * itemText, SwModuleItemId identifier, bool update)
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

bool SwAutoDefTerm::MoveNode(swUI16 node, swUI16 newPos, bool update)
{
    SwStringW buffer;

    if (!GetNodeText(node, buffer))
        return false;

    SwModuleItemId identifier = GetNodeIdentifier(node);

    if(!DeleteNode(node, update))
        return false;

    return InsertNode(newPos, buffer, identifier, update);
}


swUI16 SwAutoDefTerm::LocatePosition(wchar_t wc)
{
    swUI16 pos = 0;

    wint_t lwc = towlower(wc);
    while (pos < m_nodePos)
    {
        if (towlower(m_buffer[m_nodeData[pos].bufferPos]) >= lwc)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwAutoDefTerm::AddToAlphaIndex(wchar_t wc, swUI16 alphaIdxPos)
{
    if (!VerifyAlphaNode())
        return false;

    m_alphaIndex[m_alphaIndexPos].character = towlower(wc);
    m_alphaIndex[m_alphaIndexPos].indexpos = alphaIdxPos;

    m_alphaIndexPos ++;

    return true;
}

swUI16 SwAutoDefTerm::FindInIndex(wchar_t wc)
{
    wchar_t lwc = towlower(wc);
    for (swUI16 i = 0; i < m_alphaIndexPos; i ++)
    {
        if (m_alphaIndex[i].character == lwc)
            return i;
    }

    return NODE_ID_INVALID_16;
}

bool SwAutoDefTerm::UpdateAlphaIdx()
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

swUI16 SwAutoDefTerm::FindAlphabeticInsertionPosition(const wchar_t * itemText)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    SwStringW data;
    int result;

    for (swUI16 i = 0; i < m_nodePos; i ++)
    {
        GetNodeText(i, data);
        result = wcsicmp(itemText, data);

        if (result < 0)
            return i;
    }

    return NODE_ID_INVALID_16;
}

bool SwAutoDefTerm::AddNode(const char * itemText, SwModuleItemId identifier, bool noDuplicates, bool update)
{
    if (!itemText)
        return false;

    SwStringW buffer;
    buffer.Copy(itemText);

    return AddNode(buffer, identifier, noDuplicates, update);
}

bool SwAutoDefTerm::AddNode(const wchar_t * itemText, SwModuleItemId identifier, bool noDuplicates, bool update)
{
    if (!itemText)
        return false;

    if (noDuplicates && FindItem(itemText) != NODE_ID_INVALID_16)
        return false;

    swUI16 pos = FindAlphabeticInsertionPosition(itemText);

    if (pos == NODE_ID_INVALID_16)
    {
        if (AppendNode(itemText, identifier, update) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    return InsertNode(pos, itemText, identifier, update);
}

swUI16 SwAutoDefTerm::FindItem(const char * itemText)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    SwStringW buffer;
    buffer.Copy(itemText);

    return FindItem(buffer);
}

swUI16 SwAutoDefTerm::FindItem(const wchar_t * itemText)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    swUI16 idx = FindInIndex(*itemText);

    if (idx == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

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
            return idx;
        }

        idx ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwAutoDefTerm::FindItem(const char * itemText, Swui16Array & array)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    SwStringW buffer;
    buffer.Copy(itemText);

    return FindItem(buffer, array);
}

swUI16 SwAutoDefTerm::FindItem(const wchar_t * itemText, Swui16Array & array)
{
    if (!itemText)
        return NODE_ID_INVALID_16;

    swUI16 idx = FindInIndex(*itemText);

    if (idx == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    swUI32 start = array.GetCount();

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
            if (array.GetSize() >= array.GetCount() && !array.Size(array.GetCount() + 2))
                return NODE_ID_INVALID_16;

            array.SetAt(array.GetCount(), idx);
            array.IncrementCount();
        }

        idx ++;
    }

    if (array.GetCount() > start)
        return array.GetAt(start);

    return NODE_ID_INVALID_16;
}

swUI16 SwAutoDefTerm::FindItem(SwStrParser & strList, Swui16Array & array)
{
    swUI32 start = array.GetCount();

    for (swUI16 i = 0; i < strList.GetItems(); i ++)
    {
        FindItem(strList.GetItem(i), array);
    }

    if (array.GetCount() > start)
        return array.GetAt(start);

    return NODE_ID_INVALID_16;
}

swUI16 SwAutoDefTerm::FindItem(SwStrParserW & strList, Swui16Array & array)
{
    swUI32 start = array.GetCount();

    for (swUI16 i = 0; i < strList.GetItems(); i ++)
    {
        FindItem(strList.GetItem(i), array);
    }

    if (array.GetCount() > start)
        return array.GetAt(start);

    return NODE_ID_INVALID_16;
}

swUI16 SwAutoDefTerm::FindItem(SwStringArray & strList, Swui16Array & array)
{
    swUI32 start = array.GetCount();

    for (swUI16 i = 0; i < strList.GetCount(); i ++)
    {
        FindItem(strList.GetAt(i), array);
    }

    if (array.GetCount() > start)
        return array.GetAt(start);

    return NODE_ID_INVALID_16;
}

swUI16 SwAutoDefTerm::FindItem(SwStringWArray & strList, Swui16Array & array)
{
    swUI32 start = array.GetCount();

    for (swUI16 i = 0; i < strList.GetCount(); i ++)
    {
        FindItem(strList.GetAt(i), array);
    }

    if (array.GetCount() > start)
        return array.GetAt(start);

    return NODE_ID_INVALID_16;
}

bool SwAutoDefTerm::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!WriteUtf16Data(file, m_dataSize, m_buffer))
        return false;
    if (m_nodePos && fwrite((void *) m_nodeData, sizeof(SwADNodeData), m_nodePos, file) != m_nodePos)
        return false;

    return true;
}

bool SwAutoDefTerm::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_dataSize, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (!WriteUtf16Data(file, k1, k2, m_dataSize, m_buffer))
        return false;
    if (m_nodePos && SwTranscryptor::encryptfwrite((void *) m_nodeData, sizeof(SwADNodeData), m_nodePos, file, k1, k2) != m_nodePos)
        return false;

    return true;
}

bool SwAutoDefTerm::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 dataSize = 0;
    swUI16 nodePos = 0;

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fread((void *) &nodePos, sizeof(swUI16), 1, file) != 1)
        return false;

    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
    if (!ReadUtf16Data(file, dataSize, m_buffer))
        return false;
    if (nodePos && fread((void *) m_nodeData, sizeof(SwADNodeData), nodePos, file) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;

    UpdateAlphaIdx();

    return true;
}

bool SwAutoDefTerm::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 dataSize = 0;
    swUI16 nodePos = 0;

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &dataSize, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
   if (!ReadUtf16Data(file, k1, k2, dataSize, m_buffer))
        return false;
    if (nodePos && SwTranscryptor::decryptfread((void *) m_nodeData, sizeof(SwADNodeData), nodePos, file, k1, k2) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;

    UpdateAlphaIdx();

    return true;
}

swUI32 SwAutoDefTerm::GetType()
{
    return MODULE_INTERFACE_TYPE_AUTODEFTERM;
}

void SwAutoDefTerm::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    int item;
    SwStringW data;

    for (swUI32 i = 0; i < GetNodes(); i ++)
    {
        GetNodeText(i, data);
        item = listctrl->InsertItem(listctrl->GetItemCount(), data.GetArray());
        listctrl->SetItemData(item, i);
    }
}
