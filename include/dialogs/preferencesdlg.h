///////////////////////////////////////////////////////////////////
// Name:        preferencesdlg.h
// Purpose:     SwPreferencesDlg
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef PREFERENCESDLG_H
#define PREFERENCESDLG_H

#include "../sowerbase.h"
#include "../string/string.h"
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include <wx/gbsizer.h>

class SOWERBASEEXP SwPreferencesDlg: public wxDialog
{
public:
    SwPreferencesDlg(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~SwPreferencesDlg();

    void OnOk(wxCommandEvent& event);
    wxCheckListBox* ModulesCheckListBox;
    wxChoice* LanguageChoice;
    wxChoice* ThemeChoice;
    wxDirPickerCtrl* ThMLLibraryDirPickerCtrl;
    wxDirPickerCtrl* ModLibraryDirPickerCtrl;
    wxSpinCtrl* ADFontSizeSpinCtrl;
    wxSpinCtrl* FontSizeSpinCtrl;
    wxStaticText* ADFontSizeText;
    wxStaticText* ADModulesText;
    wxStaticText* FontSizeText;
    wxStaticText* LanguageText;
    wxStaticText* ThMLLibraryLocationText;
    wxStaticText* ModLibraryLocationText;
    wxStaticText* ThemeText;
    wxCheckBox* sessionCheckBox;

protected:
    static const long ID_LANGUAGETEXT;
    static const long ID_LANGUAGECHOICE;
    static const long ID_THEMETEXT;
    static const long ID_THEMECHOICE;
    static const long ID_FONTSIZETEXT;
    static const long ID_FONTSIZESPINCTRL;
    static const long ID_ADFONTSIZETEXT;
    static const long ID_SPINCTRL2;
    static const long ID_THMLLIBRARYLOCATIONLOCATIONTEXT;
    static const long ID_THMLLIBRARYDIRPICKERCTRL;
    static const long ID_MODLIBRARYLOCATIONLOCATIONTEXT;
    static const long ID_MODLIBRARYDIRPICKERCTRL;
    static const long ID_ADMODULESTEXT;
    static const long ID_MODULESCHECKLISTBOX;
    static const long ID_SESSIONCHECKBOX;

private:
    int m_theme;
    int m_language;
    SwStringW m_thmlPath;
};

#endif // PREFERENCESDLG_H
