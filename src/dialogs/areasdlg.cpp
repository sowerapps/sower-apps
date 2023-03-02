///////////////////////////////////////////////////////////////////
// Name:        areasdlg.cpp
// Purpose:     Manage MapAreas in HtmlImageMaps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/areasdlg.h"
#include "../../include/imgwin/command.h"

const long SwAreaDlg::ID_MAPSSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_MAPSLISTCTRL = wxNewId();
const long SwAreaDlg::ID_AREASSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_AREASLISTCTRL = wxNewId();
const long SwAreaDlg::ID_NAMESTATICTEXT = wxNewId();
const long SwAreaDlg::ID_NAMETEXTCTRL = wxNewId();
const long SwAreaDlg::ID_DRAWCOLORSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_DRAWCOLORCHOICE = wxNewId();
const long SwAreaDlg::ID_FILLCOLORSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_FILLCOLORCHOICE = wxNewId();
const long SwAreaDlg::ID_POSITIONSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_XSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_XTEXTCTRL = wxNewId();
const long SwAreaDlg::ID_YSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_YTEXTCTRL = wxNewId();
const long SwAreaDlg::ID_RADIUSSTATICTEXT = wxNewId();
const long SwAreaDlg::ID_RADIUSTEXTCTRL = wxNewId();
const long SwAreaDlg::ID_NEWAREABUTTON = wxNewId();
const long SwAreaDlg::ID_DELETEAREABUTTON = wxNewId();
const long SwAreaDlg::ID_UPDATEBUTTON = wxNewId();

SwAreaDlg::SwAreaDlg(SwImageWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_parent = parent;
    BuildContent(parent, id, pos, size);
}

