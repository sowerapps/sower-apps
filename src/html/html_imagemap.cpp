///////////////////////////////////////////////////////////////////
// Name:        html_imagemap.cpp
// Purpose:     Image maps, and lists of image maps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/html_imagemap.h"
#include "../../include/html/html.h"
#include "../../include/html/html_color.h"
#include "../../include/module/transcryptor.h"
#include "../../include/appi/appifa.h"
#include "../../include/array/pointarray.h"
#include <math.h>

SwImageData::SwImageData() {}
SwImageData::~SwImageData() {}
SwImageData * SwImageData::Clone()
{
    return new SwImageData;
}

bool SwImageData::IsOk()
{
    return false;
}

int SwImageData::GetHeight()
{
    return 0;
}

int SwImageData::GetWidth()
{
    return 0;
}

SwMapArea::SwMapArea()
{
    Init();
}

SwMapArea::~SwMapArea()
{
    ReleaseBuffers();
}

void SwMapArea::Init()
{
    href = strdup("");
    alt = strdup("");
    src = strdup("");
    points = 0;
    mapPoints = NULL;
    drawColor = NO_COLOR;
    fillColor = NO_COLOR;
    isclickItem = false;
    marked = false;
    bitMap = NULL;
}

void SwMapArea::Reset()
{
    type = AREA_TYPE_CIRCLE;
    SetHref(NULL);
    SetAlt(NULL);
    SetSrc(NULL);
    drawColor = NO_COLOR;
    fillColor = NO_COLOR;
    isclickItem = false;
    marked = false;
    SetBitmap(NULL);
    SizePointArray(0);
}

void SwMapArea::ReleaseBuffers()
{
    if (alt)
        free(alt);
    alt = NULL;
    if (href)
        free(href);
    href = NULL;
    if (src)
        free(src);
    src = NULL;
    if (mapPoints)
        free(mapPoints);
    mapPoints = NULL;
    points = 0;
    if (bitMap)
        delete bitMap;
    bitMap = NULL;
}

swUI8 SwMapArea::GetType()
{
    return type;
}

void SwMapArea::SetType(swUI8 maptype)
{
    type = maptype;
}

const char * SwMapArea::GetHref()
{
    return href;
}

void SwMapArea::SetHref(const char * hrefstring)
{
    if (href)
        free(href);

    if (!hrefstring)
        hrefstring = "";

    href = strdup(hrefstring);
}

const char * SwMapArea::GetAlt()
{
    return alt;
}

void SwMapArea::SetAlt(const char * altstring)
{

    if (alt)
        free(alt);

    if (!altstring)
        altstring = "";

    alt = strdup(altstring);
}

const char * SwMapArea::GetSrc()
{
    return src;
}

void SwMapArea::SetSrc(const char * srcstring)
{
    if (src)
        free(src);

    if (!srcstring)
        srcstring = "";

    src = strdup(srcstring);
}

swUI32 SwMapArea::GetDrawColor()
{
    return drawColor;
}

void SwMapArea::SetDrawColor(const char * drawcolor)
{
    drawColor = SwHtmlColor::GetColor(drawcolor);
}

void SwMapArea::SetDrawColor(swUI32 drawcolor)
{
    drawColor = drawcolor;
}

swUI32 SwMapArea::GetFillColor()
{
    return fillColor;
}

void SwMapArea::SetFillColor(const char * fillcolor)
{
    fillColor = SwHtmlColor::GetColor(fillcolor);
}

void SwMapArea::SetFillColor(swUI32 fillcolor)
{
    fillColor = fillcolor;
}

bool SwMapArea::GetMarked()
{
    return marked;
}

void SwMapArea::MarkItem(bool state)
{
    marked = state;
}

bool SwMapArea::GetIsClickItem()
{
    return isclickItem;
}

void SwMapArea::SetIsClickItem(bool isclickitem)
{
    isclickItem = isclickitem;
}

SwImageData * SwMapArea::GetBitmap()
{
    return bitMap;
}

swUI32 SwMapArea::GetPoints()
{
    return points;
}

void SwMapArea::SetBitmap(SwImageData * bitmap)
{
    if (bitMap)
    {
        delete bitMap;
        bitMap = NULL;
    }

    if (bitmap)
//      bitMap =  new wxBitmap(bitmap->GetSubBitmap(SwRect(0, 0, bitmap->GetWidth(), bitmap->GetHeight())));
        bitMap = bitmap->Clone();
}

bool SwMapArea::SizePointArray(swUI32 npoints)
{
    if (npoints == 0)
    {
        free(mapPoints);
        mapPoints = NULL;
        points = 0;
        return true;
    }

    SwPoint * p = (SwPoint *) realloc((void *) mapPoints, sizeof(SwPoint) * npoints);

    if (p)
    {
        points = npoints;
        mapPoints = p;
        return true;
    }

    return false;
}

SwPoint SwMapArea::GetAt(swUI32 pos)
{
    SwPoint dummy;
    dummy.x = dummy.y = 0;

    if (pos >= points)
        return dummy;

    return mapPoints[pos];
}

bool SwMapArea::SetPointAt(swUI32 pos, SwPoint & point)
{
    if (pos >= points)
        return false;

    mapPoints[pos] = point;

    return true;
}

bool SwMapArea::AddPoint(SwPoint point)
{
    if (!SizePointArray(points + 1))
        return false;

    mapPoints[points - 1] = point;

    return true;
}

bool SwMapArea::RemoveLastPoint()
{
    if (!SizePointArray(points - 1))
        return false;

    return true;
}

void SwMapArea::Copy(SwMapArea & mapData)
{
    Reset();
    if (!SizePointArray(mapData.GetPoints()))
        return;
    memcpy((void *) mapPoints, mapData.mapPoints, sizeof(SwPoint) * mapData.points);
    SetType(mapData.GetType());
    SetAlt(mapData.GetAlt());
    SetHref(mapData.GetHref());
    SetSrc(mapData.GetSrc());
    SetDrawColor(mapData.GetDrawColor());
    SetFillColor(mapData.GetFillColor());
    MarkItem(mapData.GetMarked());
    SetIsClickItem(mapData.GetIsClickItem());
    // This image should be loaded during a draw operation.
    //SetBitmap(mapData.GetBitmap());
}

