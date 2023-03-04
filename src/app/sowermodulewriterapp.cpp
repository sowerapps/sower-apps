///////////////////////////////////////////////////////////////////
// Name:        sowermodulewriterapp.cpp
// Purpose:     Sower Module Writer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowermodulewriterapp.h"
#include "appi/appifa.h"
#include "module/category.h"
#include "module/module.h"
#include "thml/thml_utility.h"
#include "filesys/bzcompression.h"
#include "dialogs/carddlg.h"
#include "bible/standard_bible.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerModuleWriterApp);

bool SowerModuleWriterApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();
    SwApplicationInterface::LoadPlugIns();
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadModules();
    SowerModuleWriterDlg Dlg(0);
    SetTopWindow(&Dlg);
    Dlg.ShowModal();

    return false;
}

const long SowerModuleWriterDlg::ID_SOURCELABEL = wxNewId();
const long SowerModuleWriterDlg::ID_SOURCEFILEPICKERCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_SAVEASLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_SAVEASFILEPICKERCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_TITLELABEL = wxNewId();
const long SowerModuleWriterDlg::ID_ABBREVIATIONLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_IDENTIFIERLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_TITLETEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_ABBREVIATIONTEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_IDENTIFIERTEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_CATEGORYLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_GROUPLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_VERSIFICATIONLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_CATEGORYCHOICE = wxNewId();
const long SowerModuleWriterDlg::ID_GROUPCOMBOBOX = wxNewId();
const long SowerModuleWriterDlg::ID_VERSIFICATIONCOMBOBOX = wxNewId();
const long SowerModuleWriterDlg::ID_ALLOWCOPYCHECKBOX = wxNewId();
const long SowerModuleWriterDlg::ID_OFNLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_ENCRYPTCHECKBOX = wxNewId();
const long SowerModuleWriterDlg::ID_COMPRESSCHECKBOX = wxNewId();
const long SowerModuleWriterDlg::ID_OFNTEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_PROGRESSGAUGE = wxNewId();
const long SowerModuleWriterDlg::ID_REPORTTEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_ABOUTBUTTON = wxNewId();
const long SowerModuleWriterDlg::ID_BUILDBUTTON = wxNewId();
const long SowerModuleWriterDlg::ID_PASSWORDLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_PASSWORDTEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_PUBLISHERLABEL = wxNewId();
const long SowerModuleWriterDlg::ID_PUBLISHERTEXTCTRL = wxNewId();
const long SowerModuleWriterDlg::ID_CANCELBUTTON = wxNewId();

