///////////////////////////////////////////////////////////////////
// Name:        controls.cpp
// Purpose:     Controls that automatically update for language,
//              and theme changes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/controls/controls.h"
#include "../../include/appi/appifa.h"

void StretchColumn(wxListCtrl * listCtrl)
{
    // Stretch column 0 to size of control.
    int h, w;
    wxListItem item;
    if (listCtrl->GetColumnCount() < 1)
        return;
    listCtrl->GetColumn(0, item);
    listCtrl->GetClientSize(&w, &h);
    item.SetWidth(w);
    listCtrl->SetColumn(0, item);
}

IMPLEMENT_DYNAMIC_CLASS(SwButton, wxButton)

SwButton::SwButton()
{
}

SwButton::SwButton(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxButton(parent, id, SwApplicationInterface::GetControlString(name.utf8_str(), label.wchar_str()), pos, size, style, validator, name)
{
    m_sid = name.utf8_str();
    m_label = label.utf8_str();
}

SwButton::~SwButton()
{
}

void SwButton::OnLanguageChange()
{
    SetLabel(SwApplicationInterface::GetControlString(m_sid, SwStringW(m_label)));
}

void SwButton::OnThemeChange()
{
}

IMPLEMENT_DYNAMIC_CLASS(SwBitmapButton, wxBitmapButton)

SwBitmapButton::SwBitmapButton()
{
}

SwBitmapButton::SwBitmapButton(wxWindow *parent, wxWindowID id, const wxBitmap &bitmap, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name)
{
    m_sid = name.utf8_str();
}

SwBitmapButton::~SwBitmapButton()
{
}

void SwBitmapButton::OnLanguageChange()
{
}

void SwBitmapButton::OnThemeChange()
{
    SetBitmap(SwApplicationInterface::GetImage(m_sid));
}

IMPLEMENT_DYNAMIC_CLASS(SwCheckBox, wxCheckBox)

SwCheckBox::SwCheckBox()
{
}

SwCheckBox::SwCheckBox(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxCheckBox(parent, id, SwApplicationInterface::GetControlString(name.utf8_str(), label.wchar_str()), pos, size, style, validator, name)
{
    m_sid = name.utf8_str();
    m_label = label.utf8_str();
}

SwCheckBox::~SwCheckBox() {}

void SwCheckBox::OnLanguageChange()
{
    SetLabel(SwApplicationInterface::GetControlString(m_sid, SwStringW(m_label)));
}

void SwCheckBox::OnThemeChange()
{
}


IMPLEMENT_DYNAMIC_CLASS(SwListBox, wxListBox)

SwListBox::SwListBox()
{
}

SwListBox::SwListBox(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, int n, const wxString choices[], long style, const wxValidator &validator, const wxString &name)
    :wxListBox(parent, id, pos, size, n, choices, style, validator, name)
{
}

SwListBox::~SwListBox()
{
}

int SwListBox::Append(const wxString &item, const wxString &sid)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxListBox::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))));
}

int SwListBox::Append(const wxString &item, const wxString &sid, void *clientData)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxListBox::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos)), clientData));
}

int SwListBox::Append(const wxString &item, const wxString &sid, wxClientData *clientData)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxListBox::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), clientData);
}

int SwListBox::Insert(const wxString &item, const wxString &sid, unsigned int pos)
{
    m_label.Insert(pos, item.utf8_str());
    m_sid.Insert(pos, sid.utf8_str());

    return wxListBox::Insert(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), pos);

}

int SwListBox::Insert(const wxString &item, const wxString &sid, unsigned int pos, void *clientData)
{
    m_label.Insert(pos, item.utf8_str());
    m_sid.Insert(pos, sid.utf8_str());

    return wxListBox::Insert(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), pos, clientData);

}

int SwListBox::Insert(const wxString &item, const wxString &sid, unsigned int pos, wxClientData *clientData)
{
    m_label.Insert(pos, item.utf8_str());
    m_sid.Insert(pos, sid.utf8_str());

    return wxListBox::Insert(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), pos, clientData);

}

void SwListBox::Delete(unsigned int n)
{
    if (m_sid.GetCount() <= n || m_label.GetCount() <= n)
        return;

    m_sid.Delete(n);
    m_label.Delete(n);

    wxListBox::Delete(n);
}

void SwListBox::Clear()
{
    m_sid.Reset();
    m_label.Reset();
    wxListBox::Clear();
}

void SwListBox::OnLanguageChange()
{
    for (swUI32 i = 0; i < m_sid.GetCount() && i < m_label.GetCount(); i ++)
    {
        SetString(i, SwApplicationInterface::GetControlString(m_sid.GetAt(i), SwStringW(m_label.GetAt(i))));
    }
}

