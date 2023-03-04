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
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnOpen();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnOpen();
    else if (m_guipanel)
        m_guipanel->OnOpen();
    else if (m_toolbook)
        m_toolbook->OnOpen();
}

void SwFrame::OnClose(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnClose();
    else if (m_toolbook && m_toolbook->OnHasFocus())
    {
         m_toolbook->OnClose();
         ToolRemoved();
    }
    else if (m_guipanel)
        m_guipanel->OnClose();
    else if (m_toolbook)
    {
        m_toolbook->OnClose();
        ToolRemoved();
    }
}

void SwFrame::OnCloseAll(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnCloseAll();
    else if (m_toolbook && m_toolbook->OnHasFocus())
    {
        m_toolbook->OnCloseAll();
        ToolRemoved();
    }
    else if (m_guipanel)
        m_guipanel->OnCloseAll();
    else if (m_toolbook)
    {
        m_toolbook->OnCloseAll();
        ToolRemoved();
    }
}

void SwFrame::OnSave(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSave();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSave();
    else if (m_guipanel)
        m_guipanel->OnSave();
    else if (m_toolbook)
        m_toolbook->OnSave();
}

void SwFrame::OnSaveAs(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSaveAs();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSaveAs();
    else if (m_guipanel)
        m_guipanel->OnSaveAs();
    else if (m_toolbook)
        m_toolbook->OnSaveAs();
}

void SwFrame::OnFile1(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile1();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile1();
    else if (m_guipanel)
        m_guipanel->OnFile1();
    else if (m_toolbook)
        m_toolbook->OnFile1();
}

void SwFrame::OnFile2(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile2();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile2();
    else if (m_guipanel)
        m_guipanel->OnFile2();
    else if (m_toolbook)
        m_toolbook->OnFile2();
}

void SwFrame::OnFile3(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile3();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile3();
    else if (m_guipanel)
        m_guipanel->OnFile3();
     else if (m_toolbook)
        m_toolbook->OnFile3();
}

void SwFrame::OnFile4(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile4();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile4();
    else if (m_guipanel)
        m_guipanel->OnFile4();
    else if (m_toolbook)
        m_toolbook->OnFile4();
}

void SwFrame::OnFile5(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile5();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile5();
    else if (m_guipanel)
        m_guipanel->OnFile5();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile5();
}

void SwFrame::OnFile6(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile6();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile6();
    else if (m_guipanel)
        m_guipanel->OnFile6();
    else if (m_toolbook)
        m_toolbook->OnFile6();
}

void SwFrame::OnFile7(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile7();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile7();
    else if (m_guipanel)
        m_guipanel->OnFile7();
     else if (m_toolbook)
        m_toolbook->OnFile7();
}

void SwFrame::OnFile8(wxCommandEvent & event)
{
   if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile8();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile8();
    else if (m_guipanel)
        m_guipanel->OnFile8();
    else if (m_toolbook)
        m_toolbook->OnFile8();
}

void SwFrame::OnFile9(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile9();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile9();
    else if (m_guipanel)
        m_guipanel->OnFile9();
    else if (m_toolbook)
        m_toolbook->OnFile9();
}

void SwFrame::OnFile10(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFile10();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFile10();
    else if (m_guipanel)
        m_guipanel->OnFile10();
}

void SwFrame::OnPrint(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPrint();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPrint();
    else if (m_guipanel)
        m_guipanel->OnPrint();
    else if (m_toolbook)
        m_toolbook->OnPrint();
}

void SwFrame::OnPrintPreview(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPrintPreview();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPrintPreview();
    else if (m_guipanel)
        m_guipanel->OnPrintPreview();
    else if (m_toolbook)
        m_toolbook->OnPrintPreview();
}

void SwFrame::OnClear(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnClear();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnClear();
    else if (m_guipanel)
        m_guipanel->OnClear();
    else if (m_toolbook)
        m_toolbook->OnClear();
}

void SwFrame::OnNew(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnNew();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnNew();
    else if (m_guipanel)
        m_guipanel->OnNew();
    else if (m_toolbook)
        m_toolbook->OnNew();
}

void SwFrame::OnCut(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnCut();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnCut();
    else if (m_guipanel)
        m_guipanel->OnCut();
    else if (m_toolbook)
        m_toolbook->OnCut();
}

void SwFrame::OnCopy(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnCopy();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnCopy();
    else if (m_guipanel)
        m_guipanel->OnCopy();
    else if (m_toolbook)
        m_toolbook->OnCopy();
}

void SwFrame::OnPaste(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPaste();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPaste();
    else if (m_guipanel)
        m_guipanel->OnPaste();
    else if (m_toolbook)
        m_toolbook->OnPaste();
}

void SwFrame::OnUndo(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnUndo();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnUndo();
    else if (m_guipanel)
        m_guipanel->OnUndo();
    else if (m_toolbook)
        m_toolbook->OnUndo();
}

void SwFrame::OnRedo(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnRedo();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnRedo();
    else if (m_guipanel)
        m_guipanel->OnRedo();
    else if (m_toolbook)
        m_toolbook->OnRedo();
}

void SwFrame::OnSelectAll(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSelectAll();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSelectAll();
    else if (m_guipanel)
        m_guipanel->OnSelectAll();
    else if (m_toolbook)
        m_toolbook->OnSelectAll();
}

void SwFrame::OnAlignLeft(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlignLeft();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlignLeft();
    else if (m_guipanel)
        m_guipanel->OnAlignLeft();
    else if (m_toolbook)
        m_toolbook->OnAlignLeft();
}

