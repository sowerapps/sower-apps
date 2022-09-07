///////////////////////////////////////////////////////////////////
// Name:        sowerhelpapp.h
// Purpose:     Sower Help
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERHELPAPP_H
#define SOWERHELPAPP_H

#include "framework/frame.h"
#include "framework/toolbar.h"
#include "framework/menubar.h"
#include "framework/guipanel.h"
#include "framework/bookpanels.h"
#include "controls/bookmarkslistctrl.h"

class SowerHelpApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerHelpFrame : public SwFrame
{
public:
    SowerHelpFrame() {}
    SowerHelpFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SowerHelpFrame();

    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnQuit(wxCommandEvent & event);

    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnTimer();

    virtual void OnBookmark(wxCommandEvent & event);
    virtual void OnDelete(wxCommandEvent & event);
    virtual void OnBookmarkActivated(wxListEvent& event);
    virtual void OnRightClick(wxCommandEvent & event);

    virtual void ProcessCmdLine();

    static const long ID_TOOLBAR;
    static const long ID_BOOKMARKSLIST;
    bool m_showBookmarks;
    SwHelpBookmarksListCtrl * m_bookmarksList;
    SwMenu * m_listMenu;
    SwStandardViewMenu * m_viewMenu;
    SwModuleBookPanel * m_bookPanel;
};

#endif // SOWERHELPAPP_H
