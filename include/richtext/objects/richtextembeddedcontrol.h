///////////////////////////////////////////////////////////////////
// Name:        richtextembeddedcontrol.h
// Purpose:     Embeddable controls for RichTextCtrlExt.
// Copyright:   David Reynolds.
///////////////////////////////////////////////////////////////////

#ifndef RICHTEXTEMBEDDEDCONTROL_H
#define RICHTEXTEMBEDDEDCONTROL_H

#include "richtextcontrolbase.h"

#define RT_CONTROL_BUTTON               1
#define RT_CONTROL_CHECKBOX             2
#define RT_CONTROL_CHOICE               3
#define RT_CONTROL_COMBOBOX             4
#define RT_CONTROL_DATEPICKER           5
#define RT_CONTROL_DIRCTRL              6
#define RT_CONTROL_LISTBOX              7
#define RT_CONTROL_CHECKLISTBOX         8
#define RT_CONTROL_RADIOBUTTON          9
#define RT_CONTROL_SEARCHCTRL          10
#define RT_CONTROL_SPINCTRL            11
#define RT_CONTROL_SPINCTRLDB          12
#define RT_CONTROL_TIMEPICKER          13
#define RT_CONTROL_MEDIACTRL           14
#define RT_CONTROL_TREECTRL            15
#define RT_CONTROL_PASSWORDCTRL        16
#define RT_CONTROL_LISTCTRL            17
#define RT_CONTROL_RICHCTRL            18
#define RT_CONTROL_GAUGE               19
#define RT_CONTROL_SLIDER              20
#define RT_CONTROL_IMAGEBUTTON         21
#define RT_CONTROL_LABEL               22
#define RT_CONTROL_COLOURPICKER        23
#define RT_CONTROL_DIRPICKER           24
#define RT_CONTROL_FILEPICKER          25
#define RT_CONTROL_FONTPICKER          26
#define RT_CONTROL_CALENDARCTRL        27
#define RT_CONTROL_DATAVIEWLISTCTRL    28
#define RT_CONTROL_DATAVIEWTREECTRL    29
#define RT_CONTROL_ANIMATIONCTRL       30
#define RT_CONTROL_SOWERAUDIOCTRL      31


#include "../../av_media/audiocontrol.h"

class SOWERBASEEXP RichTextSowerAudioCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextSowerAudioCtrl)
    public:
        /** Default constructor */
        RichTextSowerAudioCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextSowerAudioCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);

        /** Default destructor */
        virtual ~RichTextSowerAudioCtrl();

        virtual wxRichTextObject* Clone() const;
        virtual void CreateControl(wxRect * rect);
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
};

