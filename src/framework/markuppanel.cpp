///////////////////////////////////////////////////////////////////
// Name:        markuppanel.cpp
// Purpose:     Text markup.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/markuppanel.h"
#include "../../include/thml/thml_elements.h"
#include "../../include/swprjml/swprjmlparser.h"

SwDwellTimer::SwDwellTimer()
{
    m_panel = NULL;
    Start(100);
}

SwDwellTimer::~SwDwellTimer()
{
}

void SwDwellTimer::Notify()
{
    if (m_panel)
        m_panel->OnTimer();
}

const long SwMarkUpPanel::ID_THMLLISTCTRL = wxNewId();
const long SwMarkUpPanel::ID_HTMLLISTCTRL = wxNewId();
const long SwMarkUpPanel::ID_PRJMLLISTCTRL = wxNewId();
const long SwMarkUpPanel::ID_FINDREPLACEPANEL = wxNewId();
const long SwMarkUpPanel::ID_TOOLNOTEBOOK = wxNewId();
const long SwMarkUpPanel::ID_EDITORSTCTRL = wxNewId();
SwString SwMarkUpPanel::m_buffer;

SwMarkUpPanel::SwMarkUpPanel()
{
}

SwMarkUpPanel::SwMarkUpPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    BuildContent(parent,id,pos,size);
}

