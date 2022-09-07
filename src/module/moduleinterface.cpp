///////////////////////////////////////////////////////////////////
// Name:        moduleinterface.cpp
// Purpose:     Base class for module interfacess.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/moduleinterface.h"
#include "../../include/module/transcryptor.h"
#include "../../include/array/uintarray.h"

SwModuleInterface::SwModuleInterface()
{
}

SwModuleInterface::~SwModuleInterface()
{
}

swUI32 SwModuleInterface::GetType()
{
    return MODULE_INTERFACE_TYPE_UNKNOWN;
}

bool SwModuleInterface::WriteToFile(FILE * file)
{
    return false;
}

bool SwModuleInterface::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    return false;
}

bool SwModuleInterface::ReadFromFile(FILE * file)
{
    return false;
}


bool SwModuleInterface::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    return false;
}

bool SwModuleInterface::WriteUtf16Data(FILE * file, swUI32 items, const wchar_t * buffer)
{
    if (sizeof(wchar_t) == 2)
    {
        if (fwrite((void *) buffer, sizeof(wchar_t), items, file) != items)
            return false;
    }
    else
    {
        Swui16Array utf16;
        swUI16 * data = (swUI16 *) buffer;
        utf16.Size(items);
        for (swUI32 i = 0; i < items; i++)
        {
            utf16.SetAt(i, data[(i * 2) + 0]);
        }

        if (fwrite((void *) utf16.GetArray(), sizeof(swUI16), items, file) != items)
            return false;
    }

    return true;
}

bool SwModuleInterface::WriteUtf16Data(FILE * file, swUI8 k1, swUI32 k2, swUI32 items, const wchar_t * buffer)
{

    if (sizeof(wchar_t) == 2)
    {
        if (SwTranscryptor::encryptfwrite((void *) buffer, sizeof(wchar_t), items, file, k1, k2) != items)
            return false;
    }
    else
    {
        Swui16Array utf16;
        swUI16 * data = (swUI16 *) buffer;
        utf16.Size(items);
        for (swUI32 i = 0; i < items; i++)
        {
            utf16.SetAt(i, data[(i * 2) + 0]);
        }

        if (SwTranscryptor::encryptfwrite((void *) utf16.GetArray(), sizeof(swUI16), items, file, k1, k2) != items)
            return false;
    }

    return true;
}

bool SwModuleInterface::ReadUtf16Data(FILE * file, swUI32 items, wchar_t * buffer)
{
    if (sizeof(wchar_t) == 2)
    {
        if (fread((void *) buffer, sizeof(wchar_t), items, file) != items)
            return false;
    }
    else
    {
        Swui16Array utf16;
        utf16.Size(items);

        if (fread((void *) utf16.GetArray(), sizeof(swUI16), items, file) != items)
            return false;
        for (swUI32 i = 0; i < items; i++)
        {
            buffer[i] = (wchar_t) utf16.GetAt(i);
        }
    }

    return true;
}

bool SwModuleInterface::ReadUtf16Data(FILE * file, swUI8 k1, swUI32 k2, swUI32 items, wchar_t * buffer)
{
    if (sizeof(wchar_t) == 2)
    {
        if (SwTranscryptor::decryptfread((void *) buffer, sizeof(wchar_t), items, file, k1, k2) != items)
            return false;
    }
    else
    {
        Swui16Array utf16;
        utf16.Size(items);

        if (SwTranscryptor::decryptfread((void *) utf16.GetArray(), sizeof(swUI16), items, file, k1, k2) != items)
            return false;
        for (swUI32 i = 0; i < items; i++)
        {
            buffer[i] = (wchar_t) utf16.GetAt(i);
        }
    }

    return true;
}
