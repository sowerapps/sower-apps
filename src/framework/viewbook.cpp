///////////////////////////////////////////////////////////////////
// Name:        viewbook.cpp
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

#include "../../include/framework/viewbook.h"
#include "../../include/framework/panel.h"
#include "../../include/appi/appifa.h"

IMPLEMENT_DYNAMIC_CLASS(SwViewPanel, wxPanel)

SwViewPanel::SwViewPanel()
{
    SetBackgroundColour(*wxWHITE);
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
}

SwViewPanel::SwViewPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxPanel(parent, id, pos, size, style, name)
{
    SetBackgroundColour(*wxWHITE);
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwViewPanel::OnResize);
}

SwViewPanel::~SwViewPanel()
{
}

bool SwViewPanel::OnLoad(SwPageData & pageData)
{
    return false;
}

bool SwViewPanel::OnLoad(swUI8 contentType, SwStreamBuffer & data, const SwGeoConversionData * cd)
{
    return false;
}

bool SwViewPanel::OnWriteXmlText(swUI8 contentType, const char * source, bool thml,  const char * basePath)
{
    return false;
}

bool SwViewPanel::OnWriteXmlText(swUI8 contentType, const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath)
{
    return false;
}

bool SwViewPanel::OnReset()
{
    return false;
}

bool SwViewPanel::OnRefresh()
{
    return false;
}

bool SwViewPanel::OnHasFocus()
{
    return false;
}

bool SwViewPanel::OnHasSelection()
{
    return false;
}

bool SwViewPanel::OnGetSelectedText(SwString & buffer)
{
    buffer = "";

    return false;
}

bool SwViewPanel::OnGetSelection(SwTextRange & selection)
{
    selection.begin = -1;
    selection.end = -1;

    return false;
}

bool SwViewPanel::OnSetSelection(SwTextRange & selection)
{
    return false;
}

bool SwViewPanel::OnGetScrollPos(SwScrollData & scrolldata)
{
    return false;
}

bool SwViewPanel::OnSetScrollPos(SwScrollData & scrolldata)
{
    return false;
}

bool SwViewPanel::OnCanHandle(swUI8 contentType)
{
    return false;
}

bool SwViewPanel::OnSetCanCopy(bool canCopy)
{
    return false;
}

bool SwViewPanel::OnCanCopy()
{
    return false;
}

bool SwViewPanel::OnCanDoPrint()
{
    return false;
}

bool SwViewPanel::OnCanDoPrintPreview()
{
    return false;
}

bool SwViewPanel::OnCanDoZoomIn()
{
    return false;
}

bool SwViewPanel::OnCanDoZoomOut()
{
    return false;
}

bool SwViewPanel::OnCanDoViewNormal()
{
    return false;
}

bool SwViewPanel::OnCanDoPlay()
{
    return false;
}

bool SwViewPanel::OnCanDoPause()
{
    return false;
}

bool SwViewPanel::OnCanDoStop()
{
    return false;
}

bool SwViewPanel::OnCanDoRewind()
{
    return false;
}

bool SwViewPanel::OnCanDoFastForward()
{
    return false;
}

bool SwViewPanel::OnCanDoPrevious()
{
    return false;
}

bool SwViewPanel::OnCanDoNext()
{
    return false;
}

bool SwViewPanel::OnSetSwThMLTreeCtrl(SwThMLTreeCtrl * ctrl)
{
    return false;
}

bool SwViewPanel::OnFindReset()
{
    return false;
}

bool SwViewPanel::OnFindSetCaseSensitive(bool casesensitive)
{
    return false;
}

bool SwViewPanel::OnFindSetWholeWordOnly(bool wholewordonly)
{
    return false;
}

bool SwViewPanel::OnCopy()
{
    return false;
}

bool SwViewPanel::OnSelectAll()
{
    return false;
}

bool SwViewPanel::OnPrint()
{
    return false;
}

bool SwViewPanel::OnPrintPreview()
{
    return false;
}

