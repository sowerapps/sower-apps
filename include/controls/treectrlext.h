///////////////////////////////////////////////////////////////////
// Name:        treectrlext.cpp
// Purpose:     An extension to wxTreeCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef TREECTRLEXT_H
#define TREECTRLEXT_H

#include "historylist.h"
#include <wx/treectrl.h>

enum APPENDMODE
{
    AP_ASROOT, AP_ROOTCHILD, AP_CHILD
};

class SOWERBASEEXP SwTreeData : public wxTreeItemData
{
public:
    SwTreeData();
    SwTreeData(wxUint32 data);
    virtual ~SwTreeData();

    void SetData(wxUint32 data);

    wxUint32 GetData();
    wxUint32 m_data;
};

class SOWERBASEEXP SwTreeDataEx : public wxTreeItemData
{
public:
    SwTreeDataEx()
    {
        m_managerId = NODE_ID_INVALID_16;
        m_pageId = NODE_ID_INVALID_16;
    }

    SwTreeDataEx(wxUint16 managerId, wxUint16 pageId)
    {
        m_managerId = managerId;
        m_pageId = pageId;
    }

    virtual ~SwTreeDataEx(){}

    wxUint16 m_managerId;
    wxUint16 m_pageId;
};

struct SwTreeAppendData
{
    wxTreeItemId id;
    wxUint8 depth;
};

class SOWERBASEEXP SwTreeCtrl : public wxTreeCtrl
{
    DECLARE_DYNAMIC_CLASS(SwTreeCtrl)

public:
    SwTreeCtrl();
    SwTreeCtrl(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTR_DEFAULT_STYLE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTreeCtrlNameStr);
    virtual ~SwTreeCtrl();

    virtual void Reset();
    bool IsRoot(wxTreeItemId id);
    void SetSowerImageList();
    void SelectFirst();
    void SelectNext();
    void SelectPrevious();
    wxTreeItemId Search(wxTreeItemId& start, wxUint32 data);
    wxTreeItemId Search(wxTreeItemId& start, const char * text, bool casesensitive = true);
    wxTreeItemId Search(wxTreeItemId& start, const wchar_t * text, bool casesensitive = true);
    wxTreeItemId GetNextItem(const wxTreeItemId& item, bool loop = true);
    wxTreeItemId GetNextItemInScope(const wxTreeItemId& parent, const wxTreeItemId& item);
    wxTreeItemId GetPrevItem(const wxTreeItemId& item);
    wxTreeItemId  AppendItemEx(const char * text, SwTreeAppendData & appendData, int image=-1, int stateImage=-1, wxUint8 mode = 0, wxTreeItemData *data = NULL);
    SwHistoryList & GetHistory() { return m_history; }

    protected:
    SwHistoryList m_history;
};

#endif // TREECTRLEXT_H
