///////////////////////////////////////////////////////////////////
// Name:        richtextembeddedcontrol.cpp
// Purpose:     Embeddable controls for RichTextCtrlExt.
// Copyright:   David Reynolds.
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/objects/richtextembeddedcontrol.h"
#include "../../../include/richtext/richtextctrlext.h"
#include "../../../include/html/html_color.h"
#include <wx/treebase.h>
#include <wx/treectrl.h>
#include <wx/richtext/richtextxml.h>
#include <wx/xml/xml.h>
#include <wx/sstream.h>
#include "../../../include/html/html_datalist.h"

IMPLEMENT_DYNAMIC_CLASS(RichTextSowerAudioCtrl, RichTextControlBase)


RichTextSowerAudioCtrl::RichTextSowerAudioCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle)
    :RichTextControlBase(parent, charStyle)
{
}

RichTextSowerAudioCtrl::RichTextSowerAudioCtrl(wxRichTextObject* parent)
: RichTextControlBase(parent)
{
}

RichTextSowerAudioCtrl::~RichTextSowerAudioCtrl()
{
    //dtor
    if (m_control)
    {
        delete m_control;
    }
}

void RichTextSowerAudioCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    SowerAudioCtrl * control = new SowerAudioCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());
    control->BuildContent();
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);

    if (m_cattr.GetModuleId() != NODE_ID_INVALID_16)
    {
        if (!control->OnOpen(m_cattr.GetModuleId(), m_cattr.GetSource()))
            return;
    }
    else
    {
        BasicBuffer resolvedPath;
        ResolveFilePath(resolvedPath);

        if (wxFile::Exists((char *) resolvedPath))
        {
            if (!control->OnOpen(resolvedPath))
                return;
        }
    }

    if (m_cattr.GetAutoPlay())
        control->OnAutoPlay();
}

wxRichTextObject* RichTextSowerAudioCtrl::Clone() const { return new RichTextSowerAudioCtrl(*this); }
wxString RichTextSowerAudioCtrl::GetXMLNodeName() const { return "soweraudiocontrol"; }
int RichTextSowerAudioCtrl::GetControlType() {return RT_CONTROL_SOWERAUDIOCTRL;}

IMPLEMENT_DYNAMIC_CLASS(RichTextButton, RichTextControlBase)


RichTextButton::RichTextButton(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle)
    :RichTextControlBase(parent, charStyle)
{
}

RichTextButton::RichTextButton(wxRichTextObject* parent)
: RichTextControlBase(parent)
{
}

RichTextButton::~RichTextButton()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &RichTextButton::OnButtonClick, this);
        delete m_control;
    }
}

void RichTextButton::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxButton * control = new wxButton;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &RichTextButton::OnButtonClick, this);
}

void RichTextButton::OnButtonClick(wxCommandEvent& event)
{
    m_owner->OnButtonClick(event, (RichTextControlBase *) this);
    event.Skip();
}

wxRichTextObject* RichTextButton::Clone() const { return new RichTextButton(*this); }
wxString RichTextButton::GetXMLNodeName() const { return "button"; }
int RichTextButton::GetControlType() {return RT_CONTROL_BUTTON;}

IMPLEMENT_DYNAMIC_CLASS(RichTextCheckBox, RichTextControlBase)


RichTextCheckBox::RichTextCheckBox(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle)
    :RichTextControlBase(parent, charStyle)
{
}

RichTextCheckBox::RichTextCheckBox(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextCheckBox::~RichTextCheckBox()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_CHECKBOX_CLICKED, &RichTextCheckBox::OnCheckBoxClick, this);
        delete m_control;
    }
}

void RichTextCheckBox::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;
    RichTextControlBase::CreateControl(NULL);
    wxCheckBox * control = new wxCheckBox;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, m_cattr.GetStyle());

    control->SetValue(m_cattr.GetChecked());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_CHECKBOX_CLICKED, &RichTextCheckBox::OnCheckBoxClick, this);
}

wxRichTextObject* RichTextCheckBox::Clone() const { return new RichTextCheckBox(*this); }
wxString RichTextCheckBox::GetXMLNodeName() const { return "checkbox"; }
int RichTextCheckBox::GetControlType() {return RT_CONTROL_CHECKBOX;}

void RichTextCheckBox::OnCheckBoxClick(wxCommandEvent& event)
{
    m_owner->OnCheckBoxClick(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextChoice, RichTextControlBase)

RichTextChoice::RichTextChoice(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{
}

RichTextChoice::RichTextChoice(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextChoice::~RichTextChoice()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_CHOICE_SELECTED, &RichTextChoice::OnChoice, this);
        delete m_control;
    }
}

void RichTextChoice::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;
    RichTextControlBase::CreateControl(NULL);
    wxChoice * control = new wxChoice;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    wxUint32 id = m_owner->m_datalistArray.FindDataList(m_cattr.GetDataListName());

    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;
            TranslateValue(data->GetValue(), buffer);
            control->Append((char *) buffer);
            pos ++;
        }
    }
    else if (!m_owner->LoadControlData((RichTextControlBase *)this))
    {
        StrList strlist;
        strlist.ParseString(m_cattr.GetValue());
        for (wxUint32 i = 0; i < strlist.GetItems(); i++)
        {
            TranslateValue(strlist.GetItem(i), buffer);
            control->Append((char *) buffer);
        }
    }

    if (control->GetCount())
        control->SetSelection(0);

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &RichTextChoice::OnChoice, this);
}

wxRichTextObject* RichTextChoice::Clone() const { return new RichTextChoice(*this); }
wxString RichTextChoice::GetXMLNodeName() const { return "choice"; }
int RichTextChoice::GetControlType() {return RT_CONTROL_CHOICE;}

void RichTextChoice::OnChoice(wxCommandEvent& event)
{
    m_owner->OnChoice(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextComboBox, RichTextControlBase)

RichTextComboBox::RichTextComboBox(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{
}

RichTextComboBox::RichTextComboBox(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextComboBox::~RichTextComboBox()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_COMBOBOX, &RichTextComboBox::OnComboBoxSelected, this);
        m_control->Unbind(wxEVT_TEXT, &RichTextComboBox::OnComboBoxText, this);
        m_control->Unbind(wxEVT_TEXT_ENTER, &RichTextComboBox::OnComboBoxTextEnter, this);
        m_control->Unbind(wxEVT_COMBOBOX_DROPDOWN, &RichTextComboBox::OnComboBoxDropDown, this);
        m_control->Unbind(wxEVT_COMBOBOX_CLOSEUP, &RichTextComboBox::OnComboBoxCloseUp, this);

        delete m_control;
    }
}

void RichTextComboBox::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;
    RichTextControlBase::CreateControl(NULL);
    wxComboBox * control = new wxComboBox;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, 0, NULL, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    wxUint32 id = m_owner->m_datalistArray.FindDataList(m_cattr.GetDataListName());

    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;
            TranslateValue(data->GetValue(), buffer);
            control->Append((char *) buffer);
            pos ++;
        }

    }
    else if (!m_owner->LoadControlData((RichTextControlBase *)this))
    {
        StrList strlist;
        strlist.ParseString(m_cattr.GetValue());
        for (wxUint32 i = 0; i < strlist.GetItems(); i++)
        {
            TranslateValue(strlist.GetItem(i), buffer);
            control->Append((char *) buffer);
        }
    }


    if (control->GetCount())
        control->SetSelection(0);

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMBOBOX, &RichTextComboBox::OnComboBoxSelected, this);
    m_control->Bind(wxEVT_TEXT, &RichTextComboBox::OnComboBoxText, this);
    m_control->Bind(wxEVT_TEXT_ENTER, &RichTextComboBox::OnComboBoxTextEnter, this);
    m_control->Bind(wxEVT_COMBOBOX_DROPDOWN, &RichTextComboBox::OnComboBoxDropDown, this);
    m_control->Bind(wxEVT_COMBOBOX_CLOSEUP, &RichTextComboBox::OnComboBoxCloseUp, this);
}

wxRichTextObject* RichTextComboBox::Clone() const { return new RichTextComboBox(*this); }
wxString RichTextComboBox::GetXMLNodeName() const { return "combobox"; }
int RichTextComboBox::GetControlType() {return RT_CONTROL_COMBOBOX;}

void RichTextComboBox::OnComboBoxSelected(wxCommandEvent& event)
{
    m_owner->OnComboBoxSelected(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextComboBox::OnComboBoxText(wxCommandEvent& event)
{
    m_owner->OnText(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextComboBox::OnComboBoxTextEnter(wxCommandEvent& event)
{
    m_owner->OnTextEnter(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextComboBox::OnComboBoxDropDown(wxCommandEvent& event)
{
    m_owner->OnComboBoxDropDown(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextComboBox::OnComboBoxCloseUp(wxCommandEvent& event)
{
    m_owner->OnComboBoxCloseUp(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextDatePicker, RichTextControlBase)

RichTextDatePicker::RichTextDatePicker(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{
  /*  Init();
    if (charStyle)
        SetAttributes(*charStyle);*/
}

RichTextDatePicker::RichTextDatePicker(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextDatePicker::~RichTextDatePicker()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_DATE_CHANGED, &RichTextDatePicker::OnDateChanged, this);
        delete m_control;
    }
}

void RichTextDatePicker::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxDatePickerCtrl * control = new wxDatePickerCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxDP_DEFAULT|wxDP_SHOWCENTURY);

    wxDateTime dt;

    if (m_cattr.GetValue())
        dt.ParseISODate(m_cattr.GetValue());

    control->Create((wxWindow *) m_owner, m_controlId, dt, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_DATE_CHANGED, &RichTextDatePicker::OnDateChanged, this);
}

wxRichTextObject* RichTextDatePicker::Clone() const { return new RichTextDatePicker(*this); }
wxString RichTextDatePicker::GetXMLNodeName() const { return "datepicker"; }
int RichTextDatePicker::GetControlType() {return RT_CONTROL_DATEPICKER;}

void RichTextDatePicker::OnDateChanged(wxDateEvent& event)
{
    m_owner->OnDateChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextDirCtrl, RichTextControlBase)

RichTextDirCtrl::RichTextDirCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{
}

RichTextDirCtrl::RichTextDirCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextDirCtrl::~RichTextDirCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_DIRCTRL_SELECTIONCHANGED, &RichTextDirCtrl::OnDirCtrlSelectionChanged, this);
        m_control->Unbind(wxEVT_DIRCTRL_FILEACTIVATED, &RichTextDirCtrl::OnDirCtrlFileActivated, this);
        delete m_control;
    }

}

void RichTextDirCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;
    RichTextControlBase::CreateControl(NULL);
    wxGenericDirCtrl * control = new wxGenericDirCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxDIRCTRL_3D_INTERNAL);

    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValue(), point, size, m_cattr.GetStyle(), m_cattr.GetFilter());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_DIRCTRL_SELECTIONCHANGED, &RichTextDirCtrl::OnDirCtrlSelectionChanged, this);
    m_control->Bind(wxEVT_DIRCTRL_FILEACTIVATED, &RichTextDirCtrl::OnDirCtrlFileActivated, this);
}

