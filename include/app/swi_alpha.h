///////////////////////////////////////////////////////////////////
// Name:        swi_alpha.h
// Purpose:     Alpha interface plugin for Sower.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SWI_ALPHA_H
#define SWI_ALPHA_H

#include "sowerbase.h"
#include "plugin/plugin.h"
#include "framework/guipanel.h"
#include "framework/bookpanels.h"
#include "framework/librarypanels.h"
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

class SWI_AlphaPanel: public SwGuiPanel
{
public:
    SWI_AlphaPanel();
    SWI_AlphaPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SWI_AlphaPanel();

    virtual bool OnClose();
    virtual bool OnCloseAll();
    virtual bool OnCanDoCloseAll();
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
    virtual bool LoadLibraryItem(swUI16 managerId);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar);
    virtual void OnRightClick(wxCommandEvent & event);
    virtual bool LoadPerspective(const char * id, const char * perspective);
    static const long ID_NOTEBOOK;
    static const long ID_BOOKMARKSLIST;
    static const long ID_LIBRARYPANEL;

protected:
    SwBookmarksListCtrl * m_bookmarksList;
    SwModuleLibraryPanel * m_libraryPanel;
    SwMenu * m_listMenu;
    SwStandardViewMenu * m_viewMenu;
    bool m_startup;
};

#endif // SWI_ALPHA_H
