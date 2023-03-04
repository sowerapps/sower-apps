///////////////////////////////////////////////////////////////////
// Name:        splashscreen.cpp
// Purpose:     Splashscreen for Sower applications.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/splashscreen.h"

SwSplashScreen::SwSplashScreen(long splashStyle, int milliseconds, wxFrame* parent)
    : wxSplashScreen (SwApplicationInterface::GetStockImage(IMG_SPLASH),  splashStyle, milliseconds, parent, wxID_ANY)
{
}

SwSplashScreen::~SwSplashScreen()
{
    if (GetParent())
    {
        wxFrame * frame = (wxFrame *) GetParent();
        frame->Show();
    }
}

void SwSplashScreen::SetText(const wchar_t * appname, const wchar_t * copyrightYear)
{
    if (!appname || !copyrightYear)
        return;

    wxBitmap bitmap(SwApplicationInterface::GetStockImage(IMG_SPLASH));
    wchar_t s[200];

    wxMemoryDC dc;
    wxFont thisFont(14,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);

    dc.SetFont(thisFont);
    dc.SelectObject(bitmap);
    dc.SetBackgroundMode(wxTRANSPARENT);
    dc.SetTextForeground(wxColour("STEEL BLUE"));

    // Note: If text is not being displayed correctally look at '%s, and %S'.
#if defined __MSWIN__
    swprintf(s, L"%S %u.%u", appname, SOFTWAREVERSIONMAJOR, SOFTWAREVERSIONMINOR);
#else
    swprintf(s, 200, L"%S %u.%u", appname, SOFTWAREVERSIONMAJOR, SOFTWAREVERSIONMINOR);
#endif

    dc.DrawLabel (s, wxRect(3, 201, 434, 23), wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL);

    thisFont.SetPointSize(7);
    thisFont.SetWeight(wxFONTWEIGHT_NORMAL);
    dc.SetFont(thisFont);
    dc.SetTextForeground(*wxBLACK);


#if defined __MSWIN__
    swprintf(s, L"%S (c) %S, DNR", SwApplicationInterface::GetControlString("SID_COPYRIGHT", L"Copyright"), copyrightYear);
#else
    swprintf(s, 200, L"%S (c) %S, DNR", SwApplicationInterface::GetControlString("SID_COPYRIGHT", L"Copyright"), copyrightYear);
#endif

    dc.DrawLabel (s, wxRect(0, 201, 431, 23), wxALIGN_RIGHT|wxALIGN_BOTTOM);

    dc.SelectObject(wxNullBitmap);
    m_window->SetBitmap(bitmap);
    m_window->Refresh();
    ::wxYield();
    m_window->Update();
}
