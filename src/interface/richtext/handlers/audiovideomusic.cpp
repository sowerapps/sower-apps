///////////////////////////////////////////////////////////////////
// Name:        audiovideomusic.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"
#include "../../../../include/appi/appifa.h"

void SwRichTextInterface::WriteAVLink(const char * data)
{
    wxRichTextAttr attr(m_rich->GetDefaultStyle());
    attr.SetURL(data);
    m_rich->WriteImage(SwApplicationInterface::GetImage("SID_PLAY"), wxBITMAP_TYPE_PNG, attr);
}

swUI32 SwRichTextInterface::Onaudio(swUI32 node)
{
    swUI32 sourceNode;
    SwString buffer, path;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        sourceNode = FindWithInElement(node, 0, THML_SOURCE, NODE_TYPE_UNPAIRED_TAG);

        if (sourceNode != NODE_ID_INVALID && GetNamedValueFromNode(sourceNode, "src", buffer))
        {
            if (m_isModule)
            {
                char s[100];
                path = buffer;
                sprintf(s, "%u", m_moduleId);
                path += " identifier:";
                path += s;
            }
            else
            {
                SwGetPathFromRelative(GetBasePath(), buffer, path);
            }

            path.Insert(0, "audio:");
            WriteAVLink(path);
        }
    }

    return node;
}

swUI32 SwRichTextInterface::Onvideo(swUI32 node)
{
    swUI32 sourceNode;
    SwString buffer, path;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        sourceNode = FindWithInElement(node, 0, THML_CAPTION, NODE_TYPE_UNPAIRED_TAG);

        if (sourceNode != NODE_ID_INVALID && GetNamedValueFromNode(sourceNode, "src", buffer))
        {
            if (m_isModule)
            {
                SwGetFileName(buffer, path);
                char s[100];
                sprintf(s, "%u", m_moduleId);
                path += " identifier:";
                path += s;
            }
            else
            {
                SwGetPathFromRelative(GetBasePath(), buffer, path);
            }

            path.Insert(0, "video:");
            WriteAVLink(path);
        }
    }

    return node;
}

swUI32 SwRichTextInterface::Onmusic(swUI32 node)
{
    SwString buffer, path;

    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG || GetNodeType(node) == NODE_TYPE_UNPAIRED_TAG)
    {
        if (GetNamedValueFromNode(node, "href", buffer))
        {
            if (m_isModule)
            {
                SwGetFileName(buffer, path);
                char s[100];
                sprintf(s, "%u", m_moduleId);
                path += " identifier:";
                path += s;
            }
            else
            {
                SwGetPathFromRelative(GetBasePath(), buffer, path);
            }

            path.Insert(0, "video:");
            WriteAVLink(path);
        }
    }

    return node;
}
