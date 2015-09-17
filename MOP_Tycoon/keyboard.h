#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "flib.h"
#include "flib_vec3.h"
#include <math.h>

struct Keyboard
{
	TGfxSprite * g_tKeyboardBackgroundSprite = nullptr;
	TGfxTexture * g_tKeyboardBackgroundTexture = nullptr;
	TGfxSprite * tNameSprite = nullptr;
	TGfxSprite * tExplainSprite = nullptr;
	TGfxFile * tSaveFile = nullptr;

	char name[10];
	int cpt = 0;

	void Create(); // Crée les sprites nécessaires à l'affichage du menu principal
	void Delete();
	void Input(); // Gère les Inputes
	void Update();
	void Render();
	void LoadSave();
	void CreateSave();
};


#endif