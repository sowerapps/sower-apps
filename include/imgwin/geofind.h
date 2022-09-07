///////////////////////////////////////////////////////////////////
// Name:        geofind.h
// Purpose:     Find functionality for locations within an image
//              of a map. Searching the alt text of SwMapArea's in
//              an ImageMap object. Optionally searching GeoLocation
//              also.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef GEOFIND_H
#define GEOFIND_H

#include "../sowerbase.h"
#include "../string/string.h"
#include "../string/stringcompare.h"
#include "../html/html_imagemap.h"
#include "imagewindow.h"

class SOWERBASEEXP SwGeoFind
{
public:
    SwGeoFind();
    virtual ~SwGeoFind();

    void Reset();
    void SetView(SwImageWindow * imgwin);
    void SetCaseSensitive(bool casesensitive);
    void SetWholeWordOnly(bool wholewordonly);
    bool Find(const char * location, bool casesensitive, bool wholewordonly);
    bool FindNext();

private:
    bool FindInImageMaps();
    bool FindInGeo();

    bool          m_casesensitive;
    bool          m_wholewordonly;
    swI8          m_flags;
    SwString      m_original;
    bool          m_haveTranslation;
    SwString      m_translation;
    SwStringCompare m_compObj;
    SwImageWindow * m_view;
    bool          m_lastfindwasGeo;
    swUI32        m_lastfindMapNode;
    swUI32        m_lastfindMapAreaNode;
};

#endif // GEOFIND_H
