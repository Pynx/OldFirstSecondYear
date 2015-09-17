#include "build_geometries.h"
#include "geometry.h"
#include "flib.h"
#include <math.h>

void BuildBox(TGeometry & tGeometry)
{
	tGeometry.AddLine(TGfxVec3(-1, -1, -1), TGfxVec3(1, 1, -1), GfxColor(63, 63, 63, 255));
	tGeometry.AddLine(TGfxVec3(-1, 1, -1), TGfxVec3(1, -1, -1), GfxColor(63, 63, 63, 255));

	tGeometry.AddLine(TGfxVec3(1, 1, 1), TGfxVec3(-1, 1, 1));
	tGeometry.AddLine(TGfxVec3(-1, 1, 1), TGfxVec3(-1, -1, 1));
	tGeometry.AddLine(TGfxVec3(-1, -1, 1), TGfxVec3(1, -1, 1));
	tGeometry.AddLine(TGfxVec3(1, -1, 1), TGfxVec3(1, 1, 1));

	tGeometry.AddLine(TGfxVec3(1, 1, -1), TGfxVec3(-1, 1, -1));
	tGeometry.AddLine(TGfxVec3(-1, 1, -1), TGfxVec3(-1, -1, -1));
	tGeometry.AddLine(TGfxVec3(-1, -1, -1), TGfxVec3(1, -1, -1));
	tGeometry.AddLine(TGfxVec3(1, -1, -1), TGfxVec3(1, 1, -1));

	tGeometry.AddLine(TGfxVec3(1, 1, 1), TGfxVec3(1, 1, -1));
	tGeometry.AddLine(TGfxVec3(-1, 1, 1), TGfxVec3(-1, 1, -1));
	tGeometry.AddLine(TGfxVec3(-1, -1, 1), TGfxVec3(-1, -1, -1));
	tGeometry.AddLine(TGfxVec3(1, -1, 1), TGfxVec3(1, -1, -1));
}

void BuildGear(TGeometry & tGeometry, const TGearInfo & tInfo)
{
	//tInfo.m_fTeethDepth;
	//tInfo.m_iTeethCount;

	const float fDepth = 1 - tInfo.m_fTeethDepth;

	float fX = 0;
	float fY = 0;
	float fOldX = 1.0f;
	float fOldY = 0;
	

	for (int i = 0; i < 19; i++)
	{
		float fTemp = GfxMathDegToRad((float(i * 20)));
		fX = cos(fTemp);
		fY = sin(fTemp);
		tGeometry.AddLine(TGfxVec3(fOldX/3, fOldY/3, 0), TGfxVec3(fX/3, fY/3, 0));
		fOldX = fX;
		fOldY = fY;
	}
	
	bool bIsTeeth = true;
	int iTeethNbr = 0;

	for (int i = 0; i < ((tInfo.m_iTeethCount*4)+1); i++)
	{
		if (iTeethNbr>1)
		{
			if (bIsTeeth == true)
			{
				bIsTeeth = false;
			}
			else if(bIsTeeth == false)
			{
				bIsTeeth = true;
			}
			iTeethNbr = 0;
		}

		float fTemp = GfxMathDegToRad(i * (360.0f / (tInfo.m_iTeethCount * 4)));
		fX = cos(fTemp);
		fY = sin(fTemp);
		if (bIsTeeth == true)
		{
			tGeometry.AddLine(TGfxVec3(fOldX, fOldY, 0), TGfxVec3(fX, fY, 0));
			fOldX = fX;
			fOldY = fY;
		}
		else
		{
			tGeometry.AddLine(TGfxVec3(fOldX, fOldY, 0), TGfxVec3(fX * fDepth, fY * fDepth, 0));
			fOldX = fX*fDepth;
			fOldY = fY*fDepth;
		}

		iTeethNbr++;
	}
}

