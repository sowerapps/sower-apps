///////////////////////////////////////////////////////////////////
// Name:        carddlg.cpp
// Purpose:     SwCatalogCardDlg
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/carddlg.h"
#include "../../include/appi/appifa.h"
#include "../../include/module/category.h"
#include "../../include/thml/thml_utility.h"
#include "../../include/filesys/file.h"
#include "../../include/bible/standard_bible.h"

const long SwCatalogCardDlg::ID_TITLELABEL = wxNewId();
const long SwCatalogCardDlg::ID_ABBREVIATIONLABEL = wxNewId();
const long SwCatalogCardDlg::ID_IDENTIFIERLABEL = wxNewId();
const long SwCatalogCardDlg::ID_TITLETEXTCTRL = wxNewId();
const long SwCatalogCardDlg::ID_ABBREVIATIONTEXTCTRL = wxNewId();
const long SwCatalogCardDlg::ID_IDENTIFIERTEXTCTRL = wxNewId();
const long SwCatalogCardDlg::ID_CATEGORYLABEL = wxNewId();
const long SwCatalogCardDlg::ID_GROUPLABEL = wxNewId();
const long SwCatalogCardDlg::ID_VERSIFICATIONLABEL = wxNewId();
const long SwCatalogCardDlg::ID_CATEGORYCHOICE = wxNewId();
const long SwCatalogCardDlg::ID_GROUPCOMBOBOX = wxNewId();
const long SwCatalogCardDlg::ID_VERSIFICATIONCOMBOBOX = wxNewId();
const long SwCatalogCardDlg::ID_ALLOWCOPYCHECKBOX = wxNewId();
const long SwCatalogCardDlg::ID_OFNLABEL = wxNewId();
const long SwCatalogCardDlg::ID_ENCRYPTCHECKBOX = wxNewId();
const long SwCatalogCardDlg::ID_OFNTEXTCTRL = wxNewId();
const long SwCatalogCardDlg::ID_PUBLISHERLABEL = wxNewId();
const long SwCatalogCardDlg::ID_PUBLISHERTEXTCTRL = wxNewId();
const long SwCatalogCardDlg::ID_REPORTTEXTCTRL = wxNewId();
const long SwCatalogCardDlg::ID_OKBUTTON = wxNewId();
const long SwCatalogCardDlg::ID_CANCELBUTTON = wxNewId();
const long SwCatalogCardDlg::ID_STOPBUTTON = wxNewId();

