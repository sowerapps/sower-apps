///////////////////////////////////////////////////////////////////
// Name:        plugin.cpp
// Purpose:     Base class for Sower plug-ins, and plug-in manager.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/plugin/plugin.h"

SwPlugIn::SwPlugIn()
{
    m_dll = NULL;
}

SwPlugIn::~SwPlugIn()
{
}

swUI8 SwPlugIn::GetVersion()
{
    return 0;
}

swUI8 SwPlugIn::GetType()
{
    return PIT_TOOL;
}

const char * SwPlugIn::GetName()
{
    return "";
}

const char * SwPlugIn::GetDescription()
{
    return "";
}

void SwPlugIn::OnInitialize()
{
}

void SwPlugIn::OnUnInitialize()
{
}

void SwPlugIn::OnInitializeTool()
{
}

bool SwPlugIn::CanClose()
{
    return true;
}

void SwPlugIn::OnLanguageChange()
{
}

void SwPlugIn::OnThemeChange()
{
}

void SwPlugIn::OnFontSizeChange()
{
}

void SwPlugIn::OnEnable()
{
}

void SwPlugIn::OnDisable()
{
}

SwPlugInManager::SwPlugInManager()
{
    m_array = NULL;
    m_count = 0;
    m_size = 0;
    m_interface = NULL;
    m_pluginsInitialized = false;
    m_loadType = PIT_UNKNOWN;
}

SwPlugInManager::~SwPlugInManager()
{
    if (m_array)
    {
        free(m_array);
    }
}

void SwPlugInManager::Reset()
{
    Size(7);
    SetCount(0);
}

swUI32 SwPlugInManager::Size(swUI32 size, bool shrink)
{
    if (!size && m_array && shrink)
    {
        free(m_array);
        m_array = NULL;
        m_size = 0;
        m_count = 0;
        return 0;
    }

    if (size < 7)
        size = 7;

    if (m_array && m_size >= size && !shrink)
        return m_size;

    SwPlugIn ** p = (SwPlugIn **) realloc((void *) m_array, m_size * sizeof(SwPlugIn *));

    if (p)
    {
        m_size = size;
        m_array = p;
        return m_size;
    }

    // Return 0 instead of actual buffer size because operation failed.
    return 0;
}

swUI32 SwPlugInManager::GetSize()
{
    return m_size;
}

bool SwPlugInManager::AddLibrary(wxDynamicLibrary * dll)
{
    if (!dll)
        return false;

    bool result;

    if (dll->HasSymbol("PlugInInitialize"))
    {
        if (m_loadType != PIT_UNKNOWN && GetType(dll) != m_loadType)
        {
            delete dll;
            return false;
        }

        _PlugInInitialize dllfunc = (_PlugInInitialize) dll->GetSymbol("PlugInInitialize", &result);

        if (result)
        {
            if (m_count >= GetSize() && !Size(m_count + 1))
            {
                delete dll;
                return false;
            }

            m_array[m_count] = dllfunc();

            if (m_array[m_count] == NULL)
            {
                delete dll;
                return false;
            }

            m_array[m_count]->m_dll = dll;
            m_count ++;

            return true;
        }
    }

    delete dll;
    return false;
}

void SwPlugInManager::SetAt(swUI32 pos, SwPlugIn * plugin)
{
    if (pos >= GetSize())
        return;

    m_array[pos] = plugin;
}

SwPlugIn * SwPlugInManager::GetAt(swUI16 pos)
{
    if (pos >= m_count)
        return NULL;

    return m_array[pos];
}

swUI8 SwPlugInManager::GetType(wxDynamicLibrary * dll)
{
    if (!dll)
        return PIT_UNKNOWN;

    bool result;
    SwPlugIn * plugIn;

    if (dll->HasSymbol("PlugInInitialize"))
    {
        _PlugInInitialize dllfunc = (_PlugInInitialize) dll->GetSymbol("PlugInInitialize", &result);

        if (result)
        {
            plugIn = dllfunc();
            return plugIn->GetType();
        }
    }

    return PIT_UNKNOWN;
}

bool SwPlugInManager::SetInterfacePlugIn(SwPlugIn * plugin, bool callInitialize)
{
    if (!plugin)
        return false;

    m_interface = plugin;

    if (callInitialize)
        plugin->OnInitialize();

    return true;
}

