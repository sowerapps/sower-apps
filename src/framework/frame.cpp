///////////////////////////////////////////////////////////////////
// Name:        frame.cpp
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/frame.h"
#include "../../include/appi/appifa.h"
#include "../../include/framework/viewbook.h"
#include "../../include/controls/moduletreectrl.h"
#include "../../include/controls/thmltreectrl.h"
#include "../../include/richtext/richtextctrlext.h"
#include "../../include/dialogs/configurationdlg.h"
#include <wx/utils.h>

SwFrameTimer::SwFrameTimer()
{
    m_frame = NULL;
    Start(100);
}

SwFrameTimer::~SwFrameTimer()
{
}

void SwFrameTimer::Notify()
{
    if (m_frame)
        m_frame->OnTimer();
}

IMPLEMENT_DYNAMIC_CLASS(SwFrame, wxFrame)

const long SwFrame::ID_TOOLBOOK = wxNewId();

SwFrame::SwFrame()
{
    Init();
}

SwFrame::SwFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxFrame(parent, id, title, pos, size, style, name)
{
    Init();
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwFrame::OnResize);
}

SwFrame::~SwFrame()
{
    SwApplicationInterface::SetFrameWindow(NULL);
    m_manager->UnInit();
}

void SwFrame::Init()
{
    m_toolbar = NULL;
    m_menubar = NULL;
    m_guipanel = NULL;
    m_toolbook = NULL;
    SwApplicationInterface::SetFrameWindow(this);
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    m_frameTimer.m_frame = this;
    m_toolbook = new SwToolBook(this, ID_TOOLBOOK, wxPoint(232,160), wxDefaultSize, wxAUI_NB_WINDOWLIST_BUTTON|wxAUI_NB_CLOSE_ON_ACTIVE_TAB|wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT, L"ID_TOOLBOOK");
    m_manager->AddPane(m_toolbook, wxAuiPaneInfo().Name(L"ToolBookCtrl").Bottom().Caption(L"").Hide().CloseButton(false).MinSize(wxSize(-1, 100)));
    m_manager->Update();

    Connect(ID_TOOLBOOK, wxEVT_AUINOTEBOOK_PAGE_CLOSED,(wxObjectEventFunction)&SwFrame::OnPaneClosed);
}

void SwFrame::OnPaneClosed(wxAuiManagerEvent& evt)
{
    if (!m_toolbook)
        return;

    if (!m_toolbook->GetPageCount())
    {
        m_manager->GetPane(m_toolbook).Hide();
        m_manager->Update();
    }
}

void SwFrame::ToolAdded()
{
    if (!m_toolbook)
        return;

    if (m_toolbook->GetPageCount() && !m_manager->GetPane(m_toolbook).IsShown())
    {
        m_manager->GetPane(m_toolbook).Show();
        m_manager->Update();
    }
}

void SwFrame::ToolRemoved()
{
    if (!m_toolbook)
        return;

    if (m_toolbook->GetPageCount() == 0)
    {
        m_manager->GetPane(m_toolbook).Show(false);
        m_manager->Update();
    }
}

void SwFrame::OnOpen(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnOpen();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnOpen();
    else if (m_toolbook)
        m_toolbook->OnOpen();
}

void SwFrame::OnClose(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
    {
         m_toolbook->OnClose();
         ToolRemoved();
    }
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnClose();
    else if (m_toolbook)
    {
        m_toolbook->OnClose();
         ToolRemoved();
    }

}

void SwFrame::OnCloseAll(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
    {
        m_toolbook->OnCloseAll();
        ToolRemoved();
    }
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnCloseAll();
}

void SwFrame::OnSave(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSave();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSave();
}

void SwFrame::OnSaveAs(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSaveAs();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSaveAs();
}

void SwFrame::OnFile1(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile1();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile1();
    else if (m_toolbook)
        m_toolbook->OnFile1();
}

void SwFrame::OnFile2(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile2();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile2();
    else if (m_toolbook)
        m_toolbook->OnFile2();
}

void SwFrame::OnFile3(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile3();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile3();
    else if (m_toolbook)
        m_toolbook->OnFile3();
}