bool SwViewPanel::OnZoomIn()
{
    return false;
}

bool SwViewPanel::OnZoomOut()
{
    return false;
}

bool SwViewPanel::OnViewNormal()
{
    return false;
}

bool SwViewPanel::OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    return false;
}

bool SwViewPanel::OnFindNext()
{
    return false;
}

bool SwViewPanel::OnHilite(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    return false;
}

bool SwViewPanel::OnPlay()
{
    return false;
}

bool SwViewPanel::OnPause()
{
    return false;
}

bool SwViewPanel::OnStop()
{
    return false;
}

bool SwViewPanel::OnRewind()
{
    return false;
}

bool SwViewPanel::OnFastForward()
{
    return false;
}

bool SwViewPanel::OnPrevious()
{
    return false;
}

bool SwViewPanel::OnNext()
{
    return false;
}

void SwViewPanel::OnEnableAutoDef(bool enable)
{
}

void SwViewPanel::OnLanguageChange()
{
}

void SwViewPanel::OnThemeChange()
{
}

void SwViewPanel::OnFontSizeChange(const wxFont & font)
{
}

void SwViewPanel::OnResize(wxSizeEvent& event)
{
    event.Skip();
}

void SwViewPanel::OnSetPopUpMenu(SwMenu * menu)
{
}

SwRichViewPanel::SwRichViewPanel()
{
    m_view = NULL;
}

SwRichViewPanel::SwRichViewPanel(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwViewPanel(parent, id, pos, size, style, name)
{
    m_view = new SwRichView(this, id, value, pos, size, style|wxRE_MULTILINE|wxRE_READONLY, validator, name);

    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwRichViewPanel::OnResize);
}

SwRichViewPanel::~SwRichViewPanel()
{
}

bool SwRichViewPanel::OnLoad(SwPageData & pageData)
{
    SwString data;
    bool canCopy;

    SwApplicationInterface::GetModuleManager().LoadPage(pageData, data, canCopy);

    m_view->SetCanCopy(canCopy);

    m_view->Reset();

    m_view->WriteXmlText(data, true, "");

    return true;
}

bool SwRichViewPanel::OnWriteXmlText(swUI8 contentType, const char * source, bool thml,  const char * basePath)
{
    if (!source)
        return false;

    m_view->WriteXmlText(source, thml, basePath);

    return true;
}

bool SwRichViewPanel::OnWriteXmlText(swUI8 contentType, const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath)
{
    if (!source)
        return false;

    m_view->WriteXmlText(source, length, thml, list, basePath);

    return true;
}

bool SwRichViewPanel::OnReset()
{
    m_view->Reset();

    return true;
}

bool SwRichViewPanel::OnHasFocus()
{
    return m_view->HasFocus();
}

bool SwRichViewPanel::OnHasSelection()
{
    return m_view->HasSelection();
}

bool SwRichViewPanel::OnGetSelectedText(SwString & buffer)
{
    buffer = m_view->GetStringSelection().utf8_str();

    return true;
}

bool SwRichViewPanel::OnGetSelection(SwTextRange & selection)
{
    if (!m_view->HasSelection())
    {
        selection.begin = -1;
        selection.end = -1;

        return true;
    }
    wxRichTextRange range = m_view->GetSelectionRange();

    selection.begin = range.GetStart();
    selection.end = range.GetEnd();

    return true;
}

bool SwRichViewPanel::OnSetSelection(SwTextRange & selection)
{
    if (selection.begin == selection.end)
        return true;

    if (selection.begin < 0 || selection.end < 0)
        return false;

    m_view->SetSelection(selection.begin, selection.end);

    return true;
}

bool SwRichViewPanel::OnGetScrollPos(SwScrollData & scrolldata)
{
    scrolldata.vpos = 0;
    scrolldata.hpos = m_view->GetFirstVisiblePosition();

    return true;
}

