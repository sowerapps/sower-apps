///////////////////////////////////////////////////////////////////
// Name:        thmlfilemanager.h
// Purpose:     Manage a library of ThML files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLFILEMANAGER_H
#define THMLFILEMANAGER_H

#include "thml_file.h"
#include "../string/stringcompare.h"
#include "../array/uintarray.h"

#define ITEM_BREAK "<p></p>"
#define THML_OPEN "<ThML><ThML.body>\n"
#define THML_OPEN_SZ 18
#define THML_CLOSE "\n</ThML.body></ThML>"
#define THML_CLOSE_SZ 20

#define AUTODEF_OPEN "<ThML><autodef.body>\n"
#define AUTODEF_OPEN_SZ 21
#define AUTODEF_CLOSE "\n</autodef.body></ThML>"
#define AUTODEF_CLOSE_SZ 23

#define FILEMANAGER_ID_START (65535 / 2) + ((N_CATEGORIES + 2) / 2)

class SOWERBASEEXP SwThMLFileManager
{
public:
    SwThMLFileManager();
    virtual ~SwThMLFileManager();

    void Reset();
    swUI16 Add(SwThMLFile * file, bool notify = true);
    void Delete(swUI16 pos, bool notify = true);
    bool Insert(swUI16 insertPos, SwThMLFile * file, bool notify = true);
    void DeleteAll();
    swUI16 FindByAbbrev(const char * abbrev);
    swUI16 FindById(const char * id);
    swUI16 FindByTitle(const char * title);
    swUI16 FindByCcelFileName(const char * name);
    swUI16 FindByMID(swUI16 managerId);
    swUI16 FindByPath(const char * path);
    const char * GetTitleFromPath(const char * path);
    SwThMLFile * GetAt(swUI16 pos);
    SwThMLFile * GetFromMID(swUI16 managerId);
    void SetFile(swUI16 pos, SwThMLFile * file);
    swUI16 GetItemsInCategory(swUI8 category);
    void AddFileIdByCategory(Swui16Array & idArray, swUI8 category);

    bool GetAutoDefData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter);
    bool GetAutoDefBibleData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter);
    bool GetAutoDefBibleData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd);
    bool GetAutoDefCommentaryData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter);
    bool GetAutoDefCommentaryData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd);

    bool LoadAutoDefPage(SwPageData & pageData, SwString & pageBuffer);
    bool LoadAutoDefPage(swUI16 managerId, const char * id, SwString & pageBuffer);
    bool LoadAutoDefItem(swUI16 managerId, const char * id, SwString & pageBuffer);

    bool LoadElectronicInfo(swUI16 managerId, SwString & pageBuffer);
    bool LoadPage(SwPageData & pageData, SwString & pageBuffer);
    bool LoadPage(swUI16 managerId, const char * id, SwString & pageBuffer);
    bool LoadItem(swUI16 managerId, const char * id, SwString & pageBuffer);
    bool LoadBookMark(SwBookMarkData & bookmarkData, SwString & pageBuffer);
    bool LoadMedia(swUI16 managerId, const char * id, SwString & dataBuffer);

    bool Search(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool Search(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool Search(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool SearchEx(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool SearchEx(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool SearchEx(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    swUI16 GetFileCount();

protected:
    swUI16 AssignObject();
    bool IncreaseArray();
    void ReleaseArray();
    SwThMLFile ** m_array;
    swUI16        m_arrayPos;
    swUI16        m_objectsAllocated;
    swUI16        m_idPos;
};

#endif // THMLFILEMANAGER_H
