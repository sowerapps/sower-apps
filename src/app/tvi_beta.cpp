///////////////////////////////////////////////////////////////////
// Name:        tvi_beta.cpp
// Purpose:     Beta interface plugin for ThML Viewer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/tvi_beta.h"
#include "appi/appifa.h"
#include "framework/bookpanels.h"
#include "thml/thml_utility.h"
#include "thml/thml_file.h"
#include "dialogs/preferencesdlg.h"
#include "swguiml/swguimlparser.h"
#include "filesys/file.h"

const long TVI_BetaPanel::ID_BOOKMARKSLIST = wxNewId();
const long TVI_BetaPanel::ID_BOOKPANEL = wxNewId();

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
    return "TVI Beta";
}

const char * InterfacePlugIn::GetDescription()
{
    return "Beta User interface for Thml Viewer";
}

void InterfacePlugIn::OnInitialize()
{
    if (!SwApplicationInterface::GetFrameWindow())
        return;

    m_count ++;

    char name[100];
    sprintf(name, "SWI-GUI BETA %u", (unsigned int) m_count);
    SwGuiPanel * panel = (SwGuiPanel *) new TVI_BetaPanel(SwApplicationInterface::GetFrameWindow());
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

TVI_BetaPanel::TVI_BetaPanel()
{
}

TVI_BetaPanel::TVI_BetaPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
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

    m_bookpanel = new SwMultiFileThMLBookPanel(this, ID_BOOKPANEL, wxPoint(232,160), wxDefaultSize, wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT, L"ID_NOTEBOOK");
    m_manager->AddPane(m_bookpanel, wxAuiPaneInfo().MinSize(-1, 300).Name(L"BookPanel").CloseButton(false).Show(true).CenterPane().Caption(SwApplicationInterface::GetControlString("SID_LIBRARY", L"Library")));
    SetPanel(m_bookpanel);

    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());
    m_bookpanel->SetPopUpMenu(m_viewMenu);

    m_manager->Update();

    SwApplicationInterface::GetRecentFilesList(SwApplicationInterface::GetFrameWindow()->m_fileList);
    m_bookmarksList->ReadFromTable();
    SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(SwApplicationInterface::GetFrameWindow()->m_fileList);

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&TVI_BetaPanel::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&TVI_BetaPanel::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&TVI_BetaPanel::OnDelete);

    SwApplicationInterface::GetThMLFileList(m_bookpanel->TocTreeCtrl);

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += "tv_beta_uisession.gui";

<<<<<<< Updated upstream
    node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");
=======
    if (!CheckStartUpFile("tvi_beta"))
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
>>>>>>> Stashed changes

    if (node == NODE_ID_INVALID || SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
    {
        SwGuiMlParser parser;

        parser.SetGuiPanel(this);
        parser.OpenFile(path);
        parser.Run();
    }

    m_silent = false;
}

TVI_BetaPanel::~TVI_BetaPanel()
{
    m_bookpanel->TocTreeCtrl->CollapseAll();
}

void TVI_BetaPanel::OnThMLFileManagerReset()
{
    m_bookpanel->TocTreeCtrl->CollapseAll();
    m_bookpanel->TocTreeCtrl->Reset();
    m_bookpanel->viewBook->OnReset();
    SwApplicationInterface::GetThMLFileList(m_bookpanel->TocTreeCtrl);
}

void TVI_BetaPanel::OnThMLFileManagerLoaded()
{
    SwApplicationInterface::GetThMLFileList(m_bookpanel->TocTreeCtrl);
}

bool TVI_BetaPanel::OpenFile(const char * path, bool addtorecent)
{
    if (!path || !SwFile::DoesExist(path))
    {
        if (!m_silent)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return false;
    }

    SwBookMarkClientData data(path, "", "ThML");

    swUI16 id = SwApplicationInterface::GetThMLFileManager().FindByPath(path);

    if (id != NODE_ID_INVALID_16)
        return ActivateBookMark(data, LIBRARYBOOK_STR);

    if (!m_bookpanel->TocTreeCtrl->Open(path))
    {
        if (!m_silent)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return false;
    }

    if (addtorecent && SwApplicationInterface::GetFrameWindow()->m_fileList.Find(path) == NODE_ID_INVALID)
    {
        SwApplicationInterface::GetFrameWindow()->m_fileList.Insert(10, path);

        if (SwApplicationInterface::GetFrameWindow()->m_fileList.GetCount() > 10)
            SwApplicationInterface::GetFrameWindow()->m_fileList.Delete(0);

        if (SwApplicationInterface::GetMenuBar())
            SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(SwApplicationInterface::GetFrameWindow()->m_fileList);
    }

    return m_bookpanel->ActivateBookMark(data, LIBRARYBOOK_STR);
}

