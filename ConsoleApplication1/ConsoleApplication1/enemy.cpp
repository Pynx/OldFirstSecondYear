#include "stdafx.h"
#include "drawable.h"
#include "collidable.h"
#include "dynamicentity.h"
#include "enemy.h"
#include <string>

TEnemy::TEnemy() : TDynamicEntity(42)
{
	printf("Enemy Constructor\n");
}

TEnemy::~TEnemy()
{
	printf("Enemy Destructor\n");
}