///////////////////////////////////////////////////////////////////
// Name:        autodefnumbered.cpp
// Purpose:     AutodefNumbered - locates/retrieves numbered entries,
//              primarily strongs numbers, and ThML notes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/autodefnumbered.h"
#include "../../include/module/transcryptor.h"

void SwADNumberedNodeData::Reset()
{
    number = 0;
    identifier = MITEMIDINVALID;
}

bool SwADNumberedNodeData::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
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

SwAutoDefNumbered::SwAutoDefNumbered()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_Inc = 25;
    m_lower = 0;
    m_upper = 0;
    m_type = 0;
}

SwAutoDefNumbered::~SwAutoDefNumbered()
{
    if (m_nodeData)
        free(m_nodeData);
}

swUI8 SwAutoDefNumbered::GetSyncType()
{
    return m_type;
}

void SwAutoDefNumbered::SetSyncType(swUI8 type)
{
    m_type = type;
}

void SwAutoDefNumbered::SetIncrement(swUI8 increment)
{
    if (increment < 25)
        m_Inc = 25;
    else
        m_Inc = increment;
}

bool SwAutoDefNumbered::IncreaseNodeArray()
{
    swUI32 increase = m_Inc;

    if (!m_Inc)
        increase = 100;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwAutoDefNumbered::SizeNodeArray(swUI16 nodes)
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

    SwADNumberedNodeData * p = (SwADNumberedNodeData *) realloc((void *) m_nodeData, nodes * sizeof(SwADNumberedNodeData));

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

bool SwAutoDefNumbered::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    m_nodeData[m_nodePos].Reset();

    return true;
}

bool SwAutoDefNumbered::VerifyNodes(swUI16 nodes)
{
    if (nodes + m_nodePos + 1 > m_nodesAllocated && !SizeNodeArray(nodes + m_nodePos + 1 + m_Inc))
        return false;

    for (swUI32 i = m_nodePos; i < m_nodePos + nodes; i++)
        m_nodeData[i].Reset();

    return true;
}

swUI16 SwAutoDefNumbered::GetLastNode()
{
    return m_nodePos -1;
}

swUI16 SwAutoDefNumbered::GetNodes()
{
    return m_nodePos;
}

void SwAutoDefNumbered::Reset()
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].number = 0;
        m_nodeData[pos].identifier = MITEMIDINVALID;

        pos ++;
    }

    m_nodePos = 0;
}

void SwAutoDefNumbered::Update()
{
    m_lower = 0;
    m_upper = 0;

    for (swUI16 i = 0; i < m_nodePos; i++)
    {
        if (GetNodeNumber(i) < m_lower)
            m_lower = GetNodeNumber(i);

        if (GetNodeNumber(i) > m_upper)
            m_upper = GetNodeNumber(i);
    }
}

swUI16 SwAutoDefNumbered::GetLower()
{
    return m_lower;
}

swUI16 SwAutoDefNumbered::GetUpper()
{
    return m_upper;
}

void SwAutoDefNumbered::ShiftNodesUp(swUI16 startNode)
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

    m_nodePos --;
}

bool SwAutoDefNumbered::ShiftNodesDown(swUI16 startNode)
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

SwADNumberedNodeData * SwAutoDefNumbered::GetNode(swUI16 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

SwModuleItemId SwAutoDefNumbered::GetNodeIdentifier(swUI16 node)
{
    if (node >= m_nodePos)
        return MITEMIDINVALID;

    return m_nodeData[node].identifier;
}

swUI16 SwAutoDefNumbered::GetNodeNumber(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_16;

    return m_nodeData[node].number;
}

bool SwAutoDefNumbered::SetNodeIdentifier(swUI16 node, SwModuleItemId identifier)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].identifier = identifier;

    return true;
}

bool SwAutoDefNumbered::SetNodeNumber(swUI16 node, const char * number)
{
    if (!number)
        return false;

    return SetNodeNumber(node, atoi(number));
}

bool SwAutoDefNumbered::SetNodeNumber(swUI16 node, const wchar_t * number)
{
    if (!number)
        return false;

    return SetNodeNumber(node, wcstoul(number, NULL, 10));
}

bool SwAutoDefNumbered::SetNodeNumber(swUI16 node, swUI16 number)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].number = number;
    Update();

    return true;
}

swUI16 SwAutoDefNumbered::AppendNode(const char * number, SwModuleItemId identifier)
{
    if (!number)
        return NODE_ID_INVALID_16;

    return AppendNode(atoi(number), identifier);
}

swUI16 SwAutoDefNumbered::AppendNode(const wchar_t * number, SwModuleItemId identifier)
{
    if (!number)
        return NODE_ID_INVALID_16;

    return AppendNode(wcstoul(number, NULL, 10), identifier);
}

swUI16 SwAutoDefNumbered::AppendNode(swUI16 number, SwModuleItemId identifier)
{
    if (!VerifyNode())
        return NODE_ID_INVALID_16;

    m_nodeData[m_nodePos].number = number;
    m_nodeData[m_nodePos].identifier = identifier;

    m_nodePos ++;

    Update();

    return m_nodePos - 1;
}

bool SwAutoDefNumbered::InsertNode(swUI16 nodePos, const char * number, SwModuleItemId identifier)
{
    if (!number)
        return false;

    return InsertNode(nodePos, atoi(number), identifier);
}

bool SwAutoDefNumbered::InsertNode(swUI16 nodePos, const wchar_t * number, SwModuleItemId identifier)
{
    if (!number)
        return false;

    return InsertNode(nodePos, wcstoul(number, NULL, 10), identifier);
}

