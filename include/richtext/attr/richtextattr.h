///////////////////////////////////////////////////////////////////
// Name:        richtextattr.h
// Purpose:     Derived from wxRichTextAttr, sets attributes from
//              CssAttributeList.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef RICHTEXTATTR_H_INCLUDED
#define RICHTEXTATTR_H_INCLUDED

#include "../../sowerbase.h"
#include <wx/richtext/richtextbuffer.h>
#include <wx/richtext/richtextctrl.h>
#include "../../css/css_attributes.h"
#include "../../css/css_units.h"

class SOWERBASEEXP SwRichTextAttr : public wxRichTextAttr
{
public:
    SwRichTextAttr ()
    {
        Reset();
    };
    virtual ~SwRichTextAttr() {};

    void Reset();
    void SetBorder(swUI8 id, const char * value, bool html);
    void SetColor(swUI8 id, const char * value, bool html);
    void SetFloat(swUI8 id, const char * value, bool html);
    void SetFontEx(swUI8 id, const char * value, int deffontSize, bool html);
    void SetList(swUI8 id, const char * value, bool html);
    void SetHeight(swUI8 id, const char * value, bool html);
    void SetMargins(swUI8 id, const char * value, bool html);
    void SetPadding(swUI8 id, const char * value, bool html);
    void SetText(swUI8 id, const char * value, bool html);
    void SetValign(swUI8 id, const char * value, bool isCell, bool html);
    void SetWhiteSpace(swUI8 id, const char * value, bool html);
    void SetWidth(swUI8 id, const char * value, bool html);
    void SetHtmlAttributes(CssAttributeList & html, int deffontSize, bool isCell = false);
    void SetCssAttributes(CssAttributeList & css, int deffontSize, bool isCell = false);
    void SetListStart(int start);
    int GetListStart();
    CssAttributeList & GetCssAttributes();

    wxFontFamily GetWxFontFamily(swUI8 family)
    {
        switch (family)
        {
        case ATTRIBUTE_INHERIT :
            return wxFONTFAMILY_DEFAULT;
            break;
        case FONT_FAMILY_TELETYPE :
        case FONT_FAMILY_MONOSPACE :
            return wxFONTFAMILY_TELETYPE;
            break;
        case FONT_FAMILY_SANS_SERIFF :
            return wxFONTFAMILY_SWISS;
            break;
        case FONT_FAMILY_SERIFF :
        case FONT_FAMILY_ROMAN :
        case FONT_FAMILY_TIMES :
            return wxFONTFAMILY_ROMAN;
            break;
        case FONT_FAMILY_DECORATIVE :
        case FONT_FAMILY_FANTASY :
            return wxFONTFAMILY_DECORATIVE;
            break;
        case FONT_FAMILY_CURSIVE :
        case FONT_FAMILY_SCRIPT :
            return wxFONTFAMILY_SCRIPT;
            break;
        }

        return wxFONTFAMILY_ROMAN;
    }

    wxFontWeight GetWxFontWeight(swUI8 weight, bool isbold)
    {
        switch (weight)
        {
        case FONT_WEIGHT_NORMAL :
        case FONT_WEIGHT_400 :
        case FONT_WEIGHT_500 :
            return wxFONTWEIGHT_NORMAL;
            break;
        case FONT_WEIGHT_BOLD :
        case FONT_WEIGHT_600 :
        case FONT_WEIGHT_700 :
        case FONT_WEIGHT_800 :
        case FONT_WEIGHT_900 :
            return wxFONTWEIGHT_BOLD;
            break;
        case FONT_WEIGHT_100 :
        case FONT_WEIGHT_200 :
        case FONT_WEIGHT_300 :
            return wxFONTWEIGHT_LIGHT;
            break;
        case FONT_WEIGHT_LIGHTER :
            if (isbold)
                return wxFONTWEIGHT_NORMAL;
            else
                return wxFONTWEIGHT_LIGHT;
            break;
        case FONT_WEIGHT_BOLDER :
            if (isbold)
                return wxFONTWEIGHT_MAX;
            else
                return wxFONTWEIGHT_BOLD;
            break;
        }

        return wxFONTWEIGHT_NORMAL;
    }

    wxFontStyle GetWxFontStyle(swUI8 style)
    {
        switch (style)
        {
        case FONT_STYLE_NORMAL :
            return wxFONTSTYLE_NORMAL;
            break;
        case FONT_STYLE_ITALIC :
        case FONT_STYLE_OBLIQUE :
            return wxFONTSTYLE_ITALIC;
            break;
        }

        return wxFONTSTYLE_NORMAL;
    }

    wxTextBoxAttrVerticalAlignment GetWxVerticleAlign(swUI8 valign)
    {
        if (valign == VERTICAL_ALIGN_TOP || valign == VERTICAL_ALIGN_TEXT_TOP)
            return wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_TOP;
        else if (valign == VERTICAL_ALIGN_MIDDLE)
            return wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_CENTRE;
        else if (valign == VERTICAL_ALIGN_BOTTOM || valign == VERTICAL_ALIGN_TEXT_BOTTOM)
            return wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_BOTTOM;

        return wxTEXT_BOX_ATTR_VERTICAL_ALIGNMENT_CENTRE;
    }