void SwAreaDlg::BuildContent(wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    wxGridBagSizer* GridBagSizer1;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    GridBagSizer1 = new wxGridBagSizer(0, 0);

    MapsStaticText = new wxStaticText(this, ID_MAPSSTATICTEXT, SwApplicationInterface::GetControlString("SID_MAPS", L"Maps"), wxDefaultPosition, wxDefaultSize, 0, L"ID_MAPSSTATICTEXT");
    GridBagSizer1->Add(MapsStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    MapsListCtrl = new SwStretchColumnListCtrl(this, ID_MAPSLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_NO_HEADER, wxDefaultValidator, L"ID_MAPSLISTCTRL");
    MapsListCtrl->wxListCtrl::AppendColumn("");
    GridBagSizer1->Add(MapsListCtrl, wxGBPosition(1, 0), wxGBSpan(7, 2), wxALL|wxEXPAND, 5);

    AreasStaticText = new wxStaticText(this, ID_AREASSTATICTEXT, SwApplicationInterface::GetControlString("SID_AREAS", L"Areas"), wxDefaultPosition, wxDefaultSize, 0, L"ID_AREASSTATICTEXT");
    GridBagSizer1->Add(AreasStaticText, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    AreasListCtrl = new SwStretchColumnListCtrl(this, ID_AREASLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_NO_HEADER, wxDefaultValidator, L"ID_AREASLISTCTRL");
    AreasListCtrl->wxListCtrl::AppendColumn("");
    GridBagSizer1->Add(AreasListCtrl, wxGBPosition(1, 2), wxGBSpan(7, 2), wxALL|wxEXPAND, 5);

    NameStaticText = new wxStaticText(this, ID_NAMESTATICTEXT, SwApplicationInterface::GetControlString("SID_NAME", L"Name"), wxDefaultPosition, wxDefaultSize, 0, L"ID_NAMESTATICTEXT");
    GridBagSizer1->Add(NameStaticText, wxGBPosition(1, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    NameTextCtrl = new wxTextCtrl(this, ID_NAMETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_NAMETEXTCTRL");
    GridBagSizer1->Add(NameTextCtrl, wxGBPosition(1, 5), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);

    DrawColorStaticText = new wxStaticText(this, ID_DRAWCOLORSTATICTEXT, SwApplicationInterface::GetControlString("SID_DRAWCOLOR", L"Draw Color"), wxDefaultPosition, wxDefaultSize, 0, L"ID_DRAWCOLORSTATICTEXT");
    GridBagSizer1->Add(DrawColorStaticText, wxGBPosition(2, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DrawColorChoice = new wxChoice(this, ID_DRAWCOLORCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_DRAWCOLORCHOICE");
    GridBagSizer1->Add(DrawColorChoice, wxGBPosition(2, 5), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);
    SwHtmlColor::GetColorList(DrawColorChoice);

    FillColorStaticText = new wxStaticText(this, ID_FILLCOLORSTATICTEXT, SwApplicationInterface::GetControlString("SID_FILLCOLOR", L"Fill Color"), wxDefaultPosition, wxDefaultSize, 0, L"ID_FILLCOLORSTATICTEXT");
    GridBagSizer1->Add(FillColorStaticText, wxGBPosition(3, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FillColorChoice = new wxChoice(this, ID_FILLCOLORCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_FILLCOLORCHOICE");
    GridBagSizer1->Add(FillColorChoice, wxGBPosition(3, 5), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);
    SwHtmlColor::GetColorList(FillColorChoice);

    PositionStaticText = new wxStaticText(this, ID_POSITIONSTATICTEXT, SwApplicationInterface::GetControlString("SID_POSITION", L"Position"), wxDefaultPosition, wxDefaultSize, 0, L"ID_POSITIONSTATICTEXT");
    GridBagSizer1->Add(PositionStaticText, wxGBPosition(4, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    XStaticText = new wxStaticText(this, ID_XSTATICTEXT, L"X", wxDefaultPosition, wxDefaultSize, 0, L"ID_XSTATICTEXT");
    GridBagSizer1->Add(XStaticText, wxGBPosition(5, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    XTextCtrl = new wxTextCtrl(this, ID_XTEXTCTRL, "", wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_XTEXTCTRL");
    XTextCtrl->SetMinSize(wxSize(65, -1));
    GridBagSizer1->Add(XTextCtrl, wxGBPosition(5, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    YStaticText = new wxStaticText(this, ID_YSTATICTEXT, L"Y", wxDefaultPosition, wxDefaultSize, 0, L"ID_YSTATICTEXT");
    GridBagSizer1->Add(YStaticText, wxGBPosition(6, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    YTextCtrl = new wxTextCtrl(this, ID_XTEXTCTRL, "", wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_YTEXTCTRL");
    YTextCtrl->SetMinSize(wxSize(65, -1));
    GridBagSizer1->Add(YTextCtrl, wxGBPosition(6, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    RadiusStaticText = new wxStaticText(this, ID_RADIUSSTATICTEXT, SwApplicationInterface::GetControlString("SID_RADIUS", L"Radius"), wxDefaultPosition, wxDefaultSize, 0, L"ID_RADIUSSTATICTEXT");
    GridBagSizer1->Add(RadiusStaticText, wxGBPosition(7, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RadiusTextCtrl = new wxTextCtrl(this, ID_RADIUSTEXTCTRL, "3", wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_DIGITS), L"ID_YTEXTCTRL");
    RadiusTextCtrl->SetMinSize(wxSize(65, -1));
    GridBagSizer1->Add(RadiusTextCtrl, wxGBPosition(7, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);

    NewAreaButton = new wxButton(this, ID_NEWAREABUTTON, SwApplicationInterface::GetControlString("SID_NEW", L"New"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_NEWAREABUTTON");
    GridBagSizer1->Add(NewAreaButton, wxGBPosition(1, 7), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    DeleteAreaButton = new wxButton(this, ID_DELETEAREABUTTON, SwApplicationInterface::GetControlString("SID_DELETE", L"Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_DELETEAREABUTTON");
    GridBagSizer1->Add(DeleteAreaButton, wxGBPosition(2, 7), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    UpdateButton = new wxButton(this, ID_UPDATEBUTTON, SwApplicationInterface::GetControlString("SID_UPDATE", L"Update"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_UPDATEBUTTON");
    GridBagSizer1->Add(UpdateButton, wxGBPosition(3, 7), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    if (m_parent)
    {
        m_parent->GetImageMapList().FillCtrl(MapsListCtrl);
    }

    m_map = NODE_ID_INVALID;
    m_area = NODE_ID_INVALID;

    Connect(ID_MAPSLISTCTRL,wxEVT_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwAreaDlg::OnMapListCtrlItemSelect);
    Connect(ID_AREASLISTCTRL,wxEVT_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwAreaDlg::OnAreaListCtrlItemSelect);
    Connect(ID_NEWAREABUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAreaDlg::OnNewAreaButtonClick);
    Connect(ID_DELETEAREABUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAreaDlg::OnDeleteAreaButtonClick);
    Connect(ID_UPDATEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAreaDlg::OnUpdateButtonClick);
    SetLabel(SwApplicationInterface::GetControlString("SID_MAPAREAS", L"Map Areas"));
}

SwAreaDlg::~SwAreaDlg()
{
    if (m_parent)
        m_parent->Refresh();
}

void SwAreaDlg::OnMapListCtrlItemSelect(wxListEvent& event)
{
    AreasListCtrl->DeleteAllItems();
    ClearAreaData();
    int item = event.m_itemIndex;
    SwHtmlImageMap * map = (SwHtmlImageMap *) MapsListCtrl->GetItemData(item);
    if (map)
    {
        map->FillCtrl(AreasListCtrl);
        m_map = item;
    }
}

void SwAreaDlg::OnAreaListCtrlItemSelect(wxListEvent& event)
{
    ClearAreaData();
    int item = event.m_itemIndex;
    SwMapArea * area = (SwMapArea *) AreasListCtrl->GetItemData(item);

    if (area)
    {
        m_area = item;
        NameTextCtrl->SetValue(area->GetAlt());
        SwHtmlColor::SetColor(DrawColorChoice, area->GetDrawColor());
        SwHtmlColor::SetColor(FillColorChoice, area->GetFillColor());

        if (area->GetPoints() < 2)
            return;

        char s[100];

        sprintf(s, "%i", area->GetAt(0).x);
        XTextCtrl->SetValue(s);

        sprintf(s, "%i", area->GetAt(0).y);
        YTextCtrl->SetValue(s);

        sprintf(s, "%i", area->GetAt(1).x);
        RadiusTextCtrl->SetValue(s);
    }
}

void SwAreaDlg::ClearAreaData()
{
    NameTextCtrl->SetValue("");
    SwHtmlColor::SetColor(DrawColorChoice, 16711680);
    SwHtmlColor::SetColor(FillColorChoice, 16777215);
    XTextCtrl->SetValue("");
    YTextCtrl->SetValue("");
    RadiusTextCtrl->SetValue("");
}

void SwAreaDlg::OnNewAreaButtonClick(wxCommandEvent& event)
{
    if (m_map == NODE_ID_INVALID || !NameTextCtrl->GetValue().Len())
    {
        NameTextCtrl->SetFocus();
        wxBell();
        return;
    }

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();

    SwHtmlImageMap * map = mapList->GetMap(m_map);
    if(!map)
        return;

    SwMapArea area;
    area.SetAlt(NameTextCtrl->GetValue().utf8_str());
    area.drawColor = SwHtmlColor::GetColorValue(DrawColorChoice);
    area.fillColor = SwHtmlColor::GetColorValue(FillColorChoice);

    SwPoint pt;
    pt.x = (swUI32) atol(XTextCtrl->GetValue().utf8_str());
    pt.y = (swUI32) atol(XTextCtrl->GetValue().utf8_str());
    area.AddPoint(pt);

    pt.x = (swUI32) atol(RadiusTextCtrl->GetValue().utf8_str());
    pt.y = 0;
    area.AddPoint(pt);

    area.type = AREA_TYPE_CIRCLE;
    map->AppendNode(area);

    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    wxListItem lItem;
    lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
    lItem.SetColumn(0);
    lItem.SetId(AreasListCtrl->GetItemCount());
    lItem.SetText(NameTextCtrl->GetValue());
    lItem.SetData(map->GetMapData(lItem.GetId()));
    AreasListCtrl->wxListCtrl::InsertItem(lItem);
    m_area = NODE_ID_INVALID;
    ClearAreaData();

    if (m_parent)
        m_parent->Refresh();
}

void SwAreaDlg::OnDeleteAreaButtonClick(wxCommandEvent& event)
{
    if (m_map == NODE_ID_INVALID || m_area == NODE_ID_INVALID)
    {
        wxBell();
        return;
    }

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();

    SwHtmlImageMap * map = mapList->GetMap(m_map);
    if(!map)
        return;

    map->DeleteNode(m_area);

    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    AreasListCtrl->DeleteItem(m_area);

    m_area = NODE_ID_INVALID;
    ClearAreaData();

    if (m_parent)
        m_parent->Refresh();
}

void SwAreaDlg::OnUpdateButtonClick(wxCommandEvent& event)
{
    if (m_map == NODE_ID_INVALID || m_area == NODE_ID_INVALID)
    {
        wxBell();
        return;
    }

    SwHtmlImageMapList * mapList = new SwHtmlImageMapList();
    mapList->Copy(m_parent->GetImageMapList());

    m_parent->ClearHotAreas();

    SwHtmlImageMap * map = mapList->GetMap(m_map);
    if(!map)
        return;

    SwMapArea area;
    area.SetAlt(NameTextCtrl->GetValue().utf8_str());
    area.drawColor = SwHtmlColor::GetColorValue(DrawColorChoice);
    area.fillColor = SwHtmlColor::GetColorValue(FillColorChoice);

    SwPoint pt;
    pt.x = (swUI32) atol(XTextCtrl->GetValue().utf8_str());
    pt.y = (swUI32) atol(XTextCtrl->GetValue().utf8_str());
    area.AddPoint(pt);

    pt.x = (swUI32) atol(RadiusTextCtrl->GetValue().utf8_str());
    pt.y = 0;
    area.AddPoint(pt);

    area.type = AREA_TYPE_CIRCLE;
    map->ReplaceNode(m_area, area);

    SwCommandUpdateMapList * command = new SwCommandUpdateMapList("Update", &m_parent->GetImageMapList(), mapList);
    m_parent->GetCommandProcessor().Submit(command);

    if (m_parent)
        m_parent->Refresh();
}
