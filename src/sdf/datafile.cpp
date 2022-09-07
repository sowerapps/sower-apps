///////////////////////////////////////////////////////////////////
// Name:        datafile.cpp
// Purpose:     Sower Data files (sdf) are HTML files with one or
//              more tables. SowerBase uses this method for themes,
//              translations, user preferences, etc.
//              SwDataFile is used to read, write, and edit those files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/sdf/datafile.h"
#include "../../include/html/html_encoded_char.h"
#include "../../include/filesys/file.h"

static const char * tablebeginformatString = "<table border=\"1\" width=\"100%%\">\n<caption>%s</caption>\n<tbody>\n";
static const char * tablerowformatString = "<tr param1=\"%s\" param2=\"%s\">\n<td>%s</td>\n<td>%s</td>\n</tr>\n";
static const char * tablerowimageformatString = "<tr param1=\"%s\" param2=\"%s\">\n<td>%s</td>\n<td><img src=\"%s\"/></td>\n</tr>\n";
static const char * tablerowaudioformatString = "<tr param1=\"%s\" param2=\"%s\">\n<td>%s</td>\n<td><audio controls=\"controls\" src=\"%s\"/></td>\n</tr>\n";
static const char * tablerowvideoformatString = "<tr param1=\"%s\" param2=\"%s\">\n<td>%s</td>\n<td><video controls=\"controls\" src=\"%s\"/></td>\n</tr>\n";
static const char * tableendformatString = "</tbody>\n</table>\n";
static const char * blankHtml = "<html>\n<head>\n<meta content=\"text/html; charset=utf8\" http-equiv=\"content-type\">\n</head>\n<body>\n<datalist id=\"String Identifiers\">\n</datalist>\n</body>\n</html>";

SwTableItem::SwTableItem()
{
    Init();
}

SwTableItem::~SwTableItem()
{
    ReleaseBuffers();
}

void SwTableItem::Init()
{
    id = NULL;
    id = SetItem(id, "");
    data = NULL;
    data = SetItem(data, "");
    param1 = NULL;
    param1 = SetItem(param1, "");
    param2 = NULL;
    param2 = SetItem(param2, "");
    findId = 0;
    cellType = CELLTYPE_TEXT;
}

void SwTableItem::Reset()
{
    ReleaseBuffers();
    Init();
}

void SwTableItem::ReleaseBuffers()
{
    free(id);
    id = NULL;
    free(data);
    data = NULL;
    free(param1);
    param1 = NULL;
    free(param2);
    param2 = NULL;
}

const char * SwTableItem::GetId()
{
    return id;
}

void SwTableItem::SetId(const char * idstring)
{
    id = SetItem(id, idstring);
}

const char * SwTableItem::GetData()
{
    return data;
}

void SwTableItem::SetData(const char * datastring)
{
    data = SetItem(data, datastring);
}

const char * SwTableItem::GetParam1()
{
    return param1;
}

void SwTableItem::SetParam1(const char * paramstring)
{
    param1 = SetItem(param1, paramstring);
}

const char * SwTableItem::GetParam2()
{
    return param2;
}

const char * SwTableItem::GetParam2(SwTextRange & sel)
{
    sel.Reset();

    sel.begin = strtol(param2, NULL, 10);
    char * p = strchr(param2, ',');

    if (!p)
        return param2;

    while (!isdigit(*p) && *p != '\0')
        p++;

    sel.end = strtol(p, NULL, 10);

    return param2;
}

void SwTableItem::SetParam2(const char * paramstring)
{
    param2 = SetItem(param2, paramstring);
}

char * SwTableItem::SetItem(const char * item, const char * data)
{
    if (!data)
        return NULL;

    char * p = (char *) realloc((void *) item, strlen(data) + 1);
    strcpy(p, data);

    return p;
}

swUI32 SwTableItem::GetFindId()
{
    return findId;
}

swUI8 SwTableItem::GetCellType()
{
    return cellType;
}

void SwTableItem::SetCellType(swUI8 type)
{
    cellType = type;
}

void SwTableItem::SetFindId(swUI32 findID)
{
    findId = findID;
}

void SwTableItem::Copy(SwTableItem & tableItem)
{
    SetId(tableItem.GetId());
    SetData(tableItem.GetData());
    SetParam1(tableItem.GetParam1());
    SetParam2(tableItem.GetParam2());
    SetCellType(tableItem.GetCellType());
    SetFindId(tableItem.GetFindId());
}

bool SwTableItem::HasId()
{
    if (!id || id[0] == '\0')
        return false;

    return true;
}

bool SwTableItem::HasData()
{
    if (!data || data[0] == '\0')
        return false;

    return true;
}

bool SwTableItem::HasParam1()
{
    if (!param1 || param1[0] == '\0')
        return false;

    return true;
}

bool SwTableItem::HasParam2()
{
    if (!param2 || param2[0] == '\0')
        return false;

    return true;
}

SwTable::SwTable()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_Inc = 12;
    m_tableCaption = strdup("");
    m_basePath = strdup("");
}

