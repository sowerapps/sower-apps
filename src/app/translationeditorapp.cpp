///////////////////////////////////////////////////////////////////
// Name:        translationeditorapp.cpp
// Purpose:     Sower Translation Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/translationeditorapp.h"
#include "filesys/file.h"
#include "appi/appifa.h"
#include "language/language.h"
#include <wx/msgdlg.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerTranslationEditorApp);

bool SowerTranslationEditorApp::OnInit()
{
<<<<<<< Updated upstream
    bool wxsOK = true;
=======
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__
>>>>>>> Stashed changes

    SwApplicationInterface::InitBasic();

    SowerTranslationEditorFrame* Frame = new SowerTranslationEditorFrame(NULL, wxNewId(), L"");
    Frame->Show();
    SetTopWindow(Frame);

    return true;
}

const long SowerTranslationEditorFrame::ID_IDENTIFIERSSTATICTEXT = wxNewId();
const long SowerTranslationEditorFrame::ID_IDDELETEBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_IDTEXTCTRL = wxNewId();
const long SowerTranslationEditorFrame::ID_IDADDBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_STATICLINE1 = wxNewId();
const long SowerTranslationEditorFrame::ID_TABLESSTATICTEXT = wxNewId();
const long SowerTranslationEditorFrame::ID_LANGUAGECHOICE = wxNewId();
const long SowerTranslationEditorFrame::ID_TABLEDELETEBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_TABLEADDBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_TABLELOADBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_IDENTIFIERLISTVIEW = wxNewId();
const long SowerTranslationEditorFrame::ID_TRANSLATIONLISTVIEW = wxNewId();
const long SowerTranslationEditorFrame::ID_CURRENTSTATICTEXT = wxNewId();
const long SowerTranslationEditorFrame::ID_TABLESAVEBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_TABLECLOSEBTN = wxNewId();
const long SowerTranslationEditorFrame::ID_PANEL1 = wxNewId();
const long SowerTranslationEditorFrame::ID_TRANSLATIONTABLELISTVIEW = wxNewId();
const long SowerTranslationEditorFrame::ID_REFERENCETABLELISTVIEW = wxNewId();
const long SowerTranslationEditorFrame::ID_STATUSBAR1 = wxNewId();

