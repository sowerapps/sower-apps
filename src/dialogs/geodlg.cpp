///////////////////////////////////////////////////////////////////
// Name:        geodlg.cpp
// Purpose:     Generate geo data for images of maps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/geodlg.h"
#include "../../include/geo/geolocation.h"
#include "../../include/imgwin/command.h"
#include "../../include/html/html_color.h"

const long SwGeoDlg::ID_LATITUDESTATICTEXT = wxNewId();
const long SwGeoDlg::ID_DEGREESSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_PXPOSSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_TOPSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_TOPTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_TOPPXTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_BOTTOMSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_BOTTOMTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_BOTTOMPXTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_LONGITUDESTATICTEXT = wxNewId();
const long SwGeoDlg::ID_LEFTSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_LEFTTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_LEFTPXTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_RIGHTSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_RIGHTTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_RIGHTPXTEXTCTRL = wxNewId();
const long SwGeoDlg::ID_GENERATEBUTTON = wxNewId();
const long SwGeoDlg::ID_DRAWCOLORSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_DRAWCOLORCHOICE = wxNewId();
const long SwGeoDlg::ID_FILLCOLORSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_FILLCOLORCHOICE = wxNewId();
const long SwGeoDlg::ID_RADIUSSTATICTEXT = wxNewId();
const long SwGeoDlg::ID_RADIUSTEXTCTRL = wxNewId();

SwGeoDlg::SwGeoDlg(SwImageWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_parent = parent;
    BuildContent(parent, id, pos, size);
}

