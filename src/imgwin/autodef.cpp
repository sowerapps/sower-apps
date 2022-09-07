///////////////////////////////////////////////////////////////////
// Name:        autodef.cpp
// Purpose:     AutoDef functionality for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

bool SwImageWindow::LoadAutoDefText(SwMapArea & mapData)
{
    return LoadAutoDefText(mapData.alt);
}

bool SwImageWindow::LoadAutoDefText(const char * str)
{
    m_isautodefLoaded = false;

    if (!str)
        return false;

    m_parser.ParseString(str);
    m_strarray.Reset();
    m_strarray.Size(m_parser.GetItems());

    if (SwApplicationInterface::GetMapLanguageTableId() == 0)
    {
        m_autodefText.Copy(str);
        m_buffer.Reset();

        m_isautodefLoaded = SwApplicationInterface::GetModuleManager().GetAutoDefData(m_buffer, m_parser, m_canCopy);

        if (m_isautodefLoaded)
        {
            return true;
        }
    }
    else
    {
        m_buffer.Reset();
        m_strarray.Reset();

        for (swUI32 i = 0; i < m_parser.GetItems(); i ++)
        {
            SwApplicationInterface::GetMapLanguage().GetTable().GetTranslatedString(m_parser.GetItem(i), m_strarray.GetAt(i), false);
        }

        m_isautodefLoaded = SwApplicationInterface::GetModuleManager().GetAutoDefData(m_buffer, m_strarray, m_canCopy);

        if (m_isautodefLoaded)
        {
            return true;
        }
    }

    return false;
}

void SwImageWindow::ShowAutoDef(int top, int bottom)
{
    if (m_isdragging || m_ismenuVisible || m_isediting || !IsShownOnScreen())
        return;

    m_tipWindow->Hide();
    m_autodefwindow->SetValue("");
    m_autodefwindow->WriteXmlText(m_buffer, true, "");
    m_autodefwindow->ShowAutoDef(top, bottom);
}
