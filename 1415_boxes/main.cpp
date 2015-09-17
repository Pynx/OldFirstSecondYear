#include "flib.h"
#include "flib_vec2.h" // Il faut cliquer sur le projet, faire add, existing item et trouver dans main/lib le fichier flib_vec2.cpp pour pouvoir remplacer une structure avec deux variable en un TGfxVec2
#include <math.h>

TGfxSprite * g_pLines;
float g_pAngle = 0;
bool Project = true;
const int g_iNbrX = 10;
const int g_iNbrY = 10;
int g_iMouseX = 0;
int g_iMouseY = 0;



void DrawCircle(TGfxSprite * pLines, const TGfxVec2 tCenter, const float fRadius)
{
	// Test OK
	/*const int NUM_SEGMENTS = 20;
	float fAngle = 0;
	// Prendre des lignes, plein de petite ligne pour faire un cercle mais avec plein de cassure, il faut des petites lignes (changer le nbr de ligne facilement)

	GfxLineSpriteJumpTo(pLines, fCenterX + fRadius, fCenterY);

	float fCosinus = cos(fAngle); // donnne un angle en radiant, et rend la coord X d'un point qui de trouve sur le cercle de taille 1 à l'angle qu'on lui à donné
	float fSinus = sin(fAngle);

	for (int i = 0; i < NUM_SEGMENTS + 1; i++)
	{
	fAngle = i * (360.f / NUM_SEGMENTS);
	fAngle = GfxMathDegToRad(fAngle);
	fCosinus = cos(fAngle); // donnne un angle en radiant, et rend la coord X d'un point qui de trouve sur le cercle de taille 1 à l'angle qu'on lui à donné
	fSinus = sin(fAngle);
	GfxLineSpriteLineTo(pLines, fCenterX + (fCosinus * fRadius), fCenterY + (fSinus * fRadius));
	}*/

	//Correction
	const int NUM_LINES = 32;
	GfxLineSpriteJumpTo(pLines, tCenter.x + fRadius, tCenter.y);

	for (int i = 0; i < NUM_LINES; ++i)
	{
		const float fAngle = GfxMathDegToRad((360.f / NUM_LINES) * (i + 1));
		const float fPosX = tCenter.x + cos(fAngle) * fRadius;
		const float fPosY = tCenter.y + sin(fAngle) * fRadius;
		GfxLineSpriteLineTo(pLines, fPosX, fPosY);
	}
}
void DrawArrow(TGfxSprite * pLines, const TGfxVec2 tCenter, TGfxVec2 tDest, const bool Norm)
{
	if (!(tDest == tCenter))
	{
		TGfxVec2 pArrow = 15 * (tDest - tCenter).Normalize();
		const float angle = GfxMathDegToRad(160);
		TGfxVec2 pArrow1 = pArrow.Rotate(angle);
		TGfxVec2 pArrow2 = pArrow.Rotate(-angle);

		GfxLineSpriteJumpTo(pLines, tCenter.x, tCenter.y);
		GfxLineSpriteLineTo(pLines, tDest.x, tDest.y);
		GfxLineSpriteLineTo(pLines, tDest.x + pArrow1.x, tDest.y + pArrow1.y);
		GfxLineSpriteJumpTo(pLines, tDest.x, tDest.y);
		GfxLineSpriteLineTo(pLines, tDest.x + pArrow2.x, tDest.y + pArrow2.y);

	}
}
// Si trop de paramètre dans la fonction -> Met dans une structure
void DrawBox(TGfxSprite * pLines, const TGfxVec2 tCenter, const TGfxVec2 tRadius, const float fAngle) // tRadius => Un en x pour les côtés verticale, et un pour le y pour le côté horizontale
{


	//Boite si angle = 0, par rapport au centre, la faire bouger, ensuite angle

	float fRotation = GfxMathDegToRad(fAngle);
	float fCos = cos(fRotation);
	float fSin = sin(fRotation);

	// Pos de base

	TGfxVec2 tAxisX = TGfxVec2(tRadius.x, 0).Rotate(fAngle);
	TGfxVec2 tAxisY = TGfxVec2(0, tRadius.y).Rotate(fAngle);

	// OLD ---> TGfxVec2 tAxisX(tRadius.x * cos(fAngle), tRadius.x * sin(fAngle));
	// OLD ---> TGfxVec2 tAxisY(tRadius.y * -sin(fAngle), tRadius.y * cos(fAngle));

	/*TGfxVec2 tUR(tCenter.x + tRadius.x, tCenter.y + tRadius.y);//HD
	TGfxVec2 tUL(tCenter.x - tRadius.x, tCenter.y + tRadius.y);//HG
	TGfxVec2 tBL(tCenter.x - tRadius.x, tCenter.y - tRadius.y);//BG
	TGfxVec2 tBR(tCenter.x + tRadius.x, tCenter.y - tRadius.y);//BD*/

	const TGfxVec2 tUR = tCenter + tAxisX + tAxisY; // C + X + Y
	const TGfxVec2 tUL = tCenter - tAxisX + tAxisY; // C - X + Y
	const TGfxVec2 tBL = tCenter - tAxisX - tAxisY; // C - X - Y
	const TGfxVec2 tBR = tCenter + tAxisX - tAxisY; // C + X - Y

	GfxLineSpriteJumpTo(pLines, tUR.x, tUR.y);
	GfxLineSpriteLineTo(pLines, tUL.x, tUL.y);
	GfxLineSpriteLineTo(pLines, tBL.x, tBL.y);
	GfxLineSpriteLineTo(pLines, tBR.x, tBR.y);
	GfxLineSpriteLineTo(pLines, tUR.x, tUR.y);

	// Pas préci au pixel près
	GfxLineSpriteSetDrawingColor(pLines, EGfxColor_Red);
	DrawArrow(pLines, tCenter, tCenter + tAxisX, false);
	GfxLineSpriteSetDrawingColor(pLines, EGfxColor_Green);
	DrawArrow(pLines, tCenter, tCenter + tAxisY, false);
	//DrawArrow(pLine, tCenter, tCenter + tAxisX);
	//DrawArrow(pLine, tCenter, tCenter + tAxisY);
	//tCenter.Normalize();
	//tCenter.Rotate();

	/*
	GfxLineSpriteJumpTo(Lines, tCenter.x + tRadius.x, tCenter.y + tRadius.y);
	GfxLineSpriteLineTo(Lines, tCenter.x + tRadius.x, tCenter.y - tRadius.y);
	GfxLineSpriteLineTo(Lines, tCenter.x - tRadius.x, tCenter.y - tRadius.y);
	GfxLineSpriteLineTo(Lines, tCenter.x - tRadius.x, tCenter.y + tRadius.y);
	GfxLineSpriteLineTo(Lines, tCenter.x + tRadius.x, tCenter.y + tRadius.y);
	*/
}



