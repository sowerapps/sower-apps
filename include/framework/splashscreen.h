///////////////////////////////////////////////////////////////////
// Name:        splashscreen.h
// Purpose:     Splashscreen for Sower applications.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERSPLASHSCREEN_H
#define SOWERSPLASHSCREEN_H

#include <wx/splash.h>
#include "../appi/appifa.h"

class SOWERBASEEXP SwSplashScreen : public wxSplashScreen
{
    public:
    SwSplashScreen(long splashStyle, int milliseconds, wxFrame* parent);
    virtual ~SwSplashScreen();
    void SetText(const wchar_t * appname, const wchar_t * copyrightYear);
};

#endif // SOWERSPLASHSCREEN_H
