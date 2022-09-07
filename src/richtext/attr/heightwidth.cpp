///////////////////////////////////////////////////////////////////
// Name:        heightwidth.cpp
// Purpose:     Height, and width attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetHeight(swUI8 id, const char * value, bool html)
{
    float height;
    swUI8 unit;
    wxTextAttrUnits  wxunit;

    if (html)
    {
        if (id == HTML_ATTRIBUTE_HEIGHT)
        {
            SwHtml::GetFloatData(value, height, unit);

            if (unit == UNIT_PERCENT)
                wxunit = wxTEXT_ATTR_UNITS_PERCENTAGE;
            else
                wxunit = wxTEXT_ATTR_UNITS_TENTHS_MM;

            GetTextBoxAttr().GetHeight().SetValue(CssUnits::GetValueAsMM10(height, unit), wxunit);
        }
    }
    else
    {
        if (id == CSS_ATTR_HEIGHT)
        {
            SwHtml::GetFloatData(value, height, unit);

            if (unit == UNIT_PERCENT)
                wxunit = wxTEXT_ATTR_UNITS_PERCENTAGE;
            else
                wxunit = wxTEXT_ATTR_UNITS_TENTHS_MM;

            GetTextBoxAttr().GetHeight().SetValue(CssUnits::GetValueAsMM10(height, unit), wxunit);
        }
    }
}

void SwRichTextAttr::SetWidth(swUI8 id, const char * value, bool html)
{
    float width;
    swUI8 unit;
    wxTextAttrUnits  wxunit;

    if (html)
    {
        if (id == HTML_ATTRIBUTE_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);

            if (unit == UNIT_PERCENT)
                wxunit = wxTEXT_ATTR_UNITS_PERCENTAGE;
            else
                wxunit = wxTEXT_ATTR_UNITS_TENTHS_MM;

            GetTextBoxAttr().GetWidth().SetValue(CssUnits::GetValueAsMM10(width, unit), wxunit);
        }
    }
    else
    {
        if (id == CSS_ATTR_WIDTH)
        {
            SwHtml::GetFloatData(value, width, unit);

            if (unit == UNIT_PERCENT)
                wxunit = wxTEXT_ATTR_UNITS_PERCENTAGE;
            else
                wxunit = wxTEXT_ATTR_UNITS_TENTHS_MM;

            GetTextBoxAttr().GetWidth().SetValue(CssUnits::GetValueAsMM10(width, unit), wxunit);
        }
    }
}
