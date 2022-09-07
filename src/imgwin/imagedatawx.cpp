///////////////////////////////////////////////////////////////////
// Name:        imagedatawx.cpp
// Purpose:     Wrapper for wxBitmap, derived from SwImageData.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

SwImageDataWx * SwImageDataWx::Clone()
{
    SwImageDataWx * imgdata = new SwImageDataWx;
    imgdata->bitmap =  new wxBitmap(bitmap->GetSubBitmap(wxRect(0, 0, bitmap->GetWidth(), bitmap->GetHeight())));
    return imgdata;
}

bool SwImageDataWx::IsOk()
{
    if (bitmap)
        return bitmap->IsOk();

    return false;
}

int SwImageDataWx::GetHeight()
{
    if (bitmap)
        return bitmap->GetHeight();

    return 0;
}

int SwImageDataWx::GetWidth()
{
    if (bitmap)
        return bitmap->GetWidth();

    return 0;
}
