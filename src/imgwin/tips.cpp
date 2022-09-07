///////////////////////////////////////////////////////////////////
// Name:        tips.cpp
// Purpose:     Display text (alt variable) for MapAreas translated
//              if possible.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

bool SwImageWindow::LoadTipText(SwMapArea & mapData)
{
    swUI32 itemData;

    if (!mapData.alt || strlen(mapData.alt) == 0)
        return false;

    if (SwApplicationInterface::GetMapLanguageTableId() == 0)
    {
        m_tipText.Copy(mapData.alt);
        m_tipWindow->SetLabel(m_tipText.GetArray());

        return true;
    }

    itemData = SwApplicationInterface::GetMapLanguage().GetTable().FindItemById(mapData.alt);

    if (!SwApplicationInterface::GetMapLanguage().GetTable().GetNodeDataW(itemData, m_tipText))
        m_tipText.Copy(mapData.alt);

    m_tipWindow->SetLabel(m_tipText.GetArray());

    return true;
}

bool SwImageWindow::LoadTipText(const char * str)
{
    if (!str)
        return false;

    if (SwApplicationInterface::GetMapLanguageTableId() == 0)
    {
        m_tipText.Copy(str);
        m_tipWindow->SetLabel(m_tipText.GetArray());
        return true;
    }

    swUI32 node = SwApplicationInterface::GetMapLanguage().GetTable().FindItemById(str);

    if (!SwApplicationInterface::GetMapLanguage().GetTable().GetNodeDataW(node, m_tipText))
        m_tipText.Copy(str);

    m_tipWindow->SetLabel(m_tipText.GetArray());

    return true;
}

void SwImageWindow::ShowTip(wxPoint position)
{
    if (!m_showTips || m_isdragging || m_autodefwindow->IsShown() || m_ismenuVisible || m_isediting|| !IsShownOnScreen())
        return;

    wxSize client = GetClientSize();
    wxSize tipSize = m_tipWindow->GetClientSize();
    wxPoint point;
    int wrap;
    if (position.y > client.y - position.y)
        point.y = position.y - 7;
    else
        point.y = position.y + 7;

    if (position.x > client.x - position.x)
    {
        point.x = position.x - (tipSize.x + 7);
        wrap = point.x;
    }
    else
    {
        point.x = position.x + 7;
        wrap = client.x - point.x;
    }


    m_tipWindow->Wrap(wrap);
    m_tipWindow->Move(point);
    m_tipWindow->Show(true);
}