bool SwRichViewPanel::OnSetScrollPos(SwScrollData & scrolldata)
{
    m_view->ScrollIntoView(scrolldata.hpos, WXK_DOWN);

    return true;
}

bool SwRichViewPanel::OnCanHandle(swUI8 contentType)
{
    if (contentType == CT_UNKNOWN || contentType == CT_TEXT || contentType == CT_THML)
        return true;

    return false;
}

bool SwRichViewPanel::OnSetCanCopy(bool canCopy)
{
    m_view->SetCanCopy(canCopy);

    return true;
}

bool SwRichViewPanel::OnCanCopy()
{
    return m_view->GetCanCopy() && m_view->HasSelection();
}

bool SwRichViewPanel::OnCanDoPrint()
{
    return m_view->GetCanCopy();
}

bool SwRichViewPanel::OnCanDoPrintPreview()
{
    return true;
}

bool SwRichViewPanel::OnCanDoZoomIn()
{
    if (m_view->GetScale() < 2)
        return true;

    return false;
}

bool SwRichViewPanel::OnCanDoZoomOut()
{
    if (m_view->GetScale() > .5)
        return true;

    return false;
}

bool SwRichViewPanel::OnCanDoViewNormal()
{
    if (m_view->GetScale() != 1)
        return true;

    return false;
}

bool SwRichViewPanel::OnSetSwThMLTreeCtrl(SwThMLTreeCtrl * ctrl)
{
    m_view->SetThMLTreeCtrl(ctrl);

    return true;
}

bool SwRichViewPanel::OnFindReset()
{
    m_view->GetFindReplace().Reset();

    return true;
}

bool SwRichViewPanel::OnFindSetCaseSensitive(bool caseSensitive)
{
    m_view->GetFindReplace().SetCaseSensitive(caseSensitive);

    return true;
}

bool SwRichViewPanel::OnFindSetWholeWordOnly(bool wholewordOnly)
{
    m_view->GetFindReplace().SetWholeWordOnly(wholewordOnly);

    return true;
}

bool SwRichViewPanel::OnCopy()
{
    wxCommandEvent event;
    m_view->OnCopy(event);

    return true;
}

bool SwRichViewPanel::OnSelectAll()
{
    m_view->SelectAll();

    return true;
}

bool SwRichViewPanel::OnPrint()
{
    wxCommandEvent event;
    m_view->OnPrint(event);

    return true;
}

bool SwRichViewPanel::OnPrintPreview()
{
    wxCommandEvent event;
    m_view->OnPrintPreview(event);

    return true;
}

bool SwRichViewPanel::OnZoomIn()
{
    m_view->SetScale(m_view->GetScale() + .1, true);

    return true;
}

bool SwRichViewPanel::OnZoomOut()
{
    m_view->SetScale(m_view->GetScale() - .1, true);

    return true;
}

bool SwRichViewPanel::OnViewNormal()
{
    m_view->SetScale(1, true);

    return true;
}

bool SwRichViewPanel::OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    return m_view->GetFindReplace().Find(text, casesensitive, wholewordonly);
}

bool SwRichViewPanel::OnFindNext()
{
    return m_view->GetFindReplace().FindNext();
}

bool SwRichViewPanel::OnHilite(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    return m_view->GetFindReplace().Hilite(text, casesensitive, wholewordonly);
}

void SwRichViewPanel::OnEnableAutoDef(bool enable)
{
    m_view->EnableAutoDef(enable);
}

void SwRichViewPanel::OnSetPopUpMenu(SwMenu * menu)
{
    m_view->SetViewMenu(menu);
}

void SwRichViewPanel::OnResize(wxSizeEvent& event)
{
    if (m_view)
        m_view->SetSize(GetParent()->GetSize());

    event.Skip();
}


SwImageViewPanel::SwImageViewPanel()
{
    m_view = NULL;
}

