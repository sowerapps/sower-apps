///////////////////////////////////////////////////////////////////
// Name:        appdata.cpp
// Purpose:     Initialization of SowerBase.
//              Provides access to SowerBase's module manager,
//              plug-in manager, key manager, translations, theme,
//              preference, book mark files, and versification list.
//              Also a wxRichTextStyleSheet, SwRichTextInterface,
//              and SwImageWindowInterface, and wxPrint classes to prevent
//              the need for views that use these objects to each have
//              their own.
//              Pointers to an applications main gui elements, frame window,
//              tool bar, and menu bar.
//              Application, and user paths, etc.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/appi/appifa.h"
#include "../../include/language/language.h"
#include "../../include/filesys/file.h"
#include <wx/image.h>
#include <wx/stdpaths.h>
#include <wx/fs_mem.h>
#include <wx/file.h>
#include <wx/sysopt.h>

#if defined __linux__
static SowerWxInit sw_Init;
#endif // defined __linux__

SwPlugIn * SwApplicationInterface::sw_encryptor = NULL;
SwPlugIn * SwApplicationInterface::sw_decryptor = NULL;

SwDataFile SwApplicationInterface::sw_language;
bool SwApplicationInterface::sw_languageInitialized = false;

SwDataFile SwApplicationInterface::sw_maplanguage;
bool SwApplicationInterface::sw_maplanguageInitialized = false;
swUI32 SwApplicationInterface::sw_maplanguageTableId = 0;

SwDataFile SwApplicationInterface::sw_mappaths;
bool SwApplicationInterface::sw_mappathsInitialized = false;
swUI32 SwApplicationInterface::sw_mappathsTableId = 0;

SwDataFile SwApplicationInterface::sw_theme;
bool SwApplicationInterface::sw_themeInitialized = false;

SwDataFile SwApplicationInterface::sw_configure;
bool SwApplicationInterface::sw_configureInitialized = false;

wxImageList SwApplicationInterface::sw_imageList;

SwBookIdentifier SwApplicationInterface::sw_bookidentifier;
bool SwApplicationInterface::sw_bookidentifierInitialized = false;

SwDataFile SwApplicationInterface::sw_bookmarks;
bool SwApplicationInterface::sw_bookmarksInitialized = false;

SwDataFile SwApplicationInterface::sw_preferences;
SwTable SwApplicationInterface::sw_globalsettings;
bool SwApplicationInterface::sw_preferencesInitialized = false;

SwDataFile SwApplicationInterface::sw_recentfilelist;
bool SwApplicationInterface::sw_recentfilelistInitialized = false;

SwKeyManager SwApplicationInterface::sw_keymanager;
bool SwApplicationInterface::sw_keymanagerInitialized = false;

SwModuleManager SwApplicationInterface::sw_modulemanager;
bool SwApplicationInterface::sw_modulemanagerInitialized = false;

SwThMLFileManager SwApplicationInterface::sw_thmlfilemanager;
bool SwApplicationInterface::sw_thmlfilemanagerInitialized = false;

SwPlugInManager SwApplicationInterface::sw_pluginmanager;
bool SwApplicationInterface::sw_pluginmanagerInitialized = false;

SwDialogList SwApplicationInterface::sw_dialoglist;
SwPanelList SwApplicationInterface::sw_panellist;

wxLocale  * SwApplicationInterface::sw_locale = NULL;

wxPrintData * SwApplicationInterface::sw_printData = NULL;
wxPageSetupDialogData * SwApplicationInterface::sw_pagesetupData = NULL;

SwFrame * SwApplicationInterface::sw_frame = NULL;

swUI32 SwApplicationInterface::sw_ppi = 96;
swUI8 SwApplicationInterface::sw_InterfaceFontSize = 9;
swUI8 SwApplicationInterface::sw_ReaderFontSize = 9;
swUI8 SwApplicationInterface::sw_AutodefFontSize = 7;

bool SwApplicationInterface::sw_wxInitialized = false;
bool SwApplicationInterface::sw_basicInitialized = false;

