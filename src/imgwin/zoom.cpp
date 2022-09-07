///////////////////////////////////////////////////////////////////
// Name:        zoom.cpp
// Purpose:     Zoom functionality for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

void SwImageWindow::OnZoomIn()
{
    SetZoom(GetZoom() + .1);
}

void SwImageWindow::OnZoomOut()
{
    SetZoom(GetZoom() - .1);
}

void SwImageWindow::OnViewNormal()
{
    SetZoom(1);
}

wxFloat32 SwImageWindow::GetZoom()
{
    return m_czoom;
}

void SwImageWindow::SetZoom(wxFloat32 zoom)
{
    if (!m_image || !m_image->IsOk())
    {
        return;
    }

    int cy, cx;

    wxUint32 zWidth = m_image->GetWidth() * m_zoom;
    wxUint32 zHeight = m_image->GetHeight() * m_zoom;
    GetViewStart(&cx, &cy);
    Freeze();

    if (m_zoom != m_czoom)
    {
        int nx = cx/m_czoom;
        int ny = cy/m_czoom;
        nx = nx * m_zoom;
        ny = ny * m_zoom;
        SetScrollbars(1, 1, zWidth, zHeight, cx, cy);
    }

    m_zoom = zoom;
    Refresh();
    Thaw();
}
