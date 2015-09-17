#include "flib.h"
#include "flib_vec3.h"
#include "ray.h"
#include <math.h>
#include "camera.h"
#include "sphere.h"
#include "color.h"
#include "global.h"
#include "floor.h"


/*


On va utiliser :

reinterpret_cast<unsigned char *>(&iBaseColor)[0]

ça va transformer iBaseColor qui est un unsigned int ( donc 32 bits ), on prend son adresse et on la réinterprete. Vu qu'un unsigned char c'est 8bits, on va prendre la premiere couleur.
pour modifier la première couleur on va prendre [0], pour la deuxieme, [1] -->



unsigned int iBaseColor = EGfxColor_Green;

unsigned char r = reinterpret_cast<unsigned char *>(&iBaseColor)[0];
unsigned char g = reinterpret_cast<unsigned char *>(&iBaseColor)[1];
unsigned char b = reinterpret_cast<unsigned char *>(&iBaseColor)[2];
unsigned char a = reinterpret_cast<unsigned char *>(&iBaseColor)[3];

unsigned char * pRGBA = reinterpret_cast<unsigned char *>(&iBaseColor);




pRGBA[0] = 0xFF; // = 255

unsigned int iColor = GfxColor(r * fLight, g * fLight, b * fLight, 255);


Pour afficher dans le debug un tableau, on rajoute une virgule après et on mets en dur le chiffre qui représente le nombre de cases du tableau







unsigned char iRed = (iBaseColor >> 24) & 0x000000FF;     --> iBaseColor est reculé de 24 et on fait un AND avec une valeur
*/

TGfxImage * g_pImage = nullptr;
TGfxTexture * g_pTexture = nullptr;
TGfxSprite * g_pSprite = nullptr;

unsigned int * g_pImageData;

//int g_pPos = 0;
//int g_iTimeCounter = 0;

float g_fx = 0;
float g_fy = 0;
float g_fz = 2;

void Initialize()
{
	g_pImage = GfxImageCreate(GfxGetDisplaySizeX() / SCALE_FACTOR, GfxGetDisplaySizeY() / SCALE_FACTOR);
}

void Update()
{
	//Effacer le sprite et texture de la mémoire
	if (g_pSprite != nullptr)
	{
		GfxSpriteDestroy(g_pSprite);
		g_pSprite = nullptr; // Libert l'adresse mémoire du sprite
	}

	if (g_pTexture != nullptr)
	{
		GfxTextureDestroy(g_pTexture);
		g_pTexture = nullptr;
	}

	TCamera tCamera;
	TSphere tSphere[MAX_SPHERES];
	TPlan tPlan;
	tPlan.m_tPosition = TGfxVec3(0, -5, 0);
	tSphere[0].m_tPosition = TGfxVec3(-1, 0, 8);
	tSphere[0].m_tColor = TGfxVec3(255, 0, 0);
	tSphere[1].m_tPosition = TGfxVec3(-3, 0, 8);
	tSphere[1].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[2].m_tPosition = TGfxVec3(1, 0, 8);
	tSphere[2].m_tColor = TGfxVec3(0, 0, 255);
	tSphere[3].m_tPosition = TGfxVec3(3, 0, 8);
	tSphere[3].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[4].m_tPosition = TGfxVec3(0, 1, 8);
	tSphere[4].m_tColor = TGfxVec3(255, 0, 0);
	tSphere[5].m_tPosition = TGfxVec3(0, -1, 8);
	tSphere[5].m_tColor = TGfxVec3(0, 0, 255);
	tSphere[6].m_tPosition = TGfxVec3(0, -3, 8);
	tSphere[6].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[7].m_tPosition = TGfxVec3(0, 3, 8);
	tSphere[7].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[8].m_tPosition = TGfxVec3(-2, -2, 8);
	tSphere[8].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[9].m_tPosition = TGfxVec3(-2, 2, 8);
	tSphere[9].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[10].m_tPosition = TGfxVec3(2, 2, 8);
	tSphere[10].m_tColor = TGfxVec3(255, 255, 0);
	tSphere[11].m_tPosition = TGfxVec3(2, -2, 8);
	tSphere[11].m_tColor = TGfxVec3(255, 255, 0);
	tCamera.m_tPosition = TGfxVec3(g_fx, g_fy, g_fz);
	tCamera.m_fFOV = 120.f;
	tCamera.Render(g_pImage, tSphere, tPlan);

	g_pTexture = GfxTextureCreate(g_pImage);
	g_pSprite = GfxSpriteCreate(g_pTexture);
	GfxSpriteSetScale(g_pSprite, float(SCALE_FACTOR), float(SCALE_FACTOR));
	GfxSpriteSetFilteringEnabled(g_pSprite, false);



	if (GfxInputIsPressed(EGfxInputID_KeyArrowUp))
	{
		g_fy += 0.1f;
	}

	if (GfxInputIsPressed(EGfxInputID_KeyArrowDown))
	{
		g_fy -= 0.1f;
	}

	if (GfxInputIsPressed(EGfxInputID_KeyArrowRight))
	{
		g_fx += 0.1f;
	}

	if (GfxInputIsPressed(EGfxInputID_KeyArrowLeft))
	{
		g_fx -= 0.1f;
	}

	if (GfxInputIsPressed(EGfxInputID_KeyCharS))
	{
		g_fz -= 0.1f;
	}

	if (GfxInputIsPressed(EGfxInputID_KeyCharZ))
	{
		g_fz += 0.1f;
	}
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_pSprite);
}

