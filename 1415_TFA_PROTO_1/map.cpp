#include "flib.h"
#include "flib_vec2.h"
#include "map.h"
#include "global.h"



void TMap::Readmap(const int SCALE, const int TILE_SIZE, const int PLAYERPOSX, const int PLAYERPOSY, const int MAX_WALL)
{
	
	TGfxImage * pMapImage = GfxImageLoad("gfx/finishedmap.tga");
	TGfxTexture * pTexture = GfxTextureLoad("gfx/tileset.tga");
	TGfxImage * pTextureImage = GfxImageLoad("gfx/tileset.tga");

	unsigned int * iTextureData = GfxImageGetData(pTextureImage);

	int iImgSizeX = GfxImageGetSizeX(pMapImage);
	int iImgSizeY = GfxImageGetSizeY(pMapImage);
	int iWallCpt = 0;

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
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tWallTexturePos.x*(TILE_SIZE*SCALE)) + ((tWallTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						//iData[iTileIndex] = EGfxColor_Black;
						
						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 0, 0, 255)) // Death wall
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].bIsKilling = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tDeathTexturePos.x*(TILE_SIZE*SCALE)) + ((tDeathTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(200, 200, 200, 255)) // The End Wall
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].bIsTheEnd = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tTheEndTexturePos.x*(TILE_SIZE*SCALE)) + ((tTheEndTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 255, 0, 255)) // Speed boost to right
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].tBoost = TGfxVec2(10, 0);
				tWall[iWallCpt].bIsBoost = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tRightSpeedBoostTexturePos.x*(TILE_SIZE*SCALE)) + ((tRightSpeedBoostTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 0, 255, 255)) // Wall no Collision above
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].bCollisionAbove = false;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tTrapWallTexturePos.x*(TILE_SIZE*SCALE)) + ((tTrapWallTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 255, 0, 255)) // Jump block
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].tBoost = TGfxVec2(0, -4);
				tWall[iWallCpt].bIsBoost = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tUpSpeedBoostTexturePos.x*(TILE_SIZE*SCALE)) + ((tUpSpeedBoostTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(0, 255, 255, 255)) // Grap Block
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].bIsGrappable = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tGrapTexturePos.x*(TILE_SIZE*SCALE)) + ((tGrapTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 0, 255, 255)) // Speed boost to left
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].tBoost = TGfxVec2(-10, 0);
				tWall[iWallCpt].bIsBoost = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tLeftSpeedBoostTexturePos.x*(TILE_SIZE*SCALE)) + ((tLeftSpeedBoostTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(100, 100, 100, 255)) // Wall jump
			{
				//Wall item creation begin
				tWall[iWallCpt].tPosition = TGfxVec2((x*(TILE_SIZE * SCALE)), (y*(TILE_SIZE * SCALE)));
				tWall[iWallCpt].bIsWallJumpable = true;
				iWallCpt++;
				//Wall item creation end
				iTextureIndexBase = ((tWallJumpTexturePos.x*(TILE_SIZE*SCALE)) + ((tWallJumpTexturePos.y*(TILE_SIZE*SCALE) * GfxImageGetSizeX(pTextureImage))));
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = iTextureData[iTextureIndex];
					}
				}
			}
			else if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(200, 150, 50, 255)) // Player Start
			{
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));

						iData[iTileIndex] = EGfxColor_Black;
					}
				}

				tSpawnPosition = TGfxVec2(float(x * (TILE_SIZE*SCALE)), float(y * (TILE_SIZE*SCALE)));
			}
			else
			{
				for (int LevelY = 0; LevelY < (TILE_SIZE*SCALE); ++LevelY)
				{
					for (int LevelX = 0; LevelX < (TILE_SIZE*SCALE); ++LevelX)
					{
						iTileIndex = iTileIndexBase + (LevelX + (LevelY * iLevelSizeX));
						iTextureIndex = iTextureIndexBase + (LevelX + (LevelY * GfxImageGetSizeX(pTextureImage)));
						
						iData[iTileIndex] = EGfxColor_Black;
					}
				}
			}
		}
	}

	g_tLevelTexture = GfxTextureCreate(g_tLevelImage);
	g_tLevelSprite = GfxSpriteCreate(g_tLevelTexture);
	GfxSpriteSetPosition(g_tLevelSprite, (PLAYERPOSX - tSpawnPosition.x), (PLAYERPOSY - tSpawnPosition.y));


	for (int i = 0; i < MAX_WALL; i++)
	{
		tWall[i].tPosition.x = tWall[i].tPosition.x + (PLAYERPOSX - tSpawnPosition.x);
		tWall[i].tPosition.y = tWall[i].tPosition.y + (PLAYERPOSY - tSpawnPosition.y);
	}
	GfxSpriteSetPosition(g_tLevelSprite, (PLAYERPOSX - tSpawnPosition.x), (PLAYERPOSY - tSpawnPosition.y));
}
