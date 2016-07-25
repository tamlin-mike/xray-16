#ifndef WAVEFORM_H
#define WAVEFORM_H
#pragma once

#pragma pack(push,4)
struct WaveForm
{
    enum EFunction
    {
        fCONSTANT = 0,
        fSIN,
        fTRIANGLE,
        fSQUARE,
        fSAWTOOTH,
        fINVSAWTOOTH,
        fFORCE32 = unsigned int(~0)
    };
	float signf(float t) const noexcept;
	float Func(float t) const noexcept;
public:
    EFunction F;
    float arg[4];

	float Calculate(float t) const noexcept;

    WaveForm()
    {
        F = fCONSTANT;
        arg[0] = 0;
        arg[1] = 1;
        arg[2] = 0;
        arg[3] = 1;
    }

	bool Similar(const WaveForm& W) const noexcept;
};

#pragma pack(pop)
#endif
