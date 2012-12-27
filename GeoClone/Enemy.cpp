#include "Enemy.h"
#include <list>

#define _USE_MATH_DEFINES
#include <math.h>

Enemy::Enemy(int width, int height, float posX, float posY, float speed, int enemyID, int assetID, int deathAssetID, bool isAlive)
	: GameObject(width, height, posX, posY, 0, 0, 2, 0, enemyID, isAlive), _enemyID(enemyID){
		setTexture(assetID);
		setDeathTexture(deathAssetID);

		_spawnCooldown = 0;	//Disabled at the moment. Usually: 1000 = 1 second.
}


Enemy::~Enemy()
{
}

int Enemy::getEnemyID() const{
	return _enemyID;
}


void Enemy::Chase(std::shared_ptr<GameObject> &player, const float &deltaTime){

	if(_spawnCooldown > 0){
		_spawnCooldown -= deltaTime * 10;
		return;
	}

	//AI "Chase" code/idea from: http://www.peachpit.com/articles/article.aspx?p=102090&seqNum=4
	float angle = atan2(player->getY() - getY(), player->getX() - getX() );

	switch(_enemyID){
	case ENEMY_PURPLE:
		setAngle(angle);
		setX(getX() + (cosf(angle) * getSpeed()) * deltaTime );
		setY(getY() + (sinf(angle) * getSpeed()) * deltaTime );
		break;
	case ENEMY_BLUE:
		setAngle(angle);
		setX(getX() + (cosf(angle) * getSpeed()) * deltaTime );
		setY(getY() + (sinf(angle) * getSpeed()) * deltaTime );
		break;
	case ENEMY_PURPLE_MINI:
		setAngle(getAngle() + deltaTime / 10);
		setX(getX() + (cosf(getAngle()) * getSpeed()) + (cosf(angle) * getSpeed() / 4) * deltaTime );
		setY(getY() + (sinf(getAngle()) * getSpeed()) + (sinf(angle) * getSpeed() / 4) * deltaTime );
		break;
	}
	

}