SwTable::~SwTable()
{
    if (m_basePath)
        free(m_basePath);

    if (m_tableCaption)
        free(m_tableCaption);

    if (m_nodeData)
    {
        FreeNodeData();
        free(m_nodeData);
    }
}

void SwTable::SetIncrement(swUI8 increment)
{
    if (increment < 12)
        m_Inc = 12;
    else
        m_Inc = increment;
}

bool SwTable::IncreaseNodeArray()
{
    swUI32 increase = m_Inc;

    if (!m_Inc)
        increase = 12;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwTable::SizeNodeArray(swUI32 nodes)
{
    swUI32 pos = m_nodesAllocated;

    if (!nodes && m_nodeData)
    {
        FreeNodeData();
        free(m_nodeData);
        m_nodeData = NULL;
        m_nodePos = 0;
        m_nodesAllocated = 0;

        return true;
    }

    if (nodes >= NODE_ID_INVALID)
        return false;

    SwTableItem * p = (SwTableItem *) realloc((void *) m_nodeData, nodes * sizeof(SwTableItem));

    if (p)
    {
        m_nodesAllocated = nodes;
        m_nodeData = p;

        while (pos < m_nodesAllocated)
        {
            m_nodeData[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

bool SwTable::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    return true;
}

swUI32 SwTable::GetLastNode()
{
    return m_nodePos -1;
}

swUI32 SwTable::GetNodes()
{
    return m_nodePos;
}

void SwTable::Reset()
{
    ResetNodeData();
    m_nodePos = 0;

    free(m_basePath);
    m_basePath = strdup("");

    free(m_tableCaption);
    m_tableCaption = strdup("");

}

void SwTable::ResetNodeData()
{
    swUI32 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].Reset();
        pos ++;
    }
}

void SwTable::FreeNodeData()
{
    swUI32 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].ReleaseBuffers();
        pos ++;
    }
}

void SwTable::ShiftNodesUp(swUI32 startNode)
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

    swUI32 pos = startNode;

    if (startNode)
        m_nodeData[startNode - 1].Reset();

    // Shift pointers to next node up instead of freeing and reallocating buffers.
    while(pos < m_nodePos)
    {
        m_nodeData[pos - 1].Copy(m_nodeData[pos]);

        pos ++;
    }

    m_nodePos --;

    m_nodeData[m_nodePos].Reset();
}

bool SwTable::ShiftNodesDown(swUI32 startNode)
{
    if (startNode >= m_nodePos)
        return false;

    if (!VerifyNode())
        return false;

    swUI32 pos = m_nodePos;
    m_nodeData[m_nodePos].Reset();

    while(pos > startNode)
    {
        m_nodeData[pos].Copy(m_nodeData[pos - 1]);

        pos --;
    }

    m_nodePos ++;
    return true;
}

const char * SwTable::GetBasePath()
{
    return m_basePath;
}

void SwTable::SetBasePath(const char * basePath)
{
    if (!basePath)
        return;

    free(m_basePath);
    m_basePath = strdup(basePath);
}

