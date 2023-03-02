///////////////////////////////////////////////////////////////////
// Name:        swi_alpha.cpp
// Purpose:     Alpha interface plugin for Sower.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/swi_alpha.h"
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
    return "SWI Alpha";
}

const char * InterfacePlugIn::GetDescription()
{
    return "Alpha User interface for Sower";
}

void InterfacePlugIn::OnInitialize()
{
    if (!SwApplicationInterface::GetFrameWindow())
        return;

    m_count ++;

    char name[100];
    sprintf(name, "SWI-GUI ALPHA %u", (unsigned int) m_count);
    SwGuiPanel * panel = (SwGuiPanel *) new SWI_AlphaPanel(SwApplicationInterface::GetFrameWindow());
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->AddPane(panel, wxAuiPaneInfo().MinSize(-1, 300).Name(name).CloseButton(false).Show(true).CenterPane().Floatable(false));
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->Update();
    SwApplicationInterface::GetFrameWindow()->SetGuiPanel(panel);
    SwApplicationInterface::GetPreferences().GetTable().UpdateNode("Interface-PlugIn", GetName());
}

static InterfacePlugIn s_InterfacePlugIn;
SwPlugIn * PlugInInitialize()
{
    return &s_InterfacePlugIn;
}

const long SWI_AlphaPanel::ID_NOTEBOOK = wxNewId();
const long SWI_AlphaPanel::ID_BOOKMARKSLIST = wxNewId();
const long SWI_AlphaPanel::ID_LIBRARYPANEL = wxNewId();

SWI_AlphaPanel::SWI_AlphaPanel()
{
}

SWI_AlphaPanel::SWI_AlphaPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
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

    m_libraryPanel = new SwModuleLibraryPanel(this, ID_LIBRARYPANEL, wxPoint(232,160), wxDefaultSize, 0, L"ID_LIBRARYPANEL");
    m_libraryPanel->SetFrame(SwApplicationInterface::GetFrameWindow());
    m_manager->AddPane(m_libraryPanel, wxAuiPaneInfo().MinSize(-1, 300).Name(L"LibraryPanel").CloseButton(true).Show(showLibrary).Left().Caption(SwApplicationInterface::GetControlString("SID_LIBRARY", L"Library")));

    m_librarybook = new SwToolBook(this, ID_NOTEBOOK, wxPoint(232,160), wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT|wxAUI_NB_CLOSE_ON_ACTIVE_TAB, L"ID_NOTEBOOK");
    m_manager->AddPane(m_librarybook, wxAuiPaneInfo().Name(L"BookCtrl").CenterPane().Caption(L""));
    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());

    m_manager->Update();

    m_bookmarksList->ReadFromTable();

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&SWI_AlphaPanel::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&SWI_AlphaPanel::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SWI_AlphaPanel::OnDelete);

    m_libraryPanel->GetLibraryListCtrl()->LoadLibraryList();

    SwString path;

    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
<<<<<<< Updated upstream
    path += "sw_alpha_uisession.gui";