wxRichTextStyleSheet SwApplicationInterface::sw_styleSheet;

SwString SwApplicationInterface::sw_appName;

SwRichTextInterface    SwApplicationInterface::sw_richInterface;
SwImageWindowInterface SwApplicationInterface::sw_imageInterface;
bool SwApplicationInterface::sw_useappDir = false;

SwApplicationInterface::SwApplicationInterface()
{
    InitWX();
}

SwApplicationInterface::~SwApplicationInterface()
{
    Close();
}

void SwApplicationInterface::Close()
{
    // SaveUserData();
    CloseFiles();

    if (sw_printData)
        delete sw_printData;

    if (sw_pagesetupData)
        delete sw_pagesetupData;

    if (sw_locale)
        delete sw_locale;

    sw_printData = NULL;
    sw_pagesetupData = NULL;
    sw_locale = NULL;
    sw_pluginmanager.OnUnInitialize();
}


void SwApplicationInterface::InitWX()
{
    #if defined DISABLEWXASSERTS
    wxDISABLE_DEBUG_SUPPORT();
    wxDisableAsserts();
    #endif // DISABLEWXASSERTS

    if (sw_wxInitialized)
    {
        return;
    }

    // Don't call wxInitAllImageHandlers();
    // Do it this way to avoid inclusion
    // of tiff handler.
    wxImage::AddHandler(new wxPNGHandler);
    wxImage::AddHandler(new wxJPEGHandler);
    wxImage::AddHandler(new wxGIFHandler);
    wxImage::AddHandler(new wxPCXHandler);
    wxImage::AddHandler(new wxPNMHandler);
    wxImage::AddHandler(new wxTGAHandler);
    wxImage::AddHandler(new wxXPMHandler);
    wxImage::AddHandler(new wxICOHandler);
    wxImage::AddHandler(new wxCURHandler);
    wxImage::AddHandler(new wxANIHandler);


    sw_imageList.Create(16, 16);

    wxPrintData * pd = new wxPrintData;
    SetPrintData(pd);

    wxPageSetupDialogData * psd = new wxPageSetupDialogData;

    SetPageSetupData(psd);

    wxLocale * plc = new wxLocale;
    SetLocale(plc);

    wxFileSystem::AddHandler(new wxMemoryFSHandler);

    FillStyleSheet();

    sw_wxInitialized = true;

    CheckForConfigFile();
}

void SwApplicationInterface::InitBasic()
{
    if (sw_basicInitialized)
        return;

    InitWX();

    if (!sw_appName.Strlen())
        sw_appName = "default";

    LoadGuiFiles();
    LoadDataFiles();
    LoadUserFiles();
    LoadUserData();

    sw_globalsettings.SetTableCaption("Global Settings");
    sw_basicInitialized = true;
}

void SwApplicationInterface::LoadGuiFiles()
{
    bool status;
    wxString filepath;

    filepath = GetDataDir();
    filepath += S_PATH_SEP;
    filepath += "guitranslation.sdf";

    status = GetLanguage().OpenFile(filepath.utf8_str(), false);

    if (status)
    {
        status = GetLanguage().FillTable(0);
        SetLanguageState(status);
    }

    filepath = GetThemesDir();
    filepath += S_PATH_SEP;
    filepath += "themes.sdf";

    status = GetTheme().OpenFile(filepath.utf8_str(), false);

    if (status)
    {
        status = GetTheme().FillTable(0);
        SetThemeState(status);
    }
}

void SwApplicationInterface::LoadDataFiles()
{
    bool status;
    wxString filepath;

    filepath = GetDataDir();
    filepath += S_PATH_SEP;
    filepath += "mappaths.sdf";

    status = GetMapPaths().OpenFile(filepath.utf8_str(), false);
    if (status)
    {
        status = GetMapPaths().FillTable(0);
        SetMapPathsState(status);
    }

    filepath = GetDataDir();
    filepath += S_PATH_SEP;
    filepath += "maptranslation.sdf";

    status = GetMapLanguage().OpenFile(filepath.utf8_str(), false);
    if (status)
    {
        status = GetMapLanguage().FillTable(0);
        SetMapLanguageState(status);
        sw_maplanguageTableId = 0;
    }

    filepath = GetDataDir();
    filepath += S_PATH_SEP;
    filepath += "bookid.sdf";

    SwDataFile df;

    if (df.OpenFile(filepath.utf8_str(), false))
    {
        GetBookIdentifier().Import(df);
        SetBookIdentifierState(true);
    }
}

