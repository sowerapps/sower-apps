///////////////////////////////////////////////////////////////////
// Name:        mediacontents.cpp
// Purpose:     SwMediaContents provides access to additional files
//              stored in Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/mediacontents.h"
#include "../../include/module/transcryptor.h"

void SwMediaNode::Reset()
{
    identifier = MITEMIDINVALID;
    bufferPos = 0;
    contentType = 0;
}

bool SwMediaNode::ReadData(FILE * f, SwStreamBuffer & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size);

    if (!encrypted)
    {
        fseek(f, data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, data.position, SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.IncrementCount(data.size);

    return true;
}

bool SwMediaNode::ReadData(FILE * f, Swui8Array & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size);

    if (!encrypted)
    {
        fseek(f, data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, data.position, SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.IncrementCount(data.size);

    return true;
}

bool SwMediaNode::ReadData(FILE * f, SwHtmlImageMapList & imagemapList, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    fseek(f, data.position, SEEK_SET);

    if (encrypted)
        return imagemapList.ReadFromFile(f, k1, k2);

    return imagemapList.ReadFromFile(f);
}

bool SwMediaNode::ReadData(FILE * f, SwHtmlImageMap & imageMap, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    fseek(f, data.position, SEEK_SET);

    if (encrypted)
        return imageMap.ReadFromFile(f, k1, k2);

    return imageMap.ReadFromFile(f);
}

bool SwMediaNode::ReadData(FILE * f, Swui8Array & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI32 streamOffset, swUI32 bytes, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;
    swUI32 readbytes = 0;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);

    if (streamOffset + bytes > data.size)
        readbytes = data.size - streamOffset;
    else
        readbytes = bytes;

    buffer.Size(buffer.GetCount() + data.size);

    if (!encrypted)
    {
        fseek(f, streamOffset + data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), readbytes, f);
    }
    else
    {
        fseek(f, ((streamOffset * 2) + data.position), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), readbytes, f, k1, k2);
    }

    buffer.IncrementCount(readbytes);

    return true;
}

swUI32 SwMediaNode::ReadStream(FILE * f, void * buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI32 streamOffset, swUI32 bytes, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;
    swUI32 readbytes = 0;

    if (!f || !buffer)
        return 0;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);

    if (streamOffset + bytes > data.size)
        readbytes = data.size - streamOffset;
    else
        readbytes = bytes;

    if (!encrypted)
    {
        fseek(f, streamOffset + data.position, SEEK_SET);
        fread(buffer, sizeof(char), readbytes, f);
    }
    else
    {
        fseek(f, ((streamOffset * 2) + data.position), SEEK_SET);
        SwTranscryptor::decryptfread(buffer, sizeof(char), readbytes, f, k1, k2);
    }

    return readbytes;
}

swUI32 SwMediaNode::GetSize(FILE * f, swUI32 itemindexFp, swUI32 streamOffset)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    if (!fread((void *) &data, sizeof(SwModuleItem), 1, f))
        return 0;

    return data.size - streamOffset;
}

SwMediaContents::SwMediaContents()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_Inc = 25;
    m_buffer = NULL;
    m_bufferSize = 0;
    m_dataSize = 0;
}

SwMediaContents::~SwMediaContents()
{
    Reset();
    if (m_nodeData)
        free(m_nodeData);

    if (m_buffer)
        free(m_buffer);
}

void SwMediaContents::SetIncrement(swUI8 increment)
{
    if (increment < 25)
        m_Inc = 25;
    else
        m_Inc = increment;
}

bool SwMediaContents::SizeBuffer(swUI16 size)
{
    if (!size && m_buffer)
    {
        free(m_buffer);
        m_buffer = NULL;
        m_bufferSize = 0;
        return true;
    }

    char * p = (char *) realloc((void *) m_buffer, size * sizeof(char));

    if (p)
    {
        m_bufferSize = size;
        m_buffer = p;
        return true;
    }

    return false;
}

bool SwMediaContents::IncreaseNodeArray()
{
    swUI16 increase = m_Inc;

    if (!m_Inc)
        increase = 100;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwMediaContents::SizeNodeArray(swUI16 nodes)
{
    if (!nodes && m_nodeData)
    {
        ResetNodeData();
        free(m_nodeData);
        m_nodeData = NULL;
        m_nodePos = 0;
        m_nodesAllocated = 0;
        return true;
    }

    if (nodes >= NODE_ID_INVALID_16)
        return false;

    SwMediaNode * p = (SwMediaNode *) realloc((void *) m_nodeData, nodes * sizeof(SwMediaNode));

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

bool SwMediaContents::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    m_nodeData[m_nodePos].Reset();
    return true;
}

bool SwMediaContents::VerifyNodes(swUI16 nodes)
{
    if (nodes + m_nodePos + 1 > m_nodesAllocated && !SizeNodeArray(nodes + m_nodePos + 1 + m_Inc))
        return false;

    for (swUI32 i = m_nodePos; i < m_nodePos + nodes; i++)
        m_nodeData[i].Reset();

    return true;
}

swUI16 SwMediaContents::GetLastNode()
{
    return m_nodePos -1;
}

swUI16 SwMediaContents::GetNodes()
{
    return m_nodePos;
}

void SwMediaContents::Reset()
{
    ResetNodeData();
    m_nodePos = 0;
}

void SwMediaContents::ResetNodeData()
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].Reset();
        pos ++;
    }
}

