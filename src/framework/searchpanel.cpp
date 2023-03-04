///////////////////////////////////////////////////////////////////
// Name:        searchpanel.cpp
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

#include "../../include/framework/searchpanel.h"
#include "../../include/appi/appifa.h"
#include "../../include/framework/panel.h"

const long SwThMLSearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwThMLSearchPanel::ID_SEARCHRESULTSLIST = wxNewId();

SwThMLSearchPanel::SwThMLSearchPanel()
{
    m_tree = NULL;
    m_book = NULL;
}

SwThMLSearchPanel::~SwThMLSearchPanel()
{
    m_manager->UnInit();
}

SwThMLSearchPanel::SwThMLSearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_tree = NULL;
    m_book = NULL;
    CreateGui();
}

void SwThMLSearchPanel::Reset()
{
    SearchResultsList->DeleteAllItems();
    m_book->OnFindReset();
    m_first = true;
}

void SwThMLSearchPanel::CreateGui()
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

    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwThMLSearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwThMLSearchPanel::OnSearchResultsListItemActivated);
}

void SwThMLSearchPanel::SetTreeCtrl(SwThMLTreeCtrl * tree)
{
    m_tree = tree;
}

void SwThMLSearchPanel::SetViewBook(SwViewBook * book)
{
    m_book = book;
}

void SwThMLSearchPanel::OnSearchButtonClick(wxCommandEvent& event)
{
    if (!m_tree)
        return;

    swUI8 flags;

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    flags = GetSearchOption(SearchOptionsChoice);

    if (!SearchCaseCheckBox->GetValue())
        flags |= CF_NOCASE;

    if (SearchWordCheckBox->GetValue())
        flags |= CF_WORD;

    SwStringW buffer;
    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_compObj.ParseSearchString(buffer, flags);
    m_tree->Search(m_compObj, SearchResultsList, false);
}

void SwThMLSearchPanel::OnSearchResultsListItemActivated(wxListEvent& event)
{
    if (!m_tree || !m_book)
        return;

    wxBusyCursor wait;

    SwString data;
    wxTreeItemId * id;

    id = (wxTreeItemId *) SearchResultsList->GetItemData(event.GetItem());

    if (m_tree->IsSelected(id))
    {
        m_book->ResetAll();
        SwTreeDataEx * td;
        td = (SwTreeDataEx *) m_tree->GetItemData(id);

        if (td)
        {
            SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetFromMID(td->m_managerId);
            if (f)
            {
                m_tree->ReadDivText(td, data);
                m_book->OnWriteXmlText(CT_THML, data, data.Strlen(), true, &f->m_cssrules, f->m_basePath);
            }
        }
        else
            return;
    }
    else
        m_tree->SelectItem(id, true);

    for (swI8 i = 0; i < m_compObj.GetKeyWords(); i ++)
    {
        if (m_compObj.GetKeyWord(i) && m_compObj.GetKeyWordType(i) == KT_WORD)
        {
            m_book->OnHilite(m_compObj.GetKeyWord(i), m_compObj.IsModeCaseSensitive(), m_compObj.IsModeWord());
        }
    }

    m_first = true;
}

void SwThMLSearchPanel::OnLanguageChange()
{
}

void SwThMLSearchPanel::OnThemeChange()
{
}

void SwThMLSearchPanel::GetSearchOptionsList(SwChoice * choice)
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

swUI8 SwThMLSearchPanel::GetSearchOption(SwChoice * choice)
{
    int option = choice->GetCurrentSelection();

    if (option == wxNOT_FOUND)
        return 0;

    SwClientData * data = (SwClientData *) choice->GetClientObject(option);

    if (!data)
        return 0;

    return (swUI8) data->m_data;
}


const long SwMultiFileThMLSearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHEXTENTSTATICTEXT = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHEXTENTCHOICE = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_LIBRARYCHOICE = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwMultiFileThMLSearchPanel::ID_SEARCHRESULTSLIST = wxNewId();

SwMultiFileThMLSearchPanel::SwMultiFileThMLSearchPanel()
{
    m_tree = NULL;
    m_book = NULL;
    m_addId = false;
    m_hasThread = false;
}

