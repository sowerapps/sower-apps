///////////////////////////////////////////////////////////////////
// Name:        sowermapeditorapp.cpp
// Purpose:     Sower Map Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowermapeditorapp.h"
#include "dialogs/preferencesdlg.h"
#include "dialogs/interfacedlg.h"
#include "framework/bookpanels.h"
#include "appi/appifa.h"
#include "thml/thml_utility.h"
#include "geo/geolocation.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerMapEditorApp);

bool SowerMapEditorApp::OnInit()
{
<<<<<<< Updated upstream
    bool wxsOK = true;
=======
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif // defined __OSX__

>>>>>>> Stashed changes
    SwApplicationInterface::SetAppName("Sower Map Editor");
    SwApplicationInterface::InitBasic();

    SowerMapEditorFrame* Frame = new SowerMapEditorFrame(NULL, wxNewId(), L"");
    Frame->Maximize();
    SetTopWindow(Frame);

    for (int i = 1; i < argc; i ++)
    {
        Frame->GetCmdArray().Add(argv[i]);
    }

    Frame->ProcessCmdLine();

    return true;
}

const long SowerMapEditorFrame::ID_TOOLBAR = wxNewId();

SowerMapEditorFrame::SowerMapEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxBusyCursor cursor;

    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERMAPEDITOR", L"Sower Map Editor"));
    SetIcon(SwApplicationInterface::GetSowerIcon());

    SwStringArray array;
    SwApplicationInterface::GetPlugInManager().GetExtensions(array);

    m_menubar = new SwMenuBar(this);
    m_menubar->AddStockItem(SW_GUIID_OPEN, array.GetCount(), true);
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
    m_menubar->AddStockItem(SW_GUIID_CLOSE, false, true);
    m_menubar->AddStockItem(SW_GUIID_PRINT, false, true);
    m_menubar->AddStockItem(SW_GUIID_QUIT, true, true);
    m_menubar->AddStockItem(SW_GUIID_UNDO, false, false);
    m_menubar->AddStockItem(SW_GUIID_REDO, false, true);
    m_menubar->AddStockItem(SW_GUIID_GEO, false, true);
    m_menubar->AddStockItem(SW_GUIID_MAPS, false, true);
    m_menubar->AddStockItem(SW_GUIID_AREAS, false, true);
    m_menubar->AddStockItem(SW_GUIID_ZOOMIN, false, false);
    m_menubar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_menubar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_menubar->AddStockItem(SW_GUIID_ABOUT, true, true);
    m_menubar->AddStockItem(SW_GUIID_HELPCONTENTS, true, true);

    SetMenuBar(m_menubar);

    m_toolbar = new SwToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, SW_TOOLBAR_DEFAULT_STYLE, true, this);
    m_toolbar->AddStockItem(SW_GUIID_OPEN, array.GetCount(), true);
    m_toolbar->AddStockItem(SW_GUIID_SAVE, false, true);
    m_toolbar->AddStockItem(SW_GUIID_CLOSE, false, true);
    m_toolbar->AddStockItem(SW_GUIID_PRINT, false, true);
    m_toolbar->AddStockItem(SW_GUIID_UNDO, false, true);
    m_toolbar->AddStockItem(SW_GUIID_REDO, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ZOOMIN, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_toolbar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ABOUT, true, true);
    m_toolbar->AddSpacer(10000);
    m_toolbar->Realize();

    m_manager->AddPane(m_toolbar, wxAuiPaneInfo().Name(L"m_toolbar").ToolbarPane().Caption(L"").CloseButton(false).Layer(10).Top().DockFixed().Floatable(false).Movable(false).Gripper(false));
    m_manager->Update();
    SwApplicationInterface::SetFrameWindow(this);
    SetSowerMenuBar(m_menubar);
    SetSowerToolBar(m_toolbar);
    CreateStatusBar();
    m_imageWindow = new SwImageWindow(this, wxNewId(), wxDefaultPosition, wxDefaultSize, 0, "SwImageWindow");
    m_imageWindow->SetIsEditMode(true);
    m_imageWindow->SetShowTips(true);
    m_imageWindow->SetAllowDrag(true);
    m_imageWindow->EnableAutoDef(false);
    m_imageWindow->SetDoubleBuffered(true);
    m_manager->AddPane(m_imageWindow, wxAuiPaneInfo().MinSize(-1, 300).Name("SwImageWindow").CloseButton(false).Show(true).CenterPane());
    m_manager->Update();

    SwApplicationInterface::GetRecentFilesList(m_fileList);
    SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(m_fileList);

    Connect(id,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SowerMapEditorFrame::OnQuit);
    Maximize();
    Show();
}

