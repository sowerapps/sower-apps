///////////////////////////////////////////////////////////////////
// Name:        tableofcontents.h
// Purpose:     Table of Contents for Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef TABLEOFCONTENTS_H
#define TABLEOFCONTENTS_H

#include "../module/modulebase.h"
#include "../module/moduleinterface.h"
#include "../module/autodefterm.h"
#include "../string/string.h"
#include "category.h"

struct SOWERBASEEXP SwContentsNode
{
    SwModuleItemId    identifier;
    swUI8             divDepth;
    swUI32            bufferPos;
    swUI32            idbufferPos;
    bool              hasChildren;
    swUI8             contentType;

    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

};

class SOWERBASEEXP SwTableOfContents : public SwModuleInterface
{
public:
    SwTableOfContents();
    virtual ~SwTableOfContents();

    void SetIncrement(swUI8 increment);
    bool SizeBuffer(swUI32 size);
    bool SizeIdBuffer(swUI32 size);
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI16 nodes);
    bool VerifyNode();
    bool VerifyNodes(swUI16 nodes);
    swUI16 GetLastNode();
    swUI16 GetNodes();
    void Reset();
    void ResetNodeData();
    void UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type);
    void UpdateNodeIdPosData(swUI16 nodeStart, swUI16 change, bool type);
    void ShiftNodesUp(swUI16 startNode);
    bool ShiftNodesDown(swUI16 startNode);
    SwContentsNode * GetNode(swUI16 node);
    const char * GetTitleText(swUI16 node);
    bool GetTitle(swUI16 node, SwString & dest);
    const char * GetIdText(swUI16 node);
    bool GetId(swUI16 node, SwString & dest);
    bool SetTitle(swUI16 node, const char * title);
    bool SetId(swUI16 node, const char * id);
    swUI16 GetTitleSize(swUI16 node);
    swUI16 GetIdSize(swUI16 node);
    SwModuleItemId GetIdentifier(swUI16 node);
    bool SetIdentifier(swUI16 node, SwModuleItemId identifier);
    swUI8 GetDivDepth(swUI16 node);
    bool SetDivDepth(swUI16 node, swUI8 divDepth);
    bool GetHasChildren(swUI16 node);
    bool SetHasChildren(swUI16 node, bool hasChildren);
    swUI8 GetContentType(swUI16 node);
    bool SetContentType(swUI16 node, swUI8 type);
    bool BufferAppend(const char * data, swUI16 len);
    bool IdBufferAppend(const char * data, swUI16 len);
    swUI16 Append(const char * title, SwModuleItemId identifier, const char * id);
    bool BufferInsert(swUI16 pos, const char * data, swUI16 len);
    bool IdBufferInsert(swUI16 pos, const char * data, swUI16 len);
    bool Insert(swUI16 nodePos, const char * title, SwModuleItemId identifier, const char * id);
    bool BufferDelete(swUI16 pos, swUI16 len);
    bool IdBufferDelete(swUI16 pos, swUI16 len);
    bool Delete(swUI16 nodePos);
    bool BufferReplace(swUI16 pos, swUI16 len, const char * data, swUI16 newLen);
    bool IdBufferReplace(swUI16 pos, swUI16 len, const char * data, swUI16 newLen);
    bool Move(swUI16 node, swUI16 newPos);
    virtual swUI16 FindItem(const char * title);
    virtual swUI16 FindByID(const char * id);
    virtual swUI16 FindItem(SwModuleItemId identifier);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual swUI32 GetType();
    void FillCtrl(wxListCtrl * listctrl);

    protected:
    SwContentsNode * m_nodeData;
    swUI16         m_nodePos;
    swUI16         m_nodesAllocated;
    swUI8          m_Inc;
    char *         m_buffer;
    swUI32         m_bufferSize;
    swUI32         m_dataSize;
    char *         m_idbuffer;
    swUI32         m_idbufferSize;
    swUI32         m_iddataSize;
};

#endif // TABLEOFCONTENTS_H
