///////////////////////////////////////////////////////////////////
// Name:        modulewriter.h
// Purpose:     Base class for writing modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef MODULEWRITER_H
#define MODULEWRITER_H

#include "modulebase.h"
#include "module.h"
#include "autodefcommentary.h"
#include "autodefterm.h"
#include "autodefnumbered.h"
#include "autodefscripture.h"
#include "mediacontents.h"
#include "tableofcontents.h"
#include "../css/css_inliner.h"
#include "../bible/scripturemap.h"
#include "../bible/commentarymap.h"

enum MOD_WRITE_ERROR_CODES
{
    EC_UNCONTAINED_TEXT_RUN,
    EC_UNCONTAINED_SCRIPTURE,
    EC_UNCONTAINED_COMMENTARY,
    EC_COMMENTARY_SPAN_CHAPTER,
    EC_UNABLE_TO_IDENTIFY_ID,
    EC_UNABLE_TO_IDENTIFY_PASSAGE,
    EC_UNABLE_TO_IDENTIFY_OSISID,
    EC_UNABLE_TO_LOCATE_EXTERNAL_FILE,
    EC_UNABLE_TO_LOAD_EXTERNAL_FILE,
    EC_CORRUPT_ITEM_DATA,
    EC_POSSIBLE_ENTITY_ENCODING_ERROR,
    N_EC_CODES
};

class SOWERBASEEXP SwModuleWriter : public SwCssInliner
{
public :
    SwModuleWriter();
    virtual ~SwModuleWriter();

    virtual bool OpenFile(const char * path, bool thml);
    void Reset();
    bool PresizeBuffer();
    virtual swUI32 FindBreakItem(swUI32 node);
    swUI16 CountDivisionItems(swUI32 item);
    void SetDivisionItems();
    bool BuildModule();
    virtual bool CreateItemData();
    bool OnBuild();
    virtual bool WriteMedia(FILE * f);
    bool WriteModule(const char * path);
    swUI8 GetContentType(swUI32 node);
    SwModuleHeader          m_header;
    swUI16                  m_k1;
    swUI64                  m_k2;
    swUI32 GetErrors() { return m_errors; }
    swUI32 GetWarnings() { return m_warnings; }

    protected :
    SwModuleItemArray         m_swmoduleitemarray;
    SwTableOfContents         m_contents;
    SwAutoDefCommentary       m_commentary;
    SwAutoDefScripture        m_verse;
    SwAutoDefNumbered         m_strongsH;
    SwAutoDefNumbered         m_strongsG;
    SwAutoDefNumbered         m_notes;
    SwAutoDefTerm             m_term;
    SwMediaContents           m_media;
    SwScriptureMap            m_scriptureMap;
    SwCommentaryMap           m_commentaryMap;
    swUI32                    m_errors;
    swUI32                    m_warnings;
};

#endif // MODULEWRITER_H
