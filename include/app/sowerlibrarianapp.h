///////////////////////////////////////////////////////////////////
// Name:        sowermodulewriterapp.h
// Purpose:     Sower Librarian
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

class SowerLibrarianApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerLibrarianDlg : public SwDialog, public wxThreadHelper, public SwDirRecurse
{
public:
    SowerLibrarianDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SowerLibrarianDlg();

private:
    wxButton* AboutButton;
    wxButton* BuildButton;
    wxDirPickerCtrl* SourceDirPickerCtrl;
    wxGauge* ProgressGauge;
    wxStaticText* SourceLabel;
    wxStaticText* PasswordLabel;
    wxTextCtrl* PasswordTextCtrl;
    wxTextCtrl* ReportTextCtrl;
    wxButton* CancelButton;
    wxButton* OkButton;
    SwCheckBox* CompressCheckBox;

    static const long ID_SOURCELABEL;
    static const long ID_SOURCEDIRPICKERCTRL;
    static const long ID_PROGRESSGAUGE;
    static const long ID_REPORTTEXTCTRL;
    static const long ID_ABOUTBUTTON;
    static const long ID_BUILDBUTTON;
    static const long ID_PASSWORDLABEL;
    static const long ID_PASSWORDTEXTCTRL;
    static const long ID_CANCELBUTTON;
    static const long ID_COMPRESSCHECKBOX;

    void OnQuit(wxCommandEvent& event);
    void OnCancelButtonClick(wxCommandEvent& event);
    void Reset();
    void OnSourceDirPickerCtrlChanged(wxFileDirPickerEvent& event);
    void OnAboutButtonClick(wxCommandEvent& event);
    void OnOkButtonClick(wxCommandEvent& event);
    void OnThreadUpdate(wxThreadEvent& evt);
    void OnEncryptCheckBoxClick(wxCommandEvent& event);
    virtual bool OnFile(const char * path);
    void EnableControls();
    void DisableControls();

protected:
    virtual wxThread::ExitCode Entry();
    void QueText(const wchar_t * text);
    SwProgressData m_progressData;
    swUI16 m_key;
    SwString m_password;
    bool m_passwordvalid;
    SwCatalogCardArray m_catalog;
};

#endif // SOWERMODULEWRITERAPP_H
