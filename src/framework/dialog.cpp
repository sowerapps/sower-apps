///////////////////////////////////////////////////////////////////
// Name:        dialog.cpp
// Purpose:     Base class for dialogs in Sower applications.
//              SwDialog registers/unregisters itself with
//              SwApplicationInterface, and will be notified of theme,
//              language, and font size changes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/framework/dialog.h"
#include "../../include/framework/toolbook.h"
#include "../../include/framework/viewbook.h"
#include "../../include/appi/appifa.h"
#include "../../include/controls/moduletreectrl.h"
#include "../../include/controls/thmltreectrl.h"
#include "../../include/richtext/richtextctrlext.h"

bool SwDialog::SelectProjectFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_PRJFILTER", L"Sower Project files (*.swprj)|*.swprj"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SelectThMLFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_THMLFILTER", L"ThML files (*.thm)|*.thm"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SelectHtmlThMLFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_HTMLTHMLFILTER", L"Html files (*.htm;*html)|*.htm;*html|ThML files (*.thm)|*.thm|Sower project files (*.swprj)|*.swprj"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SaveAsHtmlThMLFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_HTMLTHMLFILTER", L"Html files (*.htm;*html)|*.htm;*html|ThML files (*.thm)|*.thm|Sower project files (*.swprj)|*.swprj"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SelectImageFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_IMGFILTER", L"All image files|*.bmp;*.gif;*.png;*.jpg|BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif|PNG files (*.png)|*.png|JPG files (*.jpg)|*.jpg"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SelectModuleFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_MODULEFILTER", L"Sower Modules (*.smd)|*.smd"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SaveAsModuleFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_MODULEFILTER", L"Sower Modules (*.smd)|*.smd"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

bool SwDialog::SelectBz2ModuleFile(wxWindow * parent, SwString & filePath, const char * dir)
{
    wxString p;

    if (dir)
        p = dir;

    wxFileDialog fileDlg(parent, "", p, "", SwApplicationInterface::GetControlString("SID_BZMODULE", L"Compressed Modules (*.smd.bz2)|*.smd.bz2"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (fileDlg.ShowModal() == wxID_CANCEL)
    {
        return false;
    }

    filePath = fileDlg.GetPath().utf8_str();

    return true;
}

int SwDialog::RequestSave(wxWindow * parent)
{
    return wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_REQUESTSAVE", L"Save file?")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_CONFIRM", L"Confirm")).GetArray(), wxYES_NO | wxCANCEL, parent);
}

IMPLEMENT_DYNAMIC_CLASS(SwDialog, wxDialog)

SwDialog::SwDialog()
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SwApplicationInterface::GetDialogList().Add(this);
}

SwDialog::SwDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
    :wxDialog(parent, id, title, pos, size, style, name)
{
    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    SwApplicationInterface::GetDialogList().Add(this);

    Connect(id, wxEVT_SIZE,(wxObjectEventFunction)&SwDialog::OnResize);
}

SwDialog::~SwDialog()
{
    SwApplicationInterface::GetDialogList().Delete(SwApplicationInterface::GetDialogList().Find(this));
}

// false - language, true - theme
void SwDialog::NotifyChildren(bool change)
{
    for ( wxWindowList::iterator it = GetChildren().begin(); it != GetChildren().end(); ++it )
    {
        NotifyChildren(*it, change);
    }
}

void SwDialog::NotifyChildren(wxWindow * window, bool change)
{
    if (window->IsKindOf(CLASSINFO(SwModuleTreeCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwModuleTreeCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwModuleTreeCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwThMLTreeCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwThMLTreeCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwThMLTreeCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwButton)))
    {
        if (!change)
            wxDynamicCast(window, SwButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwBitmapButton)))
    {
        if (!change)
            wxDynamicCast(window, SwBitmapButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwBitmapButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwCheckBox)))
    {
        if (!change)
            wxDynamicCast(window, SwCheckBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwCheckBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListBox)))
    {
        if (!change)
            wxDynamicCast(window, SwListBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwCheckListBox)))
    {
        if (!change)
            wxDynamicCast(window, SwCheckListBox)->OnLanguageChange();
        else
            wxDynamicCast(window, SwCheckListBox)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwChoice)))
    {
        if (!change)
            wxDynamicCast(window, SwChoice)->OnLanguageChange();
        else
            wxDynamicCast(window, SwChoice)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwDataViewListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwDataViewListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwDataViewListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwListView)))
    {
        if (!change)
            wxDynamicCast(window, SwListView)->OnLanguageChange();
        else
            wxDynamicCast(window, SwListView)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRadioButton)))
    {
        if (!change)
            wxDynamicCast(window, SwRadioButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRadioButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStaticText)))
    {
        if (!change)
            wxDynamicCast(window, SwStaticText)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStaticText)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwBitmapToggleButton)))
    {
        if (!change)
            wxDynamicCast(window, SwBitmapToggleButton)->OnLanguageChange();
        else
            wxDynamicCast(window, SwBitmapToggleButton)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStretchColumnListCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwStretchColumnListCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStretchColumnListCtrl)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwStretchColumnListView)))
    {
        if (!change)
            wxDynamicCast(window, SwStretchColumnListView)->OnLanguageChange();
        else
            wxDynamicCast(window, SwStretchColumnListView)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwViewPanel)))
    {
        if (!change)
            wxDynamicCast(window, SwViewPanel)->OnLanguageChange();
        else
            wxDynamicCast(window, SwViewPanel)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwToolBook)))
    {
        if (!change)
            wxDynamicCast(window, SwToolBook)->OnLanguageChange();
        else
            wxDynamicCast(window, SwToolBook)->OnThemeChange();
    }
    else if (window->IsKindOf(CLASSINFO(SwRichTextCtrl)))
    {
        if (!change)
            wxDynamicCast(window, SwRichTextCtrl)->OnLanguageChange();
        else
            wxDynamicCast(window, SwRichTextCtrl)->OnThemeChange();
    }
    // Do nothing, these receive notification from SwApplicationInterface
    else if (window->IsKindOf(CLASSINFO(SwFrame)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwPanel)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwDialog)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwToolBar)))
    {
    }
    else if (window->IsKindOf(CLASSINFO(SwMenuBar)))
    {
    }
    //
    else
    {
        for ( wxWindowList::iterator it = window->GetChildren().begin(); it != window->GetChildren().end(); ++it )
        {
            NotifyChildren(*it, change);
        }
    }
}

