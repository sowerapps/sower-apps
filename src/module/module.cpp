///////////////////////////////////////////////////////////////////
// Name:        module.cpp
// Purpose:     SwModule
//              SwKeyManager
//              SwKeyLoader
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/module.h"
#include "../../include/module/transcryptor.h"
#include "../../include/thml/thml_parser.h"
#include "../../include/thml/thml_elements.h"
#include "../../include/module/category.h"
#include "../../include/appi/appifa.h"
#include "../../include/filesys/bzcompression.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

SwModule::SwModule()
{
    m_header.Zero();
    m_path = NULL;
    SetPath("");
    m_managerId = NODE_ID_INVALID_16;
    m_autodefEnabled = true;
    m_file = NULL;
    m_headerLoaded = false;
    m_tableofcontentsLoaded = false;
    m_mediacontentsLoaded = false;
    m_adscriptureLoaded = false;
    m_adcommentaryLoaded = false;
    m_adstrongshLoaded = false;
    m_adstrongsgLoaded = false;
    m_adtermLoaded = false;
    m_adnotesLoaded = false;
    m_masterKey = NULL;
}

SwModule::~SwModule()
{
    if (m_path)
        free(m_path);

    if (m_file)
        fclose(m_file);
}

void SwModule::Reset()
{
    if (m_file)
        fclose(m_file);

    m_file = NULL;
    SetPath("");
    m_header.Zero();
    m_headerLoaded = false;
    m_managerId = NODE_ID_INVALID_16;
    m_tableofContents.Reset();
    m_tableofcontentsLoaded = false;
    m_mediaContents.Reset();
    m_mediacontentsLoaded = false;
    m_autodefVerse.Reset();
    m_adscriptureLoaded = false;
    m_autodefCommentary.Reset();
    m_adcommentaryLoaded = false;
    m_autodefStrongsH.Reset();
    m_adstrongshLoaded = false;
    m_autodefStrongsG.Reset();
    m_adstrongsgLoaded = false;
    m_autodefTerm.Reset();
    m_adtermLoaded = false;
    m_autodefNotes.Reset();
    m_adnotesLoaded = false;
}

bool SwModule::Load(const char * path)
{
    SwString buffer;

    if (!path)
        return false;

    if (m_file)
        return true;

    m_file = SwFopen(path, FMD_R);

    if (!m_file)
        return false;

    if (!m_header.ReadData(m_file))
    {
        fclose(m_file);
        m_file = NULL;
        return false;
    }

    if (m_header.isEncrypted && !SwApplicationInterface::GetDecryptor())
    {
        fclose(m_file);
        m_file = NULL;
        return false;
    }

    m_headerLoaded = true;

    SetPath(path);

    return true;
}

SwModuleHeader & SwModule::GetHeader()
{
    return m_header;
}

