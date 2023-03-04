///////////////////////////////////////////////////////////////////
// Name:        tvi_gamma.cpp
// Purpose:     Gamma interface plugin for ThML Viewer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/tvi_gamma.h"
#include "appi/appifa.h"
#include "framework/bookpanels.h"
#include "thml/thml_utility.h"
#include "dialogs/preferencesdlg.h"
#include "swguiml/swguimlparser.h"
#include "module/category.h"
#include "filesys/file.h"

const long TVI_GammaPanel::ID_NOTEBOOK = wxNewId();
const long TVI_GammaPanel::ID_BOOKMARKSLIST = wxNewId();
const long TVI_GammaPanel::ID_LIBRARYPANEL = wxNewId();

swUI32 InterfacePlugIn::m_count = 0;

InterfacePlugIn::InterfacePlugIn()
{
}

InterfacePlugIn::~InterfacePlugIn()
{
}

swUI8 InterfacePlugIn::GetVersion()
{
    return 1;
}

swUI8 InterfacePlugIn::GetType()
{
    return PIT_INTERFACE;
}

const char * InterfacePlugIn::GetName()
{
    return "TVI Gamma";
}

const char * InterfacePlugIn::GetDescription()
{
    return "Gamma User interface for ThML Viewer";
}

void InterfacePlugIn::OnInitialize()
{
    if (!SwApplicationInterface::GetFrameWindow())
        return;

    m_count ++;

    char name[100];
    sprintf(name, "TVI-GUI %u", (unsigned int) m_count);
    SwGuiPanel * panel = (SwGuiPanel *) new TVI_GammaPanel(SwApplicationInterface::GetFrameWindow());
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->AddPane(panel, wxAuiPaneInfo().MinSize(-1, 300).Name(name).CloseButton(false).Show(true).CenterPane());
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->Update();
    SwApplicationInterface::GetFrameWindow()->SetGuiPanel(panel);
    SwApplicationInterface::GetPreferences().GetTable().UpdateNode("Interface-PlugIn", GetName());
}

static InterfacePlugIn s_InterfacePlugIn;
SwPlugIn * PlugInInitialize()
{
    return &s_InterfacePlugIn;
}


TVI_GammaPanel::TVI_GammaPanel()
{
}

TVI_GammaPanel::TVI_GammaPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwGuiPanel(parent, id, pos, wxSize(0, 0), style, name)
{
    swUI32 node;
    m_startup = true;
    bool showBookmarks = true;
    node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("BookMarksList-Show");
    if (node != NODE_ID_INVALID)
    {
        showBookmarks = SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node));
    }

    m_bookmarksList = new SwBookmarksListCtrl(this, ID_BOOKMARKSLIST, wxPoint(232,160), wxDefaultSize, wxLC_REPORT, wxValidator(), L"ID_BOOKMARKSLIST");
    m_manager->AddPane(m_bookmarksList, wxAuiPaneInfo().MinSize(100, -1).Name(L"BookmarksView").Show(showBookmarks).Top().CloseButton(true).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks")));

    m_librarybook = new SwToolBook(this, ID_NOTEBOOK, wxPoint(232,160), wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT, L"ID_NOTEBOOK");
    m_manager->AddPane(m_librarybook, wxAuiPaneInfo().Name(L"BookCtrl").CenterPane().Caption(L""));
    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());
    BuildUI();
    m_manager->Update();

    SwApplicationInterface::GetRecentFilesList(SwApplicationInterface::GetFrameWindow()->m_fileList);
    m_bookmarksList->ReadFromTable();
    SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(SwApplicationInterface::GetFrameWindow()->m_fileList);

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&TVI_GammaPanel::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&TVI_GammaPanel::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TVI_GammaPanel::OnDelete);

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += "tv_gamma_ses.gui";

    if (!CheckStartUpFile("tvi_gamma"))
    {
        SetFocus();

        node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");

        if (node != NODE_ID_INVALID && SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
        {
            SwGuiMlParser parser;

            parser.SetGuiPanel(this);
            parser.OpenFile(path);
            parser.Run();
            parser.CloseFile();
        }

        for (size_t i = 0; i < m_librarybook->GetPageCount(); i ++)
        {
            SwThMLBookPanel * panel = (SwThMLBookPanel *) m_librarybook->GetPage(i);
            if (panel && !panel->TocTreeCtrl->GetIds().GetCount())
                m_librarybook->DeletePage(i);
        }

        CreateStartUpFile("tvi_gamma");
    }
    else
    {
        unlink(path);
    }

    for(swUI32 i = 0; i < m_panelList.GetCount(); i ++)
    {
        SwThMLBookPanel * panel = (SwThMLBookPanel *) m_panelList.GetPanel(i);
        m_librarybook->AddPage(panel, SwCategory::GetTranslatedString(panel->GetCategoryGroup()), true);
    }

    m_startup = false;
}

