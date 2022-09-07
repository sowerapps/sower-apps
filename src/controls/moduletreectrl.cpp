///////////////////////////////////////////////////////////////////
// Name:        moduletreectrl.cpp
// Purpose:     A tree control that can create it's content from
//              one or more Sower modules. The content from each
//              can be created in a category, and group folders.
//              It can perform searches, and retrieve content from
//              modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/controls/moduletreectrl.h"
#include "../../include/module/category.h"
#include "../../include/filesys/file.h"
#include "../../include/appi/appifa.h"

IMPLEMENT_DYNAMIC_CLASS(SwModuleTreeCtrl, SwTreeCtrl)

SwModuleTreeCtrl::SwModuleTreeCtrl()
    :SwTreeCtrl()
{
    SetSowerImageList();
}

SwModuleTreeCtrl::SwModuleTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwTreeCtrl(parent, id, pos, size, style, validator, name)
{
    SetSowerImageList();
}

SwModuleTreeCtrl::~SwModuleTreeCtrl()
{
}

void SwModuleTreeCtrl::Reset()
{
    DeleteAllItems();
    m_history.Reset();
    m_ids.Reset();
    m_categories.Reset();
    AddRoot("", -1, -1, new SwTreeDataEx());
}


bool SwModuleTreeCtrl::BuildTree(SwTableOfContents & toc, wxTreeItemId parent, swUI8 category, swUI16 managerId)
{
    wxUint32 pos = 0;
    SwTreeAppendData appendData;
    SwString buffer;
    appendData.id = parent;
    swUI16 mod = SwApplicationInterface::GetModuleManager().FindByMID(managerId);
    buffer = SwApplicationInterface::GetModuleManager().GetAt(mod)->GetHeader().GetTitle();
    appendData.depth = 0;

    m_ids.Add(SwApplicationInterface::GetModuleManager().GetAt(mod)->GetHeader().GetIdentifier());

    if (parent.IsOk())
    {
        appendData.id = parent;
    }
    else
    {
        wxTreeItemId id;
        id = GetRootItem();

        if (!id.IsOk())
            id = AddRoot("", -1, -1, new SwTreeDataEx());

        appendData.id = id;
    }

    if (!appendData.id.IsOk())
        return false;

    appendData.id = AppendItemEx(buffer.GetArray(), appendData, SwApplicationInterface::GetBookImageIndex(category), SwApplicationInterface::GetOpenBookImageIndex(category), 2, new SwTreeDataEx(managerId, NODE_ID_INVALID_16));

    appendData.depth = 0;

    while (pos < toc.GetNodes())
    {
        if (!toc.GetTitle(pos, buffer))
            return false;

        if (toc.GetNode(pos)->hasChildren)
            AppendItemEx(buffer.GetArray(), appendData, SwApplicationInterface::GetBookImageIndex(category), SwApplicationInterface::GetOpenBookImageIndex(category), toc.GetNode(pos)->divDepth + 1, new SwTreeDataEx(managerId, pos));
        else
            AppendItemEx(buffer.GetArray(), appendData, SwApplicationInterface::GetPageImageIndex(category), -1, toc.GetNode(pos)->divDepth + 1, new SwTreeDataEx(managerId, pos));

        pos ++;
    }

    return true;
}

bool SwModuleTreeCtrl::VerifyId(SwTreeDataEx * td)
{
    if (!td || td->m_managerId < MANAGER_ID_START || td->m_managerId == NODE_ID_INVALID_16 || td->m_pageId == NODE_ID_INVALID_16)
        return false;

    return true;
}

bool SwModuleTreeCtrl::ReadDivText(SwTreeDataEx * td, SwString & buffer, bool &canCopy)
{
    if (!VerifyId(td))
        return false;

    SwPageData pg;
    pg.m_managerId = td->m_managerId;
    pg.m_pageId = td->m_pageId;

    return SwApplicationInterface::GetModuleManager().LoadPage(pg, buffer, canCopy);
}

bool SwModuleTreeCtrl::Load(SwString & buffer, wxTreeItemId id, bool & canCopy)
{
    SwTreeDataEx * td;

    td = (SwTreeDataEx *) GetItemData(id);

    if (!VerifyId(td))
        return false;

    SwPageData pd;
    pd.m_managerId = td->m_managerId;
    pd.m_pageId = td->m_pageId;

    return SwApplicationInterface::GetModuleManager().LoadPage(pd, buffer, canCopy);
}

