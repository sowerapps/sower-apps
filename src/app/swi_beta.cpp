///////////////////////////////////////////////////////////////////
// Name:        swi_beta.cpp
// Purpose:     Beta interface plugin for Sower.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/swi_beta.h"
#include "appi/appifa.h"
#include "framework/bookpanels.h"
#include "thml/thml_utility.h"
#include "swguiml/swguimlparser.h"

swUI32 InterfacePlugIn::m_count = 0;

InterfacePlugIn::InterfacePlugIn()
{
}

InterfacePlugIn::~InterfacePlugIn()
{
}

wxUint8 InterfacePlugIn::GetVersion()
{
    return SOFTWAREVERSIONMAJOR;
}

swUI8 InterfacePlugIn::GetType()
{
    return PIT_INTERFACE;
}

const char * InterfacePlugIn::GetName()
{
    return "SWI Beta";
}

const char * InterfacePlugIn::GetDescription()
{
    return "Beta User interface for Sower";
}

void InterfacePlugIn::OnInitialize()
{
    if (!SwApplicationInterface::GetFrameWindow())
        return;

    m_count ++;

    char name[100];
    sprintf(name, "SWI-GUI BETA %u", (unsigned int) m_count);
    SwGuiPanel * panel = (SwGuiPanel *) new SWI_BetaPanel(SwApplicationInterface::GetFrameWindow());
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->AddPane(panel, wxAuiPaneInfo().MinSize(-1, 300).Name(name).CloseButton(false).Show(true).CenterPane().Floatable(false));
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->Update();
    SwApplicationInterface::GetFrameWindow()->SetGuiPanel(panel);
    SwApplicationInterface::GetPreferences().GetTable().UpdateNode("Interface-PlugIn", GetName());
}

static InterfacePlugIn InterfacePlugIn;
SwPlugIn * PlugInInitialize()
{
    return &InterfacePlugIn;
}

const long SWI_BetaPanel::ID_BOOKMARKSLIST = wxNewId();
const long SWI_BetaPanel::ID_BOOKPANEL = wxNewId();

SWI_BetaPanel::SWI_BetaPanel()
{
}

SWI_BetaPanel::SWI_BetaPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwGuiPanel(parent, id, pos, size, style, name)
{
    swUI32 node;

    bool showBookmarks = true;
    node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("BookMarksList-Show");
    if (node != NODE_ID_INVALID)
    {
        showBookmarks = SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node));
    }

    m_bookmarksList = new SwBookmarksListCtrl(this, ID_BOOKMARKSLIST, wxPoint(232,160), wxDefaultSize, wxLC_REPORT, wxValidator(), L"ID_BOOKMARKSLIST");
    m_manager->AddPane(m_bookmarksList, wxAuiPaneInfo().MinSize(100, -1).Name(L"BookmarksView").Show(showBookmarks).Top().CloseButton(true).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks")));

    bool showLibrary = true;
    node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("LibraryPanel-Show");
    if (node != NODE_ID_INVALID)
    {
        showLibrary = SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node));
    }

    m_bookpanel = new SwMultiModuleBookPanel(this, ID_BOOKPANEL, wxPoint(232,160), wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT, L"ID_NOTEBOOK");
    m_manager->AddPane(m_bookpanel, wxAuiPaneInfo().MinSize(-1, 300).Name(L"BookPanel").CloseButton(false).Show(showLibrary).CloseButton(true).CenterPane().Caption(SwApplicationInterface::GetControlString("SID_LIBRARY", L"Library")));
    SetPanel(m_bookpanel);

    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());
    m_bookpanel->SetPopUpMenu(m_viewMenu);

    m_manager->Update();

    m_bookmarksList->ReadFromTable();

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&SWI_BetaPanel::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&SWI_BetaPanel::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SWI_BetaPanel::OnDelete);

    SwApplicationInterface::GetModuleList(m_bookpanel->TocTreeCtrl);

    SwString path;

    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += "sw_beta_uisession.gui";

    SetFocus();

    node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");

    if (node == NODE_ID_INVALID || SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
    {
        SwGuiMlParser parser;

        parser.SetGuiPanel(this);
        parser.OpenFile(path);
        parser.Run();
    }
}

SWI_BetaPanel::~SWI_BetaPanel()
{
    m_bookpanel->TocTreeCtrl->CollapseAll();
}

void SWI_BetaPanel::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

bool SWI_BetaPanel::OnCanDoClose()
{
    return SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCanDoClose();
}