void SwFrame::OnAlignCenter(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlignCenter();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlignCenter();
    else if (m_guipanel)
        m_guipanel->OnAlignCenter();
    else if (m_toolbook)
        m_toolbook->OnAlignCenter();
}

void SwFrame::OnAlignRight(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlignRight();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlignRight();
    else if (m_guipanel)
        m_guipanel->OnAlignRight();
    else if (m_toolbook)
        m_toolbook->OnAlignRight();
}

void SwFrame::OnBold(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBold();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBold();
    else if (m_guipanel)
        m_guipanel->OnBold();
    else if (m_toolbook)
        m_toolbook->OnBold();
}

void SwFrame::OnItalic(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnItalic();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnItalic();
    else  if (m_guipanel)
        m_guipanel->OnItalic();
    else if (m_toolbook)
        m_toolbook->OnItalic();
}

void SwFrame::OnUnderline(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnUnderline();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnUnderline();
    else if (m_guipanel)
        m_guipanel->OnUnderline();
    else if (m_toolbook)
        m_toolbook->OnUnderline();
}

void SwFrame::OnStrikeThrough(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnStrikeThrough();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnStrikeThrough();
    else if (m_guipanel)
        m_guipanel->OnStrikeThrough();
    else if (m_toolbook)
        m_toolbook->OnStrikeThrough();
}

void SwFrame::OnSuperScript(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSuperScript();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSuperScript();
    else if (m_guipanel)
        m_guipanel->OnSuperScript();
    else if (m_toolbook)
        m_toolbook->OnSuperScript();
}

void SwFrame::OnSubScript(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSubScript();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSubScript();
    else if (m_guipanel)
        m_guipanel->OnSubScript();
    else if (m_toolbook)
        m_toolbook->OnSubScript();
}

void SwFrame::OnIndentMore(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnIndentMore();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnIndentMore();
    else if (m_guipanel)
        m_guipanel->OnIndentMore();
    else if (m_toolbook)
        m_toolbook->OnIndentMore();
}

void SwFrame::OnIndentLess(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnIndentLess();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnIndentLess();
    else if (m_guipanel)
        m_guipanel->OnIndentLess();
    else if (m_toolbook)
        m_toolbook->OnIndentLess();
}

void SwFrame::OnSingleSpacing(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSingleSpacing();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSingleSpacing();
    else  if (m_guipanel)
        m_guipanel->OnSingleSpacing();
    else if (m_toolbook)
        m_toolbook->OnSingleSpacing();
}

void SwFrame::OnDoubleSpacing(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDoubleSpacing();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDoubleSpacing();
    else if (m_guipanel)
        m_guipanel->OnDoubleSpacing();
    else if (m_toolbook)
        m_toolbook->OnDoubleSpacing();
}

void SwFrame::OnMargins(wxCommandEvent & event)
{
   if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnMargins();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnMargins();
    else  if (m_guipanel)
        m_guipanel->OnMargins();
    else if (m_toolbook)
        m_toolbook->OnMargins();
}

void SwFrame::OnFont(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFont();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFont();
    else if (m_guipanel)
        m_guipanel->OnFont();
    else if (m_toolbook)
        m_toolbook->OnFont();
}

void SwFrame::OnColor(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnColor();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnColor();
    else if (m_guipanel)
        m_guipanel->OnColor();
    else if (m_toolbook)
        m_toolbook->OnColor();
}

void SwFrame::OnBackgroundColor(wxCommandEvent & event)
{
   if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBackgroundColor();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBackgroundColor();
    else  if (m_guipanel)
        m_guipanel->OnBackgroundColor();
    else if (m_toolbook)
        m_toolbook->OnBackgroundColor();
}

void SwFrame::OnStyle(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnStyle();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnStyle();
    else if (m_guipanel)
        m_guipanel->OnStyle();
    else if (m_toolbook)
        m_toolbook->OnStyle();
}

void SwFrame::OnInsertImage(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertImage();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertImage();
    else if (m_guipanel)
        m_guipanel->OnInsertImage();
    else if (m_toolbook)
        m_toolbook->OnInsertImage();
}

void SwFrame::OnInsertLink(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertLink();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertLink();
    else if (m_guipanel)
        m_guipanel->OnInsertLink();
    else if (m_toolbook)
        m_toolbook->OnInsertLink();
}

void SwFrame::OnInsertAnchor(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertAnchor();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertAnchor();
    else if (m_guipanel)
        m_guipanel->OnInsertAnchor();
    else if (m_toolbook)
        m_toolbook->OnInsertAnchor();
}

void SwFrame::OnInsertTable(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertTable();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertTable();
    else if (m_guipanel)
        m_guipanel->OnInsertTable();
    else if (m_toolbook)
        m_toolbook->OnInsertTable();
}

void SwFrame::OnInsertRow(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertRow();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertRow();
    else  if (m_guipanel)
        m_guipanel->OnInsertRow();
    else if (m_toolbook)
        m_toolbook->OnInsertRow();
}

void SwFrame::OnInsertColumn(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertColumn();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertColumn();
    else if (m_guipanel)
        m_guipanel->OnInsertColumn();
    else if (m_toolbook)
        m_toolbook->OnInsertColumn();
}

void SwFrame::OnDeleteRow(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDeleteRow();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDeleteRow();
    else if (m_guipanel)
        m_guipanel->OnDeleteRow();
    else if (m_toolbook)
        m_toolbook->OnDeleteRow();
}

void SwFrame::OnDeleteColumn(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDeleteColumn();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDeleteColumn();
    else if (m_guipanel)
        m_guipanel->OnDeleteColumn();
    else if (m_toolbook)
        m_toolbook->OnDeleteColumn();
}