void SwModuleTreeCtrl::Search(SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId)
{
    wxTreeItemId next, dummy;
    SwTreeDataEx * td;
    swUI8 lch;
    wxListItem lItem;
    bool canCopy;
    SwPageData pg;
    SwModule * module;
    SwString buffer1, buffer2;
    SwStringW wbuffer1, wbuffer2;

    if (!GetCount())
        return;

    next = GetRootItem();

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(next);

        if (td && td->m_managerId >= MANAGER_ID_START && td->m_pageId != NODE_ID_INVALID_16)
        {
            lch = LCH_BREAK;
            pg.m_managerId = td->m_managerId;
            pg.m_pageId = td->m_pageId;
            module = SwApplicationInterface::GetModuleManager().GetFromMID(td->m_managerId);
            SwApplicationInterface::GetModuleManager().LoadPage(pg, buffer1, canCopy);
            buffer2.Size(buffer1.Strlen() + 1);
            SwHtml::Html2Text(buffer1, buffer2, buffer2.GetSize(), lch, true);
            wbuffer1.Copy(buffer2);

            if (strcmpObj.SearchBuffer(wbuffer1) == CR_EXPRESSION_PASSED)
            {
                if (addId)
                {
                    wbuffer1.Copy(module->m_header.moduleAbbreviation);
                    wbuffer1 += L" ";
                    module->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                    wbuffer2.Copy(buffer1);
                    wbuffer1 += wbuffer2;
                }
                else
                {
                    module->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                    wbuffer1.Copy(buffer1);
                }

                lItem.Clear();
                lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                lItem.SetColumn(0);
                lItem.SetId(listCtrl->GetItemCount());
                lItem.SetText(wbuffer1.GetArray());
                lItem.SetData(next);
                listCtrl->InsertItem(lItem);
            }
        }

        next = GetNextItem(next, false);

        if (!next.IsOk())
            break;
    }

    return;
}

void SwModuleTreeCtrl::Search(swUI16 managerId, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId)
{
    wxTreeItemId next, dummy, parent;
    wxTreeItemIdValue cookie;
    SwTreeDataEx * td;
    swUI8 lch;
    wxListItem lItem;
    bool canCopy;
    SwPageData pg;
    SwModule * module;
    SwString buffer1, buffer2;
    SwStringW wbuffer1, wbuffer2;

    if (!GetCount())
        return;

    next = GetRootItem();
    next = GetFirstChild(next, cookie);

    if (!next.IsOk())
    {
        return;
    }

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(next);
        if (!td)
            return;

        if (td->m_managerId == managerId)
        {
            parent = next;
            break;
        }

        next = GetNextItem(next);

        if (!next.IsOk())
            return;
    }

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(next);

        if (td && td->m_managerId == managerId && td->m_pageId != NODE_ID_INVALID_16)
        {
            lch = LCH_BREAK;
            pg.m_managerId = td->m_managerId;
            pg.m_pageId = td->m_pageId;
            module = SwApplicationInterface::GetModuleManager().GetFromMID(td->m_managerId);
            SwApplicationInterface::GetModuleManager().LoadPage(pg, buffer1, canCopy);
            buffer2.Size(buffer1.Strlen() + 1);
            SwHtml::Html2Text(buffer1, buffer2, buffer2.GetSize(), lch, true);
            wbuffer1.Copy(buffer2);

            if (strcmpObj.SearchBuffer(wbuffer1) == CR_EXPRESSION_PASSED)
            {
                if (addId)
                {
                    wbuffer1.Copy(module->m_header.moduleAbbreviation);
                    wbuffer1 += L" ";
                    module->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                    wbuffer2.Copy(buffer1);
                    wbuffer1 += wbuffer2;
                }
                else
                {
                    module->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                    wbuffer1.Copy(buffer1);
                }

                lItem.Clear();
                lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                lItem.SetColumn(0);
                lItem.SetId(listCtrl->GetItemCount());
                lItem.SetText(wbuffer1.GetArray());
                lItem.SetData(next);
                listCtrl->InsertItem(lItem);
            }
        }

        next = GetNextItemInScope(parent, next);

        if (!next.IsOk())
            break;
    }

    return;
}

