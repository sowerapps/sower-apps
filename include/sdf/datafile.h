///////////////////////////////////////////////////////////////////
// Name:        datafile.h
// Purpose:     Sower Data files (sdf) are HTML files with one or
//              more tables. SowerBase uses this method for themes,
//              translations, user preferences, etc.
//              SwDataFile is used to read, write, and edit those files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef DATAFILE_H
#define DATAFILE_H

#include "../thml/thml_parser.h"
#include "../string/stringw.h"
#include <wx/choice.h>
#include <wx/listctrl.h>
#include <wx/dataview.h>
#include <wx/propgrid/propgrid.h>

class SOWERBASEEXP SwTableItem
{
public :
    SwTableItem();
    virtual ~SwTableItem();

    char *                          id;
    char *                          data;
    char *                          param1;
    char *                          param2;
    swUI32                          findId;
    swUI8                           cellType;
    void Init();
    void Reset();
    char * SetItem(const char * item, const char * data);
    void ReleaseBuffers();
    const char * GetId();
    void SetId(const char * idstring);
    const char * GetData();
    void SetData(const char * datastring);
    const char * GetParam1();
    void SetParam1(const char * paramstring);
    const char * GetParam2();
    const char * GetParam2(SwTextRange & sel);
    void SetParam2(const char * paramstring);
    swUI8 GetCellType();
    void SetCellType(swUI8 type);
    swUI32 GetFindId();
    void SetFindId(swUI32 findID);
    void Copy(SwTableItem & tableItem);
    bool HasId();
    bool HasData();
    bool HasParam1();
    bool HasParam2();
};

class SOWERBASEEXP SwTable
{
public:
    SwTable();
    virtual ~SwTable();

    void SetIncrement(swUI8 increment);
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI32 nodes);
    bool VerifyNode();
    swUI32 GetLastNode();
    swUI32 GetNodes();
    void Reset();
    void ResetNodeData();
    void ShiftNodesUp(swUI32 startNode);
    bool ShiftNodesDown(swUI32 startNode);
    const char * GetBasePath();
    void SetBasePath(const char * basePath);
    SwTableItem * GetNode(swUI32 node);
    const char * GetNodeId(swUI32 node);
    bool SetNodeId(swUI32 node, const char * id);
    bool SetNodeId(swUI32 node, const wchar_t * id);
    const char * GetNodeData(swUI32 node);
    bool GetNodeDataW(swUI32 node, SwStringW & buffer);
    bool SetNodeData(swUI32 node, const char * data);
    const char * GetNodeParam1(swUI32 node);
    swUI32 GetNodeParam1AsUint(swUI32 node);
    bool SetNodeParam1(swUI32 node, const char * param);
    bool SetNodeParam1(swUI32 node, swUI32 param);
    const char * GetNodeParam2(swUI32 node);
    swUI32 GetNodeParam2AsUint(swUI32 node);
    void GetNodeParam2(swUI32 node, swUI32 & selBegin, swUI32 & selEnd);
    void GetNodeParam2(swUI32 node, SwTextRange & sel);
    bool SetNodeParam2(swUI32 node, const char * param);
    bool SetNodeParam2(swUI32 node, swUI32 param);
    bool SetNodeParam2(swUI32 node, swUI32 selBegin, swUI32 selEnd);
    bool SetNodeParam2(swUI32 node, SwTextRange sel);
    swUI32 GetNodeCellType(swUI32 node);
    bool SetNodeCellType(swUI32 node, swUI8 type);
    swUI32 AppendNode(const char * id, const char * data, swUI8 type = CELLTYPE_TEXT);
    swUI32 AppendNode(const char * id, const char * data, const char * param1, const char * param2, swUI8 type = CELLTYPE_TEXT);
    bool InsertNode(swUI32 nodePos, const char * id, const char * data, swUI8 type = CELLTYPE_TEXT);
    bool InsertNode(swUI32 nodePos, const char * id, const char * data, const char * param1, const char * param2, swUI8 type = CELLTYPE_TEXT);
    bool DeleteNode(swUI32 nodePos);
    swUI32 UpdateNode(const char * id, const char * data, swUI8 type = CELLTYPE_TEXT);
    swUI32 UpdateNode(const char * id, const char * data, const char * param1, const char * param2, swUI8 type = CELLTYPE_TEXT);

    const char * GetTableCaption();
    const wchar_t * GetTableCaptionW();
    void SetTableCaption(const char * caption);
    swUI32 GetDataSize();
    swUI32 GetItems();
    bool GetTranslatedString(const char * id, SwStringW & buffer, bool stripAmpersand);
    swUI32 FindItemById(const char * id);
    swUI32 FindItemByData(const char * data);
    swUI32 Format(SwString & buffer);
    bool GetMediaPath(const char * id, SwString & buffer);
    void StripAmpersand(char * source);
    void StripAmpersand(wchar_t * source);
    void FillCtrl(wxListCtrl * listCtrl);
    void FillCtrlEx(wxListCtrl * listctrl);
    void FillPropertyGrid(wxPropertyGrid * pg);
    void Import(wxPropertyGrid * pg, const char * id, swUI8 type);
    void Import(wxListCtrl * listctrl, const char * id, swUI8 type = CELLTYPE_TEXT);
    void ImportEx(wxListCtrl * listctrl, const char * id, swUI8 type = CELLTYPE_TEXT);
    void FillDataViewListCtrl(wxDataViewListCtrl * listctrl);
    void Import(wxDataViewListCtrl * listctrl, const char * id, swUI8 type = CELLTYPE_TEXT);

