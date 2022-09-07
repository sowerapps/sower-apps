///////////////////////////////////////////////////////////////////
// Name:        interfacedlg.cpp
// Purpose:     Select gui interface plug-in.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/dialogs/interfacedlg.h"
#include <wx/button.h>
#include <wx/intl.h>
#include <wx/string.h>

const long SwInterfaceDlg::ID_INTERFACECHOICE = wxNewId();

SwInterfaceDlg::SwInterfaceDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	BuildContent(parent,id,pos,size);
}

void SwInterfaceDlg::BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	wxGridBagSizer* GridBagSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, L"id");
	wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	interfaceChoice = new wxChoice(this, ID_INTERFACECHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, L"ID_INTERFACECHOICE");
	GridBagSizer1->Add(interfaceChoice, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	GridBagSizer1->Add(StdDialogButtonSizer1, wxGBPosition(1, 0), wxDefaultSpan, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

	SetLabel(SwApplicationInterface::GetControlString("SID_INTERFACE", L"Interface"));
	m_current = -1;
	Connect(ID_INTERFACECHOICE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&SwInterfaceDlg::OninterfaceChoiceSelect);
	Connect(wxID_OK,wxEVT_BUTTON,(wxObjectEventFunction)&SwInterfaceDlg::OnOk);
	SwApplicationInterface::GetInterfaceList(interfaceChoice);
 	m_current = interfaceChoice->GetSelection();
}

SwInterfaceDlg::~SwInterfaceDlg()
{
}

void SwInterfaceDlg::OninterfaceChoiceSelect(wxCommandEvent& event)
{
}

void SwInterfaceDlg::OnOk(wxCommandEvent& event)
{
    int selection = interfaceChoice->GetSelection();

    if (selection == wxNOT_FOUND)
        return;

    SwGuiPanel * panel = SwApplicationInterface::GetFrameWindow()->GetGuiPanel();

    if (selection != m_current)
    {
        if (panel)
        {
            panel->SaveUserData();
            SwApplicationInterface::SaveUserData();
            SwApplicationInterface::GetFrameWindow()->SetGuiPanel(NULL);
            SwApplicationInterface::GetFrameWindow()->GetAuiManager()->ClosePane(SwApplicationInterface::GetFrameWindow()->GetAuiManager()->GetPane(panel));
            SwApplicationInterface::GetFrameWindow()->GetAuiManager()->DetachPane(panel);
            SwApplicationInterface::GetFrameWindow()->GetAuiManager()->Update();
            delete panel;
        }

        SwClientData * data = (SwClientData *) interfaceChoice->GetClientObject(selection);
        if (!data || !SwApplicationInterface::GetPlugInManager().SetInterfacePlugIn(data->m_data))
        {
            EndModal(0);
            return;
        }
    }

    EndModal(1);
}
