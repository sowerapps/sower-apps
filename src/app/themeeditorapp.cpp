///////////////////////////////////////////////////////////////////
// Name:        themeeditorapp.cpp
// Purpose:     Sower Theme Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/themeeditorapp.h"
#include "filesys/file.h"
#include "appi/appifa.h"
#include <wx/msgdlg.h>
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerThemeEditorApp);

bool SowerThemeEditorApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();

    SowerThemeEditorFrame* Frame = new SowerThemeEditorFrame(NULL, wxNewId(), L"");
    Frame->Show();
    SetTopWindow(Frame);

    return true;
}

const long SowerThemeEditorFrame::ID_IDENTIFIERSTATICTEXT = wxNewId();
const long SowerThemeEditorFrame::ID_IDDELETEBTN = wxNewId();
const long SowerThemeEditorFrame::ID_IDTEXTCTRL = wxNewId();
const long SowerThemeEditorFrame::ID_IDADDBTN = wxNewId();
const long SowerThemeEditorFrame::ID_STATICLINE1 = wxNewId();
const long SowerThemeEditorFrame::ID_TABLESSTATICTEXT = wxNewId();
const long SowerThemeEditorFrame::ID_TABLEDELETEBTN = wxNewId();
const long SowerThemeEditorFrame::ID_TABLEADDBTN = wxNewId();
const long SowerThemeEditorFrame::ID_TABLELOADBTN = wxNewId();
const long SowerThemeEditorFrame::ID_IDENTIFIERLISTVIEW = wxNewId();
const long SowerThemeEditorFrame::ID_THEMELISTVIEW = wxNewId();
const long SowerThemeEditorFrame::ID_CURRENTTABLESTATICTEXT = wxNewId();
const long SowerThemeEditorFrame::ID_TABLESAVEBTN = wxNewId();
const long SowerThemeEditorFrame::ID_TABLECLOSEBTN = wxNewId();
const long SowerThemeEditorFrame::ID_NAMETEXTCTRL = wxNewId();
const long SowerThemeEditorFrame::ID_PANEL1 = wxNewId();
const long SowerThemeEditorFrame::ID_CUSTOM1 = wxNewId();
const long SowerThemeEditorFrame::ID_CUSTOM2 = wxNewId();
const long SowerThemeEditorFrame::ID_STATUSBAR1 = wxNewId();


