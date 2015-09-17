#include "flib.h"

TGfxSprite * g_tBackgroundSprite = nullptr;
TGfxSprite * g_tPlayerOneScore = nullptr;
TGfxSprite * g_tPlayerTwoScore = nullptr;
TGfxSprite * g_tRound = nullptr;
TGfxSprite * g_tFirstNumber = nullptr;
TGfxSprite * g_tSecondNumber = nullptr;
TGfxSprite * g_tInstruction = nullptr;
TGfxTexture * g_tBackgroundTexture = nullptr;

TGfxSprite * g_tMainMenuBackgroundSprite = nullptr;
TGfxTexture * g_tMainMenuBackgroundTexture = nullptr;


int g_iHiddenNumber = 0;
int g_iNumberOne = 0;
int g_iNumberTwo = 0;
int g_iPlayerOneScore = 0;
int g_iPlayerTwoScore = 0;
int g_iRound = 1;

int g_iMouseX;
int g_iMouseY;

int g_iPlayerTurn = 1;
bool g_bPlayerIsChosing = true;

struct TGameMenuData
{

	enum EGameMenuState
	{
		EGameMenuState_MainMenu = 1,
		EGameMenuState_InGameOne,
		EGameMenuState_InGameTwo,
		EGameMenuState_InGameThree,
	};

	EGameMenuState m_eGameMenuState = EGameMenuState_MainMenu;

	void Input()
	{
		if (m_eGameMenuState == EGameMenuState_MainMenu)
		{
			if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
			{
				g_iMouseX = GfxGetCurrentMouseX();
				g_iMouseY = GfxGetCurrentMouseY();

				if ((g_iMouseX > 128) & (g_iMouseX < 352) & (g_iMouseY > 64) & (g_iMouseY < 104)) // COLISION OK BUTTON
				{
					m_eGameMenuState = EGameMenuState_InGameOne;
					GameMenu_MainMenuToGameOne();
				}
			}
		}
		else if (m_eGameMenuState == EGameMenuState_InGameOne)
		{
			if (GfxInputIsJustPressed(EGfxInputID_MouseLeft))
			{
				g_iMouseX = GfxGetCurrentMouseX();
				g_iMouseY = GfxGetCurrentMouseY();

				if ((g_iMouseX > 352) & (g_iMouseX < 448) & (g_iMouseY > 128) & (g_iMouseY < 192)) // COLISION OK BUTTON
				{
					if ((g_bPlayerIsChosing == true) & (g_iPlayerTurn == 1)) // Joueur 1 choisi
					{
						g_iHiddenNumber = ((g_iNumberOne * 10) + g_iNumberTwo);
						g_bPlayerIsChosing = false;
						g_iNumberOne = 0;
						g_iNumberTwo = 0;
						GfxTextSpriteSetText(g_tInstruction, "Player 2, Try to find the Secret Number");
					}
					else if ((g_bPlayerIsChosing == false) & (g_iPlayerTurn == 1)) // Joueur 2 teste
					{
						if (g_iHiddenNumber == ((g_iNumberOne * 10) + g_iNumberTwo)) // Le chiffre est le bon !
						{
							g_bPlayerIsChosing = true;
							g_iPlayerTurn = 2;
							GfxTextSpriteSetText(g_tInstruction, "Player 2, Please choose a Number and press OK");
						}
						else
						{
							g_iPlayerOneScore++;
							if (g_iHiddenNumber > ((g_iNumberOne * 10) + g_iNumberTwo))
							{
								GfxTextSpriteSetText(g_tInstruction, "Player 2, The number you're seeking is Bigger !");
							}
							else
							{
								GfxTextSpriteSetText(g_tInstruction, "Player 2, The number you're seeking is Smaller !");
							}
						}
					}
					else if ((g_bPlayerIsChosing == true) & (g_iPlayerTurn == 2)) // Joueur 2 choisi
					{
						g_iHiddenNumber = ((g_iNumberOne * 10) + g_iNumberTwo);
						g_bPlayerIsChosing = false;
						g_iNumberOne = 0;
						g_iNumberTwo = 0;
						GfxTextSpriteSetText(g_tInstruction, "Player 1, Try to find the Secret Number");
					}
					else // (g_bPlayerIsChosing == false & g_iPlayerTurn == 2) // Joueur 1 teste
					{
						if (g_iHiddenNumber == ((g_iNumberOne * 10) + g_iNumberTwo)) // Le chiffre est le bon !
						{
							g_bPlayerIsChosing = true;
							g_iPlayerTurn = 1;
							GfxTextSpriteSetText(g_tInstruction, "Player 1, Please choose a Number and press OK");
							g_iRound++;
						}
						else
						{
							g_iPlayerTwoScore++;
							if (g_iHiddenNumber > ((g_iNumberOne * 10) + g_iNumberTwo))
							{
								GfxTextSpriteSetText(g_tInstruction, "Player 1, The number you're seeking is Bigger !");
							}
							else
							{
								GfxTextSpriteSetText(g_tInstruction, "Player 1, The number you're seeking is Smaller !");
							}
						}
					}
				}

				if ((g_iMouseX > 160) & (g_iMouseX < 224) & (g_iMouseY > 64) & (g_iMouseY < 128)) // COLISION NUMBER ONE ++
				{
					if (g_iNumberOne < 9)
					{
						g_iNumberOne++;
					}
					else
					{
						g_iNumberOne = 0;
					}
				}

				if ((g_iMouseX > 160) & (g_iMouseX < 224) & (g_iMouseY > 192) & (g_iMouseY < 256)) // COLISION NUMBER ONE --
				{
					if (g_iNumberOne > 0)
					{
						g_iNumberOne--;
					}
					else
					{
						g_iNumberOne = 9;
					}
				}

				if ((g_iMouseX > 256) & (g_iMouseX < 320) & (g_iMouseY > 64) & (g_iMouseY < 128)) // COLISION NUMBER TWO ++
				{
					if (g_iNumberTwo < 9)
					{
						g_iNumberTwo++;
					}
					else
					{
						g_iNumberTwo = 0;
					}
				}

				if ((g_iMouseX > 256) & (g_iMouseX < 320) & (g_iMouseY > 192) & (g_iMouseY < 256)) // COLISION NUMBER TWO --
				{
					if (g_iNumberTwo > 0)
					{
						g_iNumberTwo--;
					}
					else
					{
						g_iNumberTwo = 9;
					}
				}

				if ((g_iMouseX > 416) & (g_iMouseY > 288)) // COLISION EXIT
				{
					GameMenu_GameOneToMainMenu();
					m_eGameMenuState = EGameMenuState_MainMenu;
				}
			}
		}


	}

