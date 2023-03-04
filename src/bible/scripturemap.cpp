///////////////////////////////////////////////////////////////////
// Name:        scripturemap.cpp
// Purpose:     SwScriptureMap - data container to map the contents
//              of a biblical text.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/bible/scripturemap.h"

SwScriptureMap::SwScriptureMap()
{
    m_versification = strdup("");
    m_bookData = NULL;
    m_bookdataItems = 0;
    m_bookdataSize = 0;
    m_chapterData = NULL;
    m_chapterdataItems = 0;
    m_chapterdataSize = 0;
    m_scriptureData = NULL;
    m_scripturedataItems = 0;
    m_scripturedataSize = 0;
}

SwScriptureMap::~SwScriptureMap()
{
    if (m_versification)
        free(m_versification);

    if (m_bookData)
        free(m_bookData);

    if (m_chapterData)
        free(m_chapterData);

    if (m_scriptureData)
        free(m_scriptureData);
}

void SwScriptureMap::Reset()
{
    m_bookdataItems = 0;
    m_chapterdataItems = 0;
    m_scripturedataItems = 0;

    if (m_versification)
        free(m_versification);

    m_versification = strdup("");
}

const char * SwScriptureMap::GetVersification()
{
    return m_versification;
}

void SwScriptureMap::SetVersification(const char * versification)
{
    if (m_versification)
        free(m_versification);

    m_versification = strdup(versification);
}

swUI16 SwScriptureMap::SizeBookDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_bookData);
        m_bookData = NULL;
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

swUI16 SwScriptureMap::SizeChapterDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_chapterData);
        m_chapterData = NULL;
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

swUI16 SwScriptureMap::SizeVerseDataArray(swUI16 size)
{
    if (!size)
    {
        free(m_scriptureData);
        m_scriptureData = NULL;
        m_scripturedataItems = 0;
        m_scripturedataSize = 0;
        return 0;
    }

    void * p = (void *) realloc((void *) m_scriptureData, sizeof(SwVerseDataEx) * size);

    if (p)
    {
        m_scripturedataSize = size;
        m_scriptureData = (SwVerseDataEx *) p;

        return m_scripturedataSize;
    }

    return 0;
}

bool SwScriptureMap::AddBookData(swUI8 book, swUI8 chapters, swUI16 firstChapterNode)
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

bool SwScriptureMap::AddChapterData(swUI8 book, swUI8 chapter, swUI8 verses, swUI16 firstverseNode)
{
    if (!SizeChapterDataArray(m_chapterdataItems + 1))
        return false;

    m_chapterData[m_chapterdataItems].book = book;
    m_chapterData[m_chapterdataItems].chapter = chapter;
    m_chapterData[m_chapterdataItems].verses = verses;

    if (firstverseNode != NODE_ID_INVALID_16)
        m_chapterData[m_chapterdataItems].firstverseNode = firstverseNode;
    else
        m_chapterData[m_chapterdataItems].firstverseNode = m_scripturedataItems;

    m_chapterdataItems ++;

    return true;
}

bool SwScriptureMap::AddVerseData(swUI8 book, swUI8 chapter, swUI8 verse, SwModuleItemId identifier)
{
    if (!SizeVerseDataArray(m_scripturedataItems + 1))
        return false;

    m_scriptureData[m_scripturedataItems].book = book;
    m_scriptureData[m_scripturedataItems].chapter = chapter;
    m_scriptureData[m_scripturedataItems].verse = verse;
    m_scriptureData[m_scripturedataItems].identifier = identifier;

    m_scripturedataItems ++;

    return true;
}

void SwScriptureMap::MapVerseData()
{
    MapChapterData();
    MapBookData();
}

void SwScriptureMap::MapBookData()
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

void SwScriptureMap::MapChapterData()
{
    swUI8 book = 0, chapter = 0;
    m_chapterdataItems = 0;

    for (swUI16 i = 0; i < m_scripturedataItems; i++)
    {
        if (m_scriptureData[i].book != book || m_scriptureData[i].chapter != chapter)
        {
            book = m_scriptureData[i].book;
            chapter = m_scriptureData[i].chapter;
            AddChapterData(book, chapter, CountChapterVerses(book, chapter), i);
        }
    }
}

swUI8 SwScriptureMap::CountBookChapters(swUI8 book)
{
    swUI8 count = 0;

    for (swUI16 i = 0; i < m_chapterdataItems; i++)
    {
        if (m_chapterData[i].book == book)
            count ++;
    }

    return count;
}

swUI8 SwScriptureMap::CountChapterVerses(swUI8 book, swUI8 chapter)
{
    swUI8 count = 0;

    for (swUI16 i = 0; i < m_scripturedataItems; i++)
    {
        if (m_scriptureData[i].book == book && m_scriptureData[i].chapter == chapter)
            count ++;
    }

    return count;
}

swUI16 SwScriptureMap::FindIndexPos(swUI8 book)
{
    for (swUI16 i = 0; i < m_bookdataItems; i++)
    {
        if (m_bookData[i].book == book)
            return i;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwScriptureMap::FindIndexPos(swUI8 book, swUI8 chapter, swUI16 start)
{
    for (swUI16 i = start; i < m_chapterdataItems; i++)
    {
        if (m_chapterData[i].book == book && m_chapterData[i].chapter == chapter)
            return i;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwScriptureMap::FindVerse(swUI8 book, swUI8 chapter, swUI8 verse)
{
    swUI16 idxPos = FindIndexPos(book), count = 0;

    if (idxPos == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    idxPos = FindIndexPos(book, chapter, m_bookData[idxPos].firstchapterNode);

    if (idxPos == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    idxPos = m_chapterData[idxPos].firstverseNode;

    count = idxPos;
    while (count < m_scripturedataItems)
    {
        if (m_scriptureData[count].book == book &&
                m_scriptureData[count].chapter == chapter &&
                m_scriptureData[count].verse == verse)
        {
            return count;
        }

        count ++;
    }

    return NODE_ID_INVALID_16;
}

swUI8 SwScriptureMap::GetBookCount()
{
    return m_bookdataItems;
}

swUI16 SwScriptureMap::GetChapterCount()
{
    return m_chapterdataItems;
}

swUI16 SwScriptureMap::GetVerseCount()
{
    return m_scripturedataItems;
}

SwBookData * SwScriptureMap::GetBookData(swUI16 indexPos)
{
    if (indexPos >= m_bookdataItems)
        return NULL;

    return &m_bookData[indexPos];
}

SwChapterDataEx * SwScriptureMap::GetChapterData(swUI16 indexPos)
{
    if (indexPos >= m_chapterdataItems)
        return NULL;

    return &m_chapterData[indexPos];
}

SwVerseDataEx * SwScriptureMap::GetVerseData(swUI16 indexPos)
{
    if (indexPos >= m_scripturedataItems)
        return NULL;

    return &m_scriptureData[indexPos];
}
