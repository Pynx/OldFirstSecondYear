#include "flib.h"
#include "flib_vec2.h"
#include "drawable.h"
#include "player.h"
#include "global.h"

void TPlayer::Initialize(int x, int y, int TILE_SIZE, int SCALE)
{
	TGfxTexture * pTexture = GfxTextureLoad("gfx/tileset.tga");
	m_pSpritePlayer = GfxSpriteCreate(pTexture);
	GfxSpriteSetScale(m_pSpritePlayer, float(SCALE), float(SCALE));
	GfxSpriteSetFilteringEnabled(m_pSpritePlayer, false);
	GfxSpriteSetCutout(m_pSpritePlayer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	GfxSpriteSetPosition(m_pSpritePlayer, 
		((GfxGetDisplaySizeX() / 2) - ((GfxSpriteGetSizeX(m_pSpritePlayer)*(GfxSpriteGetScaleX(m_pSpritePlayer)) / 2))), 
		((GfxGetDisplaySizeY() / 2) - ((GfxSpriteGetSizeY(m_pSpritePlayer)*(GfxSpriteGetScaleY(m_pSpritePlayer)) / 2))));
}      

void TPlayer::Move(float fSpeed, TGfxVec2 tDirection, const int MAX_WALL, const int TILE_SIZE)
{
	TGfxVec2 tVelocity = TGfxVec2(0, 0);
	TGfxVec2 tMove = TGfxVec2(0, 0);

	TGfxVec2 tDirectionX = TGfxVec2(1, 0);
	TGfxVec2 tDirectionY = TGfxVec2(0, 1);

	float fSpeedX = (tDirection*fSpeed).DotProduct(tDirectionX);
	float fSpeedY = (tDirection*fSpeed).DotProduct(tDirectionY);

	const int iMaxPossibleCollision = 8;
	int iCollisionableWall[iMaxPossibleCollision];
	float fCollisionableWallLength[iMaxPossibleCollision];
	int iCollisionableWallCpt = 0;
	int iCloserCollisionableWall = 0;

	int iCollisionDirection = 0; // 0 = en haut, 1 = à gauche, 2 = en bas, 3 = à droite

	bool bCollision = false;
	bool bInputPressed = false;


	bool bNextToWallRight = true;
	bool bNextToWallLeft = true;

	for (int i = 0; i < MAX_WALL; i++)
	{
		if (m_tPosition.x + TILE_SIZE == tWall[i].tPosition.x
			&& m_tPosition.y > tWall[i].tPosition.y - TILE_SIZE
			&& m_tPosition.y < tWall[i].tPosition.y + TILE_SIZE)
		{
			bNextToWallRight = false;
		}
		if (m_tPosition.x - TILE_SIZE == tWall[i].tPosition.x
			&& m_tPosition.y > tWall[i].tPosition.y - TILE_SIZE
			&& m_tPosition.y < tWall[i].tPosition.y + TILE_SIZE)
		{
			bNextToWallLeft = false;
		}
	}

	int iMouseOneX = 0;
	int iMouseOneY = 0;
	int iMouseTwoX = 0;
	int iMouseTwoY = 0;
	int iNumberOfMouse = 0;

	if (GfxInputGetMouseCount() == 0)
	{
		iNumberOfMouse = 0;
	}
	else if (GfxInputGetMouseCount() == 1)
	{
		iMouseOneX = GfxInputGetMousePositionX(0);
		iMouseOneY = GfxInputGetMousePositionY(0);
		iNumberOfMouse = 1;
	}
	else
	{
		iMouseOneX = GfxInputGetMousePositionX(0);
		iMouseOneY = GfxInputGetMousePositionY(0);
		iMouseTwoX = GfxInputGetMousePositionX(1);
		iMouseTwoY = GfxInputGetMousePositionY(1);
		iNumberOfMouse = 2;
	}

	if (bNextToWallRight == true)
	{
		if ((GfxInputIsPressed(EGfxInputID_KeyArrowRight))
			||
			(iNumberOfMouse == 1
			&& iMouseOneX > 68
			&& iMouseOneX < 130
			&& iMouseOneY > 220
			&& iMouseOneY < 320)
			||
			(iNumberOfMouse == 2
			&& iMouseOneX > 68
			&& iMouseOneX < 130
			&& iMouseOneY > 220
			&& iMouseOneY < 320)
			||
			(iNumberOfMouse == 2
			&& iMouseTwoX > 68
			&& iMouseTwoX < 130
			&& iMouseTwoY > 220
			&& iMouseTwoY < 320)
			)
		{
			tVelocity += TGfxVec2(5, 0);
			bInputPressed = true;
		}
	}
	if (bNextToWallLeft == true)
	{
		if ((GfxInputIsPressed(EGfxInputID_KeyArrowLeft))
			||
			(iNumberOfMouse == 1
			&& iMouseOneX > 0
			&& iMouseOneX < 68
			&& iMouseOneY > 220
			&& iMouseOneY < 320)
			||
			(iNumberOfMouse == 2
			&& iMouseOneX > 0
			&& iMouseOneX < 68
			&& iMouseOneY > 220
			&& iMouseOneY < 320)
			||
			(iNumberOfMouse == 2
			&& iMouseTwoX > 0
			&& iMouseTwoX < 68
			&& iMouseTwoY > 220
			&& iMouseTwoY < 320)
			)
		{
			tVelocity += TGfxVec2(-5, 0);
			bInputPressed = true;
		}
	}

	 
	if (bInputPressed == true) // Si un bouton est appuyé, on augmente la vitesse, ....
	{
		if (fSpeedX > 4)
		{
			fSpeedX = 4;
		}
		if (fSpeedX < -4)
		{
			fSpeedX = -4;
		}
		tMove = ((tDirectionX * fSpeedX) + (tVelocity * GfxTimeFrameGetCurrentDurationInSeconds()));
	}
	else // sinon on la réduit jusqu'a un certain nombre où on la mets à 0
	{
		if (fSpeedX > 0.5 || fSpeedX < -0.5)
		{
			tMove = (tDirectionX * fSpeedX) * 0.9;
		}
		else
		{
			tMove = (tDirectionX * fSpeedX) * 0;
		}
	}

	for (int i = 0; i < MAX_WALL; i++)
	{
		if ((m_tPosition.x) > (tWall[i].tPosition.x - TILE_SIZE)
			&& (m_tPosition.x) < (tWall[i].tPosition.x + (TILE_SIZE))
			&& (m_tPosition.y) == (tWall[i].tPosition.y - TILE_SIZE)
			)
		{
			if (tWall[i].bIsTheEnd == true)
			{
				bIsGameWin = true;
				break;
			}
			if (tWall[i].bIsBoost == true)
			{
				tMove += tWall[i].tBoost;
				break;				
			}
			if ((GfxInputIsPressed(EGfxInputID_KeyCharZ))
				||
				(iNumberOfMouse == 1
				&& iMouseOneX > 410
				&& iMouseOneX < 480
				&& iMouseOneY > 250
				&& iMouseOneY < 320)
				||
				(iNumberOfMouse == 2
				&& iMouseOneX > 410
				&& iMouseOneX < 480
				&& iMouseOneY > 250
				&& iMouseOneY < 320)
				||
				(iNumberOfMouse == 2
				&& iMouseTwoX > 410
				&& iMouseTwoX < 480
				&& iMouseTwoY > 250
				&& iMouseTwoY < 320)
				)
			{
				tMove += TGfxVec2(0, -5.5);
				break;
			}
		}
	}

	for (int i = 0; i < MAX_WALL; i++)
	{
		if ((m_tPosition.x) >(tWall[i].tPosition.x - TILE_SIZE)
			&& (m_tPosition.x) < (tWall[i].tPosition.x + (TILE_SIZE))
			&& (m_tPosition.y) == (tWall[i].tPosition.y - TILE_SIZE)
			)
		{
			if (tWall[i].bIsKilling == true)
			{
				m_fHealth -= GfxTimeFrameGetCurrentDurationInSeconds() * 50;
				break;
			}

		}
	}

	for (int i = 0; i < MAX_WALL; i++)
	{
		if (tWall[i].bIsWallJumpable == true)
		{
			if ((m_tPosition.x + TILE_SIZE) < (tWall[i].tPosition.x + 1)
				&& (m_tPosition.x + TILE_SIZE) > (tWall[i].tPosition.x - 1)
				&& (m_tPosition.y) > (tWall[i].tPosition.y - TILE_SIZE)
				&& (m_tPosition.y) < (tWall[i].tPosition.y + TILE_SIZE)
				)
			{
				if ((GfxInputIsPressed(EGfxInputID_KeyCharZ))
					||
					(iNumberOfMouse == 1
					&& iMouseOneX > 410
					&& iMouseOneX < 480
					&& iMouseOneY > 250
					&& iMouseOneY < 320)
					||
					(iNumberOfMouse == 2
					&& iMouseOneX > 410
					&& iMouseOneX < 480
					&& iMouseOneY > 250
					&& iMouseOneY < 320)
					||
					(iNumberOfMouse == 2
					&& iMouseTwoX > 410
					&& iMouseTwoX < 480
					&& iMouseTwoY > 250
					&& iMouseTwoY < 320)
					)
				{
					tMove += TGfxVec2(-5.5, -5.5);
					break;
				}
			}
		}
		if (tWall[i].bIsWallJumpable == true)
		{
			if ((m_tPosition.x - TILE_SIZE) < (tWall[i].tPosition.x + 1)
				&& (m_tPosition.x - TILE_SIZE) > (tWall[i].tPosition.x - 1)
				&& (m_tPosition.y) > (tWall[i].tPosition.y - TILE_SIZE)
				&& (m_tPosition.y) < (tWall[i].tPosition.y + TILE_SIZE)
				)
			{
				if ((GfxInputIsPressed(EGfxInputID_KeyCharZ))
					||
					(iNumberOfMouse == 1
					&& iMouseOneX > 410
					&& iMouseOneX < 480
					&& iMouseOneY > 250
					&& iMouseOneY < 320)
					||
					(iNumberOfMouse == 2
					&& iMouseOneX > 410
					&& iMouseOneX < 480
					&& iMouseOneY > 250
					&& iMouseOneY < 320)
					||
					(iNumberOfMouse == 2
					&& iMouseTwoX > 410
					&& iMouseTwoX < 480
					&& iMouseTwoY > 250
					&& iMouseTwoY < 320)
					)
				{
					tMove += TGfxVec2(5.5, -5.5);
					break;
				}
			}
		}
	}




	tMove += (fSpeedY * tDirectionY);

	bool bInAir = true;

	for (int i = 0; i < MAX_WALL; i++)
	{
		if (m_tPosition.y + TILE_SIZE == tWall[i].tPosition.y
			&& m_tPosition.x > (tWall[i].tPosition.x - TILE_SIZE) + 0.05
			&& m_tPosition.x < (tWall[i].tPosition.x + TILE_SIZE) - 0.05)// test si un bloc sous le joueur, si oui pas de pesanteur
		{
			bInAir = false;
			break;
		}
	}

	if (bInAir == true)
	{
		tMove += (GfxTimeFrameGetCurrentDurationInSeconds() * TGfxVec2(0, 15)); // Attraction terrestre
	}

	if (tMove.y > 6)
	{
		tMove.y = 6;
	}
	if (tMove.y < -6)
	{
		tMove.y = -6;
	}


	for (int i = 0; i < MAX_WALL; i++)
	{
		if ((m_tPosition.x + tMove.x) > (tWall[i].tPosition.x - TILE_SIZE)
			&& (m_tPosition.x + tMove.x) < (tWall[i].tPosition.x + (TILE_SIZE))
			&& (m_tPosition.y + tMove.y) > (tWall[i].tPosition.y - TILE_SIZE)
			&& (m_tPosition.y + tMove.y) < (tWall[i].tPosition.y + (TILE_SIZE))
			)
		{
			//const int iMaxPossibleCollision = 4;
			//int iCollisionableWall[iMaxPossibleCollision];
			//int iCollisionableWallCpt = 0;
			//int iCloserCollisionableWall = 0;
			iCollisionableWall[iCollisionableWallCpt] = i;
			iCollisionableWallCpt++;
			bCollision = true;
		}
	}

	if (bCollision == true) // SI au moins une collision à été détectée, on regarde laquelle est la plus proche et on lance le code de collision
	{

		for (int i = 0; i < iCollisionableWallCpt; i++)
		{
			fCollisionableWallLength[i] = ((tWall[iCollisionableWall[i]].tPosition - m_tPosition).Length());
		}

		bool bIsTheSmallest = true;

		for (int i = 0; i < iCollisionableWallCpt; i++)
		{
			bIsTheSmallest = true;
			for (int e = 0; e < iCollisionableWallCpt; e++)
			{
				if (fCollisionableWallLength[i] > fCollisionableWallLength[e])
				{
					bIsTheSmallest = false;
				}
			}
			if (bIsTheSmallest == true)
			{
				iCloserCollisionableWall = iCollisionableWall[i];
				break;
			}
		}

		int i = iCloserCollisionableWall;



		TGfxVec2 tWallTopPos = TGfxVec2(tWall[i].tPosition.x, (tWall[i].tPosition.y - TILE_SIZE));
		TGfxVec2 tWallLeftPos = TGfxVec2((tWall[i].tPosition.x - TILE_SIZE), tWall[i].tPosition.y);
		TGfxVec2 tWallBottomPos = TGfxVec2(tWall[i].tPosition.x, (tWall[i].tPosition.y + TILE_SIZE));
		TGfxVec2 tWallRightPos = TGfxVec2((tWall[i].tPosition.x + TILE_SIZE), tWall[i].tPosition.y);

		//TGfxVec2 tPlayerFuturePos = TGfxVec2(m_tPosition.x + tMove.x, m_tPosition.y + tMove.y);

		TGfxVec2 tPlayerToTop = m_tPosition - tWallTopPos;
		TGfxVec2 tPlayerToLeft = m_tPosition - tWallLeftPos;
		TGfxVec2 tPlayerToBottom = m_tPosition - tWallBottomPos;
		TGfxVec2 tPlayerToRight = m_tPosition - tWallRightPos;

		float fPlayerToTopLength = tPlayerToTop.Length();
		float fPlayerToLeftLength = tPlayerToLeft.Length();
		float fPlayerToBottomLength = tPlayerToBottom.Length();
		float fPlayerToRightLength = tPlayerToRight.Length();
		
		if (fPlayerToTopLength < fPlayerToLeftLength
			&& fPlayerToTopLength < fPlayerToBottomLength
			&& fPlayerToTopLength < fPlayerToRightLength
			)
		{ // Renvoyé à gauche du mur
			float fPixelInCollision = ((tPlayer.m_tPosition.y + (tMove.y + TILE_SIZE)) - (tWall[i].tPosition.y));
			tMove.y -= fPixelInCollision;
			iCollisionDirection = 1;
		}
		else if (fPlayerToLeftLength < fPlayerToTopLength
			&& fPlayerToLeftLength < fPlayerToBottomLength
			&& fPlayerToLeftLength < fPlayerToRightLength
			)
		{
			float fPixelInCollision = ((tPlayer.m_tPosition.x + (tMove.x + TILE_SIZE)) - (tWall[i].tPosition.x));
			tMove.x -= fPixelInCollision;
			iCollisionDirection = 2;
		}
		else if (fPlayerToBottomLength < fPlayerToTopLength
			&& fPlayerToBottomLength < fPlayerToLeftLength
			&& fPlayerToBottomLength < fPlayerToRightLength
			)
		{
			float fPixelInCollision = (tWall[i].tPosition.y + TILE_SIZE) - (tPlayer.m_tPosition.y + tMove.y);
			tMove.y += fPixelInCollision;
			iCollisionDirection = 3;
		}
		else
		{
			float fPixelInCollision = (tWall[i].tPosition.x + TILE_SIZE) - (tPlayer.m_tPosition.x + tMove.x);
			tMove.x += fPixelInCollision;
			iCollisionDirection = 4;
		}

	}
	

	m_tPosition = TGfxVec2(GfxSpriteGetPositionX(m_pSpritePlayer) + tMove.x, GfxSpriteGetPositionY(m_pSpritePlayer) + tMove.y);
	GfxSpriteSetPosition(m_pSpritePlayer, m_tPosition.x, m_tPosition.y);


	m_fSpeed = tMove.Length();
	if (m_fSpeed != 0)
	{
		m_tDirection = tMove.Normalize();
	}

	//if (iCollisionDirection == 0)
	//{
	//	// Stop déplacement haut/bas -> Speed.y = 0
	//	m_fSpeed = (m_fSpeed * m_tDirection).DotProduct(TGfxVec2(0, 1));
	//}
	//if (iCollisionDirection == 1)
	//{
	//	m_fSpeed = (m_fSpeed * m_tDirection).DotProduct(TGfxVec2(1, 0));
	//}


}

void TPlayer::Render(const int MAX_Wall)
{
	TGfxVec2 tBackToCenter = (m_tPosition - m_tStartPosition);

	m_tPosition -= tBackToCenter;
	GfxSpriteSetPosition(m_pSpritePlayer, GfxSpriteGetPositionX(m_pSpritePlayer) - tBackToCenter.x, GfxSpriteGetPositionY(m_pSpritePlayer) - tBackToCenter.y);
	GfxSpriteSetPosition(tMap.g_tLevelSprite, GfxSpriteGetPositionX(tMap.g_tLevelSprite) - tBackToCenter.x, GfxSpriteGetPositionY(tMap.g_tLevelSprite) - tBackToCenter.y);
	m_tSpawnPosition -= tBackToCenter;

	for (int i = 0; i < MAX_Wall; i++)
	{
		// if different from -2000, -2000
		if (tWall[i].tPosition != TGfxVec2(-2000, -2000))
		{
			tWall[i].tPosition -= tBackToCenter;
		}
	}

	m_tRespawnVector -= tBackToCenter;

	GfxSpriteRender(tMap.g_tLevelSprite);
	GfxSpriteRender(m_pSpritePlayer);
}

void TPlayer::Respawn(const int MAX_Wall)
{
	GfxSpriteSetPosition(tMap.g_tLevelSprite, GfxSpriteGetPositionX(tMap.g_tLevelSprite) - m_tRespawnVector.x, GfxSpriteGetPositionY(tMap.g_tLevelSprite) - m_tRespawnVector.y);

	for (int i = 0; i < MAX_Wall; i++)
	{
		// if different from -2000, -2000
		if (tWall[i].tPosition != TGfxVec2(-2000, -2000))
		{
			tWall[i].tPosition -= m_tRespawnVector;
		}
	}

	m_fSpeed = 0;
	m_tDirection = TGfxVec2(0, 0);
	m_tRespawnVector = TGfxVec2(0, 0);
}
