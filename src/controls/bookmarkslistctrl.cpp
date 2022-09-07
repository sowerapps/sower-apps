///////////////////////////////////////////////////////////////////
// Name:        bookmarkslistctrl.cpp
// Purpose:     List control for bookmarks.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/controls/bookmarkslistctrl.h"

void SizeColumn(wxListCtrl * listCtrl)
{
    int h, w;
    wxListItem item;
    if (listCtrl->GetColumnCount() < 2)
        return;
    listCtrl->GetClientSize(&w, &h);
    listCtrl->GetColumn(1, item);
    w -= item.GetWidth();
    item.Clear();
    listCtrl->GetColumn(0, item);
    item.SetWidth(w);
    listCtrl->SetColumn(0, item);
}

SwBookmarksListCtrl::SwBookmarksListCtrl()
{
    Init();
}

SwBookmarksListCtrl::SwBookmarksListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwListCtrl(parent, id, pos, size, style | wxLC_SINGLE_SEL | wxLC_EDIT_LABELS, validator, name)
{
    Init();
    SizeColumn(this);
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwBookmarksListCtrl::OnResize);
    Connect(id, wxEVT_LIST_COL_END_DRAG,(wxObjectEventFunction)&SwBookmarksListCtrl::OnResize);
}

void SwBookmarksListCtrl::Init()
{
    AppendColumn("SID_NOTE", "Note", wxLIST_FORMAT_LEFT, 1000);
    AppendColumn("SID_TITLE", "Title", wxLIST_FORMAT_LEFT, 200);
    wxArrayInt order(2);order[0] = 1;order[1] = 0;

    #if defined __MSWIN__
    SetColumnsOrder(order);
    #endif // defined __MSWIN__
}

void SwBookmarksListCtrl::ReadFromTable()
{
    SwApplicationInterface::GetBookMarkList(this);
}

void SwBookmarksListCtrl::OnResize(wxSizeEvent& event)
{
    SizeColumn(this);
    event.Skip();
}

SwBookmarksListCtrl::~SwBookmarksListCtrl()
{
}

SwHelpBookmarksListCtrl::SwHelpBookmarksListCtrl()
{
    Init();
}

SwHelpBookmarksListCtrl::SwHelpBookmarksListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwStretchColumnListCtrl(parent, id, pos, size, style | wxLC_SINGLE_SEL | wxLC_EDIT_LABELS, validator, name)
{
    Init();
}

void SwHelpBookmarksListCtrl::Init()
{
    wxListCtrl::AppendColumn("", wxLIST_FORMAT_LEFT, 200);
}

void SwHelpBookmarksListCtrl::ReadFromTable()
{
    SwApplicationInterface::GetHelpBookMarkList(this);
}

SwHelpBookmarksListCtrl::~SwHelpBookmarksListCtrl()
{
}
