///////////////////////////////////////////////////////////////////
// Name:        sowermoduleinstallerapp.h
// Purpose:     Sower Module Installer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMODULEINSTALLERAPP_H
#define SOWERMODULEINSTALLERAPP_H

#include "framework/dialog.h"
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class SowerModuleInstallerApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerModuleInstallerDlg: public SwDialog
{
public:
    SowerModuleInstallerDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SowerModuleInstallerDlg();

    wxButton* AboutButton;
    wxButton* InstallButton;
    wxFilePickerCtrl* SourceFilePickerCtrl;

    static const long ID_ABOUTBUTTON;
    static const long ID_INSTALLBUTTON;
    static const long ID_SOURCEFILEPICKERCTRL;

private:
    void OnSourceFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
    void OnAboutButtonClick(wxCommandEvent& event);
    void OnInstallButtonClick(wxCommandEvent& event);
};

#endif // SOWERMODULEINSTALLERAPP_H
