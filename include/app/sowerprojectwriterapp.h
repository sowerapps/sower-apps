///////////////////////////////////////////////////////////////////
// Name:        sowerprojectwriterapp.h
// Purpose:     Sower Project Writer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERPROJECTWRITERAPP_H
#define SOWERPROJECTWRITERAPP_H

#include "framework/dialog.h"
#include "swopf/swopfparser.h"
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class SowerProjectWriterApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerProjectWriterDlg: public SwDialog, public SwOPFParser
{
public:
    SowerProjectWriterDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SowerProjectWriterDlg();

    wxButton* AboutButton;
    wxButton* BuildButton;
    wxStaticText* SourceLabel;
    wxFilePickerCtrl* SourceFilePickerCtrl;
    wxStaticText* TargetLabel;
    wxTextCtrl* TargetTextCtrl;
    wxCheckBox* ProcessReferencesCheckBox;
    wxCheckBox* RomanForChaptersCheckBox;
    wxCheckBox* RomanForVersesCheckBox;
    wxCheckBox* RomanLowerCaseCheckBox;
    wxCheckBox* BookNamesUpperCaseCheckBox;
    wxCheckBox* LineBreaksAsSpaceCheckBox;
    wxStaticText* MarkersLabel;
    wxStaticText* CVDivLabel;
    wxTextCtrl* CVDivTextCtrl;
    wxStaticText* DivisionLabel;
    wxTextCtrl* DivisionTextCtrl;
    wxStaticText* SpanLabel;
    wxTextCtrl* SpanTextCtrl;
    wxStaticText* BreakLabel;
    wxTextCtrl* BreakTextCtrl;

    static const long ID_ABOUTBUTTON;
    static const long ID_BUILDBUTTON;
    static const long ID_SOURCELABEL;
    static const long ID_SOURCEFILEPICKERCTRL;
    static const long ID_TARGETLABEL;
    static const long ID_TARGETTEXTCTRL;
    static const long ID_PROCESSREFERENCESCHECKBOX;
    static const long ID_ROMANFORCHAPTERSCHECKBOX;
    static const long ID_ROMANFORVERSESCHECKBOX;
    static const long ID_ROMANLOWERCASECHECKBOX;
    static const long ID_BOOKNAMESCASECHECKBOX;
    static const long ID_LINEBREAKSASSPACECHECKBOX;
    static const long ID_MARKERSLABEL;
    static const long ID_CVDIVLABEL;
    static const long ID_CVDIVTEXTCTRL;
    static const long ID_DIVISIONLABEL;
    static const long ID_DIVISIONTEXTCTRL;
    static const long ID_SPANLABEL;
    static const long ID_SPANTEXTCTRL;
    static const long ID_BREAKLABEL;
    static const long ID_BREAKTEXTCTRL;

private:
    void OnTextChange(wxCommandEvent& event);
    void OnCheckBox(wxCommandEvent& event);
    void OnFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
    void OnAboutButtonClick(wxCommandEvent& event);
    void OnBuildButtonClick(wxCommandEvent& event);
    void EnableControls(bool state);
};

#endif // SOWERPROJECTWRITERAPP_H
