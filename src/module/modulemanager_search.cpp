///////////////////////////////////////////////////////////////////
// Name:        modulemanager_search.cpp
// Purpose:     Search routines for SwModuleManager.
// Copyright:   David Reynolds
///////////////////////////////////////////////////////////////////

#include "../../include/module/modulemanager.h"
#include "../../include/appi/appifa.h"
#include "../../include/html/html.h"

bool SwModuleManager::Search(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    idArray += managerId;
    return Search(idArray, stringcomp, searchCallback);
}

bool SwModuleManager::Search(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    AddModuleIdByCategory(idArray, category);
    return Search(idArray, stringcomp, searchCallback);
}

bool SwModuleManager::Search(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    swUI8 lastChar;
    SwModule * module;
    SwString sb1, sb2;
    SwStringW sb3, t1, t2;

    for (swUI16 i = 0; i < idArray.GetCount(); i ++)
    {
        module = GetAt(idArray.GetAt(i));
        for (swUI16 tocPos = 0; tocPos < module->GetTableofContents().GetNodes(); tocPos ++)
        {
            sb1.SetCount(0);
            module->GetTableofContents().GetNode(tocPos)->ReadData(module->m_file, sb1, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted);
            sb2.Size(sb1.GetCount() + 1);
            lastChar = LCH_BREAK;
            SwHtml::Html2Text(sb1, sb2, sb2.GetSize(), lastChar, true);
            sb3.Copy(sb2);

            if (stringcomp.SearchBuffer(sb3) == CR_EXPRESSION_PASSED)
            {
                t1.Copy(module->m_header.moduleAbbreviation);
                module->GetTableofContents().GetTitle(tocPos, sb1);
                t2.Copy(sb1);
                t1 += L" ";
                t1 += t2;
                if (!searchCallback.Result(module->m_managerId, module->GetTableofContents().GetIdentifier(tocPos), t1.GetArray(), module->m_header.canCopy))
                    return false;
            }
        }
    }

   return true;
}

bool SwModuleManager::SearchEx(swUI16 managerId, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    idArray += managerId;
    return SearchEx(idArray, stringcomp, searchCallback);
}

bool SwModuleManager::SearchEx(swUI8 category, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    Swui16Array idArray;
    AddModuleIdByCategory(idArray, category);
    return SearchEx(idArray, stringcomp, searchCallback);
}

bool SwModuleManager::SearchEx(Swui16Array & idArray, SwStringCompareW & stringcomp, SwSearchCallBack & searchCallback)
{
    SwStringW translation;
    SwModuleItemArray itemData;
    swUI8 lastChar;
    SwModule * module;
    SwModuleItemId identifier;
    wchar_t a[17];
    SwString sb1, sb2;
    SwStringW sb3, t1, t2;

    translation = SwApplicationInterface::GetControlString("SID_PARAGRAPH", L"paragraph");

    for (swUI16 i = 0; i < idArray.GetCount(); i ++)
    {
        module = GetAt(idArray.GetAt(i));

        if (!module)
            return false;

        for (swUI16 tocPos = 0; tocPos < module->GetTableofContents().GetNodes(); tocPos ++)
        {
            identifier = module->GetTableofContents().GetIdentifier(tocPos);
            module->GetItemData(itemData, identifier);
            sb1.SetCount(0);
            module->GetTableofContents().GetNode(tocPos)->ReadData(module->m_file, sb1, module->m_header.itemdataLocator, module->m_header.filecontentsLocator, module->m_header.k1, module->m_header.k2, module->m_header.isEncrypted);

            for(swUI16 itemPos = 1; itemPos < itemData.GetAt(itemPos).divItems; itemPos ++)
            {
                sb2.Size(itemData.GetAt(itemPos).size + 1);
                lastChar = LCH_BREAK;
                SwHtml::Html2Text(itemData.GetAt(itemPos).size, sb1 + (itemData.GetAt(itemPos).position - itemData.GetAt(0).position), sb2, sb2.GetSize(), lastChar, true);
                sb3.Copy(sb2);

                if (stringcomp.SearchBuffer(sb3) == CR_EXPRESSION_PASSED)
                {
                    t1.Copy(module->m_header.moduleAbbreviation);
                    module->GetTableofContents().GetTitle(tocPos, sb1);
                    t2.Copy(sb1);
                    t1 += L" ";
                    t1 += t2;

                    if (itemData.GetAt(itemPos).type == THML_SCRIPTURE)
                    {
                        t1 += L" :";
                        #if defined __MSWIN__
                        swprintf(a, L"%u", itemData.GetAt(itemPos).verseStart);
                        #else
                        swprintf(a, 17, L"%u", itemData.GetAt(itemPos).verseStart);
                        #endif
                        t1 += a;
                    }
                    else if (itemData.GetAt(itemPos).type == THML_SCRIPCOM)
                    {
                        if (itemData.GetAt(itemPos).verseEnd > itemData.GetAt(itemPos).verseStart)
                        {
                            t1 += L" :";
                            #if defined __MSWIN__
                            swprintf(a, L"%u - %u", itemData.GetAt(itemPos).verseStart, itemData.GetAt(itemPos).verseEnd);
                            #else
                            swprintf(a, 17, L"%u - %u", itemData.GetAt(itemPos).verseStart, itemData.GetAt(itemPos).verseEnd);
                            #endif
                            t1 += a;
                        }
                        else
                        {
                            t1 += L" :";
                            #if defined __MSWIN__
                            swprintf(a, L"%u", itemData.GetAt(itemPos).verseStart);
                            #else
                            swprintf(a, 17, L"%u", itemData.GetAt(itemPos).verseStart);
                            #endif
                            t1 += a;
                        }
                    }
                    else
                    {
                        t1 += L" ";
                        t1 += translation;

                        #if defined __MSWIN__
                        swprintf(a, L" %u", itemPos);
                        #else
                        swprintf(a, 17, L" %u", itemPos);
                        #endif
                        t1 += a;
                    }

                    if (!searchCallback.Result(module->m_managerId, module->GetTableofContents().GetIdentifier(tocPos), t1, module->m_header.canCopy))
                        return false;
                }
            }
        }
    }

   return true;
}
