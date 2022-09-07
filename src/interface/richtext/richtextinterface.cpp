///////////////////////////////////////////////////////////////////
// Name:        richtextinterface.cpp
// Purpose:     Interface for SwRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../../include/interface/richtext/richtextinterface.h"
#include "../../../include/appi/appifa.h"

SwRichTextInterface::SwRichTextInterface()
{
    m_listData = NULL;
    m_listnodesAllocated = 0;
    m_listnodePos = 0;
    InitHandlers();
}

SwRichTextInterface::~SwRichTextInterface()
{
    if (m_listData)
        free(m_listData);
}

void SwRichTextInterface::OnReset()
{
    m_listnodePos = 0;
    m_richAttr.Reset();
    m_pre = false;
    m_inListItem = false;
    m_title.Reset();
    m_matrixArray.Reset();
}

void SwRichTextInterface::InitHandlers()
{
    for (swUI16 i = 0; i < N_THML_ELEMENTS; i++)
    {
        m_thmlHandlers[i] = &SwRichTextInterface::Onvoid;
    }

    m_thmlHandlers[THML_A] = &SwRichTextInterface::Ona;
    m_thmlHandlers[THML_ABBR] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_ACRONYM] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_ADDRESS] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_AREA] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_ARGUMENT] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_ARTICLE] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_ASIDE] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_ATTR] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_AUDIO] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_AUTODEF_BODY] = &SwRichTextInterface::Onautodefbody;
    m_thmlHandlers[THML_B] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_BIG] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_BLOCKQUOTE] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_BODY] = &SwRichTextInterface::Onbody;
    m_thmlHandlers[THML_BR] = &SwRichTextInterface::Onbr;
    m_thmlHandlers[THML_BUTTON] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_CANVAS] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_CAPTION] = &SwRichTextInterface::Oncaption;
    m_thmlHandlers[THML_CENTER] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_CHRIST] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_CITATION] = &SwRichTextInterface::Oncitation;
    m_thmlHandlers[THML_CITE] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_CODE] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_COL] = &SwRichTextInterface::Oncol;
    m_thmlHandlers[THML_COLGROUP] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_COMMAND] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_COMPOSER] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_DATALIST] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_DATE] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_DD] = &SwRichTextInterface::Ondd;
    m_thmlHandlers[THML_DEF] = &SwRichTextInterface::Ondef;
    m_thmlHandlers[THML_DEL] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_DELETED] = &SwRichTextInterface::Onhide;
    m_thmlHandlers[THML_DETAILS] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_DFN] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_DIR] = &SwRichTextInterface::Ondir;
    m_thmlHandlers[THML_DIV] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_DIV1] = &SwRichTextInterface::Ondivn;
    m_thmlHandlers[THML_DIV2] = &SwRichTextInterface::Ondivn;
    m_thmlHandlers[THML_DIV3] = &SwRichTextInterface::Ondivn;
    m_thmlHandlers[THML_DIV4] = &SwRichTextInterface::Ondivn;
    m_thmlHandlers[THML_DIV5] = &SwRichTextInterface::Ondivn;
    m_thmlHandlers[THML_DIV6] = &SwRichTextInterface::Ondivn;
    m_thmlHandlers[THML_DL] = &SwRichTextInterface::Ondl;
    m_thmlHandlers[THML_DT] = &SwRichTextInterface::Ondt;
    m_thmlHandlers[THML_EM] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_FIELDSET] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_FIGCAPTION] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_FIGURE] = &SwRichTextInterface::Onfigure;
    m_thmlHandlers[THML_FONT] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_FOOTER] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_FOREIGN] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_FORM] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_GLOSSARY] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_GLOSSARY_ITEM] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_HEADER] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_HTML] = &SwRichTextInterface::Onhtml;
    m_thmlHandlers[THML_HR] = &SwRichTextInterface::Onhr;
    m_thmlHandlers[THML_HYMN] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_H1] = &SwRichTextInterface::Onh1h6;
    m_thmlHandlers[THML_H2] = &SwRichTextInterface::Onh1h6;
    m_thmlHandlers[THML_H3] = &SwRichTextInterface::Onh1h6;
    m_thmlHandlers[THML_H4] = &SwRichTextInterface::Onh1h6;
    m_thmlHandlers[THML_H5] = &SwRichTextInterface::Onh1h6;
    m_thmlHandlers[THML_H6] = &SwRichTextInterface::Onh1h6;
    m_thmlHandlers[THML_I] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_IMAGE] = &SwRichTextInterface::Onimg;
    m_thmlHandlers[THML_IMG] = &SwRichTextInterface::Onimg;
    m_thmlHandlers[THML_INCIPIT] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_INPUT] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_INS] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_KBD] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_L] = &SwRichTextInterface::Onl;
    m_thmlHandlers[THML_LABEL] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_LEGEND] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_LI] = &SwRichTextInterface::Onli;
    m_thmlHandlers[THML_MAP] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_MARK] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_MENU] = &SwRichTextInterface::Onhide;
    m_thmlHandlers[THML_METER] = &SwRichTextInterface::Onmeter;
    m_thmlHandlers[THML_MUSIC] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_NAME] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_NAV] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_NOTE] = &SwRichTextInterface::Onnote;
    m_thmlHandlers[THML_OBJECT] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_OL] = &SwRichTextInterface::Onol;
    m_thmlHandlers[THML_OPTGROUP] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_OPTION] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_OUTPUT] = &SwRichTextInterface::Onhide;
    m_thmlHandlers[THML_P] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_PB] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_PRE] = &SwRichTextInterface::Onpre;
    m_thmlHandlers[THML_PROGRESS] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_Q] = &SwRichTextInterface::Onq;
    m_thmlHandlers[THML_S] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_SAMP] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_SCRIPCOM] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_SCRIPCONTEXT] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_SCRIPREF] = &SwRichTextInterface::Onscripref;
    m_thmlHandlers[THML_SCRIPT] = &SwRichTextInterface::Onhide;
    m_thmlHandlers[THML_SCRIPTURE] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_SELECT] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_SMALL] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_SPAN] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_STRIKE] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_STRONG] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_SUB] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_SUMMARY] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_SUP] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_SYNC] = &SwRichTextInterface::Onsync;
    m_thmlHandlers[THML_TABLE] = &SwRichTextInterface::Ontable;
    m_thmlHandlers[THML_TBODY] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_TD] = &SwRichTextInterface::Ontd;
    m_thmlHandlers[THML_TERM] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_TERM_STRONGS] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_TEXTAREA] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_TFOOT] = &SwRichTextInterface::Ontfoot;
    m_thmlHandlers[THML_TH] = &SwRichTextInterface::Onth;
    m_thmlHandlers[THML_THEAD] = &SwRichTextInterface::Onthead;
    m_thmlHandlers[THML_THML] = &SwRichTextInterface::Onthml;
    m_thmlHandlers[THML_THML_BODY] = &SwRichTextInterface::Onbody;
    m_thmlHandlers[THML_TIME] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_TITLE] = &SwRichTextInterface::Ontitle;
    m_thmlHandlers[THML_TR] = &SwRichTextInterface::Ontr;
    m_thmlHandlers[THML_TT] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_TUNE] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_U] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_UL] = &SwRichTextInterface::Onul;
    m_thmlHandlers[THML_UNCLEAR] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_VAR] = &SwRichTextInterface::Oninline;
    m_thmlHandlers[THML_VERSE] = &SwRichTextInterface::Onblock;
    m_thmlHandlers[THML_VIDEO] = &SwRichTextInterface::Onvoid;
    m_thmlHandlers[THML_AUTHOR] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_AUTHORID] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_BOOKID] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_COMMENTS] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_CONTRIBUTOR] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_COPYLOCATION] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_COVERAGE] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_CREATOR] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_DATE] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DESCRIPTION] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_DESCRIPTION] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_EDITORIALCOMMENTS] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_FIRSTPUBLISHED] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_FORMAT] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_IDENTIFIER] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_LANGUAGE] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_PUBLISHER] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_PUBHISTORY] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_PUBLISHED] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_PUBLISHERID] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_RELATION] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_REVISIONHISTORY] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_RIGHTS] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_SOURCE] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_STATUS] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_SUBJECT] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_DC_TITLE] = &SwRichTextInterface::Oninformation;
    m_thmlHandlers[THML_VERSION] = &SwRichTextInterface::Oninformation;
}

