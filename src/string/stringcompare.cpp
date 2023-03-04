///////////////////////////////////////////////////////////////////
// Name:        stringcompare.cpp
// Purpose:     Text search based on keyword-s, phrase, boolean operators.
//              Options - case sensitive, and whole word only.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/string/stringcompare.h"

SwStringCompare::SwStringCompare()
{
    m_searchString = NULL;
    m_keyWords = 0;
}

SwStringCompare::~SwStringCompare()
{
}

swI8 SwStringCompare::ParseSearchString(const char * dataString, swI8 flags)
{
    // Boolean operatives
    // AND - *
    // OR  - +
    // NOT - !

    if (!dataString)
        return CR_OP_FAILED;

    m_buffer = dataString;
    m_original = dataString;

    int readPos, keywordStart, dataLen = strlen(dataString);
    swI8 status, keywordsFound, lastOperator = KT_AND;
    bool isFoundWord = false;
    char * psz, * pszString;
    bool validOperator = false;

    m_searchString = m_buffer;

    if (flags & CF_NOCASE)
        strlwr(m_searchString);

    m_flags = flags;
    keywordsFound = 0;
    keywordStart = -1;
    status = CR_OP_OK;

    if (m_flags & CF_PHRASE)
    {
        m_keyWords = 1;
        m_keyIndex[0] = 0;
        m_keyTypeArray[0] = KT_WORD;
        return status;
    }

    while (m_searchString[0] == ' ')
    {
        m_searchString ++;
        m_original.Delete(0, 1);
        dataLen --;
    }

    readPos = dataLen -1;

    while (m_searchString[readPos] == ' ')
    {
        m_searchString[readPos] = '\0';
        m_original[readPos] = '\0';
        dataLen --;
        readPos --;
    }

    pszString = m_searchString;
    readPos = -1;

    while (readPos < dataLen)
    {
        readPos ++;

        if (pszString[readPos] == ' ')
        {
            keywordStart = -1;
            pszString[readPos] = '\0';
            m_original[readPos] = '\0';
            continue;
        }
        else if (keywordStart < 0)
        {
            if (keywordsFound >= MAX_KEYS)
            {
                status = CR_KEYS_EXCEEDED_MAX;
                break;
            }

            keywordStart = readPos;
            m_keyIndex[keywordsFound] = readPos;
            keywordsFound ++;
        }
    }

    readPos = 0;
    while (readPos < keywordsFound)
    {
        psz = &pszString[m_keyIndex[readPos]];
        if (m_flags & CF_BOOLEAN)
        {
            if (stricmp(psz, "and") == 0 || stricmp(psz, "*") == 0)
            {
                m_keyTypeArray[readPos] = KT_AND;
                lastOperator = KT_AND;
            }
            else if (stricmp(psz, "or") == 0 || stricmp(psz, "+") == 0)
            {
                m_keyTypeArray[readPos] = KT_OR;
                lastOperator = KT_OR;
            }
            else if (stricmp(psz, "not") == 0 || stricmp(psz, "!") == 0)
            {
                m_keyTypeArray[readPos] = KT_NOT;
                lastOperator = KT_NOT;
            }
            else if (strlen(psz) < 1)
                m_keyTypeArray[readPos] = KT_INVALID;
            else
            {
                m_keyTypeArray[readPos] = KT_WORD;
                isFoundWord = true;
                if (validOperator == false)
                {
                    if (lastOperator != KT_NOT)
                        validOperator = true;
                }
            }
        }
        else
        {
            if (strlen(psz) < 1)
                m_keyTypeArray[readPos] = KT_INVALID;
            else
            {
                m_keyTypeArray[readPos] = KT_WORD;
                isFoundWord = true;
            }
        }

        readPos ++;
    }

    if (isFoundWord != true)
        return CR_INVALID_STRING;

    if ((m_flags & CF_BOOLEAN) && (validOperator != true))
        return CR_INVALID_STRING;

    m_keyWords = keywordsFound;
    return status;
}