void GfxMain(int, char *[])
{
	GfxDefaultResolution(MAX_SIZEX, MAX_SIZEY); // Changer résolution de la fenêtre sur pc
	GfxCallbacks(Initialize, Update, Render);
}
























// ------------------------------------ OLD -------------------------------




//#include "flib.h"
//#include "flib_vec3.h"
//#include "camera.h"
//#include "ray.h"
//#include "sphere.h"
//#include <math.h>
//
//TGfxImage * g_pImage;
//TGfxTexture * g_pTexture;
//TGfxSprite * g_pSprite;
//unsigned int * g_pData;
//int g_iPos;
//int g_iRes = 10;
//
//void Initialize()
//{
//	g_pImage = GfxImageCreate(int(GfxGetDisplaySizeX() / g_iRes), int(GfxGetDisplaySizeY() / g_iRes));
//	g_pData = GfxImageGetData(g_pImage);
//	for (int i = 0; i < ((GfxGetDisplaySizeX()/g_iRes)*(GfxGetDisplaySizeY()/g_iRes)); i++)
//	{
//		g_pData[i] = EGfxColor_Black;
//	}	
//	g_pData[0] = EGfxColor_White;
//	g_iPos = 0;
//
//
//}
//
//void Update()
//{
//	if (g_pSprite != nullptr)
//	{
//		GfxSpriteDestroy(g_pSprite);
//	}
//	if (g_pTexture != nullptr)
//	{
//		GfxTextureDestroy(g_pTexture);
//	}
//	int sizeY = GfxGetDisplaySizeY()/g_iRes;
//	int sizeX = GfxGetDisplaySizeX()/g_iRes;
//	for (int i = 0; i < sizeY; i++)
//	{
//		for (int e = 0; e < sizeX; e++)
//		{
//			g_pData[i * sizeX + e] = GfxColor(e*(255.f / sizeX), i*(255.f / sizeY), 0, 255.f);
//		}
//	}
//
//	g_pTexture = GfxTextureCreate(g_pImage);
//	g_pSprite = GfxSpriteCreate(g_pTexture);
//	GfxSpriteSetScale(g_pSprite, g_iRes, g_iRes);
//	GfxSpriteSetFilteringEnabled(g_pSprite, false);
//
//	//GfxSpriteDestroy(g_pSprite);
//	//GfxTextureDestroy(g_pTexture);
//	//if (GfxInputIsPressed(EGfxInputID_KeyArrowDown))
//	//{
//	//	g_pData[g_iPos] = EGfxColor_Black;
//	//	g_iPos += GfxGetDisplaySizeX();
//	//	g_pData[g_iPos] = EGfxColor_White;
//	//}
//	//if (GfxInputIsPressed(EGfxInputID_KeyArrowUp))
//	//{
//	//	g_pData[g_iPos] = EGfxColor_Black;
//	//	g_iPos -= GfxGetDisplaySizeX();
//	//	g_pData[g_iPos] = EGfxColor_White;
//	//}
//	//if (GfxInputIsPressed(EGfxInputID_KeyArrowLeft))
//	//{
//	//	g_pData[g_iPos] = EGfxColor_Black;
//	//	g_iPos -= 1;
//	//	g_pData[g_iPos] = EGfxColor_White;
//	//}
//	//if (GfxInputIsPressed(EGfxInputID_KeyArrowRight))
//	//{
//	//	g_pData[g_iPos] = EGfxColor_Black;
//	//	g_iPos += 1;
//	//	g_pData[g_iPos] = EGfxColor_White;
//	//}
//	//g_pTexture = GfxTextureCreate(g_pImage);
//	//g_pSprite = GfxSpriteCreate(g_pTexture);
//}
//
//void Render()
//{
//	GfxClear(EGfxColor_Black);
//	GfxSpriteRender(g_pSprite);
//}
//
//void GfxMain(int, char *[])
//{
//	GfxCallbacks(Initialize, Update, Render);
//}