void SwMediaContents::UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type)
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

void SwMediaContents::ShiftNodesUp(swUI16 startNode)
{
    if (m_nodePos <= 1)
    {
        m_nodePos = 0;
        return;
    }
    else if (startNode == 0)
        return;
    else if (startNode > GetLastNode())
        return;

    swUI16 pos = startNode;

    while(pos < m_nodePos)
    {
        m_nodeData[pos - 1] = m_nodeData[pos];
        pos ++;
    }

    m_nodeData[m_nodePos - 1].identifier = MITEMIDINVALID;
    m_nodeData[m_nodePos - 1].bufferPos = 0;
    m_nodeData[m_nodePos - 1].contentType = 0;

    m_nodePos --;
}

bool SwMediaContents::ShiftNodesDown(swUI16 startNode)
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

    m_nodeData[startNode].identifier = MITEMIDINVALID;
    m_nodeData[startNode].bufferPos = 0;
    m_nodeData[startNode].contentType = 0;

    m_nodePos ++;
    return true;
}

swUI16 SwMediaContents::GetNodeTextSize(swUI16 node)
{
    if (node >= m_nodePos)
        return 0;

    return strlen(&m_buffer[m_nodeData[node].bufferPos]) + 1;
}

SwMediaNode * SwMediaContents::GetNode(swUI16 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

bool SwMediaContents::GetNodeText(swUI16 node, SwString & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetNodeTextSize(node)))
        return false;

    dest.SetAt(0, '\0');

    memcpy(dest.GetArray(), m_buffer + m_nodeData[node].bufferPos, GetNodeTextSize(node));

    return true;
}

SwModuleItemId SwMediaContents::GetNodeIdentifier(swUI16 node)
{
    if (node >= m_nodePos)
        return MITEMIDINVALID;

    return m_nodeData[node].identifier;
}

bool SwMediaContents::SetNodeIdentifier(swUI16 node, SwModuleItemId identifier)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].identifier = identifier;

    return true;
}

swUI8 SwMediaContents::GetNodeContentType(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_8;

    return m_nodeData[node].contentType;
}

bool SwMediaContents::SetNodeContentType(swUI16 node, swUI8 type)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].contentType = type;

    return true;
}

bool SwMediaContents::BufferAppend(const char * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_bufferSize <= m_dataSize + size && !SizeBuffer(m_dataSize + size))
        return false;

    memcpy(m_buffer+m_dataSize, data, size);

    return true;
}

swUI16 SwMediaContents::AppendNode(const char * itemText, SwModuleItemId identifier, swUI8 type)
{
    if (!itemText || !VerifyNode())
        return NODE_ID_INVALID_16;

    swUI16 size = strlen(itemText) + 1;

    bool status = BufferAppend(itemText, size);

    if (!status)
        return NODE_ID_INVALID_16;

    m_nodeData[m_nodePos].bufferPos = m_dataSize;
    m_nodeData[m_nodePos].identifier = identifier;
    m_nodeData[m_nodePos].contentType = type;

    m_dataSize += size;
    m_nodePos ++;

    return m_nodePos - 1;
}


bool SwMediaContents::BufferInsert(swUI16 pos, const char * data, swUI16 size)
{
    // Insertion.
    if (m_dataSize + size >= m_bufferSize && !SizeBuffer(m_dataSize + size))
        return false;

    swUI16 moveSize = (m_dataSize - pos);

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    memmove(m_buffer + pos + size, m_buffer + pos, moveSize);
    memcpy(m_buffer + pos, data, size);

    return true;
}

