///////////////////////////////////////////////////////////////////
// Name:        html_css.h
// Purpose:     Standard CSS to be applied to elements.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HTMLCSS_H
#define HTMLCSS_H

#include "../sowerbase.h"
#include "../css/css_attributes.h"

class SOWERBASEEXP SwHtmlCss
{
public:
    static void GetElementStyle(swUI16 element, CssAttributeList & styleList);
};

#endif // HTMLCSS_H
