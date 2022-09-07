///////////////////////////////////////////////////////////////////
// Name:        command.cpp
// Purpose:     Handles:
//              Initialization, reset, save, save as, cut, copy,
//              paste, select all, print, clear, open, table operations
//              insertion of images, etc.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"
#include "../../include/appi/appifa.h"
#include <wx/clipbrd.h>
#include <wx/sstream.h>

SwHtmlAnchor & SwRichTextCtrl::GetAnchors()
{
    return m_anchor;
}

SwParagraphList & SwRichTextCtrl::GetParagraphList()
{
    return m_paragraphList;
}

void SwRichTextCtrl::Init()
{
    SetDelayedLayoutThreshold(100000);
    m_paragraphList.SetView(this);
    SetExtraStyle(wxRICHTEXT_EX_NO_GUIDELINES);
    SetBackgroundColour(*wxWHITE);
    RegisterHandlers();
    m_richTimer.m_rich = this;
    m_richTimer.Start(100);
    m_arrowCursor = wxCursor(wxCURSOR_ARROW);
    SetMargins(12.5);
    m_canCopy = true;

    m_printing.SetPageSetupData(*SwApplicationInterface::GetPageSetupData());
    m_printing.SetPrintData(*SwApplicationInterface::GetPrintData());
    m_printing.SetParentWindow(this);

    SetBaseFont();
    SetStyleSheet(SwApplicationInterface::GetStyleSheet());
    SwApplicationInterface::SetPPI(this);
    BindCtrl();
}

void SwRichTextCtrl::SetBaseFont()
{
    wxFont thisFont(SwApplicationInterface::GetReaderFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    return;
}

void SwRichTextCtrl::Reset()
{
    HideAutoDef();
    SetMargins(12.5);
    SetFocusObject(NULL);
    m_anchor.DeleteAll();
    m_adTextLen = 0;
    m_paragraphList.Reset();
    SetValue("");
    Clear();
    m_mouseCount = 0;
    m_lastcaretPos = 0;
    m_lastmousePos.x = 0;
    m_lastmousePos.y = 0;
    SetBaseFont();
    SetStyleSheet(SwApplicationInterface::GetStyleSheet());
    SetBaseStyle();
}

void SwRichTextCtrl::OnPrint(wxCommandEvent& event)
{
    if (!m_canCopy)
        return;

    m_printing.SetHeaderText(L"@TITLE@", wxRICHTEXT_PAGE_ALL, wxRICHTEXT_PAGE_CENTRE);
    m_printing.SetFooterText(L"@PAGENUM@", wxRICHTEXT_PAGE_ALL, wxRICHTEXT_PAGE_RIGHT);
    m_printing.SetTitle(GetFilename());
    m_printing.PrintBuffer(GetBuffer());
}

void SwRichTextCtrl::OnPrintPreview(wxCommandEvent& event)
{
    if (!m_canCopy)
        return;

    m_printing.SetTitle(GetFilename());
    m_printing.PreviewBuffer(GetBuffer());
}

void SwRichTextCtrl::OnUndo(wxCommandEvent& event)
{
    Undo();
}

void SwRichTextCtrl::OnRedo(wxCommandEvent& event)
{
    Redo();
}

void SwRichTextCtrl::OnCut(wxCommandEvent& event)
{
    Cut();
}

void SwRichTextCtrl::OnCopy(wxCommandEvent& event)
{
    if (m_canCopy)
    {
        wxRichTextCtrl::Copy();
    }

}

void SwRichTextCtrl::OnCopyHtml(wxCommandEvent& event)
{
    if (m_canCopy)
    {
        if (wxTheClipboard->Open())
        {   wxStringOutputStream stream;
            GetBuffer().SaveFile(stream, wxRICHTEXT_TYPE_HTML);
            const wxString& html = stream.GetString();
            wxTheClipboard->SetData(new wxHTMLDataObject(html));
            wxTheClipboard->Close();
        }
    }
}

void SwRichTextCtrl::OnPaste(wxCommandEvent& event)
{
    Paste();
}

void SwRichTextCtrl::OnSelectAll(wxCommandEvent& event)
{
    SelectAll();
}

void SwRichTextCtrl::OnInsertImage(wxCommandEvent& event)
{
    wxFileDialog dialog(this, SwApplicationInterface::GetControlString("SID_INSERTIMAGE", L"Insert Image"), "", "",
                        L"(*.*)|*.bmp;*.cur;*.ico;*.jpg;*.png;*.pcx;*.pnm;*.tif;*.tga;*.xpm|BMP (*.bmp)|*.bmp|CUR (*.cur)|*.cur|ICO (*.ico)|*.ico|JPEG (*.jpg)|*.jpg|PNG (*.png)|*.png|PCX (*.pcx)|*.pcx|PNM (*.pnm)|*.pnm|TIFF (*.tif)|*.tif|TGA (*.tga)|*.tga|XPM (*.xpm)|*.xpm");

    if (dialog.ShowModal() != wxID_OK)
        return;

    wxString path = dialog.GetPath();
    wxString s;

    wxBitmapType type = wxBITMAP_TYPE_ANY;
    s = path.AfterLast(L'.');
    if (s.CmpNoCase(L"bmp") == 0)
        type = wxBITMAP_TYPE_BMP;
    else if (s.CmpNoCase(L"cur") == 0)
        type = wxBITMAP_TYPE_CUR;
    else if (s.CmpNoCase(L"ico") == 0)
        type = wxBITMAP_TYPE_ICO;
    else if (s.CmpNoCase(L"jpg") == 0)
        type = wxBITMAP_TYPE_JPEG;
    else if (s.CmpNoCase(L"png") == 0)
        type = wxBITMAP_TYPE_PNG;
    else if (s.CmpNoCase(L"pcx") == 0)
        type = wxBITMAP_TYPE_PCX;
    else if (s.CmpNoCase(L"pnm") == 0)
        type = wxBITMAP_TYPE_PNM;
    else if (s.CmpNoCase(L"tif") == 0)
        type = wxBITMAP_TYPE_TIF;
    else if (s.CmpNoCase(L"tga") == 0)
        type = wxBITMAP_TYPE_TGA;
    else if (s.CmpNoCase(L"xbm") == 0)
        type = wxBITMAP_TYPE_XBM;

    WriteImage(path, type);
}

bool SwRichTextCtrl::CanClose()
{
    if (IsModified())
    {
        int answer = wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_SAVEFILE", L"Save file")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_SAVECHANGES", L"Save changes?")).GetArray(), wxYES_NO | wxCANCEL, NULL);

        if (answer == wxNO)
            return true;
        else if (answer == wxCANCEL)
            return false;
        else if (answer == wxYES)
        {
            if (GetFilename().empty())
            {
                return SaveAs();
            }
            else
            {
                wxBusyCursor busy;
                SaveFile();
                return true;
            }

        }
    }

    return true;
}

