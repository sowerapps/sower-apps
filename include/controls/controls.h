///////////////////////////////////////////////////////////////////
// Name:        controls.h
// Purpose:     Controls that automatically update for language,
//              and theme changes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERCONTROLS_H
#define SOWERCONTROLS_H

#include "../string/string.h"
#include "../array/stringarray.h"
#include <wx/button.h>

class SOWERBASEEXP SwButton : public wxButton
{
    DECLARE_DYNAMIC_CLASS(SwButton)

public:
    SwButton();
    SwButton(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxButtonNameStr);
    virtual ~SwButton();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwString m_sid;
    SwString m_label;
};

#include <wx/bmpbuttn.h>
class SOWERBASEEXP SwBitmapButton : public wxBitmapButton
{
    DECLARE_DYNAMIC_CLASS(SwBitmapButton)

public:
    SwBitmapButton();
    SwBitmapButton(wxWindow *parent, wxWindowID id, const wxBitmap &bitmap, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxBU_AUTODRAW, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxButtonNameStr);
    virtual ~SwBitmapButton();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwString m_sid;
};

#include <wx/checkbox.h>
class SOWERBASEEXP SwCheckBox : public wxCheckBox
{
    DECLARE_DYNAMIC_CLASS(SwCheckBox)

public:
    SwCheckBox();
    SwCheckBox (wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxCheckBoxNameStr);
    virtual ~SwCheckBox();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwString m_sid;
    SwString m_label;
};

#include <wx/listbox.h>
class SOWERBASEEXP SwListBox : public wxListBox
{
    DECLARE_DYNAMIC_CLASS(SwListBox)

public:
    SwListBox();
    SwListBox(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, int n=0, const wxString choices[]=NULL, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name="listBox");
    virtual ~SwListBox();

    int  Append(const wxString &item, const wxString &sid);
    int  Append(const wxString &item, const wxString &sid, void *clientData);
    int  Append(const wxString &item, const wxString &sid, wxClientData *clientData);
    int  Insert(const wxString &item, const wxString &sid, unsigned int pos);
    int  Insert(const wxString &item, const wxString &sid, unsigned int pos, void *clientData);
    int  Insert(const wxString &item, const wxString &sid, unsigned int pos, wxClientData *clientData);
    void Delete(unsigned int n);
    void Clear();
    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sid;
    SwStringArray m_label;
};

#include <wx/checklst.h>
class SOWERBASEEXP SwCheckListBox : public wxCheckListBox
{
    DECLARE_DYNAMIC_CLASS(SwCheckListBox)

public:
    SwCheckListBox();
    SwCheckListBox(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, int n=0, const wxString choices[]=NULL, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name="listBox");
    virtual ~SwCheckListBox();

    int  Append(const wxString &item, const wxString &sid);
    int  Append (const wxString &item, const wxString &sid, void *clientData);
    int  Append (const wxString &item, const wxString &sid, wxClientData *clientData);
    int  Insert(const wxString &item, const wxString &sid, unsigned int pos);
    int  Insert(const wxString &item, const wxString &sid, unsigned int pos, void *clientData);
    int  Insert(const wxString &item, const wxString &sid, unsigned int pos, wxClientData *clientData);
    void Delete(unsigned int n);
    void Clear();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sid;
    SwStringArray m_label;
};

#include <wx/choice.h>
class SOWERBASEEXP SwChoice : public wxChoice
{
    DECLARE_DYNAMIC_CLASS(SwChoice)

public:
    SwChoice();
    SwChoice(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, int n=0, const wxString choices[]=NULL, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxChoiceNameStr);
    virtual ~SwChoice();

    int  Append(const wxString &item, const wxString &sid);
    int  Append (const wxString &item, const wxString &sid, void *clientData);
    int  Append (const wxString &item, const wxString &sid, wxClientData *clientData);
    void Delete(unsigned int n);
    void Clear();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sid;
    SwStringArray m_label;
};

#include <wx/dataview.h>
class SOWERBASEEXP SwDataViewListCtrl : public wxDataViewListCtrl
{
    DECLARE_DYNAMIC_CLASS(SwDataViewListCtrl)

public:
    SwDataViewListCtrl();
    SwDataViewListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDV_ROW_LINES, const wxValidator &validator=wxDefaultValidator);
    virtual ~SwDataViewListCtrl();

    wxDataViewColumn* AppendTextColumn(const wxString &label, wxDataViewCellMode mode=wxDATAVIEW_CELL_INERT, int width=-1, wxAlignment align=wxALIGN_LEFT, int flags=wxDATAVIEW_COL_RESIZABLE, const wxString &sid_heading=L"");
    wxDataViewColumn* AppendToggleColumn(const wxString &label, wxDataViewCellMode mode=wxDATAVIEW_CELL_ACTIVATABLE, int width=-1, wxAlignment align=wxALIGN_LEFT, int flags=wxDATAVIEW_COL_RESIZABLE, const wxString &sid_heading=L"");
    wxDataViewColumn* AppendProgressColumn(const wxString &label, wxDataViewCellMode mode=wxDATAVIEW_CELL_INERT, int width=-1, wxAlignment align=wxALIGN_LEFT, int flags=wxDATAVIEW_COL_RESIZABLE, const wxString &sid_heading=L"");
    bool ClearColumns();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sidColumn;
    SwStringArray m_labelColumn;
};