swI8 SwStringCompare::EvaluateBooleanExpression()
{
    swI8 count = 0;
    swI8 lastwordState = 1;
    swI8 previousOperator = KT_AND;
    swI8 currentOperator = KT_AND;
    bool needOr = false;

    while (count < m_keyWords)
    {
        if (m_keyTypeArray[count] == KT_AND || m_keyTypeArray[count] == KT_OR || m_keyTypeArray[count] == KT_NOT)
        {
            previousOperator = currentOperator;
            currentOperator = m_keyTypeArray[count];

            if (needOr && currentOperator != KT_OR)
                return CR_EXPRESSION_FAILED;

            count ++;
            continue;
        }
        else if (m_keyTypeArray[count] == KT_INVALID)
        {
            count ++;
            continue;
        }

        if (currentOperator == KT_NOT)
        {
            if (m_keyStateArray[count] == 1)
                return CR_EXPRESSION_FAILED;
        }
        else if (currentOperator == KT_AND)
        {
            if (lastwordState == 0
                    && previousOperator != KT_NOT
                    && previousOperator != KT_OR)
                return CR_EXPRESSION_FAILED;

            if (m_keyStateArray[count] == 0)
                needOr = true;
            else
                m_isFound = true;
        }
        else if (currentOperator == KT_OR)
        {
            if (m_keyStateArray[count] == 1)
            {
                m_isFound = true;

                if (needOr)
                    needOr = 0;
            }
        }

        lastwordState = m_keyStateArray[count];
        count ++;
    }

    if (needOr)
        return CR_EXPRESSION_FAILED;

    return CR_EXPRESSION_PASSED;
}

swI8 SwStringCompare::GetKeyWordType(swI8 index)
{
    if (index >= m_keyWords)
        return CR_KEYS_EXCEEDED_MAX;

    return m_keyTypeArray[index];
}

swI8 SwStringCompare::GetKeyWord(char * buff, swI8 index, swUI32 bufferSize)
{
    if (index >= m_keyWords)
        return CR_KEYS_EXCEEDED_MAX;
    else if (m_keyTypeArray[index] != KT_WORD)
        return CR_INVALID_STRING;

    if (!m_searchString || strlen(&m_searchString[m_keyIndex[index]]) >= bufferSize)
        return CR_OP_FAILED;

    strcpy(buff, &m_searchString[m_keyIndex[index]]);
    return CR_OP_OK;
}

const char * SwStringCompare::GetKeyWord(swI8 index)
{
    if (index >= m_keyWords)
        return NULL;
    else if (m_keyTypeArray[index] != KT_WORD)
        return NULL;

    return &m_searchString[m_keyIndex[index]];
}

const char * SwStringCompare::GetKeyWordOriginal(swI8 index)
{
    if (index >= m_keyWords)
        return NULL;
    else if (m_keyTypeArray[index] != KT_WORD)
        return NULL;

    return &m_original[m_keyIndex[index]];
}

swI8 SwStringCompare::GetKeyWords()
{
    return m_keyWords;
}