void SwApplicationInterface::LoadUserFiles()
{
    bool status;
    wxString filepath;
    swUI32 node;

    SwMakePath(GetUserDir());

    filepath = GetUserDir();
    filepath += S_PATH_SEP;
    filepath += "settings.sdf";

    status = GetPreferences().OpenFile(filepath.utf8_str(), true);

    if (status)
    {
        node = GetPreferences().FindTableByCaption("Global Settings");

        if (node != NODE_ID_INVALID)
        {
            status = GetPreferences().FillTable(node, sw_globalsettings);
        }

        node = GetPreferences().FindTableByCaption(sw_appName);

        if (node != NODE_ID_INVALID)
        {
            status = GetPreferences().FillTable(node);
        }

        SetPreferencesState(status);
        GetPreferences().CloseFile();
    }

    filepath = GetUserDir();
    filepath += S_PATH_SEP;
    filepath += "bookmarks.sdf";

    status = GetBookmarks().OpenFile(filepath.utf8_str(), true);

    if (status)
    {
        node = GetBookmarks().FindTableByCaption(sw_appName);

        if (node != NODE_ID_INVALID)
        {
            status = GetBookmarks().FillTable(node);
        }

        SetBookmarksState(status);
        GetBookmarks().CloseFile();
    }

    filepath = GetUserDir();
    filepath += S_PATH_SEP;
    filepath += "recentfiles.sdf";

    status = GetRecentFiles().OpenFile(filepath.utf8_str(), true);

    if (status)
    {
        node = GetRecentFiles().FindTableByCaption(sw_appName);

        if (node != NODE_ID_INVALID)
        {
            status = GetRecentFiles().FillTable(node);
        }

        SetRecentFilesState(status);
        GetRecentFiles().CloseFile();
    }
}

