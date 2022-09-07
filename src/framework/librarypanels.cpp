///////////////////////////////////////////////////////////////////
// Name:        librarypanels.cpp
// Purpose:     Library panels.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/librarypanels.h"
#include "../../include/appi/appifa.h"
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>

const long SwThMLLibraryPanel::ID_LIBRARYLISTCTRL = wxNewId();
const long SwThMLLibraryPanel::ID_SEARCHPANEL = wxNewId();
const long SwThMLLibraryPanel::ID_TOOLNOTEBOOK = wxNewId();

SwThMLLibraryPanel::SwThMLLibraryPanel()
{
    m_frame = NULL;
}

SwThMLLibraryPanel::SwThMLLibraryPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
:SwPanel(parent, id, pos, size, style, name)
{
    m_frame = NULL;
	BuildContent(parent,id,pos,size);
}

void SwThMLLibraryPanel::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    ToolNotebook = new wxNotebook(this, ID_TOOLNOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, L"ID_TOOLNOTEBOOK");
    ToolNotebook->SetMinSize(wxSize(300,-1));
    ToolNotebook->SetBackgroundColour(*wxWHITE);
    LibraryListCtrl = new SwThMLLibraryListCtrl(ToolNotebook, ID_LIBRARYLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, L"ID_LIBRARYLISTCTRL");
    LibraryListCtrl->SetMinSize(wxSize(300,-1));
    ToolNotebook->AddPage(LibraryListCtrl, L"Contents", false);
    searchPanel = new SwThMLLibrarySearchPanel(ToolNotebook, ID_SEARCHPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHPANEL");
    ToolNotebook->AddPage(searchPanel, L"Search", false);
    m_manager->AddPane(ToolNotebook, wxAuiPaneInfo().Name(L"ToolBook").DefaultPane().CaptionVisible(false).CloseButton(false).Center().Floatable(false).MinSize(wxSize(200,-1)));
    m_manager->Update();

    searchPanel->SetListCtrl(LibraryListCtrl);

    OnLanguageChange();
    Connect(ID_LIBRARYLISTCTRL, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&SwThMLLibraryPanel::OnLibraryItemActivated);
}

SwThMLLibraryPanel::~SwThMLLibraryPanel()
{
    m_manager->UnInit();
}

void SwThMLLibraryPanel::OnContentsUp(wxCommandEvent & event)
{
    event.Skip();
}

void SwThMLLibraryPanel::OnContentsDown(wxCommandEvent & event)
{
    event.Skip();
}

void SwThMLLibraryPanel::OnLanguageChange()
{
    ToolNotebook->SetPageText(0, SwApplicationInterface::GetControlString("SID_CONTENTS", L"Contents"));
    ToolNotebook->SetPageText(1, SwApplicationInterface::GetControlString("SID_SEARCH", L"Search"));
}

void SwThMLLibraryPanel::OnLibraryItemActivated(wxListEvent& event)
{
    if (!m_frame)
        return;

    m_frame->LoadLibraryItem(event.GetData());
}

const long SwModuleLibraryPanel::ID_LIBRARYLISTCTRL = wxNewId();
const long SwModuleLibraryPanel::ID_SEARCHPANEL = wxNewId();
const long SwModuleLibraryPanel::ID_TOOLNOTEBOOK = wxNewId();

SwModuleLibraryPanel::SwModuleLibraryPanel()
{
    m_frame = NULL;
}

SwModuleLibraryPanel::SwModuleLibraryPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
:SwPanel(parent, id, pos, size, style, name)
{
    m_frame = NULL;
	BuildContent(parent,id,pos,size);
}

void SwModuleLibraryPanel::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    ToolNotebook = new wxNotebook(this, ID_TOOLNOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, L"ID_TOOLNOTEBOOK");
    ToolNotebook->SetMinSize(wxSize(300,-1));
    ToolNotebook->SetBackgroundColour(*wxWHITE);
    LibraryListCtrl = new SwModuleLibraryListCtrl(ToolNotebook, ID_LIBRARYLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT, wxDefaultValidator, L"ID_LIBRARYLISTCTRL");
    LibraryListCtrl->SetMinSize(wxSize(300,-1));
    ToolNotebook->AddPage(LibraryListCtrl, L"Contents", false);
    searchPanel = new SwModuleLibrarySearchPanel(ToolNotebook, ID_SEARCHPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHPANEL");
    ToolNotebook->AddPage(searchPanel, L"Search", false);
    m_manager->AddPane(ToolNotebook, wxAuiPaneInfo().Name(L"ToolBook").DefaultPane().CaptionVisible(false).CloseButton(false).Center().Floatable(false).MinSize(wxSize(200,-1)));
    m_manager->Update();

    searchPanel->SetListCtrl(LibraryListCtrl);

    OnLanguageChange();
    Connect(ID_LIBRARYLISTCTRL, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&SwModuleLibraryPanel::OnLibraryItemActivated);
}

SwModuleLibraryPanel::~SwModuleLibraryPanel()
{
    m_manager->UnInit();
}

void SwModuleLibraryPanel::OnContentsUp(wxCommandEvent & event)
{
    event.Skip();
}

void SwModuleLibraryPanel::OnContentsDown(wxCommandEvent & event)
{
    event.Skip();
}

void SwModuleLibraryPanel::OnLanguageChange()
{
    ToolNotebook->SetPageText(0, SwApplicationInterface::GetControlString("SID_CONTENTS", L"Contents"));
    ToolNotebook->SetPageText(1, SwApplicationInterface::GetControlString("SID_SEARCH", L"Search"));
}

void SwModuleLibraryPanel::OnLibraryItemActivated(wxListEvent& event)
{
    if (!m_frame)
        return;

    m_frame->LoadLibraryItem(event.GetData());
}
