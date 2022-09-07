///////////////////////////////////////////////////////////////////
// Name:        tableofcontents.cpp
// Purpose:     Table of Contents for Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/tableofcontents.h"
#include "../../include/module/transcryptor.h"

bool SwContentsNode::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem dataStart, dataEnd;
    swUI32 dataSize;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &dataStart, sizeof(SwModuleItem), 1, f);
    dataSize = dataStart.size;

    if (dataStart.divItems > 1)
    {
        fseek(f, itemindexFp + (sizeof(SwModuleItem) * (identifier + (dataStart.divItems - 1))), SEEK_SET);
        fread((void *) &dataEnd, sizeof(SwModuleItem), 1, f);
        dataSize = (dataEnd.position - dataStart.position) + dataEnd.size;
    }

    buffer.Size(buffer.GetCount() + dataSize + 1);

    if (!encrypted)
    {
        fseek(f, contentOffset + dataStart.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), dataSize, f);
    }
    else
    {
        fseek(f, contentOffset + (dataStart.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), dataSize, f, k1, k2);
    }

    buffer.SetAt(buffer.GetCount() + dataSize, '\0');
    buffer.IncrementCount(dataSize);

    return true;
}

SwTableOfContents::SwTableOfContents()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_Inc = 12;
    m_buffer = NULL;
    m_bufferSize = 0;
    m_dataSize = 0;
    m_idbuffer = NULL;
    m_idbufferSize = 0;
    m_iddataSize = 0;
}

SwTableOfContents::~SwTableOfContents()
{
    if (m_nodeData)
        free(m_nodeData);

    if (m_buffer)
        free(m_buffer);

    if (m_idbuffer)
        free(m_idbuffer);
}

void SwTableOfContents::SetIncrement(swUI8 increment)
{
    if (increment < 25)
        m_Inc = 25;
    else
        m_Inc = increment;
}

bool SwTableOfContents::SizeBuffer(swUI32 size)
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

bool SwTableOfContents::SizeIdBuffer(swUI32 size)
{
    if (!size && m_idbuffer)
    {
        free(m_idbuffer);
        m_idbuffer = NULL;
        m_idbufferSize = 0;
        return true;
    }

    char * p = (char *) realloc((void *) m_idbuffer, size * sizeof(char));

    if (p)
    {
        m_idbufferSize = size;
        m_idbuffer = p;
        return true;
    }

    return false;
}

bool SwTableOfContents::IncreaseNodeArray()
{
    swUI16 increase = m_Inc;

    if (!m_Inc)
        increase = 100;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwTableOfContents::SizeNodeArray(swUI16 nodes)
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

    SwContentsNode * p = (SwContentsNode *) realloc((void *) m_nodeData, nodes * sizeof(SwContentsNode));

    if (p)
    {
        m_nodesAllocated = nodes;
        m_nodeData = p;
        return true;
    }

    return false;
}

bool SwTableOfContents::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    m_nodeData[m_nodePos].identifier = MITEMIDINVALID;
    m_nodeData[m_nodePos].divDepth = 0;
    m_nodeData[m_nodePos].bufferPos = 0;
    m_nodeData[m_nodePos].idbufferPos = 0;
    m_nodeData[m_nodePos].hasChildren = false;
    m_nodeData[m_nodePos].contentType = CT_UNKNOWN;

    return true;
}

bool SwTableOfContents::VerifyNodes(swUI16 nodes)
{
    if (nodes + m_nodePos + 1 > m_nodesAllocated && !SizeNodeArray(nodes + m_nodePos + 1 + m_Inc))
        return false;

    return true;
}

swUI16 SwTableOfContents::GetLastNode()
{
    return m_nodePos -1;
}

swUI16 SwTableOfContents::GetNodes()
{
    return m_nodePos;
}

void SwTableOfContents::Reset()
{
    ResetNodeData();
    m_nodePos = 0;
}

