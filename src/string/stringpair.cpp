///////////////////////////////////////////////////////////////////
// Name:        stringpair.cpp
// Purpose:     Container for pairs of SwString.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/string/stringpair.h"

SwStringPair::SwStringPair()
{
}

SwStringPair::SwStringPair(const char * strA, const char * strB)
{
    if (!strA || !strB)
        return;

    m_strA = strA;
    m_strB = strB;
}

SwStringPair::~SwStringPair()
{

}

void SwStringPair::Reset()
{
    m_strA.Reset();
    m_strB.Reset();
}

void SwStringPair::Init()
{
    m_strA.Init();
    m_strB.Init();
}

SwString & SwStringPair::GetStrA()
{
    return m_strA;
}

SwString & SwStringPair::GetStrB()
{
    return m_strB;
}

SwStringTriplet::SwStringTriplet()
{
}

SwStringTriplet::SwStringTriplet(const char * strA, const char * strB, const char * strC)
{
    if (!strA || !strB || !strC)
        return;

    m_strA = strA;
    m_strB = strB;
    m_strC = strC;
}

SwStringTriplet::~SwStringTriplet()
{

}

void SwStringTriplet::Reset()
{
    m_strA.Reset();
    m_strB.Reset();
    m_strC.Reset();
}

void SwStringTriplet::Init()
{
    m_strA.Init();
    m_strB.Init();
    m_strC.Init();
}

SwString & SwStringTriplet::GetStrA()
{
    return m_strA;
}

SwString & SwStringTriplet::GetStrB()
{
    return m_strB;
}

SwString & SwStringTriplet::GetStrC()
{
    return m_strC;
}

