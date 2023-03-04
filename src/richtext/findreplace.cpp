///////////////////////////////////////////////////////////////////
// Name:        findreplace.cpp
// Purpose:     Find/Replace functionality for wxRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/findreplace.h"

SwFindReplace::SwFindReplace()
{
    m_rich = NULL;
    m_ignoreCase = true;
    m_wholewordOnly = false;
    m_findtextLength = 0;
    m_replacetextLength = 0;
    Reset();
    m_foundList.Size(100);
    m_collection.Alloc(7000);
    m_collectionLwr.Alloc(7000);
    m_rangeData.Alloc(200);
}

SwFindReplace::~SwFindReplace()
{
}

void SwFindReplace::SetParent(wxRichTextCtrl * rich)
{
    // Set the wxRichTextCtrl that this object will
    // operate on.
    m_rich = rich;
}

void SwFindReplace::SetFindText(wxString text)
{
    // Set text to be found.
    // Store length now to avoid multiple calls
    // to Len. Copy and convert copy to lower case
    // for case insensitive operations keeping
    // the original intact for case sensitive operations.
    m_findTextOriginal = text;
    m_findText = text;
    m_findText.MakeLower();
    m_findtextLength = m_findText.Len();
}

void SwFindReplace::SetReplaceText(wxString text)
{
    // Set text to be used replacing find text.
    // Store length now to avoid multiple calls
    // to Len.
    m_replaceText = text;
    m_replacetextLength = m_replaceText.Len();
}

void SwFindReplace::SetCaseSensitive(bool caseSensitive)
{
    // True to compare with case sensitivity.
    if (caseSensitive)
        m_ignoreCase = false;
    else
        m_ignoreCase = true;
}

void SwFindReplace::SetWholeWordOnly(bool wholewordOnly)
{
    // True for whole word only matches.
    m_wholewordOnly = wholewordOnly;
}

void SwFindReplace::SetScrollView(bool scrollView)
{
    // True for scrolling matches into view.
    m_scrollView = scrollView;
}

void SwFindReplace::SetFindAll(bool findAll)
{
    m_findAll = findAll;
}

void SwFindReplace::Reset()
{
    // This must not be called from within IterateBuffer.
    // Init sets m_continue to false and will cause (Next)
    // operations to always begin at the beginning of the
    // buffer.
    m_topParent = NULL;
    m_parent = NULL;
    m_found = NULL;
    m_endofFind = -1;
    m_continue = false;
    m_rangeData.Empty();
    m_collection = "";
    m_collectionLwr = "";
    m_replaceAll = false;
    m_scrollView = true;
    m_findAll = false;
    m_foundList.Reset();
    m_break = false;
    m_currentFind = -1;
    m_previousFind = -1;
}

bool SwFindReplace::IterateBuffer(wxRichTextCompositeObject * obj)
{
    if (m_break)
    {
        m_break = false;
        return false;
    }

    // Start
    if (obj)
    {
        return IterateObj(obj);
    }

    bool status = IterateObj(wxDynamicCast(&m_rich->GetBuffer(), wxRichTextCompositeObject));

    if (!status)
        m_break = true;

    return status;
}

bool SwFindReplace::IterateObj(wxRichTextCompositeObject * obj)
{
    bool status;
    wxRichTextParagraphLayoutBox *  topParent;

    // Step through the object list, any
    // wxRichTextCompositeObject, or those derived from
    // it may have children and must start a new iteration
    // branch. But, no other object types.
    wxRichTextObjectList::compatibility_iterator node = obj->GetChildren().GetFirst();

    while (node)
    {
        wxRichTextObject* obj = node->GetData();

        if (obj->IsKindOf(CLASSINFO(wxRichTextCompositeObject)))
        {
            topParent = m_topParent;
            if (obj->IsKindOf(CLASSINFO(wxRichTextParagraphLayoutBox)))
            {
                OnLayoutBox(wxDynamicCast(obj, wxRichTextParagraphLayoutBox));
            }
            else if (obj->IsKindOf(CLASSINFO(wxRichTextParagraph)))
            {
                OnParagraph(wxDynamicCast(obj, wxRichTextParagraph));
            }

            // Iterate through the children of this object.
            status = IterateObj(wxDynamicCast(obj, wxRichTextCompositeObject));

            if (topParent != m_topParent)
                OnLayoutBox(topParent);

            if (status)
                return true;
        }
        else if (obj->IsKindOf(CLASSINFO(wxRichTextPlainText)))
        {
            // Add text from object and compare
            // text in m_collection to find data.
            if (OnText(obj))
            {
                // Found text.
                if (m_replaceAll)
                {
                    // If replace mode, replace and
                    // continue.
                    Replace();
                    FindNext();
                }
                else if (m_findAll)
                {
                    FindNext();
                }
                else
                {
                    // Fix for bug where find sometimes
                    // identifies previous find.

                    if (m_currentFind <= m_previousFind)
                    {
                        FindNext();
                    }

                    m_previousFind = m_currentFind;

                    return true;
                }

            }

        }

        node = node->GetNext();
    }

    return false;
}