void SwGeoDlg::BuildContent(wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxGridBagSizer* GridBagSizer1;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    LatitudeStaticText = new wxStaticText(this, ID_LATITUDESTATICTEXT, SwApplicationInterface::GetControlString("SID_LATITUDE", L"Latitude"), wxDefaultPosition, wxDefaultSize, 0, L"ID_LATITUDESTATICTEXT");
    GridBagSizer1->Add(LatitudeStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DegreesStaticText = new wxStaticText(this, ID_DEGREESSTATICTEXT, SwApplicationInterface::GetControlString("SID_DEGREES", L"Degrees"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DEGREESSTATICTEXT");
    GridBagSizer1->Add(DegreesStaticText, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PxPosStaticText = new wxStaticText(this, ID_PXPOSSTATICTEXT, SwApplicationInterface::GetControlString("SID_PIXELPOSITION", L"Pixel Position"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PXPOSSTATICTEXT");
    GridBagSizer1->Add(PxPosStaticText, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TopStaticText = new wxStaticText(this, ID_TOPSTATICTEXT, SwApplicationInterface::GetControlString("SID_TOP", L"Top"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TOPSTATICTEXT");
    GridBagSizer1->Add(TopStaticText, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TopTextCtrl = new wxTextCtrl(this, ID_TOPTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC), L"ID_TOPTEXTCTRL");
    GridBagSizer1->Add(TopTextCtrl, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TopPxTextCtrl = new wxTextCtrl(this, ID_TOPPXTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_TOPPXTEXTCTRL");
    GridBagSizer1->Add(TopPxTextCtrl, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BottomStaticText = new wxStaticText(this, ID_BOTTOMSTATICTEXT, SwApplicationInterface::GetControlString("SID_BOTTOM", L"Bottom"), wxDefaultPosition, wxDefaultSize, 0, L"ID_BOTTOMSTATICTEXT");
    GridBagSizer1->Add(BottomStaticText, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BottomTextCtrl = new wxTextCtrl(this, ID_BOTTOMTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC), L"ID_BOTTOMTEXTCTRL");
    GridBagSizer1->Add(BottomTextCtrl, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BottomPxTextCtrl = new wxTextCtrl(this, ID_BOTTOMPXTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_BOTTOMPXTEXTCTRL");
    GridBagSizer1->Add(BottomPxTextCtrl, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LongitudeStaticText = new wxStaticText(this, ID_LONGITUDESTATICTEXT, SwApplicationInterface::GetControlString("SID_LONGITUDE", L"Longitude"), wxDefaultPosition, wxDefaultSize, 0, L"ID_LONGITUDESTATICTEXT");
    GridBagSizer1->Add(LongitudeStaticText, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LeftStaticText = new wxStaticText(this, ID_LEFTSTATICTEXT, SwApplicationInterface::GetControlString("SID_LEFT", L"Left"), wxDefaultPosition, wxDefaultSize, 0, L"ID_LEFTSTATICTEXT");
    GridBagSizer1->Add(LeftStaticText, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftTextCtrl = new wxTextCtrl(this, ID_LEFTTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC), L"ID_LEFTTEXTCTRL");
    GridBagSizer1->Add(LeftTextCtrl, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftPxTextCtrl = new wxTextCtrl(this, ID_LEFTPXTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_LEFTPXTEXTCTRL");
    GridBagSizer1->Add(LeftPxTextCtrl, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RightStaticText = new wxStaticText(this, ID_RIGHTSTATICTEXT, SwApplicationInterface::GetControlString("SID_RIGHT", L"Right"), wxDefaultPosition, wxDefaultSize, 0, L"ID_RIGHTSTATICTEXT");
    GridBagSizer1->Add(RightStaticText, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RightTextCtrl = new wxTextCtrl(this, ID_RIGHTTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC), L"ID_RIGHTTEXTCTRL");
    GridBagSizer1->Add(RightTextCtrl, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RightPxTextCtrl = new wxTextCtrl(this, ID_RIGHTPXTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_RIGHTPXTEXTCTRL");
    GridBagSizer1->Add(RightPxTextCtrl, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    DrawColorStaticText = new wxStaticText(this, ID_DRAWCOLORSTATICTEXT, SwApplicationInterface::GetControlString("SID_DRAWCOLOR", L"Draw Color"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DRAWCOLORSTATICTEXT");
    GridBagSizer1->Add(DrawColorStaticText, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DrawColorChoice = new wxChoice(this, ID_DRAWCOLORCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_DRAWCOLORCHOICE");
    GridBagSizer1->Add(DrawColorChoice, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SwHtmlColor::GetColorList(DrawColorChoice);
    SwHtmlColor::SetColor(DrawColorChoice, 16711680);

    FillColorStaticText = new wxStaticText(this, ID_FILLCOLORSTATICTEXT, SwApplicationInterface::GetControlString("SID_FILLCOLOR", L"Fill Color"), wxDefaultPosition, wxDefaultSize, 0, L"ID_FILLCOLORSTATICTEXT");
    GridBagSizer1->Add(FillColorStaticText, wxGBPosition(6, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FillColorChoice = new wxChoice(this, ID_FILLCOLORCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_FILLCOLORCHOICE");
    GridBagSizer1->Add(FillColorChoice, wxGBPosition(7, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SwHtmlColor::GetColorList(FillColorChoice);
    SwHtmlColor::SetColor(FillColorChoice, 16777215);

    RadiusStaticText = new wxStaticText(this, ID_RADIUSSTATICTEXT, SwApplicationInterface::GetControlString("SID_RADIUS", L"Radius"), wxDefaultPosition, wxDefaultSize, 0, L"ID_RADIUSSTATICTEXT");
    GridBagSizer1->Add(RadiusStaticText, wxGBPosition(6, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadiusTextCtrl = new wxTextCtrl(this, ID_RADIUSTEXTCTRL, L"3", wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_RADIUSTEXTCTRL");
    GridBagSizer1->Add(RadiusTextCtrl, wxGBPosition(7, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    GenerateButton = new wxButton(this, ID_GENERATEBUTTON, SwApplicationInterface::GetControlString("SID_GENERATE", L"Generate"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_GENERATEBUTTON");
    GridBagSizer1->Add(GenerateButton, wxGBPosition(8, 2), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    SetDrawColor();
    SetFillColor();
    SetRadius();

    Connect(ID_GENERATEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwGeoDlg::OnGenerateButtonClick);

    SetLabel(SwApplicationInterface::GetControlString("SID_GEO", L"Geo"));
}

SwGeoDlg::~SwGeoDlg()
{
}

void SwGeoDlg::OnGenerateButtonClick(wxCommandEvent& event)
{
    SwMapArea area;
    SwPoint pt;
    SwGeoConversionData cd;

    if (!m_parent)
        return;

    SwClientData * data;
    int sel;

    sel = DrawColorChoice->GetSelection();
    data = (SwClientData *) DrawColorChoice->GetClientObject(sel);
    SetDrawColor(data->m_data);

    sel = FillColorChoice->GetSelection();
    data = (SwClientData *) FillColorChoice->GetClientObject(sel);
    SetFillColor(data->m_data);
    SetRadius(strtod(RadiusTextCtrl->GetValue().utf8_str(), NULL));

    double longLeft = strtod(LeftTextCtrl->GetValue().utf8_str(), NULL);
    swUI32 longpxLeft = strtoul(LeftPxTextCtrl->GetValue().utf8_str(), NULL, 10);
    double longRight = strtod(RightTextCtrl->GetValue().utf8_str(), NULL);
    swUI32 longpxRight = strtoul(RightPxTextCtrl->GetValue().utf8_str(), NULL, 10);
    double latTop = strtod(TopTextCtrl->GetValue().utf8_str(), NULL);
    swUI32 latpxTop = strtoul(TopPxTextCtrl->GetValue().utf8_str(), NULL, 10);
    double latBottom = strtod(BottomTextCtrl->GetValue().utf8_str(), NULL);
    swUI32 latpxBottom = strtoul(BottomPxTextCtrl->GetValue().utf8_str(), NULL, 10);

    double pxperdglat = (latpxBottom - latpxTop) / (latTop - latBottom);
    double pxperdglon = (longpxRight - longpxLeft) / (longRight - longLeft);

    swUI32 map = SetName();

    if (map == NODE_ID_INVALID)
        return;

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();
    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    SwHtmlImageMap * mapObj = m_parent->GetImageMapList().GetMap(map);

    cd.mapheight = m_parent->GetImage()->GetHeight();
    cd.mapwidth = m_parent->GetImage()->GetWidth();
    cd.longitudeLeft = longLeft - (longpxLeft / pxperdglon);
    cd.longitudeRight = longRight + ((cd.mapwidth - longpxRight) / pxperdglon);
    cd.latitudeTop = latTop + (latpxTop / pxperdglat);
    cd.latitudeBottom = latBottom - ((cd.mapheight - latpxBottom) / pxperdglat);

    SwMapArea * mapArea;
    for (swUI32 i = 1; i < N_GEO_LOCATIONS; i ++)
    {
        if (SwGeo::IsLocationValid(i, cd))
        {
            area.Reset();
            area.SetType(AREA_TYPE_CIRCLE);
            area.SetDrawColor(m_drawcolor);
            area.SetFillColor(m_fillcolor);
            area.SetAlt(SwGeo::GetData(i).name);
            SwGeo::GetMapLocation(i, cd, pt);
            mapArea = FindInMap(mapObj, pt);
            if (mapArea)
            {
                SwString buffer;
                buffer = mapArea->alt;
                buffer += "|";
                buffer += area.alt;
                mapArea->SetAlt(buffer);
            }
            else
            {
                SetPosition(mapObj, pt, m_radius);
                area.AddPoint(pt);
                pt.x = m_radius;
                pt.y = m_radius;
                area.AddPoint(pt);
                mapObj->AppendNode(area);
            }
        }
    }

    m_parent->GetImageMapList().GetConversionData() = cd;
    m_parent->Refresh();

    EndModal(1);
}

swUI32 SwGeoDlg::SetName()
{
    SwString buffer;
    buffer.Size(100);
    swUI32 map = NODE_ID_INVALID;

    for (int i = 1; i < 10000; i++)
    {
        sprintf(buffer, "Geo-%u", i);
        map = m_parent->GetImageMapList().FindMap(buffer);
        if (map == NODE_ID_INVALID)
        {
            map = m_parent->GetImageMapList().AddMap(buffer);
            if (map != NODE_ID_INVALID)
                return map;
        }
    }

    return NODE_ID_INVALID;
}

void SwGeoDlg::SetPosition(SwHtmlImageMap * mapObj, SwPoint & pt, swI32 radius)
{
    SwPoint p1;
    swI32 r = radius * 2;
    p1 = pt;

    if (!FindInMap(mapObj, p1))
        return;

    p1 = pt;
    p1.x -= r;
    p1.y -= r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.x -= r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.x -= r;
    p1.y += r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.y += r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.x += r;
    p1.y += r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.x += r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.x += r;
    p1.y -= r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }

    p1 = pt;
    p1.y += r;

    if (!FindInMap(mapObj, p1))
    {
        pt = p1;
        return;
    }
}

SwMapArea * SwGeoDlg::FindInMap(SwHtmlImageMap * mapObj, SwPoint pt)
{
    swUI32 nodeId = NODE_ID_INVALID;
    SwRect rc;
    rc.x = 0;
    rc.y = 0;
    rc.height = m_parent->GetImage()->GetHeight();
    rc.width = m_parent->GetImage()->GetWidth();

    nodeId = mapObj->FindMapAreaByPos(pt, 1, 0, 0, rc, 1);

    if (nodeId != NODE_ID_INVALID)
    {
        return mapObj->GetMapData(nodeId);
    }

    return NULL;
}

SwMapArea * SwGeoDlg::FindInMaps(SwPoint pt)
{
    swUI32 map = 0;
    swUI32 nodeId = NODE_ID_INVALID;
    SwRect rc;
    rc.x = 0;
    rc.y = 0;
    rc.height = m_parent->GetImage()->GetHeight();
    rc.width = m_parent->GetImage()->GetWidth();

    while (map < m_parent->GetImageMapList().GetMapCount())
    {
        nodeId = m_parent->GetImageMapList().m_mapArray[map]->FindMapAreaByPos(pt, 1, 0, 0, rc, 1);

        if (nodeId != NODE_ID_INVALID)
        {
            return m_parent->GetImageMapList().m_mapArray[map]->GetMapData(nodeId);
        }

        map ++;
    }

    return NULL;
}

void SwGeoDlg::SetDrawColor(swUI32 color)
{
    m_drawcolor = color;
}

void SwGeoDlg::SetFillColor(swUI32 color)
{
    m_fillcolor = color;
}

void SwGeoDlg::SetRadius(swUI8 radius)
{
    m_radius = radius;
}

