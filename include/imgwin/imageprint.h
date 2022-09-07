///////////////////////////////////////////////////////////////////
// Name:        imageprint.h
// Purpose:     Print contents of an SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef IMAGEPRINT_H
#define IMAGEPRINT_H

#include "imagewindow.h"
#include <wx/print.h>

class SwImageWindow;
class SOWERBASEEXP SwImagePrint : public wxPrintout
{
public:
    SwImagePrint();
    virtual ~SwImagePrint();
    SwImagePrint(SwImageWindow & imageWindow, const wxString &title = L"Print");
    virtual bool OnPrintPage(int page);
    virtual bool HasPage(int page);
    virtual bool OnBeginDocument(int startPage, int endPage);
    virtual void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);
    bool DrawImage();

protected:
    SwImageWindow * m_imageWindow;
};

#endif // IMAGEPRINT_H
