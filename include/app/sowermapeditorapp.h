///////////////////////////////////////////////////////////////////
// Name:        sowermapeditorapp.h
// Purpose:     Sower Map Editor
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMAPEDITORAPP_H
#define SOWERMAPEDITORAPP_H

#include "framework/frame.h"
#include "framework/toolbar.h"
#include "framework/menubar.h"
#include "dialogs/geodlg.h"
#include "dialogs/mapsdlg.h"
#include "dialogs/areasdlg.h"
#include "module/autodefterm.h"
#include "imgwin/imagewindow.h"

class SowerMapEditorApp : public SwBaseApp
{
    public:
        virtual bool OnInit();
};

class SowerMapEditorFrame : public SwFrame
{
public:
    SowerMapEditorFrame() {}
    SowerMapEditorFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE, const wxString &name=wxFrameNameStr);
    virtual ~SowerMapEditorFrame();

    virtual bool OnCanDoOpen() { return true; }
    virtual bool OnCanDoSave() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoClose() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoPrint() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoUndo() { return m_imageWindow->GetCommandProcessor().CanUndo(); }
    virtual bool OnCanDoRedo() { return m_imageWindow->GetCommandProcessor().CanRedo(); }
    virtual bool OnCanDoGeo() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoMaps() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoAreas() { return m_imageWindow->HasImage();  }
    virtual bool OnCanDoZoomIn() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoZoomOut() { return m_imageWindow->HasImage(); }
    virtual bool OnCanDoViewNormal() { if (m_imageWindow->GetZoom() != 1) return m_imageWindow->HasImage(); return false; }

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
    virtual void OnOpen(wxCommandEvent & event);
    virtual void OnSave(wxCommandEvent & event);
    virtual void OnClose(wxCommandEvent & event);
    virtual void OnZoomIn(wxCommandEvent & event) { m_imageWindow->OnZoomIn(); }
    virtual void OnZoomOut(wxCommandEvent & event) { m_imageWindow->OnZoomOut(); }
    virtual void OnViewNormal(wxCommandEvent & event) { m_imageWindow->OnViewNormal(); }
    virtual void OnUndo(wxCommandEvent & event) { m_imageWindow->GetCommandProcessor().Undo(); m_imageWindow->Refresh(); }
    virtual void OnRedo(wxCommandEvent & event) { m_imageWindow->GetCommandProcessor().Redo(); m_imageWindow->Refresh(); }
    virtual void OnGeo(wxCommandEvent & event) { SwGeoDlg dlg(m_imageWindow); dlg.ShowModal(); }
    virtual void OnMaps(wxCommandEvent & event) { SwMapDlg dlg(m_imageWindow); dlg.ShowModal(); }
    virtual void OnAreas(wxCommandEvent & event) { SwAreaDlg dlg(m_imageWindow); dlg.ShowModal(); }

    virtual void OnPrint(wxCommandEvent & event) { SwStringW buff; buff.Copy(m_filePath); m_imageWindow->OnPrint(buff); }
    virtual void OnAbout(wxCommandEvent & event);
    virtual void OnQuit(wxCommandEvent & event);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnTimer();
    virtual void ProcessCmdLine();

    static const long ID_TOOLBAR;
    SwImageWindow *   m_imageWindow;
    SwString          m_mapPath;
    SwString          m_filePath;
};

#endif // SOWERMAPEDITORAPP_H