void BuildClock(TGeometry & tGeometry, const TClockInfo & tInfo)
{
	float fX = 0;
	float fY = 0;
	float fOldX = 1.0f;
	float fOldY = 0;

	int iCpt = 0;

	for (int i = 0; i < 61; i++)
	{
		float fTemp = GfxMathDegToRad(float(i * 6));
		fX = cos(fTemp);
		fY = sin(fTemp);
		tGeometry.AddLine(TGfxVec3(fOldX, fOldY, 0), TGfxVec3(fX, fY, 0));
		if (iCpt == 0)
		{
			tGeometry.AddLine(TGfxVec3(fX, fY, 0), TGfxVec3(fX*0.8f, fY*0.8f, 0));
			iCpt++;
		}
		else
		{
			if (iCpt == 5 || iCpt == 10)
			{
				tGeometry.AddLine(TGfxVec3(fX, fY, 0), TGfxVec3(fX*0.9f, fY*0.9f, 0));
			}
			else
			{
				tGeometry.AddLine(TGfxVec3(fX, fY, 0), TGfxVec3(fX*0.95f, fY*0.95f, 0));
			}

			iCpt++;

			if (iCpt == 15)
			{
				iCpt = 0;
			}
		}
		fOldX = fX;
		fOldY = fY;
	}

	const int iHours = tInfo.m_iHours;

	const int iMinutes = tInfo.m_iMinutes;

	const int iAngle = -90 + (iHours * 30);

	const int iAngleMinutes = 90 - (iMinutes * 6);

	const float fTemp = GfxMathDegToRad(float(iAngle));
	const float fTempLeft = GfxMathDegToRad(float(iAngle - 60));
	const float fTempRight = GfxMathDegToRad(float(iAngle + 60));

	const float fTempMin = GfxMathDegToRad(float(iAngleMinutes));
	const float fTempLeftMin = GfxMathDegToRad(float(iAngleMinutes - 60));
	const float fTempRightMin = GfxMathDegToRad(float(iAngleMinutes + 60));

	fX = cos(fTemp);
	fY = sin(fTemp);
	const float fXLeft = cos(fTempLeft);
	const float fYLeft = sin(fTempLeft);
	const float fXRight = cos(fTempRight);
	const float fYRight = sin(fTempRight);

	const float fXMin = cos(fTempMin);
	const float fYMin = sin(fTempMin);
	const float fXLeftMin = cos(fTempLeftMin);
	const float fYLeftMin = sin(fTempLeftMin);
	const float fXRightMin = cos(fTempRightMin);
	const float fYRightMin = sin(fTempRightMin);

	tGeometry.AddLine(TGfxVec3(0, 0, 0), TGfxVec3(fXLeft / 10, -fYLeft / 10, 0));
	tGeometry.AddLine(TGfxVec3(0, 0, 0), TGfxVec3(fXRight / 10, -fYRight / 10, 0));
	tGeometry.AddLine(TGfxVec3(fXRight / 10, -fYRight / 10, 0), TGfxVec3(fX / 3, -fY / 3, 0));
	tGeometry.AddLine(TGfxVec3(fXLeft / 10, -fYLeft / 10, 0), TGfxVec3(fX / 3, -fY / 3, 0));

	tGeometry.AddLine(TGfxVec3(0, 0, 0), TGfxVec3(fXLeftMin / 10, fYLeftMin / 10, 0));
	tGeometry.AddLine(TGfxVec3(0, 0, 0), TGfxVec3(fXRightMin / 10, fYRightMin / 10, 0));
	tGeometry.AddLine(TGfxVec3(fXRightMin / 10, fYRightMin / 10, 0), TGfxVec3(fXMin / 2, fYMin / 2, 0));
	tGeometry.AddLine(TGfxVec3(fXLeftMin / 10, fYLeftMin / 10, 0), TGfxVec3(fXMin / 2, fYMin / 2, 0));
}

