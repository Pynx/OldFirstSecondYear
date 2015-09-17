/*

TO DO :

- Boost blocks
- grapins
- death block

- Add block at the begining
- add android control

DONE

- wall jump blocks
- Collisions
- Sprite unique pour la map
- Positions stockées dans un tableau
- Sprite player
- fonction restart game
- score with timer
- can jump only on the floor
- delete bounce bug
- Camera looking player

*/



#include "flib.h"
#include "flib_vec2.h"
#include "global.h"
#include "drawable.h"
#include "collidable.h"
#include "player.h"
#include "map.h"

TPlayer tPlayer;
const int TILE_SIZE = 16;
const int SCALE = 1;
const int MAX_SPEED = 5;
const int MAX_Wall = 10000;


float fTimer = 0;
int iTimer;
float fHealth = 100;
int iHealth;

int g_iScore = 0;

bool bIsScoreCalculated = false;

TMap tMap;
TCollidable tWall[MAX_Wall];

TGfxSprite * tScore = nullptr;
TGfxSprite * tTimer = nullptr;
TGfxSprite * tHealth = nullptr;
TGfxSprite * tMapControlsSprite = nullptr;
TGfxSprite * tControlsSprite = nullptr;
TGfxTexture * tMapControlsTexture = nullptr;
TGfxTexture * tControlsTexture = nullptr;

void Initialize()
{
	tControlsTexture = GfxTextureLoad("gfx/controls.tga");
	tControlsSprite = GfxSpriteCreate(tControlsTexture);
	GfxSpriteSetFilteringEnabled(tControlsSprite, false);

	tHealth = GfxTextSpriteCreate();
	GfxSpriteSetPosition(tHealth, 10, 10);
	iHealth = int(tPlayer.m_fHealth);
	GfxTextSpritePrintf(tHealth, "Health : %i%%", iHealth);

	tTimer = GfxTextSpriteCreate();
	GfxSpriteSetPosition(tTimer, 10, (GfxSpriteGetSizeY(tHealth) + 20));
	iTimer = int(fTimer);
	GfxTextSpritePrintf(tTimer, "Time : %i", iTimer);

	GfxDbgPrintf("height : %i\nwidth : %i", GfxGetDisplaySizeY(), GfxGetDisplaySizeX());

	tPlayer.Initialize(1, 2, TILE_SIZE, SCALE);
	int iPlayerPosX = GfxSpriteGetPositionX(tPlayer.m_pSpritePlayer); // Millieu écran
	int iPlayerPosY = GfxSpriteGetPositionY(tPlayer.m_pSpritePlayer);

	tPlayer.m_tPosition.x = GfxSpriteGetPositionX(tPlayer.m_pSpritePlayer);
	tPlayer.m_tPosition.y = GfxSpriteGetPositionY(tPlayer.m_pSpritePlayer);
	tPlayer.m_tStartPosition.x = GfxSpriteGetPositionX(tPlayer.m_pSpritePlayer);
	tPlayer.m_tStartPosition.y = GfxSpriteGetPositionY(tPlayer.m_pSpritePlayer);

	tMap.Readmap(SCALE, TILE_SIZE, iPlayerPosX, iPlayerPosY, MAX_Wall);

	//GfxDbgPrintf("Creation new TPlayer\n\n");
	//
	//TPlayer * pPlayer = new TPlayer();
	//
	//GfxDbgPrintf("\ntest 01 - name : %s \n", pPlayer->GetName()); // Ici on appelle le getname de player
	//GfxDbgPrintf("\ntest 02 - name : %s \n", GetName(*pPlayer));  // Ici on aura le getname de player si le getname de dynamic est en virtual !
	//
	//GfxDbgPrintf("\ntest 03 - nbr : %s \n", GetName(*pPlayer));
	//GfxDbgPrintf("\ntest 04 - nbr : %s \n", GetName(*pPlayer));
	//
	//GfxDbgPrintf("\nCreation new TStatic\n\n");
	//
	//TStatic * pStatic = new TStatic();
	//
	//pPlayer->Move(2.f, 0.5f); // ça dit que move est innacessible. C'est pourquoi on a mis player en public
	//
	//GfxDbgPrintf("\nDestruction new TEntity\n\n");
	//
	//delete pStatic;
	//
	//GfxDbgPrintf("\nDestruction new TPlayer\n\n");
	//
	//delete pPlayer;
}

void Update()
{



	if (tPlayer.bIsGameWin == false)
	{
		fTimer += GfxTimeFrameGetCurrentDurationInSeconds();
		iTimer = int(fTimer);
		GfxTextSpritePrintf(tTimer, "Time : %i", iTimer);

		//fHealth -= GfxTimeFrameGetCurrentDurationInSeconds()*5;
		iHealth = int(tPlayer.m_fHealth);
		GfxTextSpritePrintf(tHealth, "Health : %i%%", iHealth);

		tPlayer.Move(tPlayer.m_fSpeed, tPlayer.m_tDirection, MAX_Wall, TILE_SIZE);
		if (iHealth <= 0 || GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			tPlayer.m_fHealth = 100;
			fTimer = 0;
			tPlayer.Respawn(MAX_Wall);
		}
	}
	else
	{
		if (bIsScoreCalculated == false)
		{
			g_iScore = (250 - int(fTimer)) * int(tPlayer.m_fHealth);
			
			tScore = GfxTextSpriteCreate();
			GfxSpriteSetScale(tScore, 2, 2);
			GfxTextSpritePrintf(tScore, "Score : %i", g_iScore);
			GfxSpriteSetFilteringEnabled(tScore, false);
			
			bIsScoreCalculated = true;
			
			GfxSpriteSetPosition(tScore, ((GfxGetDisplaySizeX() / 2) - GfxSpriteGetSizeX(tScore)), ((GfxGetDisplaySizeY() / 2) - GfxSpriteGetSizeY(tScore)));
		}

		if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
		{
			tPlayer.m_fHealth = 100;
			fTimer = 0;
			tPlayer.Respawn(MAX_Wall);
			bIsScoreCalculated = false;
			tPlayer.bIsGameWin = false;

			GfxSpriteDestroy(tScore);
		}
		if (GfxInputGetMouseCount() > 1)
		{
			tPlayer.m_fHealth = 100;
			fTimer = 0;
			tPlayer.Respawn(MAX_Wall);
			bIsScoreCalculated = false;
			tPlayer.bIsGameWin = false;

			GfxSpriteDestroy(tScore);
		}

	}


}

void Render()
{
	GfxClear(EGfxColor_Black);
	if (bIsScoreCalculated == false)
	{
		tPlayer.Render(MAX_Wall);
		GfxSpriteRender(tTimer);
		GfxSpriteRender(tHealth);
		GfxSpriteRender(tControlsSprite);
	}
	else
	{
		GfxSpriteRender(tScore);
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
