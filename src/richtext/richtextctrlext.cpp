///////////////////////////////////////////////////////////////////
// Name:        richtextctrlext.cpp
// Purpose:     SwRichTimer, process mouse movement.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"
#include "../../include/appi/appifa.h"

SwRichTimer::SwRichTimer()
{
    m_rich = NULL;
    Start(100);
}

SwRichTimer::~SwRichTimer()
{
}

void SwRichTimer::Notify()
{
    if (m_rich)
        m_rich->OnTimer(false);
}

IMPLEMENT_DYNAMIC_CLASS(SwRichTextCtrl, wxRichTextCtrl)

SwRichTextCtrl::SwRichTextCtrl()
{
    Init();
}

SwRichTextCtrl::SwRichTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :wxRichTextCtrl(parent, id, value, pos, size, style, validator, name)
{
    Init();
}

SwRichTextCtrl::~SwRichTextCtrl()
{
    UnbindCtrl();
}

bool SwRichTextCtrl::ProcessMouseMovement(wxRichTextParagraphLayoutBox* container, wxRichTextObject* WXUNUSED(obj), long position, const wxPoint& WXUNUSED(pos))
{
    wxRichTextAttr attr;
    wxPoint mousePos = wxGetMousePosition();
    m_adClientPos = ScreenToClient(mousePos);
    long pos, start, end;

    if (container)
    {
        wxClientDC dc(this);
        PrepareDC(dc);
        dc.SetFont(GetFont());
        wxRichTextObject* hitObj = NULL;
        wxRichTextObject* contextObj = NULL;
        wxRichTextDrawingContext context(& GetBuffer());
        int hit = GetBuffer().HitTest(dc, context, GetUnscaledPoint(GetLogicalPoint(m_adClientPos)), pos, & hitObj, & contextObj, wxRICHTEXT_HITTEST_HONOUR_ATOMIC);

        if (hit != wxTE_HT_UNKNOWN)
        {
            if (hitObj->GetParent() && pos - 30 < hitObj->GetParent()->GetRange().GetStart())
            {
                m_adOffset = pos - hitObj->GetParent()->GetRange().GetStart();
                start = hitObj->GetParent()->GetRange().GetStart();
            }
            else
            {
                m_adOffset = 30;
                start = pos - 30;
            }

            end = pos + 20;

            /*
               if (end > hitObj->GetRange().GetEnd())
                   end = hitObj->GetRange().GetEnd();
            */
            m_adText = contextObj->GetTextForRange(wxRichTextRange(start, end));
            m_adTextLen = m_adText.Len();
            GetCaretPositionForIndex(pos, m_adCaret, container);
            m_adTextPos = pos;
        }
    }

    if (container && GetStyle(position, attr, container))
    {
        if (attr.HasFlag(wxTEXT_ATTR_URL))
        {
            SetCursor(m_urlCursor);
            return true;
        }
    }

    SetCursor(m_textCursor);
    return false;
}

void SwRichTextCtrl::OnTimer(bool flag)
{
    long caretPos = GetCaretPosition();
    long start, end;
    swUI32 offSet = 0;

    if (!SwAutoDefBase::IsMouseInWindow(this) || !IsShownOnScreen())
        return;

    if (caretPos != m_lastcaretPos && HasFocus())
    {
        // Caret position has changed. Use text at caret for
        // AutoDef data, and position.
        HideAutoDef();
        m_caretFlag = true;
        m_lastcaretPos = caretPos;
        m_mouseCount = 0;
    }
    else if (m_caretFlag && caretPos == m_lastcaretPos && HasFocus())
    {
        if (m_mouseCount < 7)
        {
            m_mouseCount ++;
            return;
        }
        if (caretPos - 30 < 0)
        {
            offSet = caretPos;
            start = 0;
        }
        else
        {
            offSet = 30;
            start = caretPos - 30;
        }

        end = caretPos + 20;

        GetCaretPositionForIndex(caretPos, m_adCaret);
        m_adClientPos.x = m_adCaret.x;
        m_adClientPos.y = m_adCaret.y;
        m_adClientPos = GetScaledPoint(m_adClientPos);
        m_adClientPos = GetPhysicalPoint(m_adClientPos);
        if (!m_urlClicked)
            OnCaretChange(GetRange(start, end), offSet, m_adClientPos.y - 1, m_adClientPos.y + (m_adCaret.GetHeight()) + 1);

        m_lastcaretPos = caretPos;
        m_urlClicked = false;
        m_caretFlag = false;
        return;
    }

    if (m_adClientPos == m_lastmousePos && m_adTextLen < 52)
    {
        m_mouseCount ++;
        if (m_mouseCount >= 7)
        {
            GetCaretPositionForIndex(m_adTextPos, m_adCaret);
            m_adClientPos.x = m_adCaret.x;
            m_adClientPos.y = m_adCaret.y;
            m_adClientPos = GetScaledPoint(m_adClientPos);
            m_adClientPos = GetPhysicalPoint(m_adClientPos);
            OnMouseHover(m_adText.utf8_str(), m_adOffset, m_adClientPos.y - 1, m_adClientPos.y + (m_adCaret.GetHeight() + 1));
        }

        return;
    }
    else
    {
        m_mouseCount = 0;
        m_lastmousePos = m_adClientPos;
    }
}

bool SwRichTextCtrl::NewlineEx()
{
    return GetFocusObject()->InsertNewlineWithUndo(& GetBuffer(), m_caretPosition+1, this, wxTEXT_ATTR_KEEP_FIRST_PARA_STYLE);
}
