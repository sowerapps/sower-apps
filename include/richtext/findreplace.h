///////////////////////////////////////////////////////////////////
// Name:        findreplace.h
// Purpose:     Find/Replace functionality for wxRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef FINDREPLACE_H
#define FINDREPLACE_H

#include "../sowerbase.h"
#include "../array/textrangearray.h"
#include "../framework/panel.h"
#include <wx/richtext/richtextctrl.h>
#include <wx/dynarray.h>

WX_DEFINE_ARRAY_LONG(long, LongArray);

class SOWERBASEEXP SwFindReplace
{
public:
    SwFindReplace();
    virtual ~SwFindReplace();
    void SetParent(wxRichTextCtrl * rich);
    void SetFindText(wxString text);
    void SetReplaceText(wxString text);
    void SetCaseSensitive(bool caseSensitive = true);
    void SetWholeWordOnly(bool wholewordOnly = false);
    void SetScrollView(bool scrollView = true);
    void SetFindAll(bool findAll);
    void Reset();
    bool IterateBuffer(wxRichTextCompositeObject * obj = NULL);
    bool IterateObj(wxRichTextCompositeObject * obj);
    bool OnText(wxRichTextObject * obj);
    void OnLayoutBox(wxRichTextParagraphLayoutBox * obj);
    void OnParagraph(wxRichTextParagraph * obj);
    int FindWord();
    bool Find(wxString text, bool casesensitive, bool wholewordonly);
    bool FindNext();
    void Replace();
    void ReplaceAll();
    bool Hilite(const wchar_t * str, bool casesensitive, bool wholewordonly);
    void HiliteFoundList();

protected:
    wxRichTextCtrl *                m_rich;
    wxRichTextParagraphLayoutBox *  m_topParent;
    wxRichTextParagraph *           m_parent;
    wxRichTextObject *              m_found;
    long                            m_endofFind;
    wxString                        m_findTextOriginal;
    wxString                        m_findText;
    wxString                        m_replaceText;
    long                            m_findtextLength;
    long                            m_replacetextLength;
    wxString                        m_collection;
    wxString                        m_collectionLwr;
    LongArray                       m_rangeData;
    bool                            m_ignoreCase;
    bool                            m_wholewordOnly;
    bool                            m_continue;
    bool                            m_replaceAll;
    bool                            m_scrollView;
    bool                            m_findAll;
    SwTextRangeArray                m_foundList;
    bool                            m_break;
    long                            m_currentFind;
    long                            m_previousFind;
};

#endif // FINDREPLACE_H
