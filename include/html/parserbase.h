///////////////////////////////////////////////////////////////////
// Name:        parserbase.h
// Purpose:     SwParserBase
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef PARSERBASE_H
#define PARSERBASE_H

#include "../sowerbase.h"

struct SD_NODE_DATA
{
    swUI32      position;
    swUI16      elementIdentifier;
    swUI8       nodeType;
    swUI32      nodeMate;
    swUI32      nodeParent;
    swUI32      nodeFirstChild;
    swUI32      nodeNextSibling;
    char *      xmlId;
    char *      passageId;
    void *      data;
};

class SOWERBASEEXP SwParserBase
{
public:
    SwParserBase();
    virtual ~SwParserBase();
    void Reset();
    bool IncreaseDataBuffer();
    swUI32 AssignDataNode();
    void ReleaseDataBuffer();
    void FreeIdStrings();
    bool MateElements();
    bool FixMissingMates();
    bool ParentElements();
    bool SetFirstChild();
    bool SetNextSibling();
    bool ResetNodeData();
    bool UpdateNodeData();
    swUI32 GetLastParserNode();
    swUI32 GetParserNodes();
    bool AddTag(swUI16 identifier, swUI8 type, const char * xmlId, const char * passageId, swUI32 position, void * data);
    const char * GetXmlId(swUI32 node);
    const char * GetPassageId(swUI32 node);
    swUI16 GetNodeElementIdentifier(swUI32 node);
    swUI8 GetNodeType(swUI32 node);
    swUI32 GetNodeStreamPosition(swUI32 node);
    SD_NODE_DATA * GetNode(swUI32 node);
    swUI32 GetNodeMate(swUI32 node);
    swUI32 GetNodeParent(swUI32 node);
    swUI32 GetFirstChild(swUI32 node);
    swUI32 GetNextSibling(swUI32 node);
    swUI32 GetNextSiblingOfType(swUI32 nodeOrigin, swUI8 elementId, swUI8 nodeType);
    void * GetNodeData(swUI32 node);
    swUI32 FindElement(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType);
    swUI32 FindElementUpWard(swUI32 nodeOrigin, swUI16 elementId, swUI8 nodeType);
    swUI32 FindWithInElement(swUI32 nodeParent, swUI32 nodeOffset, swUI16 elementId, swUI8 nodeType);
    swUI32 FindNodeByXmlId(swUI32 nodeOrigin, const char * id);
    swUI32 FindNodeByPassageId(swUI32 nodeOrigin, const char * id);
    swUI32 FindNodeByStreamPos(swUI32 streamPos);
    void UpdatePositionData(swUI32 startNode, swI32 change);

protected:
    SD_NODE_DATA *      m_nodeData;
    swUI32              m_nodesAllocated;
    swUI32              m_nodePos;
};

#endif // PARSERBASE_H
