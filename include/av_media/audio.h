///////////////////////////////////////////////////////////////////
// Name:        audio.h
// Purpose:     Audio playback.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUDIO_H
#define AUDIO_H

#include "../sowerbase.h"
#include "../av_media/mediadevice.h"

class SOWERBASEEXP SwAudio
{
public:
    SwAudio();
    virtual ~SwAudio();

    bool Open(const char * path);
    void Close();
    swFloat GetVolume();
    void SetVolume(swFloat volume);
    swFloat GetPlayPosition();
    bool SetPlayPosition(swFloat position);
    swFloat GetPlayLength();
    bool Play();
    bool Pause();
    bool HasAudio();
    bool IsPlaying();
    bool IsPaused();

protected:
    void *        m_device;
    void *        m_decoder;
    swFloat       m_length;
    SwMediaStream m_stream;
};

#endif // AUDIO_H