void SwTableOfContents::ResetNodeData()
{
    // Reset parts of node data that will be modified
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {

        m_nodeData[pos].identifier = MITEMIDINVALID;
        m_nodeData[pos].divDepth = 0;
        m_nodeData[pos].bufferPos = 0;
        m_nodeData[pos].idbufferPos = 0;
        m_nodeData[pos].hasChildren = false;
        m_nodeData[pos].contentType = CT_UNKNOWN;

        pos ++;
    }
}

void SwTableOfContents::UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type)
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

void SwTableOfContents::UpdateNodeIdPosData(swUI16 nodeStart, swUI16 change, bool type)
{
    // type == true for increase, type == false for decrease
    swUI16 pos = 0;
    pos = nodeStart;

    if (type)
    {
        while (pos < m_nodePos)
        {
            m_nodeData[pos].idbufferPos += change;
            pos ++;
        }
    }
    else
    {
        while (pos < m_nodePos)
        {
            m_nodeData[pos].idbufferPos -= change;
            pos ++;
        }
    }
}

void SwTableOfContents::ShiftNodesUp(swUI16 startNode)
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

bool SwTableOfContents::ShiftNodesDown(swUI16 startNode)
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

SwContentsNode * SwTableOfContents::GetNode(swUI16 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

const char * SwTableOfContents::GetTitleText(swUI16 node)
{
    if (node >= m_nodePos)
        return "";

    return m_buffer + m_nodeData[node].bufferPos;
}

bool SwTableOfContents::GetTitle(swUI16 node, SwString & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetTitleSize(node)))
        return false;

    dest.SetAt(0, '\0');

    memcpy(dest.GetArray(), m_buffer + m_nodeData[node].bufferPos, GetTitleSize(node));

    return true;
}

const char * SwTableOfContents::GetIdText(swUI16 node)
{
    if (node >= m_nodePos)
        return "";

    return m_idbuffer + m_nodeData[node].idbufferPos;
}

bool SwTableOfContents::GetId(swUI16 node, SwString & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetIdSize(node)))
        return false;

    dest.SetAt(0, '\0');

    memcpy(dest.GetArray(), m_idbuffer + m_nodeData[node].idbufferPos, GetIdSize(node));

    return true;
}

bool SwTableOfContents::SetTitle(swUI16 node, const char * title)
{
    if (!title || node > GetLastNode())
        return false;

    swUI16 size = strlen(title);

    bool status = BufferReplace(m_nodeData[node].bufferPos, GetTitleSize(node), title, size);

    if (!status)
        return false;

    if (size < GetTitleSize(node))
    {
        m_dataSize -= GetTitleSize(node) - size;

        if (node != GetLastNode())
            UpdateNodePosData(node + 1, GetTitleSize(node) - size, false);
    }
    else if (size > GetTitleSize(node))
    {
        m_dataSize += size - GetTitleSize(node);

        if (node != GetLastNode())
            UpdateNodePosData(node + 1, size - GetTitleSize(node), true);
    }

    return true;
}

bool SwTableOfContents::SetId(swUI16 node, const char * id)
{
    if (!id || node > GetLastNode())
        return false;

    swUI16 size = strlen(id);

    bool status = IdBufferReplace(m_nodeData[node].idbufferPos, GetIdSize(node), id, size);

    if (!status)
        return false;

    if (size < GetIdSize(node))
    {
        m_dataSize -= GetIdSize(node) - size;

        if (node != GetLastNode())
            UpdateNodeIdPosData(node + 1, GetIdSize(node) - size, false);
    }
    else if (size > GetIdSize(node))
    {
        m_dataSize += size - GetIdSize(node);

        if (node != GetLastNode())
            UpdateNodeIdPosData(node + 1, size - GetIdSize(node), true);
    }

    return true;
}

swUI16 SwTableOfContents::GetTitleSize(swUI16 node)
{
    if (node >= m_nodePos)
        return 0;

    return strlen(&m_buffer[m_nodeData[node].bufferPos]) + 1;
}

swUI16 SwTableOfContents::GetIdSize(swUI16 node)
{
    if (node >= m_nodePos)
        return 0;

    return strlen(&m_idbuffer[m_nodeData[node].idbufferPos]) + 1;
}

