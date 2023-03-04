///////////////////////////////////////////////////////////////////
// Name:        guidata.cpp
// Purpose:     Data for menus, and tool bars.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef GUI_H
#define GUI_H

#include "../sowerbase.h"

enum SEP_POS
{
    SEP_NONE, SEP_BEFORE, SEP_AFTER
};

enum SW_MENU_IDS
{
    SW_MENUID_UNKNOWN,
    SW_MENUID_FILE, SW_MENUID_EDIT, SW_MENUID_VIEW, SW_MENUID_NAVIGATION, SW_MENUID_FORMAT, SW_MENUID_PARAGRAPH,
    SW_MENUID_LIST, SW_MENUID_TABLE, SW_MENUID_OBJECTS, SW_MENUID_TOOLS, SW_MENUID_HELP,

    // SubMenus
    SW_MENUID_RECENTFILES,

    N_SW_MENU_IDS
};

enum SW_GUIITEM_IDS
{
    SW_GUIID_UNKNOWN,

    /* Group - FILE */
    SW_GUIID_NEW, SW_GUIID_OPEN, SW_GUIID_SAVE, SW_GUIID_SAVEAS, SW_GUIID_CLOSE, SW_GUIID_CLOSEALL,
    SW_GUIID_PRINT, SW_GUIID_PRINTPREVIEW, SW_GUIID_QUIT,

    /* GROUP - RECENT FILES */
    SW_GUIID_FILE1, SW_GUIID_FILE2, SW_GUIID_FILE3, SW_GUIID_FILE4, SW_GUIID_FILE5, SW_GUIID_FILE6, SW_GUIID_FILE7,
    SW_GUIID_FILE8, SW_GUIID_FILE9, SW_GUIID_FILE10,


    /* Group - EDIT */
    SW_GUIID_BOOKMARKPAGE, SW_GUIID_FIND, SW_GUIID_FINDNEXT, SW_GUIID_REPLACE, SW_GUIID_CLEAR, SW_GUIID_CUT, SW_GUIID_COPY,
    SW_GUIID_PASTE, SW_GUIID_UNDO, SW_GUIID_REDO, SW_GUIID_SELECTALL, SW_GUIID_GEO, SW_GUIID_MAPS, SW_GUIID_AREAS,
    SW_GUIID_PROPERTIES,

    /* Group - VIEW */
    SW_GUIID_LIBRARYVIEW, SW_GUIID_CONTENTSVIEW, SW_GUIID_SEARCHVIEW, SW_GUIID_FINDVIEW, SW_GUIID_BOOKMARKSVIEW, SW_GUIID_HISTORYVIEW,
    SW_GUIID_ZOOMIN, SW_GUIID_ZOOMOUT, SW_GUIID_VIEWNORMAL,

    /* Group - NAVIGATION */
    SW_GUIID_CONTENTSUP, SW_GUIID_CONTENTSDOWN, SW_GUIID_BACKINHISTORY, SW_GUIID_FORWARDINHISTORY,

    /* Group - FORMAT */
    SW_GUIID_FONT, SW_GUIID_BOLD, SW_GUIID_ITALIC, SW_GUIID_UNDERLINE, SW_GUIID_STRIKETHROUGH, SW_GUIID_SUPERSCRIPT, SW_GUIID_SUBSCRIPT,
    SW_GUIID_COLOR, SW_GUIID_BACKGROUNDCOLOR, SW_GUIID_STYLE,

    /* Group - PARAGRAPH */
    SW_GUIID_MARGINS, SW_GUIID_INDENTMORE, SW_GUIID_INDENTLESS, SW_GUIID_ALIGNLEFT, SW_GUIID_ALIGNCENTER, SW_GUIID_ALIGNRIGHT, SW_GUIID_SINGLESPACING,
    SW_GUIID_DOUBLESPACING,

    /* Group - LIST */
    SW_GUIID_ALPHABETICLIST, SW_GUIID_BULLETEDLIST, SW_GUIID_ROMANNUMERALSLIST, SW_GUIID_DECIMALLIST,

    /* Group - TABLE */
    SW_GUIID_INSERTTABLE, SW_GUIID_INSERTROW, SW_GUIID_DELETEROW, SW_GUIID_INSERTCOLUMN, SW_GUIID_DELETECOLUMN,

    /* Group - Objects */
    SW_GUIID_INSERTIMAGE, SW_GUIID_INSERTLINK, SW_GUIID_INSERTANCHOR,  SW_GUIID_INSERTCONTROL, SW_GUIID_INSERTHORIZONTALRULE,

    /* Group - HELP */
    SW_GUIID_HELPCONTENTS, SW_GUIID_ABOUT, SW_GUIID_PREFERENCES, SW_GUIID_CONFIGURATION, SW_GUIID_SELECTINTERFACE, SW_GUIID_SELECTLANGUAGE,
    SW_GUIID_SELECTTHEME, SW_GUIID_UPDATESOFTWARE,

    /* Players */
    SW_GUIID_PLAY, SW_GUIID_PAUSE, SW_GUIID_STOP, SW_GUIID_REWIND, SW_GUIID_FASTFORWARD, SW_GUIID_PREVIOUS, SW_GUIID_NEXT,

    SW_GUIID_DELETE,

    N_SW_GUIITEM_IDS
};

struct SwGuiDataContainer
{
    swUI8 sw_guiid;
    swUI8 sw_guiid_parent;
    const char * sid_label;
    const wchar_t * label;
    const char * sid_image;
    wxItemKind itemtype;
    swUI8 separator;
    int wx_id;
};

class SOWERBASEEXP SwGuiData
{
public:
    static swUI8 FindMenu(swUI8 swid);
    static const SwGuiDataContainer * GetDataForMenuElement(swUI8 element);
    static const SwGuiDataContainer * GetDataForMenuSwId(swUI8 swid);
    static swUI8 FindItemSwId(swUI8 swid);
    static swUI8 FindItemWxId(int wxid);
    static const SwGuiDataContainer * GetDataForElement(swUI8 element);
    static const SwGuiDataContainer * GetDataForItemSwId(swUI8 swid);
    static const SwGuiDataContainer * GetDataForItemWxId(int wxid);
    static bool IsRecentFile(swUI8 swid);
};

#endif // GUI_H