///////////////////////////////////////////////////////////////////
// Name:        carddlg.h
// Purpose:     SwCatalogCardDlg
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERCATALOGCARDDLG_H
#define SOWERCATALOGCARDDLG_H

#include "../framework/dialog.h"
#include "../controls/stretchfitctrls.h"
#include "../module/modulebase.h"
#include "../array/cardarray.h"
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>

class SOWERBASEEXP SwCatalogCardDlg: public SwDialog
{
public:
    SwCatalogCardDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwCatalogCardDlg();

    void SetCard(SwCatalogCard * card);
    void UpdateCard(SwCatalogCard * card);
    void SetCatalog(SwCatalogCardArray * catalog);
    void ShowStopButton(bool state = false);
    SwCheckBox* AllowCopyCheckBox;
    SwCheckBox* EncryptCheckBox;
    wxChoice* CategoryChoice;
    wxComboBox* GroupComboBox;
    wxComboBox* VersificationComboBox;
    wxStaticText* AbbreviationLabel;
    wxStaticText* CategoryLabel;
    wxStaticText* GroupLabel;
    wxStaticText* IdentifierLabel;
    wxStaticText* OfnLabel;
    wxStaticText* TitleLabel;
    wxStaticText* VersificationLabel;
    wxTextCtrl* AbbreviationTextCtrl;
    wxTextCtrl* IdentifierTextCtrl;
    wxTextCtrl* OfnTextCtrl;
    wxTextCtrl* TitleTextCtrl;
    wxStaticText* PublisherLabel;
    wxTextCtrl* PublisherTextCtrl;
    wxTextCtrl* ReportTextCtrl;
    wxButton* OkButton;
    wxButton* CancelButton;
    wxButton* StopButton;

    static const long ID_TITLELABEL;
    static const long ID_ABBREVIATIONLABEL;
    static const long ID_IDENTIFIERLABEL;
    static const long ID_TITLETEXTCTRL;
    static const long ID_ABBREVIATIONTEXTCTRL;
    static const long ID_IDENTIFIERTEXTCTRL;
    static const long ID_CATEGORYLABEL;
    static const long ID_GROUPLABEL;
    static const long ID_VERSIFICATIONLABEL;
    static const long ID_CATEGORYCHOICE;
    static const long ID_GROUPCOMBOBOX;
    static const long ID_VERSIFICATIONCOMBOBOX;
    static const long ID_ALLOWCOPYCHECKBOX;
    static const long ID_OFNLABEL;
    static const long ID_ENCRYPTCHECKBOX;
    static const long ID_OFNTEXTCTRL;
    static const long ID_PUBLISHERLABEL;
    static const long ID_PUBLISHERTEXTCTRL;
    static const long ID_REPORTTEXTCTRL;
    static const long ID_OKBUTTON;
    static const long ID_CANCELBUTTON;
    static const long ID_STOPBUTTON;

    bool Validate();
    void OnQuit(wxCommandEvent& event);
    void OnOkButtonClick(wxCommandEvent& event);
    void OnStopButtonClick(wxCommandEvent& event);
    void LoadFromFile(const char * path);
    void SetCategory(const char * path);

protected:
    SwCatalogCard * m_card;
    SwCatalogCardArray * m_catalog;
};

#endif // SOWERCATALOGCARDDLG_H
