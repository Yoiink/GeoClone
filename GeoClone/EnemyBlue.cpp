#include "EnemyBlue.h"


EnemyBlue::EnemyBlue(float posX, float posY, int assetID, int deathAssetID) :
	Enemy(32, 32, posX, posY, 2, ENEMY_PURPLE, assetID, deathAssetID)
{
}


EnemyBlue::~EnemyBlue(void)
{
}
