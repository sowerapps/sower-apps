///////////////////////////////////////////////////////////////////
// Name:        commentarymap.h
// Purpose:     Data container to map sections of a commentary to
//              Bible book/chapter/verse-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef COMMENTARYMAP_H
#define COMMENTARYMAP_H

#include "bibledatacontainers.h"

class SOWERBASEEXP SwCommentaryMap
{
public:
    SwCommentaryMap();
    virtual ~SwCommentaryMap();

    void Reset();
    const char * GetVersification();
    void SetVersification(const char * versification);
    swUI16 SizeBookDataArray(swUI16 size);
    swUI16 SizeChapterDataArray(swUI16 size);
    swUI16 SizeRangeDataArray(swUI16 size);
    bool AddBookData(swUI8 book, swUI8 chapters, swUI16 firstChapterNode);
    bool AddChapterData(swUI8 book, swUI8 chapter, swUI8 verses, swUI16 firstverseNode);
    bool AddCommentaryData(swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd, SwModuleItemId identifier = MITEMIDINVALID);
    void MapCommentaryData();
    void MapBookData();
    void MapChapterData();
    swUI8 CountBookChapters(swUI8 book);
    swUI8 CountChapterVerses(swUI8 book, swUI8 chapter);
    swUI16 FindIndexPos(swUI8 book);
    swUI16 FindIndexPos(swUI8 book, swUI8 chapter, swUI16 start = 0);
    bool FindVerseRange(SwCommentaryData verseRange, swUI16 & beginRange, swUI16 & endRange);
    bool DoesRangeContainVerse(SwCommentaryData & verseRange, swUI8 book, swUI8 chapter, swUI8 verse);
    swUI8 GetBookCount();
    swUI16 GetChapterCount();
    swUI16 GetRangeCount();
    SwBookData * GetBookData(swUI16 indexPos);
    SwChapterDataEx * GetChapterData(swUI16 indexPos);
    SwCommentaryData * GetCommentaryData(swUI16 indexPos);

protected:
    char *            m_versification;
    SwBookData *      m_bookData;
    swUI16            m_bookdataItems;
    swUI16            m_bookdataSize;
    SwChapterDataEx * m_chapterData;
    swUI16            m_chapterdataItems;
    swUI16            m_chapterdataSize;
    SwCommentaryData *m_rangeData;
    swUI16            m_rangedataItems;
    swUI16            m_rangedataSize;
};

#endif // COMMENTARYMAP_H
