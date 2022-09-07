///////////////////////////////////////////////////////////////////
// Name:        tvi_alpha.cpp
// Purpose:     Alpha interface plugin for ThML Viewer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/tvi_alpha.h"
#include "appi/appifa.h"
#include "framework/bookpanels.h"
#include "thml/thml_utility.h"
#include "dialogs/preferencesdlg.h"
#include "swguiml/swguimlparser.h"
#include "filesys/file.h"

const long TVI_AlphaPanel::ID_NOTEBOOK = wxNewId();
const long TVI_AlphaPanel::ID_BOOKMARKSLIST = wxNewId();
const long TVI_AlphaPanel::ID_LIBRARYPANEL = wxNewId();

swUI32 InterfacePlugIn::m_count = 0;

InterfacePlugIn::InterfacePlugIn()
{
}

InterfacePlugIn::~InterfacePlugIn()
{
}

wxUint8 InterfacePlugIn::GetVersion()
{
    return 1;
}

swUI8 InterfacePlugIn::GetType()
{
    return PIT_INTERFACE;
}

const char * InterfacePlugIn::GetName()
{
    return "TVI Alpha";
}

const char * InterfacePlugIn::GetDescription()
{
    return "Alpha User interface for ThML Viewer";
}

void InterfacePlugIn::OnInitialize()
{
    if (!SwApplicationInterface::GetFrameWindow())
        return;

    m_count ++;

    char name[100];
    sprintf(name, "TVI-GUI %u", (unsigned int) m_count);
    SwGuiPanel * panel = (SwGuiPanel *) new TVI_AlphaPanel(SwApplicationInterface::GetFrameWindow());
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->AddPane(panel, wxAuiPaneInfo().MinSize(-1, 300).Name(name).CloseButton(false).Show(true).CenterPane());
    SwApplicationInterface::GetFrameWindow()->GetAuiManager()->Update();
    SwApplicationInterface::GetFrameWindow()->SetGuiPanel(panel);
    SwApplicationInterface::GetPreferences().GetTable().UpdateNode("Interface-PlugIn", GetName());
}

static InterfacePlugIn InterfacePlugIn;
SwPlugIn * PlugInInitialize()
{
    return &InterfacePlugIn;
}


TVI_AlphaPanel::TVI_AlphaPanel()
{
}

TVI_AlphaPanel::TVI_AlphaPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwGuiPanel(parent, id, pos, wxSize(0, 0), style, name)
{
    swUI32 node;
    m_silent = true;
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

    m_libraryPanel = new SwThMLLibraryPanel(this, ID_LIBRARYPANEL, wxPoint(232,160), wxDefaultSize, 0, L"ID_LIBRARYPANEL");
    m_libraryPanel->SetFrame(SwApplicationInterface::GetFrameWindow());
    m_manager->AddPane(m_libraryPanel, wxAuiPaneInfo().MinSize(-1, 300).Name(L"LibraryPanel").CloseButton(true).Show(showLibrary).Left().Caption(SwApplicationInterface::GetControlString("SID_LIBRARY", L"Library")));

    m_librarybook = new SwToolBook(this, ID_NOTEBOOK, wxPoint(232,160), wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT|wxAUI_NB_CLOSE_ON_ACTIVE_TAB, L"ID_NOTEBOOK");
    m_manager->AddPane(m_librarybook, wxAuiPaneInfo().Name(L"BookCtrl").CenterPane().Caption(L""));

    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());

    m_manager->Update();

    SwApplicationInterface::GetRecentFilesList(SwApplicationInterface::GetFrameWindow()->m_fileList);
    m_bookmarksList->ReadFromTable();
    SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(SwApplicationInterface::GetFrameWindow()->m_fileList);

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&TVI_AlphaPanel::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&TVI_AlphaPanel::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TVI_AlphaPanel::OnDelete);

    m_libraryPanel->GetLibraryListCtrl()->LoadLibraryList();

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += "tv_alpha_uisession.gui";

    SetFocus();

    node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");

    if (node == NODE_ID_INVALID || SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
    {
        SwGuiMlParser parser;

        parser.SetGuiPanel(this);
        parser.OpenFile(path);
        parser.Run();
    }
    m_silent = false;
}

TVI_AlphaPanel::~TVI_AlphaPanel()
{
}

