///////////////////////////////////////////////////////////////////
// Name:        moduleloader.cpp
// Purpose:     SwModuleLoader
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/module/moduleloader.h"
#include "../../include/appi/appifa.h"

SwModuleLoader::SwModuleLoader()
{
}

SwModuleLoader::~SwModuleLoader()
{
}

bool SwModuleLoader::OnFile(const char * path)
{
    swUI16 key;
    SwModule * module = new SwModule;

    if (!module->Load(path))
        delete module;
    else
    {
        if (module->GetHeader().isEncrypted)
        {
            key = SwApplicationInterface::GetKeyManager().FindMasterKey(module->GetHeader().GetIdentifier());

            if (key != NODE_ID_INVALID_16)
            {
                module->m_masterKey = SwApplicationInterface::GetKeyManager().GetKey(key);
            }
            else
            {
                key = SwApplicationInterface::GetKeyManager().FindKey(module->GetHeader().GetIdentifier());
            }

            if (!SwApplicationInterface::GetDecryptor() || key == NODE_ID_INVALID_16)
            {
                delete module;
                return true;
            }

            module->GetHeader().k1 = SwApplicationInterface::GetKeyManager().GetKey(key)->header.mk1;
            module->GetHeader().k2 = SwApplicationInterface::GetKeyManager().GetKey(key)->header.mk2;
        }

        SwApplicationInterface::GetModuleManager().Add(module);
    }

    return true;
}

void SwModuleLoader::OnProcessEnd()
{
    if (SwApplicationInterface::GetFrameWindow())
        SwApplicationInterface::GetFrameWindow()->OnModuleManagerLoaded();
}
