///////////////////////////////////////////////////////////////////
// Name:        bzcompression.cpp
// Purpose:     BZip routines.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/filesys/bzcompression.h"
#include "../../include/filesys/file.h"
#include "../../include/filesys/file.h"
#include "bzlib.h"

bool SwUnBZipFile(const char * inputpath, const char * outputpath)
{
    if (!inputpath || !outputpath)
        return false;

    FILE * fsInput = SwFopen(inputpath, FMD_R);

    if (!fsInput)
        return false;

    FILE * fsOutput = SwFopen(outputpath, FMD_WC);

    if (!fsOutput)
    {
        fclose(fsInput);
        return false;
    }

    BZFILE * bzInput;
    swUI32 bytesRead;
    char readBuffer[16384];
    int bzerror;

    bzInput = BZ2_bzReadOpen(&bzerror, fsInput, 0, 1, NULL, 0);
    if (bzerror != BZ_OK)
    {
        BZ2_bzReadClose(&bzerror, bzInput);
        fclose(fsInput);
        fclose(fsOutput);
        unlink(outputpath);
        return false;
    }

    bzerror = BZ_OK;
    while (bzerror == BZ_OK)
    {
        bytesRead = BZ2_bzRead(&bzerror, bzInput, readBuffer, 16384);

        if ( bzerror == BZ_OK )
        {
            if (fwrite(readBuffer, 1, bytesRead, fsOutput) != bytesRead)
            {
                BZ2_bzReadClose(&bzerror, bzInput);
                fclose(fsInput);
                fclose(fsOutput);
                unlink(outputpath);
                return false;
            }
        }
    }

    if (bzerror != BZ_STREAM_END)
    {
        BZ2_bzReadClose(&bzerror, bzInput);
        fclose(fsInput);
        fclose(fsOutput);
        unlink(outputpath);
        return false;
    }

    BZ2_bzReadClose (&bzerror, bzInput);
    fclose(fsInput);
    fclose(fsOutput);

    return true;
}

bool SwBZipFile(const char * inputpath, const char * outputpath)
{
    if (!inputpath || !outputpath)
        return false;

    swI32 bytesRemaining = (unsigned) SwFile::GetSize(inputpath);

    if (!bytesRemaining)
        return false;

    FILE * fsInput = SwFopen(inputpath, FMD_R);

    if (!fsInput)
        return false;

    FILE * fsOutput = SwFopen(outputpath, FMD_WC);

    if (!fsOutput)
    {
        fclose(fsInput);
        return false;
    }

    BZFILE * bzOutput;
    swUI32 bytesinBuffer;
    char readBuffer[16384];
    int bzerror;

    bzOutput = BZ2_bzWriteOpen (&bzerror, fsOutput, 9, 0, 0);
    if (bzerror != BZ_OK)
    {
        BZ2_bzWriteClose(&bzerror, bzOutput, 0, NULL, NULL);
        fclose(fsInput);
        fclose(fsOutput);
        unlink(outputpath);
        return false;
    }

    bzerror = BZ_OK;
    while (bytesRemaining)
    {
        if (bytesRemaining > 16384)
        {
            bytesinBuffer = 16384;
        }
        else
        {
            bytesinBuffer = bytesRemaining;
        }

        if (fread(readBuffer, 1, bytesinBuffer, fsInput) != bytesinBuffer)
        {
            BZ2_bzWriteClose(&bzerror, bzOutput, 0, NULL, NULL);
            fclose(fsInput);
            fclose(fsOutput);
            unlink(outputpath);
            return false;
        }

        BZ2_bzWrite(&bzerror, bzOutput, readBuffer, bytesinBuffer);

        if (bzerror == BZ_IO_ERROR)
        {
            BZ2_bzWriteClose(&bzerror, bzOutput, 0, NULL, NULL);
            fclose(fsInput);
            fclose(fsOutput);
            unlink(outputpath);
            return false;
        }

        bytesRemaining -= bytesinBuffer;
    }

    BZ2_bzWriteClose(&bzerror, bzOutput, 0, NULL, NULL);
    fclose(fsInput);
    fclose(fsOutput);

    if (bzerror == BZ_IO_ERROR)
    {
        unlink(outputpath);
        return false;
    }

    return true;
}
