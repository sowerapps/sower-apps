///////////////////////////////////////////////////////////////////
// Name:        autodefterm.h
// Purpose:     AutodefTerm - locates/retrieves entries from dictionaries,
//              encyclopedias, topical indexes, etc.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUTODEFTERM_H
#define AUTODEFTERM_H

#include "../module/modulebase.h"
#include "../string/stringw.h"
#include "../array/stringarray.h"
#include "../string/strparser.h"
#include "../array/uintarray.h"
#include "../module/moduleinterface.h"
#include <wx/listctrl.h>

struct SOWERBASEEXP SwADNodeData
{
    void Reset();
    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

    swUI32          bufferPos;
    SwModuleItemId  identifier;
};

class SOWERBASEEXP SwAutoDefTerm : public SwModuleInterface
{
public:
    SwAutoDefTerm();
    virtual ~SwAutoDefTerm();

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
    void UpdateNodePosData(swUI16 nodeStart, swUI16 change, bool type);
    void ShiftNodesUp(swUI16 startNode);
    bool ShiftNodesDown(swUI16 startNode);
    swUI16 GetNodeTextSize(swUI16 node);
    SwADNodeData * GetNode(swUI16 node);
    bool GetNodeText(swUI16 node, SwStringW & dest);
    bool SetNodeText(swUI16 node, const char * itemText, bool update = true);
    bool SetNodeText(swUI16 node, const wchar_t * itemText, bool update = true);
    SwModuleItemId GetNodeIdentifier(swUI16 node);
    bool SetNodeIdentifier(swUI16 node, SwModuleItemId identifier);
    bool BufferAppend(const wchar_t * data, swUI16 len);
    swUI16 AppendNode(const char * itemText, SwModuleItemId identifier, bool update = true);
    swUI16 AppendNode(const wchar_t * itemText, SwModuleItemId identifier, bool update = true);
    bool BufferInsert(swUI32 pos, const wchar_t * data, swUI16 len);
    bool InsertNode(swUI16 nodePos, const char * itemText, SwModuleItemId identifier, bool update = true);
    bool InsertNode(swUI16 nodePos, const wchar_t * itemText, SwModuleItemId identifier, bool update = true);
    bool BufferDelete(swUI32 pos, swUI16 len);
    bool DeleteNode(swUI16 node, bool update = true);
    bool BufferReplace(swUI32 pos, swUI16 len, const wchar_t * data, swUI16 newLen);
    bool ReplaceNode(swUI16 node, const char * itemText, SwModuleItemId identifier, bool update = true);
    bool ReplaceNode(swUI16 node, const wchar_t * itemText, SwModuleItemId identifier, bool update = true);
    bool MoveNode(swUI16 node, swUI16 newPos, bool update = true);
    swUI16 LocatePosition(wchar_t wc);
    bool AddToAlphaIndex(wchar_t wc, swUI16 alphaIdxPos);
    swUI16 FindInIndex(wchar_t wc);
    bool UpdateAlphaIdx();
    swUI16 FindAlphabeticInsertionPosition(const wchar_t * itemText);
    bool AddNode(const char * itemText, SwModuleItemId identifier, bool noDuplicates, bool update = true);
    bool AddNode(const wchar_t * itemText, SwModuleItemId identifier, bool noDuplicates, bool update = true);
    virtual swUI16 FindItem(const char * itemText);
    virtual swUI16 FindItem(const wchar_t * itemText);
    virtual swUI16 FindItem(const char * itemText, Swui16Array & array);
    virtual swUI16 FindItem(const wchar_t * itemText, Swui16Array & array);
    virtual swUI16 FindItem(SwStrParser & strList, Swui16Array & array);
    virtual swUI16 FindItem(SwStrParserW & strList, Swui16Array & array);
    virtual swUI16 FindItem(SwStringArray & strList, Swui16Array & array);
    virtual swUI16 FindItem(SwStringWArray & strList, Swui16Array & array);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual swUI32 GetType();
    void FillCtrl(wxListCtrl * listctrl);

protected:
    SwADNodeData *   m_nodeData;
    swUI16           m_nodePos;
    swUI16           m_nodesAllocated;
    swUI8            m_Inc;
    SwAlphaData *    m_alphaIndex;
    swUI16           m_alphaIndexSize;
    swUI16           m_alphaIndexPos;
    wchar_t *        m_buffer;
    swUI32           m_bufferSize;
    swUI32           m_dataSize;
};

#endif // AUTODEFTERM_H
