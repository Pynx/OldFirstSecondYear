#include "flib.h"
#include "redirect.h"
#include "keyboard.h"
#include "mainmenu.h"
#include "global.h"
#include <math.h>

void Keyboard::Create()
{
	g_tKeyboardBackgroundTexture = GfxTextureLoad("gfx/keyboard.tga");
	g_tKeyboardBackgroundSprite = GfxSpriteCreate(g_tKeyboardBackgroundTexture);
	tNameSprite = GfxTextSpriteCreate();
	GfxSpriteSetScale(tNameSprite, 2, 2);
	GfxSpriteSetFilteringEnabled(tNameSprite, false);

	tExplainSprite = GfxTextSpriteCreate();
	GfxSpriteSetFilteringEnabled(tExplainSprite, false);
	GfxSpriteSetPosition(tExplainSprite, 64, 10);

	GfxSpriteSetFilteringEnabled(g_tKeyboardBackgroundSprite, false);
	GfxSpriteSetPosition(g_tKeyboardBackgroundSprite, 0, 0);
	GfxSpriteSetPosition(tNameSprite, 64, 48);

	if (tPosition.m_bLoadMode == false)
	{
		//New game
		GfxTextSpritePrintf(tExplainSprite, "Choose your nickname. Be sure to remember it !");
	}
	else
	{
		//Loading
		GfxTextSpritePrintf(tExplainSprite, "Load your game with a nickname already created !");
	}
}

void Keyboard::Delete()
{
	GfxSpriteDestroy(g_tKeyboardBackgroundSprite);
	GfxSpriteDestroy(tNameSprite);
	GfxSpriteDestroy(tExplainSprite);
	GfxTextureDestroy(g_tKeyboardBackgroundTexture);
}

void Keyboard::Input()
{
	int g_iMouseX = GfxGetCurrentMouseX();
	int g_iMouseY = GfxGetCurrentMouseY();

	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		if ((g_iMouseX > 48) & (g_iMouseX < 96) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// a
			if (cpt < 10)
			{
				name[cpt] = 'a';
				cpt++;
			}
		}
		if ((g_iMouseX > 96) & (g_iMouseX < 144) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// b
			if (cpt < 10)
			{
				name[cpt] = 'b';
				cpt++;
			}
		}
		if ((g_iMouseX > 144) & (g_iMouseX < 192) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// c
			if (cpt < 10)
			{
				name[cpt] = 'c';
				cpt++;
			}
		}
		if ((g_iMouseX > 192) & (g_iMouseX < 240) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// d
			if (cpt < 10)
			{
				name[cpt] = 'd';
				cpt++;
			}
		}
		if ((g_iMouseX > 240) & (g_iMouseX < 288) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// e
			if (cpt < 10)
			{
				name[cpt] = 'e';
				cpt++;
			}
		}
		if ((g_iMouseX > 288) & (g_iMouseX < 336) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// f
			if (cpt < 10)
			{
				name[cpt] = 'f';
				cpt++;
			}
		}
		if ((g_iMouseX > 336) & (g_iMouseX < 384) & (g_iMouseY > 112) & (g_iMouseY < 160))
		{
			// g
			if (cpt < 10)
			{
				name[cpt] = 'g';
				cpt++;
			}
		}
		if ((g_iMouseX > 48) & (g_iMouseX < 96) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// h
			if (cpt < 10)
			{
				name[cpt] = 'h';
				cpt++;
			}
		}
		if ((g_iMouseX > 96) & (g_iMouseX < 144) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// i
			if (cpt < 10)
			{
				name[cpt] = 'i';
				cpt++;
			}
		}
		if ((g_iMouseX > 144) & (g_iMouseX < 192) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// j
			if (cpt < 10)
			{
				name[cpt] = 'j';
				cpt++;
			}
		}
		if ((g_iMouseX > 192) & (g_iMouseX < 240) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// k
			if (cpt < 10)
			{
				name[cpt] = 'k';
				cpt++;
			}
		}
		if ((g_iMouseX > 240) & (g_iMouseX < 288) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// l
			if (cpt < 10)
			{
				name[cpt] = 'l';
				cpt++;
			}
		}
		if ((g_iMouseX > 288) & (g_iMouseX < 336) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// m
			if (cpt < 10)
			{
				name[cpt] = 'm';
				cpt++;
			}
		}
		if ((g_iMouseX > 336) & (g_iMouseX < 384) & (g_iMouseY > 160) & (g_iMouseY < 208))
		{
			// n
			if (cpt < 10)
			{
				name[cpt] = 'n';
				cpt++;
			}
		}
		if ((g_iMouseX > 48) & (g_iMouseX < 96) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// o
			if (cpt < 10)
			{
				name[cpt] = 'o';
				cpt++;
			}
		}
		if ((g_iMouseX > 96) & (g_iMouseX < 144) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// p
			if (cpt < 10)
			{
				name[cpt] = 'p';
				cpt++;
			}
		}
		if ((g_iMouseX > 144) & (g_iMouseX < 192) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// q
			if (cpt < 10)
			{
				name[cpt] = 'q';
				cpt++;
			}
		}
		if ((g_iMouseX > 192) & (g_iMouseX < 240) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// r
			if (cpt < 10)
			{
				name[cpt] = 'r';
				cpt++;
			}
		}
		if ((g_iMouseX > 240) & (g_iMouseX < 288) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// s
			if (cpt < 10)
			{
				name[cpt] = 's';
				cpt++;
			}
		}
		if ((g_iMouseX > 288) & (g_iMouseX < 336) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// t
			if (cpt < 10)
			{
				name[cpt] = 't';
				cpt++;
			}
		}
		if ((g_iMouseX > 336) & (g_iMouseX < 384) & (g_iMouseY > 208) & (g_iMouseY < 256))
		{
			// u
			if (cpt < 10)
			{
				name[cpt] = 'u';
				cpt++;
			}
		}
		if ((g_iMouseX > 48) & (g_iMouseX < 96) & (g_iMouseY > 256) & (g_iMouseY < 304))
		{
			// v
			if (cpt < 10)
			{
				name[cpt] = 'v';
				cpt++;
			}
		}
		if ((g_iMouseX > 96) & (g_iMouseX < 144) & (g_iMouseY > 256) & (g_iMouseY < 304))
		{
			// w
			if (cpt < 10)
			{
				name[cpt] = 'w';
				cpt++;
			}
		}
		if ((g_iMouseX > 144) & (g_iMouseX < 192) & (g_iMouseY > 256) & (g_iMouseY < 304))
		{
			// x
			if (cpt < 10)
			{
				name[cpt] = 'x';
				cpt++;
			}
		}
		if ((g_iMouseX > 192) & (g_iMouseX < 240) & (g_iMouseY > 256) & (g_iMouseY < 304))
		{
			// y
			if (cpt < 10)
			{
				name[cpt] = 'y';
				cpt++;
			}
		}
		if ((g_iMouseX > 240) & (g_iMouseX < 288) & (g_iMouseY > 256) & (g_iMouseY < 304))
		{
			// z
			if (cpt < 10)
			{
				name[cpt] = 'z';
				cpt++;
			}
		}
		if ((g_iMouseX > 336) & (g_iMouseX < 384) & (g_iMouseY > 256) & (g_iMouseY < 304))
		{
			// DEL
			if (cpt > 0)
			{
				name[cpt - 1] = ' ';
				cpt--;
			}
		}
		if ((g_iMouseX > 384) & (g_iMouseX < 464) & (g_iMouseY > 32) & (g_iMouseY < 80))
		{
			// OK;

			if (tPosition.m_bLoadMode == false) // Appelle la création d'un new fichier
			{

			}
			else // Appelle le chargement
			{
				tKeyboard.LoadSave();
				tKeyboard.Delete();
				tGame.Create();
				tPosition.EmuInGame();
			}
			
			// créer variable du nom du joueur
		}
	}
}

