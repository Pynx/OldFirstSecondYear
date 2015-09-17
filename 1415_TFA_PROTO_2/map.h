#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


class TMap
{
public:
	TGfxImage * g_tLevelImage = nullptr;
	TGfxSprite * g_tLevelSprite = nullptr;
	TGfxTexture * g_tLevelTexture = nullptr;
	TGfxImage * g_tTextureImage = nullptr;

	TGfxVec2 tGreyRackTexturePos = TGfxVec2(0, 1); // Grey ( 200, 200, 200 )
	TGfxVec2 tRedRackTexturePos = TGfxVec2(1, 1); // Red ( 255, 0, 0 )
	TGfxVec2 tGreenRackTexturePos = TGfxVec2(2, 1); // Green ( 0, 255, 0 )
	TGfxVec2 tOpenedDoorTexturePos = TGfxVec2(0, 2); // Pink ( 255, 0, 255 )
	TGfxVec2 tClosedDoorTexturePos = TGfxVec2(1, 2); // Yellow ( 255, 255, 0 )
	TGfxVec2 tWallTexturePos = TGfxVec2(2, 2); // Black ( 0, 0, 0 )
	TGfxVec2 tBaseTexturePos = TGfxVec2(0, 3); // Turquoise ( 0, 255, 255 )
	TGfxVec2 tLadderTexturePos = TGfxVec2(1, 3); // Light Blue ( 50, 100, 200 )
	TGfxVec2 tCapturedExitTexturePos = TGfxVec2(2, 3); // Blue ( 0, 0, 255 )
	TGfxVec2 tNotCapturedExitTexturePos = TGfxVec2(0, 4); // Brown ( 200, 150, 0 )
	TGfxVec2 tMovableWallTexturePos = TGfxVec2(3,0); // Special red ( 255, 100, 100 )

	int Readmap(const int SCALE, const int TILE_SIZE, const int MAX_WALL, const int g_iLevel);
	void DeleteMap();
	void CreateVar();
	void ChangeColor(const int iTilePosX, const int iTilePosY, TGfxVec2 tPosition);
};

#endif
