#include "flib.h"
#include "MovableText.h" // Il faut lier les deux fichiers ! Sinon ça ne fonctionnera pas ! La liaison permet de lier flib.h avec ce nouveau fichier .h !
// Attention ! Si on mets l'include de MovableText avant le flib, il faudra que flib soit intégré dans le fichier MovableText.
// Attention ! Il faut que l'include de MovableText soit en dessous de flib.h

// Ce qu'on appelle la stack, c'est l'endroit où les variable sont créée dans un scope, elle disparaissent donc une fois le scope fermé
// Les infos de fonction sont aussi des variables de la stack, par exemple --> void MoveText(TMovableText * pText) <-- pText en est une.

// Utiliser des variables globales, c'est la mort, il ne faut PAS ! Donc on fait faire ça autrement ! On le fait via un "struct"

TMovableText g_tText; // Cette variable contient donc trois variables ! 
TMovableText g_tText2;

const int MAX_TEXT = 10000;

int g_iTextCount = 0;
TMovableText * g_pText[MAX_TEXT];

TMovableText * NewText(const char * pString, int iPosX, int iPosY)
{
	TMovableText * pText = new TMovableText;

	pText->m_iPosX = iPosX;
	pText->m_iPosY = iPosY;

	pText->m_pSprite = GfxTextSpriteCreate();
	GfxTextSpriteSetText(pText->m_pSprite, pString);

	return pText;
}

void Initialize()
{

}

void MoveText(TMovableText * pText)
{
	if (GfxInputIsPressed(EGfxInputID_KeyArrowLeft))
	{
		//(*pText).m_iPosX -= 2;
		pText->m_iPosX -= 2;    // On doit utiliser celle ci dans les 90% des cas.

		//pText.m_iPosX -= 2;
	}
	if (GfxInputIsPressed(EGfxInputID_KeyArrowRight))
	{
		(*pText).m_iPosX += 2;
	}
	if (GfxInputIsPressed(EGfxInputID_KeyArrowUp))
	{
		(*pText).m_iPosY -= 2;
	}
	if (GfxInputIsPressed(EGfxInputID_KeyArrowDown))
	{
		(*pText).m_iPosY += 2;
	}

	GfxSpriteSetPosition((*pText).m_pSprite, float((*pText).m_iPosX), float((*pText).m_iPosY));
}

void Update()
{
	if (GfxInputIsPressed(EGfxInputID_MouseLeft))
	{
		if (g_pText[g_iTextCount % MAX_TEXT] != 0)
		{
			GfxSpriteDestroy(g_pText[g_iTextCount % MAX_TEXT]->m_pSprite);
			delete g_pText[g_iTextCount % MAX_TEXT];
			g_pText[g_iTextCount % MAX_TEXT] = 0;
		}

		g_pText[g_iTextCount % MAX_TEXT] = NewText(".", GfxGetCurrentMouseX(), GfxGetCurrentMouseY()); // Le modulo ( % 5 ) permet de ne pas sortir du tableau
		++g_iTextCount;
	}

	for (int i = 0; i < MAX_TEXT; ++i)
	{
		if (g_pText[i] != 0)
		{
			MoveText(g_pText[i]);
		}
	}
}

void Render()
{
	GfxClear(EGfxColor_Black);

	for (int i = 0; i < MAX_TEXT; ++i)
	{
		if (g_pText[i] != 0)
		{
			GfxSpriteRender(g_pText[i]->m_pSprite);
		}
	}
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}


