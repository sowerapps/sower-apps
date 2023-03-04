///////////////////////////////////////////////////////////////////
// Name:        referenceparser.h
// Purpose:     Parser for text, or html documents, with functionality
//              specific to ThML markup of scripture references.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef REFERENCEPARSER_H
#define REFERENCEPARSER_H

#include "../html/html.h"
#include "../string/stringw.h"
#include "../array/referenceitemarray.h"

enum PARSER_NODE_TYPES
{
    NODE_TYPE_REF_CVDIV, NODE_TYPE_REF_DIV, NODE_TYPE_REF_CV_DIV_COMP, NODE_TYPE_REF_SPAN, NODE_TYPE_REF_BREAK,
    NODE_TYPE_SPACE, NODE_TYPE_ALPHA, NODE_TYPE_ALPHA_ROMAN, NODE_TYPE_NUMERIC, NODE_TYPE_SYMBOL, NODE_TYPE_LINE_BREAK,
    N_NODE_TYPES
};

struct SwReferenceParserNodeData
{
    swUI32      beginPos;
    swUI32      endPos;
    swUI8       nodeType;
};

class SwReferenceParser;
typedef swUI32 (SwReferenceParser::*RefTagHandler)(swUI32 node);

class SOWERBASEEXP SwReferenceParser :public SwStringW
{
public:
    SwReferenceParser();
    virtual ~SwReferenceParser();

    void Reset();
    void SetArrayIncrement(swUI16 increment);
    bool IncreaseParserNodeArray();
    bool SizeParserNodeArray(swUI32 nodes);
    bool VerifyParserNode();
    bool VerifyParserNodes(swUI32 nodes);
    bool Parse();
    swUI32 GetLastParserNode();
    swUI32 GetParserNodes();
    void UpdateNodePosData(swUI32 nodeStart, swUI32 change, bool type);
    swUI8 GetNodeType(swUI32 node);
    void SetNodeType(swUI32 node, swUI8 type);
    swUI32 GetNodeStreamPosition(swUI32 node);
    swUI32 GetNodeDataSize(swUI32 node);
    swUI32 GetNodesDataSize(swUI32 nodeBegin, swUI32 nodeEnd);
    SwReferenceParserNodeData * GetNode(swUI32 node);
    bool GetNodeData(swUI32 node, SwStringW & dest);
    bool GetNodesData(swUI32 nodeBegin, swUI32 nodeEnd, SwStringW & dest);
    swUI32 FindNodeByStreamPos(swUI32 streamPos);
    void SetOptions(wchar_t _cvdiv, wchar_t _span, wchar_t _div, wchar_t _break, bool romanforchapters, bool romanforverses, bool romanlowercase, bool linebreakisspace, bool firstletteruc);
    void SetCVDivMarker(wchar_t marker);
    void SetSpanMarker(wchar_t marker);
    void SetDivMarker(wchar_t marker);
    void SetBreakMarker(wchar_t marker);
    void SetRomanForChapters(bool state);
    void SetRomanForVerses(bool state);
    void SetRomanLowerCase(bool state);
    void SetLineBreakIsSpace(bool state);
    void SetFirstLetterUpperCase(bool state);
    swUI8 GetValue(swUI32 node);
    bool IsMarker(wchar_t ch);
    bool IsNodeWhiteSpace(swUI32 node);
    swUI32 FindWhiteSpaceEnd(swUI32 node);
    bool CouldNodeBeNumber(swUI32 node);
    bool IsValidForChapterNumber(swUI32 node);
    bool IsValidForVerseNumber(swUI32 node);
    bool IsLowerRoman(swUI32 node);
    swUI8 IdentifyBook(swUI32 & node);
    swUI32 Oncvdiv(swUI32 node);
    swUI32 Ondiv(swUI32 node);
    swUI32 Oncvdivcomp(swUI32 node);
    swUI32 Onspan(swUI32 node);
    swUI32 Onbreak(swUI32 node);
    swUI32 Onspace(swUI32 node);
    swUI32 Onalpha(swUI32 node);
    swUI32 Onalpharoman(swUI32 node);
    swUI32 Onnumeric(swUI32 node);
    swUI32 Onsymbol(swUI32 node);
    swUI32 Onlinebreak(swUI32 node);
    bool Run();
    void WriteReferenceMarkUp();

protected:
    SwReferenceParserNodeData * m_parserNodeData;
    RefTagHandler               m_handlers[N_NODE_TYPES];
    SwReferenceItem             m_refItem;
    bool                        m_hasRef;
    bool                        m_hasSpan;
    bool                        m_primaryRefAdded;
    bool                        m_hasAdditions;
    swUI32                      m_parserNodePos;
    swUI32                      m_parserNodesAllocated;
    swUI16                      m_parserInc;
    wchar_t                     m_cvdiv;
    wchar_t                     m_span;
    wchar_t                     m_div;
    wchar_t                     m_break;
    bool                        m_romanforchapters;
    bool                        m_romanforverses;
    bool                        m_romanlowercase;
    bool                        m_linebreakisspace;
    bool                        m_firstletteruc;
    SwReferenceItemArray        m_referenceArray;

};

#endif // REFERENCEPARSER_H
