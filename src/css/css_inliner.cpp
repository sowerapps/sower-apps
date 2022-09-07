///////////////////////////////////////////////////////////////////
// Name:        css_inliner.cpp
// Purpose:     Inline CSS.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/css/css_inliner.h"

SwCssInliner::SwCssInliner()
{
    SetExtraBytes(32767);
    m_despace = true;
}

SwCssInliner::~SwCssInliner()
{
}

void SwCssInliner::Reset()
{
    SwThMLParser::Reset();
    m_skipNode = NODE_ID_INVALID;
    m_attrList.Reset();
    m_class.Reset();
    m_style.Reset();
    m_nodeBuffer.Reset();
    m_cssrules = NULL;
}

void SwCssInliner::ResetFull()
{
    SwThMLParser::Reset();
    m_skipNode = NODE_ID_INVALID;
    m_styleList.Reset();
    m_attrList.Reset();
    m_cssFile.Reset();
    m_class.Reset();
    m_style.Reset();
    m_nodeBuffer.Reset();
    m_cssrules = NULL;
}

bool SwCssInliner::OpenFile(const char * path, bool thml)
{
    if (!path)
        return false;

    Reset();

    if (!thml)
        m_markupType = MARKUP_HTML;
    else
        m_markupType = MARKUP_THML;

    return SwThMLParser::OpenFile(path, MODE_MEMORY, false);
}

bool SwCssInliner::ProcessFile()
{
    swUI32 startnode = 0;

    LoadInternalCss();

    startnode = LocateDocumentBody();

    if (startnode == NODE_ID_INVALID)
        return false;

    if (!Process(startnode))
        return false;

    RemoveStyleSheets();

    return true;
}

bool SwCssInliner::ProcessBuffer(const char * buffer)
{
    Reset();

    if (!Load(buffer, strlen(buffer)))
        return false;

    return Process(0);
}

bool SwCssInliner::Process(swUI32 startnode)
{
    bool hasClass;
    m_skipNode = NODE_ID_INVALID;
    SwString tag;
    SetRange(m_parserNodePos);

    for (swUI32 node = startnode + 1; node < GetParserNodes(); node ++)
    {
        hasClass = false;
        m_node = node;

        if (GetNodeType(node) != NODE_TYPE_BEGIN_TAG && GetNodeType(node) != NODE_TYPE_UNPAIRED_TAG)
            continue;
        else if (m_skipNode == node)
        {
            // New inserted tag from
            // ProcessScope(-);
            m_skipNode = NODE_ID_INVALID;
            continue;
        }

        if (!UpdateUI(node))
            return false;

        GetNodeData(node, tag);
        m_attrList.Reset();

        m_class.Reset();
        hasClass = GetNamedValue("class", tag, m_class);

        CollectInlineStyles(tag);
        CollectInternalStyles(node);

        if (m_markupType == MARKUP_THML)
            CollectThMLStyles(node);

        if (m_cssFile.HasFile())
            CollectExternalStyles(node);

        if (hasClass)
            DeleteNamedValue(tag, "class", m_despace);

        if (m_attrList.GetItems())
        {
            m_attrList.CreateStyleString(m_style);
            InsertAttribute(tag, m_style, m_despace);
        }

        if (hasClass || m_attrList.GetItems())
            ReplaceNode(node, tag, false);

        ProcessScope(node);
    }

    return true;
}

bool SwCssInliner::ProcessNode(swUI32 node, SwString & tag)
{
    bool hasClass = false;

    m_attrList.Reset();
    m_class.Reset();

    GetNodeData(node, tag);
    hasClass = GetNamedValue("class", tag, m_class);

    CollectInlineStyles(tag);
    CollectInternalStyles(node);

    if (m_markupType == MARKUP_THML)
        CollectThMLStyles(node);

    if (m_cssFile.HasFile())
        CollectExternalStyles(node);

    if (hasClass)
        DeleteNamedValue(tag, "class", m_despace);

    if (m_attrList.GetItems())
    {
        m_attrList.CreateStyleString(m_style);
        InsertAttribute(tag, m_style, m_despace);
        return true;
    }

    return false;
}

void SwCssInliner::LoadInternalCss()
{
    m_styleList.Reset();
    m_styleList.ReadStyleData(this);
}

swUI32 SwCssInliner::LocateDocumentBody()
{
    if (m_markupType == MARKUP_THML)
        return FindElement(0, THML_THML_BODY, NODE_TYPE_BEGIN_TAG);
    else
        return FindElement(0, THML_BODY, NODE_TYPE_BEGIN_TAG);

    return NODE_ID_INVALID;
}

void SwCssInliner::CollectInlineStyles(swUI32 node)
{
    if (GetNamedValueFromNode(node, "style", m_style))
    {
        m_attrList.ParseStyle(m_style, 10000);
    }
}

void SwCssInliner::CollectInlineStyles(SwString & source)
{
    if (GetNamedValue("style", source, m_style))
    {
        m_attrList.ParseStyle(m_style, 10000);
        DeleteNamedValue(source, "style", m_despace);
    }
}

void SwCssInliner::CollectInternalStyles(swUI32 node)
{
    SwString element;

    if (!GetElementStrFromNode(node, element))
        return;

    CssFile * cf;

    if (m_cssrules)
        cf = m_cssrules;
    else
        cf = &m_styleList;

    swUI32 idx = 0;

    for (;;)
    {
        idx = cf->Find(*this, node, m_class, idx);
        if (idx != NODE_ID_INVALID && !cf->GetNode(idx)->selector->HasPseudoClass())
        {
            m_attrList.ParseStyle(cf->GetNode(idx)->style->GetArray(), cf->GetNode(idx)->selector->GetSpecificity() + 1000);
        }

        if (idx == NODE_ID_INVALID)
            break;

        idx ++;
    }
}

