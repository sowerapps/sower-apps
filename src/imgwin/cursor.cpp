///////////////////////////////////////////////////////////////////
// Name:        cursor.cpp
// Purpose:     Cursor ...
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

void SwImageWindow::SetHotCursor(bool ishot)
{
    if (ishot)
    {
        if (!m_isHot && m_allowclickActivate)
        {
            SetCursor(wxCURSOR_HAND);
            m_isHot = true;
        }
    }
    else
    {
        if (m_isHot)
            SetCursor(*wxSTANDARD_CURSOR);

        m_isHot = false;
    }
}
