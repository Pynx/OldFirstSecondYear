#include "flib.h"
#include "redirect.h"
#include "keyboard.h"
#include "mainmenu.h"
#include "global.h"

void MainMenu::Create()
{
	g_tMainMenuBackgroundTexture = GfxTextureLoad("gfx/menu.tga");
	g_tMainMenuBackgroundSprite = GfxSpriteCreate(g_tMainMenuBackgroundTexture);

	GfxSpriteSetFilteringEnabled(g_tMainMenuBackgroundSprite, false);
	GfxSpriteSetPosition(g_tMainMenuBackgroundSprite, 0, 0);
}

void MainMenu::Delete()
{
	GfxSpriteDestroy(g_tMainMenuBackgroundSprite);
	GfxTextureDestroy(g_tMainMenuBackgroundTexture);
}

void MainMenu::Input()
{
	if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		int g_iMouseX = GfxGetCurrentMouseX();
		int g_iMouseY = GfxGetCurrentMouseY();

		if ((g_iMouseX > 128) & (g_iMouseX < 352) & (g_iMouseY > 96) & (g_iMouseY < 136)) // Click on New Game
		{
			tPosition.m_bLoadMode = false; // changer le mode en new
			tPosition.EmuKeyboard(); // State machine passe à keyboard
			tMainMenu.Delete();	// Delete background menu
			tKeyboard.Create(); // Add background keyboard	
		}
		if ((g_iMouseX > 128) & (g_iMouseX < 352) & (g_iMouseY > 184) & (g_iMouseY < 224)) // Click on Load Game
		{
			tPosition.m_bLoadMode = true;
			tPosition.EmuKeyboard();
			tMainMenu.Delete();	// Delete background menu
			tKeyboard.Create(); // Add background keyboard	
		}
	}
}

void MainMenu::Update()
{

}

void MainMenu::Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_tMainMenuBackgroundSprite);
}