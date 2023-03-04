///////////////////////////////////////////////////////////////////
// Name:        appifa.h
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

#ifndef APPIFA_H
#define APPIFA_H

#include "../sdf/datafile.h"
#include "../framework/toolbar.h"
#include "../framework/frame.h"
#include "../framework/dialog.h"
#include "../framework/guipanel.h"
#include "../module/modulemanager.h"
#include "../thml/thmlfilemanager.h"
#include "../controls/moduletreectrl.h"
#include "../controls/thmltreectrl.h"
#include "../bible/bookidentifier.h"
#include <wx/html/htmprint.h>
#include <wx/printdlg.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/aui/framemanager.h>
#include <wx/imaglist.h>
#include "../plugin/plugin.h"
#include <wx/intl.h>
#include "../interface/richtext/richtextinterface.h"
#include "../interface/imagewin/imagewindowinterface.h"
#include "../filesys/recurse.h"
#include "../../include/av_media/audio.h"

enum STOCK_IMAGE_ID
{
    IMG_MISSING, IMG_CROSS, IMG_THML, IMG_TOOLS,
    IMG_HELP, IMG_CIRCLE_HOLLOW, IMG_CIRCLE_SOLID,
    IMG_RHOMBUS_HOLLOW, IMG_RHOMBUS_SOLID, IMG_RHOMBUS_SOLID_RED,
    IMG_SQUARE_HOLLOW, IMG_SQUARE_SOLID, IMG_SPLASH,
    IMG_CROSS32, IMG_THML32, IMG_TOOLS32, IMG_HELP32,
    N_STOCK_IMAGE_ID
};

class SwPlugInManager;
class SwPanelList;
class SwToolBook;
class SwFrame;
class SwToolBar;
class SwMenuBar;
class SwPanel;
class SwImageWindowInterface;
class SwGuiPanel;
class SwPlugIn;

class SOWERBASEEXP SwApplicationInterface
{
public :
    SwApplicationInterface();
    virtual ~SwApplicationInterface();

    static void Close();
    static SwDataFile & GetLanguage();
    static bool GetLanguageState();
    static void SetLanguageState(bool initialized = true);

    static SwDataFile & GetMapLanguage();
    static bool GetMapLanguageState();
    static void SetMapLanguageState(bool initialized = true);
    static swUI32 GetMapLanguageTableId();
    static void SetMapLanguageTableId(swUI32 id);

    static SwDataFile & GetMapPaths();
    static bool GetMapPathsState();
    static void SetMapPathsState(bool initialized = true);
    static swUI32 GetMapPathsTableId();
    static void SetMapPathsTableId(swUI32 id);

    static SwDataFile & GetTheme();
    static bool GetThemeState();
    static void SetThemeState(bool initialized = true);

    static SwDataFile & GetConfigure();
    static bool GetConfigureState();
    static void SetConfigureState(bool initialized = true);

    static wxImageList & GetImageList();

    static SwBookIdentifier & GetBookIdentifier();
    static bool GetBookIdentifierState();
    static void SetBookIdentifierState(bool initialized = true);

    static SwDataFile & GetBookmarks();
    static bool GetBookmarksState();
    static void SetBookmarksState(bool initialized = true);

    static SwDataFile & GetPreferences();
    static SwTable & GetGlobalSettings();
    static bool GetPreferencesState();
    static void SetPreferencesState(bool initialized = true);

    static SwDataFile & GetRecentFiles();
    static bool GetRecentFilesState();
    static void SetRecentFilesState(bool initialized = true);

    static SwKeyManager & GetKeyManager();
    static bool GetKeyManagerState();
    static void SetKeyManagerState(bool initialized = true);

    static SwModuleManager & GetModuleManager();
    static bool GetModuleManagerState();
    static void SetModuleManagerState(bool initialized = true);

    static SwThMLFileManager & GetThMLFileManager();
    static bool GetThMLFileManagerState();
    static void SetThMLFileManagerState(bool initialized = true);

    static SwPlugInManager & GetPlugInManager();
    static bool GetPlugInManagerState();
    static void SetPlugInManagerState(bool initialized = true);

    static SwDialogList & GetDialogList();
    static SwPanelList & GetPanelList();

    static wxLocale * GetLocale();
    static void SetLocale(wxLocale * locale);

