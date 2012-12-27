#include "GameObject.h"
#include "Draw.h"

#pragma once

class Bullet : public GameObject{

public:
	//using GameObject::GameObject;
	Bullet(int width, int height, float posX, float posY, float directionX = 0, float directionY = 0, float speed = 0, float angle = 0, bool isAlive = true);
	virtual ~Bullet();

	void Update(const float &deltaTime);
	//void Render(Draw &screen);

	bool CheckCollision(const int &screenWidth, const int &screenHeight) const;

private:

};

