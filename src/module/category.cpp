///////////////////////////////////////////////////////////////////
// Name:        category.cpp
// Purpose:     SwCategory - identify category.
//              SwContentType - identify content type.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/category.h"
#include "../../include/appi/appifa.h"
#include "../../include/thml/thml_parser.h"

struct CATEGORY_DATA
{
    const char * sid;
    const char * name;
    const wchar_t * wname;
    const swUI8 id;
};

static const swUI8 LibraryLoadOrder[] =
{
    CATEGORY_BIBLE,                 //  0
    CATEGORY_BIBLECOMMENTARY,       //  1
    CATEGORY_BIBLESTUDY,            //  2
    CATEGORY_REFERENCE,             //  3
    CATEGORY_DICTIONARY,            //  4
    CATEGORY_ENCYCLOPEDIA,          //  5
    CATEGORY_LEXICON,               //  6
    CATEGORY_TOPICALINDEX,          //  7
    CATEGORY_HISTORY,               //  8
    CATEGORY_MAP,                   //  9
    CATEGORY_THEOLOGY,              // 10
    CATEGORY_SERMON,                // 11
    CATEGORY_DEVOTIONAL,            // 12
    CATEGORY_PRAYER,                // 13
    CATEGORY_WORSHIP,               // 14
    CATEGORY_MYSTICISM,             // 15
    CATEGORY_HYMNAL,                // 16
    CATEGORY_BIOGRAPHY,             // 17
    CATEGORY_ETHICS,                // 18
    CATEGORY_SCIENCE,               // 19
    CATEGORY_GENERAL,               // 20
    CATEGORY_ART,                   // 21
    CATEGORY_MEDIA,                 // 22
    CATEGORY_SYMBOLS,               // 23
    CATEGORY_FICTION,               // 24
    CATEGORY_BIBLESTORY,            // 25
    CATEGORY_UNKNOWN,               // 26
    CATEGORY_HELP                   // 27
};

swUI8 SwCategory::GetLoadOrder(swUI8 count)
{
    if (count > 27)
        return N_CATEGORIES;

    return LibraryLoadOrder[count];
}

static const CATEGORY_DATA CategoryData[] =
{
    "SID_CAT_UNKNOWN", "Unknown", L"Unknown", CATEGORY_UNKNOWN,
    "SID_CAT_ALLTEXT", "All Text", L"All Text", CATEGORY_ALLTEXT,
    "SID_CAT_ART", "Art", L"Art", CATEGORY_ART,
    "SID_CAT_BIBLE", "Bible", L"Bible", CATEGORY_BIBLE,
    "SID_CAT_BIBLECOMMENTARY", "Bible Commentary", L"Bible Commentary", CATEGORY_BIBLECOMMENTARY,
    "SID_CAT_BIBLESTORY", "Bible Story", L"Bible Story", CATEGORY_BIBLESTORY,
    "SID_CAT_BIBLESTUDY", "Bible Study", L"Bible Study", CATEGORY_BIBLESTUDY,
    "SID_CAT_BIOGRAPHY", "Biography", L"Biography", CATEGORY_BIOGRAPHY,
    "SID_CAT_DEVOTIONAL", "Devotional", L"Devotional", CATEGORY_DEVOTIONAL,
    "SID_CAT_DICTIONARY", "Dictionary", L"Dictionary", CATEGORY_DICTIONARY,
    "SID_CAT_ENCYCLOPEDIA", "Encyclopedia", L"Encyclopedia", CATEGORY_ENCYCLOPEDIA,
    "SID_CAT_FICTION", "Fiction", L"Fiction", CATEGORY_FICTION,
    "SID_CAT_GENERAL", "General", L"General", CATEGORY_GENERAL,
    "SID_CAT_HELP", "Help", L"Help", CATEGORY_HELP,
    "SID_CAT_HISTORY", "History", L"History", CATEGORY_HISTORY,
    "SID_CAT_HYMNAL", "Hymnal", L"Hymnal", CATEGORY_HYMNAL,
    "SID_CAT_LEXICON", "Lexicon", L"Lexicon", CATEGORY_LEXICON,
    "SID_CAT_MAP", "Map", L"Map", CATEGORY_MAP,
    "SID_CAT_MEDIA", "Media", L"Media", CATEGORY_MEDIA,
    "SID_CAT_MYSTICISM", "Mysticism", L"Mysticism", CATEGORY_MYSTICISM,
    "SID_CAT_PRAYER", "Prayer", L"Prayer", CATEGORY_PRAYER,
    "SID_CAT_REFERENCE", "Reference", L"Reference", CATEGORY_REFERENCE,
    "SID_CAT_SCIENCE", "Science", L"Science", CATEGORY_SCIENCE,
    "SID_CAT_SERMON", "Sermon", L"Sermon", CATEGORY_SERMON,
    "SID_CAT_SYMBOLS", "Symbols", L"Symbols", CATEGORY_SYMBOLS,
    "SID_CAT_THEOLOGY", "Theology", L"Theology", CATEGORY_THEOLOGY,
    "SID_CAT_TOPICALINDEX", "Topical Index", L"Topical Index", CATEGORY_TOPICALINDEX,
    "SID_CAT_ETHICS", "Ethics", L"Ethics", CATEGORY_ETHICS,
    "SID_CAT_WORSHIP", "Worship", L"Worship", CATEGORY_WORSHIP,
    "", "", L"", 0
};

