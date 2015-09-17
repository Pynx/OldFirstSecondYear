//Collision base to do !!!


#include "flib.h"
#include "flib_vec2.h"
#include <math.h>



int g_iCurrentCaveTarget = 0;
int g_iPlayerInventory = 0;
int g_iActualArtefacts = 0;
int g_iNbrCaveCreated = 0;

float g_iTime = 0;
float MoveX;
float MoveY;
float MoveX2;
float MoveY2;
float RatioX;
float RatioY;
int sizeX;
int sizeY;
const int g_iNbrCave = 6; // NBR CAVE
const int g_iSpeed = 160; // Speed per second

bool g_bCaveSearched[g_iNbrCave];
bool g_bAllCaveSearched = false;
bool g_bSearchingLaunch = false;
bool g_bMoving = false;

TGfxSprite * g_pSpriteBase;
TGfxSprite * g_pSpritePlayer;
TGfxTexture * g_pTexture;
TGfxImage * g_pImage;
TGfxSprite * g_pLines;
TGfxSprite * g_pLines2;

struct TCaveData
{
	TGfxSprite * g_pSpriteCave;
	float iPosX = 0;
	float iPosY = 0;
	int iScale = 0;
	bool bIsSearched = false;
	TGfxSprite * pLines;
};

TCaveData g_pCave[g_iNbrCave];

struct TPlayerData
{
	float iPosX = 0;
	float iPosY = 0;

	TGfxVec2 iPos;

	TGfxVec2 tDest;

	enum EPlayerState
	{
		EPlayerState_AtBase = 1,
		EPlayerState_AtCave,
		EPlayerState_GoingToBase,
		EPlayerState_GoingToCave,
		EPlayerState_Searching
	};

	EPlayerState m_ePlayerState = EPlayerState_AtBase;

};

TPlayerData g_TPlayerData;

namespace ArcheoStuffs
{
	float Absol(float nbr)
	{
		if (nbr < 0)
		{
			nbr = 0 - nbr;
		}
		return nbr;
	}

	void DrawArrow(TGfxSprite * pLines, const TGfxVec2 tCenter, TGfxVec2 tDest)
	{
		if (!(tDest == tCenter))
		{
			TGfxVec2 pArrow = 15 * (tDest - tCenter).Normalize();
			const float angle = GfxMathDegToRad(160);
			TGfxVec2 pArrow1 = pArrow.Rotate(angle);
			TGfxVec2 pArrow2 = pArrow.Rotate(-angle);

			GfxLineSpriteJumpTo(pLines, tCenter.x, tCenter.y);
			GfxLineSpriteLineTo(pLines, tDest.x, tDest.y);
			GfxLineSpriteLineTo(pLines, tDest.x + pArrow1.x, tDest.y + pArrow1.y);
			GfxLineSpriteJumpTo(pLines, tDest.x, tDest.y);
			GfxLineSpriteLineTo(pLines, tDest.x + pArrow2.x, tDest.y + pArrow2.y);

		}
	}

	void DrawCircle(TGfxSprite * pLines, const TGfxVec2 tCenter, const float fRadius, const unsigned int tColor, const bool tPlayer)
	{
		GfxSpriteSetPosition(pLines, g_TPlayerData.iPosX, g_TPlayerData.iPosY);
		const int NUM_LINES = 32;

		GfxLineSpriteJumpTo(pLines, tCenter.x + fRadius, tCenter.y);
		GfxLineSpriteSetDrawingColor(pLines, tColor);

		if (tPlayer == true)
		{
			ArcheoStuffs::DrawArrow(pLines, tCenter, TGfxVec2(tCenter.x + cos(GfxMathDegToRad((360.f / NUM_LINES) * (1))) * fRadius, tCenter.y + sin(GfxMathDegToRad((360.f / NUM_LINES) * (1))) * fRadius));
		}

		for (int i = 0; i < NUM_LINES; ++i)
		{
			const float fAngle = GfxMathDegToRad((360.f / NUM_LINES) * (i + 1));
			const float fPosX = tCenter.x + cos(fAngle) * fRadius;
			const float fPosY = tCenter.y + sin(fAngle) * fRadius;
			GfxLineSpriteLineTo(pLines, fPosX, fPosY);
		}
	}

