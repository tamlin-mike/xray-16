#pragma once
#ifndef _LOCAL_RAND
#define _LOCAL_RAND
#include "xrCommon/inlining_macros.h"
#include "xrCore_impexp.h"

/*
u32 dwRandSeed;
IC u32 dwfRandom(u32 dwRange)
{
u32 dwResult;
__asm {
mov eax,dwRange _eax = dwRange
imul edx,dwRandSeed,08088405H
inc edx
mov dwRandSeed,edx dwRandSeed = (dwRandSeed * 08088405H)+1
mul edx return (u64(dwRange) * u64(dwRandSeed)) >> 32
mov dwResult,edx
}
return(dwResult);
}
*/

class CRandom
{
private:
    volatile int holdrand;
public:
    CRandom() : holdrand(1) {};
    CRandom(int _seed) : holdrand(_seed) {};

    IC void seed(int val) { holdrand = val; }
    IC int maxI() { return 32767; }

	int randI() noexcept;
	int randI(int max);
    IC int randI(int min, int max) { return min + randI(max - min); }
    IC int randIs(int range) { return randI(-range, range); }
    IC int randIs(int range, int offs) { return offs + randIs(range); }

    IC float maxF() { return 32767.f; }
    IC float randF() { return float(randI()) / maxF(); }
    IC float randF(float max) { return randF()*max; }
    IC float randF(float min, float max) { return min + randF(max - min); }
    IC float randFs(float range) { return randF(-range, range); }
    IC float randFs(float range, float offs) { return offs + randFs(range); }
};

XRCORE_API extern CRandom Random;

#endif