wxRichTextObject* RichTextDirCtrl::Clone() const { return new RichTextDirCtrl(*this); }
wxString RichTextDirCtrl::GetXMLNodeName() const { return "dirctrl"; }
int RichTextDirCtrl::GetControlType() {return RT_CONTROL_DIRCTRL;}

void RichTextDirCtrl::OnDirCtrlSelectionChanged(wxCommandEvent& event)
{
    m_owner->OnDirCtrlSelectionChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDirCtrl::OnDirCtrlFileActivated(wxCommandEvent& event)
{
    m_owner->OnDirCtrlFileActivated(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextListBox, RichTextControlBase)

RichTextListBox::RichTextListBox(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextListBox::RichTextListBox(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextListBox::~RichTextListBox()
{
    //dtor

    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_LISTBOX_SELECTED, &RichTextListBox::OnListBoxSelected, this);
        m_control->Unbind(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, &RichTextListBox::OnListBoxDbClicked, this);
        delete m_control;
    }

}

void RichTextListBox::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxListBox * control = new wxListBox;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    control->Create((wxWindow *) m_owner, m_controlId, point, size, 0, NULL, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();
    BasicBuffer buffer;
    wxUint32 id = m_owner->m_datalistArray.FindDataList(m_cattr.GetDataListName());

    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;
            TranslateValue(data->GetValue(), buffer);
            control->Append((char *) buffer);
            pos ++;
        }
    }
    else if (!m_owner->LoadControlData((RichTextControlBase *)this))
    {
        StrList strlist;
        strlist.ParseString(m_cattr.GetValue());
        for (wxUint32 i = 0; i < strlist.GetItems(); i++)
        {
            TranslateValue(strlist.GetItem(i), buffer);
            control->Append((char *) buffer);
        }
    }

    if (control->GetCount())
        control->SetSelection(0);

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, &RichTextListBox::OnListBoxSelected, this);
    m_control->Bind(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, &RichTextListBox::OnListBoxDbClicked, this);
}

wxRichTextObject* RichTextListBox::Clone() const { return new RichTextListBox(*this); }
wxString RichTextListBox::GetXMLNodeName() const { return "listbox"; }
int RichTextListBox::GetControlType() {return RT_CONTROL_LISTBOX;}

void RichTextListBox::OnListBoxSelected(wxCommandEvent& event)
{
    m_owner->OnListBoxSelected(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListBox::OnListBoxDbClicked(wxCommandEvent& event)
{
    m_owner->OnListBoxDbClicked(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextCheckListBox, RichTextControlBase)

RichTextCheckListBox::RichTextCheckListBox(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextCheckListBox::RichTextCheckListBox(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextCheckListBox::~RichTextCheckListBox()
{
    //dtor

    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_LISTBOX_SELECTED, &RichTextCheckListBox::OnListBoxSelected, this);
        m_control->Unbind(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, &RichTextCheckListBox::OnListBoxDbClicked, this);
        m_control->Unbind(wxEVT_CHECKLISTBOX, &RichTextCheckListBox::OnCheckListBox, this);
        delete m_control;
    }

}

void RichTextCheckListBox::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxCheckListBox * control = new wxCheckListBox;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    BasicBuffer buffer;
    InitControl();

    wxUint32 id = m_owner->m_datalistArray.FindDataList(m_cattr.GetDataListName());

    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        unsigned int item;

        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;

            TranslateValue(data->GetValue(), buffer);
            item = control->Append((char *) buffer);
            control->Check(item, data->GetChecked());

            pos ++;
        }
    }
    else
        m_owner->LoadControlData((RichTextControlBase *)this);

    TranslateValue(m_cattr.GetValue(), buffer);
    control->SetStringSelection((char *) buffer);
    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_LISTBOX_SELECTED, &RichTextCheckListBox::OnListBoxSelected, this);
    m_control->Bind(wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, &RichTextCheckListBox::OnListBoxDbClicked, this);
    m_control->Bind(wxEVT_CHECKLISTBOX, &RichTextCheckListBox::OnCheckListBox, this);
}

wxRichTextObject* RichTextCheckListBox::Clone() const { return new RichTextCheckListBox(*this); }
wxString RichTextCheckListBox::GetXMLNodeName() const { return "checklistbox"; }
int RichTextCheckListBox::GetControlType() {return RT_CONTROL_CHECKBOX;}

void RichTextCheckListBox::OnListBoxSelected(wxCommandEvent& event)
{
    m_owner->OnListBoxSelected(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextCheckListBox::OnListBoxDbClicked(wxCommandEvent& event)
{
    m_owner->OnListBoxDbClicked(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextCheckListBox::OnCheckListBox(wxCommandEvent& event)
{
    m_owner->OnCheckListBox(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextRadioButton, RichTextControlBase)

RichTextRadioButton::RichTextRadioButton(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextRadioButton::RichTextRadioButton(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextRadioButton::~RichTextRadioButton()
{
    //dtor

    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_RADIOBUTTON_SELECTED, &RichTextRadioButton::OnRadioButtonSelected, this);
        delete m_control;
    }
}

void RichTextRadioButton::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxRadioButton * control = new wxRadioButton;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, wxRB_SINGLE);

    control->SetValue(m_cattr.GetChecked());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_RADIOBUTTON_SELECTED, &RichTextRadioButton::OnRadioButtonSelected, this);
}

wxRichTextObject* RichTextRadioButton::Clone() const { return new RichTextRadioButton(*this); }
wxString RichTextRadioButton::GetXMLNodeName() const { return "radiobutton"; }
int RichTextRadioButton::GetControlType() {return RT_CONTROL_RADIOBUTTON;}

void RichTextRadioButton::OnRadioButtonSelected(wxCommandEvent& event)
{
    m_owner->PreOnRadioButtonSelected(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextSearchCtrl, RichTextControlBase)

RichTextSearchCtrl::RichTextSearchCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextSearchCtrl::RichTextSearchCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextSearchCtrl::~RichTextSearchCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_SEARCHCTRL_SEARCH_BTN, &RichTextSearchCtrl::OnSearchCtrlSearchBtn, this);
        m_control->Unbind(wxEVT_SEARCHCTRL_CANCEL_BTN, &RichTextSearchCtrl::OnSearchCtrlCancelBtn, this);
        m_control->Unbind(wxEVT_TEXT_ENTER, &RichTextSearchCtrl::OnSearchCtrlTextEnter, this);
        m_control->Unbind(wxEVT_TEXT, &RichTextSearchCtrl::OnSearchCtrlText, this);
        delete m_control;
    }
}

void RichTextSearchCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxSearchCtrl * control = new wxSearchCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);

    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &RichTextSearchCtrl::OnSearchCtrlSearchBtn, this);
    m_control->Bind(wxEVT_SEARCHCTRL_CANCEL_BTN, &RichTextSearchCtrl::OnSearchCtrlCancelBtn, this);
    m_control->Bind(wxEVT_TEXT_ENTER, &RichTextSearchCtrl::OnSearchCtrlTextEnter, this);
    m_control->Bind(wxEVT_TEXT, &RichTextSearchCtrl::OnSearchCtrlText, this);
}

wxRichTextObject* RichTextSearchCtrl::Clone() const { return new RichTextSearchCtrl(*this); }
wxString RichTextSearchCtrl::GetXMLNodeName() const { return "searchctrl"; }
int RichTextSearchCtrl::GetControlType() {return RT_CONTROL_SEARCHCTRL;}

void RichTextSearchCtrl::OnSearchCtrlSearchBtn(wxCommandEvent& event)
{
    m_owner->OnSearchCtrlSearchBtn(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSearchCtrl::OnSearchCtrlCancelBtn(wxCommandEvent& event)
{
    m_owner->OnSearchCtrlCancelBtn(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSearchCtrl::OnSearchCtrlTextEnter(wxCommandEvent& event)
{
    m_owner->OnTextEnter(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSearchCtrl::OnSearchCtrlText(wxCommandEvent& event)
{
    m_owner->OnText(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextSpinCtrl, RichTextControlBase)

RichTextSpinCtrl::RichTextSpinCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextSpinCtrl::RichTextSpinCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextSpinCtrl::~RichTextSpinCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_SPINCTRL, &RichTextSpinCtrl::OnSpinCtrlUpdated, this);
        m_control->Unbind(wxEVT_TEXT_ENTER, &RichTextSpinCtrl::OnSpinCtrlEnter, this);
        delete m_control;
    }
}

void RichTextSpinCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxSpinCtrl * control = new wxSpinCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxSP_ARROW_KEYS);

    control->Create((wxWindow *) m_owner, m_controlId, "", point, size, m_cattr.GetStyle(), m_cattr.GetMinValueAsInt(), m_cattr.GetMaxValueAsInt(), m_cattr.GetValueAsInt());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_SPINCTRL, &RichTextSpinCtrl::OnSpinCtrlUpdated, this);
    m_control->Bind(wxEVT_TEXT_ENTER, &RichTextSpinCtrl::OnSpinCtrlEnter, this);
}

wxRichTextObject* RichTextSpinCtrl::Clone() const { return new RichTextSpinCtrl(*this); }
wxString RichTextSpinCtrl::GetXMLNodeName() const { return "spinctrl"; }
int RichTextSpinCtrl::GetControlType() {return RT_CONTROL_SPINCTRL;}

void RichTextSpinCtrl::OnSpinCtrlUpdated(wxCommandEvent& event)
{
    m_owner->OnSpinCtrlUpdated(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSpinCtrl::OnSpinCtrlEnter(wxCommandEvent& event)
{
    m_owner->OnTextEnter(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextSpinCtrlDb, RichTextControlBase)

RichTextSpinCtrlDb::RichTextSpinCtrlDb(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextSpinCtrlDb::RichTextSpinCtrlDb(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextSpinCtrlDb::~RichTextSpinCtrlDb()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_SPINCTRLDOUBLE, &RichTextSpinCtrlDb::OnSpinCtrlDouble, this);
        delete m_control;
    }
}

void RichTextSpinCtrlDb::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxSpinCtrlDouble * control = new wxSpinCtrlDouble;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxSP_ARROW_KEYS);

    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValue(), point, size, m_cattr.GetStyle(), m_cattr.GetMinValueAsDouble(), m_cattr.GetMaxValueAsDouble(), m_cattr.GetValueAsDouble(), m_cattr.GetStepAsDouble());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_SPINCTRLDOUBLE, &RichTextSpinCtrlDb::OnSpinCtrlDouble, this);
}

