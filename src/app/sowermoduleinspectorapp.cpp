///////////////////////////////////////////////////////////////////
// Name:        sowermoduleinspectorapp.cpp
// Purpose:     Sower Module Inspector
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "app/sowermoduleinspectorapp.h"
#include "appi/appifa.h"
#include "bible/standard_bible.h"
#include "filesys/streambuffer.h"
#include <wx/taskbar.h>

IMPLEMENT_APP(SowerModuleInspectorApp);

bool SowerModuleInspectorApp::OnInit()
{
<<<<<<< Updated upstream
=======
    #if defined __OSX__
    wxTaskBarIcon * dockIcon = new wxTaskBarIcon(wxTBI_DOCK);
    dockIcon->SetIcon(wxBitmapBundle(SwApplicationInterface::GetStockImage(IMG_TOOLS32)));
    #endif

>>>>>>> Stashed changes
    SwApplicationInterface::InitBasic();
    SwApplicationInterface::LoadPlugIns();
    SwApplicationInterface::LoadAllKeys();
    SwApplicationInterface::LoadModules();

    SowerModuleInspectorFrame* Frame = new SowerModuleInspectorFrame(NULL, wxNewId(), L"");
    Frame->Show();
    SetTopWindow(Frame);

    return true;
}

const long SowerModuleInspectorFrame::ID_TITLELABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_TITLETEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_ABBREVIATIONLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_ABBREVIATIONTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_IDENTIFIERLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_IDENTIFIERTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_CATEGORYLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_CATEGORYTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_GROUPLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_GROUPTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_VERSIFICATIONLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_VERSIFICATIONTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_OFNLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_OFNTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_ALLOWCOPYLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_ALLOWCOPYCHECKBOX = wxNewId();
const long SowerModuleInspectorFrame::ID_ENCRYPTEDLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_ENCRYPTEDCHECKBOX = wxNewId();
const long SowerModuleInspectorFrame::ID_PANEL1 = wxNewId();
const long SowerModuleInspectorFrame::ID_CONTENTSTREECTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_MEDIALISTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_IMAGEVIEW = wxNewId();
const long SowerModuleInspectorFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long SowerModuleInspectorFrame::ID_SCRIPTUREREFERENCELABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_SCRIPTURETEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_FINDSCRIPTUREBUTTON = wxNewId();
const long SowerModuleInspectorFrame::ID_SCRIPTUREPANEL = wxNewId();
const long SowerModuleInspectorFrame::ID_COMMENTARYREFERENCELABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_COMMENTARYTEXTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_FINDCOMMENTARYBUTTON = wxNewId();
const long SowerModuleInspectorFrame::ID_COMMENTARYPANEL = wxNewId();
const long SowerModuleInspectorFrame::ID_STRONGSGLISTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_STRONGSHLISTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_TERMLISTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_NOTESLISTCTRL = wxNewId();
const long SowerModuleInspectorFrame::ID_NOTEBOOK = wxNewId();
const long SowerModuleInspectorFrame::ID_VIEWNOTEBOOK = wxNewId();
const long SowerModuleInspectorFrame::ID_STATUSLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_COPYRIGHTBUTTON = wxNewId();
const long SowerModuleInspectorFrame::ID_PUBLISHERLABEL = wxNewId();
const long SowerModuleInspectorFrame::ID_PUBLISHERTEXT = wxNewId();

