///////////////////////////////////////////////////////////////////
// Name:        stringpair.h
// Purpose:     Container for pairs of SwString.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRINGPAIR_H
#define STRINGPAIR_H

#include "../sowerbase.h"
#include "string.h"

class SOWERBASEEXP SwStringPair
{
public:
    SwStringPair();
    SwStringPair(const char * strA, const char * strB);
    virtual ~SwStringPair();

    void Reset();
    void Init();
    SwString & GetStrA();
    SwString & GetStrB();

protected:
    SwString m_strA;
    SwString m_strB;
};

class SOWERBASEEXP SwStringTriplet
{
public:
    SwStringTriplet();
    SwStringTriplet(const char * strA, const char * strB, const char * strb);
    virtual ~SwStringTriplet();

    void Reset();
    void Init();
    SwString & GetStrA();
    SwString & GetStrB();
    SwString & GetStrC();

protected:
    SwString m_strA;
    SwString m_strB;
    SwString m_strC;
};

#endif // STRINGPAIR_H
