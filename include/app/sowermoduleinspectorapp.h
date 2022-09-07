///////////////////////////////////////////////////////////////////
// Name:        sowermoduleinspectorapp.h
// Purpose:     Sower Module Inspector
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMODULEINSPECTORAPP_H
#define SOWERMODULEINSPECTORAPP_H

#include "framework/frame.h"
#include "controls/controls.h"
#include "controls/moduletreectrl.h"
#include "controls/stretchfitctrls.h"
#include "module/modulebase.h"
#include "framework/viewbook.h"
#include "framework/menubar.h"
#include <wx/aui/aui.h>
#include <wx/checkbox.h>
#include <wx/gbsizer.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/stattext.h>

class SowerModuleInspectorApp : public SwBaseApp
{
public:
    virtual bool OnInit();
};

class SowerModuleInspectorFrame: public SwFrame
{
public:
    SowerModuleInspectorFrame(wxWindow* parent,wxWindowID id, const wxString &title,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SowerModuleInspectorFrame();

    SwCheckBox* AllowCopyCheckBox;
    SwCheckBox* EncryptedCheckBox;
    SwStretchColumnListCtrl* MediaListCtrl;
    SwStretchColumnListCtrl* NotesListCtrl;
    SwStretchColumnListCtrl* StrongsGListCtrl;
    SwStretchColumnListCtrl* StrongsHListCtrl;
    SwStretchColumnListCtrl* TermListCtrl;
    wxNotebook* Notebook;
    SwImageWindow* ImageView;
    wxPanel* Panel1;
    SwViewBook * ViewNoteBook;
    wxSplitterWindow* SplitterWindow1;
    wxStaticText* AbbreviationLabel;
    wxStaticText* AllowCopyLabel;
    wxStaticText* CategoryLabel;
    wxStaticText* EncryptedLabel;
    wxStaticText* GroupLabel;
    wxStaticText* IdentifierLabel;
    wxStaticText* OFNLabel;
    wxStaticText* TitleLabel;
    wxStaticText* VersificationLabel;
    SwFittedTextCtrl* AbbreviationTextCtrl;
    SwFittedTextCtrl* CategoryTextCtrl;
    SwFittedTextCtrl* GroupTextCtrl;
    SwFittedTextCtrl* IdentifierTextCtrl;
    SwFittedTextCtrl* OFNTextCtrl;
    SwFittedTextCtrl* TitleTextCtrl;
    SwFittedTextCtrl* VersificationTextCtrl;
    SwModuleTreeCtrl* ContentsTreeCtrl;
    wxButton* FindScriptureButton;
    wxButton* InfoButton;
    wxStaticText* ScriptureReferenceLabel;
    SwStretchTextCtrl* ScriptureTextCtrl;
    wxPanel* ScripturePanel;
    wxButton* FindCommentaryButton;
    wxStaticText* CommentaryReferenceLabel;
    SwStretchTextCtrl* CommentaryTextCtrl;
    wxPanel* CommentaryPanel;
    wxStaticText* StatusLabel;
    wxStaticText* PublisherLabel;
    SwFittedTextCtrl* PublisherTextCtrl;

protected:
    static const long ID_TITLELABEL;
    static const long ID_TITLETEXTCTRL;
    static const long ID_ABBREVIATIONLABEL;
    static const long ID_ABBREVIATIONTEXTCTRL;
    static const long ID_IDENTIFIERLABEL;
    static const long ID_IDENTIFIERTEXTCTRL;
    static const long ID_CATEGORYLABEL;
    static const long ID_CATEGORYTEXTCTRL;
    static const long ID_GROUPLABEL;
    static const long ID_GROUPTEXTCTRL;
    static const long ID_VERSIFICATIONLABEL;
    static const long ID_VERSIFICATIONTEXTCTRL;
    static const long ID_OFNLABEL;
    static const long ID_OFNTEXTCTRL;
    static const long ID_ALLOWCOPYLABEL;
    static const long ID_ALLOWCOPYCHECKBOX;
    static const long ID_ENCRYPTEDLABEL;
    static const long ID_ENCRYPTEDCHECKBOX;
    static const long ID_PANEL1;
    static const long ID_CONTENTSTREECTRL;
    static const long ID_MEDIALISTCTRL;
    static const long ID_IMAGEVIEW;
    static const long ID_SPLITTERWINDOW1;
    static const long ID_STRONGSGLISTCTRL;
    static const long ID_STRONGSHLISTCTRL;
    static const long ID_TERMLISTCTRL;
    static const long ID_NOTESLISTCTRL;
    static const long ID_NOTEBOOK;
    static const long ID_VIEWNOTEBOOK;
    static const long ID_STATUSLABEL;
    static const long ID_COPYRIGHTBUTTON;

    static const long ID_SCRIPTUREREFERENCELABEL;
    static const long ID_SCRIPTURETEXTCTRL;
    static const long ID_FINDSCRIPTUREBUTTON;
    static const long ID_SCRIPTUREPANEL;
    static const long ID_COMMENTARYREFERENCELABEL;
    static const long ID_COMMENTARYTEXTCTRL;
    static const long ID_FINDCOMMENTARYBUTTON;
    static const long ID_COMMENTARYPANEL;
    static const long ID_PUBLISHERLABEL;
    static const long ID_PUBLISHERTEXT;

private:
    void OnContentsTreeCtrlSelectionChanged(wxTreeEvent& event);
    void OnMediaListCtrlItemSelect(wxListEvent& event);
    void OnStrongsGListCtrlItemSelect(wxListEvent& event);
    void OnStrongsHListCtrlItemSelect(wxListEvent& event);
    void OnTermListCtrlItemSelect(wxListEvent& event);
    void OnNotesListCtrlItemSelect(wxListEvent& event);
    void OnFindScriptureButtonClick(wxCommandEvent& event);
    void OnFindCommentaryButtonClick(wxCommandEvent& event);
    void OnInfoButtonClick(wxCommandEvent& event);
    virtual void OnOpen(wxCommandEvent & event);
    virtual void OnClose(wxCommandEvent & event);
    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnQuit(wxCommandEvent & event);
    virtual void OnLanguageChange();
    virtual void EnableInterface(bool state);

    void Reset();

    void AddNoteBookPanel();
    void AddModulePanel();
    void AddContentsPanel();
    void AddMediaPanel();
    void AddScripturePanel();
    void AddCommentaryPanel();
    void AddStrongsGPanel();
    void AddStrongsHPanel();
    void AddTermPanel();
    void AddNotesPanel();
    void AddViewPanel();

    SwBasicMenuBar * menuBar;
    swUI16 managerId;
    SwModule * module;
};

#endif // SOWERMODULEINSPECTORAPP_H
