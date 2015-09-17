// TO DO :
// 1 : Faire le sokoban
// 2 : Ajouter des sprite sympa
// 3 : Cr�er un �diteur


#include "flib.h"

const int SCALE = 1;
const int TILE_SIZE = 16;
int iPosX = 0;
int iPosY = 0;
int g_XLign = 0;
int g_YCol = 0;
int g_iWallCount = 0;
int g_iBoxCount = 0;
int g_iGoalCount = 0;
int mPosX = 0;
int mPosY = 0;
int OldMPosX = 0;
int OldMPosY = 0;

bool g_bFileOpen = false;
bool g_bNextLevel = true;
bool g_bBoxColl = false;
bool g_bEnd = true;




TGfxFile * pFile;
TGfxSprite * g_pSpriteHero;       // cItem = @
TGfxSprite * g_pSpriteWall[500];  // cItem = #
TGfxSprite * g_pSpriteGoal[50];   // cItem = .
TGfxSprite * g_pSpriteBox[50];    // cItem = $

TGfxTexture * g_pTexture;

TGfxSprite * CreateTile(const TGfxTexture * g_pTexture, const int iPosX, const int iPosY, const int iTileX, const int iTileY)
{

	TGfxSprite * pSprite = GfxSpriteCreate(g_pTexture);    // On cr�e pSprite et on y met la la variable de la texture charg�e 
	GfxSpriteSetScale(pSprite, float(SCALE), float(SCALE));    // On choisis la taille du sprite appell� pSprite 
	GfxSpriteSetFilteringEnabled(pSprite, false);             // On d�sactive le filtering ( � laisse )
	GfxSpriteSetCutout(pSprite, iPosX * TILE_SIZE, iPosY * TILE_SIZE, TILE_SIZE, TILE_SIZE);    // On choisis ce qui sera affich� sur un sprite, ici on choisis la taille et la position du sprite dans la texture
	GfxSpriteSetPosition(pSprite, float(SCALE) * TILE_SIZE * iTileX, float(SCALE) * TILE_SIZE * iTileY);     // On choisis o� l'afficher 

	return pSprite;  // toujours mettre le return � la fin car �a sort de la fonction.
}

int Absol(int nbr)
{
	if (nbr < 0)
	{
		nbr = 0 - nbr;
	}
	return nbr;
}

void CreateLevel(unsigned char cItem)
{
	if (cItem == '#')
	{
		g_pSpriteWall[g_iWallCount] = CreateTile(g_pTexture, 6, 1, g_XLign, g_YCol);
		g_iWallCount++;
		g_XLign++;
	}
	else if (cItem == '\r')
	{
		g_XLign = 0;
		g_YCol++;
	}
	else if (cItem == '@')
	{
		iPosX = g_XLign;
		iPosY = g_YCol;
		g_XLign++;
	}
	else if (cItem == '$')
	{
		g_pSpriteBox[g_iBoxCount] = CreateTile(g_pTexture, 7, 4, g_XLign, g_YCol);
		g_iBoxCount++;
		g_XLign++;
	}
	else if(cItem == '.')
	{
		g_pSpriteGoal[g_iGoalCount] = CreateTile(g_pTexture, 8, 4, g_XLign, g_YCol);
		g_iGoalCount++;
		g_XLign++;
	}
	else if (cItem == 32)
	{
		g_XLign++;
	}
	else
	{
		g_XLign++;
	}
}

void ReadLevel(TGfxFile * pFile) // � partir d'un pFile, cette fonction lis le niveau et fais appel 
{ // La variable pFile doit contenir un GfxFileOpenRead du fichier texte contenant les niveaux
	bool bLevelLineRead = false;  // Elle va servir � passer les commentaires du d�but ...


	for (;;)
	{

		const unsigned char cCar = GfxFileReadChar(pFile); // cCar sera une lettre du fichier, et � chaque fois on lira la suivante jusqu'a avoir finit de lire tout le fichier
		if (cCar == ';') // Veut dire que c'est un commentaire. On va donc passer � la ligne suivante en ignorant les charact�res jusqu'a 
		{
			while (GfxFileReadChar(pFile) != '\n'); // Ceci va lire les caract�res un par un jusqu'a trouver un retour � la ligne ! ( On mets \n pour le retour � la ligne )
			if (bLevelLineRead) // Si bLevelLineRead est true ( ce qui veut dire qu'on a fini de lire un niveau !! ) On sortira de la boucle infinie grace � �a !
			{
				break; // Sort du for ! Sinon boucle infinie
			}
		}
		else if (cCar == '\n')
		{
		}
		else
		{
			bLevelLineRead = true;  // En true d�s qu'on commence un niveau :)

			unsigned char cItem = cCar;
			do
			{
				// GfxDbgPrintf("%c", cItem);

				CreateLevel(cItem);

				cItem = GfxFileReadChar(pFile);

			} while (cItem != '\n');

			GfxDbgPrintf("\n");
		}
	}
}  

