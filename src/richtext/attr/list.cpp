///////////////////////////////////////////////////////////////////
// Name:        list.cpp
// Purpose:     List attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/attr/richtextattr.h"

void SwRichTextAttr::SetList(swUI8 id, const char * value, bool html)
{
    swUI8 bullet;
    SwString style;
    int len;

    if (html)
    {
        SetBulletNumber(1);
        SetListStart(1);
        if (id == HTML_ATTRIBUTE_START)
        {
            if (isdigit(value[0]))
            {
                SetBulletNumber(atoi(value));
                SetListStart(atoi(value));
            }
            else if (isupper(value[0]))
            {
                SetBulletNumber('Z' - value[0]);
                SetListStart('Z' - value[0]);
            }
            else if (islower(value[0]))
            {
                SetBulletNumber('z' - value[0]);
                SetListStart('z' - value[0]);
            }
        }
        else if (id == HTML_ATTRIBUTE_TYPE)
        {
            m_listStyle = SwHtml::GetListStyle(value);

            if (m_listStyle == ATTRIBUTE_UNSPECIFIED)
                m_listStyle = LIST_STYLE_TYPE_DECIMAL;

            if (m_allowList)
                SetBulletStyle(GetWxListStyle(value, bullet));
        }
    }
    else
    {
        if (id == CSS_ATTR_LIST_STYLE)
        {
            style = value;
            len = style.Strlen();
            for (int pos = 0; pos < len; pos ++)
            {
                if (style.GetAt(pos) == ' ')
                {
                    style.SetAt(pos, '\0');
                    break;
                }
            }

            m_listStyle = SwHtml::GetListStyle(style);

            if (m_allowList)
                SetBulletStyle(GetWxListStyle(style, bullet));
        }
        else if (id == CSS_ATTR_LIST_STYLE_TYPE)
        {
            m_listStyle = SwHtml::GetListStyle(value);
            if (m_listStyle == ATTRIBUTE_UNSPECIFIED)
                m_listStyle = LIST_STYLE_TYPE_DECIMAL;

            if (m_allowList)
                SetBulletStyle(GetWxListStyle(value, bullet));
        }
    }
}
