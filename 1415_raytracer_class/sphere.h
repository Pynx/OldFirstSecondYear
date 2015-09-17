#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "flib_vec3.h"
#include "ray.h"

struct TRay; // Explique juste ce qu'est TRay (une struct), on a juste besoind d'une référence vers TRay

struct TSphere
{
	TGfxVec3 m_tPosition;
	TGfxVec3 m_tColor;

	float Collision(TRay & tRay) const;

	unsigned int Shade(TRay & tRay, TGfxVec3 tLight, float fDistance) const;
};

#endif