void SwRichTextCtrl::OnOpen(wxCommandEvent& event)
{
    if (!CanClose())
        return;

    ClearAll();

    wxString path;
    wxString filename;
    wxArrayInt fileTypes;

    wxString filter = wxRichTextBuffer::GetExtWildcard(false, false, & fileTypes);
    if (!filter.empty())
        filter += L"|";

    filter += SwApplicationInterface::GetControlString("SID_ALLFILES", L"All files");
    filter += L" (*.*)|*.*";

    wxFileDialog dialog(this,
                        SwApplicationInterface::GetControlString("SID_OPENFILE", L"Open file"),
                        path,
                        filename,
                        filter,
                        wxFD_OPEN);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        if (!path.empty())
        {
            int filterIndex = dialog.GetFilterIndex();
            int fileType = (filterIndex < (int) fileTypes.GetCount())
                           ? fileTypes[filterIndex]
                           : wxRICHTEXT_TYPE_TEXT;
            LoadFile(path, fileType);
        }
    }
}

void SwRichTextCtrl::OnClose(wxCommandEvent& event)
{
    if (!CanClose())
        return;

    ClearAll();
}

void SwRichTextCtrl::ClearAll()
{
    m_anchor.DeleteAll();
    Clear();
}

void SwRichTextCtrl::OnSave(wxCommandEvent& event)
{
    if (GetFilename().empty())
    {
        OnSaveAs(event);
        return;
    }

    wxBusyCursor busy;
    SaveFile();
}

bool SwRichTextCtrl::SaveAs()
{
    wxString filter = wxRichTextBuffer::GetExtWildcard(false, true);
    wxString path;
    wxString filename;

    wxFileDialog dialog(this,
                        SwApplicationInterface::GetControlString("SID_SAVEFILE", L"Save file"),
                        path,
                        filename,
                        filter,
                        wxFD_SAVE);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        if (!path.empty())
        {
            wxBusyCursor busy;
            SaveFile(path);
            return true;
        }
    }

    return false;
}

void SwRichTextCtrl::OnSaveAs(wxCommandEvent& event)
{
    SaveAs();
}

void SwRichTextCtrl::SetBasePath(const char * path)
{
    if (!path)
        return;

    m_base = path;
}

char * SwRichTextCtrl::GetBasePath()
{
    return m_base;
}

void SwRichTextCtrl::SetCanCopy(bool canCopy)
{
    m_canCopy = canCopy;
}

bool SwRichTextCtrl::GetCanCopy()
{
    return m_canCopy;
}

void SwRichTextCtrl::OnFind(wxCommandEvent& event)
{
}

void SwRichTextCtrl::OnReplace(wxCommandEvent& event)
{
}

bool SwRichTextCtrl::EditProperties (wxRichTextObject *obj, wxWindow *parent)
{
    return false;
}

bool SwRichTextCtrl::CanCopy()
{
    if (!m_canCopy)
        return false;

    return wxRichTextCtrl::CanCopy();
}
