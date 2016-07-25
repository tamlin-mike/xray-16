#pragma once
#ifndef __FLAGS_H__
#define __FLAGS_H__
#include "_types.h"

template <class T>
struct _flags
{
public:
    typedef T TYPE;
    typedef _flags<T> Self;
    typedef Self& SelfRef;
    typedef const Self& SelfCRef;
public:
    T flags;

    TYPE get() const noexcept { return flags; }
    SelfRef zero() noexcept { flags = T(0); return *this; }
    SelfRef one() noexcept { flags = T(-1); return *this; }
    SelfRef invert() noexcept { flags = ~flags; return *this; }
    SelfRef invert(const Self& f) noexcept { flags = ~f.flags; return *this; }
    SelfRef invert(const T mask) noexcept { flags ^= mask; return *this; }
    SelfRef assign(const Self& f) noexcept { flags = f.flags; return *this; }
    SelfRef assign(const T mask) noexcept { flags = mask; return *this; }
    SelfRef set(const T mask, bool value) noexcept { if (value) flags |= mask; else flags &= ~mask; return *this; }
    bool is(const T mask) const noexcept { return mask == (flags&mask); }
    bool is_any(const T mask) const noexcept { return !!(flags&mask); }
    bool test(const T mask) const noexcept { return !!(flags&mask); }
    SelfRef or(const T mask) noexcept { flags |= mask; return *this; }
    SelfRef or(const Self& f, const T mask)  noexcept { flags = f.flags | mask; return *this; }
    SelfRef and(const T mask) noexcept { flags &= mask; return *this; }
    SelfRef and(const Self& f, const T mask) noexcept { flags = f.flags&mask; return *this; }
    bool equal(const Self& f) const noexcept { return flags == f.flags; }
    bool equal(const Self& f, const T mask) const noexcept { return (flags&mask) == (f.flags&mask); }
};

typedef _flags<u8> Flags8;
typedef _flags<u8> flags8;
typedef _flags<u16> Flags16;
typedef _flags<u16> flags16;
typedef _flags<u32> Flags32;
typedef _flags<u32> flags32;
typedef _flags<u64> Flags64;
typedef _flags<u64> flags64;

#endif //__FLAGS_H__