void BuildChessTower(TGeometry & tGeometry, const TChessTowerInfo & tInfo)
{	
	TGfxVec3 tLevelZeroPosition[36];
	TGfxVec3 tLevelOnePosition[36];
	TGfxVec3 tLevelTwoPosition[36];
	TGfxVec3 tLevelThreePosition[36];
	TGfxVec3 tLevelFourPosition[36];
	TGfxVec3 tLevelFivePosition[36];
	TGfxVec3 tLevelSixPosition[36];
	TGfxVec3 tLevelSevenPosition[36];
	TGfxVec3 tLevelHeightPosition[36];
	TGfxVec3 tLevelNinePosition[36];
	TGfxVec3 tLevelTenPosition[36];
	TGfxVec3 tLevelElevenPosition[36];

	float fHeightFromBottomTableau[12]; // Tableau de nombres magiques suivant approximativement les hauteurs de l'exercice
	fHeightFromBottomTableau[0] = 0.0f;
	fHeightFromBottomTableau[1] = 0.0f;
	fHeightFromBottomTableau[2] = 0.2f;
	fHeightFromBottomTableau[3] = 0.2f;
	fHeightFromBottomTableau[4] = 0.4f;
	fHeightFromBottomTableau[5] = 0.6f;
	fHeightFromBottomTableau[6] = 1.4f;
	fHeightFromBottomTableau[7] = 1.6f;
	fHeightFromBottomTableau[8] = 2.0f;
	fHeightFromBottomTableau[9] = 2.0f;
	fHeightFromBottomTableau[10] = 1.6f;
	fHeightFromBottomTableau[11] = 1.6f;

	float fWidthTableau[12]; // Tableau de nombres magiques suivant approximativement les largeurs de l'exercice
	fWidthTableau[0] = 0.0f;
	fWidthTableau[1] = 1.0f;
	fWidthTableau[2] = 1.0f;
	fWidthTableau[3] = 0.8f;
	fWidthTableau[4] = 0.8f;
	fWidthTableau[5] = 0.6f;
	fWidthTableau[6] = 0.6f;
	fWidthTableau[7] = 0.8f;
	fWidthTableau[8] = 0.8f;
	fWidthTableau[9] = 0.6f;
	fWidthTableau[10] = 0.6f;
	fWidthTableau[11] = 0.0f;

	float fX = 0;
	float fY = 0;

	for (int i = 0; i < tInfo.m_iSegments; i++)
	{
		tLevelZeroPosition[i] = TGfxVec3(0.0f,-1.0f,0.0f);
	}

	for (int i = 0; i < tInfo.m_iSegments; i++)
	{
		float fTemp = GfxMathDegToRad(i * (360.0f / (tInfo.m_iSegments)));
		fX = cos(fTemp);
		fY = sin(fTemp);

		tLevelOnePosition[i] = TGfxVec3((fX*fWidthTableau[1])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[1] * tInfo.m_fHeight), (fY*fWidthTableau[1])* tInfo.m_fRadius);
		tLevelTwoPosition[i] = TGfxVec3((fX*fWidthTableau[2])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[2] * tInfo.m_fHeight), (fY*fWidthTableau[2])* tInfo.m_fRadius);
		tLevelThreePosition[i] = TGfxVec3((fX*fWidthTableau[3])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[3] * tInfo.m_fHeight), (fY*fWidthTableau[3])* tInfo.m_fRadius);
		tLevelFourPosition[i] = TGfxVec3((fX*fWidthTableau[4])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[4] * tInfo.m_fHeight), (fY*fWidthTableau[4])* tInfo.m_fRadius);
		tLevelFivePosition[i] = TGfxVec3((fX*fWidthTableau[5])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[5] * tInfo.m_fHeight), (fY*fWidthTableau[5])* tInfo.m_fRadius);
		tLevelSixPosition[i] = TGfxVec3((fX*fWidthTableau[6])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[6] * tInfo.m_fHeight), (fY*fWidthTableau[6])* tInfo.m_fRadius);
		tLevelSevenPosition[i] = TGfxVec3((fX*fWidthTableau[7])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[7] * tInfo.m_fHeight), (fY*fWidthTableau[7])* tInfo.m_fRadius);
		tLevelHeightPosition[i] = TGfxVec3((fX*fWidthTableau[8])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[8] * tInfo.m_fHeight), (fY*fWidthTableau[8])* tInfo.m_fRadius);
		tLevelNinePosition[i] = TGfxVec3((fX*fWidthTableau[9])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[9] * tInfo.m_fHeight), (fY*fWidthTableau[9])* tInfo.m_fRadius);
		tLevelTenPosition[i] = TGfxVec3((fX*fWidthTableau[10])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[10] * tInfo.m_fHeight), (fY*fWidthTableau[10])* tInfo.m_fRadius);
		tLevelElevenPosition[i] = TGfxVec3((fX*fWidthTableau[11])*tInfo.m_fRadius, -1.0f + (fHeightFromBottomTableau[11] * tInfo.m_fHeight), (fY*fWidthTableau[11])* tInfo.m_fRadius);
	}
	
	for (int i = 0; i < tInfo.m_iSegments; i++)
	{
		tGeometry.AddLine(tLevelZeroPosition[i], tLevelOnePosition[i]);
		tGeometry.AddLine(tLevelOnePosition[i], tLevelTwoPosition[i]);
		tGeometry.AddLine(tLevelTwoPosition[i], tLevelThreePosition[i]);
		tGeometry.AddLine(tLevelThreePosition[i], tLevelFourPosition[i]);
		tGeometry.AddLine(tLevelFourPosition[i], tLevelFivePosition[i]);
		tGeometry.AddLine(tLevelFivePosition[i], tLevelSixPosition[i]);
		tGeometry.AddLine(tLevelSixPosition[i], tLevelSevenPosition[i]);
		tGeometry.AddLine(tLevelSevenPosition[i], tLevelHeightPosition[i]);
		tGeometry.AddLine(tLevelHeightPosition[i], tLevelNinePosition[i]);
		tGeometry.AddLine(tLevelNinePosition[i], tLevelTenPosition[i]);
		tGeometry.AddLine(tLevelTenPosition[i], tLevelElevenPosition[i]);
	}


	for (int i = 0; i < tInfo.m_iSegments; i++)
	{
		if (i == tInfo.m_iSegments - 1)
		{
			tGeometry.AddLine(tLevelOnePosition[i], tLevelOnePosition[0]);
			tGeometry.AddLine(tLevelTwoPosition[i], tLevelTwoPosition[0]);
			tGeometry.AddLine(tLevelThreePosition[i], tLevelThreePosition[0]);
			tGeometry.AddLine(tLevelFourPosition[i], tLevelFourPosition[0]);
			tGeometry.AddLine(tLevelFivePosition[i], tLevelFivePosition[0]);
			tGeometry.AddLine(tLevelSixPosition[i], tLevelSixPosition[0]);
			tGeometry.AddLine(tLevelSevenPosition[i], tLevelSevenPosition[0]);
			tGeometry.AddLine(tLevelHeightPosition[i], tLevelHeightPosition[0]);
			tGeometry.AddLine(tLevelNinePosition[i], tLevelNinePosition[0]);
			tGeometry.AddLine(tLevelTenPosition[i], tLevelTenPosition[0]);
		}
		else
		{
			tGeometry.AddLine(tLevelOnePosition[i], tLevelOnePosition[i + 1]);
			tGeometry.AddLine(tLevelTwoPosition[i], tLevelTwoPosition[i + 1]);
			tGeometry.AddLine(tLevelThreePosition[i], tLevelThreePosition[i + 1]);
			tGeometry.AddLine(tLevelFourPosition[i], tLevelFourPosition[i + 1]);
			tGeometry.AddLine(tLevelFivePosition[i], tLevelFivePosition[i + 1]);
			tGeometry.AddLine(tLevelSixPosition[i], tLevelSixPosition[i + 1]);
			tGeometry.AddLine(tLevelSevenPosition[i], tLevelSevenPosition[i + 1]);
			tGeometry.AddLine(tLevelHeightPosition[i], tLevelHeightPosition[i + 1]);
			tGeometry.AddLine(tLevelNinePosition[i], tLevelNinePosition[i + 1]);
			tGeometry.AddLine(tLevelTenPosition[i], tLevelTenPosition[i + 1]);
		}
	}
}
