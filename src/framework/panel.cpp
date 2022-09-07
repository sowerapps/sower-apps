///////////////////////////////////////////////////////////////////
// Name:        panel.cpp
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/panel.h"
#include "../../include/framework/viewbook.h"
#include "../../include/appi/appifa.h"
#include "../../include/controls/moduletreectrl.h"
#include "../../include/controls/thmltreectrl.h"
#include "../../include/richtext/richtextctrlext.h"

IMPLEMENT_DYNAMIC_CLASS(SwPanel, wxPanel)

SwPanel::SwPanel()
{
    m_manager = NULL;
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SwApplicationInterface::GetPanelList().AddPanel(this);
}

SwPanel::SwPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxPanel(parent, id, pos, size, style, name)
{
    m_manager = NULL;
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SwApplicationInterface::GetPanelList().AddPanel(this);

    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwPanel::OnResize);
}

SwPanel::~SwPanel()
{
    SwApplicationInterface::GetPanelList().DeletePanel(SwApplicationInterface::GetPanelList().SwFindPanel(this));
}

bool SwPanel::OnNew()
{
    return false;
}

bool SwPanel::OnOpen()
{
    return false;
}

bool SwPanel::OnRecentFiles()
{
    return false;
}
bool SwPanel::OnSave()
{
    return false;
}

bool SwPanel::OnSaveAs()
{
    return false;
}

bool SwPanel::OnClose()
{
    return false;
}

bool SwPanel::OnCloseAll()
{
    return false;
}

bool SwPanel::OnPrint()
{
    return false;
}

bool SwPanel::OnPrintPreview()
{
    return false;
}

bool SwPanel::OnFile1()
{
    return false;
}

bool SwPanel::OnFile2()
{
    return false;
}

bool SwPanel::OnFile3()
{
    return false;
}

bool SwPanel::OnFile4()
{
    return false;
}

bool SwPanel::OnFile5()
{
    return false;
}

bool SwPanel::OnFile6()
{
    return false;
}

bool SwPanel::OnFile7()
{
    return false;
}

bool SwPanel::OnFile8()
{
    return false;
}

bool SwPanel::OnFile9()
{
    return false;
}

bool SwPanel::OnFile10()
{
    return false;
}

bool SwPanel::OnBookMarkPage()
{
    return false;
}

bool SwPanel::OnFind(const wchar_t * text, bool casesensitive, bool wholewordonly)
{
    return false;
}

bool SwPanel::OnFindReset()
{
    return false;
}

bool SwPanel::OnFindSetCaseSensitive(bool caseSensitive)
{
    return false;
}

bool SwPanel::OnFindSetWholeWordOnly(bool wholewordOnly)
{
    return false;
}

bool SwPanel::OnFindNext()
{
    return false;
}

bool SwPanel::OnReplace()
{
    return false;
}

bool SwPanel::OnReplaceAll()
{
    return false;
}

bool SwPanel::OnClear()
{
    return false;
}

bool SwPanel::OnCut()
{
    return false;
}

bool SwPanel::OnCopy()
{
    return false;
}

bool SwPanel::OnPaste()
{
    return false;
}

bool SwPanel::OnUndo()
{
    return false;
}

bool SwPanel::OnRedo()
{
    return false;
}

bool SwPanel::OnSelectAll()
{
    return false;
}

bool SwPanel::OnProperties()
{
    return false;
}

bool SwPanel::OnLibraryView()
{
    return false;
}

bool SwPanel::OnContentsView()
{
    return false;
}

bool SwPanel::OnSearchView()
{
    return false;
}

bool SwPanel::OnFindView()
{
    return false;
}

bool SwPanel::OnBookmarksView()
{
    return false;
}

bool SwPanel::OnHistoryView()
{
    return false;
}

bool SwPanel::OnZoomIn()
{
    return false;
}

bool SwPanel::OnZoomOut()
{
    return false;
}

bool SwPanel::OnViewNormal()
{
    return false;
}

bool SwPanel::OnContentsUp()
{
    return false;
}

bool SwPanel::OnContentsDown()
{
    return false;
}

bool SwPanel::OnHistoryBack()
{
    return false;
}

bool SwPanel::OnHistoryForward()
{
    return false;
}

bool SwPanel::OnFont()
{
    return false;
}

bool SwPanel::OnBold()
{
    return false;
}

bool SwPanel::OnItalic()
{
    return false;
}

bool SwPanel::OnUnderline()
{
    return false;
}

bool SwPanel::OnStrikeThrough()
{
    return false;
}

bool SwPanel::OnSuperScript()
{
    return false;
}

