///////////////////////////////////////////////////////////////////
// Name:        preferencesdlg.cpp
// Purpose:     SwPreferencesDlg
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/preferencesdlg.h"
#include "../../include/appi/appifa.h"

const long SwPreferencesDlg::ID_LANGUAGETEXT = wxNewId();
const long SwPreferencesDlg::ID_LANGUAGECHOICE = wxNewId();
const long SwPreferencesDlg::ID_THEMETEXT = wxNewId();
const long SwPreferencesDlg::ID_THEMECHOICE = wxNewId();
const long SwPreferencesDlg::ID_FONTSIZETEXT = wxNewId();
const long SwPreferencesDlg::ID_FONTSIZESPINCTRL = wxNewId();
const long SwPreferencesDlg::ID_ADFONTSIZETEXT = wxNewId();
const long SwPreferencesDlg::ID_SPINCTRL2 = wxNewId();
const long SwPreferencesDlg::ID_THMLLIBRARYLOCATIONLOCATIONTEXT = wxNewId();
const long SwPreferencesDlg::ID_THMLLIBRARYDIRPICKERCTRL = wxNewId();
const long SwPreferencesDlg::ID_MODLIBRARYLOCATIONLOCATIONTEXT = wxNewId();
const long SwPreferencesDlg::ID_MODLIBRARYDIRPICKERCTRL = wxNewId();
const long SwPreferencesDlg::ID_ADMODULESTEXT = wxNewId();
const long SwPreferencesDlg::ID_MODULESCHECKLISTBOX = wxNewId();
const long SwPreferencesDlg::ID_SESSIONCHECKBOX = wxNewId();

