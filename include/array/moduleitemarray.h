///////////////////////////////////////////////////////////////////
// Name:        moduleitemarray.h
// Purpose:     SwModuleItem array.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MODULEITEMARRAY_H
#define MODULEITEMARRAY_H

#include "../sowerbase.h"
#include "../module/modulebase.h"

class SOWERBASEEXP SwModuleItemArray
{
public:
    SwModuleItemArray();
    SwModuleItemArray(SwModuleItemArray& other);
    virtual ~SwModuleItemArray();

    operator SwModuleItem * ();
    bool operator += (SwModuleItem mi);
    void Init();
    void Reset();
    void Zero();
    swUI32 Size(swUI32 size, bool shrink = false);
    swUI32 GetSize();
    SwModuleItem * GetArray();
    bool Copy(const SwModuleItem * src, swUI32 length);
    void SetAt(swUI32 pos, SwModuleItem mi);
    const SwModuleItem GetAt(swUI32 pos);
    SwModuleItem * Get(swUI32 pos);
    void SetCount(swUI32 count);
    swUI32 GetCount();
    void IncrementCount(swUI32 inc = 1);
    void DecrementCount(swUI32 dec = 1);

protected:
    SwModuleItem * m_array;
    swUI32         m_size;
    swUI32         m_count;
};

#endif // MODULEITEMARRAY_H
