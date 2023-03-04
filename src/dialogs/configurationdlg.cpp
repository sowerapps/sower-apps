///////////////////////////////////////////////////////////////////
// Name:        configurationdlg.cpp
// Purpose:     SwConfigurationDlg
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/configurationdlg.h"
#include "../../include/appi/appifa.h"

const long SwConfigurationDlg::ID_CONFIGLISTCTRL = wxNewId();

SwConfigurationDlg::SwConfigurationDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    :SwDialog(parent, id, "", pos, size, wxDEFAULT_DIALOG_STYLE, "")
{
	wxGridBagSizer* GridBagSizer1;

	GridBagSizer1 = new wxGridBagSizer(0, 0);

	ConfigListCtrl = new wxListCtrl(this, ID_CONFIGLISTCTRL, wxDefaultPosition,wxSize(700,300), wxLC_REPORT, wxDefaultValidator, L"ID_CONFIGLISTCTRL");
    ConfigListCtrl->AppendColumn(SwApplicationInterface::GetControlString("SID_ITEM", L"Item"), wxLIST_FORMAT_LEFT, 100);
    ConfigListCtrl->AppendColumn(SwApplicationInterface::GetControlString("SID_PATH", L"Path"), wxLIST_FORMAT_LEFT, 600);
    GridBagSizer1->Add(ConfigListCtrl, wxGBPosition(0, 0), wxGBSpan(3, 20), wxALL|wxEXPAND, 5);

	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);
    SetLabel(SwApplicationInterface::GetControlString("SID_SOWERCONFIGURATION", L"Sower Configuration"));
	SetIcon(SwApplicationInterface::GetIcon("SID_INFORMATION"));

	AppendToList(SwApplicationInterface::GetControlString("SID_APPLICATION", L"Application"), SwApplicationInterface::GetAppDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_USER", L"User"), SwApplicationInterface::GetUserDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_DATA", L"Data"), SwApplicationInterface::GetDataDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_RESOURCES", L"Resources"), SwApplicationInterface::GetResourcesDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_MODULELIBRARY", L"Module Library"), SwApplicationInterface::GetModuleLibraryDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_THMLLIBRARY", L"ThML Library"), SwApplicationInterface::GetThMLLibraryDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_HELP", L"Help"), SwApplicationInterface::GetHelpDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_THEMES", L"Themes"), SwApplicationInterface::GetThemesDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_PLUGINS", L"Plugins"), SwApplicationInterface::GetPluginsDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_USERKEYS", L"User Keys"), SwApplicationInterface::GetUserKeysDir());
	AppendToList(SwApplicationInterface::GetControlString("SID_MASTERKEYS", L"Master Keys"), SwApplicationInterface::GetMasterKeysDir());
}

SwConfigurationDlg::~SwConfigurationDlg()
{

}

void SwConfigurationDlg::AppendToList(const wchar_t * item, const char * value)
{
    SwStringW buffer;
    wxListItem lItem;
    long listPos;

    if (!item || !value)
        return;

    lItem.Clear();
    lItem.SetStateMask(wxLIST_MASK_TEXT);
    lItem.SetColumn(0);
    lItem.SetId(ConfigListCtrl->GetItemCount());
    lItem.SetText(item);
    listPos = ConfigListCtrl->InsertItem(lItem);
    lItem.Clear();
    lItem.SetStateMask(wxLIST_MASK_TEXT);
    lItem.SetColumn(1);
    lItem.SetId(listPos);
    buffer.Copy(value);
    lItem.SetText(buffer.GetArray());
    ConfigListCtrl->SetItem(lItem);
}
