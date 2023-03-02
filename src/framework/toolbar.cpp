///////////////////////////////////////////////////////////////////
// Name:        toolbar.cpp
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/toolbar.h"
#include "../../include/appi/appifa.h"

SwToolBar::SwToolBar()
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    m_frame = NULL;
    m_lastgroup = SW_MENUID_UNKNOWN;
}


SwToolBar::SwToolBar(wxWindow *parent, wxWindowID id, const wxPoint &position, const wxSize &size, long style, bool primary, SwFrame * frame)
#ifdef __USE_WXAUI_TOOLBAR__
    :wxAuiToolBar(parent, id, position, size, style | wxAUI_TB_OVERFLOW)
#else
    :wxToolBar(parent, id, position, size, style)
#endif
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    SetFrameWindow(frame);
#ifdef __linux__
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwToolBar::OnResize);
#endif
}

int SwToolBar::GetItemCount()
{
#ifdef __USE_WXAUI_TOOLBAR__
    return GetToolCount();
#else
    return GetToolsCount();
#endif
}

SwToolBarItem * SwToolBar::Find(int id)
{
#ifdef __USE_WXAUI_TOOLBAR__
    return FindTool(id);
#else
    return FindById(id);
#endif
}

void SwToolBar::SetFrameWindow(SwFrame * frame)
{
    m_lastgroup = SW_MENUID_UNKNOWN;
    m_frame = frame;

    if (m_frame)
        m_frame->SetSowerToolBar(this);

    if (!frame)
        return;

    m_eventHandlers[SW_GUIID_UNKNOWN] = &SwFrame::OnUnknown;

    /* Group */
    m_eventHandlers[SW_GUIID_NEW] = &SwFrame::OnNew;
    m_eventHandlers[SW_GUIID_OPEN] = &SwFrame::OnOpen;
    m_eventHandlers[SW_GUIID_CLOSE] = &SwFrame::OnClose;
    m_eventHandlers[SW_GUIID_CLOSEALL] = &SwFrame::OnCloseAll;
    m_eventHandlers[SW_GUIID_SAVE] = &SwFrame::OnSave;
    m_eventHandlers[SW_GUIID_SAVEAS] = &SwFrame::OnSaveAs;
    m_eventHandlers[SW_GUIID_PRINT] = &SwFrame::OnPrint;
    m_eventHandlers[SW_GUIID_PRINTPREVIEW] = &SwFrame::OnPrintPreview;
    m_eventHandlers[SW_GUIID_QUIT] = &SwFrame::OnQuit;

    /* GROUP */
    m_eventHandlers[SW_GUIID_FILE1] = &SwFrame::OnFile1;
    m_eventHandlers[SW_GUIID_FILE2] = &SwFrame::OnFile2;
    m_eventHandlers[SW_GUIID_FILE3] = &SwFrame::OnFile3;
    m_eventHandlers[SW_GUIID_FILE4] = &SwFrame::OnFile4;
    m_eventHandlers[SW_GUIID_FILE5] = &SwFrame::OnFile5;
    m_eventHandlers[SW_GUIID_FILE6] = &SwFrame::OnFile6;
    m_eventHandlers[SW_GUIID_FILE7] = &SwFrame::OnFile7;
    m_eventHandlers[SW_GUIID_FILE8] = &SwFrame::OnFile8;
    m_eventHandlers[SW_GUIID_FILE9] = &SwFrame::OnFile9;
    m_eventHandlers[SW_GUIID_FILE10] = &SwFrame::OnFile10;


    /* Group */
    m_eventHandlers[SW_GUIID_BOOKMARKPAGE] = &SwFrame::OnBookmark;
    m_eventHandlers[SW_GUIID_FIND] = &SwFrame::OnFind;
    m_eventHandlers[SW_GUIID_FINDNEXT] = &SwFrame::OnFindNext;
    m_eventHandlers[SW_GUIID_REPLACE] = &SwFrame::OnReplace;
    m_eventHandlers[SW_GUIID_CLEAR] = &SwFrame::OnClear;
    m_eventHandlers[SW_GUIID_CUT] = &SwFrame::OnCut;
    m_eventHandlers[SW_GUIID_COPY] = &SwFrame::OnCopy;
    m_eventHandlers[SW_GUIID_PASTE] = &SwFrame::OnPaste;
    m_eventHandlers[SW_GUIID_UNDO] = &SwFrame::OnUndo;
    m_eventHandlers[SW_GUIID_REDO] = &SwFrame::OnRedo;
    m_eventHandlers[SW_GUIID_SELECTALL] = &SwFrame::OnSelectAll;
    m_eventHandlers[SW_GUIID_GEO] = &SwFrame::OnGeo;
    m_eventHandlers[SW_GUIID_MAPS] = &SwFrame::OnMaps;
    m_eventHandlers[SW_GUIID_AREAS] = &SwFrame::OnAreas;
    m_eventHandlers[SW_GUIID_PROPERTIES] = &SwFrame::OnProperties;

    /* Group */
    m_eventHandlers[SW_GUIID_LIBRARYVIEW] = &SwFrame::OnLibraryView;
    m_eventHandlers[SW_GUIID_CONTENTSVIEW] = &SwFrame::OnContentsView;
    m_eventHandlers[SW_GUIID_SEARCHVIEW] = &SwFrame::OnSearchView;
    m_eventHandlers[SW_GUIID_FINDVIEW] = &SwFrame::OnFindView;
    m_eventHandlers[SW_GUIID_BOOKMARKSVIEW] = &SwFrame::OnBookmarksView;
    m_eventHandlers[SW_GUIID_HISTORYVIEW] = &SwFrame::OnHistoryView;
    m_eventHandlers[SW_GUIID_ZOOMIN] = &SwFrame::OnZoomIn;
    m_eventHandlers[SW_GUIID_ZOOMOUT] = &SwFrame::OnZoomOut;
    m_eventHandlers[SW_GUIID_VIEWNORMAL] = &SwFrame::OnViewNormal;

    /* Group */
    m_eventHandlers[SW_GUIID_CONTENTSUP] = &SwFrame::OnContentsUp;
    m_eventHandlers[SW_GUIID_CONTENTSDOWN] = &SwFrame::OnContentsDown;
    m_eventHandlers[SW_GUIID_BACKINHISTORY] = &SwFrame::OnHistoryBack;
    m_eventHandlers[SW_GUIID_FORWARDINHISTORY] = &SwFrame::OnHistoryForward;

    /* Group */
    m_eventHandlers[SW_GUIID_FONT] = &SwFrame::OnFont;
    m_eventHandlers[SW_GUIID_BOLD] = &SwFrame::OnBold;
    m_eventHandlers[SW_GUIID_ITALIC] = &SwFrame::OnItalic;
    m_eventHandlers[SW_GUIID_UNDERLINE] = &SwFrame::OnUnderline;
    m_eventHandlers[SW_GUIID_STRIKETHROUGH] = &SwFrame::OnStrikeThrough;
    m_eventHandlers[SW_GUIID_SUPERSCRIPT] = &SwFrame::OnSuperScript;
    m_eventHandlers[SW_GUIID_SUBSCRIPT] = &SwFrame::OnSubScript;
    m_eventHandlers[SW_GUIID_COLOR] = &SwFrame::OnColor;
    m_eventHandlers[SW_GUIID_BACKGROUNDCOLOR] = &SwFrame::OnBackgroundColor;
    m_eventHandlers[SW_GUIID_STYLE] = &SwFrame::OnStyle;

    /* Group */
    m_eventHandlers[SW_GUIID_MARGINS] = &SwFrame::OnMargins;
    m_eventHandlers[SW_GUIID_INDENTMORE] = &SwFrame::OnIndentMore;
    m_eventHandlers[SW_GUIID_INDENTLESS] = &SwFrame::OnIndentLess;
    m_eventHandlers[SW_GUIID_ALIGNLEFT] = &SwFrame::OnAlignLeft;
    m_eventHandlers[SW_GUIID_ALIGNCENTER] = &SwFrame::OnAlignCenter;
    m_eventHandlers[SW_GUIID_ALIGNRIGHT] = &SwFrame::OnAlignRight;
    m_eventHandlers[SW_GUIID_SINGLESPACING] = &SwFrame::OnSingleSpacing;
    m_eventHandlers[SW_GUIID_DOUBLESPACING] = &SwFrame::OnDoubleSpacing;

    /* Group */
    m_eventHandlers[SW_GUIID_ALPHABETICLIST] = &SwFrame::OnAlphaList;
    m_eventHandlers[SW_GUIID_BULLETEDLIST] = &SwFrame::OnBulletedList;
    m_eventHandlers[SW_GUIID_ROMANNUMERALSLIST] = &SwFrame::OnRomanList;
    m_eventHandlers[SW_GUIID_DECIMALLIST] = &SwFrame::OnDecimalList;

    /* Group */
    m_eventHandlers[SW_GUIID_INSERTTABLE] = &SwFrame::OnInsertTable;
    m_eventHandlers[SW_GUIID_INSERTROW] = &SwFrame::OnInsertRow;
    m_eventHandlers[SW_GUIID_INSERTCOLUMN] = &SwFrame::OnInsertColumn;
    m_eventHandlers[SW_GUIID_DELETEROW] = &SwFrame::OnDeleteRow;
    m_eventHandlers[SW_GUIID_DELETECOLUMN] = &SwFrame::OnDeleteColumn;

    /* Group */
    m_eventHandlers[SW_GUIID_INSERTIMAGE] = &SwFrame::OnInsertImage;
    m_eventHandlers[SW_GUIID_INSERTLINK] = &SwFrame::OnInsertLink;
    m_eventHandlers[SW_GUIID_INSERTANCHOR] = &SwFrame::OnInsertAnchor;
    m_eventHandlers[SW_GUIID_INSERTCONTROL] = &SwFrame::OnInsertControl;
    m_eventHandlers[SW_GUIID_INSERTHORIZONTALRULE] = &SwFrame::OnInsertHorizontalRule;

    /* Group */
    m_eventHandlers[SW_GUIID_PREFERENCES] = &SwFrame::OnPreferences;
    m_eventHandlers[SW_GUIID_SELECTINTERFACE] = &SwFrame::OnSelectInterface;
    m_eventHandlers[SW_GUIID_SELECTLANGUAGE] = &SwFrame::OnSelectLanguage;
    m_eventHandlers[SW_GUIID_SELECTTHEME] = &SwFrame::OnSelectTheme;

    /* Group */
    m_eventHandlers[SW_GUIID_HELPCONTENTS] = &SwFrame::OnHelpContents;
    m_eventHandlers[SW_GUIID_ABOUT] = &SwFrame::OnAbout;
    m_eventHandlers[SW_GUIID_UPDATESOFTWARE] = &SwFrame::OnUpdateSoftware;

    /* Players */
    m_eventHandlers[SW_GUIID_PLAY] = &SwFrame::OnPlay;
    m_eventHandlers[SW_GUIID_PAUSE] = &SwFrame::OnPause;
    m_eventHandlers[SW_GUIID_STOP] = &SwFrame::OnStop;
    m_eventHandlers[SW_GUIID_REWIND] = &SwFrame::OnRewind;
    m_eventHandlers[SW_GUIID_FASTFORWARD] = &SwFrame::OnFastForward;
    m_eventHandlers[SW_GUIID_PREVIOUS] = &SwFrame::OnPrevious;
    m_eventHandlers[SW_GUIID_NEXT] = &SwFrame::OnNext;
}

