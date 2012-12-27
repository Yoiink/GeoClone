#pragma once
#include "enemy.h"
class EnemyBlue :
	public Enemy
{
public:
	EnemyBlue(float posX, float posY, int assetID, int deathAssetID);
	~EnemyBlue(void);
};

