#include <HAPI_lib.h>
#include "Bullet.h"
#include "Draw.h"


Bullet::Bullet(int width, int height, float posX, float posY, float directionX, float directionY, float speed, float angle, bool isAlive) 
	  : GameObject(width, height, posX, posY, directionX, directionY, speed, angle, BULLET, isAlive){
}

Bullet::~Bullet()
{
}

void Bullet::Update(const float &deltaTime){
	
	setX(getX() + (getDirectionX() * getSpeed()) * deltaTime );
	setY(getY() + (getDirectionY() * getSpeed()) * deltaTime );

}

bool Bullet::CheckCollision(const int &screenWidth, const int &screenHeight) const{
	if(getX() < 0 || getX() > screenWidth){
		return true;
	} else if(getY() < 0 || getY() > screenHeight){
		return true;
	} else {
		return false;
	}

}