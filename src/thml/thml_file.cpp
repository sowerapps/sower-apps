///////////////////////////////////////////////////////////////////
// Name:        thml_file.cpp
// Purpose:     SwThMLFile, SwThMLContentsNode, &
//              SwThMLTableOfContents - classes representing the
//              contents of a thml file.
//              SwThMLFileLoader - recursive file loader.
//              SwThMLLibrarian - recursive cnts creator.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thml_file.h"
#include "../../include/thml/thml_utility.h"
#include "../../include/framework/frame.h"
#include "../../include/filesys/recurse.h"
#include "../../include/filesys/file.h"

bool SwThMLContentsNode::ReadData(FILE * f, SwString & buffer)
{
    if (!f)
        return false;

    buffer.Size(buffer.GetCount() + fileSize + 1);
    fseek(f, filePos, SEEK_SET);
    fread(buffer + buffer.GetCount(), sizeof(char), fileSize, f);

    buffer.SetAt(buffer.GetCount() + fileSize, '\0');
    buffer.IncrementCount(fileSize);

    return true;
}

SwThMLTableOfContents::SwThMLTableOfContents()
{
    m_nodeData = NULL;
    m_nodePos = 0;
    m_nodesAllocated = 0;
    m_Inc = 12;
    m_buffer = NULL;
    m_bufferSize = 0;
    m_dataSize = 0;
    m_idbuffer = NULL;
    m_idbufferSize = 0;
    m_iddataSize = 0;
}

SwThMLTableOfContents::~SwThMLTableOfContents()
{
    if (m_nodeData)
        free(m_nodeData);

    if (m_buffer)
        free(m_buffer);

    if (m_idbuffer)
        free(m_idbuffer);
}

void SwThMLTableOfContents::SetIncrement(swUI8 increment)
{
    if (increment < 25)
        m_Inc = 25;
    else
        m_Inc = increment;
}

bool SwThMLTableOfContents::SizeBuffer(swUI32 size)
{
    if (!size && m_buffer)
    {
        free(m_buffer);
        m_buffer = NULL;
        m_bufferSize = 0;
        return true;
    }

    char * p = (char *) realloc((void *) m_buffer, size * sizeof(char));

    if (p)
    {
        m_bufferSize = size;
        m_buffer = p;
        return true;
    }

    return false;
}

bool SwThMLTableOfContents::SizeIdBuffer(swUI32 size)
{
    if (!size && m_idbuffer)
    {
        free(m_idbuffer);
        m_idbuffer = NULL;
        m_idbufferSize = 0;
        return true;
    }

    char * p = (char *) realloc((void *) m_idbuffer, size * sizeof(char));

    if (p)
    {
        m_idbufferSize = size;
        m_idbuffer = p;
        return true;
    }

    return false;
}

bool SwThMLTableOfContents::IncreaseNodeArray()
{
    swUI16 increase = m_Inc;

    if (!m_Inc)
        increase = 100;

    return SizeNodeArray(m_nodesAllocated + increase);
}

bool SwThMLTableOfContents::SizeNodeArray(swUI16 nodes)
{
    if (!nodes && m_nodeData)
    {
        free(m_nodeData);
        m_nodeData = NULL;
        m_nodePos = 0;
        m_nodesAllocated = 0;
        return true;
    }

    if (nodes >= NODE_ID_INVALID_16)
        return false;

    SwThMLContentsNode * p = (SwThMLContentsNode *) realloc((void *) m_nodeData, nodes * sizeof(SwThMLContentsNode));

    if (p)
    {
        m_nodesAllocated = nodes;
        m_nodeData = p;
        return true;
    }

    return false;
}

bool SwThMLTableOfContents::VerifyNode()
{
    if (m_nodePos >= m_nodesAllocated && !IncreaseNodeArray())
        return false;

    m_nodeData[m_nodePos].divDepth = 0;
    m_nodeData[m_nodePos].bufferPos = 0;
    m_nodeData[m_nodePos].idbufferPos = 0;
    m_nodeData[m_nodePos].filePos = 0;
    m_nodeData[m_nodePos].fileSize = 0;
    m_nodeData[m_nodePos].hasChildren = false;
    m_nodeData[m_nodePos].book = 0;
    m_nodeData[m_nodePos].chapter = 0;
    return true;
}

