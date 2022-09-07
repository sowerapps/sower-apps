///////////////////////////////////////////////////////////////////
// Name:        menubar.cpp
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/menubar.h"
#include "../../include/appi/appifa.h"

IMPLEMENT_DYNAMIC_CLASS(SwMenuItem, wxMenuItem)

SwMenuItem::SwMenuItem(wxMenu *parentMenu, int id, const wxString &text, const wxString &helpString, wxItemKind kind, wxMenu *subMenu)
    :wxMenuItem(parentMenu, id, text, helpString, kind, subMenu)
{
    m_plugIn = NULL;
    m_swid = SW_MENUID_UNKNOWN;
}

SwMenuItem::~SwMenuItem()
{
}

void SwMenuItem::SetId(swUI8 swid)
{
    m_swid = swid;
}

swUI8 SwMenuItem::GetId()
{
    return m_swid;
}

void SwMenuItem::SetPlugIn(SwPlugIn * plugIn)
{
    m_plugIn = plugIn;
}

SwPlugIn * SwMenuItem::GetAt()
{
    return m_plugIn;
}

const wchar_t * SwMenuItem::GetTranslatedLabel()
{
    if (m_swid >= N_SW_MENU_IDS)
        return L" ";

    return SwApplicationInterface::GetControlString(SwGuiData::GetDataForItemSwId(m_swid)->sid_label, SwGuiData::GetDataForItemSwId(m_swid)->label, false);
}

void SwMenuItem::OnLanguageChange()
{
    SetItemLabel(GetTranslatedLabel());
}

void SwMenuItem::OnThemeChange()
{
    SetBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(m_swid)->sid_image));
}

IMPLEMENT_DYNAMIC_CLASS(SwMenu, wxMenu)

SwMenu::SwMenu()
{
    m_swid = SW_MENUID_UNKNOWN;
    m_frame = NULL;
}

SwMenu::SwMenu(swUI8 swid)
{
    m_frame = NULL;

    if (swid >= N_SW_MENU_IDS)
        return;

    m_swid = swid;
}

SwMenu::SwMenu(SwFrame * frame)
{
    m_swid = SW_MENUID_UNKNOWN;
    m_frame  = frame;
}

SwMenu::~SwMenu()
{
}

void SwMenu::OnEvent(wxCommandEvent & event)
{
    event.Skip();
}

void SwMenu::SetFrameWindow(SwFrame * frame)
{
    m_frame = frame;
}

void SwMenu::SetId(swUI8 swid)
{
    if (swid >= N_SW_MENU_IDS)
        return;

    m_swid = swid;
}

swUI8 SwMenu::GetId()
{
    return m_swid;
}

const wchar_t * SwMenu::GetTranslatedLabel()
{
    if (m_swid >= N_SW_MENU_IDS)
        return L"";

    return SwApplicationInterface::GetControlString(SwGuiData::GetDataForMenuSwId(m_swid)->sid_label, SwGuiData::GetDataForMenuSwId(m_swid)->label, false);
}

SwMenuItem * SwMenu::AddStockItem(swUI8 swid, bool enabled, bool addSeparators)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return NULL;

    wxMenuItem * wxitem = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (wxitem && wxitem->IsKindOf(CLASSINFO(SwMenuItem)))
        return (SwMenuItem *) wxitem;

    SwMenuItem * item = new SwMenuItem(NULL, SwGuiData::GetDataForItemSwId(swid)->wx_id, SwApplicationInterface::GetControlString(SwGuiData::GetDataForItemSwId(swid)->sid_label, SwGuiData::GetDataForItemSwId(swid)->label, false), wxEmptyString, SwGuiData::GetDataForItemSwId(swid)->itemtype, NULL);
    item->SetId(swid);

    if (strlen(SwGuiData::GetDataForItemSwId(swid)->sid_image))
    {
        item->SetBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image));
    }

    swUI8 sep = SwGuiData::GetDataForItemSwId(swid)->separator;

    if (addSeparators && sep == SEP_BEFORE)
        AppendSeparator();

    Append(item);
    item->Enable(enabled);

    if (addSeparators && sep == SEP_AFTER)
        AppendSeparator();

    if (m_frame)
        Connect(SwGuiData::GetDataForItemSwId(swid)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SwMenu::OnEvent);

    return item;
}

void SwMenu::EnableItem(swUI8 swid, bool enable)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return;

    Enable(SwGuiData::GetDataForItemSwId(swid)->wx_id, enable);
}

bool SwMenu::IsItemEnabled(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return false;

    return IsEnabled(SwGuiData::GetDataForItemSwId(swid)->wx_id);
}

void SwMenu::CheckItem(swUI8 swid, bool check)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return;

    Check(SwGuiData::GetDataForItemSwId(swid)->wx_id, check);
}

bool SwMenu::IsItemChecked(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return false;

    return IsChecked(SwGuiData::GetDataForItemSwId(swid)->wx_id);
}

void SwMenu::OnLanguageChange()
{
    wxMenuItem * wxitem;
    SwMenuItem * sowermenuitem;

    for (size_t item = 0; item < GetMenuItemCount(); item ++)
    {
        wxitem = FindItemByPosition(item);

        if (!wxitem)
            continue;

        if (wxitem->IsKindOf(CLASSINFO(SwMenuItem)))
        {
            sowermenuitem = (SwMenuItem *) wxitem;
            sowermenuitem->OnLanguageChange();
        }
    }
}

void SwMenu::OnThemeChange()
{
    wxMenuItem * wxitem;
    SwMenuItem * sowermenuitem;

    for (size_t item = 0; item < GetMenuItemCount(); item ++)
    {
        wxitem = FindItemByPosition(item);

        if (!wxitem)
            continue;

        if (wxitem->IsKindOf(CLASSINFO(SwMenuItem)))
        {
            sowermenuitem = (SwMenuItem *) wxitem;
            sowermenuitem->OnThemeChange();
        }
    }
}

