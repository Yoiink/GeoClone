#pragma once

#include "Draw.h"
#include <memory>
//#include "Asset.h"

enum ObjectID{GEO, BULLET}; //Continue in Enemy.h
enum ObjectSide{ALLY, NEUTRAL, ENEMY};

class GameObject{

public:

	//Constructor/Destructor
	GameObject(int width, int height, float posX, float posY, float directionX = 0, float directionY = 0, float speed = 0, float angle = 0, int objectType = 0, bool isAlive = true);
	~GameObject();

	//Get
	virtual int getWidth() const;
	virtual int getHeight() const;
	float getX() const;
	float getY() const;
	float getDirectionX() const;
	float getDirectionY() const;
	float getSpeed() const;
	float getAngle() const;
	//BYTE* getTexture() const;
	//BYTE* getTexture(int frameNumber) const;
	//int getTextureWidth() const;
	//int getTextureHeight() const;
	int getObjectType() const;
	bool getAlive() const;
	int getFrame() const;
	int getMaxFrame() const;
	int getAssetID() const;
	int getDeathAssetID() const;
	float getRadiusPowTwo() const;
	int getObjectSide() const;
	virtual bool getIsCooldown() const;

	//Set
	virtual bool setWidth(const int width);
	virtual bool setHeight(const int height);
	bool setX(const float posX);
	bool setY(const float posY);
	bool setDirectionX(const float directionX);
	bool setDirectionY(const float directionY);
	bool setSpeed(const float speed);
	bool setTexture(int assetID);
	bool setDeathTexture(int assetID);
	bool setMaxFrame(int maxFrame);
	bool setAngle(float angle);
	bool setObjectSide(int objectSide);
	virtual bool setIsAlive(const bool aliveStatus);
	
	void updateFrame();
	void resurrect(int width, int height, float posX, float posY, int objectType = NULL, float speed = NULL, float angle = NULL);

	//Other
	bool CheckCollision(std::shared_ptr<GameObject> &objectCheck);
	//virtual void Rotate(const double angle, int &posX, int &posY, const int midX, const int midY);
	//virtual void Render(Draw &screen);
	virtual void Update(const float &deltaTime);
	virtual void Chase(std::shared_ptr<GameObject> &object, const float &deltaTime, const std::shared_ptr<Draw> grid);

protected:
	size_t _lastFrame;
private:
	int _width, _height, _frameNumber, _objectType, _objectSide, _maxFrames, _assetID, _deathAssetID;
	float _directionX, _directionY, _angle, _radius, _radiusPowTwo;
	float _speed, _posX, _posY, _lastPosX, _lastPosY;
	bool _isAlive;
	//BYTE * _textureData;
	//std::shared_ptr<Asset> _myAsset;

};

