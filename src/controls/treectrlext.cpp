///////////////////////////////////////////////////////////////////
// Name:        treectrlext.h
// Purpose:     An extension to wxTreeCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/controls/treectrlext.h"
#include "../../include/string/string.h"
#include "../../include/appi/appifa.h"

SwTreeData::SwTreeData()
{
    m_data = 0;
}

SwTreeData::SwTreeData(wxUint32 data)
{
    m_data = data;
}

SwTreeData::~SwTreeData()
{
}

void SwTreeData::SetData(wxUint32 data)
{
    m_data = data;
}

wxUint32 SwTreeData::GetData()
{
    return m_data;
}

IMPLEMENT_DYNAMIC_CLASS(SwTreeCtrl, wxTreeCtrl)

SwTreeCtrl::SwTreeCtrl()
    :wxTreeCtrl()
{
    SetBackgroundColour(*wxWHITE);
    m_history.Reset();
}

SwTreeCtrl::SwTreeCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxTreeCtrl(parent, id, pos, size, wxTR_HAS_BUTTONS|wxTR_SINGLE|wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT, validator, name)
{
    SetBackgroundColour(*wxWHITE);
    m_history.Reset();
}

SwTreeCtrl::~SwTreeCtrl()
{
}

void SwTreeCtrl::Reset()
{
    DeleteAllItems();
    m_history.Reset();
    AddRoot("", -1, -1, new SwTreeData());
}

bool SwTreeCtrl::IsRoot(wxTreeItemId id)
{
    wxTreeItemId root = GetRootItem();

    if (!root.IsOk())
        return false;

    if (id == root)
        return true;

    return false;
}

void SwTreeCtrl::SetSowerImageList()
{
    SetImageList(&SwApplicationInterface::GetImageList());
}

void SwTreeCtrl::SelectFirst()
{
    wxTreeItemIdValue cookie;

    if (!GetCount())
        return;

    wxTreeItemId id = GetRootItem();

    if (!id.IsOk())
        return;

    id = GetFirstChild(id, cookie);

    if (id.IsOk())
        SelectItem(id, true);
}

void SwTreeCtrl::SelectNext()
{
    wxTreeItemIdValue cookie;

    if (!GetCount())
        return;

    wxTreeItemId id = GetSelection(), next;

    if (!id.IsOk())
        return;

    next =  GetNextItem(id, true);

    if (!next.IsOk())
        return;

    if (IsRoot(next))
    {
        next = GetFirstChild(next, cookie);

        if (!next.IsOk())
            return;
    }

    SelectItem(next, true);
}

void SwTreeCtrl::SelectPrevious()
{
    if (!GetCount())
        return;

    wxTreeItemId id = GetSelection();
    wxTreeItemId id2;

    if (!id.IsOk())
        return;

// Root item, which should not happen because SwTreeCtrl hides root.
    if (IsRoot(id))
    {
        id = GetLastChild(id);

        for (;;)
        {
            id2 = GetLastChild(id);

            if (id2.IsOk())
                id = id2;
            else
                break;
        }

        if (id.IsOk())
            SelectItem(id);

        return;
    }


    id = GetPrevItem(id);

    if (!id.IsOk())
        return;

// Root item, should not be shown. Go to last item in tree.
    if (IsRoot(id))
    {
        for (;;)
        {
            id2 = GetLastChild(id);
            if (id2.IsOk())
                id = id2;
            else
                break;
        }

        if (!id.IsOk())
            return;
    }

    SelectItem(id, true);
}

wxTreeItemId SwTreeCtrl::Search(wxTreeItemId& start, wxUint32 data)
{
    wxTreeItemId id, dummy;
    SwTreeData * tdata;

    if (IsRoot(start))
        id = start;
    else if (!start.IsOk())
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

        tdata  = (SwTreeData *) GetItemData(id);

        if (tdata && tdata->GetData() == data)
            return id;

        id = GetNextItem(id);

        if (!id.IsOk() || id.GetID() == start.GetID())
            break;
    }

    return dummy;
}

wxTreeItemId SwTreeCtrl::Search(wxTreeItemId& start, const char * text, bool casesensitive)
{
    wxTreeItemId id, dummy;
    wxString s;

    if (!text)
        return dummy;

    if (IsRoot(start))
        id = start;
    else if (!start.IsOk())
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

        s = GetItemText(id);

        if (s.IsSameAs(text, casesensitive))
            return id;

        id = GetNextItem(id);

        if (!id.IsOk() || id.GetID() == start.GetID())
            break;
    }

    return dummy;
}

wxTreeItemId SwTreeCtrl::Search(wxTreeItemId& start, const wchar_t * text, bool caseSensitive)
{
    wxTreeItemId id, dummy;
    wxString s;

    if (!text)
        return dummy;

    if (IsRoot(start))
        id = start;
    else if (!start.IsOk())
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

        s = GetItemText(id);

        if (s.IsSameAs(text, caseSensitive))
            return id;

        id = GetNextItem(id);

        if (!id.IsOk() || id.GetID() == start.GetID())
            break;
    }

    return dummy;
}