void SwFrame::OnFile4(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile4();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile4();
    else if (m_toolbook)
        m_toolbook->OnFile4();
}

void SwFrame::OnFile5(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile5();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile5();
    else if (m_toolbook)
        m_toolbook->OnFile5();
}

void SwFrame::OnFile6(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile6();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile6();
    else if (m_toolbook)
        m_toolbook->OnFile6();
}

void SwFrame::OnFile7(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile7();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile7();
    else if (m_toolbook)
        m_toolbook->OnFile7();
}

void SwFrame::OnFile8(wxCommandEvent & event)
{
   if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile8();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile8();
    else if (m_toolbook)
        m_toolbook->OnFile8();
}

void SwFrame::OnFile9(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile9();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile9();
    else if (m_toolbook)
        m_toolbook->OnFile9();
}

void SwFrame::OnFile10(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile10();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnFile10();
    else if (m_toolbook)
        m_toolbook->OnFile10();
}

void SwFrame::OnPrint(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPrint();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPrint();
}

void SwFrame::OnPrintPreview(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPrintPreview();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPrintPreview();
}

void SwFrame::OnClear(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnClear();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnClear();
}

void SwFrame::OnNew(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnNew();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnNew();
}

void SwFrame::OnCut(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnCut();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnCut();
}

void SwFrame::OnCopy(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnCopy();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnCopy();
}

void SwFrame::OnPaste(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPaste();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPaste();
}

void SwFrame::OnUndo(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnUndo();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnUndo();
}

void SwFrame::OnRedo(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnRedo();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnRedo();
}

void SwFrame::OnSelectAll(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSelectAll();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSelectAll();
}

void SwFrame::OnAlignLeft(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlignLeft();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlignLeft();
}

void SwFrame::OnAlignCenter(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlignCenter();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlignCenter();
}

void SwFrame::OnAlignRight(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlignRight();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlignRight();
}

void SwFrame::OnBold(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBold();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBold();
}

void SwFrame::OnItalic(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnItalic();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnItalic();
}

void SwFrame::OnUnderline(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnUnderline();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnUnderline();
}

void SwFrame::OnStrikeThrough(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnStrikeThrough();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnStrikeThrough();
}

void SwFrame::OnSuperScript(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSuperScript();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSuperScript();
}

void SwFrame::OnSubScript(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSubScript();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSubScript();
}

void SwFrame::OnIndentMore(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnIndentMore();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnIndentMore();
}

void SwFrame::OnIndentLess(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnIndentLess();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnIndentLess();
}

void SwFrame::OnSingleSpacing(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSingleSpacing();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSingleSpacing();
}

void SwFrame::OnDoubleSpacing(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDoubleSpacing();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDoubleSpacing();
}

void SwFrame::OnMargins(wxCommandEvent & event)
{
   if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnMargins();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnMargins();
}

void SwFrame::OnFont(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFont();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFont();
}

void SwFrame::OnColor(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnColor();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnColor();
}

void SwFrame::OnBackgroundColor(wxCommandEvent & event)
{
   if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBackgroundColor();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBackgroundColor();
}

void SwFrame::OnStyle(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnStyle();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnStyle();
}

void SwFrame::OnInsertImage(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertImage();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertImage();
}

void SwFrame::OnInsertLink(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertLink();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertLink();
}

void SwFrame::OnInsertAnchor(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertAnchor();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertAnchor();
}

void SwFrame::OnInsertTable(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertTable();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertTable();
}

void SwFrame::OnInsertRow(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertRow();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertRow();
}

void SwFrame::OnInsertColumn(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertColumn();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertColumn();
}

void SwFrame::OnDeleteRow(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDeleteRow();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDeleteRow();
}

void SwFrame::OnDeleteColumn(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDeleteColumn();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDeleteColumn();
}

void SwFrame::OnInsertControl(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertControl();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertControl();
}

void SwFrame::OnInsertHorizontalRule(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertHorizontalRule();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertHorizontalRule();
}

