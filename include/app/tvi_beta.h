///////////////////////////////////////////////////////////////////
// Name:        tvi_beta.h
// Purpose:     Beta interface plugin for ThML Viewer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef TVI_BETA_H
#define TVI_BETA_H

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

class TVI_BetaPanel: public SwGuiPanel
{
public:
    TVI_BetaPanel();
    TVI_BetaPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~TVI_BetaPanel();

    virtual void OnThMLFileManagerReset();
    virtual void OnThMLFileManagerLoaded();

    virtual bool OnOpen();
    bool OnCanDoOpen() { return true; }
    virtual void SaveUserData();

    virtual bool OnFile1();
    virtual bool OnFile2();
    virtual bool OnFile3();
    virtual bool OnFile4();
    virtual bool OnFile5();
    virtual bool OnFile6();
    virtual bool OnFile7();
    virtual bool OnFile8();
    virtual bool OnFile9();
    virtual bool OnFile10();

    virtual bool HasLibraryView() { return true; }
    virtual bool HasBookmarksView() { return true; }
    virtual bool OnLibraryView();
    virtual bool OnBookmarksView();
    virtual bool OnBookMarkPage();
    virtual void OnDelete(wxCommandEvent & event);
    virtual void OnBookmarkActivated(wxListEvent& event);
    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    void OpenRecent(swUI8 pos);
    virtual bool OpenFile(const char * path, bool addtorecent = false);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar);
    virtual void OnRightClick(wxCommandEvent & event);
    virtual bool LoadPerspective(const char * id, const char * perspective);
    static const long ID_BOOKMARKSLIST;
    static const long ID_BOOKPANEL;

protected:
    SwBookmarksListCtrl * m_bookmarksList;
    SwMultiFileThMLBookPanel * m_bookpanel;
    SwMenu * m_listMenu;
    SwStandardViewMenu * m_viewMenu;
    bool m_startup;
};

#endif // SWI_BETA_H
