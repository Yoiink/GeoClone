#include <HAPI_lib.h>

#include "Bullet.h"
#include "Draw.h"


Bullet::Bullet(int width, int height, float posX, float posY, float directionX, float directionY, float speed, float angle, bool isAlive) 
	  : GameObject(width, height, posX, posY, directionX, directionY, speed, angle, BULLET, isAlive){

		//setTexture("bullet.png");
}

Bullet::~Bullet()
{
}

void Bullet::Update(const float &deltaTime){
	
	//Cast getDirection from double to int - Not sure how I would correctly shoot bullets yet
	setX(getX() + (getDirectionX() * getSpeed()) * deltaTime );
	setY(getY() + (getDirectionY() * getSpeed()) * deltaTime );

	//HAPI->RenderText(getX(), getY(), HAPI_TColour(255, 0, 0), "o");

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

//void Bullet::Render(Draw &screen){
//	const BYTE * textureData = getTexture();
//	const int textureWidth = getTextureWidth();
//	const int textureHeight = getTextureHeight();
//
//	const int posX = getX();
//	const int posY = getY();
//
//	if(textureData != 0 && &screen != 0){
//		int maxBytes = (textureWidth * textureHeight) * 4;
//		int curX = posX, curY = posY;
//
//		int midX = posX + (textureWidth / 2);
//		int midY = posY + (textureHeight / 2);
//
//		for(int curByte = 0; curByte < maxBytes; curByte += 4){
//
//			int rotX = curX;
//			int rotY = curY;
//			Rotate(getAngle(), rotX, rotY, midX, midY);
//			
//			if( (rotX > 0) && (rotX + textureWidth < screen.getWidth() - 1) &&
//			(rotY > 0) && (rotY + textureHeight < screen.getHeight() - 1) ){
//				//Blending from: http://stackoverflow.com/questions/5149722/get-pixel-color-after-alpha-blend
//				HAPI_TColour backgroundCol = screen.getPixelCol(rotX, rotY);
//				HAPI_TColour textureCol(textureData[curByte+2], textureData[curByte+1], textureData[curByte], textureData[curByte + 3]);
//				HAPI_TColour calculatedCol;
//
//				calculatedCol.red =  (textureCol.red * textureCol.alpha / 255) + (backgroundCol.red * (1 - textureCol.alpha / 255));
//				calculatedCol.green =  (textureCol.green * textureCol.alpha / 255) + (backgroundCol.green * (1 - textureCol.alpha / 255));
//				calculatedCol.blue =  (textureCol.blue * textureCol.alpha / 255) + (backgroundCol.blue * (1 - textureCol.alpha / 255));
//
//				screen.setPixel(rotX, rotY, calculatedCol.red, calculatedCol.green, calculatedCol.blue);
//			}
//			curX++;
//
//
//			if(curX == (posX + textureWidth)){
//				curX = posX;
//				curY++;
//			}
//		}
//
//	}
//}