void SwFrame::OnInsertControl(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertControl();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertControl();
    else if (m_guipanel)
        m_guipanel->OnInsertControl();
    else if (m_toolbook)
        m_toolbook->OnInsertControl();
}

void SwFrame::OnInsertHorizontalRule(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnInsertHorizontalRule();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnInsertHorizontalRule();
    else if (m_guipanel)
        m_guipanel->OnInsertHorizontalRule();
    else if (m_toolbook)
        m_toolbook->OnInsertHorizontalRule();
}

void SwFrame::OnAlphaList(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAlphaList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAlphaList();
    else if (m_guipanel)
        m_guipanel->OnAlphaList();
    else if (m_toolbook)
        m_toolbook->OnAlphaList();
}

void SwFrame::OnBulletedList(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBulletedList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBulletedList();
    else if (m_guipanel)
        m_guipanel->OnBulletedList();
    else if (m_toolbook)
        m_toolbook->OnBulletedList();
}

void SwFrame::OnRomanList(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnRomanList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnRomanList();
    else if (m_guipanel)
        m_guipanel->OnRomanList();
    else if (m_toolbook)
        m_toolbook->OnRomanList();
}

void SwFrame::OnDecimalList(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnDecimalList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnDecimalList();
    else if (m_guipanel)
        m_guipanel->OnDecimalList();
    else if (m_toolbook)
        m_toolbook->OnDecimalList();
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
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnProperties();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnProperties();
    else if (m_guipanel)
        m_guipanel->OnProperties();
    else if (m_toolbook)
        m_toolbook->OnProperties();
}

void SwFrame::OnZoomIn(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnZoomIn();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnZoomIn();
    else if (m_guipanel)
        m_guipanel->OnZoomIn();
    else if (m_toolbook)
        m_toolbook->OnZoomIn();
}

void SwFrame::OnZoomOut(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnZoomOut();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnZoomOut();
    else if (m_guipanel)
        m_guipanel->OnZoomOut();
    else if (m_toolbook)
        m_toolbook->OnZoomOut();
}

void SwFrame::OnViewNormal(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnViewNormal();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnViewNormal();
    else  if (m_guipanel)
        m_guipanel->OnViewNormal();
    else if (m_toolbook)
        m_toolbook->OnViewNormal();
}

void SwFrame::OnContentsUp(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnContentsUp();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnContentsUp();
    else if (m_guipanel)
        m_guipanel->OnContentsUp();
    else if (m_toolbook)
        m_toolbook->OnContentsUp();
}

void SwFrame::OnContentsDown(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnContentsDown();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnContentsDown();
    else if (m_guipanel)
        m_guipanel->OnContentsDown();
    else if (m_toolbook)
        m_toolbook->OnContentsDown();
}

void SwFrame::OnHistoryBack(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnHistoryBack();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnHistoryBack();
    else if (m_guipanel)
        m_guipanel->OnHistoryBack();
    else if (m_toolbook)
        m_toolbook->OnHistoryBack();
}

void SwFrame::OnHistoryForward(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnHistoryForward();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnHistoryForward();
    else if (m_guipanel)
        m_guipanel->OnHistoryForward();
    else if (m_toolbook)
        m_toolbook->OnHistoryForward();
}

void SwFrame::OnBookmark(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBookMarkPage();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBookMarkPage();
    else  if (m_guipanel)
        m_guipanel->OnBookMarkPage();
    else if (m_toolbook)
        m_toolbook->OnBookMarkPage();
}

void SwFrame::OnFind(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFind(L"", false, false);
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFind(L"", false, false);
    else if (m_guipanel)
        m_guipanel->OnFind(L"", false, false);
    else if (m_toolbook)
        m_toolbook->OnFind(L"", false, false);
}

void SwFrame::OnFindReset(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFindReset();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFindReset();
    else if (m_guipanel)
        m_guipanel->OnFindReset();
    else if (m_toolbook)
        m_toolbook->OnFindReset();
}

void SwFrame::OnFindNext(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFindNext();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFindNext();
    else if (m_guipanel)
        m_guipanel->OnFindNext();
    else if (m_toolbook)
        m_toolbook->OnFindNext();
}

void SwFrame::OnReplace(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnReplace();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnReplace();
    else if (m_guipanel)
        m_guipanel->OnReplace();
    else if (m_toolbook)
        m_toolbook->OnReplace();
}

void SwFrame::OnReplaceAll(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnReplaceAll();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnReplaceAll();
    else if (m_guipanel)
        m_guipanel->OnReplaceAll();
    else if (m_toolbook)
        m_toolbook->OnReplaceAll();
}

void SwFrame::OnLibraryView(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnLibraryView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnLibraryView();
    else if (m_guipanel)
        m_guipanel->OnLibraryView();
    else if (m_toolbook)
        m_toolbook->OnLibraryView();
}

void SwFrame::OnContentsView(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnContentsView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnContentsView();
    else if (m_guipanel)
        m_guipanel->OnContentsView();
    else if (m_toolbook)
        m_toolbook->OnContentsView();
}

void SwFrame::OnSearchView(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnSearchView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnSearchView();
    else  if (m_guipanel)
        m_guipanel->OnSearchView();
    else if (m_toolbook)
        m_toolbook->OnSearchView();
}

void SwFrame::OnFindView(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFindView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFindView();
    else if (m_guipanel)
        m_guipanel->OnFindView();
    else if (m_toolbook)
        m_toolbook->OnFindView();
}

