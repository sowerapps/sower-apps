///////////////////////////////////////////////////////////////////
// Name:        richtextattr.cpp
// Purpose:     Derived from wxRichTextAttr, sets attributes from
//              CssAttributeList.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"
#include "../../../include/string/string.h"
#include "../../../include/html/html.h"
#include "../../../include/html/html_attributes.h"

void SwRichTextAttr::Reset()
{
    m_allowFont = true;
    // If this is false bulleted lists are drawn by the SwRichTextInterface object and not wxRichTextCtrl.
    m_allowList = false;
    m_allowMargins = true;
    m_allowPadding = true;
    m_display = true;
    m_listStyle = LIST_STYLE_TYPE_DECIMAL;
    GetTextBoxAttr().Reset();
    Init();
    SetBackgroundColour(*wxWHITE);
    SetBulletNumber(1);
    m_listStart = 1;
    m_css.Reset();
}

void SwRichTextAttr::SetHtmlAttributes(CssAttributeList & html, int deffontSize, bool isCell)
{
    swUI8 id;
    bool hasStyle = false;
    swUI32 styleId;

    for (swUI32 i = 0; i < html.GetItems(); i ++)
    {
        id = SwHtmlAttributes::IdentifyAttribute(html.GetAttribute(i));

        if (id == HTML_ATTRIBUTE_UNKNOWN && html.GetSpecificity(i) > 0)
        {
            m_css.Add(html.GetAttribute(i), html.GetValue(i), html.GetSpecificity(i));
        }
        else if (id == HTML_ATTRIBUTE_ALIGN)
        {
            SetText(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_BORDER)
        {
            SetBorder(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_COLOR || id == HTML_ATTRIBUTE_BGCOLOR)
        {
            SetColor(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_FACE || id == HTML_ATTRIBUTE_SIZE)
        {
            SetFontEx(id, html.GetValue(i), deffontSize, true);
        }
        else if (id == HTML_ATTRIBUTE_CELLPADDING)
        {
            SetPadding(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_CELLSPACING)
        {
            SetPadding(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_START || id == HTML_ATTRIBUTE_TYPE)
        {
            SetList(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_HEIGHT)
        {
            SetHeight(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_WIDTH)
        {
            SetWidth(id, html.GetValue(i), true);
        }
        else if (id == HTML_ATTRIBUTE_VALIGN)
        {
            SetValign(id, html.GetValue(i), isCell, true);
        }
        else if (id == HTML_ATTRIBUTE_HREF)
        {
            SetURL(html.GetValue(i));
        }
        else if (id == HTML_ATTRIBUTE_NAME)
        {
            SetURL(html.GetValue(i));
        }
        else if (id == HTML_ATTRIBUTE_STYLE)
        {
            hasStyle = true;
            styleId = i;
        }
    }

    if (hasStyle)
    {
        m_css.ParseStyle(html.GetValue(styleId));
    }

    if (m_css.GetItems())
    {
        SetCssAttributes(m_css, deffontSize, isCell);
    }

}

void SwRichTextAttr::SetCssAttributes(CssAttributeList & css, int deffontSize, bool isCell)
{
    swUI8 id;

    for (swUI32 i = 0; i < css.GetItems(); i ++)
    {
        id = CssAttributes::IdentifyAttribute(css.GetAttribute(i));

        if (id == CSS_ATTR_UNKNOWN)
            continue;
        else if (id >= CSS_ATTR_BORDER && id <= CSS_ATTR_BORDER_TOP_WIDTH)
        {
            SetBorder(id, css.GetValue(i), false);
        }
        else if (id == CSS_ATTR_COLOR || id == CSS_ATTR_BACKGROUND_COLOR)
        {
            SetColor(id, css.GetValue(i), false);
        }
        else if (id == CSS_ATTR_FLOAT)
        {
            SetFloat(id, css.GetValue(i), false);
        }
        else if (id >= CSS_ATTR_FONT && id <= CSS_ATTR_FONT_WEIGHT)
        {
            SetFontEx(id, css.GetValue(i), deffontSize, false);
        }
        else if (id == CSS_ATTR_LIST_STYLE || id == CSS_ATTR_LIST_STYLE_TYPE)
        {
            SetList(id, css.GetValue(i), false);
        }
        else if (id >= CSS_ATTR_MARGIN && id <= CSS_ATTR_MARGIN_TOP)
        {
            SetMargins(id, css.GetValue(i), false);
        }
        else if (id >= CSS_ATTR_PADDING && id <= CSS_ATTR_PADDING_TOP)
        {
            SetPadding(id, css.GetValue(i), false);
        }
        else if (id >= CSS_ATTR_TEXT_ALIGN && id <= CSS_ATTR_TEXT_TRANSFORM)
        {
            SetText(id, css.GetValue(i), false);
        }
        else if (id == CSS_ATTR_WHITE_SPACE)
        {
            SetWhiteSpace(id, css.GetValue(i), false);
        }
        else if (id == CSS_ATTR_HEIGHT)
        {
            SetHeight(id, css.GetValue(i), false);
        }
        else if (id == CSS_ATTR_WIDTH)
        {
            SetWidth(id, css.GetValue(i), false);
        }
        else if (id == CSS_ATTR_VERTICAL_ALIGN)
        {
            SetValign(id, css.GetValue(i), isCell, false);
        }
        else if (id == CSS_ATTR_DISPLAY)
        {
            if (stricmp(css.GetValue(i), "none") == 0)
                m_display = false;
            else
                m_display = true;
        }
    }
}

void SwRichTextAttr::SetListStart(int start)
{
    m_listStart = start;
}

int SwRichTextAttr::GetListStart()
{
    return m_listStart;
}

CssAttributeList & SwRichTextAttr::GetCssAttributes()
{
    return m_css;
}