void SwModuleTreeCtrl::Search(wxTreeItemId & start, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl)
{
    wxTreeItemId next;
    SwTreeDataEx * td;
    swUI8 lch;
    wxListItem lItem;
    bool canCopy;
    SwPageData pg;
    SwModule * module;
    SwString buffer1, buffer2;
    SwStringW wbuffer1, wbuffer2;

    if (!GetCount())
        return;

    if (!start.IsOk())
        next = GetRootItem();
    else
        next = start;

    if (!next.IsOk())
        return;

    for(;;)
    {
        if (next.IsOk())
            td = (SwTreeDataEx *) GetItemData(next);

        if (td && td->m_managerId >= MANAGER_ID_START && td->m_pageId != NODE_ID_INVALID_16)
        {
            lch = LCH_BREAK;
            pg.m_managerId = td->m_managerId;
            pg.m_pageId = td->m_pageId;
            module = SwApplicationInterface::GetModuleManager().GetAt(td->m_managerId);
            SwApplicationInterface::GetModuleManager().LoadPage(pg, buffer1, canCopy);
            buffer2.Size(buffer1.Strlen() + 1);
            SwHtml::Html2Text(buffer1, buffer2, buffer2.GetSize(), lch, true);
            wbuffer1.Copy(buffer2);

            if (strcmpObj.SearchBuffer(wbuffer1) == CR_EXPRESSION_PASSED)
            {
                wbuffer1.Copy(module->m_header.moduleAbbreviation);
                wbuffer1 += L" ";
                module->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                wbuffer2.Copy(buffer1);
                wbuffer1 += wbuffer2;

                lItem.Clear();
                lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
                lItem.SetColumn(0);
                lItem.SetId(listCtrl->GetItemCount());
                lItem.SetText(wbuffer1.GetArray());
                lItem.SetData(next);
                listCtrl->InsertItem(lItem);
            }
        }

        next = GetNextItem(next, false);

        if (!next.IsOk())
            break;
    }

    return;
}

wxTreeItemId SwModuleTreeCtrl::Search(wxTreeItemId& start, swUI16 managerId, swUI16 pageId)
{
    wxTreeItemId id, dummy;
    SwTreeDataEx * tdata;

    if (!start.IsOk())
        id = GetRootItem();
    else
        id = start;

    if (!id.IsOk())
        return dummy;

    for(;;)
    {
        if (IsRoot(id))
        {
            id = GetNextItem(id);
            if (!id.IsOk())
                break;
        }

        tdata  = (SwTreeDataEx *) GetItemData(id);

        if (tdata && tdata->m_managerId == managerId && tdata->m_pageId == pageId)
            return id;

        id = GetNextItemInScope(start, id);

        if (!id.IsOk() || id.GetID() == start.GetID())
            break;
    }

    return dummy;
}

void SwModuleTreeCtrl::OnLanguageChange()
{
    wxTreeItemId root, child;
    wxTreeItemIdValue cookie;
    SwTreeDataEx * td;

    if (!GetCount())
        return;

    root = GetRootItem();

    child = GetFirstChild(root, cookie);

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(child);

        if (td && td->m_managerId < N_CATEGORIES)
        {
            SetItemText(child, SwApplicationInterface::GetControlString(SwCategory::GetId(td->m_managerId), SwCategory::GetStringW(td->m_managerId)));
        }

        child = GetNextChild(root, cookie);

        if (!child.IsOk())
            break;
    }
}

void SwModuleTreeCtrl::OnThemeChange()
{
    Refresh();
}

bool SwModuleTreeCtrl::HasModule(const char * bookId)
{
    if (!bookId)
        return false;

    swUI32 result = m_ids.Find(bookId);

    if (result != NODE_ID_INVALID)
        return true;

    return false;
}

const char * SwModuleTreeCtrl::GetBookId()
{
    if (m_ids.GetCount() == 0)
        return "";

    return m_ids.GetAt(0).GetArray();
}

bool SwModuleTreeCtrl::HasCategory(swUI8 category)
{
    if (m_categories.GetCount() == 0)
        return false;

    for(swUI32 i = 0; i < m_categories.GetCount(); i ++)
    {
        if (m_categories.GetAt(i) == category)
            return true;
    }

    return false;
}

swUI8 SwModuleTreeCtrl::GetCategory()
{
    if (m_categories.GetCount() == 0)
        return 0;

    return m_categories.GetAt(0);
}

void SwModuleTreeCtrl::LoadBooks()
{
    SwModule * module;

    for (swUI8 cat = 0; cat < m_categories.GetCount(); cat ++)
    {
        for (swUI16 cnt = 0; cnt < SwApplicationInterface::GetModuleManager().GetModules(); cnt ++)
        {
            module = SwApplicationInterface::GetModuleManager().GetAt(cnt);
            if (module->GetHeader().GetCategory() == m_categories.GetAt(cat))
            {
                BuildTree(module->GetTableofContents(), GetRootItem(), module->GetHeader().category, module->GetManagerId());
            }
        }
    }
}

void SwModuleTreeCtrl::LoadBooksForGroup(swUI8 group)
{
    Swui8Array categories;
    SwCategory::GetGroupList(group, categories);
    for(swUI8 i = 0; i < categories.GetCount(); i ++)
    {
        LoadBooks(categories[i]);
    }
}