SwTableItem * SwTable::GetNode(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

const char * SwTable::GetNodeId(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return m_nodeData[node].id;
}

bool SwTable::SetNodeId(swUI32 node, const char * id)
{
    if (!id || node >= m_nodePos)
        return false;

    free(m_nodeData[node].id);
    m_nodeData[node].id = strdup(id);
    m_nodeData[node].findId = SwThMLParser::GenerateId(id);

    return true;
}

const char * SwTable::GetNodeData(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return m_nodeData[node].data;
}

bool SwTable::GetNodeDataW(swUI32 node, SwStringW & buffer)
{
    if (node >= m_nodePos)
        return false;

    buffer.Copy(m_nodeData[node].data);

    return true;
}

bool SwTable::SetNodeData(swUI32 node, const char * data)
{
    if (!data || node >= m_nodePos)
        return false;

    free(m_nodeData[node].data);
    m_nodeData[node].data = strdup(data);

    return true;
}


const char * SwTable::GetNodeParam1(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return m_nodeData[node].param1;
}

swUI32 SwTable::GetNodeParam1AsUint(swUI32 node)
{
    if (node >= m_nodePos)
        return 0;

    return strtoul(m_nodeData[node].param1, NULL, 10);
}

bool SwTable::SetNodeParam1(swUI32 node, const char * param)
{
    if (!param || node >= m_nodePos)
        return false;

    free(m_nodeData[node].param1);
    m_nodeData[node].param1 = strdup(param);

    return true;
}

bool SwTable::SetNodeParam1(swUI32 node, swUI32 param)
{
    char s[12];
    sprintf(s, "%lu", (unsigned long) param);

    return SetNodeParam1(node, s);
}

const char * SwTable::GetNodeParam2(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return m_nodeData[node].param2;
}

swUI32 SwTable::GetNodeParam2AsUint(swUI32 node)
{
    if (node >= m_nodePos)
        return 0;

    return strtoul(m_nodeData[node].param2, NULL, 10);
}

void SwTable::GetNodeParam2(swUI32 node, swUI32 & selBegin, swUI32 & selEnd)
{
    selBegin = 0;
    selEnd = 0;

    if (node >= m_nodePos)
        return;

    selBegin = strtoul(m_nodeData[node].param2, NULL, 10);
    char * p = strchr(m_nodeData[node].param2, ',');

    if (!p)
        return;

    while (!isdigit(*p) && *p != '\0')
        p++;

    selEnd = strtoul(p, NULL, 10);
}

void SwTable::GetNodeParam2(swUI32 node, SwTextRange & sel)
{
    sel.Reset();

    if (node >= m_nodePos)
        return;

    sel.begin = strtol(m_nodeData[node].param2, NULL, 10);
    char * p = strchr(m_nodeData[node].param2, ',');

    if (!p)
        return;

    while (!isdigit(*p) && *p != '\0')
        p++;

    sel.end = strtol(p, NULL, 10);
}

bool SwTable::SetNodeParam2(swUI32 node, const char * param)
{
    if (!param || node >= m_nodePos)
        return false;

    free(m_nodeData[node].param2);
    m_nodeData[node].param2 = strdup(param);

    return true;
}

bool SwTable::SetNodeParam2(swUI32 node, swUI32 param)
{
    char s[12];
    sprintf(s, "%lu", (unsigned long) param);

    return SetNodeParam2(node, s);
}

bool SwTable::SetNodeParam2(swUI32 node, swUI32 selBegin, swUI32 selEnd)
{
    char s[25];
    sprintf(s, "%lu,%lu", (unsigned long) selBegin, (unsigned long) selEnd);

    return SetNodeParam2(node, s);
}

bool SwTable::SetNodeParam2(swUI32 node, SwTextRange sel)
{
    char s[25];
    sprintf(s, "%li,%li", (long) sel.begin, (long) sel.end);

    return SetNodeParam2(node, s);
}

swUI32 SwTable::GetNodeCellType(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID;

    return m_nodeData[node].cellType;
}

bool SwTable::SetNodeCellType(swUI32 node, swUI8 type)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].cellType = type;

    return true;
}

swUI32 SwTable::AppendNode(const char * id, const char * data, swUI8 type)
{
    if (!id || !data)
        return NODE_ID_INVALID;

    return AppendNode(id, data, "", "", type);
}

swUI32 SwTable::AppendNode(const char * id, const char * data, const char * param1, const char * param2, swUI8 type)
{
    if (!id || !data || !param1 || !param2)
        return NODE_ID_INVALID;

    if (!VerifyNode())
        return NODE_ID_INVALID;

    m_nodePos ++;

    SetNodeId(m_nodePos - 1, id);
    SetNodeData(m_nodePos - 1, data);
    SetNodeParam1(m_nodePos - 1, param1);
    SetNodeParam2(m_nodePos - 1, param2);
    SetNodeCellType(m_nodePos - 1, type);

    return m_nodePos - 1;
}

bool SwTable::InsertNode(swUI32 nodePos, const char * id, const char * data, swUI8 type)
{
    if (!id || !data)
        return false;

    return InsertNode(nodePos, id, data, "", "", type);
}

bool SwTable::InsertNode(swUI32 nodePos, const char * id, const char * data, const char * param1, const char * param2, swUI8 type)
{
    if (!id || !data || !param1 || !param2)
        return false;

    if (!ShiftNodesDown(nodePos))
        return false;

    if (nodePos > m_nodePos - 1)
    {
        if (AppendNode(id, data, param1, param2, type) != NODE_ID_INVALID)
            return true;

        return false;
    }

    SetNodeId(nodePos, id);
    SetNodeData(nodePos, data);
    SetNodeParam1(nodePos, param1);
    SetNodeParam2(nodePos, param2);
    SetNodeCellType(nodePos, type);

    return true;
}

bool SwTable::DeleteNode(swUI32 nodePos)
{
    if (nodePos >= m_nodePos)
        return false;

    if (nodePos != GetLastNode())
    {
        ShiftNodesUp(nodePos + 1);
    }
    else
    {
        m_nodePos --;
        m_nodeData[m_nodePos].Reset();
    }

    return true;
}

swUI32 SwTable::UpdateNode(const char * id, const char * data, swUI8 type)
{
    if (!id || !data)
        return NODE_ID_INVALID;

    return UpdateNode(id, data, "", "", type);
}


swUI32 SwTable::UpdateNode(const char * id, const char * data, const char * param1, const char * param2, swUI8 type)
{
    if (!id || !data || !param1 || !param2)
        return NODE_ID_INVALID;

    swUI32 node = FindItemById(id);

    if (node == NODE_ID_INVALID)
        return AppendNode(id, data, param1, param2, type);

    SetNodeData(node, data);
    SetNodeParam1(node, param1);
    SetNodeParam2(node, param2);
    SetNodeCellType(node, type);

    return node;
}

const char * SwTable::GetTableCaption()
{
    return m_tableCaption;
}

