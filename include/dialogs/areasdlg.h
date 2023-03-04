///////////////////////////////////////////////////////////////////
// Name:        areasdlg.h
// Purpose:     Manage MapAreas in HtmlImageMaps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AREASDLG_H
#define AREASDLG_H

#include "../framework/panel.h"
#include "../framework/viewbook.h"
#include "../controls/stretchfitctrls.h"
#include "../imgwin/imagewindow.h"

class SOWERBASEEXP SwAreaDlg: public SwDialog
{
public:
    SwAreaDlg(SwImageWindow* parent, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwAreaDlg();

    void BuildContent(wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size);

    wxStaticText* MapsStaticText;
    SwStretchColumnListCtrl* MapsListCtrl;
    wxStaticText* AreasStaticText;
    SwStretchColumnListCtrl* AreasListCtrl;
    wxStaticText* NameStaticText;
    wxTextCtrl* NameTextCtrl;
    wxStaticText* DrawColorStaticText;
    wxChoice* DrawColorChoice;
    wxStaticText* FillColorStaticText;
    wxChoice* FillColorChoice;
    wxStaticText* PositionStaticText;
    wxStaticText* XStaticText;
    wxTextCtrl* XTextCtrl;
    wxStaticText* YStaticText;
    wxTextCtrl* YTextCtrl;
    wxStaticText* RadiusStaticText;
    wxTextCtrl* RadiusTextCtrl;
    wxButton* NewAreaButton;
    wxButton* DeleteAreaButton;
    wxButton* UpdateButton;

protected:
    static const long ID_MAPSSTATICTEXT;
    static const long ID_MAPSLISTCTRL;
    static const long ID_AREASSTATICTEXT;
    static const long ID_AREASLISTCTRL;
    static const long ID_NAMESTATICTEXT;
    static const long ID_NAMETEXTCTRL;
    static const long ID_DRAWCOLORSTATICTEXT;
    static const long ID_DRAWCOLORCHOICE;
    static const long ID_FILLCOLORSTATICTEXT;
    static const long ID_FILLCOLORCHOICE;
    static const long ID_POSITIONSTATICTEXT;
    static const long ID_XSTATICTEXT;
    static const long ID_XTEXTCTRL;
    static const long ID_YSTATICTEXT;
    static const long ID_YTEXTCTRL;
    static const long ID_RADIUSSTATICTEXT;
    static const long ID_RADIUSTEXTCTRL;
    static const long ID_NEWAREABUTTON;
    static const long ID_DELETEAREABUTTON;
    static const long ID_UPDATEBUTTON;

private:
    void ClearAreaData();
    void OnMapListCtrlItemSelect(wxListEvent& event);
    void OnAreaListCtrlItemSelect(wxListEvent& event);
    void OnNewAreaButtonClick(wxCommandEvent& event);
    void OnDeleteAreaButtonClick(wxCommandEvent& event);
    void OnUpdateButtonClick(wxCommandEvent& event);
    SwImageWindow * m_parent;
    swUI32 m_map;
    swUI32 m_area;
};

#endif
