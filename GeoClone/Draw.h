#pragma once

#include <memory>
#include <HAPI_lib.h>
#include <vector>
#include "Asset.h"
//#include "GameState.h"

class GameObject;
class GameState;

class Draw
{
public:
	Draw(std::shared_ptr<GameState> gameMode, int screenWidth = 1280, int screenHeight = 720, int screenBoundry = 80, int screenLines = 30);
	~Draw(void);

	int getWidth() const;
	int getHeight() const;
	HAPI_TColour getPixelCol(int posX, int posY) const;
	int getScreenBoundry() const;
	int getScreenLines() const;
	float getGridX() const;
	float getGridY() const;
	float getLastGridX() const;
	float getLastGridY() const;

	bool setPixel(int posX, int posY, int R, int G, int B);
	bool setScreenCol(int R = 0, int G = 0, int B = 0);
	//bool drawLine(int startX, int startY, int endX, int endY, HAPI_TColour lineCol = HAPI_TColour(76, 109, 206));
	bool drawLine(int startX, int startY, int endX, int endY, HAPI_TColour lineCol = HAPI_TColour(76, 109, 206));

	void updateGrid(const float &deltaTime);
	bool drawGridBox(std::shared_ptr<GameObject> Geo);
	bool drawGridBox(int boundrySize, int gridLines);
	void distortGrid(std::shared_ptr<GameObject> &entity);

	void updateParallax(std::shared_ptr<GameObject> Geo);
	void setupParallax(std::shared_ptr<GameObject> Geo);

	void changeStatePtr(std::shared_ptr<GameState> gameState);

	//void Render(std::shared_ptr<GameObject> entity, int frameNumber = 0);
	void speedRender(float drawPosX, float drawPosY, int drawWidth, int drawHeight, BYTE* textureData);
	void Render(float drawPosX, float drawPosY, int drawWidth, int drawHeight, BYTE* textureData);
	void Render(float drawPosX, float drawPosY, int drawWidth, int drawHeight, int assetID, float entityAngle = 0, int frameNumber = 0, bool floatCalc = true);

	void Rotate(const double angle, int &posX, int &posY, const int midX, const int midY);

	struct Point{
		//Point(void){
		//	normalPosition = position;
		//	currentPosition = position;
		//}

		Point(float x, float y){
			xPos = x;
			yPos = y;
			xReturn = xPos;
			yReturn = yPos;
			//maxChange = 16;
		}

		float xPos, yPos, xReturn, yReturn;
	};

private:
	//std::shared_ptr<std::vector<std::shared_ptr<Asset>>> _gameAssets;
	//std::vector<Point> _gridPoints;

	std::vector<Point> _gridPoints;

	std::shared_ptr<GameState> _gameState;
	int _screenWidth, _screenHeight, _screenSize, _screenBoundry, _screenLines, _maxPointChange;
	float _gridX, _gridY, _lastGridX, _lastGridY;
	BYTE * _pScreen;
};