void SwListBox::OnThemeChange()
{
}


IMPLEMENT_DYNAMIC_CLASS(SwCheckListBox, wxCheckListBox)

SwCheckListBox::SwCheckListBox()
{
}

SwCheckListBox::SwCheckListBox(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, int n, const wxString choices[], long style, const wxValidator &validator, const wxString &name)
    :wxCheckListBox(parent, id, pos, size, n, choices, style, validator, name)
{
}

SwCheckListBox::~SwCheckListBox()
{
}

int SwCheckListBox::Append(const wxString &item, const wxString &sid)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxCheckListBox::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))));
}

int SwCheckListBox::Append(const wxString &item, const wxString &sid, void *clientData)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxCheckListBox::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), clientData);
}

int SwCheckListBox::Append(const wxString &item, const wxString &sid, wxClientData *clientData)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxCheckListBox::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), clientData);
}

int SwCheckListBox::Insert(const wxString &item, const wxString &sid, unsigned int pos)
{
    m_label.Insert(pos, item.utf8_str());
    m_sid.Insert(pos, sid.utf8_str());

    return wxCheckListBox::Insert(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), pos);

}

int SwCheckListBox::Insert(const wxString &item, const wxString &sid, unsigned int pos, void *clientData)
{
    m_label.Insert(pos, item.utf8_str());
    m_sid.Insert(pos, sid.utf8_str());

    return wxCheckListBox::Insert(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), pos, clientData);

}

int SwCheckListBox::Insert(const wxString &item, const wxString &sid, unsigned int pos, wxClientData *clientData)
{
    m_label.Insert(pos, item.utf8_str());
    m_sid.Insert(pos, sid.utf8_str());

    return wxCheckListBox::Insert(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), pos, clientData);

}

void SwCheckListBox::Delete(unsigned int n)
{
    if (m_sid.GetCount() <= n || m_label.GetCount() <= n)
        return;

    m_sid.Delete(n);
    m_label.Delete(n);

    wxCheckListBox::Delete(n);
}

void SwCheckListBox::Clear()
{
    m_sid.Reset();
    m_label.Reset();
    wxCheckListBox::Clear();
}

void SwCheckListBox::OnLanguageChange()
{
    for (swUI32 i = 0; i < m_sid.GetCount() && i < m_label.GetCount(); i ++)
    {
        SetString(i, SwApplicationInterface::GetControlString(m_sid.GetAt(i), SwStringW(m_label.GetAt(i))));
    }
}

void SwCheckListBox::OnThemeChange()
{
}

IMPLEMENT_DYNAMIC_CLASS(SwChoice, wxChoice)

SwChoice::SwChoice() {}

SwChoice::SwChoice(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, int n, const wxString choices[], long style, const wxValidator &validator, const wxString &name)
    :wxChoice(parent, id, pos, size, n, choices, style, validator, name)
{
}

SwChoice::~SwChoice()
{
}

int SwChoice::Append(const wxString &item, const wxString &sid)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxChoice::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))));
}

int SwChoice::Append(const wxString &item, const wxString &sid, void *clientData)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxChoice::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), clientData);
}

int SwChoice::Append(const wxString &item, const wxString &sid, wxClientData *clientData)
{
    swUI32 pos = m_sid.GetCount();
    m_label.Add(item.utf8_str());
    m_sid.Add(sid.utf8_str());

    return wxChoice::Append(SwApplicationInterface::GetControlString(m_sid.GetAt(pos), SwStringW(m_label.GetAt(pos))), clientData);
}

void SwChoice::Delete(unsigned int n)
{
     if (m_sid.GetCount() <= n || m_label.GetCount() <= n)
        return;

    m_sid.Delete(n);
    m_label.Delete(n);

    wxChoice::Delete(n);
}

void SwChoice::Clear()
{
    m_sid.Reset();
    m_label.Reset();
    wxChoice::Clear();
}

void SwChoice::OnLanguageChange()
{
    for (swUI32 i = 0; i < m_sid.GetCount() && i < m_label.GetCount(); i ++)
    {
        SetString(i, SwApplicationInterface::GetControlString(m_sid.GetAt(i), SwStringW(m_label.GetAt(i))));
    }
}

void SwChoice::OnThemeChange()
{
}

IMPLEMENT_DYNAMIC_CLASS(SwDataViewListCtrl, wxDataViewListCtrl)


SwDataViewListCtrl::SwDataViewListCtrl()
{
}

