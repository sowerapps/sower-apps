///////////////////////////////////////////////////////////////////
// Name:        sowerapp.cpp
// Purpose:     Sower
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowerapp.h"
#include "appi/appifa.h"
#include "dialogs/preferencesdlg.h"
#include "dialogs/interfacedlg.h"
#include "framework/splashscreen.h"
#include "framework/bookpanels.h"
#include "swguiml/swguimlparser.h"
#include "filesys/file.h"
#include "av_media/audio.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerApp);

bool SowerApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_CROSS32)));
    #endif // defined __OSX__

    wxBusyCursor cursor;
    SwApplicationInterface::SetAppName("Sower");
    SwApplicationInterface::InitBasic();
    SwApplicationInterface::GetPlugInManager().SetLoadType(PIT_UNKNOWN);
    SwApplicationInterface::LoadPlugIns();
    SowerAppFrame* Frame = new SowerAppFrame(NULL, wxNewId(), L"Sower");
    SwApplicationInterface::GetPlugInManager().OnInitialize();
    SwSplashScreen * splash = new SwSplashScreen(wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, 7000, Frame);
    splash->SetText(SwApplicationInterface::GetControlString("SID_SOWER", L"Sower"), L"2020");
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadModules();
    SwApplicationInterface::LoadModuleStates();
    SwApplicationInterface::LoadUserInterface();
    Frame->Maximize();
    SetTopWindow(Frame);

    for (int i = 1; i < argc; i ++)
    {
        Frame->GetCmdArray().Add(argv[i]);
    }

    Frame->ProcessCmdLine();

    return true;
}

const long SowerAppFrame::ID_TOOLBAR = wxNewId();
const long SowerAppFrame::ID_POSITIONSLIDER = wxNewId();
const long SowerAppFrame::ID_VOLUMESLIDER = wxNewId();
const long SowerAppFrame::ID_LOOPCHECKBOX = wxNewId();