void SwApplicationInterface::LoadUserData()
{
    swUI32 item;

    item = GetPreferences().GetTable().FindItemById("Theme");
    if (item == NODE_ID_INVALID)
        sw_themeInitialized = GetTheme().FillTable(0);
    else
    {
        item = GetTheme().FindTableByCaption(GetPreferences().GetTable().GetNodeData(item));
        if (item != NODE_ID_INVALID)
            sw_themeInitialized = GetTheme().FillTable(item);
        else
            sw_themeInitialized = GetTheme().FillTable(0);
    }

    LoadImageLists();

    item = GetPreferences().GetTable().FindItemById("Language");

    if (item == NODE_ID_INVALID)
    {
        int language = wxLocale::GetSystemLanguage();
        item = GetLanguage().FindTableByCaption(SwLanguage::GetString(language));

        if (item != NODE_ID_INVALID)
        {
            sw_languageInitialized = GetLanguage().FillTable(item);
        }
        else
        {
            sw_languageInitialized = GetLanguage().FillTable(0);
        }

        item = GetMapLanguage().FindTableByCaption(SwLanguage::GetString(language));

        if (item != NODE_ID_INVALID)
        {
            sw_maplanguageTableId = item;
            sw_maplanguageInitialized = GetMapLanguage().FillTable(item);
        }
        else
        {
            sw_maplanguageTableId = 0;
            sw_maplanguageInitialized = GetMapLanguage().FillTable(0);
        }

        item = GetMapPaths().FindTableByCaption(SwLanguage::GetString(language));

        if (item != NODE_ID_INVALID)
        {
            sw_mappathsTableId = item;
            sw_mappathsInitialized = GetMapPaths().FillTable(item);
        }
        else
        {
            sw_mappathsTableId = 0;
            sw_mappathsInitialized = GetMapPaths().FillTable(0);
        }
    }
    else
    {
        item = NODE_ID_INVALID;

        if (GetLocale())
        {
            GetLocale()->Init(GetPreferences().GetTable().GetNodeData(item));
            item = GetLanguage().FindTableByCaption(GetPreferences().GetTable().GetNodeData(item));
        }

        if (item != NODE_ID_INVALID)
        {
            sw_languageInitialized = GetLanguage().FillTable(item);
        }
        else
        {
            sw_languageInitialized = GetLanguage().FillTable(0);
        }

        item = GetMapLanguage().FindTableByCaption(GetPreferences().GetTable().GetNodeData(item));

        if (item != NODE_ID_INVALID)
        {
            sw_maplanguageTableId = item;
            sw_maplanguageInitialized = GetMapLanguage().FillTable(item);
        }
        else
        {
            sw_maplanguageTableId = 0;
            sw_maplanguageInitialized = GetMapLanguage().FillTable(0);
        }

        item = GetMapPaths().FindTableByCaption(GetPreferences().GetTable().GetNodeData(item));

        if (item != NODE_ID_INVALID)
        {
            sw_mappathsTableId = item;
            sw_mappathsInitialized = GetMapPaths().FillTable(item);
        }
        else
        {
            sw_mappathsTableId = 0;
            sw_mappathsInitialized = GetMapPaths().FillTable(0);
        }
    }

    item = GetPreferences().GetTable().FindItemById("Interface-Font-Size");

    if (item)
    {
        const char * data;
        data = GetPreferences().GetTable().GetNodeData(item);

        if (data)
            sw_InterfaceFontSize = atoi(data);
    }

    item = GetPreferences().GetTable().FindItemById("Reader-Font-Size");

    if (item)
    {
        const char * data;
        data = GetPreferences().GetTable().GetNodeData(item);

        if (data)
            sw_ReaderFontSize = atoi(data);
    }

    item = GetPreferences().GetTable().FindItemById("AutoDef-Font-Size");

    if (item)
    {
        const char * data;
        data = GetPreferences().GetTable().GetNodeData(item);

        if (data)
            sw_AutodefFontSize = atoi(data);
    }
}

bool SwApplicationInterface::LoadUserInterface()
{
    swUI16 plugin;

    if (!GetInterfaceCount())
        return false;

    plugin = GetPreferredInterface();

    if (plugin == NODE_ID_INVALID_16)
    {
        if (GetInterfaceCount() > 0)
        {
            plugin = GetPlugInManager().FindFirstInterface();
        }
    }

    if (plugin != NODE_ID_INVALID_16)
        return GetPlugInManager().SetInterfacePlugIn(plugin);

    return false;
}

void SwApplicationInterface::SaveUserData()
{
    char s[100];

    sprintf(s, "%u", sw_InterfaceFontSize);
    GetPreferences().GetTable().UpdateNode("Interface-Font-Size", s, CELLTYPE_TEXT);

    sprintf(s, "%u", sw_ReaderFontSize);
    GetPreferences().GetTable().UpdateNode("Reader-Font-Size", s, CELLTYPE_TEXT);

    sprintf(s, "%u", sw_AutodefFontSize);
    GetPreferences().GetTable().UpdateNode("AutoDef-Font-Size", s, CELLTYPE_TEXT);

    wxString filepath;
    bool status;
    SwMakePath(GetUserDir());

    filepath = GetUserDir();
    filepath += S_PATH_SEP;
    filepath += "settings.sdf";

    status = GetPreferences().OpenFile(filepath.utf8_str(), true);
    if (status)
    {
        GetPreferences().UpdateTable("Global Settings", sw_globalsettings);
        GetPreferences().UpdateTable(sw_appName);
        //GetPreferences().SaveFile();
        GetPreferences().CloseFile();
    }

    filepath = GetUserDir();
    filepath += S_PATH_SEP;
    filepath += "bookmarks.sdf";

    status = GetBookmarks().OpenFile(filepath.utf8_str(), true);
    if (status)
    {
        GetBookmarks().UpdateTable(sw_appName);
       // GetBookmarks().SaveFile();
        GetBookmarks().CloseFile();
    }

    filepath = GetUserDir();
    filepath += S_PATH_SEP;
    filepath += "recentfiles.sdf";

    status = GetRecentFiles().OpenFile(filepath.utf8_str(), true);

    if (status)
    {
        GetRecentFiles().UpdateTable(sw_appName);
     //   GetRecentFiles().SaveFile();
        GetRecentFiles().CloseFile();
    }
}

