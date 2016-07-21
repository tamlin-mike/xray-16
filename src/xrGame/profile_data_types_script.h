// profile_data_types_script.h
// XXX: NOTE: The type store_operation_cb is VERY heavy-weight in terms of how much
// the compiler has to work. It includes lua and therefore luabind, that is literally
// chock-full of templates, and slows down compilation measurably.
// TODO: See if it's possible to make store_operation_cb a simple free-standing type,
// that in a source file forwards to the actual mixed_delegate.
#pragma once
#include "mixed_delegate.h"

namespace gamespy_profile
{
typedef mixed_delegate<void (bool, char const *), store_operation_cb_tag>	store_operation_cb;
} //namespace gamespy_profile

//typedef gamespy_profile::store_operation_cb	gamespy_profile_store_operation_cb;