bool SwPanel::OnSubScript()
{
    return false;
}

bool SwPanel::OnColor()
{
    return false;
}

bool SwPanel::OnBackgroundColor()
{
    return false;
}

bool SwPanel::OnStyle()
{
    return false;
}

bool SwPanel::OnMargins()
{
    return false;
}

bool SwPanel::OnIndentMore()
{
    return false;
}

bool SwPanel::OnIndentLess()
{
    return false;
}

bool SwPanel::OnAlignLeft()
{
    return false;
}

bool SwPanel::OnAlignCenter()
{
    return false;
}

bool SwPanel::OnAlignRight()
{
    return false;
}

bool SwPanel::OnSingleSpacing()
{
    return false;
}

bool SwPanel::OnDoubleSpacing()
{
    return false;
}

bool SwPanel::OnAlphaList()
{
    return false;
}

bool SwPanel::OnBulletedList()
{
    return false;
}

bool SwPanel::OnRomanList()
{
    return false;
}

bool SwPanel::OnDecimalList()
{
    return false;
}

bool SwPanel::OnInsertTable()
{
    return false;
}

bool SwPanel::OnInsertRow()
{
    return false;
}

bool SwPanel::OnDeleteRow()
{
    return false;
}

bool SwPanel::OnInsertColumn()
{
    return false;
}

bool SwPanel::OnDeleteColumn()
{
    return false;
}

bool SwPanel::OnInsertImage()
{
    return false;
}

bool SwPanel::OnInsertLink()
{
    return false;
}

bool SwPanel::OnInsertAnchor()
{
    return false;
}

bool SwPanel::OnInsertControl()
{
    return false;
}

bool SwPanel::OnInsertHorizontalRule()
{
    return false;
}

bool SwPanel::OnPlay()
{
    return false;
}

bool SwPanel::OnPause()
{
    return false;
}

bool SwPanel::OnStop()
{
    return false;
}

bool SwPanel::OnRewind()
{
    return false;
}

bool SwPanel::OnFastForward()
{
    return false;
}

bool SwPanel::OnPrevious()
{
    return false;
}

bool SwPanel::OnNext()
{
    return false;
}

bool SwPanel::OnPreferences()
{
    return false;
}

bool SwPanel::OnHelpContents()
{
    return false;
}

bool SwPanel::OnAbout()
{
    return false;
}

bool SwPanel::OnUpdateSoftware()
{
    return false;
}


// false - language, true - theme
void SwPanel::NotifyChildren(bool change)
{
    for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
    {
        NotifyChildren(*it, change);
    }
}

void SwPanel::NotifyChildren(wxWindow * window, bool change)
{
    if (window->IsKindOf(CLASSINFO(SwModuleTreeCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwModuleTreeCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwModuleTreeCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwThMLTreeCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwThMLTreeCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwThMLTreeCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwButton)))
    {
        if (!change)
            wxDynamicCast(window, SwButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwBitmapButton)))
    {
        if (!change)
            wxDynamicCast(window, SwBitmapButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwBitmapButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwCheckBox)))
    {
        if (!change)
            wxDynamicCast(window, SwCheckBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwCheckBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListBox)))
    {
        if (!change)
            wxDynamicCast(window, SwListBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwCheckListBox)))
    {
        if (!change)
            wxDynamicCast(window, SwCheckListBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwCheckListBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwChoice)))
    {
        if (!change)
            wxDynamicCast(window, SwChoice)->OnLanguageChange();
        else
            wxDynamicCast(window, SwChoice)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwDataViewListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwDataViewListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwDataViewListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListView)))
    {
        if (!change)
            wxDynamicCast(window, SwListView)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListView)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRadioButton)))
    {
        if (!change)
            wxDynamicCast(window, SwRadioButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRadioButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStaticText)))
    {
        if (!change)
            wxDynamicCast(window, SwStaticText)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStaticText)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwBitmapToggleButton)))
    {
        if (!change)
            wxDynamicCast(window, SwBitmapToggleButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwBitmapToggleButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStretchColumnListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwStretchColumnListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStretchColumnListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStretchColumnListView)))
    {
        if (!change)
            wxDynamicCast(window, SwStretchColumnListView)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStretchColumnListView)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwViewPanel)))
    {
        if (!change)
            wxDynamicCast(window, SwViewPanel)->OnLanguageChange();
        else
            wxDynamicCast(window, SwViewPanel)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwToolBook)))
    {
        if (!change)
            wxDynamicCast(window, SwToolBook)->OnLanguageChange();
        else
            wxDynamicCast(window, SwToolBook)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRichTextCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwRichTextCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRichTextCtrl)->OnThemeChange();
    }
    // Do nothing, these receive notification from SwApplicationInterface
    else if (window->IsKindOf(CLASSINFO(SwFrame)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwPanel)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwDialog)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwToolBar)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwMenuBar)))
    {
    }
    //
    else
    {
        for ( wxWindowList::iterator it = window->GetChildren().begin(); it != window->GetChildren().end(); ++it )
        {
            NotifyChildren(*it, change);
        }
    }
}

