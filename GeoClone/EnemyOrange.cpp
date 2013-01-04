#include "EnemyOrange.h"


EnemyOrange::EnemyOrange(float posX, float posY, int assetID, int deathAssetID) :
	Enemy(32, 32, posX, posY, 4, ENEMY_ORANGE, assetID, deathAssetID)
{
	//GameObject::setDirectionX(1);
	//GameObject::setDirectionY(1);
}


EnemyOrange::~EnemyOrange(void)
{
}

void EnemyOrange::Chase(std::shared_ptr<GameObject> &player, const float &deltaTime, const std::shared_ptr<Draw> grid){

	if(getIsCooldown()){
		decrementCooldown(deltaTime);
	}

	float directionX = GameObject::getDirectionX();
	float directionY = GameObject::getDirectionY();

	//Work out what the angle of the arrow enemy should be.
	float angle = atan2f( (getY() + (directionY * 10)) - getY(), (getX() + (directionX * 10))  - getX());
	setAngle(angle);

	//Calculate the newX and check to see if it is okay to update.
	float calcedX = GameObject::getX() + (GameObject::getDirectionX() * (GameObject::getSpeed() * deltaTime));

	if(directionX < 0){
		if(calcedX > grid->getGridX()){
			GameObject::setX(calcedX);
		} else {
			GameObject::setDirectionX(directionX * -1);
		}
	} else {
		if(calcedX + GameObject::getWidth() < grid->getGridX() + grid->getWidth()){
			GameObject::setX(calcedX);
		} else {
			GameObject::setDirectionX(directionX * -1);
		}
	}

	//Calculate the newX and check to see if it is okay to update.
	float calcedY = GameObject::getY() + (GameObject::getDirectionY() * (GameObject::getSpeed() * deltaTime));

	if(directionY < 0){
		if(calcedY > grid->getGridY()){
			GameObject::setY(calcedY);
		} else {
			GameObject::setDirectionY(directionY * -1);
		}
	} else {
		if(calcedY + GameObject::getHeight() < grid->getGridY() + grid->getHeight()){
			GameObject::setY(calcedY);
		} else {
			GameObject::setDirectionY(directionY * -1);
		}
	}

}
