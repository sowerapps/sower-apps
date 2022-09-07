///////////////////////////////////////////////////////////////////
// Name:        thmlmodulewriter.cpp
// Purpose:     Write modules from ThML files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/thmlmodulewriter.h"
#include "../../include/thml/thml_utility.h"
#include "../../include/filesys/streambuffer.h"
#include "../../include/filesys/file.h"
#include "../../include/module/transcryptor.h"

SwThMLModuleWriter::SwThMLModuleWriter()
{
    SetThML_ElementArray();
}

SwThMLModuleWriter::~SwThMLModuleWriter()
{
}

bool SwThMLModuleWriter::OpenFile(const char * path, bool thml)
{
    Reset();
    bool status = SwModuleWriter::OpenFile(path, thml);

    return status;
}

bool SwThMLModuleWriter::CreateItemData()
{
    swUI32 nodeMate, currentDiv = NODE_ID_INVALID;
    swUI16 id = NODE_ID_INVALID_16;
    swUI8 book, chapter, verseStart, verseEnd;
    SwString buffer, titleBuffer, idbuffer, original;
    bool identifyState;

    SetRange(m_parserNodePos);
    swUI8 lastChar;

    if (!CheckParserIntegrity())
        wxMessageBox("Parser integrity failed.");

    for (swUI32 i = 0; i < m_parserNodePos; i++)
    {
        UpdateUI(i);
        if (GetNodeElementIdentifier(i) == THML_SCRIPTURE && GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG)
        {
            GetNodeData(i, buffer);
            OnError(GetNodeElementIdentifier(i), GetNodeType(i), buffer, EC_UNCONTAINED_SCRIPTURE);
            m_errors ++;
        }

        if (GetNodeElementIdentifier(i) == THML_SCRIPCOM && GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG)
        {
            GetNodeData(i, buffer);
            OnError(GetNodeElementIdentifier(i), GetNodeType(i), buffer, EC_UNCONTAINED_COMMENTARY);
            m_errors ++;
        }

        if (GetNodeElementIdentifier(i) == INT_TEXT_RUN && GetNodeParent(i) == currentDiv && currentDiv != NODE_ID_INVALID)
        {
            GetNodeData(i, buffer);
            OnError(GetNodeElementIdentifier(i), GetNodeType(i), buffer, EC_UNCONTAINED_TEXT_RUN);
            m_errors ++;
        }

        if (GetNodeElementIdentifier(i) == INT_TEXT_RUN)
        {
            CheckTextRun(i);
        }

        if (GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG || GetNodeType(i) == NODE_TYPE_END_TAG || GetNodeType(i) == NODE_TYPE_TEXT_RUN)
            continue;

        switch (GetNodeElementIdentifier(i))
        {
        case THML_STYLE :
            i = GetNodeMate(i);
            continue;
            break;
        case THML_THML :
        case THML_THML_BODY:
            continue;
            break;
        case THML_ELECTRONICEDINFO:
            nodeMate = GetNodeMate(i);

            if (nodeMate == NODE_ID_INVALID)
                continue;

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;

            i = nodeMate;
            m_header.infoItem = m_swmoduleitemarray.GetCount();
            m_swmoduleitemarray.IncrementCount();
            break;

        case INT_BINARY:
            if (GetNamedValueFromNode(i, "name", buffer))
            {
                m_media.AppendNode(buffer.GetArray(), m_swmoduleitemarray.GetCount());
            }

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i+1)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodeDataSize(i+1);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = GetMediaType(i);
            m_swmoduleitemarray.IncrementCount();
            i += 2;
            break;

        case THML_NOTE:
            nodeMate = GetNodeMate(i);

            if (nodeMate == NODE_ID_INVALID)
                continue;

            if (GetNamedValueFromNode(i, "n", buffer))
            {
                m_notes.AppendNode(buffer.GetArray(), m_swmoduleitemarray.GetCount());
            }

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;

            i = nodeMate;
            m_swmoduleitemarray.IncrementCount();
            break;

        case THML_DIV1:
        case THML_DIV2:
        case THML_DIV3:
        case THML_DIV4:
        case THML_DIV5:
        case THML_DIV6:
            if (GetNamedValueFromNode(i, "title", buffer))
            {
                lastChar = LCH_BREAK;
                titleBuffer.Size(buffer.Strlen() + 1);
                SwHtml::Html2Text(buffer, titleBuffer, titleBuffer.GetSize(), lastChar, true);

                if (!GetNamedValueFromNode(i, "id", idbuffer))
                {
                    idbuffer.SetAt(0, '\0');
                }

                id = m_contents.Append(titleBuffer.GetArray(), m_swmoduleitemarray.GetCount(), idbuffer);

                if (id != NODE_ID_INVALID_16)
                {
                    m_contents.SetDivDepth(id, 1 + GetNodeElementIdentifier(i) - THML_DIV1);
                    m_contents.SetHasChildren(id, DoesThMLDivHaveChildDiv(i));
                    m_contents.SetContentType(id, GetContentType(i));
                }
            }

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = DoesThMLDivHaveChildDiv(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;

            if (!m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren)
               m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, GetNodeMate(i));
            else
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, GetThMLDivBreakNode(i));
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = GetContentType(i);

            m_swmoduleitemarray.IncrementCount();
            currentDiv = i;
            break;

        case THML_SCRIPCOM:
            identifyState = false;

            nodeMate = GetNodeMate(i);

            if (nodeMate == NODE_ID_INVALID)
                continue;

            book = chapter = verseStart = verseEnd = 0;

            if (GetNamedValueFromNode(i, "passage", buffer))
            {
                if (!SwThMLUtility::ParsePassageId(buffer, book, chapter, verseStart, verseEnd))
                {
                    OnError(GetNodeElementIdentifier(i), GetNodeType(i), buffer, EC_UNABLE_TO_IDENTIFY_PASSAGE);
                    m_errors ++;
                }
                else
                    identifyState = true;
            }
            else if (!identifyState && GetNamedValueFromNode(i, "osisRef", buffer))
            {
                OsisRef osref;
                osref.Parse(buffer);

                if (osref.m_end.m_book &&
                        (osref.m_start.m_book != osref.m_end.m_book ||
                         osref.m_start.m_chapter != osref.m_end.m_chapter))
                {
                    GetNodeData(i, buffer);
                    OnError(GetNodeElementIdentifier(i), GetNodeType(i), buffer, EC_COMMENTARY_SPAN_CHAPTER);
                    m_errors ++;
                    continue;
                }

                book = osref.m_start.m_book;
                chapter = osref.m_start.m_chapter;
                verseStart = osref.m_start.m_verse;
                verseEnd = osref.m_end.m_verse;
            }

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->book = book;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->chapter = chapter;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseStart = verseStart;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseEnd = verseEnd;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;
            m_commentaryMap.AddCommentaryData(
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->book,
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->chapter,
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseStart,
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseEnd,
                m_swmoduleitemarray.GetCount());

            i = nodeMate;
            m_swmoduleitemarray.IncrementCount();
            continue;
            break;

        case THML_SCRIPTURE:
            identifyState = false;
            nodeMate = GetNodeMate(i);

            if (nodeMate == NODE_ID_INVALID)
                continue;
            book = chapter = verseStart = verseEnd = 0;

            if (GetNamedValueFromNode(i, "id", buffer))
            {
                original = buffer;
                buffer.Replace(" ", 1, "", 0);
                if (!SwThMLUtility::ParseScriptureId(buffer, book, chapter, verseStart, verseEnd))
                {
                    OnError(GetNodeElementIdentifier(i), GetNodeType(i), original, EC_UNABLE_TO_IDENTIFY_ID);
                    m_errors ++;
                }
                else
                    identifyState = true;
            }
            else if (!identifyState && GetNamedValueFromNode(i, "passage", buffer))
            {
                if (!SwThMLUtility::ParsePassageId(buffer, book, chapter, verseStart, verseEnd))
                {
                    OnError(GetNodeElementIdentifier(i), GetNodeType(i), buffer, EC_UNABLE_TO_IDENTIFY_PASSAGE);
                    m_errors ++;
                }
                else
                    identifyState = true;
            }
            else if (!identifyState && GetNamedValueFromNode(i, "osisID", buffer))
            {
                SwOsisId osid;
                osid.Parse(buffer);
                book = osid.m_book;
                chapter = osid.m_chapter;
                verseStart = osid.m_verse;
                verseEnd = 0;
            }

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->book = book;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->chapter = chapter;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseStart = verseStart;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseEnd = verseEnd;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;
            m_scriptureMap.AddVerseData(
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->book,
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->chapter,
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->verseStart,
                m_swmoduleitemarray.GetCount()
            );

            i = nodeMate;
            m_swmoduleitemarray.IncrementCount();
            break;

        case THML_TERM:
            nodeMate = FindElement(i, THML_DEF, NODE_TYPE_END_TAG);

            if (nodeMate == NODE_ID_INVALID)
                continue;

            GetInnerText(i, buffer);
            m_term.AddNode(buffer.GetArray(), m_swmoduleitemarray.GetCount(), false);

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = THML_TERM;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;

            i = nodeMate;
            m_swmoduleitemarray.IncrementCount();
            continue;
            break;

        case THML_TERM_STRONGS:
            nodeMate = FindElement(i, THML_DEF, NODE_TYPE_END_TAG);

            if (nodeMate == NODE_ID_INVALID)
                continue;

            if (!GetNamedValueFromNode(i, "value", buffer))
                continue;

            if (buffer.GetAt(0) == 'G' || buffer.GetAt(0) == 'g')
            {
                m_strongsG.AddNode(buffer.GetArray() + 1, m_swmoduleitemarray.GetCount());
            }
            else if (buffer.GetAt(0) == 'H' || buffer.GetAt(0) == 'h')
            {
                m_strongsG.AddNode(buffer.GetArray() + 1, m_swmoduleitemarray.GetCount());
            }

            if (GetNamedValueFromNode(i, "translit", buffer))
            {
                m_term.AddNode(buffer.GetArray(), m_swmoduleitemarray.GetCount(), false);
            }

            if (GetNamedValueFromNode(i, "origin", buffer))
            {
                m_term.AddNode(buffer.GetArray(), m_swmoduleitemarray.GetCount(), false);
            }

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = THML_TERM_STRONGS;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;

            i = nodeMate;
            m_swmoduleitemarray.IncrementCount();
            continue;
            break;

        default :
            if (GetElementType(i) == ELEMENT_TYPE_INLINE)
                continue;

            nodeMate = GetNodeMate(i);

            if (nodeMate == NODE_ID_INVALID)
                continue;

            if (GetNodeParent(i) != currentDiv)
                continue;

            if (m_swmoduleitemarray.GetSize() <= m_swmoduleitemarray.GetCount() + 10 &&
                !m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1000))
                return 0;

            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = GetNode(i)->beginPos;
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = GetNodesDataSize(i, nodeMate);
            m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = 0;

            m_swmoduleitemarray.IncrementCount();
            break;
        }
    }

    m_scriptureMap.MapVerseData();
    m_commentaryMap.MapCommentaryData();
    CheckItemData(1);
    AdjustSizes();
    CheckItemData(2);
    return m_swmoduleitemarray.GetCount();
}

