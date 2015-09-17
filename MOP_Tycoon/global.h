#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "mainmenu.h"
#include "game.h"
#include "keyboard.h"
#include "redirect.h"

extern MainMenu tMainMenu;
extern Keyboard tKeyboard;
extern Position tPosition;
extern Game tGame;

inline MainMenu GetMainMenu()
{
	return tMainMenu;
}
inline Keyboard GetKeyboard()
{
	return tKeyboard;
}
inline Game GetGame()
{
	return tGame;
}
inline Position GetPosition()
{
	return tPosition;
}


#endif