///////////////////////////////////////////////////////////////////
// Name:        thmlviewerapp.h
// Purpose:     ThML Viewer
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLVIEWERAPP_H
#define THMLVIEWERAPP_H

#include "framework/frame.h"

class ThMLViewerApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class ThMLViewerFrame : public SwFrame
{
public:
    ThMLViewerFrame() {}
    ThMLViewerFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~ThMLViewerFrame();

    virtual void OnPreferences(wxCommandEvent& event);
    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnQuit(wxCommandEvent & event);

    virtual void OnSelectInterface(wxCommandEvent & event);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnTimer();
    virtual void ProcessCmdLine();

    static const long ID_TOOLBAR;
};

#endif // THMLVIEWERAPP_H
