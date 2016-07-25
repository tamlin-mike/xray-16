#pragma once
#ifndef FTimerH
#define FTimerH
#include "_types.h"
#include "xrCore_impexp.h"
#include "Common/Noncopyable.hpp"
#include "_math.h"
#include "log.h"

class CTimer_paused;

// XXX: Why on earth play these tricks with the FPU (FPU::m64r() / FPU::m24r())?


class XRCORE_API pauseMngr : private Noncopyable
{
	struct pauseMngrImpl * m_pimpl;
    bool m_paused;
public:
	pauseMngr();
	~pauseMngr();
    bool Paused() { return m_paused; };
    void Pause(bool b);
    void Register(CTimer_paused* t);
    void UnRegister(CTimer_paused* t);
};

extern XRCORE_API pauseMngr *g_pauseMngr();

class XRCORE_API CTimerBase
{
protected:
    u64 qwStartTime;
    u64 qwPausedTime;
    u64 qwPauseAccum;
    bool bPause;
public:
	constexpr CTimerBase() noexcept : qwStartTime(0), qwPausedTime(0), qwPauseAccum(0), bPause(FALSE) { }
    ICF void Start() noexcept { if (bPause) return; qwStartTime = CPU::QPC() - qwPauseAccum; }
    ICF u64 GetElapsed_ticks() const noexcept { if (bPause) return qwPausedTime; else return CPU::QPC() - qwStartTime - CPU::qpc_overhead - qwPauseAccum; }
    IC u32 GetElapsed_ms()const { return u32(GetElapsed_ticks()*u64(1000) / CPU::qpc_freq); }
    IC float GetElapsed_sec()const
    {
#ifndef _EDITOR
        FPU::m64r();
#endif
        float _result = float(double(GetElapsed_ticks()) / double(CPU::qpc_freq));
#ifndef _EDITOR
        FPU::m24r();
#endif
        return _result;
    }
    IC void Dump() const
    {
        Msg("* Elapsed time (sec): %f", GetElapsed_sec());
    }
};

class XRCORE_API CTimer : public CTimerBase
{
private:
    typedef CTimerBase inherited;

private:
    float m_time_factor;
    u64 m_real_ticks;
    u64 m_ticks;

private:
	u64 GetElapsed_ticks(const u64 current_ticks) const noexcept;

public:
	constexpr CTimer() noexcept : m_time_factor(1.f), m_real_ticks(0), m_ticks(0) {}

    ICF void Start() noexcept
    {
        if (bPause)
            return;

        inherited::Start();

        m_real_ticks = 0;
        m_ticks = 0;
    }

    const float time_factor() const noexcept
    {
        return (m_time_factor);
    }

    IC void time_factor(const float time_factor) noexcept
    {
        u64 current = inherited::GetElapsed_ticks();
        m_ticks = GetElapsed_ticks(current);
        m_real_ticks = current;
        m_time_factor = time_factor;
    }

    IC u64 GetElapsed_ticks() const
    {
#ifndef _EDITOR
        FPU::m64r();
#endif // _EDITOR

        u64 result = GetElapsed_ticks(inherited::GetElapsed_ticks());

#ifndef _EDITOR
        FPU::m24r();
#endif // _EDITOR

        return (result);
    }

    IC u32 GetElapsed_ms() const
    {
        return (u32(GetElapsed_ticks()*u64(1000) / CPU::qpc_freq));
    }

    IC float GetElapsed_sec() const
    {
#ifndef _EDITOR
        FPU::m64r();
#endif
        float result = float(double(GetElapsed_ticks()) / double(CPU::qpc_freq));
#ifndef _EDITOR
        FPU::m24r();
#endif
        return (result);
    }

    IC void Dump() const
    {
        Msg("* Elapsed time (sec): %f", GetElapsed_sec());
    }
};

class XRCORE_API CTimer_paused_ex : public CTimer
{
    u64 save_clock;
public:
    CTimer_paused_ex() noexcept { }
    virtual ~CTimer_paused_ex() { }
    bool Paused() const noexcept { return bPause; }
    IC void Pause(bool b) noexcept
    {
        if (bPause == b) return;

        u64 _current = CPU::QPC() - CPU::qpc_overhead;
        if (b)
        {
            save_clock = _current;
            qwPausedTime = CTimerBase::GetElapsed_ticks();
        }
        else
        {
            qwPauseAccum += _current - save_clock;
        }
        bPause = b;
    }
};

class XRCORE_API CTimer_paused : public CTimer_paused_ex
{
public:
    CTimer_paused() { g_pauseMngr()->Register(this); }
    virtual ~CTimer_paused() { g_pauseMngr()->UnRegister(this); }
};

extern XRCORE_API BOOL g_bEnableStatGather;
class XRCORE_API CStatTimer
{
public:
    CTimer T;
    u64 accum;
    float result;
    u32 count;
public:
    CStatTimer();
    void FrameStart();
    void FrameEnd();

    ICF void Begin() { if (!g_bEnableStatGather) return; count++; T.Start(); }
    ICF void End() { if (!g_bEnableStatGather) return; accum += T.GetElapsed_ticks(); }

    ICF u64 GetElapsed_ticks()const { return accum; }

    IC u32 GetElapsed_ms()const { return u32(GetElapsed_ticks()*u64(1000) / CPU::qpc_freq); }
    IC float GetElapsed_sec()const
    {
#ifndef _EDITOR
        FPU::m64r();
#endif
        float _result = float(double(GetElapsed_ticks()) / double(CPU::qpc_freq));
#ifndef _EDITOR
        FPU::m24r();
#endif
        return _result;
    }
};

#endif // FTimerH
