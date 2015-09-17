#include "flib.h"

const int size = 5;
int SeqCount = 0;
int Minutes = 0;
bool check = false;
bool test = true;
float dSizeX;   // Used for Display size X


int Sequence[size];
TGfxSprite * g_pButton[size];

TGfxSprite * CreateSprite(const TGfxTexture * pTexture)
{
	TGfxSprite * pSprite;
	pSprite = GfxSpriteCreate(pTexture);
	GfxSpriteSetScale(pSprite, 30.0f, 30.0f);
	GfxSpriteSetPosition(pSprite, 100.0f, 100.0f);
	GfxSpriteSetColor(pSprite, EGfxColor_Red);
	return pSprite;
}

void Initialize()
{
	dSizeX = float(GfxGetDisplaySizeX());

	TGfxTexture * pWhitePixel = GfxTextureLoad("gfx/txt.tga");

	for (int i = 0; i < size; i++)
	{
		g_pButton[i] = CreateSprite(pWhitePixel);
	}

}

void Update()
{


	//-------------------------------------------------------------------------------------------------------------------------------------------POSITION BUTTONS
	const float PercMouseX = float(GfxGetCurrentMouseX()) / float(GfxGetDisplaySizeX()) * float(100.00);
	const float PercMouseY = float(GfxGetCurrentMouseY()) / float(GfxGetDisplaySizeY()) * float(100.00);
	const float PlaceButton = dSizeX / (size + 2);


	for (int i = 0; i < size; i++)
	{
		GfxSpriteSetPosition(g_pButton[i], float(PlaceButton * (i + 1) + GfxSpriteGetScaleX(g_pButton[i]) / 2) -15, float(GfxGetDisplaySizeY() / 2 - 15));
	}
	//_____________________________________________________________________________________________________________________________________________________________
	if (test)
	{
		for (int i = 0; i < size; i++)
		{
			Sequence[i] = GfxMathGetRandomInteger(1, size);

			for (int e = 0; e < size; e++)
			{
				if (Sequence[i] == Sequence[i - (e + 1)])
				{
					i--;
					e = size;
				}
			}
		}
		test = false;
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------HIT BUTTONS

	for (int i = 0; i < size; i++)
	{
		if (GfxInputIsJustPressed(EGfxInputID_MouseLeft)
			&& GfxSpriteGetPositionX(g_pButton[i]) <= GfxGetCurrentMouseX()
			&& GfxGetCurrentMouseX() < GfxSpriteGetPositionX(g_pButton[i]) + 30
			&& GfxSpriteGetPositionY(g_pButton[i]) <= GfxGetCurrentMouseY()
			&& GfxGetCurrentMouseY() < GfxSpriteGetPositionY(g_pButton[i]) + 30)
		{
			if (Sequence[SeqCount] == i + 1)
			{
				SeqCount++;
				GfxSpriteSetColor(g_pButton[i], EGfxColor_Green);
			}
			else
			{
				SeqCount = 0;
				for (int e = 0; e < size; e++)
				{
					GfxSpriteSetColor(g_pButton[e], EGfxColor_Red);
				}
			}
		}
		if (SeqCount >= size)
		{
			GfxSpriteSetColor(g_pButton[i], EGfxColor_Green);
			test = true;
		}
	}

}

void Render()
{
	GfxClear(EGfxColor_Black);
	for (int i = 0; i < size; i++)
	{
		GfxSpriteRender(g_pButton[i]);
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}

// Aléatoire en faisant en sorte de ne pas avoir un nombre qui revient deux fois
//   Je veux donc des permutations
//
//
//  2 3 1 4
//  1 4 3 2
//  
//  1 2 3 4
//
//   const int iItemCount = 5;
//   int pItems[iItemCount];
//
//   for (int i = 0; i < iItemCount; i++)
//   {
//       pItems[i] = i;																Mettre valeur dans tableau
//   }
//
//					
//																								Shuffle ?
//
//
//   for (int i = 0; i < 100; i++)
//   {
//
//		const int iIndexA = GfxMathGetRandomInteger(0, iItemCount -1);
//		const int iIndexB = GfxMathGetRandomInteger(0, iItemCount -1);                              Faiblesse --> on ne sait pas quand c'est assez bien mélangé.
//																									aller voir wikipédia --> Fisher gates random algo
//		const int iTemp = pItems[iIndexA];
//		pItems[iIndexA] = pItems[iIndexB];
//		pItems[iIndexB] = iTemp;  
//
//   }
//
//   for (int i = 0; i < iItemCount; i++)
//   {
//       GfxDbgPrintf("%d ", pItems[i]);
//   }
//
//
//
//
//  --> fisher algo <--
//
//
//
//   for (int i = iItemCount -1; i > 0; i--)
//   {
//		const int j = GfxMathGetRandomInteger (0, i);
//
//      const int iTemp = pItems[i];
//		pItems[i] = pItems[j]; 
//		pItems[j] = iTemp; 
//   }
//