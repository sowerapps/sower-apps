///////////////////////////////////////////////////////////////////
// Name:        horizontalrule.h
// Purpose:     Horizontal Rule for SwRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HORIZONTALRULE_H
#define HORIZONTALRULE_H

#include "../../sowerbase.h"
#include <wx/richtext/richtextbuffer.h>
#include <wx/richtext/richtextxml.h>

class SOWERBASEEXP SwHorizontalRule : public wxRichTextObject
{
    DECLARE_DYNAMIC_CLASS(SwHorizontalRule)
public:
    SwHorizontalRule(wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
    SwHorizontalRule(const SwHorizontalRule& obj);
    ~SwHorizontalRule();

    void Copy(const SwHorizontalRule& obj);
    virtual wxRichTextObject* Clone() const;
    virtual wxString GetXMLNodeName() const;
    virtual bool IsFloatable() const;

    virtual bool Draw(wxDC& dc, wxRichTextDrawingContext& context, const wxRichTextRange& range, const wxRichTextSelection& selection, const wxRect& rect, int descent, int style);
    virtual bool Layout(wxDC& dc, wxRichTextDrawingContext& context, const wxRect& rect, const wxRect& parentRect, int style);
    virtual bool GetRangeSize(const wxRichTextRange& range, wxSize& size, int& descent, wxDC& dc, wxRichTextDrawingContext& context, int flags, const wxPoint& position = wxPoint(0,0), const wxSize& parentSize = wxDefaultSize, wxArrayInt* partialExtents = NULL) const;
    virtual void CalculateCacheSize(wxDC& dc, const wxSize& parentSize);
};

#endif // HORIZONTALRULE_H