void SwMenu::UpdateGui()
{
    if (!m_frame)
        return;

    wxMenuItem * item;
    bool canDo;
    bool buttonState;

    for (swUI8 i = 0; i < N_SW_GUIITEM_IDS; i ++)
    {
        item = FindItem(SwGuiData::GetDataForElement(i)->wx_id);

        if (!item)
            continue;

        switch (SwGuiData::GetDataForElement(i)->sw_guiid)
        {
        /* Group - FILE */
        case SW_GUIID_NEW:
            canDo = m_frame->OnCanDoNew();
            item->Enable(canDo);
            break;
        case SW_GUIID_OPEN:
            canDo = m_frame->OnCanDoOpen();
            item->Enable(canDo);
            break;
        case SW_GUIID_SAVE:
            canDo = m_frame->OnCanDoSave();
            item->Enable(canDo);
            break;
        case SW_GUIID_SAVEAS:
            canDo = m_frame->OnCanDoSaveAs();
            item->Enable(canDo);
            break;
        case SW_GUIID_CLOSE:
            canDo = m_frame->OnCanDoClose();
            item->Enable(canDo);
            break;
        case SW_GUIID_CLOSEALL:
            canDo = m_frame->OnCanDoCloseAll();
            item->Enable(canDo);
            break;
        case SW_GUIID_PRINT:
            canDo = m_frame->OnCanDoPrint();
            item->Enable(canDo);
            break;
        case SW_GUIID_PRINTPREVIEW:
            canDo = m_frame->OnCanDoPrintPreview();
            item->Enable(canDo);
            break;
        case SW_GUIID_QUIT:
            item->Enable(true);
            break;

        /* Group - EDIT */
        case SW_GUIID_BOOKMARKPAGE:
            canDo = m_frame->OnCanDoBookMarkPage();
            item->Enable(canDo);
            break;
        case SW_GUIID_FIND:
            canDo = m_frame->OnCanDoFind();
            item->Enable(canDo);
            break;
        case SW_GUIID_FINDNEXT:
            canDo = m_frame->OnCanDoFindNext();
            item->Enable(canDo);
            break;
        case SW_GUIID_REPLACE:
            canDo = m_frame->OnCanDoReplace();
            item->Enable(canDo);
            break;
        case SW_GUIID_CLEAR:
            canDo = m_frame->OnCanDoClear();
            item->Enable(canDo);
            break;
        case SW_GUIID_CUT:
            canDo = m_frame->OnCanDoCut();
            item->Enable(canDo);
            break;
        case SW_GUIID_COPY:
            canDo = m_frame->OnCanDoCopy();
            item->Enable(canDo);
            break;
        case SW_GUIID_PASTE:
            canDo = m_frame->OnCanDoPaste();
            item->Enable(canDo);
            break;
        case SW_GUIID_UNDO:
            canDo = m_frame->OnCanDoUndo();
            item->Enable(canDo);
            break;
        case SW_GUIID_REDO:
            canDo = m_frame->OnCanDoRedo();
            item->Enable(canDo);
            break;
        case SW_GUIID_SELECTALL:
            canDo = m_frame->OnCanDoSelectAll();
            item->Enable(canDo);
            break;
        case SW_GUIID_GEO:
            canDo = m_frame->OnCanDoGeo();
            item->Enable(canDo);
            break;
        case SW_GUIID_MAPS:
            canDo = m_frame->OnCanDoMaps();
            item->Enable(canDo);
            break;
        case SW_GUIID_AREAS:
            canDo = m_frame->OnCanDoAreas();
            item->Enable(canDo);
            break;
        case SW_GUIID_PROPERTIES:
            canDo = m_frame->OnCanDoProperties();
            item->Enable(canDo);
            break;

        /* Group - VIEW */
        case SW_GUIID_LIBRARYVIEW:
            canDo = m_frame->HasLibraryView();
            item->Enable(canDo);
            break;
        case SW_GUIID_CONTENTSVIEW:
            canDo = m_frame->HasContentsView();
            item->Enable(canDo);
            break;
        case SW_GUIID_SEARCHVIEW:
            canDo = m_frame->HasSearchView();
            item->Enable(canDo);
            break;
        case SW_GUIID_FINDVIEW:
            canDo = m_frame->HasFindView();
            item->Enable(canDo);
            break;
        case SW_GUIID_BOOKMARKSVIEW:
            canDo = m_frame->HasBookmarksView();
            item->Enable(canDo);
            break;
        case SW_GUIID_HISTORYVIEW:
            canDo = m_frame->HasHistoryView();
            item->Enable(canDo);
            break;
        case SW_GUIID_ZOOMIN:
            canDo = m_frame->OnCanDoZoomIn();
            item->Enable(canDo);
            break;
        case SW_GUIID_ZOOMOUT:
            canDo = m_frame->OnCanDoZoomOut();
            item->Enable(canDo);
            break;
        case SW_GUIID_VIEWNORMAL:
            canDo = m_frame->OnCanDoViewNormal();
            item->Enable(canDo);
            break;

        /* Group - NAVIGATION */
        case SW_GUIID_CONTENTSUP:
            canDo = m_frame->OnCanDoUpInContents();
            item->Enable(canDo);
            break;
        case SW_GUIID_CONTENTSDOWN:
            canDo = m_frame->OnCanDoDownInContents();
            item->Enable(canDo);
            break;
        case SW_GUIID_BACKINHISTORY:
            canDo = m_frame->OnCanDoBackInHistory();
            item->Enable(canDo);
            break;
        case SW_GUIID_FORWARDINHISTORY:
            canDo = m_frame->OnCanDoForwardInHistory();
            item->Enable(canDo);
            break;

        /* Group - FORMAT */
        case SW_GUIID_FONT:
            canDo = m_frame->OnCanDoFont();
            item->Enable(canDo);
            break;
        case SW_GUIID_BOLD:
            canDo = m_frame->OnCanDoBold();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionBold())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ITALIC:
            canDo = m_frame->OnCanDoItalic();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionItalic())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_UNDERLINE:
            canDo = m_frame->OnCanDoUnderline();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionUnderline())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_STRIKETHROUGH:
            canDo = m_frame->OnCanDoStrikeThrough();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionStrikeThrough())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_SUPERSCRIPT:
            canDo = m_frame->OnCanDoSuperScript();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionSuperScript())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_SUBSCRIPT:
            canDo = m_frame->OnCanDoSubScript();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionSubScript())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_COLOR:
            canDo = m_frame->OnCanDoColor();
            item->Enable(canDo);
            break;
        case SW_GUIID_BACKGROUNDCOLOR:
            canDo = m_frame->OnCanDoBackGroundColor();
            item->Enable(canDo);
            break;
        case SW_GUIID_STYLE:
            canDo = m_frame->OnCanDoStyle();
            item->Enable(canDo);
            break;

        /* Group - PARAGRAPH */
        case SW_GUIID_MARGINS:
            canDo = m_frame->OnCanDoMargins();
            item->Enable(canDo);
            break;
        case SW_GUIID_INDENTMORE:
            canDo = m_frame->OnCanDoIndentMore();
            item->Enable(canDo);
            break;
        case SW_GUIID_INDENTLESS:
            canDo = m_frame->OnCanDoIndentLess();
            item->Enable(canDo);
            break;
        case SW_GUIID_ALIGNLEFT:
            canDo = m_frame->OnCanDoAlignLeft();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlignLeft())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ALIGNCENTER:
            canDo = m_frame->OnCanDoAlignCenter();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlignCenter())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ALIGNRIGHT:
            canDo = m_frame->OnCanDoAlignRight();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlignRight())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_SINGLESPACING:
            canDo = m_frame->OnCanDoSingleSpacing();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionSingleSpacing())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_DOUBLESPACING:
            canDo = m_frame->OnCanDoDoubleSpacing();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionDoubleSpacing())
                buttonState = true;
            item->Check(buttonState);
            break;

        /* Group - LIST */
        case SW_GUIID_ALPHABETICLIST:
            canDo = m_frame->OnCanDoAlphaList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlphaList())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_BULLETEDLIST:
            canDo = m_frame->OnCanDoBulletedList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionBulletedList())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ROMANNUMERALSLIST:
            canDo = m_frame->OnCanDoRomanNumeralsList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionRomanNumeralsList())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_DECIMALLIST:
            canDo = m_frame->OnCanDoDecimalList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionDecimalList())
                buttonState = true;
            item->Check(buttonState);
            break;

        /* Group - TABLE */
        case SW_GUIID_INSERTTABLE:
            canDo = m_frame->OnCanDoInsertTable();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTROW:
            canDo = m_frame->OnCanDoInsertRow();
            item->Enable(canDo);
            break;
        case SW_GUIID_DELETEROW:
            canDo = m_frame->OnCanDoDeleteRow();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTCOLUMN:
            canDo = m_frame->OnCanDoInsertColumn();
            item->Enable(canDo);
            break;
        case SW_GUIID_DELETECOLUMN:
            canDo = m_frame->OnCanDoDeleteColumn();
            item->Enable(canDo);
            break;

        /* Group - Objects */
        case SW_GUIID_INSERTIMAGE:
            canDo = m_frame->OnCanDoInsertImage();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTLINK:
            canDo = m_frame->OnCanDoInsertLink();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTANCHOR:
            canDo = m_frame->OnCanDoInsertAnchor();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTCONTROL:
            canDo = m_frame->OnCanDoInsertControl();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTHORIZONTALRULE:
            canDo = m_frame->OnCanDoInsertHorizontalRule();
            item->Enable(canDo);
            break;

        /* Group - SETTINGS */
        case SW_GUIID_PREFERENCES:
            item->Enable(true);
            break;
        case SW_GUIID_SELECTINTERFACE:
            if (SwApplicationInterface::GetInterfaceCount() > 1)
                item->Enable(true);
            else
                item->Enable(false);
            break;
        case SW_GUIID_SELECTLANGUAGE:
            item->Enable(true);
            break;
        case SW_GUIID_SELECTTHEME:
            item->Enable(true);
            break;
        case SW_GUIID_CONFIGURATION:
            item->Enable(true);
            break;

        /* Group - HELP */
        case SW_GUIID_HELPCONTENTS:
            item->Enable(true);
            break;
        case SW_GUIID_ABOUT:
            item->Enable(true);
            break;
        case SW_GUIID_UPDATESOFTWARE:
            item->Enable(true);
            break;

        /* Players */
        case SW_GUIID_PLAY:
            canDo = m_frame->OnCanDoPlay();
            item->Enable(canDo);
            break;
        case SW_GUIID_PAUSE:
            canDo = m_frame->OnCanDoPause();
            item->Enable(canDo);
            break;
        case SW_GUIID_STOP:
            canDo = m_frame->OnCanDoStop();
            item->Enable(canDo);
            break;
        case SW_GUIID_REWIND:
            canDo = m_frame->OnCanDoRewind();
            item->Enable(canDo);
            break;
        case SW_GUIID_FASTFORWARD:
            canDo = m_frame->OnCanDoFastForward();
            item->Enable(canDo);
            break;
        case SW_GUIID_PREVIOUS:
            canDo = m_frame->OnCanDoPrevious();
            item->Enable(canDo);
            break;
        case SW_GUIID_NEXT:
            canDo = m_frame->OnCanDoNext();
            item->Enable(canDo);
            break;
        }
    }
}

