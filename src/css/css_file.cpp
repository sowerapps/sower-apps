///////////////////////////////////////////////////////////////////
// Name:        css_file.cpp
// Purpose:     Load, and parse CSS from external files, memory,
//              or add rules with Add().
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/css/css_file.h"
#include "../../include/filesys/file.h"
#include "../../include/string/string.h"

CssFile::CssFile()
{
    m_array = NULL;
    m_arrayPos = 0;
    m_objectsAllocated = 0;
}

CssFile::~CssFile()
{
    ReleaseArray();
}

void CssFile::Reset()
{
    m_fileLoaded = false;

    swUI32 pos = 0;

    if (!m_array)
        return;

    while(pos < m_arrayPos)
    {
        if (m_array[pos].selector)
        {
            delete m_array[pos].selector;
            m_array[pos].selector = NULL;
        }

        if (m_array[pos].style)
        {
            delete m_array[pos].style;
            m_array[pos].style = NULL;
        }

        pos ++;
    }

    m_arrayPos = 0;
}

bool CssFile::OpenFile(const char * path)
{
    Reset();

    if (!path)
        return false;

    if (!SwFile::DoesExist(path))
        return false;

    SwString buffer;

    swUI32 size = SwFile::GetSize(path);
    buffer.Size(size);

    FILE * file = SwFopen(path, FMD_R);

    if (!file)
        return false;


    if (fread((void *) buffer, 1, size, file) != (unsigned) size)
    {
        fclose(file);
        return false;
    }

    fclose(file);

    buffer.GetArray()[size] = '\0';
    m_fileLoaded = ParseCss(buffer, size);

    return m_fileLoaded;
}

swUI32 CssFile::AssignObject()
{
    if (m_arrayPos >= m_objectsAllocated && !IncreaseArray())
        return NODE_ID_INVALID;

    m_array[m_arrayPos].selector = NULL;
    m_array[m_arrayPos].style = NULL;

    m_arrayPos ++;

    return m_arrayPos - 1;
}

bool CssFile::IncreaseArray()
{
    if (m_objectsAllocated >= NODE_ID_INVALID - 17)
        return false;

    SwCssListNode * p = (SwCssListNode *) realloc((void *) m_array, (m_objectsAllocated + 16) * sizeof(SwCssListNode));

    if (p)
    {
        m_objectsAllocated += 16;
        m_array = p;

        return true;
    }

    return false;
}

void CssFile::ReleaseArray()
{
    if (m_array)
    {
        Reset();
        free(m_array);
    }

    m_array = NULL;
    m_objectsAllocated = 0;
    m_arrayPos = 0;
}

swUI32 CssFile::Add(const char * selector, const char * style)
{
    if (!selector || !style)
        return NODE_ID_INVALID;

    swUI32 pos = AssignObject();

    if (pos == NODE_ID_INVALID)
        return NODE_ID_INVALID;

    m_array[pos].selector = new CssSelector;
    m_array[pos].style = new SwString;

    m_array[pos].selector->ParseSelector(selector);
    m_array[pos].style->Copy(style);

    return pos;
}

void CssFile::Delete(swUI32 pos)
{
    if (pos >= m_arrayPos)
        return;

    if (m_array[pos].selector)
    {
        delete m_array[pos].selector;
        m_array[pos].selector = NULL;
    }

    if (m_array[pos].style)
    {
        delete m_array[pos].style;
        m_array[pos].style = NULL;
    }

    if (m_arrayPos >= 1)
    {
        pos ++;

        while (pos < m_arrayPos)
        {
            m_array[pos -1].selector = m_array[pos].selector;
            m_array[pos -1].style = m_array[pos].style;
            pos ++;
        }
    }

    m_arrayPos --;
}

SwCssListNode * CssFile::GetNode(swUI32 pos)
{
    if (pos >= m_arrayPos)
        return NULL;

    return &m_array[pos];
}

bool CssFile::ReadStyleData(SwThMLParser * thmlParser)
{
    if (!thmlParser)
        return false;

    SwString type;
    swUI32 node = 0;

    if (thmlParser->GetMarkupType() == MARKUP_HTML || thmlParser->GetMarkupType() == MARKUP_THML)
        node = thmlParser->FindElement(0, THML_STYLE, NODE_TYPE_BEGIN_TAG);

    if (node == NODE_ID_INVALID)
        return false;

    if (!thmlParser->GetNamedValueFromNode(node, "type", type))
        return false;

    if (stricmp(type, "text/css") == 0)
    {
        return ReadCSS(thmlParser, node);
    }

    return false;
}

bool CssFile::ReadCSS(SwThMLParser * thmlParser, swUI32 startNode)
{
    if (!thmlParser)
        return false;

    SwString buffer;

    swUI32 nodeText = thmlParser->FindWithInElement(startNode, 0, INT_TEXT_RUN, NODE_TYPE_TEXT_RUN);

    if (nodeText == NODE_ID_INVALID)
        return false;

    swUI32 dataSize = thmlParser->GetNodeDataSize(nodeText);

    if (!thmlParser->GetNodeData(nodeText, buffer))
        return false;

    return ParseCss(buffer, dataSize);
}