wxRichTextObject* RichTextSpinCtrlDb::Clone() const { return new RichTextSpinCtrlDb(*this); }
wxString RichTextSpinCtrlDb::GetXMLNodeName() const { return "spinctrldb"; }
int RichTextSpinCtrlDb::GetControlType() {return RT_CONTROL_SPINCTRLDB;}

void RichTextSpinCtrlDb::OnSpinCtrlDouble(wxSpinDoubleEvent& event)
{
    m_owner->OnSpinCtrlDouble(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextTimePicker, RichTextControlBase)

RichTextTimePicker::RichTextTimePicker(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextTimePicker::RichTextTimePicker(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextTimePicker::~RichTextTimePicker()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_TIME_CHANGED, &RichTextTimePicker::OnTimeChanged, this);
        delete m_control;
    }
}

void RichTextTimePicker::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxTimePickerCtrl * control = new wxTimePickerCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxTP_DEFAULT);

    wxDateTime dt;

    if (m_cattr.GetValue())
        dt.ParseISOTime(m_cattr.GetValue());

    control->Create((wxWindow *) m_owner, m_controlId, dt, point, size, m_cattr.GetStyle());
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_TIME_CHANGED, &RichTextTimePicker::OnTimeChanged, this);
}

wxRichTextObject* RichTextTimePicker::Clone() const { return new RichTextTimePicker(*this); }
wxString RichTextTimePicker::GetXMLNodeName() const { return "timepicker"; }
int RichTextTimePicker::GetControlType() {return RT_CONTROL_TIMEPICKER;}

void RichTextTimePicker::OnTimeChanged(wxDateEvent& event)
{
    m_owner->OnTimeChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextMediaCtrl, RichTextControlBase)

RichTextMediaCtrl::RichTextMediaCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextMediaCtrl::RichTextMediaCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextMediaCtrl::~RichTextMediaCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_MEDIA_LOADED, &RichTextMediaCtrl::OnMediaLoaded, this);
        m_control->Unbind(wxEVT_MEDIA_STOP, &RichTextMediaCtrl::OnMediaStopped, this);
        m_control->Unbind(wxEVT_MEDIA_STATECHANGED, &RichTextMediaCtrl::OnMediaStateChanged, this);
        m_control->Unbind(wxEVT_MEDIA_PAUSE, &RichTextMediaCtrl::OnMediaPaused, this);
        m_control->Unbind(wxEVT_MEDIA_FINISHED, &RichTextMediaCtrl::OnMediaFinished, this);
        m_control->Unbind(wxEVT_MEDIA_PLAY, &RichTextMediaCtrl::OnMediaPlay, this);
        delete m_control;
    }
}

void RichTextMediaCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxMediaCtrl * control = new wxMediaCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (!strlen(m_cattr.GetSource()))
    {
        control->Create((wxWindow *) m_owner, m_controlId, "", point, size, m_cattr.GetStyle());
    }
    else
    {
        BasicBuffer resolvedPath;
        ResolveFilePath(resolvedPath);

        if (wxFile::Exists((char *) resolvedPath))
            control->Create((wxWindow *) m_owner, m_controlId, (char *) resolvedPath, point, size, m_cattr.GetStyle());
    }

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_MEDIA_LOADED, &RichTextMediaCtrl::OnMediaLoaded, this);
    m_control->Bind(wxEVT_MEDIA_STOP, &RichTextMediaCtrl::OnMediaStopped, this);
    m_control->Bind(wxEVT_MEDIA_STATECHANGED, &RichTextMediaCtrl::OnMediaStateChanged, this);
    m_control->Bind(wxEVT_MEDIA_PAUSE, &RichTextMediaCtrl::OnMediaPaused, this);
    m_control->Bind(wxEVT_MEDIA_FINISHED, &RichTextMediaCtrl::OnMediaFinished, this);
    m_control->Bind(wxEVT_MEDIA_PLAY, &RichTextMediaCtrl::OnMediaPlay, this);
}

wxRichTextObject* RichTextMediaCtrl::Clone() const { return new RichTextMediaCtrl(*this); }
wxString RichTextMediaCtrl::GetXMLNodeName() const { return "mediactrl"; }
int RichTextMediaCtrl::GetControlType() {return RT_CONTROL_MEDIACTRL;}