SowerAppFrame::SowerAppFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxBusyCursor cursor;
    m_startup = true;
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWER", L"Sower"));
    SetIcon(SwApplicationInterface::GetSowerIcon());

    m_basicviewMenu = new SwBasicViewMenu(this);
    m_menubar = new SwMenuBar(this);
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
    m_menubar->AddStockItem(SW_GUIID_CLOSE, false, true);
    m_menubar->AddStockItem(SW_GUIID_CLOSEALL, false, true);
    m_menubar->AddStockItem(SW_GUIID_PRINT, false, true);
    m_menubar->AddStockItem(SW_GUIID_PRINTPREVIEW, false, true);
    m_menubar->AddStockItem(SW_GUIID_QUIT, true, true);
    m_menubar->AddStockItem(SW_GUIID_BOOKMARKPAGE, true, true);
    m_menubar->AddStockItem(SW_GUIID_COPY, false, true);
    m_menubar->AddStockItem(SW_GUIID_SELECTALL, false, false);
    m_menubar->AddStockItem(SW_GUIID_BOOKMARKSVIEW, true, true);
    m_menubar->AddStockItem(SW_GUIID_LIBRARYVIEW, true, true);
    m_menubar->AddStockItem(SW_GUIID_ZOOMIN, false, true);
    m_menubar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_menubar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_menubar->AddStockItem(SW_GUIID_CONTENTSDOWN, false, true);
    m_menubar->AddStockItem(SW_GUIID_CONTENTSUP, false, true);
    m_menubar->AddStockItem(SW_GUIID_BACKINHISTORY, false, true);
    m_menubar->AddStockItem(SW_GUIID_FORWARDINHISTORY, false, true);
    m_menubar->AddStockItem(SW_GUIID_ABOUT, true, true);
    m_menubar->AddStockItem(SW_GUIID_HELPCONTENTS, true, true);
    m_menubar->AddStockItem(SW_GUIID_PREFERENCES, true, true);
    m_menubar->AddStockItem(SW_GUIID_CONFIGURATION, true, true);

    bool status = true;
    if (SwApplicationInterface::GetInterfaceCount() > 1)
        status = true;

    m_menubar->AddStockItem(SW_GUIID_SELECTINTERFACE, status, true);
    SetMenuBar(m_menubar);

    m_toolbar = new SwToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, SW_TOOLBAR_DEFAULT_STYLE, true, this);
    m_toolbar->AddStockItem(SW_GUIID_OPEN, true, true);
    m_toolbar->AddStockItem(SW_GUIID_CLOSE, false, true);
    m_toolbar->AddStockItem(SW_GUIID_PRINT, false, true);
    m_toolbar->AddStockItem(SW_GUIID_COPY, false, true);
    m_toolbar->AddStockItem(SW_GUIID_SELECTALL, false, false);
    m_toolbar->AddStockItem(SW_GUIID_ZOOMIN, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_toolbar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_toolbar->AddStockItem(SW_GUIID_CONTENTSDOWN, false, true);
    m_toolbar->AddStockItem(SW_GUIID_CONTENTSUP, false, true);
    m_toolbar->AddStockItem(SW_GUIID_BACKINHISTORY, false, true);
    m_toolbar->AddStockItem(SW_GUIID_FORWARDINHISTORY, false, true);
    m_toolbar->AddStockItem(SW_GUIID_BOOKMARKPAGE, true, true);

    m_VolumeSlider = new wxSlider(m_toolbar, ID_VOLUMESLIDER, 50, 0, 100, wxDefaultPosition, wxSize(100, -1), 0, wxDefaultValidator, L"ID_VOLUMESLIDER");
    #ifdef __MSWIN__
    m_VolumeSlider->SetThumbLength(12);
    #endif
    SwApplicationInterface::GetAudio().SetVolume(0.5);
    m_toolbar->AddControl(m_VolumeSlider);
    m_toolbar->SetToolShortHelp(ID_VOLUMESLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume")).GetArray());

    m_toolbar->AddStockItem(SW_GUIID_PLAY, false, false);
    m_toolbar->AddStockItem(SW_GUIID_PAUSE, false, false);

    m_PositionSlider = new wxSlider(m_toolbar, ID_POSITIONSLIDER, 0, 0, 100, wxDefaultPosition, wxSize(100, -1), 0, wxDefaultValidator, L"ID_POSITIONSLIDER");
    #ifdef __MSWIN__
    m_PositionSlider->SetThumbLength(12);
    #endif
    m_toolbar->AddControl(m_PositionSlider);
    m_toolbar->SetToolShortHelp(ID_POSITIONSLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position")).GetArray());

    m_LoopCheckBox = new wxCheckBox(m_toolbar, ID_LOOPCHECKBOX, "", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, wxDefaultValidator, L"ID_LOOPCHECKEBOX");
    m_toolbar->AddControl(m_LoopCheckBox);
    m_toolbar->SetToolShortHelp(ID_LOOPCHECKBOX, SwStringW(SwApplicationInterface::GetControlString("SID_LOOP", L"Loop")).GetArray());

    m_toolbar->AddStockItem(SW_GUIID_STOP, false, true);
    m_toolbar->AddStockItem(SW_GUIID_ABOUT, true, true);

    m_toolbar->AddSpacer(10000);
    m_toolbar->Realize();

    m_manager->AddPane(m_toolbar, wxAuiPaneInfo().Name(L"m_toolbar").ToolbarPane().Caption(L"").CloseButton(false).Layer(10).Top().DockFixed().Floatable(false).Movable(false).Gripper(false));
    m_manager->Update();
    SwApplicationInterface::SetFrameWindow(this);

    SwApplicationInterface::GetRecentFilesList(m_fileList);
    m_menubar->UpdateRecentFileList(m_fileList);

    SwString path;
    path = SwApplicationInterface::GetUserDir();
    path += PATH_SEP;
    path += "sw_session.gui";

    if (!CheckStartUpFile("sower"))
    {
        SetFocus();

        swUI32 node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");

        if (node != NODE_ID_INVALID && SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
        {
            SwGuiMlParser parser;

            parser.SetFrame(this);
            parser.OpenFile(path);
            parser.Run();
            parser.CloseFile();
        }

        for (size_t i = 0; i < m_toolbook->GetPageCount(); i ++)
        {
            SwThMLBookPanel * panel = (SwThMLBookPanel *) m_toolbook->GetPage(i);
            if (panel && !panel->TocTreeCtrl->GetIds().GetCount())
                m_toolbook->DeletePage(i);
        }

        if (m_toolbook->GetPageCount())
            ToolAdded();

        CreateStartUpFile("sower");
    }
    else
    {
        unlink(path);
    }

    m_skip = false;

    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&SowerAppFrame::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&SowerAppFrame::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&SowerAppFrame::OnVolumeSliderScroll);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&SowerAppFrame::OnPositionSliderThumb);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&SowerAppFrame::OnPositionSliderThumbRelease);
    Connect(id,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SowerAppFrame::OnQuit);

    m_startup = false;
}

