///////////////////////////////////////////////////////////////////
// Name:        thmlfilemanager_search.cpp
// Purpose:     Search routines for SwThMLFileManager.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/thml/thmlfilemanager.h"
#include "../../include/appi/appifa.h"
#include "../../include/html/html.h"

bool SwThMLFileManager::Search(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    idArray += managerId;
    return Search(idArray, stringcomp, searchCallback);
}

bool SwThMLFileManager::Search(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    AddFileIdByCategory(idArray, category);
    return Search(idArray, stringcomp, searchCallback);
}

bool SwThMLFileManager::Search(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    swUI8 lastChar;
    SwThMLFile * file;
    SwString sb1, sb2;
    SwStringW sb3;

    for (swUI16 i = 0; i < idArray.GetCount(); i ++)
    {
        file = GetAt(idArray.GetAt(i));
        for (swUI16 tocPos = 0; tocPos < file->GetTableofContents().GetNodes(); tocPos ++)
        {
            sb1.SetCount(0);
            file->GetTableofContents().GetNode(tocPos)->ReadData(file->m_file, sb1);
            sb2.Size(sb1.GetCount());
            lastChar = LCH_BREAK;
            SwHtml::Html2Text(sb1, sb2, sb2.GetSize(), lastChar, true);
            sb3.Copy(sb2);

            if (stringcomp.SearchBuffer(sb3.GetArray()) == CR_EXPRESSION_PASSED)
            {
                sb1.Copy(file->GetAbbreviation());
                file->GetTableofContents().GetTitle(tocPos, sb2);
                sb1 += " ";
                sb1 += sb2;
                sb3.Copy(sb1);

                if (!searchCallback.Result(file->m_managerId, tocPos, sb3, true))
                    return false;
            }
        }
    }

   return true;
}

bool SwThMLFileManager::SearchEx(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    idArray += managerId;
    return SearchEx(idArray, stringcomp, searchCallback);
}

bool SwThMLFileManager::SearchEx(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    AddFileIdByCategory(idArray, category);
    return SearchEx(idArray, stringcomp, searchCallback);
}

bool SwThMLFileManager::SearchEx(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    swUI8 lastChar;
    SwThMLFile * file;
    SwString sb1, sb2;
    SwStringW sb3;

    for (swUI16 i = 0; i < idArray.GetCount(); i ++)
    {
        file = GetAt(idArray.GetAt(i));

        if (!file)
            return false;

        for (swUI16 tocPos = 0; tocPos < file->GetTableofContents().GetNodes(); tocPos ++)
        {
            sb1.SetCount(0);
            file->GetTableofContents().GetNode(tocPos)->ReadData(file->m_file, sb1);
            sb2.Size(file->GetTableofContents().GetNode(tocPos)->fileSize + 1);
            lastChar = LCH_BREAK;
            SwHtml::Html2Text(file->GetTableofContents().GetNode(tocPos)->fileSize, sb1, sb2, sb2.GetSize(), lastChar, true);
            sb3.Copy(sb2);

            if (stringcomp.SearchBuffer(sb3) == CR_EXPRESSION_PASSED)
            {
                sb1.Copy(file->m_abbrev);
                file->GetTableofContents().GetTitle(tocPos, sb2);
                sb1 += " ";
                sb1 += sb2;
                sb3.Copy(sb1);

                if (!searchCallback.Result(file->m_managerId, tocPos, sb3, true))
                    return false;
            }
        }
    }

   return true;
}
