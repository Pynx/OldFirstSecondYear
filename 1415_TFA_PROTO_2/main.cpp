#include "flib.h"
#include "flib_vec2.h"
#include "global.h"
#include "lemmings.h"
#include "wall.h"
#include "map.h"

const int TILE_SIZE = 16;
const int SCALE = 1;
const int MAX_WALL = 1000;
const int MAX_LEMMINGS = 5;

int g_iWallCpt = 0;
int g_iLemmingsCpt = 0;
int g_iScore = 0;
int g_iLevel = 1;

bool g_bLevelFinished = false;

TMap tMap;
TWall tWall[MAX_WALL];
TLemmings tLemmings[MAX_LEMMINGS];

TGfxSprite * tLemmingsToSpawn = nullptr;
TGfxSprite * tLevel = nullptr;
TGfxSprite * tRestart = nullptr;

TGfxTexture * tMainTexture = nullptr;

void Initialize()
{
	tMap.CreateVar();
	tMainTexture = GfxTextureLoad("gfx/tileset.tga");
	g_iWallCpt = tMap.Readmap(SCALE, TILE_SIZE, MAX_WALL, g_iLevel); // Création de la map et modification du nombre de mur.


	tLemmingsToSpawn = GfxTextSpriteCreate();
	tLevel = GfxTextSpriteCreate();
	tRestart = GfxTextSpriteCreate();

	GfxSpriteSetFilteringEnabled(tLemmingsToSpawn, false);
	GfxSpriteSetFilteringEnabled(tLevel, false);
	GfxSpriteSetFilteringEnabled(tRestart, false);

	GfxSpriteSetPosition(tLemmingsToSpawn, 10, 310);
	GfxSpriteSetPosition(tLevel, 240, 310);
	GfxSpriteSetPosition(tRestart, 370, 310);

	GfxTextSpritePrintf(tLemmingsToSpawn, "Spawnable Cube Left : %i", MAX_LEMMINGS - g_iLemmingsCpt);
	GfxTextSpritePrintf(tLevel, "Level 1");
	GfxTextSpritePrintf(tRestart, "Restart level");
}

void Update()
{

	// Fonction Input Lemmings ( Click green -> stop them )

	for (int i = 0; i < g_iLemmingsCpt; i++)
	{
		if (tLemmings[i].m_iColor == 2)
		{
			tLemmings[i].Input(TILE_SIZE);
		}
	}

	// Fonction Click base to spawn & clickable blocks

	for (int i = 0; i < g_iWallCpt; i++)
	{
		if (tWall[i].m_bIsBase == true
			||
			tWall[i].m_bIsClickable == true)
		{
			tWall[i].Input(TILE_SIZE);
		}
	}

	// Fonction Move Lemmings

	for (int i = 0; i < g_iLemmingsCpt; i++)
	{
		tLemmings[i].Move(TILE_SIZE, g_iLemmingsCpt);
	}

	// Fonction Win Game

	g_bLevelFinished = true;

	for (int i = 0; i < MAX_LEMMINGS; i++)
	{
		if (tLemmings[i].m_bIsAtTheEnd == false)
		{
			g_bLevelFinished = false;
			break;
		}
	}

	if (g_bLevelFinished == true)
	{
		if (g_iLevel < 4)
		{
			// Delete map

			// RAZ Wall Informations

			for (int i = 0; i < g_iWallCpt; i++)
			{
				tWall[i].m_bIsBase = false;
				tWall[i].m_bIsBasePosOpen = false;
				tWall[i].m_bIsClickable = false;
				tWall[i].m_bIsClickableOpen = false;
				tWall[i].m_bIsExit = false;
				tWall[i].m_bIsExitOpen = false;
				tWall[i].m_bIsLadder = false;
				tWall[i].m_bIsRack = false;
				tWall[i].m_iColor = 0;
			}
			
			// Delete Lemmings

			for (int i = 0; i < g_iLemmingsCpt; i++)
			{
				tLemmings[i].m_bIsAtTheEnd = false;
				tLemmings[i].m_bIsStopped = false;
				tLemmings[i].m_iColor = 0;
				tLemmings[i].m_iDirection = 0;
				GfxSpriteDestroy(tLemmings[i].m_tLemmingSprite);
				//tLemmings[i].m_tLemmingSprite = nullptr;
				tLemmings[i].m_tPosition = TGfxVec2(0, 0);
			}

			// Reinitialize variable

			g_iLemmingsCpt = 0;
			g_iScore = 0;
			g_iLevel++;

			// Create new map

			g_iWallCpt = tMap.Readmap(SCALE, TILE_SIZE, MAX_WALL, g_iLevel);
			g_iScore = 0;
		}
	}


	GfxTextSpritePrintf(tLemmingsToSpawn, "Spawnable Cube Left : %i", MAX_LEMMINGS - g_iLemmingsCpt);
	GfxTextSpritePrintf(tLevel, "Level %i", g_iLevel);

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		const int iMouseX = GfxInputGetMousePositionX();
		const int iMouseY = GfxInputGetMousePositionY();

		if (iMouseX > 350
			&& iMouseY > 290)
		{
			for (int i = 0; i < g_iWallCpt; i++)
			{
				tWall[i].m_bIsBase = false;
				tWall[i].m_bIsBasePosOpen = false;
				tWall[i].m_bIsClickable = false;
				tWall[i].m_bIsClickableOpen = false;
				tWall[i].m_bIsExit = false;
				tWall[i].m_bIsExitOpen = false;
				tWall[i].m_bIsLadder = false;
				tWall[i].m_bIsRack = false;
				tWall[i].m_iColor = 0;
			}

			for (int i = 0; i < g_iLemmingsCpt; i++)
			{
				tLemmings[i].m_bIsAtTheEnd = false;
				tLemmings[i].m_bIsStopped = false;
				tLemmings[i].m_iColor = 0;
				tLemmings[i].m_iDirection = 0;
				GfxSpriteDestroy(tLemmings[i].m_tLemmingSprite);
				tLemmings[i].m_tLemmingSprite = nullptr;
				tLemmings[i].m_tPosition = TGfxVec2(0, 0);
			}

			g_iLemmingsCpt = 0;
			
			g_iWallCpt = tMap.Readmap(SCALE, TILE_SIZE, MAX_WALL, g_iLevel);
		}
	}
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(tMap.g_tLevelSprite);

	for (int i = 0; i < g_iLemmingsCpt; i++)
	{
		GfxSpriteRender(tLemmings[i].m_tLemmingSprite);
	}

	GfxSpriteRender(tLemmingsToSpawn);
	GfxSpriteRender(tLevel);
	GfxSpriteRender(tRestart);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
