///////////////////////////////////////////////////////////////////
// Name:        audio.cpp
// Purpose:     Audio playback.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/av_media/audio.h"
#include "../../include/appi/appifa.h"

#define MA_NO_ENCODING
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#define MA_NO_GENERATION
#define MA_NO_PULSEAUDIO
#define MA_NO_JACK

#define MINIAUDIO_IMPLEMENTATION
#include "../../depends-common/miniaudio.h"

SwMediaStream * gp_stream;

ma_result onVFSOpen(ma_vfs* pVFS, const char* pFilePath, ma_uint32 openMode, ma_vfs_file* pFile)
{
    if (!pFilePath)
        return MA_ERROR;

    if (openMode == MA_OPEN_MODE_READ && gp_stream->Open(pFilePath))
    {
        *pFile = (void *) gp_stream;
        return MA_SUCCESS;
    }

    return MA_ERROR;
}

ma_result onVFSOpenW(ma_vfs* pVFS, const wchar_t* pFilePath, ma_uint32 openMode, ma_vfs_file* pFile)
{
    return MA_NOT_IMPLEMENTED;
}

ma_result onVFSClose(ma_vfs* pVFS, ma_vfs_file file)
{
    SwMediaStream * stream = (SwMediaStream *) file;
    stream->Close();

    return MA_SUCCESS;
}

ma_result onVFSRead(ma_vfs* pVFS, ma_vfs_file file, void* pDst, size_t sizeInBytes, size_t* pBytesRead)
{
    SwMediaStream * stream = (SwMediaStream *) file;
    *pBytesRead = stream->read(pDst, sizeInBytes);

    return MA_SUCCESS;
}

ma_result onVFSWrite(ma_vfs* pVFS, ma_vfs_file file, const void* pSrc, size_t sizeInBytes, size_t* pBytesWritten)
{
    return MA_NOT_IMPLEMENTED;
}

ma_result onVFSSeek(ma_vfs* pVFS, ma_vfs_file file, ma_int64 offset, ma_seek_origin origin)
{
    if (!file)
        return MA_ERROR;

    int seekor = SEEK_SET;
    if (origin == ma_seek_origin_current)
        seekor = SEEK_CUR;

    SwMediaStream * stream = (SwMediaStream *) file;
    stream->seek(offset, seekor);

    return MA_SUCCESS;
}

ma_result onVFSTell(ma_vfs* pVFS, ma_vfs_file file, ma_int64* pCursor)
{
    if (!file || !pCursor)
        return MA_ERROR;

    SwMediaStream * stream = (SwMediaStream *) file;
    *pCursor = (ma_int64) stream->tell();

    return MA_SUCCESS;
}

ma_result onVFSInfo(ma_vfs* pVFS, ma_vfs_file file, ma_file_info* pInfo)
{
    if (!file || !pInfo)
        return MA_ERROR;

    SwMediaStream * stream = (SwMediaStream *) file;
    pInfo->sizeInBytes = (ma_uint64) stream->getSize();

    return MA_SUCCESS;
}

ma_vfs_callbacks m_vfs =
{
    onVFSOpen,
    onVFSOpenW,
    onVFSClose,
    onVFSRead,
    onVFSWrite,
    onVFSSeek,
    onVFSTell,
    onVFSInfo
};

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;

    if (pDecoder == NULL)
        return;

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
}

SwAudio::SwAudio()
{
    m_device = (void *) new ma_device;
    SetVolume(.5);
    m_decoder = NULL;
}

SwAudio::~SwAudio()
{
    gp_stream = NULL;

    if (m_decoder)
    {
     // It seems correct to call ma_device_uninit here, but
     // it appears to launch a thread that doesn't terminate.
     // ma_device_uninit(((ma_device *) m_device));
        ma_decoder_uninit(((ma_decoder *) m_decoder));
        delete ((ma_decoder *) m_decoder);
    }

    delete ((ma_device *) m_device);
}

