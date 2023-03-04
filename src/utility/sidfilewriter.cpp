///////////////////////////////////////////////////////////////////
// Name:        sidfilewriter.cpp
// Purpose:     Scan Sower source files for string identifiers and
//              create a Sower Data File that can be edited with
//              Sower Translation Editor.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/utility/sidfilewriter.h"
#include "../../include/module/category.h"
#include "../../include/filesys/recurse.h"
#include "../../include/filesys/file.h"
#include "../../include/sdf/datafile.h"
#include "../../include/html/html_encoded_char.h"

SidFileWriter::SidFileWriter()
{
}

SidFileWriter::~SidFileWriter()
{
}

void SidFileWriter::Reset()
{
    m_sid.Reset();
    m_text.Reset();
}

bool SidFileWriter::OnFile(const char * path)
{
    FILE * file = SwFopen(path, FMD_R);
    SwString sidValue, textValue;

    if (!file)
        return false;

    swUI32 insertPos;
    swUI32 fileSize = SwFile::GetSize(path);
    m_readBuffer.Size(fileSize + 1);

    if (fread((void *) m_readBuffer, 1, fileSize, file) != fileSize)
    {
        fclose(file);
        file = NULL;
        return false;
    }

    m_readBuffer.SetAt(fileSize, '\0');

    char * p = m_readBuffer.GetArray();

    while (p)
    {
        p = strstr(p, "SwApplicationInterface::GetControlString(\"SID");

        if (!p)
            break;

        p = strstr(p, "\"");
        if (!p)
            break;
        p ++;

        while (*p != '\0' && *p != '\"')
        {
            sidValue += *p;
            p++;
        }

        p ++;

        p = strstr(p, "\"");
        if (!p)
            break;
        p ++;

        while (*p != '\0' && *p != '\"')
        {
            textValue += *p;
            p++;
        }

        if (sidValue.Strlen() && textValue.Strlen())
        {
            if (m_sid.Find(sidValue) == NODE_ID_INVALID)
            {
                insertPos = m_sid.AddAlphabetically(sidValue);

                if (insertPos == NODE_ID_INVALID)
                    m_text.Add(textValue);
                else
                    m_text.Insert(insertPos, textValue);
            }
        }

        sidValue.Reset();
        textValue.Reset();

        p++;
    }

    fclose(file);

    return true;
}

void SidFileWriter::Create(const char * output)
{
    SwString buffer;
    buffer.Size(4096);

    FILE * file = SwFopen(output, FMD_WC);

    if (!file)
        return;

    fputs("<html>\n<head>\n<meta content=\"text/html; charset=utf8\" http-equiv=\"content-type\">\n</head>\n<body>\n", file);
    SwDataFile::CreateDataListString(m_sid, buffer, "String Identifiers");
    buffer += '\n';
    fwrite(buffer, buffer.Strlen(), 1, file);
    fputs("<table border=\"1\" width=\"100%%\">\n<caption>English (US)</caption>\n<tbody>\n", file);

    for (swUI32 i = 0; i < N_CATEGORIES; i ++)
    {
        m_text.Insert(m_sid.AddAlphabetically(SwCategory::GetId(i)), SwCategory::GetString(i));
    }

    for (swUI32 i = 0; i < N_CONTENT_TYPE; i ++)
    {
        m_text.Insert(m_sid.AddAlphabetically(SwContentType::GetId(i)), SwContentType::GetString(i));
    }

    for (swUI32 i = 0; i < m_sid.GetCount(); i ++)
    {
        if (m_sid.GetAt(i).Strlen() == 0)
            continue;
        SwHtmlEncodedChar::XmlEncodeString(m_text.GetAt(i), m_conversion);
        sprintf(buffer, "<tr param1=\"0\" param2=\"0\">\n<td>%s</td>\n<td>%s</td>\n</tr>\n", m_sid.GetAt(i).GetArray(), m_conversion.GetArray());
        fwrite(buffer, buffer.Strlen(), 1, file);
    }

    fputs("</tbody>\n</table>\n", file);
    fputs("\n</body>\n</html>", file);

    fclose(file);
}

void CreateTranslationFiles(const char * srcpath, const char * outputpath)
{
    SwString buf;
    SidFileWriter writer;

    if (!srcpath || !outputpath)
        return;

    writer.RecurseDir(srcpath, true);
    buf = outputpath;
    buf.TrimRight(PATH_SEP);
    buf += PATH_SEP;
    buf += "translation.sdf";
    writer.Create(buf);
}
