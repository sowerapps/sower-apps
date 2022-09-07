///////////////////////////////////////////////////////////////////
// Name:        audiocontrol.cpp
// Purpose:     An audio player that can play streamed audio from
//              Sower modules.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/av_media/audiocontrol.h"
#include "../../include/appi/appifa.h"

SwAudioStream::SwAudioStream()
{
    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;
}

SwAudioStream::~SwAudioStream()
{
}

bool SwAudioStream::open(swUI16 moduleId, const char * mediaId)
{
    if (moduleId == NODE_ID_INVALID_16 || !mediaId)
        return false;

    swUI16 pos;

    m_module = NULL;
    m_mediaNode = NULL;
    m_position = 0;
    m_size = 0;


    pos = SwApplicationInterface::GetModuleManager().FindByMID(moduleId);

    if (pos == NODE_ID_INVALID_16)
        return false;

    m_module = SwApplicationInterface::GetModuleManager().GetAt(pos);

    if (!m_module || !m_module->m_file)
        return false;

    pos = m_module->GetMediaContents().FindItem(mediaId);

    if (pos == NODE_ID_INVALID_16)
    {
        m_module = NULL;
        return false;
    }

    m_mediaNode = m_module->GetMediaContents().GetNode(pos);

    if (!m_mediaNode)
    {
        m_module = NULL;
        return false;
    }

    m_size = (Int64) m_mediaNode->GetSize(m_module->m_file, m_module->m_header.itemdataLocator, m_module->m_header.filecontentsLocator);

    return true;
}

Int64 SwAudioStream::read(void *data, Int64 size)
{
    if (!m_module || !m_mediaNode || !data)
        return 0;

    swUI32 bytesRead = m_mediaNode->ReadStream(m_module->m_file, data, m_module->m_header.itemdataLocator, m_module->m_header.filecontentsLocator, m_position, size, m_module->m_header.k1, m_module->m_header.k2, m_module->m_header.isEncrypted);
    m_position += bytesRead;

    return (Int64) bytesRead;
}

Int64 SwAudioStream::seek(Int64 position)
{
    m_position = position;

    return m_position;
}

Int64 SwAudioStream::tell()
{
    return m_position;
}

Int64 SwAudioStream::getSize()
{
    return m_size;
}

const long SwAudioCtrl::ID_PAUSEBUTTON = wxNewId();
const long SwAudioCtrl::ID_PLAYBUTTON = wxNewId();
const long SwAudioCtrl::ID_STOPBUTTON = wxNewId();
const long SwAudioCtrl::ID_VOLUMELABEL = wxNewId();
const long SwAudioCtrl::ID_VOLUMESLIDER = wxNewId();
const long SwAudioCtrl::ID_TITLELABEL = wxNewId();

SwAudioCtrl::SwAudioCtrl()
{
}

SwAudioCtrl::SwAudioCtrl(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxValidator &validator, const wxString &name)
{
    Create(parent, id, pos, size, style, validator, name);
    BuildContent();
}

void SwAudioCtrl::BuildContent()
{
    wxGridBagSizer* GridBagSizer1;
	wxGridBagSizer* GridBagSizer2;

	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer2 = new wxGridBagSizer(0, 0);
	PauseButton = new wxButton(this, ID_PAUSEBUTTON, SwApplicationInterface::GetControlString("SID_PAUSE", L"Pause"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PAUSEBUTTON");
	GridBagSizer2->Add(PauseButton, wxGBPosition(0, 0), wxDefaultSpan, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	PlayButton = new wxButton(this, ID_PLAYBUTTON, SwApplicationInterface::GetControlString("SID_PLAY", L"Play"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_PLAYBUTTON");
	GridBagSizer2->Add(PlayButton, wxGBPosition(0, 1), wxDefaultSpan, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StopButton = new wxButton(this, ID_STOPBUTTON, SwApplicationInterface::GetControlString("SID_STOP", L"Stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_STOPBUTTON");
	GridBagSizer2->Add(StopButton, wxGBPosition(0, 2), wxDefaultSpan, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(GridBagSizer2, wxGBPosition(0, 0), wxGBSpan(1, 2), wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	VolumeLabel = new wxStaticText(this, ID_VOLUMELABEL, SwApplicationInterface::GetControlString("SID_VOLUME", L"Volume"), wxDefaultPosition, wxDefaultSize, 0, L"ID_VOLUMELABEL");
	GridBagSizer1->Add(VolumeLabel, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	VolmeSlider = new wxSlider(this, ID_VOLUMESLIDER, 50, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, L"ID_VOLUMESLIDER");
	VolmeSlider->SetThumbLength(5);
	GridBagSizer1->Add(VolmeSlider, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxEXPAND, 5);
    TitleLabel = new wxStaticText(this, ID_TITLELABEL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, L"ID_TITLELABEL");
	GridBagSizer1->Add(TitleLabel, wxGBPosition(2, 0), wxGBSpan(1, 2), wxALL|wxEXPAND, 5);
	SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(this);
	GridBagSizer1->SetSizeHints(this);

	m_music.setVolume(50);

	Connect(ID_PAUSEBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAudioCtrl::OnPauseButtonClick);
	Connect(ID_PLAYBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAudioCtrl::OnPlayButtonClick);
	Connect(ID_STOPBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SwAudioCtrl::OnStopButtonClick);
	Connect(ID_VOLUMESLIDER,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&SwAudioCtrl::OnVolmeSliderCmdScroll);
}

SwAudioCtrl::~SwAudioCtrl()
{
}

bool SwAudioCtrl::OnOpen(const char * path)
{
    if (!path)
        return false;

    if (!m_music.openFromFile(path))
        return false;

    m_music.play();

    return true;
}

bool SwAudioCtrl::OnOpen(swUI16 managerId, const char * src)
{
    if (!src)
        return false;

    if (!m_stream.open(managerId, src))
        return false;

    return m_music.openFromStream(m_stream);
}

void SwAudioCtrl::OnAutoPlay()
{
    m_music.play();
}

void SwAudioCtrl::OnPauseButtonClick(wxCommandEvent& event)
{
    m_music.pause();
}

void SwAudioCtrl::OnPlayButtonClick(wxCommandEvent& event)
{
    m_music.play();
}

void SwAudioCtrl::OnStopButtonClick(wxCommandEvent& event)
{
    m_music.stop();
}

void SwAudioCtrl::OnVolmeSliderCmdScroll(wxScrollEvent& event)
{
    m_music.setVolume((float) event.GetPosition());
}

void SwAudioCtrl::SetLoop(bool loop)
{
    m_music.setLoop(loop);
}
