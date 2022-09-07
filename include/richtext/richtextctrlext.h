///////////////////////////////////////////////////////////////////
// Name:        richtextctrlext.h
// Purpose:     SwRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef RICHTEXTCTRLEXT_H
#define RICHTEXTCTRLEXT_H

#include "../sowerbase.h"
#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextprint.h>
#include "../../include/html/html_anchor.h"
#include "objects/horizontalrule.h"
#include <wx/mstream.h>
#include "../sdf/datafile.h"
#include "objects/paragraphlist.h"
#include "../css/css_file.h"

class SwRichTextCtrl;

class SOWERBASEEXP SwRichTimer : public wxTimer
{
public:
    SwRichTimer();
    virtual ~SwRichTimer();
    virtual void Notify();
    SwRichTextCtrl * m_rich;
};

class SwHorizontalRule;
class SOWERBASEEXP SwRichTextCtrl : public wxRichTextCtrl
{
    DECLARE_DYNAMIC_CLASS(SwRichTextCtrl)
public:
    SwRichTextCtrl();
    SwRichTextCtrl(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwRichTextCtrl();

    // Mouse movement and timer - richtextctrlext.cpp
    virtual bool ProcessMouseMovement(wxRichTextParagraphLayoutBox* container, wxRichTextObject* obj, long position, const wxPoint& pos);
    virtual void OnTimer(bool flag);

    virtual void SetBaseStyle() {}
    bool NewlineEx();
    // Called when a url has been clicked.
    virtual void OnUrlClick(const char * url, int top, int bottom) {}
    // Called when the mouse has hovered over text.
    virtual void OnMouseHover(const char * data, swUI32 offSet, int top, int bottom) {}
    // Called when a caret position has changed.
    virtual void OnCaretChange(const char * data, swUI32 offSet, int top, int bottom) {}
    // Called when AutoDef windows should be hidden.
    virtual void HideAutoDef() {}

    // Anchors - anchor.cpp
    void OnAnchor(wxCommandEvent& event);
    int GetAnchorList(wxListCtrl * listBox);
    void JumpToAnchorPosition(swUI32 id);
    void JumpToAnchorPosition(const wchar_t * name);

    // Url - url.cpp
    virtual void OnThisRichTextUrl(wxTextUrlEvent& event);

    // Event binding - binding.cpp
    void BindCtrl();
    void UnbindCtrl();

    // Commands - command.cpp
    SwHtmlAnchor & GetAnchors();
    SwParagraphList & GetParagraphList();
    void Init();
    void SetBaseFont();
    void Reset();
    virtual void OnSizeWin(wxSizeEvent& event)
    {
        event.Skip();
    }
    virtual void OnScrollWin(wxScrollWinEvent& event)
    {
        event.Skip();
    }
    void OnInsertImage(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnPrintPreview(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnCut(wxCommandEvent& event);
    virtual void Copy() { wxCommandEvent event; OnCopy(event); }
    void OnCopy(wxCommandEvent& event);
    void OnCopyHtml(wxCommandEvent& event);
    void OnPaste(wxCommandEvent& event);
    void OnSelectAll(wxCommandEvent& event);
    bool CanClose();
    void OnOpen(wxCommandEvent& event);
    void OnClose(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    bool SaveAs();
    void OnSaveAs(wxCommandEvent& event);
    void ClearAll();
    void SetBasePath(const char * path);
    char * GetBasePath();
    void SetCanCopy(bool canCopy);
    bool GetCanCopy();
    virtual void OnFind(wxCommandEvent& event);
    virtual void OnReplace(wxCommandEvent& event);
    virtual bool EditProperties (wxRichTextObject *obj, wxWindow *parent);
    virtual bool CanCopy();

    // Events - events.cpp
    virtual void OnThisRichTextLeftClick(wxRichTextEvent& event);
    virtual void OnThisRichTextRightClick(wxRichTextEvent& event);
    virtual void OnThisRichTextMiddleClick(wxRichTextEvent& event);
    virtual void OnThisRichTextLeftDClick(wxRichTextEvent& event);
    virtual void OnThisRichTextReturn(wxRichTextEvent& event);
    virtual void OnThisRichTextCharacter(wxRichTextEvent& event);
    virtual void OnThisRichTextDelete(wxRichTextEvent& event);
    virtual void OnThisRichTextSelectionChanged(wxRichTextEvent& event);
    virtual void OnThisRichTextFocusObjectChanged(wxRichTextEvent& event);
    virtual void OnThisRichTextText(wxCommandEvent& event);
    virtual void OnThisRichTextTextEnter(wxCommandEvent& event);

    // Style - style.cpp
    void OnFont(wxCommandEvent& event);
    void OnFontSizeIncrease(wxCommandEvent& event);
    void OnFontSizeDecrease(wxCommandEvent& event);
    void OnBold(wxCommandEvent& event);
    void OnItalic(wxCommandEvent& event);
    void OnUnderLine(wxCommandEvent& event);
    void OnStrikeThrough(wxCommandEvent& event);
    void OnBaseLine(wxCommandEvent& event);
    void OnSuperScript(wxCommandEvent& event);
    void OnSubScript(wxCommandEvent& event);
    void OnCapitalize(wxCommandEvent& event);
    void OnAlignLeft(wxCommandEvent& event);
    void OnAlignCenter(wxCommandEvent& event);
    void OnAlignRight(wxCommandEvent& event);
    void OnAlignTop(wxCommandEvent& event);
    void OnAlignMiddle(wxCommandEvent& event);
    void OnAlignBottom(wxCommandEvent& event);
    void OnLineSpacing1(wxCommandEvent& event);
    void OnLineSpacing15(wxCommandEvent& event);
    void OnLineSpacing2(wxCommandEvent& event);
    void OnIndentMore(wxCommandEvent& event);
    void OnIndentLess(wxCommandEvent& event);
    void OnTextColor(wxCommandEvent& event);
    void OnBackgroundColor(wxCommandEvent& event);
    void OnBulletedList(wxCommandEvent& event);
    void OnArabicList(wxCommandEvent& event);
    void OnRomanListUpper(wxCommandEvent& event);
    void OnRomanListLower(wxCommandEvent& event);
    void OnAlphaListUpper(wxCommandEvent& event);
    void OnAlphaListLower(wxCommandEvent& event);

    // Write functions for ThML, Html, etc. using
    // SwRichTextInterface.
    void WriteXmlText(const char * source, bool thml,  const char * basePath);
    void WriteXmlText(const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath);

    // Embedded Controls - objectwrite.cpp
    static void RegisterHandlers();
    // Write functions - objectwrite.cpp
    SwHorizontalRule * WriteHorizontalRule(wxRichTextAttr& textAttr);

    virtual void OnLanguageChange() {}
    virtual void OnThemeChange() {}

    SwHtmlAnchor m_anchor;
    SwParagraphList m_paragraphList;

protected:
    wxString           m_adText;
    swUI32             m_adOffset;
    swUI32             m_adTextLen;
    wxRect             m_adCaret;
    wxPoint            m_adClientPos;
    wxPoint            m_adAbsolutePos;
    bool               m_canCopy;
    wxCursor           m_arrowCursor;
    wxPoint            m_lastmousePos;
    long               m_mouseCount;
    long               m_lastcaretPos;
    SwRichTimer          m_richTimer;
    wxRichTextPrinting m_printing;
    SwString           m_base;
    long               m_textPos;
};

#endif // RICHTEXTCTRLEXT_H
