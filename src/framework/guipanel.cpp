///////////////////////////////////////////////////////////////////
// Name:        guipanel.cpp
// Purpose:     Primary panel in which to build user interfaces
//              for Sower applications.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/guipanel.h"
#include "../../include/appi/appifa.h"
#include "../../include/framework/viewbook.h"
#include "../../include/controls/moduletreectrl.h"
#include "../../include/controls/thmltreectrl.h"
#include "../../include/richtext/richtextctrlext.h"

IMPLEMENT_DYNAMIC_CLASS(SwGuiPanel, wxPanel)

SwGuiPanel::SwGuiPanel()
{
    Init();
}

SwGuiPanel::SwGuiPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxPanel(parent, id, pos, size, style, name)
{
    Init();
}

SwGuiPanel::~SwGuiPanel()
{
    m_manager->UnInit();
}

void SwGuiPanel::Init()
{
    m_librarypanel = NULL;
    m_librarybook = NULL;
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
}

bool SwGuiPanel::OnOpen()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnOpen();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnOpen();
    else if (m_librarybook)
        return m_librarybook->OnOpen();
    else if (m_librarypanel)
        return m_librarypanel->OnOpen();

    return false;
}

bool SwGuiPanel::OnClose()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnClose();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnClose();
    else if (m_librarybook)
        return m_librarybook->OnClose();
    else if (m_librarypanel)
        return m_librarypanel->OnClose();

    return true;
}

bool SwGuiPanel::OnCloseAll()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCloseAll();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCloseAll();
    else if (m_librarybook)
        return m_librarybook->OnCloseAll();
    else if (m_librarypanel)
        return m_librarypanel->OnCloseAll();

    return true;
}

bool SwGuiPanel::OnSave()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSave();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSave();
    else if (m_librarybook)
        return m_librarybook->OnSave();
    else if (m_librarypanel)
        return m_librarypanel->OnSave();

    return false;
}

bool SwGuiPanel::OnSaveAs()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSaveAs();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSaveAs();
    else if (m_librarybook)
        return m_librarybook->OnSaveAs();
    else if (m_librarypanel)
        return m_librarypanel->OnSaveAs();

    return false;
}

bool SwGuiPanel::OnFile1()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile1();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile1();
    else if (m_librarybook)
        return m_librarybook->OnFile1();
    else if (m_librarypanel)
        return m_librarypanel->OnFile1();

    return false;
}

bool SwGuiPanel::OnFile2()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile2();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile2();
    else if (m_librarybook)
        return m_librarybook->OnFile2();
    else if (m_librarypanel)
        return m_librarypanel->OnFile2();

    return false;
}

bool SwGuiPanel::OnFile3()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile3();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile3();
    else if (m_librarybook)
        return m_librarybook->OnFile3();
    else if (m_librarypanel)
        return m_librarypanel->OnFile3();

    return false;
}

bool SwGuiPanel::OnFile4()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile4();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile4();
    else if (m_librarybook)
        return m_librarybook->OnFile4();
    else if (m_librarypanel)
        return m_librarypanel->OnFile4();

    return false;
}

bool SwGuiPanel::OnFile5()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile5();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile5();
    else  if (m_librarybook)
        return m_librarybook->OnFile5();
    else if (m_librarypanel)
        return m_librarypanel->OnFile5();

    return false;
}

bool SwGuiPanel::OnFile6()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile6();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile6();
    else if (m_librarybook)
        return m_librarybook->OnFile6();
    else if (m_librarypanel)
        return m_librarypanel->OnFile6();

    return false;
}

bool SwGuiPanel::OnFile7()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile7();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile7();
    else if (m_librarybook)
        return m_librarybook->OnFile7();
    else if (m_librarypanel)
        return m_librarypanel->OnFile7();

    return false;
}

bool SwGuiPanel::OnFile8()
{
   if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile8();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile8();
    else if (m_librarybook)
        return m_librarybook->OnFile8();
    else if (m_librarypanel)
        return m_librarypanel->OnFile8();

    return false;
}

bool SwGuiPanel::OnFile9()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile9();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile9();
    else  if (m_librarybook)
        return m_librarybook->OnFile9();
    else if (m_librarypanel)
        return m_librarypanel->OnFile9();

    return false;
}

bool SwGuiPanel::OnFile10()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFile10();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFile10();
    else if (m_librarybook)
        return m_librarybook->OnFile10();
    else if (m_librarypanel)
        return m_librarypanel->OnFile10();

    return false;
}

bool SwGuiPanel::OnPrint()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnPrint();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnPrint();
    else if (m_librarybook)
        return m_librarybook->OnPrint();
    else if (m_librarypanel)
        return m_librarypanel->OnPrint();

    return false;
}

bool SwGuiPanel::OnPrintPreview()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnPrintPreview();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnPrintPreview();
    else if (m_librarybook)
        return m_librarybook->OnPrintPreview();
    else if (m_librarypanel)
        return m_librarypanel->OnPrintPreview();

    return false;
}

bool SwGuiPanel::OnClear()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnClear();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnClear();
    else if (m_librarybook)
        return m_librarybook->OnClear();
    else if (m_librarypanel)
        return m_librarypanel->OnClear();

    return false;
}

bool SwGuiPanel::OnNew()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnNew();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnNew();
    else if (m_librarybook)
        return m_librarybook->OnNew();
    else if (m_librarypanel)
        return m_librarypanel->OnNew();

    return false;
}

bool SwGuiPanel::OnCut()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCut();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCut();
    else  if (m_librarybook)
        return m_librarybook->OnCut();
    else if (m_librarypanel)
        return m_librarypanel->OnCut();

    return false;
}

bool SwGuiPanel::OnCopy()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCopy();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCopy();
    else if (m_librarybook)
        return m_librarybook->OnCopy();
    else if (m_librarypanel)
        return m_librarypanel->OnCopy();

    return false;
}