SowerModuleInspectorFrame::SowerModuleInspectorFrame(wxWindow* parent,wxWindowID id, const wxString &title,const wxPoint& pos,const wxSize& size, long style, const wxString &name)
    :SwFrame(parent, id, title, pos, size, style, name)
{
    managerId = NODE_ID_INVALID_16;
    module = NULL;

    SetIcon(SwApplicationInterface::GetToolsIcon());
    menuBar = new SwBasicMenuBar(this);
    SetMenuBar(menuBar);

    AddNoteBookPanel();
    AddModulePanel();
    AddContentsPanel();
    AddMediaPanel();
    AddScripturePanel();
    AddCommentaryPanel();
    AddStrongsGPanel();
    AddStrongsHPanel();
    AddTermPanel();
    AddNotesPanel();
    AddViewPanel();

    SetTitle(SwApplicationInterface::GetControlString("SID_SOWERMODULEINSPECTOR", L"Sower Module Inspector"));

    Connect(ID_CONTENTSTREECTRL,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnContentsTreeCtrlSelectionChanged);
    Connect(ID_MEDIALISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnMediaListCtrlItemSelect);
    Connect(ID_STRONGSGLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnStrongsGListCtrlItemSelect);
    Connect(ID_STRONGSHLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnStrongsHListCtrlItemSelect);
    Connect(ID_TERMLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnTermListCtrlItemSelect);
    Connect(ID_NOTESLISTCTRL,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnNotesListCtrlItemSelect);
    Connect(ID_FINDSCRIPTUREBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnFindScriptureButtonClick);
    Connect(ID_FINDCOMMENTARYBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnFindCommentaryButtonClick);
    Connect(ID_COPYRIGHTBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SowerModuleInspectorFrame::OnInfoButtonClick);
    Maximize();
}

SowerModuleInspectorFrame::~SowerModuleInspectorFrame()
{
}

