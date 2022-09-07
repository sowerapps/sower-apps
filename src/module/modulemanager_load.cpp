///////////////////////////////////////////////////////////////////
// Name:        modulemanager_load.cpp
// Purpose:     Content loading routines for SwModuleManager.
// Copyright:   David Reynolds
///////////////////////////////////////////////////////////////////

#include "../../include/module/modulemanager.h"
#include "../../include/appi/appifa.h"
#include "../../include/html/html.h"

bool SwModuleManager::LoadAutoDefPage(SwPageData & pageData, SwString & pageBuffer, bool & canCopy)
{
    swUI16 pos = FindByMID(pageData.m_managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    if (!module->m_file)
        return false;

    pageBuffer = AUTODEF_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    if (!module->GetTableofContents().GetNode(pageData.m_pageId)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    if (module->GetTableofContents().GetNode(pageData.m_pageId)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", module->GetTableofContents().GetNode(pageData.m_pageId)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += AUTODEF_CLOSE;
    return true;
}

bool SwModuleManager::LoadAutoDefPage(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy)
{
    if (!id)
        return false;

    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    swUI16 node = module->GetTableofContents().FindByID(id);

    if (node == NODE_ID_INVALID_16)
    {
        return false;
    }

    SwModuleItemId identifier = module->GetTableofContents().GetIdentifier(node);

    if (identifier == MITEMIDINVALID)
        return false;

    pos = module->GetTableofContents().FindItem(identifier);

    if (pos == NODE_ID_INVALID_16)
        return false;

    if (!module->m_file)
        return false;

    pageBuffer = AUTODEF_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    if (!module->GetTableofContents().GetNode(pos)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    if (module->GetTableofContents().GetNode(pos)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", module->GetTableofContents().GetNode(pos)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += AUTODEF_CLOSE;
    return true;
}

bool SwModuleManager::LoadAutoDefItem(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy)
{
    if (!id)
        return false;

    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    swUI16 node = module->GetTableofContents().FindByID(id);

    if (node == NODE_ID_INVALID_16)
    {
        return false;
    }

    if (!module->m_file)
        return false;

    pageBuffer = AUTODEF_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    if (!module->GetTableofContents().GetNode(pos)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    pageBuffer += AUTODEF_CLOSE;
    return true;
}

bool SwModuleManager::LoadElectronicInfo(swUI16 managerId, SwString & pageBuffer)
{
    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    if (module->m_header.infoItem == MITEMIDINVALID)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += "\n<div1>";

    module->ReadData(pageBuffer, module->m_header.infoItem);

    pageBuffer += "\n</div1>\n";
    pageBuffer += THML_CLOSE;

    return true;
}

bool SwModuleManager::LoadPage(SwPageData & pageData, SwString & pageBuffer, bool & canCopy)
{
    if (!pageData.VerifyId(MANAGER_ID_START))
        return false;

    swUI16 pos = FindByMID(pageData.m_managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    if (!module->m_file)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    if (!module->GetTableofContents().GetNode(pageData.m_pageId)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    if (module->GetTableofContents().GetNode(pageData.m_pageId)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", module->GetTableofContents().GetNode(pageData.m_pageId)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwModuleManager::LoadPage(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy)
{
    if (!id)
        return false;

    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    swUI16 node = module->GetTableofContents().FindByID(id);

    if (node == NODE_ID_INVALID_16)
    {
        return false;
    }

    SwModuleItemId identifier = module->GetTableofContents().GetIdentifier(node);

    if (identifier == MITEMIDINVALID)
        return false;

    if (!module->m_file)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    if (!module->GetTableofContents().GetNode(pos)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    if (module->GetTableofContents().GetNode(pos)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", module->GetTableofContents().GetNode(pos)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwModuleManager::LoadItem(swUI16 managerId, const char * id, SwString & pageBuffer, bool & canCopy)
{
    if (!id)
        return false;

    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    swUI16 node = module->GetTableofContents().FindByID(id);

    if (node == NODE_ID_INVALID_16)
    {
        return false;
    }

    if (!module->m_file)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    if (!module->GetTableofContents().GetNode(pos)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwModuleManager::LoadBookMark(SwBookMarkData & bookmarkData, SwString & pageBuffer, bool & canCopy)
{
    swUI16 pos = FindById(bookmarkData.m_bookId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;

    if (!module->m_file)
        return false;

    pageBuffer = THML_OPEN;
    pageBuffer += module->GetFormattedModuleId();

    swUI16 pageId = (swUI16) bookmarkData.m_pageId.Strtoul();

    if (!module->GetTableofContents().GetNode(pageId)->ReadData(module->m_file, pageBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    if (module->GetTableofContents().GetNode(pageId)->hasChildren)
    {
        char s[12];
        sprintf(s, "\n</div%u>", module->GetTableofContents().GetNode(pageId)->divDepth);
        pageBuffer.Strcat(s);
    }

    pageBuffer += THML_CLOSE;
    return true;
}

bool SwModuleManager::LoadMedia(swUI16 managerId, const char * id, SwStreamBuffer & dataBuffer, bool & canCopy)
{
    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;
    pos = module->GetMediaContents().FindItem(id);

    if (pos == NODE_ID_INVALID_16)
        return false;

    if (!module->m_file)
        return false;

    if (!module->GetMediaContents().GetNode(pos)->ReadData(module->m_file, dataBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    return true;
}

bool SwModuleManager::LoadMedia(swUI16 managerId, const char * id, Swui8Array & dataBuffer, bool & canCopy)
{
    swUI16 pos = FindByMID(managerId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    SwModule * module = GetAt(pos);

    if (!module)
        return false;

    canCopy = module->m_header.canCopy;
    pos = module->GetMediaContents().FindItem(id);

    if (pos == NODE_ID_INVALID_16)
        return false;

    if (!module->m_file)
        return false;

    if (!module->GetMediaContents().GetNode(pos)->ReadData(module->m_file, dataBuffer, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted))
        return false;

    return true;
}
