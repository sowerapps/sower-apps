///////////////////////////////////////////////////////////////////
// Name:        whitespace.cpp
// Purpose:     White space.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetWhiteSpace(swUI8 id, const char * value, bool html)
{
    if (html)
    {
        return;
    }
    else
    {
        if (id == CSS_ATTR_WHITE_SPACE)
        {   // Unused for now.
            //GetTextBoxAttr().SetWhitespaceMode(GetWxWhiteSpaceMode(SwHtml::GetWhiteSpace(value)));
        }
    }
}
