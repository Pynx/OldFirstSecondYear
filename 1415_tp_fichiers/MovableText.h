#ifndef MOVABLE_TEXT_INCLUDED // Grace à cette ligne, la 2eme et la derniere, nous pouvons l'intégrer un nombre infini de fois sans générer d'erreurs !
#define MOVABLE_TEXT_INCLUDED // Nous définissons ce qui permettra de ne pas le relire si il a déja été lu !

#include "flib.h" // Si on écrit ceci ici, on peut mettre le include de ce fichier avant l'include de flib dans le fichier main
// Pour créer ce fichier, on fait un clic droit sur le projet ( ici "1415_tp_fichiers" ) et on fait Add -> New Item.
// On choisis le type .h et on lui donne le nom du nouveau type !

// Il faut penser à lier les deux fichiers

struct TMovableText // Ceci est une structure, le mot clef est struct. C'est un nouveau type de variable ! 
{
	TGfxSprite * m_pSprite; // Ici, TGfxSprite sera considéré comme une erreur car l'include flib.h n'est pas intégré ! Sauf si le fichier est lié dans main.cpp !
	int m_iPosX;
	int m_iPosY;
}; // Il FAUT un ";" !

#endif