SowerAppFrame::~SowerAppFrame()
{
    DeleteStartUpFile("sower");
    SaveUserData();
    SwApplicationInterface::CloseFiles();
}

void SowerAppFrame::OnOpen(wxCommandEvent & event)
{
    SwString filePath;

    if (SwDialog::SelectThMLFile(this, filePath, ""))
    {
        OpenFile(filePath, true);
    }
}

bool SowerAppFrame::OpenFile(const char * path, bool addtorecent)
{
    SwString buffer, title;

    if (!path || !SwFile::DoesExist(path))
    {
        if (!m_startup)
            wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
        else
        {
            SwThMLBookPanel * panel = new SwThMLBookPanel(m_toolbook);
            m_toolbook->AddPage(panel, ".", false);
        }

        return false;
    }

    if (m_startup)
    {
        SwThMLBookPanel * panel = new SwThMLBookPanel(m_toolbook);
        bool status = panel->OnOpen(path);
        SwStringW title(SwApplicationInterface::GetThMLFileManager().GetTitleFromPath(path));
        panel->SetPopUpMenu(m_basicviewMenu);
        panel->SetAllowBookMarks(false);
        m_toolbook->AddPage(panel, title.GetArray(), true);
        return status;
    }
    else
    {
        swUI32 id = m_toolbook->FindFile(path);

        if (id != NODE_ID_INVALID)
        {
            m_toolbook->SetSelection(id);
            return true;
        }
        else if (id == NODE_ID_INVALID)
        {
            SwThMLBookPanel * panel = new SwThMLBookPanel(m_toolbook);
            if (!panel->OnOpen(path))
            {
                delete panel;
                wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_UNABLETOOPENFILE", L"Unable to open file.")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray());
                return false;
            }

            SwStringW title(SwApplicationInterface::GetThMLFileManager().GetTitleFromPath(path));
            panel->SetPopUpMenu(m_basicviewMenu);
            panel->SetAllowBookMarks(false);
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
    }

    return true;
}

void SowerAppFrame::OpenRecent(swUI8 pos)
{
    OpenFile(m_fileList.GetAt(pos), false);
}

void SowerAppFrame::OnFile1(wxCommandEvent & event)
{
    OpenRecent(0);
}

void SowerAppFrame::OnFile2(wxCommandEvent & event)
{
    OpenRecent(1);
}

void SowerAppFrame::OnFile3(wxCommandEvent & event)
{
    OpenRecent(2);
}

void SowerAppFrame::OnFile4(wxCommandEvent & event)
{
    OpenRecent(3);
}

void SowerAppFrame::OnFile5(wxCommandEvent & event)
{
    OpenRecent(4);
}

void SowerAppFrame::OnFile6(wxCommandEvent & event)
{
    OpenRecent(5);
}

void SowerAppFrame::OnFile7(wxCommandEvent & event)
{
    OpenRecent(6);
}

void SowerAppFrame::OnFile8(wxCommandEvent & event)
{
    OpenRecent(7);
}

void SowerAppFrame::OnFile9(wxCommandEvent & event)
{
    OpenRecent(8);
}

void SowerAppFrame::OnFile10(wxCommandEvent & event)
{
    OpenRecent(9);
}

void SowerAppFrame::OnLibraryView(wxCommandEvent & event)
{
    if (m_guipanel)
        m_guipanel->OnLibraryView();
}

void SowerAppFrame::OnBookmarksView(wxCommandEvent & event)
{
    if (m_guipanel)
        m_guipanel->OnBookmarksView();
}

bool SowerAppFrame::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    if (strcmp(ctrlid, TOOLBOOK_STR) == 0)
    {
        if (!m_toolbook)
            return false;

        if (!OpenFile(data.m_bookId, false))
            return false;

        return m_toolbook->ActivateBookMark(data, ctrlid);
    }
    else
    {
        if (m_guipanel)
            return m_guipanel->ActivateBookMark(data, ctrlid);
    }

    return false;
}

