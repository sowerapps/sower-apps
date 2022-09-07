///////////////////////////////////////////////////////////////////
// Name:        scroll.cpp
// Purpose:     Scroll functionality for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

void SwImageWindow::ScrollToLocation()
{
    if (!m_hasLocation)
        return;

    wxSize clientSize = GetClientSize();
    m_painted = false;
    Scroll((m_locationPt.x * m_zoom) + (clientSize.x / 2), (m_locationPt.y * m_zoom) + (clientSize.y / 2));

    // To ensure that a new location has been drawn even if the window was not scrolled.
    if(!m_painted)
        Refresh();
}

void SwImageWindow::ScrollToLocation(SwScrollData & scrolldata)
{
    wxSize clientSize = GetClientSize();
    m_painted = false;
    Scroll((scrolldata.hpos * m_zoom) + (clientSize.x / 2), (scrolldata.vpos * m_zoom) + (clientSize.y / 2));

    // To ensure that a new location has been drawn even if the window was not scrolled.
    if(!m_painted)
        Refresh();
}

void SwImageWindow::GetScrollPosition(SwScrollData & scrolldata)
{
    int x, y;
    GetViewStart(&x, &y);
    scrolldata.hpos = x / m_zoom;
    scrolldata.vpos = y / m_zoom;
}
