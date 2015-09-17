#include "flib.h"

#define STR_INT_VAR( varName ) \
	(#varName": %d\n"),varName  // Le "\" permet de faire de deux lignes une ligne

#define USE_VAR(varName , suffix ) varName##_##suffix   // Le double ## concatene.
#define DECLARE_VAR(type, varName , suffix ) type USE_VAR(varName , suffix) // Ces 3 defines sont enfait des macros !
#define DEBUG_VAR(varName) GfxDbgPrintf(STR_INT_VAR(g_iMyVariable));

int g_iMyVariable;


void Initialize()
{
	g_iMyVariable = 666;
}

void Update()
{
	DECLARE_VAR(int, local, win32) = 42;  //

	GfxDbgPrintf("=> %d\n", USE_VAR(local, win32));

	//GfxDbgPrintf(STR_INT_VAR(g_iMyVariable));
	DEBUG_VAR(g_iMyVariable);
	GfxDbgPrintf("File: %s\nLine: %d\nDate: %s\n", __FILE__, __LINE__, __DATE__);
}

void Render()
{
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
