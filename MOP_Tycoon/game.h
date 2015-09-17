#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "flib.h"
#include "flib_vec3.h"
#include <math.h>

struct Game
{
	TGfxSprite * g_tGameBackgroundSprite = nullptr;
	TGfxTexture * g_tGameBackgroundTexture = nullptr;
	TGfxSprite * m_tIncomeSprite = nullptr;
	TGfxSprite * m_tMoneySprite = nullptr;

	float m_fIncome = 0;
	float m_fMoney = 0;

	void Create(); // Cr�e les sprites n�cessaires � l'affichage du menu principal
	void Delete();
	void Input(); // G�re les Inputes
	void Update();
	void Render();
};



#endif