void SwToolBar::OnResize(wxSizeEvent& event)
{
    int h, w, x, y;
    GetSize(&w, &h);
    GetPosition(&x, &y);
    SetSize(wxSize(GetParent()->GetSize().GetWidth() - (x * 2), h));
    event.Skip();
}

void SwToolBar::OnEvent(wxCommandEvent & event)
{
    if (!m_frame)
        return;

    swUI8 swid = SwGuiData::FindItemWxId(event.GetId());

    if (swid == NODE_ID_INVALID_8)
    {
        (m_frame->*m_eventHandlers[SW_GUIID_UNKNOWN])(event);
    }
    else
    {
        (m_frame->*m_eventHandlers[swid])(event);
    }
}

SwToolBarItem * SwToolBar::AddStockItem(swUI8 swid, bool enable, bool addSeparators)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return NULL;

    SwToolBarItem * item = NULL;

    swUI8 sep = SwGuiData::GetDataForItemSwId(swid)->separator;

    if (addSeparators && (sep == SEP_BEFORE || (GetItemCount() && m_lastgroup != SwGuiData::GetDataForItemSwId(swid)->sw_guiid_parent)))
        AddSeparator();

    if (strlen(SwGuiData::GetDataForItemSwId(swid)->sid_image))
    {
        item = AddTool(SwGuiData::GetDataForItemSwId(swid)->wx_id, wxEmptyString, SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image), SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image).ConvertToDisabled(100), SwGuiData::GetDataForItemSwId(swid)->itemtype, SwApplicationInterface::GetControlString(SwGuiData::GetDataForItemSwId(swid)->sid_label, SwGuiData::GetDataForItemSwId(swid)->label), wxEmptyString, NULL);
    }
    else
    {
        item = AddTool(SwGuiData::GetDataForItemSwId(swid)->wx_id, wxEmptyString, SwApplicationInterface::GetMissingImage(), SwApplicationInterface::GetMissingImage().ConvertToDisabled(100), SwGuiData::GetDataForItemSwId(swid)->itemtype, SwApplicationInterface::GetControlString(SwGuiData::GetDataForItemSwId(swid)->sid_label, SwGuiData::GetDataForItemSwId(swid)->label), wxEmptyString, NULL);
    }

    if (addSeparators && sep == SEP_AFTER)
        AddSeparator();

    EnableItem(swid, enable);

    m_lastgroup  = SwGuiData::GetDataForItemSwId(swid)->sw_guiid_parent;

    Connect(SwGuiData::GetDataForItemSwId(swid)->wx_id, wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&SwToolBar::OnEvent);

    return item;
}

