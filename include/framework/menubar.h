///////////////////////////////////////////////////////////////////
// Name:        menubar.h
// Purpose:     See frame.h
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMENUBAR_H
#define SOWERMENUBAR_H

#include "../sowerbase.h"
#include "guidata.h"
#include "frame.h"
#include "../richtext/richtextctrlext.h"
#include "../plugin/plugin.h"
#include <wx/menu.h>

class SwPlugIn;
class SwFrame;

class SOWERBASEEXP SwMenuItem : public wxMenuItem
{
    DECLARE_DYNAMIC_CLASS(SwMenuItem)

public:
    SwMenuItem(wxMenu *parentMenu=NULL, int id=wxID_SEPARATOR, const wxString &text=wxEmptyString, const wxString &helpString=wxEmptyString, wxItemKind kind=wxITEM_NORMAL, wxMenu *subMenu=NULL);
    virtual ~SwMenuItem();

    void SetId(swUI8 swid);
    swUI8 GetId();
    void SetPlugIn(SwPlugIn * plugIn);
    SwPlugIn * GetAt();
    const wchar_t * GetTranslatedLabel();
    void OnLanguageChange();
    void OnThemeChange();

private:
    swUI8 m_swid;
    SwPlugIn * m_plugIn;
};

class SOWERBASEEXP SwMenu : public wxMenu
{
    DECLARE_DYNAMIC_CLASS(SwMenu)

public:
    SwMenu();
    SwMenu(swUI8 swid);
    SwMenu(SwFrame * frame);
    virtual ~SwMenu();

    void SetFrameWindow(SwFrame * frame);
    virtual void OnEvent(wxCommandEvent & event);

    void SetId(swUI8 swid);
    swUI8 GetId();

    // For menus that do not belong to a menu bar;
    virtual SwMenuItem * AddStockItem(swUI8 swid, bool enabled, bool addSeparators);
    void EnableItem(swUI8 swid, bool enable);
    bool IsItemEnabled(swUI8 swid);
    void CheckItem(swUI8 swid, bool check);
    bool IsItemChecked(swUI8 swid);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void UpdateGui();
    //

    const wchar_t * GetTranslatedLabel();

protected:
    swUI8 m_swid;
    SwFrame * m_frame;
};

typedef void (SwFrame::*SwMenuEventHandler)(wxCommandEvent & event);

class SOWERBASEEXP SwMenuBar : public wxMenuBar
{
public:
    SwMenuBar();
    SwMenuBar(SwFrame * frame);
    virtual ~SwMenuBar() {}

    void SetFrameWindow(SwFrame * frame);
    void OnEvent(wxCommandEvent & event);
    SwMenu * AddStockMenu(swUI8 menuid);
    SwMenu * AddStockSubMenu(swUI8 menuid);
    SwMenuItem * AddStockItem(swUI8 swid, bool enabled, bool addSeparators);
    SwMenuItem * AddTool(SwPlugIn * plugin, const wchar_t * label);
    void EnableItem(swUI8 swid, bool enable);
    bool IsItemEnabled(swUI8 swid);
    void CheckItem(swUI8 swid, bool check);
    bool IsItemChecked(swUI8 swid);
    void SetCustomMenuLabel(size_t pos, const char * strid, const wchar_t * deflabel);
    void SetCustomMenuItemBitmap(int wxid, const char * strid);
    void SetCustomMenuItemLabel(int wxid, const char * strid, const wchar_t * deflabel);
    void UpdateRecentFileList(SwStringArray & array);
    void ClearRecentFileList();
    const wchar_t * GetItemLabel(swUI8 swid);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();
    virtual void IterateMenu(wxMenu * menu, size_t pos, bool updateLanguage, bool updateTheme, bool issubMenu);
    virtual void OnFontSizeChange(const wxFont & font);
    virtual void UpdateGui();

private:
    SwFrame * m_frame;
    SwMenu * m_stockMenus[N_SW_MENU_IDS];

    SwMenuEventHandler m_eventHandlers[N_SW_GUIITEM_IDS];
};

class SOWERBASEEXP SwUtilityMenuBar : public SwMenuBar
{
public :
    SwUtilityMenuBar();
    SwUtilityMenuBar(SwFrame * frame);
    virtual ~SwUtilityMenuBar();

    virtual void EnableItems(bool state);
};

class SOWERBASEEXP SwBasicMenuBar : public SwMenuBar
{
public :
    SwBasicMenuBar();
    SwBasicMenuBar(SwFrame * frame);
    virtual ~SwBasicMenuBar();

    virtual void EnableItems(bool state);
    virtual void EnableOpen(bool state);
};

class SOWERBASEEXP SwBasicEditorMenuBar : public SwMenuBar
{
public :
    SwBasicEditorMenuBar();
    SwBasicEditorMenuBar(SwFrame * frame);
    virtual ~SwBasicEditorMenuBar();

    virtual void EnableItems(bool state);
    virtual void EnableOpen(bool state);
    virtual void EnableNew(bool state);
};

class SOWERBASEEXP SwViewMenu : public SwMenu
{
public :
    SwViewMenu();
    SwViewMenu(SwFrame * frame);
    virtual ~SwViewMenu();

    virtual void Init();
    virtual void OnEvent(wxCommandEvent & event);
};

class SOWERBASEEXP SwBasicViewMenu : public SwViewMenu
{
public :
    SwBasicViewMenu();
    SwBasicViewMenu(SwFrame * frame);
    virtual ~SwBasicViewMenu();

    void Init();
    virtual void OnEvent(wxCommandEvent & event);
};

class SOWERBASEEXP SwStandardViewMenu : public SwViewMenu
{
public :
    SwStandardViewMenu();
    SwStandardViewMenu(SwFrame * frame);
    virtual ~SwStandardViewMenu();

    void Init();
    virtual void OnEvent(wxCommandEvent & event);
};

class SOWERBASEEXP SwExtendedViewMenu : public SwViewMenu
{
public :
    SwExtendedViewMenu();
    SwExtendedViewMenu(SwFrame * frame);
    virtual ~SwExtendedViewMenu();

    void Init();
    virtual void OnEvent(wxCommandEvent & event);
};

class SOWERBASEEXP SwAutoDefMenu : public SwMenu
{
public :
    SwAutoDefMenu();
    SwAutoDefMenu(SwRichTextCtrl * view);
    virtual ~SwAutoDefMenu();

    void Init();
    virtual SwMenuItem * AddStockItem(swUI8 swid, bool enabled, bool addSeparators);
    virtual void OnEvent(wxCommandEvent & event);

private:
    SwRichTextCtrl * m_richView;
};

#endif // SOWERMENUBAR_H
