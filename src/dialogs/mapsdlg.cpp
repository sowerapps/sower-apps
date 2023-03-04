///////////////////////////////////////////////////////////////////
// Name:        mapsdlg.cpp
// Purpose:     Manage HtmlImageMaps in HtmlImageMapLists.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/mapsdlg.h"
#include "../../include/imgwin/command.h"

const long SwMapDlg::ID_MAPSSTATICTEXT = wxNewId();
const long SwMapDlg::ID_MAPSLISTCTRL = wxNewId();
const long SwMapDlg::ID_NEWBUTTON = wxNewId();
const long SwMapDlg::ID_RENAMEBUTTON = wxNewId();
const long SwMapDlg::ID_DELETEBUTTON = wxNewId();
const long SwMapDlg::ID_NAMESTATICTEXT = wxNewId();
const long SwMapDlg::ID_NAMETEXTCTRL = wxNewId();

SwMapDlg::SwMapDlg(SwImageWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_parent = parent;
    BuildContent(parent, id, pos, size);
}

void SwMapDlg::BuildContent(wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxGridBagSizer* GridBagSizer1;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    MapsStaticText = new wxStaticText(this, ID_MAPSSTATICTEXT, SwApplicationInterface::GetControlString("SID_MAPS", L"Maps"), wxDefaultPosition, wxDefaultSize, 0, L"ID_MAPSSTATICTEXT");
	GridBagSizer1->Add(MapsStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	MapsListCtrl = new SwStretchColumnListView(this, ID_MAPSLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING, wxDefaultValidator, L"ID_MAPSLISTCTRL");
	MapsListCtrl->wxListCtrl::AppendColumn("");
	GridBagSizer1->Add(MapsListCtrl, wxGBPosition(1, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
	NewButton = new wxButton(this, ID_NEWBUTTON, SwApplicationInterface::GetControlString("SID_NEW", L"New"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_NEWBUTTON");
	GridBagSizer1->Add(NewButton, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	RenameButton = new wxButton(this, ID_RENAMEBUTTON, SwApplicationInterface::GetControlString("SID_RENAME", L"Rename"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_RENAMEBUTTON");
	GridBagSizer1->Add(RenameButton, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	DeleteButton = new wxButton(this, ID_DELETEBUTTON, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DELETEBUTTON");
	GridBagSizer1->Add(DeleteButton, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	NameStaticText = new wxStaticText(this, ID_NAMESTATICTEXT, SwApplicationInterface::GetControlString("SID_NAME", L"Name"), wxDefaultPosition, wxDefaultSize, 0, L"ID_NAMESTATICTEXT");
	GridBagSizer1->Add(NameStaticText, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	NameTextCtrl = new wxTextCtrl(this, ID_NAMETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_NAMETEXTCTRL");
	GridBagSizer1->Add(NameTextCtrl, wxGBPosition(4, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

	if (m_parent)
    {
        m_parent->GetImageMapList().FillCtrl(MapsListCtrl);
    }

	Connect(ID_NEWBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwMapDlg::OnNewButtonClick);
	Connect(ID_RENAMEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwMapDlg::OnRenameButtonClick);
	Connect(ID_DELETEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwMapDlg::OnDeleteButtonClick);

    SetLabel(SwApplicationInterface::GetControlString("SID_MAPS", L"Maps"));
}

SwMapDlg::~SwMapDlg()
{
    if (m_parent)
        m_parent->Refresh();
}

void SwMapDlg::OnNewButtonClick(wxCommandEvent& event)
{
    if (!NameTextCtrl->GetValue().Len() || m_parent->GetImageMapList().FindMap(NameTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID)
    {
        NameTextCtrl->SetFocus();
        wxBell();
        return;
    }

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();
    swUI32 i = mapList->AddMap(NameTextCtrl->GetValue().utf8_str());
    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    wxListItem lItem;
    lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
    lItem.SetColumn(0);
    lItem.SetId(MapsListCtrl->GetItemCount());
    lItem.SetText(NameTextCtrl->GetValue());
    lItem.SetData(m_parent->GetImageMapList().GetMap(i));
    MapsListCtrl->wxListCtrl::InsertItem(lItem);
}

void SwMapDlg::OnRenameButtonClick(wxCommandEvent& event)
{
    int selection = MapsListCtrl->GetFocusedItem();

    if (selection < 0 || !NameTextCtrl->GetValue().Len() || m_parent->GetImageMapList().FindMap(NameTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID)
    {
        NameTextCtrl->SetFocus();
        wxBell();
        return;
    }

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();
    mapList->SetMapName(selection, NameTextCtrl->GetValue().utf8_str());
    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    MapsListCtrl->SetItemText(selection, NameTextCtrl->GetValue());
}

void SwMapDlg::OnDeleteButtonClick(wxCommandEvent& event)
{
    int selection = MapsListCtrl->GetFocusedItem();

    if (selection < 0)
    {
        wxBell();
        return;
    }

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();
    mapList->DeleteMap(selection);
    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    MapsListCtrl->DeleteItem(selection);

    m_parent->Refresh();
}