	void CreateCave(int ActCave)
	{
		g_pCave[ActCave].iScale = GfxMathGetRandomInteger(32, 64);
		bool Collisioned = true;
		do
		{
			g_pCave[ActCave].iPosX = (GfxMathGetRandomInteger(g_pCave[ActCave].iScale, GfxGetDisplaySizeX() - g_pCave[ActCave].iScale));
			g_pCave[ActCave].iPosY = (GfxMathGetRandomInteger(g_pCave[ActCave].iScale, GfxGetDisplaySizeY() - g_pCave[ActCave].iScale));
			Collisioned = false;
			for (int e = 0; e < ActCave; e++)
			{
				if (!(g_pCave[ActCave].iPosX > g_pCave[e].iPosX + g_pCave[e].iScale + 20)
					&& !(g_pCave[ActCave].iPosX < g_pCave[e].iPosX - g_pCave[ActCave].iScale - 20)
					&& !(g_pCave[ActCave].iPosY < g_pCave[e].iPosY - g_pCave[ActCave].iScale - 20)
					&& !(g_pCave[ActCave].iPosY > g_pCave[e].iPosY + g_pCave[e].iScale + 20))
				{
					Collisioned = true;
				}
			}
			if (ActCave == 0)
			{
				Collisioned = false;
			}
		} while (Collisioned == true);


		g_pCave[ActCave].pLines = GfxLineSpriteCreate();
		ArcheoStuffs::DrawCircle(g_pCave[ActCave].pLines, TGfxVec2(0, 0), g_pCave[ActCave].iScale / 2, EGfxColor_Blue, false);
		GfxSpriteSetPosition(g_pCave[ActCave].pLines, g_pCave[ActCave].iPosX, g_pCave[ActCave].iPosY);

		g_pCave[ActCave].g_pSpriteCave = GfxSpriteCreate(g_pTexture);
		GfxSpriteSetPivot(g_pCave[ActCave].g_pSpriteCave, 0.5, 0.5);
		GfxSpriteSetScale(g_pCave[ActCave].g_pSpriteCave, g_pCave[ActCave].iScale, g_pCave[ActCave].iScale);
		GfxSpriteSetColor(g_pCave[ActCave].g_pSpriteCave, GfxColor(0, 0, 255, 255));
		GfxSpriteSetPosition(g_pCave[ActCave].g_pSpriteCave, g_pCave[ActCave].iPosX, g_pCave[ActCave].iPosY);
		g_iNbrCaveCreated++;
	}

