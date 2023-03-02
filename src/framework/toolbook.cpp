///////////////////////////////////////////////////////////////////
// Name:        toolbook.cpp
// Purpose:     SwToolBook - a notebook control for SwPanels,
//              SwToolBook routes signals to the top level panel.
//              SwToolBar | SwMenuBar -> SwFrame -> SwToolBook -> SwPanel -> SwViewBook etc.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/toolbook.h"
#include "../../include/appi/appifa.h"
#include "../../include/string/strparser.h"
#include "../../include/thml/thml_parser.h"

// wxTabFrame from wxWidgets src - auibook.cpp
#if wxCHECK_VERSION(3, 1, 0)
class wxTabFrame : public wxWindow
{
public:

    wxTabFrame()
    {
        m_tabs = NULL;
        m_rect = wxRect(wxPoint(0,0), FromDIP(wxSize(200,200)));
        m_tabCtrlHeight = FromDIP(20);
    }

    ~wxTabFrame()
    {
        wxDELETE(m_tabs);
    }

    void SetTabCtrlHeight(int h)
    {
        m_tabCtrlHeight = h;
    }

protected:
    void DoSetSize(int x, int y,
                   int width, int height,
                   int WXUNUSED(sizeFlags = wxSIZE_AUTO)) wxOVERRIDE
    {
        m_rect = wxRect(x, y, width, height);
        DoSizing();
    }

    void DoGetClientSize(int* x, int* y) const wxOVERRIDE
    {
        *x = m_rect.width;
        *y = m_rect.height;
    }

public:
    bool Show( bool WXUNUSED(show = true) ) wxOVERRIDE { return false; }

