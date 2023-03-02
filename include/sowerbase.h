///////////////////////////////////////////////////////////////////
// Name:        sowerbase.h
// Purpose:     SowerBase primary include file &
//              SowerWxInit provides entry point required when using
//              wxWidgets in a shared object on linux.
//              SowerApp - initializes Sower wxWidgets apps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef __SOWERBASE_H__
#define __SOWERBASE_H__

#if defined __MSWIN__
#define OS_STRING "MSW"
#if defined BUILDSOWERBASE
#define SOWERBASEEXP __declspec(dllexport)
#else
#define SOWERBASEEXP __declspec(dllimport)
#endif // BUILDSOWERBASE
#else
#define SOWERBASEEXP
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <wx/app.h>
#include <wx/wx.h>
#include <wx/clntdata.h>
#include <wx/richtext/richtextbuffer.h>

#if defined __linux__
#define OS_STRING "Linux"
#define stricmp strcasecmp
#define wcsicmp wcscasecmp
#define _stat stat
char *strlwr(char *str);
wchar_t *wcslwr(wchar_t *str);
char *strupr(char *str);
wchar_t *wcsupr(wchar_t *str);
#endif // __linux__

#if defined __OSX__
#define OS_STRING "OSX"
#define stricmp strcasecmp
#define wcsicmp wcscasecmp
#define _stat stat
char *strlwr(char *str);
wchar_t *wcslwr(wchar_t *str);
char *strupr(char *str);
wchar_t *wcsupr(wchar_t *str);
#endif // defined __OSX__

typedef signed char swI8;
typedef unsigned char swUI8;
typedef signed short swI16;
typedef unsigned short swUI16;
typedef signed int swI32;
typedef unsigned int swUI32;
typedef signed long long swI64;
typedef unsigned long long swUI64;
typedef double swFloat;

#ifndef MAX_PATH
#define MAX_PATH 260
#endif // MAX_PATH

#define NODE_ID_INVALID             0xFFFFFFFF
#define NODE_ID_INVALID_16          0xFFFF
#define NODE_ID_INVALID_8           0xFF

#define SOFTWAREVERSIONMAJOR 1
<<<<<<< Updated upstream
#define SOFTWAREVERSIONMINOR 1
#define SVSTR L"1.1"
=======
#define SOFTWAREVERSIONMINOR 3
#define SVSTR L"1.3"
>>>>>>> Stashed changes

#define UNIT_CHOICE_WIDTH 50

class SOWERBASEEXP SowerWxInit
{
    public:
    SowerWxInit();
    virtual ~SowerWxInit();
};

class SOWERBASEEXP SwBaseApp : public wxApp
{
    public:
        SwBaseApp();
        virtual ~SwBaseApp();
};

struct SwPoint
{
    swI32 x, y;
    void operator=(const SwPoint & pt) { x = pt.x; y = pt.y;}
};

struct SwRect
{
    swI32 width, height, x, y;
};

struct SwTextRange
{
    swI32 begin, end;

    void Reset() { begin = -1; end = -1; }
    wxRichTextParagraphLayoutBox * parent;
};

class SOWERBASEEXP SwClientData : public wxClientData
{
public:
    SwClientData();
    SwClientData(wxUint32 data);
    virtual ~SwClientData();

    void SetData(wxUint32 data);
    wxUint32 GetData();
    void SetHiWord(wxUint16 data);
    wxUint16 GetHiWord();
    void SetLoWord(wxUint16 data);
    wxUint16 GetLoWord();
    void SetHiByte(wxUint8 data, bool lowWord = true);
    wxUint8 GetHiByte(bool lowWord = true);
    void SetLoByte(wxUint8 data, bool lowWord = true);
    wxUint8 GetLoByte(bool lowWord = true);

    wxUint32 m_data;
};

class SOWERBASEEXP SwScrollData
{
public:
    SwScrollData() {}
    SwScrollData(swUI32 v, swUI32 h) { vpos = v; hpos = h; }

    virtual ~SwScrollData() {}

    void operator = (SwScrollData scrolldata)
    {
        vpos = scrolldata.vpos;
        hpos = scrolldata.hpos;
    }

    void Reset()
    {
        vpos = 0;
        hpos = 0;
    }

    swUI32 vpos;
    swUI32 hpos;
};


static const swFloat swpi = 3.14159265358979323846;

#endif // __SOWERBASE_H__
