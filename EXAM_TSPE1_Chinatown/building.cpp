#include "flib.h"
#include "building.h"

void TBuilding::Create(const int iPosX, const int iPosY, const int iBuildingNumber, const int SCALE)
{
	this->iPosX = iPosX * SCALE;
	this->iPosY = iPosY * SCALE;

	TBuilding::m_tBuildingNumberSprite = GfxTextSpriteCreate();
	if (iBuildingNumber < 9) // Rajoute un 0 devant les nombres plus petit que 10 pour qu'ils aient tous la même taille
	{
		GfxTextSpritePrintf(this->m_tBuildingNumberSprite, "0%d", (iBuildingNumber+1));
	}
	else
	{
		GfxTextSpritePrintf(this->m_tBuildingNumberSprite, "%d", (iBuildingNumber+1));
	}

	GfxSpriteSetFilteringEnabled(this->m_tBuildingNumberSprite, false);
	GfxSpriteSetPosition(this->m_tBuildingNumberSprite, float((iPosX * SCALE) + ((SCALE / 2) - (GfxSpriteGetSizeX(this->m_tBuildingNumberSprite) / 2))),
		float((iPosY * SCALE) + ((SCALE / 2) - (GfxSpriteGetSizeY(this->m_tBuildingNumberSprite) / 2))));

	GfxSpriteSetColor(this->m_tBuildingNumberSprite, GfxColor(0, 0, 0, 255));
}