#include <wx/listctrl.h>
class SOWERBASEEXP SwListCtrl : public wxListCtrl
{
    DECLARE_DYNAMIC_CLASS(SwListCtrl)

public:
    SwListCtrl();
    SwListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_ICON, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);
    virtual ~SwListCtrl();

    long AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format=wxLIST_FORMAT_LEFT, int width=-1);
    long InsertItem(long index, const wxString &label, const wxString &sid);
    bool DeleteItem(long pos);
    void ClearAll();
    bool DeleteAllColumns();
    bool DeleteAllItems();
    long GetSelected();
    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sidColumn;
    SwStringArray m_labelColumn;
    SwStringArray m_sidItem;
    SwStringArray m_labelItem;
};

class SOWERBASEEXP SwListView : public wxListView
{
    DECLARE_DYNAMIC_CLASS(SwListView)

public:
    SwListView();
    SwListView(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_REPORT, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);
    virtual ~SwListView();

    long AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format=wxLIST_FORMAT_LEFT, int width=-1);
    long InsertItem(long index, const wxString &label, const wxString &sid);
    bool DeleteItem(long pos);
    void ClearAll();
    bool DeleteAllColumns();
    bool DeleteAllItems();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sidColumn;
    SwStringArray m_labelColumn;
    SwStringArray m_sidItem;
    SwStringArray m_labelItem;
};

#include <wx/radiobut.h>
class SOWERBASEEXP SwRadioButton : public wxRadioButton
{
    DECLARE_DYNAMIC_CLASS(SwRadioButton)

public:
    SwRadioButton();
    SwRadioButton(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxRadioButtonNameStr);
    virtual ~SwRadioButton();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwString m_sid;
    SwString m_label;
};

#include <wx/stattext.h>
class SOWERBASEEXP SwStaticText : public wxStaticText
{
    DECLARE_DYNAMIC_CLASS(SwStaticText)

public:
    SwStaticText();
    SwStaticText(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxStaticTextNameStr);
    virtual ~SwStaticText();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwString m_sid;
    SwString m_label;
};

#include <wx/tglbtn.h>
class SOWERBASEEXP SwBitmapToggleButton : public wxBitmapToggleButton
{
    DECLARE_DYNAMIC_CLASS(SwBitmapToggleButton)

public:
    SwBitmapToggleButton();
    SwBitmapToggleButton(wxWindow *parent, wxWindowID id, const wxBitmap &label, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxValidator &val=wxDefaultValidator, const wxString &name=wxCheckBoxNameStr);
    virtual ~SwBitmapToggleButton();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwString m_sid;
};

class SOWERBASEEXP SwStretchColumnListCtrl : public wxListCtrl
{
    DECLARE_DYNAMIC_CLASS(SwStretchColumnListCtrl)

public:
    SwStretchColumnListCtrl();
    SwStretchColumnListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_ICON, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);

    virtual ~SwStretchColumnListCtrl();

    long GetSelected();
    virtual void OnResize(wxSizeEvent& event);
    long AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format=wxLIST_FORMAT_LEFT, int width=-1);
    long InsertItem(long index, const wxString &label, const wxString &sid);
    bool DeleteItem(long pos);
    void ClearAll();
    bool DeleteAllColumns();
    bool DeleteAllItems();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sidColumn;
    SwStringArray m_labelColumn;
    SwStringArray m_sidItem;
    SwStringArray m_labelItem;
};

class SOWERBASEEXP SwStretchColumnListView : public wxListView
{
    DECLARE_DYNAMIC_CLASS(SwStretchColumnListView)

public:
    SwStretchColumnListView();
    SwStretchColumnListView(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxLC_REPORT, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxListCtrlNameStr);

    virtual ~SwStretchColumnListView();

    virtual void OnResize(wxSizeEvent& event);
    long AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format=wxLIST_FORMAT_LEFT, int width=-1);
    long InsertItem(long index, const wxString &label, const wxString &sid);
    bool DeleteItem(long pos);
    void ClearAll();
    bool DeleteAllColumns();
    bool DeleteAllItems();

    void OnLanguageChange();
    void OnThemeChange();

protected:
    SwStringArray m_sidColumn;
    SwStringArray m_labelColumn;
    SwStringArray m_sidItem;
    SwStringArray m_labelItem;
};

#endif // SOWERCONTROLS_H