swI8 SwStringCompare::SearchBuffer(char * pszSearch)
{

    int indexPos = 0;
    swI8 status;
    m_isFound = false;

    memset(m_keyStateArray, 0, MAX_KEYS);

    if (m_flags & CF_NOCASE)
        strlwr(pszSearch);

    if (m_flags & CF_PHRASE)
    {
        return FindMatch(pszSearch, m_searchString);
    }
    else if (m_flags & CF_ANY)
    {
        indexPos = 0;
        while (indexPos < m_keyWords)
        {
            if (FindMatch(pszSearch, &m_searchString[m_keyIndex[indexPos]]) == CR_EXPRESSION_PASSED)
                return CR_EXPRESSION_PASSED;

            indexPos ++;
        }

        return CR_EXPRESSION_FAILED;
    }
    else if (m_flags & CF_ALL)
    {
        indexPos = 0;

        while (indexPos < m_keyWords)
        {
            if (FindMatch(pszSearch, &m_searchString[m_keyIndex[indexPos]]) == CR_EXPRESSION_FAILED)
                return CR_EXPRESSION_FAILED;

            indexPos ++;
        }

        return CR_EXPRESSION_PASSED;
    }
    else if (m_flags & CF_BOOLEAN)
    {
        indexPos = 0;
        while (indexPos < m_keyWords)
        {
            if (m_keyTypeArray[indexPos] != KT_WORD)
            {
                indexPos ++;
                continue;
            }

            if (m_keyStateArray[indexPos] == 1)
            {
                indexPos ++;
                continue;
            }

            if (FindMatch(pszSearch, &m_searchString[m_keyIndex[indexPos]]) == CR_EXPRESSION_PASSED)
            {
                m_keyStateArray[indexPos] = 1;
            }

            indexPos ++;
        }

        status = EvaluateBooleanExpression();

        if (status == CR_EXPRESSION_FAILED)
            return CR_EXPRESSION_FAILED;
        else if (status == CR_EXPRESSION_PASSED)
        {
            if (m_isFound == true)
                return CR_EXPRESSION_PASSED;
        }
    }

    return CR_EXPRESSION_FAILED;
}

swI8 SwStringCompare::FindMatch(char * string, char * word)
{
    char * p = string;
    unsigned int len = strlen(word);

    while(p != NULL)
    {
        p = strstr(p, word);

        if (p)
        {
            if (m_flags & CF_WORD)
            {
                if (isspace(p[len]) || p[len] == '\0' || ispunct(p[len]))
                {
                    if (p == string)
                        return CR_EXPRESSION_PASSED;
                    else if (isspace(p[-1]))
                        return CR_EXPRESSION_PASSED;
                }
            }
            else
                return CR_EXPRESSION_PASSED;
        }
        else
            break;

        p += len;
    }

    return CR_EXPRESSION_FAILED;
}

bool SwStringCompare::IsModeWord()
{
    if (m_flags & CF_WORD)
        return true;

    return false;
}

bool SwStringCompare::IsModeCaseSensitive()
{
    if (m_flags & CF_NOCASE)
        return false;

    return true;
}


SwStringCompareW::SwStringCompareW()
{
    m_searchString = NULL;
    m_keyWords = 0;
}

SwStringCompareW::~SwStringCompareW()
{
}