SowerTranslationEditorFrame::SowerTranslationEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxGridBagSizer* GridBagSizer1;

    menuBar = new SwBasicEditorMenuBar(this);
    SetMenuBar(menuBar);

    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_PANEL1");

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    IdentifiersStaticText = new wxStaticText(Panel1, ID_IDENTIFIERSSTATICTEXT, SwApplicationInterface::GetControlString("SID_IDENTIFIERS", L"Identifiers"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERSSTATICTEXT");
    GridBagSizer1->Add(IdentifiersStaticText, wxGBPosition(0, 4), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    IdDeleteBtn = new wxButton(Panel1, ID_IDDELETEBTN, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDDELETEBTN");
    GridBagSizer1->Add(IdDeleteBtn, wxGBPosition(4, 5), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);

    IdTextCtrl = new wxTextCtrl(Panel1, ID_IDTEXTCTRL, L"SID_", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDTEXTCTRL");
    GridBagSizer1->Add(IdTextCtrl, wxGBPosition(3, 4), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);

    IdAddBtn = new wxButton(Panel1, ID_IDADDBTN, SwApplicationInterface::GetControlString("SID_ADD", L"Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDADDBTN");
    GridBagSizer1->Add(IdAddBtn, wxGBPosition(4, 4), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxDefaultPosition, wxSize(2,-1), wxLI_VERTICAL, L"ID_STATICLINE1");
    GridBagSizer1->Add(StaticLine1, wxGBPosition(0, 3), wxGBSpan(6, 1), wxALL|wxEXPAND, 5);

    TablesStaticText = new wxStaticText(Panel1, ID_TABLESSTATICTEXT, SwApplicationInterface::GetControlString("SID_TABLES", L"Tables"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TABLESSTATICTEXT");
    GridBagSizer1->Add(TablesStaticText, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    LanguageChoice = new wxChoice(Panel1, ID_LANGUAGECHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, wxCB_SORT, wxDefaultValidator, L"ID_LANGUAGECHOICE");
    GridBagSizer1->Add(LanguageChoice, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);

    TableDeleteBtn = new wxButton(Panel1, ID_TABLEDELETEBTN, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLEDELETEBTN");
    GridBagSizer1->Add(TableDeleteBtn, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableAddBtn = new wxButton(Panel1, ID_TABLEADDBTN, SwApplicationInterface::GetControlString("SID_ADD", L"Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLEADDBTN");
    GridBagSizer1->Add(TableAddBtn, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableLoadBtn = new wxButton(Panel1, ID_TABLELOADBTN, SwApplicationInterface::GetControlString("SID_LOAD", L"Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLELOADBTN");
    GridBagSizer1->Add(TableLoadBtn, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    IdentifierList = new SwStretchColumnListView(Panel1, ID_IDENTIFIERLISTVIEW, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING, wxDefaultValidator, L"ID_IDENTIFIERLISTVIEW");
    GridBagSizer1->Add(IdentifierList, wxGBPosition(1, 4), wxGBSpan(2, 3), wxALL|wxEXPAND, 5);

    TranslationList = new SwStretchColumnListView(Panel1, ID_TRANSLATIONLISTVIEW, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING, wxDefaultValidator, L"ID_TRANSLATIONLISTVIEW");
    GridBagSizer1->Add(TranslationList, wxGBPosition(1, 0), wxGBSpan(2, 3), wxALL|wxEXPAND, 5);

    CurrentStaticText = new wxStaticText(Panel1, ID_CURRENTSTATICTEXT, SwApplicationInterface::GetControlString("SID_CURRENTTABLE", L"Current Table"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CURRENTSTATICTEXT");
    GridBagSizer1->Add(CurrentStaticText, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    TableSaveBtn = new wxButton(Panel1, ID_TABLESAVEBTN, SwApplicationInterface::GetControlString("SID_SAVE", L"Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLESAVEBTN");
    GridBagSizer1->Add(TableSaveBtn, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableCloseBtn = new wxButton(Panel1, ID_TABLECLOSEBTN, SwApplicationInterface::GetControlString("SID_CLOSE", L"Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLECLOSEBTN");
    GridBagSizer1->Add(TableCloseBtn, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    Panel1->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(Panel1);
    GridBagSizer1->SetSizeHints(Panel1);

    m_manager->AddPane(Panel1, wxAuiPaneInfo().Name(L"ToolPane").DefaultPane().Caption(SwApplicationInterface::GetControlString("SID_EDIT", L"Edit")).CaptionVisible().CloseButton(false).Bottom().DockFixed().FloatingSize(wxSize(-1,-1)).Resizable(false).Position(0));
    TranslationTable = new wxListView(this, ID_TRANSLATIONTABLELISTVIEW, wxPoint(371,204), wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_TRANSLATIONTABLELISTVIEW");
    m_manager->AddPane(TranslationTable, wxAuiPaneInfo().Name(L"TransLation Table").CenterPane().CaptionVisible());

    ReferenceTable = new wxListView(this, ID_REFERENCETABLELISTVIEW, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_REFERENCETABLELISTVIEW");
    m_manager->AddPane(ReferenceTable, wxAuiPaneInfo().Name(L"Reference").DefaultPane().Caption(L"English (US)").CaptionVisible().CloseButton(false).Bottom().Position(1));
    m_manager->Update();

    m_statusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, L"ID_STATUSBAR1");
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    m_statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    m_statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(m_statusBar);

    Connect(ID_IDDELETEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnIdDeleteBtnClick);
    Connect(ID_IDADDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnIdAddBtnClick);
    Connect(ID_TABLEDELETEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnTableDeleteBtnClick);
    Connect(ID_TABLEADDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnTableAddBtnClick);
    Connect(ID_TABLELOADBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnTableLoadBtnClick);
    Connect(ID_TABLESAVEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnTableSaveBtnClick);
    Connect(ID_TABLECLOSEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerTranslationEditorFrame::OnTableCloseBtnClick);

    SetIcon(SwApplicationInterface::GetToolsIcon());
    SwLanguage::FillCtrl(LanguageChoice, true);
    LanguageChoice->SetSelection(LanguageChoice->FindString("English (US)"));
    IdentifierList->wxListCtrl::AppendColumn("");
    TranslationList->wxListCtrl::AppendColumn("");
    TranslationTable->AppendColumn(SwApplicationInterface::GetControlString("SID_VALUE", L"Value"), wxLIST_FORMAT_LEFT, 300);
    TranslationTable->AppendColumn(SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxLIST_FORMAT_LEFT, 200);
    ReferenceTable->AppendColumn(SwApplicationInterface::GetControlString("SID_VALUE", L"Value"), wxLIST_FORMAT_LEFT, 200);
    ReferenceTable->AppendColumn(SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxLIST_FORMAT_LEFT, 100);

    EnableMenuItems(false);
    EnableIdentifierButtons(false);
    EnableLanguageButtons(false);
    EnableTableButtons(false);

    SwApplicationInterface::SetFrameWindow(this);
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERTRANSLATIONEDITOR", L"Sower Translation Editor"));
    Maximize();
}

SowerTranslationEditorFrame::~SowerTranslationEditorFrame()
{
    SwApplicationInterface::CloseFiles();
}

void SowerTranslationEditorFrame::OnQuit(wxCommandEvent& event)
{
    int status;

    if (TableSaveBtn->IsEnabled())
    {
        status = SwDialog::RequestSave(this);
        if (status == wxCANCEL)
            return;
        else if (status == wxYES)
        {
            OnTableSaveBtnClick(event);
        }
    }

    Close();
}

void SowerTranslationEditorFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERTRANSLATIONEDITOR", L"Sower Translation Editor"), SVSTR, L"2019");
}

void SowerTranslationEditorFrame::OnIdAddBtnClick(wxCommandEvent& event)
{
    swUI32 item;

    if (!IdTextCtrl->GetLineLength(0))
        return;

    if (IdentifierList->FindItem(-1, IdTextCtrl->GetLineText(0)) != wxNOT_FOUND)
    {
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_IDENTIFIERALREADYEXISTS", L"Identifier already exists.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return;
    }

    if (strcmp("SID_", IdTextCtrl->GetLineText(0).utf8_str()) == 0)
        return;

    IdentifierList->wxListCtrl::InsertItem(IdentifierList->GetItemCount(), IdTextCtrl->GetLineText(0));
    SwTable table;

    for (swUI32 i = 0; i < m_datafile.GetTableCount(); i ++)
    {
        m_datafile.FillTable(i, table);
        item = table.FindItemById(IdTextCtrl->GetLineText(0).utf8_str());

        if (item == NODE_ID_INVALID)
        {
            table.AppendNode(IdTextCtrl->GetLineText(0).utf8_str(), "");
            m_datafile.ReplaceTable(i, table);
        }
    }

    SwString buffer;
    SwDataFile::CreateDataListString(IdentifierList, buffer, "String Identifiers");
    m_datafile.ReplaceDataList("String Identifiers", buffer);
    FillReferenceTable();
    IdTextCtrl->SetValue("SID_");
}

void SowerTranslationEditorFrame::OnIdDeleteBtnClick(wxCommandEvent& event)
{
    long selected = IdentifierList->GetFocusedItem();
    swUI32 item;

    if (selected > -1)
    {
        SwTable table;

        for (swUI32 i = 0; i < m_datafile.GetTableCount(); i ++)
        {
            m_datafile.FillTable(i, table);
            item = table.FindItemById(IdentifierList->GetItemText(selected).utf8_str());

            if (item != NODE_ID_INVALID)
            {
                table.DeleteNode(item);
                m_datafile.ReplaceTable(i, table);
            }
        }

        IdentifierList->DeleteItem(IdentifierList->GetFocusedItem());
        FillReferenceTable();

        SwString buffer;
        SwDataFile::CreateDataListString(IdentifierList, buffer, "String Identifiers");
        m_datafile.ReplaceDataList("String Identifiers", buffer);
    }

}

void SowerTranslationEditorFrame::OnTableAddBtnClick(wxCommandEvent& event)
{
    if (LanguageChoice->GetSelection() != wxNOT_FOUND)
    {
        if (TranslationList->FindItem(0, LanguageChoice->GetStringSelection()) != -1)
        {
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_TABLEEXISTS", L"Table already exists.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
            return;
        }

        SwTable table;
        table.SetTableCaption(LanguageChoice->GetStringSelection().utf8_str());

        for (int i = 0; i < IdentifierList->GetItemCount(); i ++)
        {
            table.AppendNode(IdentifierList->GetItemText(i).utf8_str(), "");
        }

        m_datafile.AppendTable(table);
        TranslationList->wxListCtrl::InsertItem(TranslationList->GetItemCount(), LanguageChoice->GetStringSelection());
    }

    if (!ReferenceTable->GetItemCount())
        FillReferenceTable();
}

void SowerTranslationEditorFrame::OnTableDeleteBtnClick(wxCommandEvent& event)
{
    swUI32 node;
    int item = TranslationList->GetFocusedItem();

    if (item > -1)
    {
        if (strcmp("English (US)", TranslationList->GetItemText(item).utf8_str()) == 0)
            ReferenceTable->DeleteAllItems();

        node = m_datafile.FindTableByCaption(TranslationList->GetItemText(item).utf8_str());
        if (node != NODE_ID_INVALID)
        {
            m_datafile.DeleteTable(node);
            TranslationList->DeleteItem(item);
        }
    }
}

void SowerTranslationEditorFrame::OnTableLoadBtnClick(wxCommandEvent& event)
{
    swUI32 node;
    int item = TranslationList->GetFocusedItem();

    SwTable table;

    if (item > -1)
    {
        node = m_datafile.FindTableByCaption(TranslationList->GetItemText(item).utf8_str());
        if (node != NODE_ID_INVALID)
        {
            TranslationTable->DeleteAllItems();
            m_datafile.FillTable(node, table);
            table.FillCtrl(TranslationTable);
            m_manager->GetPane(TranslationTable).Caption(table.GetTableCaption());
            m_manager->Update();
            EnableIdentifierButtons(false);
            EnableTableButtons(true);
            TableLoadBtn->Enable(false);
        }
    }
}

void SowerTranslationEditorFrame::FillReferenceTable()
{
    ReferenceTable->DeleteAllItems();

    swUI32 node = m_datafile.FindTableByCaption("English (US)");

    SwTable table;

    if (node != NODE_ID_INVALID)
    {
        m_datafile.FillTable(node, table);
        table.FillCtrl(ReferenceTable);
    }
}

void SowerTranslationEditorFrame::OnTableSaveBtnClick(wxCommandEvent& event)
{
    SwTable table;

    table.Import(TranslationTable, m_manager->GetPane(TranslationTable).caption.utf8_str());
    swUI32 node = m_datafile.FindTableByCaption(m_manager->GetPane(TranslationTable).caption.utf8_str());

    if (node != NODE_ID_INVALID)
    {
        m_datafile.ReplaceTable(node, table);
    }

    if (strcmp("English (US)", m_manager->GetPane(TranslationTable).caption.utf8_str()) == 0)
    {
        FillReferenceTable();
    }

}

void SowerTranslationEditorFrame::OnTableCloseBtnClick(wxCommandEvent& event)
{
    int status;
    if (TableSaveBtn->IsEnabled())
    {
        status = SwDialog::RequestSave(this);
        if (status == wxCANCEL)
            return;
        else if (status == wxYES)
        {
            OnTableSaveBtnClick(event);
        }
    }

    TranslationTable->DeleteAllItems();
    EnableTableButtons(false);
    EnableIdentifierButtons(true);
    TableLoadBtn->Enable(true);
    m_manager->GetPane(TranslationTable).Caption("");
    m_manager->Update();
}

void SowerTranslationEditorFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog fileDlg(this, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTAFILE", L"Select a file")).GetArray(), "", "", SwStringW(SwApplicationInterface::GetControlString("SID_SDFFILTER", L"Sower data files (*.sdf)|*.sdf")).GetArray(), wxFD_OPEN);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (!m_datafile.OpenFile(fileDlg.GetPath().utf8_str(), true))
        return;

    m_statusBar->SetStatusText(fileDlg.GetPath().utf8_str());
    m_datafile.GetDataListItems(IdentifierList, "String Identifiers");
    m_datafile.FillCtrl(TranslationList);
    FillReferenceTable();

    EnableMenuItems(true);
    EnableIdentifierButtons(true);
    EnableLanguageButtons(true);
    menuBar->EnableOpen(false);
    menuBar->EnableNew(false);
}

void SowerTranslationEditorFrame::OnNew(wxCommandEvent& event)
{
    wxFileDialog fileDlg(this, SwStringW(SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as")).GetArray(), "", "", SwStringW(SwApplicationInterface::GetControlString("SID_SDFFILTER", L"Sower data files (*.sdf)|*.sdf")).GetArray(), wxFD_SAVE);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (!m_datafile.OpenFile(fileDlg.GetPath().utf8_str(), true))
        return;

    m_statusBar->SetStatusText(fileDlg.GetPath().utf8_str());
    m_datafile.GetDataListItems(IdentifierList, "String Identifiers");
    m_datafile.FillCtrl(TranslationList);
    FillReferenceTable();

    EnableMenuItems(true);
    EnableIdentifierButtons(true);
    EnableLanguageButtons(true);
    menuBar->EnableOpen(false);
    menuBar->EnableNew(false);
}

void SowerTranslationEditorFrame::OnClose(wxCommandEvent& event)
{
    int status;
    if (TableSaveBtn->IsEnabled())
    {
        status = SwDialog::RequestSave(this);
        if (status == wxCANCEL)
            return;
        else if (status == wxYES)
        {
            OnTableSaveBtnClick(event);
        }
    }

    m_statusBar->SetStatusText("");
    m_datafile.CloseFile();
    EnableMenuItems(false);
    EnableIdentifierButtons(false);
    EnableLanguageButtons(false);
    EnableTableButtons(false);
    Clear();
    menuBar->EnableOpen(true);
    menuBar->EnableNew(true);
}

void SowerTranslationEditorFrame::EnableLanguageButtons(bool state)
{
    TableDeleteBtn->Enable(state);
    TableAddBtn->Enable(state);
    TableLoadBtn->Enable(state);

    LanguageChoice->Enable(state);
    TranslationTable->Enable(state);
    TablesStaticText->Enable(state);
    CurrentStaticText->Enable(state);
    ReferenceTable->Enable(state);
}

void SowerTranslationEditorFrame::EnableIdentifierButtons(bool state)
{
    IdDeleteBtn->Enable(state);
    IdAddBtn->Enable(state);

    IdentifierList->Enable(state);
    IdTextCtrl->Enable(state);
    IdentifiersStaticText->Enable(state);
}

void SowerTranslationEditorFrame::EnableTableButtons(bool state)
{
    TableSaveBtn->Enable(state);
    TableCloseBtn->Enable(state);
    CurrentStaticText->Enable(state);
}

void SowerTranslationEditorFrame::EnableMenuItems(bool fileLoaded)
{
    menuBar->EnableItems(fileLoaded);
}

void SowerTranslationEditorFrame::Clear()
{
    TranslationList->DeleteAllItems();
    IdentifierList->DeleteAllItems();
    ReferenceTable->DeleteAllItems();
    TranslationTable->DeleteAllItems();
    m_manager->GetPane(TranslationTable).Caption("");
    m_manager->Update();
}
