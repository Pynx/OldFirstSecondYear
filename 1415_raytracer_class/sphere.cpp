#include "sphere.h"
#include <math.h>
#include <float.h>
#include "flib.h"

float Hypotenus(float A, float B)
{
	return sqrtf((pow(A, 2) - pow(B, 2)));
}

float TSphere::Collision(TRay & tRay) const
{
	float fRadius = 1.0f;

	const TGfxVec3 tCameraToObject = m_tPosition - tRay.m_tSrc; // Vecteur entre la caméra et le centre de la sphère

	float fLength = tCameraToObject.DotProduct(tRay.m_tDir); // Longeur entre la caméra et le point le plus proche de la sphère sur le rayon

	TGfxVec3 tNearestPoint = (tRay.m_tDir * fLength); // Point le plus proche de la sphère sur le rayon

	if (fLength < 0) // N'affiche pas ce qu'il y a dérière la caméra
	{
		return FLT_MAX;
	}

	float fColisionDistance = (tNearestPoint - tCameraToObject).SquaredLength();

	if (fLength < 0) return FLT_MAX;

	if (fColisionDistance < fRadius) // Point le plus proche - le centre de la shpère.Length() => calcule l'hypoténus
	{

		float fDistNandColision = Hypotenus(fRadius, fColisionDistance); // Calcule la distance entre N et le poitn de colision
		float fDistCameraToColision = fLength - fDistNandColision; // Calcule la distance entre la point source et le point de colision

		return fDistCameraToColision;
	}
	return FLT_MAX;
}

unsigned int TSphere::Shade(TRay & tRay, const TGfxVec3 tLight, float fDistance) const
{

	TGfxVec3 tHit = tRay.m_tSrc + (tRay.m_tDir * fDistance);
	TGfxVec3 tNormale = (tHit - m_tPosition).Normalize(); // Trouver le point de colison
	TGfxVec3 tFromLight = (tHit - tLight).Normalize();

	float fAngle = - (tFromLight.DotProduct(tNormale)); //Trouver angle entre la normale et le rayon
	
	float fAmbiant = 0.1f;

	// Clamp
	if (fAngle < fAmbiant)
	{
		fAngle = fAmbiant;
	}

	// Diffuse

	TGfxVec3 tColor = m_tColor;

	tColor *= fAngle;

	if (tColor.x > 255) tColor.x = 255;
	if (tColor.x < 0) tColor.x = 0;

	if (tColor.y > 255) tColor.y = 255;
	if (tColor.y < 0) tColor.y = 0;

	if (tColor.z > 255) tColor.z = 255;
	if (tColor.z < 0) tColor.z = 0;

	return GfxColor(tColor.x, tColor.y, tColor.z, 255);
}

/*
//Changer couleur sans problème
float fLight = 0.5f;

unsigned int iBaseColor = EGfxColor_Green;

//Adresse de iBaseColor. On caste iBaseColor qqch de vraiment différent, adresse de 32 bits changer en adresse de 8    et donc la 1er coueur
reinterpret_cast<unsigned char*>(&iBaseColor);

//Avoir toute les couleurs + alpha séparer
unsigned char r = reinterpret_cast<unsigned char*>(&iBaseColor)[0];
unsigned char g = reinterpret_cast<unsigned char*>(&iBaseColor)[1];
unsigned char b = reinterpret_cast<unsigned char*>(&iBaseColor)[2];
unsigned char a = reinterpret_cast<unsigned char*>(&iBaseColor)[3];

//Peut stocker dans un tableau
unsigned char * pRGBA = reinterpret_cast<unsigned char*>(&iBaseColor);

pRGBA[0] = 0xFF; //=255

unsigned int iColor = GfxColor(r * fLight, g * fLight, b * fLight, a);


TGfxVec3 ColToVec(const unsigned int iColor);
unsigned int VecToCol(const TGfxVec3 & tVecor);
TGfxVec3 Lerp(const TGfxVec3 & tVectorA, const TGfxVec3 & tvectorB, const float fDelta);
*/
