///////////////////////////////////////////////////////////////////
// Name:        dialog.h
// Purpose:     Base class for dialogs in Sower applications.
//              SwDialog registers/unregisters itself with
//              SwApplicationInterface, and will be notified of theme,
//              language, and font size changes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERDIALOG_H
#define SOWERDIALOG_H

#include "../sowerbase.h"
#include "../../include/controls/controls.h"

#include <wx/dialog.h>

class SOWERBASEEXP SwDialog : public wxDialog
{
    DECLARE_DYNAMIC_CLASS(SwDialog)

public:
    SwDialog();
    SwDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE, const wxString &name=wxDialogNameStr);
    virtual ~SwDialog();

    void NotifyChildren(bool change);
    void NotifyChildren(wxWindow * window, bool change);
    void OnLanguageChangeBase();
    void OnThemeChangeBase();
    virtual void OnLanguageChange() {}
    virtual void OnThemeChange() {}
    virtual void OnFontSizeChange(const wxFont & font);
    virtual void OnResize(wxSizeEvent& event);

    virtual void OnModuleManagerReset() {}
    virtual void OnThMLFileManagerReset() {}
    virtual void OnModuleManagerLoaded() {}
    virtual void OnThMLFileManagerLoaded() {}
    virtual void OnModuleAdded(swUI16 mid) {}
    virtual void OnModuleDeleted(swUI16 mid) {}
    virtual void OnThMLFileAdded(swUI16 mid) {}
    virtual void OnThMLFileDeleted(swUI16 mid) {}

    static bool SelectThMLFile(wxWindow * parent, SwString & filePath, const char * dir);
    static bool SelectModuleFile(wxWindow * parent, SwString & filePath, const char * dir);
    static bool SelectImageFile(wxWindow * parent, SwString & filePath, const char * dir);
    static int RequestSave(wxWindow * parent);
};

class SOWERBASEEXP SwDialogList
{
public:
    SwDialogList();
    virtual ~SwDialogList();

    wxUint32 Add(SwDialog * dialog);
    void Delete(wxUint32 position);
    void Reset();
    wxUint32 Find(SwDialog * dialog);
    SwDialog * GetDialog(wxUint32 position);
    void SetDialog(wxUint32 position, SwDialog * dialog);
    void OnLanguageChangeBase();
    void OnThemeChangeBase();
    void OnFontSizeChange();
    void OnModuleManagerReset();
    void OnThMLFileManagerReset();
    void OnModuleManagerLoaded();
    void OnThMLFileManagerLoaded();

protected:
    wxUint32 AssignDialogObject();
    bool IncreaseDialogArray();
    void ReleaseDialogArray();
    SwDialog ** m_dialogArray;
    wxUint32 m_dialogarrayPos;
    wxUint32 m_dialogobjectsAllocated;
};

#endif // SOWERDIALOG_H
