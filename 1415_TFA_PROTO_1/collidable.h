#ifndef COLLIDABLE_H_INCLUDED
#define COLLIDABLE_H_INCLUDED

class TCollidable
{
public:
	TGfxVec2 tPosition = TGfxVec2(-2000, -2000);
	TGfxVec2 tBoost = TGfxVec2(0, 0);

	bool bIsBoost = false;
	bool bIsGrappable = false;
	bool bIsWallJumpable = false;
	bool bCollisionAbove = true;
	bool bIsKilling = false;
	bool bIsTheEnd = false;
};

#endif
