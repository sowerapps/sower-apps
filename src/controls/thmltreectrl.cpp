///////////////////////////////////////////////////////////////////
// Name:        thmltreectrl.cpp
// Purpose:     A tree control that can read the structure of a
//              ThML file, display the table of contents in the tree,
//              and retrieve the contents of a division with
//              css inlined, and notes processed. And perform
//              searches.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/controls/thmltreectrl.h"
#include "../../include/filesys/file.h"
#include "../../include/appi/appifa.h"
#include "../../include/thml/thml_utility.h"
#include "../../include/module/category.h"

IMPLEMENT_DYNAMIC_CLASS(SwThMLTreeCtrl, SwTreeCtrl)

SwThMLTreeCtrl::SwThMLTreeCtrl()
    :SwTreeCtrl()
{
    SetSowerImageList();
}

SwThMLTreeCtrl::SwThMLTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwTreeCtrl(parent, id, pos, size, style, validator, name)
{
    SetSowerImageList();
}

SwThMLTreeCtrl::~SwThMLTreeCtrl()
{
}

void SwThMLTreeCtrl::Reset()
{
    DeleteAllItems();
    m_history.Reset();
    m_ids.Reset();
    m_categories.Reset();
    AddRoot("", -1, -1, new SwTreeDataEx());
}

bool SwThMLTreeCtrl::Open(const char * path)
{
    if (!path)
        return false;

    if (!SwFile::DoesExist(path))
        return false;

    SwThMLFile * thmlfile;

    swUI16 id = SwApplicationInterface::GetThMLFileManager().FindByPath(path);
    if (id != NODE_ID_INVALID_16)
    {
        thmlfile = SwApplicationInterface::GetThMLFileManager().GetAt(id);

        if (!thmlfile)
            return false;
    }
    else
    {
        thmlfile = new SwThMLFile();
        if (!thmlfile->Open(path))
        {
            delete thmlfile;
            return false;
        }

        id = SwApplicationInterface::GetThMLFileManager().Add(thmlfile);
        if (id == NODE_ID_INVALID_16)
        {
            delete thmlfile;
            return false;
        }
    }

    return BuildTree(thmlfile->m_contents, GetRootItem(), thmlfile->GetCategory(), thmlfile->GetManagerId());
}

bool SwThMLTreeCtrl::BuildTree(SwThMLTableOfContents & toc, wxTreeItemId parent, swUI8 category, swUI16 managerId)
{
    swUI32 pos = 0;
    SwTreeAppendData appendData;
    SwString buffer;
    appendData.id = parent;
    swUI16 node = SwApplicationInterface::GetThMLFileManager().FindByMID(managerId);
    buffer = SwApplicationInterface::GetThMLFileManager().GetAt(node)->GetTitle();
    appendData.depth = 0;

    m_ids.Add(SwApplicationInterface::GetThMLFileManager().GetAt(node)->GetPath());

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

    appendData.id = AppendItemEx(buffer, appendData, SwApplicationInterface::GetBookImageIndex(category), SwApplicationInterface::GetOpenBookImageIndex(category), 2, new SwTreeDataEx(managerId, NODE_ID_INVALID_16));

    appendData.depth = 0;

    while (pos < toc.GetNodes())
    {
        if (!toc.GetTitle(pos, buffer))
            return false;

        if (toc.GetNode(pos)->hasChildren)
            AppendItemEx(buffer, appendData, SwApplicationInterface::GetBookImageIndex(category), SwApplicationInterface::GetOpenBookImageIndex(category), toc.GetNode(pos)->divDepth + 1, new SwTreeDataEx(managerId, pos));
        else
            AppendItemEx(buffer, appendData, SwApplicationInterface::GetPageImageIndex(category), -1, toc.GetNode(pos)->divDepth + 1, new SwTreeDataEx(managerId, pos));

        pos ++;
    }

    return true;
}

bool SwThMLTreeCtrl::VerifyId(SwTreeDataEx * td)
{
    if (!td || td->m_managerId < FILEMANAGER_ID_START || td->m_managerId == NODE_ID_INVALID_16 || td->m_pageId == NODE_ID_INVALID_16)
        return false;

    return true;
}

