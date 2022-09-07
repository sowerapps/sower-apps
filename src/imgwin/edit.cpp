///////////////////////////////////////////////////////////////////
// Name:        edit.cpp
// Purpose:     Edit functionality for map lists, maps, and areas
//              with undo, redo, relace, copy and paste.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"
#include "../../include/imgwin/command.h"
#include <wx/clipbrd.h>

void SwImageWindow::OnCopyMap(SwHtmlImageMap & imageMap)
{
    if (m_canCopy && wxTheClipboard->Open())
    {
        SwImageMapDataObject * dataObject = new SwImageMapDataObject;
        dataObject->SetData(1, (void *) &imageMap);
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(dataObject);
        wxTheClipboard->Close();
    }
}

void SwImageWindow::OnCopyMapArea(SwMapArea & mapArea)
{
    if (m_canCopy && wxTheClipboard->Open())
    {
        SwMapAreaDataObject * dataObject = new SwMapAreaDataObject;
        dataObject->SetData(1, (void *) &mapArea);
        // This data object is held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(dataObject);
        wxTheClipboard->Close();
    }
}

void SwImageWindow::OnPaste()
{
    if (wxTheClipboard->Open())
    {
        if (wxTheClipboard->IsSupported(wxDataFormat(MapAreaFormat)))
        {
            SwMapAreaDataObject dataObject;
            wxTheClipboard->GetData(dataObject);

            if (m_hotMap)
                m_hotMap->AppendNode(dataObject.m_mapData);
        }
        else if (wxTheClipboard->IsSupported( wxDataFormat(ImageMapFormat)))
        {
            wxUint32 id;
            SwImageMapDataObject dataObject;
            wxTheClipboard->GetData(dataObject);
            id = m_mapList.AddMap(dataObject.m_imageMap.GetName());

            if (id != NODE_ID_INVALID)
                m_mapList.GetMap(id)->Copy(dataObject.m_imageMap);
        }

        wxTheClipboard->Close();
    }
}
