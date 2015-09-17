#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "player.h"
#include "collidable.h"
#include "map.h"


extern TMap tMap;
extern TPlayer tPlayer;
extern TCollidable tWall[10000];

inline TPlayer GetPlayer()
{
	return tPlayer;
}

inline TCollidable GetCollidable()
{
	return tWall[1000];
}

inline TMap GetMap()
{
	return tMap;
}




#endif


