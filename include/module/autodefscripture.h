///////////////////////////////////////////////////////////////////
// Name:        autodefscripture.h
// Purpose:     AutodefScripture - locates/retrieves scripture
//              (Bible verses).
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef AUTODEFSCRIPTURE_H
#define AUTODEFSCRIPTURE_H

#include "../module/modulebase.h"
#include "../string/string.h"
#include "../module/moduleinterface.h"
#include "../bible/scripturemap.h"

class SOWERBASEEXP SwAutoDefScripture : public SwModuleInterface
{
public:
    SwAutoDefScripture();
    virtual ~SwAutoDefScripture();

    void Reset();
    swUI8 SizeBookDataArray(swUI8 size);
    swUI16 SizeChapterDataArray(swUI16 size);
    swUI16 SizeVerseDataArray(swUI16 size);
    bool AddBookData(swUI8 book, swUI8 chapters);
    SwBookData * GetBookData(swUI8 book);
    bool AddChapterData(swUI8 chapter, swUI8 verses);
    SwChapterData * GetChapterData(swUI16 chapter);
    bool AddVerseData(swUI8 verse, SwModuleItemId identifier);
    SwVerseData * GetVerseData(swUI16 verse);
    virtual swUI8 FindBook(swUI8 book);
    virtual swUI16 FindChapter(swUI8 book, swUI8 chapter);
    virtual swUI16 FindVerse(swUI8 book, swUI8 chapter, swUI8 verse);
    virtual SwModuleItemId FindModuleIdentifierForVerse(swUI8 book, swUI8 chapter, swUI8 verse);
    virtual bool WriteToFile(FILE * file);
    virtual bool WriteToFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual bool ReadFromFile(FILE * file);
    virtual bool ReadFromFile(FILE * file, swUI8 k1, swUI32 k2);
    virtual swUI32 GetType();
    void Import(SwScriptureMap & map);

protected:
    SwBookData *    m_bookData;
    swUI8           m_bookdataItems;
    swUI8           m_bookdataSize;
    SwChapterData * m_chapterData;
    swUI16          m_chapterdataItems;
    swUI16          m_chapterdataSize;
    SwVerseData *   m_verseData;
    swUI16          m_versedataItems;
    swUI16          m_versedataSize;
};

#endif // AUTODEFSCRIPTURE_H