bool SwThMLTableOfContents::VerifyNodes(swUI16 nodes)
{
    if (nodes + m_nodePos + 1 > m_nodesAllocated && !SizeNodeArray(nodes + m_nodePos + 1 + m_Inc))
        return false;

    return true;
}

swUI16 SwThMLTableOfContents::GetLastNode()
{
    return m_nodePos -1;
}

swUI16 SwThMLTableOfContents::GetNodes()
{
    return m_nodePos;
}

void SwThMLTableOfContents::Reset()
{
    ResetNodeData();
    m_nodePos = 0;
}

void SwThMLTableOfContents::ResetNodeData()
{
    // Reset parts of node data that will be modified
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        m_nodeData[pos].divDepth = 0;
        m_nodeData[pos].bufferPos = 0;
        m_nodeData[pos].idbufferPos = 0;
        m_nodeData[pos].filePos = 0;
        m_nodeData[pos].fileSize = 0;
        m_nodeData[pos].hasChildren = false;
        m_nodeData[pos].book = 0;
        m_nodeData[pos].chapter = 0;
        pos ++;
    }
}

SwThMLContentsNode * SwThMLTableOfContents::GetNode(swUI16 node)
{
    if (node >= m_nodePos)
        return NULL;

    return &m_nodeData[node];
}

const char * SwThMLTableOfContents::GetTitleText(swUI16 node)
{
    if (node >= m_nodePos)
        return "";

    return m_buffer + m_nodeData[node].bufferPos;
}

bool SwThMLTableOfContents::GetTitle(swUI16 node, SwString & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetTitleSize(node)))
        return false;

    dest.SetAt(0, '\0');

    memcpy(dest, m_buffer + m_nodeData[node].bufferPos, GetTitleSize(node));

    return true;
}

const char * SwThMLTableOfContents::GetIdText(swUI16 node)
{
    if (node >= m_nodePos)
        return "";

    return m_idbuffer + m_nodeData[node].idbufferPos;
}

bool SwThMLTableOfContents::GetId(swUI16 node, SwString & dest)
{
    if (node >= m_nodePos)
        return false;

    if (!dest.Size(GetIdSize(node)))
        return false;

    dest.SetAt(0, '\0');

    memcpy(dest, m_idbuffer + m_nodeData[node].idbufferPos, GetIdSize(node));

    return true;
}

swUI16 SwThMLTableOfContents::GetTitleSize(swUI16 node)
{
    if (node >= m_nodePos)
        return 0;

    return strlen(&m_buffer[m_nodeData[node].bufferPos]) + 1;
}

swUI16 SwThMLTableOfContents::GetIdSize(swUI16 node)
{
    if (node >= m_nodePos)
        return 0;

    return strlen(&m_idbuffer[m_nodeData[node].idbufferPos]) + 1;
}

swUI8 SwThMLTableOfContents::GetDivDepth(swUI16 node)
{
    if (node >= m_nodePos)
        return NODE_ID_INVALID_8;

    return m_nodeData[node].divDepth;
}

bool SwThMLTableOfContents::SetDivDepth(swUI16 node, swUI8 divDepth)
{
    if (node >= m_nodePos)
        return false;

    m_nodeData[node].divDepth = divDepth;

    return true;
}

bool SwThMLTableOfContents::BufferAppend(const char * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_dataSize + size >= 0xFFFFFFF)
        return false;

    if (m_bufferSize <= m_dataSize + size && !SizeBuffer(m_dataSize + size))
        return false;

    memcpy(m_buffer+m_dataSize, data, size);

    return true;
}

bool SwThMLTableOfContents::IdBufferAppend(const char * data, swUI16 size)
{
    if (!data || !size)
        return false;

    if (m_iddataSize + size >= 0xFFFFFFF)
        return false;

    if (m_idbufferSize <= m_iddataSize + size && !SizeIdBuffer(m_iddataSize + size))
        return false;

    memcpy(m_idbuffer+m_iddataSize, data, size);

    return true;
}