    static wxPrintData * GetPrintData();
    static void SetPrintData(wxPrintData * printdata);

    static wxPageSetupDialogData * GetPageSetupData();
    static void SetPageSetupData(wxPageSetupDialogData * pagesetupdata);

    static SwFrame * GetFrameWindow();
    static void SetFrameWindow(SwFrame * frame);

    static SwPlugIn * GetEncryptor();
    static SwPlugIn * GetDecryptor();
    static SwMenuBar * GetMenuBar();
    static SwToolBar * GetToolBar();

    static SwToolBook * GetToolBook();
    static SwGuiPanel * GetGuiPanel();

    static swUI32 GetPPI();
    static void SetPPI(wxWindow * win);
    static void SetPPI(swUI32 ppi);

    static swUI8 GetInterfaceFontSize();
    static void SetInterfaceFontSize(swUI8 size);

    static swUI8 GetReaderFontSize();
    static void SetReaderFontSize(swUI8 size);

    static swUI8 GetAutoDefFontSize();
    static void SetAutoDefFontSize(swUI8 size);

    static const char * GetAppName();
    static void SetAppName(const char * appName);

    static SwAudio & GetAudio();

    // Flag : force use of app dir for
    // user data files.
    static bool GetUseAppDir();
    static bool CheckForConfigFile();
    static const char * GetAppDir();
    static const char * GetUserDir();
    static const char * GetResourcesDir();
    static const char * GetThemesDir();
    static const char * GetModuleLibraryDir();
    static const char * GetThMLLibraryDir();
    static const char * GetPluginsDir();
    static const char * GetUserKeysDir();
    static const char * GetMasterKeysDir();
    static const char * GetPublisherKeysDir();
    static const char * GetHelpDir();
    static const char * GetReferenceDir();
    static const char * GetDataDir();


    static bool GetWxState();
    static void SetWxState(bool initialized = true);
    static void InitWX();
    static void InitImageHandlers();
    static bool GetBasicState();
    static void SetBasicState(bool initialized = true);
    static void InitBasic();
    static void FillStyleSheet();
    static wxRichTextStyleSheet * GetStyleSheet();
    static SwRichTextInterface & GetRichInterface();
    static SwImageWindowInterface & GetImageInterface();


    static void LoadGuiFiles();
    static void LoadImageLists();
    static void GetImages(wxImageList & imageList);
    static void LoadDataFiles();
    static void LoadAllKeys();
    static void LoadUserKeys();
    static void LoadMasterKeys();
    static void LoadModules();
    static void LoadHelpModules();
    static void LoadReferenceModules();
    static void LoadPlugIns();
    static void LoadUserFiles();
    static void LoadUserData();
    static bool LoadUserInterface();
    static void SaveUserData();
    static void CloseFiles();

    static swUI16 GetInterfaceCount();
    static void GetInterfaceList(wxChoice * choice);
    static swUI16 GetPreferredInterface();
    static void GetPlugInList(wxChoice * choice);
    static void GetKeyList(wxChoice * choice);
    static void GetMasterKeyList(wxChoice * choice);
    static void GetUserKeyList(wxChoice * choice);
    static void GetModuleList(wxCheckListBox * list);
    static void GetModuleList(wxChoice * choice);
    static void GetModuleList(wxChoice * choice, swUI8 category);
    static void GetModuleList(wxListCtrl * listCtrl);
    static void GetModuleList(wxListCtrl * listCtrl, swUI8 category);
    static void GetModuleList(SwModuleTreeCtrl * treeCtrl);
    static void LoadThMLFiles();
    static void GetThMLFileList(wxCheckListBox * list);
    static void GetThMLFileList(wxChoice * choice);
    static void GetThMLFileList(wxChoice * choice, swUI8 category);
    static void GetThMLFileList(wxListCtrl * listCtrl);
    static void GetThMLFileList(wxListCtrl * listCtrl, swUI8 category);
    static void GetThMLFileList(SwThMLTreeCtrl * treeCtrl);
    static void UpdateThMLFileStates(wxCheckListBox * list);
    static void LoadThMLFileStates();
    static void UpdateModuleStates(wxCheckListBox * list);
    static void LoadModuleStates();
    static void GetMasterKeyModuleList(wxChoice * choice);
    static void GetMasterKeyModuleList(wxListCtrl * listCtrl);
    static void GetMapPathsList(wxCheckListBox * listBox);
    static void GetGroupList(wxChoice * choice);
    static void GetGroupList(wxComboBox * choice);
    static void GetBookMarkList(wxListCtrl * listCtrl);
    static void GetHelpBookMarkList(wxListCtrl * listCtrl);
    static void WriteBookMarklistToTable(wxListCtrl * listCtrl);
    static void WriteHelpBookMarklistToTable(wxListCtrl * listCtrl);
    static void GetRecentFilesList(SwStringArray & array);
    static void WriteRecentFileslistToTable(SwStringArray & array);

