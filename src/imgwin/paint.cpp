///////////////////////////////////////////////////////////////////
// Name:        paint.cpp
// Purpose:     Paint, and draw functionality for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

void SwImageWindow::OnPaint(wxPaintEvent& event)
{
    if (!m_image || !m_image->IsOk())
    {
        event.Skip();
        return;
    }

    bool xScroll = false, yScroll = false;
    int sbWidth = wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
    int sbHeight = wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y);
    bool hasXScroll = HasScrollbar(wxHORIZONTAL);
    bool hasYScroll = HasScrollbar(wxVERTICAL);
    int zWidth = m_image->GetWidth() * m_zoom;
    int zHeight = m_image->GetHeight() * m_zoom;
    wxSize sizeWin = GetClientSize();
    wxRect rcImg;

    int cy, cx;
    GetViewStart(&cx, &cy);
    if (m_zoom != m_czoom)
    {
        int nx = cx/m_czoom;
        int ny = cy/m_czoom;
        nx = nx * m_zoom;
        ny = ny * m_zoom;
        SetScrollbars(1, 1, zWidth, zHeight, cx, cy);
    }

    if (hasXScroll)
        rcImg.SetBottom(sbHeight);
    else
        rcImg.SetBottom(0);

    rcImg.SetBottom(rcImg.GetBottom() + sizeWin.y);

    if (hasYScroll)
        rcImg.SetRight(sbWidth);
    else
        rcImg.SetRight(0);

    rcImg.SetRight(rcImg.GetRight() + sizeWin.x);

    if (rcImg.GetRight() < zWidth)
    {
        rcImg.SetBottom(rcImg.GetBottom() - sbHeight);
        xScroll = TRUE;
    }

    if (rcImg.GetBottom() < zHeight)
    {
        rcImg.SetRight(rcImg.GetRight() - sbWidth);
        yScroll = TRUE;
    }

    if (!xScroll && (rcImg.GetRight() < zWidth))
    {
        rcImg.SetBottom(rcImg.GetBottom() - sbHeight);
        xScroll = TRUE;
    }

    if (!yScroll)
    {
        rcImg.SetBottom(zHeight);
    }

    if (!xScroll)
    {
        rcImg.SetRight(zWidth);
    }

    wxUint32 x = rcImg.GetRight() / m_zoom;
    wxUint32 y = rcImg.GetBottom() / m_zoom;

    wxPaintDC dc(this);
    m_mdc.SelectObjectAsSource(*m_image);
    dc.StretchBlit(0, 0, rcImg.GetRight(), rcImg.GetBottom(), &m_mdc, cx/m_zoom, cy/m_zoom, x, y);
    m_mdc.SelectObjectAsSource(wxNullBitmap);
    DrawMapAreas(dc, m_zoom, cx, cy);
    m_czoom = m_zoom;
    m_painted = true;

    event.Skip();
}

void SwImageWindow::DrawMapAreas(wxDC & dc, wxFloat32 zoom, wxUint32 originX, wxUint32 originY)
{
    wxPen pen;
    wxBrush brush;

    const wxPen & oldPen = dc.GetPen();
    const wxBrush & oldBrush = dc.GetBrush();

    for(wxUint32 i = 0; i < m_mapList.GetMapCount(); i++)
        DrawImageMap(*m_mapList.GetMap(i), pen, brush, dc, zoom, originX, originY, m_drawmapList);

    DrawImageMap(m_drawAreas, pen, brush, dc, zoom, originX, originY, true);

    if (m_hasLocation)
    {
        dc.SetPen(pen);
        pen.SetColour(0, 255, 0);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.DrawCircle((m_locationPt.x * zoom) - originX, (m_locationPt.y * zoom) - originY, 7 * zoom);
    }

    dc.SetPen(oldPen);
    dc.SetBrush(oldBrush);
}

