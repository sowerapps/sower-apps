///////////////////////////////////////////////////////////////////
// Name:        historylist.h
// Purpose:     Non-Gui SwHistoryItem list.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HISTORYLIST_H
#define HISTORYLIST_H

#include "../sowerbase.h"
#include "../controls/controls.h"
#include <wx/treebase.h>

struct SwHistoryItem
{
    wxTreeItemId    id;
    SwScrollData    scrolldata;
};

class SOWERBASEEXP SwHistoryList
{
public:
    SwHistoryList();
    virtual ~SwHistoryList();

    bool Size(swUI32 size);
    swUI32 GetCount();
    void Reset();
    SwHistoryItem * GetAt(swUI32 pos);
    void SetLastItemScrollData(SwScrollData scrolldata);
    swUI32 Append(wxTreeItemId id);
    bool SetData(swUI32 pos, wxTreeItemId id, SwScrollData scrolldata);
    swUI32 GetPosition();
    bool SetPosition(swUI32 pos);
    bool CanMoveForward();
    bool CanMoveBack();
    bool IncrementPosition();
    bool DecrementPosition();

protected:
    SwHistoryItem * m_array;
    swUI32          m_count;
    swUI32          m_size;
    swUI32          m_position;
};

#endif // HISTORYLIST_H