wxTreeItemId SwTreeCtrl::GetNextItem(const wxTreeItemId& item, bool loop)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId nextA = item, nextB, nextC, dummy;

    if (!nextA.IsOk())
        return dummy;

    nextB = GetFirstChild(nextA, cookie);

    if (nextB.IsOk())
        return nextB;

    nextB = GetNextSibling(nextA);

    if (nextB.IsOk())
        return nextB;

    nextB = nextA;

    for (;;)
    {
        nextB = GetItemParent(nextB);

        if (nextB.IsOk() && IsRoot(nextB))
            break;

        if (nextB.IsOk())
        {
            nextC = GetNextSibling(nextB);
            if (nextC.IsOk())
                return nextC;
        }
        else
            break;
    }

    if (loop)
    {
        nextB = GetRootItem();

        if (!nextB.IsOk())
            return dummy;

        nextB = GetFirstChild(nextB, cookie);
        if (nextB.IsOk())
            return nextB;
    }

    return dummy;
}

// Iterates only items with in item, but includes all siblings and their children.
// Will not iterate root.
/*
root-folder1-subfolder1-child1
             subfolder2-child1
     folder2-child1

next = folder1
next = GetNextInScope(root, next);

returns :
folder1
subfolder1
subfolder1-child1
subfolder2
subfolder2-child1

breaks before folder2.
*/
wxTreeItemId SwTreeCtrl::GetNextItemInScope(const wxTreeItemId& parent, const wxTreeItemId& item)
{
    wxTreeItemIdValue cookie;
    wxTreeItemId nextA = item, nextB, nextC, dummy;

    if (!nextA.IsOk())
        return GetFirstChild(parent, cookie);
    else
    {
        nextA = GetNextItem(item, false);

        if (!nextA.IsOk())
            return dummy;

        nextB = nextA;
        for(;;)
        {
            nextB = GetItemParent(nextB);

            if (!nextB.IsOk())
                break;

            if (nextB.IsOk() && nextB == parent)
                return nextA;
        }
    }

    return dummy;
}

// Finds the previous item in the tree.
wxTreeItemId SwTreeCtrl::GetPrevItem(const wxTreeItemId& item)
{
    wxTreeItemId nextA, nextB, dummy;

    nextA = item;

    if (nextA.IsOk())
    {
        if (nextA == GetRootItem())
        {
            nextA = GetLastChild(GetRootItem());

            if (!nextA.IsOk())
                return dummy;

            for (;;)
            {
                nextB = GetLastChild(nextA);

                if (nextB.IsOk())
                    nextA = nextB;
                else
                    break;
            }

            return nextA;
        }

        nextB = GetPrevSibling(nextA);

        if (nextB.IsOk())
        {
            for (;;)
            {
                nextA = GetLastChild(nextB);

                if (nextA.IsOk())
                    nextB = nextA;
                else
                    return nextB;
            }
        }

        nextB = GetItemParent(nextA);

        if (nextB.IsOk())
            return nextB;
    }

    return dummy;
}

wxTreeItemId SwTreeCtrl::AppendItemEx(const char * text, SwTreeAppendData & appendData, int image, int stateImage, wxUint8 mode, wxTreeItemData *data)
{
    wxTreeItemId id;

    if (!text)
        return id;

    SwStringW buffer;
    buffer.Copy(text);

    id = GetRootItem();
    if (!id.IsOk())
        return id;

    if (mode == AP_ASROOT)
    {
        // Do nothing, tree roots are hidden.
    }
    else if (mode == AP_ROOTCHILD)
    {
        if (id.IsOk())
            id = AppendItem(id, buffer.GetArray(), image, -1, data);
    }
    else if (mode == appendData.depth)
    {
        id = GetItemParent(appendData.id);

        if (id.IsOk())
            id = AppendItem(id, buffer.GetArray(), image, -1, data);
    }
    else if (mode > appendData.depth)
    {
        id = AppendItem(appendData.id, buffer.GetArray(), image, -1, data);
    }
    else if (mode < appendData.depth)
    {
        wxUint8 pos = appendData.depth;
        id = appendData.id;

        if (id.IsOk())
        {
            while (pos >= mode)
            {
                id = GetItemParent(id);

                if (!id.IsOk())
                    break;
                pos --;
            }

            if (id.IsOk())
                id = AppendItem(id, buffer.GetArray(), image, -1, data);
        }
    }

    if (!id.IsOk())
        return id;

    if (stateImage != -1)
        SetItemImage(id, stateImage, wxTreeItemIcon_Expanded);

    appendData.id = id;
    appendData.depth = mode;

    return id;
}
