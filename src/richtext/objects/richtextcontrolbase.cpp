///////////////////////////////////////////////////////////////////
// Name:        richtextcontrolbase.cpp
// Purpose:     Base class for embeddable controls in RichTextCtrlExt.
// Copyright:   Original code for RichTextCtrlBase from wxRichTextImage
//              (c) Julian Smart, wxWidgets license.
//              Remaining code in this file (c) David Reynolds.
///////////////////////////////////////////////////////////////////

#include "../../../include/richtext/objects/richtextcontrolbase.h"
#include "../../../include/richtext/richtextctrlext.h"
#include "../../../include/html/html_color.h"
#include "../../../include/dirpath/path.h"
#include "../../../include/apptools/toolbase.h"
#include <wx/richtext/richtextxml.h>
#include <wx/xml/xml.h>
#include <wx/sstream.h>
#include "../../../include/apptools/appdata.h"



IMPLEMENT_DYNAMIC_CLASS(RichTextControlBase, wxRichTextObject)

RichTextControlBase::RichTextControlBase(wxRichTextObject* parent, wxRichTextAttr* charStyle):
    wxRichTextObject(parent)
{
    Init();
    if (charStyle)
        SetAttributes(*charStyle);
}

RichTextControlBase::RichTextControlBase(const RichTextControlBase& obj)
    :wxRichTextObject(obj)
{
    Copy(obj);
}

RichTextControlBase::~RichTextControlBase()
{
    if (m_owner)
    {
        wxUint32 id = m_owner->m_controlList.FindControl(this);
        if (id != NODE_ID_INVALID)
            m_owner->m_controlList.DeleteControl(id);
    }

}

void RichTextControlBase::Init()
{
//    m_originalImageSize = wxSize(-1, -1);
    m_owner = NULL;
    m_control = NULL;
    m_printing = false;
}

