///////////////////////////////////////////////////////////////////
// Name:        sowerhelpapp.cpp
// Purpose:     Sower Help
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowerhelpapp.h"
#include "framework/bookpanels.h"
#include "appi/appifa.h"
#include "thml/thml_utility.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerHelpApp);

bool SowerHelpApp::OnInit()
{
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_HELP32)));
    #endif // defined __OSX__

    wxBusyCursor cursor;
    SwApplicationInterface::SetAppName("Sower Help");
    SwApplicationInterface::InitBasic();
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadHelpModules();
    SwApplicationInterface::GetPlugInManager().SetLoadType(PIT_UNKNOWN);
    SwApplicationInterface::LoadPlugIns();

    SowerHelpFrame* Frame = new SowerHelpFrame(NULL, wxNewId(), L"");
    SwApplicationInterface::GetPlugInManager().OnInitializeTools();
    Frame->Maximize();
    SetTopWindow(Frame);

    for (int i = 1; i < argc; i ++)
    {
        Frame->GetCmdArray().Add(argv[i]);
    }

    Frame->ProcessCmdLine();

    return true;
}

const long SowerHelpFrame::ID_TOOLBAR = wxNewId();
const long SowerHelpFrame::ID_POSITIONSLIDER = wxNewId();
const long SowerHelpFrame::ID_VOLUMESLIDER = wxNewId();
const long SowerHelpFrame::ID_LOOPCHECKBOX = wxNewId();
const long SowerHelpFrame::ID_BOOKMARKSLIST = wxNewId();

SowerHelpFrame::SowerHelpFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    wxBusyCursor cursor;
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERHELP", L"Sower Help"));
    SetIcon(SwApplicationInterface::GetToolsIcon());

    m_menubar = new SwMenuBar(this);
    m_menubar->AddStockItem(SW_GUIID_PRINT, false, false);
    m_menubar->AddStockItem(SW_GUIID_PRINTPREVIEW, false, true);
    m_menubar->AddStockItem(SW_GUIID_QUIT, true, true);
    m_menubar->AddStockItem(SW_GUIID_BOOKMARKPAGE, true, true);
    m_menubar->AddStockItem(SW_GUIID_COPY, false, true);
    m_menubar->AddStockItem(SW_GUIID_SELECTALL, false, false);
    m_menubar->AddStockItem(SW_GUIID_BOOKMARKSVIEW, true, true);
    m_menubar->AddStockItem(SW_GUIID_ZOOMIN, false, true);
    m_menubar->AddStockItem(SW_GUIID_ZOOMOUT, false, true);
    m_menubar->AddStockItem(SW_GUIID_VIEWNORMAL, false, true);
    m_menubar->AddStockItem(SW_GUIID_CONTENTSDOWN, false, true);
    m_menubar->AddStockItem(SW_GUIID_CONTENTSUP, false, true);
    m_menubar->AddStockItem(SW_GUIID_BACKINHISTORY, false, true);
    m_menubar->AddStockItem(SW_GUIID_FORWARDINHISTORY, false, true);
    m_menubar->AddStockItem(SW_GUIID_ABOUT, true, true);

    SetMenuBar(m_menubar);

    m_toolbar = new SwToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, SW_TOOLBAR_DEFAULT_STYLE, true, this);
    m_toolbar->AddStockItem(SW_GUIID_PRINT, false, false);
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
    SetSowerMenuBar(m_menubar);
    SetSowerToolBar(m_toolbar);

    SwGuiPanel * guiPanel = new SwGuiPanel(this, wxNewId());
    SetGuiPanel(guiPanel);

    m_bookPanel = new SwModuleBookPanel(guiPanel, wxNewId());
    m_bookmarksList = new SwHelpBookmarksListCtrl(m_bookPanel->ToolNotebook, ID_BOOKMARKSLIST, wxPoint(232,160), wxDefaultSize, wxLC_REPORT|wxLC_NO_HEADER, wxValidator(), L"ID_BOOKMARKSLIST");

    m_bookPanel->ToolNotebook->InsertPage(3, m_bookmarksList, SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
    guiPanel->GetAuiManager()->AddPane(m_bookPanel, wxAuiPaneInfo().MinSize(-1, 300).Name(name).CloseButton(false).Show(true).CenterPane());
    guiPanel->SetPanel(m_bookPanel);
    guiPanel->GetAuiManager()->Update();
    m_bookPanel->searchPanel->SetId(true);
    m_viewMenu = new SwStandardViewMenu(SwApplicationInterface::GetFrameWindow());

    m_bookPanel->SetPopUpMenu(m_viewMenu);

    m_manager->AddPane(guiPanel, wxAuiPaneInfo().MinSize(-1, 300).Name(name).CloseButton(false).Show(true).CenterPane());
    m_manager->Update();
    SetGuiPanel(guiPanel);

    SwModule * module ;
    for (swUI16 i = 0; i < SwApplicationInterface::GetModuleManager().GetModules(); i ++)
    {
        module = SwApplicationInterface::GetModuleManager().GetAt(i);

        if (!module || module->GetHeader().category != CATEGORY_HELP)
            continue;

        m_bookPanel->TocTreeCtrl->BuildTree(module->GetTableofContents(), m_bookPanel->TocTreeCtrl->GetRootItem(), CATEGORY_HELP, module->m_managerId);
    }

    m_listMenu = new SwMenu();
    m_listMenu->AddStockItem(SW_GUIID_DELETE, true, false);

    m_bookmarksList->ReadFromTable();

    m_skip = false;

    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&SowerHelpFrame::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&SowerHelpFrame::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&SowerHelpFrame::OnVolumeSliderScroll);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&SowerHelpFrame::OnPositionSliderThumb);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&SowerHelpFrame::OnPositionSliderThumbRelease);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_ACTIVATED,(wxObjectEventFunction)&SowerHelpFrame::OnBookmarkActivated);
    Connect(ID_BOOKMARKSLIST, wxEVT_LIST_ITEM_RIGHT_CLICK,(wxObjectEventFunction)&SowerHelpFrame::OnRightClick);
    Connect(SwGuiData::GetDataForItemSwId(SW_GUIID_DELETE)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SowerHelpFrame::OnDelete);
    Connect(id,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SowerHelpFrame::OnQuit);
    Show();
}