void SwPanel::OnLanguageChangeBase()
{
    OnLanguageChange();
    NotifyChildren(false);
}

void SwPanel::OnThemeChangeBase()
{
    OnThemeChange();
    NotifyChildren(true);
}

void SwPanel::OnFontSizeChange(const wxFont & font)
{
    SetFont(font);
}

void SwPanel::UpdateGui(SwToolBar * toolbar, SwMenuBar * menubar)
{
}

void SwPanel::OnResize(wxSizeEvent& event)
{
    event.Skip();
}

bool SwPanel::OnHasFocus()
{
    if (HasFocus())
        return true;

    for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
    {
        if ((*it)->HasFocus())
            return true;

        if (HasChildWithFocus(*it))
            return true;
    }

    return false;
}

bool SwPanel::HasChildWithFocus(wxWindow * window)
{
    for ( wxWindowList::iterator it = window->GetChildren().begin(); it != window->GetChildren().end(); ++it )
    {
        if ((*it)->HasFocus())
            return true;

        if (HasChildWithFocus(*it))
            return true;
    }

    return false;
}

bool SwPanel::OnHasSelection()
{
    return false;
}

bool SwPanel::OnClosePanel()
{
    return true;
}

bool SwPanel::OnCanDoNew()
{
    return false;
}

bool SwPanel::OnCanDoOpen()
{
    return false;
}

bool SwPanel::OnCanDoSave()
{
    return false;
}

bool SwPanel::OnCanDoSaveAs()
{
    return false;
}

bool SwPanel::OnCanDoClose()
{
    return false;
}

bool SwPanel::OnCanDoCloseAll()
{
    return false;
}

bool SwPanel::OnCanDoPrint()
{
    return false;
}

bool SwPanel::OnCanDoPrintPreview()
{
    return false;
}

bool SwPanel::OnCanDoBookMarkPage()
{
    return false;
}

bool SwPanel::OnCanDoFind()
{
    return false;
}

bool SwPanel::OnCanDoFindNext()
{
    return false;
}

bool SwPanel::OnCanDoReplace()
{
    return false;
}


bool SwPanel::OnCanDoClear()
{
    return false;
}

bool SwPanel::OnCanDoCut()
{
    return false;
}

bool SwPanel::OnCanDoCopy()
{
    return false;
}

bool SwPanel::OnCanDoPaste()
{
    return false;
}

bool SwPanel::OnCanDoUndo()
{
    return false;
}

bool SwPanel::OnCanDoRedo()
{
    return false;
}

bool SwPanel::OnCanDoSelectAll()
{
    return false;
}

bool SwPanel::OnCanDoProperties()
{
    return false;
}

bool SwPanel::HasLibraryView()
{
    return false;
}

bool SwPanel::HasContentsView()
{
    return false;
}

bool SwPanel::HasBookmarksView()
{
    return false;
}

bool SwPanel::HasFindView()
{
    return false;
}

bool SwPanel::HasSearchView()
{
    return false;
}

bool SwPanel::HasHistoryView()
{
    return false;
}

bool SwPanel::OnCanDoZoomIn()
{
    return false;
}

bool SwPanel::OnCanDoZoomOut()
{
    return false;
}

bool SwPanel::OnCanDoViewNormal()
{
    return false;
}

bool SwPanel::OnCanDoUpInContents()
{
    return false;
}

bool SwPanel::OnCanDoDownInContents()
{
    return false;
}

bool SwPanel::OnCanDoBackInHistory()
{
    return false;
}

bool SwPanel::OnCanDoForwardInHistory()
{
    return false;
}

bool SwPanel::OnCanDoFont()
{
    return false;
}

bool SwPanel::OnCanDoBold()
{
    return false;
}

bool SwPanel::IsSelectionBold()
{
    return false;
}

bool SwPanel::OnCanDoItalic()
{
    return false;
}

bool SwPanel::IsSelectionItalic()
{
    return false;
}

bool SwPanel::OnCanDoUnderline()
{
    return false;
}

bool SwPanel::IsSelectionUnderline()
{
    return false;
}