SwTableOfContents & SwModule::GetTableofContents()
{
    if (!m_headerLoaded || !m_file)
        return m_tableofContents;

    if (!m_tableofcontentsLoaded)
    {
        fseek(m_file, m_header.tableofcontentsLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_tableofcontentsLoaded = m_tableofContents.ReadFromFile(m_file);
        else
            m_tableofcontentsLoaded = m_tableofContents.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_tableofContents;
}

SwMediaContents & SwModule::GetMediaContents()
{
    if (!m_headerLoaded || !m_file)
        return m_mediaContents;

    if (!m_mediacontentsLoaded)
    {
        fseek(m_file, m_header.mediacontentsLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_mediacontentsLoaded = m_mediaContents.ReadFromFile(m_file);
        else
            m_mediacontentsLoaded = m_mediaContents.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_mediaContents;
}

SwAutoDefScripture & SwModule::GetADScripture()
{
    if (!m_headerLoaded || !m_file)
        return m_autodefVerse;

    if (!m_adscriptureLoaded)
    {
        fseek(m_file, m_header.autodefverseLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_adscriptureLoaded = m_autodefVerse.ReadFromFile(m_file);
        else
            m_adscriptureLoaded = m_autodefVerse.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_autodefVerse;
}

SwAutoDefCommentary & SwModule::GetADCommentary()
{
    if (!m_headerLoaded || !m_file)
        return m_autodefCommentary;

    if (!m_adcommentaryLoaded)
    {
        fseek(m_file, m_header.autodefcommentaryLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_adcommentaryLoaded = m_autodefCommentary.ReadFromFile(m_file);
        else
            m_adcommentaryLoaded = m_autodefCommentary.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_autodefCommentary;
}

SwAutoDefTerm & SwModule::GetADTerm()
{
    if (!m_headerLoaded || !m_file)
        return m_autodefTerm;

    if (!m_adtermLoaded)
    {
        fseek(m_file, m_header.autodeftermLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_adtermLoaded = m_autodefTerm.ReadFromFile(m_file);
        else
            m_adtermLoaded = m_autodefTerm.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_autodefTerm;
}

SwAutoDefNumbered & SwModule::GetADStrongsH()
{
    if (!m_headerLoaded || !m_file)
        return m_autodefStrongsH;

    if (!m_adstrongshLoaded)
    {
        fseek(m_file, m_header.autodefstrongshLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_adstrongshLoaded = m_autodefStrongsH.ReadFromFile(m_file);
        else
            m_adstrongshLoaded = m_autodefStrongsH.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_autodefStrongsH;
}

SwAutoDefNumbered & SwModule::GetADStrongsG()
{
    if (!m_headerLoaded || !m_file)
        return m_autodefStrongsG;

    if (!m_adstrongsgLoaded)
    {
        fseek(m_file, m_header.autodefstrongsgLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_adstrongsgLoaded = m_autodefStrongsG.ReadFromFile(m_file);
        else
            m_adstrongsgLoaded = m_autodefStrongsG.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_autodefStrongsG;
}

SwAutoDefNumbered & SwModule::GetADNotes()
{
    if (!m_headerLoaded || !m_file)
        return m_autodefNotes;

    if (!m_adnotesLoaded)
    {
        fseek(m_file, m_header.autodefnotesLocator,SEEK_SET);
        if (!m_header.isEncrypted)
            m_adnotesLoaded = m_autodefNotes.ReadFromFile(m_file);
        else
            m_adnotesLoaded = m_autodefNotes.ReadFromFile(m_file, m_header.k1, m_header.k2);
    }

    return m_autodefNotes;
}

FILE * SwModule::GetFile()
{
    return m_file;
}

void SwModule::SetPath(const char * path)
{
    if (m_path)
        free(m_path);

    m_path = strdup(path);
}

const char * SwModule::GetPath()
{
    return m_path;
}

bool SwModule::GetAutodefEnabled()
{
    return m_autodefEnabled;
}

void SwModule::SetAutodefEnabled(bool enabled)
{
    m_autodefEnabled = enabled;
}

const char * SwModule::GetFormattedAbbreviation()
{
    static SwString formatBuffer;
    char s[] = "<module id=\"%u\">%s</module>";
    formatBuffer.Size(strlen(s) + m_header.GetAbbreviationLength() + 31);
    sprintf(formatBuffer, s, m_managerId, m_header.moduleAbbreviation);

    return formatBuffer;
}

const char * SwModule::GetFormattedModuleId()
{
    static SwString formatBuffer;
    char s[] = "<module id=\"%u\"/>";
    formatBuffer.Size(strlen(s) + 31);
    sprintf(formatBuffer, s, m_managerId);

    return formatBuffer;
}

void SwModule::SetManagerId(swUI16 managerId)
{
    m_managerId = managerId;
}

swUI16 SwModule::GetManagerId()
{
    return m_managerId;
}

bool SwModule::ReadData(SwString & buffer, SwModuleItemId identifierStart)
{
    SwModuleItem dataStart, dataEnd;
    swUI32 dataSize;

    if (!m_file)
        return false;

    if (identifierStart >= m_header.items)
        return false;

    fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * identifierStart), SEEK_SET);
    fread((void *) &dataStart, sizeof(SwModuleItem), 1, m_file);
    dataSize = dataStart.size;

    if (dataStart.divItems > 1)
    {
        fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * (identifierStart + (dataStart.divItems - 1))), SEEK_SET);
        fread((void *) &dataEnd, sizeof(SwModuleItem), 1, m_file);
        dataSize = (dataEnd.position - dataStart.position) + dataEnd.size;
    }

    buffer.Size(buffer.GetCount() + dataSize + 1);

    if (!m_header.isEncrypted)
    {
        fseek(m_file, m_header.filecontentsLocator + dataStart.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), dataSize, m_file);
    }
    else
    {
        fseek(m_file, m_header.filecontentsLocator + (dataStart.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), dataSize, m_file, m_header.k1, m_header.k2);
    }

    buffer.SetAt(buffer.GetCount() + dataSize, '\0');
    buffer.IncrementCount(dataSize);

    return true;
}

bool SwModule::ReadData(SwString & buffer, SwModuleItemId identifierStart, swUI32 items)
{
    SwModuleItem dataStart, dataEnd;
    swUI32 dataSize;

    if (!m_file)
        return false;

    if (identifierStart >= m_header.items || identifierStart + (items - 1) >= m_header.items)
        return false;

    if (items == 1)
    {
        fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * identifierStart), SEEK_SET);
        fread((void *) &dataStart, sizeof(SwModuleItem), 1, m_file);
        dataSize = dataStart.size;
    }
    else
    {
        fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * identifierStart), SEEK_SET);
        fread((void *) &dataStart, sizeof(SwModuleItem), 1, m_file);
        fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * (identifierStart + (items - 1))), SEEK_SET);
        fread((void *) &dataEnd, sizeof(SwModuleItem), 1, m_file);
        dataSize = (dataEnd.position - dataStart.position) + dataEnd.size;
    }

    buffer.Size(buffer.GetCount() + dataSize + 1);

    if (!m_header.isEncrypted)
    {
        fseek(m_file, m_header.filecontentsLocator + dataStart.position, SEEK_SET);
        fread(buffer.GetArray() + buffer.GetCount(), sizeof(char), dataSize, m_file);
    }
    else
    {
        fseek(m_file, m_header.filecontentsLocator + (dataStart.position * 2), SEEK_SET);
        SwTranscryptor::decryptfread(buffer.GetArray() + buffer.GetCount(), sizeof(char), dataSize, m_file, m_header.k1, m_header.k2);
    }

    buffer.SetAt(buffer.GetCount() + dataSize, '\0');
    buffer.IncrementCount(dataSize);

    return true;
}

bool SwModule::GetItemData(SwModuleItemArray & itemData, SwModuleItemId identifierStart)
{
    if (!m_file)
        return false;

    if (identifierStart >= m_header.items)
        return false;

    itemData.Size(1);
    itemData.SetCount(0);

    fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * identifierStart), SEEK_SET);
    fread((void *) itemData, sizeof(SwModuleItem), 1, m_file);

    if (identifierStart + (itemData.GetAt(0).divItems - 1) >= m_header.items)
        return false;

    if (itemData.GetAt(0).divItems == 1)
    {
        itemData.SetCount(1);
        return true;
    }
    else
    {
        itemData.Size(itemData.GetAt(0).divItems);
        fseek(m_file, m_header.itemdataLocator + (sizeof(SwModuleItem) * identifierStart), SEEK_SET);
        fread((void *) itemData.GetArray(), sizeof(SwModuleItem), itemData.GetAt(0).divItems, m_file);
        itemData.SetCount(itemData.GetAt(0).divItems);
    }

    return true;
}

SwKeyManager::SwKeyManager()
{
    m_array = NULL;
    m_arrayPos = 0;
    m_objectsAllocated = 0;
}

SwKeyManager::~SwKeyManager()
{
    ReleaseArray();
}

swUI16 SwKeyManager::AssignObject()
{
    if (m_arrayPos >= m_objectsAllocated && !IncreaseArray())
        return NODE_ID_INVALID_16;

    m_array[m_arrayPos] = NULL;
    m_arrayPos ++;

    return m_arrayPos - 1;
}

bool SwKeyManager::IncreaseArray()
{
    if (m_objectsAllocated >= NODE_ID_INVALID_16 - 17)
        return false;

    SwModuleKey ** p = (SwModuleKey **) realloc((void *) m_array, (m_objectsAllocated + 16) * sizeof(SwModuleKey *));

    if (p)
    {
        m_objectsAllocated += 16;
        m_array = p;

        return true;
    }

    return false;
}

void SwKeyManager::ReleaseArray()
{
    if (m_array)
    {
        DeleteAll();
        free(m_array);
    }

    m_array = NULL;
    m_objectsAllocated = 0;
    m_arrayPos = 0;
}

swUI16 SwKeyManager::Add(SwModuleKey * key)
{

    swUI16 pos = AssignObject();

    if (pos == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    m_array[pos] = key;

    return pos;
}

void SwKeyManager::Delete(swUI16 pos)
{
    if (pos >= m_arrayPos)
        return;

    delete m_array[pos];
    m_array[pos] = NULL;

    if (m_arrayPos >= 1)
    {
        pos ++;

        while (pos < m_arrayPos)
        {
            m_array[pos -1] = m_array[pos];
            pos ++;
        }
    }

    m_arrayPos --;
}

bool SwKeyManager::Insert(swUI16 insertPos, SwModuleKey * key)
{
    swUI16 last = AssignObject();

    if (last == NODE_ID_INVALID_16)
        return false;

    swUI16 pos = m_arrayPos;
    while(pos > insertPos)
    {
        m_array[pos] = m_array[pos - 1];
        pos --;
    }

    m_array[insertPos] = key;

    return true;
}

void SwKeyManager::DeleteAll()
{
    swUI16 pos = 0;

    if (!m_array)
        return;

    while(pos < m_arrayPos)
    {
        delete m_array[pos];
        m_array[pos] = NULL;
        pos ++;
    }

    m_arrayPos = 0;
}

swUI16 SwKeyManager::FindKey(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {

        if (strcmp(id, m_array[pos]->identifier) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwKeyManager::FindMasterKey(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if ((strcmp(id, m_array[pos]->identifier) == 0) && (m_array[pos]->header.IsMaster()))
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

SwModuleKey * SwKeyManager::GetKey(swUI16 pos)
{
    if (pos >= m_arrayPos)
        return NULL;

    return m_array[pos];
}

void SwKeyManager::SetKey(swUI16 pos, SwModuleKey * key)
{
    if (pos >= m_arrayPos)
        return;

    m_array[pos] = key;
}

swUI16 SwKeyManager::GetKeys()
{
    return m_arrayPos;
}

SwKeyLoader::SwKeyLoader()
{
}

SwKeyLoader::~SwKeyLoader()
{
}

bool SwKeyLoader::OnFile(const char * path)
{
    SwModuleKey * key = new SwModuleKey;
    if (!key->Load(path))
    {
        delete key;
    }
    else
    {
        SwApplicationInterface::GetKeyManager().Add(key);
    }

    return true;
}