SwImageViewPanel::SwImageViewPanel(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwViewPanel(parent, id, pos, size, style, name)
{
    m_view = new SwImageWindow(this, id, pos, size, 0, name);
    m_view->SetShowTips(true);
    m_view->EnableAutoDef(true);

    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwImageViewPanel::OnResize);
}

SwImageViewPanel::~SwImageViewPanel()
{
}

bool SwImageViewPanel::OnLoad(SwPageData & pageData)
{
    SwString data;
    bool canCopy;

    SwApplicationInterface::GetModuleManager().LoadPage(pageData, data, canCopy);


    m_view->Reset();
    m_view->SetCanCopy(canCopy);

    SwApplicationInterface::GetImageInterface().SetImageWindow(m_view);
    return SwApplicationInterface::GetImageInterface().Load(data, data.Strlen());
}

bool SwImageViewPanel::OnLoad(swUI8 contentType, SwStreamBuffer & data, const SwGeoConversionData * cd)
{
    if (cd)
    {
        m_view->GetImageMapList().SetUseGeo();
        m_view->GetImageMapList().SetConversionData(*cd);
    }

    return m_view->LoadImage(data);
}

bool SwImageViewPanel::OnReset()
{
    m_view->Reset();

    return true;
}

bool SwImageViewPanel::OnRefresh()
{
    m_view->Refresh();

    return true;
}

bool SwImageViewPanel::OnHasFocus()
{
    return m_view->HasFocus();
}

bool SwImageViewPanel::OnGetScrollPos(SwScrollData & scrolldata)
{
    m_view->GetScrollPosition(scrolldata);

    return true;
}

bool SwImageViewPanel::OnSetScrollPos(SwScrollData & scrolldata)
{
    m_view->ScrollToLocation(scrolldata);

    return true;
}

bool SwImageViewPanel::OnCanHandle(swUI8 contentType)
{
    if (contentType == CT_IMAGE)
        return true;

    return false;
}

bool SwImageViewPanel::OnSetCanCopy(bool canCopy)
{
    m_view->SetCanCopy(canCopy);

    return true;
}

bool SwImageViewPanel::OnCanCopy()
{
    return m_view->GetCanCopy();
}

bool SwImageViewPanel::OnCanDoPrint()
{
    return m_view->GetCanCopy();
}

bool SwImageViewPanel::OnCanDoZoomIn()
{
    if (m_view->GetZoom() < 3)
        return true;

    return false;
}

bool SwImageViewPanel::OnCanDoZoomOut()
{
    if (m_view->GetZoom() > .5)
        return true;

    return false;
}

bool SwImageViewPanel::OnCanDoViewNormal()
{
    if (m_view->GetZoom() != 1)
        return true;

    return false;
}

bool SwImageViewPanel::OnPrint()
{
    m_view->OnPrint(L"");

    return true;
}

bool SwImageViewPanel::OnZoomIn()
{
    m_view->OnZoomIn();

    return true;
}

bool SwImageViewPanel::OnZoomOut()
{
    m_view->OnZoomOut();

    return true;
}

bool SwImageViewPanel::OnViewNormal()
{
    m_view->OnViewNormal();

    return true;
}

void SwImageViewPanel::OnEnableAutoDef(bool enable)
{
    m_view->EnableAutoDef(enable);
}

void SwImageViewPanel::OnResize(wxSizeEvent& event)
{
    if (m_view)
        m_view->SetSize(GetParent()->GetSize());

    event.Skip();
}

void SwImageViewPanel::OnSetPopUpMenu(SwMenu * menu)
{
    m_view->SetPopUpMenu(menu);
}

SwMapViewPanel::SwMapViewPanel()
{
}

SwMapViewPanel::SwMapViewPanel(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwImageViewPanel(parent, id, value, pos, size, style, validator, name)
{
    m_view = new SwImageWindow(this, id, pos, size, 0, name);
    m_find.SetView(m_view);

    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwMapViewPanel::OnResize);
}

SwMapViewPanel::~SwMapViewPanel()
{
}

