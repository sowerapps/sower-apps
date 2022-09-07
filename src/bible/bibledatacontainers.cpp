///////////////////////////////////////////////////////////////////
// Name:        bibledatacontainers.cpp
// Purpose:     Structures used to store/retrieve data in various
//              classes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/bible/bibledatacontainers.h"
#include "../../include/module/transcryptor.h"
#include "../../include/module/modulebase.h"

void SwBookData::Reset()
{
    book = NODE_ID_INVALID_8;
    chapters = 0;
    firstchapterNode = NODE_ID_INVALID_16;
}

void SwChapterData::Reset()
{
    chapter = NODE_ID_INVALID_8;
    verses = 0;
    firstverseNode = NODE_ID_INVALID_16;
}

void SwChapterDataEx::Reset()
{
    book = NODE_ID_INVALID_8;
    chapter = 0;
    verses = 0;
    firstverseNode = NODE_ID_INVALID_16;
}

void SwVerseData::Reset()
{
    verse = NODE_ID_INVALID_8;
    identifier = MITEMIDINVALID;
}

bool SwVerseData::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size + 1);

    if (!encrypted)
    {
        fseek(f, contentOffset + data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, contentOffset + (data.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.SetAt(buffer.GetCount() + data.size, '\0');
    buffer.IncrementCount(data.size);

    return true;
}

void SwVerseDataEx::Reset()
{
    book = NODE_ID_INVALID_8;
    chapter = 0;
    verse = 0;
    identifier = MITEMIDINVALID;
}

bool SwVerseDataEx::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size + 1);

    if (!encrypted)
    {
        fseek(f, contentOffset + data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, contentOffset + (data.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.SetAt(buffer.GetCount() + data.size, '\0');
    buffer.IncrementCount(data.size);

    return true;
}

void SwVerseRangeData::Reset()
{
    verseStart = NODE_ID_INVALID_8;
    verseEnd = NODE_ID_INVALID_8;
    identifier = MITEMIDINVALID;
}

bool SwVerseRangeData::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFp + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size + 1);

    if (!encrypted)
    {
        fseek(f, contentOffset + data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, contentOffset + (data.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.SetAt(buffer.GetCount() + data.size, '\0');
    buffer.IncrementCount(data.size);

    return true;
}

void SwCommentaryData::Reset()
{
    book = NODE_ID_INVALID_8;
    chapter = 0;
    verseStart = 0;
    verseEnd = 0;
    identifier = MITEMIDINVALID;
}

bool SwCommentaryData::ReadData(FILE * f, SwString & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted)
{
    SwModuleItem data;

    if (!f)
        return false;

    fseek(f, itemindexFP + (sizeof(SwModuleItem) * identifier), SEEK_SET);
    fread((void *) &data, sizeof(SwModuleItem), 1, f);
    buffer.Size(buffer.GetCount() + data.size + 1);

    if (!encrypted)
    {
        fseek(f, contentOffset + data.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f);
    }
    else
    {
        fseek(f, contentOffset + (data.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), data.size, f, k1, k2);
    }

    buffer.SetAt(buffer.GetCount() + data.size, '\0');
    buffer.IncrementCount(data.size);

    return true;
}

SwScriptureRange::SwScriptureRange()
{
    Reset();
}

SwScriptureRange::~SwScriptureRange()
{
}

void SwScriptureRange::Reset()
{
    m_book = m_chapter = m_verseStart = m_verseEnd = 0;
}

bool SwScriptureRange::IsInRange(swUI8 book, swUI8 chapter, swUI8 verse)
{
    if (book != m_book || chapter != m_chapter)
        return false;

    if (!m_verseEnd)
    {
        if (verse == m_verseStart)
            return true;
    }
    else
    {
        if (verse >= m_verseStart && verse <= m_verseEnd)
            return true;
    }

    return false;
}

bool SwScriptureRange::IsInRange(swUI8 verse)
{
    if (!m_verseEnd)
    {
        if (verse == m_verseStart)
            return true;
    }
    else
    {
        if (verse >= m_verseStart && verse <= m_verseEnd)
            return true;
    }

    return false;
}
