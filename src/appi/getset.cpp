///////////////////////////////////////////////////////////////////
// Name:        getset.cpp
// Purpose:     Acess to variables, and objects.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include <wx/display.h>

bool SwApplicationInterface::GetBasicState()
{
    return sw_basicInitialized;
}

void SwApplicationInterface::SetBasicState(bool initialized)
{
    sw_basicInitialized = initialized;
}

bool SwApplicationInterface::GetUseAppDir()
{
    return sw_useappDir;
}

SwDataFile & SwApplicationInterface::GetLanguage()
{
    return sw_language;
}

bool SwApplicationInterface::GetLanguageState()
{
    return sw_languageInitialized;
}

void SwApplicationInterface::SetLanguageState(bool initialized)
{
    sw_languageInitialized = initialized;
}

SwDataFile & SwApplicationInterface::GetMapLanguage()
{
    return sw_maplanguage;
}

bool SwApplicationInterface::GetMapLanguageState()
{
    return sw_maplanguageInitialized;
}

void SwApplicationInterface::SetMapLanguageState(bool initialized)
{
    sw_languageInitialized = initialized;
}

swUI32 SwApplicationInterface::GetMapLanguageTableId()
{
    return sw_maplanguageTableId;
}

void SwApplicationInterface::SetMapLanguageTableId(swUI32 id)
{
    sw_maplanguageTableId = id;
}

SwDataFile & SwApplicationInterface::GetMapPaths()
{
    return sw_mappaths;
}

bool SwApplicationInterface::GetMapPathsState()
{
    return sw_mappathsInitialized;
}

void SwApplicationInterface::SetMapPathsState(bool initialized)
{
    sw_mappathsInitialized = initialized;
}

swUI32 SwApplicationInterface::GetMapPathsTableId()
{
    return sw_mappathsTableId;
}

void SwApplicationInterface::SetMapPathsTableId(swUI32 id)
{
    sw_mappathsTableId = id;
}

SwDataFile & SwApplicationInterface::GetTheme()
{
    return sw_theme;
}

bool SwApplicationInterface::GetThemeState()
{
    return sw_themeInitialized;
}

void SwApplicationInterface::SetThemeState(bool initialized)
{
    sw_themeInitialized = initialized;
}

SwDataFile & SwApplicationInterface::GetConfigure()
{
    return sw_configure;
}

bool SwApplicationInterface::GetConfigureState()
{
    return sw_configureInitialized;
}

void SwApplicationInterface::SetConfigureState(bool initialized)
{
    sw_configureInitialized = initialized;
}

wxImageList & SwApplicationInterface::GetImageList()
{
    return sw_imageList;
}

SwBookIdentifier & SwApplicationInterface::GetBookIdentifier()
{
    return sw_bookidentifier;
}

bool SwApplicationInterface::GetBookIdentifierState()
{
    return sw_bookidentifierInitialized;
}

void SwApplicationInterface::SetBookIdentifierState(bool initialized)
{
    sw_bookidentifierInitialized = initialized;
}

SwDataFile & SwApplicationInterface::GetBookmarks()
{
    return sw_bookmarks;
}

bool SwApplicationInterface::GetBookmarksState()
{
    return sw_bookmarksInitialized;
}

void SwApplicationInterface::SetBookmarksState(bool initialized)
{
    sw_bookmarksInitialized = initialized;
}

SwDataFile & SwApplicationInterface::GetPreferences()
{
    return sw_preferences;
}

SwTable & SwApplicationInterface::GetGlobalSettings()
{
    return sw_globalsettings;
}

bool SwApplicationInterface::GetPreferencesState()
{
    return sw_preferencesInitialized;
}

void SwApplicationInterface::SetPreferencesState(bool initialized)
{
    sw_preferencesInitialized = initialized;
}

SwDataFile & SwApplicationInterface::GetRecentFiles()
{
    return sw_recentfilelist;
}

bool SwApplicationInterface::GetRecentFilesState()
{
    return sw_recentfilelistInitialized;
}

void SwApplicationInterface::SetRecentFilesState(bool initialized)
{
    sw_recentfilelistInitialized = initialized;
}

SwKeyManager & SwApplicationInterface::GetKeyManager()
{
    return sw_keymanager;
}

bool SwApplicationInterface::GetKeyManagerState()
{
    return sw_keymanagerInitialized;
}

void SwApplicationInterface::SetKeyManagerState(bool initialized)
{
    sw_keymanagerInitialized = initialized;
}

SwModuleManager & SwApplicationInterface::GetModuleManager()
{
    return sw_modulemanager;
}

bool SwApplicationInterface::GetModuleManagerState()
{
    return sw_modulemanagerInitialized;
}

void SwApplicationInterface::SetModuleManagerState(bool initialized)
{
    sw_modulemanagerInitialized = initialized;
}