bool SwGuiPanel::OnPaste()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnPaste();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnPaste();
    else  if (m_librarybook)
        return m_librarybook->OnPaste();
    else if (m_librarypanel)
        return m_librarypanel->OnPaste();

    return false;
}

bool SwGuiPanel::OnUndo()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnUndo();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnUndo();
    else if (m_librarybook)
        return m_librarybook->OnUndo();
    else if (m_librarypanel)
        return m_librarypanel->OnUndo();

    return false;
}

bool SwGuiPanel::OnRedo()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnRedo();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnRedo();
    else if (m_librarybook)
        return m_librarybook->OnRedo();
    else if (m_librarypanel)
        return m_librarypanel->OnRedo();

    return false;
}

bool SwGuiPanel::OnSelectAll()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSelectAll();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSelectAll();
    else if (m_librarybook)
        return m_librarybook->OnSelectAll();
    else if (m_librarypanel)
        return m_librarypanel->OnSelectAll();

    return false;
}

bool SwGuiPanel::OnAlignLeft()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnAlignLeft();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnAlignLeft();
    else if (m_librarybook)
        return m_librarybook->OnAlignLeft();
    else if (m_librarypanel)
        return m_librarypanel->OnAlignLeft();

    return false;
}

bool SwGuiPanel::OnAlignCenter()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnAlignCenter();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnAlignCenter();
    else if (m_librarybook)
        return m_librarybook->OnAlignCenter();
    else if (m_librarypanel)
        return m_librarypanel->OnAlignCenter();

    return false;
}

bool SwGuiPanel::OnAlignRight()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnAlignRight();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnAlignRight();
    else  if (m_librarybook)
        return m_librarybook->OnAlignRight();
    else if (m_librarypanel)
        return m_librarypanel->OnAlignRight();

    return false;
}

bool SwGuiPanel::OnBold()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnBold();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnBold();
    else if (m_librarybook)
        return m_librarybook->OnBold();
    else if (m_librarypanel)
        return m_librarypanel->OnBold();

    return false;
}

bool SwGuiPanel::OnItalic()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnItalic();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnItalic();
    else if (m_librarybook)
        return m_librarybook->OnItalic();
    else if (m_librarypanel)
        return m_librarypanel->OnItalic();

    return false;
}

bool SwGuiPanel::OnUnderline()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnUnderline();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnUnderline();
    else if (m_librarybook)
        return m_librarybook->OnUnderline();
    else if (m_librarypanel)
        return m_librarypanel->OnUnderline();

    return false;
}

bool SwGuiPanel::OnStrikeThrough()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnStrikeThrough();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnStrikeThrough();
    else if (m_librarybook)
        return m_librarybook->OnStrikeThrough();
    else if (m_librarypanel)
        return m_librarypanel->OnStrikeThrough();

    return false;
}

bool SwGuiPanel::OnSuperScript()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSuperScript();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSuperScript();
    else if (m_librarybook)
        return m_librarybook->OnSuperScript();
    else if (m_librarypanel)
        return m_librarypanel->OnSuperScript();

    return false;
}

bool SwGuiPanel::OnSubScript()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSubScript();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSubScript();
    else if (m_librarybook)
        return m_librarybook->OnSubScript();
    else if (m_librarypanel)
        return m_librarypanel->OnSubScript();

    return false;
}

bool SwGuiPanel::OnIndentMore()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnIndentMore();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnIndentMore();
    else if (m_librarybook)
        return m_librarybook->OnIndentMore();
    else if (m_librarypanel)
        return m_librarypanel->OnIndentMore();

    return false;
}

bool SwGuiPanel::OnIndentLess()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnIndentLess();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnIndentLess();
    else if (m_librarybook)
        return m_librarybook->OnIndentLess();
    else if (m_librarypanel)
        return m_librarypanel->OnIndentLess();

    return false;
}

bool SwGuiPanel::OnSingleSpacing()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSingleSpacing();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSingleSpacing();
    else if (m_librarybook)
        return m_librarybook->OnSingleSpacing();
    else if (m_librarypanel)
        return m_librarypanel->OnSingleSpacing();

    return false;
}

bool SwGuiPanel::OnDoubleSpacing()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnDoubleSpacing();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnDoubleSpacing();
    else if (m_librarybook)
        return m_librarybook->OnDoubleSpacing();
    else if (m_librarypanel)
        return m_librarypanel->OnDoubleSpacing();

    return false;
}

bool SwGuiPanel::OnMargins()
{
   if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnMargins();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnMargins();
    else if (m_librarybook)
        return m_librarybook->OnMargins();
    else if (m_librarypanel)
        return m_librarypanel->OnMargins();

    return false;
}

bool SwGuiPanel::OnFont()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFont();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFont();
    else if (m_librarybook)
        return m_librarybook->OnFont();
    else if (m_librarypanel)
        return m_librarypanel->OnFont();

    return false;
}

bool SwGuiPanel::OnColor()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnColor();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnColor();
    else if (m_librarybook)
        return m_librarybook->OnColor();
    else if (m_librarypanel)
        return m_librarypanel->OnColor();

    return false;
}

bool SwGuiPanel::OnBackgroundColor()
{
   if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnBackgroundColor();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnBackgroundColor();
    else if (m_librarybook)
        return m_librarybook->OnBackgroundColor();
    else if (m_librarypanel)
        return m_librarypanel->OnBackgroundColor();

    return false;
}

bool SwGuiPanel::OnStyle()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnStyle();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnStyle();
    else  if (m_librarybook)
        return m_librarybook->OnStyle();
    else if (m_librarypanel)
        return m_librarypanel->OnStyle();

    return false;
}

bool SwGuiPanel::OnInsertImage()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertImage();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertImage();
    else if (m_librarybook)
        return m_librarybook->OnInsertImage();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertImage();

    return false;
}