SwMultiFileThMLSearchPanel::~SwMultiFileThMLSearchPanel()
{
    Unbind(wxEVT_THREAD, &SwMultiFileThMLSearchPanel::OnThreadUpdate, this);
    m_manager->UnInit();
}

SwMultiFileThMLSearchPanel::SwMultiFileThMLSearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_tree = NULL;
    m_book = NULL;
    m_addId = false;
    m_hasThread = false;
    CreateGui();
}

void SwMultiFileThMLSearchPanel::Reset()
{
    if (m_hasThread && GetThread())
        GetThread()->Kill();

    SearchResultsList->DeleteAllItems();
    m_book->OnFindReset();
    m_first = true;
}

void SwMultiFileThMLSearchPanel::CreateGui()
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    SearchCtrlPanel = new SwStretchPanel(this, ID_SEARCHCTRLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHCTRLPANEL");
    SearchCtrlPanel->SetMinSize(wxSize(-1,220));
    wxGridBagSizer * gridbagsizer = new wxGridBagSizer(0, 0);
    SearchExtentStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHEXTENTSTATICTEXT, L"Search Extent:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    gridbagsizer->Add(SearchExtentStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchExtentChoice = new SwFittedChoiceCtrl(SearchCtrlPanel, ID_SEARCHEXTENTCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(SearchExtentChoice, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    LibraryChoice = new SwFittedChoiceCtrl(SearchCtrlPanel, ID_LIBRARYCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(LibraryChoice, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    gridbagsizer->Add(SearchStaticText, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchTextCtrl = new SwStretchTextCtrl(SearchCtrlPanel, ID_SEARCHTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SEARCHTEXTCTRL");
    gridbagsizer->Add(SearchTextCtrl, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchOptionsStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHOPTIONSTEXT, L"Options:", wxDefaultPosition, wxDefaultSize, 0, L"SID_OPTIONS");
    gridbagsizer->Add(SearchOptionsStaticText, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchOptionsChoice = new SwChoice(SearchCtrlPanel, ID_SEARCHOPTIONSCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(SearchOptionsChoice, wxGBPosition(6, 0), wxDefaultSpan, wxALL, 5);
    SearchCaseCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_CASESENSITIVE");
    SearchCaseCheckBox->SetValue(false);
    gridbagsizer->Add(SearchCaseCheckBox, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchWordCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHWORDCHECKBOX, "Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_WHOLEWORD");
    SearchWordCheckBox->SetValue(false);
    gridbagsizer->Add(SearchWordCheckBox, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchButton = new SwButton(SearchCtrlPanel, ID_SEARCHBUTTON, L"Search", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_SEARCH");
    gridbagsizer->Add(SearchButton, wxGBPosition(9, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    SearchCtrlPanel->SetSizer(gridbagsizer);
    gridbagsizer->Fit(SearchCtrlPanel);
    gridbagsizer->SetSizeHints(SearchCtrlPanel);
    m_manager->AddPane(SearchCtrlPanel, wxAuiPaneInfo().Name(L"SearchPane").CenterPane().Caption(L"Search Pane").Top().DockFixed().MinSize(wxSize(-1,200)));
    SearchResultsList = new SwStretchColumnListCtrl(this, ID_SEARCHRESULTSLIST, wxPoint(9,15), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_SEARCHRESULTSLIST");
    SearchResultsList->AppendColumn(L"SID_SEARCHRESULTS", L"Search Results", wxLIST_FORMAT_LEFT, 300);
    m_manager->AddPane(SearchResultsList, wxAuiPaneInfo().Name(L"SearchListPane").CenterPane().Caption(L"Results").DockFixed().Floatable().Movable(false));
    m_manager->Update();
    SwCategory::FillSearchCtrl(SearchExtentChoice);
    SearchExtentChoice->SetSelection(0);
    SwApplicationInterface::GetThMLFileList(LibraryChoice);
    LibraryChoice->SetSelection(0);
    SwThMLSearchPanel::GetSearchOptionsList(SearchOptionsChoice);
    SearchOptionsChoice->SetSelection(0);

    Connect(ID_SEARCHEXTENTCHOICE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SwMultiFileThMLSearchPanel::OnSearchExtentChoiceSelect);
    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwMultiFileThMLSearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwMultiFileThMLSearchPanel::OnSearchResultsListItemActivated);
    Bind(wxEVT_THREAD, &SwMultiFileThMLSearchPanel::OnThreadUpdate, this);
}

void SwMultiFileThMLSearchPanel::SetTreeCtrl(SwThMLTreeCtrl * tree)
{
    m_tree = tree;
}

void SwMultiFileThMLSearchPanel::SetViewBook(SwViewBook * book)
{
    m_book = book;
}

void SwMultiFileThMLSearchPanel::OnSearchExtentChoiceSelect(wxCommandEvent& event)
{
    swUI8 extent = SwCategory::GetCategory(SearchExtentChoice);

    if (extent == 0)
        LibraryChoice->Enable(true);
    else
        LibraryChoice->Enable(false);
}

void SwMultiFileThMLSearchPanel::OnSearchButtonClick(wxCommandEvent& event)
{
    if (m_hasThread)
    {
        GetThread()->Kill();
        OnDelete();
        return;
    }

    if (!m_tree)
        return;

    swUI8 flags;

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    flags = SwThMLSearchPanel::GetSearchOption(SearchOptionsChoice);

    if (!SearchCaseCheckBox->GetValue())
        flags |= CF_NOCASE;

    if (SearchWordCheckBox->GetValue())
        flags |= CF_WORD;

    SwStringW buffer;
    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_compObj.ParseSearchString(buffer, flags);

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_compObj.ParseSearchString(buffer, flags);

    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    m_hasThread = true;

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }
}

void SwMultiFileThMLSearchPanel::OnSearchResultsListItemActivated(wxListEvent& event)
{
    if (!m_tree || !m_book)
        return;

    wxBusyCursor wait;

    SwString data;
    wxTreeItemId * id;

    id = (wxTreeItemId *) SearchResultsList->GetItemData(event.GetItem());

    if (m_tree->IsSelected(id))
    {
        m_book->ResetAll();
        SwTreeDataEx * td;
        td = (SwTreeDataEx *) m_tree->GetItemData(id);

        if (td)
        {
            SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetFromMID(td->m_managerId);
            if (f)
            {
                m_tree->ReadDivText(td, data);
                m_book->OnWriteXmlText(CT_THML, data, data.Strlen(), true, &f->m_cssrules, f->m_basePath);
            }
        }
        else
            return;
    }
    else
        m_tree->SelectItem(id, true);

    for (swI8 i = 0; i < m_compObj.GetKeyWords(); i ++)
    {
        if (m_compObj.GetKeyWord(i) && m_compObj.GetKeyWordType(i) == KT_WORD)
        {
            m_book->OnHilite(m_compObj.GetKeyWord(i), m_compObj.IsModeCaseSensitive(), m_compObj.IsModeWord());
        }
    }

    m_first = true;
}

wxThread::ExitCode SwMultiFileThMLSearchPanel::Entry()
{
    swUI16 managerId;
    SwThMLFile * thmlFile;
    SwPageData data;
    swUI8 searchExtent = SwCategory::GetCategory(SearchExtentChoice);
    SearchButton->SetLabel(SwApplicationInterface::GetControlString("SID_STOP", L"Stop"));
    SwString b1, b2;
    SwClientData * clientData = NULL;
    int sel = LibraryChoice->GetSelection();

    if (searchExtent == CATEGORY_UNKNOWN && sel == wxNOT_FOUND)
    {
        return (wxThread::ExitCode)0;
    }

    if (searchExtent == CATEGORY_UNKNOWN)
    {
        clientData = (SwClientData *) LibraryChoice->GetClientObject(sel);
        managerId = (swUI16) clientData->GetData();
        m_tree->Search(managerId, m_compObj, SearchResultsList, true);
    }
    else
    {
        for (unsigned int i = 0; i < LibraryChoice->GetCount(); i ++)
        {
            if (GetThread()->TestDestroy())
            {
                break;
            }

            clientData = (SwClientData *) LibraryChoice->GetClientObject(i);
            managerId = (swUI16) clientData->GetData();

            thmlFile = SwApplicationInterface::GetThMLFileManager().GetFromMID(managerId);

            if (!thmlFile)
                continue;

            if (searchExtent != CATEGORY_ALLTEXT && searchExtent != thmlFile->GetCategory())
                continue;

            m_tree->Search(managerId, m_compObj, SearchResultsList, true);
        }

    }

    OnDelete();
    return (wxThread::ExitCode)0;
}

void SwMultiFileThMLSearchPanel::OnThreadUpdate(wxThreadEvent& evt)
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

void SwMultiFileThMLSearchPanel::OnDelete()
{
    SearchButton->SetLabel(SwApplicationInterface::GetControlString("SID_SEARCH", L"Search"));
    m_hasThread = false;
}

void SwMultiFileThMLSearchPanel::OnLanguageChange()
{
    int sel = SearchExtentChoice->GetSelection();
    SearchExtentChoice->Clear();
    SwCategory::FillSearchCtrl(SearchExtentChoice);
    SearchExtentChoice->SetSelection(sel);
}

void SwMultiFileThMLSearchPanel::OnThemeChange()
{
}

const long SwModuleSearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwModuleSearchPanel::ID_SEARCHRESULTSLIST = wxNewId();

SwModuleSearchPanel::SwModuleSearchPanel()
{
    m_tree = NULL;
    m_book = NULL;
    m_addId = false;
}

SwModuleSearchPanel::~SwModuleSearchPanel()
{
    m_manager->UnInit();
}

SwModuleSearchPanel::SwModuleSearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_tree = NULL;
    m_book = NULL;
    m_addId = false;
    CreateGui();
}

void SwModuleSearchPanel::Reset()
{
    SearchResultsList->DeleteAllItems();
    m_book->OnFindReset();
    m_first = true;
}

void SwModuleSearchPanel::CreateGui()
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    SearchCtrlPanel = new SwStretchPanel(this, ID_SEARCHCTRLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHCTRLPANEL");
    SearchCtrlPanel->SetMinSize(wxSize(-1,220));
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
    SwThMLSearchPanel::GetSearchOptionsList(SearchOptionsChoice);
    SearchOptionsChoice->SetSelection(0);

    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwModuleSearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwModuleSearchPanel::OnSearchResultsListItemActivated);
}

void SwModuleSearchPanel::SetTreeCtrl(SwModuleTreeCtrl * tree)
{
    m_tree = tree;
}

void SwModuleSearchPanel::SetViewBook(SwViewBook * book)
{
    m_book = book;
}

void SwModuleSearchPanel::OnSearchButtonClick(wxCommandEvent& event)
{
    if (!m_tree)
        return;

    wxBusyCursor wait;
    swUI8 flags;

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    flags = SwThMLSearchPanel::GetSearchOption(SearchOptionsChoice);

    if (!SearchCaseCheckBox->GetValue())
        flags |= CF_NOCASE;

    if (SearchWordCheckBox->GetValue())
        flags |= CF_WORD;

    SwStringW buffer;
    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_compObj.ParseSearchString(buffer, flags);
    m_tree->Search(m_compObj, SearchResultsList, m_addId);
}

void SwModuleSearchPanel::OnSearchResultsListItemActivated(wxListEvent& event)
{
    if (!m_tree || !m_book)
        return;

    wxBusyCursor wait;

    SwString data;
    bool canCopy;
    wxTreeItemId * id;

    id = (wxTreeItemId *) SearchResultsList->GetItemData(event.GetItem());

    if (m_tree->IsSelected(id))
    {
        m_book->ResetAll();
        SwTreeDataEx * td;
        td = (SwTreeDataEx *) m_tree->GetItemData(id);

        if (td)
        {
            m_tree->ReadDivText(td, data, canCopy);
            m_book->OnWriteXmlText(CT_THML, data, true, "");
        }
        else
            return;
    }
    else
        m_tree->SelectItem(id, true);

    for (swI8 i = 0; i < m_compObj.GetKeyWords(); i ++)
    {
        if (m_compObj.GetKeyWord(i) && m_compObj.GetKeyWordType(i) == KT_WORD)
        {
            m_book->OnHilite(m_compObj.GetKeyWord(i), m_compObj.IsModeCaseSensitive(), m_compObj.IsModeWord());
        }
    }

    m_first = true;
}

void SwModuleSearchPanel::OnLanguageChange()
{
}

void SwModuleSearchPanel::OnThemeChange()
{
}

const long SwBaseMultiSearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHRESULTSLIST = wxNewId();
const long SwBaseMultiSearchPanel::ID_SEARCHRESULTSLIST2 = wxNewId();

SwBaseMultiSearchPanel::SwBaseMultiSearchPanel()
{
    m_book = NULL;
}

SwBaseMultiSearchPanel::~SwBaseMultiSearchPanel()
{
    m_manager->UnInit();
}

SwBaseMultiSearchPanel::SwBaseMultiSearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_book = NULL;
    CreateGui();
}

void SwBaseMultiSearchPanel::Reset()
{
    SearchResultsList->DeleteAllItems();
    SearchResultsList2->DeleteAllItems();
    m_book->OnFindReset();
    m_first = true;
}

void SwBaseMultiSearchPanel::CreateGui()
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
    SearchResultsList->AppendColumn(L"SID_LIBRARYRESULTS", L"Library Results", wxLIST_FORMAT_LEFT, 300);
    m_manager->AddPane(SearchResultsList, wxAuiPaneInfo().Name(L"SearchListPane").CenterPane().DockFixed().Floatable().Movable(false));
    SearchResultsList2 = new SwStretchColumnListCtrl(this, ID_SEARCHRESULTSLIST2, wxPoint(9,15), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_SEARCHRESULTSLIST2");
    SearchResultsList2->AppendColumn(L"SID_BOOKRESULTS", L"Book Results", wxLIST_FORMAT_LEFT, 300);
    m_manager->AddPane(SearchResultsList2, wxAuiPaneInfo().Name(L"SearchListPane2").CenterPane().DockFixed().Floatable().Movable(false));


    m_manager->Update();

    SwThMLSearchPanel::GetSearchOptionsList(SearchOptionsChoice);
    SearchOptionsChoice->SetSelection(0);

    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwBaseMultiSearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwBaseMultiSearchPanel::OnSearchResultsListItemActivated);
    Connect(ID_SEARCHRESULTSLIST2,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwBaseMultiSearchPanel::OnSearchResultsList2ItemActivated);

}

