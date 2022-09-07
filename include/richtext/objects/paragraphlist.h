///////////////////////////////////////////////////////////////////
// Name:        paragraphlist.h
// Purpose:     List for sections of text written to a wxRichTextCtrl.
//              Storing xml id, begin position, and extent so that it is
//              possible to scroll to, and/or hilite a specific section
//              specified by it's xml id.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef PARAGRAPHLIST_H
#define PARAGRAPHLIST_H

#include "../../sowerbase.h"
#include "../../html/parserbase.h"
#include <wx/richtext/richtextctrl.h>

class SOWERBASEEXP SwParagraphList : public SwParserBase
{
public:
    SwParagraphList();
    virtual ~SwParagraphList();

    bool HiliteParagraph(const char * id);
    bool SelectParagraph(const char * id);
    bool ShowParagraph(const char * id);
    bool SetCaretAtParagraph(const char * id);
    swUI32 FindParagraph(const char * id);
    swUI32 GetParagraphExtent(swUI32 node);
    void SetView(wxRichTextCtrl * rich);

protected:
    wxRichTextCtrl * m_rich;
};

#endif // PARAGRAPHLIST_H
