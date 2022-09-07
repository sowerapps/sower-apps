///////////////////////////////////////////////////////////////////
// Name:        thmlfilemanager_ad.cpp
// Purpose:     AutoDef routines for SwThMLFileManager.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thmlfilemanager.h"
#include "../../include/appi/appifa.h"
#include "../../include/html/html.h"

bool SwThMLFileManager::GetAutoDefData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter)
{
    swUI16 identifier;
    SwString titleBuffer;

    if (!vrs)
        return false;

    buffer = AUTODEF_OPEN;

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (GetAt(i)->m_category != CATEGORY_BIBLE)
            continue;

        identifier = GetAt(i)->GetTableofContents().FindChapter(book, chapter);

        if (identifier != NODE_ID_INVALID_16)
        {
            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            if (!GetAt(i)->GetTableofContents().GetNode(identifier)->ReadData(GetAt(i)->m_file, buffer))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(identifier)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>", GetAt(i)->GetTableofContents().GetNode(identifier)->divDepth);
                buffer.Strcat(s);
            }
        }
    }

    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (GetAt(i)->m_category != CATEGORY_BIBLECOMMENTARY)
            continue;

        identifier = GetAt(i)->GetTableofContents().FindChapter(book, chapter);
        if (identifier != NODE_ID_INVALID_16)
        {
            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            if (!GetAt(i)->GetTableofContents().GetNode(identifier)->ReadData(GetAt(i)->m_file, buffer))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(identifier)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>", GetAt(i)->GetTableofContents().GetNode(identifier)->divDepth);
                buffer.Strcat(s);
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

bool SwThMLFileManager::GetAutoDefBibleData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter)
{
    swUI16 identifier;
    SwString titleBuffer, pageBuffer;
    swUI32 startPos = buffer.GetCount();

    if (!vrs)
        return false;


    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (GetAt(i)->m_category != CATEGORY_BIBLE || !GetAt(i)->m_autodefEnabled)
            continue;

        identifier = GetAt(i)->GetTableofContents().FindChapter(book, chapter);
        if (identifier != NODE_ID_INVALID_16)
        {
            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            pageBuffer = THML_OPEN;
            if (!GetAt(i)->GetTableofContents().GetNode(identifier)->ReadData(GetAt(i)->m_file, pageBuffer))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(identifier)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>\n", GetAt(i)->GetTableofContents().GetNode(identifier)->divDepth);
                pageBuffer.Strcat(s);
            }

            pageBuffer += THML_CLOSE;

            SwApplicationInterface::GetRichInterface().Reset();
            SwApplicationInterface::GetRichInterface().SetIsThML(true);
            SwApplicationInterface::GetRichInterface().SetCtrl(NULL);
            SwApplicationInterface::GetRichInterface().SetCssFile(&GetAt(i)->m_cssrules);
            SwApplicationInterface::GetRichInterface().SetBasePath(GetAt(i)->m_basePath);
            SwApplicationInterface::GetRichInterface().Load(pageBuffer, pageBuffer.Strlen());
            SwApplicationInterface::GetRichInterface().Inline();
            SwApplicationInterface::GetRichInterface().ProcessThMLNotes();
            SwApplicationInterface::GetRichInterface().GetNodesData(2, SwApplicationInterface::GetRichInterface().GetParserNodes() - 2, pageBuffer);
            buffer += pageBuffer;
        }
    }

    if (buffer.GetCount() > startPos)
        return true;

    return false;
}

bool SwThMLFileManager::GetAutoDefBibleData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd)
{
    swUI16 identifier;
    SwString titleBuffer, pageBuffer;
    swUI32 startPos = buffer.GetCount();
    SwScriptureRange sr;
    SwNodeRange nr;

    if (!vrs)
        return false;


    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (GetAt(i)->m_category != CATEGORY_BIBLE || !GetAt(i)->m_autodefEnabled)
            continue;

        identifier = GetAt(i)->GetTableofContents().FindChapter(book, chapter);

        if (identifier != NODE_ID_INVALID_16)
        {
            pageBuffer = THML_OPEN;
            if (!GetAt(i)->GetTableofContents().GetNode(identifier)->ReadData(GetAt(i)->m_file, pageBuffer))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(identifier)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>\n", GetAt(i)->GetTableofContents().GetNode(identifier)->divDepth);
                pageBuffer.Strcat(s);
            }

            pageBuffer += THML_CLOSE;

            sr.m_book = book;
            sr.m_chapter = chapter;
            sr.m_verseStart = verseStart;
            sr.m_verseEnd = verseEnd;

            SwApplicationInterface::GetRichInterface().Reset();
            SwApplicationInterface::GetRichInterface().SetIsThML(true);
            SwApplicationInterface::GetRichInterface().SetCtrl(NULL);
            SwApplicationInterface::GetRichInterface().SetCssFile(&GetAt(i)->m_cssrules);
            SwApplicationInterface::GetRichInterface().SetBasePath(GetAt(i)->m_basePath);
            SwApplicationInterface::GetRichInterface().Load(pageBuffer, pageBuffer.Strlen());
            SwApplicationInterface::GetRichInterface().Inline();
            SwApplicationInterface::GetRichInterface().Containorize(THML_SCRIPTURE, "scripture");
            SwApplicationInterface::GetRichInterface().ProcessThMLNotes();

            if (!SwApplicationInterface::GetRichInterface().FindScriptureRange(sr, nr))
                continue;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            SwApplicationInterface::GetRichInterface().GetNodesData(nr, pageBuffer);
            buffer += pageBuffer;
        }
    }

    if (buffer.GetCount() > startPos)
        return true;

    return false;
}