bool SwGuiPanel::OnInsertLink()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertLink();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertLink();
    else if (m_librarybook)
        return m_librarybook->OnInsertLink();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertLink();

    return false;
}

bool SwGuiPanel::OnInsertAnchor()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertAnchor();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertAnchor();
    else if (m_librarybook)
        return m_librarybook->OnInsertAnchor();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertAnchor();

    return false;
}

bool SwGuiPanel::OnInsertTable()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertTable();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertTable();
    else  if (m_librarybook)
        return m_librarybook->OnInsertTable();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertTable();

    return false;
}

bool SwGuiPanel::OnInsertRow()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertRow();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertRow();
    else if (m_librarybook)
        return m_librarybook->OnInsertRow();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertRow();

    return false;
}

bool SwGuiPanel::OnInsertColumn()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertColumn();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertColumn();
    else if (m_librarybook)
        return m_librarybook->OnInsertColumn();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertColumn();

    return false;
}

bool SwGuiPanel::OnDeleteRow()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnDeleteRow();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnDeleteRow();
    else if (m_librarybook)
        return m_librarybook->OnDeleteRow();
    else if (m_librarypanel)
        return m_librarypanel->OnDeleteRow();

    return false;
}

bool SwGuiPanel::OnDeleteColumn()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnDeleteColumn();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnDeleteColumn();
    else  if (m_librarybook)
        return m_librarybook->OnDeleteColumn();
    else if (m_librarypanel)
        return m_librarypanel->OnDeleteColumn();

    return false;
}

bool SwGuiPanel::OnInsertControl()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertControl();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertControl();
    else if (m_librarybook)
        return m_librarybook->OnInsertControl();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertControl();

    return false;
}

bool SwGuiPanel::OnInsertHorizontalRule()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnInsertHorizontalRule();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnInsertHorizontalRule();
    else if (m_librarybook)
        return m_librarybook->OnInsertHorizontalRule();
    else if (m_librarypanel)
        return m_librarypanel->OnInsertHorizontalRule();

    return false;
}

bool SwGuiPanel::OnAlphaList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnAlphaList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnAlphaList();
    else if (m_librarybook)
        return m_librarybook->OnAlphaList();
    else if (m_librarypanel)
        return m_librarypanel->OnAlphaList();

    return false;
}

bool SwGuiPanel::OnBulletedList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnBulletedList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnBulletedList();
    else if (m_librarybook)
        return m_librarybook->OnBulletedList();
    else if (m_librarypanel)
        return m_librarypanel->OnBulletedList();

    return false;
}

bool SwGuiPanel::OnRomanList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnRomanList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnRomanList();
    else if (m_librarybook)
        return m_librarybook->OnRomanList();
    else if (m_librarypanel)
        return m_librarypanel->OnRomanList();

    return false;
}

bool SwGuiPanel::OnDecimalList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnDecimalList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnDecimalList();
    else  if (m_librarybook)
        return m_librarybook->OnDecimalList();
    else if (m_librarypanel)
        return m_librarypanel->OnDecimalList();

    return false;
}

bool SwGuiPanel::OnProperties()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnProperties();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnProperties();
    else if (m_librarybook)
        return m_librarybook->OnProperties();
    else if (m_librarypanel)
        return m_librarypanel->OnProperties();

    return false;
}

bool SwGuiPanel::OnZoomIn()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnZoomIn();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnZoomIn();
    else if (m_librarybook)
        return m_librarybook->OnZoomIn();
    else if (m_librarypanel)
        return m_librarypanel->OnZoomIn();

    return false;
}

bool SwGuiPanel::OnZoomOut()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnZoomOut();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnZoomOut();
    else  if (m_librarybook)
        return m_librarybook->OnZoomOut();
    else if (m_librarypanel)
        return m_librarypanel->OnZoomOut();

    return false;
}

bool SwGuiPanel::OnViewNormal()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnViewNormal();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnViewNormal();
    else if (m_librarybook)
        return m_librarybook->OnViewNormal();
    else if (m_librarypanel)
        return m_librarypanel->OnViewNormal();

    return false;
}

bool SwGuiPanel::OnContentsUp()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnContentsUp();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnContentsUp();
    else if (m_librarybook)
        return m_librarybook->OnContentsUp();
    else if (m_librarypanel)
        return m_librarypanel->OnContentsUp();

    return false;
}

bool SwGuiPanel::OnContentsDown()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnContentsDown();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnContentsDown();
    else if (m_librarybook)
        return m_librarybook->OnContentsDown();
    else if (m_librarypanel)
        return m_librarypanel->OnContentsDown();

    return false;
}

bool SwGuiPanel::OnHistoryBack()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnHistoryBack();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnHistoryBack();
    else if (m_librarybook)
        return m_librarybook->OnHistoryBack();
    else if (m_librarypanel)
        return m_librarypanel->OnHistoryBack();

    return false;
}

bool SwGuiPanel::OnHistoryForward()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnHistoryForward();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnHistoryForward();
    else if (m_librarybook)
        return m_librarybook->OnHistoryForward();
    else if (m_librarypanel)
        return m_librarypanel->OnHistoryForward();

    return false;
}

bool SwGuiPanel::OnBookMarkPage()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnBookMarkPage();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnBookMarkPage();
    else  if (m_librarybook)
        return m_librarybook->OnBookMarkPage();
    else if (m_librarypanel)
        return m_librarypanel->OnBookMarkPage();

    return false;
}

bool SwGuiPanel::OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFind(text, casesensitive, wholewordonly);
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFind(text, casesensitive, wholewordonly);
    else  if (m_librarybook)
        return m_librarybook->OnFind(text, casesensitive, wholewordonly);
    else if (m_librarypanel)
        return m_librarypanel->OnFind(text, casesensitive, wholewordonly);

    return false;
}