void SwCategory::GetGroups(Swui8Array & groups)
{
    groups.Reset();
    groups += CATEGORY_BIBLE;
    groups += CATEGORY_BIBLECOMMENTARY;
    groups += CATEGORY_BIBLESTUDY;
    groups += CATEGORY_REFERENCE;
    groups += CATEGORY_HISTORY;
    groups += CATEGORY_MAP;
    groups += CATEGORY_THEOLOGY;
    groups += CATEGORY_HYMNAL;
    groups += CATEGORY_BIOGRAPHY;
    groups += CATEGORY_ETHICS;
    groups += CATEGORY_SCIENCE;
    groups += CATEGORY_GENERAL;
    groups += CATEGORY_ART;
    groups += CATEGORY_MEDIA;
    groups += CATEGORY_SYMBOLS;
    groups += CATEGORY_FICTION;
}

swUI32 SwCategory::GetGroupCount()
{
    Swui8Array array;
    GetGroups(array);
    return array.GetCount();
}

void SwCategory::GetGroupList(swUI8 group, Swui8Array & grouplist)
{
    grouplist.Reset();
    switch (group)
    {
    case CATEGORY_BIBLE:
        grouplist += CATEGORY_BIBLE;
        break;
    case CATEGORY_BIBLECOMMENTARY:
        grouplist += CATEGORY_BIBLECOMMENTARY;
        break;
    case CATEGORY_BIBLESTUDY:
        grouplist += CATEGORY_BIBLESTUDY;
        break;
    case CATEGORY_REFERENCE:
        grouplist += CATEGORY_REFERENCE;
        grouplist += CATEGORY_DICTIONARY;
        grouplist += CATEGORY_ENCYCLOPEDIA;
        grouplist += CATEGORY_LEXICON;
        grouplist += CATEGORY_TOPICALINDEX;
        break;
    case CATEGORY_HISTORY:
        grouplist += CATEGORY_HISTORY;
        break;
    case CATEGORY_MAP:
        grouplist += CATEGORY_MAP;
        break;
    case CATEGORY_THEOLOGY:
        grouplist += CATEGORY_THEOLOGY;
        grouplist += CATEGORY_SERMON;
        grouplist += CATEGORY_DEVOTIONAL;
        grouplist += CATEGORY_PRAYER;
        grouplist += CATEGORY_WORSHIP;
        grouplist += CATEGORY_MYSTICISM;
        break;
    case CATEGORY_HYMNAL:
        grouplist += CATEGORY_HYMNAL;
        break;
    case CATEGORY_BIOGRAPHY:
        grouplist += CATEGORY_BIOGRAPHY;
        break;
    case CATEGORY_ETHICS:
        grouplist += CATEGORY_ETHICS;
        break;
    case CATEGORY_SCIENCE:
        grouplist += CATEGORY_SCIENCE;
        break;
    case CATEGORY_GENERAL:
        grouplist += CATEGORY_GENERAL;
        grouplist += CATEGORY_UNKNOWN;
        break;
    case CATEGORY_ART:
        grouplist += CATEGORY_ART;
        break;
    case CATEGORY_MEDIA:
        grouplist += CATEGORY_MEDIA;
        break;
    case CATEGORY_SYMBOLS:
        grouplist += CATEGORY_SYMBOLS;
        break;
    case CATEGORY_FICTION:
        grouplist += CATEGORY_FICTION;
        grouplist += CATEGORY_BIBLESTORY;
        break;
    }
}