void SwFrame::OnBookmarksView(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnBookmarksView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnBookmarksView();
    else if (m_guipanel)
        m_guipanel->OnBookmarksView();
    else if (m_toolbook)
        m_toolbook->OnBookmarksView();
}

void SwFrame::OnHistoryView(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnHistoryView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnHistoryView();
    else if (m_guipanel)
        m_guipanel->OnHistoryView();
    else if (m_toolbook)
        m_toolbook->OnHistoryView();
}

void SwFrame::OnPlay(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPlay();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPlay();
    else if (m_guipanel)
        m_guipanel->OnPlay();
    else if (m_toolbook)
        m_toolbook->OnPlay();
}

void SwFrame::OnPause(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPause();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPause();
    else if (m_guipanel)
        m_guipanel->OnPause();
    else if (m_toolbook)
        m_toolbook->OnPause();
}

void SwFrame::OnStop(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnStop();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnStop();
    else if (m_guipanel)
        m_guipanel->OnStop();
    else if (m_toolbook)
        m_toolbook->OnStop();
}

void SwFrame::OnRewind(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnRewind();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnRewind();
    else  if (m_guipanel)
        m_guipanel->OnRewind();
    else if (m_toolbook)
        m_toolbook->OnRewind();
}

void SwFrame::OnFastForward(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnFastForward();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnFastForward();
    else if (m_guipanel)
        m_guipanel->OnFastForward();
    else if (m_toolbook)
        m_toolbook->OnFastForward();
}

void SwFrame::OnPrevious(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPrevious();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPrevious();
    else if (m_guipanel)
        m_guipanel->OnPrevious();
    else if (m_toolbook)
        m_toolbook->OnPrevious();
}

void SwFrame::OnNext(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnNext();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnNext();
    else if (m_guipanel)
        m_guipanel->OnNext();
    else if (m_toolbook)
        m_toolbook->OnNext();
}

void SwFrame::OnPreferences(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnPreferences();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnPreferences();
    else if (m_guipanel)
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
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnAbout();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnAbout();
    else if (m_guipanel)
        m_guipanel->OnAbout();
    else if (m_toolbook)
        m_toolbook->OnAbout();
}

void SwFrame::OnUpdateSoftware(wxCommandEvent & event)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->OnUpdateSoftware();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->OnUpdateSoftware();
    else if (m_guipanel)
        m_guipanel->OnUpdateSoftware();
    else if (m_toolbook)
        m_toolbook->OnUpdateSoftware();
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

    if (m_guipanel && m_guipanel->OnHasFocus())
        m_guipanel->UpdateGui(m_toolbar, m_menubar);
    else if (m_toolbook && m_toolbook->OnHasFocus())
        m_toolbook->UpdateGui(m_toolbar, m_menubar);
    else if (m_guipanel)
        m_guipanel->UpdateGui(m_toolbar, m_menubar);
    else if (m_toolbook)
        m_toolbook->UpdateGui(m_toolbar, m_menubar);

    OnFrameTimer();
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
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnHasSelection();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnHasSelection();
    else if (m_guipanel)
        return m_guipanel->OnHasSelection();
    else if (m_toolbook)
        return m_toolbook->OnHasSelection();

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
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoNew();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoNew();
    else if (m_guipanel)
        return m_guipanel->OnCanDoNew();
    else if (m_toolbook)
        return m_toolbook->OnCanDoNew();

    return false;
}

bool SwFrame::OnCanDoOpen()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoOpen();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoOpen();
    else if (m_guipanel)
        return m_guipanel->OnCanDoOpen();
    else if (m_toolbook)
        return m_toolbook->OnCanDoOpen();

    return false;
}

bool SwFrame::OnCanDoSave()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSave();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSave();
    else if (m_guipanel)
        return m_guipanel->OnCanDoSave();
    else if (m_toolbook)
        return m_toolbook->OnCanDoSave();

    return false;
}

bool SwFrame::OnCanDoSaveAs()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSaveAs();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSaveAs();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoSaveAs();
    else if (m_toolbook)
        return m_toolbook->OnCanDoSaveAs();

    return false;
}

bool SwFrame::OnCanDoClose()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoClose();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoClose();
    else if (m_guipanel)
        return m_guipanel->OnCanDoClose();
    else if (m_toolbook)
        return m_toolbook->OnCanDoClose();

    return false;
}

bool SwFrame::OnCanDoCloseAll()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoCloseAll();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoCloseAll();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoCloseAll();
    else if (m_toolbook)
        return m_toolbook->OnCanDoCloseAll();

    return false;
}

bool SwFrame::OnCanDoPrint()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPrint();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPrint();
    else if (m_guipanel)
        return m_guipanel->OnCanDoPrint();
    else if (m_toolbook)
        return m_toolbook->OnCanDoPrint();

    return false;
}

bool SwFrame::OnCanDoPrintPreview()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPrintPreview();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPrintPreview();
    else if (m_guipanel)
        return m_guipanel->OnCanDoPrintPreview();
    else if (m_toolbook)
        return m_toolbook->OnCanDoPrintPreview();

    return false;
}

bool SwFrame::OnCanDoBookMarkPage()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBookMarkPage();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBookMarkPage();
    else if (m_guipanel)
        return m_guipanel->OnCanDoBookMarkPage();
    else if (m_toolbook)
        return m_toolbook->OnCanDoBookMarkPage();

    return false;
}

bool SwFrame::OnCanDoFind()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFind();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFind();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoFind();
    else if (m_toolbook)
        return m_toolbook->OnCanDoFind();

    return false;
}

bool SwFrame::OnCanDoFindNext()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFindNext();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFindNext();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoFindNext();
    else if (m_toolbook)
        return m_toolbook->OnCanDoFindNext();

    return false;
}

