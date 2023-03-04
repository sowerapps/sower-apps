///////////////////////////////////////////////////////////////////
// Name:        float.cpp
// Purpose:     Float attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetFloat(swUI8 id, const char * value, bool html)
{
    if (html)
    {
        return;
    }
    else
    {
        if (id == CSS_ATTR_FLOAT)
        {
            GetTextBoxAttr().SetFloatMode(GetWxFloatMode(SwHtml::GetFloatDirection(value)));
        }
    }
}
