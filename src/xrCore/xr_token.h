#pragma once
#include "xrCore_impexp.h"

struct xr_token
{
	const char* name;
	int id;
};

XRCORE_API const char* get_token_name(const xr_token* tokens, int key);
XRCORE_API int get_token_id(const xr_token* tokens, const char* key);
