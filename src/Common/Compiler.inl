#if !defined(__GNUC__) && !defined(_MSC_VER)
#error Unsupported compiler
#endif

#ifdef _MSC_VER
#include <intrin.h> // for __debugbreak
#endif

#include "xr_impexp_macros.h"
#include "inlining_macros.h"

#define UNUSED(...) (void)(__VA_ARGS__)
