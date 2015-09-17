#include "flib.h"
#include "flib_vec3.h"
#include "color.h"

TGfxVec3 ColToVec(const unsigned int iColor);
unsigned int VecToCol(const TGfxVec3 & tVector);
TGfxVec3 Lerp(const TGfxVec3 & tVectorA, const TGfxVec3 & tVectorB, const float fDelta);
