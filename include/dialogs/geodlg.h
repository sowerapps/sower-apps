///////////////////////////////////////////////////////////////////
// Name:        geodlg.h
// Purpose:     Generate geo data for images of maps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef GEODLG_H
#define GEODLG_H

#include "../framework/panel.h"
#include "../framework/viewbook.h"
#include "../controls/stretchfitctrls.h"
#include "../imgwin/imagewindow.h"
#include <wx/statline.h>

class SOWERBASEEXP SwGeoDlg: public SwDialog
{
public:
    SwGeoDlg(SwImageWindow* parent, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwGeoDlg();

    wxButton* GenerateButton;
    wxStaticText* BottomStaticText;
    wxStaticText* DegreesStaticText;
    wxStaticText* LatitudeStaticText;
    wxStaticText* LeftStaticText;
    wxStaticText* LongitudeStaticText;
    wxStaticText* PxPosStaticText;
    wxStaticText* RightStaticText;
    wxStaticText* TopStaticText;
    wxTextCtrl* BottomPxTextCtrl;
    wxTextCtrl* BottomTextCtrl;
    wxTextCtrl* LeftPxTextCtrl;
    wxTextCtrl* LeftTextCtrl;
    wxTextCtrl* RightPxTextCtrl;
    wxTextCtrl* RightTextCtrl;
    wxTextCtrl* TopPxTextCtrl;
    wxTextCtrl* TopTextCtrl;
    wxStaticText* DrawColorStaticText;
    wxChoice* DrawColorChoice;
    wxStaticText* FillColorStaticText;
    wxChoice* FillColorChoice;
    wxStaticText* RadiusStaticText;
    wxTextCtrl* RadiusTextCtrl;

protected:
    static const long ID_LATITUDESTATICTEXT;
    static const long ID_DEGREESSTATICTEXT;
    static const long ID_PXPOSSTATICTEXT;
    static const long ID_TOPSTATICTEXT;
    static const long ID_TOPTEXTCTRL;
    static const long ID_TOPPXTEXTCTRL;
    static const long ID_BOTTOMSTATICTEXT;
    static const long ID_BOTTOMTEXTCTRL;
    static const long ID_BOTTOMPXTEXTCTRL;
    static const long ID_LONGITUDESTATICTEXT;
    static const long ID_LEFTSTATICTEXT;
    static const long ID_LEFTTEXTCTRL;
    static const long ID_LEFTPXTEXTCTRL;
    static const long ID_RIGHTSTATICTEXT;
    static const long ID_RIGHTTEXTCTRL;
    static const long ID_RIGHTPXTEXTCTRL;
    static const long ID_GENERATEBUTTON;
    static const long ID_DRAWCOLORSTATICTEXT;
    static const long ID_DRAWCOLORCHOICE;
    static const long ID_FILLCOLORSTATICTEXT;
    static const long ID_FILLCOLORCHOICE;
    static const long ID_RADIUSSTATICTEXT;
    static const long ID_RADIUSTEXTCTRL;

    void BuildContent(wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size);
    void OnGenerateButtonClick(wxCommandEvent& event);
    SwMapArea * FindInMap(SwHtmlImageMap * mapObj, SwPoint pt);
    SwMapArea * FindInMaps(SwPoint pt);
    swUI32 SetName();
    void SetPosition(SwHtmlImageMap * mapObj, SwPoint & pt, swI32 radius);
    void SetDrawColor(swUI32 color = 16711680);
    void SetFillColor(swUI32 color = 16777215);
    void SetRadius(swUI8 radius = 3);

    SwImageWindow * m_parent;
    swUI32        m_drawcolor;
    swUI32        m_fillcolor;
    swUI8         m_radius;
};


#endif