TVI_GammaPanel::~TVI_GammaPanel()
{
    DeleteStartUpFile("tvi_gamma");
}

bool TVI_GammaPanel::OpenFile(const char * path, bool addtorecent)
{
    SwStringW buffer;
    bool status = false;

    if (!path || !SwFile::DoesExist(path))
    {
        if (!m_startup)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return false;
    }

    swUI32 id = FindFile(m_librarybook, path);

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        return true;
    }


    if (id == NODE_ID_INVALID && SwThMLUtility::IsFileThML(path) == 1)
    {
        status = LoadLibraryItem(path);

        id = FindFile(m_librarybook, path);

        if (id != NODE_ID_INVALID)
        {
            m_librarybook->SetFocus();
            m_librarybook->SetSelection(id);
            SwBookMarkClientData data;
            data.m_bookId = path;
            data.m_pageId = SwApplicationInterface::GetThMLFileManager().GetFirstPageId(path);
            data.m_type = "ThML";
            m_librarybook->ActivateBookMark(data, "");
        }
    }

    if (!status && id == NODE_ID_INVALID)
    {
        if (!m_startup)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return false;
    }

    if (status && addtorecent && SwApplicationInterface::GetFrameWindow()->m_fileList.Find(path) == NODE_ID_INVALID)
    {
        SwApplicationInterface::GetFrameWindow()->m_fileList.Insert(10, path);

        if (SwApplicationInterface::GetFrameWindow()->m_fileList.GetCount() > 10)
            SwApplicationInterface::GetFrameWindow()->m_fileList.Delete(0);

        if (SwApplicationInterface::GetMenuBar())
            SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(SwApplicationInterface::GetFrameWindow()->m_fileList);
    }

    return true;
}

bool TVI_GammaPanel::OnOpen()
{
    SwString filePath;

    if (SwDialog::SelectThMLFile(this, filePath, ""))
    {
        return OpenFile(filePath, true);
    }

    return false;
}

bool TVI_GammaPanel::OnFile1()
{
    OpenRecent(0);

    return true;
}

bool TVI_GammaPanel::OnFile2()
{
    OpenRecent(1);

    return true;
}

bool TVI_GammaPanel::OnFile3()
{
    OpenRecent(2);

    return true;
}

bool TVI_GammaPanel::OnFile4()
{
    OpenRecent(3);

    return true;
}

bool TVI_GammaPanel::OnFile5()
{
    OpenRecent(4);

    return true;
}

bool TVI_GammaPanel::OnFile6()
{
    OpenRecent(5);

    return true;
}

bool TVI_GammaPanel::OnFile7()
{
    OpenRecent(6);

    return true;
}

bool TVI_GammaPanel::OnFile8()
{
    OpenRecent(7);

    return true;
}

bool TVI_GammaPanel::OnFile9()
{
    OpenRecent(8);

    return true;
}

bool TVI_GammaPanel::OnFile10()
{
    OpenRecent(9);

    return true;
}