=======
    path += "sw_alpha_ses.gui";

    if (!CheckStartUpFile("sw_alpha"))
    {
        SetFocus();

        node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");

        if (node != NODE_ID_INVALID && SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
        {
            SwGuiMlParser parser;
>>>>>>> Stashed changes

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

SWI_AlphaPanel::~SWI_AlphaPanel()
{
}

void SWI_AlphaPanel::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

bool SWI_AlphaPanel::OnCanDoCloseAll()
{
    return (bool) m_librarybook->GetPageCount() || SwApplicationInterface::GetFrameWindow()->GetToolBook()->GetPageCount();
}

bool SWI_AlphaPanel::OnClose()
{
    return m_librarybook->OnClose();
}

bool SWI_AlphaPanel::OnCloseAll()
{
    m_librarybook->OnCloseAll();
    SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCloseAll();
    SwApplicationInterface::GetFrameWindow()->ToolRemoved();

    return true;
}

bool SWI_AlphaPanel::OnBookmarksView()
{
    if (m_manager->GetPane(m_bookmarksList).IsShown())
        m_manager->GetPane(m_bookmarksList).Hide();
    else
        m_manager->GetPane(m_bookmarksList).Show();

    m_manager->Update();

    return true;
}

bool SWI_AlphaPanel::OnLibraryView()
{
    if (m_manager->GetPane(m_libraryPanel).IsShown())
        m_manager->GetPane(m_libraryPanel).Hide();
    else
        m_manager->GetPane(m_libraryPanel).Show();

    m_manager->Update();

    return true;
}

bool SWI_AlphaPanel::OnBookMarkPage()
{
    SwBookMarkClientData * data = new SwBookMarkClientData();
    SwString title;
    SwStringW translation;

    if (!m_librarybook->GetBookMarkData(title, *data))
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

bool SWI_AlphaPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (strcmp(ctrlid, LIBRARYBOOK_STR) == 0)
    {
        swUI16 objpos= SwApplicationInterface::GetModuleManager().FindById(data.m_bookId);

        if (objpos == NODE_ID_INVALID_16)
            return false;

        swUI16 managerId = SwApplicationInterface::GetModuleManager().GetAt(objpos)->GetManagerId();

        if (!LoadLibraryItem(managerId))
            return false;

        return m_librarybook->ActivateBookMark(data, ctrlid);
    }

    return false;
}

void SWI_AlphaPanel::OnBookmarkActivated(wxListEvent& event)
{
    SwBookMarkClientData * data = (SwBookMarkClientData *) event.GetItem().GetData();

    swUI16 objpos= SwApplicationInterface::GetModuleManager().FindById(data->m_bookId);

    if (objpos == NODE_ID_INVALID_16)
        return;

    swUI16 managerId = SwApplicationInterface::GetModuleManager().GetAt(objpos)->GetManagerId();

    if (!LoadLibraryItem(managerId))
        return;

    m_librarybook->ActivateBookMark(*data, "");
}

bool SWI_AlphaPanel::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (!LoadLibraryItem(managerId))
        return false;

    return m_librarybook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
}

bool SWI_AlphaPanel::LoadLibraryItem(swUI16 managerId)
{
    swUI16 objpos = SwApplicationInterface::GetModuleManager().FindByMID(managerId);

    if (objpos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = SwApplicationInterface::GetModuleManager().GetAt(objpos);

    if (!module)
        return false;

    swUI32 id = m_librarybook->FindModule(module->m_header.moduleIdentifier);

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetSelection(id);
        return true;
    }

    SwStringW buffer;
    buffer.Copy(module->m_header.GetTitle());
    SwModuleBookPanel * panel = new SwModuleBookPanel(m_librarybook);
    panel->SetPopUpMenu(m_viewMenu);
    m_librarybook->AddPage(panel, buffer.GetArray(), true);

    return panel->TocTreeCtrl->BuildTree(module->GetTableofContents(), panel->TocTreeCtrl->GetRootItem(), module->GetHeader().category, module->GetManagerId());
}

void SWI_AlphaPanel::SaveUserData()
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

    if (m_manager->GetPane(m_libraryPanel).IsShown())
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("LibraryPanel-Show", "true", "", "");
    else
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("LibraryPanel-Show", "false", "", "");

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

        int sel = m_librarybook->GetSelection();
        for (size_t i = 0; i < m_librarybook->GetPageCount(); i ++)
        {
            m_librarybook->SetSelection(i);
            m_librarybook->GetBookMarkData(title, data);

            SwGuiMlParser::CreateBookTag(data, LIBRARYBOOK_STR, tag);
            buffer += tag;
            buffer += '\n';
        }
        m_librarybook->SetSelection(sel);

        buffer += "<perspective id=\"";
        buffer += LIBRARYBOOK_STR;
        buffer += "\">";
        buffer += m_librarybook->SavePerspective();
        buffer += "</perspective>\n";
    }

    buffer += "</swguiml>";

    title = SwApplicationInterface::GetUserDir();
    title += PATH_SEP;
    title += "sw_alpha_uisession.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void SWI_AlphaPanel::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    m_manager->GetPane(m_bookmarksList).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    m_manager->Update();
}

void SWI_AlphaPanel::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();
}

void SWI_AlphaPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    if (m_viewMenu)
        m_viewMenu->UpdateGui();
}

void SWI_AlphaPanel::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

bool SWI_AlphaPanel::LoadPerspective(const char * id, const char * perspective)
{
    if (!id || !perspective)
        return false;

    if (strcmp(id, GUIPANEL_STR) == 0)
    {
        bool status = m_manager->LoadPerspective(perspective);
        return status;
    }
    else if (strcmp(id, LIBRARYBOOK_STR) == 0)
    {
        bool status = m_librarybook->LoadPerspective(perspective);
        return status;
    }

    return false;
}