SwThMLFileManager & SwApplicationInterface::GetThMLFileManager()
{
    return sw_thmlfilemanager;
}

bool SwApplicationInterface::GetThMLFileManagerState()
{
    return sw_thmlfilemanagerInitialized;
}

void SwApplicationInterface::SetThMLFileManagerState(bool initialized)
{
    sw_thmlfilemanagerInitialized = initialized;
}

SwPlugInManager & SwApplicationInterface::GetPlugInManager()
{
    return sw_pluginmanager;
}

bool SwApplicationInterface::GetPlugInManagerState()
{
    return sw_pluginmanagerInitialized;
}

void SwApplicationInterface::SetPlugInManagerState(bool initialized)
{
    sw_pluginmanagerInitialized = initialized;
}

SwDialogList & SwApplicationInterface::GetDialogList()
{
    return sw_dialoglist;
}

SwPanelList & SwApplicationInterface::GetPanelList()
{
    return sw_panellist;
}

wxLocale * SwApplicationInterface::GetLocale()
{
    return sw_locale;
}

void SwApplicationInterface::SetLocale(wxLocale * locale)
{
    sw_locale = locale;
}

wxPrintData * SwApplicationInterface::GetPrintData()
{
    InitWX();
    return sw_printData;
}

void SwApplicationInterface::SetPrintData(wxPrintData * printdata)
{
    sw_printData = printdata;
}

wxPageSetupDialogData * SwApplicationInterface::GetPageSetupData()
{
    InitWX();
    return sw_pagesetupData;
}

void SwApplicationInterface::SetPageSetupData(wxPageSetupDialogData * pagesetupdata)
{
    sw_pagesetupData = pagesetupdata;
}

SwFrame * SwApplicationInterface::GetFrameWindow()
{
    return sw_frame;
}

void SwApplicationInterface::SetFrameWindow(SwFrame * frame)
{
    sw_frame = frame;
}

SwMenuBar * SwApplicationInterface::GetMenuBar()
{
    if (sw_frame)
        return sw_frame->GetSowerMenuBar();

    return NULL;
}

SwToolBar * SwApplicationInterface::GetToolBar()
{
    if (sw_frame)
        return sw_frame->GetSowerToolBar();

    return NULL;
}

SwToolBook * SwApplicationInterface::GetToolBook()
{
    if (sw_frame)
        return sw_frame->GetToolBook();

    return NULL;
}

SwGuiPanel * SwApplicationInterface::GetGuiPanel()
{
    if (sw_frame)
        return sw_frame->GetGuiPanel();

    return NULL;
}

// PPI - Used by html, css functions for conversion of units.
swUI32 SwApplicationInterface::GetPPI()
{
    return sw_ppi;
}

void SwApplicationInterface::SetPPI(wxWindow * win)
{
    if (win)
    {
        #if defined __MSWIN__
        wxDisplay w(win);
        sw_ppi = w.GetPPI().GetX();
        #else
        //wxDisplay w(0);
        sw_ppi = 96;
        #endif
    }
}

void SwApplicationInterface::SetPPI(swUI32 ppi)
{
    sw_ppi = ppi;
}
//

// Interface font size
swUI8 SwApplicationInterface::GetInterfaceFontSize()
{
    return sw_InterfaceFontSize;
}

void SwApplicationInterface::SetInterfaceFontSize(swUI8 size)
{
    sw_InterfaceFontSize = size;
    GetPanelList().OnFontSizeChange();
    GetDialogList().OnFontSizeChange();
    GetPlugInManager().OnFontSizeChange();

    if (SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnFontSizeChange();
}

swUI8 SwApplicationInterface::GetReaderFontSize()
{
    return sw_ReaderFontSize;
}

void SwApplicationInterface::SetReaderFontSize(swUI8 size)
{
    sw_ReaderFontSize = size;
}

swUI8 SwApplicationInterface::GetAutoDefFontSize()
{
    return sw_AutodefFontSize;
}

void SwApplicationInterface::SetAutoDefFontSize(swUI8 size)
{
    sw_AutodefFontSize = size;
}

const char * SwApplicationInterface::GetAppName()
{
    return sw_appName;
}

void SwApplicationInterface::SetAppName(const char * appName)
{
    if (!appName)
        sw_appName = "";

    sw_appName = appName;
}

bool SwApplicationInterface::GetWxState()
{
    return sw_wxInitialized;
}

void SwApplicationInterface::SetWxState(bool initialized)
{
    sw_wxInitialized = initialized;
}

wxRichTextStyleSheet * SwApplicationInterface::GetStyleSheet()
{
    return &sw_styleSheet;
}

SwRichTextInterface & SwApplicationInterface::GetRichInterface()
{
    return sw_richInterface;
}

SwImageWindowInterface & SwApplicationInterface::GetImageInterface()
{
    return sw_imageInterface;
}
