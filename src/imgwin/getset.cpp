///////////////////////////////////////////////////////////////////
// Name:        getset.cpp
// Purpose:     Access to variables.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

bool SwImageWindow::GetIsEditMode()
{
    return m_iseditMode;
}

void SwImageWindow::SetIsEditMode(bool iseditMode)
{
    m_iseditMode = iseditMode;
}

bool SwImageWindow::GetShowTips()
{
    return m_showTips;
}

void SwImageWindow::SetShowTips(bool showTips)
{
    m_showTips = showTips;
}

bool SwImageWindow::GetAllowDrag()
{
    return m_allowDrag;
}

void SwImageWindow::SetAllowDrag(bool allowDrag)
{
    m_allowDrag = allowDrag;
}

bool SwImageWindow::GetShowMenu()
{
    return m_showMenu;
}

void SwImageWindow::SetShowMenu(bool showMenu)
{
    m_showMenu = showMenu;
}

bool SwImageWindow::IsAutoDefEnabled()
{
    return m_enableAutoDef;
}

void SwImageWindow::EnableAutoDef(bool enableAutoDef)
{
    m_enableAutoDef = enableAutoDef;
}

bool SwImageWindow::GetDrawMapList()
{
    return m_drawmapList;
}

void SwImageWindow::SetDrawMapList(bool drawmapList)
{
    m_drawmapList = drawmapList;
    Refresh();
}

bool SwImageWindow::GetAllowClickActivate()
{
    return m_allowclickActivate;
}

void SwImageWindow::SetAllowClickActivate(bool allowclickActivate)
{
    m_allowclickActivate = allowclickActivate;
}

bool SwImageWindow::GetHasLocation()
{
    return m_hasLocation;
}

void SwImageWindow::SetHasLocation(bool hasLocation)
{
    m_hasLocation = hasLocation;
}

wxPoint SwImageWindow::GetLocation()
{
    return m_locationPt;
}

void SwImageWindow::SetLocation(wxPoint location)
{
    m_locationPt = location;
}

SwHtmlImageMapList & SwImageWindow::GetImageMapList()
{
    return m_mapList;
}

SwHtmlImageMap & SwImageWindow::GetDrawAreaImageMap()
{
    return m_drawAreas;
}

SwImageMapEventHandler * SwImageWindow::GetEventHandler()
{
    return m_eventHandler;
}

void SwImageWindow::SetEventHandler(SwImageMapEventHandler * eventHandler)
{
    m_eventHandler = eventHandler;
}

wxCommandProcessor & SwImageWindow::GetCommandProcessor()
{
    return m_commandProcessor;
}
