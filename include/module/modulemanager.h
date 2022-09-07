///////////////////////////////////////////////////////////////////
// Name:        modulemanager.h
// Purpose:     SwModuleManager
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "../module/module.h"
#include "../array/stringarray.h"
#include "../array/uintarray.h"
#include "../array/cardarray.h"
#include "../filesys/streambuffer.h"

#define ITEM_BREAK "<p></p>"
#define THML_OPEN "<ThML><ThML.body>\n"
#define THML_OPEN_SZ 18
#define THML_CLOSE "\n</ThML.body></ThML>"
#define THML_CLOSE_SZ 20

#define AUTODEF_OPEN "<ThML><autodef.body>\n"
#define AUTODEF_OPEN_SZ 21
#define AUTODEF_CLOSE "\n</autodef.body></ThML>"
#define AUTODEF_CLOSE_SZ 23

#define MANAGER_ID_START N_CATEGORIES + 2

class SOWERBASEEXP SwModuleManager
{
public:
    SwModuleManager();
    virtual ~SwModuleManager();

    void Reset();
    swUI16 Add(SwModule * module, bool notify = true);
    void Delete(swUI16 pos, bool notify = true);
    bool Insert(swUI16 insertPos, SwModule * module, bool notify = true);
    void DeleteAll();
    swUI16 FindByAbbrev(const char * abbrev);
    swUI16 FindById(const char * id);
    swUI16 FindByTitle(const char * title);
    swUI16 FindByCcelFileName(const char * name);
    swUI16 FindByMID(swUI16 managerId);
    SwModule * GetAt(swUI16 pos);
    SwModule * GetFromMID(swUI16 managerId);
    void SetModule(swUI16 pos, SwModule * module);
    swUI16 GetItemsInCategory(swUI8 category);
    void AddModuleIdByCategory(Swui16Array & idArray, swUI8 category);
    void CreateCardCatalog(SwCatalogCardArray & cardarray);

    bool GetAutoDefData(SwString & buffer, const char * term, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, const wchar_t * term, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, swUI16 number, swUI8 strongsType, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, SwStrParser & strList, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, SwStrParserW & strList, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, SwStringArray & strList, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, SwStringWArray & strList, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, bool & canCopy);
    bool GetAutoDefData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd, bool & canCopy);

    bool LoadAutoDefPage(SwPageData & pageData, SwString & pageBuffer, bool & canCopy);
    bool LoadAutoDefPage(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy);
    bool LoadAutoDefItem(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy);

    bool LoadElectronicInfo(swUI16 managerId, SwString & pageBuffer);
    bool LoadPage(SwPageData & pageData, SwString & pageBuffer, bool & canCopy);
    bool LoadPage(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy);
    bool LoadItem(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy);
    bool LoadBookMark(SwBookMarkData & bookmarkData, SwString & pageBuffer, bool & canCopy);
    bool LoadMedia(swUI16 managerId, const char * id, SwStreamBuffer & dataBuffer, bool & canCopy);
    bool LoadMedia(swUI16 managerId, const char * id, Swui8Array & dataBuffer, bool & canCopy);

    bool Search(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool Search(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool Search(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool SearchEx(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool SearchEx(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    bool SearchEx(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback);
    swUI16 GetModules();

    bool SetModuleKey(SwModule * module);

protected:
    swUI16 AssignObject();
    bool IncreaseArray();
    void ReleaseArray();
    SwModule ** m_array;
    swUI16 m_arrayPos;
    swUI16 m_objectsAllocated;
    swUI16 m_idPos;
};

#endif // MODULEMANAGER_H
