///////////////////////////////////////////////////////////////////
// Name:        mapsdlg.h
// Purpose:     Manage HtmlImageMaps in HtmlImageMapLists.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MAPSDLG_H
#define MAPSDLG_H

#include "../framework/panel.h"
#include "../framework/viewbook.h"
#include "../controls/stretchfitctrls.h"
#include "../imgwin/imagewindow.h"

class SOWERBASEEXP SwMapDlg: public SwDialog
{
public:
    SwMapDlg(SwImageWindow* parent, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwMapDlg();

    wxButton* DeleteButton;
    wxButton* NewButton;
    wxButton* RenameButton;
    SwStretchColumnListView* MapsListCtrl;
    wxStaticText* MapsStaticText;
    wxStaticText* NameStaticText;
    wxTextCtrl* NameTextCtrl;

protected:
    static const long ID_MAPSSTATICTEXT;
    static const long ID_MAPSLISTCTRL;
    static const long ID_NEWBUTTON;
    static const long ID_RENAMEBUTTON;
    static const long ID_DELETEBUTTON;
    static const long ID_NAMESTATICTEXT;
    static const long ID_NAMETEXTCTRL;
    void BuildContent(wxWindow* parent, wxWindowID id,const wxPoint& pos,const wxSize& size);
    void OnNewButtonClick(wxCommandEvent& event);
    void OnRenameButtonClick(wxCommandEvent& event);
    void OnDeleteButtonClick(wxCommandEvent& event);
    SwImageWindow * m_parent;
};

#endif
