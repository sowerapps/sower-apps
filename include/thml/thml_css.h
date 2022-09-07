///////////////////////////////////////////////////////////////////
// Name:        thml_css.h
// Purpose:     Standard CSS to be applied to a ThML file.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THML_CSS_H
#define THML_CSS_H

#include "../sowerbase.h"
#include "../string/string.h"
#include "../thml/thml_parser.h"
#include "../css/css_attributes.h"

class SOWERBASEEXP SwThMLCss
{
public:
    static void Init();
    static void GetElementStyle(swUI16 element, CssAttributeList & styleList);
    static swUI32 Find(const char * classname, swUI32 start = 0);
    static swUI32 Find(swUI16 elementId, swUI32 start = 0);
    static swUI32 Find(swUI16 elementId, const char * classname, swUI32 start = 0);
    static swUI32 Find(SwThMLParser & parser, swUI32 node, const char * name, swUI32 start);
    static void GetStyle(swUI8 style, CssAttributeList & styleList);
    static swUI16 GetSpecificity(swUI32 pos);
    static swUI16 GetScope(swUI32 pos);
    static swUI16 GetItems();
};

#endif // THML_CSS_H
