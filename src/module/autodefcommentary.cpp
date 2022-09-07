///////////////////////////////////////////////////////////////////
// Name:        autodefcommentary.cpp
// Purpose:     AutodefScripture - locates/retrieves commentary
//              entries.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/autodefcommentary.h"
#include "../../include/module/transcryptor.h"

SwAutoDefCommentary::SwAutoDefCommentary()
{
    m_bookData = NULL;
    m_bookdataItems = 0;
    m_bookdataSize = 0;
    m_chapterData = NULL;
    m_chapterdataItems = 0;
    m_chapterdataSize = 0;
    m_verserangeData = NULL;
    m_versedataItems = 0;
    m_versedataSize = 0;
}

SwAutoDefCommentary::~SwAutoDefCommentary()
{
    if (m_bookData)
        free(m_bookData);

    if (m_chapterData)
        free(m_chapterData);

    if (m_verserangeData)
        free(m_verserangeData);
}

void SwAutoDefCommentary::Reset()
{
    m_bookdataItems = 0;
    m_chapterdataItems = 0;
    m_versedataItems = 0;
}

swUI8 SwAutoDefCommentary::SizeBookDataArray(swUI8 size)
{
    if (!size)
    {
        free(m_bookData);
        m_bookdataItems = 0;
        m_bookdataSize = 0;
        return 0;
    }

    void * p = (void *) realloc((void *) m_bookData, sizeof(SwBookData) * size);

    if (p)
    {
        m_bookdataSize = size;
        m_bookData = (SwBookData *) p;

        return m_bookdataSize;
    }

    return 0;
}

swUI16 SwAutoDefCommentary::SizeChapterDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_chapterData);
        m_chapterdataItems = 0;
        m_chapterdataSize = 0;
        return 0;
    }

    void * p = (void *) realloc((void *) m_chapterData, sizeof(SwChapterData) * size);

    if (p)
    {
        m_chapterdataSize = size;
        m_chapterData = (SwChapterData *) p;

        return m_chapterdataSize;
    }

    return 0;
}

swUI16 SwAutoDefCommentary::SizeVerseRangeDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_verserangeData);
        m_versedataItems = 0;
        m_versedataSize = 0;
        return 0;
    }

    void * p = (void *) realloc((void *) m_verserangeData, sizeof(SwVerseRangeData) * size);

    if (p)
    {
        m_versedataSize = size;
        m_verserangeData = (SwVerseRangeData *) p;

        return m_versedataSize;
    }

    return 0;
}

bool SwAutoDefCommentary::AddBookData(swUI8 book, swUI8 chapters)
{
    if (!SizeBookDataArray(m_bookdataItems + 1))
        return false;

    m_bookData[m_bookdataItems].book = book;
    m_bookData[m_bookdataItems].chapters = chapters;
    m_bookData[m_bookdataItems].firstchapterNode = m_chapterdataItems;
    m_bookdataItems ++;

    return true;
}

SwBookData * SwAutoDefCommentary::GetBookData(swUI8 book)
{
    if (book >= m_bookdataItems)
        return NULL;

    return &m_bookData[book];
}

bool SwAutoDefCommentary::AddChapterData(swUI8 chapter, swUI8 verses)
{
    if (!SizeChapterDataArray(m_chapterdataItems + 1))
        return false;

    m_chapterData[m_chapterdataItems].chapter = chapter;
    m_chapterData[m_chapterdataItems].verses = verses;
    m_chapterData[m_chapterdataItems].firstverseNode = m_versedataItems;
    m_chapterdataItems ++;

    return true;
}

SwChapterData * SwAutoDefCommentary::GetChapterData(swUI16 chapter)
{
    if (chapter >= m_chapterdataItems)
        return NULL;

    return &m_chapterData[chapter];
}

bool SwAutoDefCommentary::AddVerseRangeData(swUI8 verseStart, swUI8 verseEnd, SwModuleItemId identifier)
{
    if (!SizeVerseRangeDataArray(m_versedataItems + 1))
        return false;

    m_verserangeData[m_versedataItems].verseStart = verseStart;
    m_verserangeData[m_versedataItems].verseEnd = verseEnd;
    m_verserangeData[m_versedataItems].identifier = identifier;
    m_versedataItems ++;

    return true;
}