const wchar_t * SwTable::GetTableCaptionW()
{
    static SwStringW caption;
    caption.Copy(m_tableCaption);
    return caption;
}

void SwTable::SetTableCaption(const char * caption)
{
    if (!caption)
        return;

    if (m_tableCaption)
        free(m_tableCaption);

    m_tableCaption = strdup(caption);
}


swUI32 SwTable::GetDataSize()
{
    swUI32 dataSize = strlen(m_tableCaption);

    for (swUI32 i = 0; i < m_nodePos; i ++)
        dataSize += strlen(m_nodeData[i].id) + strlen(m_nodeData[i].data) + strlen(m_nodeData[i].param1) + strlen(m_nodeData[i].param2);

    return dataSize;
}

swUI32 SwTable::GetItems()
{
    return m_nodePos;
}

bool SwTable::GetTranslatedString(const char * id, SwStringW & buffer, bool stripAmpersand)
{
    SwString buffer2;

    if (!id)
    {
        buffer = L"";
        return false;
    }

    swUI32 result = FindItemById(id);

    if (result == NODE_ID_INVALID || m_nodeData[result].data[0] == '\0')
    {
        buffer.Copy(id);
        return false;
    }

    buffer2 = m_nodeData[result].data;

    if (stripAmpersand)
        StripAmpersand(buffer2);

    buffer.Copy(buffer2);

    return true;
}

swUI32 SwTable::FindItemById(const char * id)
{
    if (!id)
        return NODE_ID_INVALID;

    swUI32 findId = SwThMLParser::GenerateId(id);

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if ((findId == m_nodeData[i].findId) & (strcmp(m_nodeData[i].id, id) == 0))
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwTable::FindItemByData(const char * data)
{
    if (!data)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (strcmp(m_nodeData[i].data, data) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 SwTable::Format(SwString & buffer)
{
    SwTable tableData;
    SwString buffer2;
    swUI32 node, dataSize = 0;

    SwHtmlEncodedChar::XmlEncodeString(m_tableCaption, buffer);
    tableData.SetTableCaption(buffer);

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        node = tableData.AppendNode("", "", "", "");

        SwHtmlEncodedChar::XmlEncodeString(m_nodeData[i].id, buffer);
        tableData.SetNodeId(node, buffer);

        SwHtmlEncodedChar::XmlEncodeString(m_nodeData[i].data, buffer);
        tableData.SetNodeData(node, buffer);

        SwHtmlEncodedChar::XmlEncodeString(m_nodeData[i].param1, buffer);
        tableData.SetNodeParam1(node, buffer);

        SwHtmlEncodedChar::XmlEncodeString(m_nodeData[i].param2, buffer);
        tableData.SetNodeParam2(node, buffer);
    }

    dataSize = tableData.GetDataSize() + strlen(tablebeginformatString) + strlen(tableendformatString);

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (m_nodeData[i].cellType == CELLTYPE_TEXT)
            dataSize += strlen(tablerowformatString);
        else if (m_nodeData[i].cellType == CELLTYPE_AUDIO)
            dataSize += strlen(tablerowaudioformatString);
        else if (m_nodeData[i].cellType == CELLTYPE_IMAGE)
            dataSize += strlen(tablerowimageformatString);
        else if (m_nodeData[i].cellType == CELLTYPE_VIDEO)
            dataSize += strlen(tablerowvideoformatString);

    }

    buffer.Size(dataSize + 1);

    sprintf(buffer, tablebeginformatString, m_tableCaption);

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (m_nodeData[i].cellType == CELLTYPE_TEXT)
        {
            buffer2.Size(strlen(tablerowformatString) + strlen(m_nodeData[i].id) + strlen(m_nodeData[i].data) + strlen(m_nodeData[i].param1) + strlen(m_nodeData[i].param2) + 1);
            sprintf(buffer2, tablerowformatString, m_nodeData[i].param1, m_nodeData[i].param2, m_nodeData[i].id, m_nodeData[i].data);
        }
        else if (m_nodeData[i].cellType == CELLTYPE_AUDIO)
        {
            buffer2.Size(strlen(tablerowaudioformatString) + strlen(m_nodeData[i].id) + strlen(m_nodeData[i].data) + strlen(m_nodeData[i].param1) + strlen(m_nodeData[i].param2) + 1);
            sprintf(buffer2, tablerowaudioformatString, m_nodeData[i].param1, m_nodeData[i].param2, m_nodeData[i].id, m_nodeData[i].data);
        }
        else if (m_nodeData[i].cellType == CELLTYPE_IMAGE)
        {
            buffer2.Size(strlen(tablerowimageformatString) + strlen(m_nodeData[i].id) + strlen(m_nodeData[i].data) + strlen(m_nodeData[i].param1) + strlen(m_nodeData[i].param2) + 1);
            sprintf(buffer2, tablerowimageformatString, m_nodeData[i].param1, m_nodeData[i].param2, m_nodeData[i].id, m_nodeData[i].data);
        }
        else if (m_nodeData[i].cellType == CELLTYPE_VIDEO)
        {
            buffer2.Size(strlen(tablerowvideoformatString) + strlen(m_nodeData[i].id) + strlen(m_nodeData[i].data) + strlen(m_nodeData[i].param1) + strlen(m_nodeData[i].param2) + 1);
            sprintf(buffer2, tablerowvideoformatString, m_nodeData[i].param1, m_nodeData[i].param2, m_nodeData[i].id, m_nodeData[i].data);
        }

        buffer += buffer2;
    }

    buffer += tableendformatString;

    return buffer.Strlen();
}