void Initialize()
{
	g_pLines = GfxLineSpriteCreate();
	//GfxLineSpriteJumpTo(g_pLines, 100, 50); // Point de départ à la destination sans tracé de ligne
	//GfxLineSpriteLineTo(g_pLines, 100, 50); // Poit de départ à l'arrivée en traçant une ligne
	// Chaque fois qu'on déssine par du point d'avant, et 0,0 au début

	//GfxSpriteSetScale(g_pLines, 4, 4); // Ici ligne toujours d'un pixel mais + longue
	GfxSpriteSetScale(g_pLines, 1, -1); // Inverser la coordoné Y pour être dans les axes de math habituelle
	GfxSpriteSetPosition(g_pLines, GfxGetDisplaySizeX() / 2.0f, GfxGetDisplaySizeY() / 2.0f);// Changer l'origine et la mettre au centre   
}


void Update()
{
	// Changement de couleur
	/*if (GfxInputIsPressed(EGfxInputID_MouseLeft)) // Quand souri enfoncé, c'est vert
	{
	GfxLineSpriteSetDrawingColor(g_pLines, EGfxColor_Green);// Changer la couleur de la ligne de manière individuelle, changer la couleur avt de traser la ligne
	}
	else
	{
	GfxLineSpriteSetDrawingColor(g_pLines, EGfxColor_Red);// Changer la couleur de la ligne
	}

	if (GfxInputIsPressed(EGfxInputID_MouseLeft))
	{
	GfxSpriteSetColor(g_pLines, EGfxColor_Green);// Change la couleur par laquelle le sprite et multiplier
	}
	else
	{
	GfxSpriteSetColor(g_pLines, EGfxColor_Red);
	}*/

	// Dessin à la souris, à chaque frame dessine et retient tout
	/*
	const int iMouseX = GfxGetCurrentMouseX() - GfxGetDisplaySizeX() / 2; // Force les coordonée de la souri
	const int iMouseY = -(GfxGetCurrentMouseY() - GfxGetDisplaySizeY() / 2);
	GfxLineSpriteJumpTo(g_pLines, 0, 0); // Ici on force le point de départ à 0,0
	GfxLineSpriteLineTo(g_pLines, iMouseX, iMouseY);*/

	if (GfxInputIsPressed(EGfxInputID_MouseRight))
	{
		g_pAngle = g_pAngle + 0.1f;
	}


	GfxLineSpriteReset(g_pLines); // Oublie toute les ligne déjà déssiner et repart de 0
	// PLus performant que de supprimer et recréer

	const int iMouseX = GfxGetCurrentMouseX() - GfxGetDisplaySizeX() / 2;
	const int iMouseY = -(GfxGetCurrentMouseY() - GfxGetDisplaySizeY() / 2);

	if (Project == true)
	{
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(-80)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(-40)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(0)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(40)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(80)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-200), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-160), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-120), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-80), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-40), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(0), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(40), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(80), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(120), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(160), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(80)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(40)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(0)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(-40)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(-80)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(200), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(160), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(120), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(80), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(40), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(0), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-40), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-80), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-120), float(-120)), 20);
		DrawCircle(g_pLines, TGfxVec2(float(-160), float(-120)), 20);

		//GfxLineSpriteReset(g_pLines);
		if (GfxInputIsPressed(EGfxInputID_MouseLeft))
		{
			DrawBox(g_pLines, TGfxVec2(float(iMouseX), float(iMouseY)), TGfxVec2(float(30), float(50)), g_pAngle);
			g_iMouseX = iMouseX; 
			g_iMouseY = iMouseY;
		}
		else
		{
			DrawBox(g_pLines, TGfxVec2(float(g_iMouseX), float(g_iMouseY)), TGfxVec2(float(30), float(50)), g_pAngle);
		}
		//DrawArrow(g_pLines, TGfxVec2(float(iMouseX), float(iMouseY)), TGfxVec2(float(30), float(50)), g_pAngle);
		//DrawArrow(g_pLines, TGfxVec2(float(iMouseX), float(iMouseY)), TGfxVec2(float(30), float(50)));
	}
	else
	{
		int iDispSizeY = GfxGetDisplaySizeY();
		int iDispSizeX = GfxGetDisplaySizeX();
		int iPosY = +(iDispSizeY / 2);
		int iPosX = -(iDispSizeX / 2);
		for (int i = 0; i < g_iNbrY; i++)
		{
			iPosY -= (iDispSizeY / (g_iNbrY + 1));
			iPosX = -(iDispSizeX / 2);
			for (int e = 0; e < g_iNbrX; e++)
			{
				iPosX += (iDispSizeX / (g_iNbrX + 1));
				const TGfxVec2 tTemp = TGfxVec2(iPosX, iPosY) - TGfxVec2(float(iMouseX), float(iMouseY));
				if (tTemp != TGfxVec2(0, 0))
				{
					DrawArrow(g_pLines, TGfxVec2(iPosX, iPosY), TGfxVec2(iPosX, iPosY) + tTemp.Normalize() * 25, true);
				}
			}
		}
		iPosX = -(iDispSizeX / 2);
		iPosY = +(iDispSizeY / 2);
	}
}

void Render()
{
	GfxClear(EGfxColor_Black);
	GfxSpriteRender(g_pLines);
}

void GfxMain(int, char *[])
{
	GfxCallbacks(Initialize, Update, Render);
}