///////////////////////////////////////////////////////////////////
// Name:        css_selector.h
// Purpose:     Parse, and identify attributes of CSS selectors.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CSS_SELECTOR_H
#define CSS_SELECTOR_H

#include "../../include/html/html.h"
#include <stdlib.h>
#include <malloc.h>

struct SwSelectorNode
{
    char *      item;
    swUI8       type;
    swUI8       opcode;
};

class SOWERBASEEXP CssSelector
{
public:
    CssSelector();
    virtual ~CssSelector();

    void Reset();
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI32 nodes);
    bool VerifyNode();
    bool ParseSelector(const char * selector);
    swUI32 FindFirstElement();
    swUI32 FindElement(const char * element);
    bool HasElement(const char * element);
    bool HasNameValuePair();
    swUI32 FindNameValuePair(swUI32 start = 0);
    bool HasNameValuePair(const char * name, const char * value);
    bool HasControl(swUI32 pos);
    swUI32 FindFirstClass();
    bool HasClass(const char * name);
    swUI32 FindPseudoClass();
    bool HasPseudoClass();
    bool HasPseudoElement(swUI32 idx);
    SwSelectorNode * GetNode(swUI32 pos);
    swUI8 GetNodeType(swUI32 pos);
    swUI32 GetLastNode();
    swUI32 GetNodePos();
    swUI32 GetElementCount();
    swUI32 GetClassCount();
    swUI16 GetSpecificity();
    swUI16 CalculateSpecificity();
    bool Add(char * item, swUI8 type, swUI8 opcode);

private:
    SwString                m_selector;
    swUI16                  m_specificity;
    SwSelectorNode *        m_nodeData;
    swUI32                  m_nodePos;
    swUI32                  m_nodesAllocated;
};

#endif // CSS_SELECTOR_H