bool SwTable::GetMediaPath(const char * id, SwString & buffer)
{
    if (!id)
        return false;

    swUI32 node = FindItemById(id);
    SwString bufferPath, bufferData;

    if (!m_basePath)
        return false;

    if (node == NODE_ID_INVALID || m_nodeData[node].data[0] == '\0')
        return false;

    return SwGetPathFromRelative(m_basePath, m_nodeData[node].data, buffer);
}

void SwTable::StripAmpersand(char * source)
{
    if (!source)
        return;

    swUI32 posRead = 0, posWrite = 0;

    while (source[posRead] != '\0')
    {
        if (source[posRead] != '&')
        {
            source[posWrite] = source[posRead];
            posWrite ++;
        }

        posRead ++;
    }

    source[posWrite] = '\0';
}

void SwTable::StripAmpersand(wchar_t * source)
{
    if (!source)
        return;

    swUI32 posRead = 0, posWrite = 0;

    while (source[posRead] != L'\0')
    {
        if (source[posRead] != L'&')
        {
            source[posWrite] = source[posRead];
            posWrite ++;
        }

        posRead ++;
    }

    source[posWrite] = '\0';
}

void SwTable::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    int item;

    // Column 1 is used as identifier column;
    for (swUI32 i = 0; i < GetItems(); i ++)
    {
        item = listctrl->InsertItem(listctrl->GetItemCount(), GetNodeData(i));
        listctrl->SetItem(item, 1, GetNodeId(i));
    }
}

void SwTable::FillCtrlEx(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    int item;

    // Column 0 is used as identifier column;
    for (swUI32 i = 0; i < GetItems(); i ++)
    {
        item = listctrl->InsertItem(listctrl->GetItemCount(), GetNodeId(i));
        listctrl->SetItem(item, 1, GetNodeData(i));
        listctrl->SetItem(item, 2, GetNodeParam1(i));
        listctrl->SetItem(item, 3, GetNodeParam2(i));
    }
}

void SwTable::FillPropertyGrid(wxPropertyGrid * pg)
{
    if (!pg)
        return;

    pg->Clear();

    SwString buffer;

    for (swUI32 i = 0; i < GetItems(); i ++)
    {
        SwGetRelativePath(GetBasePath(), GetNodeData(i), buffer);
        pg->Append(new wxStringProperty(GetNodeId(i), wxPG_LABEL, GetNodeData(i)));
    }
}

void SwTable::Import(wxPropertyGrid * pg, const char * id, swUI8 type)
{
    if (!pg || !id)
        return;

    Reset();
    SetTableCaption(id);

    wxPropertyGridIterator it;
    for (it = pg->GetIterator(); !it.AtEnd(); it ++)
    {
        wxPGProperty* p = *it;
        AppendNode(p->GetLabel().utf8_str(), p->GetValueAsString().utf8_str(), type);
    }
}

void SwTable::Import(wxListCtrl * listctrl, const char * id, swUI8 type)
{
    if (!listctrl || !id)
        return;

    Reset();
    SetTableCaption(id);

    // Column 1 is used as identifier column;
    for (int i = 0; i < listctrl->GetItemCount(); i ++)
    {
        AppendNode(listctrl->GetItemText(i, 1).utf8_str(), listctrl->GetItemText(i, 0).utf8_str(), type);
    }
}

void SwTable::ImportEx(wxListCtrl * listctrl, const char * id, swUI8 type)
{
    if (!listctrl || !id)
        return;

    Reset();
    SetTableCaption(id);

    // Column 0 is used as identifier column;
    for (int i = 0; i < listctrl->GetItemCount(); i ++)
    {
        AppendNode(listctrl->GetItemText(i, 0).utf8_str(), listctrl->GetItemText(i, 1).utf8_str(), listctrl->GetItemText(i, 2).utf8_str(), listctrl->GetItemText(i, 3).utf8_str(), type);
    }
}

void SwTable::Import(wxDataViewListCtrl * listctrl, const char * id, swUI8 type)
{
    if (!listctrl || !id)
        return;

    Reset();
    SetTableCaption(id);

    // Column 0 is used as identifier column;
    for (int i = 0; i < listctrl->GetItemCount(); i ++)
    {
        AppendNode(listctrl->GetTextValue(i, 0).utf8_str(), listctrl->GetTextValue(i, 1).utf8_str(), listctrl->GetTextValue(i, 2).utf8_str(),  listctrl->GetTextValue(i, 3).utf8_str(), type);
    }
}

