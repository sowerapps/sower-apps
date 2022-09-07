///////////////////////////////////////////////////////////////////
// Name:        standard_bible.cpp
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

#include "../../include/bible/standard_bible.h"
#include "../../include/string/string.h"
#include "../../include/string/stringw.h"
#include "../../include/appi/appifa.h"

// KJV Versification (excluding apocrypha)
// Contains the number of chapters in each book.
static const swUI8 KJV_BookChapterArray [] =
{
    00, // Alignment
    50,40,27,36,34,24,21,4,31,24,22,25,29,36,10,13,10,42,150,31,
    12,8,66,52,5,48,12,14,3,9,1,4,7,3,3,3,2,14,4,28,16,24,21,28,
    16,16,13,6,6,4,4,5,3,6,4,3,1,13,5,5,3,5,1,1,1,22
};

// Contains the number of verses in all chapters of all books.
static const swUI8 KJV_ChapterVerseArray[] =
{

    00, // Alignment
    // Genesis
    31,25,24,26,32,22,24,22,29,32,32,20,18,24,21,16,27,33,38,18,
    34,24,20,67,34,35,46,22,35,43,55,32,20,31,29,43,36,30,23,23,
    57,38,34,34,28,34,31,22,33,26,

    // Exodus
    22,25,22,31,23,30,25,32,35,29,10,51,22,31,27,36,16,27,25,26,
    36,31,33,18,40,37,21,43,46,38,18,35,23,35,35,38,29,31,43,38,

    // Leviticus
    17,16,17,35,19,30,38,36,24,20,47,8,59,57,33,34,16,30,37,27,
    24,33,44,23,55,46,34,

    // Numbers
    54,34,51,49,31,27,89,26,23,36,35,16,33,45,41,50,13,32,22,29,
    35,41,30,25,18,65,23,31,40,16,54,42,56,29,34,13,

    // Deuteronomy
    46,37,29,49,33,25,26,20,29,22,32,32,18,29,23,22,20,22,21,20,
    23,30,25,22,19,19,26,68,29,20,30,52,29,12,

    // Joshua
    18,24,17,24,15,27,26,35,27,43,23,24,33,15,63,10,18,28,51,9,
    45,34,16,33,

    // Judges
    36,23,31,24,31,40,25,35,57,18,40,15,25,20,20,31,13,31,30,48,
    25,

    // Ruth
    22,23,18,22,

    // I_Samuel
    28,36,21,22,12,21,17,22,27,27,15,25,23,52,35,23,58,30,24,42,
    15,23,29,22,44,25,12,25,11,31,13,

    // II_Samuel
    27,32,39,12,25,23,29,18,13,19,27,31,39,33,37,23,29,33,43,26,
    22,51,39,25,

    // I_Kings
    53,46,28,34,18,38,51,66,28,29,43,33,34,31,34,34,24,46,21,43,
    29,53,

    // II_Kings
    18,25,27,44,27,33,20,29,37,36,21,21,25,29,38,20,41,37,37,21,
    26,20,37,20,30,

    // I_Chronicles
    54,55,24,43,26,81,40,40,44,14,47,40,14,17,29,43,27,17,19,8,
    30,19,32,31,31,32,34,21,30,

    // II_Chronicles
    17,18,17,22,14,42,22,18,31,19,23,16,22,15,19,14,19,34,11,37,
    20,12,21,27,28,23,9,27,36,27,21,33,25,33,27,23,

    // Ezra
    11,70,13,24,17,22,28,36,15,44,

    // Nehemiah
    11,20,32,23,19,19,73,18,38,39,36,47,31,

    // Esther
    22,23,15,17,14,14,10,17,32,3,

    // Job
    22,13,26,21,27,30,21,22,35,22,20,25,28,22,35,22,16,21,29,29,
    34,30,17,25,6,14,23,28,25,31,40,22,33,37,16,33,24,41,30,24,
    34,17,

    // Psalms
    6,12,8,8,12,10,17,9,20,18,7,8,6,7,5,11,15,50,14,9,
    13,31,6,10,22,12,14,9,11,12,24,11,22,22,28,12,40,22,13,17,
    13,11,5,26,17,11,9,14,20,23,19,9,6,7,23,13,11,11,17,12,
    8,12,11,10,13,20,7,35,36,5,24,20,28,23,10,12,20,72,13,19,
    16,8,18,12,13,17,7,18,52,17,16,15,5,23,11,13,12,9,9,5,
    8,28,22,35,45,48,43,13,31,7,10,10,9,8,18,19,2,29,176,7,
    8,9,4,8,5,6,5,6,8,8,3,18,3,3,21,26,9,8,24,13,
    10,7,12,15,21,10,20,14,9,6,

    // Proverbs
    33,22,35,27,23,35,27,36,18,32,31,28,25,35,33,33,28,24,29,30,
    31,29,35,34,28,28,27,28,27,33,31,

    // Ecclesiastes
    18,26,22,16,20,12,29,17,18,20,10,14,

    // Song_of_Solomon
    17,17,11,16,16,13,13,14,

    // Isaiah
    31,22,26,6,30,13,25,22,21,34,16,6,22,32,9,14,14,7,25,6,
    17,25,18,23,12,21,13,29,24,33,9,20,24,17,10,22,38,22,8,31,
    29,25,28,28,25,13,15,22,26,11,23,15,12,17,13,12,21,14,21,22,
    11,12,19,12,25,24,

    // Jeremiah
    19,37,25,31,31,30,34,22,26,25,23,17,27,22,21,21,27,23,15,18,
    14,30,40,10,38,24,22,17,32,24,40,44,26,22,19,32,21,28,18,16,
    18,22,13,30,5,28,7,47,39,46,64,34,

    // Lamentations
    22,22,66,22,22,

    // Ezekiel
    28,10,27,17,17,14,27,18,11,22,25,28,23,23,8,63,24,32,14,49,
    32,31,49,27,17,21,36,26,21,26,18,32,33,31,15,38,28,23,29,49,
    26,20,27,31,25,24,23,35,

    // Daniel
    21,49,30,37,31,28,28,27,27,21,45,13,

    // Hosea
    11,23,5,19,15,11,16,14,17,15,12,14,16,9,

    // Joel
    20,32,21,

    // Amos
    15,16,15,13,27,14,17,14,15,

    // Obadiah
    21,

    // Jonah
    17,10,10,11,

    // Micah
    16,13,12,13,15,16,20,

    // Nahum
    15,13,19,

    // Habakkuk
    17,20,19,

    // Zephaniah
    18,15,20,

    // Haggai
    15,23,

    // Zechariah
    21,13,10,14,11,15,14,23,17,12,17,14,9,21,

    // Malachi
    14,17,18,6,

    // Matthew
    25,23,17,25,48,34,29,34,38,42,30,50,58,36,39,28,27,35,30,34,
    46,46,39,51,46,75,66,20,

    // Mark
    45,28,35,41,43,56,37,38,50,52,33,44,37,72,47,20,

    // Luke
    80,52,38,44,39,49,50,56,62,42,54,59,35,35,32,31,37,43,48,47,
    38,71,56,53,

    // John
    51,25,36,54,47,71,53,59,41,42,57,50,38,31,27,33,26,40,42,31,
    25,

    // Acts
    26,47,26,37,42,15,60,40,43,48,30,25,52,28,41,40,34,28,41,38,
    40,30,35,27,27,32,44,31,

    // Romans
    32,29,31,25,21,23,25,39,33,21,36,21,14,23,33,27,

    // I_Corinthians
    31,16,23,21,13,20,40,13,27,33,34,31,13,40,58,24,

    // II_Corinthians
    24,17,18,18,21,18,16,24,15,18,33,21,14,

    // Galatians
    24,21,29,31,26,18,

    // Ephesians
    23,22,21,32,33,24,

    // Philippians
    30,30,21,23,

    // Colossians
    29,23,25,18,

    // I_Thessalonians
    10,20,13,18,28,

    // II_Thessalonians
    12,17,18,

    // I_Timothy
    20,15,16,16,25,21,

    // II_Timothy
    18,26,17,22,

    // Titus
    16,15,15,

    // Philemon
    25,

    // Hebrews
    14,18,19,16,14,20,28,13,28,39,40,29,25,

    // James
    27,26,18,17,20,

    // I_Peter
    25,25,22,19,14,

    // II_Peter
    21,22,18,

    // I_John
    10,29,24,21,21,

    // II_John
    13,

    // III_John
    14,

    // Jude
    25,

    // Revelation
    20,29,22,11,14,17,17,13,21,11,19,17,18,20,8,21,18,24,21,15,
    27,21
};

// Index into array's ui8_ChapterVerseArray.
static const swI16 KJV_CV_IndexArray [] =
{
    00, // Alignment
    0,50,90,117,153,187,211,232,236,267,291,313,338,367,403,413,
    426,436,478,628,659,671,679,745,797,802,850,862,876,879,888,
    889,893,900,903,906,909,911,925,929,957,973,997,1018,1046,
    1062,1078,1091,1097,1103,1107,1111,1116,1119,1125,1129,1132,
    1133,1146,1151,1156,1159,1164,1165,1166,1167
};

static const swUI8 KJV_TitleIndexStyleOffSet [] =
{
    00, // Alignment
    0,0,0,0,0,
    0,0,0,67,68,
    69,70,71,72,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    73,74,0,0,0,
    0,75,76,77,78,
    0,0,0,0,79,
    80,81,82,83,0,
    0
};

static const char * KJV_Title [] =
{
    "?",
    "Genesis", "Exodus", "Leviticus", "Numbers",
    "Deuteronomy", "Joshua", "Judges", "Ruth",
    "I Samuel", "II Samuel", "I Kings", "II Kings",
    "I Chronicles", "II Chronicles", "Ezra", "Nehemiah",
    "Esther", "Job", "Psalms", "Proverbs",
    "Ecclesiastes", "Song of Solomon", "Isaiah", "Jeremiah",
    "Lamentations", "Ezekiel", "Daniel", "Hosea",
    "Joel", "Amos", "Obadiah", "Jonah",
    "Micah", "Nahum", "Habakkuk", "Zephaniah",
    "Haggai", "Zechariah", "Malachi", "Matthew",
    "Mark", "Luke", "John", "Acts",
    "Romans", "I Corinthians", "II Corinthians", "Galatians",
    "Ephesians", "Philippians", "Colossians", "I Thessalonians",
    "II Thessalonians", "I Timothy", "II Timothy", "Titus",
    "Philemon", "Hebrews", "James", "I Peter",
    "II Peter", "I John", "II John", "III John",
    "Jude", "Revelation", "1 Samuel", "2 Samuel",
    "1 Kings", "2 Kings", "1 Chronicles", "2 Chronicles",
    "1 Corinthians", "2 Corinthians", "1 Thessalonians", "2 Thessalonians",
    "1 Timothy", "2 Timothy", "1 Peter", "2 Peter",
    "1 John", "2 John", "3 John", "First Samuel",
    "Second Samuel", "First Kings", "Second Kings", "First Chronicles",
    "Second Chronicles", "First Corinthians", "Second Corinthians", "First Thessalonians",
    "Second Thessalonians", "First Timothy", "Second Timothy", "First Peter",
    "Second Peter", "First John", "Second John", "Third John"
};

static const char * KJV_Abbrev [] =
{
    "?",
    "Gen.", "Ex.", "Lev.", "Num.", "Deut.", "Josh.", "Judg.", "Ruth",
    "I Sam.", "II Sam.", "I Kin.", "II Kin.", "I Chr.", "II Chr.",
    "Ezra", "Neh.", "Esth.", "Job", "Ps.", "Prov.", "Eccl.", "Song",
    "Is.", "Jer.", "Lam.", "Ezek.", "Dan.", "Hos.", "Joel", "Amos",
    "Obad.", "Jon.", "Mic.", "Nah.", "Hab.", "Zeph.", "Hag.", "Zech.",
    "Mal.", "Matt.", "Mark", "Luke", "John", "Acts", "Rom.", "I Cor.",
    "II Cor.", "Gal.", "Eph.", "Phil.", "Col.", "I Thess.", "II Thess.",
    "I Tim.", "II Tim.", "Titus", "Philem.", "Heb.", "James", "I Pet.",
    "II Pet.", "I John", "II John", "III John", "Jude", "Rev.", "1 Sam.",
    "2 Sam.", "1 Kin.", "2 Kin.", "1 Chr.", "2 Chr.", "1 Cor.", "2 Cor.",
    "1 Thess.", "2 Thess.", "1 Tim.", "2 Tim.", "1 Pet.", "2 Pet.",
    "1 John", "2 John", "3 John"
};

SwReferenceData::SwReferenceData()
{
    book = 0;
    chapter = 0;
    verseStart = 0;
    verseEnd = 0;
    strongs = 0;
    referenceType = 0;
}

SwReferenceData::~SwReferenceData()
{
}

void SwReferenceData::Display()
{
    SwString a, b, c, d, e;
    a.Itoa((int)book);
    b.Itoa((int)chapter);
    c.Itoa((int)verseStart);
    d.Itoa((int)verseEnd);
    e.Size(1000);
    sprintf(e, "%s %s:%s-%s", a.GetArray(), b.GetArray(), c.GetArray(), d.GetArray());
    wxMessageBox(e.GetArray());
}

swUI8 SwStandardBible::Get_KJV_BookChapters(swUI8 book)
{
    // Verify ui8_Book.
    if ((book < 1 ) || (book > KJV_BOOKS))
        return INVALID_BOOK;

    // Array 'KJV_BookChapterArray' contains the number of chapters in
    // each book.
    // For the number of chapters in a specified book :
    // KJV_BookChapterArray[book number].
    // Books are numbered 1 - 66, Genesis - Revelation,

    return KJV_BookChapterArray[book];
}

// Returns the number of verses for the specified book, and chapter.
swUI8 SwStandardBible::Get_KJV_ChapterVerses(swUI8 book, swUI8 chapter)
{
    // Verify Book.
    if ((book < Genesis) || (book > KJV_BOOKS))
        return INVALID_BOOK;

    // Verify Chapter.
    if ((chapter < 1) || (chapter > KJV_BookChapterArray[book]))
        return INVALID_CHAPTER;

    // Array 'KJV_CV_IndexArray[book number]' provides the
    // position in array 'KJV_ChapterVerseArray' where the book information
    // starts, that position plus 'chapter number' provides
    // the position in array 'KJV_ChapterVerseArray' which will contain
    // the number of verses for specified book, and chapter.

    return KJV_ChapterVerseArray[KJV_CV_IndexArray[book] + chapter];
}

swUI8 SwStandardBible::Get_kJV_BookTitle(swUI8 book, swUI8 flags, SwString & buffer)
{
    swUI8 titlePos;

    // Verify ui8_Book.
    if ((book < Genesis) || (book > KJV_BOOKS))
        return INVALID_BOOK;

    if (flags & STYLE_ROMAN)
        titlePos = book;
    else if (flags & STYLE_DECIMAL)
    {
        titlePos = KJV_TitleIndexStyleOffSet[book];

        if (titlePos == 0)
            titlePos = book;
    }
    else if (flags & STYLE_TEXT)
    {
        titlePos = KJV_TitleIndexStyleOffSet[book] + STYLE_TEXT_OFFSET;

        if (titlePos == STYLE_TEXT_OFFSET)
            titlePos = book;
    }
    else
        return INVALID_STYLE;

    buffer = KJV_Title[titlePos];

    if (flags & STYLE_UPPERCASE)
        strupr(buffer);

    return _OK_;
}

