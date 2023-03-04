///////////////////////////////////////////////////////////////////
// Name:        librarysearchpanels.cpp
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

#include "../../include/framework/librarysearchpanels.h"
#include "../../include/appi/appifa.h"
#include "../../include/framework/panel.h"
#include "../../include/controls/librarylistctrl.h"

const long SwThMLLibrarySearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwThMLLibrarySearchPanel::ID_SEARCHRESULTSLIST = wxNewId();


SwThMLLibrarySearchPanel::SwThMLLibrarySearchPanel()
{
    m_list = NULL;
}

SwThMLLibrarySearchPanel::~SwThMLLibrarySearchPanel()
{
    m_manager->UnInit();
    Unbind(wxEVT_THREAD, &SwThMLLibrarySearchPanel::OnThreadUpdate, this);
}

SwThMLLibrarySearchPanel::SwThMLLibrarySearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_list = NULL;
    CreateGui();
}

void SwThMLLibrarySearchPanel::Reset()
{
    SearchResultsList->DeleteAllItems();
}

void SwThMLLibrarySearchPanel::CreateGui()
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    SearchCtrlPanel = new SwStretchPanel(this, ID_SEARCHCTRLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHCTRLPANEL");
    SearchCtrlPanel->SetMinSize(wxSize(-1,300));
    wxGridBagSizer * gridbagsizer = new wxGridBagSizer(0, 0);
    SearchStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    gridbagsizer->Add(SearchStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchTextCtrl = new SwStretchTextCtrl(SearchCtrlPanel, ID_SEARCHTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SEARCHTEXTCTRL");
    gridbagsizer->Add(SearchTextCtrl, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchOptionsStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHOPTIONSTEXT, L"Options:", wxDefaultPosition, wxDefaultSize, 0, L"SID_OPTIONS");
    gridbagsizer->Add(SearchOptionsStaticText, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchOptionsChoice = new SwChoice(SearchCtrlPanel, ID_SEARCHOPTIONSCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(SearchOptionsChoice, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchCaseCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_CASESENSITIVE");
    SearchCaseCheckBox->SetValue(false);
    gridbagsizer->Add(SearchCaseCheckBox, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchWordCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHWORDCHECKBOX, "Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_WHOLEWORD");
    SearchWordCheckBox->SetValue(false);
    gridbagsizer->Add(SearchWordCheckBox, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchButton = new SwButton(SearchCtrlPanel, ID_SEARCHBUTTON, L"Search", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_SEARCH");
    gridbagsizer->Add(SearchButton, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    SearchCtrlPanel->SetSizer(gridbagsizer);
    gridbagsizer->Fit(SearchCtrlPanel);
    gridbagsizer->SetSizeHints(SearchCtrlPanel);
    m_manager->AddPane(SearchCtrlPanel, wxAuiPaneInfo().Name(L"SearchPane").CenterPane().Caption(L"Search Pane").Top().DockFixed().MinSize(wxSize(-1,200)));
    SearchResultsList = new SwStretchColumnListCtrl(this, ID_SEARCHRESULTSLIST, wxPoint(9,15), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_SEARCHRESULTSLIST");
    SearchResultsList->AppendColumn(L"SID_SEARCHRESULTS", L"Search Results", wxLIST_FORMAT_LEFT, 300);
    m_manager->AddPane(SearchResultsList, wxAuiPaneInfo().Name(L"SearchListPane").CenterPane().Caption(L"Results").DockFixed().Floatable().Movable(false));
    m_manager->Update();

    GetSearchOptionsList(SearchOptionsChoice);
    SearchOptionsChoice->SetSelection(0);

    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwThMLLibrarySearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwThMLLibrarySearchPanel::OnSearchResultsListItemActivated);

    Bind(wxEVT_THREAD, &SwThMLLibrarySearchPanel::OnThreadUpdate, this);
}

void SwThMLLibrarySearchPanel::SetListCtrl(SwThMLLibraryListCtrl * list)
{
    Reset();
    m_list = list;
}

void SwThMLLibrarySearchPanel::GetSearchOptionsList(SwChoice * choice)
{
    if (!choice)
        return;

    SwClientData * data;

    data = new SwClientData(CF_PHRASE);
    choice->Append(L"Phrase", L"SID_PHRASE", data);

    data = new SwClientData(CF_ANY);
    choice->Append(L"Any Keywords", L"SID_ANYKEYWORDS", data);

    data = new SwClientData(CF_ALL);
    choice->Append(L"All Keywords", L"SID_ALLKEYWORDS", data);

    data = new SwClientData(CF_BOOLEAN);
    choice->Append(L"Boolean", L"SID_BOOLEAN", data);
}

swUI8 SwThMLLibrarySearchPanel::GetSearchOption(SwChoice * choice)
{
    int option = choice->GetCurrentSelection();

    if (option == wxNOT_FOUND)
        return 0;

    SwClientData * data = (SwClientData *) choice->GetClientObject(option);

    if (!data)
        return 0;

    return (swUI8) data->m_data;
}

void SwThMLLibrarySearchPanel::OnSearchButtonClick(wxCommandEvent& event)
{
    if (!m_list)
        return;

    swUI8 flags;

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    flags = GetSearchOption(SearchOptionsChoice);

    m_searchType = flags;

    if (!SearchCaseCheckBox->GetValue())
        flags |= CF_NOCASE;

    m_casesensitive = SearchCaseCheckBox->GetValue();

    if (SearchWordCheckBox->GetValue())
        flags |= CF_WORD;

    m_wholewordonly = SearchWordCheckBox->GetValue();

    SwStringW buffer;
    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_searchText = buffer.GetArray();
    m_compObj.ParseSearchString(buffer, flags);

    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }
}

void SwThMLLibrarySearchPanel::OnSearchResultsListItemActivated(wxListEvent& event)
{
    if (!m_frame)
        return;

    swUI16 managerId = event.GetData();
    swUI16 idx = SwApplicationInterface::GetThMLFileManager().FindByMID(managerId);

    if (idx == NODE_ID_INVALID)
        return;
    SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetAt(idx);

    if (!f)
        return;

    m_frame->ActivateSearchItem(f->GetPath(), m_searchText, m_searchType, m_wholewordonly, m_casesensitive);
}

void SwThMLLibrarySearchPanel::OnLanguageChange()
{
}

void SwThMLLibrarySearchPanel::OnThemeChange()
{
}

wxThread::ExitCode SwThMLLibrarySearchPanel::Entry()
{
    swUI16 managerId;
    SwThMLFile * file;
    SwPageData data;
    swUI8 lch;
    wxThreadEvent * e = NULL;

    SearchButton->Disable();

    for (int i = 0; i < m_list->GetItemCount(); i ++)
    {
        managerId = m_list->GetItemData(i);

        file = SwApplicationInterface::GetThMLFileManager().GetFromMID(managerId);

        if (!file)
            continue;

        for (swUI32 div = 0; div < file->GetTableofContents().GetNodes(); div ++)
        {
            data.m_managerId = managerId;
            data.m_pageId = div;
            SwApplicationInterface::GetThMLFileManager().LoadPage(data, b1);
            lch = LCH_BREAK;
            b2.Size(b1.Strlen() + 1);
            SwHtml::Html2Text(b1, b2, b2.GetSize() - 1, lch, true);
            b3.Copy(b2);
            if (m_compObj.SearchBuffer(b3) == CR_EXPRESSION_PASSED)
            {
                e = new wxThreadEvent();
                e->SetString(m_list->GetItemText(i, 0));
                e->SetExtraLong(managerId);
                wxQueueEvent(GetEventHandler(), e);
                break;
            }
        }
    }

    SearchButton->Enable();
    return (wxThread::ExitCode)0;
}

void SwThMLLibrarySearchPanel::OnThreadUpdate(wxThreadEvent& evt)
{
    wxListItem lItem;
    wxListCtrl * list = (wxListCtrl *) SearchResultsList;
    lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
    lItem.SetColumn(0);
    lItem.SetId(SearchResultsList->GetItemCount());
    lItem.SetText(evt.GetString());
    lItem.SetData(evt.GetExtraLong());
    list->InsertItem(lItem);
}

const long SwModuleLibrarySearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwModuleLibrarySearchPanel::ID_SEARCHRESULTSLIST = wxNewId();

SwModuleLibrarySearchPanel::SwModuleLibrarySearchPanel()
{
    m_list = NULL;
}

SwModuleLibrarySearchPanel::~SwModuleLibrarySearchPanel()
{
    m_manager->UnInit();
    Unbind(wxEVT_THREAD, &SwModuleLibrarySearchPanel::OnThreadUpdate, this);
}

SwModuleLibrarySearchPanel::SwModuleLibrarySearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_list = NULL;
    CreateGui();
}

void SwModuleLibrarySearchPanel::Reset()
{
    SearchResultsList->DeleteAllItems();
}

void SwModuleLibrarySearchPanel::CreateGui()
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    SearchCtrlPanel = new SwStretchPanel(this, ID_SEARCHCTRLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHCTRLPANEL");
    SearchCtrlPanel->SetMinSize(wxSize(-1,300));
    wxGridBagSizer * gridbagsizer = new wxGridBagSizer(0, 0);
    SearchStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    gridbagsizer->Add(SearchStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchTextCtrl = new SwStretchTextCtrl(SearchCtrlPanel, ID_SEARCHTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SEARCHTEXTCTRL");
    gridbagsizer->Add(SearchTextCtrl, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchOptionsStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHOPTIONSTEXT, L"Options:", wxDefaultPosition, wxDefaultSize, 0, L"SID_OPTIONS");
    gridbagsizer->Add(SearchOptionsStaticText, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchOptionsChoice = new SwChoice(SearchCtrlPanel, ID_SEARCHOPTIONSCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(SearchOptionsChoice, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchCaseCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_CASESENSITIVE");
    SearchCaseCheckBox->SetValue(false);
    gridbagsizer->Add(SearchCaseCheckBox, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchWordCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHWORDCHECKBOX, "Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_WHOLEWORD");
    SearchWordCheckBox->SetValue(false);
    gridbagsizer->Add(SearchWordCheckBox, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchButton = new SwButton(SearchCtrlPanel, ID_SEARCHBUTTON, L"Search", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_SEARCH");
    gridbagsizer->Add(SearchButton, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    SearchCtrlPanel->SetSizer(gridbagsizer);
    gridbagsizer->Fit(SearchCtrlPanel);
    gridbagsizer->SetSizeHints(SearchCtrlPanel);
    m_manager->AddPane(SearchCtrlPanel, wxAuiPaneInfo().Name(L"SearchPane").CenterPane().Caption(L"Search Pane").Top().DockFixed().MinSize(wxSize(-1,200)));
    SearchResultsList = new SwStretchColumnListCtrl(this, ID_SEARCHRESULTSLIST, wxPoint(9,15), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_SEARCHRESULTSLIST");
    SearchResultsList->AppendColumn(L"SID_SEARCHRESULTS", L"Search Results", wxLIST_FORMAT_LEFT, 300);
    m_manager->AddPane(SearchResultsList, wxAuiPaneInfo().Name(L"SearchListPane").CenterPane().Caption(L"Results").DockFixed().Floatable().Movable(false));
    m_manager->Update();

    GetSearchOptionsList(SearchOptionsChoice);
    SearchOptionsChoice->SetSelection(0);

    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwModuleLibrarySearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwModuleLibrarySearchPanel::OnSearchResultsListItemActivated);

    Bind(wxEVT_THREAD, &SwModuleLibrarySearchPanel::OnThreadUpdate, this);
}

void SwModuleLibrarySearchPanel::SetListCtrl(SwModuleLibraryListCtrl * list)
{
    Reset();
    m_list = list;
}


void SwModuleLibrarySearchPanel::GetSearchOptionsList(SwChoice * choice)
{
    if (!choice)
        return;

    SwClientData * data;

    data = new SwClientData(CF_PHRASE);
    choice->Append(L"Phrase", L"SID_PHRASE", data);

    data = new SwClientData(CF_ANY);
    choice->Append(L"Any Keywords", L"SID_ANYKEYWORDS", data);

    data = new SwClientData(CF_ALL);
    choice->Append(L"All Keywords", L"SID_ALLKEYWORDS", data);

    data = new SwClientData(CF_BOOLEAN);
    choice->Append(L"Boolean", L"SID_BOOLEAN", data);
}

swUI8 SwModuleLibrarySearchPanel::GetSearchOption(SwChoice * choice)
{
    int option = choice->GetCurrentSelection();

    if (option == wxNOT_FOUND)
        return 0;

    SwClientData * data = (SwClientData *) choice->GetClientObject(option);

    if (!data)
        return 0;

    return (swUI8) data->m_data;
}

void SwModuleLibrarySearchPanel::OnSearchButtonClick(wxCommandEvent& event)
{
    if (!m_list)
        return;

    swUI8 flags;

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    flags = GetSearchOption(SearchOptionsChoice);

    m_searchType = flags;

    if (!SearchCaseCheckBox->GetValue())
        flags |= CF_NOCASE;

    m_casesensitive = SearchCaseCheckBox->GetValue();

    if (SearchWordCheckBox->GetValue())
        flags |= CF_WORD;

    m_wholewordonly = SearchWordCheckBox->GetValue();

    SwStringW buffer;
    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_searchText = buffer.GetArray();
    m_compObj.ParseSearchString(buffer, flags);

    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }
}

void SwModuleLibrarySearchPanel::OnSearchResultsListItemActivated(wxListEvent& event)
{
    if (!m_frame)
        return;

    swUI16 managerId = event.GetData();
    m_frame->ActivateSearchItem(managerId, m_searchText, m_searchType, m_wholewordonly, m_casesensitive);
}

void SwModuleLibrarySearchPanel::OnLanguageChange()
{
}

void SwModuleLibrarySearchPanel::OnThemeChange()
{
}

wxThread::ExitCode SwModuleLibrarySearchPanel::Entry()
{
    swUI16 managerId;
    SwModule * module;
    SwPageData data;
    bool canCopy;
    swUI8 lch;
    wxThreadEvent * e = NULL;

    SearchButton->Disable();

    for (int i = 0; i < m_list->GetItemCount(); i ++)
    {
        managerId = m_list->GetItemData(i);

        module = SwApplicationInterface::GetModuleManager().GetFromMID(managerId);

        if (!module)
            continue;

        for (swUI32 div = 0; div < module->GetTableofContents().GetNodes(); div ++)
        {
            data.m_managerId = managerId;
            data.m_pageId = div;
            SwApplicationInterface::GetModuleManager().LoadPage(data, b1, canCopy);
            lch = LCH_BREAK;
            b2.Size(b1.Strlen() + 1);
            SwHtml::Html2Text(b1, b2, b2.GetSize() - 1, lch, true);
            b3.Copy(b2);
            if (m_compObj.SearchBuffer(b3) == CR_EXPRESSION_PASSED)
            {
                e = new wxThreadEvent();
                e->SetString(m_list->GetItemText(i, 0));
                e->SetExtraLong(managerId);
                wxQueueEvent(GetEventHandler(), e);
                break;
            }
        }
    }

    SearchButton->Enable();
    return (wxThread::ExitCode)0;
}

void SwModuleLibrarySearchPanel::OnThreadUpdate(wxThreadEvent& evt)
{
    wxListItem lItem;
    wxListCtrl * list = (wxListCtrl *) SearchResultsList;
    lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
    lItem.SetColumn(0);
    lItem.SetId(SearchResultsList->GetItemCount());
    lItem.SetText(evt.GetString());
    lItem.SetData(evt.GetExtraLong());
    list->InsertItem(lItem);
}