void SwTable::FillDataViewListCtrl(wxDataViewListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    wxVector<wxVariant> data;

    // Column 0 is used as identifier column;
    for (swUI32 i = 0; i < GetItems(); i ++)
    {
        data.clear();
        data.push_back(wxVariant(GetNodeId(i)));
        data.push_back(wxVariant(GetNodeData(i)));
        data.push_back(wxVariant(GetNodeParam1(i)));
        data.push_back(wxVariant(GetNodeParam2(i)));
        listctrl->AppendItem(data);
    }
}

SwDataFile::SwDataFile()
{
    SetThML_ElementArray();
    m_arraySize = 0;
    m_arrayPos = 0;
    m_itemNodeArray = NULL;
}

SwDataFile::~SwDataFile()
{
    if (m_itemNodeArray)
        free(m_itemNodeArray);
}

bool SwDataFile::OpenFile(const char * path, bool verifyFile)
{
    if (!path)
        return false;

    if (verifyFile && !VerifyFile(path))
        return false;

    if (SwThMLParser::OpenFile(path, MODE_FS_INT))
    {
        m_tableData.SetBasePath(GetBasePath());
        return true;
    }

    return false;
}

bool SwDataFile::VerifyFile(const char * path)
{
    if (!path)
        return false;

    FILE * f;

    f = SwFopen(path, FMD_RW);

    if (f)
    {
        fclose(f);
        return true;
    }

    f = SwFopen(path, FMD_RWC);

    if (!f)
        return false;

    fputs(blankHtml, f);
    fclose(f);

    return true;
}

bool SwDataFile::IncreaseArray()
{
    if (m_arraySize + 24 >= NODE_ID_INVALID)
        return false;

    swUI32 * p = (swUI32 *) realloc((void *) m_itemNodeArray, (m_arraySize + 24) * sizeof(swUI32));

    if (p)
    {
        m_arraySize += 24;
        m_itemNodeArray = p;
        return true;
    }

    return false;
}

swUI32 SwDataFile::CreateTableIndex()
{
    swUI32 pos = 0, caption;

    m_arrayPos = 0;

    for(;;)
    {
        pos = FindElement(pos, THML_TABLE, NODE_TYPE_BEGIN_TAG);

        if (pos == NODE_ID_INVALID)
            break;

        caption = FindWithInElement(pos, 0, THML_CAPTION, NODE_TYPE_BEGIN_TAG);

        if (caption != NODE_ID_INVALID)
        {
            if (m_arraySize <= m_arrayPos && !IncreaseArray())
                return 0;

            m_itemNodeArray[m_arrayPos] = pos;
            m_arrayPos ++;
        }


        pos ++;
    }

    return m_arrayPos;
}

swUI32 SwDataFile::GetTableCount()
{
    return m_arrayPos;
}