swI8 SwStringCompareW::ParseSearchString(const wchar_t * dataString, swI8 flags)
{
    // Boolean operatives
    // AND - *
    // OR  - +
    // NOT - !

    if (!dataString)
        return CR_OP_FAILED;

    m_buffer = dataString;
    m_original = dataString;
    m_searchString = NULL;

    int readPos, keywordStart, dataLen = wcslen(dataString);
    swI8 status, keywordsFound, lastOperator = KT_AND;
    bool isFoundWord = false;
    wchar_t * psz, * pszString;
    bool validOperator = false;

    m_searchString = m_buffer;

    if (flags & CF_NOCASE)
        wcslwr(m_searchString);

    m_flags = flags;
    keywordsFound = 0;
    keywordStart = -1;
    status = CR_OP_OK;

    if (m_flags & CF_PHRASE)
    {
        m_keyWords = 1;
        m_keyIndex[0] = 0;
        m_keyTypeArray[0] = KT_WORD;
        return status;
    }

    while (m_searchString[0] == L' ')
    {
        m_searchString ++;
        m_original.Delete(0, 1);
        dataLen --;
    }

    readPos = dataLen -1;

    while (m_searchString[readPos] == L' ')
    {
        m_searchString[readPos] = L'\0';
        m_original[readPos] = L'\0';
        dataLen --;
        readPos --;
    }

    pszString = m_searchString;
    readPos = -1;

    while (readPos < dataLen)
    {
        readPos ++;

        if (pszString[readPos] == L' ')
        {
            keywordStart = -1;
            pszString[readPos] = L'\0';
            m_original[readPos] = L'\0';
            continue;
        }
        else if (keywordStart < 0)
        {
            if (keywordsFound >= MAX_KEYS)
            {
                status = CR_KEYS_EXCEEDED_MAX;
                break;
            }

            keywordStart = readPos;
            m_keyIndex[keywordsFound] = readPos;
            keywordsFound ++;
        }
    }

    readPos = 0;
    while (readPos < keywordsFound)
    {
        psz = &pszString[m_keyIndex[readPos]];
        if (m_flags & CF_BOOLEAN)
        {
            if (wcsicmp(psz, L"and") == 0 || wcsicmp(psz, L"*") == 0)
            {
                m_keyTypeArray[readPos] = KT_AND;
                lastOperator = KT_AND;
            }
            else if (wcsicmp(psz, L"or") == 0 || wcsicmp(psz, L"+") == 0)
            {
                m_keyTypeArray[readPos] = KT_OR;
                lastOperator = KT_OR;
            }
            else if (wcsicmp(psz, L"not") == 0 || wcsicmp(psz, L"!") == 0)
            {
                m_keyTypeArray[readPos] = KT_NOT;
                lastOperator = KT_NOT;
            }
            else if (wcslen(psz) < 1)
                m_keyTypeArray[readPos] = KT_INVALID;
            else
            {
                m_keyTypeArray[readPos] = KT_WORD;
                isFoundWord = true;
                if (validOperator == false)
                {
                    if (lastOperator != KT_NOT)
                        validOperator = true;
                }
            }
        }
        else
        {
            if (wcslen(psz) < 1)
                m_keyTypeArray[readPos] = KT_INVALID;
            else
            {
                m_keyTypeArray[readPos] = KT_WORD;
                isFoundWord = true;
            }
        }

        readPos ++;
    }

    if (isFoundWord != true)
        return CR_INVALID_STRING;

    if ((m_flags & CF_BOOLEAN) && (validOperator != true))
        return CR_INVALID_STRING;

    m_keyWords = keywordsFound;
    return status;
}

swI8 SwStringCompareW::EvaluateBooleanExpression()
{
    swI8 count = 0;
    swI8 lastwordState = 1;
    swI8 previousOperator = KT_AND;
    swI8 currentOperator = KT_AND;
    bool needOr = false;

    while (count < m_keyWords)
    {
        if (m_keyTypeArray[count] == KT_AND || m_keyTypeArray[count] == KT_OR || m_keyTypeArray[count] == KT_NOT)
        {
            previousOperator = currentOperator;
            currentOperator = m_keyTypeArray[count];

            if (needOr && currentOperator != KT_OR)
                return CR_EXPRESSION_FAILED;

            count ++;
            continue;
        }
        else if (m_keyTypeArray[count] == KT_INVALID)
        {
            count ++;
            continue;
        }

        if (currentOperator == KT_NOT)
        {
            if (m_keyStateArray[count] == 1)
                return CR_EXPRESSION_FAILED;
        }
        else if (currentOperator == KT_AND)
        {
            if (lastwordState == 0
                    && previousOperator != KT_NOT
                    && previousOperator != KT_OR)
                return CR_EXPRESSION_FAILED;

            if (m_keyStateArray[count] == 0)
                needOr = true;
            else
                m_isFound = true;
        }
        else if (currentOperator == KT_OR)
        {
            if (m_keyStateArray[count] == 1)
            {
                m_isFound = true;

                if (needOr)
                    needOr = 0;
            }
        }

        lastwordState = m_keyStateArray[count];
        count ++;
    }

    if (needOr)
        return CR_EXPRESSION_FAILED;

    return CR_EXPRESSION_PASSED;
}

swI8 SwStringCompareW::GetKeyWordType(swI8 index)
{
    if (index >= m_keyWords)
        return CR_KEYS_EXCEEDED_MAX;

    return m_keyTypeArray[index];
}

swI8 SwStringCompareW::GetKeyWord(wchar_t * buff, swI8 index, swUI32 bufferSize)
{
    if (index >= m_keyWords)
        return CR_KEYS_EXCEEDED_MAX;
    else if (m_keyTypeArray[index] != KT_WORD)
        return CR_INVALID_STRING;

    if (!m_searchString || wcslen(&m_searchString[m_keyIndex[index]]) >= bufferSize)
        return CR_OP_FAILED;

    wcscpy(buff, &m_searchString[m_keyIndex[index]]);
    return CR_OP_OK;
}

