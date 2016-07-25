#include "stdafx.h"
#pragma hdrstop
#include "xrCommon/xr_vector.h"

XRCORE_API BOOL g_bEnableStatGather = FALSE;

CStatTimer::CStatTimer()
{
    accum = 0;
    result = 0.f;
    count = 0;
}

void CStatTimer::FrameStart()
{
    accum = 0;
    count = 0;
}
void CStatTimer::FrameEnd()
{
    float _time = 1000.f*float(double(accum) / double(CPU::qpc_freq));
    if (_time > result) result = _time;
    else result = 0.99f*result + 0.01f*_time;
}

XRCORE_API pauseMngr *g_pauseMngr()
{
    static pauseMngr *manager = nullptr;

    if (!manager)
    {
        manager = new pauseMngr();
    }

    return manager;
}

struct pauseMngrImpl
{
	xr_vector<CTimer_paused*> m_timers;
};

pauseMngr::pauseMngr() :
	m_paused(false),
	m_pimpl(new pauseMngrImpl)
{
	m_pimpl->m_timers.reserve(3);
}

pauseMngr::~pauseMngr()
{
	delete m_pimpl;
}

void pauseMngr::Pause(bool b)
{
    if (m_paused == b)return;

	xr_vector<CTimer_paused*>::iterator it = m_pimpl->m_timers.begin();
	xr_vector<CTimer_paused*>::iterator E = m_pimpl->m_timers.end();
    for (; it != E; ++it)
        (*it)->Pause(b);

    m_paused = b;
}

void pauseMngr::Register(CTimer_paused* t)
{
	m_pimpl->m_timers.push_back(t);
}

void pauseMngr::UnRegister(CTimer_paused* t)
{
    xr_vector<CTimer_paused*>::iterator it = std::find(m_pimpl->m_timers.begin(), m_pimpl->m_timers.end(), t);
    if (it != m_pimpl->m_timers.end())
		m_pimpl->m_timers.erase(it);
}

//////////////////////////////////////////////////////////////////

u64 CTimer::GetElapsed_ticks(const u64 current_ticks) const noexcept
{
	u64 delta = current_ticks - m_real_ticks;
	double delta_d = (double)delta;
	double time_factor_d = time_factor();
	double time = delta_d*time_factor_d + .5;
	u64 result = (u64)time;
	return (m_ticks + result);
}