bool SwThMLFileManager::GetAutoDefCommentaryData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter)
{
    swUI16 identifier;
    SwString titleBuffer, pageBuffer;
    swUI32 startPos = buffer.GetCount();

    if (!vrs)
        return false;


    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (GetAt(i)->m_category != CATEGORY_BIBLECOMMENTARY || !GetAt(i)->m_autodefEnabled)
            continue;

        identifier = GetAt(i)->GetTableofContents().FindChapter(book, chapter);

        if (identifier != NODE_ID_INVALID_16)
        {
            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            pageBuffer = THML_OPEN;
            if (!GetAt(i)->GetTableofContents().GetNode(identifier)->ReadData(GetAt(i)->m_file, pageBuffer))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(identifier)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>", GetAt(i)->GetTableofContents().GetNode(identifier)->divDepth);
                pageBuffer.Strcat(s);
            }

            pageBuffer += THML_CLOSE;

            SwApplicationInterface::GetRichInterface().Reset();
            SwApplicationInterface::GetRichInterface().SetIsThML(true);
            SwApplicationInterface::GetRichInterface().SetCtrl(NULL);
            SwApplicationInterface::GetRichInterface().SetCssFile(&GetAt(i)->m_cssrules);
            SwApplicationInterface::GetRichInterface().SetBasePath(GetAt(i)->m_basePath);
            SwApplicationInterface::GetRichInterface().Load(pageBuffer, pageBuffer.Strlen());
            SwApplicationInterface::GetRichInterface().Inline();
            SwApplicationInterface::GetRichInterface().ProcessThMLNotes();
            SwApplicationInterface::GetRichInterface().GetNodesData(2, SwApplicationInterface::GetRichInterface().GetParserNodes() - 2, pageBuffer);
            buffer += pageBuffer;
        }
    }

    if (buffer.GetCount() > startPos)
        return true;

    return false;
}

bool SwThMLFileManager::GetAutoDefCommentaryData(SwString & buffer, const char * vrs, swUI8 book, swUI8 chapter, swUI8 verseStart, swUI8 verseEnd)
{
    swUI16 identifier;
    SwString titleBuffer, pageBuffer;
    swUI32 startPos = buffer.GetCount();
    SwScriptureRange sr;
    SwNodeRange nr;

    if (!vrs)
        return false;


    for (swUI16 i = 0; i < m_arrayPos; i++)
    {
        if (GetAt(i)->m_category != CATEGORY_BIBLECOMMENTARY || !GetAt(i)->m_autodefEnabled)
            continue;


        identifier = GetAt(i)->GetTableofContents().FindChapter(book, chapter);

        if (identifier != NODE_ID_INVALID_16)
        {
            pageBuffer = THML_OPEN;
            if (!GetAt(i)->GetTableofContents().GetNode(identifier)->ReadData(GetAt(i)->m_file, pageBuffer))
                return false;

            if (GetAt(i)->GetTableofContents().GetNode(identifier)->hasChildren)
            {
                char s[12];
                sprintf(s, "\n</div%u>", GetAt(i)->GetTableofContents().GetNode(identifier)->divDepth);
                pageBuffer.Strcat(s);
            }

            pageBuffer += THML_CLOSE;

            sr.m_book = book;
            sr.m_chapter = chapter;
            sr.m_verseStart = verseStart;
            sr.m_verseEnd = verseEnd;

            SwApplicationInterface::GetRichInterface().Reset();
            SwApplicationInterface::GetRichInterface().SetIsThML(true);
            SwApplicationInterface::GetRichInterface().SetCtrl(NULL);
            SwApplicationInterface::GetRichInterface().SetCssFile(&GetAt(i)->m_cssrules);
            SwApplicationInterface::GetRichInterface().SetBasePath(GetAt(i)->m_basePath);
            SwApplicationInterface::GetRichInterface().Load(pageBuffer, pageBuffer.Strlen());
            SwApplicationInterface::GetRichInterface().Inline();
            SwApplicationInterface::GetRichInterface().Containorize(THML_SCRIPCOM, "scripCom");
            SwApplicationInterface::GetRichInterface().ProcessThMLNotes();

            if (!SwApplicationInterface::GetRichInterface().FindScriptureRange(sr, nr))
                continue;

            if (buffer.GetCount() > AUTODEF_OPEN_SZ)
            {
                buffer += ITEM_BREAK;
                buffer += "<br>";
            }

            buffer += GetAt(i)->GetFormattedAbbreviation();
            buffer += ITEM_BREAK;

            SwApplicationInterface::GetRichInterface().GetNodesData(nr, pageBuffer);
            buffer += pageBuffer;
        }
    }

    if (buffer.GetCount() > startPos)
        return true;

    return false;
}