void SwApplicationInterface::CloseFiles()
{
  //  GetPreferences().CloseFile();
  //  GetBookmarks().CloseFile();
  //  GetRecentFiles().CloseFile();
    GetTheme().CloseFile();
    GetLanguage().CloseFile();
    GetMapPaths().CloseFile();
    GetMapLanguage().CloseFile();
}

void SwApplicationInterface::GetMapPathsList(wxCheckListBox * listBox)
{
    if (!listBox)
        return;

    SwStringW buffer;
    SwTableItem * tItem;
    swUI32 pos = 0;
    wxArrayString strings;

    while (pos < GetMapPaths().GetTable().GetItems())
    {
        tItem = GetMapPaths().GetTable().GetNode(pos);

        if (tItem)
        {
            buffer.Copy(tItem->GetId());
            strings.Add(buffer.GetArray());
        }

        pos ++;
    }

    listBox->InsertItems(strings, 0);
}

void SwApplicationInterface::GetGroupList(wxChoice * choice)
{
    if (!choice)
        return;

    SwModule * module;
    SwStringW buffer;
    SwClientData * data;

    for (swUI32 i = 0; i < GetModuleManager().GetModules(); i++)
    {
        module = GetModuleManager().GetAt(i);
        if (!module)
            break;

        //if (module->m_header.category == CATEGORY_MAP)
        //    continue;

        if (module->m_header.GetGroupLength() && (choice->FindString(module->m_header.GetGroup()) == wxNOT_FOUND))
        {
            data = new SwClientData(module->GetManagerId());
            buffer.Copy(module->m_header.GetGroup());
            choice->Append(buffer.GetArray(), data);
        }
    }
}

const char * SwApplicationInterface::GetSowerSiteC()
{
    return "https://sowerapps.github.io";
}

const wchar_t * SwApplicationInterface::GetSowerSiteW()
{
    return L"https://sowerapps.github.io";
}

void SwApplicationInterface::About(const wchar_t * appTitle, const wchar_t * version, const wchar_t * copyrightYear)
{
    wxString s;

    s = L"";

    if (appTitle)
    {
        s += appTitle;
    }

    if (version)
    {
        s += L" ";
        s += version;
    }

    s += L"\n";

    s += L"Copyright ";

    if (copyrightYear)
    {
        s += copyrightYear;
    }

    s += ", DNR";
    s += L"\n";

    s += GetSowerSiteW();

    wxMessageBox(s, SwApplicationInterface::GetControlString("SID_ABOUT", L"About"));
}

const wchar_t * SwApplicationInterface::GetControlString(const char * id, const wchar_t * alt, bool stripampersand)
{
    static SwStringW translationBuffer;

    if (!id)
    {
        if (alt)
        {
            translationBuffer = alt;
            if (stripampersand)
                translationBuffer.Replace(L"&", 1, L"", 0);

            return translationBuffer;
        }

        return L"";
    }

    if (SwDataFile::MakeControlString(id, &GetLanguage().GetTable(), translationBuffer))
    {
        if (stripampersand)
            translationBuffer.Replace(L"&", 1, L"", 0);

        return translationBuffer;
    }

    if (alt)
        translationBuffer = wxGetTranslation(alt).wchar_str();

    if (stripampersand)
        translationBuffer.Replace(L"&", 1, L"", 0);

    return translationBuffer;
}

void SwApplicationInterface::SetWindowTitle(const char * title)
{
    if (sw_frame)
        sw_frame->SetTitle(title);
}
