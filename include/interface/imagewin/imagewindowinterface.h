///////////////////////////////////////////////////////////////////
// Name:        imagewindowinterface.h
// Purpose:     SwViewInterface for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef IMAGEWINDOWINTERFACE_H
#define IMAGEWINDOWINTERFACE_H

#include "../interface.h"
#include "../../imgwin/imagewindow.h"

class SwImageWindow;
class SwImageWindowInterface : public SwViewInterface
{
public:
    SwImageWindowInterface();
    virtual ~SwImageWindowInterface();
    void SetImageWindow(SwImageWindow * window);
    virtual void OnReset();
    virtual swUI32 Handle(swUI16 id, swUI32 node);

private:
    SwImageWindow * m_imagewindow;
};

#endif // IMAGEWINDOWINTERFACE_H
