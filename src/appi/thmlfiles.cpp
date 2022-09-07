///////////////////////////////////////////////////////////////////
// Name:        thmlfiles.cpp
// Purpose:     ThML files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/thml/thml_utility.h"

void SwApplicationInterface::LoadThMLFiles()
{
    SwString filepath;
    SwThMLFileLoader loader;

    filepath = GetThMLLibraryDir();
    sw_thmlfilemanager.Reset();
    loader.RecurseDir(filepath, true);

    SetThMLFileManagerState((bool) sw_thmlfilemanager.GetFileCount());
}

void SwApplicationInterface::GetThMLFileList(wxChoice * choice)
{
    if (!choice)
        return;

    SwThMLFile * thmlfile;
    SwStringW buffer;
    SwClientData * data;

    for (wxUint32 i = 0; i < GetThMLFileManager().GetFileCount(); i++)
    {
        thmlfile = GetThMLFileManager().GetAt(i);
        if (!thmlfile)
            break;

        data = new SwClientData(thmlfile->GetManagerId());
        buffer.Copy(thmlfile->GetTitle());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetThMLFileList(wxChoice * choice, swUI8 category)
{
    if (!choice)
        return;

    SwThMLFile * thmlfile;
    SwStringW buffer;
    SwClientData * data;

    for (wxUint32 i = 0; i < GetThMLFileManager().GetFileCount(); i++)
    {
        thmlfile = GetThMLFileManager().GetAt(i);
        if (!thmlfile || thmlfile->m_category != category)
            break;

        data = new SwClientData(thmlfile->GetManagerId());
        buffer.Copy(thmlfile->GetTitle());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetThMLFileList(wxCheckListBox * list)
{
    if (!list)
        return;

    SwThMLFile * thmlfile;
    SwStringW buffer;
    SwClientData * data;
    int item;
    swUI8 category;

    for (wxUint32 i = 0; i < GetThMLFileManager().GetFileCount(); i++)
    {
        thmlfile = GetThMLFileManager().GetAt(i);
        if (!thmlfile)
            break;

        category = thmlfile->m_category;

        if (category != CATEGORY_BIBLE && category != CATEGORY_BIBLECOMMENTARY && category != CATEGORY_DICTIONARY &&
                category != CATEGORY_ENCYCLOPEDIA && category != CATEGORY_LEXICON && category != CATEGORY_TOPICALINDEX && category != CATEGORY_REFERENCE)
            continue;

        data = new SwClientData(thmlfile->GetManagerId());
        buffer.Copy(thmlfile->GetTitle());
        item = list->Append(buffer.GetArray(), data);
        if (thmlfile->m_autodefEnabled)
            list->Check(item);
    }
}

void SwApplicationInterface::GetThMLFileList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;

    SwThMLFile * thmlfile;
    swUI8 category = 0;

    for (swUI8 count = 0; count < LOAD_CATEGORIES_MAX; count ++)
    {
        category = SwCategory::GetLoadOrder(count);

        for (wxUint32 i = 0; i < SwApplicationInterface::GetThMLFileManager().GetFileCount(); i++)
        {
            thmlfile = SwApplicationInterface::GetThMLFileManager().GetAt(i);

            if (!thmlfile)
                break;

            if (thmlfile->GetCategory() != category)
                continue;

            lItem.Clear();
            lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
            lItem.SetColumn(0);
            lItem.SetId(listCtrl->GetItemCount());
            buffer.Copy(thmlfile->GetTitle());
            lItem.SetText(buffer.GetArray());
            lItem.SetData(thmlfile->GetManagerId());
            listCtrl->InsertItem(lItem);
        }
    }
}

void SwApplicationInterface::GetThMLFileList(wxListCtrl * listCtrl, swUI8 category)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;

    SwThMLFile * thmlfile;

    for (wxUint32 i = 0; i < SwApplicationInterface::GetThMLFileManager().GetFileCount(); i++)
    {
        thmlfile = SwApplicationInterface::GetThMLFileManager().GetAt(i);

        if (!thmlfile)
            break;

        if (thmlfile->GetCategory() != category)
            continue;

        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(listCtrl->GetItemCount());
        buffer.Copy(thmlfile->GetTitle());
        lItem.SetText(buffer.GetArray());
        lItem.SetData(thmlfile->GetManagerId());
        listCtrl->InsertItem(lItem);
    }
}

void SwApplicationInterface::GetThMLFileList(SwThMLTreeCtrl * treeCtrl)
{
    if (!treeCtrl)
        return;

    SwThMLFile * thmlfile;
    swUI8 category = 0;

    for (swUI8 count = 0; count < LOAD_CATEGORIES_MAX; count ++)
    {
        category = SwCategory::GetLoadOrder(count);

        for (wxUint32 i = 0; i < SwApplicationInterface::GetThMLFileManager().GetFileCount(); i++)
        {
            thmlfile = SwApplicationInterface::GetThMLFileManager().GetAt(i);

            if (!thmlfile)
                break;

            if (thmlfile->GetCategory() != category)
                continue;

             treeCtrl->BuildTree(thmlfile->m_contents, treeCtrl->GetRootItem(), thmlfile->GetCategory(), thmlfile->GetManagerId());
        }
    }
}

void SwApplicationInterface::UpdateThMLFileStates(wxCheckListBox * list)
{
    if (!list)
        return;

    SwThMLFile * file;
    SwClientData * data;
    swUI32 node;

    for (wxUint32 i = 0; i < list->GetCount(); i++)
    {
        data = (SwClientData *) list->GetClientObject(i);
        node = GetThMLFileManager().FindByMID(data->m_data);

        if (node == NODE_ID_INVALID)
            continue;

        file = GetThMLFileManager().GetAt(node);

        if (!file)
            continue;

        file->m_autodefEnabled = list->IsChecked(i);

        if (list->IsChecked(i))
            SwApplicationInterface::GetPreferences().GetTable().UpdateNode(file->GetFileName(), "true");
        else
            SwApplicationInterface::GetPreferences().GetTable().UpdateNode(file->GetFileName(), "false");
    }
}

void SwApplicationInterface::LoadThMLFileStates()
{
    SwThMLFile * file;
    SwString buffer;
    swUI32 item;

    for (wxUint32 i = 0; i < GetThMLFileManager().GetFileCount(); i++)
    {
        file = GetThMLFileManager().GetAt(i);

        if (!file)
            continue;

        item = SwApplicationInterface::GetPreferences().GetTable().FindItemById(file->GetFileName());
        if (item == NODE_ID_INVALID)
            continue;

        file->m_autodefEnabled = SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(item));
    }
}