/// Create a cached image at the required size
bool RichTextControlBase::LoadImageCache(wxDC& dc, bool resetCache, const wxSize& parentSize)
{
 //   if (!m_imageBlock.IsOk())
  //      return false;

    // If we have an original image size, use that to compute the cached bitmap size
    // instead of loading the image each time. This way we can avoid loading
    // the image so long as the new cached bitmap size hasn't changed.

    wxSize image(-1, -1);

    int width = 1;
    int height = 1;

    int parentWidth = 0;
    int parentHeight = 0;

    int maxWidth = -1;
    int maxHeight = -1;

    wxSize sz = parentSize;
    if (sz == wxDefaultSize)
    {
        if (GetParent() && GetParent()->GetParent())
            sz = GetParent()->GetParent()->GetCachedSize();
    }

    wxRichTextBuffer* buffer = GetBuffer();

    if (sz != wxDefaultSize)
    {
        if (buffer)
        {
            // Find the actual space available when margin is taken into account
            wxRect marginRect, borderRect, contentRect, paddingRect, outlineRect;
            marginRect = wxRect(0, 0, sz.x, sz.y);
            if (GetParent() && GetParent()->GetParent())
            {
                buffer->GetBoxRects(dc, buffer, GetParent()->GetParent()->GetAttributes(), marginRect, borderRect, contentRect, paddingRect, outlineRect);
                sz = contentRect.GetSize();
            }

            // Use a minimum size to stop images becoming very small
            parentWidth = wxMax(7, sz.GetWidth());
            parentHeight = wxMax(7, sz.GetHeight());

            if (buffer->GetRichTextCtrl())
                // Start with a maximum width of the control size, even if not specified by the content,
                // to minimize the amount of picture overlapping the right-hand side
                maxWidth = parentWidth;
        }
    }

    wxTextAttrDimensionConverter converter(dc, buffer ? buffer->GetScale() : 1.0, wxSize(parentWidth, parentHeight));

    if (GetAttributes().GetTextBoxAttr().GetWidth().IsValid() && GetAttributes().GetTextBoxAttr().GetWidth().GetValue() > 0)
    {
        int widthPixels = converter.GetPixels(GetAttributes().GetTextBoxAttr().GetWidth(), wxHORIZONTAL);
        if (widthPixels > 0)
            width = widthPixels;
    }

    // Limit to max width

    if (GetAttributes().GetTextBoxAttr().GetMaxSize().GetWidth().IsValid() && GetAttributes().GetTextBoxAttr().GetMaxSize().GetWidth().GetValue() > 0)
    {
        int mw = converter.GetPixels(GetAttributes().GetTextBoxAttr().GetMaxSize().GetWidth(), wxHORIZONTAL);

        // If we already have a smaller max width due to the constraints of the control size,
        // don't use the larger max width.
        if (mw > 0 && ((maxWidth == -1) || (mw < maxWidth)))
            maxWidth = mw;
    }

    if (maxWidth > 0 && width > maxWidth)
        width = maxWidth;

    // Preserve the aspect ratio
 //   if (width != m_originalImageSize.GetWidth())
 //       height = (int) (float(m_originalImageSize.GetHeight()) * (float(width)/float(m_originalImageSize.GetWidth()));

    if (GetAttributes().GetTextBoxAttr().GetHeight().IsValid() && GetAttributes().GetTextBoxAttr().GetHeight().GetValue() > 0)
    {
        int heightPixels = converter.GetPixels(GetAttributes().GetTextBoxAttr().GetHeight(), wxVERTICAL);
        if (heightPixels > 0)
            height = heightPixels;

        // Preserve the aspect ratio
  //      if (height != m_originalImageSize.GetHeight())
  //          width = (int) (float(m_originalImageSize.GetWidth()) * (float(height)/float(m_originalImageSize.GetHeight()));
    }

    // Limit to max height

    if (GetAttributes().GetTextBoxAttr().GetMaxSize().GetHeight().IsValid() && GetAttributes().GetTextBoxAttr().GetMaxSize().GetHeight().GetValue() > 0)
    {
        int mh = converter.GetPixels(GetAttributes().GetTextBoxAttr().GetMaxSize().GetHeight(), wxVERTICAL);
        if (mh > 0)
            maxHeight = mh;
    }

    if (maxHeight > 0 && height > maxHeight)
    {
        height = maxHeight;

        // Preserve the aspect ratio
      //  if (height != m_originalImageSize.GetHeight())
      //      width = (int) (float(m_originalImageSize.GetWidth()) * (float(height)/float(m_originalImageSize.GetHeight()));
    }

    // Prevent the use of zero size
    width = wxMax(1, width);
    height = wxMax(1, height);

    if (/*m_imageCache.IsOk() && */m_size.GetWidth() == width && m_size.GetHeight() == height)
    {
        // Do nothing, we didn't need to change the image cache
    }
    else
    {
        if (image.GetWidth() == -1)
        {
         /*   m_imageBlock.Load(image);
            if (!image.IsOk())
                return false;*/
                image.SetWidth(width);
                image.SetHeight(height);

        }

        if (image.GetWidth() == width && image.GetHeight() == height)
            m_size = image;
        else
        {
            // If the original width and height is small, e.g. 400 or below,
            // scale up and then down to improve image quality. This can make
            // a big difference, with not much performance hit.
          /*  int upscaleThreshold = 400;
            wxImage img;
            if (image.GetWidth() <= upscaleThreshold || image.GetHeight() <= upscaleThreshold)
            {
                img = image.Scale(image.GetWidth()*2, image.GetHeight()*2);
                img.Rescale(width, height, wxIMAGE_QUALITY_HIGH);
            }
            else
                img = image.Scale(width, height, wxIMAGE_QUALITY_HIGH);
            m_imageCache = wxBitmap(img);*/
            m_size.SetWidth(width);
            m_size.SetHeight(height);
        }
    }

    wxSize size;
    if (m_control)
        size = m_control->GetBestSize();

    if (m_control && m_cattr.GetUseBestSizeH())
    {
        m_size.SetHeight(size.GetHeight());
    }
    else if (m_cattr.GetHeightUnit() != UNIT_NONE)
    {
        m_size.SetHeight(m_cattr.GetHeight());
    }

    if (m_control && m_cattr.GetUseBestSizeW())
    {
        m_size.SetWidth(size.GetWidth());
    }
    else if (m_cattr.GetWidthUnit() != UNIT_NONE)
    {
        m_size.SetWidth(m_cattr.GetWidth());
    }

    if (m_control)
        size = m_control->GetBestSize();

    if (m_control && m_cattr.GetUseBestSizeH())
    {
        m_size.SetHeight(size.GetHeight());
    }
    else if (m_size.GetHeight() > maxHeight)
            m_size.SetHeight(maxHeight);

    if (m_control && m_cattr.GetUseBestSizeW())
    {
        m_size.SetWidth(size.GetWidth());
    }

    if (m_size.GetWidth() > maxWidth)
        m_size.SetWidth(maxWidth);

    return true;
}