SwMenuBar::SwMenuBar()
{
    m_frame = NULL;

    for (swUI8 i = 0; i < N_SW_MENU_IDS; i ++)
    {
        m_stockMenus[i] = NULL;
    }
}

SwMenuBar::SwMenuBar(SwFrame * frame)
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    SetFrameWindow(frame);

    for (swUI8 i = 0; i < N_SW_MENU_IDS; i ++)
    {
        m_stockMenus[i] = NULL;
    }
}

void SwMenuBar::SetFrameWindow(SwFrame * frame)
{
    m_frame = frame;

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
    m_eventHandlers[SW_GUIID_CONFIGURATION] = &SwFrame::OnConfiguration;

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

    m_eventHandlers[SW_GUIID_DELETE] = &SwFrame::OnDelete;
}

void SwMenuBar::OnEvent(wxCommandEvent & event)
{
    if (!m_frame)
        return;

    swUI8 swid = SwGuiData::FindItemWxId(event.GetId());

    wxMenuEvent * menuevent = (wxMenuEvent *) &event;
    wxMenuItem * wxitem;
    SwMenuItem *switem;

    if (swid == NODE_ID_INVALID_8)
    {
        wxitem = (wxMenuItem *) menuevent->GetEventObject();

        if (wxitem->IsKindOf(CLASSINFO(SwMenuItem)))
        {
            switem = (SwMenuItem *) menuevent->GetEventObject();

            if (switem->GetAt())
            {
                switem->GetAt()->AddTool(m_frame->GetToolBook());
                m_frame->ToolAdded();
            }
            else
            {
                (m_frame->*m_eventHandlers[SW_GUIID_UNKNOWN])(event);
            }
        }
    }
    else
    {
        (m_frame->*m_eventHandlers[swid])(event);
    }
}

SwMenu * SwMenuBar::AddStockMenu(swUI8 menuid)
{
    if (!menuid || menuid >= N_SW_MENU_IDS)
        return NULL;

    swUI8 insertPos = 0;

    for (swUI8 i = 0; i < menuid; i ++)
    {
        if (m_stockMenus[i])
            insertPos ++;
    }

    if (m_stockMenus[menuid])
        return m_stockMenus[menuid];

    m_stockMenus[menuid] = new SwMenu(menuid);


    Insert(insertPos, m_stockMenus[menuid], m_stockMenus[menuid]->GetTranslatedLabel());

    return m_stockMenus[menuid];
}

SwMenu * SwMenuBar::AddStockSubMenu(swUI8 menuid)
{
    if (!menuid || menuid >= N_SW_MENU_IDS)
        return NULL;

    if (m_stockMenus[menuid])
        return m_stockMenus[menuid];

    swUI8 parentId = SwGuiData::GetDataForMenuSwId(menuid)->sw_guiid_parent;

    if (parentId == SW_MENUID_UNKNOWN)
        return NULL;

    if (!AddStockMenu(parentId))
        return NULL;

    m_stockMenus[menuid] = new SwMenu(menuid);
    m_stockMenus[parentId]->AppendSubMenu(m_stockMenus[menuid], m_stockMenus[menuid]->GetTranslatedLabel());

    return m_stockMenus[menuid];
}

