#include "global.h"
#include "floor.h"
#include "ray.h"
#include <math.h>
#include <float.h>
#include "sphere.h"

struct TRay;

bool TPlan::Collision(const TRay & tRay) const
{
	float fSmallLength = (tRay.m_tDir.DotProduct(-m_tNormal));
	float fLongLength = ((m_tPosition - tRay.m_tSrc).DotProduct(-m_tNormal));
	float fRatio = (fLongLength / fSmallLength);

	if (fRatio > 0)
	{
		return true;
	}

	return false;
}


unsigned int TPlan::Shade(const TRay & tRay, const TGfxVec3 & tLight, const TSphere & tSphere ) const
{
	//TGfxVec3 tCamToPlan = (m_tPosition - tRay.m_tSrc);
	//float fDotDirNorm = (tRay.m_tDir.DotProduct(-m_tNormal));
	//float fDotToPlane = (tCamToPlan.DotProduct(-m_tNormal));
	//float fRatio = (fDotToPlane / fDotDirNorm);
	//TGfxVec3 tCamToCol = (fRatio * tRay.m_tDir);
	//TGfxVec3 tColToLight = tLight - (tCamToCol + tRay.m_tSrc);
	//TGfxVec3 tColToLightNorm = tColToLight.Normalize();
	//
	//TRay tRayColToLight;
	//
	//tRayColToLight.m_tSrc = tColToLight;
	//tRayColToLight.m_tDir = tColToLightNorm;
	//
	//float fCol = tSphere.Collision(tRayColToLight);
	//
	//if (fCol < FLT_MAX)
	//{
	//	return GfxColor(0, 0, 0, 255);
	//}
	//else
	//{
	//	return GfxColor(255, 255, 255, 255);
	//}
		return GfxColor(255, 255, 255, 255);
}