///////////////////////////////////////////////////////////////////
// Name:        autodefbase.h
// Purpose:     Derived from SwRichTextCtrl, base class for
//              rich text windows with AutoDef functionality.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUTODEFBASE_H
#define AUTODEFBASE_H

#include "richtextctrlext.h"
#include "../controls/thmltreectrl.h"

class SwAutoDefBase : public SwRichTextCtrl
{
public:
    SwAutoDefBase();
    SwAutoDefBase(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
    virtual ~SwAutoDefBase();

    void EnableAutoDef(bool enable = true);
    bool InitAutoDefWin();
    void SetThMLTreeCtrl(SwThMLTreeCtrl * tree);
    virtual void OnUrlClick(const char * url, int top, int bottom);
    virtual void OnMouseHover(const char * data, swUI32 offSet, int top, int bottom);
    virtual void OnCaretChange(const char * data, swUI32 offSet, int top, int bottom);
    bool LoadAutoDefText(SwString & buffer, const char * data, swUI32 offSet, bool & canCopy);
    bool LoadAutoDefText(SwString & buffer, const char * data, bool & canCopy);
    bool WriteAutoDefText(const char * data, const char * basePath, bool canCopy, int top, int bottom);
    bool WriteAutoDefText(const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath, bool canCopy, int top, int bottom);
    static bool IsMouseInWindow(wxWindow *win);
    virtual void HideAutoDef();

protected:
    SwThMLTreeCtrl * m_multifilethmlTree;
    SwAutoDefBase *  m_autodefWindow;
    bool             m_autodefEnabled;
    static SwString  m_adbuffer;
};

#endif // AUTODEFBASE_H
