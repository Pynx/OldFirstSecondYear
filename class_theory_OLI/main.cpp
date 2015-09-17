#include "stdafx.h"

class TMyClass
{

public:
	static TMyClass * CreateNewInstance()
	{
		return new TMyClass();
	}



	int m_iMyNumber;
	int m_iMyNumber2;

	TMyClass() : TMyClass(42, 25) // Constructeur appellant un constructeur de deux int
	{

	}

	//TMyClass() : m_iMyNumber(42)
	//{
	//
	//}

	TMyClass(int iMyInitNumber) : m_iMyNumber(iMyInitNumber)
	{

	}

	TMyClass(float fMyInitNumber) : m_iMyNumber((int)fMyInitNumber)
	{

	}

	TMyClass(int iMyInitNumber, int iMyInitNumber2) : m_iMyNumber((int)iMyInitNumber), m_iMyNumber2((int)iMyInitNumber2)
	{

	}


	~TMyClass()
	{

	}

	bool Initialize()
	{
		bool bResult = true;

		// do stuff allocate
		// if error bResult = false
		
		return bResult;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	TMyClass tC0;
	TMyClass * ptC;

	ptC = new TMyClass(28, 42); // Si ça tombe, il ne restera plus de mémoire, il faut donc vérifier si on peut tout créer. SI ça ne s'est pas initialisé correctement, on delete ce qui s'est créé
	if (ptC != nullptr)
	{
		if (!ptC->Initialize())
		{
			delete ptC;
			ptC = nullptr;
		}

	}

	




	return 0;
}