void SwFrame::OnAlphaList(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlphaList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlphaList();
}

void SwFrame::OnBulletedList(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBulletedList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBulletedList();
}

void SwFrame::OnRomanList(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnRomanList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnRomanList();
}

void SwFrame::OnDecimalList(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDecimalList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDecimalList();
}

void SwFrame::OnGeo(wxCommandEvent & event)
{
}

void SwFrame::OnMaps(wxCommandEvent & event)
{
}

void SwFrame::OnAreas(wxCommandEvent & event)
{
}

void SwFrame::OnProperties(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnProperties();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnProperties();
}

void SwFrame::OnZoomIn(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnZoomIn();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnZoomIn();
}

void SwFrame::OnZoomOut(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnZoomOut();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnZoomOut();
}

void SwFrame::OnViewNormal(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnViewNormal();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnViewNormal();
}

void SwFrame::OnContentsUp(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnContentsUp();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnContentsUp();
}

void SwFrame::OnContentsDown(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnContentsDown();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnContentsDown();
}

void SwFrame::OnHistoryBack(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnHistoryBack();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnHistoryBack();
}

void SwFrame::OnHistoryForward(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnHistoryForward();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnHistoryForward();
}

void SwFrame::OnBookmark(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBookMarkPage();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBookMarkPage();
}

void SwFrame::OnFind(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFind(L"", false, false);
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFind(L"", false, false);
}

void SwFrame::OnFindReset(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFindReset();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFindReset();
}

void SwFrame::OnFindNext(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFindNext();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFindNext();
}

void SwFrame::OnReplace(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnReplace();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnReplace();
}

void SwFrame::OnReplaceAll(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnReplaceAll();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnReplaceAll();
}

void SwFrame::OnLibraryView(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnLibraryView();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnLibraryView();
    else if (m_toolbook)
        m_toolbook->OnLibraryView();
}

void SwFrame::OnContentsView(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnContentsView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnContentsView();
}

void SwFrame::OnSearchView(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSearchView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSearchView();
}

void SwFrame::OnFindView(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFindView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFindView();
}

void SwFrame::OnBookmarksView(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBookmarksView();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnBookmarksView();
    else if (m_toolbook)
        m_toolbook->OnBookmarksView();
}

void SwFrame::OnHistoryView(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnHistoryView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnHistoryView();
}

void SwFrame::OnPlay(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPlay();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPlay();
}

void SwFrame::OnPause(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPause();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPause();
}

void SwFrame::OnStop(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnStop();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnStop();
}

void SwFrame::OnRewind(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnRewind();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnRewind();
}

void SwFrame::OnFastForward(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFastForward();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFastForward();
}

void SwFrame::OnPrevious(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPrevious();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPrevious();
}

void SwFrame::OnNext(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnNext();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnNext();
}

void SwFrame::OnPreferences(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPreferences();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnPreferences();
    else if (m_toolbook)
        m_toolbook->OnPreferences();
}

void SwFrame::OnHelpContents(wxCommandEvent & event)
{
    SwString path;
    path = SwApplicationInterface::GetAppDir();
    path += PATH_SEP;
    #if defined __MSWIN__
    path += "SwHelp.exe";
    #else
    path += "SwHelp";
    #endif
    wxExecute(path.GetArray());
}

void SwFrame::OnAbout(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAbout();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        m_guipanel->OnAbout();
    else if (m_toolbook)
        m_toolbook->OnAbout();
}

void SwFrame::OnUpdateSoftware(wxCommandEvent & event)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnUpdateSoftware();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnUpdateSoftware();
}

void SwFrame::OnConfiguration(wxCommandEvent & event)
{
    SwConfigurationDlg * dlg = new SwConfigurationDlg(SwApplicationInterface::GetFrameWindow());
    dlg->ShowModal();
    delete dlg;
}

void SwFrame::OnTimer()
{
    if (m_toolbar)
        m_toolbar->UpdateGui();

    if (m_menubar)
        m_menubar->UpdateGui();

    if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->UpdateGui(m_toolbar, m_menubar);
    else if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->UpdateGui(m_toolbar, m_menubar);
}

