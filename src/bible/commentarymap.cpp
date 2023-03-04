///////////////////////////////////////////////////////////////////
// Name:        commentarymap.cpp
// Purpose:     Data container to map sections of a commentary to
//              Bible book/chapter/verse-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/bible/commentarymap.h"
#include "stdio.h"

SwCommentaryMap::SwCommentaryMap()
{
    m_versification = strdup("");
    m_bookData = NULL;
    m_bookdataItems = 0;
    m_bookdataSize = 0;
    m_chapterData = NULL;
    m_chapterdataItems = 0;
    m_chapterdataSize = 0;
    m_rangeData = NULL;
    m_rangedataItems = 0;
    m_rangedataSize = 0;

}

SwCommentaryMap::~SwCommentaryMap()
{
    if (m_versification)
        free(m_versification);

    if (m_bookData)
        free(m_bookData);

    if (m_chapterData)
        free(m_chapterData);

    if (m_rangeData)
        free(m_rangeData);
}

void SwCommentaryMap::Reset()
{
    m_bookdataItems = 0;
    m_chapterdataItems = 0;
    m_rangedataItems = 0;

    if (m_versification)
        free(m_versification);

    m_versification = strdup("");
}

const char * SwCommentaryMap::GetVersification()
{
    return m_versification;
}

void SwCommentaryMap::SetVersification(const char * versification)
{
    if (m_versification)
        free(m_versification);

    m_versification = strdup(versification);
}

swUI16 SwCommentaryMap::SizeBookDataArray(swUI16 size)
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

swUI16 SwCommentaryMap::SizeChapterDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_chapterData);
        m_chapterdataItems = 0;
        m_chapterdataSize = 0;
        return 0;
    }

    void * p = (void *) realloc((void *) m_chapterData, sizeof(SwChapterDataEx) * size);

    if (p)
    {
        m_chapterdataSize = size;
        m_chapterData = (SwChapterDataEx *) p;

        return m_chapterdataSize;
    }

    return 0;
}

swUI16 SwCommentaryMap::SizeRangeDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_rangeData);
        m_rangedataItems = 0;
        m_rangedataSize = 0;
        return 0;
    }

    void * p = (void *) realloc((void *) m_rangeData, sizeof(SwCommentaryData) * size);

    if (p)
    {
        m_rangedataSize = size;
        m_rangeData = (SwCommentaryData *) p;

        return m_rangedataSize;
    }

    return 0;
}

bool SwCommentaryMap::AddBookData(swUI8 book, swUI8 chapters, swUI16 firstChapterNode)
{
    if (!SizeBookDataArray(m_bookdataItems + 1))
        return false;

    m_bookData[m_bookdataItems].book = book;
    m_bookData[m_bookdataItems].chapters = chapters;

    if (firstChapterNode != NODE_ID_INVALID_16)
        m_bookData[m_bookdataItems].firstchapterNode = firstChapterNode;
    else
        m_bookData[m_bookdataItems].firstchapterNode = m_chapterdataItems;

    m_bookdataItems ++;

    return true;
}

bool SwCommentaryMap::AddChapterData(swUI8 book, swUI8 chapter, swUI8 verses, swUI16 firstverseNode)
{
    if (!SizeChapterDataArray(m_chapterdataItems + 1))
        return false;

    m_chapterData[m_chapterdataItems].book = book;
    m_chapterData[m_chapterdataItems].chapter = chapter;
    m_chapterData[m_chapterdataItems].verses = verses;

    if (firstverseNode != NODE_ID_INVALID_16)
        m_chapterData[m_chapterdataItems].firstverseNode = firstverseNode;
    else
        m_chapterData[m_chapterdataItems].firstverseNode = m_rangedataItems;

    m_chapterdataItems ++;

    return true;
}

bool SwCommentaryMap::AddCommentaryData(swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd, SwModuleItemId identifier)
{
    if (!SizeRangeDataArray(m_rangedataItems + 1))
        return false;

    m_rangeData[m_rangedataItems].book = book;
    m_rangeData[m_rangedataItems].chapter = chapter;
    m_rangeData[m_rangedataItems].verseStart = verseStart;
    m_rangeData[m_rangedataItems].verseEnd = verseEnd;
    m_rangeData[m_rangedataItems].identifier = identifier;
    m_rangedataItems ++;

    return true;
}

void SwCommentaryMap::MapCommentaryData()
{
    MapChapterData();
    MapBookData();
}

