///////////////////////////////////////////////////////////////////
// Name:        librarylistctrl.h
// Purpose:     Categorized lists of ThML files, and modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef LIBRARYLISTCTRL_H
#define LIBRARYLISTCTRL_H

#include "../controls/controls.h"
#include "../string/stringcompare.h"
#include <wx/thread.h>

class SOWERBASEEXP SwThMLLibraryListCtrl : public SwStretchColumnListCtrl, public wxThreadHelper
{
public:
    SwThMLLibraryListCtrl();
    SwThMLLibraryListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_REPORT|wxLC_SINGLE_SEL, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);
    virtual ~SwThMLLibraryListCtrl();

    void LoadLibraryList();

protected:
    virtual wxThread::ExitCode Entry();
    virtual void OnThreadUpdate(wxThreadEvent& evt);
};

class SOWERBASEEXP SwModuleLibraryListCtrl : public SwStretchColumnListCtrl, public wxThreadHelper
{
public:
    SwModuleLibraryListCtrl();
    SwModuleLibraryListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_REPORT|wxLC_SINGLE_SEL, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);
    virtual ~SwModuleLibraryListCtrl();

    void LoadLibraryList();

protected:
    virtual wxThread::ExitCode Entry();
    virtual void OnThreadUpdate(wxThreadEvent& evt);
};

#endif // LIBRARYLISTCTRL_H
