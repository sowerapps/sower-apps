///////////////////////////////////////////////////////////////////
// Name:        language.cpp
// Purpose:     Sower applications use their own translations
//              while defaulting to wxWidgets when necessary.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/language/language.h"
#include "../../include/appi/appifa.h"
#include <wx/language.h>

struct LANGUAGE_CODES
{
    const char *  name;
    swUI16        id;
};

LANGUAGE_CODES LanguageStrings[] =
{
    "Afrikaans", wxLANGUAGE_AFRIKAANS,
    "Albanian", wxLANGUAGE_ALBANIAN,
    "Arabic", wxLANGUAGE_ARABIC,
    "Basque", wxLANGUAGE_BASQUE,
    "Catalan", wxLANGUAGE_CATALAN,
    "Chinese (simplified)", wxLANGUAGE_CHINESE_SIMPLIFIED,
    "Chinese (traditional)", wxLANGUAGE_CHINESE_TRADITIONAL,
    "Czech", wxLANGUAGE_CZECH,
    "Danish", wxLANGUAGE_DANISH,
    "Dutch", wxLANGUAGE_DUTCH,
    "English", wxLANGUAGE_ENGLISH,
    "English (UK)", wxLANGUAGE_ENGLISH_UK,
    "English (US)", wxLANGUAGE_ENGLISH_US,
    "Finnish", wxLANGUAGE_FINNISH,
    "French", wxLANGUAGE_FRENCH,
    "Galician", wxLANGUAGE_GALICIAN,
    "German", wxLANGUAGE_GERMAN,
    "Greek", wxLANGUAGE_GREEK,
    "Hindi", wxLANGUAGE_HINDI,
    "Hungarian", wxLANGUAGE_HUNGARIAN,
    "Indonesian", wxLANGUAGE_INDONESIAN,
    "Italian", wxLANGUAGE_ITALIAN,
    "Japanese", wxLANGUAGE_JAPANESE,
    "Korean", wxLANGUAGE_KOREAN,
    "Latvian", wxLANGUAGE_LATVIAN,
    "Lithuanian", wxLANGUAGE_LITHUANIAN,
    "Malay", wxLANGUAGE_MALAY,
    "Nepali", wxLANGUAGE_NEPALI,
    "Norwegian Bokmal", wxLANGUAGE_NORWEGIAN_BOKMAL,
    "Polish", wxLANGUAGE_POLISH,
    "Portuguese", wxLANGUAGE_PORTUGUESE,
    "Portuguese (Brazilian)", wxLANGUAGE_PORTUGUESE_BRAZILIAN,
    "Romanian", wxLANGUAGE_ROMANIAN,
    "Russian", wxLANGUAGE_RUSSIAN,
    "Slovak", wxLANGUAGE_SLOVAK,
    "Slovenian", wxLANGUAGE_SLOVENIAN,
    "Spanish", wxLANGUAGE_SPANISH,
    "Swedish", wxLANGUAGE_SWEDISH,
    "Tamil", wxLANGUAGE_TAMIL,
    "Turkish", wxLANGUAGE_TURKISH,
    "Ukrainian", wxLANGUAGE_UKRAINIAN,
    "Valencian", wxLANGUAGE_VALENCIAN,
    "Vietnamese", wxLANGUAGE_VIETNAMESE,
    "", 0
};

swUI8 SwLanguage::GetStringId(const char * language)
{
    swUI32 pos = 0;

    if (!language)
        return wxLANGUAGE_UNKNOWN;

    while (LanguageStrings[pos].name[0] != '\0')
    {
        if (strcmp(LanguageStrings[pos].name, language) == 0)
            return LanguageStrings[pos].id;

        pos ++;
    }

    return wxLANGUAGE_UNKNOWN;
}

const char * SwLanguage::GetString(swUI8 id)
{
    swUI32 pos = 0;

    while (LanguageStrings[pos].name[0] != '\0')
    {
        if (LanguageStrings[pos].id == id)
            return LanguageStrings[pos].name;

        pos ++;
    }

    return "";
}

void SwLanguage::FillCtrl(wxChoice * choice, bool full)
{
    if (!choice)
        return;

    swUI32 pos = 0;
    swUI32 tableId = 0;
    SwStringW buffer;

    while (LanguageStrings[pos].name[0] != '\0')
    {
        tableId = SwApplicationInterface().GetLanguage().FindTableByCaption(LanguageStrings[pos].name);

        if (!full && tableId == NODE_ID_INVALID)
        {
            pos ++;
            continue;
        }

        SwClientData * data = new SwClientData(tableId);
        buffer.Copy(LanguageStrings[pos].name);

        choice->Append(buffer.GetArray(), data);

        pos ++;
    }
}

void SwLanguage::SetSelection(wxChoice * choice, swUI8 language)
{
    SwClientData * data;

    for (unsigned int i = 0; i < choice->GetCount(); i ++)
    {
        data = (SwClientData *) choice->GetClientObject(i);
        if (data->m_data == (unsigned) language)
        {
            choice->SetSelection(i);
            break;
        }
    }
}
