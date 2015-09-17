#ifndef __TENEMY__
#define __TENEMY__

class TEnemy : public TDynamicEntity
{

public:
	TEnemy();
	~TEnemy();

	char * GetName() { return "Enemy"; }
};

#endif