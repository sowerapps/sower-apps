///////////////////////////////////////////////////////////////////
// Name:        file.cpp
// Purpose:     Files, and file paths.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/filesys/file.h"
#include "../../include/string/stringw.h"
#include "../../include/string/strparser.h"
#include "../../include/module/transcryptor.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "wx/wxcrt.h"

FILE * SwFopen(const char * path, const char * mode)
{
    return wxFopen(wxString::FromUTF8(path), mode);
}

void SwClipFileName(char * path)
{
    if (!path)
        return;

    int len = strlen(path);

    while (len > 0)
    {
        if (path[len] == '\\' || path[len] == '/')
        {
            path[len] = '\0';
            return;
        }
        len --;
    }
}

void SwClipExtension(char * path)
{
    if (!path)
        return;

    char * p = strrchr(path, '.');
    if (p)
        *p = '\0';
}

void SwClipAnchor(char * path)
{
    if (!path)
        return;

    char * p = strrchr(path, '#');
    if (p)
        *p = '\0';
}

bool SwGetFileName(const char * path, SwString & dest)
{
    if (!path)
        return false;

    int len = strlen(path);

    while (len > 0)
    {
        if (path[len] == '\\' || path[len] == '/')
        {
            break;
        }

        len --;
    }

    if (len < 1)
        return false;

    dest = &path[len + 1];

    return true;
}

bool SwGetExtension(const char * path, SwString & dest)
{
    if (!path)
        return false;

    int len = strlen(path);

    while (len > 0)
    {
        if (path[len] == '.')
        {
            break;
        }

        len --;
    }

    if (len < 1)
        return false;

    dest = &path[len + 1];

    return true;
}

bool SwGetAnchor(const char * path, SwString & dest)
{
    if (!path)
        return false;

    int len = strlen(path);

    while (len > 0)
    {
        if (path[len] == '#')
        {
            break;
        }

        len --;
    }

    if (len < 1)
        return false;

    dest = &path[len + 1];

    return true;
}

void SwNormalizePath(char * path)
{
    if (!path)
        return;

    swUI32 pos = 0, len = strlen(path);

    while (pos < len)
    {
        if (path[pos] == '\\' || path[pos] == '/')
            path[pos] = PATH_SEP;

        pos ++;
    }
}

bool SwGetPathFromRelative(const char * base, const char * source, SwString & dest)
{
    if (!base || !source)
        return false;

    SwString path, src;

    dest = base;
    SwNormalizePath(dest);
    dest.TrimRight(PATH_SEP);
    src = source;
    SwNormalizePath(src);

    char * p = strstr(src, PATH_BRK),  * last = NULL;

    if (!p)
    {
        dest += PATH_SEP;
        dest += src;

        return true;
    }

    int count = 1;
    last = p;

    while (p)
    {

        p += 2;
        p = strstr(p, PATH_BRK);
        if (p)
        {
            last = p;
            count ++;
        }
    }

    int pos = dest.Strlen();

    while (pos)
    {
        if (dest.GetAt(pos) == PATH_SEP)
            count --;

        if (!count)
            break;

        pos --;
    }

    if (count || !last)
        return false;

    last += 3;
    dest.SetAt(pos + 1, '\0');
    dest += last;

    return true;
}

bool SwGetRelativePath(const char * base, const char * source, SwString & dest)
{
    if (!base || !source)
        return false;

    SwStrParser sla, slb;
    sla.SetDeliminator(PATH_SEP);
    slb.SetDeliminator(PATH_SEP);
    dest.Reset();

    SwString pathA, pathB;
    pathA = base;
    pathB = source;

    SwNormalizePath(pathA);
    SwNormalizePath(pathB);

    sla.ParseString(pathA);
    slb.ParseString(pathB);

    swUI32 n = 0;

    if (!sla.GetItems() || !slb.GetItems())
        return false;

    if (strcmp(sla.GetItem(0), slb.GetItem(0)) != 0)
    {
        dest = source;
        return true;
    }

    bool sepAdded = true;
    for(;;)
    {
        if (sla.GetItems() > n && slb.GetItems() > n)
        {
            if (strcmp(sla.GetItem(n), slb.GetItem(n)) != 0)
            {
                for (swUI32 i = n; i < sla.GetItems(); i ++)
                {
                    dest += PATH_BRK;
                }
                break;
            }
        }
        else
            break;

        n ++;
    }

    for(;;)
    {
        if (n >= slb.GetItems())
            break;

        if (!sepAdded)
            dest += PATH_SEP;

        dest += slb.GetItem(n);
        sepAdded = false;
        n++;
    }

    return true;
}

bool SwMakePath(const char * path)
{
    if (!path)
    {
        return false;
    }

    SwString s_path;
    s_path = path;

    int nStat;
    char * psz;
    struct _stat st;

    psz = strchr(s_path, PATH_SEP);

    if (!psz)
        return false;

    psz ++;

    for (;;)
    {
        psz = strchr(psz, PATH_SEP);

        if (!psz)
            break;

        psz[0] = '\0';
        nStat = _stat(s_path, &st);

        if (nStat == -1)
        {
#if defined __MSWIN__
            nStat = mkdir(s_path);
#else
            nStat = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif // defined
        }

        psz[0] = PATH_SEP;

        if (nStat == -1)
            return false;

        psz ++;
    }

    nStat = _stat(s_path, &st);

    if (nStat == -1)
    {
#if defined __MSWIN__
        nStat = mkdir(s_path);
#else
        nStat = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif // defined
    }

    if (nStat == -1)
        return false;

    return true;
}

