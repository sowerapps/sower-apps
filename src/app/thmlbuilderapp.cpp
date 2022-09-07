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

IMPLEMENT_APP(ThMLBuilderApp);

bool ThMLBuilderApp::OnInit()
{
    SwApplicationInterface::InitBasic();

    ThMLBuilderDlg Dlg(0);
    SetTopWindow(&Dlg);
    Dlg.ShowModal();

    return false;
}

const long ThMLBuilderDlg::ID_SOURCEBUTTON = wxNewId();
const long ThMLBuilderDlg::ID_FILESLISTCTRL = wxNewId();
const long ThMLBuilderDlg::ID_SAVEASLABEL = wxNewId();
const long ThMLBuilderDlg::ID_SAVEASFILEPICKERCTRL = wxNewId();
const long ThMLBuilderDlg::ID_PROGRESSGAUGE = wxNewId();
const long ThMLBuilderDlg::ID_ABOUTBUTTON = wxNewId();
const long ThMLBuilderDlg::ID_STATUSLABEL = wxNewId();
const long ThMLBuilderDlg::ID_BUILDBUTTON = wxNewId();

ThMLBuilderDlg::ThMLBuilderDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxGridBagSizer* GridBagSizer1;
    wxGridBagSizer* GridBagSizer2;
    wxGridBagSizer* GridBagSizer3;

    wxDialog::Create(parent, id, L"Html Converter", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    sourceButton = new wxButton(this, ID_SOURCEBUTTON, SwApplicationInterface::GetControlString("SID_SELECTFILES", L"Select files"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SOURCEBUTTON");
    GridBagSizer1->Add(sourceButton, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    filesListCtrl = new wxRearrangeCtrl(this, ID_FILESLISTCTRL,wxDefaultPosition,wxSize(400,200),wxArrayInt(0),wxArrayString (), 0, wxDefaultValidator, L"ID_FILESLISTCTRL");
    GridBagSizer1->Add(filesListCtrl, wxGBPosition(1, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    GridBagSizer2 = new wxGridBagSizer(0, 0);
    saveasLabel = new wxStaticText(this, ID_SAVEASLABEL, SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SAVEASLABEL");
    GridBagSizer2->Add(saveasLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    saveasFilePickerCtrl = new SwFittedFilePickerCtrl(this, ID_SAVEASFILEPICKERCTRL, wxEmptyString, wxEmptyString, SwApplicationInterface::GetControlString("SID_THMLFILTER", L"ThML files (*.thm)|*.thm"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_SAVEASFILEPICKERCTRL");
    GridBagSizer2->Add(saveasFilePickerCtrl, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    GridBagSizer1->Add(GridBagSizer2, wxGBPosition(2, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 0);

    progressGauge = new wxGauge(this, ID_PROGRESSGAUGE, 100, wxDefaultPosition, wxSize(-1,7), 0, wxDefaultValidator, L"ID_PROGRESSGAUGE");
    GridBagSizer1->Add(progressGauge, wxGBPosition(3, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    statusLabel = new wxStaticText(this, ID_STATUSLABEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, L"ID_STATUSLABEL");
    GridBagSizer1->Add(statusLabel, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    aboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
    GridBagSizer1->Add(aboutButton, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    GridBagSizer3 = new wxGridBagSizer(0, 0);
    okButton = new wxButton(this, ID_BUILDBUTTON, SwApplicationInterface::GetControlString("SID_BUILD", L"Build"));
    GridBagSizer3->Add(okButton, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer1->Add(GridBagSizer3, wxGBPosition(5, 1), wxDefaultSpan, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);

    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);
    sourceFileDialog = new wxFileDialog(this, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTFILES", L"Select files")).GetArray(), wxEmptyString, wxEmptyString, SwStringW(SwApplicationInterface::GetControlString("SID_HTMLFILTER", L"Html files (*.htm;*.html)|*.htm;*.html")).GetArray(), wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE|wxFD_CHANGE_DIR, wxDefaultPosition, wxDefaultSize, L"wxFileDialog");

    Connect(ID_SOURCEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnSourceButtonClick);
    Connect(ID_BUILDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnOKButtonClick);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnQuit);
    Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ThMLBuilderDlg::OnaboutButtonClick);

    Bind(wxEVT_THREAD, &ThMLBuilderDlg::OnThreadUpdate, this);
    SetIcon(SwApplicationInterface::GetToolsIcon());
    SetLabel(SwApplicationInterface::GetControlString("SID_THMLBUILDER", L"ThML Builder"));
}

ThMLBuilderDlg::~ThMLBuilderDlg()
{
    Unbind(wxEVT_THREAD, &ThMLBuilderDlg::OnThreadUpdate, this);
}

void ThMLBuilderDlg::OnSaveAsFilePickerCtrlFileChanged(wxFileDirPickerEvent& event)
{
    Reset();
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
}

void ThMLBuilderDlg::Reset()
{
    statusLabel->SetLabel("");
    progressGauge->SetValue(0);
}

void ThMLBuilderDlg::OnQuit(wxCommandEvent& event)
{
    if (GetThread() && GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }

    Close();
}

void ThMLBuilderDlg::OnOKButtonClick(wxCommandEvent& event)
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

    m_div = 0;
    m_par = 0;
    m_item = 0;

    if (!filesListCtrl->GetList()->GetCount())
    {
        return (wxThread::ExitCode)0;
    }

    if (saveasFilePickerCtrl->GetFileName().GetSize() == 0)
    {
        return (wxThread::ExitCode)0;
    }

    FILE * output = SwFopen(saveasFilePickerCtrl->GetFileName().GetFullPath().utf8_str(), FMD_RWC);

    if (!output)
    {
        statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_FAILEDTOCREATEFILE", L"Failed to create file."));
        return (wxThread::ExitCode)0;
    }

    okButton->Disable();

    SwThMLParser parser;
    parser.SetThML_ElementArray();
    parser.SetWindow(this);
    parser.SetProgressData(&m_progressData);

    m_progressData.docontinue = true;

    SwThMLUtility::WriteOpenHeader(output);
    SwThMLUtility::WriteDublinCore(output);
    SwThMLUtility::WriteCloseHeader(output);

    statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_PROCESSING", L"Processing ..."));

    for (unsigned int i = 0; i < filesListCtrl->GetList()->GetCount(); i ++)
    {
        if (!m_progressData.docontinue)
        {
            statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_PROCESSTERMINATED", L"Process terminated."));
            break;
        }

        if (!filesListCtrl->GetList()->IsChecked(i))
            continue;

        title = "unknown";

        if (!parser.OpenFile(filesListCtrl->GetList()->GetString(i).utf8_str(), MODE_MEMORY, false))
            continue;

        statusLabel->SetLabel(filesListCtrl->GetList()->GetString(i).utf8_str());

        startNode = parser.FindElement(0, THML_TITLE, NODE_TYPE_BEGIN_TAG);

        if (startNode != NODE_ID_INVALID)
        {
            parser.GetDataBetweenMates(startNode, title, false);
        }

        fprintf(output, "\n<div1 title=\"%s\" id=\"%s\">\n", title.GetArray(), GenerateId(THML_DIV1));

        startNode = parser.FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);

        SetIds(&parser);

        if (startNode != NODE_ID_INVALID && parser.GetNodeMate(startNode) != NODE_ID_INVALID)
        {
            parser.GetDataBetweenMates(startNode, data, false);
            fputs(data, output);
        }

        fputs("\n</div1>", output);
        parser.CloseFile();
    }

    SwThMLUtility::WriteFooter(output);
    fclose(output);
    statusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_FINISHED", L"Finished."));
    okButton->Enable();

    return (wxThread::ExitCode)0;
}

void ThMLBuilderDlg::OnaboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_THMLBUILDER", L"ThML Builder"), SVSTR, L"2019");
}

const char * ThMLBuilderDlg::GenerateId(swUI16 element)
{
    static char id[200];
    SwString roman;

    if (element >= THML_DIV1 && element <= THML_DIV6)
    {
        m_div ++;
        m_par = 0;
        m_item = 0;
        SwString::ToRoman(roman, m_div, false);
        sprintf(id, "%s", roman.GetArray());
    }
    else if (element == THML_P)
    {
        m_par ++;
        m_item = 0;
        SwString::ToRoman(roman, m_div, false);
        sprintf(id, "%s.p%u", roman.GetArray(), m_par);
    }
    else if (!IsSkipElement(element))
    {
        m_item ++;
        SwString::ToRoman(roman, m_div, false);
        sprintf(id, "%s.p%u-%u", roman.GetArray(), m_par, m_item);
    }

    return id;
}

bool ThMLBuilderDlg::IsSkipElement(swUI16 element)
{
    if (element >= INT_UNKNOWN)
        return true;

    switch (element)
    {
    case THML_B :
    case THML_I :
    case THML_EM :
    case THML_S :
    case THML_STRIKE :
    case THML_STRONG :
    case THML_U :
    case THML_FONT :
    case THML_Q :
    case THML_STYLE :
        return true;
    default :
        return false;
    }

    return false;
}

void ThMLBuilderDlg::SetIds(SwThMLParser * parser)
{
    SwString data;

    swUI32 start = parser->FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);
    if (start == NODE_ID_INVALID)
        return;

    swUI32 end = parser->GetNodeMate(start);

    start ++;

    for (swUI32 i = start; i < end; i ++)
    {
        if (parser->GetNodeType(i) != NODE_TYPE_BEGIN_TAG)
            continue;

        if (parser->GetNamedValueFromNode(i, "id", data))
            continue;

        if (IsSkipElement(parser->GetNodeElementIdentifier(i)))
            continue;

        parser->InsertNamedValueInNode(i, "id", GenerateId(parser->GetNodeElementIdentifier(i)));
    }
}