	void Move(TGfxVec2 tDest, TGfxVec2 tSrc)
	{
		TGfxVec2 Move(tDest.x - tSrc.x, tDest.y - tSrc.y);
		float Time = (ArcheoStuffs::Absol(Move.x) + ArcheoStuffs::Absol(Move.y)) / g_iSpeed;
		Move = Move / Time;
		Move = Move * GfxTimeFrameGetCurrentDurationInSeconds();




		MoveX = (tDest.x) - (tSrc.x);
		MoveY = (tDest.y) - (tSrc.y);
		RatioX = MoveX / (ArcheoStuffs::Absol(MoveX) + ArcheoStuffs::Absol(MoveY));
		RatioY = MoveY / (ArcheoStuffs::Absol(MoveX) + ArcheoStuffs::Absol(MoveY));
		MoveX2 = RatioX * g_iSpeed;
		MoveY2 = RatioY * g_iSpeed;

		const float X1 = tSrc.x;
		const float Y1 = tSrc.y;
		const float X2 = tDest.x;
		const float Y2 = tDest.y;
		const float X3 = (tSrc.x + (GfxTimeFrameGetCurrentDurationInSeconds() * MoveX2));
		const float Y3 = (tSrc.y + (GfxTimeFrameGetCurrentDurationInSeconds() * MoveY2));

		if (
			(
			X1 < X2
			&& Y1 > Y2
			&& X3 > X2
			&& Y3 < Y2
			)
			||
			(
			X1 < X2
			&& Y1 < Y2
			&& X3 > X2
			&& Y3 > Y2
			)
			||
			(
			X1 > X2
			&& Y1 > Y2
			&& X3 < X2
			&& Y3 < Y2
			)
			||
			(
			X1 > X2
			&& Y1 < Y2
			&& X3 < X2
			&& Y3 > Y2
			)
			)
		{
			tSrc.x = tDest.x;
			tSrc.y = tDest.y;
			g_bMoving = false;

			int sizeX = (GfxGetDisplaySizeX() / 2);
			int sizeY = (GfxGetDisplaySizeY() / 2);

			if (tDest == TGfxVec2(sizeX - 8, sizeY - 8))
			{
				g_TPlayerData.m_ePlayerState = g_TPlayerData.EPlayerState_AtBase;
			}
			else
			{
				g_TPlayerData.m_ePlayerState = g_TPlayerData.EPlayerState_AtCave;
			}
		}
		else
		{
			g_TPlayerData.iPos += Move;
			g_TPlayerData.iPosX += (GfxTimeFrameGetCurrentDurationInSeconds() * MoveX2);
			g_TPlayerData.iPosY += (GfxTimeFrameGetCurrentDurationInSeconds() * MoveY2);
		}
	}
}
void PlayerState_AtBase()
{
	GfxDbgPrintf("You are at the base \n");
	g_iActualArtefacts += g_iPlayerInventory;
	GfxDbgPrintf("You put %d artefacts in the base, you actually have %d artefacts\n", g_iPlayerInventory, g_iActualArtefacts);
	g_iPlayerInventory = 0;
	g_TPlayerData.m_ePlayerState = g_TPlayerData.EPlayerState_GoingToCave;
}
void PlayerState_AtCave()
{
	GfxDbgPrintf("You are at the cave number %d\n", g_iCurrentCaveTarget + 1);
	g_TPlayerData.m_ePlayerState = g_TPlayerData.EPlayerState_Searching;
}
void PlayerState_GoingToBase()
{
	if (g_bMoving == false)
	{
		GfxDbgPrintf("You are going to the base\n");
	}

	g_bMoving = true;

	//----------------------------------------- TRY ----------------------------------------------------------------

	int sizeX = (GfxGetDisplaySizeX() / 2);
	int sizeY = (GfxGetDisplaySizeY() / 2);

	ArcheoStuffs::Move(TGfxVec2(sizeX - 8, sizeY - 8), TGfxVec2(float(g_TPlayerData.iPosX), float(g_TPlayerData.iPosY)));


}
void PlayerState_GoingToCave()
{
	if (g_bMoving == false)
	{
		do
		{
			g_iCurrentCaveTarget = GfxMathGetRandomInteger(0, 5);
		} while (g_pCave[g_iCurrentCaveTarget].bIsSearched == true);

		GfxDbgPrintf("You are going to the cave number %d\n", g_iCurrentCaveTarget + 1);
	}
	
	g_bMoving = true;

	//----------------------------------------- TRY ----------------------------------------------------------------


	ArcheoStuffs::Move(TGfxVec2(float(g_pCave[g_iCurrentCaveTarget].iPosX), float(g_pCave[g_iCurrentCaveTarget].iPosY)), TGfxVec2(float(g_TPlayerData.iPosX), float(g_TPlayerData.iPosY)));


}
void PlayerState_Searching()
{
	if (g_bSearchingLaunch == false)
	{
		g_iTime = GfxMathGetRandomInteger(1, 3);
		g_bSearchingLaunch = true;
	}
	if (g_iTime > 0)
	{
		g_iTime -= GfxTimeFrameGetCurrentDurationInSeconds();
	}
	if (g_iTime <= 0)
	{
		g_pCave[g_iCurrentCaveTarget].bIsSearched = true;
		g_iPlayerInventory = GfxMathGetRandomInteger(0, 3);
		GfxDbgPrintf("You finished searching and you found %d artefacts\n", g_iPlayerInventory);
		g_iTime = 0;
		g_bSearchingLaunch = false;
		if (g_iPlayerInventory > 0)
		{
			g_TPlayerData.m_ePlayerState = g_TPlayerData.EPlayerState_GoingToBase;
		}
		else
		{
			g_TPlayerData.m_ePlayerState = g_TPlayerData.EPlayerState_GoingToCave;
		}
	}
}
void PlayerState_Update()
{
	switch (g_TPlayerData.m_ePlayerState)
	{
	case g_TPlayerData.EPlayerState_AtBase:
		PlayerState_AtBase();
		break;
	case g_TPlayerData.EPlayerState_AtCave:
		PlayerState_AtCave();
		break;
	case g_TPlayerData.EPlayerState_GoingToBase:
		PlayerState_GoingToBase();
		break;
	case g_TPlayerData.EPlayerState_GoingToCave:
		PlayerState_GoingToCave();
		break;
	case g_TPlayerData.EPlayerState_Searching:
		PlayerState_Searching();
		break;
	default:
		break;
	}
}
void Initialize()
{
	int sizeX = (GfxGetDisplaySizeX() / 2);
	int sizeY = (GfxGetDisplaySizeY() / 2);
	g_pLines = GfxLineSpriteCreate();
	g_pLines2 = GfxLineSpriteCreate();

	ArcheoStuffs::DrawCircle(g_pLines, TGfxVec2(0, 0), 8, GfxColor(255, 255, 0, 255), true); // Player creation

	for (int i = 0; i < g_iNbrCave; i++)
	{
		g_bCaveSearched[i] = false;
	}


	g_pImage = GfxImageCreate(1,1);
	unsigned int * pData = GfxImageGetData(g_pImage);
	*pData = EGfxColor_White;
	g_pTexture = GfxTextureCreate(g_pImage);

	g_pSpritePlayer = GfxSpriteCreate(g_pTexture);
	g_pSpriteBase = GfxSpriteCreate(g_pTexture);

	GfxSpriteSetScale(g_pSpritePlayer, 16, 16);
	GfxSpriteSetColor(g_pSpritePlayer, GfxColor(255, 255, 0, 255));
	g_TPlayerData.iPos = TGfxVec2(sizeX - 8, sizeY - 8);
	g_TPlayerData.iPosX = sizeX - 8;
	g_TPlayerData.iPosY = sizeY - 8;

	GfxSpriteSetScale(g_pSpriteBase, 32, 32);
	GfxSpriteSetColor(g_pSpriteBase, GfxColor(0, 255, 0, 255));
	GfxSpriteSetPosition(g_pSpriteBase, sizeX-16, sizeY-16);

	for (int i = 0; i < g_iNbrCave; i++)
	{
		ArcheoStuffs::CreateCave(i);
	}
	
}
void Update()
{
	g_bAllCaveSearched = true;

	for (int i = 0; i < g_iNbrCave; i++)
	{
		if (g_bCaveSearched[i] == false)
		{
			g_bAllCaveSearched = false;
		}
	}
	
	PlayerState_Update();
	GfxSpriteSetPosition(g_pLines, g_TPlayerData.iPos.x, g_TPlayerData.iPos.y);
	GfxLineSpriteReset(g_pLines2);
	GfxLineSpriteJumpTo(g_pLines2, g_TPlayerData.iPos.x, g_TPlayerData.iPos.y);
	GfxLineSpriteLineTo(g_pLines2, g_pCave[g_iCurrentCaveTarget].iPosX, g_pCave[g_iCurrentCaveTarget].iPosY);
}
void Render()
{
	GfxClear(EGfxColor_Black);

	//for (int i = 0; i < g_iNbrCave; i++)
	//{
	//	GfxSpriteRender(g_pCave[i].g_pSpriteCave);
	//}
	for (int i = 0; i < g_iNbrCave; i++)
	{
		GfxSpriteRender(g_pCave[i].pLines);
	}

	GfxSpriteRender(g_pSpriteBase);
	//GfxSpriteRender(g_pSpritePlayer);
	GfxSpriteRender(g_pLines);
	GfxSpriteRender(g_pLines2);
	
}
void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}