// false - language, true - theme
void SwFrame::NotifyChildren(bool change)
{
    for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
    {
        NotifyChildren(*it, change);
    }
}

void SwFrame::NotifyChildren(wxWindow * window, bool change)
{
    if (window->IsKindOf(CLASSINFO(SwModuleTreeCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwModuleTreeCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwModuleTreeCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwThMLTreeCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwThMLTreeCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwThMLTreeCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwButton)))
    {
        if (!change)
            wxDynamicCast(window, SwButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwBitmapButton)))
    {
        if (!change)
            wxDynamicCast(window, SwBitmapButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwBitmapButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwCheckBox)))
    {
        if (!change)
            wxDynamicCast(window, SwCheckBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwCheckBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListBox)))
    {
        if (!change)
            wxDynamicCast(window, SwListBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwCheckListBox)))
    {
        if (!change)
            wxDynamicCast(window, SwCheckListBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwCheckListBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwChoice)))
    {
        if (!change)
            wxDynamicCast(window, SwChoice)->OnLanguageChange();
        else
            wxDynamicCast(window, SwChoice)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwDataViewListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwDataViewListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwDataViewListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListView)))
    {
        if (!change)
            wxDynamicCast(window, SwListView)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListView)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRadioButton)))
    {
        if (!change)
            wxDynamicCast(window, SwRadioButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRadioButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRadioButton)))
    {
        if (!change)
            wxDynamicCast(window, SwRadioButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRadioButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStaticText)))
    {
        if (!change)
            wxDynamicCast(window, SwStaticText)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStaticText)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStretchColumnListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwStretchColumnListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStretchColumnListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStretchColumnListView)))
    {
        if (!change)
            wxDynamicCast(window, SwStretchColumnListView)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStretchColumnListView)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwViewPanel)))
    {
        if (!change)
            wxDynamicCast(window, SwViewPanel)->OnLanguageChange();
        else
            wxDynamicCast(window, SwViewPanel)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwToolBook)))
    {
        if (!change)
            wxDynamicCast(window, SwToolBook)->OnLanguageChange();
        else
            wxDynamicCast(window, SwToolBook)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRichTextCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwRichTextCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRichTextCtrl)->OnThemeChange();
    }
    // Do nothing, these receive notification from SwApplicationInterface
    else if (window->IsKindOf(CLASSINFO(SwFrame)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwPanel)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwDialog)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwToolBar)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwMenuBar)))
    {
    }
    //
    else
    {
        for ( wxWindowList::iterator it = window->GetChildren().begin(); it != window->GetChildren().end(); ++it )
        {
            NotifyChildren(*it, change);
        }
    }
}

void SwFrame::OnLanguageChangeBase()
{
    OnLanguageChange();
    NotifyChildren(false);
}

void SwFrame::OnThemeChangeBase()
{
    OnThemeChange();
    NotifyChildren(false);
}

void SwFrame::OnFontSizeChange()
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);

    SetFont(thisFont);
    SwMenuBar * menubar = (SwMenuBar *) GetMenuBar();
    if (menubar)
        menubar->SetFont(thisFont);
    if (m_toolbar)
        m_toolbar->SetFont(thisFont);
}

bool SwFrame::OnHasSelection()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnHasSelection();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnHasSelection();

    return false;
}

void SwFrame::OnResize(wxSizeEvent& event)
{
    event.Skip();
}

void SwFrame::OnQuit(wxCommandEvent & event)
{
    event.Skip();
}


bool SwFrame::OnCanDoNew()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoNew();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoNew();

    return false;
}

bool SwFrame::OnCanDoOpen()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoOpen();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        return m_guipanel->OnCanDoOpen();
    else if (m_toolbook)
        return m_toolbook->OnCanDoOpen();

    return false;
}

bool SwFrame::OnCanDoSave()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSave();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSave();

    return false;
}

bool SwFrame::OnCanDoSaveAs()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSaveAs();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSaveAs();

    return false;
}

bool SwFrame::OnCanDoClose()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoClose();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoClose();

    return false;
}

