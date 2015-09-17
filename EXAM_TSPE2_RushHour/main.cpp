//TO DO
//Faire level via fichier.txt
//faire colisions
//faire next lvl

/*
1) First create these :

//  TGfxSprite * SPRITE_NAME;
//  TGfxTexture * TEXTURE_NAME;

2) Then load a texture in a var

//  TEXTURE_NAME = GfxTextureLoad("gfx/tileset.tga");

3) Choose from which texture you must take a part

//  SPRITE_NAME = GfxSpriteCreate(TEXTURE_NAME);

4) choose what you take from the texture

//  GfxSpriteSetCutout(SPRITE_NAME, PosX , PosY, SizeX, SizeY);

5) choose the scale

//  GfxSpriteSetScale(SPRITE_NAME, SizeX, SizeY);

6) Use this

//  GfxSpriteSetFilteringEnabled(SPRITE_NAME, false);

7) Set the position

//  GfxSpriteSetPosition(SPRITE_NAME, PosX, PosY);

OPTIONAL 8) Choose the position point position

//  GfxSpriteSetPivot(SPRITE_NAME, X, Y);

*/

#include "flib.h"

const int SCALE = 1;
const int TILE_SIZE = 36;
const int g_iMaxCarNumber = 25;
const int g_iMaxTextureNumber = 31;
const int g_iDifferentCar = 15;
const int g_iTileOfGame = 6;

int g_PosX = 0;
int g_PosY = 0;
int g_iCarCount = 0;
int g_iLevel = 1;

int g_iMouseX = 0;
int g_iMouseY = 0;

bool g_bSeenCar[g_iDifferentCar];
bool g_bAllowedMove = true;

TGfxTexture * g_pTextureCar[g_iMaxTextureNumber];
TGfxSprite * g_pSpriteCar[g_iMaxCarNumber];

TGfxImage * g_pBackgroundImage = nullptr;
TGfxSprite * g_pBackgroundSprite = nullptr;
TGfxTexture * g_pBackgroundTexture = nullptr;

TGfxSprite * g_pNextLevelImage = nullptr;
TGfxSprite * g_pPreviousLevelImage = nullptr;
TGfxSprite * g_pLevelImage = nullptr;

TGfxFile * g_pFile;

unsigned char g_cItem;