void SwToolBar::EnableItem(swUI8 swid, bool enable)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return;

    EnableTool(SwGuiData::GetDataForItemSwId(swid)->wx_id, enable);
    Refresh();
}

bool SwToolBar::IsItemEnabled(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return false;

    return GetToolEnabled(SwGuiData::GetDataForItemSwId(swid)->wx_id);
}

void SwToolBar::CheckItem(swUI8 swid, bool check)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return;

    ToggleTool(SwGuiData::GetDataForItemSwId(swid)->wx_id, check);
    Refresh();
}

bool SwToolBar::IsItemChecked(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return false;

#ifdef __USE_WXAUI_TOOLBAR__
    return GetToolToggled(SwGuiData::GetDataForItemSwId(swid)->wx_id);
#else
    return GetToolState(SwGuiData::GetDataForItemSwId(swid)->wx_id);
#endif
}

const wchar_t * SwToolBar::GetItemLabel(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return L"";

    return GetToolShortHelp(SwGuiData::GetDataForItemSwId(swid)->wx_id).wchar_str();
}

void SwToolBar::SetCustomToolBitmap(int wxid, const char * strid)
{
    if (!strid)
        return;

#ifdef __USE_WXAUI_TOOLBAR__
    SetToolBitmap(wxid, SwApplicationInterface::GetImage(strid));
#else
#if wxCHECK_VERSION(3, 1, 0)
    SetToolNormalBitmap(wxid, wxBitmapBundle(SwApplicationInterface::GetImage(strid)));
#else
    SetToolNormalBitmap(wxid, SwApplicationInterface::GetImage(strid));
#endif
#endif
}