bool SwMapViewPanel::OnCanHandle(swUI8 contentType)
{
    if (contentType == CT_MAP)
        return true;

    return false;
}

bool SwMapViewPanel::OnFindReset()
{
    m_find.Reset();

    return true;
}

bool SwMapViewPanel::OnFindSetCaseSensitive(bool caseSensitive)
{
    m_find.SetCaseSensitive(caseSensitive);

    return true;
}

bool SwMapViewPanel::OnFindSetWholeWordOnly(bool wholewordOnly)
{
    m_find.SetWholeWordOnly(wholewordOnly);

    return true;
}

bool SwMapViewPanel::OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    SwString location;
    location.Copy(text);

    return m_find.Find(location, casesensitive, wholewordonly);
}

bool SwMapViewPanel::OnFindNext()
{
    return m_find.FindNext();
}

IMPLEMENT_DYNAMIC_CLASS(SwViewBook, wxSimplebook)

SwViewBook::SwViewBook()
{
    SetBackgroundColour(*wxWHITE);
    m_multifiletree = NULL;
    m_menu = NULL;
    m_enableAutoDef = true;
}

SwViewBook::SwViewBook(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxSimplebook(parent, id, pos, size, style, name)
{
    SetBackgroundColour(*wxWHITE);
    m_multifiletree = NULL;
    m_menu = NULL;
    m_enableAutoDef = true;
}

SwViewBook::~SwViewBook()
{
}

bool SwViewBook::OnLoad(SwPageData & pageData)
{
    SwViewPanel * panel;

    swUI16 pos = SwApplicationInterface::GetModuleManager().FindByMID(pageData.m_managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = SwApplicationInterface::GetModuleManager().GetAt(pos);

    if (!module)
        return false;

    swUI8 type = module->GetTableofContents().GetContentType(pageData.m_pageId);

    int page;

    page = FindViewer(type);

    if (page == -1)
    {
        if (!AddViewer(type))
            return false;

        page = FindViewer(type);
    }

    panel = (SwViewPanel *) GetPage(page);

    ChangeSelection(page);

    return panel->OnLoad(pageData);
}

bool SwViewBook::OnLoad(swUI8 contentType, SwStreamBuffer & data)
{
    SwViewPanel * panel;

    int page;

    page = FindViewer(contentType);

    if (page == -1)
    {
        if (!AddViewer(contentType))
            return false;

        page = FindViewer(contentType);
    }

    panel = (SwViewPanel *) GetPage(page);

    ChangeSelection(page);

    if (panel)
        return panel->OnLoad(contentType, data);

    return false;
}

bool SwViewBook::OnWriteXmlText(swUI8 contentType, const char * source, bool thml,  const char * basePath)
{
    SwViewPanel * panel;

    int page;

    page = FindViewer(contentType);

    if (page == -1)
    {
        if (!AddViewer(contentType))
            return false;

        page = FindViewer(contentType);
    }

    panel = (SwViewPanel *) GetPage(page);

    ChangeSelection(page);

    if (panel)
        return panel->OnWriteXmlText(contentType, source, thml, basePath);

    return false;
}

bool SwViewBook::OnWriteXmlText(swUI8 contentType, const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath)
{
    SwViewPanel * panel;

    int page;

    page = FindViewer(contentType);

    if (page == -1)
    {
        if (!AddViewer(contentType))
            return false;

        page = FindViewer(contentType);
    }

    panel = (SwViewPanel *) GetPage(page);

    ChangeSelection(page);

    if (panel)
        return panel->OnWriteXmlText(contentType, source, length, thml, list, basePath);

    return false;
}


bool SwViewBook::OnReset()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnReset();

    SetTitle("");

    return false;
}

bool SwViewBook::OnRefresh()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnRefresh();

    return false;
}

bool SwViewBook::OnHasFocus()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnHasFocus();

    return false;
}

bool SwViewBook::OnHasSelection()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnHasSelection();

    return false;
}