bool SwFrame::OnCanDoReplace()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoReplace();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoReplace();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoReplace();
    else if (m_toolbook)
        return m_toolbook->OnCanDoReplace();

    return false;
}


bool SwFrame::OnCanDoClear()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoClear();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoClear();
    else if (m_guipanel)
        return m_guipanel->OnCanDoClear();
    else if (m_toolbook)
        return m_toolbook->OnCanDoClear();

    return false;
}

bool SwFrame::OnCanDoCut()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoCut();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoCut();
    else if (m_guipanel)
        return m_guipanel->OnCanDoCut();
    else if (m_toolbook)
        return m_toolbook->OnCanDoCut();

    return false;
}

bool SwFrame::OnCanDoCopy()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoCopy();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoCopy();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoCopy();
    else if (m_toolbook)
        return m_toolbook->OnCanDoCopy();

    return false;
}

bool SwFrame::OnCanDoPaste()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPaste();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPaste();
    else if (m_guipanel)
        return m_guipanel->OnCanDoPaste();
    else if (m_toolbook)
        return m_toolbook->OnCanDoPaste();

    return false;
}

bool SwFrame::OnCanDoUndo()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoUndo();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoUndo();
    else if (m_guipanel)
        return m_guipanel->OnCanDoUndo();
    else if (m_toolbook)
        return m_toolbook->OnCanDoUndo();

    return false;
}

bool SwFrame::OnCanDoRedo()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoRedo();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoRedo();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoRedo();
    else if (m_toolbook)
        return m_toolbook->OnCanDoRedo();

    return false;
}

bool SwFrame::OnCanDoSelectAll()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSelectAll();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSelectAll();
    else if (m_guipanel)
        return m_guipanel->OnCanDoSelectAll();
    else if (m_toolbook)
        return m_toolbook->OnCanDoSelectAll();

    return false;
}

bool SwFrame::OnCanDoProperties()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoProperties();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoProperties();
    else if (m_guipanel)
        return m_guipanel->OnCanDoProperties();
    else if (m_toolbook)
        return m_toolbook->OnCanDoProperties();

    return false;
}

bool SwFrame::HasLibraryView()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasLibraryView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasLibraryView();
    else if (m_guipanel)
        return m_guipanel->HasLibraryView();
    else if (m_toolbook)
        return m_toolbook->HasLibraryView();

    return false;
}

bool SwFrame::HasContentsView()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasContentsView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasContentsView();
    else if (m_toolbook)
        return m_toolbook->HasContentsView();
    else if (m_guipanel)
        return m_guipanel->HasContentsView();

    return false;
}

bool SwFrame::HasBookmarksView()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasBookmarksView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasBookmarksView();
    else if (m_guipanel)
        return m_guipanel->HasBookmarksView();
    else if (m_toolbook)
        return m_toolbook->HasBookmarksView();

    return false;
}

bool SwFrame::HasFindView()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasFindView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasFindView();
    else if (m_guipanel)
        return m_guipanel->HasFindView();
    else if (m_toolbook)
        return m_toolbook->HasFindView();

    return false;
}

bool SwFrame::HasSearchView()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasSearchView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasSearchView();
    else  if (m_guipanel)
        return m_guipanel->HasSearchView();
    else if (m_toolbook)
        return m_toolbook->HasSearchView();

    return false;
}

bool SwFrame::HasHistoryView()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->HasHistoryView();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->HasHistoryView();
    else  if (m_guipanel)
        return m_guipanel->HasHistoryView();
    else if (m_toolbook)
        return m_toolbook->HasHistoryView();

    return false;
}

bool SwFrame::OnCanDoZoomIn()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoZoomIn();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoZoomIn();
    else if (m_guipanel)
        return m_guipanel->OnCanDoZoomIn();
    else if (m_toolbook)
        return m_toolbook->OnCanDoZoomIn();

    return false;
}

bool SwFrame::OnCanDoZoomOut()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoZoomOut();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoZoomOut();
    else if (m_guipanel)
        return m_guipanel->OnCanDoZoomOut();
    else if (m_toolbook)
        return m_toolbook->OnCanDoZoomOut();

    return false;
}

bool SwFrame::OnCanDoViewNormal()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoViewNormal();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoViewNormal();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoViewNormal();
    else if (m_toolbook)
        return m_toolbook->OnCanDoViewNormal();

    return false;
}

bool SwFrame::OnCanDoUpInContents()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoUpInContents();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoUpInContents();
    else if (m_guipanel)
        return m_guipanel->OnCanDoUpInContents();
    else if (m_toolbook)
        return m_toolbook->OnCanDoUpInContents();

    return false;
}

bool SwFrame::OnCanDoDownInContents()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDownInContents();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDownInContents();
    else if (m_guipanel)
        return m_guipanel->OnCanDoDownInContents();
    else if (m_toolbook)
        return m_toolbook->OnCanDoDownInContents();

    return false;
}

bool SwFrame::OnCanDoBackInHistory()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBackInHistory();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBackInHistory();
    else if (m_guipanel)
        return m_guipanel->OnCanDoBackInHistory();
    else if (m_toolbook)
        return m_toolbook->OnCanDoBackInHistory();

    return false;
}

bool SwFrame::OnCanDoForwardInHistory()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoForwardInHistory();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoForwardInHistory();
    else if (m_guipanel)
        return m_guipanel->OnCanDoForwardInHistory();
    else if (m_toolbook)
        return m_toolbook->OnCanDoForwardInHistory();

    return false;
}

