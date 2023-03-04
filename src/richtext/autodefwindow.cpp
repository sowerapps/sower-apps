///////////////////////////////////////////////////////////////////
// Name:        autodefwindow.cpp
// Purpose:     Implementation of AutoDefWindows.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/autodefwindow.h"

SwAutoDefWindow::SwAutoDefWindow()
{
    SetEditable(false);
    m_delay = 0;
    m_menuVisible = false;
    m_viewMenu = (SwMenu *) new SwAutoDefMenu(this);
    SetMargins(3);
}

SwAutoDefWindow::SwAutoDefWindow(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
:SwAutoDefBase(parent, id, value, pos, size, style | wxBORDER_SIMPLE, validator, name)
{
    m_delay = 0;
    m_menuVisible = false;
    SetEditable(false);
    m_viewMenu = (SwMenu *) new SwAutoDefMenu(this);
    SetMargins(3);
}

SwAutoDefWindow::~SwAutoDefWindow()
{
}

void SwAutoDefWindow::ShowAutoDef(int top, int bottom)
{
    if (!m_enabled /*|| !GetParent()->HasFocus()*/ || m_menuVisible)
        return;

    wxSize clientSize = GetParent()->GetClientSize();
    SetSize(0, 0, clientSize.GetWidth(), clientSize.GetHeight(), wxSIZE_FORCE);

    LayoutContent();
    ForceDelayedLayout();

    wxPoint ptl;
    wxRichTextLine * line = GetBuffer().GetLineAtPosition(GetLastPosition());
    if (line)
    {
        ptl = line->GetAbsolutePosition();
        ptl.y += line->GetSize().GetHeight() + 7;
    }

//    wxSize virtualSize = GetVirtualSize();
    wxRect rect;

    rect.x = 0;
    rect.width = clientSize.GetWidth();

    if (top > clientSize.y - bottom)
    {
        if (ptl.y/*virtualSize.GetHeight()*/ > top)
        {
            rect.y = 0;
            rect.SetHeight(top);
        }
        else
        {
            rect.y = top - ptl.y/*virtualSize.GetHeight()*/;
            rect.SetHeight(ptl.y/*virtualSize.GetHeight()*/);
        }
    }
    else
    {
        if (ptl.y/*virtualSize.GetHeight()*/ > clientSize.GetHeight() - bottom)
        {
            rect.y = bottom;
            rect.SetHeight(clientSize.GetHeight() - bottom);
        }
        else
        {
            rect.y = bottom;
            rect.SetHeight(ptl.y/*virtualSize.GetHeight()*/);
        }
    }

    SetSize(rect, wxSIZE_FORCE);
    Show();
    m_mousePos = wxGetMousePosition();
    m_delay = 7;
}

void SwAutoDefWindow::OnTimer(bool flag)
{
    if (m_menuVisible)
    {
        return;
    }

    if (m_delay && m_mousePos != wxGetMousePosition())
    {
        m_delay --;
        return;
    }

    bool status;
    wxRect rect = GetScreenRect();
    wxPoint point = wxGetMousePosition();
    status = rect.Contains(point);
    if (!status && !SwAutoDefBase::IsMouseInWindow(this) && m_mousePos != wxGetMousePosition())
    {
        //m_mousePos = wxGetMousePosition();
        Hide();
    }

    m_mousePos = wxGetMousePosition();
    SwRichTextCtrl::OnTimer(flag);
}

bool SwAutoDefWindow::ShowContextMenu(wxMenu *menu, const wxPoint &pt, bool addPropertyCommands)
{
    m_viewMenu->EnableItem(SW_GUIID_COPY, m_canCopy && HasSelection());
    m_viewMenu->EnableItem(SW_GUIID_PRINT, m_canCopy);

    if (m_viewMenu)
    {
        m_menuVisible = true;
        bool result =  SwRichTextCtrl::ShowContextMenu(m_viewMenu, pt, addPropertyCommands);
        m_delay = 5;
        m_menuVisible = false;
        return result;
    }

    return wxRichTextCtrl::ShowContextMenu(menu, pt, addPropertyCommands);
}

void SwAutoDefWindow::SetBaseStyle()
{
    wxRichTextAttr attr;
    attr.SetFontSize(SwApplicationInterface::GetAutoDefFontSize());
    SetDefaultStyle(attr);
}

void SwAutoDefWindow::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();
}

void SwAutoDefWindow::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();
}
