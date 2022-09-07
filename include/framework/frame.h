///////////////////////////////////////////////////////////////////
// Name:        frame.h
// Purpose:     SowerBase provides a simple gui application
//              frame work to ease the creation of Sower applications.
//              This includes SwFrame, SwMenuBar, SwToolBar,
//              SwPanel, and SwDialog. SwFrame, SwPanel,
//              and SwDialog register/unregister themselves with
//              SwApplicationInterface and receive notification of language, theme,
//              and interface font size changes.
//              OnLanguageChange is triggered by LanguageDlg.
//              OnThemeChange is triggered by ThemeDlg.
//              OnFontSize is triggered by SwApplicationInterface::SetInterfaceFontSize.
//              There should be only one SwFrame per an application.
//              SwMenuBar, and SwToolBar receive notifications only if
//              they belong to the application frame window. And should not be
//              used in SwPanels, SowerViewPanels, or SwDialogs.
//              SwFrame has a number of virtual functions which tool bars, and
//              menu bars can call when a corresponding item has sent a notification.
//              SwBasicToolBar, SwUtilityToolBar, SwBasicMenuBar, and
//              SwUtilityMenuBar maybe sufficient for most applications.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERFRAME_H
#define SOWERFRAME_H

#include "../sowerbase.h"
#include "toolbar.h"
#include "menubar.h"
#include "guipanel.h"
#include "toolbook.h"
#include <wx/frame.h>
#include <wx/aui/framemanager.h>
#include <wx/timer.h>

#define FRAME_STR "frame"
#define GUIPANEL_STR "guipanel"
#define LIBRARYBOOK_STR "book1"
#define TOOLBOOK_STR "book2"

class SwFrame;
class SOWERBASEEXP SwFrameTimer : public wxTimer
{
public:
    SwFrameTimer();
    virtual ~SwFrameTimer();
    virtual void Notify();
    SwFrame * m_frame;
};

class SwMenuBar;
class SwToolBar;
class SwToolBook;
class SwGuiPanel;

class SOWERBASEEXP SwFrame : public wxFrame
{
    DECLARE_DYNAMIC_CLASS(SwFrame)

public:
    SwFrame();
    SwFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SwFrame();

    void Init();

    virtual void OnUnknown(wxCommandEvent & event) {}

    void OnPaneClosed(wxAuiManagerEvent& evt);
    void ToolAdded();
    void ToolRemoved();

    // File
    virtual void OnOpen(wxCommandEvent & event);
    virtual void OnClose(wxCommandEvent & event);
    virtual void OnCloseAll(wxCommandEvent & event);
    virtual void OnSave(wxCommandEvent & event);
    virtual void OnSaveAs(wxCommandEvent & event);
    //

    // Recent Files
    virtual void OnFile1(wxCommandEvent & event);
    virtual void OnFile2(wxCommandEvent & event);
    virtual void OnFile3(wxCommandEvent & event);
    virtual void OnFile4(wxCommandEvent & event);
    virtual void OnFile5(wxCommandEvent & event);
    virtual void OnFile6(wxCommandEvent & event);
    virtual void OnFile7(wxCommandEvent & event);
    virtual void OnFile8(wxCommandEvent & event);
    virtual void OnFile9(wxCommandEvent & event);
    virtual void OnFile10(wxCommandEvent & event);
    //

    // Print
    virtual void OnPrint(wxCommandEvent & event);
    virtual void OnPrintPreview(wxCommandEvent & event);
    //

    // Edit
    virtual void OnClear(wxCommandEvent & event);
    virtual void OnNew(wxCommandEvent & event);
    virtual void OnCut(wxCommandEvent & event);
    virtual void OnCopy(wxCommandEvent & event);
    virtual void OnPaste(wxCommandEvent & event);
    virtual void OnUndo(wxCommandEvent & event);
    virtual void OnRedo(wxCommandEvent & event);
    virtual void OnSelectAll(wxCommandEvent & event);
    virtual void OnAlignLeft(wxCommandEvent & event);
    virtual void OnAlignCenter(wxCommandEvent & event);
    virtual void OnAlignRight(wxCommandEvent & event);
    virtual void OnBold(wxCommandEvent & event);
    virtual void OnItalic(wxCommandEvent & event);
    virtual void OnUnderline(wxCommandEvent & event);
    virtual void OnStrikeThrough(wxCommandEvent & event);
    virtual void OnSuperScript(wxCommandEvent & event);
    virtual void OnSubScript(wxCommandEvent & event);
    virtual void OnIndentMore(wxCommandEvent & event);
    virtual void OnIndentLess(wxCommandEvent & event);
    virtual void OnSingleSpacing(wxCommandEvent & event);
    virtual void OnDoubleSpacing(wxCommandEvent & event);
    virtual void OnMargins(wxCommandEvent & event);
    virtual void OnBookmark(wxCommandEvent & event);
    virtual void OnFont(wxCommandEvent & event);
    virtual void OnColor(wxCommandEvent & event);
    virtual void OnBackgroundColor(wxCommandEvent & event);
    virtual void OnStyle(wxCommandEvent & event);
    virtual void OnInsertImage(wxCommandEvent & event);
    virtual void OnInsertLink(wxCommandEvent & event);
    virtual void OnInsertAnchor(wxCommandEvent & event);
    virtual void OnInsertTable(wxCommandEvent & event);
    virtual void OnInsertRow(wxCommandEvent & event);
    virtual void OnInsertColumn(wxCommandEvent & event);
    virtual void OnDeleteRow(wxCommandEvent & event);
    virtual void OnDeleteColumn(wxCommandEvent & event);
    virtual void OnInsertControl(wxCommandEvent & event);
    virtual void OnInsertHorizontalRule(wxCommandEvent & event);
    virtual void OnAlphaList(wxCommandEvent & event);
    virtual void OnBulletedList(wxCommandEvent & event);
    virtual void OnRomanList(wxCommandEvent & event);
    virtual void OnDecimalList(wxCommandEvent & event);
    virtual void OnGeo(wxCommandEvent & event);
    virtual void OnMaps(wxCommandEvent & event);
    virtual void OnAreas(wxCommandEvent & event);
    virtual void OnProperties(wxCommandEvent & event);
    //

