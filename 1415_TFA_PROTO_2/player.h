#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class TPlayer : public TDynamic
{
public:
	TPlayer();
	~TPlayer();

	char * GetName();
};

#endif