swUI32 SwThMLModuleWriter::FindBreakItem(swUI32 node)
{
    return GetThMLDivBreakNode(node);
}

void SwThMLModuleWriter::AdjustSizes()
{
    for (swUI32 i = 0; i < m_swmoduleitemarray.GetCount(); i ++)
    {
        switch (m_swmoduleitemarray.Get(i)->type)
        {
        case THML_ELECTRONICEDINFO:
        case INT_BINARY:
        case THML_NOTE:
        case THML_DIV1:
        case THML_DIV2:
        case THML_DIV3:
        case THML_DIV4:
        case THML_DIV5:
        case THML_DIV6:
        case THML_SCRIPCOM:
        case THML_SCRIPTURE:
        case THML_TERM:
        case THML_TERM_STRONGS:
            continue;
            break;
        default :
            if (i < m_swmoduleitemarray.GetCount() - 2)
            {
                m_swmoduleitemarray.Get(i)->size = m_swmoduleitemarray.Get(i+1)->position - m_swmoduleitemarray.Get(i)->position;
            }
            break;
        }
    }
}

bool SwThMLModuleWriter::WriteMedia(FILE * f)
{
    SwString src, path, fileName;
    SwStreamBuffer media;
    long filePos;

    for (swUI32 i = 0; i < m_parserNodePos; i++)
    {
        if ((GetNodeType(i) == NODE_TYPE_BEGIN_TAG ||
                GetNodeType(i) == NODE_TYPE_UNPAIRED_TAG) &&
                ((GetNodeElementIdentifier(i) == THML_IMG ||
                  GetNodeElementIdentifier(i) == THML_IMAGE ||
                  GetNodeElementIdentifier(i) == THML_PB ||
                  GetNodeElementIdentifier(i) == THML_SOURCE ||
                  GetNodeElementIdentifier(i) == THML_INTERFACE)))
        {
            if (!GetNamedValueFromNode(i, "src", src) &&
                !GetNamedValueFromNode(i, "href", src))
                continue;

            SwGetPathFromRelative(GetBasePath(), src, path);
            swUI32 size = SwFile::GetSize(path);

            if (size == 0)
            {
                OnError(GetNodeElementIdentifier(i), GetNodeType(i), path, EC_UNABLE_TO_LOCATE_EXTERNAL_FILE);
                m_errors ++;
            }

            if (media.Load(path))
            {
                filePos = ftell(f);

                if (m_header.isEncrypted)
                    SwTranscryptor::encryptfwrite(media, 1, size, f, m_k1, m_k2);
                else
                    fwrite(media, 1, size, f);

                SwGetFileName(path, fileName);
                m_media.AppendNode(fileName, m_swmoduleitemarray.GetCount(), GetMediaType(i));

                if (!m_swmoduleitemarray.Size(m_swmoduleitemarray.GetCount() + 1))
                    return 0;

                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->Reset();
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->type = GetNodeElementIdentifier(i);
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->divItems = 1;
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->hasChildren = false;
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->position = filePos;
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->size = size;
                m_swmoduleitemarray.Get(m_swmoduleitemarray.GetCount())->contentType = GetMediaType(i);
                m_swmoduleitemarray.IncrementCount();
            }
            else
            {
                OnError(GetNodeElementIdentifier(i), GetNodeType(i), path, EC_UNABLE_TO_LOAD_EXTERNAL_FILE);
                m_errors ++;
            }

        }
    }

    return true;
}

