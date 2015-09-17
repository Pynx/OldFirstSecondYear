#include "flib.h"
#include "building.h"

const int BUILDING_NUMBER = 42;
const int SCALE = 32;

int g_iBuildingQueued[16]; // File d'attente des buildings, 16 correspondant à la taille maximum d'un ensemble de buildings
int g_iChain = 0;
int g_iQueuePosition = 0;
int g_iIncome = 0;
int g_iBuildingCount = 0;
bool g_bFirstBuy = false;
unsigned int * g_pData;

TBuilding g_tBuilding[BUILDING_NUMBER];

TGfxSprite * g_pSpriteBuilding[BUILDING_NUMBER];
TGfxSprite * g_pSpriteIncome = nullptr;
TGfxSprite * g_pBackgroundSprite = nullptr;
TGfxImage * g_pBackgroundImage = nullptr;
TGfxTexture * g_pBackgroundTexture = nullptr;


void ChangeColor(int iPosX, int iPosY, int iImgSizeX)
{
	GfxTextureDestroy(g_pBackgroundTexture);
	GfxSpriteDestroy(g_pBackgroundSprite);

	g_pData = GfxImageGetData(g_pBackgroundImage);

	const int iIndex = iPosX + (iPosY * iImgSizeX);

	if (g_pData[iIndex] == GfxColor(255, 0, 0, 255))
	{
		g_pData[iIndex] = EGfxColor_White;
	}
	else
	{
		g_pData[iIndex] = EGfxColor_Red;
	}

	g_pBackgroundTexture = GfxTextureCreate(g_pBackgroundImage);
	g_pBackgroundSprite = GfxSpriteCreate(g_pBackgroundTexture);

	GfxSpriteSetScale(g_pBackgroundSprite, 32, 32);
	GfxSpriteSetFilteringEnabled(g_pBackgroundSprite, false);
}

void Initialize()
{
	g_pBackgroundImage = GfxImageLoad("map.tga");
	g_pData = GfxImageGetData(g_pBackgroundImage);

	const int iImgSizeX = GfxImageGetSizeX(g_pBackgroundImage);
	const int iImgSizeY = GfxImageGetSizeY(g_pBackgroundImage);


	for (int y = 0; y < iImgSizeY; ++y)
	{
		for (int x = 0; x < iImgSizeX; ++x)
		{
			const int iIndex = x + (y * iImgSizeX);

			if (g_pData[iIndex] == GfxColor(0, 0, 255, 255) || g_pData[iIndex] == GfxColor(255, 0, 0, 255) || g_pData[iIndex] == GfxColor(0, 255, 0, 255))
			{
				g_pData[iIndex] = EGfxColor_White;
			}
		}
	}


	g_pBackgroundTexture = GfxTextureCreate(g_pBackgroundImage);
	g_pBackgroundSprite = GfxSpriteCreate(g_pBackgroundTexture);

	GfxSpriteSetScale(g_pBackgroundSprite, 32, 32);
	GfxSpriteSetFilteringEnabled(g_pBackgroundSprite, false);

	g_pSpriteIncome = GfxTextSpriteCreate();
	GfxTextSpritePrintf(g_pSpriteIncome, "revenue: $%d", g_iIncome);
	GfxSpriteSetFilteringEnabled(g_pSpriteIncome, false);
	GfxSpriteSetScale(g_pSpriteIncome, 2, 2);
	GfxSpriteSetPosition(g_pSpriteIncome, float((GfxGetDisplaySizeX() / 2) - GfxSpriteGetSizeX(g_pSpriteIncome)), 290);
	GfxSpriteSetColor(g_pSpriteIncome, GfxColor(255, 255, 255, 255));

	TGfxImage * pMapImage = GfxImageLoad("map.tga");
	
	const int iSecondImgSizeX = GfxImageGetSizeX(pMapImage);
	const int iSecondImgSizeY = GfxImageGetSizeY(pMapImage);

	for (int i = 0; i < 3; i++) // Boucle créant les numéros sur les buildings
	{
		for (int y = 0; y < iSecondImgSizeY; ++y)
		{
			for (int x = 0; x < iSecondImgSizeX; ++x)
			{
				const int iIndex = x + (y * iSecondImgSizeX);

				if (i == 0)
				{
					if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 0, 0, 255)) // RED CHECKING & CREATING
					{
						g_tBuilding[g_iBuildingCount].Create(x, y, g_iBuildingCount, SCALE);
						g_iBuildingCount++;
					}
				}
				else if (i == 1)
				{
					if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 255, 0, 255)) // GREEN CHECKING & CREATING
					{
						g_tBuilding[g_iBuildingCount].Create(x, y, g_iBuildingCount, SCALE);
						g_iBuildingCount++;
					}
				}
				else if (i == 2)
				{
					if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 0, 255, 255)) // BLUE CHECKING & CREATING
					{
						g_tBuilding[g_iBuildingCount].Create(x, y, g_iBuildingCount, SCALE);
						g_iBuildingCount++;
					}
				}
			}
		}
	}

	GfxImageDestroy(pMapImage);
}