SwPreferencesDlg::SwPreferencesDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	wxGridBagSizer* GridBagSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");
	wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

	GridBagSizer1 = new wxGridBagSizer(0, 0);
	LanguageText = new wxStaticText(this, ID_LANGUAGETEXT, SwApplicationInterface::GetControlString("SID_LANGUAGE", L"Language"), wxDefaultPosition, wxDefaultSize, 0, L"ID_LANGUAGETEXT");
	LanguageText->SetMinSize(wxSize(200, -1));
	GridBagSizer1->Add(LanguageText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	LanguageChoice = new wxChoice(this, ID_LANGUAGECHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_LANGUAGECHOICE");
	GridBagSizer1->Add(LanguageChoice, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ThemeText = new wxStaticText(this, ID_THEMETEXT, SwApplicationInterface::GetControlString("SID_THEME", L"Theme"), wxDefaultPosition, wxDefaultSize, 0, L"ID_THEMETEXT");
	GridBagSizer1->Add(ThemeText, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ThemeChoice = new wxChoice(this, ID_THEMECHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_THEMECHOICE");
	GridBagSizer1->Add(ThemeChoice, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FontSizeText = new wxStaticText(this, ID_FONTSIZETEXT, SwApplicationInterface::GetControlString("SID_FONTSIZE", L"Font Size"), wxDefaultPosition, wxDefaultSize, 0, L"ID_FONTSIZETEXT");
	GridBagSizer1->Add(FontSizeText, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FontSizeSpinCtrl = new wxSpinCtrl(this, ID_FONTSIZESPINCTRL, L"0", wxDefaultPosition, wxDefaultSize, 0, 5, 24, 0, L"ID_FONTSIZESPINCTRL");
	FontSizeSpinCtrl->SetValue(L"0");
	GridBagSizer1->Add(FontSizeSpinCtrl, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ADFontSizeText = new wxStaticText(this, ID_ADFONTSIZETEXT, SwApplicationInterface::GetControlString("SID_AUTODEFFONTSIZE", L"AutoDef Font Size"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ADFONTSIZETEXT");
	GridBagSizer1->Add(ADFontSizeText, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ADFontSizeSpinCtrl = new wxSpinCtrl(this, ID_SPINCTRL2, L"0", wxDefaultPosition, wxDefaultSize, 0, 5, 24, 0, L"ID_SPINCTRL2");
	ADFontSizeSpinCtrl->SetValue(L"0");
	GridBagSizer1->Add(ADFontSizeSpinCtrl, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	sessionCheckBox = new wxCheckBox(this, ID_SESSIONCHECKBOX, SwApplicationInterface::GetControlString("SID_SAVESESSION", L"Save session."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_CHECKEDBOX");
	GridBagSizer1->Add(sessionCheckBox, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ThMLLibraryLocationText = new wxStaticText(this, ID_THMLLIBRARYLOCATIONLOCATIONTEXT, SwApplicationInterface::GetControlString("SID_THMLLIBLOCATION", L"ThML Library Location"), wxDefaultPosition, wxDefaultSize, 0, L"ID_THMLLIBRARYLOCATIONLOCATIONTEXT");
	GridBagSizer1->Add(ThMLLibraryLocationText, wxGBPosition(9, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ThMLLibraryDirPickerCtrl = new wxDirPickerCtrl(this, ID_THMLLIBRARYDIRPICKERCTRL, wxEmptyString, SwApplicationInterface::GetControlString("SID_SELECTDIR", L"Select a directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_LIBRARYDIRPICKERCTRL"));
	GridBagSizer1->Add(ThMLLibraryDirPickerCtrl, wxGBPosition(10, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);
	ModLibraryLocationText = new wxStaticText(this, ID_MODLIBRARYLOCATIONLOCATIONTEXT, SwApplicationInterface::GetControlString("SID_MODLIBLOCATION", L"Module Library Location"), wxDefaultPosition, wxDefaultSize, 0, L"ID_MODLIBRARYLOCATIONLOCATIONTEXT");
	GridBagSizer1->Add(ModLibraryLocationText, wxGBPosition(11, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ModLibraryDirPickerCtrl = new wxDirPickerCtrl(this, ID_MODLIBRARYDIRPICKERCTRL, wxEmptyString, SwApplicationInterface::GetControlString("SID_SELECTDIR", L"Select a directory"), wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST|wxDIRP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_LIBRARYDIRPICKERCTRL"));
	GridBagSizer1->Add(ModLibraryDirPickerCtrl, wxGBPosition(12, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);


	ADModulesText = new wxStaticText(this, ID_ADMODULESTEXT, SwApplicationInterface::GetControlString("SID_AUTODEFACCESS", L"Allow AutoDef to access:"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ADMODULESTEXT");
	GridBagSizer1->Add(ADModulesText, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ModulesCheckListBox = new wxCheckListBox(this, ID_MODULESCHECKLISTBOX, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_MODULESCHECKLISTBOX");
	GridBagSizer1->Add(ModulesCheckListBox, wxGBPosition(1, 1), wxGBSpan(12, 1), wxALL|wxEXPAND, 5);
	StdDialogButtonSizer = new wxStdDialogButtonSizer();
	StdDialogButtonSizer->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer->Realize();
	GridBagSizer1->Add(StdDialogButtonSizer, wxGBPosition(13, 0), wxGBSpan(1, 2), wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridBagSizer1);

	int item;
	SwStringW buffer;

	SetLabel(SwApplicationInterface::GetControlString("SID_PREFERENCES", L"Preferences"));
	SwApplicationInterface::GetModuleList(ModulesCheckListBox);
	SwApplicationInterface::GetThMLFileList(ModulesCheckListBox);

	SwApplicationInterface::GetLanguage().FillCtrl(*LanguageChoice);
    item = LanguageChoice->FindString(SwApplicationInterface::GetLanguage().GetTable().GetTableCaptionW());
	LanguageChoice->SetSelection(item);

	SwApplicationInterface::GetTheme().FillCtrl(*ThemeChoice);
	item = ThemeChoice->FindString(SwApplicationInterface::GetTheme().GetTable().GetTableCaptionW());
	ThemeChoice->SetSelection(item);

	swUI32 node = SwApplicationInterface::GetGlobalSettings().FindItemById("ThML-Library-Path");

	if (node != NODE_ID_INVALID)
        SwApplicationInterface::GetGlobalSettings().GetNodeDataW(node, m_thmlPath);

    ThMLLibraryDirPickerCtrl->SetPath(m_thmlPath.GetArray());

    node = SwApplicationInterface::GetGlobalSettings().FindItemById("Module-Library-Path");

    if (node != NODE_ID_INVALID)
        SwApplicationInterface::GetGlobalSettings().GetNodeDataW(node, buffer);

    ModLibraryDirPickerCtrl->SetPath(buffer.GetArray());

	FontSizeSpinCtrl->SetValue(SwApplicationInterface::GetReaderFontSize());
	ADFontSizeSpinCtrl->SetValue(SwApplicationInterface::GetAutoDefFontSize());

	node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");
	if (node != NODE_ID_INVALID)
        sessionCheckBox->SetValue(SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)));
    else
        sessionCheckBox->SetValue(true);

    GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

	m_theme = ThemeChoice->GetSelection();
	m_language = LanguageChoice->GetSelection();
	Connect(wxID_OK,wxEVT_BUTTON,(wxObjectEventFunction)&SwPreferencesDlg::OnOk);
}

SwPreferencesDlg::~SwPreferencesDlg()
{
}

void SwPreferencesDlg::OnOk(wxCommandEvent& event)
{
    Show(false);
    SwApplicationInterface::SetReaderFontSize(FontSizeSpinCtrl->GetValue());
    SwApplicationInterface::SetAutoDefFontSize(ADFontSizeSpinCtrl->GetValue());

    if (wcscmp(m_thmlPath, ThMLLibraryDirPickerCtrl->GetTextCtrlValue().wchar_str())!= 0)
    {
        SwApplicationInterface::GetGlobalSettings().UpdateNode("ThML-Library-Path", ThMLLibraryDirPickerCtrl->GetTextCtrlValue().utf8_str());
        SwApplicationInterface::LoadThMLFiles();
    }
        SwApplicationInterface::GetGlobalSettings().UpdateNode("Module-Library-Path", ModLibraryDirPickerCtrl->GetTextCtrlValue().utf8_str());

    if (sessionCheckBox->GetValue())
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("Save-Session", "true", CELLTYPE_TEXT);
    else
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("Save-Session", "false", CELLTYPE_TEXT);

    SwApplicationInterface::UpdateModuleStates(ModulesCheckListBox);
    SwApplicationInterface::UpdateThMLFileStates(ModulesCheckListBox);

    int selection = ThemeChoice->GetSelection();

    if (selection != m_theme)
    {
        SwClientData * data = (SwClientData *) ThemeChoice->GetClientObject(selection);
        SwApplicationInterface::GetTheme().FillTable(data->m_data);
        SwApplicationInterface::GetPlugInManager().OnThemeChange();
        SwApplicationInterface::GetPanelList().OnThemeChangeBase();
        SwApplicationInterface::GetDialogList().OnThemeChangeBase();

        if (SwApplicationInterface::GetMenuBar())
            SwApplicationInterface::GetMenuBar()->OnThemeChange();
        if (SwApplicationInterface::GetToolBar())
            SwApplicationInterface::GetToolBar()->OnThemeChange();
        if (SwApplicationInterface::GetFrameWindow())
            SwApplicationInterface::GetFrameWindow()->OnThemeChangeBase();
    }

    selection = LanguageChoice->GetSelection();

    if (selection != m_language)
    {
        SwClientData * data = (SwClientData *) LanguageChoice->GetClientObject(selection);
        SwApplicationInterface::GetLanguage().FillTable(data->m_data);
        SwApplicationInterface::GetPlugInManager().OnLanguageChange();
        SwApplicationInterface::GetPanelList().OnLanguageChangeBase();
        SwApplicationInterface::GetDialogList().OnLanguageChangeBase();

        if (SwApplicationInterface::GetMenuBar())
            SwApplicationInterface::GetMenuBar()->OnLanguageChange();
        if (SwApplicationInterface::GetToolBar())
            SwApplicationInterface::GetToolBar()->OnLanguageChange();
        if (SwApplicationInterface::GetFrameWindow())
            SwApplicationInterface::GetFrameWindow()->OnLanguageChangeBase();
    }

    EndModal(1);
}
