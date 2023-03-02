///////////////////////////////////////////////////////////////////
// Name:        markupeditorapp.cpp
// Purpose:     Sower Markup Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/markupeditorapp.h"
#include "framework/markuppanel.h"
#include "appi/appifa.h"

IMPLEMENT_APP(SwMarkupEditorApp);

bool SwMarkupEditorApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

    SwApplicationInterface::SetAppName("Sower Markup Editor");
    SwApplicationInterface::InitBasic();
    SwApplicationInterface::LoadReferenceModules();

    SwMarkupEditorFrame* Frame = new SwMarkupEditorFrame(NULL, wxNewId(), L"");
    Frame->Maximize();
    SetTopWindow(Frame);

    for (int i = 1; i < argc; i ++)
    {
        Frame->GetCmdArray().Add(argv[i]);
    }

    Frame->ProcessCmdLine();

    return true;
}

const long SwMarkupEditorFrame::ID_TOOLBAR = wxNewId();

SwMarkupEditorFrame::SwMarkupEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxBusyCursor cursor;

    SetTitle(SwApplicationInterface::GetControlString("SID_SWMARKUPEDITOR", L"Sower Markup Editor"));
    SetIcon(SwApplicationInterface::GetToolsIcon());

    m_menubar = new SwMenuBar(this);
    m_menubar->AddStockItem(SW_GUIID_NEW, false, true);
    m_menubar->AddStockItem(SW_GUIID_OPEN, true, true);
    m_menubar->AddStockItem(SW_GUIID_FILE1, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE2, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE3, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE4, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE5, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE6, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE7, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE8, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE9, false, true);
    m_menubar->AddStockItem(SW_GUIID_FILE10, false, true);
    m_menubar->AddStockItem(SW_GUIID_SAVE, false, true);
    m_menubar->AddStockItem(SW_GUIID_SAVEAS, false, true);
    m_menubar->AddStockItem(SW_GUIID_CLOSE, false, true);
    m_menubar->AddStockItem(SW_GUIID_CLOSEALL, false, true);
    m_menubar->AddStockItem(SW_GUIID_QUIT, true, true);
    m_menubar->AddStockItem(SW_GUIID_UNDO, false, false);
    m_menubar->AddStockItem(SW_GUIID_REDO, false, true);
    m_menubar->AddStockItem(SW_GUIID_ZOOMIN, false, false);
    m_menubar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_menubar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_menubar->AddStockItem(SW_GUIID_ABOUT, true, true);
    m_menubar->AddStockItem(SW_GUIID_HELPCONTENTS, true, true);

    SetMenuBar(m_menubar);

    m_toolbar = new SwToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, SW_TOOLBAR_DEFAULT_STYLE, true, this);
    m_toolbar->AddStockItem(SW_GUIID_NEW, false, true);
    m_toolbar->AddStockItem(SW_GUIID_OPEN, true, true);
    m_toolbar->AddStockItem(SW_GUIID_SAVE, false, true);
    m_toolbar->AddStockItem(SW_GUIID_CLOSE, false, true);
    m_toolbar->AddStockItem(SW_GUIID_UNDO, false, true);
    m_toolbar->AddStockItem(SW_GUIID_REDO, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ZOOMIN, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_toolbar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ABOUT, true, true);
    m_toolbar->AddSpacer(10000);
    m_toolbar->Realize();

    SwApplicationInterface::SetFrameWindow(this);
    SetSowerMenuBar(m_menubar);
    SetSowerToolBar(m_toolbar);
    m_manager->AddPane(m_toolbar, wxAuiPaneInfo().Name(L"m_toolbar").ToolbarPane().Caption(L"").CloseButton(false).Layer(10).Top().DockFixed().Floatable(false).Movable(false).Gripper(false));
    m_manager->GetPane(m_toolbook).Top().Center();
    m_manager->Update();

    SwApplicationInterface::GetRecentFilesList(m_fileList);
    SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(m_fileList);

    Connect(id,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SwMarkupEditorFrame::OnQuit);
    Maximize();
    Show();
}

SwMarkupEditorFrame::~SwMarkupEditorFrame()
{
    SwApplicationInterface::CloseFiles();
}

void SwMarkupEditorFrame::OnFile1(wxCommandEvent & event)
{
    OpenRecent(0);
}

