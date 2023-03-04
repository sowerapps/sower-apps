///////////////////////////////////////////////////////////////////
// Name:        bookpanels.cpp
// Purpose:     Panels with contents, search, and find panels.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/bookpanels.h"
#include "../../include/appi/appifa.h"
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>

const long SwThMLBookPanel::ID_TOCTREECTRL = wxNewId();
const long SwThMLBookPanel::ID_CONTENTSPANEL = wxNewId();
const long SwThMLBookPanel::ID_SEARCHPANEL = wxNewId();
const long SwThMLBookPanel::ID_FINDPANEL = wxNewId();
const long SwThMLBookPanel::ID_TOOLNOTEBOOK = wxNewId();
const long SwThMLBookPanel::ID_VIEWBOOK = wxNewId();
SwString SwThMLBookPanel::m_buffer;

SwThMLBookPanel::SwThMLBookPanel()
{
    m_buffer.Size(32768);
    m_allowbookmarks = true;
    m_group = 0;
}

SwThMLBookPanel::SwThMLBookPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_buffer.Size(32768);
    m_allowbookmarks = true;
    m_group = 0;
    BuildContent(parent,id,pos,size);
}

void SwThMLBookPanel::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    ToolNotebook = new wxNotebook(this, ID_TOOLNOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, L"ID_TOOLNOTEBOOK");
    ToolNotebook->SetMinSize(wxSize(300,-1));
    ToolNotebook->SetBackgroundColour(*wxWHITE);
    TocTreeCtrl = new SwThMLTreeCtrl(ToolNotebook, ID_TOCTREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, L"ID_TOCTREECTRL");
    TocTreeCtrl->SetMinSize(wxSize(300,-1));
    ToolNotebook->AddPage(TocTreeCtrl, L"Contents", false);
    searchPanel = new SwThMLSearchPanel(ToolNotebook, ID_SEARCHPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHPANEL");
    ToolNotebook->AddPage(searchPanel, L"Search", false);
    findPanel = new SwFindPanel(ToolNotebook, ID_FINDPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_FINDPANEL");
    ToolNotebook->AddPage(findPanel, L"Find", false);
    m_manager->AddPane(ToolNotebook, wxAuiPaneInfo().Name(L"ToolBook").DefaultPane().CaptionVisible(false).CloseButton(false).Left().Floatable(false).MinSize(wxSize(200,-1)));
    viewBook = new SwViewBook(this, ID_VIEWBOOK, wxDefaultPosition, wxDefaultSize, 0,  L"ID_VIEWBOOK");
    m_manager->AddPane(viewBook, wxAuiPaneInfo().Name(L"View Pane").DefaultPane().CaptionVisible(false).Center().DockFixed().Floatable(false));
    m_manager->Update();

    viewBook->OnSetSwThMLTreeCtrl(TocTreeCtrl);
    findPanel->SetViewBook(viewBook);
    searchPanel->SetTreeCtrl(TocTreeCtrl);
    searchPanel->SetViewBook(viewBook);

    OnLanguageChange();

    Connect(ID_TOCTREECTRL,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&SwThMLBookPanel::OnTreeItemSelChanged);
}

SwThMLBookPanel::~SwThMLBookPanel()
{
    m_manager->UnInit();
}

void SwThMLBookPanel::OnTreeItemSelChanged(wxTreeEvent& event)
{
    wxBusyCursor wait;
    SwString data;
    SwScrollData scrollData;

    viewBook->OnGetScrollPos(scrollData);
    viewBook->ResetAll();

    if (TocTreeCtrl->IsRoot(event.GetItem()))
        return;

    TocTreeCtrl->GetHistory().SetLastItemScrollData(scrollData);

    findPanel->Reset();
    SwTreeDataEx * td;
    td = (SwTreeDataEx *) TocTreeCtrl->GetItemData(event.GetItem());

    if (!td || td->m_managerId < MANAGER_ID_START)
        return;

    SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetFromMID(td->m_managerId);
    if (!f)
        return;

    m_buffer.Reset();
    TocTreeCtrl->ReadDivText(td, m_buffer);

    viewBook->OnWriteXmlText(CT_THML, m_buffer, m_buffer.Strlen(), true, &f->m_cssrules, f->m_basePath);

    TocTreeCtrl->GetHistory().SetLastItemScrollData(scrollData);
    TocTreeCtrl->GetHistory().Append(event.GetItem());
    findPanel->Reset();
    TocTreeCtrl->Expand(event.GetItem());
    viewBook->SetTitle(TocTreeCtrl->GetItemText(event.GetItem()));
}

bool SwThMLBookPanel::OnOpen(const char * path)
{
    if (!path)
        return false;

    viewBook->ResetAll();
    viewBook->SetTitle("");
    findPanel->Reset();
    searchPanel->Reset();
    TocTreeCtrl->Open(path);
    TocTreeCtrl->SelectFirst();

    return true;
}

bool SwThMLBookPanel::OnContentsUp()
{
    TocTreeCtrl->SelectPrevious();
    return true;
}

bool SwThMLBookPanel::OnContentsDown()
{
    TocTreeCtrl->SelectNext();
    return true;
}

bool SwThMLBookPanel::OnHistoryBack()
{
    SwHistoryItem * item;

    if (!TocTreeCtrl->GetHistory().CanMoveBack())
        return false;

    swUI32 historyPos = TocTreeCtrl->GetHistory().GetPosition();

    item = TocTreeCtrl->GetHistory().GetAt(historyPos - 1);

    TocTreeCtrl->SelectItem(item->id);
    viewBook->OnSetScrollPos(item->scrolldata);
    TocTreeCtrl->GetHistory().SetPosition(historyPos - 1);

    return true;
}

bool SwThMLBookPanel::OnHistoryForward()
{
    SwHistoryItem * item;

    if (!TocTreeCtrl->GetHistory().CanMoveForward())
        return false;

    swUI32 historyPos = TocTreeCtrl->GetHistory().GetPosition();

    item = TocTreeCtrl->GetHistory().GetAt(historyPos + 1);

    TocTreeCtrl->SelectItem(item->id);
    viewBook->OnSetScrollPos(item->scrolldata);
    TocTreeCtrl->GetHistory().SetPosition(historyPos + 1);

    return true;
}

bool SwThMLBookPanel::OnPrint()
{
    viewBook->OnPrint();

    return true;
}

bool SwThMLBookPanel::OnPrintPreview()
{
    viewBook->OnPrintPreview();

    return true;
}

bool SwThMLBookPanel::OnCopy()
{
    viewBook->OnCopy();

    return true;
}

bool SwThMLBookPanel::GetBookMarkData(SwString & title, SwBookMarkClientData & data)
{
    SwString buffer;
    wxTreeItemId id = TocTreeCtrl->GetSelection();
    data.m_type = "ThML";

    if (!id.IsOk() || TocTreeCtrl->IsRoot(id))
    {
        if (TocTreeCtrl->GetIds().GetCount())
        {
            data.m_bookId = GetBookId();
            data.m_pageId = "65535";
            data.m_scrollHPos = 0;
            data.m_scrollVPos = 0;
            data.m_selBegin = -1;
            data.m_selEnd = -1;
            return true;
        }

        return false;

    }

    SwTreeDataEx * td = (SwTreeDataEx *) TocTreeCtrl->GetItemData(id);

    if (!td)
        return false;

    swUI16 pos = SwApplicationInterface::GetThMLFileManager().FindByMID(td->m_managerId);
    if (pos == NODE_ID_INVALID_16)
        return false;

    SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetAt(pos);

    if (!f)
        return false;

    data.m_bookId = f->m_path;
    data.m_pageId = f->GetTableofContents().GetIdText(td->m_pageId);
    buffer = f->GetTitle();

    if (buffer.Strlen())
    {
        title = buffer;
        title += " - ";
        title += viewBook->GetTitle();
    }

    SwTextRange sel;
    viewBook->OnGetSelection(sel);
    data.m_selBegin = sel.begin;
    data.m_selEnd = sel.end;

    SwScrollData scr;
    viewBook->OnGetScrollPos(scr);
    data.m_scrollHPos = scr.hpos;
    data.m_scrollVPos = scr.vpos;

    return true;
}

bool SwThMLBookPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    swUI16 node = SwApplicationInterface::GetThMLFileManager().FindByPath(data.m_bookId);

    if (node == NODE_ID_INVALID_16)
        return false;

    swUI16 managerId = SwApplicationInterface::GetThMLFileManager().GetAt(node)->m_managerId;
    wxTreeItemId item = TocTreeCtrl->SearchId(data.m_pageId, managerId);

    if (!item.IsOk())
        return false;

    TocTreeCtrl->SelectItem(item);

    SwTextRange sel;
    sel.begin = data.m_selBegin;
    sel.end = data.m_selEnd;

    viewBook->OnSetSelection(sel);

    SwScrollData scr;
    scr.hpos = data.m_scrollHPos;
    scr.vpos = data.m_scrollVPos;

    viewBook->OnSetScrollPos(scr);

    return true;
}

