///////////////////////////////////////////////////////////////////
// Name:        command.h
// Purpose:     Undo/Redo Functionality editing in ImageWindows.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef COMMAND_H
#define COMMAND_H

#include "../sowerbase.h"
#include "../html/html_imagemap.h"
#include <wx/cmdproc.h>

class SOWERBASEEXP SwCommandUpdateMapList : public wxCommand
{
public:
    SwCommandUpdateMapList();
    SwCommandUpdateMapList(const wxString& name, SwHtmlImageMapList * imagemapList1, SwHtmlImageMapList * imagemapList2);
    virtual ~SwCommandUpdateMapList();

    virtual bool CanUndo ();
    virtual bool Do();
    virtual bool Undo();

protected:
    SwHtmlImageMapList * m_imagemapList1;
    SwHtmlImageMapList * m_imagemapList2;
};

static wchar_t MapAreaFormat[] = L"SwMapArea";
static wchar_t ImageMapFormat[] = L"SwHtmlImageMap";

class SOWERBASEEXP SwMapAreaDataObject : public wxCustomDataObject
{
public:
    SwMapAreaDataObject(const wxDataFormat &format=MapAreaFormat);
    virtual ~SwMapAreaDataObject();

    virtual size_t GetSize()const;
    virtual void * GetData()const;
    virtual bool SetData(size_t size, const void * data );

    SwMapArea m_mapData;
};

class SOWERBASEEXP SwImageMapDataObject : public wxCustomDataObject
{
public:
    SwImageMapDataObject(const wxDataFormat &format=ImageMapFormat);
    virtual ~SwImageMapDataObject();

    virtual size_t GetSize() const;
    virtual void * GetData() const;
    virtual bool SetData(size_t size, const void * data );

    SwHtmlImageMap m_imageMap;
};

#endif // COMMAND_H