swUI8 SwStandardBible::Get_KJV_BookAbbreviation(swUI8 book, swUI8 flags, SwString & buffer)
{
    swUI8 titlePos;

    // Verify ui8_Book.
    if ((book < Genesis) || (book > KJV_BOOKS))
        return INVALID_BOOK;

    if (flags & STYLE_ROMAN)
        titlePos = book;
    else if (flags & STYLE_DECIMAL)
    {
        titlePos = KJV_TitleIndexStyleOffSet[book];

        if (titlePos == 0)
            titlePos = book;
    }
    else
        return INVALID_STYLE;

    buffer = KJV_Abbrev[titlePos];

    if (flags & STYLE_UPPERCASE)
        strupr(buffer);

    return _OK_;
}

swUI8 SwStandardBible::Get_KJV_ChapterAbbreviation(swUI8 book, swUI8 chapter, swUI8 flags, SwString & buffer)
{
    swUI8 result;

    result = Verify_KJV_Reference(book, chapter, 1);

    if (result != _OK_)
        return result;

    result = Get_KJV_BookAbbreviation(book, flags, buffer);

    if (result != _OK_)
        return result;

    char s[5];
    buffer.Size(strlen(buffer) + 5);
    sprintf(s, " %u", chapter);
    strcat(buffer, s);

    if (flags & STYLE_UPPERCASE)
        strupr(buffer);

    return _OK_;
}

// Verifies that book information is correct.
swUI8 SwStandardBible::Verify_KJV_Reference(swUI8 book, swUI8 chapter, swUI8 verse)
{
    // Verify book.
    if ((book < Genesis) || (book > KJV_BOOKS))
        return INVALID_BOOK;

    // Verify chapter.
    if ((chapter < 1) || (chapter > KJV_BookChapterArray[book]))
        return INVALID_CHAPTER;

    // Verify verse.
    if (verse < 1 || verse > KJV_ChapterVerseArray[KJV_CV_IndexArray[book] + chapter])
        return INVALID_VERSE;

    return _OK_;
}

swUI8 SwStandardBible::IdentifyBibleBookName(const char * name)
{
    if (!name)
        return 0;

    SwStringW buffer;
    buffer.Copy(name);
    buffer.ToLower();
    return IdentifyBibleBookName(buffer.GetArray());
}