bool SwPanel::OnCanDoStrikeThrough()
{
    return false;
}

bool SwPanel::IsSelectionStrikeThrough()
{
    return false;
}

bool SwPanel::OnCanDoSuperScript()
{
    return false;
}

bool SwPanel::IsSelectionSuperScript()
{
    return false;
}

bool SwPanel::OnCanDoSubScript()
{
    return false;
}

bool SwPanel::IsSelectionSubScript()
{
    return false;
}

bool SwPanel::OnCanDoColor()
{
    return false;
}

bool SwPanel::OnCanDoBackGroundColor()
{
    return false;
}

bool SwPanel::OnCanDoStyle()
{
    return false;
}

bool SwPanel::OnCanDoMargins()
{
    return false;
}

bool SwPanel::OnCanDoIndentMore()
{
    return false;
}

bool SwPanel::OnCanDoIndentLess()
{
    return false;
}

bool SwPanel::OnCanDoAlignLeft()
{
    return false;
}

bool SwPanel::IsSelectionAlignLeft()
{
    return false;
}

bool SwPanel::OnCanDoAlignCenter()
{
    return false;
}

bool SwPanel::IsSelectionAlignCenter()
{
    return false;
}

bool SwPanel::OnCanDoAlignRight()
{
    return false;
}

bool SwPanel::IsSelectionAlignRight()
{
    return false;
}

bool SwPanel::OnCanDoSingleSpacing()
{
    return false;
}

bool SwPanel::IsSelectionSingleSpacing()
{
    return false;
}

bool SwPanel::OnCanDoDoubleSpacing()
{
    return false;
}

bool SwPanel::IsSelectionDoubleSpacing()
{
    return false;
}

bool SwPanel::OnCanDoAlphaList()
{
    return false;
}

bool SwPanel::IsSelectionAlphaList()
{
    return false;
}

bool SwPanel::OnCanDoBulletedList()
{
    return false;
}

bool SwPanel::IsSelectionBulletedList()
{
    return false;
}

bool SwPanel::OnCanDoRomanNumeralsList()
{
    return false;
}

bool SwPanel::IsSelectionRomanNumeralsList()
{
    return false;
}

bool SwPanel::OnCanDoDecimalList()
{
    return false;
}

bool SwPanel::IsSelectionDecimalList()
{
    return false;
}

bool SwPanel::OnCanDoInsertTable()
{
    return false;
}

bool SwPanel::OnCanDoInsertRow()
{
    return false;
}

bool SwPanel::OnCanDoDeleteRow()
{
    return false;
}

bool SwPanel::OnCanDoInsertColumn()
{
    return false;
}

bool SwPanel::OnCanDoDeleteColumn()
{
    return false;
}

bool SwPanel::OnCanDoInsertImage()
{
    return false;
}

bool SwPanel::OnCanDoInsertLink()
{
    return false;
}

bool SwPanel::OnCanDoInsertAnchor()
{
    return false;
}

bool SwPanel::OnCanDoInsertControl()
{
    return false;
}

bool SwPanel::OnCanDoInsertHorizontalRule()
{
    return false;
}

bool SwPanel::OnCanDoPlay()
{
    return false;
}

bool SwPanel::OnCanDoPause()
{
    return false;
}

bool SwPanel::OnCanDoStop()
{
    return false;
}

bool SwPanel::OnCanDoRewind()
{
    return false;
}

bool SwPanel::OnCanDoFastForward()
{
    return false;
}

bool SwPanel::OnCanDoPrevious()
{
    return false;
}

bool SwPanel::OnCanDoNext()
{
    return false;
}

bool SwPanel::GetBookMarkData(SwString & title, SwBookMarkClientData & data)
{
    return false;
}

bool SwPanel::ActivateBookMark(SwBookMarkClientData & data, const char * ctrlid)
{
    return false;
}

bool SwPanel::ActivateSearchItem(const char * path, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    return false;
}

bool SwPanel::ActivateSearchItem(swUI16 managerId, const wchar_t * text, swUI8 searchType, bool wordonly, bool casesensitive)
{
    return false;
}

bool SwPanel::WriteGuiData(FILE * file)
{
    return false;
}

SwPanelList::SwPanelList()
{
    m_panelArray = NULL;
    m_panelarrayPos = 0;
    m_panelobjectsAllocated = 0;
}

SwPanelList::~SwPanelList()
{
    ReleasePanelArray();
}