void SwMarkUpPanel::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_manager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);

    ToolNotebook = new wxNotebook(this, ID_TOOLNOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_TOP, L"ID_TOOLNOTEBOOK");
    ToolNotebook->SetBackgroundColour(*wxWHITE);
    ThMLListCtrl = new SwStretchColumnListCtrl(ToolNotebook, ID_THMLLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_THMLLISTCTRL");
    ThMLListCtrl->wxListCtrl::AppendColumn("");
    ToolNotebook->AddPage(ThMLListCtrl, L"ThML", false);
    HtmlListCtrl = new SwStretchColumnListCtrl(ToolNotebook, ID_HTMLLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_HTMLLISTCTRL");
    HtmlListCtrl->wxListCtrl::AppendColumn("");
    ToolNotebook->AddPage(HtmlListCtrl, L"Html", false);
    PrjMlListCtrl = new SwStretchColumnListCtrl(ToolNotebook, ID_PRJMLLISTCTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_PRJMLLISTCTRL");
    PrjMlListCtrl->wxListCtrl::AppendColumn("");
    ToolNotebook->AddPage(PrjMlListCtrl, L"SwPrjML", false);
    FindReplacePanel = new SwStcFindReplacePanel(ToolNotebook, ID_FINDREPLACEPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SEARCHPANEL");
    ToolNotebook->AddPage(FindReplacePanel, L"Find - Replace", false);
    m_manager->AddPane(ToolNotebook, wxAuiPaneInfo().Name(L"ToolBook").DefaultPane().CaptionVisible(false).CloseButton(false).Left().Floatable(false).MinSize(wxSize(200,-1)));
    EditorStCtrl = new wxStyledTextCtrl(this, ID_EDITORSTCTRL, wxDefaultPosition, wxDefaultSize, 0, L"ID_EDITORSTCTRL");
    m_manager->AddPane(EditorStCtrl, wxAuiPaneInfo().Name(L"View Pane").DefaultPane().CaptionVisible(false).Center().DockFixed().Floatable(false));
    m_manager->Update();

    SwThMLElements::GetThMLList(ThMLListCtrl);
    SwThMLElements::GetHtmlList(HtmlListCtrl);
    SwProjectMlParser::GetPrjMlList(PrjMlListCtrl);
    EditorStCtrl->SetLexer(wxSTC_LEX_HTML);

    EditorStCtrl->StyleSetForeground(wxSTC_H_TAG, wxColour(195,0,82));
    EditorStCtrl->StyleSetForeground(wxSTC_H_TAGEND, wxColour(195,0,82));
    EditorStCtrl->StyleSetForeground(wxSTC_H_TAGUNKNOWN, wxColour(195,0,82));
    EditorStCtrl->StyleSetForeground(wxSTC_H_VALUE, wxColour(0, 0, 139));
    EditorStCtrl->StyleSetForeground(wxSTC_H_ATTRIBUTE, wxColour(45,125,154));
    EditorStCtrl->StyleSetForeground(wxSTC_H_ATTRIBUTEUNKNOWN, wxColour(45,125,154));
    EditorStCtrl->StyleSetForeground(wxSTC_H_ENTITY, wxColour(0,128,0));

    EditorStCtrl->SetMouseDwellTime(300);
    m_initZoom = EditorStCtrl->GetZoom();

    m_autodefwindow = new SwAutoDefWindow(EditorStCtrl, wxNewId(), "", wxPoint(0,0), wxSize(0, 0));
    m_autodefwindow->Show(false);

    Connect(ID_EDITORSTCTRL,wxEVT_STC_DWELLSTART,(wxObjectEventFunction)&SwMarkUpPanel::OnMouseHoverStart);
    Connect(ID_THMLLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwMarkUpPanel::OnThMLItemSelect);
    Connect(ID_HTMLLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwMarkUpPanel::OnHtmlItemSelect);
    Connect(ID_PRJMLLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SwMarkUpPanel::OnPrjMlItemSelect);

    FindReplacePanel->SetStcCtrl(EditorStCtrl);
    m_timer.m_panel = this;
    OnLanguageChange();
}

SwMarkUpPanel::~SwMarkUpPanel()
{
    m_manager->UnInit();
}

void SwMarkUpPanel::OnThMLItemSelect(wxListEvent& event)
{
    SwString name;
    SwString attributes;
    SwString beginTag;
    SwString endTag;

    if (SwThMLElements::GetThMLElementData(event.GetData(), name, attributes))
    {
        CreateTags(name, attributes, beginTag, endTag);
        InsertTags(beginTag, endTag);
    }

    ThMLListCtrl->SetItemState(event.GetIndex(), 0, wxLIST_STATE_FOCUSED);
}

void SwMarkUpPanel::OnHtmlItemSelect(wxListEvent& event)
{
    SwString name;
    SwString attributes;
    SwString beginTag;
    SwString endTag;

    if (event.GetData() == THML_BR)
    {
        InsertTags("<br>", "");
    }
    else if (SwThMLElements::GetHtmlElementData(event.GetData(), name, attributes))
    {
        CreateTags(name, attributes, beginTag, endTag);
        InsertTags(beginTag, endTag);
    }

    HtmlListCtrl->SetItemState(event.GetIndex(), 0, wxLIST_STATE_FOCUSED);
}

void SwMarkUpPanel::OnPrjMlItemSelect(wxListEvent& event)
{
    SwString name;
    SwString attributes;
    SwString beginTag;
    SwString endTag;

    if (SwProjectMlParser::GetPrjMlElementData(event.GetData(), name, attributes))
    {
        CreateTags(name, attributes, beginTag, endTag);
        InsertTags(beginTag, endTag);
    }

    PrjMlListCtrl->SetItemState(event.GetIndex(), 0, wxLIST_STATE_FOCUSED);
}

void SwMarkUpPanel::CreateTags(const char * name, const char * attributes, SwString & beginTag, SwString & endTag)
{
    beginTag.Reset();
    endTag.Reset();

    if (!name || !attributes)
        return;

    if (EditorStCtrl->HasSelection())
    {
        beginTag = "<";
        beginTag += name;

        if (strlen(attributes))
        {
            beginTag += " ";
            beginTag += attributes;
        }

        beginTag += ">";

        endTag = "</";
        endTag += name;
        endTag += ">";
    }
    else
    {
        beginTag = "<";
        beginTag += name;

        if (strlen(attributes))
        {
            beginTag += " ";
            beginTag += attributes;
        }

        beginTag += "/>";
        endTag = "";
    }
}

void SwMarkUpPanel::InsertTags(const char * beginTag, const char * endTag)
{
    if (!beginTag || !endTag)
        return;

    long position = EditorStCtrl->GetInsertionPoint();
    int start, end;
    if (EditorStCtrl->HasSelection())
    {
        start = EditorStCtrl->GetSelectionStart();
        end = EditorStCtrl->GetSelectionEnd();
        EditorStCtrl->InsertText(end, endTag);
        EditorStCtrl->SetInsertionPoint(start);
        EditorStCtrl->InsertText(start, beginTag);
    }
    else
    {
        long caret = EditorStCtrl->GetCurrentPos();
        //EditorStCtrl->InsertText(caret, endTag);
        EditorStCtrl->InsertText(caret, beginTag);
    }

    EditorStCtrl->SetInsertionPoint(position);
}

void SwMarkUpPanel::OnMouseHoverStart(wxStyledTextEvent& event)
{
    if (m_autodefwindow && m_autodefwindow->IsShownOnScreen())
        return;
    int startPos, endPos, offSet;

    if (event.GetPosition() < 30)
    {
        offSet = event.GetPosition();
        startPos = 0;
    }
    else
    {
        offSet = 30;
        startPos = event.GetPosition() - 30;
    }

    endPos = startPos + 60;

    if (endPos >= EditorStCtrl->GetLength())
        endPos = EditorStCtrl->GetLength() - 1;

    SwString data;
    data = EditorStCtrl->GetTextRange(startPos, endPos).utf8_str();

    if (!ParseText(data, offSet))
        return;

    bool canCopy;

    if (data.Strlen() && SwApplicationInterface::GetModuleManager().GetAutoDefData(m_buffer, data, canCopy))
    {
        int line = EditorStCtrl->LineFromPosition(event.GetPosition());
        int height = EditorStCtrl->TextHeight(line);
        wxPoint pt = EditorStCtrl->PointFromPosition(event.GetPosition());
        m_autodefwindow->Reset();
        m_autodefwindow->WriteXmlText(m_buffer, true, "");
        m_autodefwindow->ShowAutoDef(pt.y - 1, pt.y + height + 1);
    }
}

int SwMarkUpPanel::ParseText(SwString & data, int nOffSet)
{
    if (nOffSet >= data.Strlen())
        return 0;

    int nCnt = nOffSet;

    for(;;)
    {
        if (data[nCnt] != '.' && !isalnum(data[nCnt]))
        {
            data[nCnt] = '\0';
            break;
        }

        nCnt ++;
    }

    nCnt = nOffSet;

    for(;;)
    {
        if (nCnt < 0)
            break;

        if (data[nCnt] != '.' && !isalnum(data[nCnt]))
        {
            data.Delete(0, nCnt + 1);
            break;
        }

        nCnt --;
    }

    return data.Strlen();
}

bool SwMarkUpPanel::OnOpen()
{
    SwString path;

    if (EditorStCtrl->IsModified())
    {
        if (!OnClose())
            return false;
    }

    EditorStCtrl->Clear();

    if (SwDialog::SelectHtmlThMLFile(this, path, "") && EditorStCtrl->LoadFile(path.GetArray(), wxRICHTEXT_TYPE_TEXT))
    {
        m_path = path;
        return true;
    }

    return false;
}

bool SwMarkUpPanel::OnSave()
{
    bool status = EditorStCtrl->SaveFile(m_path.GetArray());

    if (status)
        EditorStCtrl->SetModified(false);

    return status;
}

bool SwMarkUpPanel::OnSaveAs()
{
    SwString path;

    bool status = SwDialog::SaveAsHtmlThMLFile(this, path, NULL);

    if (status)
        status = EditorStCtrl->SaveFile(path.GetArray());

    if (status)
    {
        EditorStCtrl->SetModified(false);
        m_path = path;

        int sel = SwApplicationInterface::GetFrameWindow()->GetToolBook()->GetSelection();
        SwApplicationInterface::GetFrameWindow()->GetToolBook()->SetPageText(sel, m_path.GetArray());
        SwApplicationInterface::GetFrameWindow()->AddToRecentFileList(m_path);
    }

    return status;
}

bool SwMarkUpPanel::OnClose()
{
    if (EditorStCtrl->IsModified())
    {
        int result = SwDialog::RequestSave(this);

        if (result == wxCANCEL)
            return false;
        if (result == wxNO)
            return true;
        if (m_path.Strlen())
            return EditorStCtrl->SaveFile(m_path.GetArray());
        else
            return OnSaveAs();
    }

    return true;
}

bool SwMarkUpPanel::OnCut()
{

    EditorStCtrl->Cut();

    return true;
}

bool SwMarkUpPanel::OnCopy()
{
    EditorStCtrl->Copy();

    return true;
}

bool SwMarkUpPanel::OnPaste()
{
    EditorStCtrl->Paste();

    return true;
}

bool SwMarkUpPanel::OnUndo()
{
    EditorStCtrl->Undo();

    return true;
}

bool SwMarkUpPanel::OnRedo()
{
    EditorStCtrl->Redo();

    return true;
}

bool SwMarkUpPanel::OnSelectAll()
{
    EditorStCtrl->SelectAll();

    return true;
}

bool SwMarkUpPanel::OnZoomIn()
{
    EditorStCtrl->SetZoom(EditorStCtrl->GetZoom() + 1);

    return true;
}

bool SwMarkUpPanel::OnZoomOut()
{
    EditorStCtrl->SetZoom(EditorStCtrl->GetZoom() - 1);

    return true;
}

bool SwMarkUpPanel::OnViewNormal()
{
    EditorStCtrl->SetZoom(m_initZoom);

    return true;
}

void SwMarkUpPanel::OnLanguageChange()
{
    ToolNotebook->SetPageText(0, SwApplicationInterface::GetControlString("SID_ThML", L"ThML"));
    ToolNotebook->SetPageText(1, SwApplicationInterface::GetControlString("SID_HTML", L"Html"));
    ToolNotebook->SetPageText(2, SwApplicationInterface::GetControlString("SID_SWPRJML", L"SwPrjML"));
    ToolNotebook->SetPageText(3, SwApplicationInterface::GetControlString("SID_FIND-REPLACE", L"Find - Replace"));
}

bool SwMarkUpPanel::OnHasFocus()
{
    return EditorStCtrl->HasFocus();
}

bool SwMarkUpPanel::OnHasSelection()
{
    return EditorStCtrl->HasSelection();
}

bool SwMarkUpPanel::OnClosePanel()
{
    return OnClose();
}

bool SwMarkUpPanel::OnCanDoSave()
{
    return (bool) m_path.Strlen();
}

bool SwMarkUpPanel::OnCanDoSaveAs()
{
    return true;
}

bool SwMarkUpPanel::OnCanDoClose()
{
    return true;
}

bool SwMarkUpPanel::OnCanDoCut()
{
    return EditorStCtrl->HasSelection();
}

bool SwMarkUpPanel::OnCanDoCopy()
{
    return EditorStCtrl->HasSelection();
}

bool SwMarkUpPanel::OnCanDoPaste()
{
    return true;
}

bool SwMarkUpPanel::OnCanDoUndo()
{
    return EditorStCtrl->CanUndo();
}

bool SwMarkUpPanel::OnCanDoRedo()
{
    return EditorStCtrl->CanRedo();
}

bool SwMarkUpPanel::OnCanDoZoomIn()
{
    if (EditorStCtrl->GetZoom() < m_initZoom + 10)
        return true;

    return false;
}

bool SwMarkUpPanel::OnCanDoZoomOut()
{
    if (EditorStCtrl->GetZoom() > m_initZoom - 10)
        return true;

    return false;
}

bool SwMarkUpPanel::OnCanDoViewNormal()
{
    if (EditorStCtrl->GetZoom() != m_initZoom)
        return true;

    return false;
}

const char * SwMarkUpPanel::GetFilePath()
{
    return m_path;
}

bool SwMarkUpPanel::HasFile(const char * path)
{
    if (!path)
        return false;

    if (stricmp(path, m_path) == 0)
        return true;

    return false;
}

bool SwMarkUpPanel::OpenFile(const char * path)
{
    EditorStCtrl->ClearAll();
    m_path = "";

    if (!path)
        return false;

    bool status = EditorStCtrl->LoadFile(path, wxRICHTEXT_TYPE_TEXT);
    if (status)
        m_path = path;

    return status;
}

void SwMarkUpPanel::OnTimer()
{
    int caretPos = EditorStCtrl->GetCurrentPos();
    if (caretPos != m_caretPos)
    {
        m_mouseCount = 0;
        m_caretPos = caretPos;
        m_autodefwindow->Hide();
        return;
    }
}

const long SwStcFindReplacePanel::ID_FINDSTATICTEXT = wxNewId();
const long SwStcFindReplacePanel::ID_FINDTEXTCTRL = wxNewId();
const long SwStcFindReplacePanel::ID_FINDCASECHECKBOX = wxNewId();
const long SwStcFindReplacePanel::ID_FINDWORDCHECKBOX = wxNewId();
const long SwStcFindReplacePanel::ID_REPLACESTATICTEXT = wxNewId();
const long SwStcFindReplacePanel::ID_REPLACETEXTCTRL = wxNewId();
const long SwStcFindReplacePanel::ID_FINDBUTTON = wxNewId();
const long SwStcFindReplacePanel::ID_FINDNEXTBUTTON = wxNewId();
const long SwStcFindReplacePanel::ID_REPLACEBUTTON = wxNewId();
const long SwStcFindReplacePanel::ID_REPLACEALLBUTTON = wxNewId();

SwStcFindReplacePanel::SwStcFindReplacePanel()
{
}

SwStcFindReplacePanel::~SwStcFindReplacePanel()
{
}

SwStcFindReplacePanel::SwStcFindReplacePanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    CreateGui();
}

void SwStcFindReplacePanel::Reset()
{
}

void SwStcFindReplacePanel::CreateGui()
{
    wxBoxSizer* ButtonBoxSizer, * ButtonBoxSizer2;
    FindGridSizer = new wxGridBagSizer(0, 0);
    ButtonBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    ButtonBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    FindStaticText = new wxStaticText(this, ID_FINDSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, L"ID_FINDSTATICTEXT");
    FindGridSizer->Add(FindStaticText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindTextCtrl = new SwStretchTextCtrl(this, ID_FINDTEXTCTRL, L"", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDTEXTCTRL");
    FindGridSizer->Add(FindTextCtrl, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    ReplaceStaticText = new wxStaticText(this, ID_REPLACESTATICTEXT, L"Replace With:", wxDefaultPosition, wxDefaultSize, 0, L"ID_FINDSTATICTEXT");
    FindGridSizer->Add(ReplaceStaticText, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ReplaceTextCtrl = new SwStretchTextCtrl(this, ID_REPLACETEXTCTRL, L"", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDTEXTCTRL");
    FindGridSizer->Add(ReplaceTextCtrl, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    FindCaseCheckBox = new SwCheckBox(this, ID_FINDCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDCASECHECKBOX");
    FindCaseCheckBox->SetValue(false);
    FindGridSizer->Add(FindCaseCheckBox, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindWordCheckBox = new SwCheckBox(this, ID_FINDWORDCHECKBOX, L"Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDWORDCHECKBOX");
    FindWordCheckBox->SetValue(false);
    FindGridSizer->Add(FindWordCheckBox, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindButton = new wxButton(this, ID_FINDBUTTON, L"Find", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDBUTTON");
    ButtonBoxSizer->Add(FindButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindNextButton = new wxButton(this, ID_FINDNEXTBUTTON, L"Find Next", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDNEXTBUTTON");
    ButtonBoxSizer->Add(FindNextButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindGridSizer->Add(ButtonBoxSizer, wxGBPosition(6, 0), wxDefaultSpan, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    ReplaceButton = new wxButton(this, ID_REPLACEBUTTON, L"Replace", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_REPLACEBUTTON");
    ButtonBoxSizer2->Add(ReplaceButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ReplaceAllButton = new wxButton(this, ID_REPLACEALLBUTTON, L"Replace All", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_REPLACEALLBUTTON");
    ButtonBoxSizer2->Add(ReplaceAllButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindGridSizer->Add(ButtonBoxSizer2, wxGBPosition(7, 0), wxDefaultSpan, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(FindGridSizer);
    FindGridSizer->Fit(this);
    FindGridSizer->SetSizeHints(this);
    OnLanguageChange();

    Connect(ID_FINDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwStcFindReplacePanel::OnFindButtonClick);
    Connect(ID_FINDNEXTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwStcFindReplacePanel::OnFindNextButtonClick);
    Connect(ID_REPLACEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwStcFindReplacePanel::OnReplaceButtonClick);
    Connect(ID_REPLACEALLBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwStcFindReplacePanel::OnReplaceAllButtonClick);
}

void SwStcFindReplacePanel::SetStcCtrl(wxStyledTextCtrl * stc)
{
    m_stc = stc;
}

void SwStcFindReplacePanel::OnLanguageChange()
{
    FindStaticText->SetLabel(SwApplicationInterface::GetControlString("SID_SEARCHFOR", L"Search For:"));
    FindCaseCheckBox->SetLabel(SwApplicationInterface::GetControlString("SID_CASESENSITIVE", L"Case Sensitive"));
    FindWordCheckBox->SetLabel(SwApplicationInterface::GetControlString("SID_WHOLEWORD", L"Whole Word"));
    FindButton->SetLabel(SwApplicationInterface::GetControlString("SID_FIND", L"Find"));
    FindNextButton->SetLabel(SwApplicationInterface::GetControlString("SID_FINDNEXT", L"Find Next"));
    ReplaceStaticText->SetLabel(SwApplicationInterface::GetControlString("SID_REPLACEWITH", L"Replace With:"));
    ReplaceButton->SetLabel(SwApplicationInterface::GetControlString("SID_REPLACE", L"Replace"));
    ReplaceAllButton->SetLabel(SwApplicationInterface::GetControlString("SID_REPLACEALL", L"Replace All"));
}

void SwStcFindReplacePanel::OnThemeChange()
{
}

void SwStcFindReplacePanel::OnFindButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    int flags = 0;
    if (FindWordCheckBox->IsChecked())
        flags |= wxSTC_FIND_WHOLEWORD;
    if (FindCaseCheckBox->IsChecked())
        flags |= wxSTC_FIND_MATCHCASE;

    int wordLen = FindTextCtrl->GetValue().Len();
    int end;

    int start = m_stc->FindText(0, m_stc->GetLength(), FindTextCtrl->GetValue(), flags);
    if (start != wxSTC_INVALID_POSITION)
    {
        end = start + wordLen;
        m_stc->SetSelectionStart(start);
        m_stc->SetSelectionEnd(end);
        m_stc->EnsureCaretVisible();
    }
}

void SwStcFindReplacePanel::OnFindNextButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    int flags = 0;
    if (FindWordCheckBox->IsChecked())
        flags |= wxSTC_FIND_WHOLEWORD;
    if (FindCaseCheckBox->IsChecked())
        flags |= wxSTC_FIND_MATCHCASE;

    int wordLen = FindTextCtrl->GetValue().Len();
    int end;

    int start = m_stc->FindText(m_stc->GetCurrentPos(), m_stc->GetLength(), FindTextCtrl->GetValue(), flags);
    if (start != wxSTC_INVALID_POSITION)
    {
        end = start + wordLen;
        m_stc->SetSelectionStart(start);
        m_stc->SetSelectionEnd(end);
        m_stc->EnsureCaretVisible();
    }
}

void SwStcFindReplacePanel::OnReplaceButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    int flags = 0;
    if (FindWordCheckBox->IsChecked())
        flags |= wxSTC_FIND_WHOLEWORD;
    if (FindCaseCheckBox->IsChecked())
        flags |= wxSTC_FIND_MATCHCASE;

    int wordLen = FindTextCtrl->GetValue().Len();
    int end;

    int start = m_stc->FindText(m_stc->GetCurrentPos(), m_stc->GetLength(), FindTextCtrl->GetValue(), flags);
    if (start != wxSTC_INVALID_POSITION)
    {
        end = start + wordLen;
        m_stc->SetSelectionStart(start);
        m_stc->SetSelectionEnd(end);
        m_stc->WriteText(FindTextCtrl->GetValue());
        m_stc->EnsureCaretVisible();
        m_stc->SetSelectionEnd(start);
    }
}

void SwStcFindReplacePanel::OnReplaceAllButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    wxString value = FindTextCtrl->GetValue();

    if (value.Cmp(ReplaceTextCtrl->GetValue()) == 0)
        return;

    int flags = 0;
    if (FindWordCheckBox->IsChecked())
        flags |= wxSTC_FIND_WHOLEWORD;
    if (FindCaseCheckBox->IsChecked())
        flags |= wxSTC_FIND_MATCHCASE;

    m_stc->GotoPos(0);

    int wordLen = FindTextCtrl->GetValue().Len();
    int start = 0, end;

    for(;;)
    {
        start = m_stc->FindText(m_stc->GetCurrentPos(), m_stc->GetLength(), value, flags);
        if (start == wxSTC_INVALID_POSITION)
            break;
        end = start + wordLen;
        m_stc->SetSelectionStart(start);
        m_stc->SetSelectionEnd(end);
        m_stc->WriteText(ReplaceTextCtrl->GetValue());
        m_stc->EnsureCaretVisible();
    }

    m_stc->SetSelectionStart(0);
    m_stc->SetSelectionEnd(0);
}
