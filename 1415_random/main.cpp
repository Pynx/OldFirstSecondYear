#include "flib.h" 
#define _USE_MATH_DEFINES   // deg to rad de 180 pour avoir PI
#include <math.h>


// Les variable qui sont des pointeurs commencent toujours par "p"
// Les globales commencent toujours par un "g_"


const int SCALE = 2;
const int TILE_SIZE = 16;
const int MAX_COOKIE = 10;
float g_iMove[2]; // Move all sprites
float g_iVelocity[2]; // Accélération !
int g_iPosX = 0;
int g_iPosY = 0;
int g_iWallCount = 0;
int g_iDeathWallCount = 0;

bool IsGameOver = false;

TGfxSprite * g_pSpriteHero;  // Variable globale
TGfxSprite * g_pSpriteWall[660]; // 600 car on aura besoin de 600 cases pour l'image map.tga
TGfxSprite * g_pSpriteDeathWall[660];

TGfxTexture * g_pTexture;

TGfxImage * g_pBackground;
TGfxTexture * g_pTextureTest;
TGfxSprite * g_pSpritesBg;

TGfxSprite * CreateTile(const TGfxTexture * g_pTexture, const int g_iPosX, const int g_iPosY, const int iTileX, const int iTileY)
{

	TGfxSprite * pSprite = GfxSpriteCreate(g_pTexture);
	GfxSpriteSetScale(pSprite, float(SCALE), float(SCALE));
	GfxSpriteSetFilteringEnabled(pSprite, false);
	GfxSpriteSetCutout(pSprite, g_iPosX * TILE_SIZE, g_iPosY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	GfxSpriteSetPosition(pSprite, float(SCALE) * TILE_SIZE * iTileX, float(SCALE) * TILE_SIZE * iTileY);
	GfxSpriteSetPivot(pSprite, TILE_SIZE / 2, TILE_SIZE / 2); // Change le point de collision de tout les tile créés comme ça

	return pSprite;  // toujours mettre le return à la fin car ça sort de la fonction.
}

// Obliger de la déclarer avant de l'utiliser, mais on peut la définir plus tard

void GameOver()
{
	IsGameOver = true;
	GfxSpriteSetAngle(g_pSpriteHero, -(M_PI / 2));
}

void Initialize()
{
	g_pBackground = GfxImageLoad("gfx/bg3.tga");
	g_pTextureTest = GfxTextureCreate(g_pBackground);
	g_pSpritesBg = GfxSpriteCreate(g_pTextureTest);
	g_pTexture = GfxTextureLoad("gfx/tileset.tga"); // On crée g_pTexture ici et on l'envoie dans l'appel de fonction

	g_pSpriteHero = CreateTile(g_pTexture, 7, 7, 7, 5); // Initialisée en dehors du scope pour l'utiliser autre part ( Donc on n'écrit pas "TGfxSPrite *" devant ) ( debug mode = 2, 1 | normal mode = 0, 0 )

	TGfxImage * pMapImage = GfxImageLoad("gfx/map.tga"); // Pas en const car on peut vouloir la delete ( Si on le laisse comme ça, il sera inutile et prendra de la mémoire inutile ! il faut le delete après la boucle avec le destroy
	int iImgSizeX = GfxImageGetSizeX(pMapImage);
	int iImgSizeY = GfxImageGetSizeY(pMapImage);

	for (int y = 0; y < iImgSizeY; ++y)
	{
		for (int x = 0; x < iImgSizeX; ++x)
		{

			const int iIndex = x + y * iImgSizeX;
			if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 255, 255, 255)) // SI je veux aller voir le premier élément je dois mettre [0]
			{
				g_pSpriteWall[g_iWallCount] = CreateTile(g_pTexture, 6, 1, x, y); // 6 et 1 au lieu de 1 et 1 pour mur ( 1, 1 = debug mode test )
				g_iWallCount++;
			}
			if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255, 0, 0, 255)) // SI je veux aller voir le premier élément je dois mettre [0]
			{
				g_pSpriteDeathWall[g_iDeathWallCount] = CreateTile(g_pTexture, 7, 1, x, y);
				g_iDeathWallCount++;
			}
		}
	}

	GfxImageDestroy(pMapImage);

	//	for (int i = 0; i < WALL_HEIGHT; i++)  !!!!!! Attention que ça doit bien s'adapter à la taille du tableau !!!!!!
	//	{
	//		g_pSpriteWall[i] = CreateTile(g_pTexture, 12, 3, 0, i);
	//	}
	// TGfxImage            Les 3 permettent d'afficher des choses.
	// TGfxTexture			Une image est un ensemble de pixel d'un certaine taille.
	// TGfxSprite			32 bits par pixel.
	// Un sprite n'est pas autonome, ça fait référence à une texture existente, il contiendra les info qui lui diront avec quelle rotation, quelle SCALE, et quelle partie de la texture utiliser ! Le sprite c'est la transformation. une partie de la texture

}