class SOWERBASEEXP RichTextButton : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextButton)
    public:
        /** Default constructor */
        RichTextButton(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextButton(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);

        /** Default destructor */
        virtual ~RichTextButton();

        virtual wxRichTextObject* Clone() const;
        virtual void CreateControl(wxRect * rect);
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnButtonClick(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextCheckBox : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextCheckBox)
    public:
        /** Default constructor */
        RichTextCheckBox(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextCheckBox(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);

        /** Default destructor */
        virtual ~RichTextCheckBox();
        virtual wxRichTextObject* Clone() const;
        virtual void CreateControl(wxRect * rect);
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnCheckBoxClick(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextChoice : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextChoice)
    public:
        /** Default constructor */
        RichTextChoice(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextChoice(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);

        /** Default destructor */
        virtual ~RichTextChoice();

        virtual wxRichTextObject* Clone() const;
        virtual void CreateControl(wxRect * rect);
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnChoice(wxCommandEvent& event);
};


class SOWERBASEEXP RichTextComboBox : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextComboBox)
    public:
        /** Default constructor */
        RichTextComboBox(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextComboBox(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextComboBox();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnComboBoxSelected(wxCommandEvent& event);
        void OnComboBoxText(wxCommandEvent& event);
        void OnComboBoxTextEnter(wxCommandEvent& event);
        void OnComboBoxDropDown(wxCommandEvent& event);
        void OnComboBoxCloseUp(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextDatePicker : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextDatePicker)
    public:
        /** Default constructor */
        RichTextDatePicker(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextDatePicker(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextDatePicker();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnDateChanged(wxDateEvent& event);
};

class SOWERBASEEXP RichTextDirCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextDirCtrl)
    public:
        /** Default constructor */
        RichTextDirCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextDirCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextDirCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnDirCtrlSelectionChanged(wxCommandEvent& event);
        void OnDirCtrlFileActivated(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextListBox : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextListBox)
    public:
        /** Default constructor */
        RichTextListBox(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextListBox(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextListBox();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnListBoxSelected(wxCommandEvent& event);
        void OnListBoxDbClicked(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextCheckListBox : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextCheckListBox)
    public:
        /** Default constructor */
        RichTextCheckListBox(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextCheckListBox(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextCheckListBox();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnListBoxSelected(wxCommandEvent& event);
        void OnListBoxDbClicked(wxCommandEvent& event);
        void OnCheckListBox(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextRadioButton : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextRadioButton)
    public:
        /** Default constructor */
        RichTextRadioButton(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextRadioButton(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextRadioButton();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnRadioButtonSelected(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextSearchCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextSearchCtrl)
    public:
        /** Default constructor */
        RichTextSearchCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextSearchCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextSearchCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnSearchCtrlSearchBtn(wxCommandEvent& event);
        void OnSearchCtrlCancelBtn(wxCommandEvent& event);
        void OnSearchCtrlText(wxCommandEvent& event);
        void OnSearchCtrlTextEnter(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextSpinCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextSpinCtrl)
    public:
        /** Default constructor */
        RichTextSpinCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextSpinCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextSpinCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnSpinCtrlUpdated(wxCommandEvent& event);
        void OnSpinCtrlEnter(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextSpinCtrlDb : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextSpinCtrlDb)
    public:
        /** Default constructor */
        RichTextSpinCtrlDb(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextSpinCtrlDb(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextSpinCtrlDb();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnSpinCtrlDouble(wxSpinDoubleEvent& event);
};

class SOWERBASEEXP RichTextTimePicker : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextTimePicker)
    public:
        /** Default constructor */
        RichTextTimePicker(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextTimePicker(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextTimePicker();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnTimeChanged(wxDateEvent& event);
};

class SOWERBASEEXP RichTextMediaCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextMediaCtrl)
    public:
        /** Default constructor */
        RichTextMediaCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextMediaCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextMediaCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnMediaLoaded(wxMediaEvent& event);
        void OnMediaStopped(wxMediaEvent& event);
        void OnMediaPaused(wxMediaEvent& event);
        void OnMediaPlay(wxMediaEvent& event);
        void OnMediaFinished(wxMediaEvent& event);
        void OnMediaStateChanged(wxMediaEvent& event);
};

struct SOWERBASEEXP TREE_APPEND_DATA_EMBEDDED
{
    wxTreeItemId id;
    wxUint8 depth;
};

class SOWERBASEEXP RichTextTreeCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextTreeCtrl)
    public:
        /** Default constructor */
        RichTextTreeCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextTreeCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextTreeCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnTreeBeginDrag(wxTreeEvent& event);
        void OnTreeBeginRDrag(wxTreeEvent& event);
        void OnTreeEndDrag(wxTreeEvent& event);
        void OnTreeBeginLabelEdit(wxTreeEvent& event);
        void OnTreeEndLabelEdit(wxTreeEvent& event);
        void OnTreeDeleteItem(wxTreeEvent& event);
        void OnTreeGetInfo(wxTreeEvent& event);
        void OnTreeSetInfo(wxTreeEvent& event);
        void OnTreeItemActivated(wxTreeEvent& event);
        void OnTreeItemCollapsed(wxTreeEvent& event);
        void OnTreeItemCollapsing(wxTreeEvent& event);
        void OnTreeExpanded(wxTreeEvent& event);
        void OnTreeExpanding(wxTreeEvent& event);
        void OnTreeItemRightClick(wxTreeEvent& event);
        void OnTreeItemMiddleClick(wxTreeEvent& event);
        void OnTreeSelChanged(wxTreeEvent& event);
        void OnTreeSelChanging(wxTreeEvent& event);
        void OnTreeKeyDown(wxTreeEvent& event);
        void OnTreeItemGetToolTip(wxTreeEvent& event);
        void OnTreeItemMenu(wxTreeEvent& event);
        void OnTreeStateImageClick(wxTreeEvent& event);
        bool AppendItemEx_(wxTreeCtrl * tree, const char * text, TREE_APPEND_DATA_EMBEDDED & appendData, int image=-1, int stateImage=-1, wxUint8 depth = 0);
};

class SOWERBASEEXP RichTextPasswordCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextPasswordCtrl)
    public:
        /** Default constructor */
        RichTextPasswordCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextPasswordCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextPasswordCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnPasswordCtrlText(wxCommandEvent& event);
        void OnPasswordCtrlTextEnter(wxCommandEvent& event);
        void OnPasswordCtrlTextMaxLen(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextListCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextListCtrl)
    public:
        /** Default constructor */
        RichTextListCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextListCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextListCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnListBeginDrag(wxListEvent& event);
        void OnListBeginRDrag(wxListEvent& event);
        void OnListBeginLabelEdit(wxListEvent& event);
        void OnListEndLabelEdit(wxListEvent& event);
        void OnListDeleteItem(wxListEvent& event);
        void OnListDeleteAllItems(wxListEvent& event);
        void OnListItemSelected(wxListEvent& event);
        void OnListItemDeselected(wxListEvent& event);
        void OnListItemActivated(wxListEvent& event);
        void OnListItemFocused(wxListEvent& event);
        void OnListItemRightClick(wxListEvent& event);
        void OnListItemMiddleClick(wxListEvent& event);
        void OnListKeyDown(wxListEvent& event);
        void OnInsertItem(wxListEvent& event);
        void OnListColClick(wxListEvent& event);
        void OnListColRightClick(wxListEvent& event);
        void OnListColBeginDrag(wxListEvent& event);
        void OnListColDragging(wxListEvent& event);
        void OnListColEndDrag(wxListEvent& event);
        void OnListCacheHint(wxListEvent& event);
};

class SOWERBASEEXP RichTextRichCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextRichCtrl)
    public:
        /** Default constructor */
        RichTextRichCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextRichCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextRichCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnRichTextLeftClick(wxRichTextEvent& event);
        void OnRichTextRightClick(wxRichTextEvent& event);
        void OnRichTextMiddleClick(wxRichTextEvent& event);
        void OnRichTextLeftDClick(wxRichTextEvent& event);
        void OnRichTextReturn(wxRichTextEvent& event);
        void OnRichTextCharacter(wxRichTextEvent& event);
        void OnRichTextConsumingCharacter(wxRichTextEvent& event);
        void OnRichTextDelete(wxRichTextEvent& event);
        void OnRichTextStyleChanged(wxRichTextEvent& event);
        void OnRichTextStyleSheetChanged(wxRichTextEvent& event);
        void OnRichTextStyleSheetReplacing(wxRichTextEvent& event);
        void OnRichTextStyleSheetReplaced(wxRichTextEvent& event);
        void OnRichTextPropertiesChanged(wxRichTextEvent& event);
        void OnRichTextContentInserted(wxRichTextEvent& event);
        void OnRichTextContentDeleted(wxRichTextEvent& event);
        void OnRichTextBufferReset(wxRichTextEvent& event);
        void OnRichTextSelectionChanged(wxRichTextEvent& event);
        void OnRichTextFocusObjectChanged(wxRichTextEvent& event);
        void OnRichTextText(wxCommandEvent& event);
        void OnRichTextTextEnter(wxCommandEvent& event);
        void OnRichTextUrl(wxTextUrlEvent& event);
};

class SOWERBASEEXP RichTextGauge : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextGauge)
    public:
        /** Default constructor */
        RichTextGauge(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextGauge(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextGauge();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
};

//
class SOWERBASEEXP RichTextSlider : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextSlider)
    public:
        /** Default constructor */
        RichTextSlider(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextSlider(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextSlider();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnSliderScrollTop(wxScrollEvent& event);
        void OnSliderScrollBottom(wxScrollEvent& event);
        void OnSliderScrollLineUp(wxScrollEvent& event);
        void OnSliderScrollLineDown(wxScrollEvent& event);
        void OnSliderScrollPageUp(wxScrollEvent& event);
        void OnSliderScrollPageDown(wxScrollEvent& event);
        void OnSliderScrollThumbTrack(wxScrollEvent& event);
        void OnSliderScrollThumbRelease(wxScrollEvent& event);
        void OnSliderScrollChanged(wxScrollEvent& event);
};

class SOWERBASEEXP RichTextImageButton : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextImageButton)
    public:
        /** Default constructor */
        RichTextImageButton(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextImageButton(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextImageButton();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnButtonClick(wxCommandEvent& event);
};

class SOWERBASEEXP RichTextLabel : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextLabel)
    public:
        /** Default constructor */
        RichTextLabel(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextLabel(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextLabel();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
};

class SOWERBASEEXP RichTextColourPicker : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextColourPicker)
    public:
        /** Default constructor */
        RichTextColourPicker(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextColourPicker(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextColourPicker();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnColourPickerChanged(wxColourPickerEvent& event);
};

class SOWERBASEEXP RichTextDirPicker : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextDirPicker)
    public:
        /** Default constructor */
        RichTextDirPicker(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextDirPicker(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextDirPicker();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnDirPickerChanged(wxFileDirPickerEvent& event);
};

class SOWERBASEEXP RichTextAnimationCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextAnimationCtrl)
    public:
        /** Default constructor */
        RichTextAnimationCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextAnimationCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextAnimationCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
};

