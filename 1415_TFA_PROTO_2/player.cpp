#include "flib.h"
#include "drawable.h"
#include "dynamic.h"
#include "player.h"

TPlayer::TPlayer()
{
	GfxDbgPrintf("Player Constructor\n");
}

TPlayer::~TPlayer()
{
	GfxDbgPrintf("Player Deconstructor\n");
}

char * TPlayer::GetName()
{
	return "Player";
}
