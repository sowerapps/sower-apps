///////////////////////////////////////////////////////////////////
// Name:        find.h
// Purpose:     Find panel for SowerViewPanels.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/findpanel.h"
#include "../../include/appi/appifa.h"

const long SwFindPanel::ID_FINDSTATICTEXT = wxNewId();
const long SwFindPanel::ID_FINDTEXTCTRL = wxNewId();
const long SwFindPanel::ID_FINDCASECHECKBOX = wxNewId();
const long SwFindPanel::ID_FINDWORDCHECKBOX = wxNewId();
const long SwFindPanel::ID_FINDBUTTON = wxNewId();

SwFindPanel::SwFindPanel()
{
    m_book = NULL;
}

SwFindPanel::~SwFindPanel()
{
}

SwFindPanel::SwFindPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    m_book = NULL;
    CreateGui();
}

void SwFindPanel::Reset()
{
    m_first = true;

    if (m_book)
        m_book->OnFindReset();
}

void SwFindPanel::CreateGui()
{
    FindGridSizer = new wxGridBagSizer(0, 0);
    FindStaticText = new SwStaticText(this, ID_FINDSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, L"SID_SEARCHFOR");
    FindGridSizer->Add(FindStaticText, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindTextCtrl = new SwStretchTextCtrl(this, ID_FINDTEXTCTRL, L"", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDTEXTCTRL");
    FindGridSizer->Add(FindTextCtrl, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindCaseCheckBox = new SwCheckBox(this, ID_FINDCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_CASESENSITIVE");
    FindCaseCheckBox->SetValue(false);
    FindGridSizer->Add(FindCaseCheckBox, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindWordCheckBox = new SwCheckBox(this, ID_FINDWORDCHECKBOX, L"Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_WHOLEWORD");
    FindWordCheckBox->SetValue(false);
    FindGridSizer->Add(FindWordCheckBox, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindButton = new SwButton(this, ID_FINDBUTTON, L"Find", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"SID_FIND");
    FindGridSizer->Add(FindButton, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FindGridSizer);
    FindGridSizer->Fit(this);
    FindGridSizer->SetSizeHints(this);

    Connect(ID_FINDTEXTCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SwFindPanel::OnFindTextCtrlText);
    Connect(ID_FINDCASECHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SwFindPanel::OnFindCaseCheckBoxClick);
    Connect(ID_FINDWORDCHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SwFindPanel::OnFindWordCheckBoxClick);
    Connect(ID_FINDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwFindPanel::OnFindButtonClick);
}

void SwFindPanel::SetViewBook(SwViewBook * book)
{
    m_book = book;
    m_panel = NULL;
}

void SwFindPanel::SetPanel(SwPanel * panel)
{
    m_panel = NULL;
    m_book = NULL;
}

void SwFindPanel::OnLanguageChange()
{
}

void SwFindPanel::OnThemeChange()
{
}

void SwFindPanel::OnFindTextCtrlText(wxCommandEvent& event)
{
    m_first = true;
}

void SwFindPanel::OnFindCaseCheckBoxClick(wxCommandEvent& event)
{
    if (m_book)
        m_book->OnFindSetCaseSensitive(FindCaseCheckBox->GetValue());

    if (m_panel)
        m_panel->OnFindSetCaseSensitive(FindCaseCheckBox->GetValue());
}

void SwFindPanel::OnFindWordCheckBoxClick(wxCommandEvent& event)
{
    if (m_book)
        m_book->OnFindSetWholeWordOnly(FindWordCheckBox->GetValue());

    if (m_panel)
        m_panel->OnFindSetWholeWordOnly(FindWordCheckBox->GetValue());
}

void SwFindPanel::OnFindButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    if (m_book)
    {
        if (m_first)
        {
            m_first = false;

            if (m_book->OnFind(FindTextCtrl->GetValue().wchar_str(), FindCaseCheckBox->GetValue(), FindWordCheckBox->GetValue()))
                m_first = false;
        }
        else
        {
            if (!m_book->OnFindNext())
                m_first = true;
        }
    }

    if (m_panel)
    {
        if (m_first)
        {
            m_first = false;

            if (m_panel->OnFind(FindTextCtrl->GetValue().wchar_str(), FindCaseCheckBox->GetValue(), FindWordCheckBox->GetValue()))
                m_first = false;
        }
        else
        {
            if (!m_panel->OnFindNext())
                m_first = true;
        }
    }
}


const long SwFindReplacePanel::ID_FINDSTATICTEXT = wxNewId();
const long SwFindReplacePanel::ID_FINDTEXTCTRL = wxNewId();
const long SwFindReplacePanel::ID_FINDCASECHECKBOX = wxNewId();
const long SwFindReplacePanel::ID_FINDWORDCHECKBOX = wxNewId();
const long SwFindReplacePanel::ID_REPLACESTATICTEXT = wxNewId();
const long SwFindReplacePanel::ID_REPLACETEXTCTRL = wxNewId();
const long SwFindReplacePanel::ID_FINDBUTTON = wxNewId();
const long SwFindReplacePanel::ID_REPLACEBUTTON = wxNewId();
const long SwFindReplacePanel::ID_REPLACEALLBUTTON = wxNewId();

SwFindReplacePanel::SwFindReplacePanel()
{
}

SwFindReplacePanel::~SwFindReplacePanel()
{
}

SwFindReplacePanel::SwFindReplacePanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :SwPanel(parent, id, pos, size, style, name)
{
    CreateGui();
}

void SwFindReplacePanel::Reset()
{
    m_findreplace.Reset();
    m_first = true;
}

void SwFindReplacePanel::CreateGui()
{
    wxBoxSizer* ButtonBoxSizer;
    FindGridSizer = new wxGridBagSizer(0, 0);
    ButtonBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	FindStaticText = new wxStaticText(this, ID_FINDSTATICTEXT, L"Search For:", wxDefaultPosition, wxDefaultSize, 0, _T("ID_FINDSTATICTEXT"));
	FindGridSizer->Add(FindStaticText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FindTextCtrl = new SwStretchTextCtrl(this, ID_FINDTEXTCTRL, L"", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDTEXTCTRL"));
	FindGridSizer->Add(FindTextCtrl, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	ReplaceStaticText = new wxStaticText(this, ID_REPLACESTATICTEXT, L"Replace With:", wxDefaultPosition, wxDefaultSize, 0, _T("ID_FINDSTATICTEXT"));
	FindGridSizer->Add(ReplaceStaticText, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ReplaceTextCtrl = new SwStretchTextCtrl(this, ID_REPLACETEXTCTRL, L"", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDTEXTCTRL"));
	FindGridSizer->Add(ReplaceTextCtrl, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	FindCaseCheckBox = new SwCheckBox(this, ID_FINDCASECHECKBOX, L"Case Sensitive", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDCASECHECKBOX"));
	FindCaseCheckBox->SetValue(false);
	FindGridSizer->Add(FindCaseCheckBox, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FindWordCheckBox = new SwCheckBox(this, ID_FINDWORDCHECKBOX, L"Whole Word", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDWORDCHECKBOX"));
	FindWordCheckBox->SetValue(false);
	FindGridSizer->Add(FindWordCheckBox, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FindButton = new wxButton(this, ID_FINDBUTTON, L"Find", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDBUTTON"));
	ButtonBoxSizer->Add(FindButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ReplaceButton = new wxButton(this, ID_REPLACEBUTTON, L"Replace", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDBUTTON"));
	ButtonBoxSizer->Add(ReplaceButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	ReplaceAllButton = new wxButton(this, ID_REPLACEALLBUTTON, L"Replace All", wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_FINDBUTTON"));
	ButtonBoxSizer->Add(ReplaceAllButton, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FindGridSizer->Add(ButtonBoxSizer, wxGBPosition(6, 0), wxDefaultSpan, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	SetSizer(FindGridSizer);
	FindGridSizer->Fit(this);
	FindGridSizer->SetSizeHints(this);
	OnLanguageChange();

	Connect(ID_FINDTEXTCTRL,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SwFindReplacePanel::OnFindTextCtrlText);
	Connect(ID_FINDCASECHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SwFindReplacePanel::OnFindCaseCheckBoxClick);
	Connect(ID_FINDWORDCHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SwFindReplacePanel::OnFindWordCheckBoxClick);
	Connect(ID_FINDBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwFindReplacePanel::OnFindButtonClick);
	Connect(ID_REPLACEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwFindReplacePanel::OnReplaceButtonClick);
	Connect(ID_REPLACEALLBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwFindReplacePanel::OnReplaceAllButtonClick);
}

void SwFindReplacePanel::SetRichTxtCtrl(wxRichTextCtrl * rich)
{
    m_findreplace.SetParent(rich);
}

void SwFindReplacePanel::OnLanguageChange()
{
    FindStaticText->SetLabel(SwApplicationInterface::GetControlString("SID_SEARCHFOR", L"Search For:"));
    FindCaseCheckBox->SetLabel(SwApplicationInterface::GetControlString("SID_CASESENSITIVE", L"Case Sensitive"));
    FindWordCheckBox->SetLabel(SwApplicationInterface::GetControlString("SID_WHOLEWORD", L"Whole Word"));
    FindButton->SetLabel(SwApplicationInterface::GetControlString("SID_FIND", L"Find"));
    ReplaceStaticText->SetLabel(SwApplicationInterface::GetControlString("SID_REPLACEWITH", L"Replace With:"));
    ReplaceButton->SetLabel(SwApplicationInterface::GetControlString("SID_REPLACE", L"Replace"));
    ReplaceAllButton->SetLabel(SwApplicationInterface::GetControlString("SID_REPLACEALL", L"Replace All"));
}

void SwFindReplacePanel::OnThemeChange()
{
}

void SwFindReplacePanel::OnFindTextCtrlText(wxCommandEvent& event)
{
    m_first = true;
}

void SwFindReplacePanel::OnFindCaseCheckBoxClick(wxCommandEvent& event)
{
    m_findreplace.SetCaseSensitive(FindCaseCheckBox->GetValue());
}

void SwFindReplacePanel::OnFindWordCheckBoxClick(wxCommandEvent& event)
{
    m_findreplace.SetWholeWordOnly(FindWordCheckBox->GetValue());
}

void SwFindReplacePanel::OnFindButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    if (m_first)
    {
        m_first = false;
        m_findreplace.Reset();
        m_findreplace.SetFindText(FindTextCtrl->GetValue());
        m_findreplace.IterateBuffer();
    }
    else
    {
        if (!m_findreplace.FindNext())
            m_first = true;
    }
}

void SwFindReplacePanel::OnReplaceButtonClick(wxCommandEvent& event)
{
    m_findreplace.Replace();
    m_findreplace.FindNext();
}

void SwFindReplacePanel::OnReplaceAllButtonClick(wxCommandEvent& event)
{
    if (!FindTextCtrl->GetLineLength(0))
        return;

    m_findreplace.Reset();
    m_findreplace.SetFindText(FindTextCtrl->GetValue());
    m_findreplace.SetReplaceText(ReplaceTextCtrl->GetValue());
    m_findreplace.ReplaceAll();
}
