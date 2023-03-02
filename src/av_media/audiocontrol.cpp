///////////////////////////////////////////////////////////////////
// Name:        audiocontrol.cpp
// Purpose:     An audio player that can play streamed audio from
//              Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/av_media/audiocontrol.h"
#include "../../include/appi/appifa.h"

<<<<<<< Updated upstream
SwAudioStream::SwAudioStream()
=======
SwAudioCtrlTimer::SwAudioCtrlTimer()
>>>>>>> Stashed changes
{
    m_ctrl = NULL;
    Start(100);
}

SwAudioCtrlTimer::~SwAudioCtrlTimer()
{
}

void SwAudioCtrlTimer::Notify()
{
    if (m_ctrl)
        m_ctrl->OnTimer();
}

const long SwAudioCtrl::ID_PAUSEBUTTON = wxNewId();
const long SwAudioCtrl::ID_PLAYBUTTON = wxNewId();
const long SwAudioCtrl::ID_STOPBUTTON = wxNewId();
const long SwAudioCtrl::ID_LOOPCHECKBOX = wxNewId();
const long SwAudioCtrl::ID_VOLUMELABEL = wxNewId();
const long SwAudioCtrl::ID_VOLUMESLIDER = wxNewId();
const long SwAudioCtrl::ID_POSITIONLABEL = wxNewId();
const long SwAudioCtrl::ID_POSITIONSLIDER = wxNewId();
const long SwAudioCtrl::ID_TITLELABEL = wxNewId();

SwAudioCtrl::SwAudioCtrl()
{
}

SwAudioCtrl::SwAudioCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
{
    Create(parent, id, pos, size, style, validator, name);
    BuildContent();
    m_timer.m_ctrl = this;
}

