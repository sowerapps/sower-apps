///////////////////////////////////////////////////////////////////
// Name:        css_selector.cpp
// Purpose:     Parse, and identify attributes of CSS selectors.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/css/css_selector.h"
#include "../../include/html/html.h"

const char * GetNodeTypeStr(swUI8 type)
{
    if (type == CSS_TYPE_ATTRIBUTE)
        return "attribute";
    else if (type == CSS_TYPE_CLASS)
        return "class";
    else if (type == CSS_TYPE_ELEMENT)
        return "element";
    else if (type == CSS_TYPE_ID)
        return "id";
    else if (type == CSS_TYPE_VALUE)
        return "value";
    else if (type == CSS_TYPE_PSDCLASS)
        return "psdclass";
    else if (type == CSS_TYPE_SELECTOR)
        return "selector";
    else if (type == CSS_TYPE_SET)
        return "set";
    if (type == CSS_TYPE_STYLE)
        return "style";

    return "invalid";
}

const char * GetOpTypeStr(swUI8 type)
{
    if (type == CSS_OP_ASTK)
        return "*";
    else if (type == CSS_OP_GT)
        return ">";
    else if (type == CSS_OP_NONE)
        return "none";
    else if (type == CSS_OP_PLUS)
        return "+";
    else if (type == CSS_OP_SPACE)
        return "' '";
    else if (type == CSS_OP_TILDE)
        return "~";

    return "invalid";
}

CssSelector::CssSelector()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_specificity = 0;
}

CssSelector::~CssSelector()
{
    if (m_nodeData)
        free(m_nodeData);
}

bool CssSelector::IncreaseNodeArray()
{
    return SizeNodeArray(m_nodesAllocated + 12);
}

void CssSelector::Reset()
{
    m_nodePos = 0;
    m_selector = "";
}

bool CssSelector::SizeNodeArray(swUI32 nodes)
{
    if (!nodes && m_nodeData)
    {
        free(m_nodeData);
        m_nodeData = NULL;
        m_nodePos = 0;
        m_nodesAllocated = 0;
        return true;
    }

    if (nodes >= NODE_ID_INVALID)
        return false;

    SwSelectorNode * p = (SwSelectorNode *) realloc((void *) m_nodeData, nodes * sizeof(SwSelectorNode));

    if (p)
    {
        m_nodesAllocated += nodes;
        m_nodeData = p;
        return true;
    }

    return false;
}

bool CssSelector::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;
    else
    {
        m_nodeData[m_nodePos].item = NULL;
        m_nodeData[m_nodePos].type = CSS_TYPE_INVALID;
        m_nodeData[m_nodePos].opcode = CSS_OP_NONE;
    }

    return true;
}

