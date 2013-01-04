#pragma once
#include "enemy.h"
class EnemyOrange :
	public Enemy
{
public:
	EnemyOrange(float posX, float posY, int assetID, int deathAssetID);
	~EnemyOrange(void);

	void Chase(std::shared_ptr<GameObject> &player, const float &deltaTime, const std::shared_ptr<Draw> grid);
};