bool SwThMLTreeCtrl::ReadDivText(SwTreeDataEx * td, SwString & buffer)
{
    if (!VerifyId(td))
        return false;

    SwPageData pg;
    pg.m_managerId = td->m_managerId;
    pg.m_pageId = td->m_pageId;

    return SwApplicationInterface::GetThMLFileManager().LoadPage(pg, buffer);
}

bool SwThMLTreeCtrl::Load(SwString & buffer, wxTreeItemId id)
{
    SwTreeDataEx * td;

    td = (SwTreeDataEx *) GetItemData(id);

    if (!VerifyId(td))
        return false;

    SwPageData pd;
    pd.m_managerId = td->m_managerId;
    pd.m_pageId = td->m_pageId;

    return SwApplicationInterface::GetThMLFileManager().LoadPage(pd, buffer);
}

void SwThMLTreeCtrl::Search(SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId)
{
    wxTreeItemId next, dummy;
    SwTreeDataEx * td;
    swUI8 lch;
    wxListItem lItem;
    SwPageData pg;
    SwThMLFile * file;
    SwString buffer1, buffer2;
    SwStringW wbuffer1, wbuffer2;

    if (!GetCount())
        return;

    buffer1.Size(4096);
    buffer2.Size(4096);
    wbuffer1.Size(4096);
    wbuffer2.Size(200);

    next = GetRootItem();

    for(;;)
    {
        td = (SwTreeDataEx *) GetItemData(next);

        if (td && td->m_managerId >= FILEMANAGER_ID_START && td->m_pageId != NODE_ID_INVALID_16)
        {
            lch = LCH_BREAK;
            pg.m_managerId = td->m_managerId;
            pg.m_pageId = td->m_pageId;
            file = SwApplicationInterface::GetThMLFileManager().GetFromMID(td->m_managerId);
            SwApplicationInterface::GetThMLFileManager().LoadPage(pg, buffer1);
            buffer2.Size(buffer1.Strlen() + 1);
            SwHtml::Html2Text(buffer1, buffer2, buffer2.GetSize(), lch, true);
            wbuffer1.Copy(buffer2);

            if (strcmpObj.SearchBuffer(wbuffer1) == CR_EXPRESSION_PASSED)
            {
                if (addId)
                {
                    wbuffer1.Copy(file->GetAbbreviation());
                    wbuffer1 += L" ";
                    file->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                    wbuffer2.Copy(buffer1);
                    wbuffer1 += wbuffer2;
                }
                else
                {
                    file->GetTableofContents().GetTitle(td->m_pageId, buffer1);
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

void SwThMLTreeCtrl::Search(swUI16 managerId, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId)
{
    wxTreeItemId next, dummy, parent;
    wxTreeItemIdValue cookie;
    SwTreeDataEx * td;
    swUI8 lch;
    wxListItem lItem;
    SwPageData pg;
    SwThMLFile * file;
    SwString buffer1, buffer2;
    SwStringW wbuffer1, wbuffer2;

    if (!GetCount())
        return;

    buffer1.Size(4096);
    buffer2.Size(4096);
    wbuffer1.Size(4096);
    wbuffer2.Size(200);

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
            file = SwApplicationInterface::GetThMLFileManager().GetFromMID(td->m_managerId);
            SwApplicationInterface::GetThMLFileManager().LoadPage(pg, buffer1);
            buffer2.Size(buffer1.Strlen() + 1);
            SwHtml::Html2Text(buffer1, buffer2, buffer2.GetSize(), lch, true);
            wbuffer1.Copy(buffer2);

            if (strcmpObj.SearchBuffer(wbuffer1) == CR_EXPRESSION_PASSED)
            {
                if (addId)
                {
                    wbuffer1.Copy(file->GetAbbreviation());
                    wbuffer1 += L" ";
                    file->GetTableofContents().GetTitle(td->m_pageId, buffer1);
                    wbuffer2.Copy(buffer1);
                    wbuffer1 += wbuffer2;
                }
                else
                {
                    file->GetTableofContents().GetTitle(td->m_pageId, buffer1);
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

void SwThMLTreeCtrl::Search(wxTreeItemId & start, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl)
{
    wxTreeItemId next;
    SwTreeDataEx * td;
    swUI8 lch;
    wxListItem lItem;
    SwPageData pg;
    SwThMLFile * file;
    SwString buffer1, buffer2;
    SwStringW wbuffer1, wbuffer2;

    if (!GetCount())
        return;

    buffer1.Size(4096);
    buffer2.Size(4096);
    wbuffer1.Size(4096);
    wbuffer2.Size(200);

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

        if (td && td->m_managerId >= FILEMANAGER_ID_START && td->m_pageId != NODE_ID_INVALID_16)
        {
            lch = LCH_BREAK;
            pg.m_managerId = td->m_managerId;
            pg.m_pageId = td->m_pageId;
            file = SwApplicationInterface::GetThMLFileManager().GetAt(td->m_managerId);
            SwApplicationInterface::GetThMLFileManager().LoadPage(pg, buffer1);
            buffer2.Size(buffer1.Strlen() + 1);
            SwHtml::Html2Text(buffer1, buffer2, buffer2.GetSize(), lch, true);
            wbuffer1.Copy(buffer2);

            if (strcmpObj.SearchBuffer(wbuffer1) == CR_EXPRESSION_PASSED)
            {
                wbuffer1.Copy(file->GetAbbreviation());
                wbuffer1 += L" ";
                file->GetTableofContents().GetTitle(td->m_pageId, buffer1);
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

wxTreeItemId SwThMLTreeCtrl::Search(wxTreeItemId& start, swUI16 managerId, swUI16 pageId)
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

wxTreeItemId SwThMLTreeCtrl::SearchId(const char * id, swUI16 managerId)
{
    wxTreeItemId next, dummy;
    SwTreeDataEx * td;
    wxString s;

    if (!id)
        return dummy;

    next = GetRootItem();

    if (!next.IsOk())
        return dummy;

    for(;;)
    {
        if (IsRoot(next))
        {
            next = GetNextItem(next, false);
            if (!next.IsOk())
                break;
        }

        td = (SwTreeDataEx *) GetItemData(next);

        if (td && td->m_managerId == managerId)
        {
            SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetFromMID(td->m_managerId);

            if (f && strcmp(id, f->GetTableofContents().GetIdText(td->m_pageId)) == 0)
                return next;
        }

        next = GetNextItem(next, false);

        if (!next.IsOk())
            break;
    }

    return dummy;
}

void SwThMLTreeCtrl::OnLanguageChange()
{
}

void SwThMLTreeCtrl::OnThemeChange()
{
    Refresh();
}
bool SwThMLTreeCtrl::HasFile(const char * bookId)
{
    if (!bookId)
        return false;

    swUI32 result = m_ids.Find(bookId);

    if (result != NODE_ID_INVALID)
        return true;

    return false;
}

const char * SwThMLTreeCtrl::GetBookId()
{
    if (m_ids.GetCount() == 0)
        return "";

    return m_ids.GetAt(0).GetArray();
}

bool SwThMLTreeCtrl::HasCategory(swUI8 category)
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

swUI8 SwThMLTreeCtrl::GetCategory()
{
    if (m_categories.GetCount() == 0)
        return 0;

    return m_categories.GetAt(0);
}

void SwThMLTreeCtrl::LoadBooks()
{
    SwThMLFile * file;

    for (swUI8 cat = 0; cat < m_categories.GetCount(); cat ++)
    {
        for (swUI16 cnt = 0; cnt < SwApplicationInterface::GetThMLFileManager().GetFileCount(); cnt ++)
        {
            file = SwApplicationInterface::GetThMLFileManager().GetAt(cnt);
            if (file->GetCategory() == m_categories.GetAt(cat))
            {
                BuildTree(file->GetTableofContents(), GetRootItem(), file->GetCategory(), file->GetManagerId());
            }
        }
    }
}

void SwThMLTreeCtrl::LoadBooksForGroup(swUI8 group)
{
    Swui8Array categories;
    SwCategory::GetGroupList(group, categories);
    for(swUI8 i = 0; i < categories.GetCount(); i ++)
    {
        LoadBooks(categories.GetAt(i));
    }
}

void SwThMLTreeCtrl::LoadBooks(swUI8 cat)
{
    SwThMLFile * file;

    for (swUI16 cnt = 0; cnt < SwApplicationInterface::GetThMLFileManager().GetFileCount(); cnt ++)
    {
        file = SwApplicationInterface::GetThMLFileManager().GetAt(cnt);
        if (file->GetCategory() == cat)
        {
            BuildTree(file->GetTableofContents(), GetRootItem(), file->GetCategory(), file->GetManagerId());
        }
    }
}

void SwThMLTreeCtrl::Close()
{
    Reset();
}