void Keyboard::Update()
{
	GfxTextSpritePrintf(tNameSprite, "%s", name);
}

void Keyboard::Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_tKeyboardBackgroundSprite);
	GfxSpriteRender(tNameSprite);
	GfxSpriteRender(tExplainSprite);
}

void Keyboard::CreateSave() // Variable tSaveFile à utiliser
{

}

void Keyboard::LoadSave()
{
	tSaveFile = GfxFileOpenRead("saves/saves.txt");
	bool bIsNameFinded = false;
	int iCpt = 0;
	bool bIncomeFinded = false;

	for (;;)
	{
		const unsigned char cCar = GfxFileReadChar(tSaveFile); // cCar sera une lettre lue du fichier

		if (bIsNameFinded == true)
		{
			if ((bIncomeFinded == true) & (cCar != '\n'))
			{
				tGame.m_fMoney += (float((cCar - 48) * (float(pow((float(10)), (float(iCpt)))))));
				iCpt++;
			}

			if ((bIncomeFinded == true) & (cCar == '\n'))
			{
				iCpt = 0;
				break;
			}

			if ((bIncomeFinded == false) & (cCar != '\n'))
			{
				tGame.m_fIncome += (float((cCar - 48) * (float(pow((float(10)), (float(iCpt)))))));
				iCpt++;
			}

			if ((bIncomeFinded == false) & (cCar == '\n'))
			{
				bIncomeFinded = true;
				iCpt = 0;
			}
		}

		if (cCar == ':') // Veut dire qu'on lis le nom d'un joueur
		{
			// cpt vaut le nombre de lettre présente dans mon pseudo que je désire charger
			// tester les lettres : S'arreter soit si j'ai lu le nombre de lettre qu'il faut, soit si une lettre est fausse
			iCpt = 0;
			while ((iCpt < cpt) & (name[iCpt] == GfxFileReadChar(tSaveFile))) // Je lis les lettres une par une tant que j'en ai lu moins que le nombre de lettre qu'il y a dans ce que je recherche et qu'elles correspondent
			{
				iCpt++;
			}
			if ((iCpt == cpt) & (GfxFileReadChar(tSaveFile) == '\n'))
			{
				bIsNameFinded = true;
				iCpt = 0;
			}
			// On devrait avoir trouver le nom ici, si ce n'est pas le bon, on continue
		}

	}
}