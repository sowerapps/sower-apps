///////////////////////////////////////////////////////////////////
// Name:        audiocontrol.h
// Purpose:     An audio player that can play streamed audio from
//              Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUDIOCONTROL_H
#define AUDIOCONTROL_H

#include "../sowerbase.h"
#include "../module/module.h"
#include "../module/mediacontents.h"
#include "audio.h"
#include <wx/control.h>
#include <wx/gbsizer.h>

class SwAudioCtrl;
class SOWERBASEEXP SwAudioCtrlTimer : public wxTimer
{
public:
    SwAudioCtrlTimer();
    virtual ~SwAudioCtrlTimer();
    virtual void Notify();
    SwAudioCtrl * m_ctrl;
};

class SOWERBASEEXP SwAudioCtrl : public wxControl
{
public:
    SwAudioCtrl();
    SwAudioCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxControlNameStr);
    virtual ~SwAudioCtrl();

    void BuildContent();
    void Reset();
    bool OnOpen(const char * path);
    void OnAutoPlay();
    wxButton* PauseButton;
    wxButton* PlayButton;
    wxButton* StopButton;
    wxCheckBox* LoopCheckBox;
    wxSlider* VolumeSlider;
    wxSlider* PositionSlider;
    wxStaticText* TitleLabel;
    wxStaticText* VolumeLabel;
    wxStaticText* PositionLabel;

    void OnTimer();

protected:
    static const long ID_PAUSEBUTTON;
    static const long ID_PLAYBUTTON;
    static const long ID_STOPBUTTON;
    static const long ID_LOOPCHECKBOX;
    static const long ID_VOLUMELABEL;
    static const long ID_VOLUMESLIDER;
    static const long ID_POSITIONLABEL;
    static const long ID_POSITIONSLIDER;
    static const long ID_TITLELABEL;

    void OnPauseButtonClick(wxCommandEvent& event);
    void OnPlayButtonClick(wxCommandEvent& event);
    void OnStopButtonClick(wxCommandEvent& event);
    void OnVolumeSliderScroll(wxScrollEvent& event);
    virtual void OnPositionSliderThumb(wxScrollEvent& event);
    virtual void OnPositionSliderThumbRelease(wxScrollEvent& event);
    virtual void OnLanguageChange();

    SwAudio          m_audio;
    SwAudioCtrlTimer m_timer;
    bool             m_skip;
    swUI8            m_delay;
};

#endif // AUDIOCONTROL_H
