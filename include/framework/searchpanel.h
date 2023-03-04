///////////////////////////////////////////////////////////////////
// Name:        searchpanel.h
// Purpose:     Search panel for SwThMLTreeCtrl, and SwModuleTreeCtrl.
//              In module files divN can have a type attribute
//              to identify the viewer to use. Some of those viewers
//              will not display text in the div but display other
//              media specified in the div. Text in the div will still
//              be searched and can produce search results. So in a map
//              for example to cause search routines to identify places
//              shown on the map insert text similar to this:
//              <p>place 1, place2, etc.</p>.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include "panel.h"
#include "viewbook.h"
#include "../richtext/findreplace.h"
#include "../controls/moduletreectrl.h"
#include "../controls/thmltreectrl.h"
#include "../controls/stretchfitctrls.h"
#include "../controls/controls.h"
#include "../string/stringcompare.h"

class SOWERBASEEXP SwThMLSearchPanel : public SwPanel
{
public:
    SwThMLSearchPanel();
    SwThMLSearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwThMLSearchPanel();

    void Reset();
    void CreateGui();
    void SetTreeCtrl(SwThMLTreeCtrl * tree);
    void SetViewBook(SwViewBook * book);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    static void GetSearchOptionsList(SwChoice * choice);
    static swUI8 GetSearchOption(SwChoice * choice);

    void OnSearchButtonClick(wxCommandEvent& event);
    void OnSearchResultsListItemActivated(wxListEvent& event);

    static const long ID_SEARCHCTRLPANEL;
    static const long ID_SEARCHSTATICTEXT;
    static const long ID_SEARCHTEXTCTRL;
    static const long ID_SEARCHOPTIONSTEXT;
    static const long ID_SEARCHOPTIONSCHOICE;
    static const long ID_SEARCHCASECHECKBOX;
    static const long ID_SEARCHWORDCHECKBOX;
    static const long ID_SEARCHBUTTON;
    static const long ID_SEARCHRESULTSLIST;

    SwStretchPanel* SearchCtrlPanel;
    SwStaticText* SearchStaticText;
    SwStretchTextCtrl* SearchTextCtrl;
    SwStaticText* SearchOptionsStaticText;
    SwChoice* SearchOptionsChoice;
    SwCheckBox* SearchCaseCheckBox;
    SwCheckBox* SearchWordCheckBox;
    SwButton* SearchButton;
    SwStretchColumnListCtrl* SearchResultsList;
    SwThMLTreeCtrl* m_tree;
    SwViewBook* m_book;

protected:
    SwStringCompareW m_compObj;
    bool m_first;
};

class SOWERBASEEXP SwMultiFileThMLSearchPanel : public SwPanel, public wxThreadHelper
{
public:
    SwMultiFileThMLSearchPanel();
    SwMultiFileThMLSearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwMultiFileThMLSearchPanel();

    void Reset();
    void CreateGui();
    void SetTreeCtrl(SwThMLTreeCtrl * tree);
    void SetViewBook(SwViewBook * book);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    void OnSearchExtentChoiceSelect(wxCommandEvent& event);
    void OnSearchButtonClick(wxCommandEvent& event);
    void OnSearchResultsListItemActivated(wxListEvent& event);
    void SetId(bool state)
    {
        m_addId = state;
    }
    static const long ID_SEARCHCTRLPANEL;

    static const long ID_SEARCHEXTENTSTATICTEXT;
    static const long ID_SEARCHEXTENTCHOICE;
    static const long ID_LIBRARYCHOICE;
    static const long ID_SEARCHSTATICTEXT;
    static const long ID_SEARCHTEXTCTRL;
    static const long ID_SEARCHOPTIONSTEXT;
    static const long ID_SEARCHOPTIONSCHOICE;
    static const long ID_SEARCHCASECHECKBOX;
    static const long ID_SEARCHWORDCHECKBOX;
    static const long ID_SEARCHBUTTON;
    static const long ID_SEARCHRESULTSLIST;

    SwStretchPanel* SearchCtrlPanel;
    SwStaticText* SearchStaticText;
    SwFittedChoiceCtrl* SearchExtentChoice;
    SwFittedChoiceCtrl* LibraryChoice;
    SwStaticText* SearchExtentStaticText;
    SwStretchTextCtrl* SearchTextCtrl;
    SwStaticText* SearchOptionsStaticText;
    SwChoice* SearchOptionsChoice;
    SwCheckBox* SearchCaseCheckBox;
    SwCheckBox* SearchWordCheckBox;
    SwButton* SearchButton;
    SwStretchColumnListCtrl* SearchResultsList;
    SwThMLTreeCtrl* m_tree;
    SwViewBook* m_book;

protected:
    virtual wxThread::ExitCode Entry();
    virtual void OnDelete();
    void OnThreadUpdate(wxThreadEvent& evt);
    bool m_hasThread;
    SwStringCompareW m_compObj;
    SwFindReplace m_findreplace;
    bool m_first;
    bool m_addId;
};

class SOWERBASEEXP SwModuleSearchPanel : public SwPanel
{
public:
    SwModuleSearchPanel();
    SwModuleSearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwModuleSearchPanel();

