///////////////////////////////////////////////////////////////////
// Name:        sdfeditorapp.cpp
// Purpose:     Sower Data File Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sdfeditorapp.h"
#include "filesys/file.h"
#include "appi/appifa.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerDataFileEditorApp);

bool SowerDataFileEditorApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();

    SowerDataFileEditorFrame* Frame = new SowerDataFileEditorFrame(NULL, wxNewId(), L"");
    Frame->Show();
    SetTopWindow(Frame);

    return true;
}

const long SowerDataFileEditorFrame::ID_TABLESSTATICTEXT = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLEDELETEBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLEADDBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLELOADBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLESLIST = wxNewId();
const long SowerDataFileEditorFrame::ID_CURRENTSTATICTEXT = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLESAVEBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLECLOSEBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLENAMETEXTCTRL = wxNewId();
const long SowerDataFileEditorFrame::ID_TABLESPANEL = wxNewId();
const long SowerDataFileEditorFrame::ID_IDENTIFIERSTATICTEXT = wxNewId();
const long SowerDataFileEditorFrame::ID_IDTEXTCTRL = wxNewId();
const long SowerDataFileEditorFrame::ID_DATASTATICTEXT = wxNewId();
const long SowerDataFileEditorFrame::ID_DATATEXTCTRL = wxNewId();
const long SowerDataFileEditorFrame::ID_P1STATICTEXT = wxNewId();
const long SowerDataFileEditorFrame::ID_P1TEXTCTRL = wxNewId();
const long SowerDataFileEditorFrame::ID_P2STATICTEXT = wxNewId();
const long SowerDataFileEditorFrame::ID_P2TEXTCTRL = wxNewId();
const long SowerDataFileEditorFrame::ID_ADDIDBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_DELETEIDBTN = wxNewId();
const long SowerDataFileEditorFrame::ID_IDENTIFIERPANEL = wxNewId();
const long SowerDataFileEditorFrame::ID_LISTVIEW1 = wxNewId();
const long SowerDataFileEditorFrame::ID_STATUSBAR1 = wxNewId();

SowerDataFileEditorFrame::SowerDataFileEditorFrame()
{
}