void SwCommentaryMap::MapBookData()
{
    swUI8 book = 0;
    m_bookdataItems = 0;

    for (swUI16 i = 0; i < m_chapterdataItems; i++)
    {
        if (m_chapterData[i].book != book)
        {
            book = m_chapterData[i].book;
            AddBookData(book, CountBookChapters(book), i);
        }
    }
}

void SwCommentaryMap::MapChapterData()
{
    swUI8 book = 0, chapter = 0;
    m_chapterdataItems = 0;

    for (swUI16 i = 0; i < m_rangedataItems; i++)
    {
        if (m_rangeData[i].book != book || m_rangeData[i].chapter != chapter)
        {
            book = m_rangeData[i].book;
            chapter = m_rangeData[i].chapter;
            AddChapterData(book, chapter, CountChapterVerses(book, chapter), i);
        }
    }
}

swUI8 SwCommentaryMap::CountBookChapters(swUI8 book)
{
    swUI8 count = 0;

    for (swUI16 i = 0; i < m_chapterdataItems; i++)
    {
        if (m_chapterData[i].book == book)
            count ++;
    }

    return count;
}

swUI8 SwCommentaryMap::CountChapterVerses(swUI8 book, swUI8 chapter)
{
    swUI8 count = 0;

    for (swUI16 i = 0; i < m_rangedataItems; i++)
    {
        if (m_rangeData[i].book == book && m_rangeData[i].chapter == chapter)
            count ++;
    }

    return count;
}

swUI16 SwCommentaryMap::FindIndexPos(swUI8 book)
{
    for (swUI16 i = 0; i < m_bookdataItems; i++)
    {
        if (m_bookData[i].book == book)
            return i;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwCommentaryMap::FindIndexPos(swUI8 book, swUI8 chapter, swUI16 start)
{
    for (swUI16 i = start; i < m_chapterdataItems; i++)
    {
        if (m_chapterData[i].book == book && m_chapterData[i].chapter == chapter)
            return i;
    }

    return NODE_ID_INVALID_16;
}

bool SwCommentaryMap::FindVerseRange(SwCommentaryData verseRange, swUI16 & beginRange, swUI16 & endRange)
{
    beginRange = NODE_ID_INVALID_16;
    endRange = NODE_ID_INVALID_16;

    swUI16 idxPos = FindIndexPos(verseRange.book), count = 0;

    if (idxPos == NODE_ID_INVALID_16)
        return false;

    idxPos = FindIndexPos(verseRange.book, verseRange.chapter, m_bookData[idxPos].firstchapterNode);

    if (idxPos == NODE_ID_INVALID_16)
        return false;

    idxPos = m_chapterData[idxPos].firstverseNode;

    count = idxPos;
    while (count < m_rangedataItems)
    {
        if (DoesRangeContainVerse(m_rangeData[count], verseRange.book, verseRange.chapter, verseRange.verseStart))
        {
            beginRange = count;
            break;
        }

        count ++;
    }

    if (beginRange != NODE_ID_INVALID_16 && verseRange.verseEnd == 0)
        return true;

    count = idxPos;
    while (count < m_rangedataItems)
    {
        if (DoesRangeContainVerse(m_rangeData[count], verseRange.book, verseRange.chapter, verseRange.verseEnd))
        {
            endRange = count;
            break;
        }

        count ++;
    }

    if (endRange != NODE_ID_INVALID_16)
        return true;

    return false;
}

bool SwCommentaryMap::DoesRangeContainVerse(SwCommentaryData & verseRange, swUI8 book, swUI8 chapter, swUI8 verse)
{
    if (verseRange.book != book || verseRange.chapter != chapter)
        return false;

    if (verseRange.verseStart == verse && verseRange.verseEnd == 0)
        return true;
    if (verseRange.verseStart <= verse && verseRange.verseEnd >= verse)
        return true;

    return false;
}

swUI8 SwCommentaryMap::GetBookCount()
{
    return m_bookdataItems;
}

swUI16 SwCommentaryMap::GetChapterCount()
{
    return m_chapterdataItems;
}

swUI16 SwCommentaryMap::GetRangeCount()
{
    return m_rangedataItems;
}

SwBookData * SwCommentaryMap::GetBookData(swUI16 indexPos)
{
    if (indexPos >= m_bookdataItems)
        return NULL;

    return &m_bookData[indexPos];
}

SwChapterDataEx * SwCommentaryMap::GetChapterData(swUI16 indexPos)
{
    if (indexPos >= m_chapterdataItems)
        return NULL;

    return &m_chapterData[indexPos];
}

SwCommentaryData * SwCommentaryMap::GetCommentaryData(swUI16 indexPos)
{
    if (indexPos >= m_rangedataItems)
        return NULL;

    return &m_rangeData[indexPos];
}
