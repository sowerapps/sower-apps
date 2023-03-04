///////////////////////////////////////////////////////////////////
// Name:        autodefnumbered.h
// Purpose:     AutodefNumbered - locates/retrieves numbered entries,
//              primarily strongs numbers, and ThML notes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUTODEFSTRONGS_H
#define AUTODEFSTRONGS_H

#include "../module/modulebase.h"
#include "../module/moduleinterface.h"
#include "../string/string.h"
#include <wx/listctrl.h>

struct SOWERBASEEXP SwADNumberedNodeData
{
    void Reset();
    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

    swUI16            number;
    SwModuleItemId    identifier;
};

class SOWERBASEEXP SwAutoDefNumbered : public SwModuleInterface
{
public:
    SwAutoDefNumbered();
    virtual ~SwAutoDefNumbered();

    swUI8 GetSyncType();
    void SetSyncType(swUI8 type);
    void SetIncrement(swUI8 increment);
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI16 nodes);
    bool VerifyNode();
    bool VerifyNodes(swUI16 nodes);
    swUI16 GetLastNode();
    swUI16 GetNodes();
    void Reset();
    void Update();
    swUI16 GetLower();
    swUI16 GetUpper();
    void ShiftNodesUp(swUI16 startNode);
    bool ShiftNodesDown(swUI16 startNode);
    SwADNumberedNodeData * GetNode(swUI16 node);
    SwModuleItemId GetNodeIdentifier(swUI16 node);
    swUI16 GetNodeNumber(swUI16 node);
    bool SetNodeIdentifier(swUI16 node, SwModuleItemId identifier);
    bool SetNodeNumber(swUI16 node, const char * number);
    bool SetNodeNumber(swUI16 node, const wchar_t * number);
    bool SetNodeNumber(swUI16 node, swUI16 number);
    swUI16 AppendNode(const char * number, SwModuleItemId identifier);
    swUI16 AppendNode(const wchar_t * number, SwModuleItemId identifier);
    swUI16 AppendNode(swUI16 number, SwModuleItemId identifier);
    bool InsertNode(swUI16 nodePos, const char * number, SwModuleItemId identifier);
    bool InsertNode(swUI16 nodePos, const wchar_t * number, SwModuleItemId identifier);
    bool InsertNode(swUI16 nodePos, swUI16 number, SwModuleItemId identifier);
    bool DeleteNode(swUI16 node);
    bool ReplaceNode(swUI16 node, const char * number, SwModuleItemId identifier);
    bool ReplaceNode(swUI16 node, const wchar_t * number, SwModuleItemId identifier);
    bool ReplaceNode(swUI16 node, swUI16 number, SwModuleItemId identifier);
    bool MoveNode(swUI16 node, swUI16 newPos);
    swUI16 LocatePosition(swUI16 number);
    bool AddNode(const char * number, SwModuleItemId identifier);
    bool AddNode(const wchar_t * number, SwModuleItemId identifier);
    bool AddNode(swUI16 number, SwModuleItemId identifier);
    virtual swUI16 FindItem(const char * number);
    virtual swUI16 FindItem(const wchar_t * number);
    virtual swUI16 FindItem(swUI16 number);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual swUI32 GetType();
    void FillCtrl(wxListCtrl * listctrl);

protected:
    SwADNumberedNodeData * m_nodeData;
    swUI16                 m_nodePos;
    swUI16                 m_nodesAllocated;
    swUI8                  m_Inc;
    swUI16                 m_lower;
    swUI16                 m_upper;
    swUI8                  m_type;
};

#endif // AUTODEFSTRONGS_H
