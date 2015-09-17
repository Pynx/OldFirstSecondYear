#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class TPlayer
{
public:

	float m_fSpeed = 0;
	float m_fHealth = 100;

	bool bIsGameWin = false;

	TGfxVec2 m_tDirection = TGfxVec2(0, 0);
	TGfxVec2 m_tPosition = TGfxVec2(0, 0);
	TGfxVec2 m_tStartPosition = TGfxVec2(0, 0);
	TGfxVec2 m_tSpawnPosition = TGfxVec2(0, 0);
	TGfxVec2 m_tRespawnVector = TGfxVec2(0, 0);

	TGfxSprite * m_pSpritePlayer;

	void Render(const int MAX_Wall);
	void Initialize(int x, int y, int TILE_SIZE, int SCALE);
	void Move(float fSpeed, TGfxVec2 tDirection, const int MAX_WALL, const int TILE_SIZE);
	void Respawn(const int MAX_Wall);

};

#endif
