#include "flib.h"
#include <map>




void GfxMain(int, char *[])
{
	std::map<std::string, int> tNum;  // Map créée qui associe à une chaine de caractere, un entier Donc si on utilise la chaine on peux avoir le carac

	tNum["zero"] = 0;
	tNum["one"] = 1;
	tNum["two"] = 2;

	std::map<std::string, int>::const_iterator it;
	for (it = tNum.begin(); it != tNum.end(); ++it)
	{
		GfxDbgPrintf("%s %d\n", it->first.c_str(), it->second);
	}
}











/* PARTIE 2 ---------------------------------------------------------------


#include "flib.h"
#include <vector>
#include <string>

std::string Hello(std::string name)
{
	return std::string("hello ") + name;
}

void GfxMain(int, char *[])
{
	std::vector<int> vec; // Vector = tableau        std:: sert au namespace std et est obligatoire pour appeller les vector
	int iDifference;

	std::string hello = Hello("world"); // Ceci marche super bien mais coute HYPER CHER ! à ne pas utiliser

	

	vec.push_back(123);
	vec.push_back(456);
	vec.push_back(789);

	vec.pop_back(); // delete la derniere case du tableau

	vec[1] = 666; // Remplace la case 1

	GfxDbgPrintf("%d %d \n", vec[0], vec[1]);
	GfxDbgPrintf("%d", vec.size());
	GfxDbgPrintf("%d %d \n", vec.size(), vec.capacity());

	


	vec.reserve(1000);

	for  (int i= 0; i < 1005; i++)
	{
		vec.push_back(i);
		iDifference = (vec.capacity() - vec.size());
		GfxDbgPrintf("ID : %d | SIZE : %d | CAPACITY : %d | Difference : %d\n", vec[i],vec.size(), vec.capacity(), iDifference);
	}
	
	vec.shrink_to_fit();
	iDifference = (vec.capacity() - vec.size());
	GfxDbgPrintf("\n\nID : %d | SIZE : %d | CAPACITY : %d | Difference : %d\n", vec.size()-1, vec.size(), vec.capacity(), iDifference);
}


*/



















/* PARTIE 1 DU COURS --------------------------------------------------------------------------------------------



#include "flib.h"
#include <math.h>

void GfxMain(int, char *[])
{
	/* 4 bits ( nible )

	0000 = 0
	0001
	0010
	0011
	0100
	0101
	0110
	0111 = 7
	1000 = -8
	1001 = -7
	1010 = -6
	1011 = -5
	1100 = -4
	1101 = -3
	1110 = -2
	1111 = -1
	Si on déborde, on recommence à partir de 0 

	

	int a = 2147483647;
	GfxDbgPrintf("%d\n", a);
	a++;
	GfxDbgPrintf("%d\n", a);

	

	int;
	unsigned int;
	short;
	unsigned short;
	char;
	unsigned char;

	


	GfxDbgPrintf("%d\n", sizeof(char));
	GfxDbgPrintf("%u\n", sizeof(short));
	GfxDbgPrintf("%u\n", sizeof(int));
	GfxDbgPrintf("%u\n", sizeof(long));
	GfxDbgPrintf("%u\n", sizeof(long long));



	int i = (1 << 31) - 1;

	float f = i;
	int j = f;

	float f2 = j;
	int k = f2;

	GfxDbgPrintf("%d\n", i);
	GfxDbgPrintf("%d\n", f);
	GfxDbgPrintf("%d\n", j);

	int count = 0;

	for (int i = 0;; ++i)
	{
		const float f = i;
		const int j = f;

		if (i != j)
		{
			GfxDbgPrintf("%d %d\n", i, j);
			++count;
			if (count >= 100) break;
		}
	}

	// Float bug à partir de 16777217

	// Enfait, les 23 premiers bits de droite sont le nombre réel ( en float ), les 8 suivants sont la position de la virgule, et le dernier sert au signe.
	// On doit donc choisir entre précision et taille.
	// Pour avoir un nombre énorme ET précis, il faut le faire avec un double, donc, en somme, deux floats


	// %f = nbr à virgule
	// %g = nbr à virgule, mais démerde toi pour l'afficher

	float r = -1;

	while (r != 0)
	{
		r /= 2;
		GfxDbgPrintf("%g\n", r);
	}

	GfxDbgPrintf("%g\n", f);

	//----------------------------------------------------------

	r = 1;

	while (r != 0)
	{
		float r2 = r * 2;
		if (f2 == f)
		{
			break;
		}
		r = r2;
		GfxDbgPrintf("%g\n", r);
	}

	GfxDbgPrintf("%g\n", r);

	//---------------------------------------------------

	GfxDbgPrintf("%g\n", acos(2.0f));

}


*/