void Update()
{
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		const int iMouseX = GfxGetCurrentMouseX();
		const int iMouseY = GfxGetCurrentMouseY();

		for (int i = 0; i < BUILDING_NUMBER; i++)
		{
			if ((iMouseX < (g_tBuilding[i].iPosX + SCALE))
				&& (iMouseX >(g_tBuilding[i].iPosX))
				&& (iMouseY < (g_tBuilding[i].iPosY + SCALE))
				&& (iMouseY >(g_tBuilding[i].iPosY))
				)
			{
				ChangeColor(iMouseX / 32, iMouseY / 32, GfxImageGetSizeX(g_pBackgroundImage));
				if (g_tBuilding[i].bBuyed == false)
				{
					g_tBuilding[i].bBuyed = true;
				}
				else
				{
					g_tBuilding[i].bBuyed = false;
				}
			}
		}
	}

	g_iIncome = 0;

	for (int i = 0; i < BUILDING_NUMBER; i++) // Boucle principale -> Va tester chaque building un par un.
	{
		g_iQueuePosition = 0;
		g_iBuildingQueued[g_iQueuePosition] = i;
		g_bFirstBuy = false;

		do
		{
			if (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking < 4)
			{
				if (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].bBuyed == true)
				{
					if (g_bFirstBuy == false)
					{
						g_bFirstBuy = true;
						g_iChain++;
					}
					for (int e = 0; e < BUILDING_NUMBER; e++)
					{



						if (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking == 0) // Test dernier building de la file pour savoir si il doit regarder à droite
						{
							if (((g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosX + 32) == g_tBuilding[e].iPosX) && ((g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosY) == g_tBuilding[e].iPosY)) // Test si building à sa droite
							{
								g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking++; // Si building à sa droite, on lui dit qu'il à check à droite

								if (g_tBuilding[e].iLooking == 0 && g_tBuilding[e].bBuyed == true) // Ce building DOIT avoir été acheté)								
								{
									g_iChain++;
									g_iQueuePosition++;
									g_iBuildingQueued[g_iQueuePosition] = e;
								}
								break;
							}
						}
						else if (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking == 1)
						{
							if (((g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosY + 32) == g_tBuilding[e].iPosY) && (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosX == g_tBuilding[e].iPosX)) // Test si building à sa droite
							{
								g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking++; // Si building à sa droite, on lui dit qu'il à check à droite

								if ((g_tBuilding[e].iLooking == 0) && (g_tBuilding[e].bBuyed == true)) // Ce building DOIT avoir été acheté)								
								{
									g_iChain++;
									g_iQueuePosition++;
									g_iBuildingQueued[g_iQueuePosition] = e;
								}
								break;
							}
						}
						else if (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking == 2)
						{
							if (((g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosX - 32) == (g_tBuilding[e].iPosX)) && ((g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosY) == (g_tBuilding[e].iPosY))) // Test si building à sa droite
							{
								g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking++; // Si building à sa droite, on lui dit qu'il à check à droite
								if ((g_tBuilding[e].iLooking == 0) && (g_tBuilding[e].bBuyed == true)) // Ce building DOIT avoir été acheté)								
								{
									g_iChain++;
									g_iQueuePosition++;
									g_iBuildingQueued[g_iQueuePosition] = e;
								}
								break;
							}
						}
						else if (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking == 3)
						{
							if (((g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosY - 32) == g_tBuilding[e].iPosY) && (g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iPosX == g_tBuilding[e].iPosX)) // Test si building à sa droite
							{
								g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking++; // Si building à sa droite, on lui dit qu'il à check à droite
								if (g_tBuilding[e].iLooking == 0   // Ce building ne doit pas encore avoir été check
									&& g_tBuilding[e].bBuyed == true) // Ce building DOIT avoir été acheté)								
								{
									g_iChain++;
									g_iQueuePosition++;
									g_iBuildingQueued[g_iQueuePosition] = e;
								}
								break;
							}
						}

						if (e == 41 && g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking < 4)
						{
							g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking++;
							break;
						}

					}
				}
				else
				{
					g_tBuilding[g_iBuildingQueued[g_iQueuePosition]].iLooking = 4;
				}
			}
			else if (g_iQueuePosition > 0)
			{
				g_iQueuePosition--;
			}
		} while (g_tBuilding[g_iBuildingQueued[0]].iLooking < 4);

		for (int e = 0; e < g_iChain; e++)
		{
			g_iIncome += ((e + 1) * 1000);
		}
		g_iQueuePosition = 0;
		g_iChain = 0;
	}

	GfxTextSpritePrintf(g_pSpriteIncome, "revenue: $%d", g_iIncome);
	GfxSpriteSetPosition(g_pSpriteIncome, float((GfxGetDisplaySizeX() / 2) - GfxSpriteGetSizeX(g_pSpriteIncome)), 290);

	for (int e = 0; e < BUILDING_NUMBER; e++)
	{
		g_tBuilding[e].iLooking = 0;
	}


}

void Render()
{
	GfxClear(EGfxColor_Black);

	GfxSpriteRender(g_pBackgroundSprite);
	for (int i = 0; i < BUILDING_NUMBER; i++)
	{
		GfxSpriteRender(g_tBuilding[i].m_tBuildingNumberSprite);
	}

	GfxSpriteRender(g_pSpriteIncome);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