bool SwRichTextInterface::IncreaseListDataBuffer()
{
    if (m_listnodesAllocated >= NODE_ID_INVALID_16 - 17)
        return false;

    SwListData * p = (SwListData *) realloc((void *) m_listData, (m_listnodesAllocated + 16) * sizeof(SwListData));

    if (p)
    {
        m_listnodesAllocated += 16;
        m_listData = p;
        return true;
    }

    return false;
}

swUI16 SwRichTextInterface::AssignListDataNode()
{
    if (m_listnodePos >= m_listnodesAllocated && !IncreaseListDataBuffer())
        return NODE_ID_INVALID_16;

    memset((void *)&m_listData[m_listnodePos], 0, sizeof(SwListData));
    m_listData[m_listnodePos].listType = 0;
    m_listData[m_listnodePos].start = 0;
    m_listData[m_listnodePos].itemCount = 0;

    m_listnodePos ++;

    return m_listnodePos - 1;
}

void SwRichTextInterface::ReleaseListDataBuffer()
{
    if (m_listData)
        free(m_listData);

    m_listData = NULL;
    m_listnodesAllocated = 0;
    m_listnodePos = 0;
}

void SwRichTextInterface::AddToParagraphList(swUI32 node)
{
    if (!m_rich)
        return;

    SwString xmlId, passageId;
    if (GetNodeElementIdentifier(node) == THML_SCRIPCOM ||
            GetNodeElementIdentifier(node) == THML_SCRIPTURE ||
            GetNodeElementIdentifier(node) == THML_SCRIPREF)
    {
        if (!GetNamedValueFromNode(node, "passage", passageId) &&
                !GetNamedValueFromNode(node, "osisID", passageId) &&
                GetNamedValueFromNode(node, "osisRef", passageId))
            passageId = "";
    }

    GetNamedValueFromNode(node, "id", xmlId);

    m_rich->GetParagraphList().AddTag(GetNodeElementIdentifier(node), GetNodeType(node), xmlId, passageId, m_rich->GetInsertionPoint(), m_rich->GetFocusObject());
}

void SwRichTextInterface::OnPreRun()
{
    if (m_rich)
    {
        m_rich->BeginSuppressUndo();
        m_rich->Freeze();
    }
}

void SwRichTextInterface::OnCompletion()
{
    if (m_rich)
    {
        m_rich->Thaw();
        m_rich->EndSuppressUndo();
        m_rich->GetParagraphList().UpdateNodeData();
    }
}

void SwRichTextInterface::SetCtrl(SwRichTextCtrl * rich)
{
    m_rich = rich;
}
