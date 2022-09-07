///////////////////////////////////////////////////////////////////
// Name:        translationeditorapp.h
// Purpose:     Sower Translation Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef TRANSLATIONEDITORAPP_H
#define TRANSLATIONEDITORAPP_H

#include "sdf/datafile.h"
#include "framework/frame.h"
#include "controls/controls.h"
#include "framework/menubar.h"
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>

class SowerTranslationEditorApp : public wxApp
{
    public:
        virtual bool OnInit();
};

class SowerTranslationEditorFrame: public SwFrame
{
    public:

        SowerTranslationEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
        virtual ~SowerTranslationEditorFrame();

    private:
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnIdAddBtnClick(wxCommandEvent& event);
        void OnIdDeleteBtnClick(wxCommandEvent& event);
        void OnTableAddBtnClick(wxCommandEvent& event);
        void OnTableDeleteBtnClick(wxCommandEvent& event);
        void OnTableLoadBtnClick(wxCommandEvent& event);
        void OnTableSaveBtnClick(wxCommandEvent& event);
        void OnTableCloseBtnClick(wxCommandEvent& event);

        void OnOpen(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        void OnClose(wxCommandEvent& event);

        static const long ID_IDENTIFIERSSTATICTEXT;
        static const long ID_IDDELETEBTN;
        static const long ID_IDTEXTCTRL;
        static const long ID_IDADDBTN;
        static const long ID_STATICLINE1;
        static const long ID_TABLESSTATICTEXT;
        static const long ID_LANGUAGECHOICE;
        static const long ID_TABLEDELETEBTN;
        static const long ID_TABLEADDBTN;
        static const long ID_TABLELOADBTN;
        static const long ID_IDENTIFIERLISTVIEW;
        static const long ID_TRANSLATIONLISTVIEW;
        static const long ID_CURRENTSTATICTEXT;
        static const long ID_TABLESAVEBTN;
        static const long ID_TABLECLOSEBTN;
        static const long ID_PANEL1;
        static const long ID_TRANSLATIONTABLELISTVIEW;
        static const long ID_REFERENCETABLELISTVIEW;
        static const long ID_STATUSBAR1;

        wxButton* IdAddBtn;
        wxButton* IdDeleteBtn;
        wxButton* TableAddBtn;
        wxButton* TableCloseBtn;
        wxButton* TableDeleteBtn;
        wxButton* TableLoadBtn;
        wxButton* TableSaveBtn;
        wxChoice* LanguageChoice;
        SwStretchColumnListView* IdentifierList;
        wxListView* ReferenceTable;
        SwStretchColumnListView* TranslationList;
        wxListView* TranslationTable;
        wxPanel* Panel1;
        wxStaticLine* StaticLine1;
        wxStaticText* CurrentStaticText;
        wxStaticText* IdentifiersStaticText;
        wxStaticText* TablesStaticText;
        wxStatusBar* m_statusBar;
        wxTextCtrl* IdTextCtrl;

        void EnableLanguageButtons(bool state);
        void EnableIdentifierButtons(bool state);
        void EnableTableButtons(bool state);
        void EnableMenuItems(bool fileLoaded);
        void Clear();
        void FillReferenceTable();

        SwBasicEditorMenuBar * menuBar;
        SwDataFile m_datafile;
};

#endif // TRANSLATIONEDITORAPP_H
