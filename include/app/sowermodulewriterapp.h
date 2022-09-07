///////////////////////////////////////////////////////////////////
// Name:        sowermodulewriterapp.h
// Purpose:     Sower Module Writer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMODULEWRITERAPP_H
#define SOWERMODULEWRITERAPP_H

#include "framework/dialog.h"
#include "module/thmlmodulewriter.h"
#include "array/cardarray.h"
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/gauge.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/thread.h>

class SowerModuleWriterApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerModuleWriterDlg : public SwDialog, public wxThreadHelper
{
public:

    SowerModuleWriterDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SowerModuleWriterDlg();

private:
    wxButton* AboutButton;
    wxButton* BuildButton;
    SwCheckBox* AllowCopyCheckBox;
    SwCheckBox* EncryptCheckBox;
    wxChoice* CategoryChoice;
    wxComboBox* GroupComboBox;
    wxComboBox* VersificationComboBox;
    wxFilePickerCtrl* SaveasFilePickerCtrl;
    wxFilePickerCtrl* SourceFilePickerCtrl;
    wxGauge* ProgressGauge;
    wxStaticText* AbbreviationLabel;
    wxStaticText* CategoryLabel;
    wxStaticText* GroupLabel;
    wxStaticText* IdentifierLabel;
    wxStaticText* SaveasLabel;
    wxStaticText* SourceLabel;
    wxStaticText* OfnLabel;
    wxStaticText* TitleLabel;
    wxStaticText* PasswordLabel;
    wxStaticText* VersificationLabel;
    wxTextCtrl* AbbreviationTextCtrl;
    wxTextCtrl* IdentifierTextCtrl;
    wxTextCtrl* OfnTextCtrl;
    wxTextCtrl* PasswordTextCtrl;
    wxTextCtrl* ReportTextCtrl;
    wxTextCtrl* TitleTextCtrl;
    wxStaticText* PublisherLabel;
    wxTextCtrl* PublisherTextCtrl;
    wxButton* CancelButton;
    wxButton* OkButton;

    static const long ID_SOURCELABEL;
    static const long ID_SOURCEFILEPICKERCTRL;
    static const long ID_SAVEASLABEL;
    static const long ID_SAVEASFILEPICKERCTRL;
    static const long ID_TITLELABEL;
    static const long ID_ABBREVIATIONLABEL;
    static const long ID_IDENTIFIERLABEL;
    static const long ID_TITLETEXTCTRL;
    static const long ID_ABBREVIATIONTEXTCTRL;
    static const long ID_IDENTIFIERTEXTCTRL;
    static const long ID_CATEGORYLABEL;
    static const long ID_GROUPLABEL;
    static const long ID_VERSIFICATIONLABEL;
    static const long ID_CATEGORYCHOICE;
    static const long ID_GROUPCOMBOBOX;
    static const long ID_VERSIFICATIONCOMBOBOX;
    static const long ID_ALLOWCOPYCHECKBOX;
    static const long ID_OFNLABEL;
    static const long ID_ENCRYPTCHECKBOX;
    static const long ID_OFNTEXTCTRL;
    static const long ID_PROGRESSGAUGE;
    static const long ID_REPORTTEXTCTRL;
    static const long ID_ABOUTBUTTON;
    static const long ID_BUILDBUTTON;
    static const long ID_PASSWORDLABEL;
    static const long ID_PASSWORDTEXTCTRL;
    static const long ID_CANCELBUTTON;
    static const long ID_PUBLISHERLABEL;
    static const long ID_PUBLISHERTEXTCTRL;

    void OnQuit(wxCommandEvent& event);
    void OnCancelButtonClick(wxCommandEvent& event);
    void Reset();
    void OnSourceFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
    void OnSaveasFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
    void OnAboutButtonClick(wxCommandEvent& event);
    void OnOkButtonClick(wxCommandEvent& event);
    void OnThreadUpdate(wxThreadEvent& evt);
    void OnEncryptCheckBoxClick(wxCommandEvent& event);
    bool Validate();
    void SetCategory(const char * path);
    void EnableControls();
    void DisableControls();

protected:
    virtual wxThread::ExitCode Entry();
    void QueText(const wchar_t * text);
    SwProgressData m_progressData;
    swUI16 m_key;
    SwCatalogCardArray m_catalog;
};

#endif // SOWERMODULEWRITERAPP_H
