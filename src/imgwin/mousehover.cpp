///////////////////////////////////////////////////////////////////
// Name:        mousehover.cpp
// Purpose:     Handle mouse hover events.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"
#include "../../include/geo/geolocation.h"

void SwImageWindow::OnMouseHover(wxPoint & clientPos)
{
    if (!m_enableAutoDef)
        m_autodefwindow->Hide();

    if (!m_showTips)
        m_tipWindow->Hide();

    if (!m_enableAutoDef && !m_showTips)
        return;

    wxPoint scrollPos = GetViewStart();

    bool tiploaded = false;
    swUI32 nodeId;
    SwMapItemData itemData;
    bool isGeo = false;

    SwPoint pt;
    pt.x = clientPos.x;
    pt.y = clientPos.y;
    SwRect rc;
    wxSize cs = GetClientSize();
    rc.width = cs.GetWidth();
    rc.height = cs.GetHeight();
    rc.x = 0;
    rc.y = 0;

    nodeId = CheckDrawAreas(itemData, pt, scrollPos, rc);

    if (nodeId != NODE_ID_INVALID)
    {
        m_ishotspotdrawArea = true;
    }

    if (nodeId == NODE_ID_INVALID)
    {
        nodeId = CheckImageMaps(itemData, pt, scrollPos, rc);
        if (nodeId != NODE_ID_INVALID)
        {
            m_ishotspotdrawArea = false;
        }
    }

    if (nodeId == NODE_ID_INVALID && m_mapList.GetUseGeo())
    {
        nodeId = SwGeo::IdentifyLocation(pt, m_mapList.GetConversionData());
        if (nodeId != NODE_ID_INVALID)
            isGeo = true;
    }

    SetHotCursor(itemData.ishot);

    if (nodeId == NODE_ID_INVALID)
    {
        m_autodefwindow->Hide();
        m_tipWindow->Hide();
    }
    else
    {
        if (m_enableAutoDef)
        {
            if (isGeo)
            {
                if (itemData.hotItem && m_hotmapArea != itemData.hotItem)
                {
                    m_isautodefLoaded = LoadAutoDefText(SwGeo::GetData(nodeId).name);
                }
            }
            else
            {
                if (itemData.hotItem && m_hotmapArea != itemData.hotItem)
                {
                    m_isautodefLoaded = LoadAutoDefText(*itemData.hotItem);
                }
            }

            if (m_isautodefLoaded)
            {
                ShowAutoDef(clientPos.y, clientPos.y);
            }
        }
    }

    if (m_showTips && !m_autodefwindow->IsShown())
    {
        if (isGeo)
        {
            tiploaded = LoadTipText(SwGeo::GetData(nodeId).name);
        }
        else
        {
            if (itemData.hotItem && m_hotmapArea != itemData.hotItem)
            {
                tiploaded = LoadTipText(*itemData.hotItem);
            }
        }

        if (tiploaded)
        {
            ShowTip(clientPos);
        }
    }

    m_hotMap = itemData.hotMap;
    m_hotmapArea = itemData.hotItem;
}
