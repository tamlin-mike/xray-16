////////////////////////////////////////////////////////////////////////////
//	Module 		: object_comparer.h
//	Created 	: 13.07.2004
//  Modified 	: 13.07.2004
//	Author		: Dmitriy Iassenev
//	Description : Object equality checker
////////////////////////////////////////////////////////////////////////////

#pragma once
#include "xrCore/FixedVector.h"
#include "xrCore/xrstring.h"
#include "xrCommon/xr_stack.h"

template <typename P>
struct CComparer {
	template <typename T>
	struct CHelper {
		template <bool a>
		IC	static bool compare(const T &arg1, const T &arg2, const P &p)
		{
			return p(arg1, arg2);
		}

		template <>
		IC	static bool compare<true>(const T &arg1, const T &arg2, const P &p)
		{
			return CComparer::compare(*arg1,*arg2,p);
		}
	};

	IC	static bool compare(LPCSTR arg1, LPCSTR arg2, const P &p)
	{
		return p(arg1, arg2);
	}

	IC	static bool compare(LPSTR arg1, LPSTR arg2, const P &p)
	{
		return p(arg1, arg2);
	}

	IC	static bool compare(const shared_str &arg1, const shared_str &arg2, const P &p)
	{
		return p(arg1, arg2);
	}

	template <typename T1, typename T2>
	IC	static bool compare(const std::pair<T1,T2> &arg1, const std::pair<T1,T2> &arg2, const P &p)
	{
		return						(
			compare(arg1.first, arg2.first,p)
			&&
			compare(arg1.second, arg2.second,p)
		);
	}

	template <typename T, int size>
	IC	static bool compare(const svector<T,size> &arg1, const svector<T,size> &arg2, const P &p)
	{
		if (arg1.size() != arg2.size())
			return					(p());
		
		svector<T,size>::const_iterator	I = arg1.begin(), J = arg2.begin();
		svector<T,size>::const_iterator	E = arg1.end();
		for ( ; I != E; ++I, ++J)
			if (!compare(*I,*J,p))
				return				(false);
		return						(true);
	}

	template <typename T1, typename T2>
	IC	static bool compare(const std::queue<T1,T2> &Arg1, const std::queue<T1,T2> &Arg2, const P &p)
	{
		std::queue<T1,T2> local1 = Arg1;
		std::queue<T1,T2> local2 = Arg2;
		
		if (local1.size() != local2.size())
			return					(p());

		for ( ; !local1.empty(); local1.pop(), local2.pop())
			if (!compare(local1.front(), local2.front(),p))
				return				(false);
		return						(true);
	}

	template <template <typename T1X, typename T2X> class T1, typename T2, typename T3>
	IC	static bool compare(const T1<T2,T3> &Arg1, const T1<T2,T3> &Arg2, const P &p, bool)
	{
		T1<T2,T3> local1 = Arg1;
		T1<T2,T3> local2 = Arg2;

		if (local1.size() != local2.size())
			return					(p());

		for ( ; !local1.empty(); local1.pop(), local2.pop())
			if (!compare(local1.top(), local2.top(),p))
				return				(false);
		return						(true);
	}

	template <template <typename T1X, typename T2X, typename T3X> class T1, typename T2, typename T3, typename T4>
	IC	static bool compare(const T1<T2,T3,T4> &Arg1, const T1<T2,T3,T4> &Arg2, const P &p, bool)
	{
		T1<T2,T3,T4> local1 = Arg1;
		T1<T2,T3,T4> local2 = Arg2;

		if (local1.size() != local2.size())
			return					(p());

		for ( ; !local1.empty(); local1.pop(), local2.pop())
			if (!compare(local1.top(), local2.top(),p))
				return				(false);
		return						(true);
	}

	template <typename T1, typename T2>
	IC	static bool compare(const xr_stack<T1,T2> &arg1, const xr_stack<T1,T2> &arg2, const P &p)
	{
		return compare(arg1, arg2,p,true);
	}

	template <typename T1, typename T2, typename T3>
	IC	static bool compare(const std::priority_queue<T1,T2,T3> &arg1, const std::priority_queue<T1,T2,T3> &arg2, const P &p)
	{
		return compare(arg1, arg2,p,true);
	}

	struct CHelper3 {
		template <typename T>
		IC	static bool compare(const T &arg1, const T &arg2, const P &p)
		{
			if (arg1.size() != arg2.size())
				return					(p());

			T::const_iterator			I = arg1.begin(), J = arg2.begin();
			T::const_iterator			E = arg1.end();
			for (; I != E; ++I, ++J)
			{
				if (!CComparer::compare(*I, *J, p))
					return false;
			}
			return true;
		}
	};

	template <typename T>
	struct CHelper4 {
		template <bool a>
		IC	static bool compare(const T &arg1, const T &arg2, const P &p)
		{
			return(CHelper<T>::compare<object_type_traits::is_pointer<T>::value>(arg1, arg2,p));
		}

		template <>
		IC	static bool compare<true>(const T &arg1, const T &arg2, const P &p)
		{
			return(CHelper3::compare(arg1, arg2,p));
		}
	};

	template <typename T>
	IC	static bool compare(const T &arg1, const T &arg2, const P &p)
	{
		return CHelper4<T>::compare<object_type_traits::is_stl_container<T>::value>(arg1, arg2,p);
	}
};

template <typename P>
IC	bool compare(LPCSTR p0, LPSTR p1, const P &p)
{
	return			(p(p0,p1));
}

template <typename P>
IC	bool compare(LPSTR p0, LPCSTR p1, const P &p)
{
	return			(p(p0,p1));
}

template <typename T, typename P>
IC	bool compare(const T &p0, const T &p1, const P &p)
{
	return			(CComparer<P>::compare(p0,p1,p));
}

namespace object_comparer {
	namespace detail {
		template <template <typename TX> class P>
		struct comparer {
			template <typename T>
			IC	bool operator() (const T &arg1, const T &arg2)	const	{return(P<T>()		(arg1, arg2));}
			IC	bool operator() ()								const	{return(P<bool>()	(false,true));}
			IC	bool operator() (LPCSTR arg1, LPCSTR arg2)		const	{return(P<int>()	(xr_strcmp(arg1, arg2),0));}
			IC	bool operator() (LPSTR arg1, LPSTR arg2)		const	{return(P<int>()	(xr_strcmp(arg1, arg2),0));}
			IC	bool operator() (LPCSTR arg1, LPSTR arg2)		const	{return(P<int>()	(xr_strcmp(arg1, arg2),0));}
			IC	bool operator() (LPSTR arg1, LPCSTR arg2)		const	{return(P<int>()	(xr_strcmp(arg1, arg2),0));}
		};
	};
};

#define declare_comparer(a,b) \
	template <typename T1, typename T2>\
	IC	bool a(const T1 &p0, const T2 &p1)\
	{\
		return			(compare(p0,p1,object_comparer::detail::comparer<b>()));\
	}

declare_comparer(equal,			std::equal_to);
declare_comparer(greater_equal,	std::greater_equal);
declare_comparer(greater,		std::greater);
declare_comparer(less_equal,	std::less_equal);
declare_comparer(less,			std::less);
declare_comparer(not_equal,		std::not_equal_to);
declare_comparer(logical_and,	std::logical_and);
declare_comparer(logical_or,	std::logical_or);
