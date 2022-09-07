///////////////////////////////////////////////////////////////////
// Name:        librarylistctrl.cpp
// Purpose:     Categorized lists of ThML files, and modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/controls/librarylistctrl.h"

SwThMLLibraryListCtrl::SwThMLLibraryListCtrl()
{
    wxListCtrl::AppendColumn("",wxLIST_FORMAT_LEFT, 300);
}

SwThMLLibraryListCtrl::SwThMLLibraryListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwStretchColumnListCtrl(parent, id, pos, size, style | wxLC_SINGLE_SEL | wxLC_NO_HEADER, validator, name)
{
    wxListCtrl::AppendColumn("",wxLIST_FORMAT_LEFT, 300);
    Bind(wxEVT_THREAD, &SwThMLLibraryListCtrl::OnThreadUpdate, this);
}

SwThMLLibraryListCtrl::~SwThMLLibraryListCtrl()
{
    Unbind(wxEVT_THREAD, &SwThMLLibraryListCtrl::OnThreadUpdate, this);
}

void SwThMLLibraryListCtrl::LoadLibraryList()
{
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }

}

wxThread::ExitCode SwThMLLibraryListCtrl::Entry()
{
    SwStringW buffer;
    SwThMLFile * file;
    wxThreadEvent * e = NULL;
    swUI8 category = 0;

    for (swUI8 count = 0; count < LOAD_CATEGORIES_MAX; count ++)
    {
        category = SwCategory::GetLoadOrder(count);
        for (wxUint32 i = 0; i < SwApplicationInterface::GetThMLFileManager().GetFileCount(); i++)
        {
            file = SwApplicationInterface::GetThMLFileManager().GetAt(i);

            if (!file)
                break;

            if (file->GetCategory() != category)
                continue;

            e = new wxThreadEvent();
            e->SetExtraLong((long) file->GetManagerId());
            buffer.Copy(file->GetTitle());
            e->SetString(buffer.GetArray());
            wxQueueEvent(GetEventHandler(), e);
        }
    }

    return (wxThread::ExitCode)0;
}

void SwThMLLibraryListCtrl::OnThreadUpdate(wxThreadEvent& evt)
{
    wxListItem lItem;
    lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
    lItem.SetColumn(0);
    lItem.SetId(GetItemCount());
    lItem.SetText(evt.GetString());
    lItem.SetData(evt.GetExtraLong());
    wxListCtrl::InsertItem(lItem);
}


SwModuleLibraryListCtrl::SwModuleLibraryListCtrl()
{
    wxListCtrl::AppendColumn("",wxLIST_FORMAT_LEFT, 300);
}

SwModuleLibraryListCtrl::SwModuleLibraryListCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
    :SwStretchColumnListCtrl(parent, id, pos, size, style | wxLC_SINGLE_SEL | wxLC_NO_HEADER, validator, name)
{
    wxListCtrl::AppendColumn("",wxLIST_FORMAT_LEFT, 300);
    Bind(wxEVT_THREAD, &SwModuleLibraryListCtrl::OnThreadUpdate, this);
}

SwModuleLibraryListCtrl::~SwModuleLibraryListCtrl()
{
    Unbind(wxEVT_THREAD, &SwModuleLibraryListCtrl::OnThreadUpdate, this);
}

void SwModuleLibraryListCtrl::LoadLibraryList()
{
    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
    {
        return;
    }

    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        return;
    }
}

wxThread::ExitCode SwModuleLibraryListCtrl::Entry()
{
    SwStringW buffer;
    SwModule * module;
    wxThreadEvent * e = NULL;
    swUI8 category = 0;

    for (swUI8 count = 0; count < LOAD_CATEGORIES_MAX; count ++)
    {
        category = SwCategory::GetLoadOrder(count);
        for (wxUint32 i = 0; i < SwApplicationInterface::GetModuleManager().GetModules(); i++)
        {
            module = SwApplicationInterface::GetModuleManager().GetAt(i);

            if (!module)
                break;

            if (module->m_header.GetCategory() != category)
                continue;

            e = new wxThreadEvent();
            e->SetExtraLong((long) module->GetManagerId());
            buffer.Copy(module->m_header.GetTitle());
            e->SetString(buffer.GetArray());
            wxQueueEvent(GetEventHandler(), e);
        }
    }

    return (wxThread::ExitCode)0;
}

void SwModuleLibraryListCtrl::OnThreadUpdate(wxThreadEvent& evt)
{
    wxListItem lItem;
    lItem.SetStateMask(wxLIST_MASK_TEXT|wxLIST_MASK_DATA);
    lItem.SetColumn(0);
    lItem.SetId(GetItemCount());
    lItem.SetText(evt.GetString());
    lItem.SetData(evt.GetExtraLong());
    wxListCtrl::InsertItem(lItem);
}