    void DoSizing()
    {
        if (!m_tabs)
            return;

        if (m_tabs->IsFrozen() || m_tabs->GetParent()->IsFrozen())
            return;

        m_tab_rect = wxRect(m_rect.x, m_rect.y, m_rect.width, m_tabCtrlHeight);
        if (m_tabs->GetFlags() & wxAUI_NB_BOTTOM)
        {
            m_tab_rect = wxRect (m_rect.x, m_rect.y + m_rect.height - m_tabCtrlHeight, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetSize     (m_rect.x, m_rect.y + m_rect.height - m_tabCtrlHeight, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetRect     (wxRect(0, 0, m_rect.width, m_tabCtrlHeight));
        }
        else //TODO: if (GetFlags() & wxAUI_NB_TOP)
        {
            m_tab_rect = wxRect (m_rect.x, m_rect.y, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetSize     (m_rect.x, m_rect.y, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetRect     (wxRect(0, 0,        m_rect.width, m_tabCtrlHeight));
        }
        // TODO: else if (GetFlags() & wxAUI_NB_LEFT){}
        // TODO: else if (GetFlags() & wxAUI_NB_RIGHT){}

        m_tabs->Refresh();
        m_tabs->Update();

        wxAuiNotebookPageArray& pages = m_tabs->GetPages();
        size_t i, page_count = pages.GetCount();

        for (i = 0; i < page_count; ++i)
        {
            wxAuiNotebookPage& page = pages.Item(i);
            int border_space = m_tabs->GetArtProvider()->GetAdditionalBorderSpace(page.window);

            int height = m_rect.height - m_tabCtrlHeight - border_space;
            if ( height < 0 )
            {
                // avoid passing negative height to wxWindow::SetSize(), this
                // results in assert failures/GTK+ warnings
                height = 0;
            }
            int width = m_rect.width - 2 * border_space;
            if (width < 0)
                width = 0;

            if (m_tabs->GetFlags() & wxAUI_NB_BOTTOM)
            {
                page.window->SetSize(m_rect.x + border_space,
                                     m_rect.y + border_space,
                                     width,
                                     height);
            }
            else //TODO: if (GetFlags() & wxAUI_NB_TOP)
            {
                page.window->SetSize(m_rect.x + border_space,
                                     m_rect.y + m_tabCtrlHeight,
                                     width,
                                     height);
            }
            // TODO: else if (GetFlags() & wxAUI_NB_LEFT){}
            // TODO: else if (GetFlags() & wxAUI_NB_RIGHT){}
        }
    }

protected:
    void DoGetSize(int* x, int* y) const wxOVERRIDE
    {
        if (x)
            *x = m_rect.GetWidth();
        if (y)
            *y = m_rect.GetHeight();
    }

public:
    void Update() wxOVERRIDE
    {
        // does nothing
    }

    wxRect m_rect;
    wxRect m_tab_rect;
    wxAuiTabCtrl* m_tabs;
    int m_tabCtrlHeight;
};
#else
class wxTabFrame : public wxWindow
{
public:

    wxTabFrame()
    {
        m_tabs = NULL;
        m_rect = wxRect(0,0,200,200);
        m_tabCtrlHeight = 20;
    }

    ~wxTabFrame()
    {
        wxDELETE(m_tabs);
    }

    void SetTabCtrlHeight(int h)
    {
        m_tabCtrlHeight = h;
    }

protected:
    void DoSetSize(int x, int y,
                   int width, int height,
                   int WXUNUSED(sizeFlags = wxSIZE_AUTO))
    {
        m_rect = wxRect(x, y, width, height);
        DoSizing();
    }

    void DoGetClientSize(int* x, int* y) const
    {
        *x = m_rect.width;
        *y = m_rect.height;
    }

public:
    bool Show( bool WXUNUSED(show = true) )
    {
        return false;
    }

    void DoSizing()
    {
        if (!m_tabs)
            return;

        if (m_tabs->IsFrozen() || m_tabs->GetParent()->IsFrozen())
            return;

        m_tab_rect = wxRect(m_rect.x, m_rect.y, m_rect.width, m_tabCtrlHeight);
        if (m_tabs->GetFlags() & wxAUI_NB_BOTTOM)
        {
            m_tab_rect = wxRect (m_rect.x, m_rect.y + m_rect.height - m_tabCtrlHeight, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetSize     (m_rect.x, m_rect.y + m_rect.height - m_tabCtrlHeight, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetRect     (wxRect(0, 0, m_rect.width, m_tabCtrlHeight));
        }
        else //TODO: if (GetFlags() & wxAUI_NB_TOP)
        {
            m_tab_rect = wxRect (m_rect.x, m_rect.y, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetSize     (m_rect.x, m_rect.y, m_rect.width, m_tabCtrlHeight);
            m_tabs->SetRect     (wxRect(0, 0,        m_rect.width, m_tabCtrlHeight));
        }
        // TODO: else if (GetFlags() & wxAUI_NB_LEFT){}
        // TODO: else if (GetFlags() & wxAUI_NB_RIGHT){}

        m_tabs->Refresh();
        m_tabs->Update();

        wxAuiNotebookPageArray& pages = m_tabs->GetPages();
        size_t i, page_count = pages.GetCount();

        for (i = 0; i < page_count; ++i)
        {
            wxAuiNotebookPage& page = pages.Item(i);
            int border_space = m_tabs->GetArtProvider()->GetAdditionalBorderSpace(page.window);

            int height = m_rect.height - m_tabCtrlHeight - border_space;
            if ( height < 0 )
            {
                // avoid passing negative height to wxWindow::SetSize(), this
                // results in assert failures/GTK+ warnings
                height = 0;
            }
            int width = m_rect.width - 2 * border_space;
            if (width < 0)
                width = 0;

            if (m_tabs->GetFlags() & wxAUI_NB_BOTTOM)
            {
                page.window->SetSize(m_rect.x + border_space,
                                     m_rect.y + border_space,
                                     width,
                                     height);
            }
            else //TODO: if (GetFlags() & wxAUI_NB_TOP)
            {
                page.window->SetSize(m_rect.x + border_space,
                                     m_rect.y + m_tabCtrlHeight,
                                     width,
                                     height);
            }
            // TODO: else if (GetFlags() & wxAUI_NB_LEFT){}
            // TODO: else if (GetFlags() & wxAUI_NB_RIGHT){}

#if wxUSE_MDI
            if (wxDynamicCast(page.window, wxAuiMDIChildFrame))
            {
                wxAuiMDIChildFrame* wnd = (wxAuiMDIChildFrame*)page.window;
                wnd->ApplyMDIChildFrameRect();
            }
#endif
        }
    }

protected:
    void DoGetSize(int* x, int* y) const
    {
        if (x)
            *x = m_rect.GetWidth();
        if (y)
            *y = m_rect.GetHeight();
    }

public:
    void Update()
    {
        // does nothing
    }

    wxRect m_rect;
    wxRect m_tab_rect;
    wxAuiTabCtrl* m_tabs;
    int m_tabCtrlHeight;
};
#endif // wxCHECK_VERSION

IMPLEMENT_DYNAMIC_CLASS(SwToolBook, wxAuiNotebook)

SwToolBook::SwToolBook()
{
    Init();
}

SwToolBook::SwToolBook(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxAuiNotebook(parent, id, pos, size, style | wxAUI_NB_SCROLL_BUTTONS)
{
    Init();
    Connect(id,wxEVT_AUINOTEBOOK_PAGE_CLOSE,(wxObjectEventFunction)&SwToolBook::OnClosePanelEvent);
}

SwToolBook::~SwToolBook()
{
}

void SwToolBook::Init()
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
}

bool SwToolBook::OnNew()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnNew();
}

bool SwToolBook::OnOpen()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnOpen();
}

bool SwToolBook::OnRecentFiles()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnRecentFiles();
}

bool SwToolBook::OnSave()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSave();
}

bool SwToolBook::OnSaveAs()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSaveAs();
}

bool SwToolBook::OnClose()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);
    bool state = panel->OnClose();

