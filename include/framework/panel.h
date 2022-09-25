///////////////////////////////////////////////////////////////////
// Name:        panel.h
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERPANEL_H
#define SOWERPANEL_H

#include "../sowerbase.h"
#include "menubar.h"
#include "toolbar.h"
#include "toolbook.h"
#include "../controls/treectrlext.h"
#include "../controls/controls.h"

#include <wx/panel.h>
#include <wx/sashwin.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/wrapsizer.h>

class SwMenuBar;
class SwToolBar;

class SOWERBASEEXP SwPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS(SwPanel)

public:
    SwPanel();
    SwPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwPanel();

    // File
    virtual bool OnNew();
    virtual bool OnOpen();
    virtual bool OnRecentFiles();
    virtual bool OnSave();
    virtual bool OnSaveAs();
    virtual bool OnClose();
    virtual bool OnCloseAll();
    //

    // Print
    virtual bool OnPrint();
    virtual bool OnPrintPreview();
    //

    // Recent Files
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
    //

    // Bookmarks
    virtual bool OnBookMarkPage();
    //

    // Find, Replace
    virtual bool OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnFindReset();
    virtual bool OnFindSetCaseSensitive(bool caseSensitive);
    virtual bool OnFindSetWholeWordOnly(bool wholewordOnly);
    virtual bool OnFindNext();
    virtual bool OnReplace();
    virtual bool OnReplaceAll();
    //

    // Edit
    virtual bool OnClear();
    virtual bool OnCut();
    virtual bool OnCopy();
    virtual bool OnPaste();
    virtual bool OnUndo();
    virtual bool OnRedo();
    virtual bool OnSelectAll();
    virtual bool OnProperties();
    //

    // Views
    virtual bool OnLibraryView();
    virtual bool OnContentsView();
    virtual bool OnSearchView();
    virtual bool OnFindView();
    virtual bool OnBookmarksView();
    virtual bool OnHistoryView();
    //

    // Zoom
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();
    //

    // Navigation
    virtual bool OnContentsUp();
    virtual bool OnContentsDown();
    virtual bool OnHistoryBack();
    virtual bool OnHistoryForward();
    //

    // Format
    virtual bool OnFont();
    virtual bool OnBold();
    virtual bool OnItalic();
    virtual bool OnUnderline();
    virtual bool OnStrikeThrough();
    virtual bool OnSuperScript();
    virtual bool OnSubScript();
    virtual bool OnColor();
    virtual bool OnBackgroundColor();
    virtual bool OnStyle();
    //

    // Paragraph
    virtual bool OnMargins();
    virtual bool OnIndentMore();
    virtual bool OnIndentLess();
    virtual bool OnAlignLeft();
    virtual bool OnAlignCenter();
    virtual bool OnAlignRight();
    virtual bool OnSingleSpacing();
    virtual bool OnDoubleSpacing();
    //

    // Lists
    virtual bool OnAlphaList();
    virtual bool OnBulletedList();
    virtual bool OnRomanList();
    virtual bool OnDecimalList();
    //

    // Table
    virtual bool OnInsertTable();
    virtual bool OnInsertRow();
    virtual bool OnDeleteRow();
    virtual bool OnInsertColumn();
    virtual bool OnDeleteColumn();
    //

    // Objects
    virtual bool OnInsertImage();
    virtual bool OnInsertLink();
    virtual bool OnInsertAnchor();
    virtual bool OnInsertControl();
    virtual bool OnInsertHorizontalRule();
    //

    // Players
    virtual bool OnPlay();
    virtual bool OnPause();
    virtual bool OnStop();
    virtual bool OnRewind();
    virtual bool OnFastForward();
    virtual bool OnPrevious();
    virtual bool OnNext();
    //

    // System
    virtual bool OnPreferences();
    virtual bool OnHelpContents();
    virtual bool OnAbout();
    void NotifyChildren(bool change);
    void NotifyChildren(wxWindow * window, bool change);
    virtual bool OnUpdateSoftware();
    void OnLanguageChangeBase();
    void OnThemeChangeBase();
    virtual void OnLanguageChange() {}
    virtual void OnThemeChange() {}
    virtual void OnFontSizeChange(const wxFont & font);
    virtual void OnResize(wxSizeEvent& event);
    virtual bool OnHasFocus();
    bool HasChildWithFocus(wxWindow * window);
    virtual bool OnHasSelection();
    virtual bool OnClosePanel();

    virtual void OnModuleManagerReset() {}
    virtual void OnThMLFileManagerReset() {}
    virtual void OnModuleManagerLoaded() {}
    virtual void OnThMLFileManagerLoaded() {}
    virtual void OnModuleAdded(swUI16 mid) {}
    virtual void OnModuleDeleted(swUI16 mid) {}
    virtual void OnThMLFileAdded(swUI16 mid) {}
    virtual void OnThMLFileDeleted(swUI16 mid) {}
    //

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
    virtual void UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar);
    virtual bool GetBookMarkData(SwString & title, SwBookMarkClientData & data);
    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual bool ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual bool LoadLibraryItem(const char * path) { return false; }
    virtual bool LoadLibraryItem(swUI16 managerId) { return false; }
    virtual void UpdateLabel(SwToolBook * toolbook, size_t page_idx) {}
    virtual const char * GetFilePath() { return NULL; }
    virtual const char * GetBookId() { return NULL; }
    virtual bool HasFile(const char * path) { return false; }
    virtual bool HasModule(const char * bookId) { return false; }
    virtual bool OpenFile(const char * path) { return false; }
    virtual bool WriteGuiData(FILE * file);
    wxAuiManager * GetAuiManager() { return m_manager; }

protected:
    wxAuiManager * m_manager;
};

class SOWERBASEEXP SwPanelList
{
public:
    SwPanelList();
    virtual ~SwPanelList();

    swUI32 AddPanel(SwPanel * panel);
    void DeletePanel(swUI32 position);
    void Reset();
    swUI32 SwFindPanel(SwPanel * panel);
    swUI32 FindFocusPanel();
    SwPanel * GetPanel(swUI32 position);
    void SetPanel(swUI32 position, SwPanel * panel);
    void OnLanguageChangeBase();
    void OnThemeChangeBase();
    void OnFontSizeChange();
    void OnModuleManagerReset();
    void OnThMLFileManagerReset();
    void OnModuleManagerLoaded();
    void OnThMLFileManagerLoaded();
    void OnModuleAdded(swUI16 mid);
    void OnModuleDeleted(swUI16 mid);
    void OnThMLFileAdded(swUI16 mid);
    void OnThMLFileDeleted(swUI16 mid);
    swUI32 GetCount() { return m_panelarrayPos; }

protected:
    swUI32 AssignPanelObject();
    bool IncreasePanelArray();
    void ReleasePanelArray();
    SwPanel ** m_panelArray;
    swUI32 m_panelarrayPos;
    swUI32 m_panelobjectsAllocated;
};

class SOWERBASEEXP SwStretchPanel : public SwPanel
{
public:
    SwStretchPanel();
    SwStretchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwStretchPanel();

    virtual void OnResize(wxSizeEvent& event);
};

#endif // SOWERPANEL_H