void Update()
{
	const int iMPosX = int(GfxGetCurrentMouseX());
	const int iMPosY = int(GfxGetCurrentMouseY());  // Remplacer iMPosX par iiMPosX

	bool bCollide = true;    

	g_iPosX = int(GfxSpriteGetPositionX(g_pSpriteHero));  // Le deuxieme int sert à forcer un int ! ça retire les virgules probable
	g_iPosY = int(GfxSpriteGetPositionY(g_pSpriteHero));

	const int iTileCountX = GfxGetDisplaySizeX() - 1;  // valeur de type INT pour ne pas garder ce qui est après la virgule
	const int iTileCountY = GfxGetDisplaySizeY() - 1;


	// MOUSE MOVE ( with collision )




	if (IsGameOver == false)
	{
		//-------------------------------------------------------------- Déplacement droite ---------------------------------------------------//
		if (GfxInputIsPressed(EGfxInputID_MouseLeft) && g_iPosX + 16 < iMPosX)
		{
			GfxSpriteSetScale(g_pSpriteHero, float(SCALE), float(SCALE));																	   //
			bCollide = true;																												   //
			for (int i = 0; i < g_iWallCount; i++)																							   //
			{																																   //
				if (GfxSpriteGetPositionY(g_pSpriteWall[i]) - 31 < g_iPosY && g_iPosY < GfxSpriteGetPositionY(g_pSpriteWall[i]) + 32)		   //
				{																															   //
					if (GfxSpriteGetPositionX(g_pSpriteWall[i]) - 33 < g_iPosX && g_iPosX < GfxSpriteGetPositionX(g_pSpriteWall[i]) + 32)	   //
					{																														   //
						bCollide = false;																									   //
					}																														   //
				}
			}
			for (int i = 0; i < g_iDeathWallCount; i++)																							   //
			{																																   //
				if (GfxSpriteGetPositionY(g_pSpriteDeathWall[i]) - 31 < g_iPosY && g_iPosY < GfxSpriteGetPositionY(g_pSpriteDeathWall[i]) + 32)		   //
				{																															   //
					if (GfxSpriteGetPositionX(g_pSpriteDeathWall[i]) - 33 < g_iPosX && g_iPosX < GfxSpriteGetPositionX(g_pSpriteDeathWall[i]) + 32)	   //
					{																														   //
						GameOver();																							   //
					}																														   //
				}
			}
			//
			if (bCollide == true)																											   //
			{																																   //

				g_iMove[0] -= 2;																											   //

				//g_iPosX += 2;																												   //
			}																																   //
		}																																	   //
		//-------------------------------------------------------------- Fin déplacement droite -----------------------------------------------//

		//-------------------------------------------------------------- Déplacement Gauche ----------------------------------

		if (GfxInputIsPressed(EGfxInputID_MouseLeft) && g_iPosX - 16 > iMPosX)
		{
			GfxSpriteSetScale(g_pSpriteHero, float(-SCALE), float(SCALE));
			bCollide = true;
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (GfxSpriteGetPositionY(g_pSpriteWall[i]) - 31 < g_iPosY && g_iPosY < GfxSpriteGetPositionY(g_pSpriteWall[i]) + 32)
				{
					if (GfxSpriteGetPositionX(g_pSpriteWall[i]) - 32 < g_iPosX && g_iPosX < GfxSpriteGetPositionX(g_pSpriteWall[i]) + 33)
					{
						bCollide = false;
					}
				}
			}
			for (int i = 0; i < g_iDeathWallCount; i++)
			{
				if (GfxSpriteGetPositionY(g_pSpriteDeathWall[i]) - 31 < g_iPosY && g_iPosY < GfxSpriteGetPositionY(g_pSpriteDeathWall[i]) + 32)
				{
					if (GfxSpriteGetPositionX(g_pSpriteDeathWall[i]) - 32 < g_iPosX && g_iPosX < GfxSpriteGetPositionX(g_pSpriteDeathWall[i]) + 33)
					{
						GameOver();
					}
				}
			}

			if (bCollide == true)
			{
				g_iMove[0] += 2;
				//g_iPosX-= 2;
			}
		}
		//-------------------------------------------------------------- Fin déplacement gauche ----------------------------------

		//--------------------------------------------------------------- Collision Sol ---------------------------
		bCollide = true;
		for (int i = 0; i < g_iWallCount; i++)
		{
			if (GfxSpriteGetPositionX(g_pSpriteWall[i]) - 31 < g_iPosX && g_iPosX < GfxSpriteGetPositionX(g_pSpriteWall[i]) + 31)
			{
				if (g_iPosY > GfxSpriteGetPositionY(g_pSpriteWall[i]) - 33 && g_iPosY < GfxSpriteGetPositionY(g_pSpriteWall[i]) + 32)
				{
					bCollide = false;
					if (g_iVelocity[1] < 0)
					{
						g_iPosY = GfxSpriteGetPositionY(g_pSpriteWall[i]) + 32;
					}
					if (g_iVelocity[1] > 0)
					{
						g_iPosY = GfxSpriteGetPositionY(g_pSpriteWall[i]) - 31;
					}
					g_iVelocity[1] = 0;
				}
			}
		}
		// DEBUT GAME OVER 
		for (int i = 0; i < g_iDeathWallCount; i++)
		{
			if (GfxSpriteGetPositionX(g_pSpriteDeathWall[i]) - 31 < g_iPosX && g_iPosX < GfxSpriteGetPositionX(g_pSpriteDeathWall[i]) + 31)
			{
				if (g_iPosY > GfxSpriteGetPositionY(g_pSpriteDeathWall[i]) - 33 && g_iPosY < GfxSpriteGetPositionY(g_pSpriteDeathWall[i]) + 32)
				{
					GameOver();
				}
			}
		}
		// FIN GAME OVER


		if (bCollide == true)
		{
			g_iVelocity[1] += 0.4f; // f à la fin quand c'est un float. ça corrige l'erreur appellé "truncation"
		}

		if (GfxInputIsJustPressed(EGfxInputID_KeySpace) && g_iVelocity[1] == 0 || GfxInputIsJustPressed(EGfxInputID_KeySpace) && GfxInputIsPressed(EGfxInputID_KeyControl))
		{
			g_iVelocity[1] = -7;
		}
		if (iMPosX > g_iPosX - 16
			&& iMPosX < g_iPosX + 16
			&& g_iVelocity[1] == 0
			&& GfxInputIsJustPressed(EGfxInputID_MouseLeft))
		{
			g_iVelocity[1] = -7;
		}
	}
	//------------------------------------------------------------- Fin Collision Sol --------------------------------

	//-------------------------------------------------------------- Actualisation déplacement ----------------------------------
	g_iMove[1] = g_iMove[1] - (g_iVelocity[1]);
	for (int i = 0; i < g_iWallCount; i++)
	{
		GfxSpriteSetPosition(g_pSpriteWall[i], float (GfxSpriteGetPositionX(g_pSpriteWall[i])) + float(g_iMove[0]), float (GfxSpriteGetPositionY(g_pSpriteWall[i])));
	}
	for (int i = 0; i < g_iDeathWallCount; i++)
	{
		GfxSpriteSetPosition(g_pSpriteDeathWall[i], float(GfxSpriteGetPositionX(g_pSpriteDeathWall[i])) + float(g_iMove[0]), float(GfxSpriteGetPositionY(g_pSpriteDeathWall[i])));
	}
	if (IsGameOver == false)
	{
		GfxSpriteSetPosition(g_pSpritesBg, float(GfxSpriteGetPositionX(g_pSpritesBg)) + (float(g_iMove[0]/2)), float(GfxSpriteGetPositionY(g_pSpritesBg)));
		GfxSpriteSetPosition(g_pSpriteHero, float(g_iPosX), float(g_iPosY) - float(g_iMove[1]));
	}
	g_iMove[0] = 0;
	g_iMove[1] = 0;
	//-------------------------------------------------------------- Fin Actualisation déplacement ----------------------------------
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_pSpritesBg);

	for (int i = 0; i < g_iWallCount; i++)
	{
		GfxSpriteRender(g_pSpriteWall[i]);
	}
	for (int i = 0; i < g_iDeathWallCount; i++)
	{
		GfxSpriteRender(g_pSpriteDeathWall[i]);
	}

	GfxSpriteRender(g_pSpriteHero); // A partir de ce scope, on peut accéder à tout sauf ce qui est dans les boites autres. Si on veut utiliser pSprite, il va falloir le mettre en global
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