bool SowerAppFrame::LoadPerspective(const char * id, const char * perspective)
{
    if (!id || !perspective)
        return false;

    if (strcmp(id, TOOLBOOK_STR) == 0)
        return m_toolbook->LoadPerspective(perspective);
    else if (strcmp(id, FRAME_STR) == 0)
        return m_manager->LoadPerspective(perspective);
    else if (m_guipanel)
        m_guipanel->LoadPerspective(id, perspective);

    return false;
}

void SowerAppFrame::SaveUserData()
{
    swUI32 node = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Save-Session");
    bool save = true;

    if (node != NODE_ID_INVALID && !SwString::BoolFromString(SwApplicationInterface::GetPreferences().GetTable().GetNodeData(node)))
    {
        save = false;
    }

    SwBookMarkClientData data;
    SwString title, tag, buffer;

    buffer = "<swguiml>\n";

    buffer += "<perspective id=\"";
    buffer += FRAME_STR;
    buffer += "\">";
    buffer += m_manager->SavePerspective();
    buffer += "</perspective>\n";

    if (save)
    {
        int sel = m_toolbook->GetSelection();
        for (size_t i = 0; i < m_toolbook->GetPageCount(); i ++)
        {
            m_toolbook->SetSelection(i);
            if (!m_toolbook->GetBookMarkData(title, data))
                continue;

            SwGuiMlParser::CreateBookTag(data, TOOLBOOK_STR, tag);
            buffer += tag;
            buffer += '\n';
        }
        m_toolbook->SetSelection(sel);

        buffer += "<perspective id=\"";
        buffer += TOOLBOOK_STR;
        buffer += "\">";
        buffer += m_toolbook->SavePerspective();
        buffer += "</perspective>\n";
    }

    buffer += "</swguiml>";

    title = SwApplicationInterface::GetUserDir();
    title += PATH_SEP;
    title += "sw_session.gui";

    FILE * f = SwFopen(title, FMD_WC);
    if (f)
    {
        fwrite(buffer, 1, buffer.Strlen(), f);
        fclose(f);
    }
}

void SowerAppFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWER", L"Sower"), SVSTR, L"2020");
}

void SowerAppFrame::OnQuit(wxCommandEvent& event)
{
    wxBusyCursor cursor;

    SwApplicationInterface::WriteRecentFileslistToTable(m_fileList);

    if (m_guipanel)
        m_guipanel->SaveUserData();

    Destroy();
}

void SowerAppFrame::OnPreferences(wxCommandEvent& event)
{
    SwPreferencesDlg * dlg = new SwPreferencesDlg(this);
    dlg->ShowModal();
    delete dlg;
}

