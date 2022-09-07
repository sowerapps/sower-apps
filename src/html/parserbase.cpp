///////////////////////////////////////////////////////////////////
// Name:        parserbase.cpp
// Purpose:     SwParserBase
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/parserbase.h"
#include "../../include/html/html.h"

SwParserBase::SwParserBase()
{
    m_nodeData = NULL;
    m_nodesAllocated = 0;
    m_nodePos = 0;
}

SwParserBase::~SwParserBase()
{
    if (m_nodeData)
        ReleaseDataBuffer();
}

void SwParserBase::Reset()
{
    FreeIdStrings();
    m_nodePos = 0;
}

bool SwParserBase::IncreaseDataBuffer()
{
    swUI32 pos = m_nodePos;

    if (m_nodesAllocated >= NODE_ID_INVALID - 33)
        return false;

    SD_NODE_DATA* p = (SD_NODE_DATA*) realloc((void *) m_nodeData, (m_nodesAllocated + 32) * sizeof(SD_NODE_DATA));

    if (p)
    {
        m_nodesAllocated += 32;
        m_nodeData = p;

        while (pos < m_nodesAllocated)
        {
            m_nodeData[pos].xmlId = NULL;
            m_nodeData[pos].passageId = NULL;
            m_nodeData[pos].position = 0;
            m_nodeData[pos].elementIdentifier = NODE_ID_INVALID_16;
            m_nodeData[pos].nodeMate = NODE_ID_INVALID;
            m_nodeData[pos].nodeParent = NODE_ID_INVALID;
            m_nodeData[pos].nodeFirstChild = NODE_ID_INVALID;
            m_nodeData[pos].nodeNextSibling = NODE_ID_INVALID;
            m_nodeData[pos].data = NULL;
            pos ++;
        }

        return true;
    }

    return false;
}

swUI32 SwParserBase::AssignDataNode()
{

    if (m_nodePos >= m_nodesAllocated && !IncreaseDataBuffer())
        return NODE_ID_INVALID;

    if (m_nodeData[m_nodePos].xmlId)
    {
        free(m_nodeData[m_nodePos].xmlId);
    }

    m_nodeData[m_nodePos].xmlId = NULL;
    m_nodeData[m_nodePos].passageId = NULL;
    m_nodeData[m_nodePos].position = 0;
    m_nodeData[m_nodePos].elementIdentifier = NODE_ID_INVALID_16;
    m_nodeData[m_nodePos].nodeMate = NODE_ID_INVALID;
    m_nodeData[m_nodePos].nodeParent = NODE_ID_INVALID;
    m_nodeData[m_nodePos].nodeFirstChild = NODE_ID_INVALID;
    m_nodeData[m_nodePos].nodeNextSibling = NODE_ID_INVALID;
    m_nodeData[m_nodePos].data = NULL;
    m_nodePos ++;

    return m_nodePos - 1;
}

void SwParserBase::ReleaseDataBuffer()
{
    swUI32 pos = 0;

    if (m_nodeData)
    {
        while(pos < m_nodePos)
        {
            if (m_nodeData[pos].xmlId != NULL)
            {
                free(m_nodeData[pos].xmlId);
            }

            pos ++;
        }

        free(m_nodeData);
    }

    m_nodeData = NULL;
    m_nodesAllocated = 0;
    m_nodePos = 0;
}

void SwParserBase::FreeIdStrings()
{
    swUI32 pos = 0;

    if (m_nodeData)
    {
        while(pos < m_nodePos)
        {
            if (m_nodeData[pos].xmlId != NULL)
            {
                free(m_nodeData[pos].xmlId);
                m_nodeData[pos].xmlId = NULL;
            }

            if (m_nodeData[pos].passageId != NULL)
            {
                free(m_nodeData[pos].passageId);
                m_nodeData[pos].passageId = NULL;
            }

            pos ++;
        }
    }
}

bool SwParserBase::MateElements()
{
    swUI32 indexPos = 0, indexPosB, numOpen;

    while (indexPos < m_nodePos)
    {
        if (m_nodeData[indexPos].nodeType == NODE_TYPE_BEGIN_TAG)
        {
            numOpen = 1;
            indexPosB = indexPos + 1;
            while (indexPosB < m_nodePos)
            {
                if (m_nodeData[indexPosB].elementIdentifier == m_nodeData[indexPos].elementIdentifier && m_nodeData[indexPosB].nodeType != NODE_TYPE_UNPAIRED_TAG)
                {
                    if (m_nodeData[indexPosB].nodeType == NODE_TYPE_BEGIN_TAG)
                        numOpen ++;
                    else if (m_nodeData[indexPosB].nodeType == NODE_TYPE_END_TAG && numOpen > 1)
                        numOpen --;
                    else if (m_nodeData[indexPosB].nodeType == NODE_TYPE_END_TAG && numOpen == 1)
                    {
                        m_nodeData[indexPos].nodeMate = indexPosB;
                        m_nodeData[indexPosB].nodeMate = indexPos;
                        break;
                    }
                }

                indexPosB ++;
            }
        }

        indexPos ++;
    }

    if (!FixMissingMates())
        return false;

    return true;
}