void TVI_GammaPanel::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

void TVI_GammaPanel::OpenRecent(swUI8 pos)
{
    OpenFile(SwApplicationInterface::GetFrameWindow()->m_fileList.GetAt(pos), false);
}

bool TVI_GammaPanel::OnBookmarksView()
{
    if (m_manager->GetPane(m_bookmarksList).IsShown())
        m_manager->GetPane(m_bookmarksList).Hide();
    else
        m_manager->GetPane(m_bookmarksList).Show();

    m_manager->Update();

    return true;
}

bool TVI_GammaPanel::OnBookMarkPage()
{
    SwBookMarkClientData * data = new SwBookMarkClientData();
    SwString title;
    SwString translation;

    if (!m_librarybook->GetBookMarkData(title, *data) && !SwApplicationInterface::GetFrameWindow()->GetToolBook()->GetBookMarkData(title, *data))
    {
        delete data;
        return false;
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

bool TVI_GammaPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    swUI32 id = FindFile(m_librarybook, data.m_bookId);

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        m_librarybook->ActivateBookMark(data, ctrlid);
        return true;
    }

    if (id == NODE_ID_INVALID && !LoadLibraryItem(data.m_bookId))
        return false;

    id = FindFile(m_librarybook, data.m_bookId);

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        m_librarybook->ActivateBookMark(data, ctrlid);
        return true;
    }

    return false;
}

void TVI_GammaPanel::OnBookmarkActivated(wxListEvent& event)
{
    SwBookMarkClientData * data = (SwBookMarkClientData *) event.GetItem().GetData();

    swUI32 id = FindFile(m_librarybook, data->m_bookId);

    if (id == NODE_ID_INVALID && !LoadLibraryItem(data->m_bookId))
        return;

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        m_librarybook->ActivateBookMark(*data, "");
    }
}

bool TVI_GammaPanel::LoadLibraryItem(const char * path)
{
    if (!path)
        return false;

    swUI16 id = SwApplicationInterface::GetThMLFileManager().FindByPath(path);

    if (id == NODE_ID_INVALID_16)
    {
        SwThMLFile * thmlfile = new SwThMLFile();
        if (!thmlfile->Open(path))
        {
            delete thmlfile;
            return false;
        }

        id = SwApplicationInterface::GetThMLFileManager().Add(thmlfile);
        if (id == NODE_ID_INVALID_16)
        {
            delete thmlfile;
            return false;
        }
    }

    return LoadLibraryItem(SwApplicationInterface::GetThMLFileManager().GetAt(id)->GetManagerId());
}

bool TVI_GammaPanel::LoadLibraryItem(swUI16 managerId)
{
    swUI16 objpos = SwApplicationInterface::GetThMLFileManager().FindByMID(managerId);

    if (objpos == NODE_ID_INVALID_16)
        return false;

    SwThMLFile * file = SwApplicationInterface::GetThMLFileManager().GetAt(objpos);

    if (!file)
        return false;

    swUI32 id = FindFile(m_librarybook, file->GetPath());

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        return true;
    }

    SwThMLBookPanel * panel = FindPanelForCategory(m_librarybook, file->GetCategory());

    if (panel)
    {
        panel->TocTreeCtrl->BuildTree(file->GetTableofContents(), panel->TocTreeCtrl->GetRootItem(), file->GetCategory(), file->GetManagerId());
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(m_librarybook->GetPageIndex(panel));

        return true;
    }
    else
    {
        swUI8 group = SwCategory::GetCategoryGroup(file->GetCategory());
        panel = new SwThMLBookPanel(m_librarybook);
        panel->TocTreeCtrl->LoadBooksForGroup(group);
        panel->SetCategoryGroup(group);
        panel->SetPopUpMenu(m_viewMenu);
        m_librarybook->AddPage(panel, SwCategory::GetTranslatedString(group), true);
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(m_librarybook->GetPageIndex(panel));
        return true;
    }

    return false;
}