void SwBaseMultiSearchPanel::SetViewBook(SwViewBook * book)
{
    m_book = book;
}

const long SwMultiModuleSearchPanel::ID_SEARCHCTRLPANEL = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHEXTENTSTATICTEXT = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHEXTENTCHOICE = wxNewId();
const long SwMultiModuleSearchPanel::ID_LIBRARYCHOICE = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHSTATICTEXT = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHTEXTCTRL = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHOPTIONSTEXT = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHOPTIONSCHOICE = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHCASECHECKBOX = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHWORDCHECKBOX = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHBUTTON = wxNewId();
const long SwMultiModuleSearchPanel::ID_SEARCHRESULTSLIST = wxNewId();

SwMultiModuleSearchPanel::SwMultiModuleSearchPanel()
{
    m_tree = NULL;
    m_book = NULL;
    m_addId = false;
    m_hasThread = false;
}

SwMultiModuleSearchPanel::~SwMultiModuleSearchPanel()
{
    Unbind(wxEVT_THREAD, &SwMultiModuleSearchPanel::OnThreadUpdate, this);
    m_manager->UnInit();
}

SwMultiModuleSearchPanel::SwMultiModuleSearchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_tree = NULL;
    m_book = NULL;
    m_addId = false;
    m_hasThread = false;
    CreateGui();
}