SwDataViewListCtrl::SwDataViewListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator)
    :wxDataViewListCtrl(parent, id, pos, size, style, validator)
{
}

SwDataViewListCtrl::~SwDataViewListCtrl()
{
}

wxDataViewColumn* SwDataViewListCtrl::AppendTextColumn(const wxString &label, wxDataViewCellMode mode, int width, wxAlignment align, int flags, const wxString &sid_heading)
{
    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(label.utf8_str());

    return wxDataViewListCtrl::AppendTextColumn(label, mode, width, align, flags);
}

wxDataViewColumn* SwDataViewListCtrl::AppendToggleColumn(const wxString &label, wxDataViewCellMode mode, int width, wxAlignment align, int flags, const wxString &sid_heading)
{

    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(label.utf8_str());

    return wxDataViewListCtrl::AppendToggleColumn(label, mode, width, align, flags);
}

wxDataViewColumn* SwDataViewListCtrl::AppendProgressColumn(const wxString &label, wxDataViewCellMode mode, int width, wxAlignment align, int flags, const wxString &sid_heading)
{
    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(label.utf8_str());

    return wxDataViewListCtrl::AppendProgressColumn(label, mode, width, align, flags);
}

bool SwDataViewListCtrl::ClearColumns()
{
    m_sidColumn.Reset();
    m_labelColumn.Reset();

    return wxDataViewListCtrl::ClearColumns();
}

void SwDataViewListCtrl::OnLanguageChange()
{
    wxDataViewColumn * item;

    for (swUI32 i = 0; i < m_sidColumn.GetCount() && i < m_labelColumn.GetCount(); i ++)
    {
        item = GetColumn(i);
        item->SetTitle(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(i), SwStringW(m_labelColumn.GetAt(i))));
    }
}

void SwDataViewListCtrl::OnThemeChange()
{
}


IMPLEMENT_DYNAMIC_CLASS(SwListCtrl, wxListCtrl)

SwListCtrl::SwListCtrl()
{
    SetBackgroundColour(*wxWHITE);
}

SwListCtrl::SwListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxListCtrl(parent, id, pos, size, style, validator, name)
{
    SetBackgroundColour(*wxWHITE);
}

SwListCtrl::~SwListCtrl()
{
}

long SwListCtrl::AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format, int width)
{
    swUI32 pos = m_sidColumn.GetCount();
    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(heading.utf8_str());

    return wxListCtrl::AppendColumn(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))), format, width);
}

long SwListCtrl::InsertItem(long index, const wxString &label, const wxString &sid)
{
    m_sidItem.Insert(index, sid.utf8_str());
    m_labelItem.Insert(index, label.utf8_str());

    return wxListCtrl::InsertItem(index, label);
}

bool SwListCtrl::DeleteItem(long pos)
{
    if (m_sidItem.GetCount() && m_labelItem.GetCount())
    {
        m_sidItem.Delete(pos);
        m_labelItem.Delete(pos);
    }

    return wxListCtrl::DeleteItem(pos);
}

void SwListCtrl::ClearAll()
{
    DeleteAllItems();
    DeleteAllColumns();
    wxListCtrl::ClearAll();
}

bool SwListCtrl::DeleteAllColumns()
{
    return wxListCtrl::DeleteAllColumns();
}

bool SwListCtrl::DeleteAllItems()
{
    return wxListCtrl::DeleteAllItems();
}

long SwListCtrl::GetSelected()
{
    long item = -1;

    for (;;)
    {
        item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

        if ( item == -1 )
            break;

        return item;
    }

    return -1;
}

void SwListCtrl::OnLanguageChange()
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_TEXT);

    for (swUI32 i = 0; i < m_sidColumn.GetCount() && i < m_labelColumn.GetCount(); i ++)
    {
        item.SetColumn(i);
        item.SetText(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(i), SwStringW(m_labelColumn.GetAt(i))));
        SetColumn(i, item);
    }

    for (swUI32 pos = 0; pos < m_sidItem.GetCount() && pos < m_labelItem.GetCount(); pos ++)
    {
        SetItemText(pos, SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))));
    }
}

void SwListCtrl::OnThemeChange()
{
}

IMPLEMENT_DYNAMIC_CLASS(SwListView, wxListView)

SwListView::SwListView()
{
    SetBackgroundColour(*wxWHITE);
}

SwListView::SwListView(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxListView(parent, id, pos, size, style, validator, name)
{
    SetBackgroundColour(*wxWHITE);
}

SwListView::~SwListView()
{
}

long SwListView::AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format, int width)
{
    swUI32 pos = m_sidColumn.GetCount();
    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(heading.utf8_str());

    return wxListView::AppendColumn(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))), format, width);
}


