#include "camera.h"
#include "ray.h"
#include "flib.h"
#include "sphere.h"
#include "color.h"
#include <float.h>
#include "global.h"
#include "floor.h"

TCamera::TCamera()
	: m_tPosition(0, 0, 0)
	, m_fFOV(GfxMathDegToRad(180))
{
}

void TCamera::Render(TGfxImage * pImage, TSphere * TSphere, TPlan tPlan) const
{
	float AspectRation = float(MAX_COLLONE) / MAX_LINE;
	unsigned int * pData = GfxImageGetData(pImage);
	const int iSizeX = GfxImageGetSizeX(pImage); //Permet de ne de pas rappeler trop de fois
	const int iSizeY = GfxImageGetSizeY(pImage);
	for (int x = 0; x < iSizeX; ++x)
	{
		const float fX = (2 * (float(x) / (iSizeX - 1) - 0.5f)) * AspectRation;

		for (int y = 0; y < iSizeY; ++y)
		{
			const float fY = 2 * (0.5f - float(y) / (iSizeY - 1));

			TRay tRay;
			tRay.m_tSrc = m_tPosition;
			tRay.m_tDir = TGfxVec3(fX, fY, 90.f / m_fFOV).Normalize();

			int iObjectID = -1;
			float fClosestObjectDistance = FLT_MAX;

			for (int i = 0; i < MAX_SPHERES; ++i)
			{
				float fCurrentHit = TSphere[i].Collision(tRay);

				if (fCurrentHit < fClosestObjectDistance)
				{
					fClosestObjectDistance = fCurrentHit;
					iObjectID = i;
				}
			}

			const int iIndex = x + y * iSizeX;

			if (fClosestObjectDistance < FLT_MAX)
			{
				pData[iIndex] = TSphere[iObjectID].Shade(tRay, TGfxVec3(0, 5, 0), fClosestObjectDistance);
			}
			else if (tPlan.Collision(tRay) == true)
			{
				pData[iIndex] = tPlan.Shade(tRay, TGfxVec3(0, 5, 0), TSphere[iObjectID]);
			}
			else 
			{
				pData[iIndex] = BACKGROUND;
			}

			// on commence par FLT_MAX et on passe tout en revue, on rajoute la valeur quand c'est plus proche
		}
	}
}