swUI8 SwStandardBible::IdentifyBibleBookName(const wchar_t * name)
{
    if (!name)
        return 0;

    swUI8 book = 0;

    wchar_t bookName[256];

    if (wcslen(name) > 255)
        return 0;

    int n = 0, bufferPos = 0;

    while (name[n] != L'\0')
    {
        switch(name[n])
        {
        case L' ' :
        case L'.' :
            break;
        case 0X00E1 :
        case 0X00E4 :
            bookName[bufferPos] = L'a';
            bufferPos ++;
            break;
        case 0X00E9 :
        case 0X00EB :
            bookName[bufferPos] = L'e';
            bufferPos ++;
            break;
        case 0X00ED :
        case 0X00EF :
            bookName[bufferPos] = L'i';
            bufferPos ++;
            break;
        case 0X00F3 :
        case 0X00F6 :
            bookName[bufferPos] = L'o';
            bufferPos ++;
            break;
        case 0X00FA :
            bookName[bufferPos] = L'u';
            bufferPos ++;
            break;
        default :
            bookName[bufferPos] = name[n];
            bufferPos ++;
            break;
        }
        n ++;
    }

    bookName[bufferPos] = L'\0';

    switch(bookName[0])
    {
    case L'a' :
        if (wcscmp(L"abacuc", bookName) == 0 ||  wcscmp(L"ab", bookName) == 0)
            return Habakkuk;
        if (wcscmp(L"abdias", bookName) == 0 || wcscmp(L"abdia", bookName) == 0 || wcscmp(L"abd", bookName) == 0)
            return Obadiah;
        if (wcscmp(L"acts", bookName) == 0 || wcscmp(L"ac", bookName) == 0 || wcscmp(L"apg", bookName) == 0 || wcscmp(L"at", bookName) == 0 ||
                wcscmp(L"atti", bookName) == 0 || wcscmp(L"apostolok", bookName) == 0 || wcscmp(L"actes", bookName) == 0 || wcscmp(L"apostelgeschichte", bookName) == 0 || wcscmp(L"apostelgeschichtedeslukas", bookName) == 0)
            return Acts;
        if (wcscmp(L"ag", bookName) == 0 || wcscmp(L"aggeo", bookName) == 0 || wcscmp(L"aggee", bookName) == 0 || wcscmp(L"aggeus", bookName) == 0)
            return Haggai;
        if (wcscmp(L"amos", bookName) == 0 || wcscmp(L"am", bookName) == 0)
            return Amos;
        if (wcscmp(L"ap", bookName) == 0 || wcscmp(L"apoc", bookName) == 0 || wcscmp(L"apocalisse", bookName) == 0 || wcscmp(L"apocalipsis", bookName) == 0 || wcscmp(L"apocalypse", bookName) == 0)
            return Revelation;
        break;
    case L'b' :
        if (wcscmp(L"birak", bookName) == 0)
            return Judges;
        break;
    case L'c' :
        if (wcscmp(L"col", bookName) == 0 || wcscmp(L"colossians", bookName) == 0 ||
                wcscmp(L"colossesi", bookName) == 0 || wcscmp(L"colosenses", bookName) == 0 || wcscmp(L"colossiens", bookName) == 0)
            return Colossians;
        if (wcscmp(L"cant", bookName) == 0 || wcscmp(L"canticlesofcanticles", bookName) == 0 ||wcscmp(L"canticles", bookName) == 0 ||
                wcscmp(L"cantares", bookName) == 0 || wcscmp(L"cantique", bookName) == 0 ||
                wcscmp(L"ct", bookName) == 0 || wcscmp(L"cantico", bookName) == 0 || wcscmp(L"canticodeicantici", bookName) == 0 || wcscmp(L"cantici", bookName) == 0)
            return Song_of_Solomon;
        break;
    case L'd' :
        if (wcscmp(L"dan", bookName) == 0 || wcscmp(L"daniel", bookName) == 0 || wcscmp(L"da", bookName) == 0 ||
                wcscmp(L"dn", bookName) == 0 || wcscmp(L"daniele", bookName) == 0)
            return Daniel;
        if (wcscmp(L"du", bookName) == 0 || wcscmp(L"dtn", bookName) == 0 || wcscmp(L"dt", bookName) == 0 || wcscmp(L"deut", bookName) == 0 || wcscmp(L"deuteronomy", bookName) == 0 || wcscmp(L"de", bookName) == 0 ||
                wcscmp(L"deuteronomium", bookName) == 0 || wcscmp(L"deuteronomio", bookName) == 0 || wcscmp(L"deuteronome", bookName) == 0)
            return Deuteronomy;
        break;
    case L'e' :
        switch (bookName[1])
        {
        case L'b' :
            if (wcscmp(L"ebrei", bookName) == 0)
                return Hebrews;
            break;
        case L'c' :
            if (wcscmp(L"ecl", bookName) == 0 || wcscmp(L"eccl", bookName) == 0 || wcscmp(L"ecclesiastes", bookName) == 0 || wcscmp(L"eccles", bookName) == 0 || wcscmp(L"ec", bookName) == 0 ||
                    wcscmp(L"eclesiastes", bookName) == 0 || wcscmp(L"ecclesiaste", bookName) == 0)
                return Ecclesiastes;
            break;
        case L'f' :
            if (wcscmp(L"efes", bookName) == 0 || wcscmp(L"ef", bookName) == 0 || wcscmp(L"efesini", bookName) == 0 || wcscmp(L"efezusiakhoz", bookName) == 0 || wcscmp(L"efesios", bookName) == 0)
                return Ephesians;
            break;
        case L'n' :
            if (wcscmp(L"enekekeneke", bookName) == 0 || wcscmp(L"enekek", bookName) == 0)
                return Song_of_Solomon;
            break;
        case L'p' :
            if (wcscmp(L"ephesians", bookName) == 0 || wcscmp(L"eph", bookName) == 0 || wcscmp(L"ep", bookName) == 0 ||
                    wcscmp(L"ephesiens", bookName) == 0 || wcscmp(L"epheser", bookName) == 0)
                return Ephesians;
            break;
        case L's' :
            if (wcscmp(L"esth", bookName) == 0 || wcscmp(L"esther", bookName) == 0 || wcscmp(L"est", bookName) == 0 ||
                    wcscmp(L"eszter", bookName) == 0 || wcscmp(L"ester", bookName) == 0)
                return Esther;
            if (wcscmp(L"esra", bookName) == 0 || wcscmp(L"esdras", bookName) == 0 || wcscmp(L"esdra", bookName) == 0 || wcscmp(L"esd", bookName) == 0
                    || wcscmp(L"esr", bookName) == 0)
                return Ezra;
            if (wcscmp(L"esaie", bookName) == 0)
                return Isaiah;
            if (wcscmp(L"es", bookName) == 0 ||
                    wcscmp(L"esodo", bookName) == 0)
                return Exodus;
            break;
        case L'x' :
            if (wcscmp(L"ex", bookName) == 0 || wcscmp(L"exod", bookName) == 0 || wcscmp(L"exodo", bookName) == 0 || wcscmp(L"exodus", bookName) == 0 ||
                    wcscmp(L"exo", bookName) == 0 || wcscmp(L"exode", bookName) == 0)
                return Exodus;
            break;
        case L'z' :
            if (wcscmp(L"ezek", bookName) == 0 ||  wcscmp(L"ezekiel", bookName) == 0  || wcscmp(L"eze", bookName) == 0 ||
                    wcscmp(L"ezk", bookName) == 0 || wcscmp(L"ez", bookName) == 0 || wcscmp(L"ezeq", bookName) == 0 || wcscmp(L"ezechiel", bookName) == 0 || wcscmp(L"ezequiel", bookName) == 0)
                return Ezekiel;
            if (wcscmp(L"ezra", bookName) == 0 || wcscmp(L"ezr", bookName) == 0 ||
                    wcscmp(L"ezsdras", bookName) == 0)
                return Ezra;
            if (wcscmp(L"ezsaias", bookName) == 0)
                return Isaiah;
            break;
        }
        break;
    case L'f' :
        if (wcscmp(L"flm", bookName) == 0 || wcscmp(L"filem", bookName) == 0 || wcscmp(L"fm", bookName) == 0 || wcscmp(L"filemone", bookName) == 0 || wcscmp(L"filemon", bookName) == 0 || wcscmp(L"filemonhoz", bookName) == 0)
            return Philemon;
        if (wcscmp(L"flp", bookName) == 0 || wcscmp(L"fil", bookName) == 0 || wcscmp(L"filippesi", bookName) == 0 || wcscmp(L"filipenses", bookName) == 0 || wcscmp(L"filippiekhez", bookName) == 0)
            return Philippians;
        break;
    case L'g' :
        if (wcscmp(L"galatians", bookName) == 0 || wcscmp(L"ga", bookName) == 0 || wcscmp(L"gal", bookName) == 0 ||
                wcscmp(L"galati", bookName) == 0 || wcscmp(L"galatakhoz", bookName) == 0 || wcscmp(L"galatas", bookName) == 0 || wcscmp(L"galates", bookName) == 0 || wcscmp(L"galater", bookName) == 0)
            return Galatians;
        if (wcscmp(L"gen", bookName) == 0 || wcscmp(L"genesis", bookName) == 0 || wcscmp(L"ge", bookName) == 0 || wcscmp(L"gn", bookName) == 0 ||
                wcscmp(L"genesi", bookName) == 0 || wcscmp(L"genese", bookName) == 0)
            return Genesis;
        if (wcscmp(L"giobbe", bookName) == 0 || wcscmp(L"gb", bookName) == 0)
            return Job;
        if (wcscmp(L"gioele", bookName) == 0 || wcscmp(L"gl", bookName) == 0)
            return Joel;
        if (wcscmp(L"giona", bookName) == 0 || wcscmp(L"gio", bookName) == 0)
            return Jonah;
        if (wcscmp(L"giovanni", bookName) == 0)
            return John;
        if (wcscmp(L"gv", bookName) == 0)
            return John;
        if (wcscmp(L"giuda", bookName) == 0)
            return Jude;
        if (wcscmp(L"gd", bookName) == 0)
            return Jude;
        if (wcscmp(L"giacomo", bookName) == 0)
            return James;
        if (wcscmp(L"gc", bookName) == 0)
            return James;
        if (wcscmp(L"geremia", bookName) == 0 || wcscmp(L"ger", bookName) == 0)
            return Jeremiah;
        if (wcscmp(L"gs", bookName) == 0 || wcscmp(L"giosue", bookName) == 0)
            return Joshua;
        if (wcscmp(L"gdc", bookName) == 0 || wcscmp(L"giudici", bookName) == 0)
            return Judges;
        break;
    case L'h' :
        switch (bookName[1])
        {
        case L'a' :
        case L'b' :
        case L'g' :
            if (wcscmp(L"hb", bookName) == 0 || wcscmp(L"hab", bookName) == 0 || wcscmp(L"habakkuk", bookName) == 0 ||
                    wcscmp(L"habakuk", bookName) == 0 || wcscmp(L"habacuc", bookName) == 0)
                return Habakkuk;
            if (wcscmp(L"hag", bookName) == 0 || wcscmp(L"haggai", bookName) == 0 ||
                    wcscmp(L"hg", bookName) == 0 || wcscmp(L"hageo", bookName) == 0)
                return Haggai;
            break;
        case L'c' :
            if (wcscmp(L"hch", bookName) == 0)
                return Acts;
            break;
        case L'e' :
            if (wcscmp(L"he", bookName) == 0 || wcscmp(L"hebr", bookName) == 0 || wcscmp(L"heb", bookName) == 0 || wcscmp(L"hebrews", bookName) == 0 ||
                    wcscmp(L"hebreos", bookName) == 0 || wcscmp(L"hebreux", bookName) == 0 || wcscmp(L"hebraer", bookName) == 0)
                return Hebrews;
            if (wcscmp(L"hechos", bookName) == 0 || wcscmp(L"he", bookName) == 0 || wcscmp(L"hech", bookName) == 0)
                return Acts;
            if (wcscmp(L"hesekiel", bookName) == 0)
                return Ezekiel;
            break;
        case L'i' :
            if (wcscmp(L"hiob", bookName) == 0)
                return Job;
            break;
        case L'o' :
            if (wcscmp(L"hos", bookName) == 0 || wcscmp(L"hosea", bookName) == 0 || wcscmp(L"ho", bookName) == 0 ||
                    wcscmp(L"hoseas", bookName) == 0)
                return Hosea;
            if (wcscmp(L"hoh", bookName) == 0 || wcscmp(L"hoheliedsalmos", bookName) == 0 || wcscmp(L"hohelied", bookName) == 0)
                return Song_of_Solomon;
            break;
        }
        break;
    case L'i' :
        switch (bookName[1])
        {
        case L'c' :
            if (wcscmp(L"ichr", bookName) == 0 || wcscmp(L"ich", bookName) == 0 || wcscmp(L"ichron", bookName) == 0 || wcscmp(L"ichronicles", bookName) == 0 ||
                    wcscmp(L"icronache", bookName) == 0 || wcscmp(L"ichronik", bookName) == 0 || wcscmp(L"icronicas", bookName) == 0 || wcscmp(L"ichronicas", bookName) == 0 ||
                    wcscmp(L"icr", bookName) == 0 || wcscmp(L"icro", bookName) == 0 || wcscmp(L"icron", bookName) == 0)
                return I_Chronicles;
            if (wcscmp(L"icor", bookName) == 0 || wcscmp(L"ico", bookName) == 0 || wcscmp(L"icorinthians", bookName) == 0 ||
                    wcscmp(L"icorinzi", bookName) == 0 || wcscmp(L"icorintios", bookName) == 0 || wcscmp(L"icorinthiens", bookName) == 0)
                return I_Corinthians;
            break;
        case L'g' :
            if (wcscmp(L"igv", bookName) == 0 || wcscmp(L"igiovanni", bookName) == 0)
                return I_John;
            break;
        case L'j' :
            if (wcscmp(L"ijob", bookName) == 0)
                return Job;
            if (wcscmp(L"ijohn", bookName) == 0 || wcscmp(L"ijn", bookName) == 0 || wcscmp(L"ijoh", bookName) == 0 || wcscmp(L"ijo", bookName) == 0 ||
                    wcscmp(L"ijanos", bookName) == 0 || wcscmp(L"ijuan", bookName) == 0 || wcscmp(L"ijean", bookName) == 0 || wcscmp(L"ijohannes", bookName) == 0)
                return I_John;
            break;
        case L'k' :
            if (wcscmp(L"ikin", bookName) == 0 || wcscmp(L"iki", bookName) == 0 || wcscmp(L"ikings", bookName) == 0 ||
                    wcscmp(L"ikonige", bookName) == 0 || wcscmp(L"ikiralyok", bookName) == 0)
                return I_Kings;
            if (wcscmp(L"ikorinther", bookName) == 0)
                return I_Corinthians;
            if (wcscmp(L"ikronika", bookName) == 0 ||
                    wcscmp(L"ikr", bookName) == 0 || wcscmp(L"ikro", bookName) == 0 || wcscmp(L"ikron", bookName) == 0)
                return I_Chronicles;
            if (wcscmp(L"ikor", bookName) == 0 || wcscmp(L"ikorintusi", bookName) == 0)
                return I_Corinthians;
            break;
        case L'm' :
            if (wcscmp(L"imozes", bookName) == 0 || wcscmp(L"imoz", bookName) == 0)
                return Genesis;
            break;
        case L'p' :
            if (wcscmp(L"ipt", bookName) == 0 || wcscmp(L"ipetr", bookName) == 0 || wcscmp(L"ipet", bookName) == 0 || wcscmp(L"ipe", bookName) == 0 || wcscmp(L"ipeter", bookName) == 0 ||
                    wcscmp(L"ipietro", bookName) == 0 || wcscmp(L"ipedro", bookName) == 0 || wcscmp(L"ipierre", bookName) == 0 || wcscmp(L"ipetrus", bookName) == 0)
                return I_Peter;
            break;
        case L'r' :
            if (wcscmp(L"ire", bookName) == 0 || wcscmp(L"ireyes", bookName) == 0 || wcscmp(L"irois", bookName) == 0)
                return I_Kings;
        case L's' :
            if (wcscmp(L"is", bookName) == 0 || wcscmp(L"isa", bookName) == 0 || wcscmp(L"isaiah", bookName) == 0 ||
                    wcscmp(L"isaia", bookName) == 0 || wcscmp(L"isaias", bookName) == 0)
                return Isaiah;
            if (wcscmp(L"isam", bookName) == 0 || wcscmp(L"isa", bookName) == 0 || wcscmp(L"isamuel", bookName) == 0 ||
                    wcscmp(L"isamuele", bookName) == 0)
                return I_Samuel;
            break;
        case L't' :
            if (wcscmp(L"its", bookName) == 0 || wcscmp(L"ites", bookName) == 0 || wcscmp(L"ith", bookName) == 0 || wcscmp(L"ithes", bookName) == 0 || wcscmp(L"ithess", bookName) == 0 || wcscmp(L"ith", bookName) == 0 || wcscmp(L"ithessalonians", bookName) == 0 ||
                    wcscmp(L"itessalonicesi", bookName) == 0 || wcscmp(L"itesszalonika", bookName) == 0 || wcscmp(L"itesalonicenses", bookName) == 0 || wcscmp(L"ithessalonicien", bookName) == 0 || wcscmp(L"ithessalonicher", bookName) == 0)
                return I_Thessalonians;
            if (wcscmp(L"itm", bookName) == 0 || wcscmp(L"itim", bookName) == 0 || wcscmp(L"iti", bookName) == 0 || wcscmp(L"itimothy", bookName) == 0 ||
                    wcscmp(L"itimoteushoz", bookName) == 0 || wcscmp(L"itimoteo", bookName) == 0 || wcscmp(L"itimothee", bookName) == 0 || wcscmp(L"itimotheus", bookName) == 0)
                return I_Timothy;
            break;
        case L'i' :
            switch (bookName[3])
            {
            case L'a' :
                if (wcscmp(L"iisam", bookName) == 0 || wcscmp(L"iisamuel", bookName) == 0 || wcscmp(L"iisa", bookName) == 0 ||
                        wcscmp(L"iisamuele", bookName) == 0)
                    return II_Samuel;
                if (wcscmp(L"iijanos", bookName) == 0)
                    return II_John;
                break;
            case L'g' :
                if (wcscmp(L"iiigv", bookName) == 0 || wcscmp(L"iiigiovanni", bookName) == 0)
                    return III_John;
                break;
            case L'h' :
                if (wcscmp(L"iichr", bookName) == 0 || wcscmp(L"iich", bookName) == 0 || wcscmp(L"iichron", bookName) == 0 || wcscmp(L"iichronicles", bookName) == 0 ||
                        wcscmp(L"iichronik", bookName) == 0 || wcscmp(L"iichronicas", bookName) == 0)
                    return II_Chronicles;
                if (wcscmp(L"iithes", bookName) == 0 || wcscmp(L"iithess", bookName) == 0 || wcscmp(L"iith", bookName) == 0 || wcscmp(L"iithessalonians", bookName) == 0 ||
                        wcscmp(L"iithessalonicien", bookName) == 0 || wcscmp(L"iithessalonicher", bookName) == 0)
                    return II_Thessalonians;
                break;
            case L'n' :
                if (wcscmp(L"iijn", bookName) == 0)
                    return II_John;
                break;
            case L'o' :
                if (wcscmp(L"iicor", bookName) == 0 || wcscmp(L"iico", bookName) == 0 || wcscmp(L"iicorinthians", bookName) == 0 ||
                        wcscmp(L"iicorinzi", bookName) == 0 || wcscmp(L"iikor", bookName) == 0 || wcscmp(L"iikorinther", bookName) == 0 || wcscmp(L"iicorintios", bookName) == 0 || wcscmp(L"iicorinthiens", bookName) == 0 || wcscmp(L"iikorintusi", bookName) == 0)
                    return II_Corinthians;
                if (wcscmp(L"iijohn", bookName) == 0 || wcscmp(L"iijoh", bookName) == 0 || wcscmp(L"iijo", bookName) == 0 ||
                        wcscmp(L"iijohannes", bookName) == 0)
                    return II_John;
                if (wcscmp(L"iikonige", bookName) == 0 || wcscmp(L"iirois", bookName) == 0)
                    return II_Kings;
                if (wcscmp(L"iimozes", bookName) == 0 || wcscmp(L"iimoz", bookName) == 0)
                    return Exodus;
                if (wcscmp(L"ivmozes", bookName) == 0 || wcscmp(L"ivmoz", bookName) == 0)
                    return Numbers;
                break;
            case L'i' :
                if (wcscmp(L"iikin", bookName) == 0 || wcscmp(L"iiki", bookName) == 0 || wcscmp(L"iikings", bookName) == 0 ||
                        wcscmp(L"iikiralyok", bookName) == 0)
                    return II_Kings;
                if (wcscmp(L"iitim", bookName) == 0 || wcscmp(L"iiti", bookName) == 0 || wcscmp(L"iitimothy", bookName) == 0 ||
                        wcscmp(L"iitimoteushoz", bookName) == 0 || wcscmp(L"iitimoteo", bookName) == 0 || wcscmp(L"iitimothee", bookName) == 0 || wcscmp(L"iitimotheus", bookName) == 0)
                    return II_Timothy;
                if (wcscmp(L"iipietro", bookName) == 0 || wcscmp(L"iipierre", bookName) == 0)
                    return II_Peter;
                if (wcscmp(L"iigiovanni", bookName) == 0)
                    return II_John;
                break;
            case L's' :
                if (wcscmp(L"iits", bookName) == 0)
                    return II_Thessalonians;
                break;
            case L't' :
                if (wcscmp(L"iipt", bookName) == 0)
                    return II_Peter;
                break;
            case L'e' :
                if (wcscmp(L"iites", bookName) == 0 || wcscmp(L"iitessalonicesi", bookName) == 0 || wcscmp(L"iitesszalonika", bookName) == 0 || wcscmp(L"iitesalonicenses", bookName) == 0)
                    return II_Thessalonians;
                if (wcscmp(L"iire", bookName) == 0 || wcscmp(L"iireyes", bookName) == 0)
                    return II_Kings;
                if (wcscmp(L"iipetr", bookName) == 0 || wcscmp(L"iipet", bookName) == 0 || wcscmp(L"iipeter", bookName) == 0 || wcscmp(L"iipe", bookName) == 0 ||
                        wcscmp(L"iipedro", bookName) == 0 || wcscmp(L"iipetrus", bookName) == 0)
                    return II_Peter;
                if (wcscmp(L"iijean", bookName) == 0)
                    return II_John;
                break;
            case L'j' :
                if (wcscmp(L"iiijohn", bookName) == 0 || wcscmp(L"iiijoh", bookName) == 0 || wcscmp(L"iiijn", bookName) == 0 || wcscmp(L"iiijo", bookName) == 0 ||
                        wcscmp(L"iiijanos", bookName) == 0 || wcscmp(L"iiijuan", bookName) == 0 || wcscmp(L"iiijean", bookName) == 0 || wcscmp(L"iiijohannes", bookName) == 0)
                    return III_John;
                break;
            case L'm' :
                if (wcscmp(L"iitm", bookName) == 0)
                    return II_Timothy;
                if (wcscmp(L"iiimozes", bookName) == 0 || wcscmp(L"iiimoz", bookName) == 0)
                    return Leviticus;
                break;
            case L'r' :
                if (wcscmp(L"iicronache", bookName) == 0 || wcscmp(L"iicronicas", bookName) == 0 || wcscmp(L"iikronika", bookName) == 0 ||
                        wcscmp(L"iicr", bookName) == 0 || wcscmp(L"iicro", bookName) == 0 || wcscmp(L"iicron", bookName) == 0 ||
                        wcscmp(L"iikr", bookName) == 0 || wcscmp(L"iikro", bookName) == 0 || wcscmp(L"iikron", bookName) == 0)
                    return II_Chronicles;
                break;
            case L'u' :
                if (wcscmp(L"iijuan", bookName) == 0)
                    return II_John;
                break;
            case L'v' :
                if (wcscmp(L"iigv", bookName) == 0)
                    return II_John;
                break;
            default :
                return 0;
            }
            break;
        }
        break;
    case L'j' :
        switch (bookName[1])
        {
        case L'a' :
            if (wcscmp(L"janos", bookName) == 0)
                return John;
            if (wcscmp(L"james", bookName) == 0 || wcscmp(L"ja", bookName) == 0 || wcscmp(L"jas", bookName) == 0 ||
                    wcscmp(L"jam", bookName) == 0 || wcscmp(L"jak", bookName) == 0 || wcscmp(L"jakab", bookName) == 0 || wcscmp(L"jacques", bookName) == 0 || wcscmp(L"jakobus", bookName) == 0)
                return James;
            break;
        case L'b' :
            if (wcscmp(L"jb", bookName) == 0)
                return Job;
            break;
        case L'c' :
        case L'd' :
        case L'g' :
            if (wcscmp(L"jdg", bookName) == 0 || wcscmp(L"jc", bookName) == 0 || wcscmp(L"jg", bookName) == 0)
                return Judges;
            if (wcscmp(L"jds", bookName) == 0)
                return Jude;
            break;
        case L'r' :
        case L'e' :
            if (wcscmp(L"jelenesek", bookName) == 0)
                return Revelation;
            if (wcscmp(L"jr", bookName) == 0 || wcscmp(L"jer", bookName) == 0 || wcscmp(L"jeremiah", bookName) == 0 ||
                    wcscmp(L"jeremie", bookName) == 0 || wcscmp(L"jeremias", bookName) == 0 || wcscmp(L"jeremia", bookName) == 0)
                return Jeremiah;
            if (wcscmp(L"jeremiassir", bookName) == 0)
                return Lamentations;
            if (wcscmp(L"jes", bookName) == 0 || wcscmp(L"jesaja", bookName) == 0)
                return Isaiah;
            if (wcscmp(L"jean", bookName) == 0)
                return John;
            break;
        case L'n' :
            if (wcscmp(L"jn", bookName) == 0)
                return John;
            break;
        case L'l' :
            if (wcscmp(L"jl", bookName) == 0)
                return Joel;
        case L'o' :
            if (wcscmp(L"job", bookName) == 0)
                return Job;
            if (wcscmp(L"joel", bookName) == 0 || wcscmp(L"joe", bookName) == 0)
                return Joel;
            if (wcscmp(L"john", bookName) == 0 || wcscmp(L"joh", bookName) == 0 || wcscmp(L"jo", bookName) == 0 ||
                    wcscmp(L"johannes", bookName) == 0)
                return John;
            if (wcscmp(L"jonah", bookName) == 0 || wcscmp(L"jon", bookName) == 0 ||
                    wcscmp(L"jona", bookName) == 0 || wcscmp(L"jonas", bookName) == 0)
                return Jonah;
            if (wcscmp(L"josh", bookName) == 0 || wcscmp(L"joshua", bookName) == 0 || wcscmp(L"jo", bookName) == 0 || wcscmp(L"jos", bookName) == 0 ||
                    wcscmp(L"jozsue", bookName) == 0 || wcscmp(L"josua", bookName) == 0 || wcscmp(L"josue", bookName) == 0)
                return Joshua;
            break;
        case L'u' :
            if (wcscmp(L"judg", bookName) == 0 || wcscmp(L"judges", bookName) == 0 || wcscmp(L"jud", bookName) == 0 ||
                    wcscmp(L"jue", bookName) == 0 || wcscmp(L"jueces", bookName) == 0 || wcscmp(L"juges", bookName) == 0)
                return Judges;
            if (wcscmp(L"jud", bookName) == 0 || wcscmp(L"jude", bookName) == 0 || wcscmp(L"judas", bookName) == 0)
                return Jude;
            if (wcscmp(L"juan", bookName) == 0)
                return John;
            break;
        }
        break;
    case L'k' :
        switch (bookName[1])
        {
        case L'l' :
            if (wcscmp(L"klag", bookName) == 0 || wcscmp(L"klgl", bookName) == 0 || wcscmp(L"klageliederjeremias", bookName) == 0 || wcscmp(L"klageliederjeremias", bookName) == 0 || wcscmp(L"klagelieder", bookName) == 0)
                return Lamentations;
            break;
        case L'o' :
            if (wcscmp(L"kohelet", bookName) == 0 || wcscmp(L"koh", bookName) == 0)
                return Ecclesiastes;
            if (wcscmp(L"kol", bookName) == 0 || wcscmp(L"kolosser", bookName) == 0 || wcscmp(L"kolosseiakhoz", bookName) == 0)
                return Colossians;
            break;
        }
        break;
    case L'l' :
        switch (bookName[1])
        {
        case L'a' :
            if (wcscmp(L"lam", bookName) == 0 || wcscmp(L"lamentations", bookName) == 0 || wcscmp(L"la", bookName) == 0 ||
                    wcscmp(L"lamentazioni", bookName) == 0 || wcscmp(L"lamentaciones", bookName) == 0)
                return Lamentations;
            break;
        case L'c' :
            if (wcscmp(L"lc", bookName) == 0)
                return Luke;
        case L'e' :
            if (wcscmp(L"lev", bookName) == 0 || wcscmp(L"leviticus", bookName) == 0 || wcscmp(L"le", bookName) == 0 ||
                    wcscmp(L"levitikus", bookName) == 0 || wcscmp(L"levitique", bookName) == 0 || wcscmp(L"levitico", bookName) == 0)
                return Leviticus;
            break;
        case L'k' :
            if (wcscmp(L"lk", bookName) == 0)
                return Luke;
            break;
        case L'u' :
            if (wcscmp(L"luke", bookName) == 0 || wcscmp(L"lu", bookName) == 0 ||
                    wcscmp(L"lukacs", bookName) == 0 || wcscmp(L"luca", bookName) == 0 || wcscmp(L"lucas", bookName) == 0 || wcscmp(L"luc", bookName) == 0 || wcscmp(L"lukas", bookName) == 0)
                return Luke;
            break;
        case L'v' :
            if (wcscmp(L"lv", bookName) == 0)
                return Leviticus;
            break;
        }
        break;
    case L'm' :
        switch (bookName[1])
        {
        case L'l' :
            if (wcscmp(L"ml", bookName) == 0)
                return Malachi;
            break;
        case L'a' :
            if (wcscmp(L"malachi", bookName) == 0 || wcscmp(L"mal", bookName) == 0 ||
                    wcscmp(L"malakias", bookName) == 0 || wcscmp(L"maleachi", bookName) == 0 || wcscmp(L"malachia", bookName) == 0 || wcscmp(L"malachie", bookName) == 0 || wcscmp(L"malaquias", bookName) == 0)
                return Malachi;
            if (wcscmp(L"mark", bookName) == 0 ||
                    wcscmp(L"marc", bookName) == 0 || wcscmp(L"marco", bookName) == 0 || wcscmp(L"marcos", bookName) == 0 || wcscmp(L"marc", bookName) == 0 || wcscmp(L"markus", bookName) == 0)
                return Mark;
            if (wcscmp(L"mat", bookName) == 0 || wcscmp(L"matt", bookName) == 0 || wcscmp(L"matthew", bookName) == 0 ||
                    wcscmp(L"mate", bookName) == 0 || wcscmp(L"matteo", bookName) == 0 || wcscmp(L"mateo", bookName) == 0 || wcscmp(L"matthieu", bookName) == 0 || wcscmp(L"matthaus", bookName) == 0)
                return Matthew;
            break;
        case L'i' :
            if (wcscmp(L"micah", bookName) == 0 || wcscmp(L"mic", bookName) == 0 ||
                    wcscmp(L"mikeas", bookName) == 0 || wcscmp(L"micha", bookName) == 0 || wcscmp(L"michea", bookName) == 0 || wcscmp(L"michee", bookName) == 0 || wcscmp(L"miqueas", bookName) == 0 ||
                    wcscmp(L"mik", bookName) == 0 || wcscmp(L"mi", bookName) == 0 ||wcscmp(L"miq", bookName) == 0 || wcscmp(L"mich", bookName) == 0)
                return Micah;
            break;
        case L'k' :
            if (wcscmp(L"mk", bookName) == 0)
                return Mark;
            break;
        case L'r' :
            if (wcscmp(L"mr", bookName) == 0)
                return Mark;
            break;
        case L'c' :
            if (wcscmp(L"mc", bookName) == 0)
                return Mark;
            break;
        case L't' :
            if (wcscmp(L"mt", bookName) == 0)
                return Matthew;
        }
        break;
    case L'n' :
    {
        switch (bookName[1])
        {
        case L'a' :
            if (wcscmp(L"nah", bookName) == 0 || wcscmp(L"nahum", bookName) == 0 || wcscmp(L"na", bookName) == 0)
                return Nahum;
            break;
        case L'b' :
            if (wcscmp(L"nb", bookName) == 0)
                return Numbers;
        case L'e' :
            if (wcscmp(L"neh", bookName) == 0 || wcscmp(L"nehemiah", bookName) == 0 || wcscmp(L"ne", bookName) == 0 ||
                    wcscmp(L"neemia", bookName) == 0 || wcscmp(L"nehemia", bookName) == 0 || wcscmp(L"nehemias", bookName) == 0 || wcscmp(L"nehemie", bookName) == 0)
                return Nehemiah;
            break;
        case L'm' :
            if (wcscmp(L"nm", bookName) == 0)
                return Numbers;
        case L'o' :
            if (wcscmp(L"no", bookName) == 0 || wcscmp(L"nom", bookName) == 0 || wcscmp(L"nombres", bookName) == 0)
                return Numbers;
            break;
        case L'u' :
            if (wcscmp(L"num", bookName) == 0 || wcscmp(L"numbers", bookName) == 0 || wcscmp(L"nu", bookName) == 0 ||
                    wcscmp(L"numeri", bookName) == 0 || wcscmp(L"numeros", bookName) == 0)
                return Numbers;
            break;
        }
    }
    break;
    case L'o' :
        if (wcscmp(L"obad", bookName) == 0 || wcscmp(L"obadiah", bookName) == 0 || wcscmp(L"ob", bookName) == 0 ||
                wcscmp(L"obadja", bookName) == 0 || wcscmp(L"obd", bookName) == 0)
            return Obadiah;
        if (wcscmp(L"os", bookName) == 0 || wcscmp(L"osea", bookName) == 0 || wcscmp(L"oseas", bookName) == 0 || wcscmp(L"osee", bookName) == 0)
            return Hosea;
        if (wcscmp(L"offenbarung", bookName) == 0 || wcscmp(L"offb", bookName) == 0 || wcscmp(L"offenbarungdesjohannes", bookName) == 0)
            return Revelation;
        break;
    case L'p' :
        switch (bookName[1])
        {
        case L'e' :
            if (wcscmp(L"peldabeszedek", bookName) == 0)
                return Proverbs;
            break;
        case L'h' :
            if (wcscmp(L"philem", bookName) == 0 || wcscmp(L"philemon", bookName) == 0 || wcscmp(L"phm", bookName) == 0)
                return Philemon;
            if (wcscmp(L"phil", bookName) == 0 || wcscmp(L"philippians", bookName) == 0 || wcscmp(L"php", bookName) == 0 ||
                    wcscmp(L"philippiens", bookName) == 0 || wcscmp(L"philipper", bookName) == 0)
                return Philippians;
            break;
        case L'r' :
            if (wcscmp(L"prov", bookName) == 0 || wcscmp(L"proverbs", bookName) == 0 || wcscmp(L"pr", bookName) == 0 ||
                    wcscmp(L"proverbi", bookName) == 0 || wcscmp(L"proverbios", bookName) == 0 || wcscmp(L"proverbes", bookName) == 0)
                return Proverbs;
            if (wcscmp(L"predikator", bookName) == 0)
                return Ecclesiastes;
            break;
        case L's' :
            if (wcscmp(L"ps", bookName) == 0 || wcscmp(L"psa", bookName) == 0 || wcscmp(L"psalms", bookName) == 0 || wcscmp(L"psalm", bookName) == 0 ||
                    wcscmp(L"psalter", bookName) == 0 || wcscmp(L"psaumes", bookName) == 0)
                return Psalms;
            break;
        }
        break;
    case L'q' :
        if (wcscmp(L"qoheleth", bookName) == 0 || wcscmp(L"qoh", bookName) == 0)
            return Ecclesiastes;
        break;
    case L'r' :
        switch (bookName[1])
        {
        case L'e' :
        case L'v' :
            if (wcscmp(L"rv", bookName) == 0 || wcscmp(L"rev", bookName) == 0 || wcscmp(L"revelation", bookName) == 0 || wcscmp(L"re", bookName) == 0)
                return Revelation;
            break;
        case L'i' :
            if (wcscmp(L"richter", bookName) == 0 || wcscmp(L"richter", bookName) == 0)
                return Judges;
            break;
        case L'm' :
            if (wcscmp(L"rm", bookName) == 0)
                return Romans;
            break;
        case L'o' :
            if (wcscmp(L"rom", bookName) == 0 || wcscmp(L"romans", bookName) == 0 || wcscmp(L"ro", bookName) == 0 ||
                    wcscmp(L"romani", bookName) == 0 || wcscmp(L"romaiakhoz", bookName) == 0 || wcscmp(L"romanos", bookName) == 0 || wcscmp(L"romains", bookName) == 0 || wcscmp(L"romer", bookName) == 0)
                return Romans;
            break;
        case L't' :
            if (wcscmp(L"rt", bookName) == 0)
                return Ruth;
            break;
        case L'u' :
            if (wcscmp(L"ruth", bookName) == 0 || wcscmp(L"ru", bookName) == 0 ||
                    wcscmp(L"rut", bookName) == 0)
                return Ruth;
            break;
        }
        break;
    case L's' :
        switch (bookName[1])
        {
        case L'a' :
        case L't' :
            if (wcscmp(L"santiago", bookName) == 0 || wcscmp(L"stgo", bookName) == 0 || wcscmp(L"st", bookName) == 0 || wcscmp(L"sant", bookName) == 0)
                return James;
            if (wcscmp(L"sacharja", bookName) == 0 ||wcscmp(L"sach", bookName) == 0)
                return Zechariah;
            if (wcscmp(L"sal", bookName) == 0 || wcscmp(L"salmos", bookName) == 0 || wcscmp(L"salmi", bookName) == 0)
                return Psalms;
            break;
        case L'p' :
            if (wcscmp(L"sprichworter", bookName) == 0)
                return Proverbs;
            break;
        case L'o' :
            if (wcscmp(L"song", bookName) == 0 || wcscmp(L"songofsolomon", bookName) == 0 || wcscmp(L"solomon", bookName) == 0  || wcscmp(L"sol", bookName) == 0)
                return Song_of_Solomon;
            if (wcscmp(L"so", bookName) == 0 || wcscmp(L"sof", bookName) == 0 || wcscmp(L"sofonia", bookName) == 0 || wcscmp(L"sofonias", bookName) == 0 || wcscmp(L"sophonie", bookName) == 0)
                return Zephaniah;
            break;
        }
        break;
    case L't' :
        if (wcscmp(L"titus", bookName) == 0 || wcscmp(L"tit", bookName) == 0 || wcscmp(L"tt", bookName) == 0 || wcscmp(L"ti", bookName) == 0 ||
                wcscmp(L"titushoz", bookName) == 0 || wcscmp(L"tito", bookName) == 0 || wcscmp(L"tite", bookName) == 0)
            return Titus;
        break;
    case L'v' :
        if (wcscmp(L"vmozes", bookName) == 0 || wcscmp(L"vmoz", bookName) == 0)
            return Deuteronomy;
        break;
    case L'z' :
        if (wcscmp(L"zech", bookName) == 0 || wcscmp(L"zechar", bookName) == 0 || wcscmp(L"zechariah", bookName) == 0 || wcscmp(L"zec", bookName) == 0 ||
                wcscmp(L"zac", bookName) == 0 || wcscmp(L"za", bookName) == 0 || wcscmp(L"zakarias", bookName) == 0 || wcscmp(L"zaccaria", bookName) == 0 || wcscmp(L"zacarias", bookName) == 0 || wcscmp(L"zacharie", bookName) == 0)
            return Zechariah;
        if (wcscmp(L"zeph", bookName) == 0 || wcscmp(L"zephaniah", bookName) == 0 || wcscmp(L"zep", bookName) == 0 ||
                wcscmp(L"zef", bookName) == 0 || wcscmp(L"zefanja", bookName) == 0)
            return Zephaniah;
        if (wcscmp(L"zsidokhoz", bookName) == 0)
            return Hebrews;
        if (wcscmp(L"zsoltarok", bookName) == 0)
            return Psalms;
        break;
    case L'1' :
        switch (bookName[1])
        {
        case L'c' :
            if (wcscmp(L"1ch", bookName) == 0 || wcscmp(L"1chr", bookName) == 0 || wcscmp(L"1chron", bookName) == 0 || wcscmp(L"1chronicles", bookName) == 0 ||
                    wcscmp(L"1cronache", bookName) == 0 || wcscmp(L"1chronik", bookName) == 0 || wcscmp(L"1chroniques", bookName) == 0 || wcscmp(L"1cronicas", bookName) == 0 ||
                    wcscmp(L"1cr", bookName) == 0 || wcscmp(L"1cro", bookName) == 0 || wcscmp(L"1cron", bookName) == 0)
                return I_Chronicles;
            if (wcscmp(L"1co", bookName) == 0 || wcscmp(L"1cor", bookName) == 0 || wcscmp(L"1corinthians", bookName) == 0 ||
                    wcscmp(L"1corinzi", bookName) == 0 || wcscmp(L"1corintios", bookName) == 0 || wcscmp(L"1corinthiens", bookName) == 0)
                return I_Corinthians;
            break;
        case L'g' :
            if (wcscmp(L"1gv", bookName) == 0 || wcscmp(L"1giovanni", bookName) == 0)
                return I_John;
            break;
        case L'j' :
            if (wcscmp(L"1jo", bookName) == 0 || wcscmp(L"1john", bookName) == 0  || wcscmp(L"1joh", bookName) == 0 || wcscmp(L"1jn", bookName) == 0 ||
                    wcscmp(L"1janos", bookName) == 0 || wcscmp(L"1juan", bookName) == 0 || wcscmp(L"1jean", bookName) == 0 || wcscmp(L"1johannes", bookName) == 0)
                return I_John;
            break;
        case L'k' :
            if (wcscmp(L"1ki", bookName) == 0 || wcscmp(L"1kin", bookName) == 0 || wcscmp(L"1kings", bookName) == 0 ||
                    wcscmp(L"1konige", bookName) == 0 || wcscmp(L"1kiralyok", bookName) == 0)
                return I_Kings;
            if (wcscmp(L"1korinther", bookName) == 0)
                return I_Corinthians;
            if (wcscmp(L"1kronika", bookName) == 0 ||
                    wcscmp(L"1kr", bookName) == 0 || wcscmp(L"1kro", bookName) == 0 || wcscmp(L"1kron", bookName) == 0)
                return I_Chronicles;
            if (wcscmp(L"1kor", bookName) == 0 || wcscmp(L"1korintusi", bookName) == 0)
                return I_Corinthians;
            break;
        case L'm' :
            if (wcscmp(L"1mozes", bookName) == 0 || wcscmp(L"1moz", bookName) == 0)
                return Genesis;
            break;
        case L'p' :
            if (wcscmp(L"1pt", bookName) == 0 || wcscmp(L"1pe", bookName) == 0 || wcscmp(L"1pet", bookName) == 0 || wcscmp(L"1petr", bookName) == 0 || wcscmp(L"1peter", bookName) == 0 ||
                    wcscmp(L"1pietro", bookName) == 0 || wcscmp(L"1pedro", bookName) == 0 || wcscmp(L"1pierre", bookName) == 0 || wcscmp(L"1petrus", bookName) == 0)
                return I_Peter;
            break;
        case L'r' :
            if (wcscmp(L"1re", bookName) == 0 || wcscmp(L"1reyes", bookName) == 0 || wcscmp(L"1rois", bookName) == 0)
                return I_Kings;
            break;
        case L's' :
            if (wcscmp(L"1sa", bookName) == 0 || wcscmp(L"1sam", bookName) == 0 || wcscmp(L"1samuel", bookName) == 0 ||
                    wcscmp(L"1samuele", bookName) == 0)
                return I_Samuel;
            break;
        case L't' :
            if (wcscmp(L"1ts", bookName) == 0 || wcscmp(L"1tes", bookName) == 0 || wcscmp(L"1th", bookName) == 0 || wcscmp(L"1thes", bookName) == 0 || wcscmp(L"1thess", bookName) == 0 || wcscmp(L"1thessalonians", bookName) == 0 ||
                    wcscmp(L"1tesszalonika", bookName) == 0 || wcscmp(L"1tesalonicenses", bookName) == 0 || wcscmp(L"1thessalonicien", bookName) == 0 || wcscmp(L"1thessalonicher", bookName) == 0 ||
                    wcscmp(L"1tessalonicesi", bookName) == 0)
                return I_Thessalonians;
            if (wcscmp(L"1ti", bookName) == 0 || wcscmp(L"1tim", bookName) == 0 || wcscmp(L"1timothy", bookName) == 0 ||
                    wcscmp(L"1timoteushoz", bookName) == 0 || wcscmp(L"1timoteo", bookName) == 0 || wcscmp(L"1timothee", bookName) == 0 || wcscmp(L"1timotheus", bookName) == 0)
                return I_Timothy;
            break;
        }
        break;
    case L'2' :
        switch (bookName[1])
        {
        case L'c' :
            if (wcscmp(L"2ch", bookName) == 0 || wcscmp(L"2chr", bookName) == 0 || wcscmp(L"2chron", bookName) == 0 || wcscmp(L"2chronicles", bookName) == 0 ||
                    wcscmp(L"2cronache", bookName) == 0 || wcscmp(L"2chronik", bookName) == 0 || wcscmp(L"2cronicas", bookName) == 0 || wcscmp(L"2chronicas", bookName) == 0 ||
                    wcscmp(L"2cr", bookName) == 0 || wcscmp(L"2cro", bookName) == 0 || wcscmp(L"2cron", bookName) == 0)
                return II_Chronicles;
            if (wcscmp(L"2co", bookName) == 0 || wcscmp(L"2cor", bookName) == 0 || wcscmp(L"2corinthians", bookName) == 0 ||
                    wcscmp(L"2corinzi", bookName) == 0 || wcscmp(L"2corintios", bookName) == 0 || wcscmp(L"2corinthiens", bookName) == 0)
                return II_Corinthians;
            break;
        case L'g' :
            if (wcscmp(L"2gv", bookName) == 0 || wcscmp(L"2giovanni", bookName) == 0)
                return II_John;
            break;
        case L'j' :
            if (wcscmp(L"2jo", bookName) == 0 || wcscmp(L"2john", bookName) == 0  || wcscmp(L"2joh", bookName) == 0 || wcscmp(L"2jn", bookName) == 0 ||
                    wcscmp(L"2janos", bookName) == 0 || wcscmp(L"2juan", bookName) == 0 || wcscmp(L"2jean", bookName) == 0 || wcscmp(L"2johannes", bookName) == 0)
                return II_John;
            break;
        case L'k' :
            if (wcscmp(L"2ki", bookName) == 0 || wcscmp(L"2kin", bookName) == 0 || wcscmp(L"2kings", bookName) == 0 ||
                    wcscmp(L"2konige", bookName) == 0 || wcscmp(L"2kiralyok", bookName) == 0)
                return II_Kings;
            if (wcscmp(L"2korinther", bookName) == 0)
                return II_Corinthians;
            if (wcscmp(L"2kronika", bookName) == 0 ||
                    wcscmp(L"2kr", bookName) == 0 || wcscmp(L"2kro", bookName) == 0 || wcscmp(L"2kron", bookName) == 0)
                return II_Chronicles;
            if (wcscmp(L"2kor", bookName) == 0 || wcscmp(L"2korintusi", bookName) == 0)
                return II_Corinthians;
            break;
        case L'm' :
            if (wcscmp(L"2mozes", bookName) == 0 || wcscmp(L"2moz", bookName) == 0)
                return Exodus;
            break;
        case L'p' :
            if (wcscmp(L"2pt", bookName) == 0 || wcscmp(L"2pe", bookName) == 0 || wcscmp(L"2pet", bookName) == 0 || wcscmp(L"2petr", bookName) == 0 || wcscmp(L"2peter", bookName) == 0 ||
                    wcscmp(L"2pietro", bookName) == 0 || wcscmp(L"2pedro", bookName) == 0 || wcscmp(L"2pierre", bookName) == 0 || wcscmp(L"2petrus", bookName) == 0)
                return II_Peter;
            break;
        case L'r' :
            if (wcscmp(L"2re", bookName) == 0 || wcscmp(L"2reyes", bookName) == 0 || wcscmp(L"2rois", bookName) == 0)
                return II_Kings;
            break;
        case L's' :
            if (wcscmp(L"2sa", bookName) == 0 || wcscmp(L"2sam", bookName) == 0 || wcscmp(L"2samuel", bookName) == 0 ||
                    wcscmp(L"2samuele", bookName) == 0)
                return II_Samuel;
            break;
        case L't' :
            if (wcscmp(L"2ts", bookName) == 0 || wcscmp(L"2tes", bookName) == 0 || wcscmp(L"2th", bookName) == 0 || wcscmp(L"2thes", bookName) == 0 || wcscmp(L"2thess", bookName) == 0 || wcscmp(L"2thessalonians", bookName) == 0 ||
                    wcscmp(L"2tesszalonika", bookName) == 0 || wcscmp(L"2tesalonicenses", bookName) == 0 || wcscmp(L"2thessalonicien", bookName) == 0 || wcscmp(L"2thessalonicher", bookName) == 0 ||
                    wcscmp(L"2tessalonicesi", bookName) == 0)
                return II_Thessalonians;
            if (wcscmp(L"2tm", bookName) == 0 ||wcscmp(L"2ti", bookName) == 0 || wcscmp(L"2tim", bookName) == 0 || wcscmp(L"2timothy", bookName) == 0 ||
                    wcscmp(L"2timoteushoz", bookName) == 0 || wcscmp(L"2timoteo", bookName) == 0 || wcscmp(L"2timothee", bookName) == 0 || wcscmp(L"2timotheus", bookName) == 0)
                return II_Timothy;
            break;
        }
        break;
    case L'3' :
        if (wcscmp(L"3jo", bookName) == 0 || wcscmp(L"3john", bookName) == 0  || wcscmp(L"3joh", bookName) == 0 || wcscmp(L"3jn", bookName) == 0 ||
                wcscmp(L"3gv", bookName) == 0 || wcscmp(L"3giovanni", bookName) == 0 || wcscmp(L"3janos", bookName) == 0 || wcscmp(L"3juan", bookName) == 0 || wcscmp(L"3jean", bookName) == 0 || wcscmp(L"3johannes", bookName) == 0)
            return III_John;
        if (wcscmp(L"3mozes", bookName) == 0 || wcscmp(L"3moz", bookName) == 0)
            return Leviticus;
        break;
    case L'4' :
        if (wcscmp(L"4mozes", bookName) == 0 || wcscmp(L"4moz", bookName) == 0)
            return Numbers;
        break;
    case L'5' :
        if (wcscmp(L"5mozes", bookName) == 0 || wcscmp(L"5moz", bookName) == 0)
            return Deuteronomy;
        break;
    default :
        return 0;
    }

    if (SwApplicationInterface::GetBookIdentifierState())
    {
        book = SwApplicationInterface::GetBookIdentifier().FindItem(name);
        if (book != NODE_ID_INVALID_8)
            return book;
    }

    return 0;
}

