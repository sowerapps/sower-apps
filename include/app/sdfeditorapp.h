///////////////////////////////////////////////////////////////////
// Name:        sdfeditorapp.h
// Purpose:     Sower Data File Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SDFEDITORAPP_H
#define SDFEDITORAPP_H

#include "sdf/datafile.h"
#include "framework/frame.h"
#include "framework/menubar.h"
#include "controls/controls.h"
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/dataview.h>

class SowerDataFileEditorApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerDataFileEditorFrame: public SwFrame
{
public:
    SowerDataFileEditorFrame();
    SowerDataFileEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SowerDataFileEditorFrame();

private:
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTableAddBtnClick(wxCommandEvent& event);
    void OnTableDeleteBtnClick(wxCommandEvent& event);
    void OnTableLoadBtnClick(wxCommandEvent& event);
    void OnTableSaveBtnClick(wxCommandEvent& event);
    void OnTableCloseBtnClick(wxCommandEvent& event);
    void OnIdAddBtnClick(wxCommandEvent& event);
    void OnDeleteIdBtnClick(wxCommandEvent& event);
    void OnReplaceIdBtnClick(wxCommandEvent& event);
    int Find(wxDataViewListCtrl * listctrl, const char * identifier);

    void OnOpen(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);

    static const long ID_TABLESSTATICTEXT;
    static const long ID_TABLEDELETEBTN;
    static const long ID_TABLEADDBTN;
    static const long ID_TABLELOADBTN;
    static const long ID_TABLESLIST;
    static const long ID_CURRENTSTATICTEXT;
    static const long ID_TABLESAVEBTN;
    static const long ID_TABLECLOSEBTN;
    static const long ID_TABLENAMETEXTCTRL;
    static const long ID_TABLESPANEL;
    static const long ID_IDENTIFIERSTATICTEXT;
    static const long ID_IDTEXTCTRL;
    static const long ID_DATASTATICTEXT;
    static const long ID_DATATEXTCTRL;
    static const long ID_P1STATICTEXT;
    static const long ID_P1TEXTCTRL;
    static const long ID_P2STATICTEXT;
    static const long ID_P2TEXTCTRL;
    static const long ID_ADDIDBTN;
    static const long ID_DELETEIDBTN;
    static const long ID_IDENTIFIERPANEL;
    static const long ID_LISTVIEW1;
    static const long ID_STATUSBAR1;

    wxButton* IdAddBtn;
    wxButton* DeleteIdBtn;
    wxButton* TableAddBtn;
    wxButton* TableCloseBtn;
    wxButton* TableDeleteBtn;
    wxButton* TableLoadBtn;
    wxButton* TableSaveBtn;
    wxDataViewListCtrl* DataTable;
    SwStretchColumnListView* TableList;
    wxPanel* IdentifierPanel;
    wxPanel* TablesPanel;
    wxStaticText* CurrentStaticText;
    wxStaticText* DataStaticText;
    wxStaticText* IdentifierStaticText;
    wxStaticText* P1StaticText;
    wxStaticText* P2StaticText;
    wxStaticText* TablesStaticText;
    wxStatusBar* m_statusBar;
    wxTextCtrl* DataTextCtrl;
    wxTextCtrl* IdTextCtrl;
    wxTextCtrl* P1TextCtrl;
    wxTextCtrl* P2TextCtrl;
    wxTextCtrl* TableNameTextCtrl;
    SwBasicEditorMenuBar * menuBar;

    void EnableTableButtons(bool state);
    void EnableIdentifierButtons(bool state);
    void EnableCurrentTableButtons(bool state);
    void EnableMenuItems(bool fileLoaded);
    void Clear();
    SwDataFile m_datafile;
};

#endif // SDFEDITORAPP_H
