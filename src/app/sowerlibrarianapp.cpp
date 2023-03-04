///////////////////////////////////////////////////////////////////
// Name:        sowerlibrarianapp.cpp
// Purpose:     Sower Librarian
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowerlibrarianapp.h"
#include "appi/appifa.h"
#include "module/category.h"
#include "module/module.h"
#include "thml/thml_utility.h"
#include "filesys/bzcompression.h"
#include "dialogs/carddlg.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerLibrarianApp);

bool SowerLibrarianApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();
    SwApplicationInterface::LoadPlugIns();
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadModules();
    SowerLibrarianDlg Dlg(0);
    SetTopWindow(&Dlg);
    Dlg.ShowModal();

    return false;
}

const long SowerLibrarianDlg::ID_SOURCELABEL = wxNewId();
const long SowerLibrarianDlg::ID_SOURCEDIRPICKERCTRL = wxNewId();
const long SowerLibrarianDlg::ID_PROGRESSGAUGE = wxNewId();
const long SowerLibrarianDlg::ID_REPORTTEXTCTRL = wxNewId();
const long SowerLibrarianDlg::ID_ABOUTBUTTON = wxNewId();
const long SowerLibrarianDlg::ID_BUILDBUTTON = wxNewId();
const long SowerLibrarianDlg::ID_PASSWORDLABEL = wxNewId();
const long SowerLibrarianDlg::ID_PASSWORDTEXTCTRL = wxNewId();
const long SowerLibrarianDlg::ID_CANCELBUTTON = wxNewId();
const long SowerLibrarianDlg::ID_COMPRESSCHECKBOX = wxNewId();