void SowerModuleInspectorFrame::OnInfoButtonClick(wxCommandEvent& event)
{
    SwString buffer;
    ViewNoteBook->ResetAll();
    if (!SwApplicationInterface::GetModuleManager().LoadElectronicInfo(managerId, buffer))
        return;
    ViewNoteBook->OnWriteXmlText(CT_THML, buffer, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnContentsTreeCtrlSelectionChanged(wxTreeEvent& event)
{
    wxBusyCursor busy;
    SwTreeDataEx * td = (SwTreeDataEx *) ContentsTreeCtrl->GetItemData(event.GetItem());

    if (!td)
        return;

    SwPageData pd;

    pd.m_managerId = td->m_managerId;
    pd.m_pageId = td->m_pageId;

    ViewNoteBook->OnLoad(pd);
}

void SowerModuleInspectorFrame::OnMediaListCtrlItemSelect(wxListEvent& event)
{
    if (managerId == NODE_ID_INVALID_16)
        return;

    SwStreamBuffer data;
    bool canCopy;

    swUI16 node = module->GetMediaContents().FindItem(event.GetLabel().utf8_str());
    SwMediaNode * mediaNode = module->GetMediaContents().GetNode(node);

    swUI8 contentType = CT_UNKNOWN;

    if (mediaNode->contentType == SW_MEDIA_TYPE_AUDIO)
        contentType = CT_AUDIO;
    else if (mediaNode->contentType == SW_MEDIA_TYPE_VIDEO)
        contentType = CT_VIDEO;
    else if (mediaNode->contentType == SW_MEDIA_TYPE_IMAGE)
        contentType = CT_IMAGE;

    SwApplicationInterface::GetModuleManager().LoadMedia(managerId, event.GetLabel().utf8_str(), data, canCopy);
    ViewNoteBook->ResetAll();
    ViewNoteBook->OnLoad(contentType, data);
    ViewNoteBook->OnSetCanCopy(canCopy);
    ViewNoteBook->Refresh();
}

void SowerModuleInspectorFrame::OnStrongsGListCtrlItemSelect(wxListEvent& event)
{
    if (!module)
        return;

    SwString data;
    swUI16 id = module->GetADStrongsG().FindItem(event.GetLabel().wc_str());

    if (id == NODE_ID_INVALID_16)
        return;

    ViewNoteBook->ResetAll();
    module->GetADStrongsG().GetNode(id)->ReadData(module->GetFile(), data, module->GetHeader().itemdataLocator, module->GetHeader().filecontentsLocator, module->GetHeader().k1, module->GetHeader().k2, module->GetHeader().isEncrypted);
    ViewNoteBook->OnWriteXmlText(CT_THML, data, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnStrongsHListCtrlItemSelect(wxListEvent& event)
{
    if (!module)
        return;

    SwString data;
    swUI16 id = module->GetADStrongsH().FindItem(event.GetLabel().wc_str());

    if (id == NODE_ID_INVALID_16)
        return;

    ViewNoteBook->ResetAll();
    module->GetADStrongsG().GetNode(id)->ReadData(module->GetFile(), data, module->GetHeader().itemdataLocator, module->GetHeader().filecontentsLocator, module->GetHeader().k1, module->GetHeader().k2, module->GetHeader().isEncrypted);
    ViewNoteBook->OnWriteXmlText(CT_THML, data, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnTermListCtrlItemSelect(wxListEvent& event)
{
    if (!module)
        return;

    SwString data;
    swUI16 id = module->GetADTerm().FindItem(event.GetLabel().wc_str());

    if (id == NODE_ID_INVALID_16)
        return;

    ViewNoteBook->ResetAll();
    module->GetADTerm().GetNode(id)->ReadData(module->GetFile(), data, module->GetHeader().itemdataLocator, module->GetHeader().filecontentsLocator, module->GetHeader().k1, module->GetHeader().k2, module->GetHeader().isEncrypted);
    ViewNoteBook->OnWriteXmlText(CT_THML, data, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnNotesListCtrlItemSelect(wxListEvent& event)
{
    SwString data;
    swUI16 id = module->GetADNotes().FindItem(event.GetLabel().wc_str());

    if (id == NODE_ID_INVALID_16)
        return;

    ViewNoteBook->ResetAll();
    module->GetADNotes().GetNode(id)->ReadData(module->GetFile(), data, module->GetHeader().itemdataLocator, module->GetHeader().filecontentsLocator, module->GetHeader().k1, module->GetHeader().k2, module->GetHeader().isEncrypted);
    ViewNoteBook->OnWriteXmlText(CT_THML, data, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnFindScriptureButtonClick(wxCommandEvent& event)
{
    if (!module)
        return;

    SwReferenceData rd;
    int pos = ScriptureTextCtrl->GetValue().Find(':');

    if (!SwStandardBible::IdentifyReference(ScriptureTextCtrl->GetValue(), pos, rd))
        return;

    SwString data;
    swUI16 id = module->GetADScripture().FindVerse(rd.book, rd.chapter, rd.verseStart);

    if (id == NODE_ID_INVALID_16)
        return;

    ViewNoteBook->ResetAll();
    module->GetADScripture().GetVerseData(id)->ReadData(module->GetFile(), data, module->GetHeader().itemdataLocator, module->GetHeader().filecontentsLocator, module->GetHeader().k1, module->GetHeader().k2, module->GetHeader().isEncrypted);
    ViewNoteBook->OnWriteXmlText(CT_THML, data, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnFindCommentaryButtonClick(wxCommandEvent& event)
{
    if (!module)
        return;

    SwReferenceData rd;

    int pos = CommentaryTextCtrl->GetValue().Find(':');
    if (!SwStandardBible::IdentifyReference(CommentaryTextCtrl->GetValue(), pos, rd))
        return;

    SwString data;
    swUI16 id = module->GetADCommentary().FindVerse(rd.book, rd.chapter, rd.verseStart);

    if (id == NODE_ID_INVALID_16)
        return;

    ViewNoteBook->ResetAll();
    module->GetADCommentary().GetVerseRangeData(id)->ReadData(module->GetFile(), data, module->GetHeader().itemdataLocator, module->GetHeader().filecontentsLocator, module->GetHeader().k1, module->GetHeader().k2, module->GetHeader().isEncrypted);
    ViewNoteBook->OnWriteXmlText(CT_THML, data, true, "");
    ViewNoteBook->OnSetCanCopy(module->GetHeader().canCopy);
}

void SowerModuleInspectorFrame::OnAbout(wxCommandEvent& event)
{
    SwApplicationInterface::About(SwApplicationInterface::GetControlString("SID_SOWERMODULEINSPECTOR", L"Sower Module Inspector"), SVSTR, L"2019");
}

void SowerModuleInspectorFrame::OnOpen(wxCommandEvent& event)
{
    wxBusyCursor busy;
    SwString filePath;
    SwModule * mod;
    if (SwDialog::SelectModuleFile(this, filePath, ""))
    {
        Reset();
        mod = new SwModule();
        if (!mod->Load(filePath))
        {
            StatusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_MODULEFAILED", L"Module failed."));
            delete mod;
            return;
        }

        SwApplicationInterface::GetModuleManager().Add(mod);
        SwApplicationInterface::GetModuleManager().SetModuleKey(mod);
        managerId = mod->m_managerId;
        module = mod;
        EnableInterface(true);

        SwStringW buffer;
        buffer.Copy(mod->GetHeader().GetTitle());
        TitleTextCtrl->SetValue(buffer.GetArray());
        buffer.Copy(mod->GetHeader().GetAbbreviation());
        AbbreviationTextCtrl->SetValue(buffer.GetArray());
        buffer.Copy(mod->GetHeader().GetIdentifier());
        IdentifierTextCtrl->SetValue(buffer.GetArray());

        CategoryTextCtrl->SetValue(SwApplicationInterface::GetControlString(SwCategory::GetId(mod->GetHeader().GetCategory()), SwCategory::GetStringW(mod->GetHeader().GetCategory())));
        buffer.Copy(mod->GetHeader().GetGroup());
        GroupTextCtrl->SetValue(buffer.GetArray());
        buffer.Copy(mod->GetHeader().GetVersification());
        VersificationTextCtrl->SetValue(buffer.GetArray());
        buffer.Copy(mod->GetHeader().GetCcelFileName());
        OFNTextCtrl->SetValue(buffer.GetArray());
        AllowCopyCheckBox->SetValue(mod->GetHeader().canCopy);
        EncryptedCheckBox->SetValue(mod->GetHeader().isEncrypted);

        PublisherTextCtrl->SetValue(mod->GetHeader().GetPublisher());

        ContentsTreeCtrl->BuildTree(module->GetTableofContents(), ContentsTreeCtrl->GetRootItem(), module->GetHeader().category, module->GetManagerId());
        module->GetMediaContents().FillCtrl(MediaListCtrl);
        module->GetADTerm().FillCtrl(TermListCtrl);
        module->GetADNotes().FillCtrl(NotesListCtrl);
        StatusLabel->SetLabel(SwApplicationInterface::GetControlString("SID_MODULELOADED", L"Module loaded."));
    }

    Notebook->SetSelection(0);
}

void SowerModuleInspectorFrame::OnClose(wxCommandEvent& event)
{
    Reset();
}


void SowerModuleInspectorFrame::OnQuit(wxCommandEvent& event)
{
    SwApplicationInterface::CloseFiles();
    Close();
}

void SowerModuleInspectorFrame::OnLanguageChange()
{
}

void SowerModuleInspectorFrame::EnableInterface(bool state)
{
    menuBar->EnableItems(state);
}

void SowerModuleInspectorFrame::Reset()
{
    ViewNoteBook->ResetAll();
    AllowCopyCheckBox->SetValue(false);
    EncryptedCheckBox->SetValue(false);
    MediaListCtrl->DeleteAllItems();
    NotesListCtrl->DeleteAllItems();
    StrongsGListCtrl->DeleteAllItems();
    StrongsHListCtrl->DeleteAllItems();
    TermListCtrl->DeleteAllItems();
    AbbreviationTextCtrl->SetValue(L"");
    CategoryTextCtrl->SetValue(L"");
    GroupTextCtrl->SetValue(L"");
    IdentifierTextCtrl->SetValue(L"");
    OFNTextCtrl->SetValue(L"");
    TitleTextCtrl->SetValue(L"");
    VersificationTextCtrl->SetValue(L"");
    ContentsTreeCtrl->Reset();
    PublisherTextCtrl->SetValue(L"");
    StatusLabel->SetLabel(L"");

    if (module)
        SwApplicationInterface::GetModuleManager().Delete(SwApplicationInterface::GetModuleManager().FindByMID(managerId));

    managerId = NODE_ID_INVALID_16;
    module = NULL;
}

void SowerModuleInspectorFrame::AddNoteBookPanel()
{
    Notebook = new wxNotebook(this, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, L"ID_NOTEBOOK");
    Notebook->SetMinSize(wxSize(200,-1));
    m_manager->AddPane(Notebook, wxAuiPaneInfo().Name(L"NoteBook").DefaultPane().CaptionVisible(false).CloseButton(false).Left().Floatable(false).MinSize(wxSize(300,-1)));
    m_manager->Update();
}

void SowerModuleInspectorFrame::AddModulePanel()
{
    Panel1 = new wxPanel(Notebook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_PANEL1");
    wxGridBagSizer * GridBagSizer1 = new wxGridBagSizer(0, 0);
    TitleLabel = new wxStaticText(Panel1, ID_TITLELABEL, SwApplicationInterface::GetControlString("SID_TITLE", L"Title"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
    GridBagSizer1->Add(TitleLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TitleTextCtrl = new SwFittedTextCtrl(Panel1, ID_TITLETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_TITLETEXTCTRL");
    GridBagSizer1->Add(TitleTextCtrl, wxGBPosition(0, 1), wxDefaultSpan, wxALL, 5);
    AbbreviationLabel = new wxStaticText(Panel1, ID_ABBREVIATIONLABEL, SwApplicationInterface::GetControlString("SID_ABBREVIATION", L"Abbreviation"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ABBREVIATIONLABEL");
    GridBagSizer1->Add(AbbreviationLabel, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    AbbreviationTextCtrl = new SwFittedTextCtrl(Panel1, ID_ABBREVIATIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_ABBREVIATIONTEXTCTRL");
    GridBagSizer1->Add(AbbreviationTextCtrl, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdentifierLabel = new wxStaticText(Panel1, ID_IDENTIFIERLABEL, SwApplicationInterface::GetControlString("SID_IDENTIFIER", L"Identifier"), wxDefaultPosition, wxDefaultSize, 0, L"ID_IDENTIFIERLABEL");
    GridBagSizer1->Add(IdentifierLabel, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    IdentifierTextCtrl = new SwFittedTextCtrl(Panel1, ID_IDENTIFIERTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_IDENTIFIERTEXTCTRL");
    GridBagSizer1->Add(IdentifierTextCtrl, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CategoryLabel = new wxStaticText(Panel1, ID_CATEGORYLABEL, SwApplicationInterface::GetControlString("SID_CATEGORY" ,L"Category"), wxDefaultPosition, wxDefaultSize, 0, L"ID_CATEGORYLABEL");
    GridBagSizer1->Add(CategoryLabel, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CategoryTextCtrl = new SwFittedTextCtrl(Panel1, ID_CATEGORYTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_CATEGORYTEXTCTRL");
    GridBagSizer1->Add(CategoryTextCtrl, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GroupLabel = new wxStaticText(Panel1, ID_GROUPLABEL, SwApplicationInterface::GetControlString("SID_GROUP" ,L"Group"), wxDefaultPosition, wxDefaultSize, 0, L"ID_GROUPLABEL");
    GridBagSizer1->Add(GroupLabel, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GroupTextCtrl = new SwFittedTextCtrl(Panel1, ID_GROUPTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_GROUPTEXTCTRL");
    GridBagSizer1->Add(GroupTextCtrl, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    VersificationLabel = new wxStaticText(Panel1, ID_VERSIFICATIONLABEL, SwApplicationInterface::GetControlString("SID_VERSIFICATION", L"Versification"), wxDefaultPosition, wxDefaultSize, 0, L"ID_VERSIFICATIONLABEL");
    GridBagSizer1->Add(VersificationLabel, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    VersificationTextCtrl = new SwFittedTextCtrl(Panel1, ID_VERSIFICATIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_VERSIFICATIONTEXTCTRL");
    GridBagSizer1->Add(VersificationTextCtrl, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    OFNLabel = new wxStaticText(Panel1, ID_OFNLABEL, SwApplicationInterface::GetControlString("SID_ORIGINALFILENAME" ,L"Original File Name"), wxDefaultPosition, wxDefaultSize, 0, L"ID_OFNLABEL");
    GridBagSizer1->Add(OFNLabel, wxGBPosition(6, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    OFNTextCtrl = new SwFittedTextCtrl(Panel1, ID_OFNTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_OFNTEXTCTRL");
    GridBagSizer1->Add(OFNTextCtrl, wxGBPosition(6, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    AllowCopyLabel = new wxStaticText(Panel1, ID_ALLOWCOPYLABEL, SwApplicationInterface::GetControlString("SID_ALLOWCOPY" ,L"Allow Copy"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ALLOWCOPYLABEL");
    GridBagSizer1->Add(AllowCopyLabel, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    AllowCopyCheckBox = new SwCheckBox(Panel1, ID_ALLOWCOPYCHECKBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ALLOWCOPYCHECKBOX");
    AllowCopyCheckBox->SetValue(false);
    AllowCopyCheckBox->Disable();
    GridBagSizer1->Add(AllowCopyCheckBox, wxGBPosition(7, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    EncryptedLabel = new wxStaticText(Panel1, ID_ENCRYPTEDLABEL, SwApplicationInterface::GetControlString("SID_ENCRYPTED" ,L"Encrypted"), wxDefaultPosition, wxDefaultSize, 0, L"ID_ENCRYPTEDLABEL");
    GridBagSizer1->Add(EncryptedLabel, wxGBPosition(8, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    EncryptedCheckBox = new SwCheckBox(Panel1, ID_ENCRYPTEDCHECKBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_ENCRYPTEDCHECKBOX");
    EncryptedCheckBox->SetValue(false);
    EncryptedCheckBox->Disable();
    GridBagSizer1->Add(EncryptedCheckBox, wxGBPosition(8, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    PublisherLabel = new wxStaticText(Panel1, ID_PUBLISHERLABEL, SwApplicationInterface::GetControlString("SID_PUBLISHER", L"Publisher"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
    GridBagSizer1->Add(PublisherLabel, wxGBPosition(9, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PublisherTextCtrl = new SwFittedTextCtrl(Panel1, ID_TITLETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, L"ID_TITLETEXTCTRL");
    GridBagSizer1->Add(PublisherTextCtrl, wxGBPosition(9, 1), wxDefaultSpan, wxALL, 5);


    InfoButton = new wxButton(Panel1, ID_COPYRIGHTBUTTON, SwApplicationInterface::GetControlString("SID_INFORMATION", L"Information"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_COPYRIGHTBUTTON");
    GridBagSizer1->Add(InfoButton, wxGBPosition(10, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    StatusLabel = new wxStaticText(Panel1, ID_STATUSLABEL, SwApplicationInterface::GetControlString("SID_STATUS", L"Status"), wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
    GridBagSizer1->Add(StatusLabel, wxGBPosition(11, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

    Panel1->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(Panel1);
    GridBagSizer1->SetSizeHints(Panel1);
    Notebook->AddPage(Panel1, SwApplicationInterface::GetControlString("SID_MODULE", L"Module"), false);
}

void SowerModuleInspectorFrame::AddContentsPanel()
{
    ContentsTreeCtrl = new SwModuleTreeCtrl(Notebook, ID_CONTENTSTREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_LINES_AT_ROOT|wxTR_SINGLE|wxTR_DEFAULT_STYLE, wxDefaultValidator, L"ID_CONTENTSTREECTRL");
    Notebook->AddPage(ContentsTreeCtrl, SwApplicationInterface::GetControlString("SID_CONTENTS", L"Contents"), false);
}

void SowerModuleInspectorFrame::AddMediaPanel()
{
    MediaListCtrl = new SwStretchColumnListCtrl(Notebook, ID_MEDIALISTCTRL, wxPoint(132,56), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_MEDIALISTCTRL");
    MediaListCtrl->wxListCtrl::AppendColumn("");
    MediaListCtrl->SetMinSize(wxSize(-1,200));
    Notebook->AddPage(MediaListCtrl, SwApplicationInterface::GetControlString("SID_MEDIA", L"Media"), false);
}

void SowerModuleInspectorFrame::AddScripturePanel()
{
    ScripturePanel = new wxPanel(Notebook, ID_SCRIPTUREPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_SCRIPTUREPANEL");
    wxGridBagSizer * GridBagSizer1 = new wxGridBagSizer(0, 0);
    ScriptureReferenceLabel = new wxStaticText(ScripturePanel, ID_SCRIPTUREREFERENCELABEL, SwApplicationInterface::GetControlString("SID_REFERENCE", L"Reference"), wxDefaultPosition, wxDefaultSize, 0, L"ID_SCRIPTUREREFERENCELABEL");
    GridBagSizer1->Add(ScriptureReferenceLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ScriptureTextCtrl = new SwStretchTextCtrl(ScripturePanel, ID_SCRIPTURETEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_SCRIPTURETEXTCTRL");
    GridBagSizer1->Add(ScriptureTextCtrl, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindScriptureButton = new wxButton(ScripturePanel, ID_FINDSCRIPTUREBUTTON, SwApplicationInterface::GetControlString("SID_FIND", L"Find"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDSCRIPTUREBUTTON");
    GridBagSizer1->Add(FindScriptureButton, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ScripturePanel->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(ScripturePanel);
    GridBagSizer1->SetSizeHints(ScripturePanel);
    Notebook->AddPage(ScripturePanel, SwApplicationInterface::GetControlString("SID_SCRIPTURE", L"Scripture"), false);
}

void SowerModuleInspectorFrame::AddCommentaryPanel()
{
    CommentaryPanel = new wxPanel(Notebook, ID_COMMENTARYPANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, L"ID_COMMENTARYPANEL");
    wxGridBagSizer *GridBagSizer1 = new wxGridBagSizer(0, 0);
    CommentaryReferenceLabel = new wxStaticText(CommentaryPanel, ID_COMMENTARYREFERENCELABEL, SwApplicationInterface::GetControlString("SID_REFERENCE", L"Reference"), wxDefaultPosition, wxDefaultSize, 0, L"ID_COMMENTARYREFERENCELABEL");
    GridBagSizer1->Add(CommentaryReferenceLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CommentaryTextCtrl = new SwStretchTextCtrl(CommentaryPanel, ID_COMMENTARYTEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_COMMENTARYTEXTCTRL");
    GridBagSizer1->Add(CommentaryTextCtrl, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FindCommentaryButton = new wxButton (CommentaryPanel, ID_FINDCOMMENTARYBUTTON, SwApplicationInterface::GetControlString("SID_FIND", L"Find"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_FINDCOMMENTARYBUTTON");
    GridBagSizer1->Add(FindCommentaryButton, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CommentaryPanel->SetSizer(GridBagSizer1);
    GridBagSizer1->Fit(CommentaryPanel);
    GridBagSizer1->SetSizeHints(CommentaryPanel);
    Notebook->AddPage(CommentaryPanel, SwApplicationInterface::GetControlString("SID_COMMENTARY", L"Commentary"), false);
}

void SowerModuleInspectorFrame::AddStrongsGPanel()
{
    StrongsGListCtrl = new SwStretchColumnListCtrl(Notebook, ID_STRONGSGLISTCTRL, wxPoint(331,13), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_STRONGSGLISTCTRL");
    StrongsGListCtrl->wxListCtrl::AppendColumn("");
    Notebook->AddPage(StrongsGListCtrl, SwApplicationInterface::GetControlString("SID_STRONGSGREEK", L"Strongs Greek"), false);
}

void SowerModuleInspectorFrame::AddStrongsHPanel()
{
    StrongsHListCtrl = new SwStretchColumnListCtrl(Notebook, ID_STRONGSHLISTCTRL, wxPoint(345,34), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_STRONGSHLISTCTRL");
    StrongsHListCtrl->wxListCtrl::AppendColumn("");
    Notebook->AddPage(StrongsHListCtrl, SwApplicationInterface::GetControlString("SID_STRONGSHEBREW", L"Strongs Hebrew"), false);
}

void SowerModuleInspectorFrame::AddTermPanel()
{
    TermListCtrl = new SwStretchColumnListCtrl(Notebook, ID_TERMLISTCTRL, wxPoint(216,10), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_TERMLISTCTRL");
    TermListCtrl->wxListCtrl::AppendColumn("");
    Notebook->AddPage(TermListCtrl, SwApplicationInterface::GetControlString("SID_TERM", L"Term"), false);
}

void SowerModuleInspectorFrame::AddNotesPanel()
{
    NotesListCtrl = new SwStretchColumnListCtrl(Notebook, ID_NOTESLISTCTRL, wxPoint(171,5), wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_NO_HEADER, wxDefaultValidator, L"ID_NOTESLISTCTRL");
    NotesListCtrl->wxListCtrl::AppendColumn("");
    Notebook->AddPage(NotesListCtrl, SwApplicationInterface::GetControlString("SID_NOTES", L"Notes"), false);
}

void SowerModuleInspectorFrame::AddViewPanel()
{
    ViewNoteBook = new SwViewBook(this, ID_VIEWNOTEBOOK, wxDefaultPosition, wxDefaultSize, 0, L"ID_VIEWNOTEBOOK");
    m_manager->AddPane(ViewNoteBook, wxAuiPaneInfo().Name(L"ViewNoteBook").DefaultPane().CaptionVisible(false).Center().Floatable(false));
    m_manager->Update();
}
