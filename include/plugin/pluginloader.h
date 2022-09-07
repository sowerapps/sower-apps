///////////////////////////////////////////////////////////////////
// Name:        pluginloader.h
// Purpose:     Loader for Sower plug-ins.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "../filesys/recurse.h"

class SOWERBASEEXP SwPlugInLoader : public SwDirRecurse
{
public:
    SwPlugInLoader();
    virtual ~SwPlugInLoader();

    virtual bool OnFile(const char * path);
    virtual bool OnDir(const char * path);
};

#endif // PLUGINLOADER_H