void SwToolBar::SetCustomToolLabel(int wxid, const char * strid, const wchar_t * deflabel)
{
    if (!strid || !deflabel)
        return;

#ifdef __USE_WXAUI_TOOLBAR__
    SetToolLabel(wxid, SwApplicationInterface::GetControlString(strid, deflabel));
#endif
    SetToolShortHelp(wxid, SwApplicationInterface::GetControlString(strid, deflabel));
}

void SwToolBar::OnLanguageChange()
{
    SwToolBarItem * item;

    for (swUI8 swid = 0; swid < N_SW_GUIITEM_IDS; swid ++)
    {
        item = Find(SwGuiData::GetDataForItemSwId(swid)->wx_id);

        if (item)
            item->SetShortHelp(SwApplicationInterface::GetControlString(SwGuiData::GetDataForItemSwId(swid)->sid_label, SwGuiData::GetDataForItemSwId(swid)->label));
    }
}

void SwToolBar::OnThemeChange()
{
    SwToolBarItem * item;

    for (swUI8 swid = 0; swid < N_SW_GUIITEM_IDS; swid ++)
    {
        item = Find(SwGuiData::GetDataForItemSwId(swid)->wx_id);

        if (item)
        {
            if (strlen(SwGuiData::GetDataForItemSwId(swid)->sid_image))
            {
#ifdef __USE_WXAUI_TOOLBAR__
                item->SetBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image));
                item->SetDisabledBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image).ConvertToDisabled(100));
