///////////////////////////////////////////////////////////////////
// Name:        thmlbuilderapp.cpp
// Purpose:     ThML Builder
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/thmlbuilderapp.h"
#include "thml/thml_utility.h"
#include "appi/appifa.h"
#include "string/string.h"
#include "html/html_encoded_char.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(ThMLBuilderApp);

bool ThMLBuilderApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();

    ThMLBuilderDlg Dlg(0);
    SetTopWindow(&Dlg);
    Dlg.ShowModal();

    return false;
}

const long ThMLBuilderDlg::ID_TITLELABEL = wxNewId();
const long ThMLBuilderDlg::ID_TITLETEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_CREATORLABEL = wxNewId();
const long ThMLBuilderDlg::ID_CREATORTEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_PUBLISHERLABEL = wxNewId();
const long ThMLBuilderDlg::ID_PUBLISHERTEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_SUBJECTLABEL = wxNewId();
const long ThMLBuilderDlg::ID_SUBJECTTEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_SCHEMELABEL = wxNewId();
const long ThMLBuilderDlg::ID_SCHEMECOMBOBOX = wxNewId();
const long ThMLBuilderDlg::ID_DATELABEL = wxNewId();
const long ThMLBuilderDlg::ID_DATETEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_TYPELABEL = wxNewId();
const long ThMLBuilderDlg::ID_TYPETEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_FORMATLABEL = wxNewId();
const long ThMLBuilderDlg::ID_FORMATTEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_IDENTIFIERLABEL = wxNewId();
const long ThMLBuilderDlg::ID_IDENTIFIERTEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_SOURCELABEL = wxNewId();
const long ThMLBuilderDlg::ID_SOURCETEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_LANGUAGELABEL = wxNewId();
const long ThMLBuilderDlg::ID_LANGUAGETEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_RIGHTSLABEL = wxNewId();
const long ThMLBuilderDlg::ID_RIGHTSTEXTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_SOURCEBUTTON = wxNewId();
const long ThMLBuilderDlg::ID_FILESLISTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_SAVEASLABEL = wxNewId();
const long ThMLBuilderDlg::ID_SAVEASFILEPICKERCTRL = wxNewId();
const long ThMLBuilderDlg::ID_PROGRESSGAUGE = wxNewId();
const long ThMLBuilderDlg::ID_ABOUTBUTTON = wxNewId();
const long ThMLBuilderDlg::ID_STATUSLABEL = wxNewId();
const long ThMLBuilderDlg::ID_BUILDBUTTON = wxNewId();
const long ThMLBuilderDlg::ID_CSSLABEL = wxNewId();
const long ThMLBuilderDlg::ID_CSSFILEPICKERCTRL = wxNewId();
const long ThMLBuilderDlg::ID_USEPROJECTFILECHECKBOX = wxNewId();
const long ThMLBuilderDlg::ID_PROJECTFILEPICKERCTRL = wxNewId();

