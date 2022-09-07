///////////////////////////////////////////////////////////////////
// Name:        thmlbuilderapp.h
// Purpose:     ThML Builder
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLBUILDERAPP_H
#define THMLBUILDERAPP_H

#include "framework/dialog.h"
#include "thml/thml_parser.h"
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

class ThMLBuilderDlg : public SwDialog, public wxThreadHelper
{
    public:
        ThMLBuilderDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
        virtual ~ThMLBuilderDlg();

        void OnQuit(wxCommandEvent& event);
        void OnSaveAsFilePickerCtrlFileChanged(wxFileDirPickerEvent& event);
        void OnSourceButtonClick(wxCommandEvent& event);
        void OnOKButtonClick(wxCommandEvent& event);
        void Reset();
        void ProcessFile();
		void OnThreadUpdate(wxThreadEvent& evt);

		void OnaboutButtonClick(wxCommandEvent& event);
		const char * GenerateId(swUI16 element);
        bool IsSkipElement(swUI16 element);
        void SetIds(SwThMLParser * parser);

		static const long ID_SOURCEBUTTON;
		static const long ID_FILESLISTCTRL;
		static const long ID_SAVEASLABEL;
		static const long ID_SAVEASFILEPICKERCTRL;
		static const long ID_PROGRESSGAUGE;
		static const long ID_ABOUTBUTTON;
		static const long ID_STATUSLABEL;
		static const long ID_BUILDBUTTON;

        wxButton* aboutButton;
        wxButton* okButton;
        wxButton* sourceButton;
        wxFileDialog* sourceFileDialog;
        SwFittedFilePickerCtrl* saveasFilePickerCtrl;
        wxGauge* progressGauge;
        wxRearrangeCtrl* filesListCtrl;
        wxStaticText* saveasLabel;
        wxStaticText* statusLabel;

    protected:
        virtual wxThread::ExitCode Entry();
        SwProgressData m_progressData;
        int m_div;
        int m_par;
        int m_item;
};

#endif // THMLBUILDERAPP_H
