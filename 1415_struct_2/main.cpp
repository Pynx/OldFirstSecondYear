#include "player.h"
#include "flib.h"

TPlayer g_tPlayer;

void GfxMain(int, char *[])
{
	TPlayer tPlayer;
	GfxDbgPrintf("%d, %d\n", tPlayer.m_iStrength, tPlayer.m_iHitPoints);
}
