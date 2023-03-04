///////////////////////////////////////////////////////////////////
// Name:        stylesheet.cpp
// Purpose:     Initialization of a wxRichTextStyleSheet to be used
//              by all SwRichTextCtrl, and derived objects.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"

void SwApplicationInterface::FillStyleSheet()
{
    wxFont roman(sw_ReaderFontSize, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    wxRichTextParagraphStyleDefinition * defpgstyle = new wxRichTextParagraphStyleDefinition(L"Basic Style");
    wxRichTextAttr defattr;
    defattr.SetFontFaceName(roman.GetFaceName());
    defattr.SetFontSize(12);

    defattr.SetFlags(wxTEXT_ATTR_FONT | wxTEXT_ATTR_BACKGROUND_COLOUR | wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_TABS|
                    wxTEXT_ATTR_PARA_SPACING_BEFORE|wxTEXT_ATTR_PARA_SPACING_AFTER|wxTEXT_ATTR_LINE_SPACING|
                    wxTEXT_ATTR_BULLET_STYLE|wxTEXT_ATTR_BULLET_NUMBER);
    defpgstyle->SetStyle(defattr);

    sw_styleSheet.AddParagraphStyle(defpgstyle);

    wxRichTextListStyleDefinition* listdef = new wxRichTextListStyleDefinition(L"Standard Bullet");
    listdef->SetAttributes(0, 50, 50, wxTEXT_ATTR_BULLET_STYLE_STANDARD, L"standard/circle");
    sw_styleSheet.AddListStyle(listdef);

    listdef = new wxRichTextListStyleDefinition(L"Decimal");
    listdef->SetAttributes(0, 50, 50, wxTEXT_ATTR_BULLET_STYLE_ARABIC | wxTEXT_ATTR_BULLET_STYLE_PERIOD | wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT);
    sw_styleSheet.AddListStyle(listdef);

    listdef = new wxRichTextListStyleDefinition(L"Alpha Lower");
    listdef->SetAttributes(0, 50, 50, wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER|wxTEXT_ATTR_BULLET_STYLE_PERIOD | wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT);
    sw_styleSheet.AddListStyle(listdef);

    listdef = new wxRichTextListStyleDefinition(L"Alpha Upper");
    listdef->SetAttributes(0, 50, 50, wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER|wxTEXT_ATTR_BULLET_STYLE_PERIOD | wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT);
    sw_styleSheet.AddListStyle(listdef);

    listdef = new wxRichTextListStyleDefinition(L"Roman Lower");
    listdef->SetAttributes(0, 50, 50, wxTEXT_ATTR_BULLET_STYLE_ROMAN_LOWER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES | wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT);
    sw_styleSheet.AddListStyle(listdef);

    listdef = new wxRichTextListStyleDefinition(L"Roman Upper");
    listdef->SetAttributes(0, 50, 50, wxTEXT_ATTR_BULLET_STYLE_ROMAN_UPPER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES | wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT);
    sw_styleSheet.AddListStyle(listdef);
}