bool TVI_BetaPanel::OnOpen()
{
    SwString filePath;

    if (SwDialog::SelectThMLFile(this, filePath, ""))
    {
        return OpenFile(filePath, true);
    }

    return false;
}

bool TVI_BetaPanel::OnFile1()
{
    OpenRecent(0);

    return true;
}

bool TVI_BetaPanel::OnFile2()
{
    OpenRecent(1);

    return true;
}

bool TVI_BetaPanel::OnFile3()
{
    OpenRecent(2);

    return true;
}

bool TVI_BetaPanel::OnFile4()
{
    OpenRecent(3);

    return true;
}

bool TVI_BetaPanel::OnFile5()
{
    OpenRecent(4);

    return true;
}

bool TVI_BetaPanel::OnFile6()
{
    OpenRecent(5);

    return true;
}

bool TVI_BetaPanel::OnFile7()
{
    OpenRecent(6);

    return true;
}

bool TVI_BetaPanel::OnFile8()
{
    OpenRecent(7);

    return true;
}

bool TVI_BetaPanel::OnFile9()
{
    OpenRecent(8);

    return true;
}

bool TVI_BetaPanel::OnFile10()
{
    OpenRecent(9);

    return true;
}

void TVI_BetaPanel::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

void TVI_BetaPanel::OpenRecent(swUI8 pos)
{
    OpenFile(SwApplicationInterface::GetFrameWindow()->m_fileList.GetAt(pos), false);
}

bool TVI_BetaPanel::OnBookmarksView()
{
    if (m_manager->GetPane(m_bookmarksList).IsShown())
        m_manager->GetPane(m_bookmarksList).Hide();
    else
        m_manager->GetPane(m_bookmarksList).Show();

    m_manager->Update();

    return true;
}

bool TVI_BetaPanel::OnLibraryView()
{
    if (m_manager->GetPane(m_bookpanel).IsShown())
        m_manager->GetPane(m_bookpanel).Hide();
    else
        m_manager->GetPane(m_bookpanel).Show();

    m_manager->Update();

    return true;
}

bool TVI_BetaPanel::OnBookMarkPage()
{
    SwBookMarkClientData * data = new SwBookMarkClientData();
    SwString title;
    SwStringW translation;

    if (!m_bookpanel->GetBookMarkData(title, *data))
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

bool TVI_BetaPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    swUI16 objpos = SwApplicationInterface::GetThMLFileManager().FindByPath(data.m_bookId);

    if (objpos == NODE_ID_INVALID_16)
        return false;

    return m_bookpanel->ActivateBookMark(data, ctrlid);
}

void TVI_BetaPanel::OnBookmarkActivated(wxListEvent& event)
{
    SwBookMarkClientData * data = (SwBookMarkClientData *) event.GetItem().GetData();

    swUI16 objpos= SwApplicationInterface::GetThMLFileManager().FindByPath(data->m_bookId);

    if (objpos == NODE_ID_INVALID_16 && !m_bookpanel->TocTreeCtrl->Open(data->m_bookId))
        return;

    m_bookpanel->ActivateBookMark(*data, LIBRARYBOOK_STR);
}

bool TVI_BetaPanel::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    return m_bookpanel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
}

void TVI_BetaPanel::SaveUserData()
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
    title += "tv_beta_uisession.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void TVI_BetaPanel::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    m_manager->GetPane(m_bookmarksList).Caption(SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    m_manager->Update();
}

void TVI_BetaPanel::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();
}

void TVI_BetaPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    if (m_viewMenu)
        m_viewMenu->UpdateGui();
}

void TVI_BetaPanel::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

bool TVI_BetaPanel::LoadPerspective(const char * id, const char * perspective)
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