bool SwMapArea::InsertPointAt(swUI32 pointPos, SwPoint point)
{
    if (pointPos >= points)
        return AddPoint(point);

    if (!SizePointArray(points + 1))
        return false;

    swUI32 pos = points - 1;

    while(pos >= pointPos)
    {
        mapPoints[pos] = mapPoints[pos - 1];
        pos --;
    }

    mapPoints[pointPos] = point;

    return true;
}

bool SwMapArea::DeletePoint(swUI32 pointPos)
{
    if (pointPos >= points)
        return false;

    if (points <= 1)
    {
        if (mapPoints)
            free(mapPoints);
        mapPoints = NULL;
        points = 0;

        return true;
    }

    pointPos ++;

    while (pointPos < points)
    {
        mapPoints[pointPos -1] = mapPoints[pointPos];
        pointPos++;
    }

    SizePointArray(points - 1);

    return true;
}

SwHtmlImageMap::SwHtmlImageMap()
{
    m_mapData = NULL;
    m_mapnodePos = 0;
    m_mapnodesAllocated = 0;
    m_pathWidth = 7;
    m_mapType = MAP_TYPE_HTML;
    m_name = strdup("");
}

SwHtmlImageMap::SwHtmlImageMap(SwHtmlImageMap & imageMap)
{
    m_mapData = NULL;
    m_mapnodePos = 0;
    m_mapnodesAllocated = 0;
    m_pathWidth = 7;
    m_mapType = MAP_TYPE_HTML;
    m_name = strdup("");
    Copy(imageMap);
}

void SwHtmlImageMap::Copy(SwHtmlImageMap & imageMap)
{
    Reset();
    SetPathWidth(imageMap.GetPathWidth());
    SetMapType(imageMap.GetMapType());
    SetName(imageMap.GetName());

    for (swUI32 i = 0; i < imageMap.GetMapNodeCount(); i++)
        AppendNode(*imageMap.GetMapData(i));
}

SwHtmlImageMap::~SwHtmlImageMap()
{
    if (m_name)
        free(m_name);

    if (m_mapData)
        ReleaseMapDataBuffer();
}

void SwHtmlImageMap::Reset()
{
    SetName("");
    DeleteMapData();
}

const char * SwHtmlImageMap::GetName()
{
    return m_name;
}

void SwHtmlImageMap::SetName(const char * name)
{
    if (m_name)
        free(m_name);

    if (!name)
        name = "";

    m_name = strdup(name);
}

void SwHtmlImageMap::SetPathWidth(swUI16 width)
{
    m_pathWidth = width;
}

swUI16 SwHtmlImageMap::GetPathWidth()
{
    return m_pathWidth;
}

void SwHtmlImageMap::SetMapType(swUI8 type)
{
    m_mapType = type;
}

swUI8 SwHtmlImageMap::GetMapType()
{
    return m_mapType;
}

