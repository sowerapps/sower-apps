///////////////////////////////////////////////////////////////////
// Name:        modulebase.cpp
// Purpose:     SwKeyHeader
//              SwModuleKey
//              SwModuleHeader
//              SwPageData
//              SwBookMarkData
//              SwSearchCallBack
//              SwModuleItemArray
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/modulebase.h"
#include "../../include/module/transcryptor.h"
#include "../../include/module/category.h"
#include "../../include/filesys/recurse.h"
#include "../../include/filesys/file.h"

void SwKeyHeader::Zero()
{
    memset((void *) this, 0, sizeof(SwKeyHeader));
}

void SwKeyHeader::SetAsMaster()
{
    tp2 = 7;
    tp1 = 3;
    tp0 = 1;
}

void SwKeyHeader::SetAsUser()
{
    tp2 = 1;
    tp1 = 3;
    tp0 = 7;
}

bool SwKeyHeader::IsKey()
{
    if (IsMaster() || IsUser())
        return true;

    return false;
}

bool SwKeyHeader::IsMaster()
{
    if ((tp2 == 7 && tp1 == 3 && tp0 == 1))
        return true;

    return false;
}

bool SwKeyHeader::IsUser()
{
    if ((tp2 == 1 && tp1 == 3 && tp0 == 7))
        return true;

    return false;
}

void SwKeyHeader::GenerateKey()
{
    k1 = SwTranscryptor::GetNumber(KEY_GEN_MIN, KEY_GEN_MAX, true);
    k2 = SwTranscryptor::Generate(k1);
}

void SwKeyHeader::SetModuleKeys(swUI8 modk1, swUI32 modk2)
{
    mk1 = modk1;
    mk2 = modk2;
}

void SwKeyHeader::SetDataLength(swUI8 len)
{
    dataLength = len;
}

void SwKeyHeader::SetIdentifierLength(swUI8 len)
{
    identifierLength = len;
}

bool SwKeyHeader::Read(FILE * f, SwString & identifier, SwString & data)
{
    if (fread(this, 1, sizeof(SwKeyHeader), f) != sizeof(SwKeyHeader))
        return false;

    if (!IsKey())
        return false;

    identifier.Size(identifierLength + 1);
    identifier.SetAt(identifierLength, '\0');

    if (SwTranscryptor::decryptfread(identifier.GetArray(), sizeof(char), identifierLength + 1, f, k1, k2) != (unsigned) identifierLength + 1)
        return false;

    data.Size(dataLength + 1);
    data.SetAt(dataLength, '\0');

    if (SwTranscryptor::decryptfread(data.GetArray(), sizeof(char), dataLength + 1, f, k1, k2) != (unsigned) dataLength + 1)
        return false;

    return true;
}

bool SwKeyHeader::Write(FILE *f, const char * identifier, const char * data)
{
    identifierLength = strlen(identifier);
    dataLength = strlen(data);

    if (fwrite(this, 1, sizeof(SwKeyHeader), f) != sizeof(SwKeyHeader))
        return false;

    if (SwTranscryptor::encryptfwrite(identifier, sizeof(char), identifierLength + 1, f, k1, k2) != (unsigned) identifierLength + 1)
        return false;

    if (SwTranscryptor::encryptfwrite(data, sizeof(char), dataLength + 1, f, k1, k2) != (unsigned) dataLength + 1)
        return false;

    return true;
}

SwModuleKey::SwModuleKey()
{
    header.Zero();
}

SwModuleKey::~SwModuleKey()
{
}

bool SwModuleKey::Load(const char * path)
{
    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    bool status = header.Read(f, identifier, data);

    fclose(f);

    return status;
}

bool SwModuleKey::Write(const char * path)
{
    FILE * f = SwFopen(path, FMD_WC);

    if (!f)
        return false;

    bool status = header.Write(f, identifier, data);

    fclose(f);

    return status;
}

void SwCatalogCard::Zero()
{
    memset((void *) this, 0, sizeof(SwCatalogCard));
    softwareversionMajor = MODULEVERSIONMAJOR;
    softwareversionMinor = MODULEVERSIONMINOR;
    canCopy = true;
    category = CATEGORY_GENERAL;
}

void SwCatalogCard::SetPublisher(const char * publisher)
{
    SwString::CopyN(publisher, modulepublisher, 99);
}

const char * SwCatalogCard::GetPublisher()
{
    return modulepublisher;
}

int SwCatalogCard::GetPublisherLength()
{
    return strlen(modulepublisher);
}

void SwCatalogCard::SetTitle(const char * title)
{
    SwString::CopyN(title, moduleTitle, 199);
}

const char * SwCatalogCard::GetTitle()
{
    return moduleTitle;
}

int SwCatalogCard::GetTitleLength()
{
    return strlen(moduleTitle);
}

