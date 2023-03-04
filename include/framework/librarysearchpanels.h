///////////////////////////////////////////////////////////////////
// Name:        librarysearchpanels.h
// Purpose:     Search panels for LibraryListCtrls.
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

#ifndef LIBRARYSEARCHPANELS_H
#define LIBRARYSEARCHPANELS_H

#include "panel.h"
#include "viewbook.h"
#include "../richtext/findreplace.h"
#include "../controls/moduletreectrl.h"
#include "../controls/thmltreectrl.h"
#include "../controls/stretchfitctrls.h"
#include "../controls/librarylistctrl.h"

class SOWERBASEEXP SwThMLLibrarySearchPanel : public SwPanel, public wxThreadHelper
{
public:
    SwThMLLibrarySearchPanel();
    SwThMLLibrarySearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwThMLLibrarySearchPanel();

    void Reset();
    void CreateGui();
    void SetFrame(SwFrame * frame)
    {
        m_frame = frame;
    }
    void SetListCtrl(SwThMLLibraryListCtrl * list);
    static void GetSearchOptionsList(SwChoice * choice);
    static swUI8 GetSearchOption(SwChoice * choice);
    void OnSearchButtonClick(wxCommandEvent& event);
    void OnSearchResultsListItemActivated(wxListEvent& event);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

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
    SwThMLLibraryListCtrl* m_list;

protected:
    virtual wxThread::ExitCode Entry();
    void OnThreadUpdate(wxThreadEvent& evt);
    SwStringCompareW m_compObj;
    SwStringW m_searchText;
    swUI8 m_searchType;
    bool m_wholewordonly;
    bool m_casesensitive;
    SwFrame * m_frame;

    SwString  b1;
    SwString  b2;
    SwStringW b3;
};


class SOWERBASEEXP SwModuleLibrarySearchPanel : public SwPanel, public wxThreadHelper
{
public:
    SwModuleLibrarySearchPanel();
    SwModuleLibrarySearchPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwModuleLibrarySearchPanel();

    void Reset();
    void CreateGui();
    void SetFrame(SwFrame * frame)
    {
        m_frame = frame;
    }
    void SetListCtrl(SwModuleLibraryListCtrl * list);
    static void GetSearchOptionsList(SwChoice * choice);
    static swUI8 GetSearchOption(SwChoice * choice);
    void OnSearchButtonClick(wxCommandEvent& event);
    void OnSearchResultsListItemActivated(wxListEvent& event);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

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
    SwModuleLibraryListCtrl* m_list;

protected:
    virtual wxThread::ExitCode Entry();
    void OnThreadUpdate(wxThreadEvent& evt);
    SwStringCompareW m_compObj;
    SwStringW m_searchText;
    swUI8 m_searchType;
    bool m_wholewordonly;
    bool m_casesensitive;
    SwFrame * m_frame;

    SwString  b1;
    SwString  b2;
    SwStringW b3;
};

#endif // LIBRARYSEARCHPANELS_H
