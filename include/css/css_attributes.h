///////////////////////////////////////////////////////////////////
// Name:        css_attributes.h
// Purpose:     CssAttributes - identify selector, class, attributes,
//              and scope in a style.
//              CssAttributeList - list of attributes in a style.
//              CssSpacedList - break space separated attributes
//              into individual strings.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CSS_ATTRIBUTES_H
#define CSS_ATTRIBUTES_H

#include "../../include/html/html.h"
#include "../array/uintarray.h"
#include "../array/stringarray.h"

class SOWERBASEEXP CssAttributes
{
public :
    CssAttributes();
    virtual ~CssAttributes();

    static swUI8 IdentifyAttribute(const char * source);
    static const char * GetAttributeString(swUI8 attribute);
    static bool HasStyle(const char * source);
    static swUI32 GetStyleData(const char * source, char * dest);
    static swUI32 GetClassName(const char * source, char * dest);
    static swUI32 GetElement(const char * source, char * dest);
    static swUI32 GetScope(const char * source, char * dest);
    static swUI32 GetSelector(const char * source, char * dest);
    static bool Test();
};

class SOWERBASEEXP CssAttributeList
{
public :
    CssAttributeList();
    virtual ~CssAttributeList();

    void ParseStyle(const char * style, swUI16 specificity = 100);
    void ParseTag(const char * tag);
    void Reset();

    bool Add(const char * attribute, const char * value, swUI16 specificity = 10)
    {
        if (!attribute || !value)
            return false;

        swUI32 id = Find(attribute);
        if (id == NODE_ID_INVALID)
        {
            m_attribute.Add(attribute);
            m_value.Add(value);
            m_specificity += specificity;
            return true;
        }
        else if (specificity > m_specificity.GetAt(id))
        {
            m_value.GetAt(id).Copy(value);
            m_specificity.SetAt(id, specificity);
            return true;
        }

        return false;
    }

    swUI32 Find(const char * attribute, swUI32 pos = 0)
    {
        if (!attribute)
            return NODE_ID_INVALID;

        for (swUI32 i = pos; i < m_attribute.GetCount() && i < m_value.GetCount(); i++)
        {
            if (strcmp(m_attribute.GetAt(i), attribute) == 0)
            {
                return i;
            }
        }

        return NODE_ID_INVALID;
    }

    swUI32 Find(const char * attribute, const char * value, swUI32 pos = 0)
    {
        if (!attribute || !value)
            return NODE_ID_INVALID;

        for (swUI32 i = pos; i < m_attribute.GetCount() && i < m_value.GetCount(); i++)
        {
            if (strcmp(m_attribute.GetAt(i), attribute) == 0 && strcmp(m_value.GetAt(i), value) == 0)
            {
                return i;
            }
        }

        return NODE_ID_INVALID;
    }

    swUI32 GetItems()
    {
        return m_attribute.GetCount();
    }

    void CreateStyleString(SwString & buffer);

    const char * GetAttribute(swUI32 pos)
    {
        if (pos >= GetItems())
            return "";

        return m_attribute.GetAt(pos);
    }

    const char * GetValue(swUI32 pos)
    {
        if (pos >= GetItems())
            return "";

        return m_value.GetAt(pos);
    }

    swUI16 GetSpecificity(swUI32 pos)
    {
        if (pos >= GetItems())
            return 0;

        return m_specificity.GetAt(pos);
    }

private:
    SwStringArray m_attribute;
    SwStringArray m_value;
    Swui16Array   m_specificity;
};

class SOWERBASEEXP CssSpacedList
{
public :
    CssSpacedList();
    virtual ~ CssSpacedList();

    void ParseValue(const char * value);
    void Reset();
    void Add(const char * value);
    swUI32 GetItems();
    const char * GetValue(swUI32 pos);

private:
    SwStringArray m_value;
};

#endif // CSS_ATTRIBUTES_H