swUI16 SwThMLTableOfContents::Append(const char * title, const char * id, swUI8 divDepth, swUI32 pos, swUI32 length, swUI8 book, swUI8 chapter)
{
    if (!title || !id || !VerifyNode())
        return NODE_ID_INVALID_16;

    swUI16 size = strlen(title) + 1;
    swUI16 idsize = strlen(id) + 1;

    bool status = BufferAppend(title, size);

    if (!status)
        return NODE_ID_INVALID_16;

    status = IdBufferAppend(id, idsize);

    if (!status)
        return NODE_ID_INVALID_16;

    m_nodeData[m_nodePos].bufferPos = m_dataSize;
    m_nodeData[m_nodePos].idbufferPos = m_iddataSize;
    m_nodeData[m_nodePos].divDepth = divDepth;
    m_nodeData[m_nodePos].filePos = pos;
    m_nodeData[m_nodePos].fileSize = length;
    m_nodeData[m_nodePos].book = book;
    m_nodeData[m_nodePos].chapter = chapter;

    m_dataSize += size;
    m_iddataSize += idsize;
    m_nodePos ++;

    return m_nodePos - 1;
}

swUI16 SwThMLTableOfContents::FindItem(const char * title)
{
    swUI16 pos = 0;

    if (!title)
        return NODE_ID_INVALID_16;

    while (pos < m_nodePos)
    {
        if (strcmp(title, &m_buffer[m_nodeData[pos].bufferPos]) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwThMLTableOfContents::FindByID(const char * id)
{
    swUI16 pos = 0;

    if (!id)
        return NODE_ID_INVALID_16;

    while (pos < m_nodePos)
    {
        if (strcmp(id, &m_idbuffer[m_nodeData[pos].idbufferPos]) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwThMLTableOfContents::FindChapter(swUI8 book, swUI8 chapter)
{
    swUI16 pos = 0;

    while (pos < m_nodePos)
    {
        if (m_nodeData[pos].book == book && m_nodeData[pos].chapter == chapter)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

void SwThMLTableOfContents::SetHasChildren()
{
    for (swUI16 i = 0; i < m_nodePos; i ++)
    {
        if (i + 1 == m_nodePos)
        {
            m_nodeData[i].hasChildren = false;
        }
        else
        {
            if (m_nodeData[i + 1].divDepth > m_nodeData[i].divDepth)
                m_nodeData[i].hasChildren = true;
        }
    }
}

bool SwThMLTableOfContents::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    if (fwrite((void *) &m_dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_iddataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fwrite((void *) &m_nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (m_buffer && fwrite((void *) m_buffer, sizeof(char), m_dataSize, file) != m_dataSize)
        return false;
    if (m_idbuffer && fwrite((void *) m_idbuffer, sizeof(char), m_iddataSize, file) != m_iddataSize)
        return false;
    if (m_nodeData && fwrite((void *) m_nodeData, sizeof(SwThMLContentsNode), m_nodePos, file) != m_nodePos)
        return false;

    return true;
}

bool SwThMLTableOfContents::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI32 dataSize = 0;
    swUI32 iddataSize = 0;
    swUI16 nodePos = 0;

    if (fread((void *) &dataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fread((void *) &iddataSize, sizeof(swUI32), 1, file) != 1)
        return false;
    if (fread((void *) &nodePos, sizeof(swUI16), 1, file) != 1)
        return false;
    if (!SizeBuffer(dataSize) || !SizeIdBuffer(iddataSize) || !SizeNodeArray(nodePos))
        return false;
    if (dataSize && fread((void *) m_buffer, sizeof(char), dataSize, file) != dataSize)
        return false;
    if (iddataSize && fread((void *) m_idbuffer, sizeof(char), iddataSize, file) != iddataSize)
        return false;
    if (nodePos && fread((void *) m_nodeData, sizeof(SwThMLContentsNode), nodePos, file) != nodePos)
        return false;

    m_nodePos = nodePos;
    m_dataSize = dataSize;
    m_iddataSize = iddataSize;

    return true;
}

void SwThMLFile::Reset()
{
    if (m_file)
    {
        fclose(m_file);
        m_file = NULL;
    }

    m_title.Reset();
    m_identifier.Reset();
    m_abbrev.Reset();
    m_contents.Reset();
    m_category = CATEGORY_GENERAL;
    m_autodefEnabled = true;
}

bool SwThMLFile::Open(const char * path)
{
    Reset();
    bool hasToc = false;
    SwString data, tocpath;
    data.Size(8192);
    FILE * toc = NULL;

    tocpath = path;
    tocpath += ".cnts";

    if (SwFile::CompareModifiedDates(path, tocpath) == 2)
    {
        toc = SwFopen(tocpath, FMD_R);
        if (toc)
        {
            hasToc = ReadFromFile(toc);

            if (toc)
                fclose(toc);
        }
    }

    if (!hasToc)
    {
        SwThMLUtility::GetDublinCore(data, path);
        m_category = SwCategory::IdentifyCategory(data);

        if (!SwThMLUtility::GetIdentifier(m_identifier, path))
        {
            m_identifier = "0000000";
        }

        if (!SwThMLUtility::GetTitle(m_title, path))
        {
            m_title = "Unknown";
            m_abbrev = "UKN";
        }
        else
            SetAbbreviation();
    }

    m_file = SwFopen(path, FMD_R);

    if (!m_file)
    {
        return false;
    }

    if (SwThMLUtility::ReadCss(data, data.GetSize(), m_file))
    {
        m_cssrules.ParseCss(data, data.Strlen());
    }

    m_path = path;
    m_basePath = path;
    SwClipFileName(m_basePath);

    if (!hasToc && ReadTree())
    {
        m_contents.SetHasChildren();
        toc = SwFopen(tocpath, FMD_WC);
        if (toc)
        {
            WriteToFile(toc);
            fclose(toc);
        }
    }

    return true;
}

const char * SwThMLFile::GetFormattedId()
{
    static SwString formatBuffer;
    char s[] = "<module id=\"%u\" ismodule=\"0\"/>";
    formatBuffer.Size(strlen(s) + 31);
    sprintf(formatBuffer, s, m_managerId);

    return formatBuffer;
}

const char * SwThMLFile::GetFormattedAbbreviation()
{
    static SwString formatBuffer;
    char s[] = "<module id=\"%u\" ismodule=\"0\">%s</module>";
    formatBuffer.Size(strlen(s) + m_abbrev.Strlen() + 31);
    sprintf(formatBuffer, s, m_managerId, m_abbrev.GetArray());

    return formatBuffer;
}

void SwThMLFile::SetAbbreviation()
{
    bool spaced = true;
    SwStringW buffer, abb;
    buffer.Copy(m_title);

    for (swUI32 i = 0; i < buffer.Strlen(); i ++)
    {
        if (!spaced && buffer.GetAt(i) == L' ')
        {
            spaced = true;
            continue;
        }

        if (spaced && buffer.GetAt(i) != L'(' && buffer.GetAt(i) != L')')
        {
            abb += buffer.GetAt(i);
            spaced = false;
        }
    }

    abb.ToUpper();
    m_abbrev.Copy(abb);
}

bool SwThMLFile::ReadTree()
{
    char * p;
    SwString title, passage, id, buffer;
    char title2[1024];
    swUI8 divDepth = 0;
    swUI32 pos = 0;
    swUI32 divpos = 0;
    swUI32 length = 0;
    swUI8 lastChar;
    swUI8 book = 0;
    swUI8 chapter = 0;
    swUI8 verseStart = 0;
    swUI8 verseEnd = 0;
    bool hasId = false;

    if (!m_file)
        return false;

    buffer.Size(8192);

    fseek(m_file, 0, SEEK_SET);

    bool treeData = false;
    while (fgets(buffer, buffer.GetSize(), m_file))
    {
        if (m_category == CATEGORY_BIBLECOMMENTARY && !hasId)
        {
            p = strstr(buffer, "scripCom");
            if (p && SwThMLParser::GetNamedValue("passage", p, passage))
            {
                hasId = SwThMLUtility::ParsePassageId(passage, book, chapter, verseStart, verseEnd);
            }
        }

        p = strstr(buffer, "<div");

        if (p && isdigit(p[4]))
        {
            hasId = false;
            // Divn+1 within Divn has caused Divn
            // to end before </Divn>.
            // Title and depth should be accurate for
            // this item.
            if (treeData)
            {
                length = pos - divpos;

                if (m_contents.Append(title2, id, divDepth, divpos, length, book, chapter) == NODE_ID_INVALID_16)
                    return false;

                treeData = false;
            }

            // Division level
            divDepth = (swUI8) strtoul(p + 4, NULL, 10);
            // Title
            SwThMLParser::GetNamedValue("title", p, title);
            lastChar = LCH_BREAK;
            SwHtml::Html2Text(title, title2, 1024, lastChar, true);
            id.Reset();
            SwThMLParser::GetNamedValue("id", p, id);
            SwThMLUtility::ParseScriptureId(id, book, chapter, verseStart, verseEnd);
            divpos = pos;
            treeData = true;
        }
        else
        {
            p = strstr(buffer, "</div");

            if (p && isdigit(p[5]) && treeData)
            {
                length = ftell(m_file) - divpos;

                if (m_contents.Append(title2, id, divDepth, divpos, length, book, chapter) == NODE_ID_INVALID_16)
                    return false;

                treeData = false;
            }
        }

        pos = ftell(m_file);
    }

    return true;
}

bool SwThMLFile::ReadInfoData(SwString buffer)
{
    if (!m_file)
        return false;

    fseek(m_file, m_infoPos, SEEK_SET);

    buffer.Size(m_infoSize + 1);

    if (fread((void *) buffer, 1, m_infoSize, m_file) != m_infoSize)
        return false;

    buffer.SetAt(m_infoSize, '\0');

    return true;
}

bool SwThMLFile::WriteToFile(FILE * file)
{
    if (!file)
        return false;

    swUI16 size;

    size = strlen(m_title) + 1;

    if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (fwrite(m_title, sizeof(char), size, file) != size)
        return false;

    size = strlen(m_identifier) + 1;

    if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (fwrite(m_identifier, sizeof(char), size, file) != size)
        return false;

    size = strlen(m_abbrev) + 1;

    if (fwrite((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (fwrite(m_abbrev, sizeof(char), size, file) != size)
        return false;

    if (fwrite((void *) &m_infoPos, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_infoSize, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fwrite((void *) &m_category, sizeof(swUI8), 1, file) != 1)
        return false;

    return m_contents.WriteToFile(file);
}

bool SwThMLFile::ReadFromFile(FILE * file)
{
    if (!file)
        return false;

    swUI16 size;

    if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (size)
    {
        m_title.Size(size);
        if (fread(m_title, sizeof(char), size, file) != size)
            return false;
    }

    if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (size)
    {
        m_identifier.Size(size);
        if (fread(m_identifier, sizeof(char), size, file) != size)
            return false;
    }

    if (fread((void *) &size, sizeof(swUI16), 1, file) != 1)
        return false;

    if (size)
    {
        m_abbrev.Size(size);
        if (fread(m_abbrev, sizeof(char), size, file) != size)
            return false;
    }

     if (fread((void *) &m_infoPos, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fread((void *) &m_infoSize, sizeof(swUI32), 1, file) != 1)
        return false;

    if (fread((void *) &m_category, sizeof(swUI8), 1, file) != 1)
        return false;

    return m_contents.ReadFromFile(file);
}

bool SwThMLFile::GetAutodefEnabled()
{
    return m_autodefEnabled;
}

void SwThMLFile::SetAutodefEnabled(bool enabled)
{
    m_autodefEnabled = enabled;
}

SwThMLFileLoader::SwThMLFileLoader()
{
}

SwThMLFileLoader::~SwThMLFileLoader()
{
}

bool SwThMLFileLoader::OnFile(const char * path)
{
    wxFileName fname(path);

    if (fname.GetExt().CmpNoCase("thm") == 0 || fname.GetExt().CmpNoCase("thml") == 0)
    {
        SwThMLFile * thmlfile = new SwThMLFile();

        if (!thmlfile->Open(path))
            delete thmlfile;
        else
            SwApplicationInterface::GetThMLFileManager().Add(thmlfile);
    }

    return true;
}

void SwThMLFileLoader::OnProcessEnd()
{
    if (SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnThMLFileManagerLoaded();
}

swUI16 SwThMLFileLoader::LoadFile(const char * path)
{
    if (!path)
        return NODE_ID_INVALID_16;

    wxFileName fname(path);
    SwThMLFile * thmlfile;

    if (fname.GetExt().CmpNoCase("thm") == 0 || fname.GetExt().CmpNoCase("thml") == 0)
    {
        thmlfile = new SwThMLFile();

        if (!thmlfile->Open(path))
        {
            delete thmlfile;
            return NODE_ID_INVALID_16;
        }
    }
    else
        return NODE_ID_INVALID_16;

    return SwApplicationInterface::GetThMLFileManager().Add(thmlfile);
}

SwThMLLibrarian::SwThMLLibrarian()
{
}

SwThMLLibrarian::~SwThMLLibrarian()
{
}

bool SwThMLLibrarian::OnFile(const char * path)
{
    wxFileName fname(path);

    if (fname.GetExt().CmpNoCase("thm") == 0 || fname.GetExt().CmpNoCase("thml") == 0)
    {
        SwThMLFile * thmlfile = new SwThMLFile();

        thmlfile->Open(path);
        delete thmlfile;
    }

    return true;
}