bool TVI_AlphaPanel::OpenFile(const char * path, bool addtorecent)
{
    SwStringW buffer;
    bool status = false;

    if (!path || !SwFile::DoesExist(path))
    {
        if (!m_silent)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return false;
    }

    swUI32 id = m_librarybook->FindFile(path);

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetFocus();
        m_librarybook->SetSelection(id);
    }
    else if (id == NODE_ID_INVALID)
    {
        id = SwApplicationInterface::GetFrameWindow()->GetToolBook()->FindFile(path);

        if (id != NODE_ID_INVALID)
        {
            SwApplicationInterface::GetFrameWindow()->GetToolBook()->SetFocus();
            SwApplicationInterface::GetFrameWindow()->GetToolBook()->SetSelection(id);
        }
    }

    if (id == NODE_ID_INVALID)
    {
        SwThMLUtility::GetTitleW(buffer, path);
        SwThMLBookPanel * thm = new SwThMLBookPanel(m_librarybook);
        thm->SetPopUpMenu(m_viewMenu);
        status = thm->OnOpen(path);
        if (!status)
            delete thm;
        else
        {
            m_librarybook->SetFocus();
            m_librarybook->AddPage(thm, buffer.GetArray(), true);
        }
    }

    if (!status && id == NODE_ID_INVALID)
    {
        if (!m_silent)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
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

bool TVI_AlphaPanel::OnOpen()
{
    SwString filePath;

    if (SwDialog::SelectThMLFile(this, filePath, ""))
    {
        return OpenFile(filePath, true);
    }

    return false;
}

bool TVI_AlphaPanel::OnFile1()
{
    OpenRecent(0);

    return true;
}

bool TVI_AlphaPanel::OnFile2()
{
    OpenRecent(1);

    return true;
}

bool TVI_AlphaPanel::OnFile3()
{
    OpenRecent(2);

    return true;
}

bool TVI_AlphaPanel::OnFile4()
{
    OpenRecent(3);

    return true;
}

bool TVI_AlphaPanel::OnFile5()
{
    OpenRecent(4);

    return true;
}

bool TVI_AlphaPanel::OnFile6()
{
    OpenRecent(5);

    return true;
}

bool TVI_AlphaPanel::OnFile7()
{
    OpenRecent(6);

    return true;
}

bool TVI_AlphaPanel::OnFile8()
{
    OpenRecent(7);

    return true;
}

bool TVI_AlphaPanel::OnFile9()
{
    OpenRecent(8);

    return true;
}

bool TVI_AlphaPanel::OnFile10()
{
    OpenRecent(9);

    return true;
}

void TVI_AlphaPanel::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

void TVI_AlphaPanel::OpenRecent(swUI8 pos)
{
    OpenFile(SwApplicationInterface::GetFrameWindow()->m_fileList.GetAt(pos), false);
}

bool TVI_AlphaPanel::OnClose()
{
    if (!m_librarybook->GetPageCount())
        return false;

    m_librarybook->DeletePage(m_librarybook->GetSelection());

    return true;
}

bool TVI_AlphaPanel::OnCloseAll()
{
    while (m_librarybook->GetPageCount())
    {
        m_librarybook->DeletePage(0);
    }

    return true;
}

bool TVI_AlphaPanel::OnBookmarksView()
{
    if (m_manager->GetPane(m_bookmarksList).IsShown())
        m_manager->GetPane(m_bookmarksList).Hide();
    else
        m_manager->GetPane(m_bookmarksList).Show();

    m_manager->Update();

    return true;
}

bool TVI_AlphaPanel::OnLibraryView()
{
    if (m_manager->GetPane(m_libraryPanel).IsShown())
        m_manager->GetPane(m_libraryPanel).Hide();
    else
        m_manager->GetPane(m_libraryPanel).Show();

    m_manager->Update();

    return true;
}

bool TVI_AlphaPanel::OnBookMarkPage()
{
    SwBookMarkClientData * data = new SwBookMarkClientData();
    SwString title;
    SwString translation;

    if (!m_librarybook->GetBookMarkData(title, *data))
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

bool TVI_AlphaPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (!OpenFile(data.m_bookId))
        return false;

    return m_librarybook->ActivateBookMark(data, ctrlid);
}

void TVI_AlphaPanel::OnBookmarkActivated(wxListEvent& event)
{
    SwBookMarkClientData * data = (SwBookMarkClientData *) event.GetItem().GetData();

    if (!OpenFile(data->m_bookId))
        return;

    m_librarybook->ActivateBookMark(*data, "");
}

bool TVI_AlphaPanel::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    if (!path)
        return false;

    if (!OpenFile(path))
        return false;

    return m_librarybook->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
}

bool TVI_AlphaPanel::LoadLibraryItem(const char * path)
{
    if (!path)
        return false;

    swUI16 objpos = SwApplicationInterface::GetThMLFileManager().FindByPath(path);

    if (objpos == NODE_ID_INVALID_16)
    {
        if (!OpenFile(path, false))
            return false;

        objpos = SwApplicationInterface::GetThMLFileManager().FindByPath(path);
    }

    return LoadLibraryItem(SwApplicationInterface::GetThMLFileManager().GetAt(objpos)->GetManagerId());
}

bool TVI_AlphaPanel::LoadLibraryItem(swUI16 managerId)
{
    swUI16 objpos = SwApplicationInterface::GetThMLFileManager().FindByMID(managerId);

    if (objpos == NODE_ID_INVALID_16)
        return false;

    SwThMLFile * file = SwApplicationInterface::GetThMLFileManager().GetAt(objpos);

    if (!file)
        return false;

    swUI32 id = m_librarybook->FindFile(file->GetPath());

    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetSelection(id);
        return true;
    }

    SwStringW buffer;
    buffer.Copy(file->GetTitle());
    SwThMLBookPanel * panel = new SwThMLBookPanel(m_librarybook);
    panel->SetPopUpMenu(m_viewMenu);
    m_librarybook->AddPage(panel, buffer.GetArray(), true);

    return panel->TocTreeCtrl->BuildTree(file->GetTableofContents(), panel->TocTreeCtrl->GetRootItem(), file->GetCategory(), file->GetManagerId());
}

bool TVI_AlphaPanel::SelectTab(const char * path)
{
    if (!m_librarybook)
        return false;

    swUI32 id = m_librarybook->FindFile(path);
    if (id != NODE_ID_INVALID)
    {
        m_librarybook->SetSelection(id);
    }

    return false;
}

void TVI_AlphaPanel::SaveUserData()
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

    if (m_manager->GetPane(m_libraryPanel).IsShown())
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("LibraryPanel-Show", "true", "", "");
    else
        SwApplicationInterface::GetPreferences().GetTable().UpdateNode("LibraryPanel-Show", "false", "", "");

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
    title += "tv_alpha_uisession.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void TVI_AlphaPanel::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    m_manager->GetPane(m_bookmarksList).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    m_manager->Update();
}

void TVI_AlphaPanel::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();
}

void TVI_AlphaPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    if (m_viewMenu)
        m_viewMenu->UpdateGui();
}

void TVI_AlphaPanel::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

bool TVI_AlphaPanel::LoadPerspective(const char * id, const char * perspective)
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
