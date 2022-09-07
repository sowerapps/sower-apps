///////////////////////////////////////////////////////////////////
// Name:        modulemanager.cpp
// Purpose:     SwModuleManager
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/modulemanager.h"
#include "../../include/html/html.h"
#include "../../include/appi/appifa.h"

SwModuleManager::SwModuleManager()
{
    m_array = NULL;
    m_arrayPos = 0;
    m_objectsAllocated = 0;
    m_idPos = MANAGER_ID_START;
}

SwModuleManager::~SwModuleManager()
{
    ReleaseArray();
}

void SwModuleManager::Reset()
{
    DeleteAll();

    if (SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnModuleManagerReset();
}

swUI16 SwModuleManager::AssignObject()
{
    if (m_arrayPos >= m_objectsAllocated && !IncreaseArray())
        return NODE_ID_INVALID_16;

    m_array[m_arrayPos] = NULL;
    m_arrayPos ++;

    return m_arrayPos - 1;
}

bool SwModuleManager::IncreaseArray()
{
    if (m_objectsAllocated >= NODE_ID_INVALID_16 - 17)
        return false;

    SwModule ** p = (SwModule **) realloc((void *) m_array, (m_objectsAllocated + 16) * sizeof(SwModule *));

    if (p)
    {
        m_objectsAllocated += 16;
        m_array = p;

        return true;
    }

    return false;
}

void SwModuleManager::ReleaseArray()
{
    if (m_array)
    {
        DeleteAll();
        free(m_array);
    }

    m_array = NULL;
    m_objectsAllocated = 0;
    m_arrayPos = 0;
    m_idPos = MANAGER_ID_START;
}

swUI16 SwModuleManager::Add(SwModule * module, bool notify)
{
    swUI16 pos = AssignObject();

    if (pos == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    m_array[pos] = module;
    m_array[pos]->SetManagerId(m_idPos);

    m_idPos ++;

    if (notify && SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnModuleAdded(module->GetManagerId());

    return pos;
}

void SwModuleManager::Delete(swUI16 pos, bool notify)
{
    if (pos >= m_arrayPos)
        return;

    if (!m_array[pos])
        return;

    swUI16 id = m_array[pos]->GetManagerId();

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

    if (notify && SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnModuleDeleted(id);
}

bool SwModuleManager::Insert(swUI16 insertPos, SwModule * module, bool notify)
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

    m_array[insertPos] = module;
    m_array[insertPos]->SetManagerId(m_idPos);

    m_idPos ++;

    if (notify && SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnModuleAdded(module->GetManagerId());

    return true;
}

void SwModuleManager::DeleteAll()
{
    swUI16 pos = 0;

    if (!m_array)
        return;

    while(pos < m_arrayPos)
    {
        if (m_array[pos])
            delete m_array[pos];

        m_array[pos] = NULL;

        pos ++;
    }

    m_arrayPos = 0;
}

swUI16 SwModuleManager::FindByAbbrev(const char * abbrev)
{
    swUI16 pos = 0;

    if (!abbrev)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(abbrev, m_array[pos]->m_header.moduleAbbreviation) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwModuleManager::FindById(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(id, m_array[pos]->m_header.moduleIdentifier) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwModuleManager::FindByTitle(const char * title)
{
    swUI16 pos = 0;

    if (!title)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(title, m_array[pos]->m_header.moduleTitle) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwModuleManager::FindByCcelFileName(const char * name)
{
    swUI16 pos = 0;

    if (!name)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(name, m_array[pos]->m_header.ccelFileName) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwModuleManager::FindByMID(swUI16 managerId)
{
    swUI16 pos = 0;

    while (pos < m_arrayPos)
    {
        if (managerId == m_array[pos]->GetManagerId())
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

SwModule * SwModuleManager::GetAt(swUI16 pos)
{
    if (pos >= m_arrayPos)
        return NULL;

    return m_array[pos];
}

SwModule * SwModuleManager::GetFromMID(swUI16 managerId)
{
    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return NULL;

    return m_array[pos];
}

void SwModuleManager::SetModule(swUI16 pos, SwModule * module)
{
    if (pos >= m_arrayPos)
        return;

    m_array[pos] = module;
}

swUI16 SwModuleManager::GetItemsInCategory(swUI8 category)
{
    swUI16 items = 0;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
       if (GetAt(i)->m_header.category == category)
            items += i;
    }

    return items;
}

void SwModuleManager::AddModuleIdByCategory(Swui16Array & idArray, swUI8 category)
{
    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (category == CATEGORY_ALLTEXT &&
                (GetAt(i)->m_header.category != CATEGORY_ART &&
                 GetAt(i)->m_header.category != CATEGORY_MAP &&
                 GetAt(i)->m_header.category != CATEGORY_MEDIA &&
                 GetAt(i)->m_header.category != CATEGORY_HYMNAL))
            idArray += i;
        else if (GetAt(i)->m_header.category == category)

            idArray += i;
    }
}

swUI16 SwModuleManager::GetModules()
{
    return m_arrayPos;
}

bool SwModuleManager::SetModuleKey(SwModule * module)
{
    if (!module)
        return false;

    if (module->GetHeader().isEncrypted)
    {
        swUI16 key = SwApplicationInterface::GetKeyManager().FindMasterKey(module->GetHeader().GetIdentifier());

        if (key != NODE_ID_INVALID_16)
        {
            module->m_masterKey = SwApplicationInterface::GetKeyManager().GetKey(key);
        }
        else
        {
            key = SwApplicationInterface::GetKeyManager().FindKey(module->GetHeader().GetIdentifier());
        }

        if (key == NODE_ID_INVALID_16)
        {
            return false;
        }

        module->GetHeader().k1 = SwApplicationInterface::GetKeyManager().GetKey(key)->header.mk1;
        module->GetHeader().k2 = SwApplicationInterface::GetKeyManager().GetKey(key)->header.mk2;
    }

    return true;
}

void SwModuleManager::CreateCardCatalog(SwCatalogCardArray & cardarray)
{
    cardarray.Reset();
    cardarray.Size(m_arrayPos);
    SwCatalogCard card;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        GetAt(i)->m_header.CopyToCard(&card);
        cardarray += card;
    }
}