    void Reset();
    void CreateGui();
    void SetTreeCtrl(SwModuleTreeCtrl * tree);
    void SetViewBook(SwViewBook * book);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    void OnSearchButtonClick(wxCommandEvent& event);
    void OnSearchResultsListItemActivated(wxListEvent& event);
    void SetId(bool state)
    {
        m_addId = state;
    }
    static const long ID_SEARCHCTRLPANEL;
    static const long ID_SEARCHSTATICTEXT;
    static const long ID_SEARCHTEXTCTRL;
    static const long ID_SEARCHOPTIONSTEXT;
    static const long ID_SEARCHOPTIONSCHOICE;
    static const long ID_SEARCHCASECHECKBOX;
    static const long ID_SEARCHWORDCHECKBOX;
    static const long ID_SEARCHBUTTON;
    static const long ID_SEARCHRESULTSLIST;

    SwStretchPanel* SearchCtrlPanel;
    SwStaticText* SearchStaticText;
    SwStretchTextCtrl* SearchTextCtrl;
    SwStaticText* SearchOptionsStaticText;
    SwChoice* SearchOptionsChoice;
    SwCheckBox* SearchCaseCheckBox;
    SwCheckBox* SearchWordCheckBox;
    SwButton* SearchButton;
    SwStretchColumnListCtrl* SearchResultsList;
    SwModuleTreeCtrl* m_tree;
    SwViewBook* m_book;

protected:
    SwStringCompareW m_compObj;
    SwFindReplace m_findreplace;
    bool m_first;
    bool m_addId;
};

class SOWERBASEEXP SwBaseMultiSearchPanel : public SwPanel, public wxThreadHelper
{
public:
    SwBaseMultiSearchPanel();
    SwBaseMultiSearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwBaseMultiSearchPanel();

    void Reset();
    void CreateGui();
    void SetViewBook(SwViewBook * book);

    virtual void OnSearchButtonClick(wxCommandEvent& event) {};
    virtual void OnSearchResultsListItemActivated(wxListEvent& event) {};
    virtual void OnSearchResultsList2ItemActivated(wxListEvent& event) {};

    static const long ID_SEARCHCTRLPANEL;
    static const long ID_SEARCHSTATICTEXT;
    static const long ID_SEARCHTEXTCTRL;
    static const long ID_SEARCHOPTIONSTEXT;
    static const long ID_SEARCHOPTIONSCHOICE;
    static const long ID_SEARCHCASECHECKBOX;
    static const long ID_SEARCHWORDCHECKBOX;
    static const long ID_SEARCHBUTTON;
    static const long ID_SEARCHRESULTSLIST;
    static const long ID_SEARCHRESULTSLIST2;

    SwStretchPanel* SearchCtrlPanel;
    SwStaticText* SearchStaticText;
    SwStretchTextCtrl* SearchTextCtrl;
    SwStaticText* SearchOptionsStaticText;
    SwChoice* SearchOptionsChoice;
    SwCheckBox* SearchCaseCheckBox;
    SwCheckBox* SearchWordCheckBox;
    SwButton* SearchButton;
    SwStretchColumnListCtrl* SearchResultsList;
    SwStretchColumnListCtrl* SearchResultsList2;
    SwViewBook* m_book;

protected:
    SwStringCompareW m_compObj;
    SwFindReplace m_findreplace;
    bool m_first;
};

class SOWERBASEEXP SwMultiModuleSearchPanel : public SwPanel, public wxThreadHelper
{
public:
    SwMultiModuleSearchPanel();
    SwMultiModuleSearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwMultiModuleSearchPanel();

    void Reset();
    void CreateGui();
    void SetTreeCtrl(SwModuleTreeCtrl * tree);
    void SetViewBook(SwViewBook * book);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    void OnSearchExtentChoiceSelect(wxCommandEvent& event);
    void OnSearchButtonClick(wxCommandEvent& event);
    void OnSearchResultsListItemActivated(wxListEvent& event);
    void SetId(bool state)
    {
        m_addId = state;
    }
    static const long ID_SEARCHCTRLPANEL;

    static const long ID_SEARCHEXTENTSTATICTEXT;
    static const long ID_SEARCHEXTENTCHOICE;
    static const long ID_LIBRARYCHOICE;
    static const long ID_SEARCHSTATICTEXT;
    static const long ID_SEARCHTEXTCTRL;
    static const long ID_SEARCHOPTIONSTEXT;
    static const long ID_SEARCHOPTIONSCHOICE;
    static const long ID_SEARCHCASECHECKBOX;
    static const long ID_SEARCHWORDCHECKBOX;
    static const long ID_SEARCHBUTTON;
    static const long ID_SEARCHRESULTSLIST;

    SwStretchPanel* SearchCtrlPanel;
    SwStaticText* SearchStaticText;
    SwFittedChoiceCtrl* SearchExtentChoice;
    SwFittedChoiceCtrl* LibraryChoice;
    SwStaticText* SearchExtentStaticText;
    SwStretchTextCtrl* SearchTextCtrl;
    SwStaticText* SearchOptionsStaticText;
    SwChoice* SearchOptionsChoice;
    SwCheckBox* SearchCaseCheckBox;
    SwCheckBox* SearchWordCheckBox;
    SwButton* SearchButton;
    SwStretchColumnListCtrl* SearchResultsList;
    SwModuleTreeCtrl* m_tree;
    SwViewBook* m_book;

protected:
    virtual wxThread::ExitCode Entry();
    virtual void OnDelete();
    void OnThreadUpdate(wxThreadEvent& evt);
    bool m_hasThread;
    SwStringCompareW m_compObj;
    SwFindReplace m_findreplace;
    bool m_first;
    bool m_addId;
};

#endif // SEARCHPANEL_H
