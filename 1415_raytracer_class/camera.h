#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "flib_vec3.h"

struct TGfxImage;
struct TSphere;
struct TPlan;

struct TCamera
{
	TGfxVec3 m_tPosition;
	float m_fFOV;

	TCamera();
	void Render(TGfxImage * pImage, TSphere * TSphere, TPlan tPlan) const;
};

#endif