bool SwGuiPanel::OnFindReset()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFindReset();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFindReset();
    else if (m_librarybook)
        return m_librarybook->OnFindReset();
    else if (m_librarypanel)
        return m_librarypanel->OnFindReset();

    return false;
}

bool SwGuiPanel::OnFindNext()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFindNext();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFindNext();
    else if (m_librarybook)
        return m_librarybook->OnFindNext();
    else if (m_librarypanel)
        return m_librarypanel->OnFindNext();

    return false;
}

bool SwGuiPanel::OnReplace()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnReplace();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnReplace();
    else if (m_librarybook)
        return m_librarybook->OnReplace();
    else if (m_librarypanel)
        return m_librarypanel->OnReplace();

    return false;
}

bool SwGuiPanel::OnReplaceAll()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnReplaceAll();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnReplaceAll();
    else  if (m_librarybook)
        return m_librarybook->OnReplaceAll();
    else if (m_librarypanel)
        return m_librarypanel->OnReplaceAll();

    return false;
}

bool SwGuiPanel::OnLibraryView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnLibraryView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnLibraryView();
    else if (m_librarybook)
        return m_librarybook->OnLibraryView();
    else if (m_librarypanel)
        return m_librarypanel->OnLibraryView();

    return false;
}

bool SwGuiPanel::OnContentsView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnContentsView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnContentsView();
    else if (m_librarybook)
        return m_librarybook->OnContentsView();
    else if (m_librarypanel)
        return m_librarypanel->OnContentsView();

    return false;
}

bool SwGuiPanel::OnSearchView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnSearchView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnSearchView();
    else if (m_librarybook)
        return m_librarybook->OnSearchView();
    else if (m_librarypanel)
        return m_librarypanel->OnSearchView();

    return false;
}

bool SwGuiPanel::OnFindView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFindView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFindView();
    else if (m_librarybook)
        return m_librarybook->OnFindView();
    else if (m_librarypanel)
        return m_librarypanel->OnFindView();

    return false;
}

bool SwGuiPanel::OnBookmarksView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnBookmarksView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnBookmarksView();
    else if (m_librarybook)
        return m_librarybook->OnBookmarksView();
    else if (m_librarypanel)
        return m_librarypanel->OnBookmarksView();

    return false;
}

bool SwGuiPanel::OnHistoryView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnHistoryView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnHistoryView();
    else if (m_librarybook)
        return m_librarybook->OnHistoryView();
    else if (m_librarypanel)
        return m_librarypanel->OnHistoryView();

    return false;
}

bool SwGuiPanel::OnPlay()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnPlay();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnPlay();
    else if (m_librarybook)
        return m_librarybook->OnPlay();
    else if (m_librarypanel)
        return m_librarypanel->OnPlay();

    return false;
}

bool SwGuiPanel::OnPause()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnPause();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnPause();
    else  if (m_librarybook)
        return m_librarybook->OnPause();
    else if (m_librarypanel)
        return m_librarypanel->OnPause();

    return false;
}

bool SwGuiPanel::OnStop()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnStop();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnStop();
    else if (m_librarybook)
        return m_librarybook->OnStop();
    else if (m_librarypanel)
        return m_librarypanel->OnStop();

    return false;
}

bool SwGuiPanel::OnRewind()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnRewind();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnRewind();
    else if (m_librarybook)
        return m_librarybook->OnRewind();
    else if (m_librarypanel)
        return m_librarypanel->OnRewind();

    return false;
}

bool SwGuiPanel::OnFastForward()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnFastForward();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnFastForward();
    else if (m_librarybook)
        return m_librarybook->OnFastForward();
    else if (m_librarypanel)
        return m_librarypanel->OnFastForward();

    return false;
}

bool SwGuiPanel::OnPrevious()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnPrevious();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnPrevious();
    else if (m_librarybook)
        return m_librarybook->OnPrevious();
    else if (m_librarypanel)
        return m_librarypanel->OnPrevious();

    return false;
}

bool SwGuiPanel::OnNext()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnNext();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnNext();
    else if (m_librarybook)
        return m_librarybook->OnNext();
    else if (m_librarypanel)
        return m_librarypanel->OnNext();

    return false;
}

bool SwGuiPanel::OnPreferences()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        m_librarybook->OnPreferences();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        m_librarypanel->OnPreferences();
    else if (m_librarybook)
        m_librarybook->OnPreferences();
    else if (m_librarypanel)
        m_librarypanel->OnPreferences();

    return false;
}

bool SwGuiPanel::OnHelpContents()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        m_librarybook->OnHelpContents();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        m_librarypanel->OnHelpContents();
    else if (m_librarybook)
        m_librarybook->OnHelpContents();
    else if (m_librarypanel)
        m_librarypanel->OnHelpContents();

    return false;
}

bool SwGuiPanel::OnAbout()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        m_librarybook->OnAbout();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        m_librarypanel->OnAbout();
    else if (m_librarybook)
        m_librarybook->OnAbout();
    else if (m_librarypanel)
        m_librarypanel->OnAbout();

    return false;
}

bool SwGuiPanel::OnUpdateSoftware()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        m_librarybook->OnUpdateSoftware();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        m_librarypanel->OnUpdateSoftware();
    else if (m_librarybook)
        m_librarybook->OnUpdateSoftware();
    else if (m_librarypanel)
        m_librarypanel->OnUpdateSoftware();

    return false;
}

// false - language, true - theme
void SwGuiPanel::NotifyChildren(bool change)
{
    for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
    {
        NotifyChildren(*it, change);
    }
}

void SwGuiPanel::NotifyChildren(wxWindow * window, bool change)
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
    else if (window->IsKindOf(CLASSINFO(SwGuiPanel)))
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

void SwGuiPanel::OnLanguageChangeBase()
{
    OnLanguageChange();
    NotifyChildren(false);
}

