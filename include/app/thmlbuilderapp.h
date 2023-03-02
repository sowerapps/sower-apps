///////////////////////////////////////////////////////////////////
// Name:        thmlbuilderapp.h
// Purpose:     ThML Builder
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLBUILDERAPP_H
#define THMLBUILDERAPP_H

#include "swprjml/swprjmlparser.h"
#include "framework/dialog.h"
#include "controls/stretchfitctrls.h"
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/filedlg.h>
#include <wx/rearrangectrl.h>
#include <wx/gauge.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/thread.h>

class ThMLBuilderApp : public SwBaseApp
{
public:
    virtual bool OnInit();
};

class ThMLBuilderDlg : public SwDialog, public wxThreadHelper, public SwProjectMlParser
{
public:
    ThMLBuilderDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~ThMLBuilderDlg();

    void OnQuit(wxCommandEvent& event);
    void OnSaveAsFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
    void OnPrjFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
    void OnSourceButtonClick(wxCommandEvent& event);
    void OnBuildButtonClick(wxCommandEvent& event);
    void OnUseProjectFileCheckBoxClick(wxCommandEvent& event);
    void Reset();
    void ProcessFile();
    void OnThreadUpdate(wxThreadEvent& evt);

    void OnaboutButtonClick(wxCommandEvent& event);
    void WriteCSS();
    void CollectFileData();
    void WriteDublinCore();
    void SetControlStates(bool state);

    static const long ID_TITLELABEL;
    static const long ID_TITLETEXTCTRL;
    static const long ID_CREATORLABEL;
    static const long ID_CREATORTEXTCTRL;
    static const long ID_PUBLISHERLABEL;
    static const long ID_PUBLISHERTEXTCTRL;
    static const long ID_SUBJECTLABEL;
    static const long ID_SUBJECTTEXTCTRL;
    static const long ID_SCHEMELABEL;
    static const long ID_SCHEMECOMBOBOX;
    static const long ID_DATELABEL;
    static const long ID_DATETEXTCTRL;
    static const long ID_TYPELABEL;
    static const long ID_TYPETEXTCTRL;
    static const long ID_FORMATLABEL;
    static const long ID_FORMATTEXTCTRL;
    static const long ID_IDENTIFIERLABEL;
    static const long ID_IDENTIFIERTEXTCTRL;
    static const long ID_SOURCELABEL;
    static const long ID_SOURCETEXTCTRL;
    static const long ID_LANGUAGELABEL;
    static const long ID_LANGUAGETEXTCTRL;
    static const long ID_RIGHTSLABEL;
    static const long ID_RIGHTSTEXTCTRL;
    static const long ID_SOURCEBUTTON;
    static const long ID_FILESLISTCTRL;
    static const long ID_SAVEASLABEL;
    static const long ID_SAVEASFILEPICKERCTRL;
    static const long ID_PROGRESSGAUGE;
    static const long ID_ABOUTBUTTON;
    static const long ID_STATUSLABEL;
    static const long ID_BUILDBUTTON;
    static const long ID_CSSLABEL;
    static const long ID_CSSFILEPICKERCTRL;
    static const long ID_USEPROJECTFILECHECKBOX;
    static const long ID_PROJECTFILEPICKERCTRL;

    wxStaticText* TitleLabel;
    wxTextCtrl*   TitleTextCtrl;
    wxStaticText* CreatorLabel;
    wxTextCtrl*   CreatorTextCtrl;
    wxStaticText* PublisherLabel;
    wxTextCtrl*   PublisherTextCtrl;
    wxStaticText* SubjectLabel;
    wxTextCtrl*   SubjectTextCtrl;
    wxStaticText* SchemeLabel;
    wxComboBox*   SchemeComboBox;
    wxStaticText* DateLabel;
    wxTextCtrl*   DateTextCtrl;
    wxStaticText* TypeLabel;
    wxTextCtrl*   TypeTextCtrl;
    wxStaticText* FormatLabel;
    wxTextCtrl*   FormatTextCtrl;
    wxStaticText* IdentifierLabel;
    wxTextCtrl*   IdentifierTextCtrl;
    wxStaticText* SourceLabel;
    wxTextCtrl*   SourceTextCtrl;
    wxStaticText* LanguageLabel;
    wxTextCtrl*   LanguageTextCtrl;
    wxStaticText* RightsLabel;
    wxTextCtrl*   RightsTextCtrl;
    wxButton* aboutButton;
    wxButton* buildButton;
    wxButton* sourceButton;
    wxFileDialog* sourceFileDialog;
    SwFittedFilePickerCtrl* saveasFilePickerCtrl;
    SwFittedFilePickerCtrl* cssFilePickerCtrl;
    SwFittedFilePickerCtrl* projectFilePickerCtrl;
    wxCheckBox* useprjFileCheckBox;
    wxGauge* progressGauge;
    wxRearrangeCtrl* filesListCtrl;
    wxStaticText* saveasLabel;
    wxStaticText* statusLabel;
    wxStaticText* cssLabel;

protected:
    virtual wxThread::ExitCode Entry();
    SwProgressData    m_progressData;
};

#endif // THMLBUILDERAPP_H
