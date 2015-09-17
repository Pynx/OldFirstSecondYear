#include "flib.h"


// Même nomenclature comme ça on à tous la même

TGfxSprite * pTextSprite = nullptr, * pTextSprite3 = nullptr; // Initialisation de pTextSprite --> Création d'un variable de type TGfxSprite, qui sera un pointeur ( à cause de l'* ) et qui s'appellera pTextSprite. Elle sera vide !
TGfxSprite * pTextSprite2 = nullptr;

void Initialize() // 
{
	pTextSprite = GfxTextSpriteCreate(); // Crée du texte
	pTextSprite2 = GfxTextSpriteCreate();
	pTextSprite3 = GfxTextSpriteCreate(); 

	GfxTextSpriteSetText(pTextSprite, "The Game");
	GfxTextSpriteSetText(pTextSprite2, "The Game");     // Ecrit The Game dans la variable pTextSprite2
	GfxTextSpriteSetText(pTextSprite3, "The Game");

	GfxSpriteSetPosition(pTextSprite, 200.5, 150); // Donne une position au texte. Les positions qui ne sont pas piles, qui ont des virgules seront affichées bizarrement !
	GfxSpriteSetPosition(pTextSprite2, 200, 160);
	GfxSpriteSetPosition(pTextSprite3, 200, 170.5);
}

void Update()
{
	float posX = GfxSpriteGetPositionX(pTextSprite) + 1; // Récuperer la position de pTextSprite dans la variable de type float appellée "posX" et il l'incrémente
	GfxSpriteSetPosition(pTextSprite, posX, 150);       // Modifie la pos
}

void Render()
{
	GfxClear(EGfxColor_Blue);          // Mets un flond bleu, sinon les pixel affichés vont restés ( et ce sera dégolasse ) 
	GfxSpriteRender(pTextSprite);
	GfxSpriteRender(pTextSprite2);
	GfxSpriteRender(pTextSprite3);   // Affiche pTextSprite3
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render); // Fait le le lien avec les autres parties
}
