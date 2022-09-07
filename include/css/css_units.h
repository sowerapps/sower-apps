///////////////////////////////////////////////////////////////////
// Name:        css_units.h
// Purpose:     Identify, and convert HTML/CSS measurement units.
// Copyright:   David Reynolds
// License:     Sower Applications License
///////////////////////////////////////////////////////////////////

#ifndef CSS_UNITS_H
#define CSS_UNITS_H

#include "../sowerbase.h"
#include <wx/choice.h>
#include <wx/richtext/richtextbuffer.h>

enum CSS_UNITS
{
    UNIT_NONE, UNIT_CM, UNIT_EM, UNIT_EX, UNIT_INCH, UNIT_PC, UNIT_PERCENT,
    UNIT_PREDEFINED, UNIT_PT, UNIT_PX, UNIT_MM, N_UNIT
};

class SOWERBASEEXP CssUnits
{
public :
    CssUnits();
    virtual ~CssUnits();

    static void FillCtrl(wxChoice * choice);
	static void SetUnit(wxChoice * choice, int flag);
	static void SetWxUnit(wxChoice * choice, wxTextAttrUnits flag);
	static swUI8 GetUnit(wxChoice * choice);
	static wxTextAttrUnits GetWxUnit(wxChoice * choice);
	static int GetValue(int wxUnit, int value);
	static int GetWxValue(int wxUnit, int value);

    static float In2Cm(float value);
    static float In2MM(float value);
    static float In2MM10(float value);
    static float In2Pt(float value);

    static float Cm2In(float value);
    static float Cm2MM(float value);
    static float Cm2MM10(float value);
    static float Cm2Pt(float value);

    static float Mm2In(float value);
    static float Mm2Cm(float value);
    static float Mm2MM10(float value);
    static float Mm2Pt(float value);
    static float Mm102MM(float value);

    static float Pc2In(float value);
    static float Pc2Pt(float value);
    static float Pc2MM(float value);
    static float Pc2MM10(float value);

    static float Pt2In(float value);
    static float Pt2MM(float value);
    static float Pt2MM10(float value);

    static float Px2In(float value, swUI32 ppi);
    static float Px2Cm(float value, swUI32 ppi);
    static float Px2MM(float value, swUI32 ppi);
    static float Px2MM10(float value, swUI32 ppi);
    static float Px2Pt(float value, swUI32 ppi);

    static float GetValueAsPt(float value, swUI8 unit, swUI32 ppi = 0);
    static float GetValueAsMM(float value, swUI8 unit, swUI32 ppi = 0);
    static float GetValueAsMM10(float value, swUI8 unit, swUI32 ppi = 0);
    static const char * GetUnitString(swUI8 unit);
    static swUI8 GetUnit(const char * source);
};

#endif // CSS_UNITS_H
