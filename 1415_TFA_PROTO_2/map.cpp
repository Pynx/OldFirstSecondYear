#include "flib.h"
#include "flib_vec2.h"
#include "map.h"
#include "global.h"


void TMap::DeleteMap()
{
	g_tLevelImage = nullptr;
	g_tLevelSprite = nullptr;
}

void TMap::CreateVar()
{
	g_tLevelTexture = GfxTextureLoad("gfx/tileset.tga");
	g_tTextureImage = GfxImageLoad("gfx/tileset.tga");
}

int TMap::Readmap(const int SCALE, const int TILE_SIZE, const int MAX_WALL, const int g_iLevel)
{
	// g_tLevelImage -> L'image de laquelle on crée le sprite, elle est modifiée jusqu'à la fin et ne dois pas être delete ! Pour pouvoir la modifier
	// g_tLevelTexture -> La texture du tileset, nécessaire pour le tileset, à ne pas delete
	// g_tLevelSprite -> Ce qu'on affichera à l'écran
	// pMapImage -> Image de la map, permet de comparer son futur pData pour modifier l'image du sprite final, Map du level, initialisée au début de cette fonction et destroy à la fin de celle ci
	// g_tTextureImage -> Image du tileset, créé une fois, à ne pas destroy

	TGfxImage * pMapImage = nullptr;

	if (g_iLevel == 1)
	{
		pMapImage = GfxImageLoad("gfx/level1.tga");
	}
	else if (g_iLevel == 2)
	{
		pMapImage = GfxImageLoad("gfx/level2.tga");
	}
	else if (g_iLevel == 3)
	{
		pMapImage = GfxImageLoad("gfx/level3.tga");
	}
	else if (g_iLevel == 4)
	{
		pMapImage = GfxImageLoad("gfx/level4.tga");
	}

	unsigned int * iTextureData = GfxImageGetData(g_tTextureImage);

	int iImgSizeX = GfxImageGetSizeX(pMapImage);
	int iImgSizeY = GfxImageGetSizeY(pMapImage);
	int iWallCpt = 0;


	if (g_tLevelImage != nullptr)
	{
		GfxImageDestroy(g_tLevelImage);
	}

	g_tLevelImage = GfxImageCreate((iImgSizeX*(TILE_SIZE*SCALE)), (iImgSizeY*(TILE_SIZE*SCALE)));

	unsigned int * iData = GfxImageGetData(g_tLevelImage);
	*iData = EGfxColor_Black;

	int iLevelSizeX = GfxImageGetSizeX(g_tLevelImage);
	TGfxVec2 tSpawnPosition;

	for (int y = 0; y < iImgSizeY; ++y)
	{
		for (int x = 0; x < iImgSizeX; ++x)
		{
			int iIndex = x + y * iImgSizeX;
			int iTileIndexBase = ((x * (TILE_SIZE*SCALE)) + (y * ((TILE_SIZE * SCALE) * iLevelSizeX)));
			int iTileIndex = 0;
			int iTextureIndexBase = 0;
			int iTextureIndex = 0;


			if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 0, 0, 255)) // Simple wall
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tWallTexturePos.x*(TILE_SIZE*SCALE)) + ((tWallTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						//iData[iTileIndex] = EGfxColor_Black;

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 0, 255, 255)) // Open Clickable Door
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsClickable = true;
				tWall[iWallCpt].m_bIsClickableOpen = true;
				tWall[iWallCpt].m_bIsBasePosOpen = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tOpenedDoorTexturePos.x*(TILE_SIZE*SCALE)) + ((tOpenedDoorTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));
			
						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 255, 0, 255)) // Closed Clickable Door
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsClickable = true;
				tWall[iWallCpt].m_bIsClickableOpen = false;
				tWall[iWallCpt].m_bIsBasePosOpen = false;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tClosedDoorTexturePos.x*(TILE_SIZE*SCALE)) + ((tClosedDoorTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 0, 0, 255)) // Red Rack
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsRack = true;
				tWall[iWallCpt].m_iColor = 1; // 1 = Red
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tRedRackTexturePos.x*(TILE_SIZE*SCALE)) + ((tRedRackTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 255, 0, 255)) // Green Rack
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsRack = true;
				tWall[iWallCpt].m_iColor = 2; // 2 = Green
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tGreenRackTexturePos.x*(TILE_SIZE*SCALE)) + ((tGreenRackTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(200, 200, 200, 255)) // Grey Rack
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsRack = true;
				tWall[iWallCpt].m_iColor = 0; // 0 = Grey
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tGreyRackTexturePos.x*(TILE_SIZE*SCALE)) + ((tGreyRackTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 0, 255, 255)) // Opened exit
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsExitOpen = true;
				tWall[iWallCpt].m_bIsExit = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tCapturedExitTexturePos.x*(TILE_SIZE*SCALE)) + ((tCapturedExitTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(200, 150, 0, 255)) // Closed exit
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsExitOpen = false;
				tWall[iWallCpt].m_bIsExit = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tNotCapturedExitTexturePos.x*(TILE_SIZE*SCALE)) + ((tNotCapturedExitTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 255, 255, 255)) // Spawn
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsBase = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tBaseTexturePos.x*(TILE_SIZE*SCALE)) + ((tBaseTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(50, 100, 200, 255)) // Ladder
			{
				//Wall item creation begin
				tWall[iWallCpt].m_tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].m_bIsLadder = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tLadderTexturePos.x*(TILE_SIZE*SCALE)) + ((tLadderTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(g_tTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else
			{
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(g_tTextureImage)));
			
						iData[iTileIndex] = EGfxColor_Black;
					}
				}
			}
		}
	}

	if (g_tLevelSprite != nullptr)
	{
		GfxSpriteDestroy(g_tLevelSprite);
	}
	if (g_tLevelTexture != nullptr)
	{
		GfxTextureDestroy(g_tLevelTexture);
	}

	g_tLevelTexture = GfxTextureCreate(g_tLevelImage);
	g_tLevelSprite = GfxSpriteCreate(g_tLevelTexture);

	GfxImageDestroy(pMapImage);
	
	return iWallCpt;
}

