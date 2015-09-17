#include "stdafx.h"

#include "drawable.h"
#include "collidable.h"
#include "dynamicentity.h"
#include <string>

TDynamicEntity::TDynamicEntity( int )
{
	printf("Dynamic Entity Constructor\n");
}

TDynamicEntity::~TDynamicEntity()
{
	printf("Dynamic Entity Destructor\n");
}


bool TDynamicEntity::Move(float , float )
{
	printf("\nMove\n");
	return true;
}