	void GameMenu_MainMenuToGameOne()
	{
		// Starting deleting menu sprites

		GfxSpriteDestroy(g_tMainMenuBackgroundSprite);
		GfxTextureDestroy(g_tMainMenuBackgroundTexture);

		// Starting creating sprite for the Game One

		g_tRound = GfxTextSpriteCreate();
		g_tPlayerTwoScore = GfxTextSpriteCreate();
		g_tPlayerOneScore = GfxTextSpriteCreate();
		g_tInstruction = GfxTextSpriteCreate();
		g_tFirstNumber = GfxTextSpriteCreate();
		g_tSecondNumber = GfxTextSpriteCreate();

		GfxTextSpritePrintf(g_tRound, "%d", g_iRound);
		GfxTextSpritePrintf(g_tPlayerOneScore, "%d", g_iPlayerOneScore);
		GfxTextSpritePrintf(g_tPlayerTwoScore, "%d", g_iPlayerTwoScore);
		GfxTextSpritePrintf(g_tFirstNumber, "%d", g_iNumberOne);
		GfxTextSpritePrintf(g_tSecondNumber, "%d", g_iNumberTwo);
		GfxTextSpriteSetText(g_tInstruction, "Player 1, Please choose a Number, Then press OK");

		GfxSpriteSetScale(g_tRound, 2, 2);
		GfxSpriteSetScale(g_tPlayerOneScore, 2, 2);
		GfxSpriteSetScale(g_tPlayerTwoScore, 2, 2);
		GfxSpriteSetScale(g_tFirstNumber, 5, 5);
		GfxSpriteSetScale(g_tSecondNumber, 5, 5);

		GfxSpriteSetPosition(g_tRound, 230, 40);
		GfxSpriteSetPosition(g_tPlayerOneScore, 55, 40);
		GfxSpriteSetPosition(g_tPlayerTwoScore, 400, 40);
		GfxSpriteSetPosition(g_tFirstNumber, 180, 143);
		GfxSpriteSetPosition(g_tSecondNumber, 268, 143);
		GfxSpriteSetPosition(g_tInstruction, 15, 300);

		g_tBackgroundTexture = GfxTextureLoad("gfx/background.tga");
		g_tBackgroundSprite = GfxSpriteCreate(g_tBackgroundTexture);

		GfxSpriteSetFilteringEnabled(g_tInstruction, false);
		GfxSpriteSetFilteringEnabled(g_tRound, false);
		GfxSpriteSetFilteringEnabled(g_tPlayerOneScore, false);
		GfxSpriteSetFilteringEnabled(g_tPlayerTwoScore, false);
		GfxSpriteSetFilteringEnabled(g_tBackgroundSprite, false);
		GfxSpriteSetFilteringEnabled(g_tFirstNumber, false);
		GfxSpriteSetFilteringEnabled(g_tSecondNumber, false);
		GfxSpriteSetPosition(g_tBackgroundSprite, 0, 0);

		// End of creating sprite for the Game One
	}

