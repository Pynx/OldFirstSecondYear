// TO DO :
// 1 : Faire le sokoban
// 2 : Ajouter des sprite sympa
// 3 : Créer un éditeur


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

	TGfxSprite * pSprite = GfxSpriteCreate(g_pTexture);    // On crée pSprite et on y met la la variable de la texture chargée 
	GfxSpriteSetScale(pSprite, float(SCALE), float(SCALE));    // On choisis la taille du sprite appellé pSprite 
	GfxSpriteSetFilteringEnabled(pSprite, false);             // On désactive le filtering ( à laisse )
	GfxSpriteSetCutout(pSprite, iPosX * TILE_SIZE, iPosY * TILE_SIZE, TILE_SIZE, TILE_SIZE);    // On choisis ce qui sera affiché sur un sprite, ici on choisis la taille et la position du sprite dans la texture
	GfxSpriteSetPosition(pSprite, float(SCALE) * TILE_SIZE * iTileX, float(SCALE) * TILE_SIZE * iTileY);     // On choisis où l'afficher 

	return pSprite;  // toujours mettre le return à la fin car ça sort de la fonction.
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

void ReadLevel(TGfxFile * pFile) // à partir d'un pFile, cette fonction lis le niveau et fais appel 
{ // La variable pFile doit contenir un GfxFileOpenRead du fichier texte contenant les niveaux
	bool bLevelLineRead = false;  // Elle va servir à passer les commentaires du début ...


	for (;;)
	{

		const unsigned char cCar = GfxFileReadChar(pFile); // cCar sera une lettre du fichier, et à chaque fois on lira la suivante jusqu'a avoir finit de lire tout le fichier
		if (cCar == ';') // Veut dire que c'est un commentaire. On va donc passer à la ligne suivante en ignorant les charactères jusqu'a 
		{
			while (GfxFileReadChar(pFile) != '\n'); // Ceci va lire les caractères un par un jusqu'a trouver un retour à la ligne ! ( On mets \n pour le retour à la ligne )
			if (bLevelLineRead) // Si bLevelLineRead est true ( ce qui veut dire qu'on a fini de lire un niveau !! ) On sortira de la boucle infinie grace à ça !
			{
				break; // Sort du for ! Sinon boucle infinie
			}
		}
		else if (cCar == '\n')
		{
		}
		else
		{
			bLevelLineRead = true;  // En true dès qu'on commence un niveau :)

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

	if (g_bNextLevel == true) // Si NextLevel = vrai, on supprime l'ancien lvl et on crée le neuf !
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


		ReadLevel(pFile);								   // lance la fonction créée
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


		// Début move à droite
		if (absX > absY && OldMPosX < mPosX)
		{
			iPosX++;
			// Début collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosX--;
				}
			}
			// Fin collision mur

			// Début collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//Début collision box à box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) +16 == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosX--;
							g_bBoxColl = true;
						}
					}
					//Fin collision box à box
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
		// Fin move à droite

		//---------------------------------------------------------------------------------------------------------------------------------------------------------

		
		// Debut move à gauche
		if (absX > absY && OldMPosX > mPosX)
		{
			iPosX--;
			// Début collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosX++;
				}
			}
			// Fin collision mur

			// Début collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//Début collision box à box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) - 16 == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosX++;
							g_bBoxColl = true;
						}
					}
					//Fin collision box à box
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
		// Fin move à gauche

		//---------------------------------------------------------------------------------------------------------------------------------------------------------

		// Debut move en haut
		if (absX < absY && OldMPosY > mPosY)
		{
			iPosY--;
			// Début collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosY++;
				}
			}
			// Fin collision mur

			// Début collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//Début collision box à box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) -16 == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosY++;
							g_bBoxColl = true;
						}
					}
					//Fin collision box à box
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
			// Début collision mur
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosY--;
				}
			}
			// Fin collision mur

			// Début collision box
			g_bBoxColl = false;
			for (int i = 0; i < g_iBoxCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteBox[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteBox[i]))
				{
					//Début collision box à box
					for (int e = 0; e < g_iBoxCount; e++)
					{
						if (GfxSpriteGetPositionX(g_pSpriteBox[i]) == GfxSpriteGetPositionX(g_pSpriteBox[e]) && GfxSpriteGetPositionY(g_pSpriteBox[i]) + 16 == GfxSpriteGetPositionY(g_pSpriteBox[e]))
						{

							iPosY--;
							g_bBoxColl = true;
						}
					}
					//Fin collision box à box
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