bool SwFrame::OnCanDoFont()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFont();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFont();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoFont();
    else if (m_toolbook)
        return m_toolbook->OnCanDoFont();

    return false;
}

bool SwFrame::OnCanDoBold()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBold();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBold();
    else if (m_guipanel)
        return m_guipanel->OnCanDoBold();
    else if (m_toolbook)
        return m_toolbook->OnCanDoBold();

    return false;
}

bool SwFrame::IsSelectionBold()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionBold();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionBold();
    else  if (m_guipanel)
        return m_guipanel->IsSelectionBold();
    else if (m_toolbook)
        return m_toolbook->IsSelectionBold();

    return false;
}

bool SwFrame::OnCanDoItalic()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoItalic();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoItalic();
     else if (m_guipanel)
        return m_guipanel->OnCanDoItalic();
    else if (m_toolbook)
        return m_toolbook->OnCanDoItalic();

    return false;
}

bool SwFrame::IsSelectionItalic()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionItalic();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionItalic();
    else if (m_guipanel)
        return m_guipanel->IsSelectionItalic();
    else if (m_toolbook)
        return m_toolbook->IsSelectionItalic();

    return false;
}

bool SwFrame::OnCanDoUnderline()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoUnderline();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoUnderline();
    else if (m_guipanel)
        return m_guipanel->OnCanDoUnderline();
    else if (m_toolbook)
        return m_toolbook->OnCanDoUnderline();

    return false;
}

bool SwFrame::IsSelectionUnderline()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionUnderline();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionUnderline();
    else if (m_guipanel)
        return m_guipanel->IsSelectionUnderline();
    else if (m_toolbook)
        return m_toolbook->IsSelectionUnderline();

    return false;
}

bool SwFrame::OnCanDoStrikeThrough()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoStrikeThrough();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoStrikeThrough();
    else if (m_guipanel)
        return m_guipanel->OnCanDoStrikeThrough();
    else if (m_toolbook)
        return m_toolbook->OnCanDoStrikeThrough();

    return false;
}

bool SwFrame::IsSelectionStrikeThrough()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionStrikeThrough();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionStrikeThrough();
    else if (m_guipanel)
        return m_guipanel->IsSelectionStrikeThrough();
    else if (m_toolbook)
        return m_toolbook->IsSelectionStrikeThrough();

    return false;
}

bool SwFrame::OnCanDoSuperScript()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSuperScript();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSuperScript();
    else if (m_guipanel)
        return m_guipanel->OnCanDoSuperScript();
    else if (m_toolbook)
        return m_toolbook->OnCanDoSuperScript();

    return false;
}

bool SwFrame::IsSelectionSuperScript()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionSuperScript();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionSuperScript();
    else if (m_guipanel)
        return m_guipanel->IsSelectionSuperScript();
    else if (m_toolbook)
        return m_toolbook->IsSelectionSuperScript();

    return false;
}

bool SwFrame::OnCanDoSubScript()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSubScript();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSubScript();
    else if (m_guipanel)
        return m_guipanel->OnCanDoSubScript();
    else if (m_toolbook)
        return m_toolbook->OnCanDoSubScript();

    return false;
}

bool SwFrame::IsSelectionSubScript()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionSubScript();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionSubScript();
    else if (m_guipanel)
        return m_guipanel->IsSelectionSubScript();
    else if (m_toolbook)
        return m_toolbook->IsSelectionSubScript();

    return false;
}

bool SwFrame::OnCanDoColor()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoColor();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoColor();
    else if (m_guipanel)
        return m_guipanel->OnCanDoColor();
    else if (m_toolbook)
        return m_toolbook->OnCanDoColor();

    return false;
}

bool SwFrame::OnCanDoBackGroundColor()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBackGroundColor();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBackGroundColor();
    else if (m_guipanel)
        return m_guipanel->OnCanDoBackGroundColor();
    else if (m_toolbook)
        return m_toolbook->OnCanDoBackGroundColor();

    return false;
}

bool SwFrame::OnCanDoStyle()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoStyle();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoStyle();
    else if (m_guipanel)
        return m_guipanel->OnCanDoStyle();
    else if (m_toolbook)
        return m_toolbook->OnCanDoStyle();

    return false;
}

bool SwFrame::OnCanDoMargins()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoMargins();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoMargins();
    else if (m_guipanel)
        return m_guipanel->OnCanDoMargins();
    else if (m_toolbook)
        return m_toolbook->OnCanDoMargins();

    return false;
}

bool SwFrame::OnCanDoIndentMore()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoIndentMore();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoIndentMore();
    else if (m_guipanel)
        return m_guipanel->OnCanDoIndentMore();
    else if (m_toolbook)
        return m_toolbook->OnCanDoIndentMore();

    return false;
}

bool SwFrame::OnCanDoIndentLess()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoIndentLess();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoIndentLess();
    else if (m_guipanel)
        return m_guipanel->OnCanDoIndentLess();
    else if (m_toolbook)
        return m_toolbook->OnCanDoIndentLess();

    return false;
}

bool SwFrame::OnCanDoAlignLeft()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlignLeft();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlignLeft();
    else if (m_guipanel)
        return m_guipanel->OnCanDoAlignLeft();
    else if (m_toolbook)
        return m_toolbook->OnCanDoAlignLeft();

    return false;
}

bool SwFrame::IsSelectionAlignLeft()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlignLeft();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlignLeft();
    else if (m_guipanel)
        return m_guipanel->IsSelectionAlignLeft();
    else if (m_toolbook)
        return m_toolbook->IsSelectionAlignLeft();

    return false;
}