bool SwStandardBible::IdentifyReference(const wchar_t * referenceString, swUI32 offset, SwReferenceData & referenceData)
{
    swUI32 chapterStart, verseStart, verseEnd, versePos, endPos;
    int count, bookStart, bookEnd;
    int size = wcslen(referenceString);
    wchar_t bookName[256];
    wmemset(bookName, L'\0', 256);

    count = (int) offset;
    verseStart = 0;
    verseEnd = 0;

    // Attempt to Identify first position of Numeric Data.
    if (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
    {
        if ((referenceString[count] == L':' || referenceString[count] == L'H' || referenceString[count] == L'G') && iswdigit(referenceString[count + 1]))
            count ++;
        else if (count != 0 && iswdigit(referenceString[count - 1]))
            count --;
        else if (count != 0 && SwStringW::IsRoman(referenceString[count - 1]))
            count --;
        else
            return false;
    }

    while (count >= 0)
    {
        if (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
        {
            if (referenceString[count] == L'H')
            {
                referenceData.referenceType = REFERENCE_TYPE_STRONGS_HEBREW;
                referenceData.strongs = wcstol(&referenceString[count + 1], NULL, 10);
                return true;
            }
            else if (referenceString[count] == L'G')
            {
                referenceData.referenceType = REFERENCE_TYPE_STRONGS_GREEK;
                referenceData.strongs = wcstol(&referenceString[count + 1], NULL, 10);
                return true;
            }
            else if (count > 4 && referenceString[count] == L'-' && referenceString[count - 1] == L'-')
                return false;
            else if (referenceString[count] != L'.' && referenceString[count] != L':' && referenceString[count] != L',' && referenceString[count] != L' ' && referenceString[count] != L'-')
                return false;
            else if (referenceString[count] != L'-')
            {
                verseStart = count + 1;
                break;
            }
        }

        count --;
    }

    if (verseStart == 0)
        return false;

    count = verseStart;

    while (count < size)
    {
        if(!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
        {
            if (referenceString[count] == L'-')
            {
                count ++;

                if (iswdigit(referenceString[count]) || SwStringW::IsRoman(referenceString[count]))
                    verseEnd = count;
            }
            else if (referenceString[count] == L':')
                return false;

            break;
        }

        count ++;
    }

    count = verseStart;
    int chapterFound = false;
    // Identify chapter number;
    while (count >= 0)
    {
        if (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
        {
            if (referenceString[count] == L':' || referenceString[count] == L'.')
            {
                count --;

                if (count < 0 || (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count])))
                    break;

                while(count >= 0)
                {
                    if (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
                    {
                        chapterStart = count + 1;
                        chapterFound = true;
                        break;
                    }

                    count --;
                }

                break;
            }
            else if (referenceString[count] != L',' && referenceString[count] != L' ' && referenceString[count] != L'-')
                break;
        }

        count --;
    }

    if (count > 0 && chapterFound)
    {
        if (iswalpha(referenceString[count]))
            return false;
    }
    else if (count == 0)
        return false;

    // Identify book
    bookEnd = 0;
    while (count >= 0)
    {
        if (!SwStringW::IsRoman(referenceString[count]) && referenceString[count] != L'.' && !iswdigit(referenceString[count]) && referenceString[count] != L' ' && referenceString[count] != L';' && referenceString[count] != L':' && referenceString[count] != L'-' && referenceString[count] != L',' && referenceString[count] != L'(' && referenceString[count] != L'[')
        {
            if (SwStringW::IsRoman(referenceString[count + 1]))
                count ++;
            if (referenceString[count + 1] == L'.')
                count ++;
            else if (referenceString[count + 2] == L'.')
                count += 2;
            if (referenceString[count] != L'.' && !iswalpha(referenceString[count]))
                return false;

            bookEnd = count;
            break;
        }

        count --;
    }

    // Fix for names that have roman numerals
    while (bookEnd < size -1)
    {
        if (referenceString[bookEnd+1] == L' ')
            break;
        else
            bookEnd ++;
    }

    if (referenceString[bookEnd] == L',')
        bookEnd --;

    if (bookEnd == 0)
        return false;

    count --;

    while (count >= 0)
    {
        if (!iswalpha(referenceString[count]))
        {
            if (referenceString[count - 1] == L'1' || referenceString[count-1] == L'2' || referenceString[count-1] == L'3')
            {
                count -=2;
                break;
            }

            if (referenceString[count] == L'1' || referenceString[count] == L'2' || referenceString[count] == L'3')
            {
                count -=1;
                break;
            }

            bookStart = count + 1;

            if (count - 1 >= 0 && referenceString[count] == L' ')
            {
                count -= 1;

                while (count >= 0)
                {
                    if (referenceString[count] != L'I' && referenceString[count] != L'i')
                    {
                        if (iswalpha(referenceString[count + 1]))
                            bookStart = count + 1;

                        break;
                    }

                    count --;
                }
            }

            break;
        }

        count --;
    }

    swUI32 chapterPos = chapterStart;
    if (chapterFound)
    {
        if (SwStringW::IsRoman(referenceString[chapterStart]))
            chapterStart = SwStringW::ConvertRoman(referenceString, chapterStart, endPos);
        else
            chapterStart = wcstol(&referenceString[chapterStart], NULL, 10);
    }
    else
    {
        versePos = verseStart;
        if (SwStringW::IsRoman(referenceString[verseStart]))
        {
            while (SwStringW::IsRoman(referenceString[versePos]))
                versePos ++;
            if (iswalpha(referenceString[versePos]))
                return false;
        }
        else
        {
            while (iswdigit(referenceString[versePos]))
                versePos ++;
            if (iswalpha(referenceString[versePos]))
                return false;
        }

        chapterStart = 1;
    }

    if (SwStringW::IsRoman(referenceString[verseStart]))
        verseStart = SwStringW::ConvertRoman(referenceString, verseStart, endPos);
    else
        verseStart = wcstol(&referenceString[verseStart], NULL, 10);

    if (verseEnd)
    {
        if (SwStringW::IsRoman(referenceString[verseEnd]))
            verseEnd = SwStringW::ConvertRoman(referenceString, verseEnd, endPos);
        else
            verseEnd = wcstol(&referenceString[verseEnd], NULL, 10);
    }

    count ++;
    while (referenceString[count] == L' ' || referenceString[count] == L'(')
        count ++;
    bookEnd ++;
    wmemcpy(bookName, referenceString + count, bookEnd - count);
    wcslwr(bookName);
    bookStart = IdentifyBibleBookName(bookName);

    if (!bookStart)
        return false;

    if (chapterFound && (chapterPos <= (unsigned) bookEnd))
        return false;

    if (!chapterFound)
    {
        if (Get_KJV_BookChapters(bookStart) != 1)
            return false;
        else
            chapterStart = 1;
    }

    referenceData.book = bookStart;
    referenceData.chapter = chapterStart;
    referenceData.verseStart = verseStart;
    referenceData.verseEnd = verseEnd;
    referenceData.referenceType = REFERENCE_TYPE_SCRIPTURE;

    return true;
}

bool SwStandardBible::IdentifyChapterReference(const wchar_t * referenceString, swUI32 offset, SwReferenceData & referenceData)
{
    int count = (int) offset, endPos, size = wcslen(referenceString);
    swUI32 chapterPos;
    bool verseMark = false;
    wchar_t bookName[256];

    wmemset(bookName, L'\0', 256);

    // ID Chapter Number;
    if (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
    {

        if (count != 0 && iswdigit(referenceString[count - 1]))
            count --;
        else if (count != 0 && SwStringW::IsRoman(referenceString[count - 1]))
            count --;
    }

    for(;;)
    {
        if (count < 1)
            return false;

        if (referenceString[count] == L':' || referenceString[count] == L'.')
        {
            count --;
            continue;
        }

        if (!iswdigit(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
        {
            chapterPos = count + 1;
            break;
        }

        count --;
    }

    // ID End Pos of Book Name.
    for(;;)
    {
        if (count < 0)
            return false;

        if (referenceString[count] == L';')
            verseMark = true;
        else if (referenceString[count] == L':')
        {
            if (!verseMark)
                return false;
        }

        if (count > 4 && referenceString[count] == L'-' && referenceString[count -1] == L'-')
        {
            verseMark = true;
            count -= 2;
        }
        else if (iswalpha(referenceString[count]) && !SwStringW::IsRoman(referenceString[count]))
        {
            endPos = count;
            break;
        }

        count --;
    }

    if (SwStringW::IsRoman(referenceString[endPos + 1]))
    {
        count ++;
        endPos ++;
    }

    if (referenceString[endPos + 1] == L'.')
    {
        count ++;
        endPos ++;
    }
    else if (referenceString[endPos + 2] == L'.')
    {
        count += 2;
        endPos += 2;
    }

    count --;

    // Fix for names with roman numerals
    while (endPos < size - 1)
    {
        if (referenceString[endPos + 1] == L' ')
            break;
        else
        {
            count ++;
            endPos ++;
        }
    }

    if (referenceString[endPos] == L',')
    {
        count --;
        endPos --;
    }

    // ID Start Pos of Book Name.
    while (count >= 0)
    {
        if (!iswalpha(referenceString[count]))
        {
            if (referenceString[count-1] == L'1' || referenceString[count-1] == L'2' || referenceString[count-1] == L'3')
            {
                count -=2;
                break;
            }

            if (referenceString[count] == L'1' || referenceString[count] == L'2' || referenceString[count] == L'3')
            {
                count -=1;
                break;
            }

            if (count - 1 >= 0 && (referenceString[count] == L' ' || referenceString[count] == L'.' || referenceString[count] == L'('))
            {
                count -= 1;
                while (count >= 0)
                {
                    if (referenceString[count] != L'I' && referenceString[count] != L'i')
                    {
                        break;
                    }
                    count --;
                }
            }

            break;
        }

        count --;
    }

    count ++;
    while (referenceString[count] == L' ' || referenceString[count] == L'(')
    {
        count ++;
    }

    endPos ++;
    wmemcpy(bookName, referenceString + count, endPos - count);
    wcslwr(bookName);

    if (chapterPos <= (unsigned) endPos)
        return false;

    int ncpos = chapterPos;

    if (SwStringW::IsRoman(referenceString[chapterPos]))
    {
        while (SwStringW::IsRoman(referenceString[ncpos]))
            ncpos ++;
        if (iswalpha(referenceString[ncpos]))
            return false;
        swUI32 convEPos;
        referenceData.chapter = SwStringW::ConvertRoman(referenceString, chapterPos, convEPos);
    }
    else
        referenceData.chapter = wcstoul(&referenceString[chapterPos], NULL, 10);

    referenceData.book = IdentifyBibleBookName(bookName);

    if (referenceData.book < 1)
        return false;

    referenceData.referenceType = REFERENCE_TYPE_SCRIPTURE;
    referenceData.verseStart = 0;
    referenceData.verseEnd = 0;
    return true;
}

int SwStandardBible::ParseTextEx(char * pszWord, int nOffSet)
{
    SwString::Replace(pszWord + nOffSet, ' ', '\0');
    SwString::Replace(pszWord + nOffSet, '"', '\0');
    SwString::Replace(pszWord + nOffSet, '”', '\0');
    SwString::Replace(pszWord + nOffSet, '“', ' ');

    int nLen = strlen(pszWord), nCnt = 0;

    while (nCnt < nLen)
    {
        if (!isalpha(pszWord[nCnt]))
        {
            if (pszWord[nCnt] == '-')
            {
                if (!isalpha(pszWord[nCnt + 1]))
                    pszWord[nCnt] = ' ';

            }
            else if (pszWord[nCnt] == '\'')
            {
                if (pszWord[nCnt + 1] == 's' && (pszWord[nCnt + 2] == ' ' || pszWord[nCnt + 2] == '\0'))
                {
                    pszWord[nCnt] = ' ';
                }
            }
            else if (pszWord[nCnt] != '`')
            {
                pszWord[nCnt] = ' ';
            }

        }
        nCnt++;
    }

    nCnt = nOffSet;


    for(;;)
    {
        if (nCnt == -1)
            break;

        if (pszWord[nCnt] == ' ')
        {
            SwString::Delete(pszWord, 0, nCnt + 1);
            break;
        }
        nCnt --;
    }

    nCnt = 0;
    nLen = strlen(pszWord);

    while (nCnt < nLen)
    {
        if (pszWord[nCnt] == ' ')
        {
            pszWord[nCnt] = '\0';
            break;
        }
        nCnt ++;
    }

    SwString::TrimRight(pszWord, '-');
    SwString::TrimLeft(pszWord, '-');
    return 1;
}

// Index into array 'i16_RedChapterArray'. Identifies book which contain red
// text.
static swI16 i16_RedBookArray [] =
{
    00, // Alignment
    -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5, -5, 0,
    28, 44, 68, 89, -5, 117, 133, -5, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,
    -5, -5, -5, -5, -5, 146
};

// Index into array 'i16_RedVerseArray'. Identifies chapters which contain red
// text.
static swI16 i16_RedChapterArray [] =
{
    00, // Alignment
    -6, -6, 0, 17, 42, -8, 90, 119, 153, 191,
    233, 263, 313, 371, 407, 446, 474, 501, 536, 566,
    600, 646, 692, 731, -8, 782, 857, 923, 943, 988,
    1016, 1051, 1092, 1135, 1191, 1228, 1266, 1316, 1368, 1401,
    1445, 1482, 1554, 1601, -6, 1621, -6, 1673, 1717, 1756,
    1805, 1855, 1911, 1973, 2015, 2069, 2128, 2163, 2198, 2230,
    2261, 2298, 2341, 2389, 2436, 2474, 2545, 2601, 2654, 2705,
    2730, 2766, 2820, 2867, 2938, 2991, 3050, 3091, 3133, 3190,
    3240, 3278, -8, 3309, 3342, 3368, 3408, 3450, 3481, 3506,
    -6, -6, -6, -6, -6, -6, -6, 3532, -6, 3575,
    -6, -6, -6, -6, -6, -6, 3605, -6, 3633, -6,
    3671, 3701, -6, -6, 3736, -6, -6, -6, -6, -6,
    -6, -6, -6, -6, -6, -6, -6, 3768, -6, -6,
    -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
    -6, -6, -6, -6, 3802, -6, 3823, -8, -8, -6,
    -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,
    -6, -6, -6, -6, -6, -6, -6, 3843
};

// Index into array 'i16_RedPosArray'. Identifies verses which contain red
// text.
static swI16 i16_RedVerseArray [] =
{
    00, // Alignment
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, 0, -7, -7, -7, -7, -7,
    1, -7, -7, 2, -7, -7, 3, -7, -7, -7,
    -7, -7, -7, 4, -7, 5, -7, -7, -7, -7,
    -7, -7, -7, -7, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -7, -7, -7,
    -7, 6, 7, -7, -7, 8, -7, -7, 9, -9,
    -9, 10, -7, -7, -7, -7, -7, -7, 11, -7,
    12, -7, -7, -7, 13, -7, -7, -7, -7, -7,
    14, -7, -7, -7, 15, -7, 16, -9, 17, -7,
    -7, 18, -7, -7, 19, -9, -7, 20, -9, -9,
    -7, -7, -7, -7, 21, -7, 22, -7, -7, -7,
    23, 24, 25, -7, -7, -7, -7, -7, -7, 26,
    -9, -7, -7, -7, -7, 27, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -7, -7, -7, 28, -9, -9, 29,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -7, -9, -9, -9, -9, 30, -9, -9,
    -9, -9, -9, -7, -7, 31, -9, -9, -9, -9,
    -9, -7, -7, 32, -9, 33, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 34, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -7, 35, -9, -9, -9, -9, -9, -9, -7, -7,
    36, 37, -9, -7, -7, 38, -9, -9, -9, -9,
    -9, -9, -7, 39, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, 40, -9, -9, -9,
    -9, -9, -9, 41, -9, 42, -7, -7, -7, 43,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, 44, 45, -7, -7, -7, -7, 46,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, 47, -7, 48, -7,
    -7, -7, -7, -7, -7, -7, -7, 49, -7, 50,
    -7, 51, -7, -7, -7, -7, -7, -7, -7, 52,
    -9, -9, -9, -9, -9, -9, 53, -9, -7, 54,
    -9, -7, 55, -9, -9, -9, -9, -7, -7, -7,
    56, -7, 57, -7, 58, -7, -7, -7, 59, -7,
    60, -7, -7, -7, -7, -7, -7, 61, -9, 62,
    -7, 63, -7, 64, -9, -9, -9, -7, 65, -7,
    66, -7, 67, -9, -9, -7, -7, -7, 68, 69,
    -9, -9, -9, -9, -7, -7, -7, -7, -7, -7,
    70, -7, 71, -7, 72, -9, -7, -7, -7, -7,
    73, -7, -7, 74, -9, 75, 76, -7, 77, 78,
    -9, -7, -7, 79, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -7, 80, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -7, -7, -7, 81,
    -9, -9, -7, 82, -9, -7, 83, -9, -7, 84,
    -7, -7, 85, 86, -9, -7, 87, -7, 88, -9,
    -7, 89, -7, 90, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -7, -9, -9, -7, 91, 92, 93, -7,
    94, -9, -9, -9, -7, -7, -7, 95, -7, -7,
    -7, 96, -9, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, 97, -7, -7, 98, -7, -7, 99, -7,
    100, -9, -7, 101, 102, -7, 103, -9, -9, -9,
    104, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -7, 105, -9, -9, -7, -7, -7, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -7, -7, -7, 106, 107, 13, 108, -7, -7, -7,
    -7, -7, -7, -7, 109, -9, -9, -9, -7, -7,
    -7, -7, 110, -9, -9, -9, -7, 111, 112, -9,
    -9, -7, -7, 113, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -7, 114, -7, 115, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -7, -9, -7, -7, -7, -7, -7, -7,
    -7, 116, -9, -9, -9, -7, -7, -7, -7, 117,
    -7, -7, 118, -7, 63, -9, 119, 120, 121, -9,
    -9, -7, 122, -9, -7, 123, -7, 124, -7, 125,
    126, 127, -9, 128, -7, -7, 129, -9, -7, -7,
    -7, 130, -7, 131, -9, -9, 132, 133, -7, -7,
    -7, -7, -7, -7, -7, 134, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, 135, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 136, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, 137, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 138, 139, -7, -7, -7, -7, -7, -7, -7,
    140, -9, 141, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 142, -7, 143,
    -7, -7, -7, -7, -7, -7, -7, 144, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    145, -7, -7, 146, -7, -7, 147, -7, -7, -7,
    -7, -7, 148, -7, -7, 149, -9, 150, -9, -7,
    -7, 151, -7, -7, 152, -7, 153, -9, -9, -9,
    -7, -7, 154, -9, 155, -9, -7, -7, 156, 157,
    158, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, 159, -9,
    -9, -9, -9, -9, -9, -7, -7, -7, 160, 161,
    -9, -7, -7, -9, -9, -9, -9, -9, -9, 162,
    -7, 163, -9, 164, -9, -9, -9, -9, -9, -9,
    -9, 165, -9, -9, 166, -9, 167, -9, -9, -9,
    168, -9, -9, -7, -7, 169, -7, -7, -7, 170,
    171, -7, -7, -7, -7, -7, -7, -7, -7, 172,
    173, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    174, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 175, -7, -7, -7, 176, -7, 177, -7, -7,
    178, -7, 179, -7, -7, -7, -7, -7, 180, -7,
    -7, -7, -7, -7, 145, -9, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, 181, -7, -7, -7, -7,
    -7, 182, 183, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, 184, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, 185, -9, -9, 186,
    -9, -9, -9, -9, 187, -9, -9, -7, 188, -9,
    189, -9, -9, -9, -7, -7, -7, 190, -7, 191,
    -7, -7, -7, -7, 192, -7, -7, -7, -7, -9,
    -9, -7, 193, -7, -7, -7, -7, -7, -7, 194,
    -7, -7, 195, -7, 196, -9, 197, 198, 44, -7,
    -7, -7, -7, 199, 200, -7, 201, -7, -7, -7,
    202, 203, -9, -9, -9, -9, 204, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 205, -9, -7,
    -7, 206, -7, -7, 207, -7, 12, -7, 208, -7,
    209, -7, -7, -7, 181, -7, 210, -7, 211, -7,
    212, -7, -9, -7, 213, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -7, -7, 214, -7,
    215, -9, -9, -9, -9, -7, 216, -9, -7, 217,
    -9, -7, -7, 218, -9, -7, 219, -7, 220, 221,
    -9, -7, 222, -7, 223, -9, -9, -7, 224, -9,
    -7, 225, -7, 226, 227, -9, -7, 228, -9, -9,
    -9, -7, -7, -7, -7, -7, 229, 230, -7, 231,
    -9, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 232, -7, -7, 233, -7, -7, -7, -7, 234,
    -9, -9, -9, -9, -7, -7, 235, -9, -7, -7,
    236, 237, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -7, -7, -7, 238, 49, 239, -7, -7,
    -7, -7, -7, -7, 240, -9, -9, -9, -7, 241,
    -9, -9, -7, -7, 242, 243, -9, 244, 245, -9,
    -9, -7, -7, 246, -9, -7, 247, -7, -7, 248,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -7, -7, -7, -7, -7, 249, -9, -9,
    -9, -7, -7, -7, 250, -9, -9, -7, -7, 251,
    -7, 252, -9, 253, -7, 254, -9, -7, 255, -9,
    -7, 256, -7, 257, -7, 258, -7, 259, 260, -9,
    -7, -7, 261, -9, -7, -7, -7, -7, -7, 262,
    -9, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, 263, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, 264, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 265, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, 266, -9, -9, -9, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, 267,
    -7, -7, -7, -7, -7, -7, 268, -7, -7, -7,
    269, -7, -7, -7, 270, -7, -7, -7, -7, -7,
    -9, -9, -7, 271, -7, 272, 273, -9, -9, -9,
    -7, -7, -7, -7, -7, -7, -7, 144, -7, -7,
    -7, -7, -7, -7, -7, 274, -7, -7, -7, -7,
    275, -7, -7, -7, -7, -7, 276, -7, -7, 277,
    278, -7, -7, -7, -7, -7, 279, -7, 280, -9,
    281, -7, -7, 282, -7, -7, -7, 283, -9, -7,
    157, -9, 284, -9, -9, -9, -7, -7, 285, -9,
    286, -7, -7, 287, 288, 289, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, 290, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, 291, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -7, -7, -7, -7, -7,
    -7, -7, -7, 292, -7, -7, -7, 293, 294, -7,
    -7, -7, -7, -7, -7, -7, 295, -9, 296, -9,
    -9, -9, -9, -7, -7, 297, -9, -9, -9, -9,
    -7, -7, -7, -7, 298, -9, -9, 299, 300, -9,
    -9, -9, 301, -7, 302, -7, -7, -7, -7, -9,
    -9, -9, 303, -7, 304, -9, -9, -9, -9, -9,
    -9, -9, -9, -7, -7, 305, 306, -7, -7, 307,
    -7, -7, -7, -7, 308, -7, -7, -7, -7, -7,
    -7, -7, -7, 150, -7, -7, -7, -7, -7, 309,
    310, -7, 311, -7, 312, -7, 313, -7, 314, -7,
    -7, -7, -7, 315, -9, -9, -7, -7, -7, -7,
    -7, -7, -7, 307, 316, -7, -7, -7, 317, -7,
    318, -7, 319, 320, -9, -9, -9, -9, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 321, -7, -7, -9, -7, -7, -7, 322, -7,
    323, -7, -7, -7, -7, 324, 244, -7, 325, 326,
    327, -7, 328, -7, 329, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -7,
    330, -9, -9, 331, -9, 332, -9, -7, 333, -7,
    334, -7, 335, -9, -9, -9, -9, -9, -9, 336,
    -7, -7, -7, 337, -9, -7, 338, -9, -9, 339,
    -9, -9, -9, -9, -9, -9, -9, -9, -7, -7,
    -7, 340, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -7, 341, 342, -9, -9, -9, -9, -9, -9,
    -9, -7, -7, 343, -9, -9, -9, -9, -9, -7,
    344, -9, -9, -9, -9, -9, -9, -7, -7, 345,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -7, 346, 347, 348, -9, -9, -9, -9, -9,
    349, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -7,
    350, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, 351, -9, -9, -9, -9, -9, -7, 352,
    -9, -9, -9, 3, -9, -9, -9, -7, -7, 353,
    -7, -7, 354, -9, -7, 355, -9, 356, -9, -7,
    -7, -9, -9, -9, -9, -9, -9, -7, -7, 357,
    -9, -9, -9, -7, -7, 358, -7, 359, -7, -7,
    -9, -9, -9, -9, 360, -9, -9, -7, 361, -9,
    -9, -9, -9, -9, -9, -9, -9, -7, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -7, -7,
    -7, -9, -9, -9, -9, -9, -9, -9, 362, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    363, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -7, 364, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, 365, -9, -9, -9, -7, 366, -9, -9, -9,
    -9, -7, -7, -7, 367, -9, -9, 368, -9, 369,
    370, -9, 371, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, 372, -7, 373,
    -9, -9, -9, 374, -9, -9, -7, -9, -9, -9,
    -9, -9, -7, 375, -9, -7, 376, -9, -7, 228,
    -7, 377, -9, -7, 378, -7, 272, -9, 379, -9,
    -9, -7, -7, -7, -7, -7, -7, -7, 111, 380,
    -7, -7, -7, -7, -7, 381, -7, -7, -7, 382,
    -9, -7, 383, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -7, -7,
    384, -9, -7, -7, -7, -7, -7, -7, -7, -7,
    385, -7, 386, -9, -9, -7, 387, -7, -7, -7,
    -7, 388, -9, -7, -7, -7, 389, 390, -9, -9,
    -9, -9, -9, -9, 391, 392, -9, -7, -7, -7,
    -7, 393, 394, 395, -7, -7, -7, -7, -7, -7,
    -7, -7, 252, -9, -9, -9, -9, -7, -7, 396,
    -9, -9, -9, -7, -9, -9, -7, -7, 397, -9,
    -7, -9, -7, 398, -9, 399, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, 400, -9, -9, -9, -9, -9,
    -9, -9, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 401, -7, 402, -9, -9, -7, -7, 403, -9,
    404, -9, 405, 406, -9, -9, -7, -7, 407, -9,
    -9, -9, -9, -9, 408, -9, -7, 409, 403, 410,
    -9, 411, -7, 412, -7, 413, -7, -7, -7, 2,
    -7, 414, -7, -7, 415, 416, -9, -7, -7, -7,
    -7, -7, -7, -7, 417, -7, -7, -7, -7, -7,
    418, -9, -9, 419, -7, -7, -7, 420, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, 421, -9, -9, -9, -7, -7, 422, -7,
    -7, -7, -7, -7, -7, -7, -7, 423, -7, -7,
    424, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 425, -7, 426,
    -7, -7, -7, -7, -7, 427, -9, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, 428, -7, 254, -9,
    -7, 429, -7, -7, 430, -7, 97, -9, -9, -9,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 431, 432, -7, -7, 433, 434, -7, -7, -7,
    435, 436, -7, 363, 437, -7, -7, -7, 438, -7,
    -7, 439, 440, -7, -7, -7, -7, -7, -7, -7,
    441, -7, -7, 442, -7, -7, -7, -7, -7, -7,
    -7, -7, 443, -7, 444, -9, -9, -9, -7, 445,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, 446, -7, -7, 447, -7, -7, 448, -9,
    -7, 449, 450, -9, -7, -7, 451, -9, -9, -9,
    -7, 452, -7, -7, -7, -7, -7, 225, -7, 83,
    -9, -9, -9, -9, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, 453, -7, 454, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, 455, -7, 456, -7, -7,
    -7, -7, -7, 457, -7, -7, 458, -7, 459, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -7, -7, -7,
    -7, 460, -7, -7, -7, -7, 461, -7, 462, -7,
    -7, -7, -7, -7, -7, -7, 463, -7, -7, -7,
    -7, -7, 464, -9, -7, 465, -7, -7, 466, -9,
    -7, 467, -9, -9, -9, -9, -9, -7, -7, 468,
    -9, -9, -9, -9, -9, -9, -9, -9, -7, 469,
    -9, -9, -9, -9, -9, -7, -7, 470, -9, -9,
    471, 472, -7, 473, -7, -7, 474, -7, -7, -7,
    -7, -7, -7, 368, -9, -9, -7, -7, -7, -7,
    -7, -7, -7, 475, -9, -9, -9, -7, 298, -9,
    -9, -9, -7, -7, -7, 476, -9, -7, -7, -7,
    477, -9, -7, -7, 478, -9, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 479, -7, -7,
    480, 481, 482, -7, 483, -9, -9, -9, -9, 484,
    -7, 485, -7, 267, -9, 486, -9, -7, 487, -9,
    -7, 488, -9, -7, 489, -9, -9, -9, -9, 490,
    -9, 491, 492, -9, -9, -9, -9, -9, -7, 493,
    -9, -9, -7, -7, 494, -9, -9, -7, 495, -7,
    -7, -7, 496, -9, -9, -7, 497, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, 498, -7, 499, -7, 500, -7,
    501, -9, -9, -9, -9, -9, -7, 502, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -7,
    -7, -7, -7, -7, -7, 110, -9, -9, -9, -9,
    -9, -7, 503, -7, 504, -9, -9, -9, -9, -7,
    -7, -7, -7, -7, -7, -7, 505, -7, -7, 506,
    -7, 507, -9, 508, -7, -7, 509, -9, -7, -7,
    -7, -7, -7, -7, -7, 510, -7, 511, -9, -7,
    -7, -7, -7, -7, -7, -7, 512, -7, -7, -7,
    -7, 513, 514, 515, -9, 516, 517, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, 518, -9, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, 519, -9, -9, -9, -9, 520, -7, 521,
    -9, -9, -7, -7, 522, 523, -7, -7, -7, -7,
    -7, -7, -7, 524, -9, -9, -9, -9, -9, -9,
    -7, -7, -7, -7, -7, -7, 525, 526, -7, 527,
    528, 529, -9, -9, -9, -9, -9, -9, -9, -9,
    530, -7, -7, -7, -7, 531, 532, -7, -7, -7,
    533, -9, -9, -9, -9, 534, -7, 535, -9, -9,
    -9, -9, -7, 536, -9, -7, 537, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -7,
    538, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -7, -7, 539, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -7, -7, 540,
    -9, -9, 541, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,
    -9, -9, -9, -9, -9, -9, -9, -9, -7, -7,
    -7, 542, 543, -7, 544, 545, -7, -7, 546, -7,
    -7, -7, -7, -7, -7, -7, -7, 547, -9, -7,
    548, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 549, -7, 550, 551, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, 552, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, 553, 554, 555, -7, 556, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, 557, 558, 559, -7, 560, -7,
    561, 562, -9, -7, -7, 563, 564, -7, 565, -7,
    -7, -7, -7, -7, -7, 566, 567, -7, -7, -7,
    568, -7, 569, -7, -7, 570, 571, 572, -9, 573,
    -7, -7, 574, -7, -7, -7, -7, -7, -7, 575,
    -9, -7, 576, -9, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, 577, 578, 579, -7, -7,
    -7, 580, 581, -9, -7, -7, 582, -9, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 214, -7, 583, -7, -7, -7, -7, -7, -7,
    584, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, 585, -9, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 586, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, 587, 588, -7,
    589, -7, -7, -7, -7, -7, -7, -7, 590, -7,
    -7, 591, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 592, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, 593,
    594, -9, -9, -9, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, 595, 596, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    597, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,
    598, -7, -7, 599, -7, -7, -7, -7, -7, 600,
    -9, -9, -9, -7, -7, -7, -7, -7, -7, 601,
    -7, -7, -7, -7, -9, -9, -7, -7, -9, -7,
    -7, -7, 602, -7
};

// Contains red tag insertion positions for verses with 1 area
// of red text. Provides index position into array 'i16_RedPosBArray' for
// verses which contain 2 areas of red text.
static swI16 i16_RedPosArray [] [2] =
{
    38, 116,		// 0
    28, 136,		// 1
    23, 82,		// 2
    30, 139,		// 3
    53, 98,		// 4
    27, 73,		// 5
    59, 81,		// 6
    28, 161,		// 7
    28, 53,		// 8
    72, 146,		// 9
    38, 101,		// 10
    29, 142,		// 11
    28, 72,		// 12
    27, 68,		// 13
    26, 29,		// 14
    138, 187,		// 15
    41, 80,		// 16
    -1, 0,		// 17
    127, 137,		// 18
    51, 115,		// 19
    29, 208,		// 20
    61, 122,		// 21
    22, 73,		// 22
    94, 131,		// 23
    39, 78,		// 24
    72, 101,		// 25
    37, 99,		// 26
    61, 149,		// 27
    37, 98,		// 28
    80, 153,		// 29
    41, 187,		// 30
    25, 110,		// 31
    26, 180,		// 32
    29, 54,		// 33
    54, 180,		// 34
    39, 169,		// 35
    52, 95,		// 36
    67, 100,		// 37
    58, 92,		// 38
    35, 140,		// 39
    51, 130,		// 40
    51, 150,		// 41
    39, 165,		// 42
    35, 82,		// 43
    26, 62,		// 44
    27, 206,		// 45
    60, 139,		// 46
    29, 71,		// 47
    12, 36,		// 48
    50, 91,		// 49
    16, 21,		// 50
    88, 139,		// 51
    38, 105,		// 52
    52, 73,		// 53
    29, 104,		// 54
    19, 57,		// 55
    29, 90,		// 56
    29, 99,		// 57
    42, 107,		// 58
    57, 230,		// 59
    30, 54,		// 60
    34, 108,		// 61
    2, 135,		// 62
    29, 102,		// 63
    51, 138,		// 64
    89, 130,		// 65
    23, 49,		// 66
    41, 161,		// 67
    39, 170,		// 68
    39, 131,		// 69
    45, 70,		// 70
    71, 148,		// 71
    42, 95,		// 72
    33, 152,		// 73
    29, 252,		// 74
    58, 113,		// 75
    3, 71,		// 76
    84, 208,		// 77
    61, 88,		// 78
    12, 136,		// 79
    25, 96,		// 80
    38, 125,		// 81
    22, 141,		// 82
    26, 96,		// 83
    19, 118,		// 84
    25, 153,		// 85
    41, 154,		// 86
    24, 166,		// 87
    39, 124,		// 88
    48, 114,		// 89
    29, 237,		// 90
    25, 40,		// 91
    32, 172,		// 92
    27, 253,		// 93
    47, 170,		// 94
    53, 91,		// 95
    20, 161,		// 96
    23, 121,		// 97
    78, 170,		// 98
    119, 167,		// 99
    38, 263,		// 100
    42, 159,		// 101
    3, 62,		// 102
    77, 132,		// 103
    -1, 1,		// 104
    26, 204,		// 105
    51, 84,		// 106
    3, 29,		// 107
    57, 156,		// 108
    38, 98,		// 109
    24, 122,		// 110
    11, 52,		// 111
    23, 75,		// 112
    10, 59,		// 113
    28, 163,		// 114
    41, 75,		// 115
    50, 117,		// 116
    16, 160,		// 117
    33, 88,		// 118
    90, 105,		// 119
    122, 149,		// 120
    72, 91,		// 121
    31, 181,		// 122
    24, 113,		// 123
    93, 133,		// 124
    28, 110,		// 125
    75, 182,		// 126
    84, 126,		// 127
    59, 147,		// 128
    57, 179,		// 129
    28, 60,		// 130
    29, 129,		// 131
    51, 196,		// 132
    3, 81,		// 133
    25, 179,		// 134
    64, 112,		// 135
    132, 144,		// 136
    67, 94,		// 137
    74, 83,		// 138
    30, 120,		// 139
    47, 97,		// 140
    3, 135,		// 141
    15, 107,		// 142
    29, 92,		// 143
    34, 70,		// 144
    26, 114,		// 145
    96, 118,		// 146
    23, 190,		// 147
    66, 97,		// 148
    113, 155,		// 149
    3, 80,		// 150
    111, 121,		// 151
    46, 181,		// 152
    29, 171,		// 153
    26, 131,		// 154
    26, 84,		// 155
    57, 69,		// 156
    26, 111,		// 157
    128, 153,		// 158
    66, 95,		// 159
    33, 66,		// 160
    68, 101,		// 161
    25, 65,		// 162
    26, 162,		// 163
    26, 91,		// 164
    26, 123,		// 165
    26, 149,		// 166
    16, 87,		// 167
    16, 105,		// 168
    65, 102,		// 169
    62, 78,		// 170
    26, 81,		// 171
    24, 67,		// 172
    20, 39,		// 173
    55, 171,		// 174
    119, 142,		// 175
    25, 107,		// 176
    94, 122,		// 177
    48, 117,		// 178
    -1, 2,		// 179
    29, 130,		// 180
    26, 89,		// 181
    35, 55,		// 182
    23, 59,		// 183
    102, 143,		// 184
    34, 174,		// 185
    25, 105,		// 186
    72, 123,		// 187
    27, 166,		// 188
    16, 72,		// 189
    28, 142,		// 190
    25, 91,		// 191
    60, 70,		// 192
    21, 45,		// 193
    50, 167,		// 194
    32, 111,		// 195
    49, 163,		// 196
    3, 99,		// 197
    3, 89,		// 198
    46, 105,		// 199
    136, 162,		// 200
    27, 53,		// 201
    87, 194,		// 202
    92, 181,		// 203
    23, 177,		// 204
    34, 182,		// 205
    29, 56,		// 206
    32, 133,		// 207
    24, 95,		// 208
    102, 190,		// 209
    52, 185,		// 210
    67, 124,		// 211
    64, 147,		// 212
    19, 126,		// 213
    38, 65,		// 214
    41, 98,		// 215
    27, 113,		// 216
    72, 171,		// 217
    28, 99,		// 218
    58, 226,		// 219
    63, 132,		// 220
    99, 187,		// 221
    38, 122,		// 222
    32, 202,		// 223
    13, 203,		// 224
    26, 65,		// 225
    29, 152,		// 226
    61, 179,		// 227
    56, 199,		// 228
    41, 83,		// 229
    28, 71,		// 230
    23, 186,		// 231
    40, 84,		// 232
    36, 153,		// 233
    40, 58,		// 234
    42, 150,		// 235
    95, 153,		// 236
    45, 225,		// 237
    89, 145,		// 238
    39, 123,		// 239
    39, 125,		// 240
    27, 112,		// 241
    69, 110,		// 242
    63, 115,		// 243
    3, 77,		// 244
    42, 143,		// 245
    64, 175,		// 246
    37, 150,		// 247
    41, 78,		// 248
    18, 88,		// 249
    67, 158,		// 250
    44, 115,		// 251
    39, 99,		// 252
    99, 126,		// 253
    26, 88,		// 254
    30, 160,		// 255
    29, 144,		// 256
    87, 119,		// 257
    24, 92,		// 258
    16, 144,		// 259
    67, 122,		// 260
    54, 183,		// 261
    42, 120,		// 262
    19, 128,		// 263
    87, 105,		// 264
    64, 93,		// 265
    26, 92,		// 266
    26, 109,		// 267
    34, 114,		// 268
    40, 153,		// 269
    38, 88,		// 270
    34, 84,		// 271
    26, 164,		// 272
    16, 81,		// 273
    26, 105,		// 274
    53, 116,		// 275
    118, 165,		// 276
    57, 79,		// 277
    25, 163,		// 278
    50, 82,		// 279
    73, 103,		// 280
    -1, 3,		// 281
    129, 139,		// 282
    39, 104,		// 283
    42, 213,		// 284
    33, 141,		// 285
    25, 73,		// 286
    79, 117,		// 287
    29, 149,		// 288
    64, 87,		// 289
    57, 111,		// 290
    37, 107,		// 291
    120, 187,		// 292
    75, 84,		// 293
    88, 122,		// 294
    40, 238,		// 295
    101, 179,		// 296
    22, 105,		// 297
    38, 78,		// 298
    96, 121,		// 299
    52, 224,		// 300
    25, 47,		// 301
    29, 68,		// 302
    -1, 4,		// 303
    16, 179,		// 304
    39, 113,		// 305
    109, 156,		// 306
    26, 46,		// 307
    32, 49,		// 308
    19, 34,		// 309
    19, 90,		// 310
    25, 99,		// 311
    55, 107,		// 312
    48, 88,		// 313
    74, 86,		// 314
    25, 145,		// 315
    72, 115,		// 316
    105, 135,		// 317
    22, 48,		// 318
    11, 154,		// 319
    30, 128,		// 320
    29, 133,		// 321
    23, 202,		// 322
    28, 86,		// 323
    46, 90,		// 324
    28, 133,		// 325
    29, 39,		// 326
    24, 96,		// 327
    28, 119,		// 328
    31, 185,		// 329
    26, 71,		// 330
    52, 248,		// 331
    63, 119,		// 332
    21, 66,		// 333
    25, 80,		// 334
    29, 198,		// 335
    71, 96,		// 336
    41, 105,		// 337
    25, 160,		// 338
    25, 141,		// 339
    51, 160,		// 340
    16, 86,		// 341
    70, 187,		// 342
    31, 158,		// 343
    16, 165,		// 344
    180, 241,		// 345
    25, 72,		// 346
    26, 148,		// 347
    45, 104,		// 348
    35, 154,		// 349
    22, 170,		// 350
    35, 133,		// 351
    38, 144,		// 352
    70, 114,		// 353
    41, 173,		// 354
    17, 89,		// 355
    22, 65,		// 356
    26, 157,		// 357
    68, 108,		// 358
    29, 145,		// 359
    43, 231,		// 360
    26, 75,		// 361
    16, 43,		// 362
    37, 151,		// 363
    26, 183,		// 364
    33, 122,		// 365
    21, 190,		// 366
    46, 82,		// 367
    29, 83,		// 368
    25, 75,		// 369
    110, 157,		// 370
    35, 145,		// 371
    76, 146,		// 372
    10, 82,		// 373
    21, 54,		// 374
    47, 142,		// 375
    28, 95,		// 376
    59, 128,		// 377
    16, 79,		// 378
    59, 186,		// 379
    28, 73,		// 380
    82, 157,		// 381
    27, 110,		// 382
    22, 113,		// 383
    11, 173,		// 384
    39, 127,		// 385
    11, 148,		// 386
    21, 106,		// 387
    38, 83,		// 388
    28, 83,		// 389
    53, 163,		// 390
    3, 85,		// 391
    33, 149,		// 392
    58, 74,		// 393
    3, 59,		// 394
    26, 124,		// 395
    26, 66,		// 396
    15, 95,		// 397
    15, 163,		// 398
    27, 89,		// 399
    35, 74,		// 400
    38, 86,		// 401
    26, 172,		// 402
    26, 99,		// 403
    51, 95,		// 404
    83, 152,		// 405
    47, 114,		// 406
    26, 147,		// 407
    22, 110,		// 408
    16, 126,		// 409
    27, 168,		// 410
    78, 91,		// 411
    52, 91,		// 412
    11, 109,		// 413
    28, 77,		// 414
    32, 51,		// 415
    111, 170,		// 416
    116, 164,		// 417
    56, 91,		// 418
    76, 93,		// 419
    93, 111,		// 420
    37, 125,		// 421
    20, 73,		// 422
    28, 93,		// 423
    56, 99,		// 424
    26, 121,		// 425
    26, 38,		// 426
    27, 99,		// 427
    90, 110,		// 428
    77, 99,		// 429
    26, 231,		// 430
    67, 80,		// 431
    23, 36,		// 432
    68, 128,		// 433
    96, 106,		// 434
    56, 104,		// 435
    87, 165,		// 436
    26, 161,		// 437
    24, 86,		// 438
    25, 55,		// 439
    26, 80,		// 440
    39, 115,		// 441
    38, 96,		// 442
    36, 130,		// 443
    18, 142,		// 444
    37, 95,		// 445
    71, 88,		// 446
    37, 197,		// 447
    37, 89,		// 448
    25, 63,		// 449
    72, 111,		// 450
    25, 142,		// 451
    25, 57,		// 452
    29, 82,		// 453
    25, 52,		// 454
    103, 127,		// 455
    24, 56,		// 456
    65, 141,		// 457
    28, 67,		// 458
    43, 210,		// 459
    101, 147,		// 460
    19, 41,		// 461
    54, 112,		// 462
    27, 50,		// 463
    33, 164,		// 464
    38, 104,		// 465
    30, 157,		// 466
    29, 141,		// 467
    48, 76,		// 468
    30, 149,		// 469
    84, 105,		// 470
    3, 46,		// 471
    16, 116,		// 472
    36, 57,		// 473
    24, 80,		// 474
    34, 80,		// 475
    56, 173,		// 476
    30, 102,		// 477
    82, 133,		// 478
    79, 147,		// 479
    83, 149,		// 480
    52, 99,		// 481
    45, 156,		// 482
    38, 190,		// 483
    65, 156,		// 484
    36, 128,		// 485
    69, 125,		// 486
    30, 193,		// 487
    56, 117,		// 488
    24, 103,		// 489
    82, 146,		// 490
    3, 34,		// 491
    25, 150,		// 492
    19, 86,		// 493
    19, 132,		// 494
    25, 82,		// 495
    18, 122,		// 496
    21, 52,		// 497
    88, 124,		// 498
    28, 89,		// 499
    19, 138,		// 500
    25, 119,		// 501
    35, 94,		// 502
    24, 114,		// 503
    24, 75,		// 504
    36, 142,		// 505
    47, 75,		// 506
    18, 144,		// 507
    60, 133,		// 508
    38, 54,		// 509
    25, 54,		// 510
    24, 125,		// 511
    13, 36,		// 512
    15, 38,		// 513
    25, 115,		// 514
    117, 162,		// 515
    60, 80,		// 516
    142, 168,		// 517
    19, 83,		// 518
    36, 94,		// 519
    3, 28,		// 520
    28, 82,		// 521
    30, 192,		// 522
    3, 83,		// 523
    25, 95,		// 524
    36, 98,		// 525
    75, 121,		// 526
    23, 133,		// 527
    57, 78,		// 528
    109, 141,		// 529
    81, 145,		// 530
    19, 81,		// 531
    71, 99,		// 532
    48, 109,		// 533
    76, 156,		// 534
    23, 154,		// 535
    24, 104,		// 536
    24, 189,		// 537
    37, 162,		// 538
    74, 209,		// 539
    24, 42,		// 540
    69, 147,		// 541
    97, 110,		// 542
    63, 73,		// 543
    28, 41,		// 544
    18, 98,		// 545
    31, 125,		// 546
    23, 169,		// 547
    23, 105,		// 548
    23, 91,		// 549
    19, 197,		// 550
    73, 260,		// 551
    19, 168,		// 552
    111, 133,		// 553
    34, 52,		// 554
    114, 123,		// 555
    59, 74,		// 556
    25, 68,		// 557
    25, 30,		// 558
    25, 193,		// 559
    206, 226,		// 560
    34, 103,		// 561
    74, 100,		// 562
    154, 174,		// 563
    28, 167,		// 564
    25, 143,		// 565
    30, 57,		// 566
    25, 87,		// 567
    26, 69,		// 568
    26, 42,		// 569
    -1, 5,		// 570
    -1, 6,		// 571
    -1, 7,		// 572
    114, 124,		// 573
    25, 101,		// 574
    -1, 8,		// 575
    25, 120,		// 576
    63, 99,		// 577
    54, 137,		// 578
    106, 179,		// 579
    102, 110,		// 580
    33, 181,		// 581
    31, 153,		// 582
    47, 99,		// 583
    61, 139,		// 584
    56, 105,		// 585
    143, 186,		// 586
    64, 100,		// 587
    59, 105,		// 588
    65, 175,		// 589
    31, 136,		// 590
    24, 81,		// 591
    60, 170,		// 592
    112, 198,		// 593
    48, 81,		// 594
    58, 140,		// 595
    77, 178,		// 596
    23, 100,		// 597
    2, 53,		// 598
    11, 280,		// 599
    103, 141,		// 600
    2, 25,		// 601
    43, 65		// 602
};

// Contains red tag insertion positions for verses with 2 segments
// of red text.
static swI16 i16_RedPosBArray [] [4] =
{

    2, 79, 122, 170,
    3, 54, 108, 204,
    58, 71, 101, 132,
    3, 82, 121, 192,
    2, 78, 124, 164,
    55, 109, 190, 204,
    42, 80, 161, 175,
    37, 75, 257, 271,
    104, 150, 163, 183
};

swI16 SwStandardBible::GetRedTextIndexForBook(swUI8 book)
{
    if (book < 1 || book > 66)
        return Invalid_Reference;

    return i16_RedBookArray[book];
}

swI16 SwStandardBible::GetRedTextIndexForChapter(swUI8 book, swUI8 chapter)
{
    swI16 idx = GetRedTextIndexForBook(book);

    if (idx == Invalid_Reference)
        return idx;

    if (Get_KJV_ChapterVerses(book, chapter) == INVALID_BOOK || Get_KJV_ChapterVerses(book, chapter) == INVALID_CHAPTER)
        return Invalid_Reference;

    idx = GetRedTextIndexForBook(book);

    return i16_RedChapterArray[idx + chapter];
}

swI16 SwStandardBible::GetRedTextIndexForVerse(swUI8 book, swUI8 chapter, swUI8 verse)
{
    swUI8 result = Verify_KJV_Reference(book, chapter, verse);

    if (result != _OK_)
        return Invalid_Reference;

    swI16 idx = GetRedTextIndexForChapter(book, chapter);

    if (idx < 0)
        return idx;

    return i16_RedChapterArray[idx + chapter];
}

bool SwStandardBible::GetRedTextDataForVerse(swUI8 book, swUI8 chapter, swUI8 verse, RedTextData & data)
{
    data.result = No_Red_Text_In_Verse;
    data.sec1Begin = -1;
    data.sec1End = -1;
    data.sec2Begin = -1;
    data.sec2End = -1;

    swI16 result = GetRedTextIndexForVerse(book, chapter, verse);

    if (result == Invalid_Reference)
        return false;

    if (result == Full_Chapter_Red)
    {
        data.result = Full_Verse_Red;
        return true;
    }

    if (result == No_Red_Text_In_Book || result == No_Red_Text_In_Chapter)
    {
        data.result = No_Red_Text_In_Verse;
        return true;
    }

    result = i16_RedVerseArray[result + verse];

    if (result == No_Red_Text_In_Verse)
        return true;

    if (result == Full_Verse_Red)
    {
        data.result = result;
        return true;
    }

    data.result = 0;

    if (i16_RedPosArray[result][0] != -1)
    {
        data.sec1Begin = i16_RedPosArray[result][0];
        data.sec1Begin = i16_RedPosArray[result][1];

        return true;
    }
    // If the first element of the specified position of 'i16_RedPosArray'
    // array is -1 the second element specifies a position in
    // array 'i16_RedPosBArray' which will provide the insertion positions
    // for the red tags in the verse.
    else
    {
        result = i16_RedPosArray[result][1];
        data.sec1Begin = i16_RedPosBArray[result][0];
        data.sec1End = i16_RedPosBArray[result][1];
        data.sec2Begin = i16_RedPosBArray[result][2];
        data.sec2End = i16_RedPosBArray[result][3];
    }

    return true;
}

void SwStandardBible::FillCtrl(wxComboBox * ctrl)
{
    if (!ctrl)
        return;

    ctrl->Append("ASV");
    ctrl->Append("KJV");
    ctrl->Append("NKJV");
    ctrl->Append("NEB");
    ctrl->Append("NIV");
    ctrl->Append("RSV");
    ctrl->Append("NRSV");
    ctrl->Append("VUL");
    ctrl->SetSelection(1);
}