    if (state)
        DeletePage(page);

    return state;
}

bool SwToolBook::OnCloseAll()
{
    for(int curPage = GetPageCount() - 1; curPage > -1; curPage --)
    {
        SwPanel * panel = (SwPanel *) GetPage(curPage);

        if (panel->OnClose())
            DeletePage(curPage);
        else
            return false;
    }

    return true;
}

bool SwToolBook::OnPrint()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnPrint();
}

bool SwToolBook::OnPrintPreview()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnPrintPreview();
}

bool SwToolBook::OnFile1()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile1();
}

bool SwToolBook::OnFile2()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile2();
}

bool SwToolBook::OnFile3()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile3();
}

bool SwToolBook::OnFile4()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile4();
}

bool SwToolBook::OnFile5()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile5();
}

bool SwToolBook::OnFile6()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile6();
}

bool SwToolBook::OnFile7()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile7();
}

bool SwToolBook::OnFile8()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile8();
}

bool SwToolBook::OnFile9()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile9();
}

bool SwToolBook::OnFile10()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFile10();
}

bool SwToolBook::OnBookMarkPage()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnBookMarkPage();
}

bool SwToolBook::OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFind(text, casesensitive, wholewordonly);
}

bool SwToolBook::OnFindReset()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFindReset();
}

bool SwToolBook::OnFindSetCaseSensitive(bool caseSensitive)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFindSetCaseSensitive(caseSensitive);
}

bool SwToolBook::OnFindSetWholeWordOnly(bool wholewordOnly)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFindSetWholeWordOnly(wholewordOnly);
}

bool SwToolBook::OnFindNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFindNext();
}

bool SwToolBook::OnReplace()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnReplace();
}

bool SwToolBook::OnReplaceAll()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnReplaceAll();
}

bool SwToolBook::OnClear()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnClear();
}

bool SwToolBook::OnCut()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCut();
}

bool SwToolBook::OnCopy()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCopy();
}

bool SwToolBook::OnPaste()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnPaste();
}

bool SwToolBook::OnUndo()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnUndo();
}

bool SwToolBook::OnRedo()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnRedo();
}

bool SwToolBook::OnSelectAll()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSelectAll();
}

bool SwToolBook::OnProperties()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnProperties();
}

bool SwToolBook::OnLibraryView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnLibraryView();
}

bool SwToolBook::OnContentsView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnContentsView();
}

bool SwToolBook::OnSearchView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSearchView();
}

bool SwToolBook::OnFindView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFindView();
}

