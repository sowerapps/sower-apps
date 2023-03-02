///////////////////////////////////////////////////////////////////
// Name:        markuppanel.h
// Purpose:     Text markup.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MARKUPPANEL_H
#define MARKUPPANEL_H

#include "panel.h"
#include "../framework/findpanel.h"
#include "../richtext/autodefwindow.h"
#include <wx/aui/aui.h>
#include <wx/notebook.h>
#include <wx/stattext.h>
#include <wx/stc/stc.h>

class SwMarkUpPanel;
class SOWERBASEEXP SwDwellTimer : public wxTimer
{
public:
    SwDwellTimer();
    virtual ~SwDwellTimer();
    virtual void Notify();

    SwMarkUpPanel * m_panel;
};

class SwStcFindReplacePanel;
class SOWERBASEEXP SwMarkUpPanel : public SwPanel
{
public:
    SwMarkUpPanel();
    SwMarkUpPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwMarkUpPanel();

    virtual bool OnOpen();
    virtual bool OnSave();
    virtual bool OnSaveAs();
    virtual bool OnClose();
    virtual bool OnCut();
    virtual bool OnCopy();
    virtual bool OnPaste();
    virtual bool OnUndo();
    virtual bool OnRedo();
    virtual bool OnSelectAll();
    virtual bool OnZoomIn();
    virtual bool OnZoomOut();
    virtual bool OnViewNormal();
    virtual void OnLanguageChange();
    virtual bool OnHasFocus();
    virtual bool OnHasSelection();
    virtual bool OnClosePanel();
    virtual bool OnCanDoSave();
    virtual bool OnCanDoSaveAs();
    virtual bool OnCanDoClose();
    virtual bool OnCanDoCut();
    virtual bool OnCanDoCopy();
    virtual bool OnCanDoPaste();
    virtual bool OnCanDoUndo();
    virtual bool OnCanDoRedo();
    virtual bool OnCanDoZoomIn();
    virtual bool OnCanDoZoomOut();
    virtual bool OnCanDoViewNormal();
    virtual const char * GetFilePath();
    virtual bool HasFile(const char * path);
    virtual bool OpenFile(const char * path);
    void OnThMLItemSelect(wxListEvent& event);
    void OnHtmlItemSelect(wxListEvent& event);
    void OnPrjMlItemSelect(wxListEvent& event);
    void CreateTags(const char * name, const char * attributes, SwString & beginTag, SwString & endTag);
    void InsertTags(const char * beginTag, const char * endTag);
    void OnMouseHoverStart(wxStyledTextEvent& event);
    int ParseText(SwString & data, int nOffSet);
    void OnTimer();

    wxNotebook* ToolNotebook;
    SwStcFindReplacePanel* FindReplacePanel;
    wxStyledTextCtrl* EditorStCtrl;
    SwStretchColumnListCtrl* ThMLListCtrl;
    SwStretchColumnListCtrl* HtmlListCtrl;
    SwStretchColumnListCtrl* PrjMlListCtrl;

    static const long ID_THMLLISTCTRL;
    static const long ID_HTMLLISTCTRL;
    static const long ID_PRJMLLISTCTRL;
    static const long ID_FINDREPLACEPANEL;
    static const long ID_TOOLNOTEBOOK;
    static const long ID_EDITORSTCTRL;

protected:
    void BuildContent(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size);
    SwString          m_path;
    SwAutoDefWindow * m_autodefwindow;
    wxPoint           m_lastmousePos;
    wxPoint           m_adClientPos;
    int               m_caretPos;
    long              m_mouseCount;
    int               m_initZoom;
    static SwString   m_buffer;
    SwDwellTimer      m_timer;
};

class SOWERBASEEXP SwStcFindReplacePanel : public SwPanel
{
public:
    SwStcFindReplacePanel();
    SwStcFindReplacePanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~SwStcFindReplacePanel();

    void Reset();
    void CreateGui();
    void SetStcCtrl(wxStyledTextCtrl * stc);
    virtual void OnLanguageChange();
    virtual void OnThemeChange();

    void OnFindButtonClick(wxCommandEvent& event);
    void OnFindNextButtonClick(wxCommandEvent& event);
    void OnReplaceButtonClick(wxCommandEvent& event);
    void OnReplaceAllButtonClick(wxCommandEvent& event);

    static const long ID_FINDSTATICTEXT;
    static const long ID_FINDTEXTCTRL;
    static const long ID_FINDCASECHECKBOX;
    static const long ID_FINDWORDCHECKBOX;
    static const long ID_REPLACESTATICTEXT;
    static const long ID_REPLACETEXTCTRL;
    static const long ID_FINDBUTTON;
    static const long ID_FINDNEXTBUTTON;
    static const long ID_REPLACEBUTTON;
    static const long ID_REPLACEALLBUTTON;

    wxGridBagSizer* FindGridSizer;
    wxStaticText* FindStaticText;
    SwStretchTextCtrl* FindTextCtrl;
    SwCheckBox* FindCaseCheckBox;
    SwCheckBox* FindWordCheckBox;
    wxStaticText* ReplaceStaticText;
    SwStretchTextCtrl* ReplaceTextCtrl;
    wxButton* FindButton;
    wxButton* FindNextButton;
    wxButton* ReplaceButton;
    wxButton* ReplaceAllButton;

protected:
    wxStyledTextCtrl * m_stc;
};

#endif // MARKUPPANEL_H
