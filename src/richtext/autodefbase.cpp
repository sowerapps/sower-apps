///////////////////////////////////////////////////////////////////
// Name:        autodefbase.cpp
// Purpose:     Derived from SwRichTextCtrl, base class for
//              rich text windows with AutoDef functionality.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/autodefbase.h"
#include "../../include/richtext/autodefwindow.h"
#include "../../include/bible/standard_bible.h"

SwString SwAutoDefBase::m_adbuffer;

SwAutoDefBase::SwAutoDefBase()
{
    m_autodefWindow = NULL;
    m_autodefEnabled = true;
    m_multifilethmlTree = NULL;
    m_adbuffer.Size(32768);
}

SwAutoDefBase::SwAutoDefBase(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwRichTextCtrl(parent, id, value, pos, size, style, validator, name)
{
    m_autodefWindow = NULL;
    m_autodefEnabled = true;
    m_multifilethmlTree = NULL;
    m_adbuffer.Size(32768);
}

SwAutoDefBase::~SwAutoDefBase()
{
}

void SwAutoDefBase::EnableAutoDef(bool enable)
{
    m_autodefEnabled = enable;
}

bool SwAutoDefBase::InitAutoDefWin()
{
    if (!m_autodefEnabled)
        return false;

    if (m_autodefWindow && m_autodefWindow->IsShown())
        return false;

    if (m_autodefWindow)
    {
        m_autodefWindow->Reset();
        return true;
    }

    m_autodefWindow = new SwAutoDefWindow(this, -1, "", wxPoint(0, 0), wxSize(0, 0));
    m_autodefWindow->Show(false);
    m_autodefWindow->SetSize(wxRect(this->GetSize()));
    m_autodefWindow->SetThMLTreeCtrl(m_multifilethmlTree);

    return true;
}

void SwAutoDefBase::SetThMLTreeCtrl(SwThMLTreeCtrl * tree)
{
    m_multifilethmlTree = tree;

    if (m_autodefWindow)
        m_autodefWindow->SetThMLTreeCtrl(m_multifilethmlTree);
}

void SwAutoDefBase::OnUrlClick(const char * url, int top, int bottom)
{
    bool canCopy = true;
    bool href = (bool) strstr(url, "href:#");
    SwString urlCpy, identifier;
    swUI32 offSet;
    char * p, * ip;
    swUI16 pos, id;

    if (m_multifilethmlTree && href)
    {
        urlCpy = url + 6;
        p = strchr(urlCpy, '-');

        ip = strstr(urlCpy, " identifier:");

        if (p)
        {
            *p = '\0';
        }

        if (ip)
        {
            *ip = '\0';
        }

        if (ip)
        {
            identifier = ip + 12;
            swUI16 mid = (swUI16) atoi(identifier);
            pos = SwApplicationInterface::GetThMLFileManager().FindByMID(mid);

            if (pos != NODE_ID_INVALID_16)
            {
                SwThMLFile * f = SwApplicationInterface::GetThMLFileManager().GetAt(pos);
                id = f->GetManagerId();
                if (SwApplicationInterface::GetThMLFileManager().LoadAutoDefPage(id, urlCpy, m_adbuffer))
                    WriteAutoDefText(m_adbuffer, m_adbuffer.Strlen(), true, &f->m_cssrules, f->GetBasePath(), true, top, bottom);

                if (p)
                {
                    *p = '-';

                    m_autodefWindow->GetParagraphList().HiliteParagraph(urlCpy);
                    m_autodefWindow->SetupScrollbars();
                    m_autodefWindow->GetParagraphList().ShowParagraph(urlCpy);
                }
            }
        }
    }
    else if (href)
    {
        urlCpy = url + 6;
        p = strchr(urlCpy, '-');

        ip = strstr(urlCpy, " identifier:");

        if (p)
        {
            *p = '\0';
        }

        if (ip)
        {
            *ip = '\0';
        }

        if (ip)
        {
            identifier = ip + 12;
            pos = SwApplicationInterface::GetModuleManager().FindById(identifier);

            if (pos != NODE_ID_INVALID_16)
            {
                id = SwApplicationInterface::GetModuleManager().GetAt(pos)->GetManagerId();
                if (SwApplicationInterface::GetModuleManager().LoadAutoDefPage(id, urlCpy, m_adbuffer, canCopy))
                    WriteAutoDefText(m_adbuffer, "", canCopy, top, bottom);

                if (p)
                {
                    *p = '-';

                    m_autodefWindow->GetParagraphList().HiliteParagraph(urlCpy);
                    m_autodefWindow->SetupScrollbars();
                    m_autodefWindow->GetParagraphList().ShowParagraph(urlCpy);
                }
            }
        }
    }
    else if (strstr(url, "scripref:"))
    {
        offSet = 0;
        urlCpy = url + 9;

        p = urlCpy.StrChr(':');

        if (p)
            offSet = p - urlCpy.GetArray();

        if (LoadAutoDefText(m_adbuffer, urlCpy, offSet, canCopy))
            WriteAutoDefText(m_adbuffer, "", canCopy, top, bottom);
    }
    else if (LoadAutoDefText(m_adbuffer, url, canCopy))
    {
        WriteAutoDefText(m_adbuffer, "", canCopy, top, bottom);
    }
}

void SwAutoDefBase::OnMouseHover(const char * data, swUI32 offSet, int top, int bottom)
{
    bool canCopy = true;

    if (!data || data[0] == '\0')
        return;

    if (LoadAutoDefText(m_adbuffer, data, offSet, canCopy))
        WriteAutoDefText(m_adbuffer, "", canCopy, top, bottom);
}

void SwAutoDefBase::OnCaretChange(const char * data, swUI32 offSet, int top, int bottom)
{
    bool canCopy = true;

    if (!data || data[0] == '\0')
        return;

    if (LoadAutoDefText(m_adbuffer, data, offSet, canCopy))
        WriteAutoDefText(m_adbuffer, "", canCopy, top, bottom);
}

bool SwAutoDefBase::LoadAutoDefText(SwString & buffer, const char * data, swUI32 offSet, bool & canCopy)
{
    if (!data || data[0] == '\0')
        return false;

    SwString c_data;
    SwStringW txt;
    c_data = data;
    txt.Copy(data);

    SwReferenceData refData;

    if (SwStandardBible::IdentifyReference(txt, offSet, refData))
    {
        if (refData.referenceType == REFERENCE_TYPE_STRONGS_HEBREW)
            return SwApplicationInterface::GetModuleManager().GetAutoDefData(buffer, refData.strongs, SYNC_TYPE_HEBREW, canCopy);
        else if (refData.referenceType == REFERENCE_TYPE_STRONGS_GREEK)
            return SwApplicationInterface::GetModuleManager().GetAutoDefData(buffer, refData.strongs, SYNC_TYPE_GREEK, canCopy);

        return SwApplicationInterface::GetModuleManager().GetAutoDefData(buffer, "",
                refData.book,
                refData.chapter,
                refData.verseStart,
                refData.verseEnd,
                canCopy);
    }
    else if (SwStandardBible::IdentifyChapterReference(txt, offSet, refData))
    {
        return SwApplicationInterface::GetModuleManager().GetAutoDefData(buffer, "",
                refData.book,
                refData.chapter,
                canCopy);
    }
    else
    {
        SwStandardBible::ParseTextEx(c_data, offSet);
        return SwApplicationInterface::GetModuleManager().GetAutoDefData(buffer, c_data.GetArray(), canCopy);
    }

    return false;
}

bool SwAutoDefBase::LoadAutoDefText(SwString & buffer, const char * data, bool & canCopy)
{
    if (!data || data[0] == '\0')
        return false;

    SwString txt;
    txt.Copy(data);

    if (SwApplicationInterface::GetModuleManager().GetAutoDefData(buffer, txt, canCopy))
    {
        return true;
    }

    return false;
}

bool SwAutoDefBase::WriteAutoDefText(const char * data, const char * basePath, bool canCopy, int top, int bottom)
{
    if (!InitAutoDefWin())
        return false;

    SwAutoDefWindow * win = (SwAutoDefWindow *) m_autodefWindow;
    win->WriteXmlText(data, true, basePath);
    win->SetCanCopy(canCopy);
    win->ShowAutoDef(top, bottom);

    return true;
}

bool SwAutoDefBase::WriteAutoDefText(const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath, bool canCopy, int top, int bottom)
{
    if (!InitAutoDefWin())
        return false;

    SwAutoDefWindow * win = (SwAutoDefWindow *) m_autodefWindow;
    win->WriteXmlText(source, length, thml, list, basePath);
    win->SetCanCopy(canCopy);
    win->ShowAutoDef(top, bottom);

    return true;
}

bool SwAutoDefBase::IsMouseInWindow(wxWindow *win)
{
    wxPoint pt = ::wxGetMousePosition();
    pt = win->ScreenToClient(pt);
    // wxRect rec = win->GetRect();
    wxRect rec = win->GetClientRect();

    return rec.Contains(pt);
}

void SwAutoDefBase::HideAutoDef()
{
    if (m_autodefWindow)
        m_autodefWindow->Show(false);
}

