///////////////////////////////////////////////////////////////////
// Name:        moduletreectrl.h
// Purpose:     A tree control that can create it's content from
//              one or more Sower modules. The content from each
//              can be created in a category, and group folders.
//              It can perform searches, and retrieve content from
//              modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MODULETREECTRL_H
#define MODULETREECTRL_H

#include "treectrlext.h"
#include "../module/tableofcontents.h"
#include "../controls/controls.h"
#include "../string/stringcompare.h"

class SOWERBASEEXP SwModuleTreeCtrl : public SwTreeCtrl
{
    DECLARE_DYNAMIC_CLASS(SwModuleTreeCtrl)

public:
    SwModuleTreeCtrl();
    SwModuleTreeCtrl(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTR_DEFAULT_STYLE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTreeCtrlNameStr);
    virtual ~SwModuleTreeCtrl();

    virtual void Reset();

    bool BuildTree(SwTableOfContents & toc, wxTreeItemId parent, swUI8 category, swUI16 managerId);
    bool VerifyId(SwTreeDataEx * td);
    bool ReadDivText(SwTreeDataEx * td, SwString & buffer, bool &canCopy);
    bool Load(SwString & buffer, wxTreeItemId id, bool & canCopy);
    void Search(SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId);
    void Search(swUI16 managerId, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId);
    void Search(wxTreeItemId & start, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl);
    wxTreeItemId Search(wxTreeItemId& start, swUI16 managerId, swUI16 pageId);

    void OnLanguageChange();
    void OnThemeChange();

    SwStringArray & GetIds() { return m_ids; }
    bool HasModule(const char * bookId);
    const char * GetBookId();
    Swui8Array & GetCategories() { return m_categories; }
    bool HasCategory(swUI8 category);
    swUI8 GetCategory();
    void LoadBooks();
    void LoadBooksForGroup(swUI8 group);
    void LoadBooks(swUI8 cat);

    wxTreeItemId FindCategory(swUI8 category);
    void GetCategories(SwChoice * choice);
    wxTreeItemId CreateCategory(swUI8 category);
    wxTreeItemId FindGroup(swUI8 category, const wchar_t * group);
    wxTreeItemId CreateGroup(swUI8 category, const wchar_t * group);

protected:
    SwStringArray m_ids;
    Swui8Array    m_categories;
};

#endif // MODULETREECTRL_H
