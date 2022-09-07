///////////////////////////////////////////////////////////////////
// Name:        xmlwrite.cpp
// Purpose:     Write HTML/ThML to control. The source is passed to
//              a static RichInterface (derived from Interface, which
//              which is derived from SwThMLParser) which actually writes
//              the source to this control. This allows multiple views
//              to use the same RichInterface, but is not thread safe.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/richtext/richtextctrlext.h"
#include "../../include/appi/appifa.h"

// Used by modules.
void SwRichTextCtrl::WriteXmlText(const char * source, bool thml, const char * basePath)
{
    SwApplicationInterface::GetRichInterface().Reset();
    SwApplicationInterface::GetRichInterface().Load(source, strlen(source));
    SwApplicationInterface::GetRichInterface().SetIsThML(thml);
    SwApplicationInterface::GetRichInterface().SetCtrl(this);
    SwApplicationInterface::GetRichInterface().SetBasePath(basePath);
    SwApplicationInterface::GetRichInterface().Run();
}

// Used for documents that have not been preprocessed (CSS, ThML notes  etc.).
void SwRichTextCtrl::WriteXmlText(const char * source, swUI32 length, bool thml, CssFile * list, const char * basePath)
{
    SwApplicationInterface::GetRichInterface().Reset();
    SwApplicationInterface::GetRichInterface().Load(source, length);
    SwApplicationInterface::GetRichInterface().SetIsThML(thml);
    SwApplicationInterface::GetRichInterface().SetCtrl(this);
    SwApplicationInterface::GetRichInterface().SetCssFile(list);
    SwApplicationInterface::GetRichInterface().SetBasePath(basePath);
    if (thml)
        SwApplicationInterface::GetRichInterface().ProcessThMLNotes();
    SwApplicationInterface::GetRichInterface().Run(true);
}