void SwMarkupEditorFrame::OnFile2(wxCommandEvent & event)
{
    OpenRecent(1);
}

void SwMarkupEditorFrame::OnFile3(wxCommandEvent & event)
{
    OpenRecent(2);
}

void SwMarkupEditorFrame::OnFile4(wxCommandEvent & event)
{
    OpenRecent(3);
}

void SwMarkupEditorFrame::OnFile5(wxCommandEvent & event)
{
    OpenRecent(4);
}

void SwMarkupEditorFrame::OnFile6(wxCommandEvent & event)
{
    OpenRecent(5);
}

void SwMarkupEditorFrame::OnFile7(wxCommandEvent & event)
{
    OpenRecent(6);
}

void SwMarkupEditorFrame::OnFile8(wxCommandEvent & event)
{
    OpenRecent(7);
}

void SwMarkupEditorFrame::OnFile9(wxCommandEvent & event)
{
    OpenRecent(8);
}

void SwMarkupEditorFrame::OnFile10(wxCommandEvent & event)
{
    OpenRecent(9);
}

void SwMarkupEditorFrame::OpenRecent(swUI8 pos)
{
    OpenFile(m_fileList.GetAt(pos), false);
}

void SwMarkupEditorFrame::OnNew(wxCommandEvent & event)
{
    SwMarkUpPanel * panel = new SwMarkUpPanel(m_toolbook);

    m_toolbook->SetFocus();
    m_toolbook->AddPage(panel, SwApplicationInterface::GetControlString("SID_UNTITLED", L"Untitled"), true);
    ToolAdded();
}

void SwMarkupEditorFrame::OnOpen(wxCommandEvent & event)
{
    SwString filePath;

    if (SwDialog::SelectHtmlThMLFile(this, filePath, ""))
    {
        OpenFile(filePath, true);
    }
}

bool SwMarkupEditorFrame::OpenFile(const char * path, bool addtorecent)
{
    SwString buffer, title;

    if (!path || !SwFile::DoesExist(path))
    {
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return false;
    }

        swUI32 id = m_toolbook->FindFile(path);

        if (id != NODE_ID_INVALID)
        {
            m_toolbook->SetSelection(id);
            return true;
        }
        else if (id == NODE_ID_INVALID)
        {
            SwMarkUpPanel * panel = new SwMarkUpPanel(m_toolbook);
            if (!panel->OpenFile(path))
            {
                delete panel;
                wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
                return false;
            }

            SwStringW title(path);
            m_toolbook->SetFocus();
            m_toolbook->AddPage(panel, title.GetArray(), true);
            ToolAdded();
        }

        if (addtorecent && m_fileList.Find(path) == NODE_ID_INVALID)
        {
            m_fileList.Insert(10, path);

            if (m_fileList.GetCount() > 10)
                m_fileList.Delete(0);

            m_menubar->UpdateRecentFileList(m_fileList);
        }

    return true;
}

void SwMarkupEditorFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SWMARKUPEDITOR", L"Sower Markup Editor"), SVSTR, L"2023");
}

void SwMarkupEditorFrame::OnQuit(wxCommandEvent& event)
{
    if (!m_toolbook->OnCloseAll())
    {
        return;
    }

    wxBusyCursor cursor;

    SwApplicationInterface::WriteRecentFileslistToTable(m_fileList);
    SwApplicationInterface::SaveUserData();

    Destroy();
}

void SwMarkupEditorFrame::OnLanguageChange()
{
    SetTitle(SwApplicationInterface::GetControlString("SID_SWMARKUPEDITOR", L"Sower Markup Editor"));
}

void SwMarkupEditorFrame::OnThemeChange()
{
}

void SwMarkupEditorFrame::ProcessCmdLine()
{
    for (swUI32 i = 0; i < m_cmd.GetCount(); i ++)
    {
        OpenFile(m_cmd.GetAt(i), true);
    }
}

void SwMarkupEditorFrame::AddToRecentFileList(const char * path)
{
    if (!path)
        return;

    m_fileList.Insert(10, path);

    if (m_fileList.GetCount() > 10)
        m_fileList.Delete(0);

    m_menubar->UpdateRecentFileList(m_fileList);
}