/// Draw the item
bool RichTextControlBase::Draw(wxDC& dc, wxRichTextDrawingContext& context, const wxRichTextRange& WXUNUSED(range), const wxRichTextSelection& selection, const wxRect& rect, int WXUNUSED(descent), int WXUNUSED(style))
{
    /*
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
    */
    if (!IsShown())
    {
        if (m_control)
            m_control->Show(false);
        return true;
    }


     if (m_control)
         m_control->Show(true);

    if (!LoadImageCache(dc))
        return false;

    wxRichTextAttr attr(GetAttributes());
    AdjustAttributes(attr, context);

    DrawBoxAttributes(dc, GetBuffer(), attr, wxRect(rect.GetPosition(), GetCachedSize()));

    wxRect marginRect, borderRect, contentRect, paddingRect, outlineRect;
    marginRect = rect; // outer rectangle, will calculate contentRect
    GetBoxRects(dc, GetBuffer(), attr, marginRect, borderRect, contentRect, paddingRect, outlineRect);

    if (!m_owner && !m_printing)
    {
        wxRichTextCtrl * ctrl = NULL;
        ctrl = GetBuffer()->GetRichTextCtrl();
        if (ctrl)
            m_owner = wxDynamicCast(ctrl, RichTextCtrlExt);
    }

    if (!m_control && m_owner)
    {
        CreateControl(&contentRect);
        if (m_cattr.GetUseBestSizeH() || m_cattr.GetUseBestSizeW())
        {
            m_owner->PostSizeEvent();
            m_owner->Invalidate();
            m_owner->Update();
        }

    }

    if (m_control && !m_printing)
    {
        wxFloat32 scale = GetBuffer()->GetRichTextCtrl()->GetScale();
        wxPoint position;
        position.x = contentRect.x * scale;
        position.y = contentRect.y * scale;

        position = GetBuffer()->GetRichTextCtrl()->GetPhysicalPoint(position);
        m_control->SetSize(position.x + 1, position.y + 1, (contentRect.GetWidth() - 2) * scale, (contentRect.GetHeight() - 2) * scale);
        m_screenRect = contentRect;
    }

    if (m_control && m_printing)
    {
        wxRect rect = m_control->GetRect();
        wxWindowDC * win =   new wxWindowDC((wxWindow *)m_control);
        dc.StretchBlit(contentRect.x + 1, contentRect.y + 1, contentRect.GetWidth() - 2, contentRect.GetHeight() - 2, (wxDC*) win, 0, 0, rect.GetWidth(), rect.GetHeight());
        delete win;
    }

    if (selection.WithinSelection(GetRange().GetStart(), this))
    {
        wxCheckSetBrush(dc, *wxBLACK_BRUSH);
        wxCheckSetPen(dc, *wxBLACK_PEN);
        dc.SetLogicalFunction(wxINVERT);
        dc.DrawRectangle(contentRect);
        dc.SetLogicalFunction(wxCOPY);
    }

    return true;
}