ThMLBuilderDlg::ThMLBuilderDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxGridBagSizer* GridBagSizer1;

    wxDialog::Create(parent, id, L"ThML Builder", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    TitleLabel = new wxStaticText(this, ID_TITLELABEL, SwApplicationInterface::GetControlString("SID_TITLE", L"Title"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
    GridBagSizer1->Add(TitleLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TitleTextCtrl = new wxTextCtrl(this, ID_TITLETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TITLETEXTCTRL");
    GridBagSizer1->Add(TitleTextCtrl, wxGBPosition(0, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    CreatorLabel = new wxStaticText(this, ID_CREATORLABEL, SwApplicationInterface::GetControlString("SID_CREATOR", L"Creator"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CREATORLABEL");
    GridBagSizer1->Add(CreatorLabel, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CreatorTextCtrl = new wxTextCtrl(this, ID_CREATORTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_CREATORTEXTCTRL");
    GridBagSizer1->Add(CreatorTextCtrl, wxGBPosition(1, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    PublisherLabel = new wxStaticText(this, ID_PUBLISHERLABEL, SwApplicationInterface::GetControlString("SID_PUBLISHER", L"Publisher"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PUBLISHERLABEL");
    GridBagSizer1->Add(PublisherLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PublisherTextCtrl = new wxTextCtrl(this, ID_PUBLISHERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PUBLISHERTEXTCTRL");
    GridBagSizer1->Add(PublisherTextCtrl, wxGBPosition(2, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    SubjectLabel = new wxStaticText(this, ID_SUBJECTLABEL, SwApplicationInterface::GetControlString("SID_SUBJECT", L"Subject"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SUBJECTLABEL");
    GridBagSizer1->Add(SubjectLabel, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SubjectTextCtrl = new wxTextCtrl(this, ID_SUBJECTTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SUBJECTTEXTCTRL");
    SubjectTextCtrl->SetMinSize(wxSize(50, -1));
    GridBagSizer1->Add(SubjectTextCtrl, wxGBPosition(3, 1), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    SchemeLabel = new wxStaticText(this, ID_SCHEMELABEL, SwApplicationInterface::GetControlString("SID_SCHEME", L"Scheme"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SCHEMELABEL");
    GridBagSizer1->Add(SchemeLabel, wxGBPosition(3, 2), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    SchemeComboBox = new wxComboBox(this, ID_SCHEMECOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SCHEMECOMBOBOX");
    GridBagSizer1->Add(SchemeComboBox, wxGBPosition(3, 3), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SchemeComboBox->Append("ccel");
    SchemeComboBox->Append("lccn");
    SchemeComboBox->Append("sw");

    DateLabel = new wxStaticText(this, ID_DATELABEL, SwApplicationInterface::GetControlString("SID_DATE", L"Date"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DATELABEL");
    GridBagSizer1->Add(DateLabel, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DateTextCtrl = new wxTextCtrl(this, ID_DATETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DATETEXTCTRL");
    GridBagSizer1->Add(DateTextCtrl, wxGBPosition(4, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    TypeLabel = new wxStaticText(this, ID_TYPELABEL, SwApplicationInterface::GetControlString("SID_TYPE", L"Type"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TYPELABEL");
    GridBagSizer1->Add(TypeLabel, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TypeTextCtrl = new wxTextCtrl(this, ID_TYPETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TYPETEXTCTRL");
    GridBagSizer1->Add(TypeTextCtrl, wxGBPosition(5, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    FormatLabel = new wxStaticText(this, ID_FORMATLABEL, SwApplicationInterface::GetControlString("SID_FORMAT", L"Format"), wxDefaultPosition, wxDefaultSize, 0, L"ID_FORMATLABEL");
    GridBagSizer1->Add(FormatLabel, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FormatTextCtrl = new wxTextCtrl(this, ID_FORMATTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FORMATTEXTCTRL");
    GridBagSizer1->Add(FormatTextCtrl, wxGBPosition(6, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    IdentifierLabel = new wxStaticText(this, ID_IDENTIFIERLABEL, SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERLABEL");
    GridBagSizer1->Add(IdentifierLabel, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdentifierTextCtrl = new wxTextCtrl(this, ID_IDENTIFIERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDENTIFIERTEXTCTRL");
    GridBagSizer1->Add(IdentifierTextCtrl, wxGBPosition(7, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    SourceLabel = new wxStaticText(this, ID_SOURCELABEL, SwApplicationInterface::GetControlString("SID_SOURCE", L"Source"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SOURCELABEL");
    GridBagSizer1->Add(SourceLabel, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SourceTextCtrl = new wxTextCtrl(this, ID_SOURCETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SOURCETEXTCTRL");
    GridBagSizer1->Add(SourceTextCtrl, wxGBPosition(8, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    LanguageLabel = new wxStaticText(this, ID_LANGUAGELABEL, SwApplicationInterface::GetControlString("SID_LANGUAGE", L"Language"), wxDefaultPosition, wxDefaultSize, 0, L"ID_LANGUAGELABEL");
    GridBagSizer1->Add(LanguageLabel, wxGBPosition(9, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LanguageTextCtrl = new wxTextCtrl(this, ID_LANGUAGETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_LANGUAGETEXTCTRL");
    GridBagSizer1->Add(LanguageTextCtrl, wxGBPosition(9, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    RightsLabel = new wxStaticText(this, ID_RIGHTSLABEL, SwApplicationInterface::GetControlString("SID_RIGHTS", L"Rights"), wxDefaultPosition, wxDefaultSize, 0, L"ID_RIGHTSLABEL");
    GridBagSizer1->Add(RightsLabel, wxGBPosition(10, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RightsTextCtrl = new wxTextCtrl(this, ID_RIGHTSTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_RIGHTSTEXTCTRL");
    GridBagSizer1->Add(RightsTextCtrl, wxGBPosition(10, 1), wxGBSpan(1, 4), wxALL|wxEXPAND, 5);

    cssLabel = new wxStaticText(this, ID_CSSLABEL, SwApplicationInterface::GetControlString("SID_CSSFILE", L"Css File"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CSSFILELABEL");
    GridBagSizer1->Add(cssLabel, wxGBPosition(0, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    cssFilePickerCtrl = new SwFittedFilePickerCtrl(this, ID_CSSFILEPICKERCTRL, wxEmptyString, wxEmptyString, SwApplicationInterface::GetControlString("SID_CSSFILTER", L"Css files (*.css)|*.css"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_FILE_MUST_EXIST|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_SAVEASFILEPICKERCTRL");
    GridBagSizer1->Add(cssFilePickerCtrl, wxGBPosition(0, 6), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    saveasLabel = new wxStaticText(this, ID_SAVEASLABEL, SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SAVEASLABEL");
    GridBagSizer1->Add(saveasLabel, wxGBPosition(1, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    saveasFilePickerCtrl = new SwFittedFilePickerCtrl(this, ID_SAVEASFILEPICKERCTRL, wxEmptyString, wxEmptyString, SwApplicationInterface::GetControlString("SID_THMLFILTER", L"ThML files (*.thm)|*.thm"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_SAVEASFILEPICKERCTRL");
    GridBagSizer1->Add(saveasFilePickerCtrl, wxGBPosition(1, 6), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    sourceButton = new wxButton(this, ID_SOURCEBUTTON, SwApplicationInterface::GetControlString("SID_SELECTFILES", L"Select files"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SOURCEBUTTON");
    GridBagSizer1->Add(sourceButton, wxGBPosition(2, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    filesListCtrl = new wxRearrangeCtrl(this, ID_FILESLISTCTRL,wxDefaultPosition,wxSize(400,200),wxArrayInt(0),wxArrayString (), 0, wxDefaultValidator, L"ID_FILESLISTCTRL");
    GridBagSizer1->Add(filesListCtrl, wxGBPosition(3, 5), wxGBSpan(8, 4), wxALL|wxEXPAND, 5);

    useprjFileCheckBox = new wxCheckBox(this, ID_USEPROJECTFILECHECKBOX, SwApplicationInterface::GetControlString("SID_USEPRJFILE", L"Use project file."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_USEPRJFILECHECKBOX");
    GridBagSizer1->Add(useprjFileCheckBox, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);

    projectFilePickerCtrl = new SwFittedFilePickerCtrl(this, ID_PROJECTFILEPICKERCTRL, wxEmptyString, wxEmptyString, SwApplicationInterface::GetControlString("SID_PRJFILTER", L"Sower Project files (*.swprj)|*.swprj"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_FILE_MUST_EXIST|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_PROJECTFILEPICKERCTRL");
    GridBagSizer1->Add(projectFilePickerCtrl, wxGBPosition(11, 1), wxGBSpan(1, 5), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    progressGauge = new wxGauge(this, ID_PROGRESSGAUGE, 100, wxDefaultPosition, wxSize(-1,7), 0, wxDefaultValidator, L"ID_PROGRESSGAUGE");
    GridBagSizer1->Add(progressGauge, wxGBPosition(12, 0), wxGBSpan(1, 9), wxALL|wxEXPAND, 5);

    statusLabel = new wxStaticText(this, ID_STATUSLABEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, L"ID_STATUSLABEL");
    GridBagSizer1->Add(statusLabel, wxGBPosition(13, 0), wxGBSpan(1, 9), wxALL|wxEXPAND, 5);

    aboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
    GridBagSizer1->Add(aboutButton, wxGBPosition(14, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    buildButton = new wxButton(this, ID_BUILDBUTTON, SwApplicationInterface::GetControlString("SID_BUILD", L"Build"));
    GridBagSizer1->Add(buildButton, wxGBPosition(14, 8), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    buildButton->Disable();
    sourceButton->Disable();
    projectFilePickerCtrl->Disable();
    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);
    sourceFileDialog = new wxFileDialog(this, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTFILES", L"Select files")).GetArray(), wxEmptyString, wxEmptyString, SwStringW(SwApplicationInterface::GetControlString("SID_HTMLFILTER", L"Html files (*.htm;*.html)|*.htm;*.html")).GetArray(), wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE|wxFD_CHANGE_DIR, wxDefaultPosition, wxDefaultSize, L"wxFileDialog");

    Connect(ID_USEPROJECTFILECHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnUseProjectFileCheckBoxClick);
    Connect(ID_SAVEASFILEPICKERCTRL,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&ThMLBuilderDlg::OnSaveAsFilePickerCtrlFileChanged);
    Connect(ID_PROJECTFILEPICKERCTRL,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&ThMLBuilderDlg::OnPrjFilePickerCtrlFileChanged);
    Connect(ID_SOURCEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnSourceButtonClick);
    Connect(ID_BUILDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnBuildButtonClick);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnQuit);
    Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnaboutButtonClick);

    Bind(wxEVT_THREAD, &ThMLBuilderDlg::OnThreadUpdate, this);
    SetIcon(SwApplicationInterface::GetToolsIcon());
    SetLabel(SwApplicationInterface::GetControlString("SID_THMLBUILDER", L"ThML Builder"));
}

ThMLBuilderDlg::~ThMLBuilderDlg()
{
    Unbind(wxEVT_THREAD, &ThMLBuilderDlg::OnThreadUpdate, this);
    SwApplicationInterface::CloseFiles();
}

void ThMLBuilderDlg::OnSaveAsFilePickerCtrlFileChanged(wxFileDirPickerEvent& event)
{
    sourceButton->Enable((bool)saveasFilePickerCtrl->GetFileName().GetFullPath().length());
}

void ThMLBuilderDlg::OnPrjFilePickerCtrlFileChanged(wxFileDirPickerEvent& event)
{
    buildButton->Enable((bool)projectFilePickerCtrl->GetFileName().GetFullPath().length());
}

void ThMLBuilderDlg::OnSourceButtonClick(wxCommandEvent& event)
{
    if (sourceFileDialog->ShowModal() == wxID_CANCEL)
        return;

    wxArrayString files;
    sourceFileDialog->GetPaths(files);
    filesListCtrl->GetList()->Clear();
    filesListCtrl->GetList()->Set(files);

    for (unsigned int i = 0; i < filesListCtrl->GetList()->GetCount(); i ++)
    {
        filesListCtrl->GetList()->Check(i, true);
    }

    if (filesListCtrl->GetList()->GetCount() && saveasFilePickerCtrl->GetFileName().GetFullPath().length())
    {
        buildButton->Enable();
    }
}

void ThMLBuilderDlg::Reset()
{
    statusLabel->SetLabel("");
    progressGauge->SetValue(0);
    filesListCtrl->GetList()->Clear();
    sourceButton->Disable();
    buildButton->Disable();
    TitleTextCtrl->Clear();
    CreatorTextCtrl->Clear();
    PublisherTextCtrl->Clear();
    SubjectTextCtrl->Clear();
    DateTextCtrl->Clear();
    TypeTextCtrl->Clear();
    FormatTextCtrl->Clear();
    IdentifierTextCtrl->Clear();
    SourceTextCtrl->Clear();
    LanguageTextCtrl->Clear();
    RightsTextCtrl->Clear();
    saveasFilePickerCtrl->SetPath("");
    projectFilePickerCtrl->SetPath("");
}

void ThMLBuilderDlg::OnQuit(wxCommandEvent& event)
{
    if (GetThread() && GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }

    Close();
}

void ThMLBuilderDlg::OnBuildButtonClick(wxCommandEvent& event)
{
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }
}

void ThMLBuilderDlg::OnUseProjectFileCheckBoxClick(wxCommandEvent& event)
{
    SetControlStates(!event.IsChecked());
    if (useprjFileCheckBox->GetValue())
    {
        projectFilePickerCtrl->Enable();
        buildButton->Enable((bool) projectFilePickerCtrl->GetFileName().GetFullPath().length());
    }
    else
    {
        projectFilePickerCtrl->Disable();
        buildButton->Enable((bool)(filesListCtrl->GetList()->GetCount() && saveasFilePickerCtrl->GetFileName().GetFullPath().length()));
    }

}

void ThMLBuilderDlg::OnThreadUpdate(wxThreadEvent& evt)
{
    if (!evt.GetInt())
        progressGauge->SetRange(m_progressData.range);
    else
    {
        if (m_progressData.pos > (unsigned) progressGauge->GetRange())
            progressGauge->SetValue(progressGauge->GetRange());
        else
            progressGauge->SetValue(m_progressData.pos);
    }
}

wxThread::ExitCode ThMLBuilderDlg::Entry()
{
    SwString title, data;
    swUI32 startNode;

    m_parser.SetThML_ElementArray();
    m_parser.SetWindow(this);
    m_parser.SetProgressData(&m_progressData);
    m_progressData.docontinue = true;

    if (!useprjFileCheckBox->GetValue())
    {
        m_pageData.Reset();

        if (!filesListCtrl->GetList()->GetCount())
        {
            return (wxThread::ExitCode)0;
        }

        if (saveasFilePickerCtrl->GetFileName().GetFullPath().length() == 0)
        {
            return (wxThread::ExitCode)0;
        }

        if (!m_output.Open(saveasFilePickerCtrl->GetFileName().GetFullPath().utf8_str(), FMD_RWC))
        {
            statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_FAILEDTOCREATEFILE", L"Failed to create file."));
            return (wxThread::ExitCode)0;
        }

        SetControlStates(false);

        SwThMLUtility::WriteOpenHeader(m_output.m_file);
        WriteDublinCore();
        WriteCSS();
        SwThMLUtility::WriteCloseHeader(m_output.m_file);

        statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_PROCESSING", L"Processing ..."));

        CollectFileData();

        for (unsigned int i = 0; i < m_pageData.GetCount(); i ++)
        {
            if (!m_progressData.docontinue)
            {
                statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_PROCESSTERMINATED", L"Process terminated."));
                break;
            }

            title = "unknown";

            if (!m_parser.OpenFile(m_pageData.GetAt(i).GetStrA(), MODE_MEMORY, false))
                continue;

            startNode = m_parser.FindElement(0, THML_TITLE, NODE_TYPE_BEGIN_TAG);

            if (startNode != NODE_ID_INVALID)
            {
                m_parser.GetDataBetweenMates(startNode, title, false);
            }

            title.CleanNewLines();
            fprintf(m_output.m_file, "\n<div1 title=\"%s\" id=\"%s\">\n", title.GetArray(), m_pageData.GetAt(i).GetStrB().GetArray());

            startNode = m_parser.FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);

            ProcessReferences(&m_parser);
            SetIds(&m_parser, i);
            RepairLinks(&m_parser);

            if (startNode != NODE_ID_INVALID && m_parser.GetNodeMate(startNode) != NODE_ID_INVALID)
            {
                m_parser.GetDataBetweenMates(startNode, data, false);
                fwrite(data.GetArray(), 1, data.Strlen(), m_output.m_file);
            }

            fputs("\n</div1>", m_output.m_file);
            m_parser.CloseFile();
        }

        SwThMLUtility::WriteFooter(m_output.m_file);
        m_output.Close();
    }
    else
    {
        if (!OpenFile(projectFilePickerCtrl->GetFileName().GetFullPath().utf8_str(), MODE_MEMORY, false))
        {
            statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_PROCESSTERMINATED", L"Process terminated."));
            return (wxThread::ExitCode)0;
        }

        SetControlStates(false);
        Run();
    }


    statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_FINISHED", L"Finished."));
    SetControlStates(true);

    return (wxThread::ExitCode)0;
}

void ThMLBuilderDlg::OnaboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_THMLBUILDER", L"ThML Builder"), SVSTR, L"2019");
}

void ThMLBuilderDlg::WriteCSS()
{
    if (cssFilePickerCtrl->GetPath().Len() != 0)
    {
        char s[1000];
        int bytes;

        FILE * f = SwFopen(cssFilePickerCtrl->GetFileName().GetFullPath().utf8_str(), FMD_R);
        if (f)
        {
            fputs("\n<style type=\"text/css\">\n", m_output.m_file);

            for(;;)
            {
                bytes = fread(s, 1, 1000, f);
                if (!bytes)
                    break;
                fwrite(s, 1, bytes, m_output.m_file);
            }
        }

        fputs("\n</style>\n", m_output.m_file);
    }
}

void ThMLBuilderDlg::CollectFileData()
{
    unsigned int count = 0;
    SwString roman;

    m_pageData.Reset();

    for (unsigned int i = 0; i < filesListCtrl->GetList()->GetCount(); i ++)
    {
        if (!filesListCtrl->GetList()->IsChecked(i))
            continue;

        count ++;
        SwString::ToRoman(roman, count, false);
        m_pageData.Add(filesListCtrl->GetList()->GetString(i).utf8_str(), roman, "");
    }
}

void ThMLBuilderDlg::WriteDublinCore()
{
    SwString buffer;
    SwString title;

    SwHtmlEncodedChar::EncodeString(TitleTextCtrl->GetValue().utf8_str(), title, false);
    if (title.Strlen() == 0)
        title = "Unknown";

    buffer  = "<electronicEdInfo>\n";
    buffer += "<DC>\n<DC.Title>";
    buffer += title.GetArray();
    buffer += "</DC.Title>\n<DC.Creator>";
    buffer += CreatorTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Creator>\n<DC.Publisher>";
    buffer += PublisherTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Publisher>\n<DC.Subject scheme=\"";
    buffer += SchemeComboBox->GetValue().utf8_str();
    buffer += "\">";
    buffer += SubjectTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Subject>\n<DC.Date>";
    buffer += DateTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Date>\n<DC.Type>";
    buffer += TypeTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Type>\n<DC.Format>";
    buffer += FormatTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Format>\n<DC.Identifier scheme=\"\">";
    buffer += IdentifierTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Identifier>\n<DC.Source>";
    buffer += SourceTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Source>\n<DC.Language>";
    buffer += LanguageTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Language>\n<DC.Rights>";
    buffer += RightsTextCtrl->GetValue().utf8_str();
    buffer += "</DC.Rights>\n</DC>\n";
    buffer += "</electronicEdInfo>\n";

    fwrite(buffer.GetArray(), 1, buffer.Strlen(), m_output.m_file);
}

void ThMLBuilderDlg::SetControlStates(bool state)
{
    TitleTextCtrl->Enable(state);
    CreatorTextCtrl->Enable(state);
    PublisherTextCtrl->Enable(state);
    SubjectTextCtrl->Enable(state);
    SchemeComboBox->Enable(state);
    DateTextCtrl->Enable(state);
    TypeTextCtrl->Enable(state);
    FormatTextCtrl->Enable(state);
    IdentifierTextCtrl->Enable(state);
    SourceTextCtrl->Enable(state);
    LanguageTextCtrl->Enable(state);
    RightsTextCtrl->Enable(state);
    sourceButton->Enable(state);
    saveasFilePickerCtrl->Enable(state);
    cssFilePickerCtrl->Enable(state);
    filesListCtrl->Enable(state);
    filesListCtrl->GetList()->Enable(state);
}