SwModuleItemId SwTableOfContents::GetIdentifier(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_16;

    return m_nodeData[node].identifier;
}

bool SwTableOfContents::SetIdentifier(swUI16 node, SwModuleItemId identifier)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].identifier = identifier;

    return true;
}

swUI8 SwTableOfContents::GetDivDepth(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_8;

    return m_nodeData[node].divDepth;
}

bool SwTableOfContents::SetDivDepth(swUI16 node, swUI8 divDepth)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].divDepth = divDepth;

    return true;
}

bool SwTableOfContents::GetHasChildren(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_8;

    return m_nodeData[node].hasChildren;
}

bool SwTableOfContents::SetHasChildren(swUI16 node, bool hasChildren)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].hasChildren = hasChildren;

    return true;
}

swUI8 SwTableOfContents::GetContentType(swUI16 node)
{
    if (node >= m_nodePos)
        return CT_UNKNOWN;

    return m_nodeData[node].contentType;
}

bool SwTableOfContents::SetContentType(swUI16 node, swUI8 type)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].contentType = type;

    return true;
}

bool SwTableOfContents::BufferAppend(const char * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_dataSize + size >= 0xFFFFFFF)
        return false;

    if (m_bufferSize <= m_dataSize + size && !SizeBuffer(m_dataSize + size))
        return false;

    memcpy(m_buffer+m_dataSize, data, size);

    return true;
}

bool SwTableOfContents::IdBufferAppend(const char * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_iddataSize + size >= 0xFFFFFFF)
        return false;

    if (m_idbufferSize <= m_iddataSize + size && !SizeIdBuffer(m_iddataSize + size))
        return false;

    memcpy(m_idbuffer+m_iddataSize, data, size);

    return true;
}

swUI16 SwTableOfContents::Append(const char * title, SwModuleItemId identifier, const char * id)
{
    if (!title || !id || !VerifyNode())
        return NODE_ID_INVALID_16;

    swUI16 size = strlen(title) + 1;
    swUI16 idsize = strlen(id) + 1;

    bool status = BufferAppend(title, size);

    if (!status)
        return NODE_ID_INVALID_16;

    status = IdBufferAppend(id, idsize);

    if (!status)
        return NODE_ID_INVALID_16;

    m_nodeData[m_nodePos].bufferPos = m_dataSize;
    m_nodeData[m_nodePos].idbufferPos = m_iddataSize;
    m_nodeData[m_nodePos].identifier = identifier;

    m_dataSize += size;
    m_iddataSize += idsize;
    m_nodePos ++;

    return m_nodePos - 1;
}


