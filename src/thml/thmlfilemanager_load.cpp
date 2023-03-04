///////////////////////////////////////////////////////////////////
// Name:        thmlfilemanager_load.cpp
// Purpose:     Content loading routines for SwThMLFileManager.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thmlfilemanager.h"
#include "../../include/appi/appifa.h"
#include "../../include/filesys/recurse.h"
#include "../../include/filesys/file.h"
#include "../../include/html/html.h"

bool SwThMLFileManager::LoadAutoDefPage(SwPageData & pageData, SwString & pageBuffer)
{
    SwThMLFile * file = GetFromMID(pageData.m_managerId);

    if (!file || !file->m_file)
        return false;

    pageBuffer = AUTODEF_OPEN;
    pageBuffer += file->GetFormattedId();

    if (!file->GetTableofContents().GetNode(pageData.m_pageId)->ReadData(file->m_file, pageBuffer))
        return false;

    if (file->GetTableofContents().GetNode(pageData.m_pageId)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", file->GetTableofContents().GetNode(pageData.m_pageId)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += AUTODEF_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadAutoDefPage(swUI16 managerId, const char * id, SwString & pageBuffer)
{
    if (!id)
        return false;

    SwThMLFile * file = GetFromMID(managerId);

    if (!file || !file->m_file)
        return false;

    swUI16 pos = file->GetTableofContents().FindByID(id);

    if (pos == NODE_ID_INVALID_16)
        return false;

    pageBuffer = AUTODEF_OPEN;
    pageBuffer += file->GetFormattedId();

    if (!file->GetTableofContents().GetNode(pos)->ReadData(file->m_file, pageBuffer))
        return false;

    if (file->GetTableofContents().GetNode(pos)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", file->GetTableofContents().GetNode(pos)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += AUTODEF_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadAutoDefItem(swUI16 managerId, const char * id, SwString & pageBuffer)
{
    if (!id)
        return false;

    SwThMLFile * file = GetFromMID(managerId);

    if (!file || !file->m_file)
        return false;

    swUI16 pos = file->GetTableofContents().FindByID(id);

    if (pos == NODE_ID_INVALID_16)
        return false;

    pageBuffer = AUTODEF_OPEN;
    pageBuffer += file->GetFormattedId();

    if (!file->GetTableofContents().GetNode(pos)->ReadData(file->m_file, pageBuffer))
        return false;

    pageBuffer += AUTODEF_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadElectronicInfo(swUI16 managerId, SwString & pageBuffer)
{
    SwThMLFile * file = GetFromMID(managerId);

    if (!file)
        return false;

    if (file->m_infoPos == NODE_ID_INVALID_16)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += "\n<div1>";

    file->ReadInfoData(pageBuffer);

    pageBuffer += "\n</div1>\n";
    pageBuffer += THML_CLOSE;

    return true;
}

bool SwThMLFileManager::LoadPage(SwPageData & pageData, SwString & pageBuffer)
{
    if (!pageData.VerifyId(FILEMANAGER_ID_START))
        return false;

    SwThMLFile * file = GetFromMID(pageData.m_managerId);

    if (!file || !file->m_file)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += file->GetFormattedId();

    if (!file->GetTableofContents().GetNode(pageData.m_pageId)->ReadData(file->m_file, pageBuffer))
        return false;

    if (file->GetTableofContents().GetNode(pageData.m_pageId)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", file->GetTableofContents().GetNode(pageData.m_pageId)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadPage(swUI16 managerId, const char * id, SwString & pageBuffer)
{
    if (!id)
        return false;

    SwThMLFile * file = GetFromMID(managerId);

    if (!file || !file->m_file)
        return false;

    swUI16 pos = file->GetTableofContents().FindByID(id);

    if (pos == NODE_ID_INVALID_16)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += file->GetFormattedId();

    if (!file->GetTableofContents().GetNode(pos)->ReadData(file->m_file, pageBuffer))
        return false;

    if (file->GetTableofContents().GetNode(pos)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", file->GetTableofContents().GetNode(pos)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadItem(swUI16 managerId, const char * id, SwString & pageBuffer)
{
    if (!id)
        return false;

    SwThMLFile * file = GetFromMID(managerId);

    if (!file || !file->m_file)
        return false;

    swUI16 pos = file->GetTableofContents().FindByID(id);

    if (pos == NODE_ID_INVALID_16)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += file->GetFormattedId();

    if (!file->GetTableofContents().GetNode(pos)->ReadData(file->m_file, pageBuffer))
        return false;

    if (file->GetTableofContents().GetNode(pos)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", file->GetTableofContents().GetNode(pos)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadBookMark(SwBookMarkData & bookmarkData, SwString & pageBuffer)
{
    swUI16 pos = FindByPath(bookmarkData.m_bookId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwThMLFile * file = GetAt(pos);

    if (!file || !file->m_file)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += file->GetFormattedId();

    pos = file->GetTableofContents().FindByID(bookmarkData.m_pageId);

    if (pos == NODE_ID_INVALID_16 || !file->GetTableofContents().GetNode(pos)->ReadData(file->m_file, pageBuffer))
        return false;

    if (file->GetTableofContents().GetNode(pos)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", file->GetTableofContents().GetNode(pos)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwThMLFileManager::LoadMedia(swUI16 managerId, const char * id, SwString & dataBuffer)
{
    if (!id)
        return false;

    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwThMLFile * file = GetAt(pos);

    if (!file || !file->m_file)
        return false;

    SwString path;

    SwGetPathFromRelative(file->m_basePath, id, path);
    swUI32 size = SwFile::GetSize(path);
    dataBuffer.Size(size);

    FILE * f = SwFopen(path, FMD_R);

    if (!f)
        return false;

    swUI32 read = fread(dataBuffer, 1, size, f);

    fclose(f);

    if (read != size)
        return false;

    return true;
}
