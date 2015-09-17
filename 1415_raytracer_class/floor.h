#ifndef PLAN_H_INCLUDED
#define PLAN_H_INCLUDED

#include "flib_vec3.h"
#include "ray.h"

struct TRay;
struct TSphere;

struct TPlan
{
	TGfxVec3 m_tPosition;

	TGfxVec3 m_tNormal = TGfxVec3(0, 1, 0);

	bool Collision(const TRay & tRay) const;

	unsigned int Shade(const TRay & tRay, const TGfxVec3 & tLight, const TSphere & tSphere) const; // Le const permet d'empêcher de modifier l'objet dans lequel il est
};

#endif