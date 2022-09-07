///////////////////////////////////////////////////////////////////
// Name:        modulemanager_ad.cpp
// Purpose:     AutoDef routines for SwModuleManager.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/modulemanager.h"
#include "../../include/appi/appifa.h"
#include "../../include/html/html.h"

bool SwModuleManager::GetAutoDefData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, bool & canCopy)
{
    swUI16 node;
    SwModuleItemId identifier;
    SwString titleBuffer;
    swUI16 pnt;

    if (!vrs)
        return false;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled || (GetAt(i)->m_header.category != CATEGORY_BIBLE))
            continue;

        node = GetAt(i)->GetADScripture().FindChapter(book, chapter);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            identifier = GetAt(i)->GetADScripture().GetChapterData(node)->firstverseNode;
            identifier = GetAt(i)->GetADScripture().GetVerseData(identifier)->identifier;
            pnt = GetAt(i)->GetTableofContents().FindItem(identifier);

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            buffer += ITEM_BREAK;

            if (!GetAt(i)->GetTableofContents().GetNode(pnt)->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(pnt)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>", GetAt(i)->GetTableofContents().GetNode(pnt)->divDepth);
                buffer.Strcat(s);
            }
        }
    }

    SwApplicationInterface::GetThMLFileManager().GetAutoDefBibleData(buffer, vrs, book, chapter);

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled || (GetAt(i)->m_header.category != CATEGORY_BIBLECOMMENTARY))
            continue;

        node = GetAt(i)->GetADCommentary().FindChapter(book, chapter);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            identifier = GetAt(i)->GetADCommentary().GetChapterData(node)->firstverseNode;
            identifier = GetAt(i)->GetADCommentary().GetVerseRangeData(identifier)->identifier;
            pnt = GetAt(i)->GetTableofContents().FindItem(identifier);

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            buffer += ITEM_BREAK;

            if (!GetAt(i)->GetTableofContents().GetNode(pnt)->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(pnt)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>", GetAt(i)->GetTableofContents().GetNode(pnt)->divDepth);
                buffer.Strcat(s);
            }
        }
    }

    SwApplicationInterface::GetThMLFileManager().GetAutoDefCommentaryData(buffer, vrs, book, chapter);

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd, bool & canCopy)
{
    swUI16 idxStart, idxEnd;
    SwString idArray;

    if (!vrs)
        return false;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    SwString versbuffer;
    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled || GetAt(i)->m_header.category != CATEGORY_BIBLE)
            continue;

        idxStart = GetAt(i)->GetADScripture().FindVerse(book, chapter, verseStart);
        if (idxStart == NODE_ID_INVALID_16)
            continue;

        idxEnd = NODE_ID_INVALID_16;
        if (verseEnd)
        {
            idxEnd = GetAt(i)->GetADScripture().FindVerse(book, chapter, verseEnd);
            if (idxEnd == NODE_ID_INVALID_16)
                continue;
        }

        if (!GetAt(i)->m_header.canCopy)
            canCopy = false;

        if (buffer.GetCount() > AUTODEF_OPEN_SZ)
        {
            buffer += ITEM_BREAK;
            buffer += "<br>";
        }

        buffer += GetAt(i)->GetFormattedAbbreviation();
        buffer += ITEM_BREAK;

        if (idxEnd == NODE_ID_INVALID_16)
            idxEnd = idxStart;

        for (SwModuleItemId id = idxStart; id <= idxEnd; id ++)
            GetAt(i)->GetADScripture().GetVerseData(id)->ReadData(GetAt(i)->GetFile(), buffer, GetAt(i)->GetHeader().itemdataLocator, GetAt(i)->GetHeader().filecontentsLocator, GetAt(i)->GetHeader().k1, GetAt(i)->GetHeader().k2, GetAt(i)->GetHeader().isEncrypted);
    }

    SwApplicationInterface::GetThMLFileManager().GetAutoDefBibleData(buffer, vrs, book, chapter, verseStart, verseEnd);

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled || GetAt(i)->m_header.category != CATEGORY_BIBLECOMMENTARY)
            continue;

        idxStart = GetAt(i)->GetADCommentary().FindVerse(book, chapter, verseStart);
        idxEnd = GetAt(i)->GetADCommentary().FindVerse(book, chapter, verseEnd);

        if (idxStart != NODE_ID_INVALID_16 || idxEnd != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            if (idxStart == NODE_ID_INVALID_16)
                idxStart = idxEnd;
            if (idxEnd == NODE_ID_INVALID_16)
                idxEnd = idxStart;

            for (SwModuleItemId pos = idxStart; pos <= idxEnd; pos ++)
                GetAt(i)->GetADCommentary().GetVerseRangeData(pos)->ReadData(GetAt(i)->GetFile(), buffer, GetAt(i)->GetHeader().itemdataLocator, GetAt(i)->GetHeader().filecontentsLocator, GetAt(i)->GetHeader().k1, GetAt(i)->GetHeader().k2, GetAt(i)->GetHeader().isEncrypted);
        }
    }

    SwApplicationInterface::GetThMLFileManager().GetAutoDefCommentaryData(buffer, vrs, book, chapter, verseStart, verseEnd);

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, const char * term, bool & canCopy)
{
    if (!term)
        return false;

    SwStringW wbuffer;
    wbuffer.Copy(term);

    return GetAutoDefData(buffer, wbuffer.GetArray(), canCopy);
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, const wchar_t * term, bool & canCopy)
{
    Swui16Array idArray;
    swUI16 node;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled ||
                (GetAt(i)->m_header.category != CATEGORY_DICTIONARY &&
                 GetAt(i)->m_header.category != CATEGORY_ENCYCLOPEDIA &&
                 GetAt(i)->m_header.category != CATEGORY_LEXICON &&
                 GetAt(i)->m_header.category != CATEGORY_REFERENCE &&
                 GetAt(i)->m_header.category != CATEGORY_TOPICALINDEX &&
                 GetAt(i)->m_header.category != CATEGORY_HELP))
            continue;

        idArray.SetCount(0);
        node = GetAt(i)->GetADTerm().FindItem(term, idArray);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            for (swUI16 pos = 0; pos < idArray.GetCount(); pos ++)
            {
                buffer += ITEM_BREAK;
                GetAt(i)->GetADTerm().GetNode(idArray.GetAt(pos))->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted);
            }
        }
    }

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }


    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, SwStrParser & strList, bool & canCopy)
{
    Swui16Array idArray;
    swUI16 node;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled ||
                (GetAt(i)->m_header.category != CATEGORY_DICTIONARY &&
                 GetAt(i)->m_header.category != CATEGORY_ENCYCLOPEDIA &&
                 GetAt(i)->m_header.category != CATEGORY_LEXICON &&
                 GetAt(i)->m_header.category != CATEGORY_REFERENCE &&
                 GetAt(i)->m_header.category != CATEGORY_TOPICALINDEX &&
                 GetAt(i)->m_header.category != CATEGORY_HELP))
            continue;

        idArray.SetCount(0);
        node = GetAt(i)->GetADTerm().FindItem(strList, idArray);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            for (swUI16 pos = 0; pos < idArray.GetCount(); pos ++)
            {
                buffer += ITEM_BREAK;
                GetAt(i)->GetADTerm().GetNode(idArray.GetAt(pos))->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted);
            }
        }
    }

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, SwStrParserW & strList, bool & canCopy)
{
    Swui16Array idArray;
    swUI16 node;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled ||
                (GetAt(i)->m_header.category != CATEGORY_DICTIONARY &&
                 GetAt(i)->m_header.category != CATEGORY_ENCYCLOPEDIA &&
                 GetAt(i)->m_header.category != CATEGORY_LEXICON &&
                 GetAt(i)->m_header.category != CATEGORY_REFERENCE &&
                 GetAt(i)->m_header.category != CATEGORY_TOPICALINDEX &&
                 GetAt(i)->m_header.category != CATEGORY_HELP))
            continue;

        idArray.SetCount(0);
        node = GetAt(i)->GetADTerm().FindItem(strList, idArray);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            for (swUI16 pos = 0; pos < idArray.GetCount(); pos ++)
            {
                buffer += ITEM_BREAK;
                GetAt(i)->GetADTerm().GetNode(idArray.GetAt(pos))->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted);
            }
        }
    }

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, SwStringArray & strList, bool & canCopy)
{
    Swui16Array idArray;
    swUI16 node;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled ||
                (GetAt(i)->m_header.category != CATEGORY_DICTIONARY &&
                 GetAt(i)->m_header.category != CATEGORY_ENCYCLOPEDIA &&
                 GetAt(i)->m_header.category != CATEGORY_LEXICON &&
                 GetAt(i)->m_header.category != CATEGORY_REFERENCE &&
                 GetAt(i)->m_header.category != CATEGORY_TOPICALINDEX &&
                 GetAt(i)->m_header.category != CATEGORY_HELP))
            continue;

        idArray.SetCount(0);
        node = GetAt(i)->GetADTerm().FindItem(strList, idArray);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            for (swUI16 pos = 0; pos < idArray.GetCount(); pos ++)
            {
                buffer += ITEM_BREAK;
                GetAt(i)->GetADTerm().GetNode(idArray.GetAt(pos))->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted);
            }
        }
    }

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, SwStringWArray & strList, bool & canCopy)
{
    Swui16Array idArray;
    swUI16 node;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled ||
                (GetAt(i)->m_header.category != CATEGORY_DICTIONARY &&
                 GetAt(i)->m_header.category != CATEGORY_ENCYCLOPEDIA &&
                 GetAt(i)->m_header.category != CATEGORY_LEXICON &&
                 GetAt(i)->m_header.category != CATEGORY_REFERENCE &&
                 GetAt(i)->m_header.category != CATEGORY_TOPICALINDEX &&
                 GetAt(i)->m_header.category != CATEGORY_HELP))
            continue;

        idArray.SetCount(0);
        node = GetAt(i)->GetADTerm().FindItem(strList, idArray);
        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            for (swUI16 pos = 0; pos < idArray.GetCount(); pos ++)
            {
                buffer += ITEM_BREAK;
                GetAt(i)->GetADTerm().GetNode(idArray.GetAt(pos))->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted);
            }
        }
    }

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}

