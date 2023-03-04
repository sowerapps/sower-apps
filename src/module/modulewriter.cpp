///////////////////////////////////////////////////////////////////
// Name:        modulewriter.cpp
// Purpose:     Base class for writing modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/modulewriter.h"
#include "../../include/module/transcryptor.h"
#include "../../include/thml/thml_utility.h"

SwModuleWriter::SwModuleWriter()
{
}

SwModuleWriter::~SwModuleWriter()
{
}

bool SwModuleWriter::OpenFile(const char * path, bool thml)
{
    Reset();
    if (!path)
        return false;

    bool status = SwCssInliner::OpenFile(path, thml);

    if (!status)
        return status;

    return PresizeBuffer();
}

void SwModuleWriter::Reset()
{
    m_header.Zero();
    m_contents.Reset();
    m_scriptureMap.Reset();
    m_verse.Reset();
    m_commentaryMap.Reset();
    m_commentary.Reset();
    m_term.Reset();
    m_strongsH.Reset();
    m_strongsG.Reset();
    m_notes.Reset();
    m_media.Reset();
    m_k1 = 0;
    m_k2 = 0;
    m_swmoduleitemarray.SetCount(0);
    SwCssInliner::ResetFull();
    m_errors = 0;
    m_warnings = 0;
}

bool SwModuleWriter::PresizeBuffer()
{
    swUI32 items = 0;

    for (swUI32 i = 0; i < m_parserNodePos; i++)
    {
        if (GetNodeElementIdentifier(i) >= m_elementItems)
            continue;

        if (GetNodeType(i) != NODE_TYPE_BEGIN_TAG)
            continue;

        switch (GetNode(i)->elementIdentifier)
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
            items ++;
        }
    }

    return m_swmoduleitemarray.Size(items + 100);
}

swUI16 SwModuleWriter::CountDivisionItems(swUI32 item)
{
    // Counts subitems within major divisions.
    swUI16 divItems = 1;
    swUI32 node = FindNodeByStreamPos(m_swmoduleitemarray.GetAt(item).position);

    if (node == NODE_ID_INVALID)
        return 1;

    node = FindBreakItem(node);

    if (node == NODE_ID_INVALID)
        return 1;

    swUI32 endPosition = GetNodeStreamPosition(node);

    for (swUI32 i = item + 1; i < m_swmoduleitemarray.GetCount(); i++)
    {
        if (m_swmoduleitemarray.GetAt(i).position > endPosition)
        {
            break;
        }

        divItems ++;
    }

    return divItems;
}

void SwModuleWriter::SetDivisionItems()
{
    for (swUI32 i = 0; i < m_swmoduleitemarray.GetCount(); i++)
    {
        m_swmoduleitemarray.Get(i)->divItems = CountDivisionItems(i);
    }
}

bool SwModuleWriter::BuildModule()
{
    SetDivisionItems();
    m_commentary.Import(m_commentaryMap);
    m_verse.Import(m_scriptureMap);

    return true;
}

bool SwModuleWriter::CreateItemData()
{
    return true;
}

bool SwModuleWriter::OnBuild()
{
    if (!CreateItemData())
        return false;

    return BuildModule();
}

bool SwModuleWriter::WriteModule(const char * path)
{
    if (!path)
        return false;

    FILE * f = NULL;

    f = SwFopen(path, FMD_WC);

    if (!f)
        return false;

    // Write header to disk.
    if (fwrite((void *) &m_header, sizeof(SwModuleHeader), 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    // Generate keys.
    if (m_header.isEncrypted)
    {
        m_k1 = SwTranscryptor::GetNumber(KEY_GEN_MIN, KEY_GEN_MAX, true);
        m_k2 = SwTranscryptor::Generate(m_k1);
    }

    // Write interfaces to disk.
    m_header.tableofcontentsLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_contents.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_contents.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    m_header.autodefverseLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_verse.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_verse.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    m_header.autodefcommentaryLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_commentary.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_commentary.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    m_header.autodeftermLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_term.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_term.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    m_header.autodefstrongshLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_strongsH.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_strongsH.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    m_header.autodefstrongsgLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_strongsG.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_strongsG.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    m_header.autodefnotesLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_notes.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_notes.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    // Write thml file to disk.
    m_header.filecontentsLocator = ftell(f);
    if (m_header.isEncrypted)
    {
        SwTranscryptor::encryptfwrite((void *) m_sourceBuffer, 1, m_dataSize, f, m_k1, m_k2);
    }
    else
    {
        fwrite((void *) m_sourceBuffer, 1, m_dataSize, f);
    }

    // Override to add media to file, write to disk,
    // and fill SwMediaContents object with data.
    // Add SwModuleItem for each file.
    // Add item to SwMediaContents.
    // Write media to disk.

    if (!WriteMedia(f))
    {
        fclose(f);
        return false;
    }

    m_header.mediacontentsLocator = ftell(f);
    if (!m_header.isEncrypted)
    {
        if (!m_media.WriteToFile(f))
        {
            fclose(f);
            return false;
        }
    }
    else
    {
        if (!m_media.WriteToFile(f, m_k1, m_k2))
        {
            fclose(f);
            return false;
        }
    }

    // Write SwModuleItem objects to file.
    m_header.itemdataLocator = ftell(f);
    m_header.items = m_swmoduleitemarray.GetCount();
    if (fwrite((void *) m_swmoduleitemarray.GetArray(), sizeof(SwModuleItem), m_swmoduleitemarray.GetCount(), f) != m_swmoduleitemarray.GetCount())
    {
        fclose(f);
        return false;
    }

    // Update header.
    fseek(f, 0, SEEK_SET);

    if (fwrite((void *) &m_header, sizeof(SwModuleHeader), 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    fclose(f);

    // Finished.
    return true;
}

swUI32 SwModuleWriter::FindBreakItem(swUI32 node)
{
    return GetNodeMate(node);
}

bool SwModuleWriter::WriteMedia(FILE * f)
{
    return true;
}

swUI8 SwModuleWriter::GetContentType(swUI32 node)
{
    SwString buffer;

    if (!GetNamedValueFromNode(node, "type", buffer))
        return CT_UNKNOWN;

    return SwContentType::GetContentType(buffer);
}