void SwModuleTreeCtrl::LoadBooks(swUI8 cat)
{
    SwModule * module;

    for (swUI16 cnt = 0; cnt < SwApplicationInterface::GetModuleManager().GetModules(); cnt ++)
    {
        module = SwApplicationInterface::GetModuleManager().GetAt(cnt);
        if (module->GetHeader().GetCategory() == cat)
        {
            BuildTree(module->GetTableofContents(), GetRootItem(), module->GetHeader().category, module->GetManagerId());
        }
    }
}

// Categories can only be child of root.
wxTreeItemId SwModuleTreeCtrl::FindCategory(swUI8 category)
{
    wxTreeItemId root, child, dummy;
    wxTreeItemIdValue cookie;

    SwTreeDataEx * td;

    if (!GetCount())
        return dummy;

    root = GetRootItem();

    if (!root.IsOk())
        return dummy;

    child = GetFirstChild(root, cookie);

    if (!child.IsOk())
        return dummy;

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(child);

        if (td && td->m_managerId == category)
        {
            return child;
        }

        child = GetNextChild(root, cookie);

        if (!child.IsOk())
            break;
    }

    return dummy;
}

void SwModuleTreeCtrl::GetCategories(SwChoice * choice)
{
    wxTreeItemId item, root;
    wxTreeItemIdValue cookie;

    SwTreeDataEx * td;
    SwClientData * data;

    if (!GetCount())
        return;

    choice->Clear();

    root = GetRootItem();

    if (!root.IsOk())
        return;

    item = GetFirstChild(root, cookie);

    data = new SwClientData();
    data->m_data = CATEGORY_ALLTEXT;
    choice->Append(SwCategory::GetStringW(CATEGORY_ALLTEXT), SwCategory::GetId(CATEGORY_ALLTEXT), data);

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(item);

        if (td && td->m_managerId < MANAGER_ID_START - 1)
        {
            data = new SwClientData();
            data->m_data = td->m_managerId;
            choice->Append(SwCategory::GetStringW(td->m_managerId), SwCategory::GetId(td->m_managerId), data);
        }

        item = GetNextChild(root, cookie);

        if (!item.IsOk())
            break;
    }

    choice->SetSelection(0);
}

wxTreeItemId SwModuleTreeCtrl::CreateCategory(swUI8 category)
{
    wxTreeItemId id, dummy;
    SwTreeDataEx * td;

    id = FindCategory(category);

    if (id.IsOk())
        return id;

    id = GetRootItem();

    if (!id.IsOk())
    {
        id = AddRoot("", -1, -1, new SwTreeDataEx());
    }

    td = new SwTreeDataEx();
    td->m_managerId = category;

    id = AppendItem(id, SwCategory::GetStringW(category), SwApplicationInterface::GetBookImageIndex(category), -1, td);

    if (!id.IsOk())
        return dummy;

    SetItemImage(id, SwApplicationInterface::GetOpenBookImageIndex(category), wxTreeItemIcon_Expanded);

    return id;
}

// Groups can only be child of a category.
wxTreeItemId SwModuleTreeCtrl::FindGroup(swUI8 category, const wchar_t * group)
{
    wxTreeItemId child, start, dummy;
    wxTreeItemIdValue cookie;
    SwTreeDataEx * td;

    if (!GetCount())
        return dummy;

    start = FindCategory(category);

    if (!start.IsOk())
        return dummy;

    child = GetFirstChild(start, cookie);

    if (!child.IsOk())
        return dummy;

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(child);

        if (td && td->m_managerId == CATEGORY_GROUP && GetItemText(child).Cmp(group))
        {
            return child;
        }

        child = GetNextChild(start, cookie);

        if (!child.IsOk())
            break;
    }

    return dummy;
}

wxTreeItemId SwModuleTreeCtrl::CreateGroup(swUI8 category, const wchar_t * group)
{
    wxTreeItemId id, dummy;
    SwTreeDataEx * td;

    id = FindCategory(category);

    if (!id.IsOk())
        id = CreateCategory(category);

    if (!id.IsOk())
        return dummy;

    td = new SwTreeDataEx();
    td->m_managerId = CATEGORY_GROUP;

    id = AppendItem(id, group, SwApplicationInterface::GetBookImageIndex(category), SwApplicationInterface::GetBookImageIndex(category), td);

    if (!id.IsOk())
        return dummy;

    SetItemImage(id, SwApplicationInterface::GetOpenBookImageIndex(category), wxTreeItemIcon_Expanded);

    return id;
}