/// Lay the item out
bool RichTextControlBase::Layout(wxDC& dc, wxRichTextDrawingContext& context, const wxRect& rect, const wxRect& WXUNUSED(parentRect), int WXUNUSED(style))
{
    if (!LoadImageCache(dc))
        return false;

    wxSize imageSize(m_size.GetWidth(), m_size.GetHeight());
    wxRect marginRect, borderRect, contentRect, paddingRect, outlineRect;
    contentRect = wxRect(wxPoint(0,0), imageSize);

    wxRichTextAttr attr(GetAttributes());
    AdjustAttributes(attr, context);

    GetBoxRects(dc, GetBuffer(), attr, marginRect, borderRect, contentRect, paddingRect, outlineRect);

    wxSize overallSize = marginRect.GetSize();

    SetCachedSize(overallSize);
    SetMaxSize(overallSize);
    SetMinSize(overallSize);
    SetPosition(rect.GetPosition());

    return true;
}

/// Get/set the object size for the given range. Returns false if the range
/// is invalid for this object.
bool RichTextControlBase::GetRangeSize(const wxRichTextRange& range, wxSize& size, int& WXUNUSED(descent), wxDC& dc, wxRichTextDrawingContext& context, int WXUNUSED(flags), const wxPoint& WXUNUSED(position), const wxSize& parentSize, wxArrayInt* partialExtents) const
{
    /*
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
    */
    if (!range.IsWithin(GetRange()))
        return false;

    if (!((RichTextControlBase*)this)->LoadImageCache(dc, false, parentSize))
    {
        size.x = 0; size.y = 0;
        if (partialExtents)
            partialExtents->Add(0);
        return false;
    }

    wxRichTextAttr attr(GetAttributes());
    ((wxRichTextObject*)this)->AdjustAttributes(attr, context);

    wxSize imageSize(m_size.GetWidth(), m_size.GetHeight());
    wxRect marginRect, borderRect, contentRect, paddingRect, outlineRect;
    contentRect = wxRect(wxPoint(0,0), imageSize);
    GetBoxRects(dc, GetBuffer(), attr, marginRect, borderRect, contentRect, paddingRect, outlineRect);

    wxSize overallSize = marginRect.GetSize();

    if (partialExtents)
        partialExtents->Add(overallSize.x);

    size = overallSize;

    return true;
}

// Get the 'natural' size for an object. For an image, it would be the
// image size.
wxTextAttrSize RichTextControlBase::GetNaturalSize() const
{
    wxTextAttrSize size;
//    if (GetImageCache().IsOk())
 //   {
        size.SetWidth(m_size.GetWidth(), wxTEXT_ATTR_UNITS_PIXELS);
        size.SetHeight(m_size.GetHeight(), wxTEXT_ATTR_UNITS_PIXELS);
 //   }
    return size;
}

bool RichTextControlBase::IsEmpty() const { return false;}

