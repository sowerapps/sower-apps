///////////////////////////////////////////////////////////////////
// Name:        bookmarks.cpp
// Purpose:     Bookmarks.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"

void SwApplicationInterface::GetBookMarkList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    SwTableItem * tItem;
    swUI32 pos = 0;
    long listPos;
    wxListItem lItem;
    SwTextRange selection;

    SwStrParser strlist;
    strlist.SetDeliminator('|');

    while (pos < GetBookmarks().GetTable().GetItems())
    {
        tItem = GetBookmarks().GetTable().GetNode(pos);

        if (tItem)
        {
            SwBookMarkClientData * data = new SwBookMarkClientData;

            strlist.ParseString(tItem->GetParam1());
            if (strlist.GetItems() > 1)
            {
                data->m_bookId = strlist.GetItem(0);
                data->m_pageId = strlist.GetItem(1);
                if (strlist.GetItems() > 2)
                    data->m_type = strlist.GetItem(2);

                tItem->GetParam2(selection);
                data->m_selBegin = selection.begin;
                data->m_selEnd = selection.end;

                lItem.Clear();
                lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                lItem.SetColumn(0);
                lItem.SetId(listCtrl->GetItemCount());

                buffer.Copy(tItem->GetData());
                lItem.SetText(buffer.GetArray());
                lItem.SetData(data);

                listPos = listCtrl->InsertItem(lItem);

                lItem.Clear();
                lItem.SetStateMask(wxLIST_MASK_TEXT);
                lItem.SetColumn(1);
                lItem.SetId(listPos);
                buffer.Copy(tItem->GetId());
                lItem.SetText(buffer.GetArray());
                listPos = listCtrl->SetItem(lItem);
            }
        }

        pos ++;
    }
}

void SwApplicationInterface::GetHelpBookMarkList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    SwTableItem * tItem;
    swUI32 pos = 0;
    wxListItem lItem;
    SwTextRange selection;

    SwStrParser strlist;
    strlist.SetDeliminator('|');

    while (pos < GetBookmarks().GetTable().GetItems())
    {
        tItem = GetBookmarks().GetTable().GetNode(pos);

        if (tItem)
        {
            SwBookMarkClientData * data = new SwBookMarkClientData;

            strlist.ParseString(tItem->GetParam1());
            if (strlist.GetItems() > 1)
            {
                data->m_bookId = strlist.GetItem(0);
                data->m_pageId = strlist.GetItem(1);
                if (strlist.GetItems() > 2)
                    data->m_type = strlist.GetItem(2);

                tItem->GetParam2(selection);
                data->m_selBegin = selection.begin;
                data->m_selEnd = selection.end;

                lItem.Clear();
                lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                lItem.SetColumn(0);
                lItem.SetId(listCtrl->GetItemCount());

                buffer.Copy(tItem->GetId());
                lItem.SetText(buffer.GetArray());
                lItem.SetData(data);

                listCtrl->InsertItem(lItem);
            }
        }

        pos ++;
    }
}

void SwApplicationInterface::WriteBookMarklistToTable(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwString buffer;
    SwTextRange selection;
    long listPos = 0;
    swUI32 item = 0;

    GetBookmarks().GetTable().Reset();

    while (listPos < listCtrl->GetItemCount())
    {
        SwBookMarkClientData * data = (SwBookMarkClientData *) listCtrl->GetItemData(listPos);

        if (data)
        {
            item = GetBookmarks().GetTable().AppendNode(listCtrl->GetItemText(listPos, 1).utf8_str(), listCtrl->GetItemText(listPos, 0).utf8_str());
            if (item != NODE_ID_INVALID)
            {
                buffer = data->m_bookId;
                buffer += "|";
                buffer += data->m_pageId;
                buffer += "|";
                buffer += data->m_type;

                GetBookmarks().GetTable().SetNodeParam1(item, buffer);

                selection.begin = data->m_selBegin;
                selection.end = data->m_selEnd;
                GetBookmarks().GetTable().SetNodeParam2(item, selection);
            }
        }

        listPos ++;
    }
}

void SwApplicationInterface::WriteHelpBookMarklistToTable(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwString buffer;
    SwTextRange selection;
    long listPos = 0;
    swUI32 item = 0;

    GetBookmarks().GetTable().Reset();

    while (listPos < listCtrl->GetItemCount())
    {
        SwBookMarkClientData * data = (SwBookMarkClientData *) listCtrl->GetItemData(listPos);

        if (data)
        {
            item = GetBookmarks().GetTable().AppendNode(listCtrl->GetItemText(listPos, 0).utf8_str(), "");
            if (item != NODE_ID_INVALID)
            {
                buffer = data->m_bookId;
                buffer += "|";
                buffer += data->m_pageId;
                buffer += "|";
                buffer += data->m_type;

                GetBookmarks().GetTable().SetNodeParam1(item, buffer);

                selection.begin = data->m_selBegin;
                selection.end = data->m_selEnd;
                GetBookmarks().GetTable().SetNodeParam2(item, selection);
            }
        }

        listPos ++;
    }
}

void SwApplicationInterface::GetRecentFilesList(SwStringArray & array)
{
    swUI32 node;
    SwString buffer;

    array.Reset();

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE1");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE2");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE3");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE4");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE5");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE6");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE7");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE8");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE9");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }

    node = GetRecentFiles().GetTable().FindItemById("SID_FILE10");
    if (node != NODE_ID_INVALID)
    {
        buffer = GetRecentFiles().GetTable().GetNodeData(node);
        if (buffer.Strlen())
            array.Add(buffer);
    }
}

void SwApplicationInterface::WriteRecentFileslistToTable(SwStringArray & array)
{
    if (array.GetCount() > 0)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE1", array.GetAt(0), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE1", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 1)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE2", array.GetAt(1), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE2", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 2)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE3", array.GetAt(2), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE3", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 3)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE4", array.GetAt(3), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE4", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 4)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE5", array.GetAt(4), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE5", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 5)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE6", array.GetAt(5), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE6", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 6)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE7", array.GetAt(6), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE7", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 7)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE8", array.GetAt(7), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE8", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 8)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE9", array.GetAt(8), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE9", "", "", "", CELLTYPE_TEXT);

    if (array.GetCount() > 9)
        GetRecentFiles().GetTable().UpdateNode("SID_FILE10", array.GetAt(9), "", "", CELLTYPE_TEXT);
    else
        GetRecentFiles().GetTable().UpdateNode("SID_FILE10", "", "", "", CELLTYPE_TEXT);
}