void CreateLevel(unsigned char cItem)
{
	const char * g_pCarFileName[] =
	{
		"ah.gif", "av.gif", "bh.gif", "bv.gif", "ch.gif", "cv.gif", "dh.gif", "dv.gif",
		"eh.gif", "ev.gif", "fh.gif", "fv.gif", "gh.gif", "gv.gif", "hh.gif", "hv.gif",
		"ih.gif", "iv.gif", "jh.gif", "jv.gif", "kh.gif", "kv.gif", "lh.gif", "lv.gif",
		"mh.gif", "mv.gif", "nh.gif", "nv.gif", "oh.gif", "ov.gif", "player.gif",
	};

	for (int i = 0; i < g_iDifferentCar; i++)
	{
		g_bSeenCar[i] = false;
	}

	for (int i = 0; i < g_iMaxTextureNumber; i++) // Create all textures
	{
		g_pTextureCar[i] = GfxTextureLoad(g_pCarFileName[i]);
	}

	// A to O

	while (true)
	{
		if (cItem == 'A')
		{
			if (g_bSeenCar[0] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'A')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[0]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[1]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[0] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'B')
		{
			if (g_bSeenCar[1] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'B')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[2]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[3]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[1] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'C')
		{
			if (g_bSeenCar[2] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'C')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[4]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[5]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[2] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'D')
		{
			if (g_bSeenCar[3] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'D')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[6]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[7]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[3] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'E')
		{
			if (g_bSeenCar[4] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'E')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[8]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[9]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[4] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'F')
		{
			if (g_bSeenCar[5] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'F')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[10]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[11]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[5] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'G')
		{
			if (g_bSeenCar[6] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'G')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[12]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[13]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[6] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'H')
		{
			if (g_bSeenCar[7] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'H')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[14]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[15]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[7] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'I')
		{
			if (g_bSeenCar[8] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'I')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[16]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[17]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[8] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'J')
		{
			if (g_bSeenCar[9] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'J')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[18]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[19]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[9] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'K')
		{
			if (g_bSeenCar[10] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'K')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[20]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[21]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[10] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'L')
		{
			if (g_bSeenCar[11] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'L')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[22]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[23]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[11] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'M')
		{
			if (g_bSeenCar[12] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'M')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[24]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[25]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[12] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'N')
		{
			if (g_bSeenCar[13] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'N')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[26]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[27]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[13] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'O')
		{
			if (g_bSeenCar[14] != true)
			{
				//Si il y a un A à droite, on crée l'horizontal, sinon le vertical

				cItem = GfxFileReadChar(g_pFile);
				if (cItem == 'O')
				{
					//Afficher sprite h
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[28]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_PosX++;
					g_PosX++;
					cItem = GfxFileReadChar(g_pFile);
					cItem = GfxFileReadChar(g_pFile);
				}
				else
				{
					//Afficher sprite v
					g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[29]);
					GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], (g_PosX*TILE_SIZE), (g_PosY*TILE_SIZE));
					GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
					g_iCarCount++;
					g_bSeenCar[14] = true;
				}
				g_PosX++;
			}
			else
			{
				g_PosX++;
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else if (cItem == 'P')
		{
			g_pSpriteCar[g_iCarCount] = GfxSpriteCreate(g_pTextureCar[30]);
			GfxSpriteSetPosition(g_pSpriteCar[g_iCarCount], ((g_PosX)*TILE_SIZE), (g_PosY*TILE_SIZE));
			GfxSpriteSetFilteringEnabled(g_pSpriteCar[g_iCarCount], false);
			g_iCarCount++;
			g_PosX++;
			g_PosX++;
		
			cItem = GfxFileReadChar(g_pFile);
			cItem = GfxFileReadChar(g_pFile);
		}
		else if(cItem == '.')
		{
			g_PosX++;
			cItem = GfxFileReadChar(g_pFile);
		}
		else if(cItem == '\r')
		{
			if (g_PosY == 5)
			{
				break;
			}
			else
			{
				g_PosY++;
				g_PosX = 0;
				cItem = GfxFileReadChar(g_pFile);
				cItem = GfxFileReadChar(g_pFile);
			}
		}
		else
		{
			g_PosX++;
			cItem = GfxFileReadChar(g_pFile);
		}

	} 
}

void Initialize()
{
	bool g_bSeenCar[g_iDifferentCar];
	g_pFile = GfxFileOpenRead("level01.txt");
	g_cItem = GfxFileReadChar(g_pFile);
	CreateLevel(g_cItem);

	const int iScreenSizeX = GfxGetDisplaySizeX();
	const int iScreenSizeY = GfxGetDisplaySizeY();
	const int iGameSize = (g_iTileOfGame * TILE_SIZE);
	const int iGamePosX = (iScreenSizeX / 2) - (iGameSize / 2);
	const int iGamePosY = (iScreenSizeY / 2) - (iGameSize / 2);


	for (int i = 0; i < g_iMaxCarNumber; i++)
	{
		if (g_pSpriteCar[i] != nullptr)
		{
			GfxSpriteSetPosition(g_pSpriteCar[i], (GfxSpriteGetPositionX(g_pSpriteCar[i]) + iGamePosX), (GfxSpriteGetPositionY(g_pSpriteCar[i]) + iGamePosY));
		}
	}


	g_pBackgroundImage = GfxImageCreate(1, 1);
	unsigned int * pData = GfxImageGetData(g_pBackgroundImage);
	*pData = GfxColor(200, 200, 200, 255);
	g_pBackgroundTexture = GfxTextureCreate(g_pBackgroundImage);
	g_pBackgroundSprite = GfxSpriteCreate(g_pBackgroundTexture);
	GfxSpriteSetScale(g_pBackgroundSprite, (g_iTileOfGame*TILE_SIZE), (g_iTileOfGame*TILE_SIZE));
	GfxSpriteSetPosition(g_pBackgroundSprite, iGamePosX, iGamePosY);

	g_pNextLevelImage = GfxTextSpriteCreate();
	g_pPreviousLevelImage = GfxTextSpriteCreate();
	g_pLevelImage = GfxTextSpriteCreate();

	GfxTextSpritePrintf(g_pNextLevelImage, "next");
	GfxTextSpritePrintf(g_pPreviousLevelImage, "prev");
	GfxTextSpritePrintf(g_pLevelImage, "Level %d", g_iLevel);

	GfxSpriteSetFilteringEnabled(g_pNextLevelImage, false);
	GfxSpriteSetFilteringEnabled(g_pPreviousLevelImage, false);
	GfxSpriteSetFilteringEnabled(g_pLevelImage, false);

	GfxSpriteSetScale(g_pNextLevelImage, 2, 2);
	GfxSpriteSetScale(g_pPreviousLevelImage, 2, 2);
	GfxSpriteSetScale(g_pLevelImage, 2, 2);

	GfxSpriteSetPosition(g_pNextLevelImage, 380, iScreenSizeY / 2);
	GfxSpriteSetPosition(g_pPreviousLevelImage, 40, iScreenSizeY / 2);
	GfxSpriteSetPosition(g_pLevelImage, iScreenSizeX / 2 - (GfxSpriteGetSizeX(g_pLevelImage)), 20);

}