bool SwParserBase::FixMissingMates()
{
    swUI32 indexPos = 0;

    while (indexPos < m_nodePos)
    {
        if (m_nodeData[indexPos].nodeType == NODE_TYPE_BEGIN_TAG && m_nodeData[indexPos].nodeMate == NODE_ID_INVALID)
            m_nodeData[indexPos].nodeType = NODE_TYPE_UNPAIRED_TAG;

        indexPos ++;
    }

    return true;
}

bool SwParserBase::ParentElements()
{
    swUI32 indexPos = 0, indexPosB;

    while (indexPos < m_nodePos)
    {
        if (m_nodeData[indexPos].nodeType == NODE_TYPE_BEGIN_TAG && m_nodeData[indexPos].nodeMate != NODE_ID_INVALID)
        {
            indexPosB = indexPos + 1;
            m_nodeData[m_nodeData[indexPos].nodeMate].nodeParent = indexPos;

            while (indexPosB < m_nodeData[indexPos].nodeMate)
            {
                m_nodeData[indexPosB].nodeParent = indexPos;

                if (m_nodeData[indexPosB].nodeType == NODE_TYPE_BEGIN_TAG && m_nodeData[indexPosB].nodeMate != NODE_ID_INVALID)
                    indexPosB = m_nodeData[indexPosB].nodeMate;

                indexPosB ++;
            }
        }

        indexPos ++;
    }

    return true;
}

bool SwParserBase::SetFirstChild()
{
    swUI32 indexPos = 0;

    while (indexPos < m_nodePos)
    {
        if (m_nodeData[indexPos].nodeParent != NODE_ID_INVALID && m_nodeData[m_nodeData[indexPos].nodeParent].nodeFirstChild == NODE_ID_INVALID)
            m_nodeData[m_nodeData[indexPos].nodeParent].nodeFirstChild = indexPos;

        indexPos ++;
    }

    return true;
}

bool SwParserBase::SetNextSibling()
{
    swUI32 indexPos = 0, indexPosB;

    while (indexPos < m_nodePos)
    {
        indexPosB = indexPos + 1;
        while (indexPosB < m_nodePos)
        {
            if (m_nodeData[indexPos].nodeParent == m_nodeData[indexPosB].nodeParent)
            {
                m_nodeData[indexPos].nodeNextSibling = indexPosB;
                break;
            }

            indexPosB ++;
        }

        indexPos ++;
    }

    return true;
}

bool SwParserBase::AddTag(swUI16 identifier, swUI8 type, const char * xmlId, const char * passageId, swUI32 position, void * data)
{
    if (!xmlId || !passageId)
        return false;

    swUI32 node = AssignDataNode();

    if (node == NODE_ID_INVALID)
    {
        return false;
    }

    m_nodeData[node].elementIdentifier = identifier;
    m_nodeData[node].nodeType = type;
    m_nodeData[node].xmlId = strdup(xmlId);
    m_nodeData[node].passageId = strdup(passageId);
    m_nodeData[node].position = position;
    m_nodeData[node].nodeMate = NODE_ID_INVALID;
    m_nodeData[node].nodeParent = NODE_ID_INVALID;
    m_nodeData[node].nodeFirstChild = NODE_ID_INVALID;
    m_nodeData[node].nodeNextSibling = NODE_ID_INVALID;
    m_nodeData[node].data = data;

    return true;
}

