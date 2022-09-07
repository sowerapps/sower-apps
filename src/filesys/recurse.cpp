///////////////////////////////////////////////////////////////////
// Name:        recurse.cpp
// Purpose:     Directory recursion.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/filesys/recurse.h"
#include "../../include/filesys/file.h"
#include "../../include/string/strparser.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

SwDirRecurse::SwDirRecurse()
{
}

SwDirRecurse::~SwDirRecurse()
{
}

swI8 SwDirRecurse::RecurseDir(const char *path, bool searchsubdirs)
{
    DIR *dir[128];
    swI8 i8_Deep = -1;
    swI8 i8_CloseLoop = 0;
    struct dirent *ent;
    struct _stat st;
    char szFile[MAX_PATH+1];
    swI16 i16_flen[128];
    swI8 rstatus;

    if (!path || (dir[0] = opendir(path)) == NULL)
    {
        return -1;
    }

    strcpy(szFile, path);
    i16_flen[0] = strlen(path) + 1;
    strcat(szFile, S_PATH_SEP);

    i8_Deep = 0;
    while (i8_Deep >= 0)
    {
        while ((ent = readdir(dir[i8_Deep])) != NULL && i8_CloseLoop == 0)
        {
            strcat(szFile, ent->d_name);
            SwFile::Stat(szFile, &st);

            if (st.st_mode & S_IFDIR && searchsubdirs)
            {
                if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0)
                {

                    strcat(szFile, S_PATH_SEP);
                    i16_flen[i8_Deep + 1] = i16_flen[i8_Deep] + strlen(ent->d_name) + 1;
                    dir[i8_Deep + 1] = opendir(szFile);

                    if (dir[i8_Deep + 1] != NULL)
                    {
                        i8_Deep ++;
                    }
                    else
                    {
                        szFile[i16_flen[i8_Deep]] = '\0';
                    }
                }
                else
                {
                    szFile[i16_flen[i8_Deep]] = '\0';
                }
            }
            else if (st.st_mode & S_IFREG)
            {
                rstatus = OnFile(szFile);
                if (!rstatus)
                {
                    i8_CloseLoop = 1;
                    continue;
                }
                else if (rstatus == 2)
                {
                    closedir(dir[i8_Deep]);
                    i8_Deep --;

                    if (i8_Deep >= 0)
                        szFile[i16_flen[i8_Deep]] = '\0';

                    continue;
                }

                szFile[i16_flen[i8_Deep]] = '\0';
            }
            else
            {
                szFile[i16_flen[i8_Deep]] = '\0';
            }
        }

        closedir(dir[i8_Deep]);

        if (!OnDir(szFile))
            i8_CloseLoop = 1;

        i8_Deep --;

        if (i8_Deep >= 0)
            szFile[i16_flen[i8_Deep]] = '\0';
    }

    OnProcessEnd();
    return 1;
}

bool SwDirRecurse::OnDir(const char * path)
{
    return true;
}

bool SwDirRecurse::OnFile(const char * path)
{
    return true;
}

swI8 SwDirRecurse::FindFile(const char *path, char * fileName, bool searchsubdirs, bool casesensitive)
{
    DIR *dir[128];
    swI8 i8_Deep = -1;
    swI8 i8_CloseLoop = 0;
    struct dirent *ent;
    struct _stat st;
    char szFile[MAX_PATH+1];
    swI16 i16_flen[128];

    if (!path || !fileName || (dir[0] = opendir(path)) == NULL)
    {
        return -1;
    }

    strcpy(szFile, path);
    i16_flen[0] = strlen(path) + 1;
    strcat(szFile, S_PATH_SEP);

    i8_Deep = 0;
    while (i8_Deep >= 0)
    {
        while ((ent = readdir(dir[i8_Deep])) != NULL && i8_CloseLoop == 0)
        {
            strcat(szFile, ent->d_name);
            SwFile::Stat(szFile, &st);

            if (st.st_mode & S_IFDIR && searchsubdirs)
            {
                if (strcmp(ent->d_name, "..") != 0 && strcmp(ent->d_name, ".") != 0 && i8_Deep < 128)
                {

                    strcat(szFile, S_PATH_SEP);
                    i16_flen[i8_Deep + 1] = i16_flen[i8_Deep] + strlen(ent->d_name) + 1;
                    dir[i8_Deep + 1] = opendir(szFile);

                    if (dir[i8_Deep + 1] != NULL)
                    {
                        i8_Deep ++;
                    }
                    else
                    {
                        szFile[i16_flen[i8_Deep]] = '\0';
                    }
                }
                else
                {
                    szFile[i16_flen[i8_Deep]] = '\0';
                }
            }
            else if (st.st_mode & S_IFREG)
            {
                if (!casesensitive && (stricmp(fileName, ent->d_name) == 0))
                {
                    strcpy(fileName, szFile);
                    i8_CloseLoop = 1;
                    continue;
                }
                else if (casesensitive && (strcmp(fileName, ent->d_name) == 0))
                {
                    strcpy(fileName, szFile);
                    i8_CloseLoop = 1;

                    continue;
                }

                szFile[i16_flen[i8_Deep]] = '\0';
            }
            else
            {
                szFile[i16_flen[i8_Deep]] = '\0';
            }
        }

        closedir(dir[i8_Deep]);
        i8_Deep --;

        if (i8_Deep >= 0)
            szFile[i16_flen[i8_Deep]] = '\0';
    }

    return i8_CloseLoop;
}
