///////////////////////////////////////////////////////////////////
// Name:        html_anchor.cpp
// Purpose:     For locating anchors, and links to anchors
//              that have been written to a viewer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/html/html_anchor.h"

SwHtmlAnchor::SwHtmlAnchor()
{
    m_anchorData = NULL;
    m_anchornodesAllocated = 0;
    m_anchornodePos = 0;
}

SwHtmlAnchor::~SwHtmlAnchor()
{
    if (m_anchorData)
        ReleaseAnchorDataBuffer();
}

bool SwHtmlAnchor::IncreaseAnchorDataBuffer()
{
    swUI32 pos = m_anchornodePos;

    if (m_anchornodesAllocated >= NODE_ID_INVALID - 101)
        return false;

    SwAnchorData * p = (SwAnchorData *) realloc((void *) m_anchorData, (m_anchornodesAllocated + 100) * sizeof(SwAnchorData));

    if (p)
    {
        m_anchornodesAllocated += 100;
        m_anchorData = p;

        while (pos < m_anchornodesAllocated)
        {
            m_anchorData[pos].name = NULL;
            pos ++;
        }

        return true;
    }

    return false;
}

swUI32 SwHtmlAnchor::AssignAnchorDataNode()
{

    if (m_anchornodePos >= m_anchornodesAllocated && !IncreaseAnchorDataBuffer())
        return NODE_ID_INVALID;

    memset(&m_anchorData[m_anchornodePos], 0, sizeof(SwAnchorData));
    m_anchornodePos ++;

    return m_anchornodePos - 1;
}

void SwHtmlAnchor::ReleaseAnchorDataBuffer()
{
    if (m_anchorData)
    {
        DeleteAll();
        free(m_anchorData);
    }

    m_anchorData = NULL;
    m_anchornodesAllocated = 0;
    m_anchornodePos = 0;
}

swUI32 SwHtmlAnchor::Add(const char * name, swUI32 origin, swUI32 extentPos)
{
    if (!name)
        return NODE_ID_INVALID;

    swUI32 id = AssignAnchorDataNode();

    if (id == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    SetName(id, name);
    SetAnchorOrigin(id, origin);
    SetAnchorOriginExtent(id, extentPos);

    return id;
}

void SwHtmlAnchor::Delete(swUI32 id)
{
    swUI32 pos = id;

    if (id >= m_anchornodePos)
        return;

    if (m_anchorData[id].name)
        free(m_anchorData[id].name);

    m_anchorData[id].origin = 0;
    m_anchorData[id].originExtent = 0;
    m_anchorData[id].target = 0;
    m_anchorData[id].targetExtent = 0;

    if (m_anchornodePos >= 1)
    {
        pos ++;

        while (pos < m_anchornodePos)
        {
            m_anchorData[pos -1] = m_anchorData[pos];
            m_anchorData[pos].name = NULL;
            m_anchorData[pos].origin = 0;
            m_anchorData[pos].originExtent = 0;
            m_anchorData[pos].target = 0;
            m_anchorData[pos].targetExtent = 0;

            pos ++;
        }
    }

    m_anchornodePos --;
}

void SwHtmlAnchor::DeleteAll()
{
    swUI32 pos = 0;

    if (!m_anchorData)
        return;

    while(pos < m_anchornodePos)
    {
        if (m_anchorData[pos].name != NULL)
        {
            free(m_anchorData[pos].name);
            m_anchorData[pos].name = NULL;
        }

        m_anchorData[pos].origin = 0;
        m_anchorData[pos].originExtent = 0;
        m_anchorData[pos].target = 0;
        m_anchorData[pos].targetExtent = 0;

        pos ++;
    }

    m_anchornodePos = 0;
}

bool SwHtmlAnchor::VerifyAnchorId(swUI32 id)
{
    if (id >= m_anchornodePos)
        return false;

    return true;
}

bool SwHtmlAnchor::SetName(swUI32 id, const char * name)
{
    if (id >= m_anchornodePos)
        return false;

    if (m_anchorData[id].name != NULL)
        free(m_anchorData[id].name);

    m_anchorData[id].name = strdup(name);

    if (m_anchorData[id].name)
        return true;

    return false;
}

const char * SwHtmlAnchor::GetName(swUI32 id)
{
    if (id >= m_anchornodePos)
        return NULL;

    return m_anchorData[id].name;
}

bool SwHtmlAnchor::SetAnchorOrigin(swUI32 id, swUI32 originPos)
{
    if (id >= m_anchornodePos)
        return false;

    m_anchorData[id].origin = originPos;

    return true;
}

swUI32 SwHtmlAnchor::GetAnchorOrigin(swUI32 id)
{
    if (id >= m_anchornodePos)
        return NODE_ID_INVALID;

    return m_anchorData[id].origin;
}

bool SwHtmlAnchor::SetAnchorOriginExtent(swUI32 id, swUI32 extentPos)
{
    if (id >= m_anchornodePos)
        return false;

    m_anchorData[id].originExtent = extentPos;

    return true;
}

swUI32 SwHtmlAnchor::GetAnchorOriginExtent(swUI32 id)
{
    if (id >= m_anchornodePos)
        return NODE_ID_INVALID;

    return m_anchorData[id].originExtent;
}


bool SwHtmlAnchor::SetAnchorTarget(swUI32 id, swUI32 targetPos)
{
    if (id >= m_anchornodePos)
        return false;

    m_anchorData[id].target = targetPos;

    return true;
}

swUI32 SwHtmlAnchor::GetAnchorTarget(swUI32 id)
{
    if (id >= m_anchornodePos)
        return NODE_ID_INVALID;

    return m_anchorData[id].target;
}

bool SwHtmlAnchor::SetAnchorTargetExtent(swUI32 id, swUI32 extentPos)
{
    if (id >= m_anchornodePos)
        return false;

    m_anchorData[id].targetExtent = extentPos;

    return true;
}

swUI32 SwHtmlAnchor::GetAnchorTargetExtent(swUI32 id)
{
    if (id >= m_anchornodePos)
        return NODE_ID_INVALID;

    return m_anchorData[id].targetExtent;
}

swUI32 SwHtmlAnchor::Find(const char * name)
{
    swUI32 pos = 0;

    if (!name)
        return NODE_ID_INVALID;

    while (pos < m_anchornodePos)
    {
        if (strcmp(m_anchorData[pos].name, name) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}