bool SwFrame::OnCanDoCloseAll()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoCloseAll();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoCloseAll();

    return false;
}

bool SwFrame::OnCanDoPrint()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPrint();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPrint();

    return false;
}

bool SwFrame::OnCanDoPrintPreview()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPrintPreview();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPrintPreview();

    return false;
}

bool SwFrame::OnCanDoBookMarkPage()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBookMarkPage();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBookMarkPage();

    return false;
}

bool SwFrame::OnCanDoFind()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFind();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFind();

    return false;
}

bool SwFrame::OnCanDoFindNext()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFindNext();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFindNext();

    return false;
}

bool SwFrame::OnCanDoReplace()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoReplace();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoReplace();

    return false;
}


bool SwFrame::OnCanDoClear()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoClear();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoClear();

    return false;
}

bool SwFrame::OnCanDoCut()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoCut();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoCut();

    return false;
}

bool SwFrame::OnCanDoCopy()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoCopy();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoCopy();

    return false;
}

bool SwFrame::OnCanDoPaste()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPaste();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPaste();

    return false;
}

bool SwFrame::OnCanDoUndo()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoUndo();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoUndo();

    return false;
}

bool SwFrame::OnCanDoRedo()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoRedo();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoRedo();

    return false;
}

bool SwFrame::OnCanDoSelectAll()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSelectAll();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSelectAll();

    return false;
}

bool SwFrame::OnCanDoProperties()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoProperties();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoProperties();

    return false;
}

bool SwFrame::HasLibraryView()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasLibraryView();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        return m_guipanel->HasLibraryView();
    else if (m_toolbook)
        return m_toolbook->HasLibraryView();

    return false;
}

bool SwFrame::HasContentsView()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasContentsView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasContentsView();

    return false;
}

bool SwFrame::HasBookmarksView()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasBookmarksView();
    else if (m_guipanel/* && m_guipanel->OnHasFocus()*/)
        return m_guipanel->HasBookmarksView();
    else if (m_toolbook)
        return m_toolbook->HasBookmarksView();

    return false;
}

bool SwFrame::HasFindView()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasFindView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasFindView();

    return false;
}

bool SwFrame::HasSearchView()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasSearchView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasSearchView();

    return false;
}

bool SwFrame::HasHistoryView()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasHistoryView();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasHistoryView();

    return false;
}

bool SwFrame::OnCanDoZoomIn()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoZoomIn();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoZoomIn();

    return false;
}

bool SwFrame::OnCanDoZoomOut()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoZoomOut();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoZoomOut();

    return false;
}

bool SwFrame::OnCanDoViewNormal()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoViewNormal();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoViewNormal();

    return false;
}

bool SwFrame::OnCanDoUpInContents()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoUpInContents();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoUpInContents();

    return false;
}

bool SwFrame::OnCanDoDownInContents()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDownInContents();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDownInContents();

    return false;
}

bool SwFrame::OnCanDoBackInHistory()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBackInHistory();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBackInHistory();

    return false;
}

bool SwFrame::OnCanDoForwardInHistory()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoForwardInHistory();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoForwardInHistory();

    return false;
}

bool SwFrame::OnCanDoFont()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFont();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFont();

    return false;
}

bool SwFrame::OnCanDoBold()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBold();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBold();

    return false;
}

bool SwFrame::IsSelectionBold()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionBold();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionBold();
    return false;
}

bool SwFrame::OnCanDoItalic()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoItalic();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoItalic();

    return false;
}

bool SwFrame::IsSelectionItalic()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionItalic();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionItalic();

    return false;
}

bool SwFrame::OnCanDoUnderline()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoUnderline();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoUnderline();

    return false;
}

bool SwFrame::IsSelectionUnderline()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionUnderline();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionUnderline();

    return false;
}

bool SwFrame::OnCanDoStrikeThrough()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoStrikeThrough();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoStrikeThrough();

    return false;
}

bool SwFrame::IsSelectionStrikeThrough()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionStrikeThrough();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionStrikeThrough();

    return false;
}

