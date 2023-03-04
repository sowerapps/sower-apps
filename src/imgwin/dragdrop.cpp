///////////////////////////////////////////////////////////////////
// Name:        dragdrop.cpp
// Purpose:     Drag & Drop operations.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"
#include "../../include/imgwin/command.h"

void SwImageWindow::UpdateDragMapList()
{
    if (!m_rightdownmapArea)
        return;

    SwPoint point;
    wxPoint mousePos = ScreenToClient(wxGetMousePosition());

    SwScrollData sc;
    GetScrollPosition(sc);
    point.x = (mousePos.x / m_zoom) + sc.hpos;
    point.y = (mousePos.y / m_zoom) + sc.vpos;

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_mapList);
    SwImgListSwap swap1, swap2;
    mapList->GetSwapData(&swap1);
    m_mapList.GetSwapData(&swap2);
    m_mapList.Swap(&swap1);
    mapList->Swap(&swap2);
    m_rightdownmapArea->SetPointAt(0, point);
    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_mapList, mapList);
    m_commandProcessor.Submit(command);

    Refresh();
}
