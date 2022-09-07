///////////////////////////////////////////////////////////////////
// Name:        sowerkeygeneratorapp.cpp
// Purpose:     Sower Key Generator
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowerkeygeneratorapp.h"
#include "appi/appifa.h"

IMPLEMENT_APP(SowerKeyGeneratorApp);

bool SowerKeyGeneratorApp::OnInit()
{
    bool wxsOK = true;

    SwApplicationInterface::InitBasic();
    SwApplicationInterface::LoadPlugIns();
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadModules();

    if ( wxsOK )
    {
    	SowerKeyGeneratorDlg Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }

    return wxsOK;
}

const long SowerKeyGeneratorDlg::ID_MODULELABEL = wxNewId();
const long SowerKeyGeneratorDlg::ID_PASSWORDLABEL = wxNewId();
const long SowerKeyGeneratorDlg::ID_ModuleCHOICE = wxNewId();
const long SowerKeyGeneratorDlg::ID_PASSWORDTEXTCTRL = wxNewId();
const long SowerKeyGeneratorDlg::ID_SAVEASLABEL = wxNewId();
const long SowerKeyGeneratorDlg::ID_SAVEASFILEPICKERCTRL = wxNewId();
const long SowerKeyGeneratorDlg::ID_DATALABEL = wxNewId();
const long SowerKeyGeneratorDlg::ID_DATATEXTCTRL = wxNewId();
const long SowerKeyGeneratorDlg::ID_ABOUTBUTTON = wxNewId();
const long SowerKeyGeneratorDlg::ID_GENERATEBUTTON = wxNewId();

SowerKeyGeneratorDlg::SowerKeyGeneratorDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
:SwDialog(parent, id, "", pos, size, wxDEFAULT_DIALOG_STYLE, "")
{
	wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;
	wxGridBagSizer* GridBagSizer3;

	GridBagSizer1 = new wxGridBagSizer(0, 0);
	ModuleLabel = new wxStaticText(this, ID_MODULELABEL, SwApplicationInterface::GetControlString("SID_MODULE", L"Module"), wxDefaultPosition, wxDefaultSize, 0, L"ID_MODULELABEL");
	GridBagSizer1->Add(ModuleLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	PasswordLabel = new wxStaticText(this, ID_PASSWORDLABEL, SwApplicationInterface::GetControlString("SID_PASSWORD", L"Password"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PASSWORDLABEL");
	GridBagSizer1->Add(PasswordLabel, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ModuleChoice = new wxChoice(this, ID_ModuleCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_ModuleCHOICE");
	GridBagSizer1->Add(ModuleChoice, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PasswordTextCtrl = new wxTextCtrl(this, ID_PASSWORDTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PASSWORDTEXTCTRL");
	GridBagSizer1->Add(PasswordTextCtrl, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SaveasLabel = new wxStaticText(this, ID_SAVEASLABEL, SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SAVEASLABEL");
	GridBagSizer1->Add(SaveasLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SaveasFilePickerCtrl = new wxFilePickerCtrl(this, ID_SAVEASFILEPICKERCTRL, wxEmptyString, wxEmptyString, _T("*.key*"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_SAVEASFILEPICKERCTRL"));
	GridBagSizer1->Add(SaveasFilePickerCtrl, wxGBPosition(3, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);
	DataLabel = new wxStaticText(this, ID_DATALABEL, SwApplicationInterface::GetControlString("SID_DATA", L"Data"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DATALABEL");
	GridBagSizer1->Add(DataLabel, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	DataTextCtrl = new wxTextCtrl(this, ID_DATATEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DATATEXTCTRL");
	GridBagSizer1->Add(DataTextCtrl, wxGBPosition(5, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	AboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
	GridBagSizer2->Add(AboutButton, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	GridBagSizer3 = new wxGridBagSizer(0, 0);
	GenerateButton = new wxButton(this, ID_GENERATEBUTTON, SwApplicationInterface::GetControlString("SID_GENERATE", L"Generate"));
	GridBagSizer3->Add(GenerateButton, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer3->Add(new wxButton(this, wxID_CANCEL, wxEmptyString), wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	GridBagSizer2->Add(GridBagSizer3, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(GridBagSizer2, wxGBPosition(6, 0), wxGBSpan(1, 2), wxEXPAND, 5);
	SwApplicationInterface::GetMasterKeyModuleList(ModuleChoice);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);
	Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerKeyGeneratorDlg::OnAboutButtonClick);
	Connect(ID_GENERATEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerKeyGeneratorDlg::OnOkButtonClick);
    SetLabel(SwApplicationInterface::GetControlString("SID_SOWERKEYGENERATOR", L"Sower Key Generator"));
	SetIcon(SwApplicationInterface::GetToolsIcon());
}

SowerKeyGeneratorDlg::~SowerKeyGeneratorDlg()
{

}

void SowerKeyGeneratorDlg::OnAboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERKEYGENERATOR", L"Sower Key Generator"), SVSTR, L"2019");
}

void SowerKeyGeneratorDlg::OnOkButtonClick(wxCommandEvent& event)
{
    int i = ModuleChoice->GetSelection();
    if (i == wxNOT_FOUND)
        return;

    SwClientData * data = (SwClientData *) ModuleChoice->GetClientObject(i);

    if (!data)
        return;

    SwModuleKey * key = SwApplicationInterface::GetKeyManager().GetKey(i);

    if (!key)
    {
        return;
    }

    if (strcmp(key->data, PasswordTextCtrl->GetValue().utf8_str()) != 0)
    {
        wxMessageBox(SwApplicationInterface::GetControlString("SID_INVALIDPASSWORD", L"Invalid password!"));
        return;
    }

    if (SaveasFilePickerCtrl->GetFileName().GetFullPath().Len() < 1)
    {
        SaveasFilePickerCtrl->SetFocus();
        wxBell();
        return;
    }

    if (DataTextCtrl->GetValue().Len() < 1)
    {
        DataTextCtrl->SetFocus();
        wxBell();
        return;
    }

    SwModuleKey userKey;
    userKey.header.GenerateKey();
    userKey.header.SetAsUser();
    userKey.identifier = key->identifier;
    userKey.header.SetIdentifierLength(userKey.identifier.Strlen());
    userKey.data = DataTextCtrl->GetValue().utf8_str();
    userKey.header.SetDataLength(userKey.data.Strlen());
    userKey.header.SetModuleKeys(key->header.mk1, key->header.mk2);
    userKey.Write(SaveasFilePickerCtrl->GetFileName().GetFullPath());
    wxMessageBox(SwApplicationInterface::GetControlString("SID_KEYGENERATED", L"Key generated."));
}