bool CssSelector::ParseSelector(const char * selector)
{
    if (!selector)
        return false;

    bool inalpha = false;
    bool inquotes = false;
    m_selector.Copy(selector);

    swUI8 type = CSS_TYPE_SELECTOR;
    int pos = 0;
    int len = strlen(selector);

    m_nodePos = 0;

    while (pos < len)
    {
        if (m_selector[pos] == '\t' ||
            m_selector[pos] == '\r' ||
            m_selector[pos] == '\n')
        {
            inalpha = false;
            inquotes = false;
            m_selector[pos] = '\0';
        }
        else if (!inalpha && (isalnum(m_selector[pos]) || (type == CSS_TYPE_SELECTOR && m_selector[pos] == '*')))
        {
            if (!VerifyNode())
                return false;

            m_nodeData[m_nodePos].item = m_selector.GetArray() + pos;

            if (type == CSS_TYPE_SELECTOR)
            {
                m_nodeData[m_nodePos].type = CSS_TYPE_ELEMENT;

                if (m_selector[pos] == '*')
                    m_nodeData[m_nodePos].opcode = CSS_OP_ASTK;
            }
            else
                m_nodeData[m_nodePos].type = type;

            inalpha = true;
            inquotes = false;
            m_nodePos ++;
        }
        else if (m_selector[pos] == '\"')
        {
            if (!inquotes)
                inquotes = true;
            else
                inquotes = false;
        }
        else if (m_selector[pos] == ',')
        {
            // Don't change type here.
            inalpha = false;
            inquotes = false;
            m_selector[pos] = '\0';

            if (m_selector[pos + 1] == ' ')
                pos ++;
        }
        else if (isspace(m_selector[pos]))
        {
            if (inalpha && type == CSS_TYPE_ELEMENT &&
                m_selector[pos] == ' ')
            {
                m_nodeData[m_nodePos - 1].opcode = CSS_OP_SPACE;
            }
            else if (!inquotes && m_selector[pos] == ' ')
            {
                inalpha = false;
                m_selector[pos] = '\0';
            }
        }
        else if (m_selector[pos] == '>')
        {
            if (inalpha && type == CSS_TYPE_ELEMENT)
            {
                m_nodeData[m_nodePos - 1].opcode = CSS_OP_GT;
                inalpha = false;
                inquotes = false;
                m_selector[pos] = '\0';
            }
        }
        else if (m_selector[pos] == '~')
        {
            if (inalpha && type == CSS_TYPE_ELEMENT)
            {
                m_nodeData[m_nodePos - 1].opcode = CSS_OP_TILDE;
                inalpha = false;
                inquotes = false;
                m_selector[pos] = '\0';
            }
        }
        else if (m_selector[pos] == '+')
        {
            if (inalpha && type == CSS_TYPE_ELEMENT)
            {
                m_nodeData[m_nodePos].opcode = CSS_OP_TILDE;
                inalpha = false;
                inquotes = false;
                m_selector[pos] = '\0';
            }
        }
        else if (m_selector[pos] == '.')
        {
            inalpha = false;
            inquotes = false;
            type = CSS_TYPE_CLASS;
            m_selector[pos] = '\0';
        }
        else if (m_selector[pos] == ':')
        {
            inalpha = false;
            inquotes = false;
            m_selector[pos] = '\0';

            if (m_selector[pos + 1] == ':')
                pos ++;

            type = CSS_TYPE_PSDCLASS;
        }
        else if (m_selector[pos] == '#')
        {
            inalpha = false;
            inquotes = false;

            if (type == CSS_TYPE_ID)
                type = CSS_TYPE_VALUE;
            else type = CSS_TYPE_ID;

            m_selector[pos] = '\0';
        }
        else if (m_selector[pos] == '[')
        {
            inalpha = false;
            inquotes = false;
            m_selector[pos] = '\0';
            type = CSS_TYPE_ATTRIBUTE;
        }
        else if (m_selector[pos] == ']')
        {
            inalpha = false;
            inquotes = false;
            m_selector[pos] = '\0';
        }
        else if (m_selector[pos] == '{')
        {
            return true;
        }

        pos ++;
    }

    return true;
}

SwSelectorNode * CssSelector::GetNode(swUI32 pos)
{
    if (pos >= m_nodePos)
        return NULL;

    return &m_nodeData[pos];
}

swUI8 CssSelector::GetNodeType(swUI32 pos)
{
    if (pos >= m_nodePos)
        return CSS_TYPE_INVALID;

    return m_nodeData[pos].type;
}

swUI32 CssSelector::GetLastNode()
{
    return m_nodePos - 1;
}

swUI32 CssSelector::GetNodePos()
{
    return m_nodePos;
}

swUI32 CssSelector::FindElement(const char * element)
{
    if (!element)
        return NODE_ID_INVALID;

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (GetNode(i)->type == CSS_TYPE_ELEMENT && GetNode(i)->opcode == CSS_OP_NONE && stricmp(element, GetNode(i)->item) == 0)
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 CssSelector::FindFirstElement()
{
    for (swUI32 i = 0; i < m_nodePos; i++)
    {
        if (m_nodeData[i].type == CSS_TYPE_ELEMENT &&
            m_nodeData[i].opcode == CSS_OP_NONE)
            return i;
    }

    return NODE_ID_INVALID;
}

bool CssSelector::HasElement(const char * element)
{
    if (!element)
        return false;

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (m_nodeData[i].type == CSS_TYPE_ELEMENT && GetNode(i)->opcode == CSS_OP_NONE && stricmp(element, GetNode(i)->item) == 0)
            return true;
    }

    return false;
}

bool CssSelector::HasNameValuePair()
{
    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (m_nodeData[i].type == CSS_TYPE_ID &&
            i + 1 < m_nodePos &&
            m_nodeData[i + 1].type == CSS_TYPE_VALUE)
            return true;
    }

    return false;
}