bool SwMakeDir(const char * path)
{
    if (!path)
    {
        return false;
    }

    struct _stat st;

    if (SwFile::Stat(path, &st) != 0)
    {
#if defined __MSWIN__
        if (mkdir(path) != 0)
            return false;
#else
        if (mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
            return false;
#endif // defined
    }

    return true;
}

bool SwIsPathSep(char ch)
{
    if (ch == '\\' || ch == '/')
        return true;

    return false;
}

SwFilePath::SwFilePath()
{
}

SwFilePath::SwFilePath(const char * path)
{
    if (path)
        SwString::operator = (path);
}

SwFilePath::~SwFilePath()
{
}

void SwFilePath::Add(const char * addition)
{
    if (addition)
        SwString::operator += (addition);
}

void SwFilePath::ReplaceExtension(const char * extension)
{
    if (extension)
    {
        ClipExtension();
        SwString::operator += ('.');
        SwString::operator += (extension);
    }
}

void SwFilePath::ClipFileName()
{
    SwClipFileName(m_array);
}

const char * SwFilePath::GetFileName()
{
    char * p = StrRevChr(PATH_SEP);
    if (!p)
        return m_array;

    return p + 1;
}

const char * SwFilePath::GetFilePath()
{
    return m_array;
}

void SwFilePath::ClipExtension()
{
    SwClipExtension(m_array);
}

const char * SwFilePath::GetExtension()
{
    char * p = StrRevChr('.');
    if (!p)
        return "";

    return p + 1;
}

void SwFilePath::ClipAnchor()
{
    SwClipAnchor(m_array);
}

const char * SwFilePath::GetAnchor()
{
    char * p = StrRevChr('#');
    if (!p)
        return "";

    return p + 1;
}

void SwFilePath::NormalizePath()
{
    SwNormalizePath(m_array);
}

bool SwFilePath::MakePath()
{
    return SwMakePath(m_array);
}

bool SwFilePath::MakeDir()
{
    return SwMakeDir(m_array);
}

SwFile::SwFile()
{
    m_file = NULL;
}

SwFile::SwFile(const char * path, const char * mode)
{
    m_file = SwFopen(path, mode);
}

SwFile::~SwFile()
{
    if (m_file)
        fclose(m_file);
}

bool SwFile::DoesExist(const char * path)
{
    struct _stat st;

    if (Stat(path, &st) == 0)
        return true;

    return false;
}

int SwFile::Stat(const char * path, struct _stat *st)
{
#if defined __MSWIN__
    SwStringW buffer;
    buffer.Copy(path);
    return _wstat(buffer, st);
#else
    return stat(path, st);
#endif // defined
}

int SwFile::CompareModifiedDates(const char * pathA, const char * pathB)
{
    if (!pathA || !pathB)
        return -1;

    struct _stat a, b;

    if (Stat(pathA, &a) == -1 || Stat(pathB, &b) == -1)
        return -1;

    if (a.st_mtime == b.st_mtime)
        return 0;
    else if (a.st_mtime > b.st_mtime)
        return 1;

    return 2;
}

size_t SwFile::GetSize(const char * path)
{
    struct _stat st;

    if (Stat(path, &st) == 0)
        return st.st_size;

    return 0;
}

bool SwFile::Open(const char * path, const char * mode)
{
    if (!path)
        return false;

    if (m_file)
        fclose(m_file);

    m_file = wxFopen(path, mode);
    return (bool) m_file;
}

bool SwFile::Close()
{
    if (m_file)
        fclose(m_file);
    else
        return false;

    m_file = NULL;

    return true;
}

size_t SwFile::Read(void * buffer, swUI32 size, swUI32 count)
{
    if (!m_file)
        return -1;

    return fread(buffer, size, count, m_file);
}

size_t SwFile::Read(void * buffer, swUI32 size, swUI32 count, swUI8 k1, swUI32 k2)
{
    if (!m_file)
        return -1;

    return SwTranscryptor::decryptfread(buffer, size, count, m_file, k1, k2);
}

size_t SwFile::Write(void * buffer, swUI32 size, swUI32 count)
{
    if (!m_file)
        return -1;

    return fwrite(buffer, size, count, m_file);
}

size_t SwFile::Write(void * buffer, swUI32 size, swUI32 count, swUI8 k1, swUI32 k2)
{
    if (!m_file)
        return -1;

    return SwTranscryptor::encryptfwrite(buffer, size, count, m_file, k1, k2);
}

size_t SwFile::GetSize()
{
     if (!m_file)
        return -1;

    struct stat st;
    fstat(fileno(m_file), &st);

    return st.st_size;
}

long SwFile::Ftell()
{
    if (!m_file)
        return -1;

    return ftell(m_file);
}

void SwFile::Flush()
{
    if (!m_file)
        return;

    fflush(m_file);
}

int SwFile::Fseek(long position, int origin)
{
    if (!m_file)
        return -1;

    return fseek(m_file, position, origin);
}
