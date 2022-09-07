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
#include <SFML/System/InputStream.hpp>
#include <SFML/Audio/Music.hpp>
#include <wx/control.h>
#include <wx/gbsizer.h>

using namespace sf;

class SOWERBASEEXP SwAudioStream : public sf::InputStream
{
public:
    SwAudioStream();
    virtual ~SwAudioStream();

    bool open(swUI16 moduleId, const char * mediaId);
    virtual Int64 read(void *data, Int64 size);
    virtual Int64 seek(Int64 position);
    virtual Int64 tell();
    virtual Int64 getSize();

protected:
    SwModule *      m_module;
    SwMediaNode *     m_mediaNode;
    Int64           m_position;
    Int64           m_size;
};

class SOWERBASEEXP SwAudioCtrl : public wxControl
{
public:
    SwAudioCtrl();
    SwAudioCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxControlNameStr);
    virtual ~SwAudioCtrl();

    void BuildContent();
    bool OnOpen(const char * path);
    bool OnOpen(swUI16 managerId, const char * src);
    void OnAutoPlay();
    void SetLoop(bool loop = true);
    wxButton* PauseButton;
    wxButton* PlayButton;
    wxButton* StopButton;
    wxSlider* VolmeSlider;
    wxStaticText* TitleLabel;
    wxStaticText* VolumeLabel;

protected:
    static const long ID_PAUSEBUTTON;
    static const long ID_PLAYBUTTON;
    static const long ID_STOPBUTTON;
    static const long ID_VOLUMELABEL;
    static const long ID_VOLUMESLIDER;
    static const long ID_TITLELABEL;

    void OnPauseButtonClick(wxCommandEvent& event);
    void OnPlayButtonClick(wxCommandEvent& event);
    void OnStopButtonClick(wxCommandEvent& event);
    void OnVolmeSliderCmdScroll(wxScrollEvent& event);

    sf::Music     m_music;
    SwAudioStream m_stream;
};

#endif // AUDIOCONTROL_H