bool SwToolBook::OnBookmarksView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnBookmarksView();
}

bool SwToolBook::OnHistoryView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnHistoryView();
}

bool SwToolBook::OnZoomIn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnZoomIn();
}

bool SwToolBook::OnZoomOut()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnZoomOut();
}

bool SwToolBook::OnViewNormal()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnViewNormal();
}

bool SwToolBook::OnContentsUp()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnContentsUp();
}

bool SwToolBook::OnContentsDown()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnContentsDown();
}

bool SwToolBook::OnHistoryBack()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnHistoryBack();
}

bool SwToolBook::OnHistoryForward()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnHistoryForward();
}

bool SwToolBook::OnFont()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFont();
}

bool SwToolBook::OnBold()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnBold();
}

bool SwToolBook::OnItalic()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnItalic();
}

bool SwToolBook::OnUnderline()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnUnderline();
}

bool SwToolBook::OnStrikeThrough()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnStrikeThrough();
}

bool SwToolBook::OnSuperScript()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSuperScript();
}

bool SwToolBook::OnSubScript()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSubScript();
}

bool SwToolBook::OnColor()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnColor();
}

bool SwToolBook::OnBackgroundColor()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnBackgroundColor();
}

bool SwToolBook::OnStyle()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnStyle();
}

bool SwToolBook::OnMargins()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnMargins();
}

bool SwToolBook::OnIndentMore()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnIndentMore();
}

bool SwToolBook::OnIndentLess()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnIndentLess();
}

bool SwToolBook::OnAlignLeft()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnAlignLeft();
}

bool SwToolBook::OnAlignCenter()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnAlignCenter();
}

bool SwToolBook::OnAlignRight()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnAlignRight();
}

bool SwToolBook::OnSingleSpacing()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnSingleSpacing();
}

bool SwToolBook::OnDoubleSpacing()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnDoubleSpacing();
}

bool SwToolBook::OnAlphaList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnAlphaList();
}

bool SwToolBook::OnBulletedList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnBulletedList();
}

bool SwToolBook::OnRomanList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnRomanList();
}

bool SwToolBook::OnDecimalList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnDecimalList();
}

bool SwToolBook::OnInsertTable()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertTable();
}

bool SwToolBook::OnInsertRow()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertRow();
}

bool SwToolBook::OnDeleteRow()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnDeleteRow();
}

bool SwToolBook::OnInsertColumn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertColumn();
}

bool SwToolBook::OnDeleteColumn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnDeleteColumn();
}

bool SwToolBook::OnInsertImage()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertImage();
}

bool SwToolBook::OnInsertLink()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertLink();
}

bool SwToolBook::OnInsertAnchor()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertAnchor();
}

bool SwToolBook::OnInsertControl()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertControl();
}

bool SwToolBook::OnInsertHorizontalRule()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnInsertHorizontalRule();
}

bool SwToolBook::OnPlay()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnPlay();
}

bool SwToolBook::OnPause()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnPause();
}

bool SwToolBook::OnStop()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnStop();
}

bool SwToolBook::OnRewind()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnRewind();
}

bool SwToolBook::OnFastForward()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnFastForward();
}

bool SwToolBook::OnPrevious()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnPrevious();
}

bool SwToolBook::OnNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnNext();
}

void SwToolBook::OnPreferences()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return;

    SwPanel * panel = (SwPanel *) GetPage(page);

    panel->OnPreferences();
}

void SwToolBook::OnHelpContents()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return;

    SwPanel * panel = (SwPanel *) GetPage(page);

    panel->OnHelpContents();
}

void SwToolBook::OnAbout()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return;

    SwPanel * panel = (SwPanel *) GetPage(page);

    panel->OnAbout();
}

void SwToolBook::OnUpdateSoftware()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return;

    SwPanel * panel = (SwPanel *) GetPage(page);

    panel->OnUpdateSoftware();
}

