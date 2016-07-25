#pragma once
#include <list>
#include "xalloc.h"
#include "xrCore/xrDebug_macros.h"

#if 0 // pre-C++11
template <typename T, typename allocator = xalloc<T> > class xr_list : public std::list< T, allocator > { public: u32 size() const { return (u32)std::list<T, allocator>::size(); } };
#else
template <typename T> using xr_list = std::list< T, xalloc<T> >;
#endif

#define DEF_LIST(N,T) typedef xr_list< T > N; typedef N::iterator N##_it;

#define DEFINE_LIST(T,N,I) typedef xr_list< T > N; typedef N::iterator I;
