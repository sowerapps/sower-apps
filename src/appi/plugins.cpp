///////////////////////////////////////////////////////////////////
// Name:        plugins.cpp
// Purpose:     PlugIns.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/plugin/pluginloader.h"

void SwApplicationInterface::LoadPlugIns()
{
    SwPlugInLoader plugloader;
    SwString filepath;

    filepath = GetPluginsDir();

    plugloader.RecurseDir(filepath, false);

    if (strlen(GetAppName()))
    {
        filepath += S_PATH_SEP;
        filepath += GetAppName();
        plugloader.RecurseDir(filepath, false);
    }

    SetPlugInManagerState((bool) sw_pluginmanager.GetCount());

    swUI16 plg = sw_pluginmanager.FindPlugIn(PIT_TRANSCRYPTOR);
    if (plg != NODE_ID_INVALID_16)
    {
        sw_encryptor = sw_pluginmanager.GetAt(plg);
        sw_decryptor = sw_pluginmanager.GetAt(plg);
    }
    else
    {
        plg = sw_pluginmanager.FindPlugIn(PIT_ENCRYPTOR);
        if (plg != NODE_ID_INVALID_16)
        {
            sw_encryptor = sw_pluginmanager.GetAt(plg);
        }

        plg = sw_pluginmanager.FindPlugIn(PIT_DECRYPTOR);
        if (plg != NODE_ID_INVALID_16)
        {
            sw_decryptor = sw_pluginmanager.GetAt(plg);
        }
    }
}

swUI16 SwApplicationInterface::GetInterfaceCount()
{
    swUI16 count = 0;
    SwPlugIn * plugin;

    for (swUI16 i = 0; i < GetPlugInManager().GetCount(); i++)
    {
        plugin = GetPlugInManager().GetAt(i);

        if (!plugin)
            continue;

        if (plugin->GetType() != PIT_INTERFACE)
            continue;

        count ++;
    }

    return count;
}

void SwApplicationInterface::GetInterfaceList(wxChoice * choice)
{
    if (!choice)
        return;

    SwPlugIn * plugin;
    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < GetPlugInManager().GetCount(); i++)
    {
        plugin = GetPlugInManager().GetAt(i);

        if (!plugin)
            continue;

        if (plugin->GetType() != PIT_INTERFACE)
            continue;

        data = new SwClientData(i);
        buffer.Copy(plugin->GetName());
        choice->Append(buffer.GetArray(), data);
    }

    if (GetPlugInManager().GetInterfacePlugIn() != NULL)
    {
        int item = choice->FindString(GetPlugInManager().GetInterfacePlugIn()->GetName());
        choice->SetSelection(item);
    }
}

swUI16 SwApplicationInterface::GetPreferredInterface()
{
    swUI32 item = SwApplicationInterface::GetPreferences().GetTable().FindItemById("Interface-PlugIn");

    if (item == NODE_ID_INVALID)
        return NODE_ID_INVALID_16;

    swUI16 plugin = GetPlugInManager().FindPlugIn(GetPreferences().GetTable().GetNodeData(item));

    return plugin;
}

void SwApplicationInterface::GetPlugInList(wxChoice * choice)
{
    if (!choice)
        return;

    SwPlugIn * plugin;
    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < GetPlugInManager().GetCount(); i++)
    {
        plugin = GetPlugInManager().GetAt(i);
        if (!plugin)
            continue;

        data = new SwClientData(i);
        buffer.Copy(plugin->GetName());
        choice->Append(buffer.GetArray(), data);
    }
}

SwPlugIn * SwApplicationInterface::GetEncryptor()
{
    return sw_encryptor;
}

SwPlugIn * SwApplicationInterface::GetDecryptor()
{
    return sw_decryptor;
}
