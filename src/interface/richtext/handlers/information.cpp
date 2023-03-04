///////////////////////////////////////////////////////////////////
// Name:        information.cpp
// Purpose:     SwRichTextInterface tag handler-s.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../../include/interface/richtext/richtextinterface.h"

swUI32 SwRichTextInterface::Oninformation(swUI32 node)
{
    if (GetNodeType(node) == NODE_TYPE_BEGIN_TAG)
    {
        Paragraph();
        switch (GetNodeElementIdentifier(node))
        {
        case THML_AUTHOR :
            m_rich->BeginBold();
            m_rich->WriteText(L"Author");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_AUTHORID:
            m_rich->BeginBold();
            m_rich->WriteText(L"Author ID");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_BOOKID :
            m_rich->BeginBold();
            m_rich->WriteText(L"Book ID");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_COMMENTS :
            m_rich->BeginBold();
            m_rich->WriteText(L"Comments");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_CONTRIBUTOR :
            m_rich->BeginBold();
            m_rich->WriteText(L"Contributor");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_COPYLOCATION :
            m_rich->BeginBold();
            m_rich->WriteText(L"Copy Location");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_COVERAGE :
            m_rich->BeginBold();
            m_rich->WriteText(L"Coverage");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_CREATOR :
            m_rich->BeginBold();
            m_rich->WriteText(L"Creator");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_DATE :
            m_rich->BeginBold();
            m_rich->WriteText(L"Date");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DESCRIPTION :
        case THML_DC_DESCRIPTION :
            m_rich->BeginBold();
            m_rich->WriteText(L"Description");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_EDITORIALCOMMENTS :
            m_rich->BeginBold();
            m_rich->WriteText(L"Editorial Comments");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_FIRSTPUBLISHED :
            m_rich->BeginBold();
            m_rich->WriteText(L"First Published");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_FORMAT :
            m_rich->BeginBold();
            m_rich->WriteText(L"Format");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_IDENTIFIER :
            m_rich->BeginBold();
            m_rich->WriteText(L"Identifier");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_LANGUAGE :
            m_rich->BeginBold();
            m_rich->WriteText(L"Language");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_PUBLISHER :
            m_rich->BeginBold();
            m_rich->WriteText(L"Publisher");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_PUBHISTORY :
            m_rich->BeginBold();
            m_rich->WriteText(L"Publishing History");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_PUBLISHED :
            m_rich->BeginBold();
            m_rich->WriteText(L"Published");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_PUBLISHERID :
            m_rich->BeginBold();
            m_rich->WriteText(L"Publisher ID");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_RELATION :
            m_rich->BeginBold();
            m_rich->WriteText(L"Relation");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_REVISIONHISTORY :
            m_rich->BeginBold();
            m_rich->WriteText(L"Revision History");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_RIGHTS :
            m_rich->BeginBold();
            m_rich->WriteText(L"Rights");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_SOURCE :
            m_rich->BeginBold();
            m_rich->WriteText(L"Source");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_STATUS :
            m_rich->BeginBold();
            m_rich->WriteText(L"Status");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_SUBJECT :
            m_rich->BeginBold();
            m_rich->WriteText(L"Subject");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_DC_TITLE :
            m_rich->BeginBold();
            m_rich->WriteText(L"Title");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        case THML_VERSION :
            m_rich->BeginBold();
            m_rich->WriteText(L"Version");
            m_rich->EndBold();
            m_rich->WriteText(L" = ");
            break;
        }
    }
    else if (GetNodeType(node) == NODE_TYPE_END_TAG)
    {
        m_rich->LineBreak();
    }

    return node;
}
