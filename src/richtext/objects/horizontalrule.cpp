///////////////////////////////////////////////////////////////////
// Name:        horizontalrule.cpp
// Purpose:     Horizontal Rule for SwRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/objects/horizontalrule.h"
#include "../../../include/richtext/richtextctrlext.h"
#include <wx/richtext/richtextxml.h>
#include <wx/xml/xml.h>
#include <wx/sstream.h>
#include <wx/dc.h>

IMPLEMENT_DYNAMIC_CLASS(SwHorizontalRule, wxRichTextObject)

SwHorizontalRule::SwHorizontalRule(wxRichTextObject* parent, wxRichTextAttr* charStyle):
    wxRichTextObject(parent)
{
    if (charStyle)
        SetAttributes(*charStyle);

    SetCachedSize(wxSize(100, 7));
}

SwHorizontalRule::SwHorizontalRule(const SwHorizontalRule& obj)
    : wxRichTextObject(obj)
{
    Copy(obj);
}

SwHorizontalRule::~SwHorizontalRule()
{
}

void SwHorizontalRule::Copy(const SwHorizontalRule& obj)
{
    wxRichTextObject::Copy(obj);
}

wxRichTextObject* SwHorizontalRule::Clone() const
{
    return new SwHorizontalRule(*this);
}

wxString SwHorizontalRule::GetXMLNodeName() const
{
    return L"horizontalrule";
}

bool SwHorizontalRule::IsFloatable() const
{
    return true;
}

bool SwHorizontalRule::Draw(wxDC& dc, wxRichTextDrawingContext& context, const wxRichTextRange& WXUNUSED(range), const wxRichTextSelection& selection, const wxRect& rect, int WXUNUSED(descent), int WXUNUSED(style))
{
    if (!IsShown() || !GetBuffer())
        return true;

    CalculateCacheSize(dc, rect.GetSize());
    wxRichTextAttr attr(GetAttributes());
    AdjustAttributes(attr, context);

    DrawBoxAttributes(dc, GetBuffer(), attr, wxRect(rect.GetPosition(), GetCachedSize()));
    wxRect margin(rect), border, content, padding, outline;
    GetBoxRects(dc, GetBuffer(), attr, margin, border, content, padding, outline);

    wxBrush dcBrush = dc.GetBrush();
    wxBrush attrBrush = wxBrush(attr.GetTextColour());
    dc.SetBrush(attrBrush);
    wxPen dcPen = dc.GetPen();
    wxPen attrPen = wxPen(attr.GetTextColour());
    dc.SetPen(attrPen);
    dc.DrawRectangle(content.x, content.y, GetCachedSize().GetWidth(), GetCachedSize().GetHeight());
    dc.FloodFill(content.x, content.y, attr.GetTextColour());

    if (selection.WithinSelection(GetRange().GetStart(), this))
    {
        dc.SetBrush(*wxBLUE_BRUSH);
        dc.SetPen(*wxBLUE_PEN);
        dc.SetLogicalFunction(wxXOR);
        dc.DrawRectangle(content.x, content.y, GetCachedSize().GetWidth(), GetCachedSize().GetHeight());
        dc.SetLogicalFunction(wxCOPY);
    }

    dc.SetBrush(dcBrush);
    dc.SetPen(dcPen);

    return true;
}

bool SwHorizontalRule::Layout(wxDC& dc, wxRichTextDrawingContext& context, const wxRect& rect, const wxRect& WXUNUSED(parentRect), int WXUNUSED(style))
{
    return true;
}

bool SwHorizontalRule::GetRangeSize(const wxRichTextRange& range, wxSize& size, int& WXUNUSED(descent), wxDC& dc, wxRichTextDrawingContext& context, int WXUNUSED(flags), const wxPoint& WXUNUSED(position), const wxSize& parentSize, wxArrayInt* partialExtents) const
{
    if (!range.IsWithin(GetRange()))
        return false;

    ((SwHorizontalRule*)this)->CalculateCacheSize(dc, parentSize);

    wxRichTextAttr attr(GetAttributes());
    ((wxRichTextObject*)this)->AdjustAttributes(attr, context);

    wxRect margin, border, content(wxPoint(0,0), GetCachedSize()), padding, outline;
    GetBoxRects(dc, GetBuffer(), attr, margin, border, content, padding, outline);

    size.x = wxMax(margin.GetSize().x, 7);
    size.y = wxMax(margin.GetSize().y, 1);

    if (partialExtents)
        partialExtents->Add(margin.GetSize().x);

    return true;
}

void SwHorizontalRule::CalculateCacheSize(wxDC& dc, const wxSize& parentSize)
{
    wxSize size;
    size.x = wxMax(1, parentSize.x);
    size.y = wxMax(1, parentSize.y);
    size.x = wxMax(size.x, GetCachedSize().x);
    size.y = wxMax(size.y, GetCachedSize().y);

    if (GetParent() && GetParent()->GetParent())
    {
        size.x = wxMax(size.x, GetParent()->GetParent()->GetCachedSize().x);
        size.y = wxMax(size.y, GetParent()->GetParent()->GetCachedSize().y);
    }

    if (GetBuffer() && GetParent() && GetParent()->GetParent())
    {
        wxRect margin, border, content, padding, outline;
        margin = wxRect(0, 0, size.x, size.y);
        GetBuffer()->GetBoxRects(dc, GetBuffer(), GetParent()->GetParent()->GetAttributes(), margin, border, content, padding, outline);
        size = content.GetSize();
    }

    size.x = wxMax(size.x, 1);
    size.y = wxMax(size.y, 1);

    if (GetBuffer())
    {
        wxTextAttrDimensionConverter cv(dc, GetBuffer() ? GetBuffer()->GetScale() : 1.0, size);
        size.x = wxMax(cv.GetPixels(GetAttributes().GetTextBoxAttr().GetWidth(), wxHORIZONTAL), 1);
        size.y = wxMax(cv.GetPixels(GetAttributes().GetTextBoxAttr().GetHeight(), wxVERTICAL), 1);
    }

    size.x = wxMax(size.x, 1);
    size.y = wxMax(size.y, 1);

    SetCachedSize(size);
}
