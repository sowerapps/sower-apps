///////////////////////////////////////////////////////////////////
// Name:        sowerconfigurationviewerdlg.h
// Purpose:     SwConfigurationDlg
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERCONFIGURATIONDLG_H
#define SOWERCONFIGURATIONDLG_H

#include "../framework/dialog.h"
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>

class SwConfigurationDlg: public SwDialog
{
public:
    SwConfigurationDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwConfigurationDlg();

    void AppendToList(const wchar_t * item, const char * value);

protected:
    static const long ID_CONFIGLISTCTRL;
    wxListCtrl * ConfigListCtrl;
    void OnOkButtonClick(wxCommandEvent& event);
};

#endif // SOWERCONFIGURATIONDLG_H