bool SwTableOfContents::BufferInsert(swUI16 pos, const char * data, swUI16 size)
{
    if (m_dataSize + size >= 0xFFFFFFF)
        return false;

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

bool SwTableOfContents::IdBufferInsert(swUI16 pos, const char * data, swUI16 size)
{
    if (m_iddataSize + size >= 0xFFFFFFF)
        return false;

    // Insertion.
    if (m_iddataSize + size >= m_idbufferSize && !SizeIdBuffer(m_iddataSize + size))
        return false;

    swUI16 moveSize = (m_iddataSize - pos);

    // Move characters from position point, and right of insertion
    // position, the required number of char's to the right.
    memmove(m_idbuffer + pos + size, m_idbuffer + pos, moveSize);
    memcpy(m_idbuffer + pos, data, size);

    return true;
}

bool SwTableOfContents::Insert(swUI16 nodePos, const char * title, SwModuleItemId identifier, const char * id)
{
    if (!title || !id || !ShiftNodesDown(nodePos))
        return false;

    if (nodePos > m_nodePos - 1)
    {
        if (Append(title, identifier, id) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    swUI16 sizeTitle = strlen(title) + 1;

    bool status = BufferInsert(m_nodeData[nodePos].bufferPos, title, sizeTitle);

    if (!status)
    {
        ShiftNodesUp(nodePos + 1);
        return false;
    }

    swUI16 sizeId = strlen(id) + 1;
    status = IdBufferInsert(m_nodeData[nodePos].idbufferPos, id, sizeId);

    if (!status)
    {
        BufferDelete(m_nodeData[nodePos].bufferPos, sizeTitle);
        ShiftNodesUp(nodePos + 1);
        return false;
    }

    m_nodeData[nodePos].identifier = identifier;

    m_dataSize += sizeTitle;
    m_iddataSize += sizeId;
    UpdateNodePosData(nodePos + 1, sizeTitle, true);
    UpdateNodeIdPosData(nodePos + 1, sizeId, true);

    return true;
}

bool SwTableOfContents::BufferDelete(swUI16 pos, swUI16 size)
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
    swUI16 moveSize = (m_dataSize - (pos + size));
    memmove(m_buffer + pos, m_buffer + pos + size, moveSize);

    return true;
}

bool SwTableOfContents::IdBufferDelete(swUI16 pos, swUI16 size)
{
    if (m_idbuffer == NULL || pos >= m_iddataSize)
        return false;

    // If deletion exceeds length of data, insert '\0' at
    // deletion point.
    if (pos + size >= m_iddataSize)
    {
        m_idbuffer[pos] = '\0';
        //m_dataSize = pos;
        return true;
    }

    // Move all characters from deletion point, and to the right of
    // deletion point to the left, including null terminator.
    swUI16 moveSize = (m_iddataSize - (pos + size));
    memmove(m_idbuffer + pos, m_idbuffer + pos + size, moveSize);

    return true;
}

bool SwTableOfContents::Delete(swUI16 nodePos)
{
    if (nodePos > GetLastNode())
        return false;

    swUI16 changeTitle = GetTitleSize(nodePos);

    bool status = BufferDelete(m_nodeData[nodePos].bufferPos, changeTitle);

    if (!status)
        return false;

    m_dataSize -= changeTitle;

    swUI16 changeId = GetIdSize(nodePos);

    status = IdBufferDelete(m_nodeData[nodePos].idbufferPos, changeId);

    if (!status)
        return false;

    m_dataSize -= changeTitle;
    m_iddataSize -= changeId;

    if (nodePos != GetLastNode())
    {
        ShiftNodesUp(nodePos + 1);
        UpdateNodePosData(nodePos, changeTitle, false);
        UpdateNodeIdPosData(nodePos, changeId, false);
    }
    else
        m_nodePos --;

    return true;
}

bool SwTableOfContents::BufferReplace(swUI16 pos, swUI16 size, const char * data, swUI16 newSize)
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

bool SwTableOfContents::IdBufferReplace(swUI16 pos, swUI16 size, const char * data, swUI16 newSize)
{
    if (m_idbuffer == NULL || !data)
        return false;

    if (size == newSize)
    {
        memcpy(m_idbuffer + pos, data, newSize);
        return true;
    }
    else if (newSize > size && m_iddataSize + (newSize - size) >= m_idbufferSize && !SizeIdBuffer(m_iddataSize + (newSize - size) + 1))
        return false;

    swUI16 moveSize = (m_iddataSize - (pos + size));

    memmove(m_idbuffer + pos + newSize, m_idbuffer + pos + size, moveSize);
    memcpy(m_idbuffer + pos, data, newSize);

    return true;
}

bool SwTableOfContents::Move(swUI16 node, swUI16 newPos)
{
    SwString bufferTitle, bufferId;

    if (!GetTitle(node, bufferTitle))
        return false;

    if (!GetId(node, bufferId))
        return false;

    SwModuleItemId    identifier = GetIdentifier(node);
    swUI8             divDepth = GetDivDepth(node);
    bool              hasChildren = GetHasChildren(node);
    swUI8             contentType = GetContentType(node);

    if(!Delete(node))
        return false;

    if (!Insert(newPos, bufferTitle, identifier, bufferId))
        return false;

    SetDivDepth(newPos, divDepth);
    SetHasChildren(newPos, hasChildren);
    SetContentType(newPos, contentType);

    return true;
}

swUI16 SwTableOfContents::FindItem(const char * title)
{
    swUI16 pos = 0;

    if (!title)
        return NODE_ID_INVALID_16;

    while (pos < m_nodePos)
    {
        if (strcmp(title, &m_buffer[m_nodeData[pos].bufferPos]) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwTableOfContents::FindByID(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_nodePos)
    {
        if (strcmp(id, &m_idbuffer[m_nodeData[pos].idbufferPos]) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwTableOfContents::FindItem(SwModuleItemId identifier)
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        if (m_nodeData[pos].identifier == identifier)
            return pos;
        else if (pos == m_nodePos - 1)
        {
            if (m_nodeData[pos].identifier < identifier)
                return pos;

            return NODE_ID_INVALID_16;
        }
        else if (m_nodeData[pos].identifier < identifier && m_nodeData[pos + 1].identifier > identifier)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwTableOfContents::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_iddataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (m_buffer && fwrite((void *) m_buffer, sizeof(char), m_dataSize, file) != m_dataSize)
        return false;
    if (m_idbuffer && fwrite((void *) m_idbuffer, sizeof(char), m_iddataSize, file) != m_iddataSize)
        return false;
    if (m_nodeData && fwrite((void *) m_nodeData, sizeof(SwContentsNode), m_nodePos, file) != m_nodePos)
        return false;

    return true;
}

bool SwTableOfContents::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_dataSize, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_iddataSize, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (m_buffer && SwTranscryptor::encryptfwrite((void *) m_buffer, sizeof(char), m_dataSize, file, k1, k2) != m_dataSize)
        return false;
    if (m_buffer && SwTranscryptor::encryptfwrite((void *) m_idbuffer, sizeof(char), m_iddataSize, file, k1, k2) != m_iddataSize)
        return false;
    if (m_nodeData && SwTranscryptor::encryptfwrite((void *) m_nodeData, sizeof(SwContentsNode), m_nodePos, file, k1, k2) != m_nodePos)
        return false;

    return true;
}

bool SwTableOfContents::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 dataSize = 0;
    swUI32 iddataSize = 0;
    swUI16 nodePos = 0;

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fread((void *) &iddataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fread((void *) &nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
    if (dataSize && fread((void *) m_buffer, sizeof(char), dataSize, file) != dataSize)
        return false;
    if (!SizeIdBuffer(iddataSize))
        return false;
    if (iddataSize && fread((void *) m_idbuffer, sizeof(char), iddataSize, file) != iddataSize)
        return false;
    if (nodePos && fread((void *) m_nodeData, sizeof(SwContentsNode), nodePos, file) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;
    m_iddataSize = iddataSize;

    return true;
}

bool SwTableOfContents::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 dataSize = 0;
    swUI32 iddataSize = 0;
    swUI16 nodePos = 0;

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &dataSize, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &iddataSize, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (!SizeBuffer(dataSize) || !SizeNodeArray(nodePos))
        return false;
    if (dataSize && SwTranscryptor::decryptfread((void *) m_buffer, sizeof(char), dataSize, file, k1, k2) != dataSize)
        return false;
    if (!SizeIdBuffer(iddataSize))
        return false;
    if (iddataSize && SwTranscryptor::decryptfread((void *) m_idbuffer, sizeof(char), iddataSize, file, k1, k2) != iddataSize)
        return false;
    if (nodePos && SwTranscryptor::decryptfread((void *) m_nodeData, sizeof(SwContentsNode), nodePos, file, k1, k2) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;
    m_iddataSize = iddataSize;

    return true;
}

swUI32 SwTableOfContents::GetType()
{
    return MODULE_INTERFACE_TYPE_TABLEOFCONTENTS;
}

void SwTableOfContents::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    int item;
    SwString data;
    SwStringW data2;

    for (swUI32 i = 0; i < GetNodes(); i ++)
    {
        GetId(i, data);
        data2.Copy(data);
        item = listctrl->InsertItem(listctrl->GetItemCount(), data2.GetArray());
        listctrl->SetItemData(item, i);
    }
}
