#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "flib.h"
#include "flib_vec3.h"
#include "redirect.h"
#include <math.h>

// � mettre


//g_tMainMenuBackgroundTexture = GfxTextureLoad("gfx/menu.tga");
//g_tMainMenuBackgroundSprite = GfxSpriteCreate(g_tMainMenuBackgroundTexture);
//
//GfxSpriteSetFilteringEnabled(g_tMainMenuBackgroundSprite, false);
//GfxSpriteSetPosition(g_tMainMenuBackgroundSprite, 0, 0);

struct MainMenu
{
	TGfxSprite * g_tMainMenuBackgroundSprite = nullptr;
	TGfxTexture * g_tMainMenuBackgroundTexture = nullptr;

	void Create(); // Cr�e les sprites n�cessaires � l'affichage du menu principal
	void Delete();
	void Input(); // G�re les Inputes
	void Update();
	void Render();
};


#endif