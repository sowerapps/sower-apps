///////////////////////////////////////////////////////////////////
// Name:        thmlmodulewriter.h
// Purpose:     Write modules from ThML files.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef THMLMODULEWRITER_H
#define THMLMODULEWRITER_H

#include "../module/modulewriter.h"

class SOWERBASEEXP SwThMLModuleWriter : public SwModuleWriter
{
public:
    SwThMLModuleWriter();
    virtual ~SwThMLModuleWriter();
    virtual bool OpenFile(const char * path, bool thml);
    virtual bool CreateItemData();
    virtual swUI32 FindBreakItem(swUI32 node);
    void AdjustSizes();
    // Return false to abort.
    virtual bool OnError(swUI16 elementId, swUI8 nodeType, const char * text, swUI8 ec) { return true; };
    virtual bool WriteMedia(FILE * f);
    virtual swUI8 GetMediaType(swUI32 node);
    void CheckItemData(swUI8 pass);
    void CheckTextRun(swUI32 node);
};

class SwWriter : public SwThMLModuleWriter
{
public:
    SwWriter() {}
    virtual ~SwWriter() {}
    virtual bool OnError(swUI16 elementId, swUI8 nodeType, const char * text, swUI8 ec)
    {
        if (!m_window || !text)
            return true;

        messageBuffer.Reset();

        if (ec == EC_UNCONTAINED_TEXT_RUN)
            messageBuffer += "EC_UNCONTAINED_TEXT_RUN\n";
        else if (ec == EC_UNCONTAINED_SCRIPTURE)
            messageBuffer += "EC_UNCONTAINED_SCRIPTURE\n";
        else if (ec == EC_UNCONTAINED_COMMENTARY)
            messageBuffer += "EC_UNCONTAINED_COMMENTARY\n";
        else if (ec == EC_UNABLE_TO_IDENTIFY_ID)
            messageBuffer += "EC_UNABLE_TO_IDENTIFY_ID\n";
        else if (ec == EC_UNABLE_TO_IDENTIFY_PASSAGE)
            messageBuffer += "EC_UNABLE_TO_IDENTIFY_PASSAGE\n";
        else if (ec == EC_UNABLE_TO_IDENTIFY_OSISID)
            messageBuffer += "EC_UNABLE_TO_IDENTIFY_OSISID\n";
        else if (ec == EC_UNABLE_TO_LOCATE_EXTERNAL_FILE)
            messageBuffer += "EC_UNABLE_TO_LOCATE_EXTERNAL_FILE\n";
        else if (ec == EC_UNABLE_TO_LOAD_EXTERNAL_FILE)
            messageBuffer += "EC_UNABLE_TO_LOAD_EXTERNAL_FILE\n";
        else if (ec == EC_CORRUPT_ITEM_DATA)
            messageBuffer += "EC_CORRUPT_ITEM_DATA\n";
        else if (ec == EC_POSSIBLE_ENTITY_ENCODING_ERROR)
            messageBuffer += "EC_POSSIBLE_ENTITY_ENCODING_ERROR\n";

        messageBuffer += text;
        messageBuffer += "\n";

        wxThreadEvent * e = new wxThreadEvent();
        e->SetInt(2);
        e->SetString(messageBuffer.GetArray());
        wxQueueEvent(m_window->GetEventHandler(), e);

        return true;
    }

private:
    SwString messageBuffer;
};

#endif // THMLMODULEWRITER_H
