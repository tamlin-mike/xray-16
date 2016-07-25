#include "StdAfx.h"
#include "game_type.h"
#include "Level.h"

bool OnServer() noexcept { return Level().IsServer(); }
bool OnClient() noexcept { return Level().IsClient(); }
bool IsGameTypeSingle() noexcept { return (g_pGamePersistent->GameType() == eGameIDSingle); }