class SOWERBASEEXP RichTextFilePicker : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextFilePicker)
    public:
        /** Default constructor */
        RichTextFilePicker(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextFilePicker(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextFilePicker();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnFilePickerChanged(wxFileDirPickerEvent& event);
};

class SOWERBASEEXP RichTextFontPicker : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextFontPicker)
    public:
        /** Default constructor */
        RichTextFontPicker(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextFontPicker(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextFontPicker();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnFontPickerChanged(wxFontPickerEvent& event);
};

class SOWERBASEEXP RichTextCalendarCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextCalendarCtrl)
    public:
        /** Default constructor */
        RichTextCalendarCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextCalendarCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextCalendarCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnCalendarClick(wxCalendarEvent& event);
        void OnCalendarSelChanged(wxCalendarEvent& event);
        void OnCalendarPageChanged(wxCalendarEvent& event);
};

class SOWERBASEEXP RichTextDataViewListCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextDataViewListCtrl)
    public:
        /** Default constructor */
        RichTextDataViewListCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextDataViewListCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextDataViewListCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnDataViewSelectionChanged(wxDataViewEvent& event);
        void OnDataViewItemActivated(wxDataViewEvent& event);
        void OnDataViewItemStartEditing(wxDataViewEvent& event);
        void OnDataViewItemEditingStarted(wxDataViewEvent& event);
        void OnDataViewItemEditingDone(wxDataViewEvent& event);
        void OnDataViewItemCollapsing(wxDataViewEvent& event);
        void OnDataViewItemCollapsed(wxDataViewEvent& event);
        void OnDataViewItemExpanding(wxDataViewEvent& event);
        void OnDataViewItemExpanded(wxDataViewEvent& event);
        void OnDataViewItemValueChanged(wxDataViewEvent& event);
        void OnDataViewItemContextMenu(wxDataViewEvent& event);
        void OnDataViewColumnHeaderClick(wxDataViewEvent& event);
        void OnDataViewColumnHeaderRightClick(wxDataViewEvent& event);
        void OnDataViewColumnSorted(wxDataViewEvent& event);
        void OnDataViewColumnReordered(wxDataViewEvent& event);
        void OnDataViewItemBeginDrag(wxDataViewEvent& event);
        void OnDataViewItemDropPossible(wxDataViewEvent& event);
        void OnDataViewItemDrop(wxDataViewEvent& event);
};