void SwCssInliner::CollectExternalStyles(swUI32 node)
{
    SwString element;

    if (!GetElementStrFromNode(node, element))
        return;

    swUI32 idx = 0;

    for (;;)
    {
        idx = m_cssFile.Find(*this, node, m_class, idx);
        if (idx != NODE_ID_INVALID && !m_cssFile.GetNode(idx)->selector->HasPseudoClass())
        {
            m_attrList.ParseStyle(m_cssFile.GetNode(idx)->style->GetArray(), m_styleList.GetNode(idx)->selector->GetSpecificity());
        }

        if (idx == NODE_ID_INVALID)
            break;

        idx ++;
    }
}

void SwCssInliner::CollectThMLStyles(swUI32 node)
{
    swUI32 idx = 0;
    SwString buffer;

    for (;;)
    {
        idx = SwThMLCss::Find(*this, node, m_class, idx);

        if (idx != NODE_ID_INVALID && SwThMLCss::GetScope(idx) == 0)
        {
            SwThMLCss::GetStyle(idx, m_attrList);
        }

        if (idx == NODE_ID_INVALID)
            break;

        idx ++;
    }
}

void SwCssInliner::CleanTag(swUI32 node)
{
    DeleteNamedValueFromNode(node, "class");
    DeleteNamedValueFromNode(node, "style");
}

void SwCssInliner::ProcessScope(swUI32 node)
{
    swUI32 idx = 0;
    swUI32 scope = NODE_ID_INVALID;
    swUI32 textNode;

    SwString element;
    SwString scopeStr;

    if (!GetElementStrFromNode(node, element))
        return;

    CssFile * cf;

    if (m_cssrules)
        cf = m_cssrules;
    else
        cf = &m_styleList;

    for (;;)
    {
        idx = cf->Find(*this, node, m_class, idx);
        if (idx != NODE_ID_INVALID && cf->GetNode(idx)->selector->HasPseudoClass())
        {
            scope = cf->GetNode(idx)->selector->FindPseudoClass();
            scopeStr = cf->GetNode(idx)->selector->GetNode(scope)->item;
            m_attrList.ParseStyle(cf->GetNode(idx)->style->GetArray());
            m_attrList.CreateStyleString(m_style);

            break;
        }

        if (idx == NODE_ID_INVALID)
            break;

        idx ++;
    }

    if (scope == NODE_ID_INVALID && m_cssFile.HasFile())
    {
        for (;;)
        {
            idx = m_cssFile.Find(*this, node, m_class, idx);
            if (idx != NODE_ID_INVALID && m_cssFile.GetNode(idx)->selector->HasPseudoClass())
            {
                scope = m_cssFile.GetNode(idx)->selector->FindPseudoClass();
                scopeStr = m_cssFile.GetNode(idx)->selector->GetNode(scope)->item;
                m_attrList.ParseStyle(m_cssFile.GetNode(idx)->style->GetArray());
                m_attrList.CreateStyleString(m_style);

                break;
            }

            if (idx == NODE_ID_INVALID)
                break;

            idx ++;
        }
    }

    if (m_markupType == MARKUP_THML && scope == NODE_ID_INVALID)
    {
        idx = 0;

        for (;;)
        {
            idx = SwThMLCss::Find(*this, node, m_class, idx);
            if (idx != NODE_ID_INVALID && SwThMLCss::GetScope(idx) != 0)
            {
                scope = SwThMLCss::GetScope(idx);
                SwThMLCss::GetStyle(idx, m_attrList);
                m_attrList.CreateStyleString(m_style);

                break;
            }

            if (idx == NODE_ID_INVALID)
                break;

            idx ++;
        }
    }

    if (scope && scope != NODE_ID_INVALID)
    {
        swUI32 space = 0;
        char *p;

        textNode = FindWithInElement(node, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

        if (textNode != NODE_ID_INVALID)
        {
            GetNodeData(textNode, m_nodeBuffer);

            if (scope == CSS_SCOPE_FIRST_LETTER)
            {
                space = SwString::GetUtf8CharByteLength((unsigned char) m_nodeBuffer.GetAt(0));
            }
            else if (scope == CSS_SCOPE_FIRST_WORD)
            {
                p = strchr(m_nodeBuffer, ' ');

                if (!p)
                {
                    space = 1;
                }
                else
                    space = p - m_nodeBuffer.GetArray();
            }

            if (space && space < m_nodeBuffer.Strlen())
            {
                m_nodeBuffer.Insert(space, "</span>");
                m_nodeBuffer.Insert(0, ">");
                m_nodeBuffer.Insert(0, m_style);
                m_nodeBuffer.Insert(0, "<span ");
                ReplaceNode(textNode, m_nodeBuffer, true);
                m_skipNode = textNode;
            }
        }
    }
}

void SwCssInliner::RemoveStyleSheets()
{
    swUI32 node = NODE_ID_INVALID, endNode;

    for (;;)
    {
        node = FindElement(0, THML_STYLE, NODE_TYPE_BEGIN_TAG);

        if (node == NODE_ID_INVALID)
            break;

        endNode = GetNodeMate(node);

        if (endNode != NODE_ID_INVALID)
            DeleteNodes(node, endNode, true);
    }

    for (;;)
    {
        node = FindElement(0, THML_XML_STYLESHEET, NODE_TYPE_UNPAIRED_TAG);

        if (node == NODE_ID_INVALID)
            break;

        DeleteNode(node, true);
    }
}

void SwCssInliner::SetDespace(bool despace)
{
    m_despace = despace;
}