bool SwViewBook::OnGetSelectedText(SwString & buffer)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnGetSelectedText(buffer);

    return false;
}

bool SwViewBook::OnGetSelection(SwTextRange & selection)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnGetSelection(selection);

    return false;
}

bool SwViewBook::OnSetSelection(SwTextRange & selection)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnSetSelection(selection);

    return false;
}

bool SwViewBook::OnGetScrollPos(SwScrollData & scrolldata)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnGetScrollPos(scrolldata);

    return false;
}

bool SwViewBook::OnSetScrollPos(SwScrollData & scrolldata)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnSetScrollPos(scrolldata);

    return false;
}

bool SwViewBook::OnCanHandle(swUI8 contentType)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanHandle(contentType);

    return false;
}

bool SwViewBook::OnSetCanCopy(bool canCopy)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnSetCanCopy(canCopy);

    return false;
}

bool SwViewBook::OnCanCopy()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanCopy();

    return false;
}

bool SwViewBook::OnCanDoPrint()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoPrint();

    return false;
}

bool SwViewBook::OnCanDoPrintPreview()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoPrintPreview();

    return false;
}

bool SwViewBook::OnCanZoomIn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoZoomIn();

    return false;
}

bool SwViewBook::OnCanZoomOut()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoZoomOut();

    return false;
}

bool SwViewBook::OnCanViewNormal()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoViewNormal();

    return false;
}

bool SwViewBook::OnCanDoPlay()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoPlay();

    return false;
}

bool SwViewBook::OnCanDoPause()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoPause();

    return false;
}

bool SwViewBook::OnCanDoStop()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoStop();

    return false;
}

bool SwViewBook::OnCanDoRewind()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoRewind();

    return false;
}

bool SwViewBook::OnCanDoFastForward()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoFastForward();

    return false;
}

bool SwViewBook::OnCanDoPrevious()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoPrevious();

    return false;
}

bool SwViewBook::OnCanDoNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCanDoNext();

    return false;
}

bool SwViewBook::OnSetSwThMLTreeCtrl(SwThMLTreeCtrl * ctrl)
{
    m_multifiletree = ctrl;

    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnSetSwThMLTreeCtrl(ctrl);

    return false;
}

bool SwViewBook::OnFindReset()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnFindReset();

    return false;
}

bool SwViewBook::OnFindSetCaseSensitive(bool casesensitive)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnFindSetCaseSensitive(casesensitive);

    return false;
}

bool SwViewBook::OnFindSetWholeWordOnly(bool wholewordonly)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnFindSetWholeWordOnly(wholewordonly);

    return false;
}

bool SwViewBook::OnPrint()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnPrint();

    return false;
}

bool SwViewBook::OnPrintPreview()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnPrintPreview();

    return false;
}

bool SwViewBook::OnCopy()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnCopy();

    return false;
}

bool SwViewBook::OnSelectAll()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnSelectAll();

    return false;
}

bool SwViewBook::OnZoomIn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnZoomIn();

    return false;
}

bool SwViewBook::OnZoomOut()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnZoomOut();

    return false;
}

bool SwViewBook::OnViewNormal()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnViewNormal();

    return false;
}

bool SwViewBook::OnFind(wchar_t * text, bool casesensitive, bool wholewordonly)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnFind(text, casesensitive, wholewordonly);

    return false;
}

bool SwViewBook::OnFindNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnFindNext();

    return false;
}

bool SwViewBook::OnHilite(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnHilite(text, casesensitive, wholewordonly);

    return false;
}

bool SwViewBook::OnPlay()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnPlay();

    return false;
}

bool SwViewBook::OnPause()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnPause();

    return false;
}

bool SwViewBook::OnStop()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnStop();

    return false;
}

bool SwViewBook::OnRewind()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnRewind();

    return false;
}

bool SwViewBook::OnFastForward()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnFastForward();

    return false;
}

bool SwViewBook::OnPrevious()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnPrevious();

    return false;
}

