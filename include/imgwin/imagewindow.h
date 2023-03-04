///////////////////////////////////////////////////////////////////
// Name:        imagewindow.h
// Purpose:     A window which can display images, edit image maps.
//              Provide users with information through AutoDef windows
//              and tool tip windows. Alt text for hotspots can be
//              translated to display place names in the language set
//              for the gui interface, and also used by AutoDef to
//              locate information in Sower modules and provided to
//              the user. Paths can be created and drawn from a
//              list of names that match the alt text in map areas.
//              Images can be associated with map areas and drawn
//              over the primary image.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include "../sowerbase.h"
#include "../string/string.h"
#include "../string/stringw.h"
#include "../array/pointarray.h"
#include "../array/uintarray.h"
#include "../filesys/streambuffer.h"
#include "../html/html_imagemap.h"
#include "../sdf/datafile.h"
#include "../module/module.h"
#include "../richtext/autodefwindow.h"
#include "../framework/menubar.h"
#include "imageprint.h"
#include <wx/cmdproc.h>

class SwMenu;
class SOWERBASEEXP SwMapItemData
{
public :
    SwMapItemData()
    {
        hotMap = NULL;
        hotItem = NULL;
        ishot = false;
    }
    virtual ~SwMapItemData() {}

    SwHtmlImageMap * hotMap;
    SwMapArea *      hotItem;
    bool           ishot;
};

class SOWERBASEEXP SwImageDataWx : public SwImageData
{
public :
    SwImageDataWx()
    {
        bitmap = NULL;
    }
    virtual ~SwImageDataWx() {}
    virtual SwImageDataWx * Clone();

    virtual bool IsOk();
    virtual int GetHeight();
    virtual int GetWidth();

    wxBitmap * bitmap;
};

class SwImageWindow;
class SOWERBASEEXP SwImageMapEventHandler
{
public:
    SwImageMapEventHandler() {};
    virtual ~SwImageMapEventHandler() {};
    virtual void OnImageHotSpotLeftClick(SwImageWindow * imageWindow, SwMapArea * mapData) {};
};

class SOWERBASEEXP SwHoverTimer : public wxTimer
{
public:
    SwHoverTimer();
    virtual ~SwHoverTimer();
    virtual void Notify();

    SwImageWindow * m_imgwin;
};

