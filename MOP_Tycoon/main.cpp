#include "flib.h"
#include "global.h"
#include "redirect.h"
#include "keyboard.h"
#include "game.h"
#include "mainmenu.h"

MainMenu tMainMenu;
Keyboard tKeyboard;
Position tPosition;
Game tGame;

void Initialize()
{ 
	tMainMenu.Create();
}

void Update()
{
	tPosition.Input();
	tPosition.Update();
}

void Render()
{
	tPosition.Render();
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
