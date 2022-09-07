///////////////////////////////////////////////////////////////////
// Name:        scripturemap.h
// Purpose:     SwScriptureMap - data container to map the contents
//              of a biblical text.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SCRIPTUREMAP_H
#define SCRIPTUREMAP_H

#include "bibledatacontainers.h"

class SOWERBASEEXP SwScriptureMap
{
public:
    SwScriptureMap();
    virtual ~SwScriptureMap();

    void Reset();
    const char * GetVersification();
    void SetVersification(const char * versification);
    swUI16 SizeBookDataArray(swUI16 size);
    swUI16 SizeChapterDataArray(swUI16 size);
    swUI16 SizeVerseDataArray(swUI16 size);
    bool AddBookData(swUI8 book, swUI8 chapters, swUI16 firstChapterNode);
    bool AddChapterData(swUI8 book, swUI8 chapter, swUI8 verses, swUI16 firstverseNode);
    bool AddVerseData(swUI8 book, swUI8 chapter, swUI8 verse, SwModuleItemId identifier);
    void MapVerseData();
    void MapBookData();
    void MapChapterData();
    swUI8 CountBookChapters(swUI8 book);
    swUI8 CountChapterVerses(swUI8 book, swUI8 chapter);
    swUI16 FindIndexPos(swUI8 book);
    swUI16 FindIndexPos(swUI8 book, swUI8 chapter, swUI16 start = 0);
    swUI16 FindVerse(swUI8 book, swUI8 chapter, swUI8 verse);
    swUI8 GetBookCount();
    swUI16 GetChapterCount();
    swUI16 GetVerseCount();
    SwBookData * GetBookData(swUI16 indexPos);
    SwChapterDataEx * GetChapterData(swUI16 indexPos);
    SwVerseDataEx * GetVerseData(swUI16 indexPos);

protected:
    char *            m_versification;
    SwBookData *      m_bookData;
    swUI16            m_bookdataItems;
    swUI16            m_bookdataSize;
    SwChapterDataEx * m_chapterData;
    swUI16            m_chapterdataItems;
    swUI16            m_chapterdataSize;
    SwVerseDataEx *   m_scriptureData;
    swUI16            m_scripturedataItems;
    swUI16            m_scripturedataSize;
};

#endif // SCRIPTUREMAP_H