bool SwFrame::OnCanDoAlignCenter()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlignCenter();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlignCenter();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoAlignCenter();
    else if (m_toolbook)
        return m_toolbook->OnCanDoAlignCenter();

    return false;
}

bool SwFrame::IsSelectionAlignCenter()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlignCenter();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlignCenter();
    else if (m_guipanel)
        return m_guipanel->IsSelectionAlignCenter();
    else if (m_toolbook)
        return m_toolbook->IsSelectionAlignCenter();

    return false;
}

bool SwFrame::OnCanDoAlignRight()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlignRight();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlignRight();
    else if (m_guipanel)
        return m_guipanel->OnCanDoAlignRight();
    else if (m_toolbook)
        return m_toolbook->OnCanDoAlignRight();

    return false;
}

bool SwFrame::IsSelectionAlignRight()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlignRight();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlignRight();
    else  if (m_guipanel)
        return m_guipanel->IsSelectionAlignRight();
    else if (m_toolbook)
        return m_toolbook->IsSelectionAlignRight();

    return false;
}

bool SwFrame::OnCanDoSingleSpacing()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoSingleSpacing();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoSingleSpacing();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoSingleSpacing();
    else if (m_toolbook)
        return m_toolbook->OnCanDoSingleSpacing();

    return false;
}

bool SwFrame::IsSelectionSingleSpacing()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionSingleSpacing();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionSingleSpacing();
    else if (m_guipanel)
        return m_guipanel->IsSelectionSingleSpacing();
    else if (m_toolbook)
        return m_toolbook->IsSelectionSingleSpacing();

    return false;
}

bool SwFrame::OnCanDoDoubleSpacing()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDoubleSpacing();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDoubleSpacing();
    else if (m_guipanel)
        return m_guipanel->OnCanDoDoubleSpacing();
    else if (m_toolbook)
        return m_toolbook->OnCanDoDoubleSpacing();

    return false;
}

bool SwFrame::IsSelectionDoubleSpacing()
{
   if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionDoubleSpacing();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionDoubleSpacing();
    else if (m_guipanel)
        return m_guipanel->IsSelectionDoubleSpacing();
    else if (m_toolbook)
        return m_toolbook->IsSelectionDoubleSpacing();

    return false;
}

bool SwFrame::OnCanDoAlphaList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoAlphaList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoAlphaList();
    else if (m_guipanel)
        return m_guipanel->OnCanDoAlphaList();
    else if (m_toolbook)
        return m_toolbook->OnCanDoAlphaList();

    return false;
}

bool SwFrame::IsSelectionAlphaList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionAlphaList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionAlphaList();
    else if (m_guipanel)
        return m_guipanel->IsSelectionAlphaList();
    else if (m_toolbook)
        return m_toolbook->IsSelectionAlphaList();

    return false;
}

bool SwFrame::OnCanDoBulletedList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoBulletedList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoBulletedList();
    else if (m_guipanel)
        return m_guipanel->OnCanDoBulletedList();
    else if (m_toolbook)
        return m_toolbook->OnCanDoBulletedList();

    return false;
}

bool SwFrame::IsSelectionBulletedList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionBulletedList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionBulletedList();
    else if (m_guipanel)
        return m_guipanel->IsSelectionBulletedList();
    else if (m_toolbook)
        return m_toolbook->IsSelectionBulletedList();

    return false;
}

bool SwFrame::OnCanDoRomanNumeralsList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoRomanNumeralsList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoRomanNumeralsList();
    else if (m_guipanel)
        return m_guipanel->OnCanDoRomanNumeralsList();
    else if (m_toolbook)
        return m_toolbook->OnCanDoRomanNumeralsList();

    return false;
}

bool SwFrame::IsSelectionRomanNumeralsList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionRomanNumeralsList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionRomanNumeralsList();
    else  if (m_guipanel)
        return m_guipanel->IsSelectionRomanNumeralsList();
    else if (m_toolbook)
        return m_toolbook->IsSelectionRomanNumeralsList();

    return false;
}

bool SwFrame::OnCanDoDecimalList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDecimalList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDecimalList();
    else if (m_guipanel)
        return m_guipanel->OnCanDoDecimalList();
    else if (m_toolbook)
        return m_toolbook->OnCanDoDecimalList();

    return false;
}

bool SwFrame::IsSelectionDecimalList()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->IsSelectionDecimalList();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->IsSelectionDecimalList();
    else if (m_guipanel)
        return m_guipanel->IsSelectionDecimalList();
    else if (m_toolbook)
        return m_toolbook->IsSelectionDecimalList();

    return false;
}

bool SwFrame::OnCanDoInsertTable()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertTable();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertTable();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertTable();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertTable();

    return false;
}

bool SwFrame::OnCanDoInsertRow()
{
   if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertRow();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertRow();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertRow();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertRow();

    return false;
}

bool SwFrame::OnCanDoDeleteRow()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDeleteRow();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDeleteRow();
    else if (m_guipanel)
        return m_guipanel->OnCanDoDeleteRow();
    else if (m_toolbook)
        return m_toolbook->OnCanDoDeleteRow();

    return false;
}

bool SwFrame::OnCanDoInsertColumn()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertColumn();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertColumn();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertColumn();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertColumn();

    return false;
}

bool SwFrame::OnCanDoDeleteColumn()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoDeleteColumn();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoDeleteColumn();
    else if (m_guipanel)
        return m_guipanel->OnCanDoDeleteColumn();
    else if (m_toolbook)
        return m_toolbook->OnCanDoDeleteColumn();

    return false;
}

