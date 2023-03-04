///////////////////////////////////////////////////////////////////
// Name:        events.cpp
// Purpose:     Mouse button events.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

void SwImageWindow::OnLeftDown(wxMouseEvent& event)
{
    wxPoint mousePos = wxGetMousePosition();
    wxPoint clientPos = ScreenToClient(mousePos);
    m_leftdownmapArea = m_hotmapArea;
    bool canCopy;

    if (m_enableAutoDef && m_hotmapArea)
    {
        m_autodefText.Copy(m_hotmapArea->GetHref());
        m_isautodefLoaded = SwApplicationInterface::GetModuleManager().GetAutoDefData(m_buffer, m_autodefText.GetArray(), canCopy);

        if (m_isautodefLoaded)
        {
            m_autodefwindow->SetCanCopy(canCopy);
            ShowAutoDef(clientPos.y, clientPos.y);
        }
    }

    event.Skip();
}

void SwImageWindow::OnLeftUp(wxMouseEvent& event)
{
    if (m_isHot && m_allowclickActivate && m_leftdownmapArea == m_hotmapArea && m_leftdownmapArea->isclickItem)
    {
        if (m_eventHandler)
            m_eventHandler->OnImageHotSpotLeftClick(this, m_hotmapArea);
        else
            OnLeftClick(m_hotmapArea);
    }

    event.Skip();
}

void SwImageWindow::OnRightDown(wxMouseEvent& event)
{
    m_rightdownMap = m_hotMap;
    m_rightdownmapArea = m_hotmapArea;
    m_dragPoint = ScreenToClient(wxGetMousePosition());

    if (!m_ishotspotdrawArea && m_hotmapArea && m_allowDrag)
    {
        SetCursor(wxCURSOR_CROSS);
        m_isdragging = true;
    }

    event.Skip();
}

void SwImageWindow::OnRightUp(wxMouseEvent& event)
{
    if (m_isdragging)
        SetCursor(*wxSTANDARD_CURSOR);

    wxPoint screenPoint = ScreenToClient(wxGetMousePosition());

    if (m_isdragging && m_allowDrag && m_rightdownmapArea && screenPoint != m_dragPoint)
    {
        UpdateDragMapList();
    }
    else if (m_showMenu && screenPoint == m_dragPoint)
    {
        ShowMenu();
    }

    m_isdragging = false;
    event.Skip();
}

void SwImageWindow::OnMouseMove(wxMouseEvent& event)
{
    char buf[1000];
    SwPoint point;
    wxPoint mousePos = ScreenToClient(wxGetMousePosition());

    SwScrollData sc;
    GetScrollPosition(sc);
    point.x = (mousePos.x / m_zoom) + sc.hpos;
    point.y = (mousePos.y / m_zoom) + sc.vpos;
    if (SwApplicationInterface::GetFrameWindow() && SwApplicationInterface::GetFrameWindow()->GetStatusBar() && m_iseditMode)
    {
        if (m_image)
        {
            sprintf(buf, "x:%i, y:%i", point.x, point.y);
            SwApplicationInterface::GetFrameWindow()->GetStatusBar()->SetStatusText(buf);
        }

    }

    event.Skip();
}
