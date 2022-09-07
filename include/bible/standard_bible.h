///////////////////////////////////////////////////////////////////
// Name:        standard_bible.h
// Purpose:     Provide English Bible book titles.
//              Provides KJV versification data.
//              Identifies Bible book names, and abbreviations in
//              English, French, German, Spanish, and Hungarian.
//              More names can be recognized by passing a
//              SwBookIdentifier object passed to the function, or
//              automatically through the global SwBookIdentifier
//              if it has been has a file available and has been
//              initialized.
//              Parse plain text references, recognizing several
//              different forms of writing references.
//              Validate references using KJV versification, or
//              versification from a Versification object that
//              has been passed to the function.
//              Provide information to assist in marking Christ's
//              words (red letter) in Bibles that do not have such
//              mark up.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STANDARD_BIBLE_H
#define STANDARD_BIBLE_H

#include "../string/string.h"
#include "../bible/bookidentifier.h"

// Versification Schemes
enum VERSIFICATION_SCHEMES
{
    VS_UNKNOWN, VS_ASV, VS_KJV, VS_NKJV, VS_NEB, VS_NIV, VS_RSV, VS_NRSV, VS_VUL,
    N_VERSIFICATION_SCHEMES
};

// Title styles
enum TITLE_STYLE
{
    STYLE_TEXT = 0X01, STYLE_DECIMAL = 0X02, STYLE_ROMAN = 0X04,
    STYLE_UPPERCASE = 0X08, STYLE_TEXT_OFFSET = 17
};

// Return codes for functions.
enum STATUS_CODE
{
    _OK_ = 250, INVALID_BOOK, INVALID_CHAPTER, INVALID_VERSE,
    INSUFFICIENT_BUFFER, INVALID_STYLE
};

enum REFERENCE_TYPE
{
    REFERENCE_TYPE_SCRIPTURE = 1,
    REFERENCE_TYPE_STRONGS_HEBREW,
    REFERENCE_TYPE_STRONGS_GREEK,
    REFERENCE_TYPE_WORD
};

// Old Testament Books
enum STANDARD_BIBLE_BOOK_NUMBERS
{
    Genesis = 1, Exodus, Leviticus, Numbers, Deuteronomy, Joshua, Judges, Ruth,
    I_Samuel, II_Samuel, I_Kings, II_Kings, I_Chronicles, II_Chronicles,
    Ezra, Nehemiah, Esther, Job, Psalms, Proverbs, Ecclesiastes, Song_of_Solomon,
    Isaiah,Jeremiah, Lamentations, Ezekiel, Daniel, Hosea, Joel, Amos, Obadiah,
    Jonah, Micah, Nahum, Habakkuk, Zephaniah, Haggai, Zechariah, Malachi,
    // New Testament Books
    Matthew, Mark, Luke, John, Acts, Romans, I_Corinthians, II_Corinthians,
    Galatians, Ephesians, Philippians, Colossians, I_Thessalonians, II_Thessalonians,
    I_Timothy, II_Timothy, Titus, Philemon, Hebrews, James, I_Peter, II_Peter,
    I_John, II_John, III_John, Jude, Revelation,
    OLD_TESTAMENT_BEGIN = Genesis,
    OLD_TESTAMENT_END   = Malachi,
    NEW_TESTAMENT_BEGIN = Matthew,
    NEW_TESTAMENT_END   = Revelation,
    KJV_BOOKS           = Revelation
};

class SOWERBASEEXP SwReferenceData
{
public :
    SwReferenceData();
    virtual ~SwReferenceData();
    void Display();

    swUI8    book;
    swUI8    chapter;
    swUI8    verseStart;
    swUI8    verseEnd;
    swUI16   strongs;
    swUI8    referenceType;
    SwString buffer;
};

#define Invalid_Reference -4
#define No_Red_Text_In_Book -5
#define No_Red_Text_In_Chapter -6
#define No_Red_Text_In_Verse -7
#define Full_Chapter_Red -8
#define Full_Verse_Red -9

struct RedTextData
{
    swI16 sec1Begin;
    swI16 sec1End;
    swI16 sec2Begin;
    swI16 sec2End;
    swI16 result;
};

class SOWERBASEEXP SwStandardBible
{
public :
    static swUI8 Get_KJV_BookChapters(swUI8 book);
    static swUI8 Get_KJV_ChapterVerses(swUI8 book, swUI8 chapter);
    static swUI8 Verify_KJV_Reference(swUI8 book, swUI8 chapter, swUI8 verse);
    static swUI8 Get_kJV_BookTitle(swUI8 book, swUI8 flags, SwString & buffer);
    static swUI8 Get_KJV_BookAbbreviation(swUI8 book, swUI8 flags, SwString & buffer);
    static swUI8 Get_KJV_ChapterAbbreviation(swUI8 book, swUI8 chapter, swUI8 flags, SwString & buffer);
    static swUI8 IdentifyBibleBookName(const char * name);
    static swUI8 IdentifyBibleBookName(const wchar_t * name);
    static bool IdentifyReference(const wchar_t * referenceString, swUI32 offset, SwReferenceData & referenceData);
    static bool IdentifyChapterReference(const wchar_t * referenceString, swUI32 offset, SwReferenceData & referenceData);
    static int ParseTextEx(char * pszWord, int nOffSet);
    static swI16 GetRedTextIndexForBook(swUI8 book);
    static swI16 GetRedTextIndexForChapter(swUI8 book, swUI8 chapter);
    static swI16 GetRedTextIndexForVerse(swUI8 book, swUI8 chapter, swUI8 verse);
    static bool GetRedTextDataForVerse(swUI8 book, swUI8 chapter, swUI8 verse, RedTextData & data);
    static void FillCtrl(wxComboBox * ctrl);
};

#endif // STANDARD_BIBLE_H
