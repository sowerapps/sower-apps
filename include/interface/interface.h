///////////////////////////////////////////////////////////////////
// Name:        interface.h
// Purpose:     SwViewInterface - base class for interfaces to views for
//              different types of content. SowerBase allows an
//              additional attribute (type) for ThML div elements
//              to specify the type of view needed to display the
//              content of the div. Views are created as needed,
//              and the interface for the content/view type writes
//              writes/transfers content to the view.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef INTERFACE_H
#define INTERFACE_H

#include "../css/css_inliner.h"
#include "../css/css_attributes.h"
#include "../css/css_file.h"

class SOWERBASEEXP SwViewInterface : public SwCssInliner
{
public:
    SwViewInterface();
    virtual ~SwViewInterface();

    void Init();
    virtual void Reset();
    virtual void OnReset() {}
    void Run(bool inline_ = false);
    virtual void OnPreRun() {}
    virtual void OnCompletion() {}
    virtual swUI32 Handle(swUI16 id, swUI32 node) { return node; }
    virtual swUI32 Onbinary(swUI32 node);
    virtual swUI32 Onmodule(swUI32 node);
    virtual swUI32 Ontext(swUI32 node);
    virtual swUI32 Onunknown(swUI32 node);
    virtual swUI32 Onwhitespace(swUI32 node);
    bool IsThML(){ if (GetMarkupType() == MARKUP_THML) return true; return false; }
    void SetIsThML(bool isThML) { if (isThML) SetMarkupType(MARKUP_THML); else SetMarkupType(MARKUP_HTML); }
    void SetBaseFontSize(swUI8 size) { m_basefontsize = size; }
    SwString & GetTitleBuffer() { return m_title; }
    void Inline();

protected:
    swUI8              m_basefontsize;
    bool               m_isModule;
    swUI16             m_moduleId;
    SwString           m_title;
    swUI32             m_skipNode;
};

#endif // INTERFACE_H
