#include "stdafx.h"
#include "drawable.h"
#include "collidable.h"
#include "staticentity.h"
#include <string>


TStaticEntity::TStaticEntity()
{
	printf("Static Entity Constructor\n");
}

TStaticEntity::~TStaticEntity()
{
	printf("Static Entity Destructor\n");
}