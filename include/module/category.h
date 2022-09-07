///////////////////////////////////////////////////////////////////
// Name:        category.h
// Purpose:     SwCategory - identify category.
//              SwContentType - identify content type.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CATEGORY_H
#define CATEGORY_H

#include "../sowerbase.h"
#include "../array/uintarray.h"

enum CATEGORIES
{
    CATEGORY_UNKNOWN,
    CATEGORY_ALLTEXT,
    CATEGORY_ART,
    CATEGORY_BIBLE,
    CATEGORY_BIBLECOMMENTARY,
    CATEGORY_BIBLESTORY,
    CATEGORY_BIBLESTUDY,
    CATEGORY_BIOGRAPHY,
    CATEGORY_DEVOTIONAL,
    CATEGORY_DICTIONARY,
    CATEGORY_ENCYCLOPEDIA,
    CATEGORY_FICTION,
    CATEGORY_GENERAL,
    CATEGORY_HELP,
    CATEGORY_HISTORY,
    CATEGORY_HYMNAL,
    CATEGORY_LEXICON,
    CATEGORY_MAP,
    CATEGORY_MEDIA,
    CATEGORY_MYSTICISM,
    CATEGORY_PRAYER,
    CATEGORY_REFERENCE,
    CATEGORY_SERMON,
    CATEGORY_THEOLOGY,
    CATEGORY_TOPICALINDEX,
    CATEGORY_ETHICS,
    CATEGORY_WORSHIP,
    CATEGORY_SCIENCE,
    CATEGORY_SYMBOLS,
    N_CATEGORIES,
    CATEGORY_GROUP = N_CATEGORIES
};

#define LOAD_CATEGORIES_MAX 27

enum CONTENT_TYPE
{
    CT_UNKNOWN, CT_TEXT, CT_THML, CT_HTML, CT_HYMN, CT_LESSON, CT_IMAGE, CT_MAP, CT_AUDIO, CT_VIDEO, CT_2D, CT_3D, N_CONTENT_TYPE
};

class SOWERBASEEXP SwCategory
{
public:
    static void GetGroups(Swui8Array & groups);
    static void GetGroupList(swUI8 group, Swui8Array & grouplist);
    static swUI8 GetLoadOrder(swUI8 count);
    static const char * GetId(swUI8 category);
    static const char * GetString(swUI8 category);
    static const wchar_t * GetStringW(swUI8 category);
    static const wchar_t * GetTranslatedString(swUI8 category);
    static void FillCtrl(wxChoice * choice);
    static void FillSearchCtrl(wxChoice * choice);
    static swUI8 GetCategory(wxChoice * choice);
    static swUI8 GetCategory(const char * value);
    static void SetCategory(wxChoice * choice, swUI8 cat);
    static swUI8 IdentifyCategory(const char * dc);
};

class SOWERBASEEXP SwContentType
{
public:
    static const char * GetId(swUI8 ct);
    static const char * GetString(swUI8 ct);
    static const wchar_t * GetStringW(swUI8 ct);
    static void FillCtrl(wxChoice * choice);
    static swUI8 GetContentType(wxChoice * choice);
    static swUI8 GetContentType(const char * value);
    static void SetContentType(wxChoice * choice, swUI8 contentType);
};

#endif // GUISTRINGS_H