wxUint32 SwPanelList::AssignPanelObject()
{
    if (m_panelarrayPos >= m_panelobjectsAllocated && !IncreasePanelArray())
        return NODE_ID_INVALID;

    m_panelArray[m_panelarrayPos] = NULL;
    m_panelarrayPos ++;

    return m_panelarrayPos - 1;
}

bool SwPanelList::IncreasePanelArray()
{
    if (m_panelobjectsAllocated >= NODE_ID_INVALID - 17)
        return false;

    SwPanel ** p = (SwPanel **) realloc((void *) m_panelArray, (m_panelobjectsAllocated + 16) * sizeof(SwPanel));

    if (p)
    {
        m_panelobjectsAllocated += 16;
        m_panelArray = p;

        return true;
    }

    return false;
}

void SwPanelList::ReleasePanelArray()
{
    if (m_panelArray)
    {
        free(m_panelArray);
    }

    m_panelArray = NULL;
    m_panelobjectsAllocated = 0;
    m_panelarrayPos = 0;
}

wxUint32 SwPanelList::AddPanel(SwPanel * panel)
{

    wxUint32 position = AssignPanelObject();

    if (position == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    m_panelArray[position] = panel;

    return position;
}

void SwPanelList::DeletePanel(wxUint32 position)
{
    wxUint32 pos = position;
    if (position >= m_panelarrayPos)
        return;

    m_panelArray[position] = NULL;

    if (m_panelarrayPos >= 1)
    {
        pos ++;

        while (pos < m_panelarrayPos)
        {
            m_panelArray[pos -1] = m_panelArray[pos];
            pos ++;
        }
    }

    m_panelarrayPos --;
}

void SwPanelList::Reset()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        m_panelArray[pos] = NULL;
        pos ++;
    }

    m_panelarrayPos = 0;
}

wxUint32 SwPanelList::SwFindPanel(SwPanel * panel)
{
    wxUint32 pos = 0;

    while (pos < m_panelarrayPos)
    {
        if (m_panelArray[pos] == panel)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

wxUint32 SwPanelList::FindFocusPanel()
{
    wxUint32 pos = 0;

    while (pos < m_panelarrayPos)
    {
        if (m_panelArray[pos]->HasFocus())
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}


SwPanel * SwPanelList::GetPanel(wxUint32 position)
{
    if (position >= m_panelarrayPos)
        return NULL;

    return m_panelArray[position];
}

void SwPanelList::SetPanel(wxUint32 position, SwPanel * panel)
{
    if (position >= m_panelarrayPos)
        return;

    m_panelArray[position] = panel;
}

void SwPanelList::OnLanguageChangeBase()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnLanguageChangeBase();

        pos ++;
    }
}

void SwPanelList::OnThemeChangeBase()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnThemeChangeBase();

        pos ++;
    }
}

void SwPanelList::OnFontSizeChange()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnFontSizeChange(thisFont);

        pos ++;
    }
}

void SwPanelList::OnModuleManagerReset()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnModuleManagerReset();

        pos ++;
    }
}

void SwPanelList::OnThMLFileManagerReset()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnThMLFileManagerReset();

        pos ++;
    }
}

void SwPanelList::OnModuleManagerLoaded()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnModuleManagerLoaded();

        pos ++;
    }
}

void SwPanelList::OnThMLFileManagerLoaded()
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnThMLFileManagerLoaded();

        pos ++;
    }
}

void SwPanelList::OnModuleAdded(swUI16 mid)
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnModuleAdded(mid);

        pos ++;
    }
}

void SwPanelList::OnModuleDeleted(swUI16 mid)
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnModuleDeleted(mid);

        pos ++;
    }
}

void SwPanelList::OnThMLFileAdded(swUI16 mid)
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnThMLFileAdded(mid);

        pos ++;
    }
}

void SwPanelList::OnThMLFileDeleted(swUI16 mid)
{
    wxUint32 pos = 0;

    if (!m_panelArray)
        return;

    while(pos < m_panelarrayPos)
    {
        if (m_panelArray[pos])
            m_panelArray[pos]->OnThMLFileDeleted(mid);

        pos ++;
    }
}

SwStretchPanel::SwStretchPanel()
{
}

SwStretchPanel::SwStretchPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchPanel::OnResize);
}

SwStretchPanel::~SwStretchPanel()
{
}

void SwStretchPanel::OnResize(wxSizeEvent& event)
{
    if (!GetSizer() || !GetSizer()->GetItemCount())
        return;

    int items = GetSizer()->GetItemCount();
    int height = GetSizer()->GetItem(items - 1)->GetRect().GetBottom();

    wxSize s = event.GetSize();
    s.SetHeight(height + 5);
    SetMinSize(s);
    event.Skip();
}