	void GameMenu_GameOneToMainMenu()
	{
		GfxSpriteDestroy(g_tInstruction);
		GfxSpriteDestroy(g_tRound);
		GfxSpriteDestroy(g_tPlayerOneScore);
		GfxSpriteDestroy(g_tPlayerTwoScore);
		GfxSpriteDestroy(g_tFirstNumber);
		GfxSpriteDestroy(g_tSecondNumber);
		GfxSpriteDestroy(g_tBackgroundSprite);
		GfxTextureDestroy(g_tBackgroundTexture);

		//Starting to create sprite for main menu

		g_tMainMenuBackgroundTexture = GfxTextureLoad("gfx/menu.tga");
		g_tMainMenuBackgroundSprite = GfxSpriteCreate(g_tMainMenuBackgroundTexture);

		GfxSpriteSetFilteringEnabled(g_tMainMenuBackgroundSprite, false);
		GfxSpriteSetPosition(g_tMainMenuBackgroundSprite, 0, 0);

		g_iHiddenNumber = 0;
		g_iNumberOne = 0;
		g_iNumberTwo = 0;
		g_iPlayerOneScore = 0;
		g_iPlayerTwoScore = 0;
		g_iRound = 1;
		g_iPlayerTurn = 1;
		g_bPlayerIsChosing = true;
	}

	void Update()
	{
		if (m_eGameMenuState == EGameMenuState_MainMenu)
		{
		}
		else if (m_eGameMenuState == EGameMenuState_InGameOne)
		{
			GfxTextSpritePrintf(g_tRound, "%d", g_iRound);
			GfxTextSpritePrintf(g_tPlayerOneScore, "%d", g_iPlayerOneScore);
			GfxTextSpritePrintf(g_tPlayerTwoScore, "%d", g_iPlayerTwoScore);
			GfxTextSpritePrintf(g_tFirstNumber, "%d", g_iNumberOne);
			GfxTextSpritePrintf(g_tSecondNumber, "%d", g_iNumberTwo);
		}
	}

	void GameMenu_Render()
	{
		if (m_eGameMenuState == EGameMenuState_MainMenu)
		{
			GfxSpriteRender(g_tMainMenuBackgroundSprite);
		}
		else if (m_eGameMenuState == EGameMenuState_InGameOne)
		{
			GfxSpriteRender(g_tBackgroundSprite);
			GfxSpriteRender(g_tRound);
			GfxSpriteRender(g_tPlayerTwoScore);
			GfxSpriteRender(g_tPlayerOneScore);
			GfxSpriteRender(g_tInstruction);
			GfxSpriteRender(g_tFirstNumber);
			GfxSpriteRender(g_tSecondNumber);
		}
	}
};

TGameMenuData g_tGameMenuData;

void Initialize()
{
	//Création des sprites du menu

	g_tMainMenuBackgroundTexture = GfxTextureLoad("gfx/menu.tga");
	g_tMainMenuBackgroundSprite = GfxSpriteCreate(g_tMainMenuBackgroundTexture);

	GfxSpriteSetFilteringEnabled(g_tMainMenuBackgroundSprite, false);
	GfxSpriteSetPosition(g_tMainMenuBackgroundSprite, 0, 0);

	//Fin de création des sprites du menu
}

void Update()
{
	g_tGameMenuData.Input();
	g_tGameMenuData.Update();
}

void Render()
{
	GfxClear(EGfxColor_Black);
	g_tGameMenuData.GameMenu_Render();
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render); // Fait le le lien avec les autres parties
}