long SwListView::InsertItem(long index, const wxString &label, const wxString &sid)
{
    m_sidItem.Insert(index, sid.utf8_str());
    m_labelItem.Insert(index, label.utf8_str());

    return wxListView::InsertItem(index, label);
}

bool SwListView::DeleteItem(long pos)
{
    m_sidItem.Delete(pos);
    m_labelItem.Delete(pos);

    return wxListView::DeleteItem(pos);
}

void SwListView::ClearAll()
{
    DeleteAllItems();
    DeleteAllColumns();
    wxListView::ClearAll();
}

bool SwListView::DeleteAllColumns()
{
    return wxListView::DeleteAllColumns();
}

bool SwListView::DeleteAllItems()
{
    return wxListView::DeleteAllItems();
}

void SwListView::OnLanguageChange()
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_TEXT);

    for (swUI32 i = 0; i < m_sidColumn.GetCount() && i < m_labelColumn.GetCount(); i ++)
    {
        item.SetColumn(i);
        item.SetText(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(i), SwStringW(m_labelColumn.GetAt(i))));
        SetColumn(i, item);
    }

    for (swUI32 pos = 0; pos < m_sidItem.GetCount() && pos < m_labelItem.GetCount(); pos ++)
    {
        SetItemText(pos, SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))));
    }
}

void SwListView::OnThemeChange()
{
}

IMPLEMENT_DYNAMIC_CLASS(SwRadioButton, wxRadioButton)

SwRadioButton::SwRadioButton()
{
}

SwRadioButton::SwRadioButton(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxRadioButton(parent, id, SwApplicationInterface::GetControlString(name.utf8_str(), label.wchar_str()), pos, size, style, validator, name)
{
    m_sid = name.utf8_str();
    m_label = label.utf8_str();
}

SwRadioButton::~SwRadioButton()
{
}

void SwRadioButton::OnLanguageChange()
{
    SetLabel(SwApplicationInterface::GetControlString(m_sid, SwStringW(m_label)));
}

void SwRadioButton::OnThemeChange()
{
}


IMPLEMENT_DYNAMIC_CLASS(SwStaticText, wxStaticText)

SwStaticText::SwStaticText() {}

SwStaticText::SwStaticText(wxWindow *parent, wxWindowID id, const wxString &label, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxStaticText(parent, id, SwApplicationInterface::GetControlString(name.utf8_str(), label.wchar_str()), pos, size, style, name)
{
    m_sid = name.utf8_str();
    m_label = label.utf8_str();
}

SwStaticText::~SwStaticText()
{
}

void SwStaticText::OnLanguageChange()
{
    SetLabel(SwApplicationInterface::GetControlString(m_sid, SwStringW(m_label)));
}

void SwStaticText::OnThemeChange()
{
}


IMPLEMENT_DYNAMIC_CLASS(SwBitmapToggleButton, wxBitmapToggleButton)

SwBitmapToggleButton::SwBitmapToggleButton()
{
}

SwBitmapToggleButton::SwBitmapToggleButton(wxWindow *parent, wxWindowID id, const wxBitmap &label, const wxPoint &pos, const wxSize &size, long style, const wxValidator &val, const wxString &name)
    :wxBitmapToggleButton(parent, id, label, pos, size, style, val, name)
{
    m_sid = name.utf8_str();
}

SwBitmapToggleButton::~SwBitmapToggleButton()
{
}

void SwBitmapToggleButton::OnLanguageChange()
{
}

void SwBitmapToggleButton::OnThemeChange()
{
    SetBitmap(SwApplicationInterface::GetImage(m_sid));
}


IMPLEMENT_DYNAMIC_CLASS(SwStretchColumnListCtrl, wxListCtrl)

SwStretchColumnListCtrl::SwStretchColumnListCtrl()
{
    SetBackgroundColour(*wxWHITE);
}

SwStretchColumnListCtrl::SwStretchColumnListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxListCtrl(parent, id, pos, size, style, validator, name)
{
    SetBackgroundColour(*wxWHITE);
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchColumnListCtrl::OnResize);
}

SwStretchColumnListCtrl::~SwStretchColumnListCtrl()
{
}

long SwStretchColumnListCtrl::GetSelected()
{
    long item = -1;

    for (;;)
    {
        item = GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

        if ( item == -1 )
            break;

        return item;
    }

    return -1;
}

void SwStretchColumnListCtrl::OnResize(wxSizeEvent& event)
{
    StretchColumn(this);
    event.Skip();
}

long SwStretchColumnListCtrl::AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format, int width)
{
    swUI32 pos = m_sidColumn.GetCount();
    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(heading.utf8_str());

    return wxListCtrl::AppendColumn(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))), format, width);
}