const wchar_t * SwStringCompareW::GetKeyWord(swI8 index)
{
    if (index >= m_keyWords)
        return NULL;
    else if (m_keyTypeArray[index] != KT_WORD)
        return NULL;

    return &m_searchString[m_keyIndex[index]];
}

const wchar_t * SwStringCompareW::GetKeyWordOriginal(swI8 index)
{
    if (index >= m_keyWords)
        return NULL;
    else if (m_keyTypeArray[index] != KT_WORD)
        return NULL;

    return &m_original[m_keyIndex[index]];
}

swI8 SwStringCompareW::GetKeyWords()
{
    return m_keyWords;
}

swI8 SwStringCompareW::SearchBuffer(wchar_t * pszSearch)
{
    int indexPos = 0;
    swI8 status;
    m_isFound = false;

    memset(m_keyStateArray, 0, MAX_KEYS);

    if (m_flags & CF_NOCASE)
        wcslwr(pszSearch);

    if (m_flags & CF_PHRASE)
    {
        return FindMatch(pszSearch, m_searchString);
    }
    else if (m_flags & CF_ANY)
    {
        indexPos = 0;
        while (indexPos < m_keyWords)
        {
            if (FindMatch(pszSearch, &m_searchString[m_keyIndex[indexPos]]) == CR_EXPRESSION_PASSED)
                return CR_EXPRESSION_PASSED;

            indexPos ++;
        }

        return CR_EXPRESSION_FAILED;
    }
    else if (m_flags & CF_ALL)
    {
        indexPos = 0;

        while (indexPos < m_keyWords)
        {
            if (FindMatch(pszSearch, &m_searchString[m_keyIndex[indexPos]]) == CR_EXPRESSION_FAILED)
                return CR_EXPRESSION_FAILED;

            indexPos ++;
        }

        return CR_EXPRESSION_PASSED;
    }
    else if (m_flags & CF_BOOLEAN)
    {
        indexPos = 0;
        while (indexPos < m_keyWords)
        {
            if (m_keyTypeArray[indexPos] != KT_WORD)
            {
                indexPos ++;
                continue;
            }

            if (m_keyStateArray[indexPos] == 1)
            {
                indexPos ++;
                continue;
            }

            if (FindMatch(pszSearch, &m_searchString[m_keyIndex[indexPos]]) == CR_EXPRESSION_PASSED)
            {
                m_keyStateArray[indexPos] = 1;
            }

            indexPos ++;
        }

        status = EvaluateBooleanExpression();

        if (status == CR_EXPRESSION_FAILED)
            return CR_EXPRESSION_FAILED;
        else if (status == CR_EXPRESSION_PASSED)
        {
            if (m_isFound == true)
                return CR_EXPRESSION_PASSED;
        }
    }

    return CR_EXPRESSION_FAILED;
}

swI8 SwStringCompareW::FindMatch(wchar_t * string, wchar_t * word)
{
    wchar_t * p = string;
    unsigned int len = wcslen(word);

    while(p != NULL)
    {
        p = wcsstr(p, word);

        if (p)
        {
            if (m_flags & CF_WORD)
            {
                if (iswspace(p[len]) || p[len] == L'\0' || iswpunct(p[len]))
                {
                    if (p == string)
                        return CR_EXPRESSION_PASSED;
                    else if (iswspace(p[-1]))
                        return CR_EXPRESSION_PASSED;
                }
            }
            else
                return CR_EXPRESSION_PASSED;
        }
        else
            break;

        p += len;
    }

    return CR_EXPRESSION_FAILED;
}

bool SwStringCompareW::IsModeWord()
{
    if (m_flags & CF_WORD)
        return true;

    return false;
}

bool SwStringCompareW::IsModeCaseSensitive()
{
    if (m_flags & CF_NOCASE)
        return false;

    return true;
}
