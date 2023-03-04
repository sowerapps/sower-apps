///////////////////////////////////////////////////////////////////
// Name:        plugin.h
// Purpose:     Base class for Sower plug-ins, and plug-in manager.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef PLUGIN_H
#define PLUGIN_H

#include "../sowerbase.h"
#include "../appi/appifa.h"
#include "../framework/panel.h"
#include "../av_media/mediadevice.h"
#include <wx/wx.h>
#include <wx/dynlib.h>
#include <wx/simplebook.h>

#if defined __MSWIN__
#define PLUGEXT     "dll"
#define WPLUGEXT    L"dll"
#endif // __MSWIN__

#if defined __linux__
#define PLUGEXT     "so"
#define WPLUGEXT    L"so"
#endif // __linux___

#if defined __OSX__
#define PLUGEXT     "dylib"
#define WPLUGEXT    L"dylib"
#endif // __OSX___

#ifndef PLUGEXT
#define PLUGEXT     "so"
#define WPLUGEXT    L"so"
#endif // PLUGEXT

enum PLUG_IN_TYPE
{
    PIT_UNKNOWN,
    PIT_INTERFACE,
    PIT_MODULE,
    PIT_VIEWER,
    PIT_EDITOR,
    PIT_TOOL,
    PIT_DEVICE_AUDIO,
    PIT_DEVICE_VIDEO,
    PIT_TRANSCRYPTOR,
    PIT_ENCRYPTOR,
    PIT_DECRYPTOR,
    PIT_IMPORT,
    PIT_EXPORT
};

class SwToolBook;
class SOWERBASEEXP SwPlugIn
{
public:
    SwPlugIn();
    virtual ~SwPlugIn();

    virtual swUI8 GetVersion();
    virtual swUI8 GetType();
    virtual const char * GetName();
    virtual const char * GetDescription();
    virtual void OnInitialize();
    virtual void OnUnInitialize();
    virtual void OnInitializeTool();
    virtual bool CanClose();
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnFontSizeChange();
    virtual void OnEnable();
    virtual void OnDisable();
    virtual bool CanHandle(swUI8 type){ return false; }
    virtual bool AddTool(SwToolBook * book){ return false; }
    virtual bool AddViewer(swUI8 type, wxSimplebook * book) { return false; }
    virtual bool CanHandle(const char * extension){ return false; }
    // Extension list should use '|' as separator.
    virtual const char * GetExtensions() { return ""; }
    SwMediaDevice * GetMediaDevice(SwPanel * panel = NULL) { return NULL; }

    virtual swUI8 Generate8BitKey(swUI8 min, swUI8 max, bool modify = false) { return 0; }
    virtual swUI32 Generate32BitKey(swUI8 k1) { return 0; }
    virtual size_t DecryptedRead(void * buffer, size_t size, size_t count, FILE *stream, const swUI8 k1, const swUI32 k2) { return 0; }
    virtual size_t EncryptedWrite(const void * buffer, size_t size, size_t count, FILE *stream, const swUI8 k1, const swUI32 k2) { return 0; }


    wxDynamicLibrary * m_dll;
};

typedef SwPlugIn * (* _PlugInInitialize)();

class SOWERBASEEXP SwPlugInManager
{
public:
    SwPlugInManager();
    virtual ~SwPlugInManager();

    void Reset();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    bool AddLibrary(wxDynamicLibrary * dll);
    void SetAt(swUI32 pos, SwPlugIn * plugin);
    SwPlugIn * GetAt(swUI16 pos);
    static swUI8 GetType(wxDynamicLibrary * dll);
    bool SetInterfacePlugIn(SwPlugIn * plugin, bool callInitialize = true);
    bool SetInterfacePlugIn(swUI16 pos, bool callInitialize = true);
    SwPlugIn * GetInterfacePlugIn();
    void OnInitialize(swUI8 type);
    void OnInitialize();
    void OnUnInitialize(swUI8 type);
    void OnUnInitialize();
    void OnInitializeTools();
    bool CanClose();
    void OnLanguageChange();
    void OnThemeChange();
    void OnFontSizeChange();
    swUI16 FindPlugIn(const char * name, swUI16 start = 0);
    swUI16 FindPlugIn(swUI8 pittype, swUI16 start = 0);
    bool AreplugInsInitialized();
    void SetCount(swUI16 count);
    swUI16 GetCount();
    swUI16 FindFirstInterface();
    swUI8 GetLoadType() { return m_loadType; }
    void SetLoadType(swUI8 pittype) { m_loadType = pittype; }
    swUI16 FindFileHandler(const char * extension);
    void GetExtensions(SwStringArray & array);

protected:
    SwPlugIn ** m_array;
    SwPlugIn *  m_interface;
    swUI16      m_count;
    swUI16      m_size;
    bool        m_pluginsInitialized;
    swUI8       m_loadType;
};

#endif // PLUGIN_H
