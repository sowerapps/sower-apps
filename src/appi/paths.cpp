///////////////////////////////////////////////////////////////////
// Name:        paths.cpp
// Purpose:     Paths.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/filesys/file.h"
#include <wx/stdpaths.h>

bool SwApplicationInterface::CheckForConfigFile()
{
    SwString path;
    path = GetAppDir();
    path += S_PATH_SEP;
    path += "sw_configure.sdf";

    swUI32 table = NODE_ID_INVALID;

    if (wxFile::Exists(path.GetArray()))
        sw_configure.OpenFile(path.GetArray(), false);

    table = sw_configure.FindTableByCaption(OS_STRING);

    if (table != NODE_ID_INVALID)
    {
        sw_configure.FillTable(table);
        sw_configureInitialized = true;
    }

    swUI32 item = sw_configure.GetTable().FindItemById("Use-App-Path");

    if (item != NODE_ID_INVALID)
        sw_useappDir = SwString::BoolFromString(sw_configure.GetTable().GetNodeData(item));

    return sw_configureInitialized;
}

const char * SwApplicationInterface::GetAppDir()
{
    static SwString buffer;

    buffer = wxStandardPaths::Get().GetExecutablePath().utf8_str();
    SwClipFileName(buffer.GetArray());

    return buffer;
}

const char * SwApplicationInterface::GetUserDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        return filepath;
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("User-Data-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    filepath = wxStandardPaths::Get().GetUserLocalDataDir().utf8_str();

    return filepath;
}

const char * SwApplicationInterface::GetResourcesDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        return filepath;
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Resources-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    filepath = wxStandardPaths::Get().GetResourcesDir().utf8_str();
    filepath += S_PATH_SEP;
    filepath += "resource";

    return filepath;
}

const char * SwApplicationInterface::GetThemesDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        filepath += S_PATH_SEP;
        filepath += "themes";

        return filepath;
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Themes-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    filepath = GetResourcesDir();

    filepath += S_PATH_SEP;
    filepath += "themes";

    return filepath;
}

const char * SwApplicationInterface::GetModuleLibraryDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_preferencesInitialized)
    {
        item = sw_globalsettings.FindItemById("Module-Library-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_globalsettings.GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Module-Library-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        filepath += S_PATH_SEP;
        filepath += "library";
        filepath += S_PATH_SEP;
        filepath += "module";

        return filepath;
    }

    filepath = wxStandardPaths::Get().GetResourcesDir().utf8_str();
    filepath += S_PATH_SEP;
    filepath += "library";
    filepath += S_PATH_SEP;
    filepath += "module";

    return filepath;
}

const char * SwApplicationInterface::GetThMLLibraryDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_preferencesInitialized)
    {
        item = sw_globalsettings.FindItemById("ThML-Library-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_globalsettings.GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("ThML-Library-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        filepath += S_PATH_SEP;
        filepath += "library";
        filepath += S_PATH_SEP;
        filepath += "thml";

        return filepath;
    }

    filepath = wxStandardPaths::Get().GetResourcesDir().utf8_str();
    filepath += S_PATH_SEP;
    filepath += "library";
    filepath += S_PATH_SEP;
    filepath += "thml";

    return filepath;
}

const char * SwApplicationInterface::GetPluginsDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Plugins-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
            {
                /*
                #if defined __linuxdebug__ || defined __osxdebug__
                    filepath += S_PATH_SEP;
                    filepath += "debug";
                #endif // defined
                */
                return filepath;
            }
        }
    }

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        filepath += S_PATH_SEP;
        filepath += "plugins";

        /*
        #if defined __linuxdebug__ || defined __osxdebug__
        filepath += S_PATH_SEP;
        filepath += "debug";
        #endif // defined
        */

        return filepath;
    }

    filepath = wxStandardPaths::Get().GetPluginsDir().utf8_str();

    if (!filepath.StrStr("plugins") && !filepath.StrStr("PlugIns"))
    {
        filepath += S_PATH_SEP;
        filepath += "plugins";

        /*
        #if defined __linuxdebug__ || defined __osxdebug__
        filepath += S_PATH_SEP;
        filepath += "debug";
        #endif // defined
        */
    }

    /*
    #if defined __linuxdebug__ || defined __osxdebug__
        filepath += S_PATH_SEP;
        filepath += "debug";
    #endif // defined
    */

    return filepath;
}

const char * SwApplicationInterface::GetUserKeysDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_useappDir)
    {
        filepath = GetAppDir();

        filepath += S_PATH_SEP;
        filepath += "keys";
        filepath += S_PATH_SEP;
        filepath += "user";

        return filepath;
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("User-Keys-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    filepath = GetResourcesDir();

    filepath += S_PATH_SEP;
    filepath += "keys";
    filepath += S_PATH_SEP;
    filepath += "user";

    return filepath;
}

const char * SwApplicationInterface::GetMasterKeysDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_useappDir)
    {
        filepath = GetAppDir();

        filepath += S_PATH_SEP;
        filepath += "keys";
        filepath += S_PATH_SEP;
        filepath += "master";

        return filepath;
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Master-Keys-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    filepath = GetResourcesDir();

    filepath += S_PATH_SEP;
    filepath += "keys";
    filepath += S_PATH_SEP;
    filepath += "master";

    return filepath;
}

const char * SwApplicationInterface::GetHelpDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Help-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    if (sw_useappDir)
    {
        filepath = GetAppDir();

        filepath += S_PATH_SEP;
        filepath += "help";

        return filepath;
    }

    filepath = GetResourcesDir();

    filepath += S_PATH_SEP;
    filepath += "help";

    return filepath;
}

const char * SwApplicationInterface::GetDataDir()
{
    static SwString filepath;
    swUI32 item = NODE_ID_INVALID;

    if (sw_useappDir)
    {
        filepath = GetAppDir();
        filepath += S_PATH_SEP;
        filepath += "data";

        return filepath;
    }

    if (sw_configureInitialized)
    {
        item = sw_configure.GetTable().FindItemById("Data-Path");
        if (item != NODE_ID_INVALID)
        {
            filepath = sw_configure.GetTable().GetNodeData(item);

            if (filepath.Strlen())
                return filepath;
        }
    }

    filepath = GetResourcesDir();

    filepath += S_PATH_SEP;
    filepath += "data";

    return filepath;
}