SowerModuleWriterDlg::SowerModuleWriterDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    :SwDialog(parent, id, L"", pos, size, wxDEFAULT_DIALOG_STYLE, L"")
{
    m_key = NODE_ID_INVALID_16;
    wxGridBagSizer* GridBagSizer1;
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    SourceLabel = new wxStaticText(this, ID_SOURCELABEL, SwApplicationInterface::GetControlString("SID_SOURCE", L"Source"), wxDefaultPosition, wxDefaultSize, 0, "ID_SOURCELABEL");
    GridBagSizer1->Add(SourceLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SourceFilePickerCtrl = new wxFilePickerCtrl(this, ID_SOURCEFILEPICKERCTRL, wxEmptyString, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTAFILE", L"Select a file")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_THMLFILTER", L"ThML files (*.thm)|*.thm")).GetArray(), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_SOURCEFILEPICKERCTRL");
    GridBagSizer1->Add(SourceFilePickerCtrl, wxGBPosition(1, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    SaveasLabel = new wxStaticText(this, ID_SAVEASLABEL, SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SAVEASLABEL");
    GridBagSizer1->Add(SaveasLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SaveasFilePickerCtrl = new wxFilePickerCtrl(this, ID_SAVEASFILEPICKERCTRL, wxEmptyString, SwStringW(SwApplicationInterface::GetControlString("SID_SAVEAS", L"Save as")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_SMDFILTER", L"Sower module files (*.smd;)|*.smd;")).GetArray(), wxDefaultPosition, wxDefaultSize, wxFLP_SAVE|wxFLP_OVERWRITE_PROMPT|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"IDSAVEAS_FILEPICKERCTRL");
    GridBagSizer1->Add(SaveasFilePickerCtrl, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    TitleLabel = new wxStaticText(this, ID_TITLELABEL, SwApplicationInterface::GetControlString("SID_TITLE", L"Title"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
    GridBagSizer1->Add(TitleLabel, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    AbbreviationLabel = new wxStaticText(this, ID_ABBREVIATIONLABEL, SwApplicationInterface::GetControlString("SID_ABBREVIATION", L"Abbreviation"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ABBREVIATIONLABEL");
    GridBagSizer1->Add(AbbreviationLabel, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdentifierLabel = new wxStaticText(this, ID_IDENTIFIERLABEL, SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERLABEL");
    GridBagSizer1->Add(IdentifierLabel, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TitleTextCtrl = new wxTextCtrl(this, ID_TITLETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TITLETEXTCTRL");
    GridBagSizer1->Add(TitleTextCtrl, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    AbbreviationTextCtrl = new wxTextCtrl(this, ID_ABBREVIATIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABBREVIATIONTEXTCTRL");
    GridBagSizer1->Add(AbbreviationTextCtrl, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
    IdentifierTextCtrl = new wxTextCtrl(this, ID_IDENTIFIERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDENTIFIERTEXTCTRL");
    GridBagSizer1->Add(IdentifierTextCtrl, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxEXPAND, 5);
    CategoryLabel = new wxStaticText(this, ID_CATEGORYLABEL, SwApplicationInterface::GetControlString("SID_CATEGORY", L"Category"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CATEGORYLABEL");
    GridBagSizer1->Add(CategoryLabel, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GroupLabel = new wxStaticText(this, ID_GROUPLABEL, SwApplicationInterface::GetControlString("SID_GROUP", L"Group"), wxDefaultPosition, wxDefaultSize, 0, L"ID_GROUPLABEL");
    GridBagSizer1->Add(GroupLabel, wxGBPosition(6, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    VersificationLabel = new wxStaticText(this, ID_VERSIFICATIONLABEL, SwApplicationInterface::GetControlString("SID_VERSIFICATION", L"Versification"), wxDefaultPosition, wxDefaultSize, 0, L"ID_VERSIFICATIONLABEL");
    GridBagSizer1->Add(VersificationLabel, wxGBPosition(6, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CategoryChoice = new wxChoice(this, ID_CATEGORYCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_CATEGORYCHOICE");
    SwCategory::FillCtrl(CategoryChoice);
    GridBagSizer1->Add(CategoryChoice, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    GroupComboBox = new wxComboBox(this, ID_GROUPCOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_GROUPCOMBOBOX");
    SwApplicationInterface::GetGroupList(GroupComboBox);
    GridBagSizer1->Add(GroupComboBox, wxGBPosition(7, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
    VersificationComboBox = new wxComboBox(this, ID_VERSIFICATIONCOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_VERSIFICATIONCOMBOBOX");
    GridBagSizer1->Add(VersificationComboBox, wxGBPosition(7, 2), wxDefaultSpan, wxALL|wxEXPAND, 5);
    PublisherLabel = new wxStaticText(this, ID_PUBLISHERLABEL, SwApplicationInterface::GetControlString("SID_PUBLISHER", L"Publisher"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PASSWORDLABEL");
    GridBagSizer1->Add(PublisherLabel, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PasswordLabel = new wxStaticText(this, ID_PASSWORDLABEL, SwApplicationInterface::GetControlString("SID_PASSWORD", L"Password"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PASSWORDLABEL");
    GridBagSizer1->Add(PasswordLabel, wxGBPosition(8, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    OfnLabel = new wxStaticText(this, ID_OFNLABEL, SwApplicationInterface::GetControlString("SID_ORIGINALFILENAME", L"Original File Name"), wxDefaultPosition, wxDefaultSize, 0, L"ID_STATICTEXT9");
    GridBagSizer1->Add(OfnLabel, wxGBPosition(8, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PublisherTextCtrl = new wxTextCtrl(this, ID_PUBLISHERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PASSWORDTEXTCTRL");
    GridBagSizer1->Add(PublisherTextCtrl, wxGBPosition(9, 0), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    PasswordTextCtrl = new wxTextCtrl(this, ID_PASSWORDTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PASSWORDTEXTCTRL");
    GridBagSizer1->Add(PasswordTextCtrl, wxGBPosition(9, 1), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    OfnTextCtrl = new wxTextCtrl(this, ID_OFNTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_OFNTEXTCTRL");
    GridBagSizer1->Add(OfnTextCtrl, wxGBPosition(9, 2), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    AllowCopyCheckBox = new SwCheckBox(this, ID_ALLOWCOPYCHECKBOX, SwApplicationInterface::GetControlString("SID_ALLOWCOPY", L"Allow Copy"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ALLOWCOPYCHECKBOX");
    AllowCopyCheckBox->SetValue(false);
    GridBagSizer1->Add(AllowCopyCheckBox, wxGBPosition(10, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    EncryptCheckBox = new SwCheckBox(this, ID_ENCRYPTCHECKBOX, SwApplicationInterface::GetControlString("SID_ENCRYPT", L"Encrypt"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ENCRYPTCHECKBOX");
    EncryptCheckBox->SetValue(false);
    GridBagSizer1->Add(EncryptCheckBox, wxGBPosition(10, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CompressCheckBox = new SwCheckBox(this, ID_COMPRESSCHECKBOX, SwApplicationInterface::GetControlString("SID_COMPRESS", L"Compress"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_COMPRESSCHECKBOX");
    CompressCheckBox->SetValue(false);
    GridBagSizer1->Add(CompressCheckBox, wxGBPosition(10, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ProgressGauge = new wxGauge(this, ID_PROGRESSGAUGE, 100, wxDefaultPosition, wxSize(-1,7), 0, wxDefaultValidator, L"ID_PROGRESSGAUGE");
    GridBagSizer1->Add(ProgressGauge, wxGBPosition(11, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    ReportTextCtrl = new wxTextCtrl(this, ID_REPORTTEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(-1,100), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, L"ID_REPORTTEXTCTRL");
    GridBagSizer1->Add(ReportTextCtrl, wxGBPosition(12, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    AboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
    GridBagSizer1->Add(AboutButton, wxGBPosition(13, 0), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    OkButton = new wxButton(this, ID_BUILDBUTTON, SwApplicationInterface::GetControlString("SID_BUILD", L"Build"));
    GridBagSizer1->Add(OkButton, wxGBPosition(13, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    CancelButton = new wxButton(this, ID_CANCELBUTTON, SwApplicationInterface::GetControlString("SID_CANCEL", L"Cancel"));
    GridBagSizer1->Add(CancelButton, wxGBPosition(13, 2), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);

    PasswordLabel->Enable(false);
    PasswordTextCtrl->Enable(false);
    AllowCopyCheckBox->SetValue(true);

    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    EncryptCheckBox->Enable(true);
    AllowCopyCheckBox->Enable(true);
    SwStandardBible::FillCtrl(VersificationComboBox);
    VersificationComboBox->SetValue("KJV");
    Connect(ID_SOURCEFILEPICKERCTRL,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnSourceFilePickerCtrlFileChanged);
    Connect(ID_SAVEASFILEPICKERCTRL,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnSaveasFilePickerCtrlFileChanged);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnQuit);
    Connect(ID_BUILDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnOkButtonClick);
    Connect(ID_CANCELBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnCancelButtonClick);
    Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnAboutButtonClick);
    Connect(ID_ENCRYPTCHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SowerModuleWriterDlg::OnEncryptCheckBoxClick);
    Bind(wxEVT_THREAD, &SowerModuleWriterDlg::OnThreadUpdate, this);
    SetLabel(SwApplicationInterface::GetControlString("SID_SOWERMODULEWRITER", L"Sower Module Writer"));
    SetIcon(SwApplicationInterface::GetToolsIcon());
    SwApplicationInterface::GetModuleManager().CreateCardCatalog(m_catalog);
    SwApplicationInterface::GetModuleManager().Reset();
    if (!SwApplicationInterface::GetEncryptor())
    {
        EncryptCheckBox->Enable(false);
        PasswordTextCtrl->Enable(false);
    }
}

SowerModuleWriterDlg::~SowerModuleWriterDlg()
{
    Unbind(wxEVT_THREAD, &SowerModuleWriterDlg::OnThreadUpdate, this);
    SwApplicationInterface::CloseFiles();
}

void SowerModuleWriterDlg::OnQuit(wxCommandEvent& event)
{
    if (GetThread() && GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }

    Close();
}

void SowerModuleWriterDlg::OnCancelButtonClick(wxCommandEvent& event)
{
    if (GetThread() && GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }

    Reset();
    EnableControls();
}

void SowerModuleWriterDlg::Reset()
{
    ProgressGauge->SetValue(0);
    ReportTextCtrl->SetValue(L"");
}

void SowerModuleWriterDlg::OnSourceFilePickerCtrlFileChanged(wxFileDirPickerEvent& event)
{
    SwStringW buffer, abb;
    SwString id;
    bool spaced = true;
    Reset();

    TitleTextCtrl->SetValue("");
    AbbreviationTextCtrl->SetValue("");

    SwCatalogCard card;
    SwString cpath;
    cpath = SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str();
    cpath += ".card";

    buffer = SourceFilePickerCtrl->GetFileName().GetFullPath().wchar_str();
    buffer.Replace(L".thm", 6, L".smd", 4);
    SaveasFilePickerCtrl->SetPath(buffer.GetArray());

    if (card.ReadData(cpath))
    {
        TitleTextCtrl->SetValue(card.GetTitle());
        AbbreviationTextCtrl->SetValue(card.GetAbbreviation());
        OfnTextCtrl->SetValue(card.GetCcelFileName());
        IdentifierTextCtrl->SetValue(card.GetIdentifier());
        PublisherTextCtrl->SetValue(card.GetPublisher());
        GroupComboBox->SetValue(card.GetGroup());
        AllowCopyCheckBox->SetValue(card.canCopy);
        if (SwApplicationInterface::GetEncryptor())
        {
            EncryptCheckBox->SetValue(card.isEncrypted);
            PasswordTextCtrl->Enable(card.isEncrypted);
        }

        if (card.isEncrypted && !SwApplicationInterface::GetEncryptor())
        {
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_MODULENOTENCRYPTED", L"Module will not be encrypted.")).GetArray(),
                         SwStringW(SwApplicationInterface::GetControlString("SID_ENCRYPTIONNOTAVAILABLE", L"Encryption not available.")).GetArray());
        }

        SwCategory::SetCategory(CategoryChoice, card.category);
        return;
    }

    if (SwThMLUtility::GetTitleW(buffer, SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str()))
    {
        TitleTextCtrl->SetValue(buffer.GetArray());

        for (swUI32 i = 0; i < buffer.Strlen(); i ++)
        {
            if (!spaced && buffer.GetAt(i) == L' ')
            {
                spaced = true;
                continue;
            }

            if (spaced)
            {
                abb += buffer.GetAt(i);
                spaced = false;
            }
        }

        abb.ToUpper();
        AbbreviationTextCtrl->SetValue(abb.GetArray());
    }

    OfnTextCtrl->SetValue("");
    buffer = SourceFilePickerCtrl->GetFileName().GetFullName().wchar_str();
    OfnTextCtrl->SetValue(buffer.GetArray());

    IdentifierTextCtrl->SetValue("");
    if (SwThMLUtility::GetIdentifier(id, SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str()))
    {
        id.TrimRight(' ');
        if (id.Strlen() < 7)
            id += "-000";
        IdentifierTextCtrl->SetValue(id.GetArray());
    }

    CategoryChoice->SetSelection(0);
    SetCategory(SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str());

    GroupComboBox->SetValue("");
    AllowCopyCheckBox->SetValue(true);
    EncryptCheckBox->SetValue(false);
    PasswordTextCtrl->SetValue("");
}

void SowerModuleWriterDlg::OnSaveasFilePickerCtrlFileChanged(wxFileDirPickerEvent& event)
{
    Reset();
}

void SowerModuleWriterDlg::OnAboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERMODULEWRITER", L"Sower Module Writer"), SVSTR, L"2019");
}

void SowerModuleWriterDlg::OnThreadUpdate(wxThreadEvent& evt)
{
    if (evt.GetInt() == 0)
        ProgressGauge->SetRange(m_progressData.range);
    else if (evt.GetInt() == 1)
    {
        if (m_progressData.pos > (unsigned) ProgressGauge->GetRange())
            ProgressGauge->SetValue(ProgressGauge->GetRange());
        else
            ProgressGauge->SetValue(m_progressData.pos);
    }
    else if (evt.GetInt() == 2)
    {
        ReportTextCtrl->AppendText(evt.GetString());
    }
}

void SowerModuleWriterDlg::OnOkButtonClick(wxCommandEvent& event)
{
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }

    DisableControls();
}

wxThread::ExitCode SowerModuleWriterDlg::Entry()
{
    const char * formatstr =
        "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>Title</title></head><body><p>%s</p></body></html>";

    ReportTextCtrl->Clear();
    SwWriter  modWriter;
    FILE * output;
    SwThMLParser parser;
    SwString buffer1, buffer2;
    SwStringW que;
    wchar_t s[1024];

    if (!Validate())
    {
        EnableControls();
        return (wxThread::ExitCode)0;
    }

    modWriter.SetProgressData(&m_progressData);
    modWriter.SetWindow(this);
    modWriter.SetArrayIncrement(1000);
    modWriter.SetExtraBytes(64000);

    DisableControls();
    QueText(SwApplicationInterface::GetControlString("SID_PARSING", L"Parsing file."));
    QueText(L"\n");

    m_progressData.docontinue = true;
    modWriter.OpenFile(SourceFilePickerCtrl->GetPath().utf8_str(), true);

    QueText(SwApplicationInterface::GetControlString("SID_INLININGCSS", L"Inlining CSS."));
    QueText(L"\n");

    modWriter.ProcessFile();

    parser.SetThML_ElementArray();
    parser.SetMarkupType(MARKUP_THML);

    buffer1 = SaveasFilePickerCtrl->GetFileName().GetFullPath().utf8_str();
    buffer1 += ".tmp";
    output = SwFopen(buffer1, FMD_RWC);
    SwString id;
    swUI32 divn = 0, endNode;
    for (swUI32 i = 0; i < modWriter.GetParserNodes(); i ++)
    {
        if (modWriter.IsNodeThMLDiv(i) && modWriter.GetNodeType(i) == NODE_TYPE_BEGIN_TAG)
        {
            modWriter.GetNamedValueFromNode(i, "id", id);
            divn ++;
            que = SwApplicationInterface::GetControlString("SID_PROCESSINGDIVISION", L"Processing division ... ");
#if defined __MSWIN__
            swprintf(s, L"%u - ", divn);
#else
            swprintf(s, 1024, L"%u - ", divn);
#endif
            que += s;
            que += L"'";
            que += SwStringW(id).GetArray();
            que += L"'.\n";
            QueText(que);
            endNode = modWriter.GetThMLDivBreakNode(i);
            modWriter.GetNodesData(i, endNode, buffer1);
            parser.Load(buffer1, buffer1.Strlen());
            parser.UpdateNodeData();

            if (parser.FindElement(0, THML_SCRIPTURE, NODE_TYPE_UNPAIRED_TAG) != NODE_ID_INVALID)
                parser.Containorize(THML_SCRIPTURE, "scripture");
            if (parser.FindElement(0, THML_SCRIPCOM, NODE_TYPE_UNPAIRED_TAG) != NODE_ID_INVALID)
                parser.Containorize(THML_SCRIPCOM, "scripCom");
            if (parser.FindElement(0, THML_NOTE, NODE_TYPE_BEGIN_TAG) != NODE_ID_INVALID &&
                    parser.FindElement(0, THML_NOTE, NODE_TYPE_UNPAIRED_TAG) == NODE_ID_INVALID)
                parser.ProcessThMLNotes();

            parser.GetNodesData(0, parser.GetLastParserNode(), buffer2);
            fwrite(buffer2, 1, buffer2.Strlen(), output);
            i = endNode;
        }
        else
        {
            modWriter.GetNodeData(i, buffer1);
            fwrite(buffer1, 1, buffer1.Strlen(), output);
        }

        wxThreadEvent * e = new wxThreadEvent();
        e->SetInt(1);
        m_progressData.pos = i;
        wxQueueEvent(GetEventHandler(), e);
    }

    fclose(output);

    QueText(SwApplicationInterface::GetControlString("SID_BUILDINGMODULE", L"Building module."));
    QueText(L"\n");

    buffer1 = SaveasFilePickerCtrl->GetFileName().GetFullPath().utf8_str();
    buffer1 += ".tmp";
    modWriter.OpenFile(buffer1, true);
    modWriter.m_header.SetTitle(TitleTextCtrl->GetValue().utf8_str());
    modWriter.m_header.SetAbbreviation(AbbreviationTextCtrl->GetValue().utf8_str());
    modWriter.m_header.SetIdentifier(IdentifierTextCtrl->GetValue().utf8_str());
    modWriter.m_header.SetPublisher(PublisherTextCtrl->GetValue().utf8_str());
    modWriter.m_header.SetGroup(GroupComboBox->GetValue().utf8_str());
    modWriter.m_header.SetVersification(VersificationComboBox->GetValue().utf8_str());
    modWriter.m_header.SetCcelFileName(OfnTextCtrl->GetValue().utf8_str());
    modWriter.m_header.canCopy = AllowCopyCheckBox->GetValue();
    if (SwApplicationInterface::GetEncryptor())
        modWriter.m_header.isEncrypted = EncryptCheckBox->GetValue();
    else
        modWriter.m_header.isEncrypted = false;
    modWriter.m_header.category = SwCategory::GetCategory(CategoryChoice);

    modWriter.OnBuild();
    modWriter.WriteModule(SaveasFilePickerCtrl->GetPath().utf8_str());

    modWriter.CloseFile();
    buffer1 = SaveasFilePickerCtrl->GetFileName().GetFullPath().utf8_str();
    buffer1 += ".tmp";
    unlink(buffer1.GetArray());

    SwString path;

    if (modWriter.m_header.isEncrypted)
    {
        wxFileName fname = SourceFilePickerCtrl->GetFileName();
        fname.SetExt("mky");
        path = SwApplicationInterface::GetMasterKeysDir();
        path += S_PATH_SEP;
        path += fname.GetFullName().utf8_str();
        SwModuleKey key;
        key.header.GenerateKey();
        key.header.SetAsMaster();
        key.identifier = IdentifierTextCtrl->GetValue().utf8_str();
        key.header.SetIdentifierLength(key.identifier.Strlen());
        key.data = PasswordTextCtrl->GetValue().utf8_str();
        key.header.SetDataLength(key.data.Strlen());
        SwMakePath(SwApplicationInterface::GetMasterKeysDir());
        key.header.SetModuleKeys(modWriter.m_k1, modWriter.m_k2);
        key.Write(path);
    }

    QueText(SwApplicationInterface::GetControlString("SID_ERRORS", L"Errors"));
    QueText(L": ");

#if defined __MSWIN__
    swprintf(s, L"%u\n", modWriter.GetErrors());
#else
    swprintf(s, 1024, L"%u\n", modWriter.GetErrors());
#endif

    QueText(s);

    QueText(SwApplicationInterface::GetControlString("SID_WARNINGS", L"Warnings"));
    QueText(L": ");

#if defined __MSWIN__
    swprintf(s, L"%u\n", modWriter.GetWarnings());
#else
    swprintf(s, 1024, L"%u\n", modWriter.GetWarnings());
#endif

    QueText(s);

    if (CompressCheckBox->GetValue())
    {
        QueText(SwApplicationInterface::GetControlString("SID_COMPRESSINGMODULE", L"Compressing module."));
        QueText(L"\n");

        path.Copy(SaveasFilePickerCtrl->GetPath().utf8_str());
        path += ".bz2";
        SwBZipFile(SaveasFilePickerCtrl->GetPath().utf8_str(), path);

        path.Copy(SaveasFilePickerCtrl->GetFileName().GetPathWithSep().utf8_str());
        path += "Title.html";
        FILE * f = SwFopen(path, FMD_WC);
        SwString buffer;
        buffer.Copy(TitleTextCtrl->GetValue().utf8_str());
        if (f)
        {
            fprintf(f, formatstr, buffer.GetArray());
            fclose(f);
        }
    }

    SwCatalogCard card;
    modWriter.m_header.CopyToCard(&card);
    m_catalog += card;
    path.Copy(SourceFilePickerCtrl->GetPath().utf8_str());
    path += ".card";
    card.WriteData(path);

    SwStringW wpath;
    QueText(SwApplicationInterface::GetControlString("SID_BUILDCOMPLETE", L"Build complete."));
    wpath.Copy(SaveasFilePickerCtrl->GetPath().wchar_str());
    wpath += L".log.txt";
    ReportTextCtrl->SaveFile(wpath.GetArray());

    EnableControls();
    return (wxThread::ExitCode)0;
}

void SowerModuleWriterDlg::QueText(const wchar_t * text)
{
    wxThreadEvent * e = new wxThreadEvent();
    e->SetInt(2);
    e->SetString(text);
    wxQueueEvent(this, e);
}

void SowerModuleWriterDlg::OnEncryptCheckBoxClick(wxCommandEvent& event)
{
    PasswordLabel->Enable(event.IsChecked());
    PasswordTextCtrl->Enable(event.IsChecked());
}

bool SowerModuleWriterDlg::Validate()
{
    bool status = true;
    if (SourceFilePickerCtrl->GetPath().Len() < 1)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_SOURCEINVALID", L"Source invalid."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (SaveasFilePickerCtrl->GetPath().Len() < 1)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_MODULEPATHINVALID", L"Module path invalid."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (SourceFilePickerCtrl->GetPath() == SaveasFilePickerCtrl->GetPath())
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_MODULEPATHINVALID", L"Module path invalid."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (TitleTextCtrl->GetValue().Len() < 3 || TitleTextCtrl->GetValue().Len() > 199)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_TITLELENGTH", L"Title must be 3 - 199 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }
    else if (m_catalog.FindByTitle(TitleTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID_16)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_TITLEINUSE", L"Title in use."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (AbbreviationTextCtrl->GetValue().Len() < 3 || AbbreviationTextCtrl->GetValue().Len() > 12)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_ABBREVIATIONLENGTH", L"Abbreviation must be 3 - 12 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }
    else if (m_catalog.FindByAbbrev(AbbreviationTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID_16)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_ABBREVIATIONINUSE", L"Abbreviation in use."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (IdentifierTextCtrl->GetValue().Len() < 7)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_IDENTIFIERLENGTH", L"Identifier must be 7 - 12 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }
    else if (m_catalog.FindById(IdentifierTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID_16)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_IDENTIFIERINUSE", L"Identifier in use."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (OfnTextCtrl->GetValue().Len() > 39)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_ORIGINALFILENAMELENGTH", L"Original file name may not exceed 39 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (PublisherTextCtrl->GetValue().Len() > 49)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_PUBLISHERNAMELENGTH", L"Publisher name may not exceed 49 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (VersificationComboBox->GetValue().Len() > 12)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_VERSIFICATIONLENGTH", L"Versification name may not exceed 12 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (EncryptCheckBox->GetValue() && PasswordTextCtrl->GetValue().Len() < 7)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_PASSWORDLENGTH", L"Password must be at least 7 characters"));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    return status;
}

void SowerModuleWriterDlg::SetCategory(const char * path)
{
    SwString buffer;

    if (!SwThMLUtility::GetDublinCore(buffer, path))
        return;

    SwCategory::SetCategory(CategoryChoice, SwCategory::IdentifyCategory(buffer));
}

void SowerModuleWriterDlg::EnableControls()
{
    SourceFilePickerCtrl->GetPickerCtrl()->Enable();
    SourceFilePickerCtrl->GetTextCtrl()->Enable();
    SaveasFilePickerCtrl->GetPickerCtrl()->Enable();
    SaveasFilePickerCtrl->GetTextCtrl()->Enable();
    PasswordTextCtrl->Enable(SwApplicationInterface::GetEncryptor());
    OkButton->Enable();
    if (EncryptCheckBox->GetValue())
        PasswordTextCtrl->Enable();
    EncryptCheckBox->Enable();
    CompressCheckBox->Enable();
    CancelButton->Disable();
}

void SowerModuleWriterDlg::DisableControls()
{
    SourceFilePickerCtrl->GetPickerCtrl()->Disable();
    SourceFilePickerCtrl->GetTextCtrl()->Disable();
    SaveasFilePickerCtrl->GetPickerCtrl()->Disable();
    SaveasFilePickerCtrl->GetTextCtrl()->Disable();
    OkButton->Disable();
    EncryptCheckBox->Disable();
    CompressCheckBox->Disable();
    PasswordTextCtrl->Disable();
    CancelButton->Enable();
}