    // Zoom
    virtual void OnZoomIn(wxCommandEvent & event);
    virtual void OnZoomOut(wxCommandEvent & event);
    virtual void OnViewNormal(wxCommandEvent & event);
    //

    // Navigation
    virtual void OnContentsUp(wxCommandEvent & event);
    virtual void OnContentsDown(wxCommandEvent & event);
    virtual void OnHistoryBack(wxCommandEvent & event);
    virtual void OnHistoryForward(wxCommandEvent & event);
    //

    // Find, Replace
    virtual void OnFind(wxCommandEvent & event);
    virtual void OnFindReset(wxCommandEvent & event);
    virtual void OnFindNext(wxCommandEvent & event);
    virtual void OnReplace(wxCommandEvent & event);
    virtual void OnReplaceAll(wxCommandEvent & event);
    //

    // Views
    virtual void OnLibraryView(wxCommandEvent & event);
    virtual void OnContentsView(wxCommandEvent & event);
    virtual void OnSearchView(wxCommandEvent & event);
    virtual void OnFindView(wxCommandEvent & event);
    virtual void OnBookmarksView(wxCommandEvent & event);
    virtual void OnHistoryView(wxCommandEvent & event);
    //

    // Players
    virtual void OnPlay(wxCommandEvent & event);
    virtual void OnPause(wxCommandEvent & event);
    virtual void OnStop(wxCommandEvent & event);
    virtual void OnRewind(wxCommandEvent & event);
    virtual void OnFastForward(wxCommandEvent & event);
    virtual void OnPrevious(wxCommandEvent & event);
    virtual void OnNext(wxCommandEvent & event);
    //

    // Software
    virtual void OnPreferences(wxCommandEvent & event);
    virtual void OnHelpContents(wxCommandEvent & event);
    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnUpdateSoftware(wxCommandEvent & event);
    virtual void OnConfiguration(wxCommandEvent & event);
    //

    // System
    virtual void OnSelectInterface(wxCommandEvent & event) {}
    virtual void OnSelectLanguage(wxCommandEvent & event) {}
    virtual void OnSelectTheme(wxCommandEvent & event) {}
    void NotifyChildren(bool change);
    void NotifyChildren(wxWindow * window, bool change);
    void OnLanguageChangeBase();
    void OnThemeChangeBase();
    virtual void OnLanguageChange() {}
    virtual void OnThemeChange() {}
    virtual void OnFontSizeChange();
    virtual bool OnHasSelection();
    virtual void OnResize(wxSizeEvent& event);
    virtual void OnQuit(wxCommandEvent & event);
    //

    virtual void OnDelete(wxCommandEvent & event) {}

