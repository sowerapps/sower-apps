///////////////////////////////////////////////////////////////////
// Name:        richview.cpp
// Purpose:     Derived from SwRichTextCtrl, it is read only by
//              default, and extends processing for AutoDef
//              functionality.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richview.h"
#include "../../include/appi/appifa.h"

SwRichView::SwRichView()
{
    m_viewMenu = NULL;
    m_findReplace.SetParent(this);
    InitAutoDefWin();
}

SwRichView::SwRichView(wxWindow *parent, wxWindowID id, const wxString &value, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
:SwAutoDefBase(parent, id, value, pos, size, style, validator, name)
{
    m_viewMenu = NULL;
    m_findReplace.SetParent(this);
    InitAutoDefWin();
}

SwRichView::~SwRichView()
{
}

void SwRichView::SetViewMenu(SwMenu * viewMenu)
{
    m_viewMenu = viewMenu;
}

void SwRichView::SetBaseStyle()
{
    wxRichTextAttr attr;
    attr.SetFontSize(SwApplicationInterface::GetReaderFontSize());
    SetDefaultStyle(attr);
}

bool SwRichView::ShowContextMenu(wxMenu *menu, const wxPoint &pt, bool addPropertyCommands)
{
    if (m_viewMenu)
        return wxRichTextCtrl::ShowContextMenu(m_viewMenu, pt, false);

    return wxRichTextCtrl::ShowContextMenu(menu, pt, addPropertyCommands);
}

void SwRichView::OnLanguageChange()
{
    if (m_viewMenu)
        m_viewMenu->OnLanguageChange();
}

void SwRichView::OnThemeChange()
{
    if (m_viewMenu)
        m_viewMenu->OnThemeChange();
}
