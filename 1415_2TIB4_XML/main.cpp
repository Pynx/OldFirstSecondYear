#include "flib.h"
#include <cstring>

class TSLL_Item
{
	TSLL_Item();
	~TSLL_Item();

	int m_iItemData;
	TSLL_Item * m_pNextItem;

	TSLL_Item * FindLastItem()
	{
		TSLL_Item * m_pActualItem = this;

		for (;;)
		{
			if (m_pActualItem->m_pNextItem == 0)
			{
				return m_pActualItem;
			}
			else
			{
				m_pActualItem = m_pActualItem->m_pNextItem;
			}
		}
	}

	void Append(TSLL_Item * pNewItem) // Add an item
	{
		pNewItem->m_pNextItem = 0; // become the new terminator
		TSLL_Item * endListItem = FindLastItem();
		endListItem->m_pNextItem = newItem; // link it to the chain
	}

	int GetCount()
	{
		TSLL_Item * m_pActualItem = this;
		int m_pCount = 0;

		for (;;)
		{
			if (m_pActualItem->m_pNextItem == 0)
			{
				return m_pCount++;
			}
			else
			{
				m_pActualItem = m_pActualItem->m_pNextItem;
				m_pCount++;
			}
		}

	}
};

int RecursiveInt(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n > 0)
	{
		return n * RecursiveInt(n - 1);
	}
}

long long RecursiveLong(long long n)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n > 0)
	{
		return n * RecursiveLong(n - 1);
	}
}

char * ScanElement(char * MonPetitPointeurDeMaPetiteChaineDeCaractereTouteMignonne)
{


	return MonPetitPointeurDeMaPetiteChaineDeCaractereTouteMignonne;
}

