#include "flib.h"    

// IDEE : SI CLIC PERSO : DEPOSE UN COOKIE

// Les variable qui sont des pointeurs commencent toujours par "p"
// Les globales commencent toujours par un "g_"


const int SCALE = 2;
const int TILE_SIZE = 16;
const int MAX_COOKIE = 10;
int iPosX = 0;
int iPosY = 0;
int g_cptCookie = 0;
int g_iWallCount = 0;

TGfxSprite * g_pSpriteHero;  // Variable globale
TGfxSprite * g_pSpriteEnemy;
TGfxSprite * g_pSpriteWall[600]; // 600 car on aura besoin de 600 cases pour l'image map.tga
TGfxSprite * g_pCookie[MAX_COOKIE];

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

// Obliger de la d�clarer avant de l'utiliser, mais on peut la d�finir plus tard

void Initialize()
{
	g_pTexture = GfxTextureLoad("gfx/tileset.tga"); // On cr�e g_pTexture ici et on l'envoie dans l'appel de fonction

	g_pSpriteHero = CreateTile(g_pTexture, 1, 4, 1, 1); // Initialis�e en dehors du scope pour l'utiliser autre part ( Donc on n'�crit pas "TGfxSPrite *" devant )
	g_pSpriteEnemy = CreateTile(g_pTexture, 8, 7, 2, 2);

	TGfxImage * pMapImage = GfxImageLoad("gfx/map.tga"); // Pas en const car on peut vouloir la delete ( Si on le laisse comme �a, il sera inutile et prendra de la m�moire inutile ! il faut le delete apr�s la boucle avec le destroy
	int iImgSizeX = GfxImageGetSizeX(pMapImage);
	int iImgSizeY = GfxImageGetSizeY(pMapImage);

	for (int y = 0; y < iImgSizeY; ++y)
	{
		for (int x = 0; x < iImgSizeX; ++x)
		{   
			 
			const int iIndex = x + y * iImgSizeX; // Le *15 permet de compter les lignes d�ja parcourue ...
			if (GfxImageGetData(pMapImage)[iIndex] == GfxColor(255,255,255,255)) // SI je veux aller voir le premier �l�ment je dois mettre [0]
			{
				g_pSpriteWall[g_iWallCount] = CreateTile(g_pTexture, 6, 1, x, y);
				g_iWallCount++;
			}
		}
	}

	GfxImageDestroy(pMapImage);

	//	for (int i = 0; i < WALL_HEIGHT; i++)  !!!!!! Attention que �a doit bien s'adapter � la taille du tableau !!!!!!
	//	{
	//		g_pSpriteWall[i] = CreateTile(g_pTexture, 12, 3, 0, i);
	//	}

	GfxSpriteSetPosition(g_pSpriteEnemy, -16 * SCALE, 0 * SCALE); // *4 car on a agrandi la texture X4, c'est pour avoir la m�me �chelle

	// TGfxImage            Les 3 permettent d'afficher des choses.
	// TGfxTexture			Une image est un ensemble de pixel d'un certaine taille.
	// TGfxSprite			32 bits par pixel.
	// Un sprite n'est pas autonome, �a fait r�f�rence � une texture existente, il contiendra les info qui lui diront avec quelle rotation, quelle SCALE, et quelle partie de la texture utiliser ! Le sprite c'est la transformation. une partie de la texture

}