bool SwAudio::Open(const char * path)
{
    if (m_decoder)
        Close();

    if (!path)
        return false;

    m_decoder = (void *) new ma_decoder;
    ma_result result;
    ma_device_config config;
    config = ma_device_config_init(ma_device_type_playback);
    gp_stream = &m_stream;
    result = ma_decoder_init_vfs(&m_vfs, path, NULL, ((ma_decoder *) m_decoder));

    if (result != MA_SUCCESS)
        return false;

    config.playback.format   = ((ma_decoder *) m_decoder)->outputFormat;
    config.playback.channels = ((ma_decoder *) m_decoder)->outputChannels;
    config.sampleRate        = ((ma_decoder *) m_decoder)->outputSampleRate;
    config.dataCallback      = &data_callback;
    config.pUserData         = m_decoder;

    if (ma_device_init(NULL, &config, ((ma_device *) m_device)) != MA_SUCCESS)
    {
        ma_decoder_uninit(((ma_decoder *) m_decoder));
        delete ((ma_decoder *) m_decoder);
        m_decoder = NULL;
        return false;
    }

    GetPlayLength();

    if (SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnAudioOpen();

    return true;
}

void SwAudio::Close()
{
    ma_device_stop(((ma_device *) m_device));

    if (m_decoder)
    {
        ma_device_uninit(((ma_device *) m_device));
        ma_decoder_uninit(((ma_decoder *) m_decoder));
        delete ((ma_decoder *) m_decoder);
        m_decoder = NULL;
    }

    m_length = 0;
    gp_stream = NULL;
    SwApplicationInterface::GetFrameWindow()->OnAudioClose();
}

swFloat SwAudio::GetVolume()
{
    float volume = 0;
    ma_device_get_master_volume(((ma_device *) m_device), &volume);

    return (swFloat) volume;
}

void SwAudio::SetVolume(swFloat volume)
{
    ma_device_set_master_volume(((ma_device *) m_device), volume);
}

swFloat SwAudio::GetPlayPosition()
{
    if (!m_decoder)
        return 0;

    float cursor = 0;
    ma_data_source_get_cursor_in_seconds(((ma_decoder *) m_decoder), &cursor);

    return (swFloat) cursor;
}

bool SwAudio::SetPlayPosition(swFloat position)
{
    if (!m_decoder)
        return false;

    ma_decoder_seek_to_pcm_frame(((ma_decoder *) m_decoder), (ma_uint64) position * ((ma_device *) m_device)->sampleRate);

    return true;
}

swFloat SwAudio::GetPlayLength()
{
    if (!m_decoder)
        return 0;

    if (m_length == 0)
    {
        float length = 0;
        ma_data_source_get_length_in_seconds(((ma_decoder *) m_decoder), &length);
        m_length = (swFloat) length;
    }

    return m_length;
}

bool SwAudio::Play()
{
    if (!m_decoder)
        return false;

    if (ma_device_start(((ma_device *) m_device)) != MA_SUCCESS)
    {
        ma_device_uninit(((ma_device *) m_device));
        ma_decoder_uninit(((ma_decoder *) m_decoder));
        delete (((ma_decoder *) m_decoder));
        m_decoder = NULL;
        return false;
    }

    return true;
}

bool SwAudio::Pause()
{
    if (!m_decoder)
        return false;

    if (ma_device_stop(((ma_device *) m_device)) != MA_SUCCESS)
        return false;

    return true;
}

bool SwAudio::HasAudio()
{
    return (bool) m_decoder;
}

bool SwAudio::IsPlaying()
{
    if (!m_decoder)
        return false;

    ma_uint64 frames;
    ma_decoder_get_available_frames((ma_decoder*) m_decoder, &frames);
    ma_device_state state = ma_device_get_state(((ma_device *) m_device));

    if ((state == ma_device_state_starting || state == ma_device_state_started) && frames)
        return true;

    return false;
}

bool SwAudio::IsPaused()
{
    if (!m_decoder)
        return false;

    ma_device_state state = ma_device_get_state(((ma_device *) m_device));

    if (state == ma_device_state_stopping || state == ma_device_state_stopped)
        return true;

    return false;
}

