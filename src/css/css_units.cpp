///////////////////////////////////////////////////////////////////
// Name:        css_units.cpp
// Purpose:     Identify, and convert HTML/CSS measurement units.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#include "../../include/css/css_units.h"
#include "../../include/appi/appifa.h"

struct UNIT_DATA
{
    const char *  name;
    swUI8 id;
};

static const UNIT_DATA Units [] =
{
    {"",    UNIT_NONE},
    {"cm",  UNIT_CM},
    {"em",  UNIT_EM},
    {"ex",  UNIT_EX},
    {"in",  UNIT_INCH},
    {"pc",  UNIT_PC},
    {"%",   UNIT_PERCENT},
    {"",    UNIT_PREDEFINED},
    {"pt",  UNIT_PT},
    {"px",  UNIT_PX}
};

CssUnits::CssUnits()
{
}

CssUnits::~CssUnits()
{
}

void CssUnits::FillCtrl(wxChoice * choice)
{
    SwClientData * data;

    data = new SwClientData(UNIT_MM);
    choice->Append(SwApplicationInterface::GetControlString("SID_MM", L"mm"), data);

    data = new SwClientData(UNIT_PX);
    choice->Append(SwApplicationInterface::GetControlString("SID_PX", L"px"), data);

    data = new SwClientData(UNIT_PERCENT);
    choice->Append(SwApplicationInterface::GetControlString("SID_PERCENT", L"%"), data);

    data = new SwClientData(UNIT_PT);
    choice->Append(SwApplicationInterface::GetControlString("SID_PT", L"pt"), data);

    choice->SetSelection(0);
}

void CssUnits::SetUnit(wxChoice * choice, int flag)
{
    SwClientData * data;

    for (unsigned int i = 0; i < choice->GetCount(); i ++)
    {
        data = (SwClientData *) choice->GetClientObject(i);
        if (data->m_data == (unsigned) flag)
        {
            choice->SetSelection(i);
            break;
        }
    }
}

void CssUnits::SetWxUnit(wxChoice * choice, wxTextAttrUnits flag)
{
    SwClientData * data;

    for (unsigned int i = 0; i < choice->GetCount(); i ++)
    {
        data = (SwClientData *) choice->GetClientObject(i);

        if (data->m_data == UNIT_MM && flag == wxTEXT_ATTR_UNITS_TENTHS_MM)
        {
            choice->SetSelection(i);
            break;
        }
        else if (data->m_data == UNIT_PX && flag == wxTEXT_ATTR_UNITS_PIXELS)
        {
            choice->SetSelection(i);
            break;
        }
        else if (data->m_data == UNIT_PERCENT && flag == wxTEXT_ATTR_UNITS_PERCENTAGE)
        {
            choice->SetSelection(i);
            break;
        }
        else if (data->m_data == UNIT_PT && flag == wxTEXT_ATTR_UNITS_POINTS)
        {
            choice->SetSelection(i);
            break;
        }
    }
}

swUI8 CssUnits::GetUnit(wxChoice * choice)
{
    SwClientData * data;

    if (choice->GetSelection() == wxNOT_FOUND)
        return UNIT_PX;

    data = (SwClientData *) choice->GetClientObject(choice->GetSelection());

    return (swUI8) data->m_data;
}

wxTextAttrUnits CssUnits::GetWxUnit(wxChoice * choice)
{
    SwClientData * data;

    if (choice->GetSelection() == wxNOT_FOUND)
        return wxTEXT_ATTR_UNITS_PIXELS;

    data = (SwClientData *) choice->GetClientObject(choice->GetSelection());

    if (data->m_data == UNIT_MM)
        return wxTEXT_ATTR_UNITS_TENTHS_MM;
    else if (data->m_data == UNIT_PX)
        return wxTEXT_ATTR_UNITS_PIXELS;
    else if (data->m_data == UNIT_PERCENT)
        return wxTEXT_ATTR_UNITS_PERCENTAGE;
    else if (data->m_data == UNIT_PT)
        return wxTEXT_ATTR_UNITS_POINTS;

    return wxTEXT_ATTR_UNITS_PIXELS;
}

int CssUnits::GetValue(int wxUnit, int value)
{
    if (wxUnit == wxTEXT_ATTR_UNITS_TENTHS_MM)
    {
        return value / 10;
    }
    else if (wxUnit == wxTEXT_ATTR_UNITS_HUNDREDTHS_POINT)
    {
        return value / 100;
    }

    return value;
}

int CssUnits::GetWxValue(int wxUnit, int value)
{
    if (wxUnit == wxTEXT_ATTR_UNITS_TENTHS_MM)
    {
        return value * 10;
    }

    return value;
}

