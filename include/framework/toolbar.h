///////////////////////////////////////////////////////////////////
// Name:        toolbar.h
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERTOOLBAR_H
#define SOWERTOOLBAR_H

#include "../sowerbase.h"
#include "guidata.h"
#include "frame.h"
#include "../plugin/plugin.h"
#include <wx/aui/auibar.h>
#include <wx/toolbar.h>

#if !defined __USE_WXAUI_TOOLBAR__ && !defined __USE_WXTOOLBAR__
#define __USE_WXAUI_TOOLBAR__
#endif

#ifdef __USE_WXAUI_TOOLBAR__
#define SW_TOOLBAR_DEFAULT_STYLE wxAUI_TB_DEFAULT_STYLE
#define SwToolBarItem wxAuiToolBarItem
#else
#define SW_TOOLBAR_DEFAULT_STYLE wxTB_DEFAULT_STYLE
#define SwToolBarItem wxToolBarToolBase
#endif // __USE_WXAUI_TOOLBAR__

class SwFrame;

typedef void (SwFrame::*SwToolBarEventHandler)(wxCommandEvent & event);

#ifdef __USE_WXAUI_TOOLBAR__
class SOWERBASEEXP SwToolBar : public wxAuiToolBar
#else
class SOWERBASEEXP SwToolBar : public wxToolBar
#endif
{
public:
    SwToolBar();
    SwToolBar(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &position=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxAUI_TB_DEFAULT_STYLE, bool primary = false, SwFrame * frame = NULL);
    virtual ~SwToolBar() {}
    virtual void OnResize(wxSizeEvent& event);
    int GetItemCount();
    SwToolBarItem * Find(int id);
    #ifdef __USE_WXTOOLBAR__
    void AddSpacer(int i) { return; }
    #endif
    void SetFrameWindow(SwFrame * frame);
    void OnEvent(wxCommandEvent & event);
    SwToolBarItem * AddStockItem(swUI8 swid, bool enable, bool addSeparators);
    void EnableItem(swUI8 swid, bool enable);
    bool IsItemEnabled(swUI8 swid);
    void CheckItem(swUI8 swid, bool check);
    bool IsItemChecked(swUI8 swid);
    const wchar_t * GetItemLabel(swUI8 swid);
    void SetCustomToolBitmap(int wxid, const char * strid);
    void SetCustomToolLabel(int wxid, const char * strid, const wchar_t * deflabel);
    virtual void Reset() { m_lastgroup = SW_MENUID_UNKNOWN; }
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnFontSizeChange(wxFont & font);
    virtual void UpdateGui();

protected:
    swUI8 m_lastgroup;
    SwFrame * m_frame;
    SwToolBarEventHandler m_eventHandlers[N_SW_GUIITEM_IDS];
};

class SOWERBASEEXP SwBasicToolBar : public SwToolBar
{
public:
    SwBasicToolBar();
    SwBasicToolBar(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &position=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxAUI_TB_DEFAULT_STYLE, bool primary = false, SwFrame * frame = NULL);
    virtual ~SwBasicToolBar() {}

    virtual void EnableItems(bool state);
};

class SOWERBASEEXP SwUtilityToolBar : public SwToolBar
{
public:
    SwUtilityToolBar();
    SwUtilityToolBar(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &position=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxAUI_TB_DEFAULT_STYLE, bool primary = false, SwFrame * frame = NULL);
    virtual ~SwUtilityToolBar() {}

    virtual void EnableItems(bool state);
};

class SOWERBASEEXP SwEditorToolBar : public SwToolBar
{
public:
    SwEditorToolBar();
    SwEditorToolBar(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &position=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxAUI_TB_DEFAULT_STYLE, bool primary = false, SwFrame * frame = NULL);
    virtual ~SwEditorToolBar() {}

    virtual void EnableItems(bool state);
};

#endif // SOWERTOOLBAR_H
