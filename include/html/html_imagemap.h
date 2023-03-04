///////////////////////////////////////////////////////////////////
// Name:        html_imagemap.h
// Purpose:     Image maps, and lists of image maps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HTML_IMAGEMAP_H
#define HTML_IMAGEMAP_H

#include "../sowerbase.h"
#include "../string/string.h"
#include "../array/pointarray.h"
#include "../module/moduleinterface.h"
#include "../geo/geolocation.h"
#include <wx/listctrl.h>

class SOWERBASEEXP SwImageData
{
    public :
    SwImageData();
    virtual ~SwImageData();

    virtual SwImageData * Clone();
    virtual bool IsOk();
    virtual int GetHeight();
    virtual int GetWidth();
};

class SwHtmlImageMap;
class SOWERBASEEXP SwMapArea
{
    public :
    SwMapArea();
    virtual ~SwMapArea();

    swUI8               type;
    char *              href;
    char *              alt;
    char *              src;
    swUI32              points;
    SwPoint *           mapPoints;
    swUI32              drawColor;
    swUI32              fillColor;
    bool                isclickItem;
    bool                marked;
    SwImageData *       bitMap;

    void Init();
    void Reset();
    void ReleaseBuffers();
    swUI8 GetType();
    void SetType(swUI8 maptype);
    const char * GetHref();
    void SetHref(const char * hrefstring);
    const char * GetAlt();
    void SetAlt(const char * altstring);
    const char * GetSrc();
    void SetSrc(const char * srcstring);
    swUI32 GetDrawColor();
    void SetDrawColor(const char * drawcolor);
    void SetDrawColor(swUI32 drawcolor);
    swUI32 GetFillColor();
    void SetFillColor(const char * fillcolor);
    void SetFillColor(swUI32 fillcolor);
    bool GetMarked();
    void MarkItem(bool state);
    bool GetIsClickItem();
    void SetIsClickItem(bool isclickitem);
    SwImageData * GetBitmap();
    swUI32 GetPoints();
    void SetBitmap(SwImageData * bitmap);
    bool SizePointArray(swUI32 npoints);
    SwPoint GetAt(swUI32 pos);
    bool SetPointAt(swUI32 pos, SwPoint & point);
    bool AddPoint(SwPoint point);
    bool RemoveLastPoint();
    void Copy(SwMapArea & mapData);
    bool InsertPointAt(swUI32 pointPos, SwPoint point);
    bool DeletePoint(swUI32 pointPos);
};

/*
    For drawable images:
    stock:image-identifier
    theme:table-name:image-identifier
    module:module-identifier:image-identifier
    file:image-identifier
    * For 'file:' image-identifier must be a relative file path, or name of image in module associated
    with the image in the SwImageWindow.
*/

class SwMapArea;
class SOWERBASEEXP SwHtmlImageMap : public SwModuleInterface
{
public:
    SwHtmlImageMap();
    SwHtmlImageMap(SwHtmlImageMap & imageMap);
    virtual ~SwHtmlImageMap();