void SwMultiModuleSearchPanel::Reset()
{
    if (m_hasThread && GetThread())
        GetThread()->Kill();

    SearchResultsList->DeleteAllItems();
    m_book->OnFindReset();
    m_first = true;
}

void SwMultiModuleSearchPanel::CreateGui()
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    SearchCtrlPanel = new SwStretchPanel(this, ID_SEARCHCTRLPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHCTRLPANEL");
    SearchCtrlPanel->SetMinSize(wxSize(-1,220));
    wxGridBagSizer * gridbagsizer = new wxGridBagSizer(0, 0);
    SearchExtentStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHEXTENTSTATICTEXT, L"Search Extent:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    gridbagsizer->Add(SearchExtentStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchExtentChoice = new SwFittedChoiceCtrl(SearchCtrlPanel, ID_SEARCHEXTENTCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(SearchExtentChoice, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    LibraryChoice = new SwFittedChoiceCtrl(SearchCtrlPanel, ID_LIBRARYCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(LibraryChoice, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    gridbagsizer->Add(SearchStaticText, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchTextCtrl = new SwStretchTextCtrl(SearchCtrlPanel, ID_SEARCHTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SEARCHTEXTCTRL");
    gridbagsizer->Add(SearchTextCtrl, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SearchOptionsStaticText = new SwStaticText(SearchCtrlPanel, ID_SEARCHOPTIONSTEXT, L"Options:", wxDefaultPosition, wxDefaultSize, 0, L"SID_OPTIONS");
    gridbagsizer->Add(SearchOptionsStaticText, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchOptionsChoice = new SwChoice(SearchCtrlPanel, ID_SEARCHOPTIONSCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_SEARCHOPTIONSCHOICE");
    gridbagsizer->Add(SearchOptionsChoice, wxGBPosition(6, 0), wxDefaultSpan, wxALL, 5);
    SearchCaseCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_CASESENSITIVE");
    SearchCaseCheckBox->SetValue(false);
    gridbagsizer->Add(SearchCaseCheckBox, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchWordCheckBox = new SwCheckBox(SearchCtrlPanel, ID_SEARCHWORDCHECKBOX, "Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_WHOLEWORD");
    SearchWordCheckBox->SetValue(false);
    gridbagsizer->Add(SearchWordCheckBox, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SearchButton = new SwButton(SearchCtrlPanel, ID_SEARCHBUTTON, L"Search", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_SEARCH");
    gridbagsizer->Add(SearchButton, wxGBPosition(9, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
    SearchCtrlPanel->SetSizer(gridbagsizer);
    gridbagsizer->Fit(SearchCtrlPanel);
    gridbagsizer->SetSizeHints(SearchCtrlPanel);
    m_manager->AddPane(SearchCtrlPanel, wxAuiPaneInfo().Name(L"SearchPane").CenterPane().Caption(L"Search Pane").Top().DockFixed().MinSize(wxSize(-1,200)));
    SearchResultsList = new SwStretchColumnListCtrl(this, ID_SEARCHRESULTSLIST, wxPoint(9,15), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, L"ID_SEARCHRESULTSLIST");
    SearchResultsList->AppendColumn(L"SID_SEARCHRESULTS", L"Search Results", wxLIST_FORMAT_LEFT, 300);
    m_manager->AddPane(SearchResultsList, wxAuiPaneInfo().Name(L"SearchListPane").CenterPane().Caption(L"Results").DockFixed().Floatable().Movable(false));
    m_manager->Update();
    SwCategory::FillSearchCtrl(SearchExtentChoice);
    SearchExtentChoice->SetSelection(0);
    SwApplicationInterface::GetModuleList(LibraryChoice);
    LibraryChoice->SetSelection(0);
    SwThMLSearchPanel::GetSearchOptionsList(SearchOptionsChoice);
    SearchOptionsChoice->SetSelection(0);

    Connect(ID_SEARCHEXTENTCHOICE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SwMultiModuleSearchPanel::OnSearchExtentChoiceSelect);
    Connect(ID_SEARCHBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwMultiModuleSearchPanel::OnSearchButtonClick);
    Connect(ID_SEARCHRESULTSLIST,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwMultiModuleSearchPanel::OnSearchResultsListItemActivated);
    Bind(wxEVT_THREAD, &SwMultiModuleSearchPanel::OnThreadUpdate, this);
}

void SwMultiModuleSearchPanel::SetTreeCtrl(SwModuleTreeCtrl * tree)
{
    m_tree = tree;
}

void SwMultiModuleSearchPanel::SetViewBook(SwViewBook * book)
{
    m_book = book;
}

void SwMultiModuleSearchPanel::OnSearchExtentChoiceSelect(wxCommandEvent& event)
{
    swUI8 extent = SwCategory::GetCategory(SearchExtentChoice);

    if (extent == 0)
        LibraryChoice->Enable(true);
    else
        LibraryChoice->Enable(false);
}

void SwMultiModuleSearchPanel::OnSearchButtonClick(wxCommandEvent& event)
{
    if (m_hasThread)
    {
        GetThread()->Kill();
        OnDelete();
        return;
    }

    if (!m_tree)
        return;

    swUI8 flags;

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    flags = SwThMLSearchPanel::GetSearchOption(SearchOptionsChoice);

    if (!SearchCaseCheckBox->GetValue())
        flags |= CF_NOCASE;

    if (SearchWordCheckBox->GetValue())
        flags |= CF_WORD;

    SwStringW buffer;
    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_compObj.ParseSearchString(buffer, flags);

    SearchResultsList->DeleteAllItems();

    if (!SearchTextCtrl->GetLineLength(0))
        return;

    buffer = SearchTextCtrl->GetValue().wchar_str();
    m_compObj.ParseSearchString(buffer, flags);

    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    m_hasThread = true;

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }
}

void SwMultiModuleSearchPanel::OnSearchResultsListItemActivated(wxListEvent& event)
{
    if (!m_tree || !m_book)
        return;

    wxBusyCursor wait;

    SwString data;
    bool canCopy;
    wxTreeItemId * id;

    id = (wxTreeItemId *) SearchResultsList->GetItemData(event.GetItem());

    if (m_tree->IsSelected(id))
    {
        m_book->ResetAll();
        SwTreeDataEx * td;
        td = (SwTreeDataEx *) m_tree->GetItemData(id);

        if (td)
        {
            m_tree->ReadDivText(td, data, canCopy);
            m_book->OnWriteXmlText(CT_THML, data, true, "");
        }
        else
            return;
    }
    else
        m_tree->SelectItem(id, true);

    for (swI8 i = 0; i < m_compObj.GetKeyWords(); i ++)
    {
        if (m_compObj.GetKeyWord(i) && m_compObj.GetKeyWordType(i) == KT_WORD)
        {
            m_book->OnHilite(m_compObj.GetKeyWord(i), m_compObj.IsModeCaseSensitive(), m_compObj.IsModeWord());
        }
    }

    m_first = true;
}

wxThread::ExitCode SwMultiModuleSearchPanel::Entry()
{
    swUI16 managerId;
    SwModule * module;
    SwPageData data;
    swUI8 searchExtent = SwCategory::GetCategory(SearchExtentChoice);
    SearchButton->SetLabel(SwApplicationInterface::GetControlString("SID_STOP", L"Stop"));
    SwString b1, b2;
    SwClientData * clientData = NULL;
    int sel = LibraryChoice->GetSelection();

    if (searchExtent == CATEGORY_UNKNOWN && sel == wxNOT_FOUND)
    {
        return (wxThread::ExitCode)0;
    }

    if (searchExtent == CATEGORY_UNKNOWN)
    {
        clientData = (SwClientData *) LibraryChoice->GetClientObject(sel);
        managerId = (swUI16) clientData->GetData();
        m_tree->Search(managerId, m_compObj, SearchResultsList, true);
    }
    else
    {
        for (unsigned int i = 0; i < LibraryChoice->GetCount(); i ++)
        {
            if (GetThread()->TestDestroy())
            {
                break;
            }

            clientData = (SwClientData *) LibraryChoice->GetClientObject(i);
            managerId = (swUI16) clientData->GetData();

            module = SwApplicationInterface::GetModuleManager().GetFromMID(managerId);

            if (!module)
                continue;

            if (searchExtent != CATEGORY_ALLTEXT && searchExtent != module->GetHeader().category)
                continue;

            m_tree->Search(managerId, m_compObj, SearchResultsList, true);
        }

    }

    OnDelete();
    return (wxThread::ExitCode)0;
}

void SwMultiModuleSearchPanel::OnThreadUpdate(wxThreadEvent& evt)
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

void SwMultiModuleSearchPanel::OnDelete()
{
    SearchButton->SetLabel(SwApplicationInterface::GetControlString("SID_SEARCH", L"Search"));
    m_hasThread = false;
}

void SwMultiModuleSearchPanel::OnLanguageChange()
{
    int sel = SearchExtentChoice->GetSelection();
    SearchExtentChoice->Clear();
    SwCategory::FillSearchCtrl(SearchExtentChoice);
    SearchExtentChoice->SetSelection(sel);
}

void SwMultiModuleSearchPanel::OnThemeChange()
{
}
