///////////////////////////////////////////////////////////////////
// Name:        streambuffer.cpp
// Purpose:     SwStreamBuffer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/filesys/streambuffer.h"
#include "../../include/filesys/file.h"

SwStreamBuffer::SwStreamBuffer()
{
    Init();
}

SwStreamBuffer::~SwStreamBuffer()
{
    if (m_array)
        free(m_array);
}

void SwStreamBuffer::Init()
{
    m_array = NULL;
    m_size = 0;
    m_count = 0;

    if (!Size(1000))
        return;

    memset((void *) m_array, 0, 1000);
}

void SwStreamBuffer::Zero()
{
    if (!m_array)
        return;

    memset(m_array, 0, m_size);
}

void SwStreamBuffer::Reset()
{
    Size(1000);
    Zero();
    m_count = 0;
}

swUI32 SwStreamBuffer::Size(swUI32 size, bool shrink)
{
    if (!size && m_array && shrink)
    {
        free(m_array);
        m_array = NULL;
        m_size = 0;
        return 0;
    }

    if (size < 100)
        size = 100;

    if (m_array && m_size >= size && !shrink)
        return m_size;

    swUI8 * p = (swUI8 *) realloc((void *) m_array, size);

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual array size because operation failed.
    return 0;
}

swUI32 SwStreamBuffer::GetSize()
{
    return m_size;
}

swUI8 * SwStreamBuffer::GetArray()
{
    // Ensure that array exists.
    Size(100);

    return m_array;
}

SwStreamBuffer::operator void * ()
{
    return (void *) m_array;
}

SwStreamBuffer::operator char * ()
{
    return (char *) m_array;
}

SwStreamBuffer::operator unsigned char * ()
{
    return (unsigned char *) m_array;
}

void SwStreamBuffer::SetAt(swUI32 pos, swUI8 byte)
{
    if (pos >= m_size)
        return;

    m_array[pos] = byte;
}

swUI8 SwStreamBuffer::GetAt(swUI32 pos)
{
    if (pos >= m_size)
        return 0;

    return m_array[pos];
}

bool SwStreamBuffer::Load(const char * path)
{
    if (!path)
        return false;

    struct _stat st;

    if (SwFile::Stat(path, &st) == -1)
        return false;

    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    if (!Size(st.st_size))
        return false;

    if (fread((void *) m_array, 1, st.st_size, f) != (unsigned) st.st_size)
    {
        fclose(f);
        return false;
    }

    m_count = st.st_size;

    fclose(f);
    return true;
}

bool SwStreamBuffer::Write(const char * path)
{
    if (!path)
        return false;

    FILE * f = SwFopen(path, FMD_WC);

    if (!f)
        return false;

    bool status = Write(f);
    fclose(f);

    return status;
}

bool SwStreamBuffer::Write(FILE * f)
{
    if (!f)
        return false;

    fwrite((void *) m_array, 1, m_count, f);

    return true;
}

void SwStreamBuffer::SetCount(swUI32 pos)
{
    m_count = pos;
}

swUI32 SwStreamBuffer::GetCount()
{
    return m_count;
}

void SwStreamBuffer::IncrementCount(swUI32 inc)
{
    m_count += inc;
}

void SwStreamBuffer::DecrementCount(swUI32 dec)
{
    m_count -= dec;
}
