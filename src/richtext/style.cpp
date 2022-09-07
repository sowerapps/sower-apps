///////////////////////////////////////////////////////////////////
// Name:        style.cpp
// Purpose:     Set text styles, margins, etc. in control.
//              Some styles are from a static wxRichTextStyleSheet,
//              that is initialized by SwApplicationInterface (appifa.h) and is
//              set for every SwRichTextCtrl, or derived object that is
//              created.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"
#include <wx/richtext/richtextformatdlg.h>
#include <wx/richtext/richtextfontpage.h>
#include <wx/colordlg.h>
#include <wx/colourdata.h>
#include "../../include/appi/appifa.h"

void SwRichTextCtrl::OnAnchor(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
    {
        wxRichTextObject* obj = GetFocusObject();
        if (obj->GetProperties().HasProperty("rtx:anchor:"))
        {
            obj->GetProperties().Remove("rtx:anchor:");
            range = GetSelectionRange();
            wxTextAttr attr;
            GetStyleForRange(range, attr);
            attr.SetTextColour(*wxBLACK);
            SetStyle(range, attr);
        }
        else
        {
            wxString name = wxGetTextFromUser(SwApplicationInterface::GetControlString("SID_NAME", L"Name"));
            if (!name.IsEmpty())
            {
                obj->GetProperties().SetProperty("rtx:anchor:", name);
                range = GetSelectionRange();
                wxTextAttr attr;
                GetStyleForRange(range, attr);
                attr.SetTextColour(*wxBLUE);
                SetStyle(range, attr);
            }
        }
    }
}

void SwRichTextCtrl::OnFont(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(0, GetLastPosition() + 1);

    wxRichTextFormattingDialog formatDlg(wxRICHTEXT_FORMAT_FONT, this, "", wxID_ANY, wxDefaultPosition, wxDefaultSize, wxCAPTION | wxSYSTEM_MENU);

    formatDlg.SetLabel(SwApplicationInterface::GetControlString("SID_FONT", L"Font"));

    formatDlg.GetStyle(this, range);
    wxWindow * w;
    w = formatDlg.FindWindow(wxRICHTEXT_FORMAT_HELP_BUTTON);

    if (w)
        w->Enable(false);
    /*
    w = formatDlg.FindWindow(wxRichTextFontPage::ID_RICHTEXTFONTPAGE_SMALLCAPSCTRL);

    if (w)
        w->Hide();
    */

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(this, range, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_OPTIMIZE|wxRICHTEXT_SETSTYLE_CHARACTERS_ONLY);
    }
}

void SwRichTextCtrl::OnFontSizeIncrease(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetFontSize(attr.GetFontSize() + 1);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnFontSizeDecrease(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetFontSize(attr.GetFontSize() - 1);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnBold(wxCommandEvent& event)
{
    ApplyBoldToSelection();
}

void SwRichTextCtrl::OnItalic(wxCommandEvent& event)
{
    ApplyItalicToSelection();
}

void SwRichTextCtrl::OnUnderLine(wxCommandEvent& event)
{
    ApplyUnderlineToSelection();
}

void SwRichTextCtrl::OnStrikeThrough(wxCommandEvent& event)
{
    ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
}

void SwRichTextCtrl::OnBaseLine(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxRichTextAttr attr;
    GetStyleForRange(range, attr);
    ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_NONE);

    if (attr.HasTextEffect(wxTEXT_ATTR_EFFECT_STRIKETHROUGH))
        ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);

    if (attr.HasTextEffect(wxTEXT_ATTR_EFFECT_CAPITALS))
        ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_CAPITALS);
}

void SwRichTextCtrl::OnSuperScript(wxCommandEvent& event)
{
    ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
}

void SwRichTextCtrl::OnSubScript(wxCommandEvent& event)
{
    ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUBSCRIPT);
}

void SwRichTextCtrl::OnCapitalize(wxCommandEvent& event)
{
    ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_CAPITALS);
}

void SwRichTextCtrl::OnAlignLeft(wxCommandEvent& event)
{
    ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_LEFT);
}

void SwRichTextCtrl::OnAlignCenter(wxCommandEvent& event)
{
    ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_CENTER);
}

void SwRichTextCtrl::OnAlignRight(wxCommandEvent& event)
{
    ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_RIGHT);
}

void SwRichTextCtrl::OnAlignTop(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxRichTextAttr attr;
    GetStyleForRange(range, attr);
    attr.GetTextBoxAttr().SetVerticalAlignment(wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_TOP);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnAlignMiddle(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxRichTextAttr attr;
    GetStyleForRange(range, attr);
    attr.GetTextBoxAttr().SetVerticalAlignment(wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_CENTRE);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnAlignBottom(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxRichTextAttr attr;
    GetStyleForRange(range, attr);
    attr.GetTextBoxAttr().SetVerticalAlignment(wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_BOTTOM);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnLineSpacing1(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetLineSpacing(wxTEXT_ATTR_LINE_SPACING_NORMAL);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnLineSpacing15(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetLineSpacing(wxTEXT_ATTR_LINE_SPACING_HALF);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnLineSpacing2(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetLineSpacing(wxTEXT_ATTR_LINE_SPACING_TWICE);
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnIndentMore(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetLeftIndent(attr.GetLeftIndent() + 1, attr.GetLeftSubIndent());
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnIndentLess(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);
    attr.SetLeftIndent(attr.GetLeftIndent() - 1, attr.GetLeftSubIndent());
    SetStyle(range, attr);
}

void SwRichTextCtrl::OnTextColor(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);

    wxColourDialog * dlg = new wxColourDialog(this);
    dlg->GetColourData().SetColour(attr.GetTextColour());

    if (dlg->ShowModal() == wxID_OK)
    {
        attr.SetTextColour(dlg->GetColourData().GetColour());
        SetStyle(range, attr);
    }

    dlg->Destroy();
    delete dlg;
}

void SwRichTextCtrl::OnBackgroundColor(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    wxTextAttr attr;
    GetStyleForRange(range, attr);

    wxColourDialog * dlg = new wxColourDialog(this);
    dlg->GetColourData().SetColour(attr.GetBackgroundColour());

    if (dlg->ShowModal() == wxID_OK)
    {
        attr.SetBackgroundColour(dlg->GetColourData().GetColour());
        SetStyle(range, attr);
    }

    dlg->Destroy();
    delete dlg;
}

void SwRichTextCtrl::OnBulletedList(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    if (event.IsChecked())
        SetListStyle(range, "Standard Bullet", wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    else
        ClearListStyle(range);
}

void SwRichTextCtrl::OnArabicList(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    if (event.IsChecked())
        SetListStyle(range, "Arabic", wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    else
        ClearListStyle(range);
}

void SwRichTextCtrl::OnRomanListUpper(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    if (event.IsChecked())
        SetListStyle(range, "Roman Upper", wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    else
        ClearListStyle(range);
}

void SwRichTextCtrl::OnRomanListLower(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    if (event.IsChecked())
        SetListStyle(range, "Roman Lower", wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    else
        ClearListStyle(range);
}

void SwRichTextCtrl::OnAlphaListUpper(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    if (event.IsChecked())
        SetListStyle(range, "Alpha Lower", wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    else
        ClearListStyle(range);
}

void SwRichTextCtrl::OnAlphaListLower(wxCommandEvent& event)
{
    wxRichTextRange range;

    if (HasSelection())
        range = GetSelectionRange();
    else
        range = wxRichTextRange(GetCaretPosition(), GetCaretPosition());

    if (event.IsChecked())
        SetListStyle(range, "Alpha Upper", wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    else
        ClearListStyle(range);
}
