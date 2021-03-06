#include "geometry.h"
#include "flib_vec2.h"
#include "axes.h"
#include <math.h>

#ifndef M_PI
static const float M_PI = GfxMathDegToRad(180);
#endif

void PerspectiveSegment(TGfxSprite * pSprite, const TGfxVec3 & tSrc, const TGfxVec3 & tDst)
{
	const float fPerspSrc = (-0.5f * tSrc.z + 0.5f);
	const float fPerspDst = (-0.5f * tDst.z + 0.5f);

	GfxLineSpriteJumpTo(pSprite, tSrc.x / fPerspSrc, tSrc.y / fPerspSrc);
	GfxLineSpriteLineTo(pSprite, tDst.x / fPerspDst, tDst.y / fPerspDst);
}

void DrawClipSegment(TGfxSprite * pSprite, const TGfxVec3 & tSrc, const TGfxVec3 & tDst)
{
	const float fNearPlane = -0.25f;

	if (tSrc.z > fNearPlane)
	{
		if (tDst.z >= fNearPlane)
		{
			// completely culled
		}
		else
		{
			// crop tSrc
			const TGfxVec3 tSrcToDst = (tDst - tSrc);
			const float fZSrcToCut = (fNearPlane - tSrc.z);
			const TGfxVec3 tCut = tSrc + (tDst - tSrc) * (fZSrcToCut / tSrcToDst.z);
			PerspectiveSegment(pSprite, tCut, tDst);
		}
	}
	else
	{
		if (tDst.z > fNearPlane)
		{
			// crop tDst
			const TGfxVec3 tDstToSrc = (tSrc - tDst);
			const float fZDstToCut = (fNearPlane - tDst.z);
			const TGfxVec3 tCut = tDst + tDstToSrc * (fZDstToCut / tDstToSrc.z);
			PerspectiveSegment(pSprite, tSrc, tCut);
		}
		else
		{
			// completely visible
			PerspectiveSegment(pSprite, tSrc, tDst);
		}
	}
}

void TGeometry::AddLine(const TGfxVec3 & tPointA, const TGfxVec3 & tPointB, unsigned int iColor)
{
	m_tVertexBuffer.PushBack(tPointA);
	m_tVertexBuffer.PushBack(tPointB);
	m_tColorBuffer.PushBack(iColor);
}

void TGeometry::Render(TGfxSprite * pSprite) const
{
	const float fAngle = GfxMathDegToRad(60 * sin(GfxTimeGetMilliseconds() / 2000.0f));
	TAxes tRotZ = TAxes::CreateYRotation(fAngle).Multiply(TAxes::CreateXRotation(GfxMathDegToRad(22.5f)));

	for (int i = 0; i < m_tVertexBuffer.GetCount();)
	{
		GfxLineSpriteSetDrawingColor(pSprite, m_tColorBuffer[i / 2]);
		const TGfxVec3 tSrc = tRotZ.Multiply(m_tVertexBuffer[i++]) + TGfxVec3(0, 0, -2);
		const TGfxVec3 tDst = tRotZ.Multiply(m_tVertexBuffer[i++]) + TGfxVec3(0, 0, -2);
		DrawClipSegment(pSprite, tSrc, tDst);
	}
}

int TGeometry::GetLineCount() const
{
	return m_tVertexBuffer.GetCount() / 2;
}

void TGeometry::Clear()
{
	m_tVertexBuffer.Clear();
	m_tColorBuffer.Clear();
}
