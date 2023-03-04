///////////////////////////////////////////////////////////////////
// Name:        image.cpp
// Purpose:     Image loading.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"
#include "../../include/filesys/file.h"

bool SwImageWindow::LoadImage(const char * path)
{
    if (!path)
        return false;

    if (!SwFile::DoesExist(path))
        return false;

    Reset();
    m_hasImage = false;

    if (!m_image)
        m_image = new wxBitmap;

    if (!m_image->LoadFile(path, wxBITMAP_TYPE_ANY))
        return false;

    m_mapList.GetConversionData().SetMapSize(m_image->GetHeight(), m_image->GetWidth());
    m_hasImage = true;

    return true;
}

bool SwImageWindow::LoadImage(Swui8Array & buffer)
{
    Reset();

    wxMemoryInputStream stream((void *)buffer.GetArray(), buffer.GetCount());
    wxImage image(stream, wxBITMAP_TYPE_ANY, -1);
    m_image = new wxBitmap(image, -1);

    if (m_image && m_image->IsOk())
    {
        m_hasImage = true;
        m_mapList.GetConversionData().SetMapSize(m_image->GetHeight(), m_image->GetWidth());
        return true;
    }

    return false;
}

bool SwImageWindow::LoadImage(SwStreamBuffer & buffer)
{
    Reset();

    wxMemoryInputStream stream(buffer, buffer.GetCount());
    wxImage image(stream, wxBITMAP_TYPE_ANY, -1);
    m_image = new wxBitmap(image, -1);

    if (m_image && m_image->IsOk())
    {
        m_hasImage = true;
        m_mapList.GetConversionData().SetMapSize(m_image->GetHeight(), m_image->GetWidth());
        return true;
    }

    return false;
}

wxBitmap * SwImageWindow::GetImage(const unsigned char *data, int len)
{
    wxMemoryInputStream stream(data, len);
    wxImage image(stream, wxBITMAP_TYPE_ANY, -1);
    wxBitmap * bitmap = new wxBitmap(image, -1);
    return bitmap;
}

wxBitmap * SwImageWindow::GetImage(const wchar_t * path)
{
    wxBitmap * bitmap = new wxBitmap;
    bitmap->LoadFile(path, wxBITMAP_TYPE_ANY);
    return bitmap;
}

SwImageData * SwImageWindow::GetAreaImage(const char * src)
{
    if (!src)
        return NULL;

    SwStrParser strList;
    strList.SetDeliminator(':');
    strList.ParseString(src);

    if (!strList.GetItems())
        return NULL;

    bool canCopy;
    SwImageDataWx * img = new SwImageDataWx;
    SwString imgPath;
    SwStringW imgPathW;
    Swui8Array buffer;

    if (strList.GetItems() == 2 && strcmp("file", strList.GetItem(0)) == 0)
    {
        if (m_managerId != NODE_ID_INVALID_16)
        {
            if (SwApplicationInterface().GetModuleManager().LoadMedia(m_managerId, strList.GetItem(1), buffer, canCopy))
            {
                img->bitmap = GetImage(buffer, buffer.GetCount());
            }
        }
        else if (m_basePath.Strlen())
        {
            SwGetPathFromRelative(m_basePath, strList.GetItem(1), imgPath);
            if (SwFile::DoesExist(imgPath))
            {
                imgPathW.Copy(imgPath);
                img->bitmap = GetImage(imgPathW);
            }
        }
    }
    else if (strList.GetItems() == 2 && strcmp("stock", strList.GetItem(0)) == 0)
    {
        img->bitmap = new wxBitmap(SwApplicationInterface::GetStockImage(SwApplicationInterface::GetStockImageId(strList.GetItem(1))));
    }
    else if (strList.GetItems() == 3)
    {
        if (strcmp(strList.GetItem(0), "theme") == 0)
        {
            img->bitmap = new wxBitmap(SwApplicationInterface::GetImage(strList.GetItem(1), strList.GetItem(2)));
        }
        else if (strcmp(strList.GetItem(0), "module") == 0)
        {
            swUI16 pos = SwApplicationInterface::GetModuleManager().FindById(strList.GetItem(1));
            if (pos != NODE_ID_INVALID_16)
            {
                pos = SwApplicationInterface::GetModuleManager().GetAt(pos)->GetManagerId();
                bool status = SwApplicationInterface::GetModuleManager().LoadMedia(pos, strList.GetItem(2), buffer, canCopy);
                if (status)
                {
                    SetCanCopy(canCopy);
                    img->bitmap = GetImage(buffer, buffer.GetCount());
                }
            }
        }
    }

    if (!img->bitmap)
    {
        img->bitmap = new wxBitmap(SwApplicationInterface::GetMissingImage());
    }

    return img;
}
