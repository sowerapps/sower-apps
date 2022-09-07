///////////////////////////////////////////////////////////////////
// Name:        html_attributes.h
// Purpose:     Identify HTML attributes.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef HTML_ATTRIBUTES_H
#define HTML_ATTRIBUTES_H

#include "html.h"

class SOWERBASEEXP SwHtmlAttributes
{
public:
    static swUI8 IdentifyAttribute(const char * source);
    static const char * GetAttributeString(swUI8 property);
};

#endif // HTML_ATTRIBUTES_H
