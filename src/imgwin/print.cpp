///////////////////////////////////////////////////////////////////
// Name:        print.cpp
// Purpose:     Print functionality for SwImageWindow.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/imgwin/imagewindow.h"

void SwImageWindow::OnPrint(const wchar_t * title)
{
    if (!m_canCopy)
        return;

    wxPrintDialogData printDialogData(*SwApplicationInterface::GetPrintData());

    wxPrinter printer(&printDialogData);
    SwImagePrint printout(*this, title);

    if (!printer.Print(this, &printout, true))
    {
        wxMessageBox(SwStringW(SwApplicationInterface::GetControlString("SID_ERROR", L"Error")).GetArray(), SwStringW(SwApplicationInterface::GetControlString("SID_PRINT", L"Print")).GetArray());
        return;
    }
}
