#include "flib.h"
#include "flib_vec3.h"
#include "global.h"
#include "redirect.h"
#include "keyboard.h"
#include "mainmenu.h"
#include "game.h"
#include <math.h>


void Position::EmuMainMenu()
{
	m_eMenuState = EMenuState_MainMenu;
}

void Position::EmuKeyboard()
{
	m_eMenuState = EMenuState_Keyboard;
}

void Position::EmuInGame()
{
	m_eMenuState = EMenuState_InGame;
}

void Position::Input()
{
	if (m_eMenuState == EMenuState_MainMenu)
	{
		tMainMenu.Input();
	}
	else if (m_eMenuState == EMenuState_Keyboard)
	{
		tKeyboard.Input();
	}
	else
	{
		tGame.Input();
	}
}

void Position::Update()
{
	if (m_eMenuState == EMenuState_MainMenu)
	{
		tMainMenu.Update();
	}
	else if (m_eMenuState == EMenuState_Keyboard)
	{
		tKeyboard.Update();
	}
	else 
	{
		tGame.Update();
	}
}

void Position::Render()
{
	if (m_eMenuState == EMenuState_MainMenu)
	{
		tMainMenu.Render();
	}
	else if (m_eMenuState == EMenuState_Keyboard)
	{
		tKeyboard.Render();
	}
	else
	{
		tGame.Render();
	}
}