bool RichTextControlBase::CanEditProperties() const { return false; }
// This code comes out because I don't fully understand the expat license.
/*
bool RichTextControlBase::ImportFromXML(wxRichTextBuffer* buffer, wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse)
{
    wxRichTextObject::ImportFromXML(buffer, node, handler, recurse);

    wxString value = node->GetAttribute("cname", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetName(value.ToUTF8());
    }

    value = node->GetAttribute("cgroupname", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetGroup(value.ToUTF8());
    }

    value = node->GetAttribute("cvalue", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetValue(value.ToUTF8());
    }

    value = node->GetAttribute("cminvalue", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetMinValue(value.ToUTF8());
    }

    value = node->GetAttribute("cmaxvalue", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetMaxValue(value.ToUTF8());
    }

    value = node->GetAttribute("cformname", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetFormName(value.ToUTF8());
    }

    value = node->GetAttribute("cdatalistname", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetDataListName(value.ToUTF8());
    }

    value = node->GetAttribute("cimagelistname", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetImageListName(value.ToUTF8());
    }

    value = node->GetAttribute("cstateimagelistname", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetStateImageListName(value.ToUTF8());
    }

    value = node->GetAttribute("cfilter", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetFilter(value.ToUTF8());
    }

    value = node->GetAttribute("csource", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetSource(value.ToUTF8());
    }

    value = node->GetAttribute("chint", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetHint(value.ToUTF8());
    }

    value = node->GetAttribute("cstep", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetStep(value.ToUTF8());
    }

    value = node->GetAttribute("cbackgroundcolor", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetBackGroundColor(value.ToUTF8());
    }

    value = node->GetAttribute("ctextcolor", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetTextColor(value.ToUTF8());
    }

    value = node->GetAttribute("cstyle", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetStyle(wxAtol(value));
    }

    value = node->GetAttribute("cdisabled", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetDisabled(wxAtol(value));
    }

    value = node->GetAttribute("creadonly", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetReadOnly(wxAtol(value));
    }

    value = node->GetAttribute("crequired", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetRequired(wxAtol(value));
    }

    value = node->GetAttribute("cfocus", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetFocus(wxAtol(value));
    }

    value = node->GetAttribute("cusebestsizeh", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetUseBestSizeH(wxAtol(value));
    }

    value = node->GetAttribute("cusebestsizew", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetUseBestSizeH(wxAtol(value));
    }

    value = node->GetAttribute("cmute", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetMute(wxAtol(value));
    }

    value = node->GetAttribute("cautoplay", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetAutoPlay(wxAtol(value));
    }

    value = node->GetAttribute("cchecked", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetChecked(wxAtol(value));
    }

    value = node->GetAttribute("cmultiple", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetMultiple(wxAtol(value));
    }

    value = node->GetAttribute("ctype", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetType(value);
    }

    value = node->GetAttribute("cmaxlength", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetMaxLength(wxAtol(value));
    }

    value = node->GetAttribute("cusetheme", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetUseTheme(wxAtol(value));
    }

    value = node->GetAttribute("ctranslate", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetTranslate(wxAtol(value));
    }

    value = node->GetAttribute("cheight", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetHeight(value);
    }

    value = node->GetAttribute("cwidth", wxEmptyString);

    if (!value.empty())
    {
        m_cattr.SetWidth(value);
    }


    return true;
}
*/

