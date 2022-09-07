///////////////////////////////////////////////////////////////////
// Name:        imagewindow.cpp
// Purpose:     A window which can display images, edit image maps.
//              Provide users with information through AutoDef windows
//              and tool tip windows. 'Alt' text for map areas can be
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

#include "../../include/imgwin/imagewindow.h"
#include "../../include/html/html.h"
#include "../../include/html/html_color.h"
#include "../../include/html/html_imagemap.h"
#include "../../include/imgwin/command.h"
#include "../../include/appi/appifa.h"
#include <wx/mstream.h>

SwImageWindow::SwImageWindow()
{
    Init();
}

SwImageWindow::SwImageWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxScrolledCanvas(parent, id, pos, size, wxVSCROLL | wxHSCROLL)
{
    Init();
}

void SwImageWindow::Init()
{
    wxFont thisFont(8,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    m_image = NULL;
    m_menu = NULL;
    m_eventHandler = NULL;
    m_allowclickActivate = false;
    m_drawmapList = true;
    m_showTips = true;
    m_enableAutoDef = true;
    m_allowDrag = false;
    m_showMenu = false;
    m_iseditMode = false;
    m_autodefwindow = new SwAutoDefWindow(this, wxNewId(), "", wxPoint(0,0), wxSize(0, 0));
    m_autodefwindow->Show(false);
    m_tipWindow = new wxStaticText(this, wxNewId(), "", wxPoint(0, 0), wxSize(0, 0), wxBORDER_SIMPLE);
    m_tipWindow->Show(false);
    m_tipWindow->SetBackgroundColour("WHITE");
    m_tipWindow->SetForegroundColour("BLACK");
    m_hasImage = false;
    SetBackgroundColour(*wxWHITE);

    Bind(wxEVT_MOTION,&SwImageWindow::OnMouseMove,this);
    Bind(wxEVT_PAINT, &SwImageWindow::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN,&SwImageWindow::OnLeftDown,this);
    Bind(wxEVT_LEFT_UP,&SwImageWindow::OnLeftUp,this);
    Bind(wxEVT_RIGHT_DOWN,&SwImageWindow::OnRightDown,this);
    Bind(wxEVT_RIGHT_UP,&SwImageWindow::OnRightUp,this);
    Bind(wxEVT_KILL_FOCUS,&SwImageWindow::OnKillFocus,this);
    m_timer.m_imgwin = this;
    m_commandProcessor.Initialize();
    m_buffer.Size(32768);
    m_parser.SetDeliminator('|');
    Reset();
}

SwImageWindow::~SwImageWindow()
{
    Unbind(wxEVT_MOTION,&SwImageWindow::OnMouseMove,this);
    Unbind(wxEVT_PAINT, &SwImageWindow::OnPaint, this);
    Unbind(wxEVT_LEFT_DOWN,&SwImageWindow::OnLeftDown,this);
    Unbind(wxEVT_LEFT_UP,&SwImageWindow::OnLeftUp,this);
    Unbind(wxEVT_RIGHT_DOWN,&SwImageWindow::OnRightDown,this);
    Unbind(wxEVT_RIGHT_UP,&SwImageWindow::OnRightUp,this);
    Unbind(wxEVT_KILL_FOCUS,&SwImageWindow::OnKillFocus,this);

    m_mdc.SelectObject(wxNullBitmap);

    if (m_image)
        delete m_image;

    if (m_tipWindow)
        delete m_tipWindow;

    if (m_autodefwindow)
        delete m_autodefwindow;
}

void SwImageWindow::Reset()
{
    m_zoom = 1;
    m_czoom = 0;
    m_isautodefLoaded = false;
    m_isHot = false;
    m_hotmapArea = NULL;
    m_leftdownmapArea = NULL;
    m_rightdownmapArea = NULL;
    m_hasLocation = false;
    m_mdc.SelectObject(wxNullBitmap);
    m_locationPt.x = 0;
    m_locationPt.y = 0;
    m_isdragging = false;
    m_isediting = false;
    m_ismenuVisible = false;
    m_autodefwindow->Hide();
    m_tipWindow->Hide();
    m_modified = 0;
    m_canCopy = true;
    m_commandProcessor.ClearCommands();
    Scroll(0, 0);
    m_mapList.DeleteMapObjects();
    m_drawAreas.Reset();
    Clear();
    m_title.Reset();
    m_basePath.Reset();
    m_managerId = NODE_ID_INVALID_16;
    m_mapList.GetConversionData().Reset();
    Refresh();
}

void SwImageWindow::UpdateMenu()
{
}

void SwImageWindow::ShowMenu()
{
    if (m_menu && m_showMenu)
    {
        PopupMenu(m_menu);
    }
}

void SwImageWindow::OnLanguageChange()
{
}

void SwImageWindow::OnKillFocus(wxFocusEvent& event)
{
    m_isdragging = false;
    m_isediting = false;
    event.Skip();
}

void SwImageWindow::OnOpen(wxCommandEvent& event)
{
}

void SwImageWindow::OnClose(wxCommandEvent& event)
{
}

void SwImageWindow::OnSave(wxCommandEvent& event)
{
}

void SwImageWindow::Clear()
{
    if (m_image)
    {
        delete m_image;
        m_image = NULL;
    }

    char image[1] = {'0'};
    m_image = new wxBitmap(image, 1, 1, 1);
    m_hasImage = false;
}