bool SwPlugInManager::SetInterfacePlugIn(swUI16 pos, bool callInitialize)
{
    if (pos >= GetCount())
        return false;

    m_interface = GetAt(pos);

    if (!m_interface)
        return false;

    if (callInitialize)
        m_interface->OnInitialize();

    return true;
}

SwPlugIn * SwPlugInManager::GetInterfacePlugIn()
{
    return m_interface;
}

void SwPlugInManager::OnInitialize(swUI8 type)
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != type)
            continue;

        m_array[i]->OnInitialize();
    }

    m_pluginsInitialized = true;
}

void SwPlugInManager::OnInitialize()
{
    if (m_pluginsInitialized)
        return;

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_MODULE)
            continue;

        m_array[i]->OnInitialize();
    }

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_VIEWER)
            continue;

        m_array[i]->OnInitialize();
    }

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_EDITOR)
            continue;

        m_array[i]->OnInitialize();
    }

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_TOOL)
            continue;

        m_array[i]->OnInitialize();
    }

    m_pluginsInitialized = true;
}

void SwPlugInManager::OnUnInitialize(swUI8 type)
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != type)
            continue;

        m_array[i]->OnUnInitialize();
    }
}

void SwPlugInManager::OnUnInitialize()
{
    if (!m_pluginsInitialized)
        return;

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_TOOL)
            continue;

        m_array[i]->OnUnInitialize();
    }

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_EDITOR)
            continue;

        m_array[i]->OnUnInitialize();
    }

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_VIEWER)
            continue;

        m_array[i]->OnUnInitialize();
    }

    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_MODULE)
            continue;

        m_array[i]->OnUnInitialize();
    }

    m_pluginsInitialized = false;
}


void SwPlugInManager::OnInitializeTools()
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_TOOL)
            continue;

        m_array[i]->OnInitializeTool();
    }
}

bool SwPlugInManager::CanClose()
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (!m_array[i] || m_array[i]->GetType() != PIT_EDITOR)
            continue;

        if (!m_array[i]->CanClose())
            return false;
    }

    return true;
}

void SwPlugInManager::OnLanguageChange()
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (m_array[i])
            m_array[i]->OnLanguageChange();
    }
}

void SwPlugInManager::OnThemeChange()
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (m_array[i])
            m_array[i]->OnThemeChange();
    }
}

void SwPlugInManager::OnFontSizeChange()
{
    for (swUI16 i = 0; i < m_count; i++)
    {
        if (m_array[i])
            m_array[i]->OnFontSizeChange();
    }
}

swUI16 SwPlugInManager::FindPlugIn(const char * name, swUI16 start)
{
    swUI16 pos = start;

    if (!name)
        return NODE_ID_INVALID_16;

    while (pos < m_count)
    {
        if (m_array[pos] &&
                strcmp(name, m_array[pos]->GetName()) == 0)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwPlugInManager::FindPlugIn(swUI8 pittype, swUI16 start)
{
    swUI16 pos = start;

    while (pos < m_count)
    {
        if (m_array[pos] &&
                m_array[pos]->GetType() == pittype)
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

bool SwPlugInManager::AreplugInsInitialized()
{
    return m_pluginsInitialized;
}

void SwPlugInManager::SetCount(swUI16 count)
{
    m_count = count;
}

swUI16 SwPlugInManager::GetCount()
{
    return m_count;
}

swUI16 SwPlugInManager::FindFirstInterface()
{
    SwPlugIn * plugin;

    for (swUI32 i = 0; i < GetCount(); i++)
    {
        plugin = GetAt(i);

        if (!plugin)
            continue;

        if (plugin->GetType() != PIT_INTERFACE)
            continue;

        return i;
    }

    return NODE_ID_INVALID_16;
}

swUI16 SwPlugInManager::FindFileHandler(const char * extension)
{
    swUI16 pos = 0;

    if (!extension)
        return NODE_ID_INVALID_16;

    while (pos < m_count)
    {
        if (m_array[pos] && m_array[pos]->CanHandle(extension))
            return pos;

        pos ++;
    }

    return NODE_ID_INVALID_16;
}

void SwPlugInManager::GetExtensions(SwStringArray & array)
{
    swUI16 pos = 0;

    while (pos < m_count)
    {
        if (m_array[pos] && m_array[pos]->GetExtensions() && strlen(m_array[pos]->GetExtensions()))
            array.Add(m_array[pos]->GetExtensions());

        pos ++;
    }
}
