///////////////////////////////////////////////////////////////////
// Name:        bookmarkslistctrl.h
// Purpose:     List control for bookmarks.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef BOOKMARKSLISTCTRL_H
#define BOOKMARKSLISTCTRL_H

#include "../controls/controls.h"
#include "../framework/frame.h"

class SOWERBASEEXP SwBookmarksListCtrl : public SwListCtrl
{
public:
    SwBookmarksListCtrl();
    SwBookmarksListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_ICON, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);

    virtual ~SwBookmarksListCtrl();

    void Init();
    void ReadFromTable();
    void OnResize(wxSizeEvent& event);
    SwMenu * GetMenu()
    {
        return listMenu;
    }

protected:
    SwMenu * listMenu;
};

class SOWERBASEEXP SwHelpBookmarksListCtrl : public SwStretchColumnListCtrl
{
public:
    SwHelpBookmarksListCtrl();
    SwHelpBookmarksListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_ICON, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);

    virtual ~SwHelpBookmarksListCtrl();

    void Init();
    void ReadFromTable();
    SwMenu * GetMenu()
    {
        return listMenu;
    }

protected:
    SwMenu * listMenu;
};

#endif // BOOKMARKSLISTCTRL_H