SwMenuItem * SwMenuBar::AddStockItem(swUI8 swid, bool enabled, bool addSeparators)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return NULL;

    wxMenuItem * wxitem = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (wxitem && wxitem->IsKindOf(CLASSINFO(SwMenuItem)))
        return (SwMenuItem *) wxitem;

    SwMenuItem * item = new SwMenuItem(NULL, SwGuiData::GetDataForItemSwId(swid)->wx_id, SwApplicationInterface::GetControlString(SwGuiData::GetDataForItemSwId(swid)->sid_label, SwGuiData::GetDataForItemSwId(swid)->label, false), wxEmptyString, SwGuiData::GetDataForItemSwId(swid)->itemtype, NULL);
    item->SetId(swid);

    if (strlen(SwGuiData::GetDataForItemSwId(swid)->sid_image))
    {
        item->SetBitmap(SwApplicationInterface::GetImage(SwGuiData::GetDataForItemSwId(swid)->sid_image));
    }

    swUI8 parent = SwGuiData::GetDataForItemSwId(swid)->sw_guiid_parent;
    swUI8 sep = SwGuiData::GetDataForItemSwId(swid)->separator;

    if (SwGuiData::GetDataForMenuSwId(parent)->sw_guiid_parent == SW_MENUID_UNKNOWN)
    {
        if (!AddStockMenu(parent))
            return NULL;
    }
    else
    {
        if (!AddStockSubMenu(parent))
            return NULL;
    }

    if (addSeparators && sep == SEP_BEFORE)
        m_stockMenus[parent]->AppendSeparator();

    m_stockMenus[parent]->Append(item);
    item->Enable(enabled);

    if (addSeparators && sep == SEP_AFTER)
        m_stockMenus[parent]->AppendSeparator();

    Connect(SwGuiData::GetDataForItemSwId(swid)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SwMenuBar::OnEvent);

    return item;
}

SwMenuItem * SwMenuBar::AddTool(SwPlugIn * plugin, const wchar_t * label)
{
    if (!plugin || !label)
        return NULL;

    AddStockMenu(SW_MENUID_TOOLS);
    SwMenuItem * item = new SwMenuItem(m_stockMenus[SW_MENUID_TOOLS], wxNewId(), label, wxEmptyString, wxITEM_NORMAL, NULL);

    Connect(item->GetId(), wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SwMenuBar::OnEvent);

    return item;
}

void SwMenuBar::EnableItem(swUI8 swid, bool enable)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return;

    wxMenuItem * item = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (!item)
        return;

    item->Enable(enable);
}

bool SwMenuBar::IsItemEnabled(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return false;

    wxMenuItem * item = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (!item)
        return false;

    return item->IsEnabled();
}

void SwMenuBar::CheckItem(swUI8 swid, bool check)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return;

    wxMenuItem * item = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (!item)
        return;

    item->Check(check);
}

bool SwMenuBar::IsItemChecked(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return false;

    wxMenuItem * item = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (!item)
        return false;

    return item->IsChecked();
}

// Top level menu's only.
void SwMenuBar::SetCustomMenuLabel(size_t pos, const char * strid, const wchar_t * deflabel)
{
    if (!strid || !deflabel)
        return;

    wxMenu * menu = GetMenu(pos);

    if (menu)
        menu->SetTitle(SwApplicationInterface::GetControlString(strid, deflabel));
}

void SwMenuBar::SetCustomMenuItemBitmap(int wxid, const char * strid)
{
    if (!strid)
        return;

    wxMenuItem * item = FindItem(wxid);

    if (!item)
        return;

    item->SetBitmap(SwApplicationInterface::GetImage(strid));
    #if defined __MSWIN__
    item->SetDisabledBitmap(SwApplicationInterface::GetImage(strid).ConvertToDisabled());
    #endif
}

void SwMenuBar::SetCustomMenuItemLabel(int wxid, const char * strid, const wchar_t * deflabel)
{
    if (!strid || !deflabel)
        return;

    SetLabel(wxid, SwApplicationInterface::GetControlString(strid, deflabel));
}

// Strings must be stored as utf8 strings.
void SwMenuBar::UpdateRecentFileList(SwStringArray & array)
{
    SwStringW translation;

    for (swUI32 pos = 0; pos < 10 && pos < array.GetCount(); pos ++)
    {
        translation.Copy(array.GetAt(pos));
        if (FindItem(SwGuiData::GetDataForItemSwId(SW_GUIID_FILE1 + pos)->wx_id))
        {
            SetLabel(SwGuiData::GetDataForItemSwId(SW_GUIID_FILE1 + pos)->wx_id, translation.GetArray());
            EnableItem(SW_GUIID_FILE1 + pos, true);
        }
    }

    // Empty strings.
    for (swUI32 pos = array.GetCount(); pos < 10; pos ++)
    {
        if (FindItem(SwGuiData::GetDataForItemSwId(SW_GUIID_FILE1 + pos)->wx_id))
        {
            SetLabel(SwGuiData::GetDataForItemSwId(SW_GUIID_FILE1 + pos)->wx_id, L" ");
            EnableItem(SW_GUIID_FILE1 + pos, false);
        }
    }
}

void SwMenuBar::ClearRecentFileList()
{
    SwString translation;

    for (swUI32 pos = 0; pos < 10; pos ++)
    {
        if (FindItem(SwGuiData::GetDataForItemSwId(SW_GUIID_FILE1 + pos)->wx_id))
        {
            SetLabel(SwGuiData::GetDataForItemSwId(SW_GUIID_FILE1 + pos)->wx_id, L" ");
            EnableItem(SW_GUIID_FILE1 + pos, false);
        }
    }
}

const wchar_t * SwMenuBar::GetItemLabel(swUI8 swid)
{
    if (swid >= N_SW_GUIITEM_IDS)
        return L"";

    wxMenuItem * item = FindItem(SwGuiData::GetDataForItemSwId(swid)->wx_id);

    if (!item)
        return L"";

    return GetLabel(SwGuiData::GetDataForItemSwId(swid)->wx_id).wchar_str();
}

void SwMenuBar::OnLanguageChange()
{
    for (size_t pos = 0; pos < GetMenuCount(); pos ++)
    {
        IterateMenu(GetMenu(pos), pos, true, false, false);
    }
}

void SwMenuBar::OnThemeChange()
{
    for (size_t pos = 0; pos < GetMenuCount(); pos ++)
    {
        IterateMenu(GetMenu(pos), pos, false, true, false);
    }
}