long SwStretchColumnListCtrl::InsertItem(long index, const wxString &label, const wxString &sid)
{
    m_sidItem.Insert(index, sid.utf8_str());
    m_labelItem.Insert(index, label.utf8_str());

    return wxListCtrl::InsertItem(index, label);
}

bool SwStretchColumnListCtrl::DeleteItem(long pos)
{
    m_sidItem.Delete(pos);
    m_labelItem.Delete(pos);

    return wxListCtrl::DeleteItem(pos);
}

void SwStretchColumnListCtrl::ClearAll()
{
    DeleteAllItems();
    DeleteAllColumns();
    wxListCtrl::ClearAll();
}

bool SwStretchColumnListCtrl::DeleteAllColumns()
{
    return wxListCtrl::DeleteAllColumns();
}

bool SwStretchColumnListCtrl::DeleteAllItems()
{
    return wxListCtrl::DeleteAllItems();
}

void SwStretchColumnListCtrl::OnLanguageChange()
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_TEXT);

    for (swUI32 i = 0; i < m_sidColumn.GetCount() && i < m_labelColumn.GetCount(); i ++)
    {
        item.SetColumn(i);
        item.SetText(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(i), SwStringW(m_labelColumn.GetAt(i))));
        SetColumn(i, item);
    }

    for (swUI32 pos = 0; pos < m_sidItem.GetCount() && pos < m_labelItem.GetCount(); pos ++)
    {
        SetItemText(pos, SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))));
    }
}

void SwStretchColumnListCtrl::OnThemeChange()
{
}


IMPLEMENT_DYNAMIC_CLASS(SwStretchColumnListView, wxListView)

SwStretchColumnListView::SwStretchColumnListView()
{
    SetBackgroundColour(*wxWHITE);
}

SwStretchColumnListView::SwStretchColumnListView(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxListView(parent, id, pos, size, style, validator, name)
{
    SetBackgroundColour(*wxWHITE);
    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchColumnListCtrl::OnResize);Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwStretchColumnListCtrl::OnResize);
}

SwStretchColumnListView::~SwStretchColumnListView()
{
}

void SwStretchColumnListView::OnResize(wxSizeEvent& event)
{
    StretchColumn(this);
    event.Skip();
}

long SwStretchColumnListView::AppendColumn(const wxString &sid_heading, const wxString &heading, wxListColumnFormat format, int width)
{
    swUI32 pos = m_sidColumn.GetCount();
    m_sidColumn.Add(sid_heading.utf8_str());
    m_labelColumn.Add(heading.utf8_str());

    return wxListView::AppendColumn(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))), format, width);
}

long SwStretchColumnListView::InsertItem(long index, const wxString &label, const wxString &sid)
{
    m_sidItem.Insert(index, sid.utf8_str());
    m_labelItem.Insert(index, label.utf8_str());

    return wxListView::InsertItem(index, label);
}

bool SwStretchColumnListView::DeleteItem(long pos)
{
    m_sidItem.Delete(pos);
    m_labelItem.Delete(pos);

    return wxListView::DeleteItem(pos);
}

void SwStretchColumnListView::ClearAll()
{
    DeleteAllItems();
    DeleteAllColumns();
    wxListView::ClearAll();
}

bool SwStretchColumnListView::DeleteAllColumns()
{
    return wxListView::DeleteAllColumns();
}

bool SwStretchColumnListView::DeleteAllItems()
{
    return wxListView::DeleteAllItems();
}

void SwStretchColumnListView::OnLanguageChange()
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_TEXT);

    for (swUI32 i = 0; i < m_sidColumn.GetCount() && i < m_labelColumn.GetCount(); i ++)
    {
        item.SetColumn(i);
        item.SetText(SwApplicationInterface::GetControlString(m_sidColumn.GetAt(i), SwStringW(m_labelColumn.GetAt(i))));
        SetColumn(i, item);
    }

    for (swUI32 pos = 0; pos < m_sidItem.GetCount() && pos < m_labelItem.GetCount(); pos ++)
    {
        SetItemText(pos, SwApplicationInterface::GetControlString(m_sidColumn.GetAt(pos), SwStringW(m_labelColumn.GetAt(pos))));
    }
}

void SwStretchColumnListView::OnThemeChange()
{
}
