///////////////////////////////////////////////////////////////////
// Name:        moduleloader.h
// Purpose:     SwModuleLoader
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SOWERMODULELOADER_H
#define SOWERMODULELOADER_H

#include "../module/module.h"

class SOWERBASEEXP SwModuleLoader : public SwDirRecurse
{
public:
    SwModuleLoader();
    virtual ~SwModuleLoader();

    virtual bool OnFile(const char * path);
    virtual void OnProcessEnd();
};

#endif // SOWERMODULELOADER_H
