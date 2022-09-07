///////////////////////////////////////////////////////////////////
// Name:        file.h
// Purpose:     Files, and file paths.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef FILE_H
#define FILE_H

#include "../../include/string/string.h"

#if defined __MSWIN__
#include <share.h>
#define FMD_R        "rb"
#define FMD_WC       "wb"
#define FMD_RW       "r+b"
#define FMD_RWC      "w+b"
#define FMD_A        "ab"
#define FMD_AC       "a+b"
#define PATH_SEP     '\\'
#define S_PATH_SEP   "\\"
#define S_WPATH_SEP L"\\"
#define PATH_BRK     "..\\"
#else
#define FMD_R        "r"
#define FMD_WC       "w"
#define FMD_RW       "r+"
#define FMD_RWC      "w+"
#define FMD_A        "a"
#define FMD_AC       "a+"
#define PATH_SEP     '/'
#define S_PATH_SEP   "/"
#define S_WPATH_SEP L"/"
#define PATH_BRK     "../"
#endif //

extern "C" SOWERBASEEXP FILE * SwFopen(const char * path, const char * mode);
extern "C" SOWERBASEEXP void SwClipFileName(char * path);
extern "C" SOWERBASEEXP void SwClipExtension(char * path);
extern "C" SOWERBASEEXP bool SwGetFileName(const char * path, SwString & dest);
extern "C" SOWERBASEEXP bool SwGetExtension(const char * path, SwString & dest);
extern "C" SOWERBASEEXP void NormalizePath(char * path);
extern "C" SOWERBASEEXP bool SwGetPathFromRelative(const char * base, const char * source, SwString & dest);
extern "C" SOWERBASEEXP bool SwGetRelativePath(const char * base, const char * source, SwString & dest);
extern "C" SOWERBASEEXP bool SwMakePath(const char * path);
extern "C" SOWERBASEEXP bool SwMakeDir(const char * path);
extern "C" SOWERBASEEXP bool SwIsPathSep(char ch);

class SOWERBASEEXP SwFilePath : public SwString
{
public:
    SwFilePath();
    SwFilePath(const char * path);
    virtual ~SwFilePath();

    void Add(const char * addition);
    void ReplaceExtension(const char * extension);
    void ClipFileName();
    const char * GetFileName();
    const char * GetFilePath();
    void ClipExtension();
    const char * GetExtension();
    void NormalizePath();
    bool MakePath();
    bool MakeDir();
};

class SOWERBASEEXP SwFile
{
public:
    SwFile();
    SwFile(const char * path, const char * mode = FMD_R);
    virtual ~SwFile();

    static bool DoesExist(const char * path);
    static int Stat(const char * path, struct _stat *st);
    static int CompareModifiedDates(const char * pathA, const char * pathB);
    static size_t GetSize(const char * path);

    bool Open(const char * path, const char * mode);
    bool Close();
    size_t Read(void * buffer, swUI32 size, swUI32 count);
    size_t Read(void * buffer, swUI32 size, swUI32 count, swUI8 k1, swUI32 k2);
    size_t Write(void * buffer, swUI32 size, swUI32 count);
    size_t Write(void * buffer, swUI32 size, swUI32 count, swUI8 k1, swUI32 k2);
    size_t GetSize();
    long Ftell();
    void Flush();
    int Fseek(long position, int origin = SEEK_SET);

protected:
    FILE * m_file;
};

#endif // PATH_H
