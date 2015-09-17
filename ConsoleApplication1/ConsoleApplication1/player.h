#ifndef __TPLAYER__
#define __TPLAYER__

class TPlayer : public TDynamicEntity
{

public:
	TPlayer();
	~TPlayer();

	virtual char * GetName() { return "Player"; }

	int m_iTemp;
};

#endif