class SwAutoDefWindow;
class SOWERBASEEXP SwImageWindow : public wxScrolledCanvas
{
    friend class SwImagePrint;
public:
    SwImageWindow();
    SwImageWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxPanelNameStr);
    virtual ~SwImageWindow();

    void Reset();
    bool GetIsEditMode();
    void SetIsEditMode(bool iseditMode);
    void SetStandardEditMode(bool mode) { m_iseditMode = true; m_allowDrag = true; }
    bool GetShowTips();
    void SetShowTips(bool showTips);
    virtual bool LoadTipText(SwMapArea & mapData);
    virtual bool LoadTipText(const char * str);
    void ShowTip(wxPoint position);
    bool GetAllowDrag();
    void SetAllowDrag(bool allowDrag);
    bool GetShowMenu();
    void SetShowMenu(bool showMenu);
    virtual void UpdateMenu();
    virtual void ShowMenu();
    bool IsAutoDefEnabled();
    void EnableAutoDef(bool enableAutoDef);
    virtual bool LoadAutoDefText(SwMapArea & mapData);
    virtual bool LoadAutoDefText(const char * str);
    void ShowAutoDef(int top, int bottom);
    bool GetDrawMapList();
    void SetDrawMapList(bool drawmapList);
    bool GetAllowClickActivate();
    void SetAllowClickActivate(bool allowclickActivate);
    bool GetHasLocation();
    void SetHasLocation(bool hasLocation);
    wxPoint GetLocation();
    void SetLocation(wxPoint location);
    void ScrollToLocation();
    void ScrollToLocation(SwScrollData & scrolldata);
    void GetScrollPosition(SwScrollData & scrolldata);
    SwHtmlImageMapList & GetImageMapList();
    SwHtmlImageMap & GetDrawAreaImageMap();
    SwImageMapEventHandler * GetEventHandler();
    void SetEventHandler(SwImageMapEventHandler * eventHandler);
    void UpdateDragMapList();
    void OnLanguageChange();
    virtual void OnZoomIn();
    virtual void OnZoomOut();
    virtual void OnViewNormal();
    swFloat GetZoom();
    virtual void SetZoom(swFloat zoom);
    virtual void OnKillFocus(wxFocusEvent& event);
    virtual void OnLeftDown(wxMouseEvent& event);
    virtual void OnLeftUp(wxMouseEvent& event);
    virtual void OnLeftClick(SwMapArea * mapData) {};
    virtual void OnRightDown(wxMouseEvent& event);
    virtual void OnRightUp(wxMouseEvent& event);
    virtual void OnRightClick(SwMapArea * mapData) {};
    void OnPrint(const wchar_t * title);
    bool LoadImage(const char * path);
    bool LoadImage(Swui8Array & buffer);
    bool LoadImage(SwStreamBuffer & buffer);
    static wxBitmap * GetImage(const unsigned char *data, int len);
    static wxBitmap * GetImage(const wchar_t * path);
    void OnPaint(wxPaintEvent& event);
    void DrawMapAreas(wxDC & dc, swFloat zoom, swUI32 cx, swUI32 cy);
    void DrawImageMap(SwHtmlImageMap & imageMap, wxPen & pen, wxBrush & brush, wxDC & dc, swFloat zoom, swUI32 originX, swUI32 originY, bool drawAreas = false);
    virtual void OnMarkItem(wxCommandEvent& event);
    virtual void OnUnMarkItem(wxCommandEvent& event);

    virtual void OnMouseMove(wxMouseEvent& event);
    virtual void OnMouseHover(wxPoint & clientPos);
    swUI32 CheckDrawAreas(SwMapItemData & itemData, SwPoint & pt, wxPoint & scrollPos, SwRect & rc);
    swUI32 CheckImageMaps(SwMapItemData & itemData, SwPoint & pt, wxPoint & scrollPos, SwRect & rc);
    void SetHotCursor(bool ishot);

    virtual void OnCopyMap(SwHtmlImageMap & imageMap);
    virtual void OnCopyMapArea(SwMapArea & mapData);
    virtual void OnPaste();

    virtual void OnOpen(wxCommandEvent& event);
    virtual void OnClose(wxCommandEvent& event);
    virtual void OnSave(wxCommandEvent& event);
    void Clear();
    wxCommandProcessor & GetCommandProcessor();

    bool GetCanCopy()
    {
        return m_canCopy;
    }

    void SetCanCopy(bool canCopy)
    {
        m_canCopy = canCopy;
    }

    void SetTitle(const char * title)
    {
        if (!title)
            return;
        m_title = title;
    }

    const char * GetTitle()
    {
        return m_title;
    }

    void SetBasePath(const char * path)
    {
        if (!path)
            return;
        m_basePath = path;
    }

    const char * GetBasePath()
    {
        return m_basePath;
    }

    void SetManagerId(swUI16 id)
    {
        m_managerId = id;
    }

    swUI16 GetManagerId()
    {
        return m_managerId;
    }

    void SetPopUpMenu(SwMenu * menu)
    {
        if (menu)
            m_showMenu = true;

        m_menu = menu;
    }

    static void DrawSolidRectangle(wxDC & dc, wxCoord x, wxCoord y, wxCoord width, wxCoord height);
    SwImageData * GetAreaImage(const char * src);
    void OnTimer();

    bool HasImage() { return m_hasImage; }
    wxBitmap * GetImage() { return m_image; }

    void ClearHotAreas()
    {
        m_hotmapArea = NULL;
        m_hotMap = NULL;
        m_leftdownmapArea = NULL;
        m_rightdownMap = NULL;
        m_rightdownmapArea = NULL;
        m_hasLocation = false;
    }

protected:
    SwHoverTimer              m_timer;
    wxPoint                   m_lastmousePos;
    long                      m_mouseCount;
    wxStaticText *            m_tipWindow;
    wxBitmap *                m_image;
    wxMemoryDC                m_mdc;
    SwPointArray              m_pt;
    SwPointArray              m_p2polyBuffer;
    SwStringW                 m_tipText;
    swFloat                   m_zoom;
    swFloat                   m_czoom;
    SwMapArea *               m_hotmapArea;
    SwHtmlImageMap *          m_hotMap;
    SwMapArea *               m_leftdownmapArea;
    SwHtmlImageMap *          m_rightdownMap;
    SwMapArea *               m_rightdownmapArea;
    SwMenu *                  m_menu;
    SwAutoDefWindow *         m_autodefwindow;
    SwString                  m_autodefText;
    wxPoint                   m_dragPoint;
    SwStrParser               m_parser;
    SwStringWArray            m_strarray;
    bool                      m_canCopy;
    bool                      m_iseditMode;
    bool                      m_showTips;
    bool                      m_allowDrag;
    bool                      m_showMenu;
    bool                      m_enableAutoDef;
    bool                      m_drawmapList;
    bool                      m_allowclickActivate;
    bool                      m_hasLocation;
    wxPoint                   m_locationPt;
    SwHtmlImageMapList        m_mapList;
    SwHtmlImageMap            m_drawAreas;
    SwImageMapEventHandler *  m_eventHandler;
    wxCommandProcessor        m_commandProcessor;
    bool                      m_hasImage;
    bool                      m_isHot;
    bool                      m_isautodefLoaded;
    bool                      m_ismenuVisible;
    bool                      m_isdragging;
    bool                      m_isediting;
    bool                      m_painted;
    bool                      m_ishotspotdrawArea;
    swUI32                    m_modified;
    SwMapArea                 m_editmapData;
    SwString                  m_title;
    SwString                  m_basePath;
    swUI16                    m_managerId;
    SwString                  m_buffer;

private:
    void Init();
};

#endif // IMAGEWINDOW_H