bool SwModuleManager::GetAutoDefData(SwString & buffer, swUI16 strongsNumber, swUI8 strongsType, bool & canCopy)
{
    SwString idArray;
    swUI16 node;

    canCopy = true;
    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (!GetAt(i)->m_autodefEnabled ||
                (GetAt(i)->m_header.category != CATEGORY_LEXICON))
            continue;

        if (strongsType == SYNC_TYPE_HEBREW)
            node = GetAt(i)->GetADStrongsH().FindItem(strongsNumber);
        else if (strongsType == SYNC_TYPE_GREEK)
            node = GetAt(i)->GetADStrongsG().FindItem(strongsNumber);
        else
            return false;

        if (node != NODE_ID_INVALID_16)
        {
            if (!GetAt(i)->m_header.canCopy)
                canCopy = false;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();

            buffer += ITEM_BREAK;
            GetAt(i)->GetADTerm().GetNode(node)->ReadData(GetAt(i)->m_file, buffer, GetAt(i)->m_header.itemdataLocator, GetAt(i)->m_header.filecontentsLocator, GetAt(i)->m_header.k1, GetAt(i)->m_header.k2, GetAt(i)->m_header.isEncrypted);
        }
    }

    if (buffer.GetCount() > AUTODEF_OPEN_SZ)
    {
        buffer += AUTODEF_CLOSE;
        return true;
    }

    return false;
}