    void Reset();
    void Copy(SwHtmlImageMap & imageMap);
    const char * GetName();
    void SetName(const char * name);
    void SetPathWidth(swUI16 width);
    swUI16 GetPathWidth();
    void SetMapType(swUI8 type);
    swUI8 GetMapType();
    swUI32 AppendNode(SwMapArea & mapData);
    swUI32 AppendNode(const char * alt, const char * href, const char * src, swUI8 type, swUI32 points);
    SwMapArea * GetMapData(swUI32 mapNode);
    void ReplaceNode(swUI32 mapNode, SwMapArea & mapData);
    bool InsertNode(swUI32 nodePos, SwMapArea & mapData);
    void DeleteNode(swUI32 mapNode);
    void DeleteMapData();
    swUI32 FindMapAreaByhref(const char * href);
    swUI32 FindMapAreaBySrc(const char * src);
    swUI32 FindMapAreaByalt(const char * alt);
    swUI32 FindMapAreaByPos(SwPoint mousePos, float scale, long scrollPosX, long scrollPosY, SwRect objectRect, float objectRatio);
    swUI32 GetLastMapNode();
    swUI32 GetMapNodeCount();
    swUI32 AssignMapDataNode();
    bool IncreaseImgMapDataBuffer();
    void ReleaseMapDataBuffer();
    bool IsPointInPolygon(SwPoint * source, swUI32 points, SwPoint mousePos, float scale, float objectRatio, SwRect objectRect);
    static swUI32 PathToPolygon(const SwPoint * source, swUI32 points, SwPointArray & destination, swUI32 width);
    static float Distance(SwPoint pointA, SwPoint pointB);
    static float Distance(SwPoint point, SwPoint mousePos, float scale);
    static void FindInsertionPoint(SwMapArea & mapData, SwPoint insertPoint, swUI32 & insPoint1, swUI32 & insPoint2);
    static void FindInsertionPoint(SwMapArea & mapData, SwPoint insertPoint, swUI32 & insPoint1, swUI32 & insPoint2, float scale);
    bool FindCenter(swUI32 node, SwPoint & center);
    bool FindCenter(SwPoint & center, const SwPoint * source, swUI32 points, swUI8 areaType);
    virtual void ResetMarked();
    void DeleteBitMaps();
    swUI32 CreatePath(const char * places, SwMapArea & mapArea, bool breakonMissing = false);
    void UpdateMapData(SwMapArea & mapData, int diffX, int diffY);
    void OffSetMap(int diffX, int diffY);
    void CreatePolygonFromMapNodes(SwMapArea & mapArea);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, const swUI8 k1, const swUI32 k2);
    virtual swUI32 GetType();
    void FillCtrl(wxListCtrl * listctrl);

    SwMapArea *           m_mapData;

protected:
    char *                m_name;
    swUI32                m_mapnodePos;
    swUI32                m_mapnodesAllocated;
    swUI16                m_pathWidth;
    SwPointArray          m_pointArray;
    swUI8                 m_mapType;
};

struct SwImgListSwap
{
    swUI32              m_maparrayPos;
    swUI32              m_mapobjectsAllocated;
    SwHtmlImageMap **   m_mapArray;
};

class SOWERBASEEXP SwHtmlImageMapList : public SwModuleInterface
{
public:
    SwHtmlImageMapList();
    virtual ~SwHtmlImageMapList();

    void Copy(SwHtmlImageMapList & imagemapList);
    bool IncreaseMapArray();
    void ReleaseMapArray();
    swUI32 AssignMapObject();
    swUI32 AddMap(const char * name);
    void DeleteMap(swUI32 mapId);
    void DeleteMapObjects();
    bool SetMapName(swUI32 mapId, const char * name);
    const char * GetMapName(swUI32 mapId);
    swUI32 FindMap(const char * name);
    SwHtmlImageMap * GetMap(swUI32 mapId);
    swUI32 GetMapCount();
    void ResetMarked();
    void DeleteBitMaps();
    swUI32 CreatePath(const char * places, SwMapArea & mapArea, bool breakonMissing = false);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual swUI32 GetType();
    void FillCtrl(wxListCtrl * listctrl);
    void FillCtrlEx(wxListCtrl * listctrl);
    void SetUseGeo(bool useGeo = true) { m_useGeo = useGeo; }
    bool GetUseGeo() { return m_useGeo; }
    void SetConversionData(const SwGeoConversionData & cd) { m_geocd = cd; }
    SwGeoConversionData & GetConversionData() { return m_geocd; }

    void GetSwapData(SwImgListSwap * swap)
    {
        swap->m_mapArray = m_mapArray;
        swap->m_maparrayPos = m_maparrayPos;
        swap->m_mapobjectsAllocated = m_mapobjectsAllocated;
    }

    void Swap(SwImgListSwap * swap)
    {
        m_maparrayPos = swap->m_maparrayPos;
        m_mapobjectsAllocated = swap->m_mapobjectsAllocated;
        m_mapArray = swap->m_mapArray;
    }

    SwHtmlImageMap **   m_mapArray;

protected:
    swUI32              m_maparrayPos;
    swUI32              m_mapobjectsAllocated;
    SwString            m_basePath;
    swUI16              m_managerId;
    SwGeoConversionData m_geocd;
    bool                m_useGeo;
};

#endif // IMAGEMAP_H
