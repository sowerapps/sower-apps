///////////////////////////////////////////////////////////////////
// Name:        css_file.h
// Purpose:     Load, and parse CSS from external files, memory,
//              or add styles with Add().
//              CssParser - break styles into a list of selectors,
//              and attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CSSFILE_H
#define CSSFILE_H

#include <wx/richtext/richtextctrl.h>
#include "../html/html.h"
#include "../thml/thml_parser.h"
#include "../thml/thml_elements.h"
#include "css_selector.h"
#include "css_attributes.h"

struct SwCssListNode
{
    CssSelector * selector;
    SwString *    style;
};

class SOWERBASEEXP CssFile
{
public:
    CssFile();
    virtual ~CssFile();

    virtual void Reset();
    bool OpenFile(const char * path);
    bool HasFile() { return m_fileLoaded; }
    swUI32 Add(const char * selector, const char * style);
    void Delete(swUI32 pos);
    SwCssListNode * GetNode(swUI32 pos);
    bool ReadStyleData(SwThMLParser * thmlParser);
    bool ReadCSS(SwThMLParser * thmlParser, swUI32 startNode);
    bool ParseCss(const char * css, swUI32 dataSize);
    swUI32 FindClass(const char * className, swUI32 start = 0);
    swUI32 FindElement(const char * element, swUI32 start = 0);
    swUI32 Find(const char *, const char * className, swUI32 start = 0);
    swUI32 Find(SwThMLParser & parser, swUI32 node, const char * name, swUI32 start);
    const char * GetStyle(swUI32 pos);
    swUI16 GetSpecificity(swUI32 pos);
    swUI32 GetCount() { return m_arrayPos; }

private :
    bool IncreaseArray();
    void ReleaseArray();
    swUI32 AssignObject();

    bool            m_fileLoaded;
    SwCssListNode * m_array;
    swUI32          m_arrayPos;
    swUI32          m_objectsAllocated;
};

#endif // CSSFILE_H
