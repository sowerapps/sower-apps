///////////////////////////////////////////////////////////////////
// Name:        keys.cpp
// Purpose:     Module keys.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"

void SwApplicationInterface::LoadAllKeys()
{
    LoadUserKeys();
    LoadMasterKeys();
}

void SwApplicationInterface::LoadUserKeys()
{
    wxString filepath;
    SwKeyLoader keyLoader;

    filepath = GetUserKeysDir();
    keyLoader.RecurseDir(filepath, false);
    SetKeyManagerState((bool) sw_keymanager.GetKeys());
}

void SwApplicationInterface::LoadMasterKeys()
{
    wxString filepath;
    SwKeyLoader keyLoader;

    filepath = GetMasterKeysDir();
    keyLoader.RecurseDir(filepath, false);
    SetKeyManagerState((bool) sw_keymanager.GetKeys());
}

void SwApplicationInterface::GetKeyList(wxChoice * choice)
{
    if (!choice)
        return;

    SwStringW buffer;
    SwClientData * data;

    for (wxUint32 i = 0; i < GetKeyManager().GetKeys(); i++)
    {
        if (!GetKeyManager().GetKey(i)->header.IsMaster() && !GetKeyManager().GetKey(i)->header.IsUser())
            continue;
        data = new SwClientData(i);
        buffer.Copy(GetKeyManager().GetKey(i)->identifier.GetArray());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetMasterKeyList(wxChoice * choice)
{
    if (!choice)
        return;

    SwStringW buffer;
    SwClientData * data;

    for (wxUint32 i = 0; i < GetKeyManager().GetKeys(); i++)
    {
        if (!GetKeyManager().GetKey(i)->header.IsMaster())
            continue;

        data = new SwClientData(i);
        buffer.Copy(GetKeyManager().GetKey(i)->identifier.GetArray());
        choice->Append(buffer.GetArray(), data);
    }
}

void SwApplicationInterface::GetUserKeyList(wxChoice * choice)
{
    if (!choice)
        return;

    SwStringW buffer;
    SwClientData * data;

    for (wxUint32 i = 0; i < GetKeyManager().GetKeys(); i++)
    {
        if (!GetKeyManager().GetKey(i)->header.IsUser())
            continue;

        data = new SwClientData(i);
        buffer.Copy(GetKeyManager().GetKey(i)->identifier.GetArray());
        choice->Append(buffer.GetArray(), data);
    }
}