    virtual bool OnCanDoNew();
    virtual bool OnCanDoOpen();
    virtual bool OnCanDoSave();
    virtual bool OnCanDoSaveAs();
    virtual bool OnCanDoClose();
    virtual bool OnCanDoCloseAll();
    virtual bool OnCanDoPrint();
    virtual bool OnCanDoPrintPreview();
    virtual bool OnCanDoBookMarkPage();
    virtual bool OnCanDoFind();
    virtual bool OnCanDoFindNext();
    virtual bool OnCanDoReplace();
    virtual bool OnCanDoClear();
    virtual bool OnCanDoCut();
    virtual bool OnCanDoCopy();
    virtual bool OnCanDoPaste();
    virtual bool OnCanDoUndo();
    virtual bool OnCanDoRedo();
    virtual bool OnCanDoSelectAll();
    virtual bool OnCanDoGeo() { return false; }
    virtual bool OnCanDoMaps() { return false; }
    virtual bool OnCanDoAreas() { return false; }
    virtual bool OnCanDoProperties();
    virtual bool HasLibraryView();
    virtual bool HasContentsView();
    virtual bool HasBookmarksView();
    virtual bool HasFindView();
    virtual bool HasSearchView();
    virtual bool HasHistoryView();
    virtual bool OnCanDoZoomIn();
    virtual bool OnCanDoZoomOut();
    virtual bool OnCanDoViewNormal();
    virtual bool OnCanDoUpInContents();
    virtual bool OnCanDoDownInContents();
    virtual bool OnCanDoBackInHistory();
    virtual bool OnCanDoForwardInHistory();
    virtual bool OnCanDoFont();
    virtual bool OnCanDoBold();
    virtual bool IsSelectionBold();
    virtual bool OnCanDoItalic();
    virtual bool IsSelectionItalic();
    virtual bool OnCanDoUnderline();
    virtual bool IsSelectionUnderline();
    virtual bool OnCanDoStrikeThrough();
    virtual bool IsSelectionStrikeThrough();
    virtual bool OnCanDoSuperScript();
    virtual bool IsSelectionSuperScript();
    virtual bool OnCanDoSubScript();
    virtual bool IsSelectionSubScript();
    virtual bool OnCanDoColor();
    virtual bool OnCanDoBackGroundColor();
    virtual bool OnCanDoStyle();
    virtual bool OnCanDoMargins();
    virtual bool OnCanDoIndentMore();
    virtual bool OnCanDoIndentLess();
    virtual bool OnCanDoAlignLeft();
    virtual bool IsSelectionAlignLeft();
    virtual bool OnCanDoAlignCenter();
    virtual bool IsSelectionAlignCenter();
    virtual bool OnCanDoAlignRight();
    virtual bool IsSelectionAlignRight();
    virtual bool OnCanDoSingleSpacing();
    virtual bool IsSelectionSingleSpacing();
    virtual bool OnCanDoDoubleSpacing();
    virtual bool IsSelectionDoubleSpacing();
    virtual bool OnCanDoAlphaList();
    virtual bool IsSelectionAlphaList();
    virtual bool OnCanDoBulletedList();
    virtual bool IsSelectionBulletedList();
    virtual bool OnCanDoRomanNumeralsList();
    virtual bool IsSelectionRomanNumeralsList();
    virtual bool OnCanDoDecimalList();
    virtual bool IsSelectionDecimalList();
    virtual bool OnCanDoInsertTable();
    virtual bool OnCanDoInsertRow();
    virtual bool OnCanDoDeleteRow();
    virtual bool OnCanDoInsertColumn();
    virtual bool OnCanDoDeleteColumn();
    virtual bool OnCanDoInsertImage();
    virtual bool OnCanDoInsertLink();
    virtual bool OnCanDoInsertAnchor();
    virtual bool OnCanDoInsertControl();
    virtual bool OnCanDoInsertHorizontalRule();
    virtual bool OnCanDoPlay();
    virtual bool OnCanDoPause();
    virtual bool OnCanDoStop();
    virtual bool OnCanDoRewind();
    virtual bool OnCanDoFastForward();
    virtual bool OnCanDoPrevious();
    virtual bool OnCanDoNext();

    SwToolBar * GetSowerToolBar()
    {
        return m_toolbar;
    }

    void SetSowerToolBar(SwToolBar * toolbar)
    {
        m_toolbar = toolbar;
    }

    SwMenuBar * GetSowerMenuBar()
    {
        return m_menubar;
    }

    void SetSowerMenuBar(SwMenuBar * menubar)
    {
        m_menubar = menubar;
    }

    SwGuiPanel * GetGuiPanel()
    {
        return m_guipanel;
    }

    void SetGuiPanel(SwGuiPanel * guipanel)
    {
        m_guipanel = guipanel;
    }

    SwToolBook * GetToolBook()
    {
        return m_toolbook;
    }

    void SetToolBook(SwToolBook * toolbook)
    {
        m_toolbook = toolbook;
    }

    wxAuiManager * GetAuiManager() { return m_manager; }


    virtual void OnModuleManagerReset();
    virtual void OnThMLFileManagerReset();
    virtual void OnModuleManagerLoaded();
    virtual void OnThMLFileManagerLoaded();
    virtual void OnModuleAdded(swUI16 mid);
    virtual void OnModuleDeleted(swUI16 mid);
    virtual void OnThMLFileAdded(swUI16 mid);
    virtual void OnThMLFileDeleted(swUI16 mid);

    virtual void ProcessCmdLine() {}
    SwStringArray & GetCmdArray() { return m_cmd; }
    virtual void OnTimer();
    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual bool ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual bool LoadLibraryItem(const char * path);
    virtual bool LoadLibraryItem(swUI16 managerId);
    virtual bool SelectTab(const char * path);
    virtual bool LoadPerspective(const char * id, const char * perspective) { return false; }
    virtual bool SetOption(const char * id, const char * value) { return false; }
    swUI16 GetInitialInterfacePlugIn();

    static const long ID_TOOLBOOK;
    SwStringArray   m_fileList;
    wxAuiManager *  m_manager;

protected:
    SwToolBar *     m_toolbar;
    SwMenuBar *     m_menubar;
    SwGuiPanel *    m_guipanel;
    SwToolBook *    m_toolbook;
    SwFrameTimer    m_frameTimer;
    SwStringArray   m_cmd;
};

#endif // SOWERFRAME_H
