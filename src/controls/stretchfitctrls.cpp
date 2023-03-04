///////////////////////////////////////////////////////////////////
// Name:        stretchfitctrls.cpp
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

#include "../../include/controls/stretchfitctrls.h"

void StretchCtrl(wxWindow * ctrl, wxSize & parentSize)
{
    // Stretch control, or window to fit width of
    // parentSize - (border spacing * 2).

    int h, w, x, y;
    ctrl->GetSize(&w, &h);
    ctrl->GetPosition(&x, &y);
    ctrl->SetSize(wxSize(parentSize.GetWidth() - (x * 2), h));
}

void FitCtrl(wxWindow * ctrl, wxSize & parentSize, swUI16 margin)
{
    // Stretch control, or window to fit width of
    // parentSize - (x position + margin in pixels).

    int h, w, x, y;
    ctrl->GetSize(&w, &h);
    ctrl->GetPosition(&x, &y);
    ctrl->SetSize(wxSize(parentSize.GetWidth() - (x + margin), h));
}

SwStretchFilePickerCtrl::SwStretchFilePickerCtrl(wxWindow *parent, wxWindowID id, const wxString &path, const wxString &message, const wxString &wildcard, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxFilePickerCtrl(parent, id, path, message, wildcard, pos, size, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchFilePickerCtrl::OnResize);
}

SwStretchFilePickerCtrl::~SwStretchFilePickerCtrl()
{
}

void SwStretchFilePickerCtrl::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    StretchCtrl(this, s);
    event.Skip();
}

SwFittedFilePickerCtrl::SwFittedFilePickerCtrl(wxWindow *parent, wxWindowID id, const wxString &path, const wxString &message, const wxString &wildcard, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxFilePickerCtrl(parent, id, path, message, wildcard, pos, size, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwFittedFilePickerCtrl::OnResize);
}

SwFittedFilePickerCtrl::~SwFittedFilePickerCtrl()
{
}

void SwFittedFilePickerCtrl::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    FitCtrl(this, s, 10);
    event.Skip();
}

SwStretchGauge::SwStretchGauge(wxWindow *parent, wxWindowID id, int range, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxGauge(parent, id, range, pos, size, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchGauge::OnResize);
}

SwStretchGauge::~SwStretchGauge()
{
}

void SwStretchGauge::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    StretchCtrl(this, s);
    event.Skip();
}


SwFittedGauge::SwFittedGauge(wxWindow *parent, wxWindowID id, int range, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxGauge(parent, id, range, pos, size, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwFittedGauge::OnResize);
}

SwFittedGauge::~SwFittedGauge()
{
}

void SwFittedGauge::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    FitCtrl(this, s, 10);
    event.Skip();
}

SwStretchTextCtrl::SwStretchTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxTextCtrl(parent, id, value, pos, size, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchTextCtrl::OnResize);
}

SwStretchTextCtrl::~SwStretchTextCtrl()
{
}

void SwStretchTextCtrl::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    StretchCtrl(this, s);
    event.Skip();
}

SwFittedTextCtrl::SwFittedTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxTextCtrl(parent, id, value, pos, size, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwFittedTextCtrl::OnResize);
}

SwFittedTextCtrl::~SwFittedTextCtrl()
{
}

void SwFittedTextCtrl::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    FitCtrl(this, s, 10);
    event.Skip();
}

SwFittedChoiceCtrl::SwFittedChoiceCtrl(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], long style, const wxValidator& validator, const wxString& name)
    :wxChoice(parent, id, pos, size, n, choices, style, validator, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwFittedChoiceCtrl::OnResize);
}

SwFittedChoiceCtrl::~SwFittedChoiceCtrl()
{
}

void SwFittedChoiceCtrl::OnResize(wxSizeEvent& event)
{
    wxSize s = GetParent()->GetSize();

    FitCtrl(this, s, 5);
    event.Skip();
}

