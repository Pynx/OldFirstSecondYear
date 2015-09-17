#ifndef REDIRECT_H_INCLUDED
#define REDIRECT_H_INCLUDED




struct Position 
{
	// le m_ veut dire member.
	bool m_bLoadMode; // True = Loading, False = New Game

	enum EMenuState
	{
		EMenuState_MainMenu = 1,
		EMenuState_Keyboard,
		EMenuState_InGame,
	};

	EMenuState m_eMenuState = EMenuState_MainMenu;


	void EmuMainMenu();

	void EmuKeyboard();

	void EmuInGame();

	void Input();

	void Update();

	void Render();
};


#endif