float CssUnits::In2Cm(float value)
{
    return value * 2.54;
}

float CssUnits::In2MM(float value)
{
    return value * 25.4;
}

float CssUnits::In2MM10(float value)
{
    return value * 254;
}

float CssUnits::In2Pt(float value)
{
    return value * 72;
}

float CssUnits::Cm2In(float value)
{
    return value / 2.54;
}

float CssUnits::Cm2MM(float value)
{
    return value * 10;
}

float CssUnits::Cm2MM10(float value)
{
    return value * 100;
}

float CssUnits::Cm2Pt(float value)
{
    return value * 28.346;
}

float CssUnits::Mm2In(float value)
{
    return value / 25.4;
}

float CssUnits::Mm2Cm(float value)
{
    return value / 10;
}

float CssUnits::Mm2MM10(float value)
{
    return value * 10;
}

float CssUnits::Mm2Pt(float value)
{
    return value * 2.834;
}

float CssUnits::Mm102MM(float value)
{
    return value / 10;
}

float CssUnits::Pc2In(float value)
{
    return value / (72 * 12);
}

float CssUnits::Pc2MM(float value)
{
    return value * 152.4;
}

float CssUnits::Pc2MM10(float value)
{
    return value * 1524;
}

float CssUnits::Pc2Pt(float value)
{
    return value * 12;
}

float CssUnits::Pt2In(float value)
{
    return value / 72;
}

float CssUnits::Pt2MM(float value)
{
    return value * .35;
}

float CssUnits::Pt2MM10(float value)
{
    return value * 3.5;
}

float CssUnits::Px2In(float value, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    return value / ppi;
}

float CssUnits::Px2Cm(float value, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    return value * (25.4 / ppi);
}

float CssUnits::Px2MM(float value, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    return value * (25.4 / ppi);
}

float CssUnits::Px2MM10(float value, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    return value * (254 / ppi);
}

float CssUnits::Px2Pt(float value, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    return value * (72 / ppi);
}

float CssUnits::GetValueAsPt(float value, swUI8 unit, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    if (unit == UNIT_PT)
        return value;
    if (unit == UNIT_INCH)
        return In2Pt(value);
    if (unit == UNIT_CM)
        return Cm2Pt(value);
    if (unit == UNIT_MM)
        return Mm2Pt(value);
    if (unit == UNIT_PC)
        return Pc2Pt(value);
    if (unit == UNIT_PX)
        return Px2Pt(value, ppi);
    if (unit == UNIT_PERCENT)
        return value;
    if (unit == UNIT_PREDEFINED)
        return value;

    return 0;
}

float CssUnits::GetValueAsMM(float value, swUI8 unit, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    if (unit == UNIT_INCH)
        return In2MM(value);
    if (unit == UNIT_CM)
        return Cm2MM(value);
    if (unit == UNIT_MM)
        return Mm102MM(value);
    if (unit == UNIT_PC)
        return Pc2MM(value);
    if (unit == UNIT_PX)
        return Px2MM(value, ppi);
    if (unit == UNIT_PT)
        return Pt2MM(value);
    if (unit == UNIT_PERCENT)
        return value;
    if (unit == UNIT_PREDEFINED)
        return value;

    return 0;
}

float CssUnits::GetValueAsMM10(float value, swUI8 unit, swUI32 ppi)
{
    if (ppi == 0)
    {
        ppi = SwApplicationInterface::GetPPI();
    }

    if (unit == UNIT_INCH)
        return In2MM10(value);
    if (unit == UNIT_CM)
        return Cm2MM10(value);
    if (unit == UNIT_MM)
        return Mm2MM10(value);
    if (unit == UNIT_PC)
        return Pc2MM10(value);
    if (unit == UNIT_PX)
        return Px2MM10(value, ppi);
    if (unit == UNIT_PT)
        return Pt2MM10(value);
    if (unit == UNIT_PERCENT)
        return value;
    if (unit == UNIT_PREDEFINED)
        return value;

    return 0;
}

const char * CssUnits::GetUnitString(swUI8 unit)
{
    if (unit >= N_UNIT)
        return "";

    swUI8 pos = 0;

    while (pos < N_UNIT)
    {
        if (Units[pos].id == unit)
        {
            return Units[pos].name;
        }

        pos ++;
    }

    return "";
}

swUI8 CssUnits::GetUnit(const char * source)
{
    if (!source)
        return UNIT_NONE;

    swUI8 pos = 0;

    while (pos < N_UNIT)
    {
        if (stricmp(Units[pos].name, source) == 0)
        {
            return Units[pos].id;
        }

        pos ++;
    }

    return UNIT_NONE;
}
