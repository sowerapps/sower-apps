///////////////////////////////////////////////////////////////////
// Name:        thml_file.h
// Purpose:     SwThMLFile, SwThMLContentsNode, &
//              SwThMLTableOfContents - classes representing the
//              contents of a thml file.
//              SwThMLFileLoader - recursive file loader.
//              SwThMLLibrarian - recursive cnts creator.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THML_FILE_H
#define THML_FILE_H

#include "../sowerbase.h"
#include "../module/modulebase.h"
#include "../css/css_inliner.h"
#include "../filesys/recurse.h"
#include <wx/treebase.h>

struct SOWERBASEEXP SwThMLContentsNode
{
    bool ReadData(FILE * f, SwString & buffer);

    swUI8     divDepth;
    swUI32    bufferPos;
    swUI32    idbufferPos;
    swUI32    filePos;
    swUI32    fileSize;
    bool      hasChildren;
    swUI8     book;
    swUI8     chapter;
};

class SOWERBASEEXP SwThMLTableOfContents
{
public:
    SwThMLTableOfContents();
    virtual ~SwThMLTableOfContents();

    void SetIncrement(swUI8 increment);
    bool SizeBuffer(swUI32 size);
    bool SizeIdBuffer(swUI32 size);
    bool IncreaseNodeArray();
    bool SizeNodeArray(swUI16 nodes);
    bool VerifyNode();
    bool VerifyNodes(swUI16 nodes);
    swUI16 GetLastNode();
    swUI16 GetNodes();
    void Reset();
    void ResetNodeData();
    SwThMLContentsNode * GetNode(swUI16 node);
    const char * GetTitleText(swUI16 node);
    bool GetTitle(swUI16 node, SwString & dest);
    const char * GetIdText(swUI16 node);
    bool GetId(swUI16 node, SwString & dest);
    swUI16 GetTitleSize(swUI16 node);
    swUI16 GetIdSize(swUI16 node);
    swUI8 GetDivDepth(swUI16 node);
    bool SetDivDepth(swUI16 node, swUI8 divDepth);
    bool BufferAppend(const char * data, swUI16 len);
    bool IdBufferAppend(const char * data, swUI16 len);
    swUI16 Append(const char * title, const char * id, swUI8 divDepth, swUI32 pos, swUI32 length, swUI8 book = 0, swUI8 chapter = 0);
    virtual swUI16 FindItem(const char * title);
    virtual swUI16 FindByID(const char * id);
    virtual swUI16 FindChapter(swUI8 book, swUI8 chapter);
    void SetHasChildren();
    virtual bool WriteToFile(FILE * file);
    virtual bool ReadFromFile(FILE * file);

    protected:
    SwThMLContentsNode * m_nodeData;
    swUI16             m_nodePos;
    swUI16             m_nodesAllocated;
    swUI8              m_Inc;
    char *             m_buffer;
    swUI32             m_bufferSize;
    swUI32             m_dataSize;
    char *             m_idbuffer;
    swUI32             m_idbufferSize;
    swUI32             m_iddataSize;
};

class SOWERBASEEXP SwThMLFile
{
public:
    SwThMLFile() { m_file = NULL; m_managerId = NODE_ID_INVALID_16; m_category = CATEGORY_GENERAL; m_autodefEnabled = true; }
    virtual ~SwThMLFile() { if (m_file) fclose(m_file); }

    void Reset();
    bool Open(const char * path);
    void SetManagerId(swUI16 managerId) { m_managerId = managerId; }
    swUI16 GetManagerId() { return m_managerId; }
    void SetCategory(swUI8 category) { m_category = category; }
    swUI8 GetCategory() { return m_category; }
    void SetTitle(const char * title) { if (!title) return; m_title = title; }
    const char * GetTitle() { return m_title; }
    const char * GetPath() { return m_path; }
    const char * GetBasePath() { return m_basePath; }
    void SetIdentifier(const char * identifier) { if (!identifier) return; m_identifier = identifier; }
    const char * GetIdentifier() { return m_identifier; }
    const char * GetFormattedId();
    const char * GetFormattedAbbreviation();
    void SetAbbreviation();
    const char * GetAbbreviation() { return m_abbrev; }
    const char * GetFileName() { char * p = strrchr(m_path, PATH_SEP); if (p) return p + 1; return ""; }
    bool ReadTree();
    virtual bool WriteToFile(FILE * file);
    virtual bool ReadFromFile(FILE * file);
    bool GetAutodefEnabled();
    void SetAutodefEnabled(bool enabled);
    SwThMLTableOfContents & GetTableofContents() { return m_contents; }
    bool ReadInfoData(SwString buffer);
    CssFile             m_cssrules;
    SwThMLTableOfContents m_contents;
    SwString            m_title;
    SwString            m_identifier;
    SwString            m_basePath;
    SwString            m_path;
    SwString            m_abbrev;
    FILE *              m_file;
    swUI16              m_managerId;
    swUI8               m_category;
    swUI32              m_infoPos;
    swUI32              m_infoSize;
    bool                m_autodefEnabled;
};

class SOWERBASEEXP SwThMLFileLoader : public SwDirRecurse
{
public:
    SwThMLFileLoader();
    virtual ~SwThMLFileLoader();

    virtual bool OnFile(const char * path);
    virtual void OnProcessEnd();
    static swUI16 LoadFile(const char * path);
};


class SOWERBASEEXP SwThMLLibrarian : public SwDirRecurse
{
public:
    SwThMLLibrarian();
    virtual ~SwThMLLibrarian();

    virtual bool OnFile(const char * path);
};

#endif // THML_FILE_H
