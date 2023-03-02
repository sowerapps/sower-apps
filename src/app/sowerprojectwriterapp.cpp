///////////////////////////////////////////////////////////////////
// Name:        sowerprojectwriterapp.cpp
// Purpose:     Sower Project Writer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowerprojectwriterapp.h"
#include "appi/appifa.h"
#include "filesys/file.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerProjectWriterApp);

bool SowerProjectWriterApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();

    SowerProjectWriterDlg Dlg(0);
    SetTopWindow(&Dlg);
    Dlg.ShowModal();

    return false;
}

const long SowerProjectWriterDlg::ID_ABOUTBUTTON = wxNewId();
const long SowerProjectWriterDlg::ID_BUILDBUTTON = wxNewId();
const long SowerProjectWriterDlg::ID_SOURCELABEL = wxNewId();
const long SowerProjectWriterDlg::ID_SOURCEFILEPICKERCTRL = wxNewId();
const long SowerProjectWriterDlg::ID_TARGETLABEL = wxNewId();
const long SowerProjectWriterDlg::ID_TARGETTEXTCTRL = wxNewId();
const long SowerProjectWriterDlg::ID_PROCESSREFERENCESCHECKBOX = wxNewId();
const long SowerProjectWriterDlg::ID_ROMANFORCHAPTERSCHECKBOX = wxNewId();
const long SowerProjectWriterDlg::ID_ROMANFORVERSESCHECKBOX = wxNewId();
const long SowerProjectWriterDlg::ID_ROMANLOWERCASECHECKBOX = wxNewId();
const long SowerProjectWriterDlg::ID_BOOKNAMESCASECHECKBOX = wxNewId();
const long SowerProjectWriterDlg::ID_LINEBREAKSASSPACECHECKBOX = wxNewId();
const long SowerProjectWriterDlg::ID_MARKERSLABEL = wxNewId();
const long SowerProjectWriterDlg::ID_CVDIVLABEL = wxNewId();
const long SowerProjectWriterDlg::ID_CVDIVTEXTCTRL = wxNewId();
const long SowerProjectWriterDlg::ID_DIVISIONLABEL = wxNewId();
const long SowerProjectWriterDlg::ID_DIVISIONTEXTCTRL = wxNewId();
const long SowerProjectWriterDlg::ID_SPANLABEL = wxNewId();
const long SowerProjectWriterDlg::ID_SPANTEXTCTRL = wxNewId();
const long SowerProjectWriterDlg::ID_BREAKLABEL = wxNewId();
const long SowerProjectWriterDlg::ID_BREAKTEXTCTRL = wxNewId();

