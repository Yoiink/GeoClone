#include <HAPI_lib.h>
#include <list>

#include "Draw.h"
#include "GameObject.h"

GameObject::GameObject(int width, int height, float posX, float posY, float directionX, float directionY, float speed, float angle, int objectType, bool isAlive){
	_posX = posX;
	_posY = posY;
	_width = width;
	_height = height;
	_directionX = directionX;
	_directionY = directionY;
	_speed = speed;
	//_textureData = 0;
	_angle = angle;
	_frameNumber = 0;
	_objectType = objectType; // 0 = PLAYER | 1 = BULLET   -- Bullet & Player could share same type, but seperate them for possible future fixed list
	_isAlive = true;
	_lastFrame = HAPI->GetTime();
	_assetID = 0;
	_maxFrames = 0;
	_isAlive = isAlive;
	_deathAssetID = 0;
	_radius = 20;
	_radiusPowTwo = _radius * _radius;

	if(_objectType <= 1){
		_objectSide = ALLY;
	} else {
		_objectSide = ENEMY;
	}

}


GameObject::~GameObject(){

}

#pragma region Getters

	int GameObject::getWidth() const{
		return _width;
	}

	int GameObject::getHeight() const{
		return _height;
	}

	float GameObject::getX() const{
		return _posX;
	}

	float GameObject::getY() const{
		return _posY;
	}

	float GameObject::getDirectionX() const{
		return _directionX;
	}

	float GameObject::getDirectionY() const{
		return _directionY;
	}

	float GameObject::getSpeed() const{
		return _speed;
	}

	float GameObject::getAngle() const{
		return _angle;
	}

	//BYTE* GameObject::getTexture() const{
	//	return _myAsset->getTexture();
	//	//return _textureData;
	//}

	//BYTE* GameObject::getTexture(int frameNumber) const{
	//	return _myAsset->getTexture(frameNumber);
	//	//return _textureData;
	//}

	//int GameObject::getTextureWidth() const{
	//	return _myAsset->getWidth();
	//	//return _textureWidth;
	//}

	//int GameObject::getTextureHeight() const{
	//	return _myAsset->getHeight();
	//	//return _textureHeight;
	//}

	int GameObject::getObjectType() const{
		return _objectType;
	}

	bool GameObject::getAlive() const{
		return _isAlive;
	}

	int GameObject::getFrame() const{
		return _frameNumber;
	}

	//int GameObject::getMaxFrame() const{
	//	return _myAsset->getMaxFrame();
	//}

	int GameObject::getAssetID() const{
		return _assetID;
	}

	int GameObject::getDeathAssetID() const{
		return _deathAssetID;
	}

	float GameObject::getRadiusPowTwo() const{
		return _radiusPowTwo;
	}

	int GameObject::getObjectSide() const{
		return _objectSide;
	}

	bool GameObject::getIsCooldown() const{
		return false;
	}


#pragma endregion Get functions

#pragma region Setters
	bool GameObject::setWidth(int width){
		_width = width;
		return true;
	}

	bool GameObject::setHeight(int height){
		_height = height;
		return true;
	}

	bool GameObject::setX(float posX){
		_lastPosX = _posX;
		_posX = posX;
		return true;
	}

	bool GameObject::setY(float posY){
		_lastPosY = _posY;
		_posY = posY;
		return true;
	}

	bool GameObject::setDirectionX(float directionX){
		_directionX = directionX;
		return true;
	}

	bool GameObject::setDirectionY(float directionY){
		_directionY = directionY;
		return true;
	}

	bool GameObject::setSpeed(float speed){
		_speed = speed;
		return true;
	}

	bool GameObject::setTexture(int assetID){
		_assetID = assetID;

		return true;
	}

	bool GameObject::setDeathTexture(int assetID){
		_deathAssetID = assetID;
		return true;
	}

	bool GameObject::setAngle(float angle){
		_angle = angle;
		return true;
	}

	bool GameObject::setIsAlive(bool aliveStatus){
		_isAlive = aliveStatus;

		return true;
	}

	bool GameObject::setMaxFrame(int maxFrame){
		_maxFrames = maxFrame;
		return true;
	}

	bool GameObject::setObjectSide(int objectSide){
		_objectSide = objectSide;
		return true;
	}

#pragma endregion Set functions


void GameObject::Update(const float &deltaTime){
	if(_lastFrame + 2000 < HAPI->GetTime()){
		this->updateFrame();
		_lastFrame = HAPI->GetTime();
		//HAPI->DebugText("UPDATED FRAME:" + std::to_string(_frameNumber) + "MAX FRAMES = " + std::to_string(_myAsset->getMaxFrame()));
	}
}

void GameObject::updateFrame(){
	if((_frameNumber >= _maxFrames - 1)){
		_frameNumber = 0;
	} else {
		_frameNumber++;
	}
}

void GameObject::resurrect(int width, int height, float posX, float posY, int objectType, float speed, float angle){
	_width = width;
	_height = height;
	_posX = posX;
	_posY = posY;

	if(objectType != NULL)
		_objectType = objectType;

	if(speed != NULL)
		_speed = speed;

	if(angle != NULL)
		_angle = angle;

}

void GameObject::Chase(std::shared_ptr<GameObject> &object, const float &deltaTime){
	//Implemented in Enemy
}

bool GameObject::CheckCollision(std::shared_ptr<GameObject> &objectCheck){

	//Do rectangle check to see if bullets have hit/player and object have hit.
	if( getObjectType() != objectCheck->getObjectType() ){
		//Logic from: http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
		//Visual: http://silentmatt.com/rectangle-intersection/
		if( (getX() < objectCheck->getX() + objectCheck->getWidth())	&&		//Left < Other Right
			(getX() + getWidth() > objectCheck->getX())					&&		//Right > Other Left
			(getY() < objectCheck->getY() + objectCheck->getHeight())	&&		//Top < Other Bottom
			(getY() + getHeight() > objectCheck->getY())				){		//Bottom > Other Top
				//HAPI->DebugText("Collision");

				//If both objects are the same side, there's no need to mark dead.
				if( (getObjectSide() == objectCheck->getObjectSide()) )
					return false;

				//Check to see if we're checking an enemy against geo or visa-versa.
				if( (getObjectType() == GEO && objectCheck->getObjectSide() == ENEMY) || 
					(getObjectSide() == ENEMY && objectCheck->getObjectType() == GEO) ){
						//Check if the enemy is in cooldown (just spawened)
						if(getIsCooldown() || objectCheck->getIsCooldown()){
							//We don't want to kill the player if it has just spawned.
							return false;
						}
				}

				objectCheck->setIsAlive(false);
				setIsAlive(false);

				return true;
		}
	} else {
		//If the objects are the same type, then they should not overlap (Mainly enemies...)
		if( getObjectType() == objectCheck->getObjectType() ){
			if(getObjectType() == BULLET) //If bullet, escape. Bullet will stick otherwise.
				return false;
			float x = objectCheck->getX() - getX();
			float y = objectCheck->getY() - getY();
			if( (x*x) + (y*y) < _radiusPowTwo ){
					_posX = _lastPosX;
					_posY = _lastPosY;
			}
		}

	}

	

	return false;
}