// Pages in SwToolBook should be derived from SwPanel, and will receive these notifications
// from SwApplicationInterface.
void SwToolBook::OnLanguageChange()
{
    for (size_t tab = 0; tab < GetPageCount(); tab ++)
    {
        wxWindow * win = GetPage(tab);

        if (win && win->IsKindOf(CLASSINFO(SwPanel)))
        {
            SwPanel * panel = wxDynamicCast(win, SwPanel);
            if (panel)
                panel->UpdateLabel(this, tab);
        }
    }
}

void SwToolBook::OnThemeChange()
{
}

void SwToolBook::OnFontSizeChange()
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
}

void SwToolBook::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return;

    SwPanel * panel = (SwPanel *) GetPage(page);

    panel->UpdateGui(toolbar, menubar);
}

bool SwToolBook::OnHasFocus()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnHasFocus();
}

bool SwToolBook::OnHasSelection()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnHasSelection();
}

void SwToolBook::OnModuleManagerReset()
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnModuleManagerReset();
    }
}

void SwToolBook::OnThMLFileManagerReset()
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnThMLFileManagerReset();
    }
}

void SwToolBook::OnModuleManagerLoaded()
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnModuleManagerLoaded();
    }
}

void SwToolBook::OnThMLFileManagerLoaded()
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnThMLFileManagerLoaded();
    }
}

void SwToolBook::OnModuleAdded(swUI16 mid)
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnModuleAdded(mid);
    }
}
void SwToolBook::OnModuleDeleted(swUI16 mid)
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnModuleDeleted(mid);
    }
}

void SwToolBook::OnThMLFileAdded(swUI16 mid)
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnThMLFileAdded(mid);
    }
}

void SwToolBook::OnThMLFileDeleted(swUI16 mid)
{
    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->OnThMLFileDeleted(mid);
    }
}

void SwToolBook::OnClosePanelEvent(wxAuiNotebookEvent& event)
{
    SwPanel * panel = (SwPanel *) GetPage(event.GetSelection());
    if (!panel->OnClosePanel())
        event.Veto();
}

bool SwToolBook::OnClosePanel()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnClosePanel();
}

bool SwToolBook::OnCloseAllPanels()
{
    size_t pageCount = GetPageCount();
    for (size_t i = 0; i < pageCount; i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        if (!panel->OnClosePanel())
            return false;
    }

    return true;
}

bool SwToolBook::OnCanDoNew()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoNew();
}

bool SwToolBook::OnCanDoOpen()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoOpen();
}

bool SwToolBook::OnCanDoSave()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoSave();
}

bool SwToolBook::OnCanDoSaveAs()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoSaveAs();
}

bool SwToolBook::OnCanDoClose()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoClose();
}

bool SwToolBook::OnCanDoCloseAll()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoCloseAll();
}

bool SwToolBook::OnCanDoPrint()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoPrint();
}

bool SwToolBook::OnCanDoPrintPreview()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoPrintPreview();
}

bool SwToolBook::OnCanDoBookMarkPage()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoBookMarkPage();
}

bool SwToolBook::OnCanDoFind()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoFind();
}

bool SwToolBook::OnCanDoFindNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoFindNext();
}

bool SwToolBook::OnCanDoReplace()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoReplace();
}


bool SwToolBook::OnCanDoClear()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoClear();
}

bool SwToolBook::OnCanDoCut()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoCut();
}

bool SwToolBook::OnCanDoCopy()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoCopy();
}

bool SwToolBook::OnCanDoPaste()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoPaste();
}

bool SwToolBook::OnCanDoUndo()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoUndo();
}

bool SwToolBook::OnCanDoRedo()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoRedo();
}

bool SwToolBook::OnCanDoSelectAll()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoSelectAll();
}

bool SwToolBook::OnCanDoProperties()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoProperties();
}

bool SwToolBook::HasLibraryView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->HasLibraryView();
}

bool SwToolBook::HasContentsView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->HasContentsView();
}

bool SwToolBook::HasBookmarksView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->HasBookmarksView();
}

bool SwToolBook::HasFindView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->HasFindView();
}

bool SwToolBook::HasSearchView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->HasSearchView();
}

bool SwToolBook::HasHistoryView()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->HasHistoryView();
}

bool SwToolBook::OnCanDoZoomIn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoZoomIn();
}

