///////////////////////////////////////////////////////////////////
// Name:        thml_utility.h
// Purpose:     Utility functions for working with ThML files.
//              Parse Osis scripture id's.
//              Find and read into a buffer - css, title, dublin core.
//              Write basic ThML header, dublin core, and footer for a new
//              ThML file.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THML_UTILITY_H
#define THML_UTILITY_H

#include "../../include/html/html.h"
#include "../../include/bible/bibledatacontainers.h"

enum CCEL_CATEGORY
{
    CCEL_UNKNOWN, CCEL_BIBLE, CCEL_EARLY, CCEL_CREED,
    CCEL_HYMN, CCEL_HISTORY, CCEL_MYSTICISM, CCEL_SERMON ,
    CCEL_REFERENCE, CCEL_CLASSIC,
    CCEL_FICTION, CCEL_BIOGRAPHY, CCEL_CHRISTIANLIFE, CCEL_ETHICS,
    CCEL_SCIENCE, CCEL_SYMBOLS, CCEL_THEOLOGY, CCEL_WORSHIP
};

class SOWERBASEEXP SwOsisId
{
public:
    SwOsisId();
    virtual ~SwOsisId();
    void Reset();
    bool Parse(const char * id);
    void SetVersification(const char * versification);
    char m_versification[7];
    swUI8 m_book;
    swUI8 m_chapter;
    swUI8 m_verse;
};

class SOWERBASEEXP OsisRef
{
public:
    OsisRef(){}
    virtual ~OsisRef(){}
    void Reset();
    bool Parse(const char * ref);
    void SetVersification(const char * versification);
    char m_versification[7];
    SwOsisId m_start;
    SwOsisId m_end;
};


class SOWERBASEEXP SwThMLUtility
{
public:
    SwThMLUtility();
    virtual ~SwThMLUtility();

    static swI8 IsFileThML(FILE * file);
    static swI8 IsFileThML(const char * path);
    static bool GetTitle(SwString & buffer, const char * path);
    static bool GetTitleW(SwStringW & buffer, const char * path);
    static bool ReadTitle(char * dest, swUI32 bufferLen, FILE * file, swUI32 filePos = 0);
    static bool GetIdentifier(SwString & buffer, const char * path);
    static bool ReadIdentifier(char * dest, swUI32 bufferLen, FILE * file, swUI32 filePos = 0);
    static bool ReadCss(char * buffer, swUI32 bufferLen, FILE * file, swUI32 filePos = 0);
    static bool GetDublinCore(SwString & buffer, const char * path);
    static bool ReadDublinCore(char * buffer, swUI32 bufferLen, FILE * file, swUI32 filePos = 0);
    static int ReadDivText(SwString & buffer, FILE * file, swUI32 filePos);
    static void GetSyncValue(const char * source, swUI8 & syncType, swUI16 & syncValue);
    static bool IdentifyBook(const char * name, swUI8 & book);
    static const char * GetThMLBookIdString(swUI8 book, bool abbrev = true);
    static const wchar_t * GetThMLBookIdStringW(swUI8 book, bool abbrev = true);
    static bool ParseScriptureId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verse);
    static bool ParseScriptureId(const char * id, SwScriptureRange & sr);
    static bool ParseScriptureId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verseStart, swUI8 & verseEnd);
    static bool ParsePassageId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verse);
    static bool ParsePassageId(const char * id, SwScriptureRange & sr);
    static bool ParsePassageId(const char * id, swUI8 & book, swUI8 & chapter, swUI8 & verseStart, swUI8 & verseEnd);
    static const char * WriteOpenHeader(FILE * file);
    static const char * WriteCloseHeader(FILE * file);
    static const char * WriteDublinCore(FILE * file);
    static const char * WriteFooter(FILE * file);
    static swUI8 IdentifyCategory(const char * ccsubject);
    static swUI8 GetDivType(const char * type);
    static bool CreateInstallPathFromUrl(const char * base, const char * url, char * buffer);
};

#endif // THML_UTILITY_H
