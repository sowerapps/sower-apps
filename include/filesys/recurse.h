///////////////////////////////////////////////////////////////////
// Name:        recurse.h
// Purpose:     Directory recursion.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef RECURSE_H
#define RECURSE_H

#include "../sowerbase.h"

class SOWERBASEEXP SwDirRecurse
{
public:
    SwDirRecurse();
    virtual ~SwDirRecurse();

    swI8 RecurseDir(const char *path, bool searchsubdirs);
    virtual bool OnFile(const char * path);
    virtual bool OnDir(const char * path);
    virtual void OnProcessEnd() {}
    static swI8 FindFile(const char *path, char * fileName, bool searchsubdirs, bool casesensitive);
};

#endif // RECURSE_H
