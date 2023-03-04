///////////////////////////////////////////////////////////////////
// Name:        modules.cpp
// Purpose:     Modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/module/moduleloader.h"

void SwApplicationInterface::LoadModules()
{
    SwString filepath;
    SwModuleLoader loader;

    filepath = GetModuleLibraryDir();
    loader.RecurseDir(filepath, true);

    SetModuleManagerState((bool) sw_modulemanager.GetModules());
}

void SwApplicationInterface::LoadHelpModules()
{
    SwString filepath;
    SwModuleLoader loader;

    filepath = GetHelpDir();
    loader.RecurseDir(filepath, true);

    SetModuleManagerState((bool) sw_modulemanager.GetModules());
}

void SwApplicationInterface::LoadReferenceModules()
{
    SwString filepath;
    SwModuleLoader loader;

    filepath = GetReferenceDir();
    loader.RecurseDir(filepath, true);

    SetModuleManagerState((bool) sw_modulemanager.GetModules());
}

void SwApplicationInterface::GetModuleList(wxChoice * choice)
{
    if (!choice)
        return;

    SwModule * module;
    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < GetModuleManager().GetModules(); i++)
    {
        module = GetModuleManager().GetAt(i);
        if (!module)
            break;

        data = new SwClientData(module->GetManagerId());
        buffer.Copy(module->m_header.GetTitle());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetModuleList(wxChoice * choice, swUI8 category)
{
    if (!choice)
        return;

    SwModule * module;
    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < GetModuleManager().GetModules(); i++)
    {
        module = GetModuleManager().GetAt(i);
        if (!module || module->GetHeader().category != category)
            break;

        data = new SwClientData(module->GetManagerId());
        buffer.Copy(module->m_header.GetTitle());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetModuleList(wxCheckListBox * list)
{
    if (!list)
        return;

    SwModule * module;
    SwStringW buffer;
    SwClientData * data;
    int item;
    swUI8 modType;

    for (swUI32 i = 0; i < GetModuleManager().GetModules(); i++)
    {
        module = GetModuleManager().GetAt(i);
        if (!module)
            break;

        modType = module->m_header.category;

        if (modType != CATEGORY_BIBLE && modType != CATEGORY_BIBLECOMMENTARY && modType != CATEGORY_DICTIONARY &&
                modType != CATEGORY_ENCYCLOPEDIA && modType != CATEGORY_LEXICON && modType != CATEGORY_TOPICALINDEX && modType != CATEGORY_REFERENCE)
            continue;

        data = new SwClientData(module->GetManagerId());
        buffer.Copy(module->m_header.GetTitle());
        item = list->Append(buffer.GetArray(), data);
        if (module->m_autodefEnabled)
            list->Check(item);
    }
}

void SwApplicationInterface::UpdateModuleStates(wxCheckListBox * list)
{
    if (!list)
        return;

    SwModule * module;
    SwClientData * data;
    swUI32 node;

    for (swUI32 i = 0; i < list->GetCount(); i++)
    {
        data = (SwClientData *) list->GetClientObject(i);
        node = GetModuleManager().FindByMID(data->m_data);

        if (node == NODE_ID_INVALID)
            continue;

        module = GetModuleManager().GetAt(node);

        if (!module)
            continue;

        module->m_autodefEnabled = list->IsChecked(i);

        if (list->IsChecked(i))
            SwApplicationInterface::GetPreferences().GetTable().UpdateNode(module->GetHeader().GetIdentifier(), "true");
        else
            SwApplicationInterface::GetPreferences().GetTable().UpdateNode(module->GetHeader().GetIdentifier(), "false");
    }
}

void SwApplicationInterface::LoadModuleStates()
{
    SwModule * module;
    SwStringW buffer;
    swUI32 item;

    for (swUI32 i = 0; i < GetModuleManager().GetModules(); i++)
    {
        module = GetModuleManager().GetAt(i);

        if (!module)
            continue;

        item = SwApplicationInterface::GetPreferences().GetTable().FindItemById(module->GetHeader().GetIdentifier());
        if (item == NODE_ID_INVALID)
            continue;

        module->m_autodefEnabled = SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(item));
    }
}

void SwApplicationInterface::GetModuleList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;
    SwModule * module;
    swUI8 category = 0;

    for (swUI8 count = 0; count < LOAD_CATEGORIES_MAX; count ++)
    {
        category = SwCategory::GetLoadOrder(count);

        for (swUI32 i = 0; i < SwApplicationInterface::GetModuleManager().GetModules(); i++)
        {
            module = SwApplicationInterface::GetModuleManager().GetAt(i);

            if (!module)
                break;

            if (module->m_header.GetCategory() != category)
                continue;

            lItem.Clear();
            lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
            lItem.SetColumn(0);
            lItem.SetId(listCtrl->GetItemCount());
            buffer.Copy(module->m_header.GetTitle());
            lItem.SetText(buffer.GetArray());
            lItem.SetData(module->GetManagerId());
            listCtrl->InsertItem(lItem);
        }
    }
}

void SwApplicationInterface::GetModuleList(wxListCtrl * listCtrl, swUI8 category)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;
    SwModule * module;

    for (swUI32 i = 0; i < SwApplicationInterface::GetModuleManager().GetModules(); i++)
    {
        module = SwApplicationInterface::GetModuleManager().GetAt(i);

        if (!module)
            break;

        if (module->m_header.GetCategory() != category)
            continue;

        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(listCtrl->GetItemCount());
        buffer.Copy(module->m_header.GetTitle());
        lItem.SetText(buffer.GetArray());
        lItem.SetData(module->GetManagerId());
        listCtrl->InsertItem(lItem);
    }
}

void SwApplicationInterface::GetMasterKeyModuleList(wxChoice * choice)
{
    if (!choice)
        return;

    SwModule * module;
    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < GetModuleManager().GetModules(); i++)
    {
        module = GetModuleManager().GetAt(i);

        if (!module)
            break;

        if (!module->m_masterKey)
            continue;

        data = new SwClientData(module->GetManagerId());
        buffer.Copy(module->m_header.GetTitle());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetMasterKeyModuleList(wxListCtrl * listCtrl)
{
    if (!listCtrl)
        return;

    SwStringW buffer;
    wxListItem lItem;

    SwModule * module;

    for (swUI32 i = 0; i < SwApplicationInterface::GetModuleManager().GetModules(); i++)
    {
        module = SwApplicationInterface::GetModuleManager().GetAt(i);

        if (!module)
            break;

        if (!module->m_masterKey)
            continue;

        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(listCtrl->GetItemCount());
        buffer.Copy(module->m_header.GetTitle());
        lItem.SetText(buffer.GetArray());
        lItem.SetData(module->GetManagerId());
        listCtrl->InsertItem(lItem);
    }
}

void SwApplicationInterface::GetModuleList(SwModuleTreeCtrl * treeCtrl)
{
    if (!treeCtrl)
        return;

    SwModule * module;
    swUI8 category = 0;

    for (swUI8 count = 0; count < LOAD_CATEGORIES_MAX; count ++)
    {
        category = SwCategory::GetLoadOrder(count);

        for (swUI32 i = 0; i < SwApplicationInterface::GetModuleManager().GetModules(); i++)
        {
            module = SwApplicationInterface::GetModuleManager().GetAt(i);

            if (!module)
                break;

            if (module->m_header.GetCategory() != category)
                continue;

            treeCtrl->BuildTree(module->GetTableofContents(), treeCtrl->GetRootItem(), module->GetHeader().category, module->GetManagerId());
        }
    }
}
