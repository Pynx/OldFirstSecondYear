#include "flib.h"
#include "flib_vec2.h"
#include "lemmings.h"
#include "global.h"


void TLemmings::Spawn(TGfxVec2 tPosition)
{
	m_tLemmingSprite = GfxSpriteCreate(tMainTexture);
	GfxSpriteSetCutout(m_tLemmingSprite, 0, 0, 16, 16);
	GfxSpriteSetFilteringEnabled(m_tLemmingSprite, false);
	GfxSpriteSetPosition(m_tLemmingSprite, tPosition.x, tPosition.y);
	m_tPosition = tPosition;

	g_iLemmingsCpt++;
}

void TLemmings::Input(const int TILE_SIZE)
{
	// m_bIsStoppedd

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		const int iMouseX = GfxInputGetMousePositionX();
		const int iMouseY = GfxInputGetMousePositionY();

		if (iMouseX > (m_tPosition.x - TILE_SIZE)
			&& iMouseX < (m_tPosition.x + (TILE_SIZE * 2))
			&& iMouseY >(m_tPosition.y - TILE_SIZE)
			&& iMouseY < (m_tPosition.y + (TILE_SIZE * 2))) // Add Condition : Lemmings position not close to spawn
		{
			if (m_bIsStopped == true)
			{
				m_bIsStopped = false;
			}
			else
			{
				m_bIsStopped = true;
			}
		}
	}
}

