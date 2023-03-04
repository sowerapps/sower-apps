///////////////////////////////////////////////////////////////////
// Name:        interfacedlg.h
// Purpose:     Select gui interface plug-in.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef INTERFACEDLG_H
#define INTERFACEDLG_H

#include "../appi/appifa.h"
#include "../framework/dialog.h"
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/gbsizer.h>
#include <wx/sizer.h>

class SOWERBASEEXP SwInterfaceDlg: public SwDialog
{
public:
    SwInterfaceDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwInterfaceDlg();

    wxChoice* interfaceChoice;

protected:
    static const long ID_INTERFACECHOICE;
    void OninterfaceChoiceSelect(wxCommandEvent& event);
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    void OnOk(wxCommandEvent& event);
    int m_current;
};

#endif