void SwGuiPanel::OnThemeChangeBase()
{
    OnThemeChange();
    NotifyChildren(false);
}

void SwGuiPanel::OnFontSizeChange(const wxFont & font)
{
    SetFont(font);
}

void SwGuiPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
}

bool SwGuiPanel::OnHasSelection()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnHasSelection();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnHasSelection();
    else if (m_librarybook)
        return m_librarybook->OnHasSelection();
    else if (m_librarypanel)
        return m_librarypanel->OnHasSelection();

    return false;
}

void SwGuiPanel::OnModuleManagerReset()
{
    if (m_librarybook)
        return m_librarybook->OnModuleManagerReset();

    if (m_librarypanel)
        return m_librarypanel->OnModuleManagerReset();
}

void SwGuiPanel::OnThMLFileManagerReset()
{
    if (m_librarybook)
        return m_librarybook->OnThMLFileManagerReset();

    if (m_librarypanel)
        return m_librarypanel->OnThMLFileManagerReset();
}

void SwGuiPanel::OnModuleManagerLoaded()
{
    if (m_librarybook)
        return m_librarybook->OnModuleManagerLoaded();

    if (m_librarypanel)
        return m_librarypanel->OnModuleManagerLoaded();
}

void SwGuiPanel::OnThMLFileManagerLoaded()
{
    if (m_librarybook)
        return m_librarybook->OnThMLFileManagerLoaded();

    if (m_librarypanel)
        return m_librarypanel->OnThMLFileManagerLoaded();
}

void SwGuiPanel::OnModuleAdded(swUI16 mid)
{
    if (m_librarybook)
        return m_librarybook->OnModuleAdded(mid);

    if (m_librarypanel)
        return m_librarypanel->OnModuleAdded(mid);
}

void SwGuiPanel::OnModuleDeleted(swUI16 mid)
{
    if (m_librarybook)
        return m_librarybook->OnModuleDeleted(mid);

    if (m_librarypanel)
        return m_librarypanel->OnModuleDeleted(mid);
}

void SwGuiPanel::OnThMLFileAdded(swUI16 mid)
{
    if (m_librarybook)
        return m_librarybook->OnThMLFileAdded(mid);

    if (m_librarypanel)
        return m_librarypanel->OnThMLFileAdded(mid);
}


void SwGuiPanel::OnThMLFileDeleted(swUI16 mid)
{
    if (m_librarybook)
        return m_librarybook->OnThMLFileDeleted(mid);

    if (m_librarypanel)
        return m_librarypanel->OnThMLFileDeleted(mid);
}

bool SwGuiPanel::OnCanDoNew()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoNew();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoNew();
    else if (m_librarybook)
        return m_librarybook->OnCanDoNew();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoNew();

    return false;
}

bool SwGuiPanel::OnCanDoOpen()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoOpen();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoOpen();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoOpen();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoOpen();

    return false;
}

bool SwGuiPanel::OnCanDoSave()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoSave();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoSave();
    else if (m_librarybook)
        return m_librarybook->OnCanDoSave();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoSave();

    return false;
}

bool SwGuiPanel::OnCanDoSaveAs()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoSaveAs();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoSaveAs();
    else if (m_librarybook)
        return m_librarybook->OnCanDoSaveAs();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoSaveAs();

    return false;
}

bool SwGuiPanel::OnCanDoClose()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoClose();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoClose();
    else if (m_librarybook)
        return m_librarybook->OnCanDoClose();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoClose();

    return false;
}

bool SwGuiPanel::OnCanDoCloseAll()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoCloseAll();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoCloseAll();
    else if (m_librarybook)
        return m_librarybook->OnCanDoCloseAll();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoCloseAll();

    return false;
}

bool SwGuiPanel::OnCanDoPrint()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoPrint();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoPrint();
    else if (m_librarybook)
        return m_librarybook->OnCanDoPrint();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoPrint();

    return false;
}

bool SwGuiPanel::OnCanDoPrintPreview()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoPrintPreview();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoPrintPreview();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoPrintPreview();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoPrintPreview();

    return false;
}

bool SwGuiPanel::OnCanDoBookMarkPage()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoBookMarkPage();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoBookMarkPage();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoBookMarkPage();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoBookMarkPage();

    return false;
}

bool SwGuiPanel::OnCanDoFind()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoFind();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoFind();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoFind();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoFind();

    return false;
}

bool SwGuiPanel::OnCanDoFindNext()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoFindNext();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoFindNext();
    else if (m_librarybook)
        return m_librarybook->OnCanDoFindNext();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoFindNext();

    return false;
}

bool SwGuiPanel::OnCanDoReplace()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoReplace();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoReplace();
    else if (m_librarybook)
        return m_librarybook->OnCanDoReplace();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoReplace();

    return false;
}

bool SwGuiPanel::OnCanDoClear()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoClear();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoClear();
    else if (m_librarybook)
        return m_librarybook->OnCanDoClear();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoClear();

    return false;
}

bool SwGuiPanel::OnCanDoCut()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoCut();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoCut();
    else if (m_librarybook)
        return m_librarybook->OnCanDoCut();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoCut();

    return false;
}

bool SwGuiPanel::OnCanDoCopy()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoCopy();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoCopy();
    else if (m_librarybook)
        return m_librarybook->OnCanDoCopy();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoCopy();

    return false;
}

bool SwGuiPanel::OnCanDoPaste()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoPaste();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoPaste();
    else if (m_librarybook)
        return m_librarybook->OnCanDoPaste();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoPaste();

    return false;
}

bool SwGuiPanel::OnCanDoUndo()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoUndo();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoUndo();
    else if (m_librarybook)
        return m_librarybook->OnCanDoUndo();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoUndo();

    return false;
}

bool SwGuiPanel::OnCanDoRedo()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoRedo();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoRedo();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoRedo();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoRedo();

    return false;
}

