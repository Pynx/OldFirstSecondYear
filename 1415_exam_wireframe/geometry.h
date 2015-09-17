#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "flib.h"
#include "flib_vec3.h"
#include "vector.h"

class TGeometry
{
public:

	void AddLine( const TGfxVec3 & tPointA, const TGfxVec3 & tPointB, unsigned int iColor = EGfxColor_White);
	void Render( TGfxSprite * pSprite ) const;

	int GetLineCount() const;
	void Clear();

private:

	TVector< TGfxVec3 > m_tVertexBuffer;
	TVector< unsigned int > m_tColorBuffer;
};

#endif
