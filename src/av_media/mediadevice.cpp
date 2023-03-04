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
    m_file = NULL;
}

SwMediaStream::~SwMediaStream()
{
}

bool SwMediaStream::Open(const char * path)
{
    if (!path)
        return false;

    SwString urlCpy(path), identifier;
    char * ip;

    ip = strstr(urlCpy, " identifier:");

    if (ip)
    {
        *ip = '\0';
        swUI16 modid = (swUI16) atoi(ip + 12);
        return Open(modid, urlCpy);
    }

    Close();

    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;

    swI16 size = SwFile::GetSize(path);
    m_file = SwFopen(path, FMD_R);

    if (m_file)
        m_size = size;

    return true;
}

bool SwMediaStream::Open(swUI16 moduleId, const char * mediaId)
{
    Close();

    if (moduleId == NODE_ID_INVALID_16 || !mediaId)
        return false;

    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;

    swUI16 pos = SwApplicationInterface::GetModuleManager().FindByMID(moduleId);

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

    m_size = (swI64) m_mediaNode->GetSize(m_module->m_file, m_module->m_header.itemdataLocator, 0);

    return true;
}

void SwMediaStream::Close()
{
    if (m_file)
    {
        fclose(m_file);
        m_file = NULL;
    }

    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;
}

swI64 SwMediaStream::read(void *data, swI64 size)
{
    if (!data)
        return 0;

    swUI32 bytesRead = 0;

    if (m_file)
    {
        bytesRead =  fread(data, 1, size, m_file);
    }
    else if (m_module && m_mediaNode)
    {
        bytesRead = m_mediaNode->ReadStream(m_module->m_file, data, m_module->m_header.itemdataLocator, m_module->m_header.filecontentsLocator, m_position, size, m_module->m_header.k1, m_module->m_header.k2, m_module->m_header.isEncrypted);
    }

    m_position += bytesRead;

    return bytesRead;
}

swI64 SwMediaStream::seek(swI64 offset, int origin)
{
    if (m_file)
    {
        fseek(m_file, offset, origin);
        m_position = (swI64) ftell(m_file);
        return m_position;
    }

    if (origin == SEEK_SET)
        m_position = offset;
    else if (origin == SEEK_CUR)
        m_position = m_position + offset;

    if (m_position >= m_size)
        m_position = m_size - 1;

    return m_position;
}

swI64 SwMediaStream::tell()
{
    if (m_file)
        return (swI64) ftell(m_file);

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

    if (!m_stream.Open(managerId, src))
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
