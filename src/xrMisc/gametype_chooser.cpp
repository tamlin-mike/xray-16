#include "xrServerEntities/gametype_chooser.h"

EGameIDs ParseStringToGameType(LPCSTR str)
{
#define IS(NAME) (!xr_strcmp(str, NAME))
	if (IS("single"))                          return eGameIDSingle;
	if (IS("deathmatch") || IS("dm"))          return eGameIDDeathmatch;
	if (IS("teamdeathmatch") || IS("tdm"))     return eGameIDTeamDeathmatch;
	if (IS("artefacthunt") || IS("ah"))        return eGameIDArtefactHunt;
	if (IS("capturetheartefact") || IS("cta")) return eGameIDCaptureTheArtefact;
	if (IS("dominationzone"))                  return eGameIDDominationZone;
	if (IS("teamdominationzone"))              return eGameIDTeamDominationZone;
	return eGameIDNoGame; //EGameIDs
#undef IS
}
