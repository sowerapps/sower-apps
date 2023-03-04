///////////////////////////////////////////////////////////////////
// Name:        swi_beta.h
// Purpose:     Beta interface plugin for Sower.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SWI_BETA_H
#define SWI_BETA_H

#include "sowerbase.h"
#include "plugin/plugin.h"
#include "framework/guipanel.h"
#include "framework/bookpanels.h"
#include "controls/bookmarkslistctrl.h"
#include "controls/librarylistctrl.h"

#if defined __MSWIN__
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif
#else
    #define DLL_EXPORT
#endif // defined


#ifdef __cplusplus
extern "C"
{
#endif

SwPlugIn * DLL_EXPORT PlugInInitialize();

#ifdef __cplusplus
}
#endif

class InterfacePlugIn: public SwPlugIn
{
public:
    InterfacePlugIn();
    virtual ~InterfacePlugIn();

    virtual swUI8 GetVersion();
    virtual swUI8 GetType();
    virtual const char * GetName();
    virtual const char * GetDescription();
    virtual void OnInitialize();
    static swUI32 m_count;
};

class SWI_BetaPanel: public SwGuiPanel
{
public:
    SWI_BetaPanel();
    SWI_BetaPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SWI_BetaPanel();

    virtual bool OnCanDoClose();
    virtual bool OnCanDoCloseAll();
    virtual bool OnClose();
    virtual bool OnCloseAll();
    virtual void SaveUserData();
    virtual bool HasLibraryView() { return true; }
    virtual bool HasBookmarksView() { return true; }
    virtual bool OnLibraryView();
    virtual bool OnBookmarksView();
    virtual bool OnBookMarkPage();
    virtual void OnDelete(wxCommandEvent & event);
    virtual void OnBookmarkActivated(wxListEvent& event);
    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar);
    virtual void OnRightClick(wxCommandEvent & event);
    virtual bool LoadPerspective(const char * id, const char * perspective);
    static const long ID_BOOKMARKSLIST;
    static const long ID_BOOKPANEL;

protected:
    SwBookmarksListCtrl * m_bookmarksList;
    SwMultiModuleBookPanel * m_bookpanel;
    SwMenu * m_listMenu;
    SwStandardViewMenu * m_viewMenu;
};

#endif // SWI_BETA_H
