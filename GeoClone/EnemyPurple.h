#pragma once
#include "enemy.h"
class EnemyPurple :
	public Enemy
{
public:
	EnemyPurple(float posX, float posY, int assetID, int deathAssetID);
	~EnemyPurple(void);

	//Add override on death? To spawn mini purples
};