bool SwFrame::OnCanDoInsertImage()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertImage();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertImage();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoInsertImage();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertImage();

    return false;
}

bool SwFrame::OnCanDoInsertLink()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertLink();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertLink();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertLink();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertLink();

    return false;
}

bool SwFrame::OnCanDoInsertAnchor()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertAnchor();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertAnchor();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertAnchor();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertAnchor();

    return false;
}

bool SwFrame::OnCanDoInsertControl()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertControl();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertControl();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertControl();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertControl();

    return false;
}

bool SwFrame::OnCanDoInsertHorizontalRule()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoInsertHorizontalRule();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoInsertHorizontalRule();
    else if (m_guipanel)
        return m_guipanel->OnCanDoInsertHorizontalRule();
    else if (m_toolbook)
        return m_toolbook->OnCanDoInsertHorizontalRule();

    return false;
}

bool SwFrame::OnCanDoPlay()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPlay();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPlay();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoPlay();
    else if (m_toolbook)
        return m_toolbook->OnCanDoPlay();

    return false;
}

bool SwFrame::OnCanDoPause()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPause();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPause();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoPause();
    else if (m_toolbook)
        return m_toolbook->OnCanDoPause();

    return false;
}

bool SwFrame::OnCanDoStop()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoStop();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoStop();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoStop();
    else if (m_toolbook)
        return m_toolbook->OnCanDoStop();


    return false;
}

bool SwFrame::OnCanDoRewind()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoRewind();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoRewind();
    else if (m_guipanel)
        return m_guipanel->OnCanDoRewind();
    else if (m_toolbook)
        return m_toolbook->OnCanDoRewind();

    return false;
}

bool SwFrame::OnCanDoFastForward()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoFastForward();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoFastForward();
    else if (m_guipanel)
        return m_guipanel->OnCanDoFastForward();
    else if (m_toolbook)
        return m_toolbook->OnCanDoFastForward();

    return false;
}

bool SwFrame::OnCanDoPrevious()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoPrevious();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoPrevious();
    else  if (m_guipanel)
        return m_guipanel->OnCanDoPrevious();
    else if (m_toolbook)
        return m_toolbook->OnCanDoPrevious();

    return false;
}

bool SwFrame::OnCanDoNext()
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->OnCanDoNext();
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->OnCanDoNext();
    else if (m_guipanel)
        return m_guipanel->OnCanDoNext();
    else if (m_toolbook)
        return m_toolbook->OnCanDoNext();

    return false;
}

bool SwFrame::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->ActivateBookMark(data, ctrlid);
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->ActivateBookMark(data, ctrlid);
    else if (m_guipanel)
        return m_guipanel->ActivateBookMark(data, ctrlid);
    else if (m_toolbook)
        return m_toolbook->ActivateBookMark(data, ctrlid);

    return false;
}

bool SwFrame::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_guipanel)
        return m_guipanel->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_toolbook)
        return m_toolbook->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);

    return false;
}

bool SwFrame::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (m_guipanel && m_guipanel->OnHasFocus())
        return m_guipanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_toolbook && m_toolbook->OnHasFocus())
        return m_toolbook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_guipanel)
        return m_guipanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_toolbook)
        return m_toolbook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);

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
    if (m_guipanel)
        m_guipanel->OnModuleManagerReset();

    if (m_toolbook)
        m_toolbook->OnModuleManagerReset();
}

void SwFrame::OnThMLFileManagerReset()
{
    if (m_guipanel)
        m_guipanel->OnThMLFileManagerReset();

    if (m_toolbook)
        m_toolbook->OnThMLFileManagerReset();
}

void SwFrame::OnModuleManagerLoaded()
{
    if (m_guipanel)
        m_guipanel->OnModuleManagerLoaded();

    if (m_toolbook)
        m_toolbook->OnModuleManagerLoaded();
}

void SwFrame::OnThMLFileManagerLoaded()
{
    if (m_guipanel)
        m_guipanel->OnThMLFileManagerLoaded();

    if (m_toolbook)
        m_toolbook->OnThMLFileManagerLoaded();
}

void SwFrame::OnModuleAdded(swUI16 mid)
{
    if (m_guipanel)
        m_guipanel->OnModuleAdded(mid);

    if (m_toolbook)
        m_toolbook->OnModuleAdded(mid);
}

void SwFrame::OnModuleDeleted(swUI16 mid)
{
    if (m_guipanel)
        m_guipanel->OnModuleDeleted(mid);

    if (m_toolbook)
        m_toolbook->OnModuleDeleted(mid);
}

void SwFrame::OnThMLFileAdded(swUI16 mid)
{
    if (m_guipanel)
        m_guipanel->OnThMLFileAdded(mid);

    if (m_toolbook)
        m_toolbook->OnThMLFileAdded(mid);
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
    if (m_guipanel)
        m_guipanel->OnThMLFileDeleted(mid);

    if (m_toolbook)
        m_toolbook->OnThMLFileDeleted(mid);
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

void SwFrame::CreateStartUpFile(const char * name)
{
    if (!name)
        return;

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += name;
    path += ".st";

    SwFile f(path, FMD_WC);
    if (!f.m_file)
        return;

    f.Write((void *) ".", 1, 1);
    f.Close();
}

void SwFrame::DeleteStartUpFile(const char * name)
{
    if (!name)
        return;

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += name;
    path += ".st";

    unlink(path);
}

bool SwFrame::CheckStartUpFile(const char * name)
{
    if (!name)
        return false;

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += name;
    path += ".st";

    return SwFile::DoesExist(path);
}