bool SwCategory::IsCategoryInGroup(swUI8 group, swUI8 category)
{
    Swui8Array array;
    GetGroupList(group, array);

    for (swUI32 i = 0; i < array.GetCount(); i ++)
    {
        if (array.GetAt(i) == category)
            return true;
    }

    return false;
}

swUI8 SwCategory::GetCategoryGroup(swUI8 category)
{
    Swui8Array groups;
    GetGroups(groups);

    for (swUI32 i = 0; i < groups.GetCount(); i ++)
    {
        if (IsCategoryInGroup(groups.GetAt(i), category))
            return groups.GetAt(i);
    }

    return CATEGORY_GENERAL;
}

const char * SwCategory::GetId(swUI8 category)
{
    swUI32 pos = 0;

    while (CategoryData[pos].sid[0] != '\0')
    {
        if (CategoryData[pos].id == category)
            return CategoryData[pos].sid;

        pos ++;
    }

    return "";
}

const char * SwCategory::GetString(swUI8 category)
{
    swUI32 pos = 0;

    while (CategoryData[pos].sid[0] != '\0')
    {
        if (CategoryData[pos].id == category)
            return CategoryData[pos].name;

        pos ++;
    }

    return "";
}

const wchar_t * SwCategory::GetStringW(swUI8 category)
{
    swUI32 pos = 0;

    while (CategoryData[pos].sid[0] != '\0')
    {
        if (CategoryData[pos].id == category)
            return CategoryData[pos].wname;

        pos ++;
    }

    return L"";
}

const wchar_t * SwCategory::GetTranslatedString(swUI8 category)
{
    return SwApplicationInterface::GetControlString(GetId(category), GetStringW(category));
}

void SwCategory::FillCtrl(wxChoice * choice)
{
    if (!choice)
        return;

    swUI32 pos = CATEGORY_ALLTEXT + 1;
    SwClientData * data;

    for(;;)
    {
        if (SwCategory::GetString(pos)[0] == '\0')
            break;

        data = new SwClientData(CategoryData[pos].id);
        choice->Append(SwApplicationInterface::GetControlString(GetId(pos), GetStringW(pos)), data);

        pos ++;
    }

    choice->SetSelection(0);
}

void SwCategory::FillSearchCtrl(wxChoice * choice)
{
    if (!choice)
        return;

    swUI32 pos = 0;
    SwClientData * data;

    for(;;)
    {
        if (SwCategory::GetString(pos)[0] == '\0')
            break;

        data = new SwClientData(CategoryData[pos].id);

        if (pos == 0)
            choice->Append(SwApplicationInterface::GetControlString("SID_TITLE", L"Title"), data);
        else
            choice->Append(SwApplicationInterface::GetControlString(CategoryData[pos].sid, CategoryData[pos].wname), data);

        pos ++;
    }

    choice->SetSelection(0);
}

swUI8 SwCategory::GetCategory(wxChoice * choice)
{
    SwClientData * data;

    if (choice->GetSelection() == wxNOT_FOUND)
        return CATEGORY_GENERAL;

    data = (SwClientData *) choice->GetClientObject(choice->GetSelection());

    if (!data)
        return CATEGORY_GENERAL;

    return data->m_data;
}

swUI8 SwCategory::GetCategory(const char * value)
{
    swUI32 pos = 0;

    while (CategoryData[pos].sid[0] != '\0')
    {
        if (stricmp(value, CategoryData[pos].name) == 0)
            return CategoryData[pos].id;

        pos ++;
    }

    return CATEGORY_GENERAL;
}

void SwCategory::SetCategory(wxChoice * choice, swUI8 cat)
{
    SwClientData * data;

    for (unsigned int i = 0; i < choice->GetCount(); i ++)
    {
        data = (SwClientData *) choice->GetClientObject(i);
        if (data->m_data == cat)
        {
            choice->SetSelection(i);
            break;
        }
    }
}

