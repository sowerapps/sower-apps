///////////////////////////////////////////////////////////////////
// Name:        find.h
// Purpose:     Find panel for SowerViewPanels.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef FINDPANEL_H
#define FINDPANEL_H

#include "panel.h"
#include "viewbook.h"
#include "../controls/stretchfitctrls.h"
#include "../string/stringcompare.h"

class SOWERBASEEXP SwFindPanel : public SwPanel
{
public:
    SwFindPanel();
    SwFindPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwFindPanel();

    void Reset();
    void CreateGui();
    void SetViewBook(SwViewBook * book);
    void SetPanel(SwPanel * panel);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    virtual void OnFindTextCtrlText(wxCommandEvent& event);
    virtual void OnFindCaseCheckBoxClick(wxCommandEvent& event);
    virtual void OnFindWordCheckBoxClick(wxCommandEvent& event);
    virtual void OnFindButtonClick(wxCommandEvent& event);

    static const long ID_FINDSTATICTEXT;
    static const long ID_FINDTEXTCTRL;
    static const long ID_FINDCASECHECKBOX;
    static const long ID_FINDWORDCHECKBOX;
    static const long ID_FINDBUTTON;

    wxGridBagSizer* FindGridSizer;
    SwStaticText* FindStaticText;
    SwStretchTextCtrl* FindTextCtrl;
    SwCheckBox* FindCaseCheckBox;
    SwCheckBox* FindWordCheckBox;
    SwButton* FindButton;

protected:
    SwStringCompareW m_compObj;
    bool m_first;
    SwViewBook * m_book;
    SwPanel * m_panel;
};


class SOWERBASEEXP SwFindReplacePanel : public SwPanel
{
public:
    SwFindReplacePanel();
    SwFindReplacePanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwFindReplacePanel();

    void Reset();
    void CreateGui();
    void SetRichTxtCtrl(wxRichTextCtrl * rich);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    void OnFindTextCtrlText(wxCommandEvent& event);
    void OnFindCaseCheckBoxClick(wxCommandEvent& event);
    void OnFindWordCheckBoxClick(wxCommandEvent& event);
    void OnFindButtonClick(wxCommandEvent& event);
    void OnReplaceButtonClick(wxCommandEvent& event);
    void OnReplaceAllButtonClick(wxCommandEvent& event);

    static const long ID_FINDSTATICTEXT;
    static const long ID_FINDTEXTCTRL;
    static const long ID_FINDCASECHECKBOX;
    static const long ID_FINDWORDCHECKBOX;
    static const long ID_REPLACESTATICTEXT;
    static const long ID_REPLACETEXTCTRL;
    static const long ID_FINDBUTTON;
    static const long ID_REPLACEBUTTON;
    static const long ID_REPLACEALLBUTTON;

    wxGridBagSizer* FindGridSizer;
    wxStaticText* FindStaticText;
    SwStretchTextCtrl* FindTextCtrl;
    SwCheckBox* FindCaseCheckBox;
    SwCheckBox* FindWordCheckBox;
    wxStaticText* ReplaceStaticText;
    SwStretchTextCtrl* ReplaceTextCtrl;
    wxButton* FindButton;
    wxButton* ReplaceButton;
    wxButton* ReplaceAllButton;

protected:
    SwStringCompareW m_compObj;
    SwFindReplace m_findreplace;
    bool m_first;
};

#endif // FINDPANEL_H