void Level()
{

	if (g_bNextLevel == true) // Si NextLevel = vrai, on supprime l'ancien lvl et on cr�e le neuf !
	{
		g_XLign = 0;
		g_YCol = 0;

		for (int i = 0; i < g_iWallCount; i++)
		{
			g_pSpriteWall[i] = 0;
		}

		g_iWallCount = 0;

		for (int i = 0; i < g_iBoxCount; i++)
		{
			g_pSpriteBox[i] = 0;
		}

		g_iBoxCount = 0;

		for (int i = 0; i < g_iGoalCount; i++)
		{
			g_pSpriteGoal[i] = 0;
		}

		g_iGoalCount = 0;


		ReadLevel(pFile);								   // lance la fonction cr��e
		g_bNextLevel = false;


		g_pSpriteHero = CreateTile(g_pTexture, 1, 4, iPosX, iPosY);

	}
}

void Initialize()
{
	pFile = GfxFileOpenRead("Sokoban.txt");
	g_pTexture = GfxTextureLoad("gfx/tileset.tga");
}

void Update()
{
	Level();

	if (GfxInputIsJustPressed(EGfxInputID_KeySpace))
	{
		g_bNextLevel = true;
	}

	g_bEnd = true;
	for (int i = 0; i < g_iGoalCount; i++)
	{
		if (g_bEnd == true)
		{
			g_bEnd = false;
			for (int e = 0; e < g_iBoxCount; e++)
			{
				if (GfxSpriteGetPositionX(g_pSpriteGoal[i]) == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteGoal[i]) == GfxSpriteGetPositionY(g_pSpriteBox[e]))
				{
					g_bEnd = true;
				}
			}
		}
	}

	if (g_bEnd == true)
	{
		g_bNextLevel = true;
	}



	//---------------------- MOVE START ---------------------------------------



	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		OldMPosX = int(GfxGetCurrentMouseX());
		OldMPosY = int(GfxGetCurrentMouseY());
	}
	if (GfxInputIsJustReleased(EGfxInputID_MouseLeft))
	{
		mPosX = int(GfxGetCurrentMouseX());
		mPosY = int(GfxGetCurrentMouseY());

		int absX = Absol((OldMPosX - mPosX));
		int absY = Absol((OldMPosY - mPosY));


		// D�but move � droite
		if (absX > absY && OldMPosX < mPosX)
		{
			iPosX++;
			// D�but collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosX--;
				}
			}
			// Fin collision mur

			// D�but collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//D�but collision box � box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) +16 == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosX--;
							g_bBoxColl = true;
						}
					}
					//Fin collision box � box
					//---------collision box a mur-----------
					for (int e = 0; e < g_iWallCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) + 16 == GfxSpriteGetPositionX(g_pSpriteWall[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) == GfxSpriteGetPositionY(g_pSpriteWall[e]))
						{

							iPosX--;
							g_bBoxColl = true;
						}
					}
					//---------collision box a mur-----------
					if (g_bBoxColl == false)
					{
						GfxSpriteSetPosition(g_pSpriteBox[i], GfxSpriteGetPositionX(g_pSpriteBox[i]) + 16, GfxSpriteGetPositionY(g_pSpriteBox[i]));
					}
				}
			}
			// Fin collision box
		}
		// Fin move � droite

		//---------------------------------------------------------------------------------------------------------------------------------------------------------

		
		// Debut move � gauche
		if (absX > absY && OldMPosX > mPosX)
		{
			iPosX--;
			// D�but collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosX++;
				}
			}
			// Fin collision mur

			// D�but collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//D�but collision box � box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) - 16 == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosX++;
							g_bBoxColl = true;
						}
					}
					//Fin collision box � box
					//---------collision box a mur-----------
					for (int e = 0; e < g_iWallCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) - 16 == GfxSpriteGetPositionX(g_pSpriteWall[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) == GfxSpriteGetPositionY(g_pSpriteWall[e]))
						{

							iPosX++;
							g_bBoxColl = true;
						}
					}
					//---------collision box a mur-----------
					if (g_bBoxColl == false)
					{
						GfxSpriteSetPosition(g_pSpriteBox[i], GfxSpriteGetPositionX(g_pSpriteBox[i]) - 16, GfxSpriteGetPositionY(g_pSpriteBox[i]));
					}
				}
			}
			// Fin collision box
		}
		// Fin move � gauche

		//---------------------------------------------------------------------------------------------------------------------------------------------------------

		// Debut move en haut
		if (absX < absY && OldMPosY > mPosY)
		{
			iPosY--;
			// D�but collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosY++;
				}
			}
			// Fin collision mur

			// D�but collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//D�but collision box � box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) -16 == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosY++;
							g_bBoxColl = true;
						}
					}
					//Fin collision box � box
					//---------collision box a mur-----------
					for (int e = 0; e < g_iWallCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) == GfxSpriteGetPositionX(g_pSpriteWall[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) -16 == GfxSpriteGetPositionY(g_pSpriteWall[e]))
						{

							iPosY++;
							g_bBoxColl = true;
						}
					}
					//---------collision box a mur-----------
					if (g_bBoxColl == false)
					{
						GfxSpriteSetPosition(g_pSpriteBox[i], GfxSpriteGetPositionX(g_pSpriteBox[i]), GfxSpriteGetPositionY(g_pSpriteBox[i]) - 16 );
					}
				}
			}
			// Fin collision box
		}
		// Fin move en haut

		//---------------------------------------------------------------------------------------------------------------------------------------------------------

		// Debut move en bas
		if (absX < absY && OldMPosY < mPosY)
		{
			iPosY++;
			// D�but collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosY--;
				}
			}
			// Fin collision mur

			// D�but collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//D�but collision box � box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) + 16 == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosY--;
							g_bBoxColl = true;
						}
					}
					//Fin collision box � box
					//---------collision box a mur-----------
					for (int e = 0; e < g_iWallCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) == GfxSpriteGetPositionX(g_pSpriteWall[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) + 16 == GfxSpriteGetPositionY(g_pSpriteWall[e]))
						{

							iPosY--;
							g_bBoxColl = true;
						}
					}
					//---------collision box a mur-----------
					if (g_bBoxColl == false)
					{
						GfxSpriteSetPosition(g_pSpriteBox[i], GfxSpriteGetPositionX(g_pSpriteBox[i]), GfxSpriteGetPositionY(g_pSpriteBox[i]) + 16);
					}
				}
			}
			// Fin collision box
		}
		// Fin move en bas

		//---------------------------------------------------------------------------------------------------------------------------------------------------------


	}

	//if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosX < mPosX)
	//{
	//	iPosX++;
	//	for (int i = 0; i < g_iWallCount; i++)
	//	{
	//		if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
	//		{
	//			iPosX--;
	//		}
	//	}
	//}
	//
	//if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosX > 0 && iPosX > mPosX)
	//{
	//	iPosX--;
	//	for (int i = 0; i < g_iWallCount; i++)
	//	{
	//		if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
	//		{
	//			iPosX++;
	//		}
	//	}
	//}
	//
	//if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosY < mPosY)
	//{
	//	iPosY++;
	//	for (int i = 0; i < g_iWallCount; i++)
	//	{
	//		if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
	//		{
	//			iPosY--;
	//		}
	//	}
	//}
	//
	//if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosY > 0 && iPosY > mPosY)
	//{
	//	iPosY--;
	//	for (int i = 0; i < g_iWallCount; i++)
	//	{
	//		if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
	//		{
	//			iPosY++;
	//		}
	//	}
	//}

	//-------------------------------- END MOVE ------------------------------

	GfxSpriteSetPosition(g_pSpriteHero, float(iPosX * SCALE * 16), float(iPosY * SCALE * 16));
}

void Render()
{
	GfxClear(EGfxColor_Black);

	for (int i = 0; i < g_iWallCount; i++)
	{
		GfxSpriteRender(g_pSpriteWall[i]);
	}

	for (int i = 0; i < g_iGoalCount; i++)
	{
		GfxSpriteRender(g_pSpriteGoal[i]);
	}

	for (int i = 0; i < g_iBoxCount; i++)
	{
		GfxSpriteRender(g_pSpriteBox[i]);
	}

	GfxSpriteRender(g_pSpriteHero);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render); // Fait le le lien avec les autres parties
}