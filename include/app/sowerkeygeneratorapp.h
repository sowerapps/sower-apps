///////////////////////////////////////////////////////////////////
// Name:        sowerkeygeneratorapp.h
// Purpose:     Sower Key Generator
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERKEYGENERATORAPP_H
#define SOWERKEYGENERATORAPP_H

#include "framework/dialog.h"
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class SowerKeyGeneratorApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerKeyGeneratorDlg: public SwDialog
{
public:
    SowerKeyGeneratorDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SowerKeyGeneratorDlg();

    wxButton* AboutButton;
    wxButton* GenerateButton;
    wxChoice* ModuleChoice;
    wxFilePickerCtrl* SaveasFilePickerCtrl;
    wxStaticText* DataLabel;
    wxStaticText* ModuleLabel;
    wxStaticText* PasswordLabel;
    wxStaticText* SaveasLabel;
    wxTextCtrl* DataTextCtrl;
    wxTextCtrl* PasswordTextCtrl;

protected:
    static const long ID_MODULELABEL;
    static const long ID_PASSWORDLABEL;
    static const long ID_ModuleCHOICE;
    static const long ID_PASSWORDTEXTCTRL;
    static const long ID_SAVEASLABEL;
    static const long ID_SAVEASFILEPICKERCTRL;
    static const long ID_DATALABEL;
    static const long ID_DATATEXTCTRL;
    static const long ID_ABOUTBUTTON;
    static const long ID_GENERATEBUTTON;

private:
    void OnAboutButtonClick(wxCommandEvent& event);
    void OnOkButtonClick(wxCommandEvent& event);
};

#endif // SOWERKEYGENERATORAPP_H
