///////////////////////////////////////////////////////////////////
// Name:        mediadevice.h
// Purpose:     Wrapper for media players made available through
//              plugins.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MEDIADEVICE_H
#define MEDIADEVICE_H

#include "../sowerbase.h"
#include "../module/module.h"


class SOWERBASEEXP SwMediaStream
{
public:
    SwMediaStream();
    virtual ~SwMediaStream();

    bool Open(const char * path);
    bool Open(swUI16 moduleId, const char * mediaId);
    void Close();
    virtual swI64 read(void *data, swI64 size);
    virtual swI64 seek(swI64 offset, int origin);
    virtual swI64 tell();
    virtual swI64 getSize();
    FILE * GetFile() { return m_file; }

protected:
    SwModule *      m_module;
    SwMediaNode *   m_mediaNode;
    swI64           m_position;
    swI64           m_size;
    FILE *          m_file;
};

/*  Example ...

    SwMediaDevice * device = NULL;
    swUI16 plg = SwApplicationInterface::GetPlugInManager().FindPlugIn(PIT_DEVICE_AUDIO, 0);

    if (plg != NODE_ID_INVALID_16)
    {
        device = SwApplicationInterface::GetPlugInManager().GetAt(plg)->GetMediaDevice();
    }
*/

class SOWERBASEEXP SwMediaDevice
{
public:
    SwMediaDevice();
    ~SwMediaDevice();

    virtual bool OpenFromFile(const char * path);
    virtual bool OpenFromModule(swUI16 managerId, const char * src);
    virtual void Play();
    virtual void Pause();
    virtual void Stop();
    virtual void SetVolume(float volume);
    virtual swUI32 GetVolume();
    virtual void SetLoop(bool loop);
    virtual bool GetLoop();
    virtual void SetPlayPosition(swI64 position);
    virtual swI64 GetPlayPosition();
    virtual swI64 GetLength();

protected:
    SwMediaStream m_stream;
};

#endif // MEDIADEVICE_H