swUI8 SwThMLModuleWriter::GetMediaType(swUI32 node)
{
    SwString data;
    if (GetNodeElementIdentifier(node) == THML_IMG ||
            GetNodeElementIdentifier(node) == THML_IMAGE ||
            GetNodeElementIdentifier(node) == THML_PB)
        return SW_MEDIA_TYPE_IMAGE;

    // If element is 'interface' type will be
    // SW_MEDIA_TYPE_INTERFACE + MODULE_INTERFACE_TYPE_?.
    if (GetNodeElementIdentifier(node) == THML_INTERFACE)
    {
        if (!GetNamedValueFromNode(node, "type", data))
            return SW_MEDIA_TYPE_UNKNOWN;

        return atoi(data) + SW_MEDIA_TYPE_INTERFACE;
    }

    swUI32 nodeParent = GetNodeParent(node);

    if (nodeParent == NODE_ID_INVALID)
        return SW_MEDIA_TYPE_UNKNOWN;

    if (GetNodeElementIdentifier(nodeParent) == THML_AUDIO)
        return SW_MEDIA_TYPE_AUDIO;

    if (GetNodeElementIdentifier(nodeParent) == THML_VIDEO)
        return SW_MEDIA_TYPE_VIDEO;

    return SW_MEDIA_TYPE_UNKNOWN;
}

