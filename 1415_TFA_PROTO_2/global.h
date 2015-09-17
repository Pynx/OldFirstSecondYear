#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "map.h"
#include "wall.h"
#include "lemmings.h"


extern int g_iWallCpt;
extern int g_iLemmingsCpt;
extern TMap tMap;
extern TWall tWall[1000];
extern TGfxTexture * tMainTexture;
extern TLemmings tLemmings[5];

inline TMap GetMap()
{
	return tMap;
}

inline TWall GetWall()
{
	return tWall[1000];
}

inline TGfxTexture * GetTexture()
{
	return tMainTexture;
}

inline TLemmings GetLemmings()
{
	return tLemmings[5];
}

inline int GetLemmingsCpt()
{
	return g_iLemmingsCpt;
}

inline int GetWallCpt()
{
	return g_iWallCpt;
}

#endif


