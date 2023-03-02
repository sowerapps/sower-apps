///////////////////////////////////////////////////////////////////
// Name:        thmlviewerapp.cpp
// Purpose:     ThML Viewer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/thmlviewerapp.h"
#include "appi/appifa.h"
#include "dialogs/preferencesdlg.h"
#include "dialogs/interfacedlg.h"
#include "framework/splashscreen.h"
#include "av_media/audio.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(ThMLViewerApp);

bool ThMLViewerApp::OnInit()
{
<<<<<<< Updated upstream
=======
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_THML32)));
    #endif // defined __OSX__

>>>>>>> Stashed changes
    wxBusyCursor cursor;
    SwApplicationInterface::SetAppName("ThML Viewer");
    SwApplicationInterface::InitBasic();
    SwApplicationInterface::GetPlugInManager().SetLoadType(PIT_UNKNOWN);
    SwApplicationInterface::LoadPlugIns();
    ThMLViewerFrame* Frame = new ThMLViewerFrame(NULL, wxNewId(), L"ThML Viewer");
    SwApplicationInterface::GetPlugInManager().OnInitialize();
    SwSplashScreen * splash= new SwSplashScreen(wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT, 7000, Frame);
    splash->SetText(SwStringW(SwApplicationInterface::GetControlString("SID_THMLVIEWER", L"ThML Viewer")), L"2020");
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadModules();
    SwApplicationInterface::LoadModuleStates();
    // ThML files should be loaded before interface is created to prevent interface from loading
    // contents multiple times.
    SwApplicationInterface::LoadThMLFiles();
    SwApplicationInterface::LoadThMLFileStates();
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

const long ThMLViewerFrame::ID_TOOLBAR = wxNewId();
const long ThMLViewerFrame::ID_POSITIONSLIDER = wxNewId();
const long ThMLViewerFrame::ID_VOLUMESLIDER = wxNewId();
const long ThMLViewerFrame::ID_LOOPCHECKBOX = wxNewId();

ThMLViewerFrame::ThMLViewerFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxBusyCursor cursor;
    SetTitle(SwApplicationInterface::GetControlString("SID_THMLVIEWER", L"ThML Viewer"));
    SetIcon(SwApplicationInterface::GetThMLIcon());

    m_menubar = new SwMenuBar(this);
    m_menubar->AddStockItem(SW_GUIID_OPEN, true, true);
    m_menubar->AddStockItem(SW_GUIID_ABOUT, true, true);
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
    m_toolbar->SetToolShortHelp(ID_POSITIONSLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position")).GetArray());
    m_toolbar->AddControl(m_PositionSlider);

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

    m_skip = false;

    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&ThMLViewerFrame::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&ThMLViewerFrame::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&ThMLViewerFrame::OnVolumeSliderScroll);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&ThMLViewerFrame::OnPositionSliderThumb);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&ThMLViewerFrame::OnPositionSliderThumbRelease);
    Connect(id,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ThMLViewerFrame::OnQuit);
}

ThMLViewerFrame::~ThMLViewerFrame()
{
    SwApplicationInterface::CloseFiles();
}

void ThMLViewerFrame::OnPreferences(wxCommandEvent& event)
{
    SwPreferencesDlg * dlg = new SwPreferencesDlg(SwApplicationInterface::GetFrameWindow());
    dlg->ShowModal();
    delete dlg;
}

void ThMLViewerFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_THMLVIEWER", L"ThML Viewer"), SVSTR, L"2020");
}

void ThMLViewerFrame::OnQuit(wxCommandEvent& event)
{
    wxBusyCursor cursor;

    if (m_guipanel)
        m_guipanel->SaveUserData();

    Destroy();
}

void ThMLViewerFrame::OnLanguageChange()
{
    SetTitle(SwApplicationInterface::GetControlString("SID_THMLVIEWER", L"ThML Viewer"));
    m_toolbar->SetToolShortHelp(ID_VOLUMESLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume")).GetArray());
    m_toolbar->SetToolShortHelp(ID_POSITIONSLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position")).GetArray());
    m_toolbar->SetToolShortHelp(ID_LOOPCHECKBOX, SwStringW(SwApplicationInterface::GetControlString("SID_LOOP", L"Loop")).GetArray());

    if (m_guipanel)
        m_guipanel->OnLanguageChange();
}

void ThMLViewerFrame::OnThemeChange()
{
    if (m_guipanel)
        m_guipanel->OnThemeChange();
}

void ThMLViewerFrame::OnSelectInterface(wxCommandEvent & event)
{
    SwInterfaceDlg * dlg = new SwInterfaceDlg(SwApplicationInterface::GetFrameWindow());
    dlg->ShowModal();
    delete dlg;
}

void ThMLViewerFrame::OnAudioOpen()
{
    m_PositionSlider->SetValue(0);
    m_PositionSlider->SetRange(0, SwApplicationInterface::GetAudio().GetPlayLength());
}

void ThMLViewerFrame::OnPositionSliderThumb(wxScrollEvent& event)
{
    m_skip = true;
}

void ThMLViewerFrame::OnPositionSliderThumbRelease(wxScrollEvent& event)
{
    SwApplicationInterface::GetAudio().SetPlayPosition(event.GetPosition());
    m_skip = false;
}

void ThMLViewerFrame::OnVolumeSliderScroll(wxScrollEvent& event)
{
    SwApplicationInterface::GetAudio().SetVolume(0.01 * event.GetPosition());
}

bool ThMLViewerFrame::OnCanDoPlay()
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

bool ThMLViewerFrame::OnCanDoPause()
{
    return SwApplicationInterface::GetAudio().HasAudio() && SwApplicationInterface::GetAudio().IsPlaying();
}

bool ThMLViewerFrame::OnCanDoStop()
{
    return SwApplicationInterface::GetAudio().HasAudio();
}

void ThMLViewerFrame::OnPlay(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Play();
}

void ThMLViewerFrame::OnPause(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Pause();
}

void ThMLViewerFrame::OnStop(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Close();
}

void ThMLViewerFrame::OnFrameTimer()
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

void ThMLViewerFrame::ProcessCmdLine()
{
    for (swUI32 i = 0; i < m_cmd.GetCount(); i ++)
    {
        if (m_guipanel)
            m_guipanel->OpenFile(m_cmd.GetAt(i));
    }
}
