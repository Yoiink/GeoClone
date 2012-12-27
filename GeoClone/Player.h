#pragma once
#include "gameobject.h"
class Player :
	public GameObject
{
public:
	Player(float xPos, float yPos);
	~Player(void);

	bool setIsAlive(const bool aliveStatus);
	void Update(const float &deltaTime);

	int getWidth() const;
	int getHeight() const;

private:
	float _immunityTimer;
};

