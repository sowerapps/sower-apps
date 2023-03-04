///////////////////////////////////////////////////////////////////
// Name:        autodefwindow.h
// Purpose:     Implementation of AutoDefWindows.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUTODEFWINDOW_H
#define AUTODEFWINDOW_H

#include "../sowerbase.h"
#include "richtextctrlext.h"
#include "autodefbase.h"
#include "../framework/menubar.h"

class SwMenu;
class SOWERBASEEXP SwAutoDefWindow : public SwAutoDefBase
{
public:
    SwAutoDefWindow();
    SwAutoDefWindow(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);

    virtual ~SwAutoDefWindow();

    void ShowAutoDef(int top, int bottom);
    virtual void OnTimer(bool flag);

    virtual bool ShowContextMenu(wxMenu *menu, const wxPoint &pt, bool addPropertyCommands);
    SwAutoDefWindow * GetAutoDefWindow() { return (SwAutoDefWindow *) m_autodefWindow; }
    virtual void SetBaseStyle();

    virtual void OnLanguageChange();
    virtual void OnThemeChange();

private:
    wxPoint     m_mousePos;
    swUI8       m_delay;
    bool        m_menuVisible;
    SwMenu *    m_viewMenu;
};

#endif // AUTODEFWINDOW_H