void SowerAppFrame::OnLanguageChange()
{
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWER", L"Sower"));
    m_toolbar->SetToolShortHelp(ID_VOLUMESLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume")).GetArray());
    m_toolbar->SetToolShortHelp(ID_POSITIONSLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position")).GetArray());
    m_toolbar->SetToolShortHelp(ID_LOOPCHECKBOX, SwStringW(SwApplicationInterface::GetControlString("SID_LOOP", L"Loop")).GetArray());

    if (m_guipanel)
        m_guipanel->OnLanguageChange();
}

void SowerAppFrame::OnThemeChange()
{
    if (m_guipanel)
        m_guipanel->OnThemeChange();
}

void SowerAppFrame::OnSelectInterface(wxCommandEvent & event)
{
    SwInterfaceDlg * dlg = new SwInterfaceDlg(SwApplicationInterface::GetFrameWindow());
    dlg->ShowModal();
    delete dlg;
}

void SowerAppFrame::ProcessCmdLine()
{
    for (swUI32 i = 0; i < m_cmd.GetCount(); i ++)
    {
        if (m_guipanel)
            m_guipanel->OpenFile(m_cmd.GetAt(i));
    }
}

void SowerAppFrame::OnAudioOpen()
{
    m_PositionSlider->SetValue(0);
    m_PositionSlider->SetRange(0, SwApplicationInterface::GetAudio().GetPlayLength());
}

void SowerAppFrame::OnPositionSliderThumb(wxScrollEvent& event)
{
    m_skip = true;
}

void SowerAppFrame::OnPositionSliderThumbRelease(wxScrollEvent& event)
{
    SwApplicationInterface::GetAudio().SetPlayPosition(event.GetPosition());
    m_skip = false;
}

void SowerAppFrame::OnVolumeSliderScroll(wxScrollEvent& event)
{
    SwApplicationInterface::GetAudio().SetVolume(0.01 * event.GetPosition());
}

bool SowerAppFrame::OnCanDoPlay()
{
    if (SwApplicationInterface::GetAudio().HasAudio())
    {
        // Trying to avoid flicker.
        if (!m_VolumeSlider->IsEnabled())
        {
            m_PositionSlider->Enable();
            m_VolumeSlider->Enable();
            m_LoopCheckBox->Enable();
        }
    }
    else
    {
        // Trying to avoid flicker.
        if (m_VolumeSlider->IsEnabled())
        {
            m_PositionSlider->Disable();
            m_VolumeSlider->Disable();
            m_LoopCheckBox->Disable();
        }
    }

    return SwApplicationInterface::GetAudio().HasAudio() && !SwApplicationInterface::GetAudio().IsPlaying();
}

bool SowerAppFrame::OnCanDoPause()
{
    return SwApplicationInterface::GetAudio().HasAudio() && SwApplicationInterface::GetAudio().IsPlaying();
}

bool SowerAppFrame::OnCanDoStop()
{
    return SwApplicationInterface::GetAudio().HasAudio();
}

void SowerAppFrame::OnPlay(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Play();
}

void SowerAppFrame::OnPause(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Pause();
}

void SowerAppFrame::OnStop(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Close();
}

void SowerAppFrame::OnFrameTimer()
{
    if (!m_skip)
    {
        if (!SwApplicationInterface::GetAudio().HasAudio())
        {
            m_PositionSlider->SetValue(0);
        }
        else if (SwApplicationInterface::GetAudio().HasAudio() && !SwApplicationInterface::GetAudio().IsPlaying() && !SwApplicationInterface::GetAudio().IsPaused())
        {
            if (!m_LoopCheckBox->GetValue())
                SwApplicationInterface::GetAudio().Pause();

            m_PositionSlider->SetValue(0);
            SwApplicationInterface::GetAudio().SetPlayPosition(0);
        }
        else
            m_PositionSlider->SetValue(SwApplicationInterface::GetAudio().GetPlayPosition());
    }
}