protected:
    char *                          m_basePath;
    char *                          m_tableCaption;
    SwTableItem *                   m_nodeData;
    swUI32                          m_nodePos;
    swUI32                          m_nodesAllocated;
    swUI8                           m_Inc;

private:
    void FreeNodeData();
};

class SOWERBASEEXP SwDataFile : public SwThMLParser
{
public:
    SwDataFile();
    virtual ~SwDataFile();

    bool OpenFile(const char * path, bool verifyFile = false);
    bool OpenFile(const wchar_t * path, bool verifyFile = false);
    bool VerifyFile(const char * path);
    virtual swUI32 CreateTableIndex();
    swUI32 GetTableCount();
    swUI32 GetTableCaption(swUI32 table, SwString & dest);
    swUI32 GetTableCaptionW(swUI32 table, SwStringW & dest);
    swUI32 FindTableByCaption(const char * caption);
    swUI32 FindTableByCaption(const wchar_t * caption);
    void OnNodeDataUpdate();
    bool OpenFile(const char * path, swUI8 mode, bool processtableData);
    bool CloseFile(bool freeResources = false);
    virtual bool VerifyClose();
    bool FillTable(swUI32 table);
    bool FillTable(swUI32 table, SwTable & tableData);
    bool AppendTable();
    bool AppendTable(SwTable & tableData);
    bool InsertTable(swUI32 tablePos);
    bool InsertTable(swUI32 tablePos, SwTable & tableData);
    bool ReplaceTable(swUI32 table);
    bool ReplaceTable(swUI32 table, SwTable & tableData);
    bool UpdateTable(const char * name);
    bool UpdateTable(const char * name, SwTable & tableData);
    bool DeleteTable(swUI32 table);
    static void RemoveWhiteSpace(char * buffer);
    SwTable & GetTable();
    static bool MakeControlString(const char * id, SwTable * translationTable, SwStringW & buffer);
    void FillCtrl(wxListCtrl * listCtrl);
    void FillCtrl(wxChoice & choice);
    static void CreateDataListString(wxListCtrl * listctrl, SwString & buffer, const char * id);
    static void CreateDataListString(SwStringArray & array, SwString & buffer, const char * id);

protected:
    bool IncreaseArray();
    swUI32 *              m_itemNodeArray;
    swUI32                m_arrayPos;
    swUI32                m_arraySize;
    SwTable               m_tableData;
};

#endif // DATAFILE_H