void SwMenuBar::IterateMenu(wxMenu * menu, size_t pos, bool updateLanguage, bool updateTheme, bool issubMenu)
{
    SwMenu * sowermenu;
    SwMenuItem * sowermenuitem;
    wxMenuItem * wxitem;

    if (!menu)
        return;

    if (menu && menu->IsKindOf(CLASSINFO(SwMenu)))
    {
        sowermenu = (SwMenu *) menu;
        if (updateLanguage && !SwGuiData::IsRecentFile(sowermenu->GetId()))
        {
            if (!issubMenu)
                SetMenuLabel(pos, sowermenu->GetTranslatedLabel());
            else
                sowermenu->SetTitle(sowermenu->GetTranslatedLabel());
        }
    }

    for (size_t i = 0; i < menu->GetMenuItemCount(); i ++)
    {
        wxitem = menu->FindItemByPosition(i);

        if (!wxitem)
            continue;

        if (wxitem->IsKindOf(CLASSINFO(SwMenuItem)))
        {
            sowermenuitem = (SwMenuItem *) wxitem;

            if (updateLanguage && !SwGuiData::IsRecentFile(sowermenuitem->GetId()))
            {
                sowermenuitem->OnLanguageChange();
            }

            if (updateTheme)
            {
                sowermenuitem->OnThemeChange();
            }
        }

        IterateMenu(wxitem->GetSubMenu(), 0, updateLanguage, updateTheme, true);
    }
}

void SwMenuBar::OnFontSizeChange(const wxFont & font)
{
    SetFont(font);
}