void Update()
{
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		g_iMouseX = GfxInputGetMousePositionX(0);
		g_iMouseY = GfxInputGetMousePositionY(0);

		for (int i = 0; i < g_iMaxCarNumber; i++)
		{

			if (g_pSpriteCar[i] != nullptr)
			{
				int iSpriteSizeX = GfxSpriteGetSizeX(g_pSpriteCar[i]);
				if (iSpriteSizeX == 107)
				{
					iSpriteSizeX = 108;
				}
				int iSpriteSizeY = GfxSpriteGetSizeY(g_pSpriteCar[i]);
				if (iSpriteSizeY == 107)
				{
					iSpriteSizeY = 108;
				}
				const int iSpritePositionX = GfxSpriteGetPositionX(g_pSpriteCar[i]);
				const int iSpritePositionY = GfxSpriteGetPositionY(g_pSpriteCar[i]);

				if (iSpriteSizeX > TILE_SIZE) // Voiture horizontale
				{
					if (g_iMouseX > iSpritePositionX
						&& g_iMouseX < (iSpritePositionX + TILE_SIZE)
						&& g_iMouseY > iSpritePositionY
						&& g_iMouseY < (iSpritePositionY + TILE_SIZE)
						)// CLic à gauche
					{ // Start moving cond right
						for (int e = 0; e < g_iMaxCarNumber; e++)
						{							
							if (g_pSpriteCar[e] != nullptr)
							{
								const int iSpriteSecondSizeX = GfxSpriteGetSizeX(g_pSpriteCar[e]);
								const int iSpriteSecondSizeY = GfxSpriteGetSizeY(g_pSpriteCar[e]);
								const int iSpriteSecondPositionX = GfxSpriteGetPositionX(g_pSpriteCar[e]);
								const int iSpriteSecondPositionY = GfxSpriteGetPositionY(g_pSpriteCar[e]);
								if (((iSpritePositionX + iSpriteSizeX)) == iSpriteSecondPositionX
									&& iSpritePositionY >= iSpriteSecondPositionY
									&& iSpritePositionY < (iSpriteSecondPositionY + iSpriteSecondSizeY))
								{
									g_bAllowedMove = false;
								}
							}
						}
						if (g_bAllowedMove == true)
						{
							GfxSpriteSetPosition(g_pSpriteCar[i], (iSpritePositionX + TILE_SIZE), iSpritePositionY);
						}
						g_bAllowedMove = true;
					} // End moving cond right
					else if (g_iMouseX > (iSpritePositionX + (iSpriteSizeX - TILE_SIZE))
						&& g_iMouseX < (iSpritePositionX + iSpriteSizeX)
						&& g_iMouseY > iSpritePositionY
						&& g_iMouseY < (iSpritePositionY + TILE_SIZE)
						)// CLic à droite
					{ // Start moving left
						for (int e = 0; e < g_iMaxCarNumber; e++)
						{
							if (g_pSpriteCar[e] != nullptr)
							{
								const int iSpriteSecondSizeX = GfxSpriteGetSizeX(g_pSpriteCar[e]);
								const int iSpriteSecondSizeY = GfxSpriteGetSizeY(g_pSpriteCar[e]);
								const int iSpriteSecondPositionX = GfxSpriteGetPositionX(g_pSpriteCar[e]);
								const int iSpriteSecondPositionY = GfxSpriteGetPositionY(g_pSpriteCar[e]);
								if (iSpritePositionX == (iSpriteSecondPositionX + iSpriteSecondSizeX)
									&& iSpritePositionY >= iSpriteSecondPositionY
									&& iSpritePositionY < (iSpriteSecondPositionY + iSpriteSecondSizeY))
								{
									g_bAllowedMove = false;
								}
							}
						}
						if (g_bAllowedMove == true)
						{
							GfxSpriteSetPosition(g_pSpriteCar[i], (iSpritePositionX - TILE_SIZE), iSpritePositionY);
						}
						g_bAllowedMove = true;
					} // End moving left
				}
				else // Voiture verticale
				{
					if (g_iMouseX > iSpritePositionX
						&& g_iMouseX < (iSpritePositionX + TILE_SIZE)
						&& g_iMouseY > iSpritePositionY
						&& g_iMouseY < (iSpritePositionY + TILE_SIZE)
						)// CLic en haut
					{ // Start moving Down
						for (int e = 0; e < g_iMaxCarNumber; e++)
						{
							if (g_pSpriteCar[e] != nullptr)
							{
								int iSpriteSecondSizeX = GfxSpriteGetSizeX(g_pSpriteCar[e]);
								if (iSpriteSecondSizeX == 107)
								{
									iSpriteSecondSizeX = 108;
								}
								int iSpriteSecondSizeY = GfxSpriteGetSizeY(g_pSpriteCar[e]);
								if (iSpriteSecondSizeY == 107)
								{
									iSpriteSecondSizeY = 108;
								}
								int iSpriteSecondPositionX = GfxSpriteGetPositionX(g_pSpriteCar[e]);
								int iSpriteSecondPositionY = GfxSpriteGetPositionY(g_pSpriteCar[e]);
								if (iSpritePositionY == (iSpriteSecondPositionY - iSpriteSizeY)
									&& iSpritePositionX >= iSpriteSecondPositionX
									&& iSpritePositionX < (iSpriteSecondPositionX + iSpriteSecondSizeX)
									)
								{
									g_bAllowedMove = false;
								}
							}
						}
						if (g_bAllowedMove == true)
						{
							GfxSpriteSetPosition(g_pSpriteCar[i], iSpritePositionX, (iSpritePositionY + TILE_SIZE));
						}
						g_bAllowedMove = true;
					} // End moving up
					else if (g_iMouseX > iSpritePositionX
						&& g_iMouseX < (iSpritePositionX + TILE_SIZE)
						&& g_iMouseY >(iSpritePositionY + (iSpriteSizeY - TILE_SIZE))
						&& g_iMouseY < (iSpritePositionY + iSpriteSizeY)
						)// CLic en bas
					{ // Start moving up
						for (int e = 0; e < g_iMaxCarNumber; e++)
						{
							if (g_pSpriteCar[e] != nullptr)
							{
								const int iSpriteSecondSizeX = GfxSpriteGetSizeX(g_pSpriteCar[e]);
								const int iSpriteSecondSizeY = GfxSpriteGetSizeY(g_pSpriteCar[e]);
								const int iSpriteSecondPositionX = GfxSpriteGetPositionX(g_pSpriteCar[e]);
								const int iSpriteSecondPositionY = GfxSpriteGetPositionY(g_pSpriteCar[e]);
								if (iSpritePositionY == (iSpriteSecondPositionY + iSpriteSecondSizeY)
									&& iSpritePositionX >= iSpriteSecondPositionX
									&& iSpritePositionX < (iSpriteSecondPositionX + iSpriteSecondSizeX))
								{
									g_bAllowedMove = false;
								}
							}
						}
						if (g_bAllowedMove == true)
						{
							GfxSpriteSetPosition(g_pSpriteCar[i], iSpritePositionX, (iSpritePositionY - TILE_SIZE));
						}
						g_bAllowedMove = true;
					} // End moving up
				}
			}// Fin if sprite not nullptr
		}// Fin boucle test all vehicle
	}
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_pBackgroundSprite);
	GfxSpriteRender(g_pNextLevelImage);
	GfxSpriteRender(g_pPreviousLevelImage);
	GfxSpriteRender(g_pLevelImage);
	for (int i = 0; i < g_iMaxCarNumber; i++)
	{
		if (g_pSpriteCar[i] != nullptr)
		{
			GfxSpriteRender(g_pSpriteCar[i]);
		}
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render); // Fait le le lien avec les autres parties
}