// ----------------------------------------------      Partie 4      ---------------------------------------------------------------------------
//
//#include "flib.h"
//
//struct TLargeData
//{
//	int value[5000];
//};
//
//struct TFoo
//{
//public:
//	void Hello();
//	void SetA(const TLargeData & value);
//	const TLargeData & GetA() const;
//private: // Empêche de les modifier extérieurement
//	TLargeData a;
//	int b;
//};
//
//void TFoo::SetA(const int value)
//{
//	a = value;
//}
//
//const TLargeData & TFoo::GetA() const
//{
//	return a;
//}
//
//void TFoo::Hello()
//{
//	GfxDbgPrintf("Hello\n");
//}
//
//TFoo GetValue(const TFoo & tFoo) // Permet de modifier les variables
//{
//	GfxDbgPrintf("%d, %d\n", tFoo.a, tFoo.b);
//}
//
//void GfxMain(int, char *[])
//{
//	TFoo tFoo;
//	tFoo.a = 123;
//	tFoo.b = 456;
//	GetValue(tFoo);
//
//	tFoo.Hello();
//}
//
// ----------------------------------------------      Partie 3      ---------------------------------------------------------------------------


//#include "flib.h"
//
//struct TFoo
//
//{
//	int a;
//	int b;
//};
//
//TFoo GetValue(TFoo & tFoo) // Permet de modifier les variables
//{
//	tFoo.a = 123;
//	tFoo.b = 456;
//}
//
//void GfxMain(int, char *[])
//{
//	TFoo tFoo;
//
//	GetValue(tFoo);
//}

// ----------------------------------------------      Partie 2      ---------------------------------------------------------------------------




//struct TFoo
//
//{
//	int a;
//	int b;
//};
//
//TFoo GetValue(int & a, int & b) // Permet de modifier les variables
//{
//	a = 123;
//	b = 456;
//}
//
//void GfxMain(int, char *[])
//{
//	int a;
//	int b;
//
//	GetValue(a, b);
//
//
//
//}
//

// ----------------------------------------------      Partie 1      ---------------------------------------------------------------------------




// Opérateur ternaire : Prend trois paramètres ! Le - par exemple est un binaire, le * un 'sais plus cmt s'apelle' et le ternaire lui en a trois.

//for (int i = 0; i < 10; i++)
//{
//	if (i % 2)
//	{
//		GfxDbgPrintf("%i est impair\n", i);
//	}
//	else
//	{
//		GfxDbgPrintf("%i est pair\n", i);
//	}
//	GfxDbgPrintf("%d est %s\n", i, (i % 2) ? "impair" : "pair"); // Fais pareil que le commentaire du dessus
//
//}
//
//
//int i = 123;
//int * p = &i;
//
//i = 456;
//*p = 456;
//
//	struct TFoo
//{
//	int a;
//	int b;
//};
//
//	TFoo foo;
//	foo.a = 123;
//	foo.b = 456;
//
//	TFoo foo2;
//	foo2.a = 789;
//	foo2.b = 987;
//
//
//	TFoo * p;
//	p = &foo;
//	p = &foo2;
//
//	(*p).a = 123;
//	(*p).b = 456;
//
//	p->a = 123;
//	p->b = 456;
//
//	TFoo & r = foo;
//	r.a = 123;
//	r.b = 123;

