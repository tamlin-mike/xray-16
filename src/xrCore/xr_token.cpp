#include "stdafx.h"
#include "xr_token.h"
#include "Common/Platform.hpp"

const char* get_token_name(const xr_token* tokens, int key)
{
	for (int k = 0; tokens[k].name; k++)
		if (key == tokens[k].id) return tokens[k].name;
	return "";
}

int get_token_id(const xr_token* tokens, const char* key)
{
	for (int k = 0; tokens[k].name; k++)
		if (xr_stricmp(tokens[k].name, key) == 0)
			return tokens[k].id;
	return -1;
}

