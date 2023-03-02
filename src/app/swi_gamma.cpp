///////////////////////////////////////////////////////////////////
// Name:        swi_alpha.cpp
// Purpose:     Gamma interface plugin for Sower.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/swi_gamma.h"
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
    return "SWI Gamma";
}

const char * InterfacePlugIn::GetDescription()
{
    return "Gamma User interface for Sower";
}

void InterfacePlugIn::OnInitialize()
{
    if (!SwApplicationInterface::GetFrameWindow())
        return;

    m_count ++;

    char name[100];
    sprintf(name, "SWI-GUI ALPHA %u", (unsigned int) m_count);
    SwGuiPanel * panel = (SwGuiPanel *) new SWI_GammaPanel(SwApplicationInterface::GetFrameWindow());
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

const long SWI_GammaPanel::ID_NOTEBOOK = wxNewId();
const long SWI_GammaPanel::ID_BOOKMARKSLIST = wxNewId();
const long SWI_GammaPanel::ID_LIBRARYPANEL = wxNewId();

SWI_GammaPanel::SWI_GammaPanel()
{
}

SWI_GammaPanel::SWI_GammaPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
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

    m_librarybook = new SwToolBook(this, ID_NOTEBOOK, wxPoint(232,160), wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT, L"ID_NOTEBOOK");
    m_manager->AddPane(m_librarybook, wxAuiPaneInfo().Name(L"BookCtrl").CenterPane().Caption(L"").Show(showLibrary));

    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());
    BuildUI();
    m_manager->Update();

    m_bookmarksList->ReadFromTable();

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&SWI_GammaPanel::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&SWI_GammaPanel::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SWI_GammaPanel::OnDelete);

    SwString path;

    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
<<<<<<< Updated upstream
    path += "sw_gamma_uisession.gui";
=======
    path += "sw_gamma_ses.gui";
    SetFocus();
    if (!CheckStartUpFile("sw_gamma"))
    {
        node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");
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

SWI_GammaPanel::~SWI_GammaPanel()
{
}

void SWI_GammaPanel::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

bool SWI_GammaPanel::OnCanDoClose()
{
    return SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCanDoClose();
}

bool SWI_GammaPanel::OnCanDoCloseAll()
{
    return SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCanDoCloseAll();
}

bool SWI_GammaPanel::OnClose()
{
    SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnClose();
    SwApplicationInterface::GetFrameWindow()->ToolRemoved();

    return true;
}

bool SWI_GammaPanel::OnCloseAll()
{
    SwApplicationInterface::GetFrameWindow()->GetToolBook()->OnCloseAll();
    SwApplicationInterface::GetFrameWindow()->ToolRemoved();

    return true;
}

bool SWI_GammaPanel::OnBookmarksView()
{
    if (m_manager->GetPane(m_bookmarksList).IsShown())
        m_manager->GetPane(m_bookmarksList).Hide();
    else
        m_manager->GetPane(m_bookmarksList).Show();

    m_manager->Update();

    return true;
}

bool SWI_GammaPanel::OnLibraryView()
{
    if (m_manager->GetPane(m_librarybook).IsShown())
        m_manager->GetPane(m_librarybook).Hide();
    else
        m_manager->GetPane(m_librarybook).Show();

    m_manager->Update();

    return true;
}

bool SWI_GammaPanel::OnBookMarkPage()
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

bool SWI_GammaPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
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

void SWI_GammaPanel::OnBookmarkActivated(wxListEvent& event)
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

bool SWI_GammaPanel::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (!LoadLibraryItem(managerId))
        return false;

    return m_librarybook->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
}

