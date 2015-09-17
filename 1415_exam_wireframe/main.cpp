#include "flib.h"
#include "build_geometries.h"
#include "geometry.h"
#include "menu.h"

TGfxSprite * g_pLineSprite;
TGfxSprite * g_pLabelSprite;
TGeometry g_tGeometry;

#define MESHINFO(name) struct T ## name ## InfoFull : T ## name ## Info { const char * g_pName = #name; } g_t ## name ## Info
MESHINFO(Gear);
MESHINFO(Clock);
MESHINFO(ChessTower);
#undef MESHINFO

int g_iCurrentMenuIndex;

TMenu MenuGear()
{
	TMenu tMenu(g_tGearInfo.g_pName);
	tMenu.AddOption("teeth count", g_tGearInfo.m_iTeethCount, 16, 8, 32);
	tMenu.AddOption("teeth depth", g_tGearInfo.m_fTeethDepth, 1 / 16.0f, 0, 1 / 4.0f, 1 / 32.0f);
	return tMenu;
}

TMenu MenuClock()
{
	TMenu tMenu(g_tClockInfo.g_pName);
	tMenu.AddOption("hours", g_tClockInfo.m_iHours, 10, 0, 11);
	tMenu.AddOption("minutes", g_tClockInfo.m_iMinutes, 10, 0, 59);
	tMenu.AddOption("angle X", g_tClockInfo.m_iAngleX, 0, 0, 90, 5);
	return tMenu;
}

TMenu MenuChessTower()
{
	TMenu tMenu(g_tChessTowerInfo.g_pName);
	tMenu.AddOption("segments", g_tChessTowerInfo.m_iSegments, 12, 8, 36, 2);
	tMenu.AddOption("radius", g_tChessTowerInfo.m_fRadius, 0.5f, 1 / 16.0f, 1.0f, 1 / 32.0f);
	tMenu.AddOption("height", g_tChessTowerInfo.m_fHeight, 1.0f, 1 / 16.0f, 1.0f, 1 / 32.0f);
	return tMenu;
}

TMenu g_pMenu[] = {
	MenuGear(),
	MenuClock(),
	MenuChessTower(),
};

void UpdateGeometry()
{
	g_tGeometry.Clear();
	BuildBox(g_tGeometry);

	const TMenu & tMenu = g_pMenu[g_iCurrentMenuIndex];

#define MENUOPTION(name) if (tMenu.GetName() == g_t ## name ## Info.g_pName) Build ## name(g_tGeometry, g_t ## name ## Info)
	MENUOPTION(Gear);
	MENUOPTION(Clock);
	MENUOPTION(ChessTower);
#undef MENUOPTION

	GfxTextSpritePrintf(g_pLabelSprite, "%s - %d lines", tMenu.GetName(), g_tGeometry.GetLineCount());
	GfxSpriteSetPivot(g_pLabelSprite, static_cast<float>(GfxSpriteGetSizeX(g_pLabelSprite) / 2), static_cast<float>(GfxSpriteGetSizeY(g_pLabelSprite)));
	GfxSpriteSetPosition(g_pLabelSprite, static_cast<float>(GfxGetDisplaySizeX() / 2), static_cast<float>(GfxGetDisplaySizeY()));
}

void Initialize()
{
	g_pLineSprite = GfxLineSpriteCreate();
	GfxSpriteSetPosition(g_pLineSprite, 480 / 2, 272 / 2);
	GfxSpriteSetScale(g_pLineSprite, 100, -100);

	g_pLabelSprite = GfxTextSpriteCreate();
	UpdateGeometry();
}

void Update()
{
	const int iOldMenuIndex = g_iCurrentMenuIndex;

	if (GfxInputIsJustPressed(EGfxInputID_AnyPadShoulderL) || GfxInputIsJustPressed(EGfxInputID_KeyShift))
	{
		g_iCurrentMenuIndex--;
	}

	if (GfxInputIsJustPressed(EGfxInputID_AnyPadShoulderR) || GfxInputIsJustPressed(EGfxInputID_KeyControl) || GfxInputIsJustPressed(EGfxInputID_MouseLeft))
	{
		g_iCurrentMenuIndex++;
	}

	const int iMenuCount = sizeof(g_pMenu) / sizeof(g_pMenu[0]);
	g_iCurrentMenuIndex = (g_iCurrentMenuIndex + iMenuCount) % iMenuCount;

	if (g_pMenu[g_iCurrentMenuIndex].Update() || g_iCurrentMenuIndex != iOldMenuIndex)
	{
		UpdateGeometry();
	}

	GfxLineSpriteReset(g_pLineSprite);
	g_tGeometry.Render(g_pLineSprite);
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_pLineSprite);
	g_pMenu[g_iCurrentMenuIndex].Render();
	GfxSpriteRender(g_pLabelSprite);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}
