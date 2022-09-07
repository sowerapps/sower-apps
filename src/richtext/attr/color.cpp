///////////////////////////////////////////////////////////////////
// Name:        color.cpp
// Purpose:     Color attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"
#include "../../../include/html/html_color.h"

void SwRichTextAttr::SetColor(swUI8 id, const char * value, bool html)
{
    if (html)
    {
        if (id == HTML_ATTRIBUTE_COLOR)
            SetTextColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        else if (id == HTML_ATTRIBUTE_BGCOLOR)
            SetBackgroundColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
    }
    else
    {
        if (id == CSS_ATTR_COLOR)
            SetTextColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
        else if (id == CSS_ATTR_BACKGROUND_COLOR)
            SetBackgroundColour(SwHtmlColor::GetBGR(SwHtmlColor::GetColor(value)));
    }
}
