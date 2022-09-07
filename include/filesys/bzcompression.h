///////////////////////////////////////////////////////////////////
// Name:        bzcompression.h
// Purpose:     BZip routines.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef BZCOMPRESSION_H
#define BZCOMPRESSION_H

#include "../sowerbase.h"

extern "C" SOWERBASEEXP bool SwUnBZipFile(const char * inputpath, const char * outputpath);
extern "C" SOWERBASEEXP bool SwBZipFile(const char * inputpath, const char * outputpath);

#endif // BZCOMPRESSION_H