void Update()
{
	const int mPosX = int(GfxGetCurrentMouseX() / (SCALE * TILE_SIZE));
	const int mPosY = int(GfxGetCurrentMouseY() / (SCALE * TILE_SIZE));

	iPosX = int(GfxSpriteGetPositionX(g_pSpriteHero) / (SCALE * 16));  // Le deuxieme int sert � forcer un int ! �a retire les virgules probable
	iPosY = int(GfxSpriteGetPositionY(g_pSpriteHero) / (SCALE * 16));
	int iPosX2 = int(GfxSpriteGetPositionX(g_pSpriteEnemy) / (SCALE * 16));
	int iPosY2 = int(GfxSpriteGetPositionY(g_pSpriteEnemy) / (SCALE * 16));

	const int iTileCountX = GfxGetDisplaySizeX() / (SCALE * 16) - 1;  // valeur de type INT pour ne pas garder ce qui est apr�s la virgule
	const int iTileCountY = GfxGetDisplaySizeY() / (SCALE * 16) - 1;


	// Clic perso ( pose cookie )

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosX == mPosX && iPosY == mPosY && g_cptCookie < MAX_COOKIE)
	{
		g_pCookie[g_cptCookie] = CreateTile(g_pTexture, 13, 3, iPosX, iPosY);
		g_cptCookie++;
	}

	// MOUSE MOVE ( with collision )

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosX < iTileCountX && iPosX < mPosX)
	{
		iPosX++;
		for (int i = 0; i < g_iWallCount; i++)
		{
			if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
			{
				iPosX--;
			}
		}
	}

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosX > 0 && iPosX > mPosX)
	{
		iPosX--;
		for (int i = 0; i < g_iWallCount; i++)
		{
			if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
			{
				iPosX++;
			}
		}
	}

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosY < iTileCountY && iPosY < mPosY)
	{
		iPosY++;
		for (int i = 0; i < g_iWallCount; i++)
		{
			if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
			{
				iPosY--;
			}
		}
	}

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft) && iPosY > 0 && iPosY > mPosY)
	{
		iPosY--;
		for (int i = 0; i < g_iWallCount; i++)
		{
			if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
			{
				iPosY++;
			}
		}
	}

	// KEYBOARD MOVE ( With collision )

		if (GfxInputIsJustPressed(EGfxInputID_KeyArrowRight) && iPosX < iTileCountX)
		{
			iPosX++;
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosX--;
				}
			}
		}

		if (GfxInputIsJustPressed(EGfxInputID_KeyArrowLeft) && iPosX > 0)
		{
			iPosX--;
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosX++;
				}
			}
		}
		
		if (GfxInputIsJustPressed(EGfxInputID_KeyArrowDown) && iPosY < iTileCountY)
		{
			iPosY++;
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosY--;
				}
			}
		}
		
		if (GfxInputIsJustPressed(EGfxInputID_KeyArrowUp) && iPosY > 0)
		{
			iPosY--;
			for (int i = 0; i < g_iWallCount; i++)
			{
				if (iPosX *(SCALE * 16) == GfxSpriteGetPositionX(g_pSpriteWall[i]) && iPosY*(SCALE * 16) == GfxSpriteGetPositionY(g_pSpriteWall[i]))
				{
					iPosY++;
				}
			}
		}
		

	GfxSpriteSetPosition(g_pSpriteHero, float(iPosX * SCALE * 16), float(iPosY * SCALE * 16));

	// DEPLACEMENT JOUEUR 2 CACH� HORS DE L'ECRAN POUR LES VERSION ANDROID ( cach� � gauche )

	if (GfxInputIsJustPressed(EGfxInputID_KeyCharD) && iPosX2 < iTileCountX)
	{
		iPosX2++;
	}
	if (GfxInputIsJustPressed(EGfxInputID_KeyCharQ) && iPosX2 > 0)
	{
		iPosX2--;
	}
	if (GfxInputIsJustPressed(EGfxInputID_KeyCharS) && iPosY2 < iTileCountY)
	{
		iPosY2++;
	}
	if (GfxInputIsJustPressed(EGfxInputID_KeyCharZ) && iPosY2 > 0)
	{
		iPosY2--;
	}

	GfxSpriteSetPosition(g_pSpriteEnemy, float(iPosX2 * SCALE * 16), float(iPosY2 * SCALE * 16));


}

void Render()
{

	for (int i = 0; i < g_iWallCount; i++)
	{
		GfxSpriteRender(g_pSpriteWall[i]);
	}

	for (int i = 0; i < g_cptCookie; i++)
	{
		GfxSpriteRender(g_pCookie[i]);
	}

	GfxSpriteRender(g_pSpriteEnemy);
	GfxSpriteRender(g_pSpriteHero); // A partir de ce scope, on peut acc�der � tout sauf ce qui est dans les boites autres. Si on veut utiliser pSprite, il va falloir le mettre en global
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