swUI32 SwHtmlImageMap::AppendNode(SwMapArea & mapData)
{
    if (AssignMapDataNode() == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    m_mapData[m_mapnodePos - 1].Copy(mapData);

    return m_mapnodePos -1;
}

swUI32 SwHtmlImageMap::AppendNode(const char * alt, const char * href, const char * src, swUI8 type, swUI32 points)
{
    if (AssignMapDataNode() == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    m_mapData[m_mapnodePos -1].type = type;

    m_mapData[m_mapnodePos -1].SizePointArray(points);
    m_mapData[m_mapnodePos -1].SetHref(href);
    m_mapData[m_mapnodePos -1].SetAlt(alt);
    m_mapData[m_mapnodePos -1].SetSrc(src);
    m_mapData[m_mapnodePos -1].SetBitmap(NULL);

    return m_mapnodePos -1;
}


SwMapArea * SwHtmlImageMap::GetMapData(swUI32 mapNode)
{
    if (mapNode >= m_mapnodePos)
        return NULL;

    return &m_mapData[mapNode];
}

void SwHtmlImageMap::ReplaceNode(swUI32 mapNode, SwMapArea & mapData)
{
    if (mapNode >= m_mapnodePos)
        return;

    m_mapData[mapNode].Copy(mapData);
}

void SwHtmlImageMap::DeleteNode(swUI32 mapNode)
{
    swUI32 pos = mapNode;
    if (mapNode >= m_mapnodePos)
        return;

    if (m_mapnodePos <= 1)
    {
        m_mapnodePos = 0;
        return;
    }

    if (m_mapnodePos > 1)
    {
        pos ++;

        while (pos < m_mapnodePos)
        {
            m_mapData[pos -1].Copy(m_mapData[pos]);
            pos ++;
        }
    }

    m_mapnodePos --;
}

swUI32 SwHtmlImageMap::GetLastMapNode()
{
    return m_mapnodePos - 1;
}

swUI32 SwHtmlImageMap::GetMapNodeCount()
{
    return m_mapnodePos;
}

swUI32 SwHtmlImageMap::AssignMapDataNode()
{
    if (m_mapnodePos >= m_mapnodesAllocated && !IncreaseImgMapDataBuffer())
        return NODE_ID_INVALID;

    m_mapData[m_mapnodePos].Reset();
    m_mapnodePos ++;

    return m_mapnodePos - 1;
}

bool SwHtmlImageMap::IncreaseImgMapDataBuffer()
{
    swUI32 pos = m_mapnodePos;

    if (m_mapnodesAllocated >= NODE_ID_INVALID - 17)
        return false;

    SwMapArea * p = (SwMapArea *) realloc((void *) m_mapData, (m_mapnodesAllocated + 16) * sizeof(SwMapArea));

    if (p)
    {
        m_mapnodesAllocated += 16;
        m_mapData = p;

        while (pos < m_mapnodesAllocated)
        {
            m_mapData[pos].Init();
            pos ++;
        }

        return true;
    }

    return false;
}

void SwHtmlImageMap::ReleaseMapDataBuffer()
{
    if (m_mapData)
    {
        DeleteMapData();
        free(m_mapData);
    }

    m_mapData = NULL;
    m_mapnodesAllocated = 0;
    m_mapnodePos = 0;
}

bool SwHtmlImageMap::InsertNode(swUI32 nodePos, SwMapArea & mapData)
{
    if (nodePos >= m_mapnodePos || !AssignMapDataNode())
        return false;

    swUI32 pos = m_mapnodePos;

    while(pos >= nodePos)
    {
        m_mapData[pos].Copy(m_mapData[pos - 1]);
        pos --;
    }

    ReplaceNode(nodePos, mapData);

    return true;
}

void SwHtmlImageMap::DeleteMapData()
{
    swUI32 pos = 0;

    if (!m_mapData)
        return;

    while(pos < m_mapnodesAllocated)
    {
        m_mapData[pos].ReleaseBuffers();
        pos ++;
    }

    m_mapnodePos = 0;
}

swUI32 SwHtmlImageMap::FindMapAreaBySrc(const char * src)
{
    swUI32 pos = 0;

    if (!src)
        return NODE_ID_INVALID;

    while (pos < m_mapnodePos)
    {

        if (m_mapData[pos].src && stricmp(m_mapData[pos].src, src) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwHtmlImageMap::FindMapAreaByhref(const char * href)
{
    swUI32 pos = 0;

    if (!href)
        return NODE_ID_INVALID;

    while (pos < m_mapnodePos)
    {

        if (m_mapData[pos].href && stricmp(m_mapData[pos].href, href) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwHtmlImageMap::FindMapAreaByalt(const char * alt)
{
    swUI32 pos = 0;

    if (!alt)
        return NODE_ID_INVALID;

    while (pos < m_mapnodePos)
    {
        if (m_mapData[pos].alt)
        {
            if (m_mapData[pos].alt && stricmp(m_mapData[pos].alt, alt) == 0)
                return pos;
        }

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwHtmlImageMap::FindMapAreaByPos(SwPoint mousePos, float scale, long scrollPosX, long scrollPosY, SwRect objectRect, float objectRatio)
{
    swUI32 pos = 0;
    float distance;
    mousePos.x += scrollPosX;
    mousePos.y += scrollPosY;
    bool firstValid = false;

    if (m_mapnodePos < 1)
        return NODE_ID_INVALID;

    while (pos < m_mapnodePos)
    {
        if (m_mapData[pos].type == AREA_TYPE_RECTANGLE || m_mapData[pos].type == AREA_TYPE_IMAGE)
        {
            if ((mousePos.x >= ((objectRect.x * scale) + (m_mapData[pos].mapPoints[0].x * objectRatio))) && (mousePos.x <= ((objectRect.x * scale) + (m_mapData[pos].mapPoints[1].x * objectRatio))) &&
                    (mousePos.y >= ((objectRect.y * scale) + (m_mapData[pos].mapPoints[0].y * objectRatio))) &&  (mousePos.y <= ((objectRect.y * scale) + (m_mapData[pos].mapPoints[1].y * objectRatio))))
            {
                if (m_mapType == MAP_TYPE_HTML)
                    return pos;
                else if (pos == 0)
                {
                    firstValid = true;
                }
            }
            else if (m_mapType == MAP_TYPE_REGIONAL && pos == 0)
                return NODE_ID_INVALID;
        }
        else if (m_mapData[pos].type == AREA_TYPE_CIRCLE)
        {
            swUI32 actX = (objectRect.x * scale) + (m_mapData[pos].mapPoints[0].x * objectRatio);
            swUI32 actY = (objectRect.y * scale) + (m_mapData[pos].mapPoints[0].y * objectRatio);
            distance = sqrt( (double)(actX-mousePos.x)*(actX - mousePos.x) + (actY - mousePos.y)*(actY-mousePos.y));
            if (distance <= m_mapData[pos].mapPoints[1].x * objectRatio)
            {
                if (m_mapType == MAP_TYPE_HTML)
                    return pos;
                else if (pos == 0)
                {
                    firstValid = true;
                }
            }
            else if (m_mapType == MAP_TYPE_REGIONAL && pos == 0)
                return NODE_ID_INVALID;
        }
        else if (m_mapData[pos].type == AREA_TYPE_POLYGON)
        {
            if (IsPointInPolygon(m_mapData[pos].mapPoints, m_mapData[pos].points, mousePos, scale, objectRatio, objectRect))
            {
                if (m_mapType == 0)
                    return pos;
                else if (pos == 0)
                {
                    firstValid = true;
                }
            }
            else if (m_mapType == MAP_TYPE_REGIONAL && pos == 0)
                return NODE_ID_INVALID;
        }
        else if (m_mapData[pos].type == AREA_TYPE_PATH && m_mapData[pos].points > 1)
        {
            swUI32 points;
            points = PathToPolygon(m_mapData[pos].mapPoints, m_mapData[pos].points, m_pointArray, m_pathWidth);
            if (IsPointInPolygon(m_pointArray.GetArray(), points, mousePos, scale, objectRatio, objectRect))
            {
                if (m_mapType == MAP_TYPE_HTML)
                    return pos;
                else if (pos == 0)
                {
                    firstValid = true;
                }
            }
            else if (m_mapType == MAP_TYPE_REGIONAL && pos == 0)
                return NODE_ID_INVALID;
        }

        pos ++;
    }

    if (m_mapType == 1 && firstValid)
        return 0;

    return NODE_ID_INVALID;
}

bool SwHtmlImageMap::IsPointInPolygon(SwPoint * source, swUI32 points, SwPoint mousePos, float scale, float objectRatio, SwRect objectRect)
{
    float actXi, actYi;
    float actXj, actYj;

    swUI32   j = points - 1;
    bool  oddNodes = false;

    for (swUI32 i=0; i<points; i++)
    {
        actXi = (objectRect.x * scale) + (source[i].x * objectRatio);
        actYi = (objectRect.y * scale) + (source[i].y * objectRatio);
        actXj = (objectRect.x * scale) + (source[j].x * objectRatio);
        actYj = (objectRect.y * scale) + (source[j].y * objectRatio);

        if ((actYi<mousePos.y && actYj>=mousePos.y)
                ||  (actYj<mousePos.y && actYi>=mousePos.y))
        {
            if (actXi+(mousePos.y-actYi)/(actYj-actYi)*( actXj-actXi)<mousePos.x)
            {
                oddNodes=!oddNodes;
            }
        }
        j=i;
    }

    return oddNodes;
}

swUI32 SwHtmlImageMap::PathToPolygon(const SwPoint * source, swUI32 points, SwPointArray & destination, swUI32 width)
{
    if (destination.GetSize() < (unsigned) (points * 2) + 1)
        destination.Size((points * 2) + 1);

    swUI32 n = 0;
    while (n < points)
    {
        destination.SetAt(n, source[n]);
        n ++;
    }

    n = 0;
    SwPoint last;
    last.x = 0;
    last.y = 0;

    while (n < points)
    {
        *destination.Get((points * 2) - n) = source[n];

        if (n == 0)
        {
            if (source[0].y > source[1].y)
            {
                if (source[0].x < source[1].x)
                    destination.Get((points * 2) - n)->y += width;
                if (source[0].x > source[1].x)
                    destination.Get((points * 2) - n)->y -= width;

                destination.Get((points * 2) - n)->x += width;

            }
            else if (source[0].y < source[1].y)
            {
                if (source[0].x < source[1].x)
                    destination.Get((points * 2) - n)->y += width;
                if (source[0].x > source[1].x)
                    destination.Get((points * 2) - n)->y -= width;

                destination.Get((points * 2) - n)->x -= width;
            }
            else if (source[0].x > source[1].x)
                destination.Get((points * 2) - n)->y -= width;
            else if (source[0].x < source[1].x)
                destination.Get((points * 2) - n)->y += width;
        }
        else if (n + 1 < points)
        {
            if (source[n+1].y > source[n].y)
            {
                destination.Get((points * 2) - n)->x -= width;

                if (source[n].x < last.x)
                    destination.Get((points * 2) - n)->y -= width;
                else
                    destination.Get((points * 2) - n)->y += width;
            }
            else if (source[n+1].y < source[n].y)
            {
                destination.Get((points * 2) - n)->x += width;

                if (source[n].x < last.x)
                    destination.Get((points * 2) - n)->y -= width;
                else
                    destination.Get((points * 2) - n)->y += width;
            }
            else if (source[n+1].x > source[n].x)
            {
                destination.Get((points * 2) - n)->y += width;

                if (source[n].y < last.y)
                    destination.Get((points * 2) - n)->x += width;
                else
                    destination.Get((points * 2) - n)->x -= width;
            }
            else if (source[n+1].x < source[n].x)
            {
                destination.Get((points * 2) - n)->y -= width;

                if (source[n].y < last.y)
                    destination.Get((points * 2) - n)->x += width;
                else
                    destination.Get((points * 2) - n)->x -= width;
            }
        }

        last = source[n];
        n ++;
    }

    if (source[points - 2].y > source[points - 1].y)
    {
        if (source[points - 2].x < source[points - 1].x)
        {
            destination.Get(points + 1)->y += width;
            destination.Get(points)->y = destination.Get(points + 1)->y - (width * 2);
            destination.Get(points + 1)->x += width;
            destination.Get(points)->x = destination.Get(points + 1)->x + (width);
        }
        else if (source[points - 2].x > source[points - 1].x)
        {
            destination.Get(points + 1)->y -= width;
            destination.Get(points)->y = destination.Get(points + 1)->y - (width);
            destination.Get(points + 1)->x += width;
            destination.Get(points)->x = destination.Get(points + 1)->x - (width);
        }
        else
        {
            destination.Get(points + 1)->x += width;
            destination.Get(points)->y = destination.Get(points + 1)->y - (width * 2);
            destination.Get(points)->x = destination.Get(points + 1)->x - (width / 2);
        }

    }
    else if (source[points - 2].y < source[points - 1].y)
    {
        if (source[points - 2].x < source[points - 1].x)
        {
            destination.Get(points + 1)->y += width;
            destination.Get(points)->y = destination.Get(points + 1)->y + (width);
            destination.Get(points + 1)->x -= width;
            destination.Get(points)->x = destination.Get(points + 1)->x + (width * 2);

        }
        else if (source[points - 2].x > source[points - 1].x)
        {
            destination.Get(points + 1)->y -= width;
            destination.Get(points)->y = destination.Get(points + 1)->y + (width * 2);
            destination.Get(points + 1)->x -= width;
            destination.Get(points)->x = destination.Get(points + 1)->x - (width);
        }
        else
        {
            destination.Get(points + 1)->x -= width;
            destination.Get(points)->y = destination.Get(points + 1)->y + (width * 2);
            destination.Get(points)->x = destination.Get(points + 1)->x + (width / 2);

        }
    }
    else if (source[points - 2].x > source[points - 1].x)
    {
        destination.Get(points + 1)->y -= width;
        destination.Get(points)->y = destination.Get(points + 1)->y + (width / 2);
        destination.Get(points)->x = destination.Get(points + 1)->x - (width * 2);
    }
    else if (source[points - 2].x < source[points - 1].x)
    {
        destination.Get(points + 1)->y += width;
        destination.Get(points)->y = destination.Get(points + 1)->y - (width / 2);
        destination.Get(points)->x = destination.Get(points + 1)->x + (width * 2);
    }

    return (points * 2) + 1;
}

float SwHtmlImageMap::Distance(SwPoint pointA, SwPoint pointB)
{
    return sqrt((double)(pointA.x - pointB.x) * (pointA.x - pointB.x) + (pointA.y - pointB.y) * (pointA.y - pointB.y));
}

float SwHtmlImageMap::Distance(SwPoint point, SwPoint mousePos, float scale)
{
    return sqrt((double)((point.x * scale) - mousePos.x) * ((point.x * scale) - mousePos.x) + ((point.y * scale) - mousePos.y) * ((point.y * scale) - mousePos.y));
}

void SwHtmlImageMap::FindInsertionPoint(SwMapArea & mapData, SwPoint insertPoint, swUI32 & insPoint1, swUI32 & insPoint2)
{
    float distance, distance1, distance2;

    insPoint1 = NODE_ID_INVALID;
    insPoint2 = NODE_ID_INVALID;

    for (swUI32 i = 0; i < mapData.points; i++)
    {
        if (i == 0)
        {
            distance1 = Distance(mapData.mapPoints[i], insertPoint);
            insPoint1 = i;
        }
        else
        {
            distance = Distance(mapData.mapPoints[i], insertPoint);
            if (distance < distance1)
            {
                distance1 = distance;
                insPoint1 = i;
            }
        }

    }

    bool first = true;
    for (swUI32 i = 0; i < mapData.points; i++)
    {
        if (i == insPoint1)
            continue;

        if (first)
        {
            distance2 = Distance(mapData.mapPoints[i], insertPoint);
            insPoint2 = i;
            first = false;
        }
        else
        {
            distance = Distance(mapData.mapPoints[i], insertPoint);
            if (distance < distance2)
            {
                distance2 = distance;
                insPoint2 = i;
            }
        }
    }
}

void SwHtmlImageMap::FindInsertionPoint(SwMapArea & mapData, SwPoint insertPoint, swUI32 & insPoint1, swUI32 & insPoint2, float scale)
{
    float distance, distance1, distance2;

    insPoint1 = NODE_ID_INVALID;
    insPoint2 = NODE_ID_INVALID;

    for (swUI32 i = 0; i < mapData.points; i++)
    {
        if (i == 0)
        {
            distance1 = Distance(mapData.mapPoints[i], insertPoint, scale);
            insPoint1 = i;
        }
        else
        {
            distance = Distance(mapData.mapPoints[i], insertPoint, scale);
            if (distance < distance1)
            {
                distance1 = distance;
                insPoint1 = i;
            }
        }

    }

    bool first = true;
    for (swUI32 i = 0; i < mapData.points; i++)
    {
        if (i == insPoint1)
            continue;

        if (first)
        {
            distance2 = Distance(mapData.mapPoints[i], insertPoint, scale);
            insPoint2 = i;
            first = false;
        }
        else
        {
            distance = Distance(mapData.mapPoints[i], insertPoint, scale);
            if (distance < distance2)
            {
                distance2 = distance;
                insPoint2 = i;
            }
        }
    }
}

bool SwHtmlImageMap::FindCenter(swUI32 node, SwPoint & center)
{
    if (node >= m_mapnodePos)
        return false;

    return FindCenter(center, m_mapData[node].mapPoints, m_mapData[node].points, m_mapData[node].type);
}

bool SwHtmlImageMap::FindCenter(SwPoint & center, const SwPoint * source, swUI32 points, swUI8 areaType)
{
    if (!source || !points)
        return false;

    if (areaType == AREA_TYPE_CIRCLE)
    {
        center = *source;
        return true;
    }

    if ((areaType == AREA_TYPE_IMAGE || areaType == AREA_TYPE_RECTANGLE) && points == 2)
    {
        center.x = source[0].x + (source[1].x / 2);
        center.y = source[0].y + (source[1].y / 2);
        return true;
    }

    if (areaType == AREA_TYPE_POLYGON && points > 1)
    {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        for (swUI32 i = 0; i < points; i++)
        {
            if (x1 > source[i].x)
                x1 = source[i].x;
            if (x2 < source[i].x)
                x2 = source[i].x;
            if (y1 > source[i].y)
                y1 = source[i].y;
            if (y2 < source[i].y)
                y2 = source[i].y;
        }

        center.x = x1 + ((x2 - x1) / 2);
        center.y = y1 + ((y2 - y1) / 2);

        return true;
    }

    if (areaType == AREA_TYPE_PATH && points > 1)
    {
        SwPointArray pt;
        pt.Size(points);
        PathToPolygon(source, points, pt, m_pathWidth);
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        for (swUI32 i = 0; i < points; i++)
        {
            if (x1 > pt.GetAt(i).x)
                x1 = pt.GetAt(i).x;
            if (x2 < pt.GetAt(i).x)
                x2 = pt.GetAt(i).x;
            if (y1 > pt.GetAt(i).y)
                y1 = pt.GetAt(i).y;
            if (y2 < pt.GetAt(i).y)
                y2 = pt.GetAt(i).y;
        }

        center.x = x1 + ((x2 - x1) / 2);
        center.y = y1 + ((y2 - y1) / 2);

        return true;
    }

    return false;
}


void SwHtmlImageMap::ResetMarked()
{
    swUI32 pos = 0;

    while (pos < m_mapnodePos)
    {
        m_mapData[pos].marked = false;
        pos ++;
    }
}

void SwHtmlImageMap::DeleteBitMaps()
{
    swUI32 pos = 0;

    while (pos < m_mapnodePos)
    {
        if (m_mapData[pos].bitMap)
            delete m_mapData[pos].bitMap;

        m_mapData[pos].bitMap = NULL;

        pos ++;
    }
}

swUI32 SwHtmlImageMap::CreatePath(const char * places, SwMapArea & mapArea, bool breakonMissing)
{
    if (!places)
        return 0;

    SwStrParser strList;
    strList.SetDeliminator('|');
    strList.ParseString(places);
    swUI32 node;
    swUI32 pointsFound = 0;
    SwPoint center;

    for (swUI32 i = 0; i < strList.GetItems(); i++)
    {
        node = FindMapAreaByalt(strList.GetItem(i));
        if (node == NODE_ID_INVALID && breakonMissing)
            return pointsFound;
        if (FindCenter(i, center))
        {
            mapArea.AddPoint(center);
            pointsFound ++;
        }
        else if (breakonMissing)
            return pointsFound;
    }

    return pointsFound;
}

void SwHtmlImageMap::UpdateMapData(SwMapArea & mapData, int diffX, int diffY)
{
    // Updates positions of dragged map areas.
    swUI32 pointPos = 0;

    if (mapData.type == AREA_TYPE_POLYGON)
    {
        while (pointPos < mapData.points)
        {
            mapData.mapPoints[pointPos].x += diffX;
            mapData.mapPoints[pointPos].y += diffY;
            pointPos ++;
        }
    }
    else if (mapData.points &&(mapData.type == AREA_TYPE_CIRCLE))
    {
        mapData.mapPoints[0].x += diffX;
        mapData.mapPoints[0].y += diffY;
    }
    else if (mapData.points &&(mapData.type == AREA_TYPE_RECTANGLE))
    {
        mapData.mapPoints[0].x += diffX;
        mapData.mapPoints[0].y += diffY;
    }
    else if (mapData.points && mapData.type == AREA_TYPE_PATH)
    {
        while (pointPos < mapData.points)
        {
            mapData.mapPoints[pointPos].x += diffX;
            mapData.mapPoints[pointPos].y += diffY;
            pointPos ++;
        }
    }
    else if (mapData.points && mapData.type == AREA_TYPE_IMAGE)
    {
        mapData.mapPoints[0].x += diffX;
        mapData.mapPoints[0].y += diffY;
    }
}

void SwHtmlImageMap::OffSetMap(int diffX, int diffY)
{
    for (swUI32 i = 0; i < m_mapnodePos; i++)
        UpdateMapData(m_mapData[i], diffX, diffY);
}

void SwHtmlImageMap::CreatePolygonFromMapNodes(SwMapArea & mapArea)
{
    mapArea.SizePointArray(m_mapnodePos);

    for (swUI32 i = 0; i < m_mapnodePos; i++)
    {
        if (GetMapData(i)->points > 0)
            mapArea.AddPoint(GetMapData(i)->mapPoints[0]);
    }
}

bool SwHtmlImageMap::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI16 size;

    size = strlen(m_name) + 1;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (fwrite((void *) m_name, sizeof(char), size, file) != size)
        return false;

    if (fwrite((void *) &m_mapType, sizeof(swUI8), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_pathWidth, sizeof(swUI16), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_mapnodePos, sizeof(swUI32), 1, file) != 1)
        return false;

    for (swUI32 i = 0; i < m_mapnodePos; i++)
    {
        size = 0;
        if (m_mapData[i].href)
        {
            size = strlen(m_mapData[i].href) + 1;
            if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
                return false;
            if (fwrite((void *) m_mapData[i].href, sizeof(char), size, file) != size)
                return false;
        }
        else if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
            return false;

        size = 0;
        if (m_mapData[i].alt)
        {
            size = strlen(m_mapData[i].alt) + 1;
            if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
                return false;
            if (fwrite((void *) m_mapData[i].alt, sizeof(char), size, file) != size)
                return false;
        }
        else if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
            return false;

        size = 0;
        if (m_mapData[i].src)
        {
            size = strlen(m_mapData[i].src) + 1;
            if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
                return false;
            if (fwrite((void *) m_mapData[i].src, sizeof(char), size, file) != size)
                return false;
        }
        else if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
            return false;

        if (fwrite((void *) &m_mapData[i].type, sizeof(swUI8), 1, file) != 1)
            return false;

        if (fwrite((void *) &m_mapData[i].drawColor, sizeof(swUI32), 1, file) != 1)
            return false;

        if (fwrite((void *) &m_mapData[i].fillColor, sizeof(swUI32), 1, file) != 1)
            return false;

        // Reserved for use with SwImageWindow, value should not be used on reload.
        if (fwrite((void *) &m_mapData[i].marked, sizeof(bool), 1, file) != 1)
            return false;

        if (fwrite((void *) &m_mapData[i].isclickItem, sizeof(swUI8), 1, file) != 1)
            return false;

        if (fwrite((void *) &m_mapData[i].points, sizeof(swUI32), 1, file) != 1)
            return false;

        if (fwrite((void *) m_mapData[i].mapPoints, sizeof(SwPoint), m_mapData[i].points, file) != m_mapData[i].points)
            return false;
    }

    return true;
}

bool SwHtmlImageMap::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI16 size = strlen(m_name) + 1;
    swUI32 type = GetType();

    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) m_name, sizeof(char), size, file, k1, k2) != size)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_mapType, sizeof(swUI8), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_pathWidth, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_mapnodePos, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    for (swUI32 i = 0; i < m_mapnodePos; i++)
    {
        size = 0;
        if (m_mapData[i].href)
        {
            size = strlen(m_mapData[i].href) + 1;
            if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
                return false;
            if (SwTranscryptor::encryptfwrite((void *) m_mapData[i].href, sizeof(char), size, file, k1, k2) != size)
                return false;
        }
        else if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
            return false;

        size = 0;
        if (m_mapData[i].alt)
        {
            size = strlen(m_mapData[i].alt) + 1;
            if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
                return false;
            if (SwTranscryptor::encryptfwrite((void *) m_mapData[i].alt, sizeof(char), size, file, k1, k2) != size)
                return false;
        }
        else if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
            return false;

        size = 0;
        if (m_mapData[i].src)
        {
            size = strlen(m_mapData[i].src) + 1;
            if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
                return false;
            if (SwTranscryptor::encryptfwrite((void *) m_mapData[i].src, sizeof(char), size, file, k1, k2) != size)
                return false;
        }
        else if (SwTranscryptor::encryptfwrite((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::encryptfwrite((void *) &m_mapData[i].type, sizeof(swUI8), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::encryptfwrite((void *) &m_mapData[i].drawColor, sizeof(swUI32), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::encryptfwrite((void *) &m_mapData[i].fillColor, sizeof(swUI32), 1, file, k1, k2) != 1)
            return false;

        // Reserved for use with SwImageWindow, value should not be used on reload.
        if (SwTranscryptor::encryptfwrite((void *) &m_mapData[i].marked, sizeof(bool), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::encryptfwrite((void *) &m_mapData[i].isclickItem, sizeof(swUI8), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::encryptfwrite((void *) &m_mapData[i].points, sizeof(swUI32), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::encryptfwrite((void *) m_mapData[i].mapPoints, sizeof(SwPoint), m_mapData[i].points, file, k1, k2) != m_mapData[i].points)
            return false;
    }

    return true;
}

bool SwHtmlImageMap::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    Reset();

    swUI16 size;
    swUI32 items;

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (size)
    {
        char * p = (char *) malloc(size);

        if (!p)
            return false;

        if (fread((void *) p, sizeof(char), size, file) != size)
        {
            free(p);
            return false;
        }

        SetName(p);
        free(p);
    }

    if (fread((void *) &m_mapType, sizeof(swUI8), 1, file) != 1)
        return false;

    if (fread((void *) &m_pathWidth, sizeof(swUI16), 1, file) != 1)
        return false;

    if (fread((void *) &items, sizeof(swUI32), 1, file) != 1)
        return false;

    swUI32 id;
    for (swUI32 i = 0; i < items; i++)
    {
        id = AssignMapDataNode();

        size = 0;
        if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
            return false;

        if (size)
        {
            char * p = (char *) malloc(size);

            if (!p)
                return false;

            if (fread((void *) p, sizeof(char), size, file) != size)
            {
                free(p);
                return false;
            }

            m_mapData[id].SetHref(p);
            free(p);
        }

        size = 0;
        if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
            return false;

        if (size)
        {
            char * p = (char *) malloc(size);

            if (!p)
                return false;

            if (fread((void *) p, sizeof(char), size, file) != size)
            {
                free(p);
                return false;
            }

            m_mapData[id].SetAlt(p);
            free(p);
        }

        size = 0;
        if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
            return false;

        if (size)
        {
            char * p = (char *) malloc(size);

            if (!p)
                return false;

            if (fread((void *) p, sizeof(char), size, file) != size)
            {
                free(p);
                return false;
            }

            m_mapData[id].SetSrc(p);
            free(p);
        }

        if (fread((void *) &m_mapData[id].type, sizeof(swUI8), 1, file) != 1)
            return false;

        if (fread((void *) &m_mapData[id].drawColor, sizeof(swUI32), 1, file) != 1)
            return false;

        if (fread((void *) &m_mapData[id].fillColor, sizeof(swUI32), 1, file) != 1)
            return false;

        if (fread((void *) &m_mapData[id].marked, sizeof(bool), 1, file) != 1)
            return false;

        m_mapData[id].marked = false;

        if (fread((void *) &m_mapData[id].isclickItem, sizeof(swUI8), 1, file) != 1)
            return false;

        swUI32 points;
        if (fread((void *) &points, sizeof(swUI32), 1, file) != 1)
            return false;

        if (!m_mapData[id].SizePointArray(points))
            return false;

        if (fread((void *) m_mapData[id].mapPoints, sizeof(SwPoint), m_mapData[id].points, file) != m_mapData[id].points)
            return false;
        m_mapData[id].bitMap = NULL;
    }

    m_mapnodePos = items;
    return true;
}

bool SwHtmlImageMap::ReadFromFile(FILE * file, const swUI8 k1, const swUI32 k2)
{
    if (!file)
        return false;

    Reset();

    swUI16 size;
    swUI32 items;

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;

    if (size)
    {
        char * p = (char *) malloc(size);

        if (!p)
            return false;

        if (SwTranscryptor::decryptfread((void *) p, sizeof(char), size, file, k1, k2) != size)
        {
            free(p);
            return false;
        }

        SetName(p);
        free(p);
    }

    if (SwTranscryptor::decryptfread((void *) &m_mapType, sizeof(swUI8), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::decryptfread((void *) &m_pathWidth, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::decryptfread((void *) &items, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    swUI32 id;
    for (swUI32 i = 0; i < items; i++)
    {
        id = AssignMapDataNode();

        size = 0;
        if (SwTranscryptor::decryptfread((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
            return false;

        if (size)
        {
            char * p = (char *) malloc(size);

            if (!p)
                return false;

            if (SwTranscryptor::decryptfread((void *) p, sizeof(char), size, file, k1, k2) != size)
            {
                free(p);
                return false;
            }

            m_mapData[id].SetHref(p);
            free(p);
        }

        size = 0;
        if (SwTranscryptor::decryptfread((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
            return false;

        if (size)
        {
            char * p = (char *) malloc(size);

            if (!p)
                return false;

            if (SwTranscryptor::decryptfread((void *) p, sizeof(char), size, file, k1, k2) != size)
            {
                free(p);
                return false;
            }

            m_mapData[id].SetAlt(p);
            free(p);
        }

        size = 0;
        if (SwTranscryptor::decryptfread((void *) &size, sizeof(swUI16), 1, file, k1, k2) != 1)
            return false;

        if (size)
        {
            char * p = (char *) malloc(size);

            if (!p)
                return false;

            if (SwTranscryptor::decryptfread((void *) p, sizeof(char), size, file, k1, k2) != size)
            {
                free(p);
                return false;
            }

            m_mapData[id].SetSrc(p);
            free(p);
        }

        if (SwTranscryptor::decryptfread((void *) &m_mapData[id].type, sizeof(swUI8), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::decryptfread((void *) &m_mapData[id].drawColor, sizeof(swUI32), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::decryptfread((void *) &m_mapData[id].fillColor, sizeof(swUI32), 1, file, k1, k2) != 1)
            return false;

        if (SwTranscryptor::decryptfread((void *) &m_mapData[id].marked, sizeof(bool), 1, file, k1, k2) != 1)
            return false;

        m_mapData[id].marked = false;

        if (SwTranscryptor::decryptfread((void *) &m_mapData[id].isclickItem, sizeof(swUI8), 1, file, k1, k2) != 1)
            return false;

        swUI32 points;
        if (SwTranscryptor::decryptfread((void *) &points, sizeof(swUI32), 1, file, k1, k2) != 1)
            return false;

        if (!m_mapData[id].SizePointArray(points))
            return false;

        if (SwTranscryptor::decryptfread((void *) m_mapData[id].mapPoints, sizeof(SwPoint), m_mapData[id].points, file, k1, k2) != m_mapData[id].points)
            return false;

        m_mapData[id].bitMap = NULL;
    }

    m_mapnodePos = items;
    return true;
}

swUI32 SwHtmlImageMap::GetType()
{
    return MODULE_INTERFACE_TYPE_IMAGEMAP;
}

void SwHtmlImageMap::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    wxListItem lItem;
    SwStringW buffer;

    for (swUI32 i = 0; i < GetMapNodeCount(); i ++)
    {

        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(listctrl->GetItemCount());
        buffer.Copy(GetMapData(i)->GetAlt());
        lItem.SetText(buffer.GetArray());
        lItem.SetData(GetMapData(i));
        listctrl->InsertItem(lItem);
    }
}

SwHtmlImageMapList::SwHtmlImageMapList()
{
    m_mapArray = NULL;
    m_maparrayPos = 0;
    m_mapobjectsAllocated = 0;
    m_geocd.Reset();
    m_useGeo = false;
}

SwHtmlImageMapList::~SwHtmlImageMapList()
{
    ReleaseMapArray();
}

void SwHtmlImageMapList::Copy(SwHtmlImageMapList & imagemapList)
{
    DeleteMapObjects();
    swUI32 node;
    for (swUI32 i = 0; i < imagemapList.GetMapCount(); i++)
    {
        node = AddMap(imagemapList.GetMap(i)->GetName());
        GetMap(node)->Copy(*imagemapList.GetMap(i));
    }

    m_geocd = imagemapList.GetConversionData();
}

swUI32 SwHtmlImageMapList::AssignMapObject()
{
    if (m_maparrayPos >= m_mapobjectsAllocated && !IncreaseMapArray())
        return NODE_ID_INVALID;

    m_mapArray[m_maparrayPos] = new SwHtmlImageMap();
    m_maparrayPos ++;

    return m_maparrayPos - 1;
}

bool SwHtmlImageMapList::IncreaseMapArray()
{
    if (m_mapobjectsAllocated >= NODE_ID_INVALID - 17)
        return false;

    SwHtmlImageMap ** p = (SwHtmlImageMap **) realloc((void *) m_mapArray, (m_mapobjectsAllocated + 16) * sizeof(SwHtmlImageMap *));

    if (p)
    {
        m_mapobjectsAllocated += 16;
        m_mapArray = p;

        return true;
    }

    return false;
}

void SwHtmlImageMapList::ReleaseMapArray()
{
    if (m_mapArray)
    {
        DeleteMapObjects();
        free(m_mapArray);
    }

    m_mapArray = NULL;
    m_mapobjectsAllocated = 0;
    m_maparrayPos = 0;
}

swUI32 SwHtmlImageMapList::AddMap(const char * name)
{
    if (!name)
        return NODE_ID_INVALID;

    if (FindMap(name) != NODE_ID_INVALID)
        return NODE_ID_INVALID;

    swUI32 mapId = AssignMapObject();

    if (mapId == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    SetMapName(mapId, name);

    return mapId;
}

void SwHtmlImageMapList::DeleteMap(swUI32 mapId)
{
    swUI32 pos = mapId;

    if (mapId >= m_maparrayPos)
        return;

    if (m_mapArray[mapId])
        delete m_mapArray[mapId];

    m_mapArray[mapId] = NULL;

    if (m_maparrayPos >= 1)
    {
        pos ++;

        while (pos < m_maparrayPos)
        {
            m_mapArray[pos -1] = m_mapArray[pos];
            m_mapArray[pos] = NULL;
            pos ++;
        }
    }

    m_maparrayPos --;
}

void SwHtmlImageMapList::DeleteMapObjects()
{
    swUI32 pos = 0;

    if (!m_mapArray)
        return;

    while(pos < m_maparrayPos)
    {
        if (m_mapArray[pos])
            delete m_mapArray[pos];

        pos ++;
    }

    m_maparrayPos = 0;
}

bool SwHtmlImageMapList::SetMapName(swUI32 mapId, const char * name)
{
    if (mapId >= m_maparrayPos)
        return false;

    m_mapArray[mapId]->SetName(name);

    return true;
}

const char * SwHtmlImageMapList::GetMapName(swUI32 mapId)
{
    if (mapId >= m_maparrayPos)
        return NULL;

    return m_mapArray[mapId]->GetName();
}

swUI32 SwHtmlImageMapList::FindMap(const char * name)
{
    swUI32 pos = 0;

    if (!name)
        return NODE_ID_INVALID;

    while (pos < m_maparrayPos)
    {
        if (strcmp(name, m_mapArray[pos]->GetName()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

SwHtmlImageMap * SwHtmlImageMapList::GetMap(swUI32 mapId)
{
    if (mapId >= m_maparrayPos)
        return NULL;

    return m_mapArray[mapId];
}

void SwHtmlImageMapList::ResetMarked()
{
    swUI32 pos = 0;

    while (pos < m_maparrayPos)
    {
        m_mapArray[pos]->ResetMarked();
        pos ++;
    }
}

void SwHtmlImageMapList::DeleteBitMaps()
{
    swUI32 pos = 0;

    while (pos < m_maparrayPos)
    {
        m_mapArray[pos]->DeleteBitMaps();
        pos ++;
    }
}

swUI32 SwHtmlImageMapList::GetMapCount()
{
    return m_maparrayPos;
}

swUI32 SwHtmlImageMapList::CreatePath(const char * places, SwMapArea & mapArea, bool breakonMissing)
{
    if (!places)
        return 0;

    SwStrParser strList;
    strList.SetDeliminator('|');
    strList.ParseString(places);
    swUI32 node;
    swUI32 pointsFound = 0;
    SwPoint center;
    bool isGeo;

    for (swUI32 map = 0; map < m_maparrayPos; map++)
    {
        for (swUI32 i = 0; i < strList.GetItems(); i++)
        {
            isGeo = false;
            node = m_mapArray[map]->FindMapAreaByalt(strList.GetItem(i));
            if (node == NODE_ID_INVALID && m_useGeo)
            {
                node = SwGeo::FindByName(strList.GetItem(i));
                if (node != NODE_ID_INVALID)
                    isGeo = true;
            }

            if (node == NODE_ID_INVALID && breakonMissing)
            {
                return pointsFound;
            }

            if (!isGeo && node != NODE_ID_INVALID && m_mapArray[map]->FindCenter(i, center))
            {
                mapArea.AddPoint(center);
                pointsFound ++;
            }
            else if (isGeo && node != NODE_ID_INVALID)
            {
                SwGeo::GetMapLocation(node, m_geocd, center);
                mapArea.AddPoint(center);
                pointsFound ++;
            }
        }
    }

    return pointsFound;
}

bool SwHtmlImageMapList::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_maparrayPos, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_geocd, sizeof(SwGeoConversionData), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_useGeo, sizeof(bool), 1, file) != 1)
        return false;

    for (swUI32 i = 0; i < m_maparrayPos; i++)
        m_mapArray[i]->WriteToFile(file);

    return true;
}

bool SwHtmlImageMapList::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_maparrayPos, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_geocd, sizeof(SwGeoConversionData), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_useGeo, sizeof(bool), 1, file, k1, k2) != 1)
        return false;

    for (swUI32 i = 0; i < m_maparrayPos; i++)
        m_mapArray[i]->WriteToFile(file, k1, k2);

    return true;
}

bool SwHtmlImageMapList::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 items;

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &items, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fread((void *) &m_geocd, sizeof(SwGeoConversionData), 1, file) != 1)
        return false;

    if (fread((void *) &m_useGeo, sizeof(bool), 1, file) != 1)
        return false;

    swUI32 id;
    for (swUI32 i = 0; i < items; i++)
    {
        id = AssignMapObject();
        m_mapArray[id]->ReadFromFile(file);
    }

    return true;
}

bool SwHtmlImageMapList::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 items;

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &items, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::decryptfread((void *) &m_geocd, sizeof(SwGeoConversionData), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::decryptfread((void *) &m_useGeo, sizeof(bool), 1, file, k1, k2) != 1)
        return false;

    swUI32 id;
    for (swUI32 i = 0; i < items; i++)
    {
        id = AssignMapObject();
        m_mapArray[id]->ReadFromFile(file, k1, k2);
    }

    return true;
}

swUI32 SwHtmlImageMapList::GetType()
{
    return MODULE_INTERFACE_TYPE_IMAGEMAPLIST;
}

void SwHtmlImageMapList::FillCtrl(wxListCtrl * listctrl)
{
    if (!listctrl)
        return;

    listctrl->DeleteAllItems();

    wxListItem lItem;
    SwStringW buffer;

    for (swUI32 i = 0; i < GetMapCount(); i ++)
    {
        lItem.Clear();
        lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
        lItem.SetColumn(0);
        lItem.SetId(listctrl->GetItemCount());
        buffer.Copy(GetMap(i)->GetName());
        lItem.SetText(buffer.GetArray());
        lItem.SetData(GetMap(i));
        listctrl->InsertItem(lItem);
    }
}