swUI8 SwCategory::IdentifyCategory(const char * dc)
{
    if (!dc)
        return CATEGORY_UNKNOWN;

    SwThMLParser parser;
    SwString data;
    SwStrParser strlist;

    parser.SetThML_ElementArray();
    parser.Load(dc, strlen(dc));
    strlist.SetDeliminator(';');

    for (swUI32 node = 0; node < parser.GetParserNodes(); node ++)
    {
        if (parser.GetNodeType(node) == NODE_TYPE_BEGIN_TAG && parser.GetNodeElementIdentifier(node) == THML_DC_TYPE)
        {
            parser.GetDataBetweenMates(node, data, false);
            strlist.ParseString(data);

                if (strlist.Find("Text.Bible") != NODE_ID_INVALID)
                    return CATEGORY_BIBLE;
                else if (strlist.Find("Text.Commentary") != NODE_ID_INVALID)
                    return CATEGORY_BIBLECOMMENTARY;
                else if (strlist.Find("Text.Dictionary") != NODE_ID_INVALID)
                    return CATEGORY_DICTIONARY;
                else if (strlist.Find("Text.Hymns") != NODE_ID_INVALID)
                    return CATEGORY_HYMNAL;
                else if (strlist.Find("Text.Daily") != NODE_ID_INVALID)
                    return CATEGORY_DEVOTIONAL;
        }
    }

    for (swUI32 node = 0; node < parser.GetParserNodes(); node ++)
    {
        if (parser.GetNodeType(node) == NODE_TYPE_BEGIN_TAG && parser.GetNodeElementIdentifier(node) == THML_DC_SUBJECT)
        {
            parser.GetDataBetweenMates(node, data, false);
            strlist.ParseString(data);

            for (swUI32 i = 0; i < strlist.GetItems(); i ++)
            {
                if (strlist.Find("Art") != NODE_ID_INVALID)
                    return CATEGORY_ART;
                else if (strlist.Find("Bible Story") != NODE_ID_INVALID)
                    return CATEGORY_BIBLESTORY;
                else if (strlist.Find("Bible Study") != NODE_ID_INVALID)
                    return CATEGORY_BIBLESTUDY;
                else if (strlist.Find("Commentary") != NODE_ID_INVALID)
                    return CATEGORY_BIBLECOMMENTARY;
                else if (strlist.Find("Biography") != NODE_ID_INVALID)
                    return CATEGORY_BIOGRAPHY;
                else if (strlist.Find("Devotional") != NODE_ID_INVALID)
                    return CATEGORY_DEVOTIONAL;
                else if (strlist.Find("Dictionary") != NODE_ID_INVALID)
                    return CATEGORY_DICTIONARY;
                else if (strlist.Find("Encyclopedia") != NODE_ID_INVALID)
                    return CATEGORY_ENCYCLOPEDIA;
                else if (strlist.Find("General") != NODE_ID_INVALID)
                    return CATEGORY_GENERAL;
                else if (strlist.Find("Fiction") != NODE_ID_INVALID)
                    return CATEGORY_FICTION;
                else if (strlist.Find("Help") != NODE_ID_INVALID)
                    return CATEGORY_HELP;
                else if (strlist.Find("History") != NODE_ID_INVALID)
                    return CATEGORY_HISTORY;
                else if (strlist.Find("Early Church") != NODE_ID_INVALID)
                    return CATEGORY_HISTORY;
                else if (strlist.Find("Early") != NODE_ID_INVALID)
                    return CATEGORY_HISTORY;
                else if (strlist.Find("Hymns") != NODE_ID_INVALID)
                    return CATEGORY_HYMNAL;
                else if (strlist.Find("Lexicon") != NODE_ID_INVALID)
                    return CATEGORY_LEXICON;
                else if (strlist.Find("Map") != NODE_ID_INVALID)
                    return CATEGORY_MAP;
                else if (strlist.Find("Media") != NODE_ID_INVALID)
                    return CATEGORY_MEDIA;
                else if (strlist.Find("Mysticism") != NODE_ID_INVALID)
                    return CATEGORY_MYSTICISM;
                else if (strlist.Find("Prayer") != NODE_ID_INVALID)
                    return CATEGORY_PRAYER;
                else if (strlist.Find("Reference") != NODE_ID_INVALID)
                    return CATEGORY_REFERENCE;
                else if (strlist.Find("Sermon") != NODE_ID_INVALID || strlist.Find("Sermons") != NODE_ID_INVALID)
                    return CATEGORY_SERMON;
                else if (strlist.Find("Theology") != NODE_ID_INVALID)
                    return CATEGORY_THEOLOGY;
                else if (strlist.Find("Creeds") != NODE_ID_INVALID)
                    return CATEGORY_THEOLOGY;
                else if (strlist.Find("Eschatology") != NODE_ID_INVALID)
                    return CATEGORY_THEOLOGY;
                else if (strlist.Find("Topical Index") != NODE_ID_INVALID)
                    return CATEGORY_TOPICALINDEX;
                else if (strlist.Find("Ethics") != NODE_ID_INVALID)
                    return CATEGORY_ETHICS;
                else if (strlist.Find("Worship") != NODE_ID_INVALID)
                    return CATEGORY_WORSHIP;
                else if (strlist.Find("Science") != NODE_ID_INVALID)
                    return CATEGORY_SCIENCE;
                else if (strlist.Find("Symbols") != NODE_ID_INVALID)
                    return CATEGORY_SYMBOLS;
                else if (strlist.Find("Bible") != NODE_ID_INVALID)
                    return CATEGORY_BIBLE;
                else if (strlist.Find("Christian life") != NODE_ID_INVALID || strlist.Find("Christian Life") != NODE_ID_INVALID)
                    return CATEGORY_THEOLOGY;
                else if (strlist.Find("Practical theology") != NODE_ID_INVALID)
                    return CATEGORY_THEOLOGY;
                else if (strstr(data, "theology"))
                        return CATEGORY_THEOLOGY;
                else if (strstr(data, "Christianity"))
                        return CATEGORY_THEOLOGY;
            }
        }
    }

    return CATEGORY_GENERAL;
};