SowerMapEditorFrame::~SowerMapEditorFrame()
{
    SwApplicationInterface::CloseFiles();
}

void SowerMapEditorFrame::OnFile1(wxCommandEvent & event)
{
    OpenRecent(0);
}

void SowerMapEditorFrame::OnFile2(wxCommandEvent & event)
{
    OpenRecent(1);
}

void SowerMapEditorFrame::OnFile3(wxCommandEvent & event)
{
    OpenRecent(2);
}

void SowerMapEditorFrame::OnFile4(wxCommandEvent & event)
{
    OpenRecent(3);
}

void SowerMapEditorFrame::OnFile5(wxCommandEvent & event)
{
    OpenRecent(4);
}

void SowerMapEditorFrame::OnFile6(wxCommandEvent & event)
{
    OpenRecent(5);
}

void SowerMapEditorFrame::OnFile7(wxCommandEvent & event)
{
    OpenRecent(6);
}

void SowerMapEditorFrame::OnFile8(wxCommandEvent & event)
{
    OpenRecent(7);
}

void SowerMapEditorFrame::OnFile9(wxCommandEvent & event)
{
    OpenRecent(8);
}

void SowerMapEditorFrame::OnFile10(wxCommandEvent & event)
{
    OpenRecent(9);
}

void SowerMapEditorFrame::OpenRecent(swUI8 pos)
{
    OpenFile(m_fileList.GetAt(pos), false);
}

bool SowerMapEditorFrame::OpenFile(const char * path, bool addtorecent)
{
    bool status = false;

    if (!path)
        return false;

    status = m_imageWindow->LoadImage(path);
    /*
        if (status)
            m_geoPanel->SetImageWindow(m_imageWindow);
        else
            m_geoPanel->SetImageWindow(NULL);
    */
    if (status)
    {
        m_filePath = path;
        m_mapPath = path;
        m_mapPath += ".sbo";

        FILE * f = SwFopen(m_mapPath, FMD_R);
        if (f)
        {
            m_imageWindow->GetImageMapList().ReadFromFile(f);
            fclose(f);
        }

        m_imageWindow->Refresh();
    }

    if (!status)
    {
        m_filePath.Reset();
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
    }

    if (status && addtorecent && m_fileList.Find(path) == NODE_ID_INVALID)
    {
        m_fileList.Insert(10, path);

        if (m_fileList.GetCount() > 10)
            m_fileList.Delete(0);

        if (SwApplicationInterface::GetMenuBar())
            SwApplicationInterface::GetMenuBar()->UpdateRecentFileList(m_fileList);
    }

    return true;
}

void SowerMapEditorFrame::OnOpen(wxCommandEvent& event)
{
    SwString imagepath;

    if (SwDialog::SelectImageFile(this, imagepath, ""))
    {
        OpenFile(imagepath, true);
    }
}

void SowerMapEditorFrame::OnSave(wxCommandEvent & event)
{
    FILE * f = SwFopen(m_mapPath, FMD_WC);

    if (!f)
    {
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOSAVEFILE", L"Unable to save file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        return;
    }

    m_imageWindow->GetImageMapList().WriteToFile(f);
    fclose(f);
}

void SowerMapEditorFrame::OnClose(wxCommandEvent & event)
{
    if (m_imageWindow->GetCommandProcessor().CanUndo())
    {
        int i = SwDialog::RequestSave(this);

        if (i == wxCANCEL)
            return;

        if (i == wxYES)
        {
            wxCommandEvent ev;
            OnSave(ev);
        }
    }

    m_imageWindow->Reset();
}

void SowerMapEditorFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERMAPEDITOR", L"Sower Map Editor"), SVSTR, L"2021");
}

void SowerMapEditorFrame::OnQuit(wxCommandEvent& event)
{
    wxBusyCursor cursor;

    SwApplicationInterface::WriteRecentFileslistToTable(m_fileList);
    SwApplicationInterface::SaveUserData();

    Destroy();
}

void SowerMapEditorFrame::OnLanguageChange()
{
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERMAPEDITOR", L"Sower Map Editor"));
}

void SowerMapEditorFrame::OnThemeChange()
{
}

void SowerMapEditorFrame::OnTimer()
{
    SwFrame::OnTimer();
}

void SowerMapEditorFrame::ProcessCmdLine()
{
    for (swUI32 i = 0; i < m_cmd.GetCount(); i ++)
    {
        OpenFile(m_cmd.GetAt(i), true);
    }
}
