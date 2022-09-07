///////////////////////////////////////////////////////////////////
// Name:        moduleinterface.h
// Purpose:     Base class for module interfacess.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

#include "../module/modulebase.h"
#include <stdio.h>

struct SwAlphaData
{
    wchar_t character;
    swUI16  indexpos;

    void Reset()
    {
        character = L'\0';
        indexpos = NODE_ID_INVALID_16;
    }
};

enum MODULE_INTERFACE_TYPE
{
    // Order must not change.
    // New interface types must
    // be appended to the list.
    MODULE_INTERFACE_TYPE_UNKNOWN,
    MODULE_INTERFACE_TYPE_AUTODEFTERM,
    MODULE_INTERFACE_TYPE_AUTODEFSTRONGS,
    MODULE_INTERFACE_TYPE_AUTODEFSCRIPTURE,
    MODULE_INTERFACE_TYPE_AUTODEFCOMMENTARY,
    MODULE_INTERFACE_TYPE_MEDIACONTENTS,
    MODULE_INTERFACE_TYPE_TABLEOFCONTENTS,
    MODULE_INTERFACE_TYPE_IMAGEMAP,
    MODULE_INTERFACE_TYPE_IMAGEMAPLIST
};

class SOWERBASEEXP SwModuleInterface
{
public:
    SwModuleInterface();
    virtual ~SwModuleInterface();

    virtual swUI32 GetType();
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    static bool WriteUtf16Data(FILE * file, swUI32 items, const wchar_t * buffer);
    static bool WriteUtf16Data(FILE * file, swUI8 k1, swUI32 k2, swUI32 items, const wchar_t * buffer);
    static bool ReadUtf16Data(FILE * file, swUI32 items, wchar_t * buffer);
    static bool ReadUtf16Data(FILE * file, swUI8 k1, swUI32 k2, swUI32 items, wchar_t * buffer);
};

#endif // MODULEINTERFACE_H