swUI32 CssSelector::FindNameValuePair(swUI32 start)
{
    for (swUI32 i = start; i < m_nodePos - 1; i ++)
    {
        if (m_nodeData[i].type == CSS_TYPE_ID &&
            i + 1 < m_nodePos &&
            m_nodeData[i + 1].type == CSS_TYPE_VALUE)
            return i;
    }

    return NODE_ID_INVALID;
}

bool CssSelector::HasNameValuePair(const char * name, const char * value)
{
    if (!name || !value)
        return false;

    swUI32 id = 0;

    for (;;)
    {
        id = FindNameValuePair(id);

        if (id == NODE_ID_INVALID)
            break;

        if (stricmp(GetNode(id)->item, name) == 0 &&
            strcmp(GetNode(id + 1)->item, value) == 0)
            return true;

        id ++;
    }

    return false;
}

bool CssSelector::HasControl(swUI32 pos)
{
    if (pos < 1)
        return false;

    if (GetNode(pos - 1)->type == CSS_TYPE_ELEMENT &&
        GetNode(pos - 1)->opcode != CSS_OP_NONE)
        return true;

    return false;
}

swUI32 CssSelector::FindFirstClass()
{
    for (swUI32 i = 0; i < m_nodePos; i++)
    {
        if (GetNode(i)->type == CSS_TYPE_CLASS)
            return i;
    }

    return NODE_ID_INVALID;
}

bool CssSelector::HasClass(const char * name)
{
    if (!name)
        return false;

    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (GetNode(i)->type == CSS_TYPE_CLASS && strcmp(name, GetNode(i)->item) == 0)
            return true;
    }

    return false;
}

swUI32 CssSelector::FindPseudoClass()
{
    for (swUI32 i = 0; i < m_nodePos; i++)
    {
        if (GetNode(i)->type == CSS_TYPE_PSDCLASS)
            return i;
    }

    return NODE_ID_INVALID;
}

bool CssSelector::HasPseudoClass()
{
    for (swUI32 i = 0; i < m_nodePos; i++)
    {
        if (GetNode(i)->type == CSS_TYPE_PSDCLASS)
            return true;
    }

    return false;
}

bool CssSelector::HasPseudoElement(swUI32 idx)
{
    if (idx < 1)
        return false;

    if (GetNode(idx - 1)->type == CSS_TYPE_ELEMENT && GetNode(idx - 1)->opcode != CSS_OP_NONE)
        return true;

    return false;
}

swUI32 CssSelector::GetElementCount()
{
    swUI32 elementCount = 0;

    for (swUI32 i = 0; i < m_nodePos; i++)
    {
        if (GetNode(i)->type == CSS_TYPE_ELEMENT &&
            GetNode(i)->opcode == CSS_OP_NONE)
            elementCount ++;
    }

    return elementCount;
}

swUI32 CssSelector::GetClassCount()
{
    swUI32 classCount = 0;

    for (swUI32 i = 0; i < m_nodePos; i++)
    {
        if (GetNode(i)->type == CSS_TYPE_CLASS)
            classCount ++;
    }

    return classCount;
}

swUI16 CssSelector::GetSpecificity()
{
    return m_specificity;
}

swUI16 CssSelector::CalculateSpecificity()
{
    swUI16 a = 0, b = 0, c = 0;

    for (swUI16 i = 0; i < GetNodePos(); i ++)
    {
        if (GetNode(i)->type == CSS_TYPE_ID)
        {
            a ++;
        }
        else if (GetNode(i)->type == CSS_TYPE_ATTRIBUTE)
        {
            b ++;
        }
        else if (GetNode(i)->type == CSS_TYPE_CLASS)
        {
            b++;
        }
        else if (GetNode(i)->type == CSS_TYPE_PSDCLASS)
        {
            if (!strstr(GetNode(i)->item, "not"))
                b++;
        }
        else if (GetNode(i)->type == CSS_TYPE_ELEMENT &&
                GetNode(i)->opcode == CSS_OP_NONE)
        {
            c ++;
        }
    }

    m_specificity = (a * 100);
    m_specificity += (b * 10);
    m_specificity += c;

    return m_specificity;
}

bool CssSelector::Add(char * item, swUI8 type, swUI8 opcode)
{
    if (!VerifyNode())
        return false;

    m_nodeData[m_nodePos].item = item;
    m_nodeData[m_nodePos].type = type;
    m_nodeData[m_nodePos].opcode = opcode;

    m_nodePos ++;

    return true;
}