    static wxBitmap GetImage(const char * id);
    static wxBitmap GetImage(const char * theme, const char * id);
    static wxBitmap GetMissingImage();
    static wxBitmap GetImage(char * path, const unsigned char *data, int len);
    static wxIcon GetIcon(const char * id);
    static wxIcon GetMissingIcon();
    static wxBitmap GetStockImage(swUI8 id);
    static wxIcon GetSowerIcon();
    static wxIcon GetThMLIcon();
    static wxIcon GetToolsIcon();
    static const char * GetSowerSiteC();
    static const wchar_t * GetSowerSiteW();
    static void About(const wchar_t * appTitle, const wchar_t * version, const wchar_t * copyrightYear);
    static swUI8 GetBookImageIndex(swUI8 category);
    static swUI8 GetOpenBookImageIndex(swUI8 category);
    static swUI8 GetPageImageIndex(swUI8 category);
    static const wchar_t * GetControlString(const char * id, const wchar_t * alt, bool stripampersand = true);
    static swUI8 GetStockImageId(const char * strid);
    static void GetStockImageList(wxChoice * choice);
    static void SetWindowTitle(const char * title);

    static SwPlugIn *              sw_encryptor;
    static SwPlugIn *              sw_decryptor;
    static SwDataFile              sw_language;
    static bool                    sw_languageInitialized;
    static SwDataFile              sw_maplanguage;
    static bool                    sw_maplanguageInitialized;
    static swUI32                  sw_maplanguageTableId;
    static SwDataFile              sw_mappaths;
    static bool                    sw_mappathsInitialized;
    static swUI32                  sw_mappathsTableId;
    static SwDataFile              sw_theme;
    static bool                    sw_themeInitialized;
    static SwDataFile              sw_configure;
    static bool                    sw_configureInitialized;
    static wxImageList             sw_imageList;
    static SwBookIdentifier        sw_bookidentifier;
    static bool                    sw_bookidentifierInitialized;
    static SwDataFile              sw_bookmarks;
    static bool                    sw_bookmarksInitialized;
    static SwDataFile              sw_preferences;
    static SwTable                 sw_globalsettings;
    static bool                    sw_preferencesInitialized;
    static SwDataFile              sw_recentfilelist;
    static bool                    sw_recentfilelistInitialized;
    static SwKeyManager            sw_keymanager;
    static bool                    sw_keymanagerInitialized;
    static SwModuleManager         sw_modulemanager;
    static bool                    sw_modulemanagerInitialized;
    static SwThMLFileManager       sw_thmlfilemanager;
    static bool                    sw_thmlfilemanagerInitialized;
    static SwPlugInManager         sw_pluginmanager;
    static bool                    sw_pluginmanagerInitialized;
    static SwDialogList            sw_dialoglist;
    static SwPanelList             sw_panellist;
    static wxLocale *              sw_locale;
    static wxPrintData *           sw_printData;
    static wxPageSetupDialogData * sw_pagesetupData;
    static SwFrame *               sw_frame;
    static swUI32                  sw_ppi;
    static swUI8                   sw_InterfaceFontSize;
    static swUI8                   sw_ReaderFontSize;
    static swUI8                   sw_AutodefFontSize;
    static bool                    sw_wxInitialized;
    static bool                    sw_basicInitialized;
    static wxRichTextStyleSheet    sw_styleSheet;
    static SwString                sw_appName;
    static SwRichTextInterface     sw_richInterface;
    static SwImageWindowInterface  sw_imageInterface;
    static bool                    sw_useappDir;
    static SwAudio                 sw_audio;
    static bool                    sw_imagehandlersInitialized;
};

#define QuickText   SwApplicationInterface::SetWindowTitle

#endif // APPIFA_H
