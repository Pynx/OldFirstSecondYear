//#include "conio.h"

#include "stdafx.h"
#include "drawable.h"
#include "collidable.h"
#include "dynamicentity.h"
#include "enemy.h"
#include "player.h"
#include "staticentity.h"

char * GetName(TDynamicEntity &obj)
{
	return obj.GetName();
}

//int GetValue(TDynamicEntity &obj)
//{
//	//return obj.m_iTemp;
//}

void Destroy(TDynamicEntity &obj)
{
	delete &obj; // Le & c'est l'adresse de l'objet. C'est donc un pointeur ( référence )
}
void Destroy(TDynamicEntity * obj)
{
	delete obj; // On peut aussi faire celle du dessus comme ça

	// Les référence sont pour nous, le code fait de toute façon des pointeurs.
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Creation new TPlayer\n\n");

	TPlayer * pPlayer = new TPlayer();

	printf("\ntest 01 - name : %s \n", pPlayer->GetName()); // Ici on appelle le getname de player
	printf("\ntest 02 - name : %s \n", GetName(*pPlayer) );  // Ici on aura le getname de player si le getname de dynamic est en virtual !

	printf("\ntest 03 - nbr : %s \n", GetName(*pPlayer));
	printf("\ntest 04 - nbr : %s \n", GetName(*pPlayer));

	printf("\nCreation new TEntity\n\n");

	TStaticEntity * pStaticEntity = new TStaticEntity();

	pPlayer->Move(2.f, 0.5f); // ça dit que move est innacessible. C'est pourquoi on a mis player en public

	printf("\nDestruction new TEntity\n\n");

	delete pStaticEntity;

	printf("\nDestruction new TPlayer\n\n");

	//delete pPlayer;
	Destroy(pPlayer);

	pPlayer = nullptr;

	//getch();

	return 0;
}











































//class TMyClass
//{
//
//
//
//public:
//	static TMyClass * CreateNewInstance()
//	{
//		return new TMyClass();
//	}
//
//
//
//	int m_iMyNumber;
//	int m_iMyNumber2;
//
//	TMyClass()
//	{
//
//	}
//
//	TMyClass() : TMyClass(42, 25) // Constructeur appellant un constructeur de deux int
//	{
//
//	}
//
//	//TMyClass() : m_iMyNumber(42)
//	//{
//	//
//	//}
//
//	TMyClass(int iMyInitNumber) : m_iMyNumber(iMyInitNumber)
//	{
//
//	}
//
//	TMyClass(float fMyInitNumber) : m_iMyNumber((int)fMyInitNumber)
//	{
//
//	}
//
//	TMyClass(int iMyInitNumber, int iMyInitNumber2) : m_iMyNumber((int)iMyInitNumber), m_iMyNumber2((int)iMyInitNumber2)
//	{
//
//	}
//
//
//	~TMyClass()
//	{
//
//	}
//
//	bool Initialize()
//	{
//		bool bResult = true;
//
//		// do stuff allocate
//		// if error bResult = false
//
//		return bResult;
//	}
//};
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	TMyClass tC0;
//	TMyClass * ptC;
//
//	ptC = new TMyClass(28, 42); // Si ça tombe, il ne restera plus de mémoire, il faut donc vérifier si on peut tout créer. SI ça ne s'est pas initialisé correctement, on delete ce qui s'est créé
//	if (ptC != nullptr)
//	{
//		if (!ptC->Initialize())
//		{
//			delete ptC;
//			ptC = nullptr;
//		}
//
//	}
//
//
//	return 0;
//}