void SwCatalogCard::SetAbbreviation(const char * abbreviation)
{
    SwString::CopyN(abbreviation, moduleAbbreviation, 20);
}

const char * SwCatalogCard::GetAbbreviation()
{
    return moduleAbbreviation;
}

int SwCatalogCard::GetAbbreviationLength()
{
    return strlen(moduleAbbreviation);
}

void SwCatalogCard::SetIdentifier(const char * identifier)
{
    SwString::CopyN(identifier, moduleIdentifier, 20);
}

const char * SwCatalogCard::GetIdentifier()
{
    return moduleIdentifier;
}

int SwCatalogCard::GetIdentifierLength()
{
    return strlen(moduleIdentifier);
}

void SwCatalogCard::SetVersification(const char * versification)
{
    SwString::CopyN(versification, moduleVersification, 20);
}

const char * SwCatalogCard::GetVersification()
{
    return moduleVersification;
}

int SwCatalogCard::GetVersificationLength()
{
    return strlen(moduleVersification);
}

void SwCatalogCard::SetGroup(const char * group)
{
    SwString::CopyN(group, moduleGroup, 70);
}

const char * SwCatalogCard::GetGroup()
{
    return moduleGroup;
}

int SwCatalogCard::GetGroupLength()
{
    return strlen(moduleGroup);
}

void SwCatalogCard::SetCcelFileName(const char * name)
{
    SwString::CopyN(name, ccelFileName, 70);
}

const char * SwCatalogCard::GetCcelFileName()
{
    return ccelFileName;
}

int SwCatalogCard::GetCcelFileNameLength()
{
    return strlen(ccelFileName);
}

void SwCatalogCard::SetCategory(swUI8 cat)
{
    category = cat;
}

swUI8 SwCatalogCard::GetCategory()
{
    return category;
}

bool SwCatalogCard::ReadData(const char * path)
{
    if (!path)
        return false;

    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    return ReadData(f);
}

bool SwCatalogCard::WriteData(const char * path)
{
    if (!path)
        return false;

    FILE * f = SwFopen(path, FMD_WC);

    if (!f)
        return false;

    bool state = WriteData(f);
    fclose(f);

    return state;
}

bool SwCatalogCard::ReadData(FILE * f)
{
    if (!f)
        return false;

    Zero();

    if (fread((void *) this, sizeof(SwCatalogCard), 1, f) != 1)
        return false;

    return true;
}

bool SwCatalogCard::WriteData(FILE * f)
{
    if (!f)
        return false;

    if (fwrite((void *) this, sizeof(SwCatalogCard), 1, f) != 1)
        return false;

    return true;
}

void SwModuleHeader::Zero()
{
    memset((void *) this, 0, sizeof(SwModuleHeader));
    strcpy(SW, "SW");
    softwareversionMajor = MODULEVERSIONMAJOR;
    softwareversionMinor = MODULEVERSIONMINOR;
    canCopy = true;
    category = CATEGORY_GENERAL;
    infoItem = MITEMIDINVALID;
}

void SwModuleHeader::SetPublisher(const char * publisher)
{
    SwString::CopyN(publisher, modulepublisher, 99);
}

const char * SwModuleHeader::GetPublisher()
{
    return modulepublisher;
}

int SwModuleHeader::GetPublisherLength()
{
    return strlen(modulepublisher);
}

void SwModuleHeader::SetTitle(const char * title)
{
    SwString::CopyN(title, moduleTitle, 199);
}

const char * SwModuleHeader::GetTitle()
{
    return moduleTitle;
}

int SwModuleHeader::GetTitleLength()
{
    return strlen(moduleTitle);
}

void SwModuleHeader::SetAbbreviation(const char * abbreviation)
{
    SwString::CopyN(abbreviation, moduleAbbreviation, 20);
}

const char * SwModuleHeader::GetAbbreviation()
{
    return moduleAbbreviation;
}

int SwModuleHeader::GetAbbreviationLength()
{
    return strlen(moduleAbbreviation);
}

void SwModuleHeader::SetIdentifier(const char * identifier)
{
    SwString::CopyN(identifier, moduleIdentifier, 20);
}

const char * SwModuleHeader::GetIdentifier()
{
    return moduleIdentifier;
}

int SwModuleHeader::GetIdentifierLength()
{
    return strlen(moduleIdentifier);
}

void SwModuleHeader::SetVersification(const char * versification)
{
    SwString::CopyN(versification, moduleVersification, 20);
}

const char * SwModuleHeader::GetVersification()
{
    return moduleVersification;
}

int SwModuleHeader::GetVersificationLength()
{
    return strlen(moduleVersification);
}

void SwModuleHeader::SetGroup(const char * group)
{
    SwString::CopyN(group, moduleGroup, 70);
}

const char * SwModuleHeader::GetGroup()
{
    return moduleGroup;
}