SowerThemeEditorFrame::SowerThemeEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxGridBagSizer* GridBagSizer1;

    menuBar = new SwBasicEditorMenuBar(this);
    SetMenuBar(menuBar);

    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_PANEL1");

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    IdentifierStaticText = new wxStaticText(Panel1, ID_IDENTIFIERSTATICTEXT, SwApplicationInterface::GetControlString("SID_IDENTIFIERS", L"Identifiers"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERSTATICTEXT");
    GridBagSizer1->Add(IdentifierStaticText, wxGBPosition(0, 4), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    IdDeleteBtn = new wxButton(Panel1, ID_IDDELETEBTN, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDDELETEBTN");
    GridBagSizer1->Add(IdDeleteBtn, wxGBPosition(4, 5), wxDefaultSpan, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);

    IdTextCtrl = new wxTextCtrl(Panel1, ID_IDTEXTCTRL, L"SID_", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDTEXTCTRL");
    GridBagSizer1->Add(IdTextCtrl, wxGBPosition(3, 4), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);

    IdAddBtn = new wxButton(Panel1, ID_IDADDBTN, SwApplicationInterface::GetControlString("SID_ADD", L"Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDADDBTN");
    GridBagSizer1->Add(IdAddBtn, wxGBPosition(4, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxDefaultPosition, wxSize(2,-1), wxLI_VERTICAL, L"ID_STATICLINE1");
    GridBagSizer1->Add(StaticLine1, wxGBPosition(0, 3), wxGBSpan(6, 1), wxALL|wxEXPAND, 5);

    TablesStaticText = new wxStaticText(Panel1, ID_TABLESSTATICTEXT, SwApplicationInterface::GetControlString("SID_TABLES", L"Tables"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TABLESSTATICTEXT");
    GridBagSizer1->Add(TablesStaticText, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableDeleteBtn = new wxButton(Panel1, ID_TABLEDELETEBTN, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLEDELETEBTN");
    GridBagSizer1->Add(TableDeleteBtn, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableAddBtn = new wxButton(Panel1, ID_TABLEADDBTN, SwApplicationInterface::GetControlString("SID_ADD", L"Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLEADDBTN");
    GridBagSizer1->Add(TableAddBtn, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableLoadBtn = new wxButton(Panel1, ID_TABLELOADBTN, SwApplicationInterface::GetControlString("SID_LOAD", L"Load"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLELOADBTN");
    GridBagSizer1->Add(TableLoadBtn, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    IdentifierList = new SwStretchColumnListView(Panel1, ID_IDENTIFIERLISTVIEW, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING, wxDefaultValidator, L"ID_IDENTIFIERLISTVIEW");
    GridBagSizer1->Add(IdentifierList, wxGBPosition(1, 4), wxGBSpan(2, 3), wxALL|wxEXPAND, 5);

    ThemeList = new SwStretchColumnListView(Panel1, ID_THEMELISTVIEW, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING, wxDefaultValidator, L"ID_THEMELISTVIEW");
    GridBagSizer1->Add(ThemeList, wxGBPosition(1, 0), wxGBSpan(2, 3), wxALL|wxEXPAND, 5);

    CurrentTableStaticText = new wxStaticText(Panel1, ID_CURRENTTABLESTATICTEXT, SwApplicationInterface::GetControlString("SID_CURRENTTABLE", L"Current Table"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CURRENTTABLESTATICTEXT");
    GridBagSizer1->Add(CurrentTableStaticText, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableSaveBtn = new wxButton(Panel1, ID_TABLESAVEBTN, SwApplicationInterface::GetControlString("SID_SAVE", L"Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLESAVEBTN");
    GridBagSizer1->Add(TableSaveBtn, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    TableCloseBtn = new wxButton(Panel1, ID_TABLECLOSEBTN, SwApplicationInterface::GetControlString("SID_CLOSE", L"Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TABLECLOSEBTN");
    GridBagSizer1->Add(TableCloseBtn, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    ThemeNameTextCtrl = new wxTextCtrl(Panel1, ID_NAMETEXTCTRL, L"", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_NAMETEXTCTRL");
    GridBagSizer1->Add(ThemeNameTextCtrl, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);

    Panel1->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(Panel1);
    GridBagSizer1->SetSizeHints(Panel1);

    m_manager->AddPane(Panel1, wxAuiPaneInfo().Name(L"ToolPane").DefaultPane().Caption(SwApplicationInterface::GetControlString("SID_EDIT", L"Edit")).CaptionVisible().CloseButton(false).Bottom().DockFixed().Floatable(false).FloatingSize(wxSize(-1,-1)).Resizable(false).Movable(false).Position(0));
    ImagePreview = new SwImageWindow(this,ID_CUSTOM1,wxPoint(107,217),wxDefaultSize,0,L"ID_CUSTOM1");
    m_manager->AddPane(ImagePreview, wxAuiPaneInfo().Name(L"ImageView").DefaultPane().Caption(SwApplicationInterface::GetControlString("SID_IMAGE", L"Image")).CaptionVisible().CloseButton(false).Position(1).Bottom().DockFixed().Floatable(false).Movable(false).Position(1));

    ThemeGrid = new wxListView(this, ID_CUSTOM2, wxPoint(371,204), wxDefaultSize, wxLC_REPORT|wxLC_EDIT_LABELS|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_CUSTOM2");
    m_manager->AddPane(ThemeGrid, wxAuiPaneInfo().Name(L"ThemeGrid").CenterPane().CaptionVisible().DockFixed());
    m_manager->Update();

    m_statusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, L"ID_STATUSBAR1");
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    m_statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    m_statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(m_statusBar);

    Connect(ID_IDDELETEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnIdDeleteBtnClick);
    Connect(ID_IDADDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnIdAddBtnClick);
    Connect(ID_TABLEDELETEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnTableDeleteBtnClick);
    Connect(ID_TABLEADDBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnTableAddBtnClick);
    Connect(ID_TABLELOADBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnTableLoadBtnClick);
    Connect(ID_TABLESAVEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnTableSaveBtnClick);
    Connect(ID_TABLECLOSEBTN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnTableCloseBtnClick);

    Connect(ID_CUSTOM2,wxEVT_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SowerThemeEditorFrame::OnThemeGridItemFocused);
    Connect(ID_CUSTOM2,wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&SowerThemeEditorFrame::OnThemeGridBeginLabelEdit);

    SetIcon(SwApplicationInterface::GetToolsIcon());
    IdentifierList->wxListCtrl::AppendColumn("");
    ThemeList->wxListCtrl::AppendColumn("");
    ThemeGrid->AppendColumn(SwApplicationInterface::GetControlString("SID_VALUE", L"Value"), wxLIST_FORMAT_LEFT, 300);
    ThemeGrid->AppendColumn(SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxLIST_FORMAT_LEFT, 200);

    EnableMenuItems(false);
    EnableIdentifierButtons(false);
    EnableTableButtons(false);
    EnableCurrentTableButtons(false);

    SwApplicationInterface::SetFrameWindow(this);
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERTHEMEEDITOR", L"Sower Theme Editor"));
    Maximize();
}

SowerThemeEditorFrame::~SowerThemeEditorFrame()
{
    SwApplicationInterface::CloseFiles();
}

void SowerThemeEditorFrame::OnQuit(wxCommandEvent& event)
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

void SowerThemeEditorFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERTHEMEEDITOR", L" Sower Theme Editor"), SVSTR, L"2019");
}

void SowerThemeEditorFrame::OnIdAddBtnClick(wxCommandEvent& event)
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
    IdTextCtrl->SetValue("SID_");
}

void SowerThemeEditorFrame::OnIdDeleteBtnClick(wxCommandEvent& event)
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

        SwString buffer;
        SwDataFile::CreateDataListString(IdentifierList, buffer, "String Identifiers");
        m_datafile.ReplaceDataList("String Identifiers", buffer);
    }
}

void SowerThemeEditorFrame::OnTableAddBtnClick(wxCommandEvent& event)
{
    if (!ThemeNameTextCtrl->GetLineLength(0))
        return;

    if (ThemeList->FindItem(0, ThemeNameTextCtrl->GetLineText(0)) != -1)
    {
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_TABLEEXISTS", L"Table already exists.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return;
    }

    SwTable table;
    table.SetTableCaption(ThemeNameTextCtrl->GetLineText(0).utf8_str());

    for (int i = 0; i < IdentifierList->GetItemCount(); i ++)
    {
        table.AppendNode(IdentifierList->GetItemText(i).utf8_str(), "");
    }

    m_datafile.AppendTable(table);
    ThemeList->wxListCtrl::InsertItem(ThemeList->GetItemCount(), ThemeNameTextCtrl->GetLineText(0));
}

void SowerThemeEditorFrame::OnTableDeleteBtnClick(wxCommandEvent& event)
{
    swUI32 node;
    int item = ThemeList->GetFocusedItem();

    if (item > -1)
    {
        node = m_datafile.FindTableByCaption(ThemeList->GetItemText(item).utf8_str());
        if (node != NODE_ID_INVALID)
        {
            m_datafile.DeleteTable(node);
            ThemeList->DeleteItem(item);
        }
    }
}

void SowerThemeEditorFrame::OnTableLoadBtnClick(wxCommandEvent& event)
{
    swUI32 node;
    int item = ThemeList->GetFocusedItem();

    SwTable table;

    if (item > -1)
    {
        node = m_datafile.FindTableByCaption(ThemeList->GetItemText(item).utf8_str());
        if (node != NODE_ID_INVALID)
        {
            ThemeGrid->DeleteAllItems();
            ImagePreview->Clear();
            ImagePreview->Reset();
            ImagePreview->Refresh();
            m_datafile.FillTable(node, table);
            table.FillCtrl(ThemeGrid);
            m_manager->GetPane(ThemeGrid).Caption(table.GetTableCaption());
            m_manager->Update();
            EnableIdentifierButtons(false);
            EnableCurrentTableButtons(true);
            TableLoadBtn->Enable(false);
        }
    }
}

void SowerThemeEditorFrame::OnTableSaveBtnClick(wxCommandEvent& event)
{
    SwTable table;

    table.Import(ThemeGrid, m_manager->GetPane(ThemeGrid).caption.utf8_str(), CELLTYPE_IMAGE);
    swUI32 node = m_datafile.FindTableByCaption(m_manager->GetPane(ThemeGrid).caption.utf8_str());

    if (node != NODE_ID_INVALID)
    {
        m_datafile.ReplaceTable(node, table);
    }
}

void SowerThemeEditorFrame::OnTableCloseBtnClick(wxCommandEvent& event)
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

    ThemeGrid->DeleteAllItems();
    EnableTableButtons(false);
    EnableIdentifierButtons(true);
    TableLoadBtn->Enable(true);
    ImagePreview->Clear();
    ImagePreview->Refresh();
    m_manager->GetPane(ThemeGrid).Caption("");
    m_manager->Update();
}

void SowerThemeEditorFrame::OnOpen(wxCommandEvent& event)
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
    m_datafile.GetDataListItems(IdentifierList, "String Identifiers");
    m_datafile.FillCtrl(ThemeList);

    EnableMenuItems(true);
    EnableIdentifierButtons(true);
    EnableTableButtons(true);
    menuBar->EnableOpen(false);
    menuBar->EnableNew(false);
}

void SowerThemeEditorFrame::OnNew(wxCommandEvent& event)
{
    SwString path;

    wxFileDialog fileDlg(this, SwStringW(SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as")).GetArray(), "", "", SwStringW(SwApplicationInterface::GetControlString("SID_SDFFILTER", L"Sower data files (*.sdf)|*.sdf")).GetArray(), wxFD_SAVE);
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
    m_datafile.GetDataListItems(IdentifierList, "String Identifiers");
    m_datafile.FillCtrl(ThemeList);

    EnableMenuItems(true);
    EnableIdentifierButtons(true);
    EnableTableButtons(true);
    menuBar->EnableOpen(false);
    menuBar->EnableNew(false);
}

void SowerThemeEditorFrame::OnClose(wxCommandEvent& event)
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

void SowerThemeEditorFrame::EnableTableButtons(bool state)
{
    TableDeleteBtn->Enable(state);
    TableAddBtn->Enable(state);
    TableLoadBtn->Enable(state);
    ThemeNameTextCtrl->Enable(state);
    ThemeList->Enable(state);
    TablesStaticText->Enable(state);
}

void SowerThemeEditorFrame::EnableIdentifierButtons(bool state)
{
    IdDeleteBtn->Enable(state);
    IdAddBtn->Enable(state);
    IdTextCtrl->Enable(state);
    IdentifierList->Enable(state);
    IdentifierStaticText->Enable(state);
}

void SowerThemeEditorFrame::EnableCurrentTableButtons(bool state)
{
    TableSaveBtn->Enable(state);
    TableCloseBtn->Enable(state);
    CurrentTableStaticText->Enable(state);
    ThemeGrid->Enable(state);
}

void SowerThemeEditorFrame::EnableMenuItems(bool fileLoaded)
{
    menuBar->EnableItems(fileLoaded);
}

void SowerThemeEditorFrame::Clear()
{
    ThemeList->DeleteAllItems();
    IdentifierList->DeleteAllItems();
    ThemeGrid->DeleteAllItems();
    m_manager->GetPane(ThemeGrid).Caption("");
    ImagePreview->Clear();
    ImagePreview->Reset();
    ImagePreview->Refresh();
    m_manager->Update();
}

void SowerThemeEditorFrame::OnThemeGridItemFocused(wxListEvent& event)
{
    SwString path;

    if (!ThemeGrid->GetItemText(event.GetIndex(), 1).Len())
    {
        ImagePreview->Reset();
        ImagePreview->Clear();
        ImagePreview->Refresh();
        event.Skip();
        return;
    }

    SwGetPathFromRelative(m_datafile.GetBasePath(), ThemeGrid->GetItemText(event.GetIndex(), 0), path);
    ImagePreview->LoadImage(path.GetArray());
    ImagePreview->Refresh();
    event.Veto();
}

void SowerThemeEditorFrame::OnThemeGridBeginLabelEdit(wxListEvent& event)
{
    SwString path;
    wxFileDialog fileDlg(this, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTAFILE", L"Select a file")).GetArray(), "", "", SwStringW(SwApplicationInterface::GetControlString("SID_PNGFILTER", L"png files (*.png)|*.png")).GetArray(), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    int status = fileDlg.ShowModal();

    if (status == wxID_CANCEL)
    {
        event.Skip();
        return;
    }

    SwGetRelativePath(m_datafile.GetBasePath(), fileDlg.GetPath().utf8_str(), path);

    ThemeGrid->SetItemText(event.GetIndex(), path.GetArray());
    ImagePreview->LoadImage(fileDlg.GetPath().utf8_str());
    ImagePreview->Refresh();

    event.Skip();
}
