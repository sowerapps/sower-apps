///////////////////////////////////////////////////////////////////
// Name:        thmltreectrl.h
// Purpose:     A tree control that can read the structure of a
//              ThML file, display the table of contents in the tree,
//              and retrieve the contents of a division with
//              css inlined, and notes processed. And perform
//              searches.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLTREECTRL_H
#define THMLTREECTRL_H

#include "treectrlext.h"
#include "../string/stringcompare.h"
#include "../thml/thml_file.h"

class SOWERBASEEXP SwThMLTreeCtrl : public SwTreeCtrl
{
    DECLARE_DYNAMIC_CLASS(SwThMLTreeCtrl)

public:
    SwThMLTreeCtrl();
    SwThMLTreeCtrl(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTR_DEFAULT_STYLE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTreeCtrlNameStr);
    virtual ~SwThMLTreeCtrl();

    virtual void Reset();

    bool BuildTree(SwThMLTableOfContents & toc, wxTreeItemId parent, swUI8 category, swUI16 managerId);
    bool VerifyId(SwTreeDataEx * td);
    bool ReadDivText(SwTreeDataEx * td, SwString & buffer);
    bool Load(SwString & buffer, wxTreeItemId id);
    void Search(SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId = true);
    void Search(swUI16 managerId, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl, bool addId = true);
    void Search(wxTreeItemId & start, SwStringCompareW & strcmpObj, wxListCtrl * listCtrl);
    wxTreeItemId Search(wxTreeItemId& start, swUI16 managerId, swUI16 pageId);
    wxTreeItemId SearchId(const char * id, swUI16 managerId);

    void OnLanguageChange();
    void OnThemeChange();

    SwStringArray & GetIds() { return m_ids; }
    bool HasFile(const char * bookId);
    const char * GetBookId();
    Swui8Array & GetCategories() { return m_categories; }
    bool HasCategory(swUI8 category);
    swUI8 GetCategory();
    void LoadBooks();
    void LoadBooksForGroup(swUI8 group);
    void LoadBooks(swUI8 cat);

    bool Open(const char * path);
    void Close();

protected:
    SwStringArray m_ids;
    Swui8Array    m_categories;
};

#endif // THMLTREECTRL_H
