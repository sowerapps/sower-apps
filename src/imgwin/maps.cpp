///////////////////////////////////////////////////////////////////
// Name:        maps.cpp
// Purpose:     Locate active map area.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

swUI32 SwImageWindow::CheckDrawAreas(SwMapItemData & itemData, SwPoint & pt, wxPoint & scrollPos, SwRect & rc)
{
    swUI32 nodeId = m_drawAreas.FindMapAreaByPos(pt, 1, scrollPos.x, scrollPos.y, /*GetClientSize()*/ rc, m_zoom);

    if (nodeId != NODE_ID_INVALID)
    {
        itemData.hotItem = m_drawAreas.GetMapData(nodeId);
        itemData.hotMap = &m_drawAreas;
        itemData.ishot = m_drawAreas.GetMapData(nodeId)->isclickItem;
        return nodeId;
    }

    return NODE_ID_INVALID;
}

swUI32 SwImageWindow::CheckImageMaps(SwMapItemData & itemData, SwPoint & pt, wxPoint & scrollPos, SwRect & rc)
{
    swUI32 map = 0;
    swUI32 nodeId = NODE_ID_INVALID;

    while (map < m_mapList.GetMapCount())
    {
        nodeId = m_mapList.m_mapArray[map]->FindMapAreaByPos(pt, m_zoom, scrollPos.x, scrollPos.y, /*GetClientSize()*/ rc, m_zoom);

        if (nodeId != NODE_ID_INVALID)
        {
            itemData.hotItem = m_mapList.GetMap(map)->GetMapData(nodeId);
            itemData.hotMap = m_mapList.GetMap(map);
            itemData.ishot = m_mapList.GetMap(map)->GetMapData(nodeId)->isclickItem;
            break;
        }

        map ++;
    }

    return nodeId;
}

void SwImageWindow::OnMarkItem(wxCommandEvent& event)
{
    if (m_rightdownmapArea)
        m_rightdownmapArea->marked = true;

    Refresh();
}

void SwImageWindow::OnUnMarkItem(wxCommandEvent& event)
{
    if (m_rightdownmapArea)
        m_rightdownmapArea->marked = false;

    Refresh();
}