bool SwGuiPanel::OnCanDoSelectAll()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoSelectAll();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoSelectAll();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoSelectAll();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoSelectAll();

    return false;
}

bool SwGuiPanel::OnCanDoProperties()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoProperties();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoProperties();
    else if (m_librarybook)
        return m_librarybook->OnCanDoProperties();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoProperties();

    return false;
}

bool SwGuiPanel::HasLibraryView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->HasLibraryView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->HasLibraryView();
    else if (m_librarybook)
        return m_librarybook->HasLibraryView();
    else if (m_librarypanel)
        return m_librarypanel->HasLibraryView();

    return false;
}

bool SwGuiPanel::HasContentsView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->HasContentsView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->HasContentsView();
    else if (m_librarybook)
        return m_librarybook->HasContentsView();
    else if (m_librarypanel)
        return m_librarypanel->HasContentsView();

    return false;
}

bool SwGuiPanel::HasBookmarksView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->HasBookmarksView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->HasBookmarksView();
    else if (m_librarybook)
        return m_librarybook->HasBookmarksView();
    else if (m_librarypanel)
        return m_librarypanel->HasBookmarksView();

    return false;
}

bool SwGuiPanel::HasFindView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->HasFindView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->HasFindView();
    else if (m_librarybook)
        return m_librarybook->HasFindView();
    else if (m_librarypanel)
        return m_librarypanel->HasFindView();

    return false;
}

bool SwGuiPanel::HasSearchView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->HasSearchView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->HasSearchView();
    else if (m_librarybook)
        return m_librarybook->HasSearchView();
    else if (m_librarypanel)
        return m_librarypanel->HasSearchView();

    return false;
}

bool SwGuiPanel::HasHistoryView()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->HasHistoryView();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->HasHistoryView();
    else if (m_librarybook)
        return m_librarybook->HasHistoryView();
    else if (m_librarypanel)
        return m_librarypanel->HasHistoryView();

    return false;
}

bool SwGuiPanel::OnCanDoZoomIn()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoZoomIn();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoZoomIn();
    else if (m_librarybook)
        return m_librarybook->OnCanDoZoomIn();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoZoomIn();

    return false;
}

bool SwGuiPanel::OnCanDoZoomOut()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoZoomOut();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoZoomOut();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoZoomOut();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoZoomOut();

    return false;
}

bool SwGuiPanel::OnCanDoViewNormal()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoViewNormal();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoViewNormal();
    else if (m_librarybook)
        return m_librarybook->OnCanDoViewNormal();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoViewNormal();

    return false;
}

bool SwGuiPanel::OnCanDoUpInContents()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoUpInContents();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoUpInContents();
    else if (m_librarybook)
        return m_librarybook->OnCanDoUpInContents();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoUpInContents();

    return false;
}

bool SwGuiPanel::OnCanDoDownInContents()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoDownInContents();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoDownInContents();
    else if (m_librarybook)
        return m_librarybook->OnCanDoDownInContents();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoDownInContents();

    return false;
}

bool SwGuiPanel::OnCanDoBackInHistory()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoBackInHistory();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoBackInHistory();
    else if (m_librarybook)
        return m_librarybook->OnCanDoBackInHistory();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoBackInHistory();

    return false;
}

bool SwGuiPanel::OnCanDoForwardInHistory()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoForwardInHistory();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoForwardInHistory();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoForwardInHistory();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoForwardInHistory();

    return false;
}

bool SwGuiPanel::OnCanDoFont()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoFont();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoFont();
    else if (m_librarybook)
        return m_librarybook->OnCanDoFont();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoFont();

    return false;
}

bool SwGuiPanel::OnCanDoBold()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoBold();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoBold();
    else if (m_librarybook)
        return m_librarybook->OnCanDoBold();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoBold();

    return false;
}

bool SwGuiPanel::IsSelectionBold()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionBold();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionBold();
    else if (m_librarybook)
        return m_librarybook->IsSelectionBold();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionBold();

    return false;
}

bool SwGuiPanel::OnCanDoItalic()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoItalic();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoItalic();
    else if (m_librarybook)
        return m_librarybook->OnCanDoItalic();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoItalic();

    return false;
}

bool SwGuiPanel::IsSelectionItalic()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionItalic();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionItalic();
    else if (m_librarybook)
        return m_librarybook->IsSelectionItalic();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionItalic();

    return false;
}

bool SwGuiPanel::OnCanDoUnderline()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoUnderline();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoUnderline();
    else if (m_librarybook)
        return m_librarybook->OnCanDoUnderline();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoUnderline();

    return false;
}

bool SwGuiPanel::IsSelectionUnderline()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionUnderline();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionUnderline();
    else if (m_librarybook)
        return m_librarybook->IsSelectionUnderline();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionUnderline();

    return false;
}

bool SwGuiPanel::OnCanDoStrikeThrough()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoStrikeThrough();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoStrikeThrough();
    else if (m_librarybook)
        return m_librarybook->OnCanDoStrikeThrough();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoStrikeThrough();

    return false;
}

bool SwGuiPanel::IsSelectionStrikeThrough()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionStrikeThrough();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionStrikeThrough();
    else if (m_librarybook)
        return m_librarybook->IsSelectionStrikeThrough();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionStrikeThrough();

    return false;
}

bool SwGuiPanel::OnCanDoSuperScript()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoSuperScript();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoSuperScript();
    else if (m_librarybook)
        return m_librarybook->OnCanDoSuperScript();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoSuperScript();

    return false;
}

bool SwGuiPanel::IsSelectionSuperScript()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionSuperScript();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionSuperScript();
    else if (m_librarybook)
        return m_librarybook->IsSelectionSuperScript();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionSuperScript();

    return false;
}

