///////////////////////////////////////////////////////////////////
// Name:        module.h
// Purpose:     SwModule
//              SwKeyManager
//              SwKeyLoader
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMODULE_H
#define SOWERMODULE_H

#include "../module/modulebase.h"
#include "../bible/scripturemap.h"
#include "autodefcommentary.h"
#include "autodefterm.h"
#include "autodefnumbered.h"
#include "autodefscripture.h"
#include "tableofcontents.h"
#include "mediacontents.h"
#include "../string/stringcompare.h"
#include "../filesys/recurse.h"
#include "../array/moduleitemarray.h"

class SOWERBASEEXP SwModule
{
public:
    SwModule();
    virtual ~SwModule();

    void Reset();
    bool Load(const char * path);
    const char * GetPath();
    void SetPath(const char * path);
    bool GetAutodefEnabled();
    void SetAutodefEnabled(bool enabled);
    const char * GetFormattedAbbreviation();
    const char * GetFormattedModuleId();
    void SetManagerId(swUI16 managerId);
    swUI16 GetManagerId();
    bool ReadData(SwString & buffer, SwModuleItemId identifierStart);
    bool ReadData(SwString & buffer, SwModuleItemId identifierStart, swUI32 items);
    bool GetItemData(SwModuleItemArray & itemData, SwModuleItemId identifierStart);

    SwModuleHeader &    GetHeader();
    SwTableOfContents &   GetTableofContents();
    SwMediaContents &     GetMediaContents();
    SwAutoDefScripture &  GetADScripture();
    SwAutoDefCommentary & GetADCommentary();
    SwAutoDefTerm &       GetADTerm();
    SwAutoDefNumbered &   GetADStrongsH();
    SwAutoDefNumbered &   GetADStrongsG();
    SwAutoDefNumbered &   GetADNotes();

    FILE * GetFile();

    char *                  m_path;
    swUI16                  m_managerId;
    FILE *                  m_file;
    bool                    m_autodefEnabled;
    SwModuleHeader          m_header;
    SwModuleKey *           m_masterKey;

    private:
    bool m_headerLoaded;
    bool m_tableofcontentsLoaded;
    bool m_mediacontentsLoaded;
    bool m_adscriptureLoaded;
    bool m_adcommentaryLoaded;
    bool m_adstrongshLoaded;
    bool m_adstrongsgLoaded;
    bool m_adtermLoaded;
    bool m_adnotesLoaded;

    SwTableOfContents         m_tableofContents;
    SwMediaContents           m_mediaContents;
    SwAutoDefScripture        m_autodefVerse;
    SwAutoDefCommentary       m_autodefCommentary;
    SwAutoDefTerm             m_autodefTerm;
    SwAutoDefNumbered         m_autodefStrongsH;
    SwAutoDefNumbered         m_autodefStrongsG;
    SwAutoDefNumbered         m_autodefNotes;
};

class SOWERBASEEXP SwKeyManager
{
public:
    SwKeyManager();
    virtual ~SwKeyManager();
    swUI16 Add(SwModuleKey * key);
    void Delete(swUI16 pos);
    bool Insert(swUI16 insertPos, SwModuleKey * key);
    void DeleteAll();
    swUI16 FindKey(const char * id);
    swUI16 FindMasterKey(const char * id);
    swUI16 FindPublisherKey();
    SwModuleKey * GetKey(swUI16 pos);
    void SetKey(swUI16 pos, SwModuleKey * key);

    swUI16 GetKeys();

protected:
    swUI16 AssignObject();
    bool IncreaseArray();
    void ReleaseArray();
    SwModuleKey ** m_array;
    swUI16 m_arrayPos;
    swUI16 m_objectsAllocated;
};

class SOWERBASEEXP SwKeyLoader : public SwDirRecurse
{
public:
    SwKeyLoader();
    virtual ~SwKeyLoader();

    virtual bool OnFile(const char * path);
};

#endif // SOWERMODULE_H
