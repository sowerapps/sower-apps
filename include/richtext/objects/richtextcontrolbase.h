///////////////////////////////////////////////////////////////////
// Name:        richtextcontrolbase.h
// Purpose:     Base class for embeddable controls in RichTextCtrlExt.
// Copyright:   Original code for RichTextCtrlBase from wxRichTextImage
//              (c) Julian Smart, wxWidgets license.
//              Remaining code in this file (c) David Reynolds.
///////////////////////////////////////////////////////////////////

#ifndef RICHTEXTCONTROLBASE_H
#define RICHTEXTCONTROLBASE_H

#include <wx/richtext/richtextbuffer.h>
#include <wx/datectrl.h>
#include <wx/dirctrl.h>
#include <wx/spinctrl.h>
#include <wx/timectrl.h>
#include <wx/mediactrl.h>
#include <wx/treectrl.h>
#include <wx/srchctrl.h>
#include <wx/textctrl.h>
#include <wx/listctrl.h>
#include <wx/calctrl.h>
#include <wx/slider.h>
#include <wx/fontpicker.h>
#include <wx/filepicker.h>
#include <wx/animate.h>
#include <wx/clrpicker.h>
#include <wx/dataview.h>
#include "../../sowerbase.h"
#include "../../buffer/basicbuffer.h"
#include "../../html/html_controlattr.h"

class RichTextCtrlExt;


class SOWERBASEEXP RichTextControlBase: public wxRichTextObject
{
    DECLARE_DYNAMIC_CLASS(RichTextControlBase)
       public:
// Constructors

    /**
        Default constructor.

    */
    RichTextControlBase(wxRichTextObject* parent = NULL, wxRichTextAttr* charStyle = NULL);
    /**
        Copy constructor.
    */
    RichTextControlBase(const RichTextControlBase& obj);

    /**
        Destructor.
    */
    ~RichTextControlBase();

    /**
        Initialisation.
    */
    void Init();

// Overridables

    virtual bool Draw(wxDC& dc, wxRichTextDrawingContext& context, const wxRichTextRange& range, const wxRichTextSelection& selection, const wxRect& rect, int descent, int style);

    virtual bool Layout(wxDC& dc, wxRichTextDrawingContext& context, const wxRect& rect, const wxRect& parentRect, int style);

    virtual bool GetRangeSize(const wxRichTextRange& range, wxSize& size, int& descent, wxDC& dc, wxRichTextDrawingContext& context, int flags, const wxPoint& position = wxPoint(0,0), const wxSize& parentSize = wxDefaultSize, wxArrayInt* partialExtents = NULL) const;

    /**
        Returns the 'natural' size for this object - the image size.
    */
    virtual wxTextAttrSize GetNaturalSize() const;
    virtual bool IsEmpty() const;

    // Set this to true after providing a dialog for this purpose.
    virtual bool CanEditProperties() const;

    virtual bool EditProperties(wxWindow* parent, wxRichTextBuffer* buffer);

    virtual wxString GetPropertiesMenuLabel() const;
    virtual bool UsesParagraphAttributes() const;
    // This code comes out because I don't fully understand the expat license.
    //virtual bool ImportFromXML(wxRichTextBuffer* buffer, wxXmlNode* node, wxRichTextXMLHandler* handler, bool* recurse);
    virtual bool ExportXML(wxOutputStream& stream, int indent, wxRichTextXMLHandler* handler);
    virtual bool IsFloatable() const;
    virtual wxString GetXMLNodeName() const;
    void Copy(const RichTextControlBase& obj);
    virtual wxRichTextObject* Clone() const;
    virtual bool LoadImageCache(wxDC& dc, bool resetCache = false, const wxSize& parentSize = wxDefaultSize);
    wxRect GetScreenRect();
    void SetOwner(RichTextCtrlExt * ctrl);
    virtual void SetParent(wxRichTextObject *parent);
    virtual void CreateControl(wxRect * rect);
    virtual void SetControlAttributes(const HtmlControlAttributes& cattr);
    long GetId();
    void SetPrintState(bool state);
    bool GetPrintState();
    void InitControl();
    virtual int GetControlType();
    wxControl * GetControl(){return m_control;}
    bool ResolveFilePath(BasicBuffer & dest);
    bool TranslateValue(const char * value, BasicBuffer & dest, bool stripAmp = true);
    wxImageList * CreateImageList(bool normal = true);
    wxIcon GetIconFromPath(const char * path);
    void wxCheckSetBrush(wxDC& dc, const wxBrush& brush);
    void wxCheckSetPen(wxDC& dc, const wxPen& pen);

    wxControl *             m_control;
    HtmlControlAttributes   m_cattr;

    protected:

    bool                    m_printing;
    wxRect                  m_screenRect;
    RichTextCtrlExt *       m_owner;
    long                    m_controlId;
};

#endif // RICHTEXTCONTROLBASE_H
