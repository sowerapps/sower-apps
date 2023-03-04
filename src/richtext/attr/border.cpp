///////////////////////////////////////////////////////////////////
// Name:        border.cpp
// Purpose:     Border attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"
#include "../../../include/html/html_color.h"

void SwRichTextAttr::SetBorder(swUI8 id, const char * value, bool html)
{
    swUI8 unit;
    float width;
    CssSpacedList   spaceList;

    if (html)
    {
        if (id == HTML_ATTRIBUTE_BORDER)
        {
            if (value[0] == '1')
            {
                GetTextBoxAttr().GetBorder().SetColour(*wxBLACK);
                GetTextBoxAttr().GetBorder().SetWidth(1, wxTEXT_ATTR_UNITS_PIXELS);
                GetTextBoxAttr().GetBorder().SetStyle(wxTEXT_BOX_ATTR_BORDER_SOLID);
                GetTextBoxAttr().GetPadding().GetLeft().SetValue(3, wxTEXT_ATTR_UNITS_PIXELS);
                GetTextBoxAttr().GetPadding().GetTop().SetValue(3, wxTEXT_ATTR_UNITS_PIXELS);
                GetTextBoxAttr().GetPadding().GetRight().SetValue(3, wxTEXT_ATTR_UNITS_PIXELS);
                GetTextBoxAttr().GetPadding().GetBottom().SetValue(3, wxTEXT_ATTR_UNITS_PIXELS);
            }
            else
            {
                GetTextBoxAttr().GetBorder().SetStyle(wxTEXT_BOX_ATTR_BORDER_NONE);
            }
        }
    }
    else if (!html)
    {
        if (id == CSS_ATTR_BORDER)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                GetTextBoxAttr().GetBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
            }
            else if (spaceList.GetItems() == 2)
            {
                GetTextBoxAttr().GetBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(0))));
                GetTextBoxAttr().GetBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(1))));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), width, unit);
                GetTextBoxAttr().GetBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetTop().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
                GetTextBoxAttr().GetBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(1))));
                GetTextBoxAttr().GetBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(2))));
            }
        }
        else if (id == CSS_ATTR_BORDER_COLLAPSE)
        {
            if (stricmp(value, "collapse") == 0)
                GetTextBoxAttr().SetCollapseBorders(wxTEXT_BOX_ATTR_COLLAPSE_FULL);
            else if (stricmp(value, "separate") == 0)
                GetTextBoxAttr().SetCollapseBorders(wxTEXT_BOX_ATTR_COLLAPSE_NONE);
        }
        else if (id == CSS_ATTR_BORDER_STYLE)
        {
            GetTextBoxAttr().GetBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(value)));
        }
        else if (id == CSS_ATTR_BORDER_COLOR)
        {
            GetTextBoxAttr().GetBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        }
        else if (id == CSS_ATTR_BORDER_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);
            GetTextBoxAttr().GetBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetTop().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
        }
        else if (id == CSS_ATTR_BORDER_BOTTOM)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                GetTextBoxAttr().GetBottomBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
            }
            else if (spaceList.GetItems() == 2)
            {
                GetTextBoxAttr().GetBottomBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(0))));
                GetTextBoxAttr().GetBottomBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(1))));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), width, unit);
                GetTextBoxAttr().GetBottomBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetBottom().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
                GetTextBoxAttr().GetBottomBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(1))));
                GetTextBoxAttr().GetBottomBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(2))));
            }
        }
        else if (id == CSS_ATTR_BORDER_BOTTOM_STYLE)
        {
            GetTextBoxAttr().GetBottomBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(value)));
        }
        else if (id == CSS_ATTR_BORDER_BOTTOM_COLOR)
        {
            GetTextBoxAttr().GetBottomBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        }
        else if (id == CSS_ATTR_BORDER_BOTTOM_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);
            GetTextBoxAttr().GetBottomBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetBottom().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
        }
        else if (id == CSS_ATTR_BORDER_TOP)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                GetTextBoxAttr().GetTopBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
            }
            else if (spaceList.GetItems() == 2)
            {
                GetTextBoxAttr().GetTopBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(0))));
                GetTextBoxAttr().GetTopBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(1))));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), width, unit);
                GetTextBoxAttr().GetTopBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetTop().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
                GetTextBoxAttr().GetTopBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(1))));
                GetTextBoxAttr().GetTopBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(2))));
            }
        }
        else if (id == CSS_ATTR_BORDER_TOP_STYLE)
        {
            GetTextBoxAttr().GetTopBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(value)));
        }
        else if (id == CSS_ATTR_BORDER_TOP_COLOR)
        {
            GetTextBoxAttr().GetTopBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        }
        else if (id == CSS_ATTR_BORDER_TOP_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);
            GetTextBoxAttr().GetTopBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetTop().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
        }
        else if (id == CSS_ATTR_BORDER_LEFT)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                GetTextBoxAttr().GetLeftBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
            }
            else if (spaceList.GetItems() == 2)
            {
                GetTextBoxAttr().GetLeftBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(0))));
                GetTextBoxAttr().GetLeftBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(1))));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), width, unit);
                GetTextBoxAttr().GetLeftBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetLeft().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
                GetTextBoxAttr().GetLeftBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(1))));
                GetTextBoxAttr().GetLeftBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(2))));
            }
        }
        else if (id == CSS_ATTR_BORDER_LEFT_STYLE)
        {
            GetTextBoxAttr().GetLeftBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(value)));
        }
        else if (id == CSS_ATTR_BORDER_LEFT_COLOR)
        {
            GetTextBoxAttr().GetLeftBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        }
        else if (id == CSS_ATTR_BORDER_LEFT_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);
            GetTextBoxAttr().GetLeftBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetLeft().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
        }
        else if (id == CSS_ATTR_BORDER_RIGHT)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                GetTextBoxAttr().GetRightBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
            }
            else if (spaceList.GetItems() == 2)
            {
                GetTextBoxAttr().GetRightBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(0))));
                GetTextBoxAttr().GetRightBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(1))));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), width, unit);
                GetTextBoxAttr().GetRightBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetRight().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
                GetTextBoxAttr().GetRightBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(spaceList.GetValue(1))));
                GetTextBoxAttr().GetRightBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(spaceList.GetValue(2))));
            }
        }
        else if (id == CSS_ATTR_BORDER_RIGHT_STYLE)
        {
            GetTextBoxAttr().GetRightBorder().SetStyle(GetWxBorderStyle(SwHtml::GetBorderStyle(value)));
        }
        else if (id == CSS_ATTR_BORDER_RIGHT_COLOR)
        {
            GetTextBoxAttr().GetRightBorder().SetColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        }
        else if (id == CSS_ATTR_BORDER_RIGHT_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);
            GetTextBoxAttr().GetRightBorder().SetWidth(GetWxBorder(width, unit, GetTextBoxAttr().GetBorder().GetRight().GetWidth().GetValue()), wxTEXT_ATTR_UNITS_TENTHS_MM);
        }
    }
}