void RichTextMediaCtrl::OnMediaLoaded(wxMediaEvent& event)
{
    m_owner->OnMediaLoaded(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextMediaCtrl::OnMediaStopped(wxMediaEvent& event)
{
    m_owner->OnMediaStopped(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextMediaCtrl::OnMediaPaused(wxMediaEvent& event)
{
    m_owner->OnMediaPaused(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextMediaCtrl::OnMediaPlay(wxMediaEvent& event)
{
    m_owner->OnMediaPlay(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextMediaCtrl::OnMediaFinished(wxMediaEvent& event)
{
    m_owner->OnMediaFinished(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextMediaCtrl::OnMediaStateChanged(wxMediaEvent& event)
{
    m_owner->OnMediaStateChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextTreeCtrl, RichTextControlBase)

RichTextTreeCtrl::RichTextTreeCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextTreeCtrl::RichTextTreeCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextTreeCtrl::~RichTextTreeCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_TREE_BEGIN_DRAG, &RichTextTreeCtrl::OnTreeBeginDrag, this);
        m_control->Unbind(wxEVT_TREE_BEGIN_RDRAG, &RichTextTreeCtrl::OnTreeBeginRDrag, this);
        m_control->Unbind(wxEVT_TREE_END_DRAG, &RichTextTreeCtrl::OnTreeEndDrag, this);
        m_control->Unbind(wxEVT_TREE_BEGIN_LABEL_EDIT, &RichTextTreeCtrl::OnTreeBeginLabelEdit, this);
        m_control->Unbind(wxEVT_TREE_END_LABEL_EDIT, &RichTextTreeCtrl::OnTreeEndLabelEdit, this);
        m_control->Unbind(wxEVT_TREE_DELETE_ITEM, &RichTextTreeCtrl::OnTreeDeleteItem, this);
        m_control->Unbind(wxEVT_TREE_GET_INFO, &RichTextTreeCtrl::OnTreeGetInfo, this);
        m_control->Unbind(wxEVT_TREE_SET_INFO, &RichTextTreeCtrl::OnTreeSetInfo, this);
        m_control->Unbind(wxEVT_TREE_ITEM_ACTIVATED, &RichTextTreeCtrl::OnTreeItemActivated, this);
        m_control->Unbind(wxEVT_TREE_ITEM_COLLAPSED, &RichTextTreeCtrl::OnTreeItemCollapsed, this);
        m_control->Unbind(wxEVT_TREE_ITEM_COLLAPSING, &RichTextTreeCtrl::OnTreeItemCollapsing, this);
        m_control->Unbind(wxEVT_TREE_ITEM_EXPANDED, &RichTextTreeCtrl::OnTreeExpanded, this);
        m_control->Unbind(wxEVT_TREE_ITEM_EXPANDING, &RichTextTreeCtrl::OnTreeExpanding, this);
        m_control->Unbind(wxEVT_TREE_ITEM_RIGHT_CLICK, &RichTextTreeCtrl::OnTreeItemRightClick, this);
        m_control->Unbind(wxEVT_TREE_ITEM_MIDDLE_CLICK, &RichTextTreeCtrl::OnTreeItemMiddleClick, this);
        m_control->Unbind(wxEVT_TREE_SEL_CHANGED, &RichTextTreeCtrl::OnTreeSelChanged, this);
        m_control->Unbind(wxEVT_TREE_SEL_CHANGING, &RichTextTreeCtrl::OnTreeSelChanging, this);
        m_control->Unbind(wxEVT_TREE_KEY_DOWN, &RichTextTreeCtrl::OnTreeKeyDown, this);
        m_control->Unbind(wxEVT_TREE_ITEM_GETTOOLTIP, &RichTextTreeCtrl::OnTreeItemGetToolTip, this);
        m_control->Unbind(wxEVT_TREE_ITEM_MENU, &RichTextTreeCtrl::OnTreeItemMenu, this);
        m_control->Unbind(wxEVT_TREE_STATE_IMAGE_CLICK, &RichTextTreeCtrl::OnTreeStateImageClick, this);
        delete m_control;
    }
}

void RichTextTreeCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxTreeCtrl * control = new wxTreeCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxTR_DEFAULT_STYLE|wxTR_HAS_BUTTONS|wxTR_TWIST_BUTTONS);

    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);
    BasicBuffer buffer;
    InitControl();
    wxUint32 id = m_owner->m_datalistArray.FindDataList(m_cattr.GetDataListName());
    TREE_APPEND_DATA_EMBEDDED tad;
    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;
            TranslateValue(data->GetValue(), buffer);
            AppendItemEx_(control, (char *) buffer, tad, -1, -1, data->GetDepth());
            pos ++;
        }
    }
    else
        m_owner->LoadControlData((RichTextControlBase *)this);

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_TREE_BEGIN_DRAG, &RichTextTreeCtrl::OnTreeBeginDrag, this);
    m_control->Bind(wxEVT_TREE_BEGIN_RDRAG, &RichTextTreeCtrl::OnTreeBeginRDrag, this);
    m_control->Bind(wxEVT_TREE_END_DRAG, &RichTextTreeCtrl::OnTreeEndDrag, this);
    m_control->Bind(wxEVT_TREE_BEGIN_LABEL_EDIT, &RichTextTreeCtrl::OnTreeBeginLabelEdit, this);
    m_control->Bind(wxEVT_TREE_END_LABEL_EDIT, &RichTextTreeCtrl::OnTreeEndLabelEdit, this);
    m_control->Bind(wxEVT_TREE_DELETE_ITEM, &RichTextTreeCtrl::OnTreeDeleteItem, this);
    m_control->Bind(wxEVT_TREE_GET_INFO, &RichTextTreeCtrl::OnTreeGetInfo, this);
    m_control->Bind(wxEVT_TREE_SET_INFO, &RichTextTreeCtrl::OnTreeSetInfo, this);
    m_control->Bind(wxEVT_TREE_ITEM_ACTIVATED, &RichTextTreeCtrl::OnTreeItemActivated, this);
    m_control->Bind(wxEVT_TREE_ITEM_COLLAPSED, &RichTextTreeCtrl::OnTreeItemCollapsed, this);
    m_control->Bind(wxEVT_TREE_ITEM_COLLAPSING, &RichTextTreeCtrl::OnTreeItemCollapsing, this);
    m_control->Bind(wxEVT_TREE_ITEM_EXPANDED, &RichTextTreeCtrl::OnTreeExpanded, this);
    m_control->Bind(wxEVT_TREE_ITEM_EXPANDING, &RichTextTreeCtrl::OnTreeExpanding, this);
    m_control->Bind(wxEVT_TREE_ITEM_RIGHT_CLICK, &RichTextTreeCtrl::OnTreeItemRightClick, this);
    m_control->Bind(wxEVT_TREE_ITEM_MIDDLE_CLICK, &RichTextTreeCtrl::OnTreeItemMiddleClick, this);
    m_control->Bind(wxEVT_TREE_SEL_CHANGED, &RichTextTreeCtrl::OnTreeSelChanged, this);
    m_control->Bind(wxEVT_TREE_SEL_CHANGING, &RichTextTreeCtrl::OnTreeSelChanging, this);
    m_control->Bind(wxEVT_TREE_KEY_DOWN, &RichTextTreeCtrl::OnTreeKeyDown, this);
    m_control->Bind(wxEVT_TREE_ITEM_GETTOOLTIP, &RichTextTreeCtrl::OnTreeItemGetToolTip, this);
    m_control->Bind(wxEVT_TREE_ITEM_MENU, &RichTextTreeCtrl::OnTreeItemMenu, this);
    m_control->Bind(wxEVT_TREE_STATE_IMAGE_CLICK, &RichTextTreeCtrl::OnTreeStateImageClick, this);

}

wxRichTextObject* RichTextTreeCtrl::Clone() const { return new RichTextTreeCtrl(*this); }
wxString RichTextTreeCtrl::GetXMLNodeName() const { return "treectrl"; }
int RichTextTreeCtrl::GetControlType() {return RT_CONTROL_TREECTRL;}

void RichTextTreeCtrl::OnTreeBeginDrag(wxTreeEvent& event)
{
    m_owner->OnTreeBeginDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeBeginRDrag(wxTreeEvent& event)
{
    m_owner->OnTreeBeginRDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeEndDrag(wxTreeEvent& event)
{
    m_owner->OnTreeEndDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeBeginLabelEdit(wxTreeEvent& event)
{
    m_owner->OnTreeBeginLabelEdit(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeEndLabelEdit(wxTreeEvent& event)
{
    m_owner->OnTreeEndLabelEdit(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeDeleteItem(wxTreeEvent& event)
{
    m_owner->OnTreeDeleteItem(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeGetInfo(wxTreeEvent& event)
{
    m_owner->OnTreeGetInfo(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeSetInfo(wxTreeEvent& event)
{
    m_owner->OnTreeSetInfo(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemActivated(wxTreeEvent& event)
{
    m_owner->OnTreeItemActivated(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemCollapsed(wxTreeEvent& event)
{
    m_owner->OnTreeItemCollapsed(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemCollapsing(wxTreeEvent& event)
{
    m_owner->OnTreeItemCollapsing(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeExpanded(wxTreeEvent& event)
{
    m_owner->OnTreeExpanded(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeExpanding(wxTreeEvent& event)
{
    m_owner->OnTreeExpanding(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemRightClick(wxTreeEvent& event)
{
    m_owner->OnTreeItemRightClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemMiddleClick(wxTreeEvent& event)
{
    m_owner->OnTreeItemMiddleClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeSelChanged(wxTreeEvent& event)
{
    m_owner->OnTreeSelChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeSelChanging(wxTreeEvent& event)
{
    m_owner->OnTreeSelChanging(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeKeyDown(wxTreeEvent& event)
{
    m_owner->OnTreeKeyDown(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemGetToolTip(wxTreeEvent& event)
{
    m_owner->OnTreeItemGetToolTip(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeItemMenu(wxTreeEvent& event)
{
    m_owner->OnTreeItemMenu(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextTreeCtrl::OnTreeStateImageClick(wxTreeEvent& event)
{
    m_owner->OnTreeStateImageClick(event, (RichTextControlBase *) this);
    event.Skip();
}

bool RichTextTreeCtrl::AppendItemEx_(wxTreeCtrl * tree, const char * text, TREE_APPEND_DATA_EMBEDDED & appendData, int image, int stateImage, wxUint8 depth)
{
    if (!tree || !text)
        return false;

    wxTreeItemId id;
    BasicBuffer buffer;
    buffer.CopyAsUtf16(text);

    if (depth == 0)
    {
        id = tree->AddRoot((wchar_t *) buffer, image, -1);
    }
    else if (depth == 1)
    {
        id = tree->GetRootItem();

        if (!id.IsOk())
            id = tree->AddRoot("", -1, -1);

        if (id.IsOk())
            id = tree->AppendItem(id, (wchar_t *) buffer, image, -1, NULL);
    }
    else if (depth == appendData.depth)
    {
        id = tree->GetItemParent(appendData.id);

        if (id.IsOk())
            id = tree->AppendItem(id, (wchar_t *) buffer, image, -1, NULL);
    }
    else if (depth > appendData.depth)
    {
        id = tree->AppendItem(appendData.id, (wchar_t *) buffer, image, -1, NULL);
    }
    else if (depth < appendData.depth)
    {
        wxUint8 pos = appendData.depth;
        id = appendData.id;

        if (id.IsOk())
        {
            while (pos >= depth)
            {
                id = tree->GetItemParent(id);

                if (!id.IsOk())
                    break;
                pos --;
            }

            if (id.IsOk())
                id = tree->AppendItem(id, (wchar_t *) buffer, image, -1, NULL);
        }
    }

    if (!id.IsOk())
        return false;

    if (id.IsOk())
        tree->SetItemImage(id, stateImage, wxTreeItemIcon_Expanded);

    appendData.id = id;
    appendData.depth = depth;

    return true;
}

IMPLEMENT_DYNAMIC_CLASS(RichTextPasswordCtrl, RichTextControlBase)

RichTextPasswordCtrl::RichTextPasswordCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextPasswordCtrl::RichTextPasswordCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextPasswordCtrl::~RichTextPasswordCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_TEXT_ENTER, &RichTextPasswordCtrl::OnPasswordCtrlTextEnter, this);
        m_control->Unbind(wxEVT_TEXT, &RichTextPasswordCtrl::OnPasswordCtrlText, this);
        m_control->Unbind(wxEVT_TEXT_MAXLEN, &RichTextPasswordCtrl::OnPasswordCtrlTextMaxLen, this);
        delete m_control;
    }
}

void RichTextPasswordCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxTextCtrl * control = new wxTextCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    m_cattr.SetStyle(m_cattr.GetStyle() | wxTE_PASSWORD);

    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValue(), point, size, m_cattr.GetStyle());
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_TEXT_ENTER, &RichTextPasswordCtrl::OnPasswordCtrlTextEnter, this);
    m_control->Bind(wxEVT_TEXT, &RichTextPasswordCtrl::OnPasswordCtrlText, this);
    m_control->Bind(wxEVT_TEXT_MAXLEN, &RichTextPasswordCtrl::OnPasswordCtrlTextMaxLen, this);
}

wxRichTextObject* RichTextPasswordCtrl::Clone() const { return new RichTextPasswordCtrl(*this); }
wxString RichTextPasswordCtrl::GetXMLNodeName() const { return "passwordctrl"; }
int RichTextPasswordCtrl::GetControlType() {return RT_CONTROL_PASSWORDCTRL;}

void RichTextPasswordCtrl::OnPasswordCtrlText(wxCommandEvent& event)
{
    m_owner->OnText(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextPasswordCtrl::OnPasswordCtrlTextEnter(wxCommandEvent& event)
{
    m_owner->OnTextEnter(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextPasswordCtrl::OnPasswordCtrlTextMaxLen(wxCommandEvent& event)
{
    m_owner->OnTextMaxLen(event, (RichTextControlBase *) this);
    event.Skip();
}



IMPLEMENT_DYNAMIC_CLASS(RichTextListCtrl, RichTextControlBase)

RichTextListCtrl::RichTextListCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextListCtrl::RichTextListCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextListCtrl::~RichTextListCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_LIST_BEGIN_DRAG, &RichTextListCtrl::OnListBeginDrag, this);
        m_control->Unbind(wxEVT_LIST_BEGIN_RDRAG, &RichTextListCtrl::OnListBeginRDrag, this);
        m_control->Unbind(wxEVT_LIST_BEGIN_LABEL_EDIT, &RichTextListCtrl::OnListBeginLabelEdit, this);
        m_control->Unbind(wxEVT_LIST_END_LABEL_EDIT, &RichTextListCtrl::OnListEndLabelEdit, this);
        m_control->Unbind(wxEVT_LIST_DELETE_ITEM, &RichTextListCtrl::OnListDeleteItem, this);
        m_control->Unbind(wxEVT_LIST_DELETE_ALL_ITEMS, &RichTextListCtrl::OnListDeleteAllItems, this);
        m_control->Unbind(wxEVT_LIST_ITEM_SELECTED, &RichTextListCtrl::OnListItemSelected, this);
        m_control->Unbind(wxEVT_LIST_ITEM_DESELECTED, &RichTextListCtrl::OnListItemDeselected, this);
        m_control->Unbind(wxEVT_LIST_ITEM_ACTIVATED, &RichTextListCtrl::OnListItemActivated, this);
        m_control->Unbind(wxEVT_LIST_ITEM_FOCUSED, &RichTextListCtrl::OnListItemFocused, this);
        m_control->Unbind(wxEVT_LIST_ITEM_RIGHT_CLICK, &RichTextListCtrl::OnListItemRightClick, this);
        m_control->Unbind(wxEVT_LIST_ITEM_MIDDLE_CLICK, &RichTextListCtrl::OnListItemMiddleClick, this);
        m_control->Unbind(wxEVT_LIST_KEY_DOWN, &RichTextListCtrl::OnListKeyDown, this);
        m_control->Unbind(wxEVT_LIST_INSERT_ITEM, &RichTextListCtrl::OnInsertItem, this);
        m_control->Unbind(wxEVT_LIST_COL_CLICK, &RichTextListCtrl::OnListColClick, this);
        m_control->Unbind(wxEVT_LIST_COL_RIGHT_CLICK, &RichTextListCtrl::OnListColRightClick, this);
        m_control->Unbind(wxEVT_LIST_COL_BEGIN_DRAG, &RichTextListCtrl::OnListColBeginDrag, this);
        m_control->Unbind(wxEVT_LIST_COL_DRAGGING, &RichTextListCtrl::OnListColDragging, this);
        m_control->Unbind(wxEVT_LIST_COL_END_DRAG, &RichTextListCtrl::OnListColEndDrag, this);
        m_control->Unbind(wxEVT_LIST_CACHE_HINT, &RichTextListCtrl::OnListCacheHint, this);
        delete m_control;
    }
}

void RichTextListCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxListCtrl * control = new wxListCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxLC_REPORT);

    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    BasicBuffer buffer;
    InitControl();

    wxUint32 id = m_owner->m_datalistArray.FindDataList(m_cattr.GetDataListName());

    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        wxListItem li;
        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;
            TranslateValue(data->GetValue(), buffer);
            if (data->GetIsColumn())
                control->AppendColumn((char *) buffer);
            else
            {
                li.SetColumn(data->GetDepth());
                TranslateValue(data->GetValue(), buffer);
                li.SetText((char *) buffer);
                control->InsertItem(li);
            }

            pos ++;
        }
    }
    else
        m_owner->LoadControlData((RichTextControlBase *)this);

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_LIST_BEGIN_DRAG, &RichTextListCtrl::OnListBeginDrag, this);
    m_control->Bind(wxEVT_LIST_BEGIN_RDRAG, &RichTextListCtrl::OnListBeginRDrag, this);
    m_control->Bind(wxEVT_LIST_BEGIN_LABEL_EDIT, &RichTextListCtrl::OnListBeginLabelEdit, this);
    m_control->Bind(wxEVT_LIST_END_LABEL_EDIT, &RichTextListCtrl::OnListEndLabelEdit, this);
    m_control->Bind(wxEVT_LIST_DELETE_ITEM, &RichTextListCtrl::OnListDeleteItem, this);
    m_control->Bind(wxEVT_LIST_DELETE_ALL_ITEMS, &RichTextListCtrl::OnListDeleteAllItems, this);
    m_control->Bind(wxEVT_LIST_ITEM_SELECTED, &RichTextListCtrl::OnListItemSelected, this);
    m_control->Bind(wxEVT_LIST_ITEM_DESELECTED, &RichTextListCtrl::OnListItemDeselected, this);
    m_control->Bind(wxEVT_LIST_ITEM_ACTIVATED, &RichTextListCtrl::OnListItemActivated, this);
    m_control->Bind(wxEVT_LIST_ITEM_FOCUSED, &RichTextListCtrl::OnListItemFocused, this);
    m_control->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &RichTextListCtrl::OnListItemRightClick, this);
    m_control->Bind(wxEVT_LIST_ITEM_MIDDLE_CLICK, &RichTextListCtrl::OnListItemMiddleClick, this);
    m_control->Bind(wxEVT_LIST_KEY_DOWN, &RichTextListCtrl::OnListKeyDown, this);
    m_control->Bind(wxEVT_LIST_INSERT_ITEM, &RichTextListCtrl::OnInsertItem, this);
    m_control->Bind(wxEVT_LIST_COL_CLICK, &RichTextListCtrl::OnListColClick, this);
    m_control->Bind(wxEVT_LIST_COL_RIGHT_CLICK, &RichTextListCtrl::OnListColRightClick, this);
    m_control->Bind(wxEVT_LIST_COL_BEGIN_DRAG, &RichTextListCtrl::OnListColBeginDrag, this);
    m_control->Bind(wxEVT_LIST_COL_DRAGGING, &RichTextListCtrl::OnListColDragging, this);
    m_control->Bind(wxEVT_LIST_COL_END_DRAG, &RichTextListCtrl::OnListColEndDrag, this);
    m_control->Bind(wxEVT_LIST_CACHE_HINT, &RichTextListCtrl::OnListCacheHint, this);
}

wxRichTextObject* RichTextListCtrl::Clone() const { return new RichTextListCtrl(*this); }
wxString RichTextListCtrl::GetXMLNodeName() const { return "listctrl"; }
int RichTextListCtrl::GetControlType() {return RT_CONTROL_LISTCTRL;}

void RichTextListCtrl::OnListBeginDrag(wxListEvent& event)
{
    m_owner->OnListBeginDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListBeginRDrag(wxListEvent& event)
{
    m_owner->OnListBeginRDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListBeginLabelEdit(wxListEvent& event)
{
    m_owner->OnListBeginLabelEdit(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListEndLabelEdit(wxListEvent& event)
{
    m_owner->OnListEndLabelEdit(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListDeleteItem(wxListEvent& event)
{
    m_owner->OnListDeleteItem(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListDeleteAllItems(wxListEvent& event)
{
    m_owner->OnListDeleteAllItems(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListItemSelected(wxListEvent& event)
{
    m_owner->OnListItemSelected(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListItemDeselected(wxListEvent& event)
{
    m_owner->OnListItemDeselected(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListItemActivated(wxListEvent& event)
{
    m_owner->OnListItemActivated(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListItemFocused(wxListEvent& event)
{
    m_owner->OnListItemFocused(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListItemRightClick(wxListEvent& event)
{
    m_owner->OnListItemRightClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListItemMiddleClick(wxListEvent& event)
{
    m_owner->OnListItemMiddleClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListKeyDown(wxListEvent& event)
{
    m_owner->OnListKeyDown(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnInsertItem(wxListEvent& event)
{
    m_owner->OnInsertItem(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListColClick(wxListEvent& event)
{
    m_owner->OnListColClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListColRightClick(wxListEvent& event)
{
    m_owner->OnListColRightClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListColBeginDrag(wxListEvent& event)
{
    m_owner->OnListColBeginDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListColDragging(wxListEvent& event)
{
    m_owner->OnListColDragging(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListColEndDrag(wxListEvent& event)
{
    m_owner->OnListColEndDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextListCtrl::OnListCacheHint(wxListEvent& event)
{
    m_owner->OnListCacheHint(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextRichCtrl, RichTextControlBase)

RichTextRichCtrl::RichTextRichCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextRichCtrl::RichTextRichCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextRichCtrl::~RichTextRichCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_RICHTEXT_LEFT_CLICK, &RichTextRichCtrl::OnRichTextLeftClick, this);
        m_control->Unbind(wxEVT_RICHTEXT_RIGHT_CLICK, &RichTextRichCtrl::OnRichTextRightClick, this);
        m_control->Unbind(wxEVT_RICHTEXT_MIDDLE_CLICK, &RichTextRichCtrl::OnRichTextMiddleClick, this);
        m_control->Unbind(wxEVT_RICHTEXT_LEFT_DCLICK, &RichTextRichCtrl::OnRichTextLeftDClick, this);
        m_control->Unbind(wxEVT_RICHTEXT_RETURN, &RichTextRichCtrl::OnRichTextReturn, this);
        m_control->Unbind(wxEVT_RICHTEXT_CHARACTER, &RichTextRichCtrl::OnRichTextCharacter, this);
        m_control->Unbind(wxEVT_RICHTEXT_CONSUMING_CHARACTER, &RichTextRichCtrl::OnRichTextConsumingCharacter, this);
        m_control->Unbind(wxEVT_RICHTEXT_DELETE, &RichTextRichCtrl::OnRichTextDelete, this);
        m_control->Unbind(wxEVT_RICHTEXT_STYLE_CHANGED, &RichTextRichCtrl::OnRichTextStyleChanged, this);
        m_control->Unbind(wxEVT_RICHTEXT_STYLESHEET_CHANGED, &RichTextRichCtrl::OnRichTextStyleSheetChanged, this);
        m_control->Unbind(wxEVT_RICHTEXT_STYLESHEET_REPLACING, &RichTextRichCtrl::OnRichTextStyleSheetReplacing, this);
        m_control->Unbind(wxEVT_RICHTEXT_STYLESHEET_REPLACED, &RichTextRichCtrl::OnRichTextStyleSheetReplaced, this);
        m_control->Unbind(wxEVT_RICHTEXT_PROPERTIES_CHANGED, &RichTextRichCtrl::OnRichTextPropertiesChanged, this);
        m_control->Unbind(wxEVT_RICHTEXT_CONTENT_INSERTED, &RichTextRichCtrl::OnRichTextContentInserted, this);
        m_control->Unbind(wxEVT_RICHTEXT_CONTENT_DELETED, &RichTextRichCtrl::OnRichTextContentDeleted, this);
        m_control->Unbind(wxEVT_RICHTEXT_BUFFER_RESET, &RichTextRichCtrl::OnRichTextBufferReset, this);
        m_control->Unbind(wxEVT_RICHTEXT_SELECTION_CHANGED, &RichTextRichCtrl::OnRichTextSelectionChanged, this);
        m_control->Unbind(wxEVT_RICHTEXT_FOCUS_OBJECT_CHANGED, &RichTextRichCtrl::OnRichTextFocusObjectChanged, this);
        m_control->Unbind(wxEVT_TEXT, &RichTextRichCtrl::OnRichTextText, this);
        m_control->Unbind(wxEVT_TEXT_ENTER, &RichTextRichCtrl::OnRichTextTextEnter, this);
        m_control->Unbind(wxEVT_TEXT_URL, &RichTextRichCtrl::OnRichTextUrl, this);

        delete m_control;
    }
}

void RichTextRichCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    RichTextCtrlExt * control = new RichTextCtrlExt;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxRE_MULTILINE);

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer, false);
    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, m_cattr.GetStyle());
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    if (m_cattr.GetMaxLength())
        control->SetMaxLength(m_cattr.GetMaxLength());

    if (strlen(m_cattr.GetSource()))
    {
        BasicBuffer resolvedPath;
        ResolveFilePath(resolvedPath);

        control->LoadFile((char *) resolvedPath);
    }

    m_owner->m_controlList.AddControl(obj);
/*?*/ /*    m_owner->Init(); */
    m_control->Bind(wxEVT_RICHTEXT_LEFT_CLICK, &RichTextRichCtrl::OnRichTextLeftClick, this);
    m_control->Bind(wxEVT_RICHTEXT_RIGHT_CLICK, &RichTextRichCtrl::OnRichTextRightClick, this);
    m_control->Bind(wxEVT_RICHTEXT_MIDDLE_CLICK, &RichTextRichCtrl::OnRichTextMiddleClick, this);
    m_control->Bind(wxEVT_RICHTEXT_LEFT_DCLICK, &RichTextRichCtrl::OnRichTextLeftDClick, this);
    m_control->Bind(wxEVT_RICHTEXT_RETURN, &RichTextRichCtrl::OnRichTextReturn, this);
    m_control->Bind(wxEVT_RICHTEXT_CHARACTER, &RichTextRichCtrl::OnRichTextCharacter, this);
    m_control->Bind(wxEVT_RICHTEXT_CONSUMING_CHARACTER, &RichTextRichCtrl::OnRichTextConsumingCharacter, this);
    m_control->Bind(wxEVT_RICHTEXT_DELETE, &RichTextRichCtrl::OnRichTextDelete, this);
    m_control->Bind(wxEVT_RICHTEXT_STYLE_CHANGED, &RichTextRichCtrl::OnRichTextStyleChanged, this);
    m_control->Bind(wxEVT_RICHTEXT_STYLESHEET_CHANGED, &RichTextRichCtrl::OnRichTextStyleSheetChanged, this);
    m_control->Bind(wxEVT_RICHTEXT_STYLESHEET_REPLACING, &RichTextRichCtrl::OnRichTextStyleSheetReplacing, this);
    m_control->Bind(wxEVT_RICHTEXT_STYLESHEET_REPLACED, &RichTextRichCtrl::OnRichTextStyleSheetReplaced, this);
    m_control->Bind(wxEVT_RICHTEXT_PROPERTIES_CHANGED, &RichTextRichCtrl::OnRichTextPropertiesChanged, this);
    m_control->Bind(wxEVT_RICHTEXT_CONTENT_INSERTED, &RichTextRichCtrl::OnRichTextContentInserted, this);
    m_control->Bind(wxEVT_RICHTEXT_CONTENT_DELETED, &RichTextRichCtrl::OnRichTextContentDeleted, this);
    m_control->Bind(wxEVT_RICHTEXT_BUFFER_RESET, &RichTextRichCtrl::OnRichTextBufferReset, this);
    m_control->Bind(wxEVT_RICHTEXT_SELECTION_CHANGED, &RichTextRichCtrl::OnRichTextSelectionChanged, this);
    m_control->Bind(wxEVT_RICHTEXT_FOCUS_OBJECT_CHANGED, &RichTextRichCtrl::OnRichTextFocusObjectChanged, this);
    m_control->Bind(wxEVT_TEXT, &RichTextRichCtrl::OnRichTextText, this);
    m_control->Bind(wxEVT_TEXT_ENTER, &RichTextRichCtrl::OnRichTextTextEnter, this);
    m_control->Bind(wxEVT_TEXT_URL, &RichTextRichCtrl::OnRichTextUrl, this);
}

wxRichTextObject* RichTextRichCtrl::Clone() const { return new RichTextRichCtrl(*this); }
wxString RichTextRichCtrl::GetXMLNodeName() const { return "richctrl"; }
int RichTextRichCtrl::GetControlType() {return RT_CONTROL_RICHCTRL;}

void RichTextRichCtrl::OnRichTextLeftClick(wxRichTextEvent& event)
{
    m_owner->OnRichTextLeftClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextRightClick(wxRichTextEvent& event)
{
    m_owner->OnRichTextRightClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextMiddleClick(wxRichTextEvent& event)
{
    m_owner->OnRichTextMiddleClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextLeftDClick(wxRichTextEvent& event)
{
    m_owner->OnRichTextLeftDClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextReturn(wxRichTextEvent& event)
{
    m_owner->OnRichTextReturn(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextCharacter(wxRichTextEvent& event)
{
    m_owner->OnRichTextCharacter(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextConsumingCharacter(wxRichTextEvent& event)
{
    m_owner->OnRichTextConsumingCharacter(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextDelete(wxRichTextEvent& event)
{
    m_owner->OnRichTextDelete(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextStyleChanged(wxRichTextEvent& event)
{
    m_owner->OnRichTextStyleChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextStyleSheetChanged(wxRichTextEvent& event)
{
    m_owner->OnRichTextStyleSheetChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextStyleSheetReplacing(wxRichTextEvent& event)
{
    m_owner->OnRichTextStyleSheetReplacing(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextStyleSheetReplaced(wxRichTextEvent& event)
{
    m_owner->OnRichTextStyleSheetReplaced(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextPropertiesChanged(wxRichTextEvent& event)
{
    m_owner->OnRichTextPropertiesChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextContentInserted(wxRichTextEvent& event)
{
    m_owner->OnRichTextContentInserted(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextContentDeleted(wxRichTextEvent& event)
{
    m_owner->OnRichTextContentDeleted(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextBufferReset(wxRichTextEvent& event)
{
    m_owner->OnRichTextBufferReset(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextSelectionChanged(wxRichTextEvent& event)
{
    m_owner->OnRichTextSelectionChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextFocusObjectChanged(wxRichTextEvent& event)
{
    m_owner->OnRichTextFocusObjectChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextText(wxCommandEvent& event)
{
    m_owner->OnText(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextTextEnter(wxCommandEvent& event)
{
    m_owner->OnTextEnter(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextRichCtrl::OnRichTextUrl(wxTextUrlEvent& event)
{
    m_owner->OnTextUrl(event, (RichTextControlBase *) this);
    event.Skip();
}


IMPLEMENT_DYNAMIC_CLASS(RichTextGauge, RichTextControlBase)

RichTextGauge::RichTextGauge(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextGauge::RichTextGauge(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextGauge::~RichTextGauge()
{
    //dtor
    if (m_control)
    {
        delete m_control;
    }
}

void RichTextGauge::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxGauge * control = new wxGauge;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxGA_HORIZONTAL);

    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValueAsInt(), point, size);
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
}

wxRichTextObject* RichTextGauge::Clone() const { return new RichTextGauge(*this); }
wxString RichTextGauge::GetXMLNodeName() const { return "gauge"; }
int RichTextGauge::GetControlType() {return RT_CONTROL_GAUGE;}

IMPLEMENT_DYNAMIC_CLASS(RichTextAnimationCtrl, RichTextControlBase)

RichTextAnimationCtrl::RichTextAnimationCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextAnimationCtrl::RichTextAnimationCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextAnimationCtrl::~RichTextAnimationCtrl()
{
    //dtor
    if (m_control)
    {
        delete m_control;
    }
}

void RichTextAnimationCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxAnimationCtrl * control = new wxAnimationCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxAC_DEFAULT_STYLE);

    control->Create((wxWindow *) m_owner, m_controlId, wxNullAnimation, point, size, m_cattr.GetStyle());
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    if (strlen(m_cattr.GetSource()))
    {
        BasicBuffer resolvedPath;
        ResolveFilePath(resolvedPath);

        control->LoadFile((char *) resolvedPath);
    }

    m_owner->m_controlList.AddControl(obj);
}

wxRichTextObject* RichTextAnimationCtrl::Clone() const { return new RichTextAnimationCtrl(*this); }
wxString RichTextAnimationCtrl::GetXMLNodeName() const { return "animationctrl"; }
int RichTextAnimationCtrl::GetControlType() {return RT_CONTROL_ANIMATIONCTRL;}

IMPLEMENT_DYNAMIC_CLASS(RichTextSlider, RichTextControlBase)

RichTextSlider::RichTextSlider(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextSlider::RichTextSlider(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextSlider::~RichTextSlider()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_SCROLL_TOP, &RichTextSlider::OnSliderScrollTop, this);
        m_control->Unbind(wxEVT_SCROLL_BOTTOM, &RichTextSlider::OnSliderScrollBottom, this);
        m_control->Unbind(wxEVT_SCROLL_LINEUP, &RichTextSlider::OnSliderScrollLineUp, this);
        m_control->Unbind(wxEVT_SCROLL_LINEDOWN, &RichTextSlider::OnSliderScrollLineDown, this);
        m_control->Unbind(wxEVT_SCROLL_PAGEUP, &RichTextSlider::OnSliderScrollPageUp, this);
        m_control->Unbind(wxEVT_SCROLL_PAGEDOWN, &RichTextSlider::OnSliderScrollPageDown, this);
        m_control->Unbind(wxEVT_SCROLL_THUMBTRACK, &RichTextSlider::OnSliderScrollThumbTrack, this);
        m_control->Unbind(wxEVT_SCROLL_THUMBRELEASE, &RichTextSlider::OnSliderScrollThumbRelease, this);
        m_control->Unbind(wxEVT_SCROLL_CHANGED, &RichTextSlider::OnSliderScrollChanged, this);
        delete m_control;
    }
}

void RichTextSlider::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxSlider * control = new wxSlider;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxSL_HORIZONTAL);

    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValueAsInt(), m_cattr.GetMinValueAsInt(), m_cattr.GetMaxValueAsInt(), point, size, m_cattr.GetStyle());
    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_SCROLL_TOP, &RichTextSlider::OnSliderScrollTop, this);
    m_control->Bind(wxEVT_SCROLL_BOTTOM, &RichTextSlider::OnSliderScrollBottom, this);
    m_control->Bind(wxEVT_SCROLL_LINEUP, &RichTextSlider::OnSliderScrollLineUp, this);
    m_control->Bind(wxEVT_SCROLL_LINEDOWN, &RichTextSlider::OnSliderScrollLineDown, this);
    m_control->Bind(wxEVT_SCROLL_PAGEUP, &RichTextSlider::OnSliderScrollPageUp, this);
    m_control->Bind(wxEVT_SCROLL_PAGEDOWN, &RichTextSlider::OnSliderScrollPageDown, this);
    m_control->Bind(wxEVT_SCROLL_THUMBTRACK, &RichTextSlider::OnSliderScrollThumbTrack, this);
    m_control->Bind(wxEVT_SCROLL_THUMBRELEASE, &RichTextSlider::OnSliderScrollThumbRelease, this);
    m_control->Bind(wxEVT_SCROLL_CHANGED, &RichTextSlider::OnSliderScrollChanged, this);
}

wxRichTextObject* RichTextSlider::Clone() const { return new RichTextSlider(*this); }
wxString RichTextSlider::GetXMLNodeName() const { return "slider"; }
int RichTextSlider::GetControlType() {return RT_CONTROL_SLIDER;}

void RichTextSlider::OnSliderScrollTop(wxScrollEvent& event)
{
    m_owner->OnScrollTop(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollBottom(wxScrollEvent& event)
{
    m_owner->OnScrollBottom(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollLineUp(wxScrollEvent& event)
{
    m_owner->OnScrollLineUp(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollLineDown(wxScrollEvent& event)
{
    m_owner->OnScrollLineDown(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollPageUp(wxScrollEvent& event)
{
    m_owner->OnScrollPageUp(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollPageDown(wxScrollEvent& event)
{
    m_owner->OnScrollPageDown(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollThumbTrack(wxScrollEvent& event)
{
    m_owner->OnScrollThumbTrack(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollThumbRelease(wxScrollEvent& event)
{
    m_owner->OnScrollThumbRelease(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextSlider::OnSliderScrollChanged(wxScrollEvent& event)
{
    m_owner->OnScrollChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextImageButton, RichTextControlBase)

RichTextImageButton::RichTextImageButton(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextImageButton::RichTextImageButton(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextImageButton::~RichTextImageButton()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, &RichTextImageButton::OnButtonClick, this);
        delete m_control;
    }
}

void RichTextImageButton::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxBitmapButton * control = new wxBitmapButton;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxBU_AUTODRAW);

    wxBitmap * bmp = NULL;
    wxImage img;
    if (strlen(m_cattr.GetSource()))
    {
        BasicBuffer resolvedPath;
        ResolveFilePath(resolvedPath);

        if (img.LoadFile((char *) resolvedPath))
            bmp = new wxBitmap(img);
    }

//    if (bmp && bmp->IsOk())
        control->Create((wxWindow *) m_owner, m_controlId, *bmp, point, size, m_cattr.GetStyle());
//    else
//        control->Create((wxWindow *) m_owner, m_controlId, NULL, point, size, m_cattr.GetStyle());

    if (bmp)
        delete bmp;

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &RichTextImageButton::OnButtonClick, this);
}

wxRichTextObject* RichTextImageButton::Clone() const { return new RichTextImageButton(*this); }
wxString RichTextImageButton::GetXMLNodeName() const { return "imagebutton"; }
int RichTextImageButton::GetControlType() {return RT_CONTROL_IMAGEBUTTON;}

void RichTextImageButton::OnButtonClick(wxCommandEvent& event)
{
    m_owner->OnButtonClick(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextLabel, RichTextControlBase)

RichTextLabel::RichTextLabel(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextLabel::RichTextLabel(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextLabel::~RichTextLabel()
{
    //dtor
    if (m_control)
        delete m_control;
}

void RichTextLabel::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxStaticText * control = new wxStaticText;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetValue(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, (char *) buffer, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
}

wxRichTextObject* RichTextLabel::Clone() const { return new RichTextLabel(*this); }
wxString RichTextLabel::GetXMLNodeName() const { return "label"; }
int RichTextLabel::GetControlType() {return RT_CONTROL_LABEL;}

IMPLEMENT_DYNAMIC_CLASS(RichTextColourPicker, RichTextControlBase)

RichTextColourPicker::RichTextColourPicker(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextColourPicker::RichTextColourPicker(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextColourPicker::~RichTextColourPicker()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_COLOURPICKER_CHANGED, &RichTextColourPicker::OnColourPickerChanged, this);
        delete m_control;
    }
}

void RichTextColourPicker::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxColourPickerCtrl * control = new wxColourPickerCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle((long)wxCLRP_DEFAULT_STYLE);

    control->Create((wxWindow *) m_owner, m_controlId, wxColour(HtmlColor::GetBGR(HtmlColor::GetColor(m_cattr.GetValue()))), point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_COLOURPICKER_CHANGED, &RichTextColourPicker::OnColourPickerChanged, this);
}

wxRichTextObject* RichTextColourPicker::Clone() const { return new RichTextColourPicker(*this); }
wxString RichTextColourPicker::GetXMLNodeName() const { return "colourpicker"; }
int RichTextColourPicker::GetControlType() {return RT_CONTROL_COLOURPICKER;}

void RichTextColourPicker::OnColourPickerChanged(wxColourPickerEvent& event)
{
    m_owner->OnColourPickerChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextDirPicker, RichTextControlBase)

RichTextDirPicker::RichTextDirPicker(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextDirPicker::RichTextDirPicker(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextDirPicker::~RichTextDirPicker()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_DIRPICKER_CHANGED, &RichTextDirPicker::OnDirPickerChanged, this);
        delete m_control;
    }

}

void RichTextDirPicker::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxDirPickerCtrl * control = new wxDirPickerCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxDIRP_DEFAULT_STYLE);

    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValue(), m_cattr.GetHint(), point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_DIRPICKER_CHANGED, &RichTextDirPicker::OnDirPickerChanged, this);
}

wxRichTextObject* RichTextDirPicker::Clone() const { return new RichTextDirPicker(*this); }
wxString RichTextDirPicker::GetXMLNodeName() const { return "dirpicker"; }
int RichTextDirPicker::GetControlType() {return RT_CONTROL_DIRPICKER;}

void RichTextDirPicker::OnDirPickerChanged(wxFileDirPickerEvent& event)
{
    m_owner->OnDirPickerChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextFilePicker, RichTextControlBase)

RichTextFilePicker::RichTextFilePicker(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextFilePicker::RichTextFilePicker(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextFilePicker::~RichTextFilePicker()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_FILEPICKER_CHANGED, &RichTextFilePicker::OnFilePickerChanged, this);
        delete m_control;
    }

}

void RichTextFilePicker::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxFilePickerCtrl * control = new wxFilePickerCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxFLP_DEFAULT_STYLE);

    BasicBuffer buffer;
    TranslateValue(m_cattr.GetHint(), buffer);
    control->Create((wxWindow *) m_owner, m_controlId, m_cattr.GetValue(), (char *) buffer, m_cattr.GetFilter(), point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_FILEPICKER_CHANGED, &RichTextFilePicker::OnFilePickerChanged, this);
}

wxRichTextObject* RichTextFilePicker::Clone() const { return new RichTextFilePicker(*this); }
wxString RichTextFilePicker::GetXMLNodeName() const { return "filepicker"; }
int RichTextFilePicker::GetControlType() {return RT_CONTROL_FILEPICKER;}

void RichTextFilePicker::OnFilePickerChanged(wxFileDirPickerEvent& event)
{
    m_owner->OnFilePickerChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextFontPicker, RichTextControlBase)

RichTextFontPicker::RichTextFontPicker(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextFontPicker::RichTextFontPicker(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextFontPicker::~RichTextFontPicker()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_FONTPICKER_CHANGED, &RichTextFontPicker::OnFontPickerChanged, this);
        delete m_control;
    }
}

void RichTextFontPicker::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxFontPickerCtrl * control = new wxFontPickerCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxFNTP_DEFAULT_STYLE);

    wxFont * ft = new wxFont(m_cattr.GetValue());
    control->Create((wxWindow *) m_owner, m_controlId, *ft, point, size, m_cattr.GetStyle());
    delete ft;

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();

    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_FONTPICKER_CHANGED, &RichTextFontPicker::OnFontPickerChanged, this);
}

wxRichTextObject* RichTextFontPicker::Clone() const { return new RichTextFontPicker(*this); }
wxString RichTextFontPicker::GetXMLNodeName() const { return "fontpicker"; }
int RichTextFontPicker::GetControlType() {return RT_CONTROL_FONTPICKER;}

void RichTextFontPicker::OnFontPickerChanged(wxFontPickerEvent& event)
{
    m_owner->OnFontPickerChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextCalendarCtrl, RichTextControlBase)

RichTextCalendarCtrl::RichTextCalendarCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextCalendarCtrl::RichTextCalendarCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextCalendarCtrl::~RichTextCalendarCtrl()
{
    //dtor
    if (m_control)
    {
        m_control->Unbind(wxEVT_CALENDAR_DOUBLECLICKED, &RichTextCalendarCtrl::OnCalendarClick, this);
        m_control->Unbind(wxEVT_CALENDAR_SEL_CHANGED, &RichTextCalendarCtrl::OnCalendarSelChanged, this);
        m_control->Unbind(wxEVT_CALENDAR_PAGE_CHANGED, &RichTextCalendarCtrl::OnCalendarPageChanged, this);
        delete m_control;
    }
}

void RichTextCalendarCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxCalendarCtrl * control = new wxCalendarCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxCAL_SHOW_HOLIDAYS);

    wxDateTime dt;
    dt.ParseISODate(m_cattr.GetValue());
    control->Create((wxWindow *) m_owner, m_controlId, dt, point, size, m_cattr.GetStyle());

    InitControl();

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);
    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_CALENDAR_DOUBLECLICKED, &RichTextCalendarCtrl::OnCalendarClick, this);
    m_control->Bind(wxEVT_CALENDAR_SEL_CHANGED, &RichTextCalendarCtrl::OnCalendarSelChanged, this);
    m_control->Bind(wxEVT_CALENDAR_PAGE_CHANGED, &RichTextCalendarCtrl::OnCalendarPageChanged, this);
}

wxRichTextObject* RichTextCalendarCtrl::Clone() const { return new RichTextCalendarCtrl(*this); }
wxString RichTextCalendarCtrl::GetXMLNodeName() const { return "calendarctrl"; }
int RichTextCalendarCtrl::GetControlType() {return RT_CONTROL_CALENDARCTRL;}

void RichTextCalendarCtrl::OnCalendarClick(wxCalendarEvent& event)
{
    m_owner->OnCalendarClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextCalendarCtrl::OnCalendarSelChanged(wxCalendarEvent& event)
{
    m_owner->OnCalendarSelChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextCalendarCtrl::OnCalendarPageChanged(wxCalendarEvent& event)
{
    m_owner->OnCalendarPageChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextDataViewListCtrl, RichTextControlBase)

RichTextDataViewListCtrl::RichTextDataViewListCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextDataViewListCtrl::RichTextDataViewListCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextDataViewListCtrl::~RichTextDataViewListCtrl()
{
    //dtor

    if (m_control)
    {
        m_control->Unbind(wxEVT_DATAVIEW_SELECTION_CHANGED, &RichTextDataViewListCtrl::OnDataViewSelectionChanged, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &RichTextDataViewListCtrl::OnDataViewItemActivated, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_START_EDITING, &RichTextDataViewListCtrl::OnDataViewItemStartEditing, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EDITING_STARTED, &RichTextDataViewListCtrl::OnDataViewItemEditingStarted, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, &RichTextDataViewListCtrl::OnDataViewItemEditingDone, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_COLLAPSING, &RichTextDataViewListCtrl::OnDataViewItemCollapsing, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_COLLAPSED, &RichTextDataViewListCtrl::OnDataViewItemCollapsed, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EXPANDING, &RichTextDataViewListCtrl::OnDataViewItemExpanding, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EXPANDED, &RichTextDataViewListCtrl::OnDataViewItemExpanded, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &RichTextDataViewListCtrl::OnDataViewItemValueChanged, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &RichTextDataViewListCtrl::OnDataViewItemContextMenu, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &RichTextDataViewListCtrl::OnDataViewColumnHeaderClick, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK, &RichTextDataViewListCtrl::OnDataViewColumnHeaderRightClick, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_SORTED, &RichTextDataViewListCtrl::OnDataViewColumnSorted, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_REORDERED, &RichTextDataViewListCtrl::OnDataViewColumnReordered, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG, &RichTextDataViewListCtrl::OnDataViewItemBeginDrag, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE, &RichTextDataViewListCtrl::OnDataViewItemDropPossible, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_DROP, &RichTextDataViewListCtrl::OnDataViewItemDrop, this);
        delete m_control;
    }

}

void RichTextDataViewListCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxDataViewListCtrl  * control = new wxDataViewListCtrl ;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxDV_ROW_LINES);

    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();
    m_owner->LoadControlData((RichTextControlBase *)this);
    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &RichTextDataViewListCtrl::OnDataViewSelectionChanged, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &RichTextDataViewListCtrl::OnDataViewItemActivated, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_START_EDITING, &RichTextDataViewListCtrl::OnDataViewItemStartEditing, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EDITING_STARTED, &RichTextDataViewListCtrl::OnDataViewItemEditingStarted, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, &RichTextDataViewListCtrl::OnDataViewItemEditingDone, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_COLLAPSING, &RichTextDataViewListCtrl::OnDataViewItemCollapsing, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_COLLAPSED, &RichTextDataViewListCtrl::OnDataViewItemCollapsed, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EXPANDING, &RichTextDataViewListCtrl::OnDataViewItemExpanding, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EXPANDED, &RichTextDataViewListCtrl::OnDataViewItemExpanded, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &RichTextDataViewListCtrl::OnDataViewItemValueChanged, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &RichTextDataViewListCtrl::OnDataViewItemContextMenu, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &RichTextDataViewListCtrl::OnDataViewColumnHeaderClick, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK, &RichTextDataViewListCtrl::OnDataViewColumnHeaderRightClick, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_SORTED, &RichTextDataViewListCtrl::OnDataViewColumnSorted, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_REORDERED, &RichTextDataViewListCtrl::OnDataViewColumnReordered, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG, &RichTextDataViewListCtrl::OnDataViewItemBeginDrag, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE, &RichTextDataViewListCtrl::OnDataViewItemDropPossible, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_DROP, &RichTextDataViewListCtrl::OnDataViewItemDrop, this);
}

wxRichTextObject* RichTextDataViewListCtrl::Clone() const { return new RichTextDataViewListCtrl(*this); }
wxString RichTextDataViewListCtrl::GetXMLNodeName() const { return "dataviewlistctrl"; }
int RichTextDataViewListCtrl::GetControlType() {return RT_CONTROL_DATAVIEWLISTCTRL;}

void RichTextDataViewListCtrl::OnDataViewSelectionChanged(wxDataViewEvent& event)
{
    m_owner->OnDataViewSelectionChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemActivated(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemActivated(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemStartEditing(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemStartEditing(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemEditingStarted(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemEditingStarted(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemEditingDone(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemEditingDone(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemCollapsing(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemCollapsing(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemCollapsed(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemCollapsed(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemExpanding(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemExpanding(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemExpanded(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemExpanded(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemValueChanged(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemValueChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemContextMenu(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemContextMenu(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewColumnHeaderClick(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnHeaderClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewColumnHeaderRightClick(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnHeaderRightClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewColumnSorted(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnSorted(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewColumnReordered(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnReordered(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemBeginDrag(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemBeginDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemDropPossible(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemDropPossible(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewListCtrl::OnDataViewItemDrop(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemDrop(event, (RichTextControlBase *) this);
    event.Skip();
}

IMPLEMENT_DYNAMIC_CLASS(RichTextDataViewTreeCtrl, RichTextControlBase)

RichTextDataViewTreeCtrl::RichTextDataViewTreeCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent, wxRichTextAttr* charStyle):
    RichTextControlBase(parent, charStyle)
{

}

RichTextDataViewTreeCtrl::RichTextDataViewTreeCtrl(wxRichTextObject* parent): RichTextControlBase(parent) {}

RichTextDataViewTreeCtrl::~RichTextDataViewTreeCtrl()
{
    //dtor

    if (m_control)
    {
        delete m_control;
        m_control->Unbind(wxEVT_DATAVIEW_SELECTION_CHANGED, &RichTextDataViewTreeCtrl::OnDataViewSelectionChanged, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &RichTextDataViewTreeCtrl::OnDataViewItemActivated, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_START_EDITING, &RichTextDataViewTreeCtrl::OnDataViewItemStartEditing, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EDITING_STARTED, &RichTextDataViewTreeCtrl::OnDataViewItemEditingStarted, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, &RichTextDataViewTreeCtrl::OnDataViewItemEditingDone, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_COLLAPSING, &RichTextDataViewTreeCtrl::OnDataViewItemCollapsing, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_COLLAPSED, &RichTextDataViewTreeCtrl::OnDataViewItemCollapsed, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EXPANDING, &RichTextDataViewTreeCtrl::OnDataViewItemExpanding, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_EXPANDED, &RichTextDataViewTreeCtrl::OnDataViewItemExpanded, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &RichTextDataViewTreeCtrl::OnDataViewItemValueChanged, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &RichTextDataViewTreeCtrl::OnDataViewItemContextMenu, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &RichTextDataViewTreeCtrl::OnDataViewColumnHeaderClick, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK, &RichTextDataViewTreeCtrl::OnDataViewColumnHeaderRightClick, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_SORTED, &RichTextDataViewTreeCtrl::OnDataViewColumnSorted, this);
        m_control->Unbind(wxEVT_DATAVIEW_COLUMN_REORDERED, &RichTextDataViewTreeCtrl::OnDataViewColumnReordered, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG, &RichTextDataViewTreeCtrl::OnDataViewItemBeginDrag, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE, &RichTextDataViewTreeCtrl::OnDataViewItemDropPossible, this);
        m_control->Unbind(wxEVT_DATAVIEW_ITEM_DROP, &RichTextDataViewTreeCtrl::OnDataViewItemDrop, this);
    }

}

void RichTextDataViewTreeCtrl::CreateControl(wxRect * rect)
{
    if (!m_owner)
        return;

    RichTextControlBase::CreateControl(NULL);
    wxDataViewTreeCtrl * control = new wxDataViewTreeCtrl;
    wxPoint point;
    point.x = rect->x;
    point.y = rect->y;
    wxSize size;
    size.SetHeight(rect->GetHeight());
    size.SetWidth(rect->GetWidth());

    if (m_cattr.GetStyle() == 0)
        m_cattr.SetStyle(wxDV_NO_HEADER|wxDV_ROW_LINES);

    control->Create((wxWindow *) m_owner, m_controlId, point, size, m_cattr.GetStyle());

    m_control = control;
    RichTextControlBase * obj = wxDynamicCast(this, RichTextControlBase);

    InitControl();
    m_owner->LoadControlData((RichTextControlBase *)this);
    m_owner->m_controlList.AddControl(obj);
    m_control->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &RichTextDataViewTreeCtrl::OnDataViewSelectionChanged, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED, &RichTextDataViewTreeCtrl::OnDataViewItemActivated, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_START_EDITING, &RichTextDataViewTreeCtrl::OnDataViewItemStartEditing, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EDITING_STARTED, &RichTextDataViewTreeCtrl::OnDataViewItemEditingStarted, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EDITING_DONE, &RichTextDataViewTreeCtrl::OnDataViewItemEditingDone, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_COLLAPSING, &RichTextDataViewTreeCtrl::OnDataViewItemCollapsing, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_COLLAPSED, &RichTextDataViewTreeCtrl::OnDataViewItemCollapsed, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EXPANDING, &RichTextDataViewTreeCtrl::OnDataViewItemExpanding, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_EXPANDED, &RichTextDataViewTreeCtrl::OnDataViewItemExpanded, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &RichTextDataViewTreeCtrl::OnDataViewItemValueChanged, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &RichTextDataViewTreeCtrl::OnDataViewItemContextMenu, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &RichTextDataViewTreeCtrl::OnDataViewColumnHeaderClick, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK, &RichTextDataViewTreeCtrl::OnDataViewColumnHeaderRightClick, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_SORTED, &RichTextDataViewTreeCtrl::OnDataViewColumnSorted, this);
    m_control->Bind(wxEVT_DATAVIEW_COLUMN_REORDERED, &RichTextDataViewTreeCtrl::OnDataViewColumnReordered, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG, &RichTextDataViewTreeCtrl::OnDataViewItemBeginDrag, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE, &RichTextDataViewTreeCtrl::OnDataViewItemDropPossible, this);
    m_control->Bind(wxEVT_DATAVIEW_ITEM_DROP, &RichTextDataViewTreeCtrl::OnDataViewItemDrop, this);
}

wxRichTextObject* RichTextDataViewTreeCtrl::Clone() const { return new RichTextDataViewTreeCtrl(*this); }
wxString RichTextDataViewTreeCtrl::GetXMLNodeName() const { return "dataviewtreectrl"; }
int RichTextDataViewTreeCtrl::GetControlType() {return RT_CONTROL_DATAVIEWTREECTRL;}

void RichTextDataViewTreeCtrl::OnDataViewSelectionChanged(wxDataViewEvent& event)
{
    m_owner->OnDataViewSelectionChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemActivated(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemActivated(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemStartEditing(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemStartEditing(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemEditingStarted(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemEditingStarted(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemEditingDone(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemEditingDone(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemCollapsing(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemCollapsing(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemCollapsed(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemCollapsed(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemExpanding(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemExpanding(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemExpanded(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemExpanded(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemValueChanged(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemValueChanged(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemContextMenu(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemContextMenu(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewColumnHeaderClick(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnHeaderClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewColumnHeaderRightClick(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnHeaderRightClick(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewColumnSorted(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnSorted(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewColumnReordered(wxDataViewEvent& event)
{
    m_owner->OnDataViewColumnReordered(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemBeginDrag(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemBeginDrag(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemDropPossible(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemDropPossible(event, (RichTextControlBase *) this);
    event.Skip();
}

void RichTextDataViewTreeCtrl::OnDataViewItemDrop(wxDataViewEvent& event)
{
    m_owner->OnDataViewItemDrop(event, (RichTextControlBase *) this);
    event.Skip();
}
