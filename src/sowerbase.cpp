///////////////////////////////////////////////////////////////////
// Name:        sowerbase.cpp
// Purpose:     SowerWxInit provides entry point required when using
//              wxWidgets in a shared object on linux.
//              SowerApp - initializes Sower wxWidgets apps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../include/sowerbase.h"
#include <wx/stdpaths.h>

#if defined __linux__ || defined __OSX__

char *strlwr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    while (*p)
    {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

wchar_t *wcslwr(wchar_t *str)
{
    wchar_t *p = (wchar_t *)str;

    while (*p)
    {
        *p = towlower((wchar_t)*p);
        p++;
    }

    return str;
}

char *strupr(char *str)
{
    unsigned char *p = (unsigned char *)str;

    while (*p)
    {
        *p = toupper((unsigned char)*p);
        p++;
    }

    return str;
}

wchar_t *wcsupr(wchar_t *str)
{
    wchar_t *p = (wchar_t *)str;

    while (*p)
    {
        *p = towupper((wchar_t)*p);
        p++;
    }

    return str;
}
#endif // __linux__ || defined __OSX__

SowerWxInit::SowerWxInit()
{
    int i = 0;
    char ** p = NULL;
    wxEntry(i, p);
}

SowerWxInit::~SowerWxInit()
{
}

SwBaseApp::SwBaseApp()
{
    SetVendorName(L"Sower Applications");
    wxStandardPaths::Get().UseAppInfo(wxStandardPathsBase::AppInfo_VendorName);
    #if defined __linux__
    //wxStandardPaths::Get().SetFileLayout(FileLayout_XDG);
    #endif // defined __linux__
}

SwBaseApp::~SwBaseApp()
{
}

SwClientData::SwClientData()
{
    m_data = 0;
}

SwClientData::SwClientData(wxUint32 data)
{
    m_data = data;
}

SwClientData::~SwClientData()
{
}

void SwClientData::SetData(wxUint32 data)
{
    m_data = data;
}

wxUint32 SwClientData::GetData()
{
    return m_data;
}

wxUint16 SwClientData::GetHiWord()
{
    wxUint16 * p = (wxUint16 *) & m_data;
    return p[1];
}

void SwClientData::SetHiWord(wxUint16 data)
{
    wxUint16 * p = (wxUint16 *) & m_data;
    p[1] = data;
}

wxUint16 SwClientData::GetLoWord()
{
    wxUint16 * p = (wxUint16 *) & m_data;
    return p[0];
}

void SwClientData::SetLoWord(wxUint16 data)
{
    wxUint16 * p = (wxUint16 *) & m_data;
    p[0] = data;
}

wxUint8 SwClientData::GetHiByte(bool lowWord)
{
    wxUint8 * p = (wxUint8 *) & m_data;

    if (lowWord)
        return p[1];

    return p[3];
}

void SwClientData::SetHiByte(wxUint8 data, bool lowWord)
{
    wxUint8 * p = (wxUint8 *) & m_data;

    if (lowWord)
        p[1] = data;

    p[3] = data;
}

wxUint8 SwClientData::GetLoByte(bool lowWord)
{
    wxUint8 * p = (wxUint8 *) & m_data;

    if (lowWord)
        return p[0];

    return p[2];
}

void SwClientData::SetLoByte(wxUint8 data, bool lowWord)
{
    wxUint8 * p = (wxUint8 *) & m_data;

    if (lowWord)
        p[0] = data;

    p[2] = data;
}
