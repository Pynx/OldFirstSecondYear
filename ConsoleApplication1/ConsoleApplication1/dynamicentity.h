#ifndef __TDYNAMICENTITY__
#define __TDYNAMICENTITY__

class TDynamicEntity : public TCollidable
{

public:
	TDynamicEntity(int);
	virtual ~TDynamicEntity();

	bool Move(float fDeltaX, float fDeltaY);

	virtual char * GetName() { return "Dynamic"; } // Virtual veut dire qu'il va être redéfini dans ses enfants et qu'il faudra donc prendre un autre si on prend celui de plus bas.

	int m_iTemp;

};

#endif