void TLemmings::Move(const int TILE_SIZE, const int g_iLemmingsCpt)
{
	bool bColToRight = false;
	bool bColToLeft = false;
	bool bColToGround = false;
	bool bIsOnLadder = false;
	bool bIsOnRedRack = false;
	bool bIsOnGreenRack = false;
	bool bIsOnGreyRack = false;
	bool bIsAtTheEnd = false;
	
	for (int i = 0; i < g_iLemmingsCpt; i++)
	{
		if ((tLemmings[i].m_iColor == 2
			|| m_iColor == 2)
			&& m_tPosition.y == tLemmings[i].m_tPosition.y)
		{
			if (m_tPosition.x == (tLemmings[i].m_tPosition.x - TILE_SIZE))
			{
				//m_iDirection == 1;
				bColToRight = true;
			}
			else if (m_tPosition.x == (tLemmings[i].m_tPosition.x + TILE_SIZE))
			{
				//m_iDirection == 0;
				bColToLeft = true;
			}
		}
	}

	for (int i = 0; i < g_iWallCpt; i++)
	{
		if (m_tPosition.x > (tWall[i].m_tPosition.x - TILE_SIZE)
			&& m_tPosition.x < (tWall[i].m_tPosition.x + TILE_SIZE)
			&& m_tPosition.y == (tWall[i].m_tPosition.y - TILE_SIZE)
			)
		{
			if (tWall[i].m_bIsClickable == true)
			{
				if (tWall[i].m_bIsClickableOpen != true)
				{
					bColToGround = true;
				}
			}
			else
			{
				bColToGround = true;
			}
		}

		if ((m_tPosition.x + TILE_SIZE == tWall[i].m_tPosition.x
			&& m_tPosition.y == tWall[i].m_tPosition.y)
			||
			(m_tPosition.x - TILE_SIZE == tWall[i].m_tPosition.x
			&& m_tPosition.y == tWall[i].m_tPosition.y))
		{
			if (tWall[i].m_bIsExitOpen == false
				&& tWall[i].m_bIsExit == true
				&& m_iColor == 1)
			{
				tWall[i].m_bIsExitOpen = true;
				tMap.ChangeColor(2, 3, tWall[i].m_tPosition);
			}
		}
		
		if (m_tPosition.x + TILE_SIZE == tWall[i].m_tPosition.x
			&& m_tPosition.y == tWall[i].m_tPosition.y
			&& tWall[i].m_bIsLadder == false
			&& tWall[i].m_bIsBase == false
			&& tWall[i].m_bIsExitOpen == false
			&& tWall[i].m_bIsRack == false
			&& tWall[i].m_bIsClickableOpen == false
			)
		{
			bColToRight = true;
		}

		if (m_tPosition.x - TILE_SIZE == tWall[i].m_tPosition.x
			&& m_tPosition.y == tWall[i].m_tPosition.y
			&& tWall[i].m_bIsLadder == false
			&& tWall[i].m_bIsBase == false
			&& tWall[i].m_bIsExitOpen == false
			&& tWall[i].m_bIsRack == false
			&& tWall[i].m_bIsClickableOpen == false
			)
		{
			bColToLeft = true;
		}

		if (m_tPosition.x == tWall[i].m_tPosition.x
			&& m_tPosition.y > (tWall[i].m_tPosition.y - TILE_SIZE)
			&& m_tPosition.y < (tWall[i].m_tPosition.y + TILE_SIZE)
			&& tWall[i].m_bIsLadder == true
			)
		{
			bIsOnLadder = true;
		}

		if (m_tPosition.x == tWall[i].m_tPosition.x
			&& m_tPosition.y == tWall[i].m_tPosition.y
			)
		{
			if (tWall[i].m_bIsExitOpen == true)
			{
				bIsAtTheEnd = true;
			}
			else if (tWall[i].m_bIsRack == true)
			{
				if (tWall[i].m_iColor == 0)
				{
					bIsOnGreyRack = true;
					tWall[i].m_iColor = m_iColor;

					tMap.ChangeColor(m_iColor, 1, tWall[i].m_tPosition);
					// Fonction changecolor mur
				}
				if (tWall[i].m_iColor == 1)
				{
					bIsOnRedRack = true;
					tWall[i].m_iColor = m_iColor;

					tMap.ChangeColor(m_iColor, 1, tWall[i].m_tPosition);
					// Fonction changecolor mur
				}
				if (tWall[i].m_iColor == 2)
				{
					bIsOnGreenRack = true;
					tWall[i].m_iColor = m_iColor;

					tMap.ChangeColor(m_iColor, 1, tWall[i].m_tPosition);
					// Fonction changecolor mur
				}
			}
		}
	}

	if (m_bIsStopped == false)
	{
		if (bIsAtTheEnd == true
			&& m_iColor == 0)
		{
			// TO DO :
			//
			m_bIsAtTheEnd = true;
			// DELETE LEMMINGS AND ADD ONE TO GOAL
			//
		}
		else if (bIsOnLadder == true)
		{
			m_tPosition.y--;
		}
		else if (bColToGround == true) // Si il touche le sol
		{
			if (m_iDirection == 0) // Si il va à droite
			{
				if (bColToRight == false) // Si il n'y a pas de mur à droite
				{
					m_tPosition.x++;
				}
				else // Si il y a un mur à droite
				{
					m_iDirection = 1;
				}
			}
			else // Si il va à gauche
			{
				if (bColToLeft == false) // Si il n'y a pas de mur à gauche
				{
					m_tPosition.x--;
				}
				else // Si il y a un mur à gauche
				{
					m_iDirection = 0;
				}
			}

		}
		else // Ne touche pas le sol
		{
			m_tPosition.y += 2;
		}
	}

	if (bIsOnGreyRack)
	{
		ChangeColor(0);
	}
	else if (bIsOnRedRack)
	{
		ChangeColor(1);
	}
	else if (bIsOnGreenRack)
	{
		ChangeColor(2);
	}




	GfxSpriteSetPosition(m_tLemmingSprite, m_tPosition.x, m_tPosition.y);
}

void TLemmings::ChangeColor(const int Color) // 0 = Grey, 1 = Red, 2 = Green
{
	m_iColor = Color;
	
	GfxSpriteDestroy(m_tLemmingSprite);

	m_tLemmingSprite = GfxSpriteCreate(tMainTexture);
	GfxSpriteSetCutout(m_tLemmingSprite, m_iColor * 16, 0, 16, 16);
	GfxSpriteSetFilteringEnabled(m_tLemmingSprite, false);
	GfxSpriteSetPosition(m_tLemmingSprite, m_tPosition.x, m_tPosition.y);
}
