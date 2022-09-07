///////////////////////////////////////////////////////////////////
// Name:        align.cpp
// Purpose:     Vertical alignment.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

// Numeric values are not supported.
void SwRichTextAttr::SetValign(swUI8 id, const char * value, bool isCell, bool html)
{
    swUI8 valign;

    if (html)
    {
        if (id == HTML_ATTRIBUTE_VALIGN)
        {
            if (!isCell)
            {
                valign = SwHtml::GetVerticalAlign(value);
                if (valign == VERTICAL_ALIGN_SUB)
                {
                    SetTextEffectFlags(GetTextEffectFlags() | wxTEXT_ATTR_EFFECT_SUBSCRIPT);
                    SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_SUBSCRIPT);
                }
                else if (valign == VERTICAL_ALIGN_SUPER)
                {
                    SetTextEffectFlags(GetTextEffectFlags() | wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
                    SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
                }
            }
            else
            {
                GetTextBoxAttr().SetVerticalAlignment(GetWxVerticleAlign(SwHtml::GetVerticalAlign(value)));
            }
        }
    }
    else
    {
        if (id == CSS_ATTR_VERTICAL_ALIGN)
        {
            if (!isCell)
            {
                valign = SwHtml::GetVerticalAlign(value);
                if (valign == VERTICAL_ALIGN_SUB)
                {
                    SetTextEffectFlags(wxTEXT_ATTR_EFFECT_SUBSCRIPT);
                    SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_SUBSCRIPT);
                }
                else if (valign == VERTICAL_ALIGN_SUPER)
                {
                    SetTextEffectFlags(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
                    SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
                }
            }
            else
            {
                GetTextBoxAttr().SetVerticalAlignment(GetWxVerticleAlign(SwHtml::GetVerticalAlign(value)));
            }
        }
    }
}