bool RichTextControlBase::ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler)
{
    wxString style = handler->GetHelper().AddAttributes(GetAttributes(), false);

    handler->GetHelper().OutputIndentation(stream, indent);
    handler->GetHelper().OutputString(stream, "<");
    handler->GetHelper().OutputString(stream, GetXMLNodeName());
    handler->GetHelper().OutputString(stream, wxString::Format(" cname=\"%s\"", m_cattr.GetName()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cgroupname=\"%s\"", m_cattr.GetGroup()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cvalue=\"%s\"", m_cattr.GetValue()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cminvalue=\"%s\"", m_cattr.GetMinValue()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cmaxvalue=\"%s\"", m_cattr.GetMaxValue()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cformname=\"%s\"", m_cattr.GetFormName()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cdatalistname=\"%s\"", m_cattr.GetDataListName()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cimagelistname=\"%s\"", m_cattr.GetImageListName()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cstateimagelistname=\"%s\"", m_cattr.GetStateImageListName()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cfilter=\"%s\"", m_cattr.GetFilter()));
    handler->GetHelper().OutputString(stream, wxString::Format(" csource=\"%s\"", m_cattr.GetSource()));
    handler->GetHelper().OutputString(stream, wxString::Format(" chint=\"%s\"", m_cattr.GetHint()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cstep=\"%s\"", m_cattr.GetStep()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cbackgroundcolor=\"%s\"", m_cattr.GetBackGroundColor()));
    handler->GetHelper().OutputString(stream, wxString::Format(" ctextcolor=\"%s\"", m_cattr.GetTextColor()));


    handler->GetHelper().OutputString(stream, wxString::Format(" cstyle=\"%u\"", m_cattr.GetStyle()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cdisabled=\"%u\"", m_cattr.GetDisabled()));
    handler->GetHelper().OutputString(stream, wxString::Format(" creadonly=\"%u\"", m_cattr.GetReadOnly()));
    handler->GetHelper().OutputString(stream, wxString::Format(" crequired=\"%u\"", m_cattr.GetRequired()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cfocus=\"%u\"", m_cattr.GetFocus()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cusebestsizeh=\"%u\"", m_cattr.GetUseBestSizeH()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cusebestsizew=\"%u\"", m_cattr.GetUseBestSizeW()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cmute=\"%u\"", m_cattr.GetMute()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cautoplay=\"%u\"", m_cattr.GetAutoPlay()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cchecked=\"%u\"", m_cattr.GetChecked()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cmultiple=\"%u\"", m_cattr.GetMultiple()));
    handler->GetHelper().OutputString(stream, wxString::Format(" ctype=\"%s\"", m_cattr.GetTypeStr()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cmaxlength=\"%u\"", m_cattr.GetMaxLength()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cusetheme=\"%u\"", m_cattr.GetUseTheme()));
    handler->GetHelper().OutputString(stream, wxString::Format(" ctranslate=\"%u\"", m_cattr.GetTranslate()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cheight=\"%s\"", m_cattr.GetHeightStr()));
    handler->GetHelper().OutputString(stream, wxString::Format(" cwidth=\"%s\"", m_cattr.GetWidthStr()));


    handler->GetHelper().OutputString(stream, style);
    handler->GetHelper().OutputString(stream, ">");

    if (GetProperties().GetCount() > 0)
    {
        handler->GetHelper().WriteProperties(stream, GetProperties(), indent);
        handler->GetHelper().OutputIndentation(stream, indent);
    }

    handler->GetHelper().OutputIndentation(stream, indent);
    handler->GetHelper().OutputString(stream, "</");
    handler->GetHelper().OutputString(stream, GetXMLNodeName());
    handler->GetHelper().OutputString(stream, ">");

    return true;
}
/// Copy
void RichTextControlBase::Copy(const RichTextControlBase& obj)
{
    wxRichTextObject::Copy(obj);
    m_cattr.Copy(obj.m_cattr);
//    m_originalImageSize = obj.m_originalImageSize;
    m_owner = NULL;
    m_screenRect = obj.m_screenRect;

    m_printing = obj.m_printing;
    if (m_printing)
        m_control = obj.m_control;
    else
        m_control = NULL;
}

/// Edit properties via a GUI
bool RichTextControlBase::EditProperties(wxWindow* parent, wxRichTextBuffer* buffer)
{
    return false;
}

wxString RichTextControlBase::GetPropertiesMenuLabel() const { return "ControlBase"; }

bool RichTextControlBase::UsesParagraphAttributes() const { return false; }

bool RichTextControlBase::IsFloatable() const { return true; }

wxRichTextObject* RichTextControlBase::Clone() const { return new RichTextControlBase(*this); }

wxString RichTextControlBase::GetXMLNodeName() const { return "RichTextControlBase"; }

void RichTextControlBase::SetParent(wxRichTextObject *parent)
{
    wxRichTextObject::SetParent(parent);
}

void RichTextControlBase::CreateControl(wxRect * rect){m_controlId = wxNewId();}

wxRect RichTextControlBase::GetScreenRect() {return m_screenRect;}

long RichTextControlBase::GetId() {return m_controlId;}

bool RichTextControlBase::GetPrintState(){return m_printing;}

int RichTextControlBase::GetControlType(){return 0;}

void RichTextControlBase::SetOwner(RichTextCtrlExt * ctrl){m_owner = ctrl;}

void RichTextControlBase::SetControlAttributes(const HtmlControlAttributes& cattr)
{
    m_cattr.Copy(cattr);
}

void RichTextControlBase::InitControl()
{
    if (m_cattr.GetDisabled())
        m_control->Enable(false);

    if (!wxIsEmpty(m_cattr.GetBackGroundColor()))
    {
        m_control->SetBackgroundColour(HtmlColor::GetBGR(m_cattr.GetBackGroundColor32Bit()));
    }

    if (!wxIsEmpty(m_cattr.GetTextColor()))
    {
        m_control->SetForegroundColour(HtmlColor::GetBGR(m_cattr.GetTextColor32Bit()));
    }
}