bool SWI_GammaPanel::LoadLibraryItem(swUI16 managerId)
{
    swUI16 objpos = SwApplicationInterface::GetModuleManager().FindByMID(managerId);

    if (objpos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = SwApplicationInterface::GetModuleManager().GetAt(objpos);

    if (!module)
        return false;

    swUI32 id = FindModule(m_librarybook, module->m_header.moduleIdentifier);

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        return true;
    }

    SwStringW buffer;
    buffer.Copy(module->m_header.GetTitle());
    SwMultiModuleBookPanel * panel = new SwMultiModuleBookPanel(m_librarybook);
    panel->SetPopUpMenu(m_viewMenu);
    m_librarybook->AddPage(panel, buffer.GetArray(), true);
    m_librarybook->SetFocus();

    return panel->TocTreeCtrl->BuildTree(module->GetTableofContents(), panel->TocTreeCtrl->GetRootItem(), module->GetHeader().category, module->GetManagerId());
}

void SWI_GammaPanel::SaveUserData()
{
    int sel;
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

    if (m_manager->GetPane(m_librarybook).IsShown())
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

        sel = m_librarybook->GetSelection();
        for (size_t i = 0; i < m_librarybook->GetPageCount(); i ++)
        {
            m_librarybook->SetSelection(i);
            m_librarybook->GetBookMarkData(title, data);

            SwGuiMlParser::CreateBookTag(data, LIBRARYBOOK_STR, tag);
            buffer += tag;
            buffer += '\n';
        }
        sel = m_librarybook->SetSelection(sel);

        buffer += "<perspective id=\"";
        buffer += LIBRARYBOOK_STR;
        buffer += "\">";
        buffer += m_librarybook->SavePerspective();
        buffer += "</perspective>\n";
    }

    buffer += "</swguiml>";

    title = SwApplicationInterface::GetUserDir();
    title += PATH_SEP;
    title += "sw_gamma_uisession.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void SWI_GammaPanel::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    for(swUI32 i = 0; i < m_librarybook->GetPageCount(); i ++)
    {
        SwMultiModuleBookPanel * p = (SwMultiModuleBookPanel *) m_librarybook->GetPage(i);
        if (p->GetCategoryGroup() == NODE_ID_INVALID_8)
            continue;
        m_librarybook->SetPageText(i, SwCategory::GetTranslatedString(p->GetCategoryGroup()));
    }

    m_manager->GetPane(m_bookmarksList).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    m_manager->Update();
}

void SWI_GammaPanel::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();
}

void SWI_GammaPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    if (m_viewMenu)
        m_viewMenu->UpdateGui();
}

void SWI_GammaPanel::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

bool SWI_GammaPanel::LoadPerspective(const char * id, const char * perspective)
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

void SWI_GammaPanel::BuildUI()
{
    Swui8Array groups, grouplist;
    swUI16 files;
    SwCategory::GetGroups(groups);

    for (swUI8 group = 0; group < groups.GetCount(); group ++)
    {
        files = 0;
        grouplist.Reset();
        SwCategory::GetGroupList(groups.GetAt(group), grouplist);

        for (swUI32 i = 0; i < grouplist.GetCount(); i ++)
        {
            files += SwApplicationInterface::GetModuleManager().GetItemsInCategory(grouplist.GetAt(i));
        }

        if (files)
        {
            SwMultiModuleBookPanel * panel = new SwMultiModuleBookPanel(m_librarybook);
            panel->TocTreeCtrl->LoadBooksForGroup(groups.GetAt(group));
            panel->SetCategoryGroup(groups.GetAt(group));
            panel->SetPopUpMenu(m_viewMenu);
            m_librarybook->AddPage(panel, SwCategory::GetTranslatedString(groups.GetAt(group)));
        }
    }
}

swUI32 SWI_GammaPanel::FindModule(SwToolBook * book, const char * identifier)
{
    if (!book || !identifier)
        return NODE_ID_INVALID;

    for(swUI32 i = 0; i < book->GetPageCount(); i ++)
    {
        SwMultiModuleBookPanel * p = (SwMultiModuleBookPanel *) book->GetPage(i);
        if (p->TocTreeCtrl->HasModule(identifier))
            return i;
    }

    return NODE_ID_INVALID;
}
