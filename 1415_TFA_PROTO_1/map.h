#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


class TMap
{
public:
	TGfxImage * g_tLevelImage = nullptr;
	TGfxTexture * g_tLevelTexture = nullptr;
	TGfxSprite * g_tLevelSprite = nullptr;

	TGfxVec2 tWallTexturePos = TGfxVec2(3, 1);
	TGfxVec2 tDeathTexturePos = TGfxVec2(0, 0);
	TGfxVec2 tTheEndTexturePos = TGfxVec2(2, 2);
	TGfxVec2 tRightSpeedBoostTexturePos = TGfxVec2(1, 0);
	TGfxVec2 tLeftSpeedBoostTexturePos = TGfxVec2(2, 1);
	TGfxVec2 tUpSpeedBoostTexturePos = TGfxVec2(0, 1);
	TGfxVec2 tTrapWallTexturePos = TGfxVec2(2, 0);
	TGfxVec2 tGrapTexturePos = TGfxVec2(1, 1);
	TGfxVec2 tWallJumpTexturePos = TGfxVec2(0, 2);

	void Readmap(const int SCALE, const int TILE_SIZE, const int PLAYERPOSX, const int PLAYERPOSY, const int MAX_WALL);
	TGfxVec2 Move(float fSpeed, TGfxVec2 tDirection, const int MAX_WALL, const int TILE_SIZE);

};

#endif
