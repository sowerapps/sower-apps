///////////////////////////////////////////////////////////////////
// Name:        viewbook.h
// Purpose:     SwViewBook - a tabless notebook control that is used
//              to contain viewers for different types of media, as
//              opposed to embedding viewers, or media players etc.
//              in another control such as a SwRichView control.
//              Sower allows an additional attribute called 'type' for
//              the ThML elements div1 - div6 to specify the type of
//              viewer/player needed for the media.
//              The control first checks existing views for the type needed,
//              if that fails it checks for a plug-in that can handle the
//              media, and last checks the type needed against built in
//              viewers/players. This does not prevent embedding media such
//              as images, or audio. It is an optional method to embedding
//              content.
//              SwViewPanel - a base class and wrapper for viewers/players.
//              SwRichViewPanel - a wrapper for SwRichView.
//              SwImageViewPanel - a wrapper for SwImageWindow.
//              SwMapViewPanel - SwImageViewPanel with extended capability
//              for maps.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERVIEWBOOK_H
#define SOWERVIEWBOOK_H

#include <wx/simplebook.h>
#include "../css/css_file.h"
#include "../module/modulebase.h"
#include "../richtext/richview.h"
#include "../imgwin/geofind.h"
#include "../imgwin/imagewindow.h"
#include "../filesys/streambuffer.h"

class SOWERBASEEXP SwViewPanel : public wxPanel
{
    DECLARE_DYNAMIC_CLASS(SwViewPanel)

public:
    SwViewPanel();
    SwViewPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwViewPanel();

    // Viewer
    virtual bool OnLoad(SwPageData & pageData);
    virtual bool OnLoad(swUI8 contentType, SwStreamBuffer & data, const SwGeoConversionData * cd = NULL);
    virtual bool OnWriteXmlText(swUI8 contentType, const char * source, bool thml,  const char * basePath);
    virtual bool OnWriteXmlText(swUI8 contentType, const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath);
    virtual bool OnReset();
    virtual bool OnRefresh();
    virtual bool OnHasFocus();
    virtual bool OnHasSelection();
    virtual bool OnGetSelectedText(SwString & buffer);
    virtual bool OnGetSelection(SwTextRange & selection);
    virtual bool OnSetSelection(SwTextRange & selection);
    virtual bool OnGetScrollPos(SwScrollData & scrolldata);
    virtual bool OnSetScrollPos(SwScrollData & scrolldata);
    virtual bool OnCanHandle(swUI8 contentType);
    virtual bool OnSetCanCopy(bool canCopy);
    virtual bool OnCanCopy();
    virtual bool OnCanDoPrint();
    virtual bool OnCanDoPrintPreview();
    virtual bool OnCanDoZoomIn();
    virtual bool OnCanDoZoomOut();
    virtual bool OnCanDoViewNormal();
    virtual bool OnCanDoPlay();
    virtual bool OnCanDoPause();
    virtual bool OnCanDoStop();
    virtual bool OnCanDoRewind();
    virtual bool OnCanDoFastForward();
    virtual bool OnCanDoPrevious();
    virtual bool OnCanDoNext();
    virtual bool OnSetSwThMLTreeCtrl(SwThMLTreeCtrl * ctrl);

    // Find
    virtual bool OnFindReset();
    virtual bool OnFindSetCaseSensitive(bool caseSensitive);
    virtual bool OnFindSetWholeWordOnly(bool wholewordOnly);

