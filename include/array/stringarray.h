///////////////////////////////////////////////////////////////////
// Name:        stringarray.h
// Purpose:     SwString, SwStringW & SwStringPair arrays.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#include "../string/string.h"
#include "../string/stringw.h"
#include "../string/stringpair.h"

class SOWERBASEEXP SwStringArray
{
public:
    SwStringArray();
    virtual ~SwStringArray();

    void Reset();
    void ShiftUp(swUI32 start);
    bool ShiftDown(swUI32 start);
    swUI32 operator += (const char * str);
    swUI32 Add(const char * str);
    bool Delete(swUI32 pos);
    bool Insert(swUI32 nodePos, const char * str);
    SwString & GetAt(swUI32 pos);
    swUI32 Find(const char * str);
    swUI32 AddAlphabetically(const char * str);
    swUI32 FindAlphabeticInsertionPosition(const char * str);
    bool Size(swUI32 size);
    swUI32 GetCount();

protected:
    bool Grow();
    SwString * m_array;
    swUI32     m_size;
    swUI32     m_count;
};


class SOWERBASEEXP SwStringWArray
{
public:
    SwStringWArray();
    virtual ~SwStringWArray();

    void Reset();
    void ShiftUp(swUI32 start);
    bool ShiftDown(swUI32 start);
    swUI32 operator += (const wchar_t * str);
    swUI32 Add(const wchar_t * str);
    bool Delete(swUI32 pos);
    bool Insert(swUI32 nodePos, const wchar_t * str);
    SwStringW & GetAt(swUI32 pos);
    swUI32 Find(const wchar_t * str);
    swUI32 AddAlphabetically(const wchar_t * str);
    swUI32 FindAlphabeticInsertionPosition(const wchar_t * str);
    bool Size(swUI32 size);
    swUI32 GetCount();

protected:
    bool Grow();
    SwStringW * m_array;
    swUI32      m_size;
    swUI32      m_count;
};

class SOWERBASEEXP SwStringPairArray
{
public:
    SwStringPairArray();
    virtual ~SwStringPairArray();

    void Reset();
    void ShiftUp(swUI32 start);
    bool ShiftDown(swUI32 start);
    swUI32 Add(const char * strA, const char * strB);
    bool Delete(swUI32 pos);
    bool Insert(swUI32 nodePos, const char * strA, const char * strB);
    SwStringPair & GetAt(swUI32 pos);
    swUI32 FindInA(const char * str);
    swUI32 FindInB(const char * str);
    bool Size(swUI32 size);
    swUI32 GetCount();

protected:
    bool Grow();
    SwStringPair * m_array;
    swUI32     m_size;
    swUI32     m_count;
};

class SOWERBASEEXP SwStringTripletArray
{
public:
    SwStringTripletArray();
    virtual ~SwStringTripletArray();

    void Reset();
    void ShiftUp(swUI32 start);
    bool ShiftDown(swUI32 start);
    swUI32 Add(const char * strA, const char * strB, const char * strC);
    bool Delete(swUI32 pos);
    bool Insert(swUI32 nodePos, const char * strA, const char * strB, const char * strC);
    SwStringTriplet & GetAt(swUI32 pos);
    swUI32 FindInA(const char * str);
    swUI32 FindInB(const char * str);
    swUI32 FindInC(const char * str);
    bool Size(swUI32 size);
    swUI32 GetCount();

protected:
    bool Grow();
    SwStringTriplet * m_array;
    swUI32     m_size;
    swUI32     m_count;
};

#endif // STRINGARRAY_H
