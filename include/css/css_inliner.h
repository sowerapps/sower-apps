///////////////////////////////////////////////////////////////////
// Name:        css_inliner.h
// Purpose:     Inline CSS.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CSS_INLINER_H
#define CSS_INLINER_H

#include "../thml/thml_parser.h"
#include "../thml/thml_css.h"
#include "css_file.h"
#include "css_attributes.h"

class SOWERBASEEXP SwCssInliner : public SwThMLParser
{
    public:
        SwCssInliner();
        virtual ~SwCssInliner();
        virtual bool OpenFile(const char * path, bool thml = true);

        void Reset();
        void ResetFull();
        bool ProcessFile();
        bool ProcessBuffer(const char * buffer);
        bool Process(swUI32 startnode);
        bool ProcessNode(swUI32 node, SwString & tag);
        void LoadInternalCss();
        swUI32 LocateDocumentBody();
        void CollectInlineStyles(swUI32 node);
        void CollectInlineStyles(SwString & source);
        void CollectInternalStyles(swUI32 node);
        void CollectExternalStyles(swUI32 node);
        void CollectThMLStyles(swUI32 nodenode);
        void CleanTag(swUI32 node);
        void ProcessScope(swUI32 node);
        void RemoveStyleSheets();
        CssFile & GetCssFile(){ return m_cssFile; }
        CssFile & GetCssStyleList(){ return m_styleList; }
        CssAttributeList & GetAttributeList(){ return m_attrList; }
        swUI32 GetNodePos() { return m_node; }
        void SetDespace(bool despace);
        void SetCssFile(CssFile * list){ m_cssrules = list; }

    protected:
        bool                m_despace;
        swUI32              m_node;
        swUI32              m_skipNode;
        CssFile *           m_cssrules;
        CssFile             m_styleList;
        CssAttributeList    m_attrList;
        CssFile             m_cssFile;
        SwString            m_class;
        SwString            m_style;
        SwString            m_nodeBuffer;
};

#endif // CSS_INLINER_H
