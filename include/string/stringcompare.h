///////////////////////////////////////////////////////////////////
// Name:        stringcompare.h
// Purpose:     Text search based on keyword-s, phrase, boolean operators.
//              Options - case sensitive, and whole word only.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef STRINGCOMPARE_H
#define STRINGCOMPARE_H

#include "../sowerbase.h"
#include "string.h"
#include "stringw.h"

// Comparison Flags
enum STRING_COMPARE_FLAGS
{
    CF_PHRASE	= 0x01,
    CF_ANY		= 0x02,
    CF_ALL		= 0x04,
    CF_BOOLEAN	= 0x08,
    CF_WORD	    = 0x10,
    CF_NOCASE	= 0x20
};

enum STRING_COMPARE_KEY_TYPES
{
    KT_INVALID, KT_WORD, KT_AND, KT_OR, KT_NOT
};

enum STRING_COMPARE_RETURN_CODES
{
    CR_OP_OK = 1,
    CR_EXPRESSION_PASSED,
    CR_EXPRESSION_FAILED,
    CR_KEYS_EXCEEDED_MAX,
    CR_INVALID_STRING,
    CR_EXPRESSION_INDETERMINATE,
    CR_OP_FAILED
};

#define MAX_KEYS 127

class SOWERBASEEXP SwStringCompare
{
public:
    SwStringCompare();
    virtual ~SwStringCompare();
    swI8 ParseSearchString(const char * dataString, swI8 flags);
    swI8 EvaluateBooleanExpression();
    swI8 GetKeyWord(char * buff, swI8 index, swUI32 bufferSize);
    swI8 GetKeyWordType(swI8 index);
    const char * GetKeyWord(swI8 index);
    const char * GetKeyWordOriginal(swI8 index);
    swI8 GetKeyWords();
    swI8 SearchBuffer(char * pszSearch);
    swI8 FindMatch(char * string, char * word);
    bool IsModeWord();
    bool IsModeCaseSensitive();

protected:
    char *	  m_searchString;
    swI8	  m_keyWords;
    swUI16    m_keyIndex[MAX_KEYS];
    swI8	  m_keyTypeArray[MAX_KEYS];
    swI8	  m_keyStateArray[MAX_KEYS];
    swI8	  m_flags;
    bool	  m_isFound;
    SwString  m_buffer;
    SwString  m_original;
};


class SOWERBASEEXP SwStringCompareW
{
public:
    SwStringCompareW();
    virtual ~SwStringCompareW();
    swI8 ParseSearchString(const wchar_t * dataString, swI8 flags);
    swI8 EvaluateBooleanExpression();
    swI8 GetKeyWord(wchar_t * buff, swI8 index, swUI32 bufferSize);
    swI8 GetKeyWordType(swI8 index);
    const wchar_t * GetKeyWord(swI8 index);
    const wchar_t * GetKeyWordOriginal(swI8 index);
    swI8 GetKeyWords();
    swI8 SearchBuffer(wchar_t * pszSearch);
    swI8 FindMatch(wchar_t * string, wchar_t * word);
    bool IsModeWord();
    bool IsModeCaseSensitive();

protected:
    wchar_t *  m_searchString;
    swI8	   m_keyWords;
    swUI16     m_keyIndex[MAX_KEYS];
    swI8	   m_keyTypeArray[MAX_KEYS];
    swI8	   m_keyStateArray[MAX_KEYS];
    swI8	   m_flags;
    bool	   m_isFound;
    SwStringW  m_buffer;
    SwStringW  m_original;
};

#endif // STRINGCOMPARE_H
