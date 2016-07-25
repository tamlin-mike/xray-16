#include "xrEngine/WaveForm.h"
#include "xrCommon/math_funcs_inline.h"
#include "xrCore/math_constants.h"

float WaveForm::signf(float t) const throw()
{
	return t / _abs(t);
}

float WaveForm::Func(float t) const throw()
{
	switch (F)
	{
	case fCONSTANT:
		return 0;
	case fSIN:
		return _sin(t*PI_MUL_2);
	case fTRIANGLE:
		return asinf(_sin((t - 0.25f)*PI_MUL_2)) / PI_DIV_2;
	case fSQUARE:
		return signf(_cos(t*PI));
	case fSAWTOOTH:
		return atanf(tanf((t + 0.5f)*PI)) / PI_DIV_2;
	case fINVSAWTOOTH:
		return -(atanf(tanf((t + 0.5f)*PI)) / PI_DIV_2);
	}
	return 0.f;
}

float WaveForm::Calculate(float t) const throw()
{
	// y = arg0 + arg1*func( (time+arg2)*arg3 )
	float x = (t + arg[2])*arg[3];
	return arg[0] + arg[1] * Func(x - floorf(x));
}

bool WaveForm::Similar(const WaveForm& W) const throw()
{
	if (!fsimilar(arg[0], W.arg[0], EPS_L)) return FALSE;
	if (!fsimilar(arg[1], W.arg[1], EPS_L)) return FALSE;
	if (fis_zero(arg[1], EPS_L)) return TRUE;
	if (F != W.F) return FALSE;
	if (!fsimilar(arg[2], W.arg[2], EPS_L)) return FALSE;
	if (!fsimilar(arg[3], W.arg[3], EPS_L)) return FALSE;
	return TRUE;
}
