///////////////////////////////////////////////////////////////////
// Name:        command.cpp
// Purpose:     For editing in ImageWindows. Edit commands are passed
//              to the window command processor with an object and data
//              appropriate for the command. This provides undo\redo
//              functionality. SwImageWindow does not edit images, only
//              image maps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/command.h"

SwCommandUpdateMapList::SwCommandUpdateMapList()
{
    m_imagemapList1 = NULL;
    m_imagemapList2 = NULL;
}

SwCommandUpdateMapList::SwCommandUpdateMapList(const wxString& name, SwHtmlImageMapList * imagemapList1, SwHtmlImageMapList * imagemapList2)
    : wxCommand(true, name), m_imagemapList1(imagemapList1), m_imagemapList2(imagemapList2)
{
}

SwCommandUpdateMapList::~SwCommandUpdateMapList()
{
    if (m_imagemapList2)
        delete m_imagemapList2;
}

bool SwCommandUpdateMapList::CanUndo ()
{
    return true;
}

bool SwCommandUpdateMapList::Do()
{
    SwImgListSwap swap1, swap2;

    if (m_imagemapList1 && m_imagemapList2)
    {
        m_imagemapList1->GetSwapData(&swap1);
        m_imagemapList2->GetSwapData(&swap2);
        m_imagemapList1->Swap(&swap2);
        m_imagemapList2->Swap(&swap1);
    }

    return true;
}

bool SwCommandUpdateMapList::Undo()
{
    SwImgListSwap swap1, swap2;

    if (m_imagemapList1 && m_imagemapList2)
    {
        m_imagemapList1->GetSwapData(&swap1);
        m_imagemapList2->GetSwapData(&swap2);
        m_imagemapList1->Swap(&swap2);
        m_imagemapList2->Swap(&swap1);
    }

    return true;
}

SwMapAreaDataObject::SwMapAreaDataObject(const wxDataFormat &format)
    :wxCustomDataObject(format)
{
    m_mapData.Init();
}

SwMapAreaDataObject::~SwMapAreaDataObject()
{
    m_mapData.ReleaseBuffers();
}

size_t SwMapAreaDataObject::GetSize() const
{
    return 1;
}

void * SwMapAreaDataObject::GetData() const
{
    return (void *) &m_mapData;
}

bool SwMapAreaDataObject::SetData(size_t size, const void * data )
{
    SwMapArea * p = (SwMapArea *) data;
    m_mapData.Copy(*p);
    return true;
}

SwImageMapDataObject::SwImageMapDataObject(const wxDataFormat &format)
    :wxCustomDataObject(format)
{
}

SwImageMapDataObject::~SwImageMapDataObject()
{
}

size_t SwImageMapDataObject::GetSize() const
{
    return 1;
}

void * SwImageMapDataObject::GetData() const
{
    return (void *) &m_imageMap;
}

bool SwImageMapDataObject::SetData(size_t size, const void * data )
{
    SwHtmlImageMap * p = (SwHtmlImageMap *) data;
    m_imageMap.Copy(*p);
    return true;
}
