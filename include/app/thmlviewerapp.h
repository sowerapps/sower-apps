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
    virtual void OnFrameTimer();
    virtual void ProcessCmdLine();
    virtual void OnAudioOpen();
    virtual void OnVolumeSliderScroll(wxScrollEvent& event);
    virtual void OnPositionSliderThumb(wxScrollEvent& event);
    virtual void OnPositionSliderThumbRelease(wxScrollEvent& event);
    virtual bool OnCanDoPlay();
    virtual bool OnCanDoPause();
    virtual bool OnCanDoStop();
    virtual void OnPlay(wxCommandEvent& event);
    virtual void OnPause(wxCommandEvent& event);
    virtual void OnStop(wxCommandEvent& event);

    static const long ID_TOOLBAR;
    static const long ID_POSITIONSLIDER;
    static const long ID_VOLUMESLIDER;
    static const long ID_LOOPCHECKBOX;

private:
    wxSlider *        m_PositionSlider;
    wxSlider *        m_VolumeSlider;
    wxCheckBox *      m_LoopCheckBox;
    bool              m_startup;
    bool              m_skip;
};

#endif // THMLVIEWERAPP_H
