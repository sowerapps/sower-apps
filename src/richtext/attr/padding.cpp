///////////////////////////////////////////////////////////////////
// Name:        padding.cpp
// Purpose:     Padding attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetPadding(swUI8 id, const char * value, bool html)
{
    swUI8 unit;
    float padding;
    CssSpacedList   spaceList;

    if (html && m_allowPadding)
    {
        SwHtml::GetFloatData(value, padding, unit);
        GetTextBoxAttr().GetTopPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetTopPadding().GetValueMM()));
        GetTextBoxAttr().GetBottomPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetBottomPadding().GetValueMM()));
        GetTextBoxAttr().GetLeftPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetLeftPadding().GetValueMM()));
        GetTextBoxAttr().GetRightPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetRightPadding().GetValueMM()));
    }
    else
    {
        if (id == CSS_ATTR_PADDING && m_allowPadding)
        {
            spaceList.ParseValue(value);
            if (spaceList.GetItems() == 1)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), padding, unit);
                GetTextBoxAttr().GetTopPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetTopPadding().GetValueMM()));
                GetTextBoxAttr().GetBottomPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetBottomPadding().GetValueMM()));
                GetTextBoxAttr().GetLeftPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetLeftPadding().GetValueMM()));
                GetTextBoxAttr().GetRightPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetRightPadding().GetValueMM()));
            }
            else if (spaceList.GetItems() == 2)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), padding, unit);
                GetTextBoxAttr().GetTopPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetTopPadding().GetValueMM()));
                GetTextBoxAttr().GetBottomPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetBottomPadding().GetValueMM()));

                SwHtml::GetFloatData(spaceList.GetValue(1), padding, unit);
                GetTextBoxAttr().GetLeftPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetLeftPadding().GetValueMM()));
                GetTextBoxAttr().GetRightPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetRightPadding().GetValueMM()));
            }
            else if (spaceList.GetItems() == 3)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), padding, unit);
                GetTextBoxAttr().GetTopPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetTopPadding().GetValueMM()));

                SwHtml::GetFloatData(spaceList.GetValue(1), padding, unit);
                GetTextBoxAttr().GetLeftPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetLeftPadding().GetValueMM()));
                GetTextBoxAttr().GetRightPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetRightPadding().GetValueMM()));

                SwHtml::GetFloatData(spaceList.GetValue(2), padding, unit);
                GetTextBoxAttr().GetBottomPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetBottomPadding().GetValueMM()));
            }
            else if (spaceList.GetItems() == 4)
            {
                SwHtml::GetFloatData(spaceList.GetValue(0), padding, unit);
                GetTextBoxAttr().GetTopPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetTopPadding().GetValueMM()));

                SwHtml::GetFloatData(spaceList.GetValue(1), padding, unit);
                GetTextBoxAttr().GetLeftPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetLeftPadding().GetValueMM()));

                SwHtml::GetFloatData(spaceList.GetValue(2), padding, unit);
                GetTextBoxAttr().GetRightPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetRightPadding().GetValueMM()));

                SwHtml::GetFloatData(spaceList.GetValue(3), padding, unit);
                GetTextBoxAttr().GetBottomPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetBottomPadding().GetValueMM()));
            }
        }
        else if (id == CSS_ATTR_PADDING_TOP && m_allowPadding)
        {
            SwHtml::GetFloatData(value, padding, unit);
            GetTextBoxAttr().GetTopPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetTopPadding().GetValueMM()));
        }
        else if (id == CSS_ATTR_PADDING_BOTTOM && m_allowPadding)
        {
            SwHtml::GetFloatData(value, padding, unit);
            GetTextBoxAttr().GetBottomPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetBottomPadding().GetValueMM()));
        }
        else if (id == CSS_ATTR_PADDING_LEFT && m_allowPadding)
        {
            SwHtml::GetFloatData(value, padding, unit);
            GetTextBoxAttr().GetLeftPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetLeftPadding().GetValueMM()));
        }
        else if (id == CSS_ATTR_PADDING_RIGHT && m_allowPadding)
        {
            SwHtml::GetFloatData(value, padding, unit);
            GetTextBoxAttr().GetRightPadding().SetValueMM(GetWxPadding(padding, unit, GetTextBoxAttr().GetRightPadding().GetValueMM()));
        }
    }
}