    wxTextAttrAlignment GetWxTextAlign(swUI8 align)
    {
        switch (align)
        {
        case TEXT_ALIGN_NONE :
            return wxTEXT_ALIGNMENT_DEFAULT;
            break;
        case TEXT_ALIGN_LEFT :
            return wxTEXT_ALIGNMENT_LEFT;
            break;
        case TEXT_ALIGN_RIGHT :
            return wxTEXT_ALIGNMENT_RIGHT;
            break;
        case TEXT_ALIGN_CENTER :
            return wxTEXT_ALIGNMENT_CENTER;
            break;
        case TEXT_ALIGN_JUSTIFY :
            return wxTEXT_ALIGNMENT_LEFT;
        }

        return wxTEXT_ALIGNMENT_DEFAULT;
    }

    int GetWxIndent(const char * value, float current)
    {
        if (!value)
            return 0;

        float indent;
        swUI8 unit;
        SwHtml::GetFloatData(value, indent, unit);

        if (unit == UNIT_PERCENT)
        {
            return current * (indent / 100);
        }
        else if (unit == UNIT_EM)
        {
            return current * indent;
        }

        return (int) CssUnits::GetValueAsMM10(indent, unit);
    }

    int GetWxFontSize(const char * value, int curSize, int defSize)
    {
        if (!value)
            return 0;

        float fontSize;
        swUI8 unit;

        SwHtml::GetFontSize(value, fontSize, unit);

        if (unit == UNIT_PREDEFINED)
        {
            switch ((int) fontSize)
            {
            case FONT_SIZE_XX_SMALL :
                return defSize * .80;
                break;
            case FONT_SIZE_X_SMALL :
                return defSize * .87;
                break;
            case FONT_SIZE_SMALL :
                return defSize * .93;
                break;
            case FONT_SIZE_MEDIUM :
                return defSize;
                break;
            case FONT_SIZE_LARGE :
                return defSize * 1.7;
                break;
            case FONT_SIZE_X_LARGE :
                return defSize * 3.4;
                break;
            case FONT_SIZE_XX_LARGE :
                return defSize * 4.1;
                break;
            case FONT_SIZE_SMALLER :
                return curSize / 1.2;
                break;
            case FONT_SIZE_LARGER :
                return curSize * 1.2;
                break;
            }
        }
        else if (unit == UNIT_PERCENT || unit == UNIT_EM)
        {
            // SwHtml::GetFontSize() converts text %
            // to floating value equal to em.
            return curSize * fontSize;
        }

        return (int) CssUnits::GetValueAsPt(fontSize, unit);
    }

    wxTextAttrBulletStyle GetWxListStyle(const char * value, swUI8 & bullet)
    {
        bullet = ATTRIBUTE_UNSPECIFIED;
        swUI8 liststyleType = SwHtml::GetListStyle(value);

        if (liststyleType == LIST_STYLE_TYPE_ARMENIAN)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER;
        else if (liststyleType == LIST_STYLE_TYPE_CIRCLE)
        {
            bullet = LIST_STYLE_TYPE_CIRCLE;
            return wxTEXT_ATTR_BULLET_STYLE_STANDARD;
        }
        else if (liststyleType == LIST_STYLE_TYPE_DECIMAL)
            return wxTEXT_ATTR_BULLET_STYLE_ARABIC;
        else if (liststyleType == LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO)
            return wxTEXT_ATTR_BULLET_STYLE_ARABIC;
        else if (liststyleType == LIST_STYLE_TYPE_DISC)
            return wxTEXT_ATTR_BULLET_STYLE_STANDARD;
        else if (liststyleType == LIST_STYLE_TYPE_HEBREW)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER;
        else if (liststyleType == LIST_STYLE_TYPE_LOWER_ALPHA)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER;
        else if (liststyleType == LIST_STYLE_TYPE_UPPER_ALPHA)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER;
        else if (liststyleType == LIST_STYLE_TYPE_LOWER_ROMAN)
            return wxTEXT_ATTR_BULLET_STYLE_ROMAN_LOWER;
        else if (liststyleType == LIST_STYLE_TYPE_UPPER_ROMAN)
            return wxTEXT_ATTR_BULLET_STYLE_ROMAN_UPPER;
        else if (liststyleType == LIST_STYLE_TYPE_LOWER_GREEK)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER;
        else if (liststyleType == LIST_STYLE_TYPE_UPPER_GREEK)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER;
        else if (liststyleType == LIST_STYLE_TYPE_LOWER_LATIN)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER;
        else if (liststyleType == LIST_STYLE_TYPE_UPPER_LATIN)
            return wxTEXT_ATTR_BULLET_STYLE_LETTERS_UPPER;
        else if (liststyleType == LIST_STYLE_TYPE_SQUARE)
        {
            bullet = LIST_STYLE_TYPE_SQUARE;
            return wxTEXT_ATTR_BULLET_STYLE_STANDARD;
        }

        bullet = LIST_STYLE_TYPE_CIRCLE;
        return wxTEXT_ATTR_BULLET_STYLE_STANDARD;
    }