void SwMenuBar::UpdateGui()
{
    if (!m_frame)
        return;

    wxMenuItem * item;
    bool canDo;
    bool buttonState;

    for (swUI8 i = 0; i < N_SW_GUIITEM_IDS; i ++)
    {
        item = FindItem(SwGuiData::GetDataForElement(i)->wx_id);

        if (!item)
            continue;

        switch (SwGuiData::GetDataForElement(i)->sw_guiid)
        {
        /* Group - FILE */
        case SW_GUIID_NEW:
            canDo = m_frame->OnCanDoNew();
            item->Enable(canDo);
            break;
        case SW_GUIID_OPEN:
            canDo = m_frame->OnCanDoOpen();
            item->Enable(canDo);
            break;
        case SW_GUIID_SAVE:
            canDo = m_frame->OnCanDoSave();
            item->Enable(canDo);
            break;
        case SW_GUIID_SAVEAS:
            canDo = m_frame->OnCanDoSaveAs();
            item->Enable(canDo);
            break;
        case SW_GUIID_CLOSE:
            canDo = m_frame->OnCanDoClose();
            item->Enable(canDo);
            break;
        case SW_GUIID_CLOSEALL:
            canDo = m_frame->OnCanDoCloseAll();
            item->Enable(canDo);
            break;
        case SW_GUIID_PRINT:
            canDo = m_frame->OnCanDoPrint();
            item->Enable(canDo);
            break;
        case SW_GUIID_PRINTPREVIEW:
            canDo = m_frame->OnCanDoPrintPreview();
            item->Enable(canDo);
            break;
        case SW_GUIID_QUIT:
            item->Enable(true);
            break;

        /* Group - EDIT */
        case SW_GUIID_BOOKMARKPAGE:
            canDo = m_frame->OnCanDoBookMarkPage();
            item->Enable(canDo);
            break;
        case SW_GUIID_FIND:
            canDo = m_frame->OnCanDoFind();
            item->Enable(canDo);
            break;
        case SW_GUIID_FINDNEXT:
            canDo = m_frame->OnCanDoFindNext();
            item->Enable(canDo);
            break;
        case SW_GUIID_REPLACE:
            canDo = m_frame->OnCanDoReplace();
            item->Enable(canDo);
            break;
        case SW_GUIID_CLEAR:
            canDo = m_frame->OnCanDoClear();
            item->Enable(canDo);
            break;
        case SW_GUIID_CUT:
            canDo = m_frame->OnCanDoCut();
            item->Enable(canDo);
            break;
        case SW_GUIID_COPY:
            canDo = m_frame->OnCanDoCopy();
            item->Enable(canDo);
            break;
        case SW_GUIID_PASTE:
            canDo = m_frame->OnCanDoPaste();
            item->Enable(canDo);
            break;
        case SW_GUIID_UNDO:
            canDo = m_frame->OnCanDoUndo();
            item->Enable(canDo);
            break;
        case SW_GUIID_REDO:
            canDo = m_frame->OnCanDoRedo();
            item->Enable(canDo);
            break;
        case SW_GUIID_SELECTALL:
            canDo = m_frame->OnCanDoSelectAll();
            item->Enable(canDo);
            break;
        case SW_GUIID_GEO:
            canDo = m_frame->OnCanDoGeo();
            item->Enable(canDo);
            break;
        case SW_GUIID_MAPS:
            canDo = m_frame->OnCanDoMaps();
            item->Enable(canDo);
            break;
        case SW_GUIID_AREAS:
            canDo = m_frame->OnCanDoAreas();
            item->Enable(canDo);
            break;
        case SW_GUIID_PROPERTIES:
            canDo = m_frame->OnCanDoProperties();
            item->Enable(canDo);
            break;

        /* Group - VIEW */
        case SW_GUIID_LIBRARYVIEW:
            canDo = m_frame->HasLibraryView();
            item->Enable(canDo);
            break;
        case SW_GUIID_CONTENTSVIEW:
            canDo = m_frame->HasContentsView();
            item->Enable(canDo);
            break;
        case SW_GUIID_SEARCHVIEW:
            canDo = m_frame->HasSearchView();
            item->Enable(canDo);
            break;
        case SW_GUIID_FINDVIEW:
            canDo = m_frame->HasFindView();
            item->Enable(canDo);
            break;
        case SW_GUIID_BOOKMARKSVIEW:
            canDo = m_frame->HasBookmarksView();
            item->Enable(canDo);
            break;
        case SW_GUIID_HISTORYVIEW:
            canDo = m_frame->HasHistoryView();
            item->Enable(canDo);
            break;
        case SW_GUIID_ZOOMIN:
            canDo = m_frame->OnCanDoZoomIn();
            item->Enable(canDo);
            break;
        case SW_GUIID_ZOOMOUT:
            canDo = m_frame->OnCanDoZoomOut();
            item->Enable(canDo);
            break;
        case SW_GUIID_VIEWNORMAL:
            canDo = m_frame->OnCanDoViewNormal();
            item->Enable(canDo);
            break;

        /* Group - NAVIGATION */
        case SW_GUIID_CONTENTSUP:
            canDo = m_frame->OnCanDoUpInContents();
            item->Enable(canDo);
            break;
        case SW_GUIID_CONTENTSDOWN:
            canDo = m_frame->OnCanDoDownInContents();
            item->Enable(canDo);
            break;
        case SW_GUIID_BACKINHISTORY:
            canDo = m_frame->OnCanDoBackInHistory();
            item->Enable(canDo);
            break;
        case SW_GUIID_FORWARDINHISTORY:
            canDo = m_frame->OnCanDoForwardInHistory();
            item->Enable(canDo);
            break;

        /* Group - FORMAT */
        case SW_GUIID_FONT:
            canDo = m_frame->OnCanDoFont();
            item->Enable(canDo);
            break;
        case SW_GUIID_BOLD:
            canDo = m_frame->OnCanDoBold();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionBold())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ITALIC:
            canDo = m_frame->OnCanDoItalic();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionItalic())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_UNDERLINE:
            canDo = m_frame->OnCanDoUnderline();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionUnderline())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_STRIKETHROUGH:
            canDo = m_frame->OnCanDoStrikeThrough();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionStrikeThrough())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_SUPERSCRIPT:
            canDo = m_frame->OnCanDoSuperScript();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionSuperScript())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_SUBSCRIPT:
            canDo = m_frame->OnCanDoSubScript();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionSubScript())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_COLOR:
            canDo = m_frame->OnCanDoColor();
            item->Enable(canDo);
            break;
        case SW_GUIID_BACKGROUNDCOLOR:
            canDo = m_frame->OnCanDoBackGroundColor();
            item->Enable(canDo);
            break;
        case SW_GUIID_STYLE:
            canDo = m_frame->OnCanDoStyle();
            item->Enable(canDo);
            break;

        /* Group - PARAGRAPH */
        case SW_GUIID_MARGINS:
            canDo = m_frame->OnCanDoMargins();
            item->Enable(canDo);
            break;
        case SW_GUIID_INDENTMORE:
            canDo = m_frame->OnCanDoIndentMore();
            item->Enable(canDo);
            break;
        case SW_GUIID_INDENTLESS:
            canDo = m_frame->OnCanDoIndentLess();
            item->Enable(canDo);
            break;
        case SW_GUIID_ALIGNLEFT:
            canDo = m_frame->OnCanDoAlignLeft();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlignLeft())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ALIGNCENTER:
            canDo = m_frame->OnCanDoAlignCenter();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlignCenter())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ALIGNRIGHT:
            canDo = m_frame->OnCanDoAlignRight();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlignRight())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_SINGLESPACING:
            canDo = m_frame->OnCanDoSingleSpacing();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionSingleSpacing())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_DOUBLESPACING:
            canDo = m_frame->OnCanDoDoubleSpacing();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionDoubleSpacing())
                buttonState = true;
            item->Check(buttonState);
            break;

        /* Group - LIST */
        case SW_GUIID_ALPHABETICLIST:
            canDo = m_frame->OnCanDoAlphaList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionAlphaList())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_BULLETEDLIST:
            canDo = m_frame->OnCanDoBulletedList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionBulletedList())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_ROMANNUMERALSLIST:
            canDo = m_frame->OnCanDoRomanNumeralsList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionRomanNumeralsList())
                buttonState = true;
            item->Check(buttonState);
            break;
        case SW_GUIID_DECIMALLIST:
            canDo = m_frame->OnCanDoDecimalList();
            item->Enable(canDo);
            buttonState = false;
            if (canDo && m_frame->IsSelectionDecimalList())
                buttonState = true;
            item->Check(buttonState);
            break;

        /* Group - TABLE */
        case SW_GUIID_INSERTTABLE:
            canDo = m_frame->OnCanDoInsertTable();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTROW:
            canDo = m_frame->OnCanDoInsertRow();
            item->Enable(canDo);
            break;
        case SW_GUIID_DELETEROW:
            canDo = m_frame->OnCanDoDeleteRow();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTCOLUMN:
            canDo = m_frame->OnCanDoInsertColumn();
            item->Enable(canDo);
            break;
        case SW_GUIID_DELETECOLUMN:
            canDo = m_frame->OnCanDoDeleteColumn();
            item->Enable(canDo);
            break;

        /* Group - Objects */
        case SW_GUIID_INSERTIMAGE:
            canDo = m_frame->OnCanDoInsertImage();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTLINK:
            canDo = m_frame->OnCanDoInsertLink();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTANCHOR:
            canDo = m_frame->OnCanDoInsertAnchor();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTCONTROL:
            canDo = m_frame->OnCanDoInsertControl();
            item->Enable(canDo);
            break;
        case SW_GUIID_INSERTHORIZONTALRULE:
            canDo = m_frame->OnCanDoInsertHorizontalRule();
            item->Enable(canDo);
            break;

        /* Group - SETTINGS */
        case SW_GUIID_PREFERENCES:
            item->Enable(true);
            break;
        case SW_GUIID_SELECTINTERFACE:
            if (SwApplicationInterface::GetInterfaceCount() > 1)
                item->Enable(true);
            else
                item->Enable(false);
            break;
        case SW_GUIID_SELECTLANGUAGE:
            item->Enable(true);
            break;
        case SW_GUIID_SELECTTHEME:
            item->Enable(true);
            break;
        case SW_GUIID_CONFIGURATION:
            item->Enable(true);
            break;

        /* Group - HELP */
        case SW_GUIID_HELPCONTENTS:
            item->Enable(true);
            break;
        case SW_GUIID_ABOUT:
            item->Enable(true);
            break;
        case SW_GUIID_UPDATESOFTWARE:
            item->Enable(true);
            break;

        /* Players */
        case SW_GUIID_PLAY:
            canDo = m_frame->OnCanDoPlay();
            item->Enable(canDo);
            break;
        case SW_GUIID_PAUSE:
            canDo = m_frame->OnCanDoPause();
            item->Enable(canDo);
            break;
        case SW_GUIID_STOP:
            canDo = m_frame->OnCanDoStop();
            item->Enable(canDo);
            break;
        case SW_GUIID_REWIND:
            canDo = m_frame->OnCanDoRewind();
            item->Enable(canDo);
            break;
        case SW_GUIID_FASTFORWARD:
            canDo = m_frame->OnCanDoFastForward();
            item->Enable(canDo);
            break;
        case SW_GUIID_PREVIOUS:
            canDo = m_frame->OnCanDoPrevious();
            item->Enable(canDo);
            break;
        case SW_GUIID_NEXT:
            canDo = m_frame->OnCanDoNext();
            item->Enable(canDo);
            break;
        }
    }

  //  Refresh();
}

SwUtilityMenuBar::SwUtilityMenuBar()
{
}

SwUtilityMenuBar::SwUtilityMenuBar(SwFrame * frame)
    :SwMenuBar(frame)
{
    AddStockItem(SW_GUIID_OPEN, true, true);
    AddStockItem(SW_GUIID_CLOSE, false, true);
    AddStockItem(SW_GUIID_CLOSEALL, false, true);
    AddStockItem(SW_GUIID_PRINT, false, true);
    AddStockItem(SW_GUIID_QUIT, true, true);
    AddStockItem(SW_GUIID_ABOUT, true, true);
}

SwUtilityMenuBar::~SwUtilityMenuBar()
{
}

void SwUtilityMenuBar::EnableItems(bool state)
{
    EnableItem(SW_GUIID_CLOSE, state);
    EnableItem(SW_GUIID_CLOSEALL, state);
    EnableItem(SW_GUIID_PRINT, state);
}