swUI32 SwDataFile::GetTableCaption(swUI32 table, SwString & dest)
{
    SwString buffer;
    swUI32 pos;

    if (table >= m_arrayPos)
        return 0;

    pos = FindWithInElement(m_itemNodeArray[table], 0, THML_CAPTION, NODE_TYPE_BEGIN_TAG);

    if (pos == NODE_ID_INVALID)
        return 0;

    pos = FindWithInElement(pos, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

    if (pos == NODE_ID_INVALID)
        return 0;

    if (!GetNodeData(pos, buffer))
        return 0;

    RemoveWhiteSpace(buffer);
    swUI32 len = strlen((char *) buffer) + 1;

    if (!dest.Size(len))
        return 0;

    swUI8 lastChar = LCH_BREAK;
    return SwHtml::Html2Text(buffer, (char *) dest, len, lastChar, true);
}

swUI32 SwDataFile::GetTableCaptionW(swUI32 table, SwStringW & dest)
{
    SwString buffer, buffer2;
    swUI32 pos;

    if (table >= m_arrayPos)
        return 0;

    pos = FindWithInElement(m_itemNodeArray[table], 0, THML_CAPTION, NODE_TYPE_BEGIN_TAG);

    if (pos == NODE_ID_INVALID)
        return 0;

    pos = FindWithInElement(pos, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

    if (pos == NODE_ID_INVALID)
        return 0;

    if (!GetNodeData(pos, buffer))
        return 0;

    RemoveWhiteSpace(buffer);

    swUI32 len = buffer.Strlen() + 1;

    if (!buffer2.Size(len))
        return 0;

    swUI8 lastChar = LCH_BREAK;
    len = SwHtml::Html2Text(buffer, buffer2, len, lastChar, true);

    dest.Copy(buffer2);
    return dest.Strlen();
}

swUI32 SwDataFile::FindTableByCaption(const char * caption)
{
    SwString buffer;
    swUI32 pos = 0;

    if (!caption || !strlen(caption))
        return NODE_ID_INVALID;

    while (pos < m_arrayPos)
    {
        if (GetTableCaption(pos, buffer) && strcmp(caption, (char *) buffer) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwDataFile::FindTableByCaption(const wchar_t * caption)
{
    SwStringW buffer;
    swUI32 pos = 0;

    if (!caption || !wcslen(caption))
        return NODE_ID_INVALID;

    while (pos < m_arrayPos)
    {
        if (GetTableCaptionW(pos, buffer) && buffer.StrCmp(caption) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

void SwDataFile::OnNodeDataUpdate()
{
    m_arrayPos = 0;
    CreateTableIndex();
}

bool SwDataFile::OpenFile(const char * path, swUI8 mode, bool processtableData)
{
    if (!path)
        return false;

    bool status = SwThMLParser::OpenFile(path, mode, processtableData);

    if (status)
        OnNodeDataUpdate();

    return status;
}

bool SwDataFile::CloseFile(bool freeResources)
{
    bool status = SwThMLParser::CloseFile(freeResources);

    if (status)
        m_arrayPos = 0;

    return status;
}

bool SwDataFile::VerifyClose()
{
    return true;
}

bool SwDataFile::FillTable(swUI32 table)
{
    return FillTable(table, m_tableData);
}

bool SwDataFile::FillTable(swUI32 table, SwTable & tableData)
{
    if (table >= m_arrayPos)
        return false;

    swUI32 offSet = 0;
    swUI32 caption, tableRow, column1, column2;
    swUI32 tableNode;
    SwString buffer, buffer2;
    swUI8 lastChar;

    if (GetBasePath())
        tableData.SetBasePath(GetBasePath());

    caption = FindWithInElement(m_itemNodeArray[table], 0, THML_CAPTION, NODE_TYPE_BEGIN_TAG);

    if (caption != NODE_ID_INVALID)
    {
        if (GetInnerText(caption, buffer2))
        {
            lastChar = LCH_BREAK;
            buffer.Size(strlen(buffer2) + 1);
            SwHtml::Html2Text(buffer2, buffer, buffer.GetSize(), lastChar, true);
            RemoveWhiteSpace(buffer);
            tableData.SetTableCaption(buffer);
        }
    }

    for(;;)
    {
        tableRow = FindWithInElement(m_itemNodeArray[table], offSet, THML_TR, NODE_TYPE_BEGIN_TAG);

        if (tableRow == NODE_ID_INVALID)
            break;

        offSet = tableRow + 1 - m_itemNodeArray[table];

        column1 = FindWithInElement(tableRow, 0, THML_TD, NODE_TYPE_BEGIN_TAG);

        if (column1 == NODE_ID_INVALID)
            continue;

        column2 = FindWithInElement(tableRow, 1 + column1 - tableRow,  THML_TD, NODE_TYPE_BEGIN_TAG);

        if (column2 == NODE_ID_INVALID)
            continue;

        tableNode = tableData.AppendNode("", "", "", "");

        if (tableNode == NODE_ID_INVALID)
            break;

        if (GetInnerText(column1, buffer2))
        {
            lastChar = LCH_BREAK;
            buffer.Size(buffer2.Strlen() + 1);
            SwHtml::Html2Text(buffer2, buffer, buffer.GetSize(), lastChar, true);
            RemoveWhiteSpace(buffer);
            tableData.SetNodeId(tableNode, buffer);
        }

        swUI8 type = GetInnerMediaPath(column2, buffer2);
        if (type == CELLTYPE_AUDIO || type == CELLTYPE_IMAGE || type == CELLTYPE_VIDEO)
        {
            lastChar = LCH_BREAK;
            buffer.Size(buffer2.Strlen() + 1);
            SwHtml::Html2Text(buffer2, buffer, buffer.GetSize(), lastChar, true);
            tableData.SetNodeData(tableNode, buffer);
            tableData.SetNodeCellType(tableNode, type);
        }
        else
        {
            tableData.SetNodeCellType(tableNode, CELLTYPE_TEXT);
            if (GetInnerText(column2, buffer2))
            {
                lastChar = LCH_BREAK;
                buffer.Size(buffer2.Strlen() + 1);
                SwHtml::Html2Text(buffer2, buffer, buffer.GetSize(), lastChar, true);
                RemoveWhiteSpace(buffer);
                tableData.SetNodeData(tableNode, buffer);
            }
        }

        if (GetNamedValueFromNode(tableRow, "param1", buffer2))
        {
            lastChar = LCH_BREAK;
            buffer.Size(buffer2.Strlen() + 1);
            SwHtml::Html2Text(buffer2, buffer, buffer.GetSize(), lastChar, true);
            tableData.SetNodeParam1(tableNode, buffer);
        }

        if (GetNamedValueFromNode(tableRow, "param2", buffer2))
        {
            lastChar = LCH_BREAK;
            buffer.Size(buffer2.Strlen() + 1);
            SwHtml::Html2Text(buffer2, buffer, buffer.GetSize(), lastChar, true);
            tableData.SetNodeParam2(tableNode, buffer);
        }
    }

    return true;
}

bool SwDataFile::AppendTable()
{
    return AppendTable(m_tableData);
}

bool SwDataFile::AppendTable(SwTable & tableData)
{
    SwString buffer;
    tableData.Format(buffer);
    swUI32 insertPos;

    insertPos = FindElement(0, THML_BODY, NODE_TYPE_END_TAG);
    if (insertPos == NODE_ID_INVALID)
        return false;

    return InsertNodes(insertPos, buffer, true);
}

bool SwDataFile::InsertTable(swUI32 tablePos)
{
    return InsertTable(tablePos, m_tableData);
}

bool SwDataFile::InsertTable(swUI32 tablePos, SwTable & tableData)
{
    SwString buffer;
    tableData.Format(buffer);

    if (tablePos >= m_arrayPos)
        return AppendTable(tableData);

    return InsertNodes(m_itemNodeArray[tablePos], buffer, true);
}

bool SwDataFile::ReplaceTable(swUI32 table)
{
    return ReplaceTable(table, m_tableData);
}

bool SwDataFile::ReplaceTable(swUI32 table, SwTable & tableData)
{
    if (table >= m_arrayPos)
        return false;

    if (m_arrayPos == 0)
        return AppendTable(tableData);

    SwString buffer;
    tableData.Format(buffer);

    return ReplaceNodes(m_itemNodeArray[table], GetNodeMate(m_itemNodeArray[table]), buffer, true);
}

bool SwDataFile::UpdateTable(const char * name)
{
    if (!name)
        return false;

    swUI32 node = FindTableByCaption(name);

    GetTable().SetTableCaption(name);

    if (node == NODE_ID_INVALID)
    {
        return AppendTable();
    }
    else
    {
        return ReplaceTable(node);
    }

    return false;
}

bool SwDataFile::UpdateTable(const char * name, SwTable & tableData)
{
    if (!name)
        return false;

    swUI32 node = FindTableByCaption(name);

    if (node == NODE_ID_INVALID)
    {
        return AppendTable(tableData);
    }
    else
    {
        return ReplaceTable(node, tableData);
    }

    return false;
}

bool SwDataFile::DeleteTable(swUI32 table)
{
    if (table >= m_arrayPos || m_arrayPos == 0)
        return false;

    return DeleteNodes(m_itemNodeArray[table], GetNodeMate(m_itemNodeArray[table]), true);
}

void SwDataFile::RemoveWhiteSpace(char * buffer)
{
    if (!buffer)
        return;

    swUI32 pos = 0, leadingSpace = 0;

    if (buffer[0] == '\0')
        return;

    pos = strlen(buffer) - 1;

    while(isspace(buffer[pos]))
        pos --;

    buffer[pos + 1] = '\0';

    while(isspace(buffer[leadingSpace]))
        leadingSpace ++;

    pos = 0;
    if (leadingSpace)
    {
        while(buffer[leadingSpace] != '\0')
        {
            buffer[pos] = buffer[leadingSpace];
            leadingSpace ++;
            pos ++;
        }

        buffer[pos] = '\0';
    }
}

SwTable & SwDataFile::GetTable()
{
    return m_tableData;
}

bool SwDataFile::MakeControlString(const char * id, SwTable * translationTable, SwStringW & buffer)
{
    buffer.Reset();

    if (!id)
        return false;

    bool success = translationTable->GetTranslatedString(id, buffer, false);

    return success;
}

void SwDataFile::FillCtrl(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    listCtrl->DeleteAllItems();

    swUI32 pos = 0;
    SwStringW buffer;

    while (pos < GetTableCount())
    {
        GetTableCaptionW(pos, buffer);
        listCtrl->InsertItem(listCtrl->GetItemCount(), buffer.GetArray());

        pos ++;
    }
}

void SwDataFile::FillCtrl(wxChoice & choice)
{
    SwStringW buffer;

    SwClientData * data;
    for (swUI32 i = 0; i < GetTableCount(); i++)
    {
        if (!GetTableCaptionW(i, buffer))
            break;

        data = new SwClientData(i);
        choice.Append(buffer.GetArray(), data);
    }
}

void SwDataFile::CreateDataListString(wxListCtrl * listctrl, SwString & buffer, const char * id)
{
    if (!listctrl || !id)
        return;

    buffer = "";
    buffer = "<datalist id=\"";
    buffer += id;
    buffer += "\">\n";

    for (int i = 0; i < listctrl->GetItemCount(); i ++)
    {
        buffer += "<option value=\"";
        buffer += listctrl->GetItemText(i, 0).utf8_str();
        buffer += "\"/>\n";
    }

    buffer += "</datalist>\n";
}

void SwDataFile::CreateDataListString(SwStringArray & array, SwString & buffer, const char * id)
{
    if (!id)
        return;

    buffer = "";
    buffer = "<datalist id=\"";
    buffer += id;
    buffer += "\">\n";

    for (swUI32 i = 0; i < array.GetCount(); i ++)
    {
        buffer += "<option value=\"";
        buffer += array.GetAt(i);
        buffer += "\"/>\n";
    }

    buffer += "</datalist>\n";
}