bool SwToolBook::OnCanDoZoomOut()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoZoomOut();
}

bool SwToolBook::OnCanDoViewNormal()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoViewNormal();
}

bool SwToolBook::OnCanDoUpInContents()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoUpInContents();
}

bool SwToolBook::OnCanDoDownInContents()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoDownInContents();
}

bool SwToolBook::OnCanDoBackInHistory()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoBackInHistory();
}

bool SwToolBook::OnCanDoForwardInHistory()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoForwardInHistory();
}

bool SwToolBook::OnCanDoFont()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoFont();
}

bool SwToolBook::OnCanDoBold()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoBold();
}

bool SwToolBook::IsSelectionBold()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionBold();
}

bool SwToolBook::OnCanDoItalic()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoItalic();
}

bool SwToolBook::IsSelectionItalic()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionItalic();
}

bool SwToolBook::OnCanDoUnderline()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoUnderline();
}

bool SwToolBook::IsSelectionUnderline()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionUnderline();
}

bool SwToolBook::OnCanDoStrikeThrough()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoStrikeThrough();
}

bool SwToolBook::IsSelectionStrikeThrough()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionStrikeThrough();
}

bool SwToolBook::OnCanDoSuperScript()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoSuperScript();
}

bool SwToolBook::IsSelectionSuperScript()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionSuperScript();
}

bool SwToolBook::OnCanDoSubScript()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoSubScript();
}

bool SwToolBook::IsSelectionSubScript()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionSubScript();
}

bool SwToolBook::OnCanDoColor()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoColor();
}

bool SwToolBook::OnCanDoBackGroundColor()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoBackGroundColor();
}

bool SwToolBook::OnCanDoStyle()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoStyle();
}

bool SwToolBook::OnCanDoMargins()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoMargins();
}

bool SwToolBook::OnCanDoIndentMore()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoIndentMore();
}

bool SwToolBook::OnCanDoIndentLess()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoIndentLess();
}

bool SwToolBook::OnCanDoAlignLeft()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoAlignLeft();
}

bool SwToolBook::IsSelectionAlignLeft()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionAlignLeft();
}

bool SwToolBook::OnCanDoAlignCenter()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoAlignCenter();
}

bool SwToolBook::IsSelectionAlignCenter()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionAlignCenter();
}

bool SwToolBook::OnCanDoAlignRight()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoAlignRight();
}

bool SwToolBook::IsSelectionAlignRight()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionAlignRight();
}

bool SwToolBook::OnCanDoSingleSpacing()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoSingleSpacing();
}

bool SwToolBook::IsSelectionSingleSpacing()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionSingleSpacing();
}

bool SwToolBook::OnCanDoDoubleSpacing()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoDoubleSpacing();
}

bool SwToolBook::IsSelectionDoubleSpacing()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionDoubleSpacing();
}

bool SwToolBook::OnCanDoAlphaList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoAlphaList();
}

bool SwToolBook::IsSelectionAlphaList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionAlphaList();
}

bool SwToolBook::OnCanDoBulletedList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoBulletedList();
}

bool SwToolBook::IsSelectionBulletedList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionBulletedList();
}

bool SwToolBook::OnCanDoRomanNumeralsList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoRomanNumeralsList();
}

bool SwToolBook::IsSelectionRomanNumeralsList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionRomanNumeralsList();
}

bool SwToolBook::OnCanDoDecimalList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoDecimalList();
}

bool SwToolBook::IsSelectionDecimalList()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->IsSelectionDecimalList();
}

bool SwToolBook::OnCanDoInsertTable()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertTable();
}

bool SwToolBook::OnCanDoInsertRow()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertRow();
}

bool SwToolBook::OnCanDoDeleteRow()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoDeleteRow();
}

bool SwToolBook::OnCanDoInsertColumn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertColumn();
}

bool SwToolBook::OnCanDoDeleteColumn()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoDeleteColumn();
}

bool SwToolBook::OnCanDoInsertImage()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertImage();
}

bool SwToolBook::OnCanDoInsertLink()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertLink();
}

