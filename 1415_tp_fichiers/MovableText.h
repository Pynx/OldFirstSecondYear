#ifndef MOVABLE_TEXT_INCLUDED // Grace � cette ligne, la 2eme et la derniere, nous pouvons l'int�grer un nombre infini de fois sans g�n�rer d'erreurs !
#define MOVABLE_TEXT_INCLUDED // Nous d�finissons ce qui permettra de ne pas le relire si il a d�ja �t� lu !

#include "flib.h" // Si on �crit ceci ici, on peut mettre le include de ce fichier avant l'include de flib dans le fichier main
// Pour cr�er ce fichier, on fait un clic droit sur le projet ( ici "1415_tp_fichiers" ) et on fait Add -> New Item.
// On choisis le type .h et on lui donne le nom du nouveau type !

// Il faut penser � lier les deux fichiers

struct TMovableText // Ceci est une structure, le mot clef est struct. C'est un nouveau type de variable ! 
{
	TGfxSprite * m_pSprite; // Ici, TGfxSprite sera consid�r� comme une erreur car l'include flib.h n'est pas int�gr� ! Sauf si le fichier est li� dans main.cpp !
	int m_iPosX;
	int m_iPosY;
}; // Il FAUT un ";" !

#endif