///////////////////////////////////////////////////////////////////
// Name:        imagewindowinterface.cpp
// Purpose:     Interface for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/interface/imagewin/imagewindowinterface.h"
#include "../../../include/appi/appifa.h"
#include "../../../include/array/uintarray.h"

SwImageWindowInterface::SwImageWindowInterface()
{
    m_imagewindow = NULL;
}

SwImageWindowInterface::~SwImageWindowInterface()
{
}

void SwImageWindowInterface::SetImageWindow(SwImageWindow * window)
{
    m_imagewindow = window;

    if (window)
    {
        window->SetManagerId(m_moduleId);
        window->SetBasePath("");
    }

}

void SwImageWindowInterface::OnReset()
{
    m_title.Reset();
}

swUI32 SwImageWindowInterface::Handle(swUI16 id, swUI32 node)
{
    bool canCopy;
    SwString buffer;
    SwString fileName;

    if (IsNodeThMLDiv(GetNodeElementIdentifier(node)))
    {
        if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG ||
                GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
        {
            GetTitleBuffer().Reset();
            GetNamedValueFromNode(node, "title", GetTitleBuffer());
        }
    }
    else if (GetNodeElementIdentifier(node) == THML_IMG)
    {
        Swui8Array mediabuffer;

        if (m_moduleId == NODE_ID_INVALID_16 || !m_imagewindow)
            return node;

        if (!GetNamedValueFromNode(node, "src", buffer))
            return node;

        SwGetFileName(buffer, fileName);
        SwApplicationInterface::GetModuleManager().LoadMedia(m_moduleId, fileName, mediabuffer, canCopy);
        m_imagewindow->LoadImage(mediabuffer);
        m_imagewindow->SetCanCopy(canCopy);
        m_imagewindow->Refresh();

        SwGeoConversionData data;
        SwStrParser strlist;
        if (GetNamedValueFromNode(node, "geodata", buffer))
        {
            strlist.SetDeliminator(',');
            strlist.ParseString(buffer);

            if (strlist.GetItems() == 6)
            {
                data.mapwidth = strtoul(strlist.GetItem(0), NULL, 10);
                data.mapheight = strtoul(strlist.GetItem(1), NULL, 10);
                data.latitudeTop = atof(strlist.GetItem(2));
                data.latitudeBottom = atof(strlist.GetItem(3));
                data.longitudeLeft = atof(strlist.GetItem(4));
                data.longitudeRight = atof(strlist.GetItem(5));

                m_imagewindow->GetImageMapList().SetConversionData(data);
                m_imagewindow->GetImageMapList().SetUseGeo(true);
            }
        }
    }
    else  if (GetNodeElementIdentifier(node) == THML_INTERFACE)
    {
        if (m_moduleId == NODE_ID_INVALID_16 || !m_imagewindow)
            return node;

        if (!GetNamedValueFromNode(node, "src", buffer))
            return node;

        SwGetFileName(buffer, fileName);

        swUI16 item = SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetMediaContents().FindItem(fileName);

        if (item == NODE_ID_INVALID_16)
            return node;


        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetMediaContents().GetNode(item)->ReadData(
        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->m_file,
        m_imagewindow->GetImageMapList(),
        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetHeader().itemdataLocator,
        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetHeader().filecontentsLocator,
        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetHeader().k1,
        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetHeader().k2,
        SwApplicationInterface::GetModuleManager().GetAt(m_moduleId)->GetHeader().isEncrypted);
    }

    return node;
}
