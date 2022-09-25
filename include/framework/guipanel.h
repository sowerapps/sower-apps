///////////////////////////////////////////////////////////////////
// Name:        guipanel.h
// Purpose:     Primary panel in which to build user interfaces
//              for Sower applications.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERGUIPANEL_H
#define SOWERGUIPANEL_H

#include "../sowerbase.h"
#include "../module/modulebase.h"
#include "panel.h"
#include "toolbook.h"
#include "menubar.h"
#include "toolbar.h"
#include <wx/aui/framemanager.h>

class SwToolBook;
class SwPanel;
class SwToolBar;
class SwMenuBar;

class SOWERBASEEXP SwGuiPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS(SwGuiPanel)

public:
    SwGuiPanel();
    SwGuiPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SwGuiPanel();

    virtual void Init();

    virtual bool OnUnknown() { return false; }

    // File
    virtual bool OnOpen();
    virtual bool OnClose();
    virtual bool OnCloseAll();
    virtual bool OnSave();
    virtual bool OnSaveAs();
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

    // Print
    virtual bool OnPrint();
    virtual bool OnPrintPreview();
    //

    // Edit
    virtual bool OnClear();
    virtual bool OnNew();
    virtual bool OnCut();
    virtual bool OnCopy();
    virtual bool OnPaste();
    virtual bool OnUndo();
    virtual bool OnRedo();
    virtual bool OnSelectAll();
    virtual bool OnAlignLeft();
    virtual bool OnAlignCenter();
    virtual bool OnAlignRight();
    virtual bool OnBold();
    virtual bool OnItalic();
    virtual bool OnUnderline();
    virtual bool OnStrikeThrough();
    virtual bool OnSuperScript();
    virtual bool OnSubScript();
    virtual bool OnIndentMore();
    virtual bool OnIndentLess();
    virtual bool OnSingleSpacing();
    virtual bool OnDoubleSpacing();
    virtual bool OnMargins();
    virtual bool OnBookMarkPage();
    virtual bool OnFont();
    virtual bool OnColor();
    virtual bool OnBackgroundColor();
    virtual bool OnStyle();
    virtual bool OnInsertImage();
    virtual bool OnInsertLink();
    virtual bool OnInsertAnchor();
    virtual bool OnInsertTable();
    virtual bool OnInsertRow();
    virtual bool OnInsertColumn();
    virtual bool OnDeleteRow();
    virtual bool OnDeleteColumn();
    virtual bool OnInsertControl();
    virtual bool OnInsertHorizontalRule();
    virtual bool OnAlphaList();
    virtual bool OnBulletedList();
    virtual bool OnRomanList();
    virtual bool OnDecimalList();
    virtual bool OnProperties();
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

    // Find, Replace
    virtual bool OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnFindReset();
    virtual bool OnFindNext();
    virtual bool OnReplace();
    virtual bool OnReplaceAll();
    //

    // Views
    virtual bool OnLibraryView();
    virtual bool OnContentsView();
    virtual bool OnSearchView();
    virtual bool OnFindView();
    virtual bool OnBookmarksView();
    virtual bool OnHistoryView();
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

    // Software
    virtual bool OnPreferences();
    virtual bool OnHelpContents();
    virtual bool OnAbout();
    virtual bool OnUpdateSoftware();
    //

    // System
    void NotifyChildren(bool change);
    void NotifyChildren(wxWindow * window, bool change);
    void OnLanguageChangeBase();
    void OnThemeChangeBase();
    virtual void OnLanguageChange() {}
    virtual void OnThemeChange() {}
    virtual void OnFontSizeChange(const wxFont & font);
    virtual bool OnHasSelection();
    virtual void OnModuleManagerReset();
    virtual void OnThMLFileManagerReset();
    virtual void OnModuleManagerLoaded();
    virtual void OnThMLFileManagerLoaded();
    virtual void OnModuleAdded(swUI16 mid);
    virtual void OnModuleDeleted(swUI16 mid);
    virtual void OnThMLFileAdded(swUI16 mid);
    virtual void OnThMLFileDeleted(swUI16 mid);
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

    SwToolBook * GetToolBook()
    {
        return m_librarybook;
    }

    void SetToolBook(SwToolBook * toolbook)
    {
        m_librarybook = toolbook;
    }

    SwPanel * GetPanel()
    {
        return m_librarypanel;
    }

    void SetPanel(SwPanel * panel)
    {
        m_librarypanel = panel;
    }

    wxAuiManager * GetAuiManager() { return m_manager; }

    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual bool ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    virtual bool LoadLibraryItem(const char * path);
    virtual bool LoadLibraryItem(swUI16 managerId);
    virtual bool SelectTab(const char * path);
    virtual bool OnHasFocus();
    bool HasChildWithFocus(wxWindow * window);
    virtual void UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar);
    virtual void SaveUserData() {}
    virtual bool OpenFile(const char * path, bool addtorecent = false) { return false; }
    virtual bool LoadPerspective(const char * id, const char * perspective) { return false; }
    virtual bool SetOption(const char * id, const char * value) { return false; }
    void CreateStartUpFile(const char * name);
    void DeleteStartUpFile(const char * name);
    bool CheckStartUpFile(const char * name);

protected:
    SwPanel *      m_librarypanel;
    SwToolBook *   m_librarybook;
    wxAuiManager * m_manager;
};

#endif // SOWERGUIPANEL_H