#else
#if wxCHECK_VERSION(3, 1, 0)
                item->SetNormalBitmap(wxBitmapBundle(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image)));
                item->SetDisabledBitmap(wxBitmapBundle(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image).ConvertToDisabled(100)));
#else
                item->SetNormalBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image));
                item->SetDisabledBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image).ConvertToDisabled(100));
#endif
#endif
            }
            else
            {
#ifdef __USE_WXAUI_TOOLBAR__
                item->SetBitmap(SwApplicationInterface::GetMissingImage());
                item->SetDisabledBitmap(SwApplicationInterface::GetMissingImage().ConvertToDisabled());
#else
#if wxCHECK_VERSION(3, 1, 0)
                item->SetNormalBitmap(wxBitmapBundle(SwApplicationInterface::GetMissingImage()));
                item->SetDisabledBitmap(wxBitmapBundle(SwApplicationInterface::GetMissingImage().ConvertToDisabled()));
#else
                item->SetNormalBitmap(SwApplicationInterface::GetMissingImage());
                item->SetDisabledBitmap(SwApplicationInterface::GetMissingImage().ConvertToDisabled());
#endif
#endif
            }
        }
    }
}

void SwToolBar::OnFontSizeChange(wxFont & font)
{
    SetFont(font);
}


void SwToolBar::UpdateGui()
{
    if (!m_frame)
        return;

    SwToolBarItem * item;
    bool canDo;
    int buttonState;

    for (swUI8 i = 0; i < N_SW_GUIITEM_IDS; i ++)
    {
        item = Find(SwGuiData::GetDataForElement(i)->wx_id);

        if (!item)
            continue;

        switch (SwGuiData::GetDataForElement(i)->sw_guiid)
        {
        /* Group - FILE */
        case SW_GUIID_NEW:
            canDo = m_frame->OnCanDoNew();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_OPEN:
            canDo = m_frame->OnCanDoOpen();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_SAVE:
            canDo = m_frame->OnCanDoSave();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_SAVEAS:
            canDo = m_frame->OnCanDoSaveAs();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_CLOSE:
            canDo = m_frame->OnCanDoClose();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_CLOSEALL:
            canDo = m_frame->OnCanDoCloseAll();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_PRINT:
            canDo = m_frame->OnCanDoPrint();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_PRINTPREVIEW:
            canDo = m_frame->OnCanDoPrintPreview();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_QUIT:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;

        /* Group - EDIT */
        case SW_GUIID_BOOKMARKPAGE:
            canDo = m_frame->OnCanDoBookMarkPage();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_FIND:
            canDo = m_frame->OnCanDoFind();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_FINDNEXT:
            canDo = m_frame->OnCanDoFindNext();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_REPLACE:
            canDo = m_frame->OnCanDoReplace();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_CLEAR:
            canDo = m_frame->OnCanDoClear();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_CUT:
            canDo = m_frame->OnCanDoCut();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_COPY:
            canDo = m_frame->OnCanDoCopy();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_PASTE:
            canDo = m_frame->OnCanDoPaste();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_UNDO:
            canDo = m_frame->OnCanDoUndo();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_REDO:
            canDo = m_frame->OnCanDoRedo();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_SELECTALL:
            canDo = m_frame->OnCanDoSelectAll();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_GEO:
            canDo = m_frame->OnCanDoGeo();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_MAPS:
            canDo = m_frame->OnCanDoMaps();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_AREAS:
            canDo = m_frame->OnCanDoAreas();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_PROPERTIES:
            canDo = m_frame->OnCanDoProperties();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;

        /* Group - VIEW */
        case SW_GUIID_LIBRARYVIEW:
            canDo = m_frame->HasLibraryView();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_CONTENTSVIEW:
            canDo = m_frame->HasContentsView();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_SEARCHVIEW:
            canDo = m_frame->HasSearchView();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_FINDVIEW:
            canDo = m_frame->HasFindView();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_BOOKMARKSVIEW:
            canDo = m_frame->HasBookmarksView();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_HISTORYVIEW:
            canDo = m_frame->HasHistoryView();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_ZOOMIN:
            canDo = m_frame->OnCanDoZoomIn();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_ZOOMOUT:
            canDo = m_frame->OnCanDoZoomOut();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_VIEWNORMAL:
            canDo = m_frame->OnCanDoViewNormal();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;

        /* Group - NAVIGATION */
        case SW_GUIID_CONTENTSUP:
            canDo = m_frame->OnCanDoUpInContents();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_CONTENTSDOWN:
            canDo = m_frame->OnCanDoDownInContents();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_BACKINHISTORY:
            canDo = m_frame->OnCanDoBackInHistory();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_FORWARDINHISTORY:
            canDo = m_frame->OnCanDoForwardInHistory();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;

        /* Group - FORMAT */
        case SW_GUIID_FONT:
            canDo = m_frame->OnCanDoFont();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_BOLD:
            canDo = m_frame->OnCanDoBold();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionBold())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_ITALIC:
            canDo = m_frame->OnCanDoItalic();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionItalic())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_UNDERLINE:
            canDo = m_frame->OnCanDoUnderline();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionUnderline())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_STRIKETHROUGH:
            canDo = m_frame->OnCanDoStrikeThrough();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionStrikeThrough())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_SUPERSCRIPT:
            canDo = m_frame->OnCanDoSuperScript();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionSuperScript())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_SUBSCRIPT:
            canDo = m_frame->OnCanDoSubScript();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionSubScript())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_COLOR:
            canDo = m_frame->OnCanDoColor();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_BACKGROUNDCOLOR:
            canDo = m_frame->OnCanDoBackGroundColor();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_STYLE:
            canDo = m_frame->OnCanDoStyle();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;

        /* Group - PARAGRAPH */
        case SW_GUIID_MARGINS:
            canDo = m_frame->OnCanDoMargins();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INDENTMORE:
            canDo = m_frame->OnCanDoIndentMore();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INDENTLESS:
            canDo = m_frame->OnCanDoIndentLess();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_ALIGNLEFT:
            canDo = m_frame->OnCanDoAlignLeft();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionAlignLeft())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_ALIGNCENTER:
            canDo = m_frame->OnCanDoAlignCenter();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionAlignCenter())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_ALIGNRIGHT:
            canDo = m_frame->OnCanDoAlignRight();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionAlignRight())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_SINGLESPACING:
            canDo = m_frame->OnCanDoSingleSpacing();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionSingleSpacing())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_DOUBLESPACING:
            canDo = m_frame->OnCanDoDoubleSpacing();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionDoubleSpacing())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;

        /* Group - LIST */
        case SW_GUIID_ALPHABETICLIST:
            canDo = m_frame->OnCanDoAlphaList();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionAlphaList())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_BULLETEDLIST:
            canDo = m_frame->OnCanDoBulletedList();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionBulletedList())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_ROMANNUMERALSLIST:
            canDo = m_frame->OnCanDoRomanNumeralsList();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionRomanNumeralsList())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;
        case SW_GUIID_DECIMALLIST:
            canDo = m_frame->OnCanDoDecimalList();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            buttonState = wxAUI_BUTTON_STATE_NORMAL;
            if (canDo && m_frame->IsSelectionDecimalList())
                buttonState = wxAUI_BUTTON_STATE_CHECKED;
            ToggleTool(SwGuiData::GetDataForElement(i)->wx_id, buttonState);
            break;

        /* Group - TABLE */
        case SW_GUIID_INSERTTABLE:
            canDo = m_frame->OnCanDoInsertTable();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INSERTROW:
            canDo = m_frame->OnCanDoInsertRow();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_DELETEROW:
            canDo = m_frame->OnCanDoDeleteRow();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INSERTCOLUMN:
            canDo = m_frame->OnCanDoInsertColumn();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_DELETECOLUMN:
            canDo = m_frame->OnCanDoDeleteColumn();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;

        /* Group - Objects */
        case SW_GUIID_INSERTIMAGE:
            canDo = m_frame->OnCanDoInsertImage();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INSERTLINK:
            canDo = m_frame->OnCanDoInsertLink();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INSERTANCHOR:
            canDo = m_frame->OnCanDoInsertAnchor();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INSERTCONTROL:
            canDo = m_frame->OnCanDoInsertControl();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_INSERTHORIZONTALRULE:
            canDo = m_frame->OnCanDoInsertHorizontalRule();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;

        /* Group - SETTINGS */
        case SW_GUIID_PREFERENCES:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;
        case SW_GUIID_SELECTINTERFACE:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;
        case SW_GUIID_SELECTLANGUAGE:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;
        case SW_GUIID_SELECTTHEME:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;

        /* Group - HELP */
        case SW_GUIID_HELPCONTENTS:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;
        case SW_GUIID_ABOUT:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;
        case SW_GUIID_UPDATESOFTWARE:
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, true);
            break;

        /* Players */
        case SW_GUIID_PLAY:
            canDo = m_frame->OnCanDoPlay();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_PAUSE:
            canDo = m_frame->OnCanDoPause();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_STOP:
            canDo = m_frame->OnCanDoStop();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_REWIND:
            canDo = m_frame->OnCanDoRewind();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_FASTFORWARD:
            canDo = m_frame->OnCanDoFastForward();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_PREVIOUS:
            canDo = m_frame->OnCanDoPrevious();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        case SW_GUIID_NEXT:
            canDo = m_frame->OnCanDoNext();
            EnableTool(SwGuiData::GetDataForElement(i)->wx_id, canDo);
            break;
        }
    }

    Refresh();
}