SowerLibrarianDlg::SowerLibrarianDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    :SwDialog(parent, id, L"", pos, size, wxDEFAULT_DIALOG_STYLE, L"")
{
    m_key = NODE_ID_INVALID_16;

    wxGridBagSizer * GridBagSizer1, * GridBagSizer2;

    GridBagSizer1 = new wxGridBagSizer(0, 0);
    GridBagSizer2 = new wxGridBagSizer(0, 0);
    SourceLabel = new wxStaticText(this, ID_SOURCELABEL, SwApplicationInterface::GetControlString("SID_SOURCE", L"Source"), wxDefaultPosition, wxDefaultSize, 0, "ID_SOURCELABEL");
    GridBagSizer1->Add(SourceLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SourceDirPickerCtrl = new wxDirPickerCtrl(this, ID_SOURCEDIRPICKERCTRL, wxEmptyString, SwStringW(SwApplicationInterface::GetControlString("SID_SELECTAFILE", L"Select a file")).GetArray(), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE, wxDefaultValidator, L"ID_SOURCEFILEPICKERCTRL");
    SourceDirPickerCtrl->SetMinSize(wxSize(200, -1));
    GridBagSizer1->Add(SourceDirPickerCtrl, wxGBPosition(1, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    PasswordLabel = new wxStaticText(this, ID_PASSWORDLABEL, SwApplicationInterface::GetControlString("SID_PASSWORD", L"Password"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PASSWORDLABEL");
    GridBagSizer1->Add(PasswordLabel, wxGBPosition(0, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);
    PasswordTextCtrl = new wxTextCtrl(this, ID_PASSWORDTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PASSWORDTEXTCTRL");
    GridBagSizer1->Add(PasswordTextCtrl, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    PasswordTextCtrl->SetMinSize(wxSize(200, -1));
    CompressCheckBox = new SwCheckBox(this, ID_COMPRESSCHECKBOX, SwApplicationInterface::GetControlString("SID_COMPRESS", L"Compress"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_COMPRESSCHECKBOX");
    CompressCheckBox->SetValue(false);
    GridBagSizer1->Add(CompressCheckBox, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ProgressGauge = new wxGauge(this, ID_PROGRESSGAUGE, 100, wxDefaultPosition, wxSize(-1,7), 0, wxDefaultValidator, L"ID_PROGRESSGAUGE");
    GridBagSizer1->Add(ProgressGauge, wxGBPosition(3, 0), wxGBSpan(1, 5), wxALL|wxEXPAND, 5);
    ReportTextCtrl = new wxTextCtrl(this, ID_REPORTTEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(-1,100), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, L"ID_REPORTTEXTCTRL");
    GridBagSizer1->Add(ReportTextCtrl, wxGBPosition(4, 0), wxGBSpan(2, 5), wxALL|wxEXPAND, 5);
    AboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
    GridBagSizer2->Add(AboutButton, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    OkButton = new wxButton(this, ID_BUILDBUTTON, SwApplicationInterface::GetControlString("SID_BUILD", L"Build"));
    GridBagSizer2->Add(OkButton, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    CancelButton = new wxButton(this, ID_CANCELBUTTON, SwApplicationInterface::GetControlString("SID_CANCEL", L"Cancel"));
    GridBagSizer2->Add(CancelButton, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer1->Add(GridBagSizer2, wxGBPosition(6, 0), wxGBSpan(1, 5), wxALL|wxALIGN_CENTER|wxEXPAND, 5);

    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    Connect(ID_SOURCEDIRPICKERCTRL,wxEVT_DIRPICKER_CHANGED,(wxObjectEventFunction)&SowerLibrarianDlg::OnSourceDirPickerCtrlChanged);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerLibrarianDlg::OnQuit);
    Connect(ID_BUILDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerLibrarianDlg::OnOkButtonClick);
    Connect(ID_CANCELBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerLibrarianDlg::OnCancelButtonClick);
    Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerLibrarianDlg::OnAboutButtonClick);
    Bind(wxEVT_THREAD, &SowerLibrarianDlg::OnThreadUpdate, this);
    SetLabel(SwApplicationInterface::GetControlString("SID_SOWERLIBRARIAN", L"Sower Librarian"));
    SetIcon(SwApplicationInterface::GetToolsIcon());
    SwApplicationInterface::GetModuleManager().CreateCardCatalog(m_catalog);
    SwApplicationInterface::GetModuleManager().Reset();
    PasswordTextCtrl->Enable(SwApplicationInterface::GetEncryptor());

}

SowerLibrarianDlg::~SowerLibrarianDlg()
{
    Unbind(wxEVT_THREAD, &SowerLibrarianDlg::OnThreadUpdate, this);
    SwApplicationInterface::CloseFiles();
}

void SowerLibrarianDlg::OnQuit(wxCommandEvent& event)
{
    if (GetThread() && GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }

    Close();
}

void SowerLibrarianDlg::OnCancelButtonClick(wxCommandEvent& event)
{
    ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_TERMINATINGMSG", L"Terminating as result of user input.\n"));
    SwStringW wpath(SourceDirPickerCtrl->GetPath().wchar_str());
    wpath += S_WPATH_SEP;
    wpath += L"log.txt";
    ReportTextCtrl->SaveFile(wpath.GetArray());

    if (GetThread() && GetThread()->IsRunning())
    {
        GetThread()->Kill();
    }

    EnableControls();
}

void SowerLibrarianDlg::Reset()
{
    ProgressGauge->SetValue(0);
    ReportTextCtrl->SetValue(L"");
    EnableControls();
}

void SowerLibrarianDlg::OnSourceDirPickerCtrlChanged(wxFileDirPickerEvent& event)
{
    Reset();
}

void SowerLibrarianDlg::OnAboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERLIBRARIAN", L"Sower Librarian"), SVSTR, L"2022");
}

void SowerLibrarianDlg::OnThreadUpdate(wxThreadEvent& evt)
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

void SowerLibrarianDlg::OnOkButtonClick(wxCommandEvent& event)
{
    Reset();
    if (!SourceDirPickerCtrl->GetPath().Len())
    {
        SourceDirPickerCtrl->SetFocus();
        wxBell();
        return;
    }

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

wxThread::ExitCode SowerLibrarianDlg::Entry()
{
    m_passwordvalid = false;
    if (!SourceDirPickerCtrl->GetPath().Len())
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_SOURCEINVALID", L"Source invalid."));
        ReportTextCtrl->AppendText("\n");
        EnableControls();
        return (wxThread::ExitCode)0;
    }

    if (PasswordTextCtrl->GetValue().Len() > 0 && PasswordTextCtrl->GetValue().Len() < 7)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_PASSWORDLENGTH", L"Password must be at least 7 characters"));
        ReportTextCtrl->AppendText("\n");
    }
    else if (PasswordTextCtrl->GetValue().Len() >= 7)
    {
        m_passwordvalid = true;
        m_password = PasswordTextCtrl->GetValue().utf8_str();
    }

    ReportTextCtrl->Clear();

    SwDirRecurse::RecurseDir(SourceDirPickerCtrl->GetPath().utf8_str(), true);

    SwStringW wpath(SourceDirPickerCtrl->GetPath().wchar_str());
    wpath += S_WPATH_SEP;
    wpath += L"log.txt";
    ReportTextCtrl->SaveFile(wpath.GetArray());
    EnableControls();

    return (wxThread::ExitCode)0;
}

void SowerLibrarianDlg::QueText(const wchar_t * text)
{
    wxThreadEvent * e = new wxThreadEvent();
    e->SetInt(2);
    e->SetString(text);
    wxQueueEvent(this, e);
}

bool SowerLibrarianDlg::OnFile(const char * path)
{
    const char * formatstr =
        "<!DOCTYPE html><html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"><title>Title</title></head><body><p>%s</p></body></html>";

    SwWriter  modWriter;
    FILE * output;
    SwThMLParser parser;
    SwString buffer1, buffer2;
    SwFilePath cardPath(path), tmpPath(path), modPath(path), htmlPath(path), bzPath(path);
    cardPath += ".card";

    if (stricmp(modPath.GetExtension(), "thm") != 0)
        return true;

    tmpPath += ".tmp";
    modPath.ReplaceExtension("smd");
    bzPath.ReplaceExtension("smd.bz2");
    htmlPath.ClipFileName();
    htmlPath.Add(S_PATH_SEP);
    htmlPath.Add("Title.html");
    SwStringW que;
    wchar_t s[1024];

    QueText(SwStringW(path));
    QueText(L"\n");

    SwCatalogCard card;
    card.Zero();
    if (card.ReadData(cardPath.GetFilePath()) && SwFile::DoesExist(modPath.GetFilePath()))
    {
        if (SwFile::CompareModifiedDates(path, modPath.GetFilePath()) == 2 &&
                card.softwareversionMajor == MODULEVERSIONMAJOR &&
                card.softwareversionMinor == MODULEVERSIONMINOR)
        {
            QueText(SwApplicationInterface::GetControlString("SID_MODULEUPTODATE", L"Existing module is up to date.\n\n"));
            return true;
        }
    }
    else
    {
        SwCatalogCardDlg dlg(this);
        card.Zero();
        dlg.SetCard(&card);
        dlg.LoadFromFile(path);
        dlg.SetCatalog(&m_catalog);
        int result = dlg.ShowModal();
        if (result == 0)
        {
            QueText(SwApplicationInterface::GetControlString("SID_SKIPPINGMSG1", L"Skipping as result of user input.\n\n"));
            return true;
        }

        if (result == 2)
        {
            ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_TERMINATINGMSG", L"Terminating as result of user input.\n"));
            return false;
        }
    }

    if (card.isEncrypted && !SwApplicationInterface::GetEncryptor())
    {
        QueText(SwApplicationInterface::GetControlString("SID_ENCRYPTIONNOTAVAILABLE", L"Encryption not available."));
        QueText(L"\n");
        QueText(SwApplicationInterface::GetControlString("SID_SKIPPING", L"Skipping.\n\n"));
        return true;
    }

    modWriter.SetProgressData(&m_progressData);
    modWriter.SetWindow(this);
    modWriter.SetArrayIncrement(1000);
    modWriter.SetExtraBytes(64000);

    if (card.isEncrypted && !m_passwordvalid)
    {
        QueText(SwApplicationInterface::GetControlString("SID_SKIPPINGMSG2", L"Encryption has been specified for module.\nNo password has been set.\nSkipping.\n\n"));
        return true;
    }

    QueText(SwApplicationInterface::GetControlString("SID_PARSING", L"Parsing file."));
    QueText(L"\n");

    m_progressData.docontinue = true;
    modWriter.OpenFile(path, true);

    QueText(SwApplicationInterface::GetControlString("SID_INLININGCSS", L"Inlining CSS."));
    QueText(L"\n");

    modWriter.ProcessFile();

    parser.SetThML_ElementArray();
    parser.SetMarkupType(MARKUP_THML);

    output = SwFopen(tmpPath.GetFilePath(), FMD_WC);

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

    modWriter.OpenFile(tmpPath.GetFilePath(), true);
    modWriter.m_header.CopyFromCard(&card);
    modWriter.OnBuild();
    modWriter.WriteModule(modPath.GetFilePath());
    modWriter.CloseFile();
    unlink(tmpPath.GetFilePath());

    if (modWriter.m_header.isEncrypted)
    {
        SwFilePath keypath(path);
        keypath.ReplaceExtension("mky");
        SwFilePath installPath(SwApplicationInterface::GetMasterKeysDir());
        installPath.Add(S_PATH_SEP);
        installPath.Add(keypath.GetFileName());
        SwModuleKey key;
        key.header.GenerateKey();
        key.header.SetAsMaster();
        key.identifier = card.GetIdentifier();
        key.header.SetIdentifierLength(key.identifier.Strlen());
        key.data = m_password;
        key.header.SetDataLength(key.data.Strlen());
        SwMakePath(SwApplicationInterface::GetMasterKeysDir());
        key.header.SetModuleKeys(modWriter.m_k1, modWriter.m_k2);
        key.Write(installPath.GetFilePath());
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

        SwBZipFile(modPath.GetFilePath(), bzPath.GetFilePath());

        FILE * f = SwFopen(htmlPath.GetFilePath(), FMD_WC);
        SwString buffer;
        buffer.Copy(card.GetTitle());
        if (f)
        {
            fprintf(f, formatstr, buffer.GetArray());
            fclose(f);
        }
    }
    m_catalog += card;
    card.WriteData(cardPath.GetFilePath());

    QueText(SwApplicationInterface::GetControlString("SID_BUILDCOMPLETE", L"Build complete."));
    QueText(L"\n\n");

    return true;
}

void SowerLibrarianDlg::EnableControls()
{
    SourceDirPickerCtrl->GetPickerCtrl()->Enable();
    SourceDirPickerCtrl->GetTextCtrl()->Enable();
    PasswordTextCtrl->Enable(SwApplicationInterface::GetEncryptor());
    CompressCheckBox->Enable();
    OkButton->Enable();
    CancelButton->Disable();
}

void SowerLibrarianDlg::DisableControls()
{
    SourceDirPickerCtrl->GetPickerCtrl()->Disable();
    SourceDirPickerCtrl->GetTextCtrl()->Disable();
    CompressCheckBox->Disable();
    OkButton->Disable();
    PasswordTextCtrl->Disable();
    CancelButton->Enable();
}