void SwThMLModuleWriter::CheckItemData(swUI8 pass)
{
    swUI32 position = 0;
    swUI32 node;
    SwString buffer;
    char s[100];

    for (swUI32 i = 0; i < m_swmoduleitemarray.GetCount(); i ++)
    {
        if (m_swmoduleitemarray.Get(i)->position < position)
        {
            sprintf(s, "Error at %u on pass %u.", i, pass);
            OnError(m_swmoduleitemarray.Get(i)->type, 0, s, EC_CORRUPT_ITEM_DATA);
            m_errors ++;
            node = FindNodeByStreamPos(m_swmoduleitemarray.Get(i)->position);
            if (node != NODE_ID_INVALID)
            {
                GetNodeData(node, buffer);
                OnError(m_swmoduleitemarray.Get(i)->type, 0, buffer, EC_CORRUPT_ITEM_DATA);
                m_errors ++;
            }
        }

        position = m_swmoduleitemarray.Get(i)->position;
    }
}

void SwThMLModuleWriter::CheckTextRun(swUI32 node)
{
    SwString buffer, entity;
    GetNodeData(node, buffer);

    swUI32 len = buffer.Strlen();

    for (swUI32 i = 0; i < len; i ++)
    {
        if (buffer.GetAt(i) == '#')
        {
            if ((i == 0 || buffer.GetAt(i - 1) != '&') && isdigit(buffer.GetArray()[i + 1]))
            {
                for (swUI32 n = i + 1; n < len; n ++)
                {
                    if (isdigit(buffer.GetArray()[n]))
                    {
                        continue;
                    }
                    else if (buffer.GetArray()[n] == ';')
                    {
                        buffer.GetTextRange(i, n, entity);
                        m_warnings ++;
                        OnError(m_swmoduleitemarray.Get(i)->type, 0, entity, EC_POSSIBLE_ENTITY_ENCODING_ERROR);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }
}
