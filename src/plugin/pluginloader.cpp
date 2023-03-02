///////////////////////////////////////////////////////////////////
// Name:        pluginloader.cpp
// Purpose:     Loader for Sower plug-ins.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/plugin/pluginloader.h"
#include "../../include/appi/appifa.h"
#include <wx/dynlib.h>
#include <wx/filename.h>

SwPlugInLoader::SwPlugInLoader()
{
}

SwPlugInLoader::~SwPlugInLoader()
{

}

bool SwPlugInLoader::OnFile(const char * path)
{
    wxFileName fname(path);

    if (fname.GetExt().CmpNoCase(PLUGEXT) == 0)
    {
        wxDynamicLibrary * dll = new wxDynamicLibrary(path, wxDL_NOW|wxDL_VERBATIM|wxDL_QUIET);

        if (!dll)
            return true;

        if (!dll->IsLoaded())
            delete dll;
        else
            SwApplicationInterface::GetPlugInManager().AddLibrary(dll);
    }

    return true;
}

bool SwPlugInLoader::OnDir(const char * path)
{
    return false;
}