SwBasicMenuBar::SwBasicMenuBar()
{
}

SwBasicMenuBar::SwBasicMenuBar(SwFrame * frame)
    :SwMenuBar(frame)
{
    AddStockItem(SW_GUIID_OPEN, true, true);
    AddStockItem(SW_GUIID_CLOSE, false, true);
    AddStockItem(SW_GUIID_QUIT, true, true);
    AddStockItem(SW_GUIID_ABOUT, true, true);
}

SwBasicMenuBar::~SwBasicMenuBar()
{
}

void SwBasicMenuBar::EnableItems(bool state)
{
    EnableItem(SW_GUIID_CLOSE, state);
}

void SwBasicMenuBar::EnableOpen(bool state)
{
    EnableItem(SW_GUIID_OPEN, state);
}


SwBasicEditorMenuBar::SwBasicEditorMenuBar()
{
}

SwBasicEditorMenuBar::SwBasicEditorMenuBar(SwFrame * frame)
    :SwMenuBar(frame)
{
    AddStockItem(SW_GUIID_OPEN, true, true);
    AddStockItem(SW_GUIID_NEW, true, true);
    AddStockItem(SW_GUIID_CLOSE, false, true);
    AddStockItem(SW_GUIID_QUIT, true, true);
    AddStockItem(SW_GUIID_ABOUT, true, true);
}

SwBasicEditorMenuBar::~SwBasicEditorMenuBar()
{
}

void SwBasicEditorMenuBar::EnableItems(bool state)
{
    EnableItem(SW_GUIID_CLOSE, state);
}

void SwBasicEditorMenuBar::EnableOpen(bool state)
{
    EnableItem(SW_GUIID_OPEN, state);
}

void SwBasicEditorMenuBar::EnableNew(bool state)
{
    EnableItem(SW_GUIID_NEW, state);
}

SwViewMenu::SwViewMenu()
{
}

SwViewMenu::SwViewMenu(SwFrame * frame)
    : SwMenu(frame)
{
}

SwViewMenu::~SwViewMenu()
{
}

void SwViewMenu::Init()
{
}

void SwViewMenu::OnEvent(wxCommandEvent & event)
{
}

SwBasicViewMenu::SwBasicViewMenu()
{
}

SwBasicViewMenu::SwBasicViewMenu(SwFrame * frame)
    : SwViewMenu(frame)
{
    Init();
}

SwBasicViewMenu::~SwBasicViewMenu()
{
}

void SwBasicViewMenu::Init()
{
    AddStockItem(SW_GUIID_COPY, true, false);
    AddStockItem(SW_GUIID_SELECTALL, true, false);
    AppendSeparator();
    AddStockItem(SW_GUIID_CONTENTSUP, true, false);
    AddStockItem(SW_GUIID_CONTENTSDOWN, true, true);
    AddStockItem(SW_GUIID_BACKINHISTORY, true, true);
    AddStockItem(SW_GUIID_FORWARDINHISTORY, true, true);
    AppendSeparator();
    AddStockItem(SW_GUIID_BOOKMARKPAGE, true, false);
    AddStockItem(SW_GUIID_ZOOMIN, true, true);
    AddStockItem(SW_GUIID_ZOOMOUT, true, true);
    AddStockItem(SW_GUIID_VIEWNORMAL, true, true);
    AddStockItem(SW_GUIID_PRINT, true, true);
    AddStockItem(SW_GUIID_PRINTPREVIEW, true, false);
    AppendSeparator();
    AddStockItem(SW_GUIID_PLAY, false, true);
    AddStockItem(SW_GUIID_PAUSE, false, true);
    AddStockItem(SW_GUIID_STOP, false, true);
    AddStockItem(SW_GUIID_REWIND, false, true);
    AddStockItem(SW_GUIID_FASTFORWARD, false, true);
    AddStockItem(SW_GUIID_PREVIOUS, false, true);
    AddStockItem(SW_GUIID_NEXT, false, true);
}

void SwBasicViewMenu::OnEvent(wxCommandEvent & event)
{
    if (!m_frame)
        return;

    swUI8 swid = SwGuiData::FindItemWxId(event.GetId());

    if (swid == NODE_ID_INVALID_8)
    {
        event.Skip();
        return;
    }

    switch (swid)
    {
    case SW_GUIID_COPY:
        m_frame->OnCopy(event);
        break;
    case SW_GUIID_SELECTALL:
        m_frame->OnSelectAll(event);
        break;
    case SW_GUIID_CONTENTSUP:
        m_frame->OnContentsUp(event);
        break;
    case SW_GUIID_CONTENTSDOWN:
        m_frame->OnContentsDown(event);
        break;
    case SW_GUIID_BACKINHISTORY:
        m_frame->OnHistoryBack(event);
        break;
    case SW_GUIID_FORWARDINHISTORY:
        m_frame->OnHistoryForward(event);
        break;
    case SW_GUIID_ZOOMIN:
        m_frame->OnZoomIn(event);
        break;
    case SW_GUIID_ZOOMOUT:
        m_frame->OnZoomOut(event);
        break;
    case SW_GUIID_VIEWNORMAL:
        m_frame->OnViewNormal(event);
        break;
    case SW_GUIID_PRINT:
        m_frame->OnPrint(event);
        break;
    case SW_GUIID_PRINTPREVIEW:
        m_frame->OnPrintPreview(event);
        break;
    }
}

SwStandardViewMenu::SwStandardViewMenu()
{
}

SwStandardViewMenu::SwStandardViewMenu(SwFrame * frame)
    : SwViewMenu(frame)
{
    Init();
}

SwStandardViewMenu::~SwStandardViewMenu()
{
}

void SwStandardViewMenu::Init()
{
    AddStockItem(SW_GUIID_COPY, true, false);
    AddStockItem(SW_GUIID_SELECTALL, true, false);
    AppendSeparator();
    AddStockItem(SW_GUIID_CONTENTSUP, true, false);
    AddStockItem(SW_GUIID_CONTENTSDOWN, true, true);
    AddStockItem(SW_GUIID_BACKINHISTORY, true, true);
    AddStockItem(SW_GUIID_FORWARDINHISTORY, true, true);
    AppendSeparator();
    AddStockItem(SW_GUIID_BOOKMARKPAGE, true, false);
    AddStockItem(SW_GUIID_ZOOMIN, true, true);
    AddStockItem(SW_GUIID_ZOOMOUT, true, true);
    AddStockItem(SW_GUIID_VIEWNORMAL, true, true);
    AddStockItem(SW_GUIID_PRINT, true, true);
    AddStockItem(SW_GUIID_PRINTPREVIEW, true, false);
}

