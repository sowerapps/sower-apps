///////////////////////////////////////////////////////////////////
// Name:        imageprint.cpp
// Purpose:     Print contents of an SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imageprint.h"
#include "../../include/appi/appifa.h"

SwImagePrint::SwImagePrint()
{
    m_imageWindow = NULL;
}

SwImagePrint::SwImagePrint(SwImageWindow & imageWindow, const wxString &title)
    : wxPrintout(title)
{
    m_imageWindow = &imageWindow;
}

SwImagePrint::~SwImagePrint()
{
}

bool SwImagePrint::OnPrintPage(int page)
{
    return DrawImage();
}

bool SwImagePrint::HasPage(int page)
{
    if (page == 1)
        return true;

    return false;
}

bool SwImagePrint::OnBeginDocument(int startPage, int endPage)
{
    if (!wxPrintout::OnBeginDocument(startPage, endPage))
        return false;

    return true;
}

void SwImagePrint::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    *minPage = 1;
    *maxPage = 1;
    *selPageFrom = 1;
    *selPageTo = 1;
}

bool SwImagePrint::DrawImage()
{
    wxDC *dc = GetDC();

    if (!dc || !m_imageWindow || !m_imageWindow->m_image->IsOk())
        return false;

    wxSize printSize = wxSize(m_imageWindow->m_image->GetWidth(), m_imageWindow->m_image->GetHeight());
    FitThisSizeToPageMargins(printSize, *SwApplicationInterface::GetPageSetupData());
    wxRect fitRect = GetLogicalPageMarginsRect(*SwApplicationInterface::GetPageSetupData());
    wxCoord xoff = (fitRect.width - printSize.x) / 2;
    wxCoord yoff = (fitRect.height - printSize.y) / 2;
    OffsetLogicalOrigin(xoff, yoff);
    m_imageWindow->m_mdc.SelectObjectAsSource(*m_imageWindow->m_image);
    dc->Blit(0, 0, printSize.x, printSize.y, &m_imageWindow->m_mdc, 0, 0);
    m_imageWindow->DrawMapAreas(*dc, 1, 0, 0);

    return true;
}