void TMap::ChangeColor(const int iTilePosX, const int iTilePosY, TGfxVec2 tPosition)
{
	unsigned int * g_pData;
	unsigned int * g_g_tLevelTextureData;


	TGfxTexture * g_tLevelTexture = GfxTextureLoad("gfx/tileset.tga");
	TGfxImage * g_tTextureImage = GfxImageLoad("gfx/tileset.tga");	
	
	g_pData = GfxImageGetData(g_tLevelImage);
	g_g_tLevelTextureData = GfxImageGetData(g_tTextureImage);
	
	const int iImgSizeX = GfxImageGetSizeX(g_tLevelImage);
	const int iImgSizeY = GfxImageGetSizeX(g_tLevelImage);
	const int iTextSizeX = GfxTextureGetSizeX(g_tLevelTexture);
	const int iTextSizeY = GfxTextureGetSizeY(g_tLevelTexture);
	
	int iIndex = tPosition.x + (tPosition.y * iImgSizeX);
	int iIndexBase = tPosition.x + (tPosition.y * iImgSizeX);
	//------------------------------------
	int iTileIndex = iTilePosX * 16 + ((iTilePosY * 16) * iTextSizeX);
	int iTileIndexBase = iTilePosX * 16 + ((iTilePosY * 16) * iTextSizeX);
	// Fonctionne uniquement avec le tileset actuel, 
	//c'est à dire sur la premiere ligne et dans l'ordre gris, rouge, vert.

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			iIndex = iIndexBase + (x + (y * iImgSizeX));
			iTileIndex = iTileIndexBase + (x + (y * iTextSizeX));

			//iData[iTileIndex] = EGfxColor_Black;

			g_pData[iIndex] = g_g_tLevelTextureData[iTileIndex];
		}
	}


	GfxTextureDestroy(g_tLevelTexture);
	GfxImageDestroy(g_tTextureImage);
	
	g_tLevelTexture = GfxTextureCreate(g_tLevelImage);
	g_tLevelSprite = GfxSpriteCreate(g_tLevelTexture);
	GfxSpriteSetFilteringEnabled(g_tLevelSprite, false);



	//g_pBackgroundTexture = GfxTextureCreate(g_pBackgroundImage);
	//g_pBackgroundSprite = GfxSpriteCreate(g_pBackgroundTexture);
	//
	//GfxSpriteSetScale(g_pBackgroundSprite, 32, 32);
	//GfxSpriteSetFilteringEnabled(g_pBackgroundSprite, false);
}