void SwStandardViewMenu::OnEvent(wxCommandEvent & event)
{
    if (!m_frame)
        return;

    swUI8 swid = SwGuiData::FindItemWxId(event.GetId());

    if (swid == NODE_ID_INVALID_8)
    {
        event.Skip();
        return;
    }

    switch (swid)
    {
    case SW_GUIID_COPY:
        m_frame->OnCopy(event);
        break;
    case SW_GUIID_SELECTALL:
        m_frame->OnSelectAll(event);
        break;
    case SW_GUIID_CONTENTSUP:
        m_frame->OnContentsUp(event);
        break;
    case SW_GUIID_CONTENTSDOWN:
        m_frame->OnContentsDown(event);
        break;
    case SW_GUIID_BACKINHISTORY:
        m_frame->OnHistoryBack(event);
        break;
    case SW_GUIID_FORWARDINHISTORY:
        m_frame->OnHistoryForward(event);
        break;
    case SW_GUIID_BOOKMARKPAGE:
        m_frame->OnBookmark(event);
        break;
    case SW_GUIID_ZOOMIN:
        m_frame->OnZoomIn(event);
        break;
    case SW_GUIID_ZOOMOUT:
        m_frame->OnZoomOut(event);
        break;
    case SW_GUIID_VIEWNORMAL:
        m_frame->OnViewNormal(event);
        break;
    case SW_GUIID_PRINT:
        m_frame->OnPrint(event);
        break;
    case SW_GUIID_PRINTPREVIEW:
        m_frame->OnPrintPreview(event);
        break;
    }
}

SwExtendedViewMenu::SwExtendedViewMenu()
{
}

SwExtendedViewMenu::SwExtendedViewMenu(SwFrame * frame)
    :SwViewMenu(frame)
{
    Init();
}

SwExtendedViewMenu::~SwExtendedViewMenu()
{
}

void SwExtendedViewMenu::Init()
{
    AddStockItem(SW_GUIID_COPY, true, false);
    AddStockItem(SW_GUIID_SELECTALL, true, false);
    AppendSeparator();
    AddStockItem(SW_GUIID_CONTENTSUP, true, false);
    AddStockItem(SW_GUIID_CONTENTSDOWN, true, true);
    AddStockItem(SW_GUIID_BACKINHISTORY, true, true);
    AddStockItem(SW_GUIID_FORWARDINHISTORY, true, true);
    AppendSeparator();
    AddStockItem(SW_GUIID_BOOKMARKPAGE, true, false);
    AddStockItem(SW_GUIID_ZOOMIN, true, true);
    AddStockItem(SW_GUIID_ZOOMOUT, true, true);
    AddStockItem(SW_GUIID_VIEWNORMAL, true, true);
    AddStockItem(SW_GUIID_PRINT, true, true);
    AddStockItem(SW_GUIID_PRINTPREVIEW, true, false);
    AppendSeparator();
    AddStockItem(SW_GUIID_PLAY, false, true);
    AddStockItem(SW_GUIID_PAUSE, false, true);
    AddStockItem(SW_GUIID_STOP, false, true);
    AddStockItem(SW_GUIID_REWIND, false, true);
    AddStockItem(SW_GUIID_FASTFORWARD, false, true);
    AddStockItem(SW_GUIID_PREVIOUS, false, true);
    AddStockItem(SW_GUIID_NEXT, false, true);
}

void SwExtendedViewMenu::OnEvent(wxCommandEvent & event)
{
    if (!m_frame)
        return;

    swUI8 swid = SwGuiData::FindItemWxId(event.GetId());

    if (swid == NODE_ID_INVALID_8)
    {
        event.Skip();
        return;
    }

    switch (swid)
    {
    case SW_GUIID_COPY:
        m_frame->OnCopy(event);
        break;
    case SW_GUIID_SELECTALL:
        m_frame->OnSelectAll(event);
        break;
    case SW_GUIID_CONTENTSUP:
        m_frame->OnContentsUp(event);
        break;
    case SW_GUIID_CONTENTSDOWN:
        m_frame->OnContentsDown(event);
        break;
    case SW_GUIID_BACKINHISTORY:
        m_frame->OnHistoryBack(event);
        break;
    case SW_GUIID_FORWARDINHISTORY:
        m_frame->OnHistoryForward(event);
        break;
    case SW_GUIID_BOOKMARKPAGE:
        m_frame->OnBookmark(event);
        break;
    case SW_GUIID_ZOOMIN:
        m_frame->OnZoomIn(event);
        break;
    case SW_GUIID_ZOOMOUT:
        m_frame->OnZoomOut(event);
        break;
    case SW_GUIID_VIEWNORMAL:
        m_frame->OnViewNormal(event);
        break;
    case SW_GUIID_PRINT:
        m_frame->OnPrint(event);
        break;
    case SW_GUIID_PRINTPREVIEW:
        m_frame->OnPrintPreview(event);
        break;
    case SW_GUIID_PLAY:
        m_frame->OnPlay(event);
        break;
    case SW_GUIID_PAUSE:
        m_frame->OnPause(event);
        break;
    case SW_GUIID_STOP:
        m_frame->OnStop(event);
        break;
    case SW_GUIID_REWIND:
        m_frame->OnRewind(event);
        break;
    case SW_GUIID_FASTFORWARD:
        m_frame->OnFastForward(event);
        break;
    case SW_GUIID_PREVIOUS:
        m_frame->OnPrevious(event);
        break;
    case SW_GUIID_NEXT:
        m_frame->OnNext(event);
        break;
    }
}


SwAutoDefMenu::SwAutoDefMenu()
{
    m_richView = NULL;
}

SwAutoDefMenu::SwAutoDefMenu(SwRichTextCtrl * view)
{
    m_richView = view;
    Init();
}

SwAutoDefMenu::~SwAutoDefMenu()
{
}

void SwAutoDefMenu::Init()
{
    AddStockItem(SW_GUIID_COPY, true, false);
    AddStockItem(SW_GUIID_SELECTALL, true, false);
    AddStockItem(SW_GUIID_PRINT, true, true);
}

SwMenuItem * SwAutoDefMenu::AddStockItem(swUI8 swid, bool enabled, bool addSeparators)
{
    SwMenuItem * item = SwMenu::AddStockItem(swid, enabled, addSeparators);

    if (m_richView)
        Connect(SwGuiData::GetDataForItemSwId(swid)->wx_id, wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SwMenu::OnEvent);

    return item;
}

void SwAutoDefMenu::OnEvent(wxCommandEvent & event)
{
    if (!m_richView)
        return;

    swUI8 swid = SwGuiData::FindItemWxId(event.GetId());

    if (swid == NODE_ID_INVALID_8)
    {
        event.Skip();
        return;
    }

    switch (swid)
    {
    case SW_GUIID_COPY:
        m_richView->OnCopy(event);
        break;
    case SW_GUIID_SELECTALL:
        m_richView->OnSelectAll(event);
        break;
    case SW_GUIID_PRINT:
        m_richView->OnPrint(event);
        break;
    }
}
