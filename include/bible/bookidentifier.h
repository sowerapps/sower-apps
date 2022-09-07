///////////////////////////////////////////////////////////////////
// Name:        bookidentifier.h
// Purpose:     Data container for biblical book names, and
//              abbreviations. This container can import it's
//              data from a file created by Sower Table Editor,
//              and save it's data as a Sower Binary Object and
//              load it's data without the need for import.
//              In the data file identifiers can be standard book
//              names (Genesis, Exodus). The data parameter can
//              be multiple entries separated with '|' (Genesis|Gen|Ge).
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef BOOKIDENTIFIER_H
#define BOOKIDENTIFIER_H

#include "../bible/bookidentifier.h"
#include "../string/string.h"
#include "../sdf/datafile.h"
#include "../module/moduleinterface.h"

struct SOWERBASEEXP SwBookIdNode
{
    void Reset();

    swUI32        bufferPos;
    swUI8         identifier;
};

class SOWERBASEEXP SwBookIdentifier
{
public:
    SwBookIdentifier();
    virtual ~SwBookIdentifier();

    void SetIncrement(swUI8 increment);
    bool IncreaseAlphaIdx();
    bool SizeAlphaIdx(swUI16 size);
    bool SizeBuffer(swUI32 size);
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI16 nodes);
    bool VerifyNode();
    bool VerifyNodes(swUI16 nodes);
    bool VerifyAlphaNode();
    bool VerifyAlphaNodes(swUI16 nodes);
    swUI16 GetLastNode();
    swUI16 GetNodes();
    void Reset();
    void ResetNodeData();
    void ResetAlphaIdx();
    bool AddToAlphaIndex(wchar_t wc, swUI16 identifier);
    swUI16 FindInIndex(wchar_t wc);
    bool UpdateAlphaIdx();
    void UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type);
    void ShiftNodesUp(swUI16 startNode);
    bool ShiftNodesDown(swUI16 startNode);
    swUI16 GetNodeTextSize(swUI16 node);
    SwBookIdNode * GetNode(swUI16 node);
    bool GetNodeText(swUI16 node, SwStringW & dest);
    bool GetNodeText(swUI16 node, wchar_t * dest);
    bool SetNodeText(swUI16 node, const char * itemText, bool update = true);
    bool SetNodeText(swUI16 node, const wchar_t * itemText, bool update = true);
    swUI8 GetNodeIdentifier(swUI16 node);
    bool SetNodeIdentifier(swUI16 node, swUI8 identifier);
    bool BufferAppend(const wchar_t * data, swUI16 len);
    swUI16 AppendNode(const char * itemText, swUI8 identifier, bool update = true);
    swUI16 AppendNode(const wchar_t * itemText, swUI8 identifier, bool update = true);
    bool BufferInsert(swUI32 pos, const wchar_t * data, swUI16 len);
    bool InsertNode(swUI16 nodePos, const char * itemText, swUI8 identifier, bool update = true);
    bool InsertNode(swUI16 nodePos, const wchar_t * itemText, swUI8 identifier, bool update = true);
    bool BufferDelete(swUI32 pos, swUI16 len);
    bool DeleteNode(swUI16 node, bool update = true);
    bool BufferReplace(swUI32 pos, swUI16 len, const wchar_t * data, swUI16 newLen);
    bool ReplaceNode(swUI16 node, const char * itemText, swUI8 identifier, bool update = true);
    bool ReplaceNode(swUI16 node, const wchar_t * itemText, swUI8 identifier, bool update = true);
    bool MoveNode(swUI16 node, swUI16 newPos, bool update = true);
    swUI16 LocatePosition(wchar_t ch);
    bool AddNode(const char * itemText, swUI8 identifier, bool update = true);
    bool AddNode(const wchar_t * itemText, swUI8 identifier, bool update = true);
    virtual swUI8 FindItem(const char * itemText);
    virtual swUI8 FindItem(const wchar_t * itemText);
    virtual bool WriteToFile(FILE * file);
    virtual bool ReadFromFile(FILE * file);
    void Import(SwDataFile & datafile);

protected:
    SwBookIdNode *          m_nodeData;
    swUI16                  m_nodePos;
    swUI16                  m_nodesAllocated;
    swUI8                   m_Inc;
    SwAlphaData *             m_alphaIndex;
    swUI16                  m_alphaIndexSize;
    swUI16                  m_alphaIndexPos;
    wchar_t *               m_buffer;
    swUI32                  m_bufferSize;
    swUI32                  m_dataSize;
};

#endif // BOOKIDENTIFIER_H
