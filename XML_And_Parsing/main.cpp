#include "flib.h"


TGfxFile * g_tSaveFile = nullptr;

int g_iFileSize;
int g_iCharNumber;

void Initialize()
{

}

void Update()
{
	g_tSaveFile = GfxFileOpenRead("fichier.xml");

	g_iFileSize = (GfxFileSize(g_tSaveFile) + 1);


	g_iCharNumber = 0;

	for (;;)
	{
		const unsigned char cCar = GfxFileReadChar(g_tSaveFile);
		g_iCharNumber++;
	}
}

void Render()
{

}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
