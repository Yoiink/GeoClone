#include "Player.h"


Player::Player(float xPos, float yPos) :
	GameObject(32, 32, xPos, yPos, 0, 0, 0, 0, 0, true)
{
	_immunityTimer = 3000; //3 Seconds
}


Player::~Player(void)
{
}

int Player::getWidth() const{
	return 32;
}

int Player::getHeight() const{
	return 32;
}

bool Player::setIsAlive(const bool aliveStatus){
	if(_immunityTimer > 0){
		return true;
	} else {
		GameObject::setIsAlive(aliveStatus);
		//_isAlive = aliveStatus;
	}
	return true;
}

void Player::Update(const float &deltaTime){

	if(_immunityTimer > 0){
		_immunityTimer -= deltaTime * 10;
		//HAPI->RenderText(0, 60, HAPI_TColour(), std::to_string(_immunityTimer));
	}

	if(_lastFrame + 2000 < HAPI->GetTime()){
		this->updateFrame();
		_lastFrame = HAPI->GetTime();
	}
}
