///////////////////////////////////////////////////////////////////
// Name:        margin.cpp
// Purpose:     Margin attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetMargins(swUI8 id, const char * value, bool html)
{
    swUI8 unit;
    float margin;
    CssSpacedList   spaceList;

    if (html)
    {
        return;
    }
    else
    {
        if (id == CSS_ATTR_MARGIN && m_allowMargins)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), margin, unit);
                GetTextBoxAttr().GetTopMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetTopMargin().GetValue()));
                GetTextBoxAttr().GetBottomMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetBottomMargin().GetValue()));
                GetTextBoxAttr().GetLeftMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetLeftMargin().GetValue()));
                GetTextBoxAttr().GetRightMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetRightMargin().GetValue()));
            }
            else if (spaceList.GetItems() == 2)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), margin, unit);
                GetTextBoxAttr().GetTopMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetTopMargin().GetValue()));
                GetTextBoxAttr().GetBottomMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetBottomMargin().GetValue()));

                SwHtml::GetFloatData(spaceList.GetValue(1), margin, unit);
                GetTextBoxAttr().GetLeftMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetLeftMargin().GetValue()));
                GetTextBoxAttr().GetRightMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetRightMargin().GetValue()));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), margin, unit);
                GetTextBoxAttr().GetTopMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetTopMargin().GetValue()));

                SwHtml::GetFloatData(spaceList.GetValue(1), margin, unit);
                GetTextBoxAttr().GetLeftMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetLeftMargin().GetValue()));
                GetTextBoxAttr().GetRightMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetRightMargin().GetValue()));

                SwHtml::GetFloatData(spaceList.GetValue(2), margin, unit);
                GetTextBoxAttr().GetBottomMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetBottomMargin().GetValue()));
            }
            else if (spaceList.GetItems() == 4)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), margin, unit);
                GetTextBoxAttr().GetTopMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetTopMargin().GetValue()));

                SwHtml::GetFloatData(spaceList.GetValue(1), margin, unit);
                GetTextBoxAttr().GetLeftMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetLeftMargin().GetValue()));

                SwHtml::GetFloatData(spaceList.GetValue(2), margin, unit);
                GetTextBoxAttr().GetRightMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetRightMargin().GetValue()));

                SwHtml::GetFloatData(spaceList.GetValue(3), margin, unit);
                GetTextBoxAttr().GetBottomMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetBottomMargin().GetValue()));
            }
        }
        else if (id == CSS_ATTR_MARGIN_TOP && m_allowMargins)
        {
            SwHtml::GetFloatData(value, margin, unit);
            GetTextBoxAttr().GetTopMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetTopMargin().GetValue()));
        }
        else if (id == CSS_ATTR_MARGIN_BOTTOM && m_allowMargins)
        {
            SwHtml::GetFloatData(value, margin, unit);
            GetTextBoxAttr().GetBottomMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetBottomMargin().GetValue()));
        }
        else if (id == CSS_ATTR_MARGIN_LEFT && m_allowMargins)
        {
            SwHtml::GetFloatData(value, margin, unit);
            GetTextBoxAttr().GetLeftMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetLeftMargin().GetValue()));
        }
        else if (id == CSS_ATTR_MARGIN_RIGHT && m_allowMargins)
        {
            SwHtml::GetFloatData(value, margin, unit);
            GetTextBoxAttr().GetRightMargin().SetValue(GetWxMargin(margin, unit, GetTextBoxAttr().GetRightMargin().GetValue()));
        }
    }
}
