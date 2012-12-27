#pragma once
#include "gameobject.h"
#include "Asset.h"

enum EnemyNames{ENEMY_PURPLE = 2, ENEMY_PURPLE_MINI, ENEMY_GREEN, ENEMY_BLUE};

class Enemy : public GameObject
{
public:
	Enemy(int width, int height, float posX, float posY, float speed, int enemyID,  int assetID, int deathAssetID, bool isAlive = true);
	~Enemy();

	void Chase(std::shared_ptr<GameObject> &player, const float &deltaTime);
	int getEnemyID() const;

private:
	int _enemyID;
	float _spawnCooldown;

};

