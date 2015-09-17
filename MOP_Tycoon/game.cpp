#include "flib.h"
#include "redirect.h"
#include "keyboard.h"
#include "mainmenu.h"
#include "global.h"

void Game::Create()
{
	g_tGameBackgroundTexture = GfxTextureLoad("gfx/gamebg.tga");
	g_tGameBackgroundSprite = GfxSpriteCreate(g_tGameBackgroundTexture);


	m_tIncomeSprite = GfxTextSpriteCreate();
	m_tMoneySprite = GfxTextSpriteCreate();
	//GfxSpriteSetScale(m_tIncomeSprite, 1, 1);
	//GfxSpriteSetScale(m_tMoneySprite, 1, 1);
	GfxSpriteSetFilteringEnabled(m_tIncomeSprite, false);
	GfxSpriteSetFilteringEnabled(m_tMoneySprite, false);
	GfxSpriteSetPosition(m_tIncomeSprite, 3, 15);
	GfxSpriteSetPosition(m_tMoneySprite, 3, 3);
	GfxTextSpritePrintf(m_tIncomeSprite, "Income : %d/s", m_fIncome);
	GfxTextSpritePrintf(m_tMoneySprite, "Money : %d", m_fMoney);


	GfxSpriteSetFilteringEnabled(g_tGameBackgroundSprite, false);
	GfxSpriteSetPosition(g_tGameBackgroundSprite, 0, 0);
}

void Game::Delete()
{
}

void Game::Input()
{
}

void Game::Update()
{
	m_fMoney += (int((GfxTimeFrameGetCurrentDurationInSeconds())* m_fIncome));

	GfxTextSpritePrintf(m_tIncomeSprite, "Income : %d/s", m_fIncome);
	GfxTextSpritePrintf(m_tMoneySprite, "Money : %d", m_fMoney);
}

void Game::Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_tGameBackgroundSprite);
	GfxSpriteRender(m_tIncomeSprite);
	GfxSpriteRender(m_tMoneySprite);
}