SowerHelpFrame::~SowerHelpFrame()
{
    SwApplicationInterface::WriteHelpBookMarklistToTable(m_bookmarksList);
    SwApplicationInterface::SaveUserData();
    SwApplicationInterface::CloseFiles();
}

void SowerHelpFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERHELP", L"Sower Help"), SVSTR, L"2020");
}

void SowerHelpFrame::OnQuit(wxCommandEvent& event)
{
    wxBusyCursor cursor;

    if (m_guipanel)
        m_guipanel->SaveUserData();

    Destroy();
}

void SowerHelpFrame::OnLanguageChange()
{
    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERHELP", L"Sower Help"));
    m_toolbar->SetToolShortHelp(ID_VOLUMESLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume")).GetArray());
    m_toolbar->SetToolShortHelp(ID_POSITIONSLIDER, SwStringW(SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position")).GetArray());
    m_toolbar->SetToolShortHelp(ID_LOOPCHECKBOX, SwStringW(SwApplicationInterface::GetControlString("SID_LOOP", L"Loop")).GetArray());

    if (m_guipanel)
        m_guipanel->OnLanguageChange();

    if (m_listMenu)
        m_listMenu->OnLanguageChange();

    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();

    m_bookPanel->ToolNotebook->SetPageText(3, SwApplicationInterface::GetControlString("SID_BOOKMARKS", L"Bookmarks"));
}

void SowerHelpFrame::OnThemeChange()
{
    if (m_guipanel)
        m_guipanel->OnThemeChange();

    if (m_listMenu)
        m_listMenu->OnThemeChange();

    if (m_viewMenu)
        m_viewMenu->OnThemeChange();
}

void SowerHelpFrame::OnAudioOpen()
{
    m_PositionSlider->SetValue(0);
    m_PositionSlider->SetRange(0, SwApplicationInterface::GetAudio().GetPlayLength());
}

void SowerHelpFrame::OnPositionSliderThumb(wxScrollEvent& event)
{
    m_skip = true;
}

void SowerHelpFrame::OnPositionSliderThumbRelease(wxScrollEvent& event)
{
    SwApplicationInterface::GetAudio().SetPlayPosition(event.GetPosition());
    m_skip = false;
}

void SowerHelpFrame::OnVolumeSliderScroll(wxScrollEvent& event)
{
    SwApplicationInterface::GetAudio().SetVolume(0.01 * event.GetPosition());
}

bool SowerHelpFrame::OnCanDoPlay()
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

bool SowerHelpFrame::OnCanDoPause()
{
    return SwApplicationInterface::GetAudio().HasAudio() && SwApplicationInterface::GetAudio().IsPlaying();
}

bool SowerHelpFrame::OnCanDoStop()
{
    return SwApplicationInterface::GetAudio().HasAudio();
}

void SowerHelpFrame::OnPlay(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Play();
}

void SowerHelpFrame::OnPause(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Pause();
}

void SowerHelpFrame::OnStop(wxCommandEvent& event)
{
    SwApplicationInterface::GetAudio().Close();
}

void SowerHelpFrame::OnFrameTimer()
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

void SowerHelpFrame::OnBookmark(wxCommandEvent & event)
{
    SwBookMarkClientData * data = new SwBookMarkClientData();
    SwString title;
    SwStringW translation;

    if (!m_bookPanel->GetBookMarkData(title, *data))
    {
        delete data;
    }
    else
    {
        translation.Copy(title);
        wxListItem lItem;
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(m_bookmarksList->GetItemCount());
        lItem.SetText(translation.GetArray());
        lItem.SetData(data);
        m_bookmarksList->wxListCtrl::InsertItem(lItem);
    }
}

void SowerHelpFrame::OnBookmarkActivated(wxListEvent& event)
{
    SwBookMarkClientData * data = (SwBookMarkClientData *) event.GetItem().GetData();

    m_bookPanel->ActivateBookMark(*data, "");
}

void SowerHelpFrame::OnDelete(wxCommandEvent & event)
{
    long item = m_bookmarksList->GetSelected();

    if (item == -1)
        return;

    m_bookmarksList->DeleteItem(item);
}

void SowerHelpFrame::OnRightClick(wxCommandEvent & event)
{
    m_bookmarksList->PopupMenu(m_listMenu);
}

void SowerHelpFrame::ProcessCmdLine()
{
    for (swUI32 i = 0; i < m_cmd.GetCount(); i ++)
    {
        if (m_guipanel)
            m_guipanel->OpenFile(m_cmd.GetAt(i));
    }
}