    // User
    virtual bool OnCopy();
    virtual bool OnSelectAll();
    virtual bool OnPrint();
    virtual bool OnPrintPreview();
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();
    virtual bool OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnFindNext();
    virtual bool OnHilite(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnPlay();
    virtual bool OnPause();
    virtual bool OnStop();
    virtual bool OnRewind();
    virtual bool OnFastForward();
    virtual bool OnPrevious();
    virtual bool OnNext();

    // System
    virtual void OnEnableAutoDef(bool enable = true);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnFontSizeChange(const wxFont & font);
    virtual void OnResize(wxSizeEvent& event);
    virtual void OnSetPopUpMenu(SwMenu * menu);
};


class SOWERBASEEXP SwRichViewPanel : public SwViewPanel
{
public:
    SwRichViewPanel();
    SwRichViewPanel(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwRichViewPanel();

    // Viewer
    virtual bool OnLoad(SwPageData & pageData);
    virtual bool OnWriteXmlText(swUI8 contentType, const char * source, bool thml,  const char * basePath);
    virtual bool OnWriteXmlText(swUI8 contentType, const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath);
    virtual bool OnReset();
    virtual bool OnHasFocus();
    virtual bool OnHasSelection();
    virtual bool OnGetSelectedText(SwString & buffer);
    virtual bool OnGetSelection(SwTextRange & selection);
    virtual bool OnSetSelection(SwTextRange & selection);
    virtual bool OnGetScrollPos(SwScrollData & scrolldata);
    virtual bool OnSetScrollPos(SwScrollData & scrolldata);
    virtual bool OnCanHandle(swUI8 contentType);
    virtual bool OnSetCanCopy(bool canCopy);
    virtual bool OnCanCopy();
    virtual bool OnCanDoPrint();
    virtual bool OnCanDoPrintPreview();
    virtual bool OnCanDoZoomIn();
    virtual bool OnCanDoZoomOut();
    virtual bool OnCanDoViewNormal();
    virtual bool OnSetSwThMLTreeCtrl(SwThMLTreeCtrl * ctrl);

    // Find
    virtual bool OnFindReset();
    virtual bool OnFindSetCaseSensitive(bool caseSensitive);
    virtual bool OnFindSetWholeWordOnly(bool wholewordOnly);

    // User
    virtual bool OnCopy();
    virtual bool OnSelectAll();
    virtual bool OnPrint();
    virtual bool OnPrintPreview();
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();
    virtual bool OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnFindNext();
    virtual bool OnHilite(const wchar_t * text, bool casesensitive, bool wholewordonly);

    // System
    virtual void OnEnableAutoDef(bool enable = true);
    virtual void OnResize(wxSizeEvent& event);
    virtual void OnSetPopUpMenu(SwMenu * menu);

    SwRichView * m_view;
};

class SOWERBASEEXP SwImageViewPanel : public SwViewPanel
{
public:
    SwImageViewPanel();
    SwImageViewPanel(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwImageViewPanel();

    // Viewer
    virtual bool OnLoad(SwPageData & pageData);
    virtual bool OnLoad(swUI8 contentType, SwStreamBuffer & data, const SwGeoConversionData * cd = NULL);
    virtual bool OnReset();
    virtual bool OnRefresh();
    virtual bool OnGetScrollPos(SwScrollData & scrolldata);
    virtual bool OnSetScrollPos(SwScrollData & scrolldata);
    virtual bool OnHasFocus();
    virtual bool OnCanHandle(swUI8 contentType);
    virtual bool OnSetCanCopy(bool canCopy);
    virtual bool OnCanCopy();
    virtual bool OnCanDoPrint();
    virtual bool OnCanDoZoomIn();
    virtual bool OnCanDoZoomOut();
    virtual bool OnCanDoViewNormal();
    // User
    virtual bool OnPrint();
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();

    // System
    virtual void OnEnableAutoDef(bool enable = true);
    virtual void OnSetPopUpMenu(SwMenu * menu);
    void OnResize(wxSizeEvent& event);

    SwImageWindow * m_view;
};

class SOWERBASEEXP SwMapViewPanel : public SwViewPanel
{
public:
    SwMapViewPanel();
    SwMapViewPanel(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwMapViewPanel();

    void OnLanguageChange();

    // Viewer
    virtual bool OnCanHandle(swUI8 contentType);
    virtual bool OnLoad(SwPageData & pageData);
    virtual bool OnLoad(swUI8 contentType, SwStreamBuffer & data, const SwGeoConversionData * cd = NULL);
    virtual bool OnReset();
    virtual bool OnRefresh();
    virtual bool OnGetScrollPos(SwScrollData & scrolldata);
    virtual bool OnSetScrollPos(SwScrollData & scrolldata);
    virtual bool OnHasFocus();
    virtual bool OnSetCanCopy(bool canCopy);
    virtual bool OnCanCopy();
    virtual bool OnCanDoPrint();
    virtual bool OnCanDoZoomIn();
    virtual bool OnCanDoZoomOut();
    virtual bool OnCanDoViewNormal();

    // Find
    virtual bool OnFindReset();
    virtual bool OnFindSetCaseSensitive(bool caseSensitive);
    virtual bool OnFindSetWholeWordOnly(bool wholewordOnly);

    // User
    virtual bool OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnFindNext();
    virtual bool OnPrint();
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();
    virtual void OnPlaceItemActivated(wxListEvent& event);
    virtual void OnJourneyItemActivated(wxCommandEvent& event);



    // System
    virtual void OnEnableAutoDef(bool enable = true);
    virtual void OnSetPopUpMenu(SwMenu * menu);
    void OnResize(wxSizeEvent& event);

    static const long ID_TOOLNOTEBOOK;
    static const long ID_PLACESLISTCTRL;
    static const long ID_JOURNEYSSCHECKLISTBOX;
    static const long ID_IMAGEVIEW;

    wxNotebook * ToolNotebook;
    SwStretchColumnListCtrl * PlacesListCtrl;
    wxCheckListBox * JourneysCheckListBox;
    SwImageWindow * m_view;

private:
    SwGeoFind m_find;
    wxAuiManager *  m_manager;
};

class SOWERBASEEXP SwViewBook : public wxSimplebook
{
    DECLARE_DYNAMIC_CLASS(SwViewBook)
public:
    SwViewBook();
    SwViewBook(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxEmptyString);
    virtual ~SwViewBook();