void SwDialog::OnLanguageChangeBase()
{
    OnLanguageChange();
    NotifyChildren(false);
}

void SwDialog::OnThemeChangeBase()
{
    OnThemeChange();
    NotifyChildren(true);
}

void SwDialog::OnFontSizeChange(const wxFont & font)
{
    SetFont(font);
}

void SwDialog::OnResize(wxSizeEvent& event)
{
    event.Skip();
}

SwDialogList::SwDialogList()
{
    m_dialogArray = NULL;
    m_dialogarrayPos = 0;
    m_dialogobjectsAllocated = 0;
}

SwDialogList::~SwDialogList()
{
    ReleaseDialogArray();
}

wxUint32 SwDialogList::AssignDialogObject()
{
    if (m_dialogarrayPos >= m_dialogobjectsAllocated && !IncreaseDialogArray())
        return NODE_ID_INVALID;

    m_dialogArray[m_dialogarrayPos] = NULL;
    m_dialogarrayPos ++;

    return m_dialogarrayPos - 1;
}

bool SwDialogList::IncreaseDialogArray()
{
    if (m_dialogobjectsAllocated >= NODE_ID_INVALID - 17)
        return false;

    SwDialog ** p = (SwDialog **) realloc((void *) m_dialogArray, (m_dialogobjectsAllocated + 16) * sizeof(SwDialog *));

    if (p)
    {
        m_dialogobjectsAllocated += 16;
        m_dialogArray = p;

        return true;
    }

    return false;
}

void SwDialogList::ReleaseDialogArray()
{
    if (m_dialogArray)
    {
        free(m_dialogArray);
    }

    m_dialogArray = NULL;
    m_dialogobjectsAllocated = 0;
    m_dialogarrayPos = 0;
}

wxUint32 SwDialogList::Add(SwDialog * dialog)
{

    wxUint32 position = AssignDialogObject();

    if (position == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    m_dialogArray[position] = dialog;

    return position;
}

void SwDialogList::Delete(wxUint32 position)
{
    wxUint32 pos = position;
    if (position >= m_dialogarrayPos)
        return;

    m_dialogArray[position] = NULL;

    if (m_dialogarrayPos >= 1)
    {
        pos ++;

        while (pos < m_dialogarrayPos)
        {
            m_dialogArray[pos -1] = m_dialogArray[pos];
            pos ++;
        }
    }

    m_dialogarrayPos --;
}

void SwDialogList::Reset()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        m_dialogArray[pos] = NULL;
        pos ++;
    }

    m_dialogarrayPos = 0;
}

wxUint32 SwDialogList::Find(SwDialog * dialog)
{
    wxUint32 pos = 0;

    while (pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos] == dialog)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID;
}


SwDialog * SwDialogList::GetDialog(wxUint32 position)
{
    if (position >= m_dialogarrayPos)
        return NULL;

    return m_dialogArray[position];
}

void SwDialogList::SetDialog(wxUint32 position, SwDialog * dialog)
{
    if (position >= m_dialogarrayPos)
        return;

    m_dialogArray[position] = dialog;
}

void SwDialogList::OnLanguageChangeBase()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnLanguageChangeBase();

        pos ++;
    }
}

void SwDialogList::OnThemeChangeBase()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnThemeChangeBase();

        pos ++;
    }
}

void SwDialogList::OnFontSizeChange()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    wxFont thisFont(SwApplicationInterface::GetInterfaceFontSize(),wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnFontSizeChange(thisFont);

        pos ++;
    }
}

void SwDialogList::OnModuleManagerReset()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnModuleManagerReset();

        pos ++;
    }
}

void SwDialogList::OnThMLFileManagerReset()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnThMLFileManagerReset();

        pos ++;
    }
}

void SwDialogList::OnModuleManagerLoaded()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnModuleManagerLoaded();

        pos ++;
    }
}

void SwDialogList::OnThMLFileManagerLoaded()
{
    wxUint32 pos = 0;

    if (!m_dialogArray)
        return;

    while(pos < m_dialogarrayPos)
    {
        if (m_dialogArray[pos])
            m_dialogArray[pos]->OnThMLFileManagerLoaded();

        pos ++;
    }
}