bool SwGuiPanel::OnCanDoSubScript()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoSubScript();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoSubScript();
    else if (m_librarybook)
        return m_librarybook->OnCanDoSubScript();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoSubScript();

    return false;
}

bool SwGuiPanel::IsSelectionSubScript()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionSubScript();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionSubScript();
    else if (m_librarybook)
        return m_librarybook->IsSelectionSubScript();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionSubScript();

    return false;
}

bool SwGuiPanel::OnCanDoColor()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoColor();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoColor();
    else if (m_librarybook)
        return m_librarybook->OnCanDoColor();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoColor();

    return false;
}

bool SwGuiPanel::OnCanDoBackGroundColor()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoBackGroundColor();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoBackGroundColor();
    else if (m_librarybook)
        return m_librarybook->OnCanDoBackGroundColor();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoBackGroundColor();

    return false;
}

bool SwGuiPanel::OnCanDoStyle()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoStyle();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoStyle();
    else if (m_librarybook)
        return m_librarybook->OnCanDoStyle();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoStyle();

    return false;
}

bool SwGuiPanel::OnCanDoMargins()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoMargins();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoMargins();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoMargins();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoMargins();

    return false;
}

bool SwGuiPanel::OnCanDoIndentMore()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoIndentMore();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoIndentMore();
    else if (m_librarybook)
        return m_librarybook->OnCanDoIndentMore();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoIndentMore();

    return false;
}

bool SwGuiPanel::OnCanDoIndentLess()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoIndentLess();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoIndentLess();
    else if (m_librarybook)
        return m_librarybook->OnCanDoIndentLess();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoIndentLess();

    return false;
}

bool SwGuiPanel::OnCanDoAlignLeft()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoAlignLeft();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoAlignLeft();
    else if (m_librarybook)
        return m_librarybook->OnCanDoAlignLeft();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoAlignLeft();

    return false;
}

bool SwGuiPanel::IsSelectionAlignLeft()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionAlignLeft();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionAlignLeft();
    else if (m_librarybook)
        return m_librarybook->IsSelectionAlignLeft();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionAlignLeft();

    return false;
}

bool SwGuiPanel::OnCanDoAlignCenter()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoAlignCenter();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoAlignCenter();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoAlignCenter();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoAlignCenter();

    return false;
}

bool SwGuiPanel::IsSelectionAlignCenter()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionAlignCenter();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionAlignCenter();
    else if (m_librarybook)
        return m_librarybook->IsSelectionAlignCenter();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionAlignCenter();

    return false;
}

bool SwGuiPanel::OnCanDoAlignRight()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoAlignRight();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoAlignRight();
    else if (m_librarybook)
        return m_librarybook->OnCanDoAlignRight();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoAlignRight();

    return false;
}

bool SwGuiPanel::IsSelectionAlignRight()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionAlignRight();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionAlignRight();
    else if (m_librarybook)
        return m_librarybook->IsSelectionAlignRight();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionAlignRight();

    return false;
}

bool SwGuiPanel::OnCanDoSingleSpacing()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoSingleSpacing();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoSingleSpacing();
    else if (m_librarybook)
        return m_librarybook->OnCanDoSingleSpacing();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoSingleSpacing();

    return false;
}

bool SwGuiPanel::IsSelectionSingleSpacing()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionSingleSpacing();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionSingleSpacing();
    else if (m_librarybook)
        return m_librarybook->IsSelectionSingleSpacing();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionSingleSpacing();

    return false;
}

bool SwGuiPanel::OnCanDoDoubleSpacing()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoDoubleSpacing();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoDoubleSpacing();
    else if (m_librarybook)
        return m_librarybook->OnCanDoDoubleSpacing();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoDoubleSpacing();

    return false;
}

bool SwGuiPanel::IsSelectionDoubleSpacing()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionDoubleSpacing();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionDoubleSpacing();
    else if (m_librarybook)
        return m_librarybook->IsSelectionDoubleSpacing();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionDoubleSpacing();

    return false;
}

bool SwGuiPanel::OnCanDoAlphaList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoAlphaList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoAlphaList();
    else if (m_librarybook)
        return m_librarybook->OnCanDoAlphaList();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoAlphaList();

    return false;
}

bool SwGuiPanel::IsSelectionAlphaList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionAlphaList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionAlphaList();
    else if (m_librarybook)
        return m_librarybook->IsSelectionAlphaList();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionAlphaList();

    return false;
}

bool SwGuiPanel::OnCanDoBulletedList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoBulletedList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoBulletedList();
    else if (m_librarybook)
        return m_librarybook->OnCanDoBulletedList();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoBulletedList();

    return false;
}

bool SwGuiPanel::IsSelectionBulletedList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionBulletedList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionBulletedList();
    else if (m_librarybook)
        return m_librarybook->IsSelectionBulletedList();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionBulletedList();

    return false;
}

bool SwGuiPanel::OnCanDoRomanNumeralsList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoRomanNumeralsList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoRomanNumeralsList();
    else if (m_librarybook)
        return m_librarybook->OnCanDoRomanNumeralsList();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoRomanNumeralsList();

    return false;
}

bool SwGuiPanel::IsSelectionRomanNumeralsList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionRomanNumeralsList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionRomanNumeralsList();
    else if (m_librarybook)
        return m_librarybook->IsSelectionRomanNumeralsList();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionRomanNumeralsList();

    return false;
}

bool SwGuiPanel::OnCanDoDecimalList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoDecimalList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoDecimalList();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoDecimalList();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoDecimalList();

    return false;
}

bool SwGuiPanel::IsSelectionDecimalList()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->IsSelectionDecimalList();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->IsSelectionDecimalList();
    else if (m_librarybook)
        return m_librarybook->IsSelectionDecimalList();
    else if (m_librarypanel)
        return m_librarypanel->IsSelectionDecimalList();

    return false;
}

