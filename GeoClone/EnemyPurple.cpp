#include "EnemyPurple.h"


EnemyPurple::EnemyPurple(float posX, float posY, int assetID, int deathAssetID) :
	Enemy(32, 32, posX, posY, 2, ENEMY_PURPLE, assetID, deathAssetID)
{
}


EnemyPurple::~EnemyPurple(void)
{
}
