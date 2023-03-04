///////////////////////////////////////////////////////////////////
// Name:        themeeditorapp.h
// Purpose:     Sower Theme Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THEMEEDITORAPP_H
#define THEMEEDITORAPP_H

#include "imgwin/imagewindow.h"
#include "sdf/datafile.h"
#include "framework/frame.h"
#include "controls/controls.h"
#include "framework/menubar.h"
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>

class SowerThemeEditorApp : public SwBaseApp
{
public:
    virtual bool OnInit();
};

class SowerThemeEditorFrame: public SwFrame
{
public:
    SowerThemeEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SowerThemeEditorFrame();

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

    void OnThemeGridItemFocused(wxListEvent& event);
    void OnThemeGridBeginLabelEdit(wxListEvent& event);

    void OnOpen(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);

    static const long ID_IDENTIFIERSTATICTEXT;
    static const long ID_IDDELETEBTN;
    static const long ID_IDTEXTCTRL;
    static const long ID_IDADDBTN;
    static const long ID_STATICLINE1;
    static const long ID_TABLESSTATICTEXT;
    static const long ID_TABLEDELETEBTN;
    static const long ID_TABLEADDBTN;
    static const long ID_TABLELOADBTN;
    static const long ID_IDENTIFIERLISTVIEW;
    static const long ID_THEMELISTVIEW;
    static const long ID_CURRENTTABLESTATICTEXT;
    static const long ID_TABLESAVEBTN;
    static const long ID_TABLECLOSEBTN;
    static const long ID_NAMETEXTCTRL;
    static const long ID_PANEL1;
    static const long ID_CUSTOM1;
    static const long ID_CUSTOM2;
    static const long ID_STATUSBAR1;

    SwImageWindow* ImagePreview;
    wxButton* IdAddBtn;
    wxButton* IdDeleteBtn;
    wxButton* TableAddBtn;
    wxButton* TableCloseBtn;
    wxButton* TableDeleteBtn;
    wxButton* TableLoadBtn;
    wxButton* TableSaveBtn;
    SwStretchColumnListView* IdentifierList;
    SwStretchColumnListView* ThemeList;
    wxPanel* Panel1;
    wxListView* ThemeGrid;
    wxStaticLine* StaticLine1;
    wxStaticText* CurrentTableStaticText;
    wxStaticText* IdentifierStaticText;
    wxStaticText* TablesStaticText;
    wxStatusBar* m_statusBar;
    wxTextCtrl* IdTextCtrl;
    wxTextCtrl* ThemeNameTextCtrl;

    void EnableTableButtons(bool state);
    void EnableIdentifierButtons(bool state);
    void EnableCurrentTableButtons(bool state);
    void EnableMenuItems(bool fileLoaded);
    void Clear();

    SwBasicEditorMenuBar * menuBar;
    SwDataFile m_datafile;
};

#endif // THEMEEDITORAPP_H
