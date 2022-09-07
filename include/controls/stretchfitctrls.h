///////////////////////////////////////////////////////////////////
// Name:        stretchfitctrls.h
// Purpose:     Controls that size themselves to 'fit' themselves into
//              the remaining space of the client area minus the right
//              margin.
//              ------------
//              |[][  fit ]|
//              ------------
//              Controls that size themselves to 'stretch' in the client
//              area of the parent using the value of the left margin
//              for the right margin.
//              -----------
//              |[stretch]|
//              -----------
//              File Picker, Gauge, Text, and Choice controls.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRETCHFITCTRLS_H
#define STRETCHFITCTRLS_H

#include "../sowerbase.h"
#include <wx/filepicker.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>

class SOWERBASEEXP SwStretchFilePickerCtrl : public wxFilePickerCtrl
{
public:
    SwStretchFilePickerCtrl(wxWindow *parent, wxWindowID id, const wxString &path=wxEmptyString, const wxString &message=wxFileSelectorPromptStr, const wxString &wildcard=wxFileSelectorDefaultWildcardStr, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxFLP_DEFAULT_STYLE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxFilePickerCtrlNameStr);
    virtual ~SwStretchFilePickerCtrl();

    virtual void OnResize(wxSizeEvent& event);
};

class SOWERBASEEXP SwFittedFilePickerCtrl : public wxFilePickerCtrl
{
public:
    SwFittedFilePickerCtrl(wxWindow *parent, wxWindowID id, const wxString &path=wxEmptyString, const wxString &message=wxFileSelectorPromptStr, const wxString &wildcard=wxFileSelectorDefaultWildcardStr, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxFLP_DEFAULT_STYLE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxFilePickerCtrlNameStr);
    virtual ~SwFittedFilePickerCtrl();

    virtual void OnResize(wxSizeEvent& event);
};

class SOWERBASEEXP SwStretchGauge : public wxGauge
{
public:
    SwStretchGauge(wxWindow *parent, wxWindowID id, int range, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxGA_HORIZONTAL, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxGaugeNameStr);
    virtual ~SwStretchGauge();

    virtual void OnResize(wxSizeEvent& event);
};

class SOWERBASEEXP SwFittedGauge : public wxGauge
{
public:
    SwFittedGauge(wxWindow *parent, wxWindowID id, int range, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxGA_HORIZONTAL, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxGaugeNameStr);
    virtual ~SwFittedGauge();

    virtual void OnResize(wxSizeEvent& event);
protected:

private:
};

class SOWERBASEEXP SwStretchTextCtrl : public wxTextCtrl
{
public:
    SwStretchTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwStretchTextCtrl();

    virtual void OnResize(wxSizeEvent& event);
};

class SOWERBASEEXP SwFittedTextCtrl : public wxTextCtrl
{
public:
    SwFittedTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwFittedTextCtrl();

    virtual void OnResize(wxSizeEvent& event);
};

class SOWERBASEEXP SwFittedChoiceCtrl : public wxChoice
{
public:
    SwFittedChoiceCtrl(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxChoiceNameStr);
    virtual ~SwFittedChoiceCtrl();

    virtual void OnResize(wxSizeEvent& event);
};

#endif // STRETCHFITCTRLS_H
