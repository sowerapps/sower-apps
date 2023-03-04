///////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     Text attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetText(swUI8 id, const char * value, bool html)
{
    swUI8 decoration;
    int leftIndent;

    if (html)
    {
        if (id == HTML_ATTRIBUTE_ALIGN)
        {
            SetAlignment(GetWxTextAlign(SwHtml::GetTextAlign(value)));
        }
        return;
    }
    else
    {
        if (id == CSS_ATTR_TEXT_ALIGN)
        {
            SetAlignment(GetWxTextAlign(SwHtml::GetTextAlign(value)));
        }
        else if (id == CSS_ATTR_TEXT_INDENT)
        {
            // Value must be in MM10.
            leftIndent = GetWxIndent(value, GetLeftIndent());
            if (leftIndent < 0)
            {
                SetLeftIndent(-leftIndent, -leftIndent);
            }
            else
                SetLeftIndent(leftIndent, -leftIndent);
        }
        else if (id == CSS_ATTR_TEXT_DECORATION)
        {
            if (strstr(value, "underline"))
            {
                SetFontUnderlined(true);
            }

            if (strstr(value, "line-through"))
            {
                // SetFlags(wxTEXT_ATTR_EFFECTS);
                SetTextEffectFlags(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
                SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
            }

            if (strstr(value, "none"))
            {
                SetFontUnderlined(false);
                // SetFlags(wxTEXT_ATTR_EFFECTS);
                SetTextEffectFlags(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
                SetTextEffects(GetTextEffects() & ~wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
            }
        }
        else if (id == CSS_ATTR_TEXT_TRANSFORM)
        {
            // Note: Not accurate for Capitalize and
            // lowercase is not supported.
            decoration = SwHtml::GetTextTransform(value);
            if (decoration == TEXT_TRANSFORM_UPPERCASE || decoration == TEXT_TRANSFORM_CAPITALIZE)
            {
                // SetFlags(wxTEXT_ATTR_EFFECTS);
                SetTextEffectFlags(wxTEXT_ATTR_EFFECT_CAPITALS);
                SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_CAPITALS);
            }
            else if (decoration == TEXT_TRANSFORM_NONE)
            {
                // SetFlags(wxTEXT_ATTR_EFFECTS);
                SetTextEffectFlags(wxTEXT_ATTR_EFFECT_CAPITALS);
                SetTextEffects(GetTextEffects() & ~wxTEXT_ATTR_EFFECT_CAPITALS);
            }
        }
   }
}
