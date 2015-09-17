#include "flib.h"
#include "flib_vec2.h"
#include "wall.h"
#include "global.h"

void TWall::Input(const int TILE_SIZE)
{
	if (m_bIsClickable == true) // Clickable Wall
	{
		bool bOldOpenStatus = m_bIsClickableOpen;

		if (m_bIsBasePosOpen == true) // Ouvert -> Click to activate Wall
		{
			m_bIsClickableOpen = true;
		}
		else // Fermé -> Click to Deactivate Wall
		{
			m_bIsClickableOpen = false;
		}

		if (GfxInputIsPressed(EGfxInputID_MouseLeft))
		{
			const int iMouseX = GfxInputGetMousePositionX();
			const int iMouseY = GfxInputGetMousePositionY();

			if (iMouseX > (m_tPosition.x - (TILE_SIZE*2))
				&& iMouseX < (m_tPosition.x + (TILE_SIZE * 3))
				&& iMouseY >(m_tPosition.y - (TILE_SIZE*2))
				&& iMouseY < (m_tPosition.y + (TILE_SIZE * 3)))
			{
				if (m_bIsBasePosOpen == true) // Ouvert -> Click to activate Wall
				{
					m_bIsClickableOpen = false;
				}
				else // Fermé -> Click to Deactivate Wall
				{
					m_bIsClickableOpen = true;
				}
			}
		}

		if (bOldOpenStatus != m_bIsClickableOpen)
		{
			if (m_bIsClickableOpen == true)
			{
				tMap.ChangeColor(0, 2, m_tPosition);
				// Fonction qui passe en bloc pleins
			}
			else
			{
				tMap.ChangeColor(1, 2, m_tPosition);
				// Fonction qui passe en bloc vides
			}
		}

	}
	else // Spawn Base
	{
		if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
		{
			const int iMouseX = GfxInputGetMousePositionX();
			const int iMouseY = GfxInputGetMousePositionY();

			if (iMouseX > (m_tPosition.x - TILE_SIZE)
				&& iMouseX < (m_tPosition.x + (TILE_SIZE * 2))
				&& iMouseY >(m_tPosition.y - TILE_SIZE)
				&& iMouseY < (m_tPosition.y + (TILE_SIZE * 2))) // Add Condition : Lemmings position not close to spawn
			{
				if (g_iLemmingsCpt < 5)
				{
					tLemmings[g_iLemmingsCpt].Spawn(TGfxVec2(m_tPosition.x + TILE_SIZE, m_tPosition.y));
				}
			}
		}
	}



	/*
	


	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	
	*/
}