bool SWI_BetaPanel::OnCanDoCloseAll()
{
    return SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCanDoCloseAll();
}

bool SWI_BetaPanel::OnClose()
{
    return SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnClose();
}

bool SWI_BetaPanel::OnCloseAll()
{
    return SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCloseAll();
}

bool SWI_BetaPanel::OnBookmarksView()
{
    if (m_manager->GetPane(m_bookmarksList).IsShown())
        m_manager->GetPane(m_bookmarksList).Hide();
    else
        m_manager->GetPane(m_bookmarksList).Show();

    m_manager->Update();

    return true;
}

bool SWI_BetaPanel::OnLibraryView()
{
    if (m_manager->GetPane(m_bookpanel).IsShown())
        m_manager->GetPane(m_bookpanel).Hide();
    else
        m_manager->GetPane(m_bookpanel).Show();

    m_manager->Update();

    return true;
}

bool SWI_BetaPanel::OnBookMarkPage()
{
    SwBookMarkClientData * data = new SwBookMarkClientData();
    SwString title;
    SwStringW translation;

    if (!m_bookpanel->GetBookMarkData(title, *data))
    {
        delete data;
    }
    else
    {
        translation.Copy(title);
        wxListItem lItem;
        int item;
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(m_bookmarksList->GetItemCount());
        lItem.SetText("");
        lItem.SetData(data);
        item = m_bookmarksList->wxListCtrl::InsertItem(lItem);
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT);
        lItem.SetColumn(1);
        lItem.SetId(item);
        lItem.SetText(translation.GetArray());
        m_bookmarksList->SetItem(lItem);
    }

    return true;
}

bool SWI_BetaPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (strcmp(ctrlid, LIBRARYBOOK_STR) == 0)
    {
        swUI16 objpos= SwApplicationInterface::GetModuleManager().FindById(data.m_bookId);

        if (objpos == NODE_ID_INVALID_16)
            return false;

        return m_bookpanel->ActivateBookMark(data, ctrlid);
    }

    m_manager->GetPane(m_bookpanel).Show();
    m_manager->Update();

    return false;
}

void SWI_BetaPanel::OnBookmarkActivated(wxListEvent& event)
{
    SwBookMarkClientData * data = (SwBookMarkClientData *) event.GetItem().GetData();

    swUI16 objpos = SwApplicationInterface::GetModuleManager().FindById(data->m_bookId);

    if (objpos == NODE_ID_INVALID_16)
        return;

    m_bookpanel->ActivateBookMark(*data, LIBRARYBOOK_STR);
    m_manager->GetPane(m_bookpanel).Show();
    m_manager->Update();
}

bool SWI_BetaPanel::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    return m_bookpanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
}

void SWI_BetaPanel::SaveUserData()
{
    swUI32 node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");
    bool save = true;

    if (node != NODE_ID_INVALID && !SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
    {
        save = false;
    }

    if (m_manager->GetPane(m_bookmarksList).IsShown())
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("BookMarksList-Show", "true", "", "");
    else
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("BookMarksList-Show", "false", "", "");

    SwApplicationInterface::WriteBookMarklistToTable(m_bookmarksList);
    SwApplicationInterface::SaveUserData();

    SwString title, buffer, tag, perspective;
    SwBookMarkClientData data;
    buffer = "<swguiml>\n";

    if (save)
    {
        buffer += "<perspective id=\"";
        buffer += GUIPANEL_STR;
        buffer += "\">";
        buffer += m_manager->SavePerspective();
        buffer += "</perspective>\n";

        if (m_bookpanel->GetBookMarkData(title, data))
        {
            SwGuiMlParser::CreateBookTag(data, LIBRARYBOOK_STR, tag);
            buffer += tag;
            buffer += '\n';
        }
    }

    buffer += "</swguiml>";

    title = SwApplicationInterface::GetUserDir();
    title += PATH_SEP;
    title += "sw_beta_uisession.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void SWI_BetaPanel::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    m_manager->GetPane(m_bookmarksList).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    m_manager->Update();
}

void SWI_BetaPanel::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();
}

void SWI_BetaPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    if (m_viewMenu)
        m_viewMenu->UpdateGui();
}

void SWI_BetaPanel::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

bool SWI_BetaPanel::LoadPerspective(const char * id, const char * perspective)
{
    if (!id || !perspective)
        return false;

    if (strcmp(id, GUIPANEL_STR) == 0)
    {
        bool status = m_manager->LoadPerspective(perspective);
        return status;
    }

    return false;
}