bool SwFrame::OnCanDoSuperScript()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSuperScript();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSuperScript();

    return false;
}

bool SwFrame::IsSelectionSuperScript()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionSuperScript();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionSuperScript();

    return false;
}

bool SwFrame::OnCanDoSubScript()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSubScript();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSubScript();

    return false;
}

bool SwFrame::IsSelectionSubScript()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionSubScript();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionSubScript();

    return false;
}

bool SwFrame::OnCanDoColor()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoColor();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoColor();

    return false;
}

bool SwFrame::OnCanDoBackGroundColor()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBackGroundColor();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBackGroundColor();

    return false;
}

bool SwFrame::OnCanDoStyle()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoStyle();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoStyle();

    return false;
}

bool SwFrame::OnCanDoMargins()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoMargins();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoMargins();

    return false;
}

bool SwFrame::OnCanDoIndentMore()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoIndentMore();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoIndentMore();

    return false;
}

bool SwFrame::OnCanDoIndentLess()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoIndentLess();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoIndentLess();

    return false;
}

bool SwFrame::OnCanDoAlignLeft()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlignLeft();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlignLeft();

    return false;
}

bool SwFrame::IsSelectionAlignLeft()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlignLeft();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlignLeft();

    return false;
}

bool SwFrame::OnCanDoAlignCenter()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlignCenter();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlignCenter();

    return false;
}

bool SwFrame::IsSelectionAlignCenter()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlignCenter();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlignCenter();

    return false;
}

bool SwFrame::OnCanDoAlignRight()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlignRight();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlignRight();

    return false;
}

bool SwFrame::IsSelectionAlignRight()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlignRight();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlignRight();

    return false;
}

bool SwFrame::OnCanDoSingleSpacing()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSingleSpacing();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSingleSpacing();

    return false;
}

bool SwFrame::IsSelectionSingleSpacing()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionSingleSpacing();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionSingleSpacing();

    return false;
}

bool SwFrame::OnCanDoDoubleSpacing()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDoubleSpacing();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDoubleSpacing();

    return false;
}

bool SwFrame::IsSelectionDoubleSpacing()
{
   if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionDoubleSpacing();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionDoubleSpacing();

    return false;
}

bool SwFrame::OnCanDoAlphaList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlphaList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlphaList();

    return false;
}

bool SwFrame::IsSelectionAlphaList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlphaList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlphaList();

    return false;
}

bool SwFrame::OnCanDoBulletedList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBulletedList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBulletedList();

    return false;
}

bool SwFrame::IsSelectionBulletedList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionBulletedList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionBulletedList();

    return false;
}

bool SwFrame::OnCanDoRomanNumeralsList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoRomanNumeralsList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoRomanNumeralsList();

    return false;
}

bool SwFrame::IsSelectionRomanNumeralsList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionRomanNumeralsList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionRomanNumeralsList();

    return false;
}

bool SwFrame::OnCanDoDecimalList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDecimalList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDecimalList();

    return false;
}

bool SwFrame::IsSelectionDecimalList()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionDecimalList();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionDecimalList();

    return false;
}

bool SwFrame::OnCanDoInsertTable()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertTable();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertTable();

    return false;
}

bool SwFrame::OnCanDoInsertRow()
{
   if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertRow();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertRow();

    return false;
}

bool SwFrame::OnCanDoDeleteRow()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDeleteRow();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDeleteRow();

    return false;
}

bool SwFrame::OnCanDoInsertColumn()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertColumn();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertColumn();

    return false;
}

bool SwFrame::OnCanDoDeleteColumn()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDeleteColumn();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDeleteColumn();

    return false;
}

bool SwFrame::OnCanDoInsertImage()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertImage();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertImage();

    return false;
}

bool SwFrame::OnCanDoInsertLink()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertLink();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertLink();

    return false;
}

bool SwFrame::OnCanDoInsertAnchor()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertAnchor();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertAnchor();

    return false;
}

bool SwFrame::OnCanDoInsertControl()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertControl();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertControl();

    return false;
}

