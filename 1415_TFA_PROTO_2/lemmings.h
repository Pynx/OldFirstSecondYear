#ifndef LEMMINGS_H_INCLUDED
#define LEMMINGS_H_INCLUDED


class TLemmings
{
public:

	TGfxVec2 m_tPosition = TGfxVec2(0, 0);

	int m_iColor = 0; // 0 = Grey, 1 = Red, 2 = Green
	int m_iDirection = 0; // 0 = Right, 1 = Left

	bool m_bIsStopped = false;
	bool m_bIsAtTheEnd = false;

	void Spawn(TGfxVec2 tPosition);
	void Move(const int TILE_SIZE, const int g_iLemmingsCpt);
	void Input(const int TILE_SIZE);
	void ChangeColor(const int Color); // 0 = Grey, 1 = Red, 2 = Green

	TGfxSprite * m_tLemmingSprite = nullptr;
};

#endif
