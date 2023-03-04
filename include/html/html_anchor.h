///////////////////////////////////////////////////////////////////
// Name:        html_anchor.h
// Purpose:     For locating anchors, and links to anchors
//              that have been written to a viewer.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef ANCHOR_H
#define ANCHOR_H

#include "../sowerbase.h"

struct SwAnchorData
{
    char * name;
    swUI32 origin;
    swUI32 originExtent;
    swUI32 target;
    swUI32 targetExtent;
};

class SOWERBASEEXP SwHtmlAnchor
{
public:
    SwHtmlAnchor();
    virtual ~SwHtmlAnchor();

    swUI32 Add(const char * name, swUI32 origin, swUI32 extentPos = 0);
    void Delete(swUI32 id);
    void DeleteAll();
    bool VerifyAnchorId(swUI32 id);
    bool SetName(swUI32 id, const char * name);
    const char * GetName(swUI32 id);
    bool SetAnchorOrigin(swUI32 id, swUI32 originPos);
    swUI32 GetAnchorOrigin(swUI32 id);
    bool SetAnchorOriginExtent(swUI32 id, swUI32 extentPos);
    swUI32 GetAnchorOriginExtent(swUI32 id);
    bool SetAnchorTarget(swUI32 id, swUI32 targetPos);
    swUI32 GetAnchorTarget(swUI32 id);
    bool SetAnchorTargetExtent(swUI32 id, swUI32 extentPos);
    swUI32 GetAnchorTargetExtent(swUI32 id);
    swUI32 Find(const char * name);

protected:
    swUI32 AssignAnchorDataNode();
    bool IncreaseAnchorDataBuffer();
    void ReleaseAnchorDataBuffer();

    SwAnchorData *   m_anchorData;
    swUI32           m_anchornodesAllocated;
    swUI32           m_anchornodePos;
};

#endif // ANCHOR_H
