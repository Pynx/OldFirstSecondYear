#include "stdafx.h"
#include "drawable.h"
#include "collidable.h"
#include "dynamicentity.h"
#include "player.h"
#include <string>

TPlayer::TPlayer() : TDynamicEntity(42)
{
	printf("Player Constructor\n");
}

TPlayer::~TPlayer()
{
	printf("Player Destructor\n");
}