static const CATEGORY_DATA ContentTypeData[] =
{
    "SID_CTTYPE_UNKNOWN", "Unknown", L"Unknown", CT_UNKNOWN,
    "SID_CTTYPE_TEXT", "Text", L"Text", CT_TEXT,
    "SID_CTTYPE_THML", "ThML", L"ThML", CT_THML,
    "SID_CTTYPE_HTML", "Html", L"Html", CT_HTML,
    "SID_CTTYPE_HYMN", "Hymn", L"Hymn", CT_HYMN,
    "SID_CTTYPE_LESSON", "Lesson", L"Lesson", CT_LESSON,
    "SID_CTTYPE_IMAGE", "Image", L"Image", CT_IMAGE,
    "SID_CTTYPE_MAP", "Map", L"Map", CT_MAP,
    "SID_CTTYPE_AUDIO", "Audio", L"Audio", CT_AUDIO,
    "SID_CTTYPE_VIDEO", "Video", L"Video", CT_VIDEO,
    "SID_CTTYPE_2D", "2D", L"2D", CT_2D,
    "SID_CTTYPE_3D", "3D", L"3D", CT_3D,
    "", "", L"", 0
};

const char * SwContentType::GetId(swUI8 ct)
{
    swUI32 pos = 0;

    while (ContentTypeData[pos].sid[0] != '\0')
    {
        if (ContentTypeData[pos].id == ct)
            return ContentTypeData[pos].sid;

        pos ++;
    }

    return "";
}

const char * SwContentType::GetString(swUI8 ct)
{
    swUI32 pos = 0;

    while (ContentTypeData[pos].sid[0] != '\0')
    {
        if (ContentTypeData[pos].id == ct)
            return ContentTypeData[pos].name;

        pos ++;
    }

    return "";
}

const wchar_t * SwContentType::GetStringW(swUI8 ct)
{
    swUI32 pos = 0;

    while (ContentTypeData[pos].sid[0] != '\0')
    {
        if (ContentTypeData[pos].id == ct)
            return ContentTypeData[pos].wname;

        pos ++;
    }

    return L"";
}

void SwContentType::FillCtrl(wxChoice * choice)
{
    if (!choice)
        return;

    swUI32 pos = 0;
    SwClientData * data;

    for(;;)
    {
        if (GetString(pos)[0] == '\0')
            break;

        data = new SwClientData(pos);
        choice->Append(GetStringW(pos), data);

        pos ++;
    }
}

swUI8 SwContentType::GetContentType(wxChoice * choice)
{
    SwClientData * data;

    if (choice->GetSelection() == wxNOT_FOUND)
        return CT_UNKNOWN;

    data = (SwClientData *) choice->GetClientObject(choice->GetSelection());

    if (!data)
        return CT_UNKNOWN;

    return (swUI8) data->m_data;
}

swUI8 SwContentType::GetContentType(const char * value)
{
    swUI32 pos = 0;

    while (ContentTypeData[pos].sid[0] != '\0')
    {
        if (stricmp(value, ContentTypeData[pos].name) == 0)
            return ContentTypeData[pos].id;

        pos ++;
    }

    if (isdigit(*value))
        return (swUI8) atoi(value);

    return CT_UNKNOWN;
}

void SwContentType::SetContentType(wxChoice * choice, swUI8 contentType)
{
    SwClientData * data;

    for (unsigned int i = 0; i < choice->GetCount(); i ++)
    {
        data = (SwClientData *) choice->GetClientObject(i);
        if (data->m_data == (unsigned) contentType)
        {
            choice->SetSelection(i);
            break;
        }
    }
}