bool SwToolBook::OnCanDoInsertAnchor()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertAnchor();
}

bool SwToolBook::OnCanDoInsertControl()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertControl();
}

bool SwToolBook::OnCanDoInsertHorizontalRule()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoInsertHorizontalRule();
}

bool SwToolBook::OnCanDoPlay()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoPlay();
}

bool SwToolBook::OnCanDoPause()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoPause();
}

bool SwToolBook::OnCanDoStop()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoStop();
}

bool SwToolBook::OnCanDoRewind()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoRewind();
}

bool SwToolBook::OnCanDoFastForward()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoFastForward();
}

bool SwToolBook::OnCanDoPrevious()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoPrevious();
}

bool SwToolBook::OnCanDoNext()
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->OnCanDoNext();
}

bool SwToolBook::GetBookMarkData(SwString & title, SwBookMarkClientData & data)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->GetBookMarkData(title, data);
}

bool SwToolBook::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->ActivateBookMark(data, ctrlid);
}

bool SwToolBook::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->ActivateSearchItem(path, text, searchType, wordonly, casesensitive);
}

bool SwToolBook::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);

    return panel->ActivateSearchItem(managerId, text, searchType, wordonly, casesensitive);
}

bool SwToolBook::WriteGuiData(FILE * file)
{
    if (!file)
        return false;

    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        panel->WriteGuiData(file);
    }

    return true;
}

swUI32 SwToolBook::FindFile(const char * filepath)
{
    const char * path;

    if (!filepath)
        return NODE_ID_INVALID;

    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        if (!panel)
            continue;

        path = panel->GetFilePath();

        if (!path)
            continue;

        if (strcmp(filepath, path) == 0)
        {
            return i;
        }
    }

    return NODE_ID_INVALID;
}

swUI32 SwToolBook::FindModule(const char * bookId)
{
    const char * id;

    if (!bookId)
        return NODE_ID_INVALID;

    for (size_t i = 0; i < GetPageCount(); i ++)
    {
        SwPanel * panel = (SwPanel *) GetPage(i);

        if (!panel)
            continue;

        id = panel->GetBookId();

        if (!id)
            continue;

        if (strcmp(bookId, id) == 0)
        {
            return i;
        }
    }

    return NODE_ID_INVALID;
}

bool SwToolBook::OpenFile(const char * path)
{
    if (!path)
        return false;

    int page = GetSelection();

    if (page == wxNOT_FOUND)
        return false;

    SwPanel * panel = (SwPanel *) GetPage(page);


    return panel->OpenFile(path);
}

wxWindow * SwToolBook::FindTabFrame(const char * name)
{
    for (swUI32 i = 0; i < m_mgr.GetAllPanes().GetCount(); ++i)
    {
        if (m_mgr.GetAllPanes().Item(i).name == name)
            return m_mgr.GetAllPanes().Item(i).window;
    }

    return NULL;
}

swUI32 SwToolBook::FindTabFrameIdx(const char * name)
{
    for (swUI32 i = 0; i < m_mgr.GetAllPanes().GetCount(); ++i)
    {
        if (m_mgr.GetAllPanes().Item(i).name == name)
            return i;
    }

    return 1;
}

void SwToolBook::SetFocusToTabCtrl(swUI32 idx)
{
    if (idx >= m_mgr.GetAllPanes().GetCount())
        return;

    (((wxTabFrame *)((wxAuiPaneInfo &) m_mgr.GetAllPanes().Item(idx)).window))->m_tabs->SetFocus();
}

const char * SwToolBook::GetTabFrameAuiName(wxWindow * pane)
{
    wxAuiTabCtrl * ctrl;
    int index;

    if (!FindTab(pane, &ctrl, &index))
        return "";

    wxAuiPaneInfo & info = m_mgr.GetPane(GetTabFrameFromTabCtrl(ctrl));
    return info.name;
}

