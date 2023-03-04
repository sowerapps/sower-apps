///////////////////////////////////////////////////////////////////
// Name:        font.cpp
// Purpose:     Font attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"
#include "../../../include/string/strparser.h"

void SwRichTextAttr::SetFontEx(swUI8 id, const char * value, int deffontSize, bool html)
{
    SwString face;
    int fontSize;
    SwStrParser strList;
    CssSpacedList spaceList;

    bool isbold = false;
    if (HasFontWeight())
    {
        if (GetFontWeight() == wxFONTWEIGHT_BOLD)
        {
            isbold = true;
        }
    }

    if (html)
    {
        if (id == HTML_ATTRIBUTE_FACE && m_allowFont)
        {
            face = value;
            face.Replace("'", 1, "", 0);

            for (int pos = 0; pos < (int) face.Strlen(); pos ++)
            {
                if (face.GetAt(pos) == ',')
                    face.SetAt(pos, '\0');
            }

            wxFont font = GetFont();
            font.SetFaceName(face.GetArray());
            SetFont(font);
        }
        else if (id == HTML_ATTRIBUTE_SIZE)
        {
            face = value;
            face += "pt";
            fontSize = GetFontSize();
            if (!fontSize)
                fontSize = deffontSize;
            SetFontPointSize(GetWxFontSize(face, fontSize, deffontSize));
        }
    }
    else
    {
        if (id == CSS_ATTR_FONT_FAMILY && m_allowFont)
        {
            wxFont font = GetFont();
            font.SetFamily(GetWxFontFamily(SwHtml::GetFontFamily(value)));
            SetFont(font);
        }
        else if (id == CSS_ATTR_FONT_WEIGHT)
        {
            SetFontWeight(GetWxFontWeight(SwHtml::GetFontWeight(value), isbold));
        }
        else if (id == CSS_ATTR_FONT_STYLE)
        {
            SetFontStyle(GetWxFontStyle(SwHtml::GetFontStyle(value)));
        }
        else if (id == CSS_ATTR_FONT)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 4)
            {
                SetFontStyle(GetWxFontStyle(SwHtml::GetFontStyle(spaceList.GetValue(0))));
                SetFontWeight(GetWxFontWeight(SwHtml::GetFontWeight(spaceList.GetValue(1)), isbold));
                fontSize = GetFontSize();
                if (!fontSize)
                    fontSize = deffontSize;
                SetFontPointSize(GetWxFontSize(spaceList.GetValue(2), fontSize, deffontSize));
                strList.ParseString(spaceList.GetValue(3));

                if (strList.GetItems() && m_allowFont)
                {
                    wxFont font = GetFont();
                    font.SetFamily(GetWxFontFamily(SwHtml::GetFontFamily(strList.GetItem(0))));
                    SetFont(font);
                }
            }
            else if (strList.GetItems() == 3)
            {
                SetFontWeight(GetWxFontWeight(SwHtml::GetFontWeight(spaceList.GetValue(0)), isbold));
                fontSize = GetFontSize();
                if (!fontSize)
                    fontSize = deffontSize;
                SetFontPointSize(GetWxFontSize(spaceList.GetValue(1), fontSize, deffontSize));
                strList.ParseString(spaceList.GetValue(2));

                if (strList.GetItems() && m_allowFont)
                {
                    wxFont font = GetFont();
                    font.SetFamily(GetWxFontFamily(SwHtml::GetFontFamily(strList.GetItem(0))));
                    SetFont(font);
                }
            }
            else if (strList.GetItems() == 2)
            {
                fontSize = GetFontSize();
                if (!fontSize)
                    fontSize = deffontSize;
                SetFontPointSize(GetWxFontSize(spaceList.GetValue(0), fontSize, deffontSize));
                strList.ParseString(spaceList.GetValue(1));

                if (strList.GetItems() && m_allowFont)
                {
                    wxFont font = GetFont();
                    font.SetFamily(GetWxFontFamily(SwHtml::GetFontFamily(strList.GetItem(0))));
                    SetFont(font);
                }
            }
        }
        else if (id == CSS_ATTR_FONT_SIZE)
        {
            fontSize = GetFontSize();
            if (!fontSize)
                fontSize = deffontSize;
            SetFontPointSize(GetWxFontSize(value, fontSize, deffontSize));
        }
        else if (id == CSS_ATTR_FONT_VARIANT)
        {
            swUI8 variant = SwHtml::GetFontVariant(value);
            if (variant == FONT_VARIANT_SMALLCAPS)
            {
                SetTextEffectFlags(wxTEXT_ATTR_EFFECT_CAPITALS);
                SetTextEffects(GetTextEffects() | wxTEXT_ATTR_EFFECT_CAPITALS);
                SetFontPointSize(GetFontSize()*.70);
            }
        }
    }
}
