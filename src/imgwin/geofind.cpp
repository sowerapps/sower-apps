///////////////////////////////////////////////////////////////////
// Name:        geofind.cpp
// Purpose:     Find functionality for locations within an image
//              of a map. Searching the alt text of SwMapArea's in
//              an ImageMap object. Optionally searching GeoLocation
//              also.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/geofind.h"
#include "../../include/geo/geolocation.h"
#include "../../include/appi/appifa.h"

SwGeoFind::SwGeoFind()
{
    m_view = NULL;
    Reset();
}

SwGeoFind::~SwGeoFind()
{
}

void SwGeoFind::Reset()
{
    m_lastfindwasGeo = false;
    m_lastfindMapNode = NODE_ID_INVALID;
    m_lastfindMapAreaNode = NODE_ID_INVALID;
    m_haveTranslation = false;
    m_original = "";
    m_translation = "";
}

void SwGeoFind::SetView(SwImageWindow * imgwin)
{
    m_view = imgwin;
}

void SwGeoFind::SetCaseSensitive(bool casesensitive)
{
    m_casesensitive = casesensitive;
    m_flags = CF_PHRASE;

    if (!casesensitive)
        m_flags |= CF_NOCASE;

    if (m_wholewordonly)
        m_flags |= CF_WORD;
}

void SwGeoFind::SetWholeWordOnly(bool wholewordonly)
{
    m_wholewordonly = wholewordonly;

    m_flags = CF_PHRASE;

    if (!m_casesensitive)
        m_flags |= CF_NOCASE;

    if (wholewordonly)
        m_flags |= CF_WORD;
}

bool SwGeoFind::Find(const char * location, bool casesensitive, bool wholewordonly)
{
    swUI32 node;
    if (!location || !m_view)
    {
        return false;
    }

    Reset();

    m_original = location;

    if (SwApplicationInterface::GetMapLanguageTableId())
    {
        node = SwApplicationInterface::GetMapLanguage().GetTable().FindItemByData(location);
        if (node != NODE_ID_INVALID)
        {
            m_translation = SwApplicationInterface::GetMapLanguage().GetTable().GetNodeId(node);
            m_haveTranslation = true;
        }
    }

    SetCaseSensitive(casesensitive);
    SetWholeWordOnly(wholewordonly);

    if (FindInImageMaps())
        return true;

    return FindInGeo();
}

bool SwGeoFind::FindInImageMaps()
{
    swUI32 startMap, startMapArea;
    bool first = false;
    SwString searchBuffer;
    SwScrollData scd;
    SwPoint point;

    if (m_lastfindwasGeo)
        return false;

    if (m_lastfindMapNode == NODE_ID_INVALID || m_lastfindMapAreaNode == NODE_ID_INVALID)
    {
        startMap = 0;
        startMapArea = 0;
        first = true;
    }
    else
    {
        startMap  = m_lastfindMapNode;
        startMapArea = m_lastfindMapAreaNode;

        if (!first)
            startMapArea ++;

        if (!m_view->GetImageMapList().GetMap(startMap))
            return false;

        if (!m_view->GetImageMapList().GetMap(startMap)->GetMapData(startMapArea))
        {
            startMap ++;
            startMapArea = 0;

            if (!m_view->GetImageMapList().GetMap(startMap) || !m_view->GetImageMapList().GetMap(startMap)->GetMapData(startMapArea))
                return false;
        }
    }

    for (swUI32 i = startMap; i < m_view->GetImageMapList().GetMapCount(); i++)
    {
        for (swUI32 node = 0; m_view->GetImageMapList().GetMap(i)->GetMapNodeCount(); node ++)
        {
            m_compObj.ParseSearchString(m_original, m_flags);
            searchBuffer = m_view->GetImageMapList().GetMap(i)->GetMapData(node)->GetAlt();

            if (m_compObj.SearchBuffer(searchBuffer) == CR_EXPRESSION_PASSED)
            {
                m_lastfindMapNode = i;
                m_lastfindMapAreaNode = node;
                m_lastfindwasGeo = false;
                point = m_view->GetImageMapList().GetMap(i)->GetMapData(node)->GetAt(0);
                scd.hpos = point.x;
                scd.vpos = point.y;

                m_view->ScrollToLocation(scd);

                return true;
            }
            else if (m_haveTranslation)
            {
                m_compObj.ParseSearchString(m_translation, m_flags);

                if (m_compObj.SearchBuffer(searchBuffer) == CR_EXPRESSION_PASSED)
                {
                    m_lastfindMapNode = i;
                    m_lastfindMapAreaNode = node;
                    m_lastfindwasGeo = false;
                    point = m_view->GetImageMapList().GetMap(i)->GetMapData(node)->GetAt(0);
                    scd.hpos = point.x;
                    scd.vpos = point.y;

                    m_view->ScrollToLocation(scd);

                    return true;
                }
            }
        }
    }

    return false;
}

bool SwGeoFind::FindInGeo()
{
    swUI32 start, status;
    SwString geoName;
    SwScrollData scd;
    SwPoint point;

    if (m_lastfindwasGeo)
        start = m_lastfindMapAreaNode + 1;
    else
        start = 0;

    for (swUI32 i = start; i < N_GEO_LOCATIONS; i ++)
    {
        geoName = SwGeo::GetData(i).name;
        m_compObj.ParseSearchString(m_original, m_flags);
        status = m_compObj.SearchBuffer(geoName);

        if (status == CR_EXPRESSION_PASSED && SwGeo::IsLocationValid(i, m_view->GetImageMapList().GetConversionData()))
        {
            m_lastfindwasGeo = true;
            m_lastfindMapAreaNode = i;
            SwGeo::CalculatePosition(m_view->GetImageMapList().GetConversionData(), SwGeo::GetData(i).coords, point);
            scd.hpos = point.x;
            scd.vpos = point.y;

            m_view->ScrollToLocation(scd);

            return true;
        }

        if (m_haveTranslation)
        {
            m_compObj.ParseSearchString(m_translation, m_flags);
            status = m_compObj.SearchBuffer(geoName);

            if (status == CR_EXPRESSION_PASSED && SwGeo::IsLocationValid(i, m_view->GetImageMapList().GetConversionData()))
            {
                m_lastfindwasGeo = true;
                m_lastfindMapAreaNode = i;
                SwGeo::CalculatePosition(m_view->GetImageMapList().GetConversionData(), SwGeo::GetData(i).coords, point);

                scd.hpos = point.x;
                scd.vpos = point.y;

                m_view->ScrollToLocation(scd);

                return true;
            }
        }
    }

    return false;
}

bool SwGeoFind::FindNext()
{
    bool status = false;

    if (!m_lastfindwasGeo)
        status = FindInImageMaps();

    if (status)
        return true;

    return FindInGeo();
}
