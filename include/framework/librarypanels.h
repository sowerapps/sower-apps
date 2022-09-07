///////////////////////////////////////////////////////////////////
// Name:        librarypanels.h
// Purpose:     Library panels.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef LIBRARYPANELS_H
#define LIBRARYPANELS_H

#include "panel.h"
#include "viewbook.h"
#include "../controls/treectrlext.h"
#include "../framework/findpanel.h"
#include "../framework/searchpanel.h"
#include "../controls/librarylistctrl.h"
#include "librarysearchpanels.h"
#include <wx/aui/aui.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

class SOWERBASEEXP SwThMLLibraryPanel : public SwPanel
{
public:
    SwThMLLibraryPanel();
    SwThMLLibraryPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwThMLLibraryPanel();

    virtual void OnContentsUp(wxCommandEvent & event);
    virtual void OnContentsDown(wxCommandEvent & event);

    virtual void OnLanguageChange();
    virtual void OnThemeChange() {}
    virtual void OnLibraryItemActivated(wxListEvent& event);

    wxNotebook* ToolNotebook;
    SwThMLLibrarySearchPanel* searchPanel;
    SwThMLLibraryListCtrl* LibraryListCtrl;
    SwThMLLibraryListCtrl* GetLibraryListCtrl()
    {
        return LibraryListCtrl;
    }
    wxListCtrl * GetSearchResultsList()
    {
        return searchPanel->SearchResultsList;
    }
    void SetFrame(SwFrame * frame)
    {
        m_frame = frame;
        if (searchPanel)
            searchPanel->SetFrame(frame);
    }

protected:
    SwFrame * m_frame;
    static const long ID_LIBRARYLISTCTRL;
    static const long ID_SEARCHPANEL;
    static const long ID_TOOLNOTEBOOK;

    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
};


class SOWERBASEEXP SwModuleLibraryPanel : public SwPanel
{
public:
    SwModuleLibraryPanel();
    SwModuleLibraryPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwModuleLibraryPanel();

    virtual void OnContentsUp(wxCommandEvent & event);
    virtual void OnContentsDown(wxCommandEvent & event);

    virtual void OnLanguageChange();
    virtual void OnThemeChange() {}
    virtual void OnLibraryItemActivated(wxListEvent& event);

    wxNotebook* ToolNotebook;
    SwModuleLibrarySearchPanel* searchPanel;
    SwModuleLibraryListCtrl* LibraryListCtrl;
    SwModuleLibraryListCtrl* GetLibraryListCtrl()
    {
        return LibraryListCtrl;
    }
    wxListCtrl * GetSearchResultsList()
    {
        return searchPanel->SearchResultsList;
    }
    void SetFrame(SwFrame * frame)
    {
        m_frame = frame;
        if (searchPanel)
            searchPanel->SetFrame(frame);
    }

protected:
    SwFrame * m_frame;
    static const long ID_LIBRARYLISTCTRL;
    static const long ID_SEARCHPANEL;
    static const long ID_TOOLNOTEBOOK;

    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
};

#endif // LIBRARYPANELS_H