    // Viewer
    virtual bool OnLoad(SwPageData & pageData);
    virtual bool OnLoad(swUI8 contentType, SwStreamBuffer & data);
    virtual bool OnWriteXmlText(swUI8 contentType, const char * source, bool thml,  const char * basePath);
    virtual bool OnWriteXmlText(swUI8 contentType, const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath);
    virtual bool OnReset();
    virtual bool OnRefresh();
    virtual bool OnHasFocus();
    virtual bool OnHasSelection();
    virtual bool OnGetSelectedText(SwString & buffer);
    virtual bool OnGetSelection(SwTextRange & selection);
    virtual bool OnSetSelection(SwTextRange & selection);
    virtual bool OnGetScrollPos(SwScrollData & scrolldata);
    virtual bool OnSetScrollPos(SwScrollData & scrolldata);
    virtual bool OnCanHandle(swUI8 contentType);
    virtual bool OnSetCanCopy(bool canCopy);
    virtual bool OnCanCopy();
    virtual bool OnCanDoPrint();
    virtual bool OnCanDoPrintPreview();
    virtual bool OnCanZoomIn();
    virtual bool OnCanZoomOut();
    virtual bool OnCanViewNormal();
    virtual bool OnCanDoPlay();
    virtual bool OnCanDoPause();
    virtual bool OnCanDoStop();
    virtual bool OnCanDoRewind();
    virtual bool OnCanDoFastForward();
    virtual bool OnCanDoPrevious();
    virtual bool OnCanDoNext();
    virtual bool OnSetSwThMLTreeCtrl(SwThMLTreeCtrl * ctrl);

    // Find
    virtual bool OnFindReset();
    virtual bool OnFindSetCaseSensitive(bool caseSensitive);
    virtual bool OnFindSetWholeWordOnly(bool wholewordOnly);

    // User
    virtual bool OnCopy();
    virtual bool OnSelectAll();
    virtual bool OnPrint();
    virtual bool OnPrintPreview();
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();
    virtual bool OnFind(wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnFindNext();
    virtual bool OnHilite(const wchar_t * text, bool casesensitive, bool wholewordonly);
    virtual bool OnPlay();
    virtual bool OnPause();
    virtual bool OnStop();
    virtual bool OnRewind();
    virtual bool OnFastForward();
    virtual bool OnPrevious();
    virtual bool OnNext();

    // System
    virtual void OnEnableAutoDef(bool enable = true);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void OnFontSizeChange(const wxFont & font);
    virtual void OnSetPopUpMenu(SwMenu * menu);

    // Book Control
    int FindViewer(swUI8 contentType);
    bool AddViewer(swUI8 contentType);
    void ResetAll();
    void SetTitle(const char * title) { m_title = title; }
    const char * GetTitle() { return m_title; }

protected:
    bool m_enableAutoDef;
    SwThMLTreeCtrl * m_multifiletree;
    SwMenu * m_menu;
    SwString m_title;
};

#endif // SOWERVIEWBOOK_H
