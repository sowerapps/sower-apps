///////////////////////////////////////////////////////////////////
// Name:        thmlfilemanager.cpp
// Purpose:     SwThMLFileManager
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thmlfilemanager.h"
#include "../../include/html/html.h"
#include "../../include/appi/appifa.h"

SwThMLFileManager::SwThMLFileManager()
{
    m_array = NULL;
    m_arrayPos = 0;
    m_objectsAllocated = 0;
    m_idPos = FILEMANAGER_ID_START;
}

SwThMLFileManager::~SwThMLFileManager()
{
    ReleaseArray();
}

void SwThMLFileManager::Reset()
{
    DeleteAll();

    if (SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnThMLFileManagerReset();
}

swUI16 SwThMLFileManager::AssignObject()
{
    if (m_arrayPos >= m_objectsAllocated && !IncreaseArray())
        return NODE_ID_INVALID_16;

    m_array[m_arrayPos] = NULL;
    m_arrayPos ++;

    return m_arrayPos - 1;
}

bool SwThMLFileManager::IncreaseArray()
{
    if (m_objectsAllocated >= NODE_ID_INVALID_16 - 17)
        return false;

    SwThMLFile ** p = (SwThMLFile **) realloc((void *) m_array, (m_objectsAllocated + 16) * sizeof(SwThMLFile *));

    if (p)
    {
        m_objectsAllocated += 16;
        m_array = p;

        return true;
    }

    return false;
}

void SwThMLFileManager::ReleaseArray()
{
    if (m_array)
    {
        DeleteAll();
        free(m_array);
    }

    m_array = NULL;
    m_objectsAllocated = 0;
    m_arrayPos = 0;
    m_idPos = FILEMANAGER_ID_START;
}

swUI16 SwThMLFileManager::Add(SwThMLFile * file, bool notify)
{
    swUI16 pos = AssignObject();

    if (pos == NODE_ID_INVALID_16)
        return NODE_ID_INVALID_16;

    m_array[pos] = file;
    m_array[pos]->SetManagerId(m_idPos);

    m_idPos ++;

    if (notify && SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnThMLFileAdded(file->GetManagerId());

    return pos;
}

void SwThMLFileManager::Delete(swUI16 pos, bool notify)
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
        SwApplicationInterface::GetFrameWindow()->OnThMLFileDeleted(id);
}

bool SwThMLFileManager::Insert(swUI16 insertPos, SwThMLFile * file, bool notify)
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

    m_array[insertPos] = file;
    m_array[insertPos]->SetManagerId(m_idPos);

    m_idPos ++;

    if (notify && SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnThMLFileAdded(file->GetManagerId());

    return true;
}

void SwThMLFileManager::DeleteAll()
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

swUI16 SwThMLFileManager::FindByAbbrev(const char * abbrev)
{
    swUI16 pos = 0;

    if (!abbrev)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(abbrev, m_array[pos]->GetAbbreviation()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwThMLFileManager::FindById(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(id, m_array[pos]->GetIdentifier()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwThMLFileManager::FindByTitle(const char * title)
{
    swUI16 pos = 0;

    if (!title)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(title, m_array[pos]->GetTitle()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwThMLFileManager::FindByCcelFileName(const char * name)
{
    swUI16 pos = 0;

    if (!name)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(name, m_array[pos]->GetFileName()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwThMLFileManager::FindByMID(swUI16 managerId)
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

swUI16 SwThMLFileManager::FindByPath(const char * path)
{
    swUI16 pos = 0;

    if (!path)
        return NODE_ID_INVALID_16;

    while (pos < m_arrayPos)
    {
        if (strcmp(path, m_array[pos]->GetPath()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

const char * SwThMLFileManager::GetTitleFromPath(const char * path)
{
    if (!path)
        return "";

    swUI16 id = FindByPath(path);

    if (id == NODE_ID_INVALID_16)
        return "";

    return GetAt(id)->GetTitle();
}

SwThMLFile * SwThMLFileManager::GetAt(swUI16 pos)
{
    if (pos >= m_arrayPos)
        return NULL;

    return m_array[pos];
}

SwThMLFile * SwThMLFileManager::GetFromMID(swUI16 managerId)
{
    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return NULL;

    return m_array[pos];
}

void SwThMLFileManager::SetFile(swUI16 pos, SwThMLFile * file)
{
    if (pos >= m_arrayPos)
        return;

    m_array[pos] = file;
}

swUI16 SwThMLFileManager::GetItemsInCategory(swUI8 category)
{
    swUI16 items = 0;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
       if (GetAt(i)->GetCategory() == category)
            items += i;
    }

    return items;
}

void SwThMLFileManager::AddFileIdByCategory(Swui16Array & idArray, swUI8 category)
{
    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (category == CATEGORY_ALLTEXT &&
                (GetAt(i)->m_category != CATEGORY_ART &&
                 GetAt(i)->m_category != CATEGORY_MAP &&
                 GetAt(i)->m_category != CATEGORY_MEDIA &&
                 GetAt(i)->m_category != CATEGORY_HYMNAL))
            idArray += i;
        else if (GetAt(i)->m_category == category)

            idArray += i;
    }
}

const char * SwThMLFileManager::GetFirstPageId(const char * path)
{
    if (!path)
        return "0";

    swUI16 id = FindByPath(path);

    if (id == NODE_ID_INVALID_16)
        return "0";

    return GetAt(id)->GetTableofContents().GetIdText(0);
}

swUI16 SwThMLFileManager::GetFileCount()
{
    return m_arrayPos;
}