bool CssFile::ParseCss(const char * css, swUI32 dataSize)
{
    if (!css)
        return false;

    SwString composite, selector, style;
    composite.Size(dataSize + 1);
    selector.Size(dataSize + 1);
    style.Size(dataSize + 1);


    for(swUI32 i = 0; i < dataSize; i ++)
    {
        composite.Reset();

        while (css[i] != '}' && css[i] != '\0')
        {
            composite += css[i];
            i ++;
        }

        composite += '}';

        if (CssAttributes::GetSelector(composite, selector)&&
            CssAttributes::GetStyleData(composite, style))
            {
                Add(selector, style);
            }

    }

    return true;
}

swUI32 CssFile::FindClass(const char * className, swUI32 start)
{
    if (!className)
        return NODE_ID_INVALID;

    swUI32 idx = start;

    while (idx < m_arrayPos)
    {
        if (m_array[idx].selector->HasClass(className))
            return idx;

        idx ++;
    }

    return NODE_ID_INVALID;
}

swUI32 CssFile::FindElement(const char * element, swUI32 start)
{
    if (!element)
        return NODE_ID_INVALID;

    for (swUI32 i = start; i < m_arrayPos; i ++)
    {
       if (m_array[i].selector->HasElement(element))
            return i;
    }

    return NODE_ID_INVALID;
}

swUI32 CssFile::Find(const char * element, const char * className, swUI32 start)
{
    if (!element || !className)
        return NODE_ID_INVALID;

    if (className[0] == '\0')
    {
        for (swUI32 i = start; i < m_arrayPos; i ++)
        {
            if (m_array[i].selector->HasElement(element) && m_array[i].selector->GetClassCount() == 0)
                return i;
        }
    }
    else if (element[0] != '\0')
    {
        for (swUI32 i = start; i < m_arrayPos; i ++)
        {
            if ((m_array[i].selector->GetElementCount() == 0 || m_array[i].selector->HasElement(element)) &&
                m_array[i].selector->HasClass(className))
            return i;
        }
    }
    else
    {
        for (swUI32 i = start; i < m_arrayPos; i ++)
        {
            if (m_array[i].selector->HasClass(className))
                return i;
        }
    }

    return NODE_ID_INVALID;
}

swUI32 CssFile::Find(SwThMLParser & parser, swUI32 node, const char * name, swUI32 start)
{
    swUI32 elementPos;
    swUI16 selelement;
    bool IdMatch = false;
    swUI32 id;

    SwString element, value;

    if (!name)
        return NODE_ID_INVALID;

    parser.GetElementStrFromNode(node, element);

    for (swUI32 i = start; i < m_arrayPos; i ++)
    {
        elementPos = NODE_ID_INVALID;

        id = m_array[i].selector->FindNameValuePair();
        if (id != NODE_ID_INVALID)
        {
            IdMatch = parser.GetNamedValueFromNode(node, m_array[i].selector->GetNode(id)->item, value);
            if (IdMatch)
            {
                if (strcmp(value, m_array[i].selector->GetNode(id + 1)->item) != 0)
                    IdMatch = false;
            }
        }

        if (id != NODE_ID_INVALID && !IdMatch)
            continue;

        if (name[0] == '\0' && !m_array[i].selector->HasElement(element) && !IdMatch)
            continue;

        if (name[0] != '\0' && m_array[i].selector->GetClassCount() > 0 && !m_array[i].selector->HasClass(name))
            continue;

         if (name[0] == '\0' && m_array[i].selector->GetClassCount() > 0)
            continue;

        if (m_array[i].selector->GetElementCount() > 0 && !m_array[i].selector->HasElement(element))
            continue;

        if (m_array[i].selector->GetElementCount() > 0)
            elementPos = m_array[i].selector->FindElement(element);

        if (elementPos && elementPos != NODE_ID_INVALID && m_array[i].selector->HasPseudoElement(elementPos))
        {
            selelement = parser.IdentifyElement(m_array[i].selector->GetNode(elementPos - 1)->item, false);

            if (m_array[i].selector->GetNode(elementPos - 1)->opcode == CSS_OP_SPACE && parser.IsWithIn(node, selelement))
                return i;
            else if (m_array[i].selector->GetNode(elementPos - 1)->opcode == CSS_OP_GT && parser.IsChildOf(node, selelement))
                return i;
            else if (m_array[i].selector->GetNode(elementPos - 1)->opcode == CSS_OP_PLUS && parser.IsNext(node, selelement))
                return i;
            else if (m_array[i].selector->GetNode(elementPos - 1)->opcode == CSS_OP_TILDE && parser.IsPreceededBy(node, selelement))
                return i;
        }
        else
        {
            return i;
        }
    }

    return NODE_ID_INVALID;
}

const char * CssFile::GetStyle(swUI32 pos)
{
    if (pos >= m_arrayPos)
    {
        return NULL;
    }

    return m_array[pos].style->GetArray();
}

swUI16 CssFile::GetSpecificity(swUI32 pos)
{
    if (pos >= m_arrayPos)
        return 0;

    return m_array[pos].selector->GetSpecificity();
}