void RichTextControlBase::SetPrintState(bool state)
{
    m_printing = state;
}

bool RichTextControlBase::ResolveFilePath(BasicBuffer & dest)
{
    BasicBuffer relative;
    wxUint32 pathLen = strlen(m_cattr.GetSource() + 1);

    dest.SizeBuffer(1);
    dest.SetAt(0, '\0');

    if (pathLen < 3)
        return false;

    if (!Path::IsPathRelative(m_cattr.GetSource()))
    {
        if (!dest.SizeBuffer(pathLen))
            return false;

        strcpy((char *) dest, m_cattr.GetSource());
        return true;
    }

    if (!relative.SizeBuffer(pathLen))
            return false;

    strcpy((char *) relative, m_cattr.GetSource());

    int docpathLen = 0;

    if (m_owner)
        docpathLen = strlen(m_owner->GetBasePath());

    pathLen = strlen((char *) relative) + 1;
    pathLen += docpathLen;

    if (!dest.SizeBuffer(pathLen))
        return false;

    if (!docpathLen)
    {
        strcpy((char *) dest, (char *) relative);
        return true;
    }


    Path::MakePathFromRelative(m_owner->GetBasePath(), (char *) relative, (char *) dest, pathLen);
    return true;
}

bool RichTextControlBase::TranslateValue(const char * value, BasicBuffer & dest, bool stripAmp)
{
    if (!value)
        return false;

    if (!dest.SizeBuffer(strlen(value) + 1))
        return false;

    dest.SetAt(0, '\0');

    strcpy((char *) dest, value);

    if (!m_cattr.GetTranslate())
        return true;

    SowerAppData::GetLanguage().GetTable().GetTranslatedString(value, dest, stripAmp, false);

    return true;
}

wxImageList * RichTextControlBase::CreateImageList(bool normal)
{
    BasicBuffer buffer;
    wxUint32 id;

    if (normal)
        id = m_owner->m_datalistArray.FindDataList(m_cattr.GetImageListName());
    else
        id = m_owner->m_datalistArray.FindDataList(m_cattr.GetStateImageListName());

    wxImageList * ilist = new wxImageList;
    if (id != NODE_ID_INVALID)
    {
        HtmlDataList * dlo = m_owner->m_datalistArray.GetDataList(id);

        wxUint32 pos = 0;
        DataItem * data;
        wxIcon i;
        for(;;)
        {
            data = dlo->GetListItemData(pos);
            if (!data)
                break;
            buffer.SizeBuffer(strlen(data->GetValue() + 1));
            strcpy((char *) buffer, data->GetValue());
            if (ResolveFilePath(buffer) && wxFile::Exists((char *)buffer))
            {
                i = GetIconFromPath((char *) buffer);
                if (i.IsOk())
                    ilist->Add(i);
            }

            pos ++;
        }
    }

    return ilist;
}

wxIcon RichTextControlBase::GetIconFromPath(const char * path)
{
    wxBitmap bitmap;
    wxIcon i;

    if (bitmap.LoadFile(path, wxBITMAP_TYPE_ANY))
    {
        i.CopyFromBitmap(bitmap);
        return i;
    }

    return i;
}

void RichTextControlBase::wxCheckSetBrush(wxDC& dc, const wxBrush& brush)
{
    const wxBrush& brush1 = dc.GetBrush();
    if (brush1.IsOk() && brush.IsOk())
    {
        if (brush1.GetStyle() == brush.GetStyle() &&
            brush1.GetColour() == brush.GetColour())
            return;
    }
    dc.SetBrush(brush);
}

void RichTextControlBase::wxCheckSetPen(wxDC& dc, const wxPen& pen)
{
    const wxPen& pen1 = dc.GetPen();
    if (pen1.IsOk() && pen.IsOk())
    {
        if (pen1.GetWidth() == pen.GetWidth() &&
            pen1.GetStyle() == pen.GetStyle() &&
            pen1.GetColour() == pen.GetColour())
            return;
    }
    dc.SetPen(pen);
}

/*
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
}*/
