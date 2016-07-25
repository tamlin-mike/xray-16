#pragma once
#ifndef _CYLINDER_H
#define _CYLINDER_H
#include "_vector3d.h"

template <class T>
class _cylinder
{
public:
    typedef T TYPE;
	typedef _vector3<T> VEC_TYPE;
    typedef _cylinder<T>Self;
    typedef Self& SelfRef;
    typedef const Self& SelfCRef;
public:
	VEC_TYPE m_center;
	VEC_TYPE m_direction;
    T m_height;
    T m_radius;
public:
    IC SelfRef invalidate() { m_center.set(0, 0, 0); m_direction.set(0, 0, 0); m_height = 0; m_radius = 0; return *this; }
    enum ecode { cyl_cap, cyl_wall, cyl_none };
	int intersect(const VEC_TYPE& start, const VEC_TYPE& dir, T afT[2], ecode code[2]) const;
    enum ERP_Result
    {
        rpNone = 0,
        rpOriginInside = 1,
        rpOriginOutside = 2,
        fcv_forcedword = u32(-1)
    };
	ERP_Result intersect(const VEC_TYPE& start, const VEC_TYPE& dir, T& dist) const;
    //----------------------------------------------------------------------------
};

typedef _cylinder<float> Fcylinder;
typedef _cylinder<double> Dcylinder;

template <class T>
bool _valid(const _cylinder<T>& c) { return _valid(c.m_center) && _valid(c.m_direction) && _valid(c.m_height) && _valid(c.m_radius); }

#endif // include guard
