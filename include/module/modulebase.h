///////////////////////////////////////////////////////////////////
// Name:        modulebase.h
// Purpose:     SwKeyHeader
//              SwModuleKey
//              SwModuleHeader
//              SwPageData
//              SwBookMarkData
//              SwSearchCallBack
//              SwModuleItem
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef __MODULEBASE_H__
#define __MODULEBASE_H__

#include "../string/string.h"
#include <wx/treebase.h>

#define MODULEVERSIONMAJOR 2
#define MODULEVERSIONMINOR 0
#define SwModuleItemId swUI32
#define MITEMIDINVALID NODE_ID_INVALID

struct SwModuleItem
{
    swUI16  type;
    swUI8   book, chapter, verseStart, verseEnd;
    swUI16  divItems;
    bool    hasChildren;
    swUI32  position;
    swUI32  size;
    swUI8   contentType;

    void Reset()
    {
        type = 0;
        book = 0;
        verseStart = 0;
        verseEnd = 0;
        divItems = 0;
        hasChildren = false;
        position = 0;
        size = 0;
        contentType = 0;
    }
};

struct SOWERBASEEXP SwKeyHeader
{
    swUI8   tp0;
    swUI8   tp1;
    swUI8   tp2;
    swUI8   k1;
    swUI32  k2;
    swUI8   mk1;
    swUI32  mk2;
    swUI8   dataLength;
    swUI8   identifierLength;
    void Zero();
    void SetAsMaster();
    void SetAsUser();
    bool IsMaster();
    bool IsUser();
    bool IsKey();
    void GenerateKey();
    void SetModuleKeys(swUI8 modk1, swUI32 modk2);
    void SetDataLength(swUI8 len);
    void SetIdentifierLength(swUI8 len);
    bool Read(FILE * f, SwString & identifier, SwString & data);
    bool Write(FILE *f, const char * identifier, const char * data);
};

class SOWERBASEEXP SwModuleKey
{
public:
    SwModuleKey();
    virtual ~SwModuleKey();

    bool Load(const char * path);
    bool Write(const char * path);
    SwKeyHeader  header;
    SwString identifier;
    SwString data;
};

struct SOWERBASEEXP SwCatalogCard
{
    swUI8               softwareversionMajor;
    swUI8               softwareversionMinor;
    swUI8               category;
    char                modulepublisher[200];
    char                moduleTitle[200];
    char                moduleAbbreviation[21];
    char                moduleIdentifier[21];
    char                moduleVersification[21];
    char                moduleGroup[71];
    char                ccelFileName[71];
    bool                canCopy;
    bool                isEncrypted;
    void Zero();
    void SetPublisher(const char * publisher);
    const char * GetPublisher();
    int  GetPublisherLength();
    void SetTitle(const char * title);
    const char * GetTitle();
    int  GetTitleLength();
    void SetAbbreviation(const char * abbreviation);
    const char * GetAbbreviation();
    int  GetAbbreviationLength();
    void SetIdentifier(const char * identifier);
    const char * GetIdentifier();
    int  GetIdentifierLength();
    void SetVersification(const char * versification);
    const char * GetVersification();
    int  GetVersificationLength();
    void SetGroup(const char * group);
    const char * GetGroup();
    int  GetGroupLength();
    void SetCategory(swUI8 cat);
    swUI8 GetCategory();
    void SetCcelFileName(const char * title);
    const char * GetCcelFileName();
    int  GetCcelFileNameLength();
    bool ReadData(const char * path);
    bool WriteData(const char * path);
    bool ReadData(FILE * f);
    bool WriteData(FILE * f);
};

struct SOWERBASEEXP SwModuleHeader
{
    char                SW[3];
    swUI8               softwareversionMajor;
    swUI8               softwareversionMinor;
    swUI8               category;
    swUI32              filecontentsLocator;
    swUI32              tableofcontentsLocator;
    swUI32              mediacontentsLocator;
    swUI32              autodefverseLocator;
    swUI32              autodefcommentaryLocator;
    swUI32              autodeftermLocator;
    swUI32              autodefstrongshLocator;
    swUI32              autodefstrongsgLocator;
    swUI32              autodefnotesLocator;
    swUI32              unusedLocator1;
    swUI32              unusedLocator2;
    swUI32              unusedLocator3;
    swUI32              itemdataLocator;
    SwModuleItemId      items;
    SwModuleItemId      infoItem;
    char                modulepublisher[100];
    char                moduleTitle[200];
    char                moduleAbbreviation[21];
    char                moduleIdentifier[21];
    char                moduleVersification[21];
    char                moduleGroup[71];
    char                ccelFileName[71];
    bool                canCopy;
    bool                isEncrypted;
    swUI8               k1;
    swUI32              k2;
    void Zero();
    void SetPublisher(const char * publisher);
    const char * GetPublisher();
    int  GetPublisherLength();
    void SetTitle(const char * title);
    const char * GetTitle();
    int  GetTitleLength();
    void SetAbbreviation(const char * abbreviation);
    const char * GetAbbreviation();
    int  GetAbbreviationLength();
    void SetIdentifier(const char * identifier);
    const char * GetIdentifier();
    int  GetIdentifierLength();
    void SetVersification(const char * versification);
    const char * GetVersification();
    int  GetVersificationLength();
    void SetGroup(const char * group);
    const char * GetGroup();
    int  GetGroupLength();
    void SetCategory(swUI8 cat);
    swUI8 GetCategory();
    void SetCcelFileName(const char * title);
    const char * GetCcelFileName();
    int  GetCcelFileNameLength();
    bool ReadData(FILE * f);
    bool CopyToCard(SwCatalogCard * card);
    bool CopyFromCard(SwCatalogCard * card);
};

class SOWERBASEEXP SwPageData
{
public:
    SwPageData();
    SwPageData(swUI16 managerId, swUI16 pageId, swUI8 divType);
    virtual ~SwPageData();

    // Does not verify with module, only checks that it is within bounds.
    bool VerifyId(swUI16 lowest);

    swUI16 m_managerId;
    swUI16 m_pageId;
};

class SOWERBASEEXP SwBookMarkData
{
public:
    SwBookMarkData();
    virtual ~SwBookMarkData();

    SwString   m_bookId;
    SwString   m_pageId;
    SwString   m_title;
    SwString   m_note;
    swI32      m_selBegin;
    swI32      m_selEnd;
    swI32      m_scrollHPos;
    swI32      m_scrollVPos;
};

class SOWERBASEEXP SwBookMarkClientData : public wxClientData
{
public:
    SwBookMarkClientData();
    SwBookMarkClientData(const char * book, const char * page, const char * type);
    virtual ~SwBookMarkClientData();

    SwString   m_bookId;
    SwString   m_pageId;
    SwString   m_type;
    swI32      m_selBegin;
    swI32      m_selEnd;
    swI32      m_scrollHPos;
    swI32      m_scrollVPos;
};

class SOWERBASEEXP SwSearchCallBack
{
public :
    SwSearchCallBack();
    virtual ~SwSearchCallBack();

    virtual bool Result(const char * title, const char * xmlId);
    virtual bool Result(const wchar_t * title, const char * xmlId);
    virtual bool Result(const wchar_t * title, wxTreeItemId * treeId);
    virtual bool Result(const char * title, wxTreeItemId * treeId);
    virtual bool Result(swUI16 managerid, SwModuleItemId identifier, const char * title, bool canCopy);
    virtual bool Result(swUI16 managerid, SwModuleItemId identifier, const wchar_t * title, bool canCopy);
};

#endif // __MODULEBASE_H__