SwBasicToolBar::SwBasicToolBar()
{
}

SwBasicToolBar::SwBasicToolBar(wxWindow *parent, wxWindowID id, const wxPoint &position, const wxSize &size, long style, bool primary, SwFrame * frame)
    :SwToolBar(parent, id, position, size, style, true, frame)
{
    AddStockItem(SW_GUIID_OPEN, true, true);
    AddStockItem(SW_GUIID_CLOSE, false, true);
    AddSeparator();
    AddStockItem(SW_GUIID_ABOUT, true, true);
    AddSpacer(10000);
    Realize();
}

void SwBasicToolBar::EnableItems(bool state)
{
    EnableItem(SW_GUIID_CLOSE, state);
}


SwUtilityToolBar::SwUtilityToolBar()
{
}

SwUtilityToolBar::SwUtilityToolBar(wxWindow *parent, wxWindowID id, const wxPoint &position, const wxSize &size, long style, bool primary, SwFrame * frame)
    :SwToolBar(parent, id, position, size, style, true, frame)
{
    AddStockItem(SW_GUIID_OPEN, true, true);
    AddStockItem(SW_GUIID_CLOSE, false, true);
    AddStockItem(SW_GUIID_PRINT, false, true);
    AddStockItem(SW_GUIID_CONTENTSDOWN, false, true);
    AddStockItem(SW_GUIID_CONTENTSUP, false, true);
    AddStockItem(SW_GUIID_ABOUT, true, true);
    AddSpacer(10000);
    Realize();
}

void SwUtilityToolBar::EnableItems(bool state)
{
    EnableItem(SW_GUIID_CLOSE, state);
    EnableItem(SW_GUIID_PRINT, state);
    EnableItem(SW_GUIID_CONTENTSDOWN, state);
    EnableItem(SW_GUIID_CONTENTSUP, state);
}