void Initialize()
{
	TGfxFile  * pFile = GfxFileOpenRead("test2.XML");
	int iFileSize = GfxFileSize(pFile);
	char * g_ToParse = static_cast<char*>(GfxMemAlloc(iFileSize + 1));

	int iAlign = 0;

	for (int i = 0; i < iFileSize; i++)
	{
		g_ToParse[i] = GfxFileReadChar(pFile);
	}

	g_ToParse[iFileSize] = 0;

	int iPointeur = 0;
	int iNbrAttribut = 0;

	GfxFileClose(pFile);


	char * pch; // Création de la position dans la mémoire actuelle, un pointeur.
	GfxDbgPrintf("Parsing the xml file : \n\n%s\n\n", g_ToParse); // Printf d'explication

	pch = strchr(g_ToParse, '<');

	while ((pch - g_ToParse) < iFileSize)
	{
		if (pch != nullptr)
		{
			if ((strchr(pch, '/')) < (strchr(pch, '>'))) // Balise auto fermante ou fermante
			{
				if ((strchr(pch, '/')) - 1 == pch) // Balise fermante
				{
					//int iCpt = ((strchr(pch, '>')) - (strchr(pch, '<')));
					//char * cTest = (strchr(pch, '<') + 1);
					//for (int i = 0; i < iCpt - 1; i++)
					//{
					//	GfxDbgPrintf("%c", cTest[i]);
					//}
					iAlign--;
					for (int i = 0; i < iAlign; i++)
					{
						GfxDbgPrintf("\t");
					}
					GfxDbgPrintf("Balise Fermante : ");
					
					/*
					
					Afficher le nom de l'élément :

					*/

					int iCpt = ((strchr(pch, '>')) - (strchr(pch, '<')));
					char * cTest = (strchr(pch, '<') + 1);
					for (int i = 1; i < iCpt - 1; i++)
					{
						GfxDbgPrintf("%c", cTest[i]);
					}
					GfxDbgPrintf("\n");

					
					
					if (strchr(pch+1, '<') == nullptr)
					{
						break;
					}
					pch = (strchr(pch+1, '<'));
				}
				else // Balise auto fermante
				{
					iNbrAttribut = 0;
					for (int i = 0; i < iAlign; i++)
					{
						GfxDbgPrintf("\t");
					}
					GfxDbgPrintf("Balise Auto-Fermante : ");

					if (strchr(pch + 1, '=') == nullptr)
					{
						iNbrAttribut = 0;
					}
					else
					{
						if (strchr(pch + 1, '=') > strchr(pch + 1, '>'))
						{
							iNbrAttribut = 0;
						}
						else
						{
							iNbrAttribut = 1;

							char * secondpch = ((strchr(pch, '=')) + 1);

							for (;;)
							{
								if ((strchr(secondpch, '=') == nullptr))
								{
									break;
								}
								else
								{
									if (strchr(secondpch, '=') < strchr(secondpch, '>'))
									{
										iNbrAttribut++;
										secondpch = ((strchr(secondpch, '=')) + 1);
									}
									else
									{
										break;
									}
								}
							}

						}
					}


					if (iNbrAttribut == 0)
					{
						int iCpt = ((strchr(pch, '>')) - (strchr(pch, '<')));
						char * cTest = (strchr(pch, '<') + 1);
						for (int i = 0; i < iCpt - 2; i++)
						{
							GfxDbgPrintf("%c", cTest[i]);
						}

						GfxDbgPrintf(" : %i Attributes\n", iNbrAttribut);

					}
					else
					{
						int iCpt = ((strchr(pch, ' ')) - (strchr(pch, '<')));
						char * cTest = (strchr(pch, '<') + 1);
						for (int i = 0; i < iCpt - 1; i++)
						{
							GfxDbgPrintf("%c", cTest[i]);
						}

						GfxDbgPrintf(" : %i Attributes : ", iNbrAttribut);

						char * secondpch = (strchr(pch, ' ') + 1);

						for (int i = 0; i < iNbrAttribut; i++)
						{
							iCpt = ((strchr(secondpch, '=')) - secondpch);
							GfxDbgPrintf("Att. %i = ", i + 1);

							for (int i = 0; i < iCpt; i++)
							{
								GfxDbgPrintf("%c", secondpch[i]);
							}

							secondpch += iCpt + 1;
							if (i == iNbrAttribut - 1)
							{
								iCpt = ((strchr(secondpch, '/')) - secondpch);
							}
							else
							{
								iCpt = ((strchr(secondpch, ' ')) - secondpch);
							}

							GfxDbgPrintf(" = ");

							for (int i = 0; i < iCpt; i++)
							{
								GfxDbgPrintf("%c", secondpch[i]);
							}

							GfxDbgPrintf(" | ");

							secondpch += ((strchr(secondpch, ' ') + 1) - secondpch);

						}
						GfxDbgPrintf("\n");

					}


					if (strchr(pch+1, '<') == nullptr)
					{
						break;
					}
					pch = (strchr(pch + 1, '<'));

				}
			}
			else // Balise ouvrante ----------------------------------------------------
			{
				for (int i = 0; i < iAlign; i++)
				{
					GfxDbgPrintf("\t");
				}
				GfxDbgPrintf("Balise Ouvrante : ");
								
				if (strchr(pch + 1, '=') == nullptr)
				{
					iNbrAttribut = 0;
				}
				else
				{
					if (strchr(pch + 1, '=') > strchr(pch + 1, '>'))
					{
						iNbrAttribut = 0;
					}
					else
					{
						iNbrAttribut = 1;

						char * secondpch = ((strchr(pch, '=')) + 1);

						for (;;)
						{
							if ((strchr(secondpch, '=') == nullptr))
							{
								break;
							}
							else
							{
								if (strchr(secondpch, '=') < strchr(secondpch, '>'))
								{
									iNbrAttribut++;
									secondpch = ((strchr(secondpch, '=')) + 1);
								}
								else
								{
									break;
								}
							}
						}
					}
				}
				
				if (iNbrAttribut == 0)
				{
					int iCpt = ((strchr(pch, '>')) - (strchr(pch, '<')));
					char * cTest = (strchr(pch, '<') + 1);
					for (int i = 0; i < iCpt - 1; i++)
					{
						GfxDbgPrintf("%c", cTest[i]);
					}

					GfxDbgPrintf(" : %i Attributes\n", iNbrAttribut);

				}
				else
				{
					int iCpt = ((strchr(pch, ' ')) - (strchr(pch, '<')));
					char * cTest = (strchr(pch, '<') + 1);
					for (int i = 0; i < iCpt - 1; i++)
					{
						GfxDbgPrintf("%c", cTest[i]);
					}

					GfxDbgPrintf(" : %i Attributes : ", iNbrAttribut);

					char * secondpch = (strchr(pch, ' ') + 1);

					for (int i = 0; i < iNbrAttribut; i++)
					{
						iCpt = ((strchr(secondpch, '=')) - secondpch);
						GfxDbgPrintf("Att. %i = ", i+1);

						for (int i = 0; i < iCpt; i++)
						{
							GfxDbgPrintf("%c", secondpch[i]);
						}

						secondpch += iCpt + 1;
						if (i == iNbrAttribut - 1)
						{
							iCpt = ((strchr(secondpch, '>')) - secondpch);
						}
						else
						{
							iCpt = ((strchr(secondpch, ' ')) - secondpch);
						}

						GfxDbgPrintf(" = ");
						
						for (int i = 0; i < iCpt; i++)
						{
							GfxDbgPrintf("%c", secondpch[i]);
						}

						GfxDbgPrintf(" | ");

						secondpch += ((strchr(secondpch, ' ') + 1) - secondpch);

					}
					GfxDbgPrintf("\n");

				}



				if (strchr(pch+1, '<') == nullptr)
				{
					break;
				}
				pch = (strchr(pch+1, '<'));
				//pch = (strchr(pch, '>') + 1);
				iAlign++;

				//     \t = tabulation
			}
		}
	}



	GfxDbgPrintf("\n\n");



	//char * pch; // Création de pch 
	//GfxDbgPrintf("Looking for the '<' character in \n\"---------------------\"\n%s\"---------------------\"\n", g_ToParse); // Printf d'explication
	//pch = strchr(g_ToParse, '<'); //
	//while (pch != NULL)
	//{
	//	GfxDbgPrintf("found at %d\n", pch - g_ToParse + 1);
	//	pch = strchr(pch + 1, '<');
	//}






	//while (g_ToParse[iPointeur] != 0)
	//{
	//	GfxDbgPrintf("%c", g_ToParse[iPointeur]);
	//	iPointeur++;
	//}
	//
	//GfxDbgPrintf("\nNombres de caractères du fichier : %d", iPointeur);
	//
	//GfxMemFree(g_ToParse);




	// Recursive

	for (int i = 4; i < 60; i++)
	{
		unsigned int Recur = RecursiveInt(i);
		long long RecurLong = RecursiveLong(i);
		GfxDbgPrintf("%i -> Int : %i     HEXA : %x   Long Long : %lld  \n", i, Recur, RecurLong, RecurLong);
	}

	int valeur = 1;

	for (int i = 1; i < 60; i++)
	{
		valeur *= i;
		GfxDbgPrintf("%i -> %i \n", i, valeur);
	}




}

void Update()
{

}

void Render()
{
	GfxClear(EGfxColor_Black);
}


void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}