///////////////////////////////////////////////////////////////////
// Name:        bookpanels.h
// Purpose:     Panels with contents, search, and find panels.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef BOOKPANELS_H
#define BOOKPANELS_H

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

class SOWERBASEEXP SwThMLBookPanel : public SwPanel
{
public:
    SwThMLBookPanel();
    SwThMLBookPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwThMLBookPanel();

    virtual bool OnOpen(const char * path);
    virtual bool OnContentsUp();
    virtual bool OnContentsDown();
    virtual bool OnHistoryBack();
    virtual bool OnHistoryForward();
    virtual bool OnPrint();
    virtual bool OnPrintPreview();

    virtual bool OnCanDoClose()
    {
        return true;
    }

    virtual bool OnCanDoCloseAll()
    {
        return true;
    }

    virtual bool OnCanDoPrint()
    {
        return TocTreeCtrl->GetHistory().GetCount();
    }

    virtual bool OnCanDoPrintPreview()
    {
        return TocTreeCtrl->GetHistory().GetCount();
    }

    virtual bool OnCanDoBookMarkPage()
    {
        return m_allowbookmarks && (bool) TocTreeCtrl->GetHistory().GetCount();
    }

    virtual bool OnCanDoCopy()
    {
        return viewBook->OnCanCopy();
    }

    virtual bool OnCopy();

    virtual bool OnCanDoSelectAll()
    {
        return true;
    }

    virtual bool OnSelectAll()
    {
        return viewBook->OnSelectAll();
    }

    virtual bool HasContentsView()
    {
        return true;
    }

    virtual bool HasBookmarksView()
    {
        return true;
    }

    virtual bool HasFindView()
    {
        return true;
    }

    virtual bool HasSearchView()
    {
        return true;
    }

    virtual bool OnCanDoZoomIn()
    {
        return viewBook->OnCanZoomIn();
    }

    virtual bool OnZoomIn()
    {
        return viewBook->OnZoomIn();
    }

    virtual bool OnCanDoZoomOut()
    {
        return viewBook->OnCanZoomOut();
    }

    virtual bool OnZoomOut()
    {
        return viewBook->OnZoomOut();
    }

    virtual bool OnCanDoViewNormal()
    {
        return viewBook->OnCanViewNormal();
    }

    virtual bool OnViewNormal()
    {
        return viewBook->OnViewNormal();
    }

    virtual bool OnCanDoUpInContents()
    {
        return TocTreeCtrl->GetCount();
    }

    virtual bool OnCanDoDownInContents()
    {
        return TocTreeCtrl->GetCount();
    }

    virtual bool OnCanDoBackInHistory()
    {
        return TocTreeCtrl->GetHistory().CanMoveBack();
    }

    virtual bool OnCanDoForwardInHistory()
    {
        return TocTreeCtrl->GetHistory().CanMoveForward();
    }

    void OnTreeItemSelChanged(wxTreeEvent& event);

    virtual const char * GetBookId()
    {
        if (!TocTreeCtrl)
            return NULL;

        return TocTreeCtrl->GetBookId();
    }

    virtual const char * GetFilePath()
    {
        if (!TocTreeCtrl)
            return NULL;

        return TocTreeCtrl->GetBookId();
    }

    virtual bool GetBookMarkData(SwString & title, SwBookMarkClientData & data);
    virtual bool ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid);
    virtual bool ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive);
    void SetPopUpMenu(SwViewMenu * menu);
    virtual void OnLanguageChange();
    virtual void OnThemeChange() {}
    void SetAllowBookMarks(bool state = false) { m_allowbookmarks = state; }
    bool GetAllowBookMarks() { return m_allowbookmarks; }
    wxNotebook* ToolNotebook;
    SwFindPanel* findPanel;
    SwThMLSearchPanel* searchPanel;
    SwViewBook* viewBook;
    SwThMLTreeCtrl* TocTreeCtrl;
    void SetCategoryGroup(swUI8 category) { m_group = category; }
    swUI8 GetCategoryGroup() { return m_group; }
    virtual bool HasFile(const char * path);

protected:
    static const long ID_TOCTREECTRL;
    static const long ID_CONTENTSPANEL;
    static const long ID_SEARCHPANEL;
    static const long ID_FINDPANEL;
    static const long ID_TOOLNOTEBOOK;
    static const long ID_VIEWBOOK;
    static SwString   m_buffer;
    bool              m_allowbookmarks;
    swUI8             m_group;
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
};