swUI32 SwParserBase::FindNodeByXmlId(swUI32 nodeOrigin, const char * id)
{
    if (!id)
    {
        return NODE_ID_INVALID;
    }

    swUI32 pos = nodeOrigin;

    if (nodeOrigin >= m_nodePos)
        return NODE_ID_INVALID;

    while (pos < m_nodePos)
    {
        if (stricmp(id, m_nodeData[pos].xmlId) == 0)
        {
            return pos;
        }

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwParserBase::FindNodeByPassageId(swUI32 nodeOrigin, const char * id)
{
    if (!id)
    {
        return NODE_ID_INVALID;
    }

    swUI32 pos = nodeOrigin;

    if (nodeOrigin >= m_nodePos)
        return NODE_ID_INVALID;

    while (pos < m_nodePos)
    {
        if (stricmp(id, m_nodeData[pos].passageId) == 0)
        {
            return pos;
        }

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwParserBase::FindNodeByStreamPos(swUI32 streamPos)
{
    for (swUI32 i = 0; i < m_nodePos; i ++)
    {
        if (streamPos == GetNodeStreamPosition(i))
            return i;
    }

    return NODE_ID_INVALID;
}

const char * SwParserBase::GetXmlId(swUI32 node)
{
    if (node >= m_nodePos)
        return "";

    return m_nodeData[node].xmlId;
}

const char * SwParserBase::GetPassageId(swUI32 node)
{
    if (node >= m_nodePos)
        return "";

    return m_nodeData[node].passageId;
}

swUI16 SwParserBase::GetNodeElementIdentifier(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_16;

    return m_nodeData[node].elementIdentifier;
}

swUI8 SwParserBase::GetNodeType(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_TYPE_INVALID;

    return m_nodeData[node].nodeType;
}

swUI32 SwParserBase::GetNodeStreamPosition(swUI32 node)
{
    if (node >= m_nodePos)
        return 0;

    return m_nodeData[node].position;
}

SD_NODE_DATA * SwParserBase::GetNode(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

swUI32 SwParserBase::GetNodeMate(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID;

    return m_nodeData[node].nodeMate;
}

swUI32 SwParserBase::GetNodeParent(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID;

    return m_nodeData[node].nodeParent;
}

swUI32 SwParserBase::GetFirstChild(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID;

    return m_nodeData[node].nodeFirstChild;
}

swUI32 SwParserBase::GetNextSibling(swUI32 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID;

    return m_nodeData[node].nodeNextSibling;
}

swUI32 SwParserBase::GetNextSiblingOfType(swUI32 nodeOrigin, swUI8 elementId, swUI8 nodeType)
{
    swUI32 next = nodeOrigin;
    for(;;)
    {
        next = GetNextSibling(next);

        if (next == NODE_ID_INVALID)
            return NODE_ID_INVALID;

        if (nodeType == 0 && m_nodeData[next].elementIdentifier == elementId)
            return next;

        if (m_nodeData[next].elementIdentifier == elementId)
            return next;
    }
}

void * SwParserBase::GetNodeData(swUI32 node)
{
    if (node >= m_nodePos)
        return NULL;

    return m_nodeData[node].data;
}

swUI32 SwParserBase::FindElement(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType)
{
    swUI32 pos = nodeOrigin;

    while (pos < m_nodePos)
    {
        if (m_nodeData[pos].elementIdentifier == elementId && m_nodeData[pos].nodeType == nodeType)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

swUI32 SwParserBase::FindElementUpWard(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType)
{
    swUI32 pos = nodeOrigin;

    while (pos && pos < m_nodePos)
    {
        if (m_nodeData[pos].elementIdentifier == elementId && m_nodeData[pos].nodeType == nodeType)
            return pos;

        pos --;
    }

    return NODE_ID_INVALID;
}

swUI32 SwParserBase::FindWithInElement(swUI32 nodeParent, swUI32 nodeOffset, swUI16 elementId, swUI8 nodeType)
{
    swUI32 pos = nodeParent;
    swUI32 endPos = GetNodeMate(nodeParent);

    if (endPos == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    pos += nodeOffset;

    while (pos < m_nodePos && pos < endPos)
    {
        if (m_nodeData[pos].elementIdentifier == elementId && m_nodeData[pos].nodeType == nodeType)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}

bool SwParserBase::ResetNodeData()
{
    // Reset parts of node data that will be modified
    swUI32 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].nodeMate = NODE_ID_INVALID;
        m_nodeData[pos].nodeParent = NODE_ID_INVALID;
        m_nodeData[pos].nodeFirstChild = NODE_ID_INVALID;
        m_nodeData[pos].nodeNextSibling = NODE_ID_INVALID;
        pos ++;
    }

    return true;
}

bool SwParserBase::UpdateNodeData()
{
    if (!ResetNodeData())
        return false;

    if (!MateElements())
        return false;

    if (!ParentElements())
        return false;

    if (!SetFirstChild())
        return false;

    if (!SetNextSibling())
        return false;

    return true;
}

void SwParserBase::UpdatePositionData(swUI32 startNode, swI32 change)
{
    swUI32 pos = startNode;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].position += change;
        pos ++;
    }
}

swUI32 SwParserBase::GetLastParserNode()
{
    return m_nodePos -1;
}

swUI32 SwParserBase::GetParserNodes()
{
    return m_nodePos;
}
