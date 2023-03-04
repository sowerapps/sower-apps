///////////////////////////////////////////////////////////////////
// Name:        body.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"
#include "../../../../include/appi/appifa.h"
#include "../../../../include/html/html_css.h"

swUI32 SwRichTextInterface::Onautodefbody(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_richAttr.Reset();
        m_basefontsize = SwApplicationInterface::GetAutoDefFontSize();
        GetBlockStyle(node);
        m_richAttr.SetFontPointSize(m_basefontsize);
        BeginBlockStyle(node, false);
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}

swUI32 SwRichTextInterface::Onbody(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        m_richAttr.Reset();
        m_basefontsize = SwApplicationInterface::GetReaderFontSize();
        GetBlockStyle(node);
        m_richAttr.SetFontPointSize(m_basefontsize);
        BeginBlockStyle(node, false);
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        EndBlockStyle(node);
    }

    return node;
}