int SwModuleHeader::GetGroupLength()
{
    return strlen(moduleGroup);
}

void SwModuleHeader::SetCcelFileName(const char * name)
{
    SwString::CopyN(name, ccelFileName, 70);
}

const char * SwModuleHeader::GetCcelFileName()
{
    return ccelFileName;
}

int SwModuleHeader::GetCcelFileNameLength()
{
    return strlen(ccelFileName);
}

void SwModuleHeader::SetCategory(swUI8 cat)
{
    category = cat;
}

swUI8 SwModuleHeader::GetCategory()
{
    return category;
}

bool SwModuleHeader::ReadData(FILE * f)
{
    if (!f)
        return false;

    Zero();

    if (fread((void *) this, sizeof(SwModuleHeader), 1, f) != 1)
        return false;

    if (SW[0] != 'S' || SW[1] != 'W' || SW[2] != '\0')
        return false;

    if (softwareversionMajor != MODULEVERSIONMAJOR || softwareversionMinor != MODULEVERSIONMINOR)
        return false;

    return true;
}

bool SwModuleHeader::CopyToCard(SwCatalogCard * card)
{
    if (!card)
        return false;

    card->Zero();
    card->softwareversionMajor = softwareversionMajor;
    card->softwareversionMinor = softwareversionMinor;
    card->isEncrypted = isEncrypted;
    card->canCopy = canCopy;
    card->SetPublisher(GetPublisher());
    card->SetTitle(GetTitle());
    card->SetAbbreviation(GetAbbreviation());
    card->SetIdentifier(GetIdentifier());
    card->SetVersification(GetVersification());
    card->SetGroup(GetGroup());
    card->SetCategory(GetCategory());
    card->SetCcelFileName(GetCcelFileName());

    return true;
}

bool SwModuleHeader::CopyFromCard(SwCatalogCard * card)
{
    if (!card)
        return false;

    card->softwareversionMajor = softwareversionMajor;
    card->softwareversionMinor = softwareversionMinor;
    card->isEncrypted = isEncrypted;
    card->canCopy = canCopy;
    SetPublisher(card->GetPublisher());
    SetTitle(card->GetTitle());
    SetAbbreviation(card->GetAbbreviation());
    SetIdentifier(card->GetIdentifier());
    SetVersification(card->GetVersification());
    SetGroup(card->GetGroup());
    SetCategory(card->GetCategory());
    SetCcelFileName(card->GetCcelFileName());

    return true;
}

SwPageData::SwPageData()
{
    m_managerId = NODE_ID_INVALID_16;
    m_pageId = NODE_ID_INVALID_16;
}

SwPageData::SwPageData(swUI16 managerId, swUI16 pageId, swUI8 divType)
{
    m_managerId = managerId;
    m_pageId = pageId;
}

SwPageData::~SwPageData()
{
}

bool SwPageData::VerifyId(swUI16 lowest)
{
    if (m_managerId < lowest || m_managerId == NODE_ID_INVALID_16 || m_pageId == NODE_ID_INVALID_16)
        return false;

    return true;
}

SwBookMarkData::SwBookMarkData()
{
    m_selBegin = -1;
    m_selEnd = -1;
    m_scrollHPos = 0;
    m_scrollVPos = 0;
}

SwBookMarkData::~SwBookMarkData()
{
}

SwBookMarkClientData::SwBookMarkClientData()
{
    m_selBegin = -1;
    m_selEnd = -1;
    m_scrollHPos = 0;
    m_scrollVPos = 0;
}

SwBookMarkClientData::SwBookMarkClientData(const char * book, const char * page, const char * type)
{
    if (book)
        m_bookId = book;

    if (page)
        m_pageId = page;

    if (type)
        m_type = type;

    m_selBegin = -1;
    m_selEnd = -1;
    m_scrollHPos = 0;
    m_scrollVPos = 0;
}

SwBookMarkClientData::~SwBookMarkClientData()
{
}

SwSearchCallBack::SwSearchCallBack()
{
}

SwSearchCallBack::~SwSearchCallBack()
{
}

bool SwSearchCallBack::Result(const char * title, const char * xmlId)
{
    return true;
}

bool SwSearchCallBack::Result(const wchar_t * title, const char * xmlId)
{
    return true;
}

bool SwSearchCallBack::Result(const char * title, wxTreeItemId * treeId)
{
    return true;
}

bool SwSearchCallBack::Result(const wchar_t * title, wxTreeItemId * treeId)
{
    return true;
}

bool SwSearchCallBack::Result(swUI16 managerid, SwModuleItemId identifier, const char * title, bool canCopy)
{
    return true;
}

bool SwSearchCallBack::Result(swUI16 managerid, SwModuleItemId identifier, const wchar_t * title, bool canCopy)
{
    return true;
}
