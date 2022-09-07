///////////////////////////////////////////////////////////////////
// Name:        mediadevice.cpp
// Purpose:     Wrapper for media players made available through
//              plugins.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/av_media/mediadevice.h"
#include "../../include/appi/appifa.h"

SwMediaStream::SwMediaStream()
{
    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;
}

SwMediaStream::~SwMediaStream()
{
}

bool SwMediaStream::open(swUI16 moduleId, const char * mediaId)
{
    if (moduleId == NODE_ID_INVALID_16 || !mediaId)
        return false;

    swUI16 pos;

    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;


    pos = SwApplicationInterface::GetModuleManager().FindByMID(moduleId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    m_module = SwApplicationInterface::GetModuleManager().GetAt(pos);

    if (!m_module || !m_module->m_file)
        return false;

    pos = m_module->GetMediaContents().FindItem(mediaId);

    if (pos == NODE_ID_INVALID_16)
    {
        m_module = NULL;
        return false;
    }

    m_mediaNode = m_module->GetMediaContents().GetNode(pos);

    if (!m_mediaNode)
    {
        m_module = NULL;
        return false;
    }

    m_size = (swI64) m_mediaNode->GetSize(m_module->m_file, m_module->m_header.itemdataLocator, m_module->m_header.filecontentsLocator);

    return true;
}

swI64 SwMediaStream::read(void *data, swI64 size)
{
    if (!m_module || !m_mediaNode || !data)
        return 0;

    swUI32 bytesRead = m_mediaNode->ReadStream(m_module->m_file, data, m_module->m_header.itemdataLocator, m_module->m_header.filecontentsLocator, m_position, size, m_module->m_header.k1, m_module->m_header.k2, m_module->m_header.isEncrypted);
    m_position += bytesRead;

    return (swI64) bytesRead;
}

swI64 SwMediaStream::seek(swI64 position)
{
    m_position = position;

    return m_position;
}

swI64 SwMediaStream::tell()
{
    return m_position;
}

swI64 SwMediaStream::getSize()
{
    return m_size;
}

SwMediaDevice::SwMediaDevice()
{
}

SwMediaDevice::~SwMediaDevice()
{
}

bool SwMediaDevice::OpenFromFile(const char * path)
{
    return false;
}

bool SwMediaDevice::OpenFromModule(swUI16 managerId, const char * src)
{
    if (!src)
        return false;

    if (!m_stream.open(managerId, src))
        return false;

    return true;
}

void SwMediaDevice::Play()
{
}

void SwMediaDevice::Pause()
{
}

void SwMediaDevice::Stop()
{
}

void SwMediaDevice::SetVolume(float volume)
{
}

swUI32 SwMediaDevice::GetVolume()
{
    return 0;
}

void SwMediaDevice::SetLoop(bool loop)
{
}

bool SwMediaDevice::GetLoop()
{
    return false;
}

void SwMediaDevice::SetPlayPosition(swI64 position)
{
}

swI64 SwMediaDevice::GetPlayPosition()
{
    return 0;
}

swI64 SwMediaDevice::GetLength()
{
    return 0;
}