bool SwFindReplace::OnText(wxRichTextObject * obj)
{
    int result;
    long selEnd;

    if (m_continue && obj != m_found)
    {
        // Continue operation but,
        // not previous object so skip it.
        return false;
    }

    // Object parent different than previous object
    // so this text is not part of the text of
    // the previous object. Something separates text
    // currently in the collection and the text from
    // this object, and if find text has not been found
    // in m_collection then it is no longer valid.
    // Empty buffer, update object data, etc.
    if (obj->GetParent() != m_parent)
    {
        m_rangeData.Empty();
        m_collection = "";
        m_collectionLwr = "";

        if (obj->GetParent())
            m_parent = wxDynamicCast(obj->GetParent(), wxRichTextParagraph);
        else
            m_parent = NULL;

        if (m_parent)
            m_topParent = wxDynamicCast(m_parent->GetParent(), wxRichTextParagraphLayoutBox);
    }

    // Get objects text, start position etc.
    wxString temp;
    m_rangeData.Add(obj->GetRange().GetStart());
    temp = obj->GetTextForRange(obj->GetRange());

    // Add to collection of text that maybe represented
    // by multiple RichTextPlainText objects.
    // This may or may not be the first text in the buffer.
    m_collection += temp;
    temp.MakeLower();
    m_collectionLwr += temp;

    // Find text if it exists in m_collection.
    result = FindWord();

    // Flag must be reset or this function will
    // skip objects down the list on subsequent
    // operations.
    m_continue = false;

    if (result != wxNOT_FOUND)
    {
        // Find Text has been found.
        // Update m_found so Next operations will
        // skip all objects until this one is found
        // and all occurrences of find text have been
        // marked.
        m_found = obj;
        selEnd = m_rangeData[0] + result + m_findtextLength;
        // Set m_endofFind with buffer position and length
        // so that this occurrence in the buffer will be
        // skipped next iteration.
        m_endofFind = result + m_findtextLength;
        m_rich->SetFocusObject(m_topParent, true);
        m_currentFind = m_rangeData[0] + result;
        m_rich->SetSelection(m_rangeData[0] + result, selEnd);


        if (m_scrollView)
            m_rich->ScrollIntoView(m_rich->GetCaretPosition(), WXK_DOWN);

        return true;
    }

    return false;
}

void SwFindReplace::OnLayoutBox(wxRichTextParagraphLayoutBox * obj)
{
    // New layout box so buffer contents, range, and parent
    // data are invalid. And this object will be the parent
    // of subsequent wxRichTextParagraph objects, which
    // will be the parent of subsequent wxRichTextPlainText
    // objects.
    m_topParent = obj;
    m_parent = NULL;
    m_rangeData.Empty();
    m_collection = "";
    m_collectionLwr = "";
    m_currentFind = -1;
    m_previousFind = -1;
}

void SwFindReplace::OnParagraph(wxRichTextParagraph * obj)
{
    // New paragraph so buffer contents, and range data
    // are invalid. And this object will be the parent
    // of subsequent wxRichTextPlainText objects.
    m_rangeData.Empty();
    m_collection = "";
    m_collectionLwr = "";
    m_parent = obj;
    //  m_currentFind = -1;
    //  m_previousFind = -1;
}