SwCatalogCardDlg::SwCatalogCardDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
    :SwDialog(parent, id, "", pos, size, wxDEFAULT_DIALOG_STYLE, "")
{
    m_card = NULL;
    m_catalog = NULL;
    wxGridBagSizer* GridBagSizer1, * GridBagSizer2;
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    GridBagSizer2 = new wxGridBagSizer(0, 0);
    TitleLabel = new wxStaticText(this, ID_TITLELABEL, SwApplicationInterface::GetControlString("SID_TITLE", L"Title"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
    GridBagSizer1->Add(TitleLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    AbbreviationLabel = new wxStaticText(this, ID_ABBREVIATIONLABEL, SwApplicationInterface::GetControlString("SID_ABBREVIATION", L"Abbreviation"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ABBREVIATIONLABEL");
    GridBagSizer1->Add(AbbreviationLabel, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdentifierLabel = new wxStaticText(this, ID_IDENTIFIERLABEL, SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERLABEL");
    GridBagSizer1->Add(IdentifierLabel, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TitleTextCtrl = new wxTextCtrl(this, ID_TITLETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_TITLETEXTCTRL");
    GridBagSizer1->Add(TitleTextCtrl, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    AbbreviationTextCtrl = new wxTextCtrl(this, ID_ABBREVIATIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ABBREVIATIONTEXTCTRL");
    GridBagSizer1->Add(AbbreviationTextCtrl, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
    IdentifierTextCtrl = new wxTextCtrl(this, ID_IDENTIFIERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_IDENTIFIERTEXTCTRL");
    GridBagSizer1->Add(IdentifierTextCtrl, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxEXPAND, 5);
    CategoryLabel = new wxStaticText(this, ID_CATEGORYLABEL, SwApplicationInterface::GetControlString("SID_CATEGORY", L"Category"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CATEGORYLABEL");
    GridBagSizer1->Add(CategoryLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GroupLabel = new wxStaticText(this, ID_GROUPLABEL, SwApplicationInterface::GetControlString("SID_GROUP", L"Group"), wxDefaultPosition, wxDefaultSize, 0, L"ID_GROUPLABEL");
    GridBagSizer1->Add(GroupLabel, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    VersificationLabel = new wxStaticText(this, ID_VERSIFICATIONLABEL, SwApplicationInterface::GetControlString("SID_VERSIFICATION", L"Versification"), wxDefaultPosition, wxDefaultSize, 0, L"ID_VERSIFICATIONLABEL");
    GridBagSizer1->Add(VersificationLabel, wxGBPosition(2, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CategoryChoice = new wxChoice(this, ID_CATEGORYCHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_CATEGORYCHOICE");
    SwCategory::FillCtrl(CategoryChoice);
    GridBagSizer1->Add(CategoryChoice, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    GroupComboBox = new wxComboBox(this, ID_GROUPCOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_GROUPCOMBOBOX");
    SwApplicationInterface::GetGroupList(GroupComboBox);
    GridBagSizer1->Add(GroupComboBox, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
    VersificationComboBox = new wxComboBox(this, ID_VERSIFICATIONCOMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_VERSIFICATIONCOMBOBOX");
    GridBagSizer1->Add(VersificationComboBox, wxGBPosition(3, 2), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SwStandardBible::FillCtrl(VersificationComboBox);
    PublisherLabel = new wxStaticText(this, ID_PUBLISHERLABEL, SwApplicationInterface::GetControlString("SID_PUBLISHER", L"Publisher"), wxDefaultPosition, wxDefaultSize, 0, L"ID_PASSWORDLABEL");
    GridBagSizer1->Add(PublisherLabel, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    OfnLabel = new wxStaticText(this, ID_OFNLABEL, SwApplicationInterface::GetControlString("SID_ORIGINALFILENAME", L"Original File Name"), wxDefaultPosition, wxDefaultSize, 0, L"ID_STATICTEXT9");
    GridBagSizer1->Add(OfnLabel, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PublisherTextCtrl = new wxTextCtrl(this, ID_PUBLISHERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PASSWORDTEXTCTRL");
    GridBagSizer1->Add(PublisherTextCtrl, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    OfnTextCtrl = new wxTextCtrl(this, ID_OFNTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_OFNTEXTCTRL");
    GridBagSizer1->Add(OfnTextCtrl, wxGBPosition(5, 1), wxGBSpan(1, 1), wxALL|wxEXPAND, 5);
    AllowCopyCheckBox = new SwCheckBox(this, ID_ALLOWCOPYCHECKBOX, SwApplicationInterface::GetControlString("SID_ALLOWCOPY", L"Allow Copy"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ALLOWCOPYCHECKBOX");
    AllowCopyCheckBox->SetValue(false);
    GridBagSizer1->Add(AllowCopyCheckBox, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    EncryptCheckBox = new SwCheckBox(this, ID_ENCRYPTCHECKBOX, SwApplicationInterface::GetControlString("SID_ENCRYPT", L"Encrypt"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ENCRYPTCHECKBOX");
    EncryptCheckBox->SetValue(false);
    GridBagSizer1->Add(EncryptCheckBox, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ReportTextCtrl = new wxTextCtrl(this, ID_REPORTTEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(-1,100), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, L"ID_REPORTTEXTCTRL");
    GridBagSizer1->Add(ReportTextCtrl, wxGBPosition(6, 0), wxGBSpan(1, 3), wxALL|wxEXPAND, 5);
    OkButton = new wxButton(this, ID_OKBUTTON, SwApplicationInterface::GetControlString("SID_OK", L"OK"));
    GridBagSizer2->Add(OkButton, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    CancelButton = new wxButton(this, ID_CANCELBUTTON, SwApplicationInterface::GetControlString("SID_SKIP", L"Skip"));
    GridBagSizer2->Add(CancelButton, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    StopButton = new wxButton(this, ID_STOPBUTTON, SwApplicationInterface::GetControlString("SID_STOP", L"Stop"));
    GridBagSizer2->Add(StopButton, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL, 5);
    GridBagSizer1->Add(GridBagSizer2, wxGBPosition(7, 0), wxGBSpan(1, 3), wxALL|wxALIGN_CENTER|wxEXPAND, 5);

    AllowCopyCheckBox->SetValue(true);
    EncryptCheckBox->Enable(true);
    AllowCopyCheckBox->Enable(true);
    VersificationComboBox->SetValue("KJV");

    SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwCatalogCardDlg::OnQuit);
    Connect(ID_OKBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwCatalogCardDlg::OnOkButtonClick);
    Connect(ID_STOPBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwCatalogCardDlg::OnStopButtonClick);
    Connect(ID_CANCELBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwCatalogCardDlg::OnQuit);

    SetLabel(SwApplicationInterface::GetControlString("SID_CATALOGCARD", L"Catalog Card"));
    SetIcon(SwApplicationInterface::GetIcon("SID_INFORMATION"));
}

SwCatalogCardDlg::~SwCatalogCardDlg()
{

}

void SwCatalogCardDlg::SetCard(SwCatalogCard * card)
{
    if (!card)
        return;

    SwStringW buffer;
    buffer.Copy(card->GetTitle());
    TitleTextCtrl->SetValue(buffer.GetArray());
    buffer.Copy(card->GetAbbreviation());
    AbbreviationTextCtrl->SetValue(buffer.GetArray());
    buffer.Copy(card->GetIdentifier());
    IdentifierTextCtrl->SetValue(buffer.GetArray());
    SwCategory::SetCategory(CategoryChoice, card->GetCategory());
    buffer.Copy(card->GetGroup());
    GroupComboBox->SetValue(buffer.GetArray());
    buffer.Copy(card->GetVersification());
    VersificationComboBox->SetValue(buffer.GetArray());
    buffer.Copy(card->GetCcelFileName());
    OfnTextCtrl->SetValue(buffer.GetArray());
    buffer.Copy(card->GetPublisher());
    PublisherTextCtrl->SetValue(buffer.GetArray());
    AllowCopyCheckBox->SetValue(card->canCopy);
    EncryptCheckBox->SetValue(card->isEncrypted);
    m_card = card;
}

void SwCatalogCardDlg::UpdateCard(SwCatalogCard * card)
{
    if (!card)
        return;

    card->SetTitle(TitleTextCtrl->GetValue().utf8_str());
    card->SetAbbreviation(AbbreviationTextCtrl->GetValue().utf8_str());
    card->SetIdentifier(IdentifierTextCtrl->GetValue().utf8_str());
    card->category = SwCategory::GetCategory(CategoryChoice);
    card->SetGroup(GroupComboBox->GetValue().utf8_str());
    card->SetPublisher(PublisherTextCtrl->GetValue().utf8_str());
    card->SetVersification(VersificationComboBox->GetValue().utf8_str());
    card->SetCcelFileName(OfnTextCtrl->GetValue().utf8_str());
    card->canCopy = AllowCopyCheckBox->GetValue();
    card->isEncrypted = EncryptCheckBox->GetValue();
}

void SwCatalogCardDlg::SetCatalog(SwCatalogCardArray * catalog)
{
    m_catalog = catalog;
    GroupComboBox->Clear();
    m_catalog->GetGroupList(GroupComboBox);
}

void SwCatalogCardDlg::ShowStopButton(bool state)
{
    StopButton->Show(state);
}

void SwCatalogCardDlg::OnQuit(wxCommandEvent& event)
{
    EndModal(0);
}

void SwCatalogCardDlg::OnOkButtonClick(wxCommandEvent& event)
{
    if (!Validate())
        return;
    UpdateCard(m_card);
    EndModal(1);
}

void SwCatalogCardDlg::OnStopButtonClick(wxCommandEvent& event)
{
    EndModal(2);
}

bool SwCatalogCardDlg::Validate()
{
    bool status = true;

    if (TitleTextCtrl->GetValue().Len() < 3 || TitleTextCtrl->GetValue().Len() > 199)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_TITLELENGTH", L"Title must be 3 - 199 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }
    else if (m_catalog && m_catalog->FindByTitle(TitleTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID_16)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_TITLEINUSE", L"Title in use."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (AbbreviationTextCtrl->GetValue().Len() < 3 || AbbreviationTextCtrl->GetValue().Len() > 12)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_ABBREVIATIONLENGTH", L"Abbreviation must be 3 - 12 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }
    else if (m_catalog && m_catalog->FindByAbbrev(AbbreviationTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID_16)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_ABBREVIATIONINUSE", L"Abbreviation in use."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (IdentifierTextCtrl->GetValue().Len() < 7)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_IDENTIFIERLENGTH", L"Identifier must be 7 - 12 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }
    else if (m_catalog && m_catalog->FindById(IdentifierTextCtrl->GetValue().utf8_str()) != NODE_ID_INVALID_16)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_IDENTIFIERINUSE", L"Identifier in use."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (OfnTextCtrl->GetValue().Len() > 39)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_ORIGINALFILENAMELENGTH", L"Original file name may not exceed 39 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (PublisherTextCtrl->GetValue().Len() > 49)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_PUBLISHERNAMELENGTH", L"Publisher name may not exceed 49 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    if (VersificationComboBox->GetValue().Len() > 12)
    {
        ReportTextCtrl->AppendText(SwApplicationInterface::GetControlString("SID_VERSIFICATIONLENGTH", L"Versification name may not exceed 12 characters."));
        ReportTextCtrl->AppendText("\n");
        status = false;
    }

    return status;
}

void SwCatalogCardDlg::LoadFromFile(const char * path)
{
    if (!path)
        return;

    bool spaced = true;
    SwStringW buffer, abb;
    SwString id;

    if (SwThMLUtility::GetTitleW(buffer, path))
    {
        TitleTextCtrl->SetValue(buffer.GetArray());

        for (swUI32 i = 0; i < buffer.Strlen(); i ++)
        {
            if (!spaced && buffer.GetAt(i) == L' ')
            {
                spaced = true;
                continue;
            }

            if (spaced)
            {
                abb += buffer.GetAt(i);
                spaced = false;
            }
        }

        abb.ToUpper();
        AbbreviationTextCtrl->SetValue(abb.GetArray());
    }

    SwFilePath filepath(path);

    buffer.Copy(filepath.GetFileName());
    OfnTextCtrl->SetValue(buffer.GetArray());

    if (SwThMLUtility::GetIdentifier(id, path))
    {
        id.TrimRight(' ');
        if (id.Strlen() < 7)
            id += "-000";
        IdentifierTextCtrl->SetValue(id.GetArray());
    }

    CategoryChoice->SetSelection(0);
    SetCategory(path);
}

void SwCatalogCardDlg::SetCategory(const char * path)
{
    SwString buffer;

    if (!SwThMLUtility::GetDublinCore(buffer, path))
        return;

    SwCategory::SetCategory(CategoryChoice, SwCategory::IdentifyCategory(buffer));
}
