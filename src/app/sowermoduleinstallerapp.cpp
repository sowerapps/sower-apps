///////////////////////////////////////////////////////////////////
// Name:        sowermoduleinstallerapp.cpp
// Purpose:     Sower Module Installer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowermoduleinstallerapp.h"
#include "appi/appifa.h"
#include "filesys/file.h"
#include "filesys/bzcompression.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerModuleInstallerApp);

bool SowerModuleInstallerApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::InitBasic();

    SowerModuleInstallerDlg Dlg(0);
    SetTopWindow(&Dlg);
    Dlg.ShowModal();

    return false;
}

const long SowerModuleInstallerDlg::ID_ABOUTBUTTON = wxNewId();
const long SowerModuleInstallerDlg::ID_INSTALLBUTTON = wxNewId();
const long SowerModuleInstallerDlg::ID_SOURCEFILEPICKERCTRL = wxNewId();

SowerModuleInstallerDlg::SowerModuleInstallerDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    :SwDialog(parent, id, "", pos, size, wxDEFAULT_DIALOG_STYLE, "")
{
    wxGridBagSizer* GridBagSizer1;

    GridBagSizer1 = new wxGridBagSizer(0, 0);
    SourceFilePickerCtrl = new wxFilePickerCtrl(this, ID_SOURCEFILEPICKERCTRL, wxEmptyString, wxEmptyString, L"*.smd.bz2", wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_USE_TEXTCTRL, wxDefaultValidator, L"ID_SOURCEFILEPICKERCTRL");
    GridBagSizer1->Add(SourceFilePickerCtrl, wxGBPosition(0, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    AboutButton = new wxButton(this, ID_ABOUTBUTTON, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABOUTBUTTON");
    GridBagSizer1->Add(AboutButton, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    InstallButton = new wxButton(this, ID_INSTALLBUTTON, SwApplicationInterface::GetControlString("SID_INSTALL", L"Install"));
    InstallButton->Disable();
    GridBagSizer1->Add(InstallButton, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);
    Connect(ID_SOURCEFILEPICKERCTRL,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&SowerModuleInstallerDlg::OnSourceFilePickerCtrlFileChanged);
    Connect(ID_ABOUTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleInstallerDlg::OnAboutButtonClick);
    Connect(ID_INSTALLBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleInstallerDlg::OnInstallButtonClick);
    SetLabel(SwApplicationInterface::GetControlString("SID_SOWERMODULEINSTALLER", L"Sower Module Installer"));
    SetIcon(SwApplicationInterface::GetToolsIcon());
}

SowerModuleInstallerDlg::~SowerModuleInstallerDlg()
{
    SwApplicationInterface::CloseFiles();
}

void SowerModuleInstallerDlg::OnAboutButtonClick(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERMODULEINSTALLER", L"Sower Module Installer"), L"1.0", L"2022");
}

void SowerModuleInstallerDlg::OnSourceFilePickerCtrlFileChanged(wxFileDirPickerEvent& event)
{
    InstallButton->Enable((bool) SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str().length());
}

void SowerModuleInstallerDlg::OnInstallButtonClick(wxCommandEvent& event)
{
    SwFilePath path;
    SwString writepath;

    path.Copy(SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str());
    path.ClipExtension();

    writepath = SwApplicationInterface::GetModuleLibraryDir();
    writepath += PATH_SEP;
    writepath += path.GetFileName();

    if (SwUnBZipFile(SourceFilePickerCtrl->GetFileName().GetFullPath().utf8_str(), writepath.GetArray()))
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_SOWERMODULEINSTALLER", L"Sower Module Installer")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_MODULEINSTALLED", L"Module Installed.")).GetArray());
    else
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_SOWERMODULEINSTALLER", L"Sower Module Installer")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_MODULEINSTALLFAILED", L"Module install failed.")).GetArray());
}
