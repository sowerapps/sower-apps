///////////////////////////////////////////////////////////////////
// Name:        language.h
// Purpose:     Sower applications use their own translations
//              while defaulting to wxWidgets when necessary.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "../sowerbase.h"
#include <wx/choice.h>

class SOWERBASEEXP SwLanguage
{
public:
    static swUI8 GetStringId(const char * language);
    static const char * GetString(swUI8 id);
    static void FillCtrl(wxChoice * choice, bool full);
    static void SetSelection(wxChoice * choice, swUI8 language);
};

#endif // LANGUAGE_H
