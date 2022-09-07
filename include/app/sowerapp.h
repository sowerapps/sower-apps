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
    virtual bool OnCanDoClose();
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

    static const long ID_TOOLBAR;

private:
    SwBasicViewMenu * m_basicviewMenu;
    bool m_silent;
};

#endif // SOWERAPP_H