bool SwGuiPanel::OnCanDoInsertTable()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertTable();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertTable();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoInsertTable();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertTable();

    return false;
}

bool SwGuiPanel::OnCanDoInsertRow()
{
   if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertRow();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertRow();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoInsertRow();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertRow();

    return false;
}

bool SwGuiPanel::OnCanDoDeleteRow()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoDeleteRow();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoDeleteRow();
    else if (m_librarybook)
        return m_librarybook->OnCanDoDeleteRow();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoDeleteRow();

    return false;
}

bool SwGuiPanel::OnCanDoInsertColumn()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertColumn();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertColumn();
    else if (m_librarybook)
        return m_librarybook->OnCanDoInsertColumn();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertColumn();

    return false;
}

bool SwGuiPanel::OnCanDoDeleteColumn()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoDeleteColumn();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoDeleteColumn();
    else if (m_librarybook)
        return m_librarybook->OnCanDoDeleteColumn();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoDeleteColumn();

    return false;
}

bool SwGuiPanel::OnCanDoInsertImage()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertImage();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertImage();
    else if (m_librarybook)
        return m_librarybook->OnCanDoInsertImage();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertImage();

    return false;
}

bool SwGuiPanel::OnCanDoInsertLink()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertLink();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertLink();
    else if (m_librarybook)
        return m_librarybook->OnCanDoInsertLink();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertLink();

    return false;
}

bool SwGuiPanel::OnCanDoInsertAnchor()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertAnchor();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertAnchor();
    else if (m_librarybook)
        return m_librarybook->OnCanDoInsertAnchor();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertAnchor();

    return false;
}

bool SwGuiPanel::OnCanDoInsertControl()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertControl();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertControl();
    else if (m_librarybook)
        return m_librarybook->OnCanDoInsertControl();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertControl();

    return false;
}

bool SwGuiPanel::OnCanDoInsertHorizontalRule()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoInsertHorizontalRule();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoInsertHorizontalRule();
    else if (m_librarybook)
        return m_librarybook->OnCanDoInsertHorizontalRule();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoInsertHorizontalRule();

    return false;
}

bool SwGuiPanel::OnCanDoPlay()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoPlay();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoPlay();
    else if (m_librarybook)
        return m_librarybook->OnCanDoPlay();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoPlay();

    return false;
}

bool SwGuiPanel::OnCanDoPause()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoPause();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoPause();
    else if (m_librarybook)
        return m_librarybook->OnCanDoPause();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoPause();

    return false;
}

bool SwGuiPanel::OnCanDoStop()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoStop();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoStop();
    else if (m_librarybook)
        return m_librarybook->OnCanDoStop();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoStop();

    return false;
}

bool SwGuiPanel::OnCanDoRewind()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoRewind();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoRewind();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoRewind();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoRewind();

    return false;
}

bool SwGuiPanel::OnCanDoFastForward()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoFastForward();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoFastForward();
    else if (m_librarybook)
        return m_librarybook->OnCanDoFastForward();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoFastForward();

    return false;
}

bool SwGuiPanel::OnCanDoPrevious()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoPrevious();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoPrevious();
    else if (m_librarybook)
        return m_librarybook->OnCanDoPrevious();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoPrevious();

    return false;
}

bool SwGuiPanel::OnCanDoNext()
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->OnCanDoNext();
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->OnCanDoNext();
    else  if (m_librarybook)
        return m_librarybook->OnCanDoNext();
    else if (m_librarypanel)
        return m_librarypanel->OnCanDoNext();

    return false;
}

bool SwGuiPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->ActivateBookMark(data, ctrlid);
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->ActivateBookMark(data, ctrlid);
    else if (m_librarybook)
        return m_librarybook->ActivateBookMark(data, ctrlid);
    else if (m_librarypanel)
        return m_librarypanel->ActivateBookMark(data, ctrlid);

    return false;
}

bool SwGuiPanel::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_librarybook)
        return m_librarybook->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
    else if (m_librarypanel)
        return m_librarypanel->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);

    return false;
}

bool SwGuiPanel::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (m_librarybook && m_librarybook->OnHasFocus())
        return m_librarybook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_librarypanel && m_librarypanel->OnHasFocus())
        return m_librarypanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_librarybook)
        return m_librarybook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
    else if (m_librarypanel)
        return m_librarypanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);

    return false;
}

bool SwGuiPanel::LoadLibraryItem(const char * path)
{
    if (m_librarypanel)
        return m_librarypanel->LoadLibraryItem(path);

    return false;
}

bool SwGuiPanel::LoadLibraryItem(swUI16 managerId)
{
    if (m_librarypanel)
        return m_librarypanel->LoadLibraryItem(managerId);

    return false;
}

bool SwGuiPanel::SelectTab(const char * path)
{
    if (!m_librarybook)
        return false;

    swUI32 id = m_librarybook->FindFile(path);
    if (id != NODE_ID_INVALID)
    {
        m_librarybook->ChangeSelection(id);
        return true;
    }

    return false;
}


bool SwGuiPanel::OnHasFocus()
{
    if (HasFocus())
        return true;

    for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
    {
        if ((*it)->HasFocus())
            return true;

        if (HasChildWithFocus(*it))
            return true;
    }

    return false;
}

bool SwGuiPanel::HasChildWithFocus(wxWindow * window)
{
    for ( wxWindowList::iterator it = window->GetChildren().begin(); it != window->GetChildren().end(); ++it )
    {
        if ((*it)->HasFocus())
            return true;

        if (HasChildWithFocus(*it))
            return true;
    }

    return false;
}

void SwGuiPanel::CreateStartUpFile(const char * name)
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

    f.Write((void *)".", 1, 1);
    f.Close();
}

void SwGuiPanel::DeleteStartUpFile(const char * name)
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

bool SwGuiPanel::CheckStartUpFile(const char * name)
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