bool SwAutoDefNumbered::InsertNode(swUI16 nodePos, swUI16 number, SwModuleItemId identifier)
{
    if (!ShiftNodesDown(nodePos))
        return false;

    if (nodePos > m_nodePos - 1)
    {
        if (AppendNode(number, identifier) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    m_nodeData[nodePos].number = number;
    m_nodeData[nodePos].identifier = identifier;

    Update();

    return true;
}

bool SwAutoDefNumbered::DeleteNode(swUI16 node)
{
    if (node > GetLastNode())
        return false;

    if (node != GetLastNode())
    {
        ShiftNodesUp(node + 1);
    }
    else
        m_nodePos --;

    Update();

    return true;
}

bool SwAutoDefNumbered::ReplaceNode(swUI16 node, const char * number, SwModuleItemId identifier)
{
    if (!number)
        return false;

    return ReplaceNode(node, atoi(number), identifier);
}

bool SwAutoDefNumbered::ReplaceNode(swUI16 node, const wchar_t * number, SwModuleItemId identifier)
{
    if (!number)
        return false;

    return ReplaceNode(node, wcstoul(number, NULL, 10), identifier);
}

bool SwAutoDefNumbered::ReplaceNode(swUI16 node, swUI16 number, SwModuleItemId identifier)
{
    if (node > GetLastNode())
        return false;

    m_nodeData[node].number = number;
    m_nodeData[node].identifier = identifier;
    Update();

    return true;
}

bool SwAutoDefNumbered::MoveNode(swUI16 node, swUI16 newPos)
{
    swUI16 number = GetNodeNumber(node);
    SwModuleItemId identifier = GetNodeIdentifier(node);

    if(!DeleteNode(node))
        return false;

    return InsertNode(newPos, number, identifier);
}


swUI16 SwAutoDefNumbered::LocatePosition(swUI16 number)
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        if (m_nodeData[pos].number >= number)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwAutoDefNumbered::AddNode(const char * number, SwModuleItemId identifier)
{
    if (!number)
        return false;

    return AddNode(atoi(number), identifier);
}

bool SwAutoDefNumbered::AddNode(const wchar_t * number, SwModuleItemId identifier)
{
    if (!number)
        return false;

    return AddNode(wcstoul(number, NULL, 10), identifier);
}

bool SwAutoDefNumbered::AddNode(swUI16 number, SwModuleItemId identifier)
{
    swUI32 pos = LocatePosition(number);

    if (pos == NODE_ID_INVALID_16)
    {
        if (AppendNode(number, identifier) == NODE_ID_INVALID_16)
            return false;

        return true;
    }

    return InsertNode(pos, number, identifier);
}

swUI16 SwAutoDefNumbered::FindItem(const char * number)
{
    if (!number)
        return NODE_ID_INVALID_16;

    return FindItem(atoi(number));
}

swUI16 SwAutoDefNumbered::FindItem(const wchar_t * number)
{
    if (!number)
        return NODE_ID_INVALID_16;

    return FindItem(wcstoul(number, NULL, 10));
}

swUI16 SwAutoDefNumbered::FindItem(swUI16 number)
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        if (m_nodeData[pos].number == number)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwAutoDefNumbered::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_lower, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_upper, sizeof(swUI16), 1, file) != 1)
        return false;
    if (m_nodePos && fwrite((void *) m_nodeData, sizeof(SwADNumberedNodeData), m_nodePos, file) != m_nodePos)
        return false;
    if (fwrite((void *) &m_type, sizeof(swUI8), 1, file) != 1)
        return false;

    return true;
}

bool SwAutoDefNumbered::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_lower, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_upper, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (m_nodePos && SwTranscryptor::encryptfwrite((void *) m_nodeData, sizeof(SwADNumberedNodeData), m_nodePos, file, k1, k2) != m_nodePos)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_type, sizeof(swUI8), 1, file, k1, k2) != 1)
        return false;

    return true;
}

bool SwAutoDefNumbered::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 nodePos = 0;
    swUI16 lower = 0, upper = 0;

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fread((void *) &lower, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fread((void *) &upper, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!SizeNodeArray(nodePos))
        return false;
    if (nodePos && fread((void *) m_nodeData, sizeof(SwADNumberedNodeData), nodePos, file) != nodePos)
        return false;
    if (fread((void *) &m_type, sizeof(swUI8), 1, file) != 1)
        return false;

    m_nodePos = nodePos;
    m_lower = lower;
    m_upper = upper;

    return true;
}

bool SwAutoDefNumbered::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 nodePos = 0;
    swUI16 lower = 0, upper = 0;

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &nodePos, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &lower, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &upper, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (!SizeNodeArray(nodePos))
        return false;
    if (nodePos && SwTranscryptor::decryptfread((void *) m_nodeData, sizeof(SwADNumberedNodeData), nodePos, file, k1, k2) != nodePos)
        return false;
    if (SwTranscryptor::decryptfread((void *) &m_type, sizeof(swUI8), 1, file, k1, k2) != 1)
        return false;

    m_nodePos = nodePos;
    m_lower = lower;
    m_upper = upper;

    return true;
}

swUI32 SwAutoDefNumbered::GetType()
{
    return MODULE_INTERFACE_TYPE_AUTODEFSTRONGS;
}

void SwAutoDefNumbered::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    int item;
    wchar_t s[21];

    for (swUI32 i = 0; i < GetNodes(); i ++)
    {
        #if defined __MSWIN__
        swprintf(s, L"%u", GetNodeNumber(i));
        #else
        swprintf(s, 21, L"%u", GetNodeNumber(i));
        #endif

        item = listctrl->InsertItem(listctrl->GetItemCount(), s);
        listctrl->SetItemData(item, i);
    }
}