class SOWERBASEEXP RichTextDataViewTreeCtrl : public RichTextControlBase
{
    DECLARE_DYNAMIC_CLASS(RichTextDataViewTreeCtrl)
    public:
        /** Default constructor */
        RichTextDataViewTreeCtrl(wxRichTextObject* parent = NULL);
    /**
        Default constructor.

    */
        RichTextDataViewTreeCtrl(HtmlControlAttributes * cattr, wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
        /** Default destructor */
        virtual ~RichTextDataViewTreeCtrl();

        virtual void CreateControl(wxRect * rect);
        virtual wxRichTextObject* Clone() const;
        virtual wxString GetXMLNodeName() const;
        virtual int GetControlType();
        void OnDataViewSelectionChanged(wxDataViewEvent& event);
        void OnDataViewItemActivated(wxDataViewEvent& event);
        void OnDataViewItemStartEditing(wxDataViewEvent& event);
        void OnDataViewItemEditingStarted(wxDataViewEvent& event);
        void OnDataViewItemEditingDone(wxDataViewEvent& event);
        void OnDataViewItemCollapsing(wxDataViewEvent& event);
        void OnDataViewItemCollapsed(wxDataViewEvent& event);
        void OnDataViewItemExpanding(wxDataViewEvent& event);
        void OnDataViewItemExpanded(wxDataViewEvent& event);
        void OnDataViewItemValueChanged(wxDataViewEvent& event);
        void OnDataViewItemContextMenu(wxDataViewEvent& event);
        void OnDataViewColumnHeaderClick(wxDataViewEvent& event);
        void OnDataViewColumnHeaderRightClick(wxDataViewEvent& event);
        void OnDataViewColumnSorted(wxDataViewEvent& event);
        void OnDataViewColumnReordered(wxDataViewEvent& event);
        void OnDataViewItemBeginDrag(wxDataViewEvent& event);
        void OnDataViewItemDropPossible(wxDataViewEvent& event);
        void OnDataViewItemDrop(wxDataViewEvent& event);
};
#endif // RICHTEXTEMBEDDEDCONTROL_H
