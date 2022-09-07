///////////////////////////////////////////////////////////////////
// Name:        interface.cpp
// Purpose:     SwViewInterface - base class for interfaces to views for
//              different types of content. SowerBase allows an
//              additional attribute (type) for ThML div elements
//              to specify the type of view needed to display the
//              content of the div. Views are created as needed,
//              and the interface for the content/view type writes
//              writes/transfers content to the view.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/interface/interface.h"
#include "../../include/appi/appifa.h"
#include "../../include/thml/thml_css.h"

SwViewInterface::SwViewInterface()
{
    Init();
}

SwViewInterface::~SwViewInterface()
{
}

void SwViewInterface::Init()
{
    SetIsThML(true);
    m_isModule = false;
    m_moduleId = NODE_ID_INVALID_16;
    m_isModule = false;
    m_basefontsize = SwApplicationInterface::GetReaderFontSize();
}

void SwViewInterface::Reset()
{
    SwCssInliner::ResetFull();
    m_title.Reset();
    m_isModule = false;
    m_moduleId = NODE_ID_INVALID_16;
    m_basefontsize = SwApplicationInterface::GetReaderFontSize();
    OnReset();
}

void SwViewInterface::Run(bool inline_)
{
    swUI16 id;
    m_skipNode = NODE_ID_INVALID;
    OnPreRun();
    for (swUI32 node = 0; node < GetParserNodes(); node ++)
    {
        m_attrList.Reset();
        m_style.Reset();
        m_class.Reset();

        id = GetNodeElementIdentifier(node);

        if (id >= INT_UNKNOWN)
        {
            if (id == INT_UNKNOWN)
            {
                node = Onunknown(node);
            }
            else if (id == INT_BINARY)
            {
                node = Onbinary(node);
            }
            else if (id == INT_MODULE)
            {
                node = Onmodule(node);
            }
            else if (id == INT_TEXT_RUN)
            {
                node = Ontext(node);
            }
        }
        else
        {
            if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
            {
                GetNodeData(node, m_style);
                m_attrList.ParseTag(m_style);

                if (inline_)
                {
                    if (m_skipNode != node)
                    {
                        GetNamedValue("class", m_style, m_class);
                        CollectInternalStyles(node);
                        if (m_markupType == MARKUP_THML)
                            CollectThMLStyles(node);
                    }
                    else
                        m_skipNode = NODE_ID_INVALID;
                }
                // 'param3 is used as flag for whether the
                // style was changed by the begin tag. Tag Mate
                // param3 is set to false before further processing.
                m_parserNodeData[GetNodeMate(node)].param3 = false;
            }
            else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
            {
                GetNodeData(node, m_style);
                m_attrList.ParseTag(m_style);

                if (inline_)
                {
                    GetNamedValue("class", m_style, m_class);
                    CollectInternalStyles(node);
                    if (m_markupType == MARKUP_THML)
                        CollectThMLStyles(node);
                }
            }

            if (id < N_THML_ELEMENTS)
                node = Handle(id, node);
            else
                node = Onunknown(node);
        }
    }

    OnCompletion();
}

swUI32 SwViewInterface::Onbinary(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
        return GetNodeMate(node);

    return node;
}

swUI32 SwViewInterface::Onmodule(swUI32 node)
{
    SwString id;

    if (GetNamedValueFromNode(node, "id", id))
    {
        m_moduleId = id.Atoi();

        if (GetNamedValueFromNode(node, "ismodule", id))
        {
            m_isModule = SwString::BoolFromString(id);
        }
        else
        {
            m_isModule = true;
        }
    }

    return node;
}

swUI32 SwViewInterface::Ontext(swUI32 node)
{
    return node;
}

swUI32 SwViewInterface::Onunknown(swUI32 node)
{
    return node;
}

swUI32 SwViewInterface::Onwhitespace(swUI32 node)
{
    return node;
}

void SwViewInterface::Inline()
{
    bool hasClass;
    m_skipNode = NODE_ID_INVALID;
    SwString newStyle;

    for (swUI32 node = 0; node < GetParserNodes(); node ++)
    {
        m_attrList.Reset();
        m_style.Reset();
        m_class.Reset();
        hasClass = false;

        if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
        {
            GetNodeData(node, m_style);
            m_attrList.ParseTag(m_style);

            if (m_skipNode != node)
            {
                hasClass = GetNamedValue("class", m_style, m_class);
                CollectInternalStyles(node);
                if (m_markupType == MARKUP_THML)
                    CollectThMLStyles(node);
            }
            else
                m_skipNode = NODE_ID_INVALID;
        }
        else if (GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
        {
            GetNodeData(node, m_style);
            m_attrList.ParseTag(m_style);

            hasClass = GetNamedValue("class", m_style, m_class);
            CollectInternalStyles(node);
            if (m_markupType == MARKUP_THML)
                CollectThMLStyles(node);
        }

        if (hasClass)
            DeleteNamedValue(m_style, "class", true);

        if (m_attrList.GetItems())
        {
            m_attrList.CreateStyleString(newStyle);
            InsertAttribute(m_style, newStyle, true);
            ReplaceNode(node, m_style);
        }

        ProcessScope(node);
    }
}
