///////////////////////////////////////////////////////////////////
// Name:        richtextinterface.h
// Purpose:     Interface for SwRichTextCtrl.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef RICHTEXTINTERFACE_H
#define RICHTEXTINTERFACE_H

#include "../interface.h"
#include "../../richtext/richtextctrlext.h"
#include "../../richtext/attr/richtextattr.h"
#include "../../richtext/objects/richtexttablematrix.h"
#include "../../html/html_imagemap.h"
#include "../../string/stringw.h"

struct SwListData
{
    swUI8   listType;
    swUI16  start;
    swUI16  itemCount;
};

class SwRichTextInterface;
typedef swUI32 (SwRichTextInterface::*TagHandler)(swUI32 node);

class SOWERBASEEXP SwRichTextInterface : public SwViewInterface
{
public:
    SwRichTextInterface();
    virtual ~SwRichTextInterface();

    virtual void OnReset();
    virtual void OnPreRun();
    virtual void OnCompletion();

    bool IncreaseListDataBuffer();
    swUI16 AssignListDataNode();
    void ReleaseListDataBuffer();

    swUI32 Handle(swUI16 id, swUI32 node)
    {
        m_richAttr.Reset();
        AddToParagraphList(node);
        return (this->*m_thmlHandlers[id])(node);
    }

    void GetBlockStyle(swUI32 node);
    void GetInlineStyle(swUI32 node);
    bool GetEndStyleFlag(swUI32 node);
    void SetEndStyleFlag(swUI32 node, bool state);
    bool BeginBlockStyle(swUI32 node, bool force = false);
    void EndBlockStyle(swUI32 node);
    bool BeginInlineStyle(swUI32 node, bool force = false);
    void EndInlineStyle(swUI32 node);

    void Paragraph()
    {
        if (m_inListItem)
        {
            LineBreak();
            return;
        }

        m_rich->NewlineEx();
        m_lch = LCH_BREAK;
    }

    void LineBreak()
    {
        m_rich->NewlineEx();
        m_lch = LCH_BREAK;
    }

    virtual void InitHandlers();
    void AddToParagraphList(swUI32 node);

    swUI32 Oninline(swUI32 node);
    swUI32 Onblock(swUI32 node);
    swUI32 Onvoid(swUI32 node);
    swUI32 Onautodefbody(swUI32 node);
    swUI32 Onbody(swUI32 node);
    swUI32 Ona(swUI32 node);
    swUI32 Onbr(swUI32 node);
    swUI32 Oncaption(swUI32 node);
    swUI32 Oncol(swUI32 node);
    swUI32 Oncitation(swUI32 node);
    swUI32 Ondd(swUI32 node);
    swUI32 Ondef(swUI32 node);
    swUI32 Ondir(swUI32 node);
    swUI32 Ondl(swUI32 node);
    swUI32 Ondt(swUI32 node);
    swUI32 Onfigure(swUI32 node);
    swUI32 Onh1h6(swUI32 node);
    swUI32 Onhide(swUI32 node);
    swUI32 Onhtml(swUI32 node);
    swUI32 Onhr(swUI32 node);
    swUI32 Onimg(swUI32 node);
    swUI32 Oninformation(swUI32 node);
    swUI32 Onli(swUI32 node);
    swUI32 Onmeter(swUI32 node);
    swUI32 Onmusic(swUI32 node);
    swUI32 Onol(swUI32 node);
    swUI32 Onpre(swUI32 node);
    swUI32 Onq(swUI32 node);
    swUI32 Ontable(swUI32 node);
    swUI32 Ontd(swUI32 node);
    swUI32 Ontfoot(swUI32 node);
    swUI32 Onth(swUI32 node);
    swUI32 Onthead(swUI32 node);
    swUI32 Onthml(swUI32 node);
    swUI32 Ontitle(swUI32 node);
    swUI32 Ontr(swUI32 node);
    swUI32 Onul(swUI32 node);
    swUI32 Ondivn(swUI32 node);
    swUI32 Onl(swUI32 node);
    swUI32 Onnote(swUI32 node);
    swUI32 Onscripref(swUI32 node);
    swUI32 Onsync(swUI32 node);
    swUI32 Onterm(swUI32 node);
    swUI32 Onunclear(swUI32 node);

    virtual swUI32 Ontext(swUI32 node)
    {
        bool strip = true;

        if (m_pre)
            strip = false;

        if (!GetNodeDataSize(node) || !GetNodeData(node, m_input))
            return node;

        m_output.Size(GetNodeDataSize(node) + 1);
        SwHtml::Html2Text(m_input, m_output, m_output.GetSize(), m_lch, strip);
        m_raw.Copy(m_output);
        m_rich->WriteText(m_raw.GetArray());

        return node;
    }

    virtual swUI32 Onwhitespace(swUI32 node)
    {
        return Ontext(node);
    }

    void SetCtrl(SwRichTextCtrl * rich);
    void BeginNumberedBullet(int number, int leftIndent, int subIndent);
    void EndNumberedBullet();
    void WriteSymbol(swUI8 listType);

protected:
    SwRichTextTableMatrixArray m_matrixArray;
    SwRichTextCtrl *         m_rich;
    SwRichTextAttr           m_richAttr;
    CssSpacedList            m_spaceList;
    SwListData *             m_listData;
    SwHtmlImageMap *         m_map;
    swUI16                   m_listnodePos;
    swUI16                   m_listnodesAllocated;
    swUI8                    m_lch;
    TagHandler               m_thmlHandlers[N_THML_ELEMENTS];
    bool                     m_pre;
    bool                     m_inListItem;
    SwStringW                m_raw;
    SwString                 m_output;
    SwString                 m_input;
};

#endif // RICHTEXTINTERFACE_H