SowerDataFileEditorFrame::SowerDataFileEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxGridBagSizer* GridBagSizer1;
    wxGridBagSizer* GridBagSizer2;

    menuBar = new SwBasicEditorMenuBar(this);

    SetMenuBar(menuBar);

    TablesPanel = new wxPanel(this, ID_TABLESPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_TABLESPANEL");
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    TablesStaticText = new wxStaticText(TablesPanel, ID_TABLESSTATICTEXT, SwApplicationInterface::GetControlString("SID_TABLES", L"Tables"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TABLESSTATICTEXT");
    GridBagSizer1->Add(TablesStaticText, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableDeleteBtn = new wxButton(TablesPanel, ID_TABLEDELETEBTN, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLEDELETEBTN");
    GridBagSizer1->Add(TableDeleteBtn, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableAddBtn = new wxButton(TablesPanel, ID_TABLEADDBTN, SwApplicationInterface::GetControlString("SID_ADD", L"Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLEADDBTN");
    GridBagSizer1->Add(TableAddBtn, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableLoadBtn = new wxButton(TablesPanel, ID_TABLELOADBTN, SwApplicationInterface::GetControlString("SID_LOAD", L"Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLELOADBTN");
    GridBagSizer1->Add(TableLoadBtn, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableList = new SwStretchColumnListView(TablesPanel, ID_TABLESLIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING, wxDefaultValidator, L"ID_TABLESLIST");
    TableList->wxListCtrl::AppendColumn("");
    GridBagSizer1->Add(TableList, wxGBPosition(1, 0), wxGBSpan(2, 3), wxALL|wxEXPAND, 5);
    CurrentStaticText = new wxStaticText(TablesPanel, ID_CURRENTSTATICTEXT, SwApplicationInterface::GetControlString("SID_CURRENTTABLE", L"Current Table"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CURRENTSTATICTEXT");
    GridBagSizer1->Add(CurrentStaticText, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableSaveBtn = new wxButton(TablesPanel, ID_TABLESAVEBTN, SwApplicationInterface::GetControlString("SID_SAVE", L"Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLESAVEBTN");
    GridBagSizer1->Add(TableSaveBtn, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableCloseBtn = new wxButton(TablesPanel, ID_TABLECLOSEBTN, SwApplicationInterface::GetControlString("SID_CLOSE", L"Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLECLOSEBTN");
    GridBagSizer1->Add(TableCloseBtn, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TableNameTextCtrl = new wxTextCtrl(TablesPanel, ID_TABLENAMETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLENAMETEXTCTRL");
    GridBagSizer1->Add(TableNameTextCtrl, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    TablesPanel->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(TablesPanel);
    GridBagSizer1->SetSizeHints(TablesPanel);
    m_manager->AddPane(TablesPanel, wxAuiPaneInfo().Name(L"ToolPane").DefaultPane().Caption(SwApplicationInterface::GetControlString("SID_EDIT", L"Edit")).CaptionVisible().CloseButton(false).Bottom().DockFixed().FloatingSize(wxSize(-1,-1)).Resizable(false).Movable(false).Position(0));
    IdentifierPanel = new wxPanel(this, ID_IDENTIFIERPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_IDENTIFIERPANEL");
    GridBagSizer2 = new wxGridBagSizer(0, 0);
    IdentifierStaticText = new wxStaticText(IdentifierPanel, ID_IDENTIFIERSTATICTEXT, SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERSTATICTEXT");
    GridBagSizer2->Add(IdentifierStaticText, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdTextCtrl = new wxTextCtrl(IdentifierPanel, ID_IDTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDTEXTCTRL");
    GridBagSizer2->Add(IdTextCtrl, wxGBPosition(1, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    DataStaticText = new wxStaticText(IdentifierPanel, ID_DATASTATICTEXT, SwApplicationInterface::GetControlString("SID_DATA", L"Data"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DATASTATICTEXT");
    GridBagSizer2->Add(DataStaticText, wxGBPosition(2, 0), wxGBSpan(1, 3), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DataTextCtrl = new wxTextCtrl(IdentifierPanel, ID_DATATEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DATATEXTCTRL");
    GridBagSizer2->Add(DataTextCtrl, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    P1StaticText = new wxStaticText(IdentifierPanel, ID_P1STATICTEXT, SwApplicationInterface::GetControlString("SID_PARAMETER1", L"Parameter 1"), wxDefaultPosition, wxDefaultSize, 0, L"ID_P1STATICTEXT");
    GridBagSizer2->Add(P1StaticText, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    P1TextCtrl = new wxTextCtrl(IdentifierPanel, ID_P1TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_P1TEXTCTRL");
    GridBagSizer2->Add(P1TextCtrl, wxGBPosition(5, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    P2StaticText = new wxStaticText(IdentifierPanel, ID_P2STATICTEXT, SwApplicationInterface::GetControlString("SID_PARAMETER2", L"Parameter 2"), wxDefaultPosition, wxDefaultSize, 0, L"ID_P2STATICTEXT");
    GridBagSizer2->Add(P2StaticText, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT, 5);
    P2TextCtrl = new wxTextCtrl(IdentifierPanel, ID_P2TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_P2TEXTCTRL");
    GridBagSizer2->Add(P2TextCtrl, wxGBPosition(7, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    IdAddBtn = new wxButton(IdentifierPanel, ID_ADDIDBTN, SwApplicationInterface::GetControlString("SID_ADD", L"Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ADDIDBTN");
    GridBagSizer2->Add(IdAddBtn, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DeleteIdBtn = new wxButton(IdentifierPanel, ID_DELETEIDBTN, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DELETEIDBTN");
    GridBagSizer2->Add(DeleteIdBtn, wxGBPosition(8, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdentifierPanel->SetSizer(GridBagSizer2);
    GridBagSizer2->Fit(IdentifierPanel);
    GridBagSizer2->SetSizeHints(IdentifierPanel);
    m_manager->AddPane(IdentifierPanel, wxAuiPaneInfo().Name(L"ItemPane").DefaultPane().Caption(SwApplicationInterface::GetControlString("SID_ITEM", L"Item")).CaptionVisible().CloseButton(false).Bottom().DockFixed().Movable(false).Position(1));
    DataTable = new wxDataViewListCtrl(this, ID_LISTVIEW1, wxPoint(371,204), wxDefaultSize, wxDV_VERT_RULES, wxDefaultValidator);
    DataTable->AppendTextColumn(SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxDATAVIEW_CELL_EDITABLE);
    DataTable->AppendTextColumn(SwApplicationInterface::GetControlString("SID_DATA", L"Data"), wxDATAVIEW_CELL_EDITABLE);
    DataTable->AppendTextColumn(SwApplicationInterface::GetControlString("SID_PARAMETER1", L"Parameter 1"), wxDATAVIEW_CELL_EDITABLE);
    DataTable->AppendTextColumn(SwApplicationInterface::GetControlString("SID_PARAMETER2", L"Parameter 2"), wxDATAVIEW_CELL_EDITABLE);
    m_manager->AddPane(DataTable, wxAuiPaneInfo().Name(L"Table Table").CenterPane().CaptionVisible());
    m_manager->Update();

    m_statusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, L"ID_STATUSBAR1");
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    m_statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    m_statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(m_statusBar);

    Connect(ID_TABLEDELETEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnTableDeleteBtnClick);
    Connect(ID_TABLEADDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnTableAddBtnClick);
    Connect(ID_TABLELOADBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnTableLoadBtnClick);
    Connect(ID_TABLESAVEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnTableSaveBtnClick);
    Connect(ID_TABLECLOSEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnTableCloseBtnClick);
    Connect(ID_ADDIDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnIdAddBtnClick);
    Connect(ID_DELETEIDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerDataFileEditorFrame::OnDeleteIdBtnClick);

    EnableMenuItems(false);
    EnableIdentifierButtons(false);
    EnableTableButtons(false);
    EnableCurrentTableButtons(false);
    SwApplicationInterface::SetFrameWindow(this);
    SetIcon(SwApplicationInterface::GetToolsIcon());
    SetTitle(SwApplicationInterface::GetControlString("SID_SDFEDITOR", L"Sower Data File Editor"));
    Maximize();
}

SowerDataFileEditorFrame::~SowerDataFileEditorFrame()
{
    SwApplicationInterface::CloseFiles();
}

void SowerDataFileEditorFrame::OnQuit(wxCommandEvent& event)
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

void SowerDataFileEditorFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SDFEDITOR", L"Sower Data File Editor"), SVSTR, L"2019");
}

void SowerDataFileEditorFrame::OnTableAddBtnClick(wxCommandEvent& event)
{
    if (!TableNameTextCtrl->GetLineLength(0))
        return;

    if (TableList->FindItem(0, TableNameTextCtrl->GetLineText(0)) != -1)
    {
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_TABLEEXISTS", L"Table already exists.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return;
    }

    SwTable table;
    table.SetTableCaption(TableNameTextCtrl->GetLineText(0).utf8_str());
    m_datafile.AppendTable(table);
    TableList->wxListCtrl::InsertItem(TableList->GetItemCount(), TableNameTextCtrl->GetLineText(0));
}

void SowerDataFileEditorFrame::OnTableDeleteBtnClick(wxCommandEvent& event)
{
    swUI32 node;
    int item = TableList->GetFocusedItem();

    if (item > -1)
    {
        node = m_datafile.FindTableByCaption(TableList->GetItemText(item).utf8_str());
        if (node != NODE_ID_INVALID)
        {
            m_datafile.DeleteTable(node);
            TableList->DeleteItem(item);
        }
    }
}

void SowerDataFileEditorFrame::OnTableLoadBtnClick(wxCommandEvent& event)
{
    swUI32 node;
    int item = TableList->GetFocusedItem();

    SwTable table;

    if (item > -1)
    {
        node = m_datafile.FindTableByCaption(TableList->GetItemText(item).utf8_str());
        if (node != NODE_ID_INVALID)
        {
            DataTable->DeleteAllItems();
            m_datafile.FillTable(node, table);
            table.FillDataViewListCtrl(DataTable);
            m_manager->GetPane(DataTable).Caption(table.GetTableCaption());
            m_manager->Update();
            EnableIdentifierButtons(true);
            EnableCurrentTableButtons(true);
            TableLoadBtn->Enable(false);
        }
    }
}

void SowerDataFileEditorFrame::OnTableSaveBtnClick(wxCommandEvent& event)
{
    SwTable table;
    table.Import(DataTable, m_manager->GetPane(DataTable).caption.utf8_str(), CELLTYPE_TEXT);
    swUI32 node = m_datafile.FindTableByCaption(m_manager->GetPane(DataTable).caption.utf8_str());

    if (node != NODE_ID_INVALID)
    {
        m_datafile.ReplaceTable(node, table);
    }
}

void SowerDataFileEditorFrame::OnTableCloseBtnClick(wxCommandEvent& event)
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

    DataTable->DeleteAllItems();
    EnableCurrentTableButtons(false);
    EnableIdentifierButtons(false);
    TableLoadBtn->Enable(true);
    m_manager->GetPane(DataTable).Caption("");
    m_manager->Update();
}

void SowerDataFileEditorFrame::OnOpen(wxCommandEvent& event)
{
    SwString path;

    wxFileDialog fileDlg(this, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTAFILE", L"Select a file")).GetArray(), "", "", SwStringW(SwApplicationInterface::GetControlString("SID_SDFFILTER", L"Sower data files (*.sdf)|*.sdf")).GetArray(), wxFD_OPEN);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (!m_datafile.OpenFile(fileDlg.GetPath().utf8_str(), true))
        return;

    path = fileDlg.GetPath().utf8_str();
    SwClipFileName(path);
    m_datafile.SetBasePath(path);

    m_statusBar->SetStatusText(fileDlg.GetPath().utf8_str());
    m_datafile.FillCtrl(TableList);

    EnableMenuItems(true);
    EnableIdentifierButtons(false);
    EnableTableButtons(true);
    EnableCurrentTableButtons(false);
    menuBar->EnableOpen(false);
    menuBar->EnableNew(false);
}

void SowerDataFileEditorFrame::OnNew(wxCommandEvent& event)
{
    wxFileDialog fileDlg(this, SwStringW(SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as")).GetArray(), "", "", SwStringW(SwApplicationInterface::GetControlString("SID_SDFFILTER", L"Sower data files (*.sdf)|*.sdf")).GetArray(), wxFD_SAVE);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    if (!m_datafile.OpenFile(fileDlg.GetPath().utf8_str(), true))
        return;

    m_statusBar->SetStatusText(fileDlg.GetPath().utf8_str());
    m_datafile.FillCtrl(TableList);

    EnableMenuItems(true);
    EnableIdentifierButtons(false);
    EnableTableButtons(true);
    EnableCurrentTableButtons(false);
    menuBar->EnableOpen(false);
    menuBar->EnableNew(false);
}

void SowerDataFileEditorFrame::OnClose(wxCommandEvent& event)
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
    EnableTableButtons(false);
    EnableCurrentTableButtons(false);
    Clear();
    menuBar->EnableOpen(true);
    menuBar->EnableNew(true);
}

void SowerDataFileEditorFrame::EnableTableButtons(bool state)
{
    TableDeleteBtn->Enable(state);
    TableAddBtn->Enable(state);
    TableLoadBtn->Enable(state);
    TableList->Enable(state);
    TableNameTextCtrl->Enable(state);
    TablesStaticText->Enable(state);
}

void SowerDataFileEditorFrame::EnableIdentifierButtons(bool state)
{
    DeleteIdBtn->Enable(state);
    IdAddBtn->Enable(state);
    DataTextCtrl->Enable(state);
    IdTextCtrl->Enable(state);
    P1TextCtrl->Enable(state);
    P2TextCtrl->Enable(state);
    DataStaticText->Enable(state);
    IdentifierStaticText->Enable(state);
    P1StaticText->Enable(state);
    P2StaticText->Enable(state);
}

void SowerDataFileEditorFrame::EnableCurrentTableButtons(bool state)
{
    TableSaveBtn->Enable(state);
    TableCloseBtn->Enable(state);
    CurrentStaticText->Enable(state);
    DataTable->Enable(state);
}

void SowerDataFileEditorFrame::EnableMenuItems(bool fileLoaded)
{
    menuBar->EnableItems(fileLoaded);
}

void SowerDataFileEditorFrame::Clear()
{
    TableList->DeleteAllItems();
    DataTable->DeleteAllItems();
    m_manager->GetPane(DataTable).Caption("");
    m_manager->Update();
}

void SowerDataFileEditorFrame::OnIdAddBtnClick(wxCommandEvent& event)
{
    if (!IdTextCtrl->GetLineLength(0))
        return;

    if (TableSaveBtn->IsEnabled() && Find(DataTable, IdTextCtrl->GetLineText(0)) > -1 )
    {
        wxMessageBox(SwApplicationInterface::GetControlString("SID_IDENTIFIERALREADYEXISTS", L"Identifier already exists."), SwApplicationInterface::GetControlString("SID_ERROR", L"Error"));
        return;
    }

    wxVector<wxVariant> data;
    data.push_back( wxVariant(IdTextCtrl->GetLineText(0)) );
    data.push_back( wxVariant(DataTextCtrl->GetLineText(0)) );
    data.push_back( wxVariant(P1TextCtrl->GetLineText(0)) );
    data.push_back( wxVariant(P2TextCtrl->GetLineText(0)) );

    if (TableSaveBtn->IsEnabled())
        DataTable->AppendItem( data );
}

void SowerDataFileEditorFrame::OnDeleteIdBtnClick(wxCommandEvent& event)
{
    int selected = Find(DataTable, IdTextCtrl->GetLineText(0));

    if (selected < 0)
    {
        selected = DataTable->GetSelectedRow();
    }

    if (selected != wxNOT_FOUND)
    {
        DataTable->DeleteItem(selected);
    }
}

int SowerDataFileEditorFrame::Find(wxDataViewListCtrl * listctrl, const char * identifier)
{
    if (!listctrl || !identifier)
        return -1;

    for (int i = 0; i < listctrl->GetItemCount(); i ++)
    {
        if (listctrl->GetTextValue(i, 0).CmpNoCase(identifier) == 0)
            return i;
    }

    return -1;
}