bool SwToolBook::Empty()
{
    int idx;
    wxAuiTabCtrl* ctrl;
    size_t pageCount = m_tabs.GetPageCount();

    for (swUI32 page = 0; page < pageCount; page ++)
    {
        if (!FindTab(m_tabs.GetWindowFromIdx(page), &ctrl, &idx))
            return false;

        if (!ctrl->RemovePage(m_tabs.GetWindowFromIdx(page)))
            return false;
    }

    RemoveEmptyTabFrames();

    return true;
}

SwString SwToolBook::SavePerspective()
{
    SwString perspective;
    char s[100];
    bool firstFrame = true;

    for (swUI32 frame = 0; frame < m_mgr.GetAllPanes().GetCount(); frame ++)
    {
        if (strcmp(m_mgr.GetAllPanes().Item(frame).name.utf8_str(), "dummy") == 0)
            continue;

        if (!firstFrame)
        {
            perspective += "|";
        }
        else
            firstFrame = false;

        perspective += "name=\"";
        perspective += m_mgr.GetAllPanes().Item(frame).name.utf8_str();
        perspective += "\"";

        for (size_t pane = 0; pane < ((wxTabFrame*)m_mgr.GetAllPanes().Item(frame).window)->m_tabs->GetPageCount(); pane ++)
        {
            perspective += ":";

            int idx = m_tabs.GetIdxFromWindow(((wxTabFrame*)m_mgr.GetAllPanes().Item(frame).window)->m_tabs->GetPage(pane).window);

            if (idx == m_curPage)
                perspective += "iscp=\"1\" ";
            else
                perspective += "iscp=\"0\" ";

            if (pane == (size_t)((wxTabFrame*)m_mgr.GetAllPanes().Item(frame).window)->m_tabs->GetActivePage())
                perspective += "isac=\"1\" ";
            else
                perspective += "isac=\"0\" ";

            sprintf(s, "index=\"%i\"", idx);
            perspective += s;
        }
    }

    perspective += "~";
    perspective += m_mgr.SavePerspective().utf8_str();

    return perspective;
}

bool SwToolBook::LoadPerspective(const char * perspective)
{
    if (!perspective || !Empty())
        return false;

    int selection = 0;
    SwStrParser parser1, parser2, parser3;
    SwString value;

    parser1.SetDeliminator('~');
    parser2.SetDeliminator('|');
    parser3.SetDeliminator(':');

    parser1.ParseStringStrict(perspective);
    parser2.ParseStringStrict(parser1.GetItem(0));

    for (swUI32 frame = 0; frame < parser2.GetItems(); frame ++)
    {
        parser3.ParseStringStrict(parser2.GetItem(frame));
        SwThMLParser::GetNamedValue("name", parser3.GetItem(0), value);

        wxTabFrame * tabframe = new wxTabFrame;
        tabframe->m_tabs = new wxAuiTabCtrl(this, m_tabIdCounter++);
        tabframe->m_tabs->SetArtProvider(m_tabs.GetArtProvider()->Clone());
        tabframe->SetTabCtrlHeight(m_tabCtrlHeight);
        tabframe->m_tabs->SetFlags(m_flags);
        m_mgr.AddPane(tabframe, wxAuiPaneInfo().CaptionVisible(false).Name(value.GetArray()));

        for (swUI32 i = 1; i < parser3.GetItems(); i ++)
        {
            SwThMLParser::GetNamedValue("index", parser3.GetItem(i), value);
            size_t index = (size_t) value.Atoi();
            if (index >= m_tabs.GetPageCount())
                continue;
            tabframe->m_tabs->InsertPage(m_tabs.GetPage(index).window, m_tabs.GetPage(index), tabframe->m_tabs->GetPageCount());
            SwThMLParser::GetNamedValue("isac", parser3.GetItem(i), value);
            if (value.BoolFromString())
                tabframe->m_tabs->SetActivePage(tabframe->m_tabs->GetPageCount() - 1);
            SwThMLParser::GetNamedValue("iscp", parser3.GetItem(i), value);
            if (value.BoolFromString())
                selection = index;
        }

        tabframe->m_tabs->DoShowHide();
    }

    m_mgr.LoadPerspective(parser1.GetItem(1));
    RemoveEmptyTabFrames();
    SetSelection(selection);

    return true;
}

