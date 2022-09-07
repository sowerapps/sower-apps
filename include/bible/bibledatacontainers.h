///////////////////////////////////////////////////////////////////
// Name:        bibledatacontainers.h
// Purpose:     Structures used to store/retrieve data in various
//              classes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef BIBLEDATACONTAINERS_H_INCLUDED
#define BIBLEDATACONTAINERS_H_INCLUDED

#include "../sowerbase.h"
#include "../string/string.h"
#include "../module/modulebase.h"

struct SOWERBASEEXP SwBookData
{
    void Reset();

    swUI8     book;
    swUI8     chapters;
    swUI16    firstchapterNode;
};

struct SOWERBASEEXP SwChapterData
{
    void Reset();

    swUI8     chapter;
    swUI8     verses;
    swUI16    firstverseNode;
};

struct SOWERBASEEXP SwChapterDataEx
{
    void Reset();

    swUI8     book;
    swUI8     chapter;
    swUI8     verses;
    swUI16    firstverseNode;
};

struct SOWERBASEEXP SwVerseData
{
    void Reset();
    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

    swUI8             verse;
    SwModuleItemId    identifier;
};

struct SOWERBASEEXP SwVerseDataEx
{
    void Reset();
    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFp, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

    swUI8             book;
    swUI8             chapter;
    swUI8             verse;
    SwModuleItemId    identifier;
};

struct SOWERBASEEXP SwVerseRangeData
{
    void Reset();
    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

    swUI8             verseStart;
    swUI8             verseEnd;
    SwModuleItemId    identifier;
};

struct SOWERBASEEXP SwCommentaryData
{
    void Reset();
    bool ReadData(FILE * f, SwString & buffer, swUI32 itemindexFP, swUI32 contentOffset, swUI8 k1, swUI32 k2, bool encrypted);

    swUI8             book;
    swUI8             chapter;
    swUI8             verseStart;
    swUI8             verseEnd;
    SwModuleItemId    identifier;
};

class SOWERBASEEXP SwScriptureRange
{
    public :
    SwScriptureRange();
    virtual ~SwScriptureRange();

    void Reset();
    bool IsInRange(swUI8 book, swUI8 chapter, swUI8 verse);
    bool IsInRange(swUI8 verse);

    swUI8 m_book;
    swUI8 m_chapter;
    swUI8 m_verseStart;
    swUI8 m_verseEnd;
};

#endif // BIBLEDATACONTAINERS_H_INCLUDED