void SwAudioCtrl::BuildContent()
{
    wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;

	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	TitleLabel = new wxStaticText(this, ID_TITLELABEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
	GridBagSizer1->Add(TitleLabel, wxGBPosition(0, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);
	PauseButton = new wxButton(this, ID_PAUSEBUTTON, SwApplicationInterface::GetControlString("SID_PAUSE", L"Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PAUSEBUTTON");
	GridBagSizer2->Add(PauseButton, wxGBPosition(0, 0), wxDefaultSpan, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlayButton = new wxButton(this, ID_PLAYBUTTON, SwApplicationInterface::GetControlString("SID_PLAY", L"Play"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PLAYBUTTON");
	GridBagSizer2->Add(PlayButton, wxGBPosition(0, 1), wxDefaultSpan, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StopButton = new wxButton(this, ID_STOPBUTTON, SwApplicationInterface::GetControlString("SID_STOP", L"Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_STOPBUTTON");
	GridBagSizer2->Add(StopButton, wxGBPosition(0, 2), wxDefaultSpan, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(GridBagSizer2, wxGBPosition(1, 0), wxGBSpan(1, 2), wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	VolumeLabel = new wxStaticText(this, ID_VOLUMELABEL, SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume"), wxDefaultPosition, wxDefaultSize, 0, L"ID_VOLUMELABEL");
	GridBagSizer1->Add(VolumeLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	VolumeSlider = new wxSlider(this, ID_VOLUMESLIDER, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_VOLUMESLIDER");
	VolumeSlider->SetThumbLength(5);
	GridBagSizer1->Add(VolumeSlider, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
	PositionLabel = new wxStaticText(this, ID_POSITIONLABEL, SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position"), wxDefaultPosition, wxDefaultSize, 0, L"ID_POSITIONLABEL");
	GridBagSizer1->Add(PositionLabel, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	PositionSlider = new wxSlider(this, ID_POSITIONSLIDER, 0, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_POSITIONSLIDER");
	PositionSlider->SetThumbLength(5);
	GridBagSizer1->Add(PositionSlider, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
	LoopCheckBox = new wxCheckBox(this, ID_LOOPCHECKBOX, SwApplicationInterface::GetControlString("SID_LOOP", L"Loop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_LOOPCHECKEBOX");
	GridBagSizer1->Add(LoopCheckBox, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

    m_skip = false;
    m_delay = 0;
    m_audio.SetVolume(.5);

	Connect(ID_PAUSEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAudioCtrl::OnPauseButtonClick);
	Connect(ID_PLAYBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAudioCtrl::OnPlayButtonClick);
	Connect(ID_STOPBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAudioCtrl::OnStopButtonClick);
	Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEUP,(wxObjectEventFunction)&SwAudioCtrl::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_LINEDOWN,(wxObjectEventFunction)&SwAudioCtrl::OnVolumeSliderScroll);
    Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&SwAudioCtrl::OnVolumeSliderScroll);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBTRACK,(wxObjectEventFunction)&SwAudioCtrl::OnPositionSliderThumb);
    Connect(ID_POSITIONSLIDER,wxEVT_SCROLL_THUMBRELEASE,(wxObjectEventFunction)&SwAudioCtrl::OnPositionSliderThumbRelease);
}

SwAudioCtrl::~SwAudioCtrl()
{
}

void SwAudioCtrl::Reset()
{
    m_audio.Close();
    PositionSlider->SetValue(0);
    TitleLabel->SetLabel("");
    PlayButton->Disable();
    PauseButton->Disable();
    PositionSlider->Disable();
    LoopCheckBox->Disable();
}

bool SwAudioCtrl::OnOpen(const char * path)
{
    Reset();

    if (!path)
        return false;

    PositionSlider->SetValue(0);

    if (!m_audio.Open(path))
        return false;

    PositionSlider->SetRange(0, (int) m_audio.GetPlayLength());
    PositionSlider->Enable();
    TitleLabel->SetLabel(path);

    return true;
}

void SwAudioCtrl::OnAutoPlay()
{
    m_audio.Play();
}

void SwAudioCtrl::OnPauseButtonClick(wxCommandEvent& event)
{
    m_audio.Pause();
}

void SwAudioCtrl::OnPlayButtonClick(wxCommandEvent& event)
{
    m_audio.Play();
}

void SwAudioCtrl::OnStopButtonClick(wxCommandEvent& event)
{
    m_audio.Close();
}

void SwAudioCtrl::OnVolumeSliderScroll(wxScrollEvent& event)
{

    m_audio.SetVolume(.01 * event.GetPosition());
}

void SwAudioCtrl::OnPositionSliderThumb(wxScrollEvent& event)
{
    m_skip = true;
}

void SwAudioCtrl::OnPositionSliderThumbRelease(wxScrollEvent& event)
{
    m_delay = 2;
    m_audio.SetPlayPosition(event.GetPosition());
    m_skip = false;
}
<<<<<<< Updated upstream
=======

void SwAudioCtrl::OnTimer()
{
    if (!m_audio.HasAudio())
    {
        PlayButton->Disable();
        PauseButton->Disable();
        StopButton->Disable();
        LoopCheckBox->Disable();
        PositionSlider->Disable();
        VolumeSlider->Disable();
    }
    else if (m_audio.IsPlaying())
    {
        PlayButton->Disable();
        PauseButton->Enable();
        StopButton->Enable();
        LoopCheckBox->Enable();
        PositionSlider->Enable();
        VolumeSlider->Enable();
    }
    else if (m_audio.IsPaused())
    {
        PlayButton->Enable();
        PauseButton->Disable();
        StopButton->Enable();
        LoopCheckBox->Enable();
        PositionSlider->Enable();
        VolumeSlider->Enable();
    }

    if (m_delay)
    {
        m_delay --;
        return;
    }

    if (!m_skip)
    {
        if (!m_audio.HasAudio())
        {
            PositionSlider->SetValue(0);
        }
        else if (m_audio.HasAudio() && !m_audio.IsPlaying() && !m_audio.IsPaused())
        {
            if (!LoopCheckBox->GetValue())
                m_audio.Pause();

            PositionSlider->SetValue(0);
            m_audio.SetPlayPosition(0);
        }
        else
            PositionSlider->SetValue(m_audio.GetPlayPosition());
    }
}

void SwAudioCtrl::OnLanguageChange()
{
    PlayButton->SetLabel(SwApplicationInterface::GetControlString("SID_PLAY", L"Play"));
    PauseButton->SetLabel(SwApplicationInterface::GetControlString("SID_PAUSE", L"Pause"));
    StopButton->SetLabel(SwApplicationInterface::GetControlString("SID_STOP", L"Stop"));
    PositionLabel->SetLabel(SwApplicationInterface::GetControlString("SID_PLAYPOSITION", L"Play position"));
    VolumeLabel->SetLabel(SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume"));
    LoopCheckBox->SetLabel(SwApplicationInterface::GetControlString("SID_LOOP", L"Loop"));
}
>>>>>>> Stashed changes
