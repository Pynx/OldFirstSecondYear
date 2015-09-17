#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED


class TWall
{
public:

	TGfxVec2 m_tPosition = TGfxVec2(0, 0);

	bool m_bIsClickable = false;
	bool m_bIsBasePosOpen = false;
	bool m_bIsClickableOpen = false;
	bool m_bIsRack = false;
	bool m_bIsBase = false;
	bool m_bIsExit = false;
	bool m_bIsExitOpen = false;
	bool m_bIsLadder = false;
	bool m_bIsMovable = false;

	bool m_bIsStopped = false;
	const int m_iTimeToStop = 1;
	int m_iStoppedTime = 0;
	int m_iDirection = 0; // 0 = right, 1 = left

	int m_iColor = 0; // 0 = Grey, 1 = Red, 2 = Green

	void Input(const int TILE_SIZE);

};

#endif