int SwFindReplace::FindWord()
{
    // Run loop looking for find text.
    // For case sensitive search use m_findText
    // which is the lower case version of the
    // original find text.
    // It is possible that there is more than
    // one instance of find text in the range
    // that is being searched and that this is
    // not the first time this range has been
    // searched. If it has been searched and at
    // least one instance of find text has been
    // found m_continue will be true and m_endofFind
    // will contain the position of the end of the
    // find text string at the time.
    // If there was a replace operation this may
    // fail in some situations.

    int result = 0;
    long selEnd;
    SwTextRange sel;

    if (m_continue)
    {
        result = m_endofFind;
    }

    if (m_findAll)
    {
        while(result != wxNOT_FOUND)
        {
            if (m_ignoreCase)
                result = m_collectionLwr.find(m_findText, result);
            else
                result = m_collection.find(m_findTextOriginal, result);

            if (result != wxNOT_FOUND)
            {
                if (m_wholewordOnly)
                {
                    // If whole word only check characters
                    // before and after for space or punctuation
                    // characters. Alphabetic, or numeric characters
                    // will cause a false result and the loop will
                    // continue starting the search at the end
                    // of the previous find text position in the string.
                    // Continue until all occurrences of find text in
                    // the string have been examined or there is a
                    // positive result.
                    if ((result == 0 || iswspace(m_collection[ result - 1])) &&
                            (iswspace(m_collection[result + m_findtextLength])
                             || iswpunct(m_collection[result + m_findtextLength])
                             || m_collection[result + m_findtextLength] == L'\0'))
                    {
                        selEnd = m_rangeData[0] + result + m_findtextLength;
                        sel.begin = m_rangeData[0] + result;
                        sel.end = selEnd;
                        m_foundList += sel;
                    }

                    result += m_findtextLength;
                    continue;
                }
                else
                {
                    selEnd = m_rangeData[0] + result + m_findtextLength;
                    sel.begin = m_rangeData[0] + result;
                    sel.end = selEnd;
                    sel.parent = m_topParent;
                    m_foundList += sel;
                    result += m_findtextLength;
                    continue;
                }

            }
            else
                break;
        }
    }
    else
    {
        // Return value is used to identify where in
        // m_collection next find operations should
        // begin. Allowing all matches in a paragraph
        // to be identified and marked.
        while(result != wxNOT_FOUND)
        {
            if (m_ignoreCase)
                result = m_collectionLwr.find(m_findText, result);
            else
                result = m_collection.find(m_findTextOriginal, result);

            if (result != wxNOT_FOUND)
            {
                if (m_wholewordOnly)
                {
                    // If whole word only check characters
                    // before and after for space or punctuation
                    // characters. Alphabetic, or numeric characters
                    // will cause a false result and the loop will
                    // continue starting the search at the end
                    // of the previous find text position in the string.
                    // Continue until all occurrences of find text in
                    // the string have been examined or there is a
                    // positive result.
                    if ((result == 0 || iswspace(m_collection[ result - 1])) &&
                            (iswspace(m_collection[result + m_findtextLength])
                             || iswpunct(m_collection[result + m_findtextLength])
                             || m_collection[result + m_findtextLength] == L'\0'))
                        return result;

                    result += m_findtextLength;
                    continue;
                }

                return result;
            }
            else
                break;
        }
    }
    return wxNOT_FOUND;
}

bool SwFindReplace::Find(wxString text, bool casesensitive, bool wholewordonly)
{
    Reset();
    SetFindText(text);
    SetCaseSensitive(casesensitive);
    SetWholeWordOnly(wholewordonly);

    return IterateBuffer();
}

bool SwFindReplace::FindNext()
{
    // Set m_continue flag so the the operation begins
    // where it left off.
    m_continue = true;

    // Begin stepping through the buffers objects ignoring
    // all objects until the last object examined on previous
    // iteration (m_found) is found. And then begin examining
    // content using m_endofFind as starting point to search
    // text.

    return IterateBuffer();
}

void SwFindReplace::Replace()
{
    wxRichTextRange range;

    if (m_rich->HasSelection())
    {
        range = m_rich->GetSelectionRange();
        m_rich->Replace(range.GetStart(), range.GetEnd(), m_replaceText);
        m_rich->SetSelection(range.GetStart(), range.GetStart() + m_replacetextLength);
        // When undo operations are enabled RichTextBuffer
        // moves the original object-s to the undo list,
        // and inserts a copy with specified modifications
        // in the originals place, and m_found will no
        // longer be valid.
        // The new object is not known but the range is,
        // so update m_found now to prevent subsequent
        // operations from failing. Such as find text
        // existing more than once in the text-s objects
        // collective content represented by m_collection.
        m_found = m_parent->FindObjectAtPosition(range.GetStart());
    }
}

// Replace all text in buffer that matches find data.
void SwFindReplace::ReplaceAll()
{
    Reset();
    m_replaceAll = true;
    IterateBuffer();
    m_replaceAll = false;
    Reset();
}

bool SwFindReplace::Hilite(const wchar_t * str, bool casesensitive, bool wholewordonly)
{
    if (!str)
        return false;

    Reset();
    SetFindAll(true);
    SetScrollView(false);
    SetFindText(str);
    SetCaseSensitive(casesensitive);
    SetWholeWordOnly(wholewordonly);

    bool status = IterateBuffer();
    HiliteFoundList();
    Reset();

    return status;
}

void SwFindReplace::HiliteFoundList()
{
    wxRichTextAttr attr;
    attr.SetBackgroundColour(*wxYELLOW);

    for (swUI32 i = 0; i < m_foundList.GetCount(); i++)
    {
        m_rich->SetFocusObject(m_foundList.GetAt(i).parent, true);
        m_rich->SetSelection(m_foundList.GetAt(i).begin, m_foundList.GetAt(i).end);
        m_rich->GetStyleForRange(wxRichTextRange(m_foundList.GetAt(i).begin, m_foundList.GetAt(i).end), attr);
        attr.SetBackgroundColour(*wxYELLOW);
        m_rich->SetStyle(m_foundList.GetAt(i).begin, m_foundList.GetAt(i).end, attr);
    }

    m_rich->SetSelection(0, 0);
}
