///////////////////////////////////////////////////////////////////
// Name:        sidfilewriter.h
// Purpose:     Scan Sower source files for string identifiers and
//              create a Sower Data File that can be edited with
//              Sower Translation Editor.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef SIDFILEWRITER_H
#define SIDFILEWRITER_H

#include "../string/string.h"
#include "../array/stringarray.h"
#include "../filesys/recurse.h"

class SOWERBASEEXP SidFileWriter : public SwDirRecurse
{
public:
    SidFileWriter();
    virtual ~SidFileWriter();

    void Reset();
    virtual bool OnFile(const char * path);
    void Create(const char * output);

protected:
    SwStringArray m_sid;
    SwStringArray m_text;
    SwString      m_conversion;
    SwString      m_readBuffer;
};

extern "C" SOWERBASEEXP void CreateTranslationFiles(const char * srcpath, const char * outputpath);

#endif // SIDFILEWRITER_H
