///////////////////////////////////////////////////////////////////
// Name:        transcryptor.h
// Purpose:     Encryption, and decryption for Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef TRANSCRYPTOR_H
#define TRANSCRYPTOR_H

#include "../sowerbase.h"

#define KEY_GEN_MIN 17
#define KEY_GEN_MAX 217

class SOWERBASEEXP SwTranscryptor
{
public:
    static swUI8 GetNumber(swUI8 min, swUI8 max, bool modify = false);
    static swUI32 Generate(swUI8 k1);
    static size_t decryptfread(void * buffer, size_t size, size_t count, FILE *stream, const swUI8 k1, const swUI32 k2);
    static size_t encryptfwrite(const void * buffer, size_t size, size_t count, FILE *stream, const swUI8 k1, const swUI32 k2);
};

#endif // TRANSCRYPTOR_H