bool SwThMLBookPanel::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    ToolNotebook->SetSelection(1);
    swUI8 sel;
    switch (searchType)
    {
    case 1:
        sel = 0;
        break;
    case 2:
        sel = 1;
        break;
    case 4:
        sel = 2;
        break;
    case 8:
        sel = 3;
    default:
        sel = 0;
    }
    searchPanel->SearchTextCtrl->SetValue(text);
    searchPanel->SearchOptionsChoice->SetSelection(sel);
    searchPanel->SearchWordCheckBox->SetValue(wordonly);
    searchPanel->SearchCaseCheckBox->SetValue(casesensitive);
    wxCommandEvent event;
    searchPanel->OnSearchButtonClick(event);

    return true;
}

bool SwThMLBookPanel:: HasFile(const char * path)
{
    return TocTreeCtrl->HasFile(path);
}

void SwThMLBookPanel::SetPopUpMenu(SwViewMenu * menu)
{
    viewBook->OnSetPopUpMenu(menu);
}

void SwThMLBookPanel::OnLanguageChange()
{
    ToolNotebook->SetPageText(0, SwApplicationInterface::GetControlString("SID_CONTENTS", L"Contents"));
    ToolNotebook->SetPageText(1, SwApplicationInterface::GetControlString("SID_SEARCH", L"Search"));
    ToolNotebook->SetPageText(2, SwApplicationInterface::GetControlString("SID_FIND", L"Find"));
}