bool TVI_GammaPanel::SelectTab(const char * path)
{
    swUI32 id = FindFile(m_librarybook, path);
    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
        return true;
    }

    id = FindFile(SwApplicationInterface::GetFrameWindow()->GetToolBook(), path);
    if (id != NODE_ID_INVALID)
    {
        SwApplicationInterface::GetFrameWindow()->GetToolBook()->SetFocus();
        SwApplicationInterface::GetFrameWindow()->GetToolBook()->SetSelection(id);
        return true;
    }

    return false;
}

void TVI_GammaPanel::SaveUserData()
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

    SwApplicationInterface::WriteRecentFileslistToTable(SwApplicationInterface::GetFrameWindow()->m_fileList);
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
            if (!m_librarybook->GetBookMarkData(title, data))
                continue;

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
    title += "tv_gamma_ses.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void TVI_GammaPanel::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    for(swUI32 i = 0; i < m_librarybook->GetPageCount(); i ++)
    {
        SwThMLBookPanel * p = (SwThMLBookPanel *) m_librarybook->GetPage(i);
        if (p->GetCategoryGroup() == NODE_ID_INVALID_8)
            continue;
        m_librarybook->SetPageText(i, SwCategory::GetTranslatedString(p->GetCategoryGroup()));
    }

    m_manager->GetPane(m_bookmarksList).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    m_manager->Update();
}

void TVI_GammaPanel::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();
}

void TVI_GammaPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    if (m_viewMenu)
        m_viewMenu->UpdateGui();
}

void TVI_GammaPanel::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

bool TVI_GammaPanel::LoadPerspective(const char * id, const char * perspective)
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

void TVI_GammaPanel::BuildUI()
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
            files += SwApplicationInterface::GetThMLFileManager().GetItemsInCategory(grouplist.GetAt(i));
        }

        if (files)
        {
            SwThMLBookPanel * panel = new SwThMLBookPanel(m_librarybook);
            panel->TocTreeCtrl->LoadBooksForGroup(groups.GetAt(group));
            panel->SetCategoryGroup(groups.GetAt(group));
            panel->SetPopUpMenu(m_viewMenu);
            m_panelList.AddPanel(panel);
        }
    }
}

swUI32 TVI_GammaPanel::FindFile(SwToolBook * book, const char * path)
{
    if (!book || !path)
        return NODE_ID_INVALID;

    for(swUI32 i = 0; i < book->GetPageCount(); i ++)
    {
        SwThMLBookPanel * p = (SwThMLBookPanel *) book->GetPage(i);
        if (p->TocTreeCtrl->HasFile(path))
            return i;
    }

    return NODE_ID_INVALID;
}

SwThMLBookPanel * TVI_GammaPanel::FindPanelForCategory(SwToolBook * book, swUI8 category)
{
    if (!book)
        return NULL;

    return FindPanelForGroup(book, SwCategory::GetCategoryGroup(category));
}

SwThMLBookPanel * TVI_GammaPanel::FindPanelForGroup(SwToolBook * book, swUI8 group)
{
    if (!book)
        return NULL;

    if (!m_startup)
    {
        for(swUI32 i = 0; i < book->GetPageCount(); i ++)
        {
            SwThMLBookPanel * panel = (SwThMLBookPanel *) book->GetPage(i);
            if (panel->GetCategoryGroup() == group)
                return panel;
        }
    }
    else
    {
        for(swUI32 i = 0; i < m_panelList.GetCount(); i ++)
        {
            SwThMLBookPanel * panel = (SwThMLBookPanel *) m_panelList.GetPanel(i);
            if (panel->GetCategoryGroup() == group)
            {
                m_librarybook->AddPage(panel, SwCategory::GetTranslatedString(group), true);
                m_panelList.DeletePanel(i);
                return panel;
            }
        }
    }

    return NULL;
}