void SwImageWindow::DrawImageMap(SwHtmlImageMap & imageMap, wxPen & pen, wxBrush & brush, wxDC & dc, wxFloat32 zoom, wxUint32 originX, wxUint32 originY, bool drawAreas)
{
    wxUint32 pos = 0;
    wxUint32 pointPos;
    wxUint8 r, g, b, a;

    if (imageMap.GetMapNodeCount() > 0)
    {
        while (pos < imageMap.GetMapNodeCount())
        {
            if (m_pt.GetSize() < imageMap.m_mapData[pos].points)
                m_pt.Size(imageMap.m_mapData[pos].points);

            if (imageMap.m_mapData[pos].drawColor == NO_COLOR)
                dc.SetPen(*wxTRANSPARENT_PEN);
            else
            {
                if (imageMap.m_mapData[pos].GetMarked())
                {
                    pen.SetStyle(wxPENSTYLE_DOT);
                }
                SwHtmlColor::SplitRGB(imageMap.m_mapData[pos].drawColor, r, g, b, a);
                pen.SetColour(r, g, b);
                dc.SetPen(pen);
            }

            if (imageMap.m_mapData[pos].fillColor == NO_COLOR)
                dc.SetBrush(*wxTRANSPARENT_BRUSH);
            else
            {
                SwHtmlColor::SplitRGB(imageMap.m_mapData[pos].fillColor, r, g, b, a);
                brush.SetColour(r, g, b);
                dc.SetBrush(brush);
            }

            pointPos = 0;
            // Create copy of map area modified for zoom value.
            while (pointPos < imageMap.m_mapData[pos].points)
            {
                m_pt.GetArray()[pointPos].x = (imageMap.m_mapData[pos].mapPoints[pointPos].x * zoom) - originX;
                m_pt.GetArray()[pointPos].y = (imageMap.m_mapData[pos].mapPoints[pointPos].y * zoom) - originY;

                pointPos ++;
            }

            // Skip if area has no points.
            if (pointPos)
            {
                if (drawAreas && imageMap.m_mapData[pos].type == AREA_TYPE_POLYGON)
                    dc.DrawPolygon(pointPos, (wxPoint *) m_pt.GetArray());
                else if (drawAreas && imageMap.m_mapData[pos].type == AREA_TYPE_CIRCLE && pointPos > 1)
                    dc.DrawCircle(wxPoint(m_pt.GetArray()[0].x, m_pt.GetArray()[0].y), imageMap.m_mapData[pos].mapPoints[1].x * zoom);
                else if (drawAreas && imageMap.m_mapData[pos].type == AREA_TYPE_RECTANGLE  && pointPos > 1)
                    dc.DrawRectangle(wxRect(wxPoint(m_pt.GetArray()[0].x, m_pt.GetArray()[0].y), wxPoint(m_pt.GetArray()[1].x, m_pt.GetArray()[1].y)));
                else if (drawAreas && imageMap.m_mapData[pos].type == AREA_TYPE_PATH  && pointPos > 1)
                {
                    wxUint32 points;
                    points = imageMap.PathToPolygon(m_pt.GetArray(), imageMap.m_mapData[pos].points, m_p2polyBuffer, imageMap.GetPathWidth());
                    dc.DrawPolygon(points, (wxPoint *) m_p2polyBuffer.GetArray());
                }
            }

            if (imageMap.m_mapData[pos].type == AREA_TYPE_IMAGE && pointPos == 1)
            {
                if (!imageMap.m_mapData[pos].bitMap)
                {
                    imageMap.m_mapData[pos].bitMap = GetAreaImage(imageMap.m_mapData[pos].GetSrc());
                }

                if (imageMap.m_mapData[pos].bitMap->IsOk())
                {
                    SwImageDataWx * imgwx = (SwImageDataWx *) imageMap.m_mapData[pos].bitMap;
                    m_mdc.SelectObjectAsSource(*imgwx->bitmap);
                    dc.StretchBlit(m_pt.GetArray()[0].x, m_pt.GetArray()[0].y, imageMap.m_mapData[pos].bitMap->GetWidth() * zoom, imageMap.m_mapData[pos].bitMap->GetHeight() * zoom, &m_mdc, 0, 0, imageMap.m_mapData[pos].bitMap->GetWidth(), imageMap.m_mapData[pos].bitMap->GetHeight());
                    m_mdc.SelectObjectAsSource(wxNullBitmap);
                }
            }

            pen.SetStyle(wxPENSTYLE_SOLID);
            pos ++;
        }
    }
}

void SwImageWindow::DrawSolidRectangle(wxDC & dc, wxCoord x, wxCoord y, wxCoord width, wxCoord height)
{
    for (int i = 0; i < height; i ++)
    {
        dc.DrawLine(x, y + i, x + width, y + i);
    }
}
