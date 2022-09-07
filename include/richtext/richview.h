///////////////////////////////////////////////////////////////////
// Name:        richview.h
// Purpose:     Derived from SwAutoDefBase, it is read only by
//              default, and extends processing for AutoDef
//              functionality.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef RICHVIEW_H
#define RICHVIEW_H

#include "richtextctrlext.h"
#include "autodefbase.h"
#include "autodefwindow.h"
#include "../controls/thmltreectrl.h"
#include "findreplace.h"
#include "../framework/menubar.h"

class SwMenu;
class SOWERBASEEXP SwRichView : public SwAutoDefBase
{
    public:
        SwRichView();
        SwRichView(wxWindow *parent, wxWindowID id=-1, const wxString &value=wxEmptyString, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxRE_MULTILINE, const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTextCtrlNameStr);
        virtual ~SwRichView();

        void SetViewMenu(SwMenu * viewMenu);
        virtual void SetBaseStyle();
        SwFindReplace & GetFindReplace() { return m_findReplace; }
        virtual bool ShowContextMenu(wxMenu *menu, const wxPoint &pt, bool addPropertyCommands);

        virtual void OnLanguageChange();
        virtual void OnThemeChange();

    private:
        SwFindReplace     m_findReplace;
        SwMenu *     m_viewMenu;
};

#endif // RICHVIEW_H
