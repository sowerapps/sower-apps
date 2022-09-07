///////////////////////////////////////////////////////////////////
// Name:        transcryptor.cpp
// Purpose:     Encryption, and decryption for Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/module/transcryptor.h"

swUI8 SwTranscryptor::GetNumber(swUI8 min, swUI8 max, bool modify)
{
    if (!SwApplicationInterface::GetEncryptor())
        return 0;

    return SwApplicationInterface::GetEncryptor()->Generate8BitKey(min, max, modify);
}

swUI32 SwTranscryptor::Generate(swUI8 k1)
{
    if (!SwApplicationInterface::GetEncryptor())
        return 0;

    return SwApplicationInterface::GetEncryptor()->Generate32BitKey(k1);
}

size_t SwTranscryptor::decryptfread(void * buffer, size_t size, size_t count, FILE *stream, const swUI8 k1, const swUI32 k2)
{
    if (!SwApplicationInterface::GetDecryptor())
        return 0;

    return SwApplicationInterface::GetDecryptor()->DecryptedRead(buffer, size, count, stream, k1, k2);
}

size_t SwTranscryptor::encryptfwrite(const void * buffer, size_t size, size_t count, FILE *stream, const swUI8 k1, const swUI32 k2)
{
    if (!SwApplicationInterface::GetEncryptor())
        return 0;

    return SwApplicationInterface::GetEncryptor()->EncryptedWrite(buffer, size, count, stream, k1, k2);
}