bool SwMediaContents::InsertNode(swUI16 nodePos, const char * itemText, SwModuleItemId identifier, swUI8 type)
{
    if (!itemText || !ShiftNodesDown(nodePos))
        return false;

    if (nodePos > m_nodePos - 1)
    {
        if (AppendNode(itemText, identifier, type) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    swUI16 size = strlen(itemText) + 1;

    bool status = BufferInsert(m_nodeData[nodePos].bufferPos, itemText, size);

    if (!status)
    {
        ShiftNodesUp(nodePos + 1);
        return false;
    }

    m_nodeData[nodePos].identifier = identifier;
    m_nodeData[nodePos].contentType = type;

    m_dataSize += size;
    UpdateNodePosData(nodePos + 1, size, true);

    return true;
}


bool SwMediaContents::BufferDelete(swUI16 pos, swUI16 size)
{
    if (m_buffer == NULL || pos >= m_dataSize)
        return false;

    // If deletion exceeds length of data, insert '\0' at
    // deletion point.
    if (pos + size >= m_dataSize)
    {
        m_buffer[pos] = '\0';
        m_dataSize = pos;
        return true;
    }

    // Move all characters from deletion point, and to the right of
    // deletion point to the left, including null terminator.
    swUI32 moveSize = (m_dataSize - (pos + size));
    memmove(m_buffer + pos, m_buffer + pos + size, moveSize);

    return true;
}

bool SwMediaContents::DeleteNode(swUI16 nodePos)
{
    if (nodePos > GetLastNode())
        return false;

    swUI16 change = GetNodeTextSize(nodePos);

    bool status = BufferDelete(m_nodeData[nodePos].bufferPos, change);

    if (!status)
        return false;

    m_dataSize -= change;

    if (nodePos != GetLastNode())
    {
        ShiftNodesUp(nodePos + 1);
        UpdateNodePosData(nodePos, change, false);
    }
    else
        m_nodePos --;

    return true;
}

bool SwMediaContents::BufferReplace(swUI16 pos, swUI16 size, const char * data, swUI16 newSize)
{
    if (m_buffer == NULL || !data)
        return false;

    if (size == newSize)
    {
        memcpy(m_buffer + pos, data, newSize);
        return true;
    }
    else if (newSize > size && m_dataSize + (newSize - size) >= m_bufferSize && !SizeBuffer(m_dataSize + (newSize - size) + 1))
        return false;

    swUI16 moveSize = (m_dataSize - (pos + size));

    memmove(m_buffer + pos + newSize, m_buffer + pos + size, moveSize);
    memcpy(m_buffer + pos, data, newSize);

    return true;
}

bool SwMediaContents::SetNodeText(swUI16 nodePos, const char * itemText)
{
    if (!itemText || nodePos > GetLastNode())
        return false;

    swUI16 size = strlen(itemText);

    bool status = BufferReplace(m_nodeData[nodePos].bufferPos, GetNodeTextSize(nodePos), itemText, size);

    if (!status)
        return false;

    if (size < GetNodeTextSize(nodePos))
    {
        m_dataSize -= GetNodeTextSize(nodePos) - size;

        if (nodePos != GetLastNode())
            UpdateNodePosData(nodePos + 1, GetNodeTextSize(nodePos) - size, false);
    }
    else if (size > GetNodeTextSize(nodePos))
    {
        m_dataSize += size - GetNodeTextSize(nodePos);

        if (nodePos != GetLastNode())
            UpdateNodePosData(nodePos + 1, size - GetNodeTextSize(nodePos), true);
    }

    return true;
}


bool SwMediaContents::MoveNode(swUI16 node, swUI16 newPos)
{
    SwString buffer;

    if (!GetNodeText(node, buffer))
        return false;

    swUI16 id = GetNodeIdentifier(node);

    if(!DeleteNode(node))
        return false;

    if (!InsertNode(newPos, buffer.GetArray(), id))
        return false;

    return true;
}

swUI16 SwMediaContents::FindItem(const char * itemText)
{
    swUI16 pos = 0;

    if (!itemText)
        return NODE_ID_INVALID_16;

    while (pos < m_nodePos)
    {
        if (strcmp(itemText, &m_buffer[m_nodeData[pos].bufferPos]) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwMediaContents::FindItem(SwModuleItemId identifier)
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        if (m_nodeData[pos].identifier == identifier)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwMediaContents::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_dataSize, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fwrite((void *) m_buffer, sizeof(char), m_dataSize, file) != m_dataSize)
        return false;
    if (fwrite((void *) m_nodeData, sizeof(SwMediaNode), m_nodePos, file) != m_nodePos)
        return false;

    return true;
}

bool SwMediaContents::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_dataSize, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) m_buffer, sizeof(char), m_dataSize, file, k1, k2) != m_dataSize)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) m_nodeData, sizeof(SwMediaNode), m_nodePos, file, k1, k2) != m_nodePos)
        return false;

    return true;
}

bool SwMediaContents::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI16 dataSize = 0;
    swUI16 nodePos = 0;

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &dataSize, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fread((void *) &nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
    if (fread((void *) m_buffer, sizeof(char), dataSize, file) != dataSize)
        return false;
    if (fread((void *) m_nodeData, sizeof(SwMediaNode), nodePos, file) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;

    return true;
}

bool SwMediaContents::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI16 dataSize = 0;
    swUI16 nodePos = 0;

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &dataSize, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
    if (SwTranscryptor::decryptfread((void *) m_buffer, sizeof(char), dataSize, file, k1, k2) != dataSize)
        return false;
    if (SwTranscryptor::decryptfread((void *) m_nodeData, sizeof(SwMediaNode), nodePos, file, k1, k2) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;

    return true;
}

swUI32 SwMediaContents::GetType()
{
    return MODULE_INTERFACE_TYPE_MEDIACONTENTS;
}

void SwMediaContents::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    int item;
    SwString data;
    SwStringW data2;

    for (swUI32 i = 0; i < GetNodes(); i ++)
    {
        GetNodeText(i, data);
        data2.Copy(data);
        item = listctrl->InsertItem(listctrl->GetItemCount(), data2.GetArray());
        listctrl->SetItemData(item, i);
    }
}
