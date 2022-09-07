///////////////////////////////////////////////////////////////////
// Name:        mediacontents.h
// Purpose:     SwMediaContents provides access to additional files
//              stored in Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MEDIACONTENTS_H
#define MEDIACONTENTS_H

#include "../module/modulebase.h"
#include "../module/moduleinterface.h"
#include "../module/autodefterm.h"
#include "../string/string.h"
#include "../array/uintarray.h"
#include "../filesys/streambuffer.h"
#include "../html/html_imagemap.h"

enum SW_MEDIA_TYPE
{
    SW_MEDIA_TYPE_UNKNOWN,
    SW_MEDIA_TYPE_AUDIO,
    SW_MEDIA_TYPE_IMAGE,
    SW_MEDIA_TYPE_VIDEO,
    SW_MEDIA_TYPE_INTERFACE,
    N_SW_MEDIA_TYPE
};

struct SOWERBASEEXP SwMediaNode
{
    void Reset();
    bool ReadData(FILE * f, SwStreamBuffer & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);
    bool ReadData(FILE * f, Swui8Array & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);
    bool ReadData(FILE * f, SwHtmlImageMapList & imagemapList, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);
    bool ReadData(FILE * f, SwHtmlImageMap & imageMap, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);
    bool ReadData(FILE * f, Swui8Array & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI32 streamOffset, swUI32 bytes, swUI8 k1, swUI32 k2, bool encrypted);
    swUI32 ReadStream(FILE * f, void * buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI32 streamOffset, swUI32 bytes, swUI8 k1, swUI32 k2, bool encrypted);
    swUI32 GetSize(FILE * f, swUI32 itemindexFp, swUI32 streamOffset);
    SwModuleItemId identifier;
    swUI16         bufferPos;
    swUI8          contentType;
};

class SOWERBASEEXP SwMediaContents : public SwModuleInterface
{
public:
    SwMediaContents();
    virtual ~SwMediaContents();

    void SetIncrement(swUI8 increment);
    bool SizeBuffer(swUI16 size);
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI16 nodes);
    bool VerifyNode();
    bool VerifyNodes(swUI16 nodes);
    swUI16 GetLastNode();
    swUI16 GetNodes();
    void Reset();
    void ResetNodeData();
    void UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type);
    void ShiftNodesUp(swUI16 startNode);
    bool ShiftNodesDown(swUI16 startNode);
    swUI16 GetNodeTextSize(swUI16 node);
    SwMediaNode * GetNode(swUI16 node);
    bool GetNodeText(swUI16 node, SwString & dest);
    SwModuleItemId GetNodeIdentifier(swUI16 node);
    bool SetNodeIdentifier(swUI16 node, SwModuleItemId identifier);
    swUI8 GetNodeContentType(swUI16 node);
    bool SetNodeContentType(swUI16 node, swUI8 type);
    bool BufferAppend(const char * data, swUI16 len);
    swUI16 AppendNode(const char * itemText, SwModuleItemId identifier, swUI8 type = 0);
    bool BufferInsert(swUI16 pos, const char * data, swUI16 len);
    bool InsertNode(swUI16 nodePos, const char * itemText, SwModuleItemId identifier, swUI8 type = 0);
    bool BufferDelete(swUI16 pos, swUI16 len);
    bool DeleteNode(swUI16 nodePos);
    bool BufferReplace(swUI16 pos, swUI16 len, const char * data, swUI16 newLen);
    bool SetNodeText(swUI16 nodePos, const char * itemText);
    bool MoveNode(swUI16 node, swUI16 newPos);
    virtual swUI16 FindItem(const char * itemText);
    virtual swUI16 FindItem(SwModuleItemId identifier);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual swUI32 GetType();
    void FillCtrl(wxListCtrl * listctrl);

protected:
    SwMediaNode * m_nodeData;
    swUI16        m_nodePos;
    swUI16        m_nodesAllocated;
    swUI8         m_Inc;
    char *        m_buffer;
    swUI16        m_bufferSize;
    swUI16        m_dataSize;
};

#endif // MEDIACONTENTS_H