bool SwFrame::OnCanDoInsertHorizontalRule()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertHorizontalRule();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertHorizontalRule();

    return false;
}

bool SwFrame::OnCanDoPlay()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPlay();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPlay();

    return false;
}

bool SwFrame::OnCanDoPause()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPause();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPause();

    return false;
}

bool SwFrame::OnCanDoStop()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoStop();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoStop();

    return false;
}

bool SwFrame::OnCanDoRewind()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoRewind();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoRewind();

    return false;
}

bool SwFrame::OnCanDoFastForward()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFastForward();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFastForward();

    return false;
}

bool SwFrame::OnCanDoPrevious()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPrevious();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPrevious();

    return false;
}

bool SwFrame::OnCanDoNext()
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoNext();
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoNext();

    return false;
}

bool SwFrame::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->ActivateBookMark(data, ctrlid);
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->ActivateBookMark(data, ctrlid);

    return false;
}

bool SwFrame::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);

    return false;
}

bool SwFrame::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);

    return false;
}

bool SwFrame::LoadLibraryItem(const char * path)
{
    if (m_guipanel)
        return m_guipanel->LoadLibraryItem(path);

    return false;
}

bool SwFrame::LoadLibraryItem(swUI16 managerId)
{
    if (m_guipanel)
        return m_guipanel->LoadLibraryItem(managerId);

    return false;
}

void SwFrame::OnModuleManagerReset()
{
    if (m_toolbook)
        m_toolbook->OnModuleManagerReset();

    if (m_guipanel)
        m_guipanel->OnModuleManagerReset();
}

void SwFrame::OnThMLFileManagerReset()
{
    if (m_toolbook)
        m_toolbook->OnThMLFileManagerReset();

    if (m_guipanel)
        m_guipanel->OnThMLFileManagerReset();
}

void SwFrame::OnModuleManagerLoaded()
{
    if (m_toolbook)
        m_toolbook->OnModuleManagerLoaded();

    if (m_guipanel)
        m_guipanel->OnModuleManagerLoaded();
}

void SwFrame::OnThMLFileManagerLoaded()
{
    if (m_toolbook)
        m_toolbook->OnThMLFileManagerLoaded();

    if (m_guipanel)
        m_guipanel->OnThMLFileManagerLoaded();
}

void SwFrame::OnModuleAdded(swUI16 mid)
{
    if (m_toolbook)
        m_toolbook->OnModuleAdded(mid);

    if (m_guipanel)
        m_guipanel->OnModuleAdded(mid);
}

void SwFrame::OnModuleDeleted(swUI16 mid)
{
    if (m_toolbook)
        m_toolbook->OnModuleDeleted(mid);

    if (m_guipanel)
        m_guipanel->OnModuleDeleted(mid);
}

void SwFrame::OnThMLFileAdded(swUI16 mid)
{
    if (m_toolbook)
        m_toolbook->OnThMLFileAdded(mid);

    if (m_guipanel)
        m_guipanel->OnThMLFileAdded(mid);
}

bool SwFrame::SelectTab(const char * path)
{
    if (!m_toolbook)
        return false;

    swUI32 id = m_toolbook->FindFile(path);
    if (id != NODE_ID_INVALID)
    {
        m_toolbook->ChangeSelection(id);
        return true;
    }

    return false;
}

void SwFrame::OnThMLFileDeleted(swUI16 mid)
{
    if (m_toolbook)
        m_toolbook->OnThMLFileDeleted(mid);

    if (m_guipanel)
        m_guipanel->OnThMLFileDeleted(mid);
}

swUI16 SwFrame::GetInitialInterfacePlugIn()
{
    swUI16 plugIn = NODE_ID_INVALID_16;
    swUI32 node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Interface-PlugIn");

    if (node != NODE_ID_INVALID)
    {
        plugIn = SwApplicationInterface::GetPlugInManager().FindPlugIn(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node));
    }

    if (plugIn == NODE_ID_INVALID_16)
    {
        plugIn = SwApplicationInterface::GetPlugInManager().FindFirstInterface();
    }

    return plugIn;
}
