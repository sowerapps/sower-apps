///////////////////////////////////////////////////////////////////
// Name:        timer.cpp
// Purpose:     Hover timer for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

SwHoverTimer::SwHoverTimer()
{
    m_imgwin = NULL;
    Start(100);
}

SwHoverTimer::~SwHoverTimer()
{
}

void SwHoverTimer::Notify()
{
    if (m_imgwin)
        m_imgwin->OnTimer();
}

void SwImageWindow::OnTimer()
{
    if (!SwAutoDefBase::IsMouseInWindow(this) || !IsShownOnScreen())
        return;

    if (m_autodefwindow && m_autodefwindow->IsShownOnScreen())
        return;

    wxPoint mousePos = wxGetMousePosition();
    wxPoint clientPos = ScreenToClient(mousePos);

    if (clientPos == m_lastmousePos)
    {
        m_mouseCount ++;
        if (m_mouseCount > 1)
        {
            OnMouseHover(clientPos);
        }
    }
    else
    {
        m_mouseCount = 0;
        m_lastmousePos = clientPos;
    }
}
