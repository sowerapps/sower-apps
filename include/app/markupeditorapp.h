///////////////////////////////////////////////////////////////////
// Name:        markupeditorapp.h
// Purpose:     Sower Markup Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SWMARKUPEDITORAPP_H
#define SWMARKUPEDITORAPP_H

#include "framework/frame.h"
#include "framework/toolbar.h"

class SwMarkupEditorApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SwMarkupEditorFrame : public SwFrame
{
public:
    SwMarkupEditorFrame() {}
    SwMarkupEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SwMarkupEditorFrame();

    virtual bool OnCanDoNew() { return true; }
    virtual bool OnCanDoOpen() { return true; }
    virtual bool OnCanDoCloseAll() { return (bool) m_toolbook->GetPageCount(); }
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

    void OpenRecent(swUI8 pos);
    bool OpenFile(const char * path, bool addtorecent);
    virtual void OnNew(wxCommandEvent & event);
    virtual void OnOpen(wxCommandEvent & event);

    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnQuit(wxCommandEvent & event);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void ProcessCmdLine();

    virtual void AddToRecentFileList(const char * path);

    static const long ID_TOOLBAR;
};

#endif // SWMARKUPEDITORAPP_H