SwVerseRangeData * SwAutoDefCommentary::GetVerseRangeData(swUI16 verse)
{
    if (verse >= m_versedataItems)
        return NULL;

    return &m_verserangeData[verse];
}

swUI8 SwAutoDefCommentary::FindBook(swUI8 book)
{
    for (swUI16 i = 0; i < m_bookdataItems; i++)
    {
        if (m_bookData[i].book == book)
            return i;
    }

    return NODE_ID_INVALID_8;
}

swUI16 SwAutoDefCommentary::FindChapter(swUI8 book, swUI8 chapter)
{
    swUI8 idx = FindBook(book);

    if (idx == NODE_ID_INVALID_8)
        return NODE_ID_INVALID_16;

    for (swUI16 i = m_bookData[idx].firstchapterNode; i < m_bookData[idx].firstchapterNode + m_bookData[idx].chapters; i++)
    {
        if (m_chapterData[i].chapter == chapter)
        {
            return i;
        }
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwAutoDefCommentary::FindVerse(swUI8 book, swUI8 chapter, swUI8 verse)
{
    swUI16 idx = FindChapter(book, chapter);

    if (idx == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    if (!verse)
        return NODE_ID_INVALID_16;

    for (swUI16 i = m_chapterData[idx].firstverseNode; i < m_chapterData[idx].firstverseNode + m_chapterData[idx].verses; i++)
    {
        if ((m_verserangeData[i].verseStart >= verse || m_verserangeData[i].verseEnd >= verse) && verse <= m_verserangeData[i].verseEnd)
            return i;
    }

    return NODE_ID_INVALID_16;
}

SwModuleItemId SwAutoDefCommentary::FindModuleIdentifierForVerse(swUI8 book, swUI8 chapter, swUI8 verse)
{
    swUI16 idx = FindChapter(book, chapter);

    if (idx == NODE_ID_INVALID_16)
        return MITEMIDINVALID;

    for (swUI16 i = m_chapterData[idx].firstverseNode; i < m_chapterData[idx].firstverseNode + m_chapterData[idx].verses; i++)
    {
        if (m_verserangeData[i].verseStart >= verse && m_verserangeData[i].verseEnd <= verse)
            return m_verserangeData[i].identifier;
    }

    return MITEMIDINVALID;
}

bool SwAutoDefCommentary::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (fwrite((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_bookdataItems, sizeof(swUI8), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_chapterdataItems, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_versedataItems, sizeof(swUI16), 1, file) != 1)
        return false;
    if (m_bookdataItems && fwrite((void *) m_bookData, sizeof(SwBookData), m_bookdataItems, file) != m_bookdataItems)
        return false;
    if (m_chapterdataItems && fwrite((void *) m_chapterData, sizeof(SwChapterData), m_chapterdataItems, file) != m_chapterdataItems)
        return false;
    if (m_versedataItems && fwrite((void *) m_verserangeData, sizeof(SwVerseRangeData), m_versedataItems, file) != m_versedataItems)
        return false;

    return true;
}

bool SwAutoDefCommentary::WriteToFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI32 type = GetType();
    if (SwTranscryptor::encryptfwrite((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;

    if (SwTranscryptor::encryptfwrite((void *) &m_bookdataItems, sizeof(swUI8), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_chapterdataItems, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::encryptfwrite((void *) &m_versedataItems, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (m_bookdataItems && SwTranscryptor::encryptfwrite((void *) m_bookData, sizeof(SwBookData), m_bookdataItems, file, k1, k2) != m_bookdataItems)
        return false;
    if (m_chapterdataItems && SwTranscryptor::encryptfwrite((void *) m_chapterData, sizeof(SwChapterData), m_chapterdataItems, file, k1, k2) != m_chapterdataItems)
        return false;
    if (m_versedataItems && SwTranscryptor::encryptfwrite((void *) m_verserangeData, sizeof(SwVerseRangeData), m_versedataItems, file, k1, k2) != m_versedataItems)
        return false;

    return true;
}

bool SwAutoDefCommentary::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI8 bookdataItems;
    swUI16 chapterdataItems, versedataItems;

    Reset();

    swUI32 type;
    if (fread((void *) &type, sizeof(swUI32), 1, file) != 1)
        return false;
    if (type != GetType())
        return false;

    if (fread((void *) &bookdataItems, sizeof(swUI8), 1, file) != 1)
        return false;
    if (fread((void *) &chapterdataItems, sizeof(swUI16), 1, file) != 1)
        return false;
    if (fread((void *) &versedataItems, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!SizeBookDataArray(bookdataItems) || !SizeChapterDataArray(chapterdataItems) || !SizeVerseRangeDataArray(versedataItems))
        return false;
    if (bookdataItems && fread((void *) m_bookData, sizeof(SwBookData), bookdataItems, file) != bookdataItems)
        return false;
    if (chapterdataItems && fread((void *) m_chapterData, sizeof(SwChapterData), chapterdataItems, file) != chapterdataItems)
        return false;
    if (versedataItems && fread((void *) m_verserangeData, sizeof(SwVerseRangeData), versedataItems, file) != versedataItems)
        return false;

    m_bookdataItems = bookdataItems;
    m_chapterdataItems = chapterdataItems;
    m_versedataItems = versedataItems;

    return true;
}

bool SwAutoDefCommentary::ReadFromFile(FILE * file, swUI8 k1, swUI32 k2)
{
    if (!file)
        return false;

    swUI8 bookdataItems;
    swUI16 chapterdataItems, versedataItems;

    Reset();

    swUI32 type;
    if (SwTranscryptor::decryptfread((void *) &type, sizeof(swUI32), 1, file, k1, k2) != 1)
        return false;
    if (type != GetType())
        return false;

    if (SwTranscryptor::decryptfread((void *) &bookdataItems, sizeof(swUI8), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &chapterdataItems, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (SwTranscryptor::decryptfread((void *) &versedataItems, sizeof(swUI16), 1, file, k1, k2) != 1)
        return false;
    if (!SizeBookDataArray(bookdataItems) || !SizeChapterDataArray(chapterdataItems) || !SizeVerseRangeDataArray(versedataItems))
        return false;
    if (bookdataItems && SwTranscryptor::decryptfread((void *) m_bookData, sizeof(SwBookData), bookdataItems, file, k1, k2) != bookdataItems)
        return false;
    if (chapterdataItems && SwTranscryptor::decryptfread((void *) m_chapterData, sizeof(SwChapterData), chapterdataItems, file, k1, k2) != chapterdataItems)
        return false;
    if (versedataItems && SwTranscryptor::decryptfread((void *) m_verserangeData, sizeof(SwVerseRangeData), versedataItems, file, k1, k2) != versedataItems)
        return false;

    m_bookdataItems = bookdataItems;
    m_chapterdataItems = chapterdataItems;
    m_versedataItems = versedataItems;

    return true;
}

swUI32 SwAutoDefCommentary::GetType()
{
    return MODULE_INTERFACE_TYPE_AUTODEFCOMMENTARY;
}

void SwAutoDefCommentary::Import(SwCommentaryMap & map)
{
    SizeBookDataArray(map.GetBookCount());
    SizeChapterDataArray(map.GetChapterCount());
    SizeVerseRangeDataArray(map.GetRangeCount());
    m_bookdataItems = map.GetBookCount();
    m_chapterdataItems = map.GetChapterCount();
    m_versedataItems = map.GetRangeCount();

    for (swUI8 book = 0; book < map.GetBookCount(); book ++)
    {
        m_bookData[book].book = map.GetBookData(book)->book;
        m_bookData[book].chapters = map.GetBookData(book)->chapters;
        m_bookData[book].firstchapterNode = map.GetBookData(book)->firstchapterNode;
    }

    for (swUI16 chapter = 0; chapter < map.GetChapterCount(); chapter ++)
    {
        m_chapterData[chapter].chapter = map.GetChapterData(chapter)->chapter;
        m_chapterData[chapter].verses = map.GetChapterData(chapter)->verses;
        m_chapterData[chapter].firstverseNode = map.GetChapterData(chapter)->firstverseNode;
    }

    for (swUI16 verse = 0; verse < map.GetRangeCount(); verse ++)
    {
        m_verserangeData[verse].verseStart = map.GetCommentaryData(verse)->verseStart;
        m_verserangeData[verse].verseEnd = map.GetCommentaryData(verse)->verseEnd;
        m_verserangeData[verse].identifier = map.GetCommentaryData(verse)->identifier;
    }

}
