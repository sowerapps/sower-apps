///////////////////////////////////////////////////////////////////
// Name:        sowerapp.h
// Purpose:     Sower
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERAPP_H
#define SOWERAPP_H

#include "framework/frame.h"

class SowerApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerAppFrame : public SwFrame
{
public:
    SowerAppFrame() {}
    SowerAppFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SowerAppFrame();

    virtual bool OnCanDoOpen() { return true; }
    virtual bool OpenFile(const char * path, bool addtorecent);
    virtual void OpenRecent(swUI8 pos);
    virtual void OnOpen(wxCommandEvent & event);
    virtual void OnFile1(wxCommandEvent & event);
    virtual void OnFile2(wxCommandEvent & event);
    virtual void OnFile3(wxCommandEvent & event);
    virtual void OnFile4(wxCommandEvent & event);
    virtual void OnFile5(wxCommandEvent & event);
    virtual void OnFile6(wxCommandEvent & event);
    virtual void OnFile7(wxCommandEvent & event);
    virtual void OnFile8(wxCommandEvent & event);
    virtual void OnFile9(wxCommandEvent & event);
    virtual void OnFile10(wxCommandEvent & event);
    virtual bool HasLibraryView() { return true; }
    virtual bool HasBookmarksView() { return true; }
    virtual void OnBookmarksView(wxCommandEvent & event);
    virtual void OnLibraryView(wxCommandEvent & event);
    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool LoadPerspective(const char * id, const char * perspective);
    virtual void SaveUserData();
    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnQuit(wxCommandEvent & event);
    virtual void OnPreferences(wxCommandEvent& event);
    virtual void OnSelectInterface(wxCommandEvent & event);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
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
    virtual void OnFrameTimer();

    static const long ID_TOOLBAR;
    static const long ID_POSITIONSLIDER;
    static const long ID_VOLUMESLIDER;
    static const long ID_LOOPCHECKBOX;

private:
    SwBasicViewMenu * m_basicviewMenu;
    wxSlider *        m_PositionSlider;
    wxSlider *        m_VolumeSlider;
    wxCheckBox *      m_LoopCheckBox;
    bool              m_startup;
    bool              m_skip;
};

#endif // SOWERAPP_H