bool SwViewBook::OnNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwViewPanel * panel = (SwViewPanel *) GetPage(page);

    if (panel)
        return panel->OnNext();

    return false;
}

void SwViewBook::OnEnableAutoDef(bool enable)
{
    SwViewPanel * panel;

    m_enableAutoDef = enable;

    for (int i = 0; i < (signed) GetPageCount(); i ++)
    {
        panel = (SwViewPanel *) GetPage(i);
        panel->OnEnableAutoDef(enable);
    }
}

void SwViewBook::OnLanguageChange()
{
}

void SwViewBook::OnThemeChange()
{
}

void SwViewBook::OnFontSizeChange(const wxFont & font)
{
}

void SwViewBook::OnSetPopUpMenu(SwMenu * menu)
{
    SwViewPanel * panel;
    m_menu = menu;
    for (int i = 0; i < (signed) GetPageCount(); i ++)
    {
        panel = (SwViewPanel *) GetPage(i);
        panel->OnSetPopUpMenu(menu);
    }
}

int SwViewBook::FindViewer(swUI8 contentType)
{
    SwViewPanel * panel;

    int page = GetSelection();

    if (page != wxNOT_FOUND)
    {
        panel = (SwViewPanel *) GetPage(page);

        if (panel)
            panel->OnReset();
    }

    for (int i = 0; i < (signed) GetPageCount(); i ++)
    {
        panel = (SwViewPanel *) GetPage(i);

        if (panel->OnCanHandle(contentType))
        {
            return i;
        }
    }

    return -1;
}

bool SwViewBook::AddViewer(swUI8 contentType)
{
    SwPlugIn * plugIn;
    SwViewPanel * panel;
    int page;

    for (swUI16 i = 0; i < SwApplicationInterface::GetPlugInManager().GetCount(); i ++)
    {
        plugIn = SwApplicationInterface::GetPlugInManager().GetAt(i);

        if (plugIn->GetType() != PIT_VIEWER)
            continue;

        if (plugIn->CanHandle(contentType) && plugIn->AddViewer(contentType, this))
        {
            page = FindViewer(contentType);
            panel = (SwViewPanel *) GetPage(page);
            panel->OnSetSwThMLTreeCtrl(m_multifiletree);
            panel->OnSetPopUpMenu(m_menu);
            panel->OnEnableAutoDef(m_enableAutoDef);
            return true;
        }
    }

    if (contentType == CT_UNKNOWN || contentType == CT_TEXT || contentType == CT_THML || contentType == CT_HTML)
    {
        SwRichViewPanel * panel = new SwRichViewPanel(this, wxNewId(), L"", wxDefaultPosition, wxSize(0, 0), 0, wxDefaultValidator, L"RICHPANEL");
        panel->OnSetSwThMLTreeCtrl(m_multifiletree);
        panel->OnSetPopUpMenu(m_menu);
        ShowNewPage(panel);
        return true;
    }
    else if (contentType == CT_IMAGE)
    {
        SwImageViewPanel * panel = new SwImageViewPanel(this, wxNewId(), L"", wxDefaultPosition, wxSize(0, 0), 0, wxDefaultValidator, L"IMAGEPANEL");
        panel->OnSetPopUpMenu(m_menu);
        ShowNewPage(panel);
        return true;
    }
    else if (contentType == CT_MAP)
    {
        SwMapViewPanel * panel = new SwMapViewPanel(this, wxNewId(), L"", wxDefaultPosition, wxSize(0, 0), 0, wxDefaultValidator, L"MAPPANEL");
        panel->OnSetPopUpMenu(m_menu);
        ShowNewPage(panel);
        return true;
    }

    return false;
}

void SwViewBook::ResetAll()
{
    SwViewPanel * panel;

    for (int i = 0; i < (signed) GetPageCount(); i ++)
    {
        panel = (SwViewPanel *) GetPage(i);
        panel->OnReset();
    }
}
