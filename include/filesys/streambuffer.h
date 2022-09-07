///////////////////////////////////////////////////////////////////
// Name:        streambuffer.h
// Purpose:     SwStreamBuffer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STREAMBUFFER_H
#define STREAMBUFFER_H

#include "../sowerbase.h"

class SOWERBASEEXP SwStreamBuffer
{
public:
    SwStreamBuffer();
    virtual ~SwStreamBuffer();

    void Init();
    void Zero();
    void Reset();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    swUI8 * GetArray();

    operator void * ();
    operator char * ();
    operator unsigned char * ();

    void SetAt(swUI32 pos, swUI8 byte);
    swUI8 GetAt(swUI32 pos);

    void SetCount(swUI32 pos);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

    bool Load(const char * path);
    bool Write(const char * path);
    bool Write(FILE * f);

protected:
    swUI8 *   m_array;
    swUI32    m_size;
    swUI32    m_count;
};

#endif // STREAMBUFFER_H
