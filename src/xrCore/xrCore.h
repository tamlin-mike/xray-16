#pragma once
#ifndef xrCoreH
#define xrCoreH

// XXX: upgrade std hash structures
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#ifndef DEBUG
# define MASTER_GOLD
#endif // DEBUG

#include "xrCore_benchmark_macros.h"

#if !defined(_CPPUNWIND)
#error Please enable exceptions...
#endif
#ifndef _MT
#error Please enable multi-threaded library...
#endif
#ifdef NDEBUG
#define XRAY_EXCEPTIONS 0
#define LUABIND_NO_EXCEPTIONS
#else
#define XRAY_EXCEPTIONS 1
#endif

#include "Common/Platform.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <typeinfo.h>

#ifdef _DEBUG
#define DEBUG
#endif
#ifdef MIXED
# ifndef DEBUG
#  define DEBUG
# endif
#endif

#ifndef DEBUG
#pragma inline_depth ( 254 )
#pragma inline_recursion( on )
#ifndef __BORLANDC__
#pragma intrinsic (abs, fabs, fmod, sin, cos, tan, asin, acos, atan, sqrt, exp, log, log10, strcat)
#endif
#endif

#include <time.h>

// Warnings
#pragma warning (disable : 4251 ) // object needs DLL interface
#pragma warning (disable : 4201 ) // nonstandard extension used : nameless struct/union
#pragma warning (disable : 4100 ) // unreferenced formal parameter
#pragma warning (disable : 4127 ) // conditional expression is constant
//#pragma warning (disable : 4530 ) // C++ exception handler used, but unwind semantics are not enabled
#pragma warning (disable : 4345 )
#pragma warning (disable : 4714 ) // __forceinline not inlined
#ifndef DEBUG
#pragma warning (disable : 4189 ) // local variable is initialized but not refenced
#endif // frequently in release code due to large amount of VERIFY


#ifdef _M_AMD64
#pragma warning (disable : 4512 )
#endif

// stl
#pragma warning (push)
#pragma warning (disable:4702)
#include <algorithm>
#include <limits>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <map>

#ifndef _EDITOR
# include <hash_map>
# include <hash_set>
#endif

#include <string>
#pragma warning (pop)
#pragma warning (disable : 4100 ) // unreferenced formal parameter

// Our headers
#include "xrCore_impexp.h"

#include "xrDebug.h"
//#include "vector.h"

#include "clsid.h"
//#include "Threading/Lock.hpp"
#include "xrMemory.h"
#include "xrDebug.h"

//#include "_stl_extensions.h"
#include "xrCommon/xr_vector.h"
#include "xrCommon/xr_set.h"
#include "xrsharedmem.h"
#include "xrstring.h"
#include "xr_resource.h"
#include "Compression/rt_compressor.h"
#include "xr_shared.h"
#include "string_concatenations.h"
#include "_flags.h"

// stl ext
struct XRCORE_API xr_rtoken
{
    shared_str name;
    int id;
    xr_rtoken(LPCSTR _nm, int _id) { name = _nm; id = _id; }
public:
    void rename(LPCSTR _nm) { name = _nm; }
    bool equal(LPCSTR _nm) { return (0 == xr_strcmp(*name, _nm)); }
};

#include "xr_shortcut.h"

DEFINE_VECTOR(shared_str, RStringVec, RStringVecIt);
DEFINE_SET(shared_str, RStringSet, RStringSetIt);
DEFINE_VECTOR(xr_rtoken, RTokenVec, RTokenVecIt);

#include "FS.h"
#include "log.h"
#include "xr_trims.h"
#include "xr_ini.h"
#ifdef NO_FS_SCAN
# include "ELocatorAPI.h"
#else
# include "LocatorAPI.h"
#endif
#include "FileSystem.h"
#include "FTimer.h"
#include "fastdelegate.h"
#include "intrusive_ptr.h"

#include "net_utils.h"

// destructor
template <class T>
class destructor
{
    T* ptr;
public:
    destructor(T* p) { ptr = p; }
    ~destructor() { xr_delete(ptr); }
    IC T& operator() ()
    {
        return *ptr;
    }
};

// ********************************************** The Core definition
class XRCORE_API xrCore
{
private:
    const char *buildDate;
    u32 buildId;

public:
    string64 ApplicationName;
    string_path ApplicationPath;
    string_path WorkingPath;
    string64 UserName;
    string64 CompName;
    char* Params;
    DWORD dwFrame;
    bool PluginMode;

public:
    void _initialize(LPCSTR ApplicationName, LogCallback cb = 0, BOOL init_fs = TRUE, LPCSTR fs_fname = 0, bool plugin = false);
    void _destroy();
    const char *GetBuildDate() const { return buildDate; }
    u32 GetBuildId() const { return buildId; }

private:
    void CalculateBuildId();
};

extern XRCORE_API xrCore Core;

#endif

