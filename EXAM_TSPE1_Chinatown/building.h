#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include "flib.h"

struct TBuilding
{
	TGfxSprite * m_tBuildingNumberSprite = nullptr;

	unsigned int * m_pData;

	int iPosX; // initialisée à une position correcte dans la fonction Create
	int iPosY; // Like above
	int iLooking = 0;

	bool bBuyed = false;
	
	void Create(const int iPosX, const int iPosY, const int iBuildingNumber, const int SCALE);
};


#endif