SowerProjectWriterDlg::SowerProjectWriterDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    :SwDialog(parent, id, "", pos, size, wxDEFAULT_DIALOG_STYLE, "")
{
    wxGridBagSizer* GridBagSizer1;

    GridBagSizer1 = new wxGridBagSizer(0, 0);
    SourceLabel = new wxStaticText(this, ID_SOURCELABEL, SwApplicationInterface::GetControlString("SID_SOURCE", L"Source"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SOURCELABEL");
	GridBagSizer1->Add(SourceLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SourceFilePickerCtrl = new wxFilePickerCtrl(this, ID_SOURCEFILEPICKERCTRL, wxEmptyString, wxEmptyString, L"*.opf", wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_SOURCEFILEPICKERCTRL");
    GridBagSizer1->Add(SourceFilePickerCtrl, wxGBPosition(1, 0), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);
    TargetLabel = new wxStaticText(this, ID_TARGETLABEL, SwApplicationInterface::GetControlString("SID_TARGET", L"Target"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TARGETLABEL");
	GridBagSizer1->Add(TargetLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TargetTextCtrl = new wxTextCtrl(this, ID_TARGETTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TARGETTEXTCTRL");
    GridBagSizer1->Add(TargetTextCtrl, wxGBPosition(3, 0), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    ProcessReferencesCheckBox = new wxCheckBox(this, ID_PROCESSREFERENCESCHECKBOX, SwApplicationInterface::GetControlString("SID_PROCESSREFERENCES", L"Process references."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PROCESSREFERENCESCHECKBOX");
    ProcessReferencesCheckBox->SetValue(true);
    GridBagSizer1->Add(ProcessReferencesCheckBox, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    RomanForChaptersCheckBox = new wxCheckBox(this, ID_ROMANFORCHAPTERSCHECKBOX, SwApplicationInterface::GetControlString("SID_ROMANNUMERALCHAPTERS", L"Roman numerals for chapters."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ROMANFORCHAPTERSCHECKBOX");
    GridBagSizer1->Add(RomanForChaptersCheckBox, wxGBPosition(5, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    RomanForVersesCheckBox = new wxCheckBox(this, ID_ROMANFORVERSESCHECKBOX, SwApplicationInterface::GetControlString("SID_ROMANNUMERALVERSES", L"Roman numerals for verses."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ROMANFORCVERSESCHECKBOX");
    GridBagSizer1->Add(RomanForVersesCheckBox, wxGBPosition(5, 2), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    RomanLowerCaseCheckBox = new wxCheckBox(this, ID_ROMANLOWERCASECHECKBOX, SwApplicationInterface::GetControlString("SID_ROMANLOWERCASE", L"Roman numerals must be lower case."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ROMANLOWERCASECHECKBOX");
    GridBagSizer1->Add(RomanLowerCaseCheckBox, wxGBPosition(6, 0), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    BookNamesUpperCaseCheckBox = new wxCheckBox(this, ID_BOOKNAMESCASECHECKBOX, SwApplicationInterface::GetControlString("SID_FIRSTLETTERUPPERCASE", L"First letter of book names must be upper case."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_BOOKNAMESCASECHECKBOX");
    GridBagSizer1->Add(BookNamesUpperCaseCheckBox, wxGBPosition(7, 0), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    LineBreaksAsSpaceCheckBox = new wxCheckBox(this, ID_LINEBREAKSASSPACECHECKBOX, SwApplicationInterface::GetControlString("SID_TREATLINEBREAKSASSPACE", L"Treat line breaks as space."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_LINEBREAKSASSPACECHECKBOX");
    GridBagSizer1->Add(LineBreaksAsSpaceCheckBox, wxGBPosition(8, 0), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    MarkersLabel = new wxStaticText(this, ID_MARKERSLABEL, SwApplicationInterface::GetControlString("SID_MARKERS", L"Markers"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SOURCEMARKERS");
  	GridBagSizer1->Add(MarkersLabel, wxGBPosition(9, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

  	CVDivLabel = new wxStaticText(this, ID_CVDIVLABEL, SwApplicationInterface::GetControlString("SID_CVDIV", L"Chap. Vs. division"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CVDIVLABEL");
	GridBagSizer1->Add(CVDivLabel, wxGBPosition(10, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CVDivTextCtrl = new wxTextCtrl(this, ID_CVDIVTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_CVDIVTEXTCTRL");
    CVDivTextCtrl->SetMaxLength(1);
    CVDivTextCtrl->SetValue(L":");
    GridBagSizer1->Add(CVDivTextCtrl, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);

    DivisionLabel = new wxStaticText(this, ID_DIVISIONLABEL, SwApplicationInterface::GetControlString("SID_DIVISION", L"Division"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DIVISIONLABEL");
	GridBagSizer1->Add(DivisionLabel, wxGBPosition(10, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DivisionTextCtrl = new wxTextCtrl(this, ID_DIVISIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DIVISIONTEXTCTRL");
    DivisionTextCtrl->SetMaxLength(1);
    DivisionTextCtrl->SetValue(L",");
    GridBagSizer1->Add(DivisionTextCtrl, wxGBPosition(11, 1), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);

    SpanLabel = new wxStaticText(this, ID_SPANLABEL, SwApplicationInterface::GetControlString("SID_SPAN", L"Span"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SPANLABEL");
	GridBagSizer1->Add(SpanLabel, wxGBPosition(10, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SpanTextCtrl = new wxTextCtrl(this, ID_SPANTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SPANTEXTCTRL");
    SpanTextCtrl->SetMaxLength(1);
    SpanTextCtrl->SetValue(L"-");
    GridBagSizer1->Add(SpanTextCtrl, wxGBPosition(11, 2), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);

    BreakLabel = new wxStaticText(this, ID_BREAKLABEL, SwApplicationInterface::GetControlString("SID_BREAK", L"Break"), wxDefaultPosition, wxDefaultSize, 0, L"ID_BREAKLABEL");
	GridBagSizer1->Add(BreakLabel, wxGBPosition(10, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BreakTextCtrl = new wxTextCtrl(this, ID_BREAKTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_BREAKTEXTCTRL");
    BreakTextCtrl->SetMaxLength(1);
    BreakTextCtrl->SetValue(L";");
    GridBagSizer1->Add(BreakTextCtrl, wxGBPosition(11, 3), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);

    AboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
    GridBagSizer1->Add(AboutButton, wxGBPosition(12, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BuildButton = new wxButton(this, ID_BUILDBUTTON, SwApplicationInterface::GetControlString("SID_BUILD", L"Build"));
    BuildButton->Disable();
    GridBagSizer1->Add(BuildButton, wxGBPosition(12, 3), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);

    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    Connect(ID_TARGETTEXTCTRL,wxEVT_TEXT,(wxObjectEventFunction)&SowerProjectWriterDlg::OnTextChange);
    Connect(ID_PROCESSREFERENCESCHECKBOX,wxEVT_CHECKBOX,(wxObjectEventFunction)&SowerProjectWriterDlg::OnCheckBox);
    Connect(ID_SOURCEFILEPICKERCTRL,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SowerProjectWriterDlg::OnFilePickerCtrlFileChanged);
    Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerProjectWriterDlg::OnAboutButtonClick);
    Connect(ID_BUILDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerProjectWriterDlg::OnBuildButtonClick);

    SetLabel(SwApplicationInterface::GetControlString("SID_SOWERPROJECTWRITER", L"Sower Project Writer"));
    SetIcon(SwApplicationInterface::GetToolsIcon());
}

SowerProjectWriterDlg::~SowerProjectWriterDlg()
{
    SwApplicationInterface::CloseFiles();
}

void SowerProjectWriterDlg::OnAboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERPROJECTWRITER", L"Sower Project Writer"), L"1.0", L"2023");
}

void SowerProjectWriterDlg::OnTextChange(wxCommandEvent& event)
{
    if (SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str().length() && TargetTextCtrl->GetValue().utf8_str().length())
        BuildButton->Enable();
    else
        BuildButton->Disable();
}

void SowerProjectWriterDlg::OnFilePickerCtrlFileChanged(wxFileDirPickerEvent & event)
{
    if (SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str().length() && TargetTextCtrl->GetValue().utf8_str().length())
        BuildButton->Enable();
    else
        BuildButton->Disable();
}

void SowerProjectWriterDlg::OnCheckBox(wxCommandEvent& event)
{
    RomanForChaptersCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
    RomanForVersesCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
    CVDivTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
    DivisionTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
    SpanTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
    BreakTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
}

void SowerProjectWriterDlg::OnBuildButtonClick(wxCommandEvent& event)
{
    EnableControls(false);

    SetProcessReferences(ProcessReferencesCheckBox->IsChecked());
    SetRomanForChapters(RomanForChaptersCheckBox->IsChecked());
    SetRomanForVerses(RomanForVersesCheckBox->IsChecked());
    SetRomanLowerCase(RomanLowerCaseCheckBox->IsChecked());
    SetBookNamesUpperCase(BookNamesUpperCaseCheckBox->IsChecked());
    SetLineBreakIsSpace(LineBreaksAsSpaceCheckBox->IsChecked());
    SetCVDivMarker(static_cast<wchar_t>(CVDivTextCtrl->GetValue()[0]));
    SetDivMarker(static_cast<wchar_t>(DivisionTextCtrl->GetValue()[0]));
    SetSpanMarker(static_cast<wchar_t>(SpanTextCtrl->GetValue()[0]));
    SetBreakMarker(static_cast<wchar_t>(BreakTextCtrl->GetValue()[0]));

    OpenFile(SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str(), MODE_MEMORY, false);
    bool status = Run(TargetTextCtrl->GetValue().utf8_str());

    if (status)
        wxMessageBox(SwApplicationInterface::GetControlString("SID_BUILDCOMPLETE", L"Build complete."));
    else
        wxMessageBox(SwApplicationInterface::GetControlString("SID_BUILDFAILED", L"Build failed."));

    EnableControls(true);
}

void SowerProjectWriterDlg::EnableControls(bool state)
{
    SourceFilePickerCtrl->Enable(state);
    TargetTextCtrl->Enable(state);
    ProcessReferencesCheckBox->Enable(state);
    BuildButton->Enable(state);
    AboutButton->Enable(state);

    if (state)
    {
        RomanForChaptersCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
        RomanForVersesCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
        RomanLowerCaseCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
        BookNamesUpperCaseCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
        BookNamesUpperCaseCheckBox->Enable(ProcessReferencesCheckBox->IsChecked());
        CVDivTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
        DivisionTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
        SpanTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
        BreakTextCtrl->Enable(ProcessReferencesCheckBox->IsChecked());
    }
    else
    {
        RomanForChaptersCheckBox->Disable();
        RomanForVersesCheckBox->Disable();
        RomanLowerCaseCheckBox->Disable();
        BookNamesUpperCaseCheckBox->Disable();
        LineBreaksAsSpaceCheckBox->Disable();
        CVDivTextCtrl->Disable();
        DivisionTextCtrl->Disable();
        SpanTextCtrl->Disable();
        BreakTextCtrl->Disable();
    }
}