    wxTextAttrBorderStyle GetWxBorderStyle(swUI8 borderStyle)
    {
        if (borderStyle == ATTRIBUTE_INHERIT)
            return wxTEXT_BOX_ATTR_BORDER_SOLID;
        else if (borderStyle == BORDER_STYLE_NONE)
            return wxTEXT_BOX_ATTR_BORDER_NONE;
        else if (borderStyle == BORDER_STYLE_HIDDEN)
            return wxTEXT_BOX_ATTR_BORDER_NONE;
        else if (borderStyle == BORDER_STYLE_DOTTED)
            return wxTEXT_BOX_ATTR_BORDER_DOTTED;
        else if (borderStyle == BORDER_STYLE_DASHED)
            return wxTEXT_BOX_ATTR_BORDER_DASHED;
        else if (borderStyle == BORDER_STYLE_SOLID)
            return wxTEXT_BOX_ATTR_BORDER_SOLID;
        else if (borderStyle == BORDER_STYLE_DOUBLE)
            return wxTEXT_BOX_ATTR_BORDER_DOUBLE;
        else if (borderStyle == BORDER_STYLE_GROOVE)
            return wxTEXT_BOX_ATTR_BORDER_GROOVE;
        else if (borderStyle == BORDER_STYLE_RIDGE)
            return wxTEXT_BOX_ATTR_BORDER_RIDGE;
        else if (borderStyle == BORDER_STYLE_INSET)
            return wxTEXT_BOX_ATTR_BORDER_INSET;
        else if (borderStyle == BORDER_STYLE_OUTSET)
            return wxTEXT_BOX_ATTR_BORDER_OUTSET;

        return wxTEXT_BOX_ATTR_BORDER_SOLID;
    }
/*
    wxTextBoxAttrWhitespaceMode GetWxWhiteSpaceMode(swUI8 whiteSpace)
    {
        if (whiteSpace == ATTRIBUTE_INHERIT)
            return wxTEXT_BOX_ATTR_WHITESPACE_NORMAL;
        else if (whiteSpace == WHITE_SPACE_NORMAL)
            return wxTEXT_BOX_ATTR_WHITESPACE_NORMAL;
        else if (whiteSpace == WHITE_SPACE_NOWRAP)
            return wxTEXT_BOX_ATTR_WHITESPACE_NO_WRAP;
        else if (whiteSpace == WHITE_SPACE_PRE)
            return wxTEXT_BOX_ATTR_WHITESPACE_PREFORMATTED;
        else if (whiteSpace == WHITE_SPACE_PRE_LINE)
            return wxTEXT_BOX_ATTR_WHITESPACE_PREFORMATTED_LINE;
        else if (whiteSpace == WHITE_SPACE_PRE_WRAP)
            return wxTEXT_BOX_ATTR_WHITESPACE_PREFORMATTED_WRAP;

        return wxTEXT_BOX_ATTR_WHITESPACE_NORMAL;
    }
*/
    wxTextBoxAttrFloatStyle GetWxFloatMode(swUI8 flt)
    {
        if (flt == FLOAT_DIRECTION_NONE)
            return wxTEXT_BOX_ATTR_FLOAT_NONE;
        else if (flt == FLOAT_DIRECTION_LEFT)
            return wxTEXT_BOX_ATTR_FLOAT_LEFT;
        else if (flt == FLOAT_DIRECTION_RIGHT)
            return wxTEXT_BOX_ATTR_FLOAT_RIGHT;

        return wxTEXT_BOX_ATTR_FLOAT_NONE;
    }

    int GetWxMargin(float margin, swUI8 unit, float current)
    {
        if (unit == UNIT_PERCENT)
        {
            return current * (margin / 100);
        }
        else if (unit == UNIT_EM)
        {
            return current * margin;
        }

        return (int) CssUnits::GetValueAsMM10(margin, unit);
    }

    float GetWxPadding(float padding, swUI8 unit, float current)
    {
        if (unit == UNIT_PERCENT)
        {
            return current * (padding / 100);
        }
        else if (unit == UNIT_EM)
        {
            return current * padding;
        }

        return CssUnits::GetValueAsMM(padding, unit);
    }

    float GetWxBorder(float border, swUI8 unit, float current)
    {
        if (unit == UNIT_PERCENT)
        {
            return current * (border / 100);
        }
        else if (unit == UNIT_EM)
        {
            return current * border;
        }

        return CssUnits::GetValueAsMM10(border, unit);
    }

    CssAttributeList m_css;
    bool m_allowFont;
    bool m_allowList;
    bool m_allowMargins;
    bool m_allowPadding;
    bool m_display;
    swUI8 m_listStyle;
    int m_listStart;
};

#endif // RICHTEXTATTR_H_INCLUDED
