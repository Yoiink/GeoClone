#include "Draw.h"
#include "GameObject.h"
#include <HAPI_lib.h>

#include "EvolvedGame.h"

Draw::Draw(std::shared_ptr<GameState> gameMode, int screenWidth, int screenHeight, int screenBoundry, int screenLines) : _screenWidth(screenWidth), _screenHeight(screenHeight), _screenSize((screenWidth * screenHeight) * 4), 
		  _screenBoundry(screenBoundry), _screenLines(screenLines), _gridX(0), _gridY(0), _gameState(gameMode)
{
	if(!HAPI->Initialise(&screenWidth, &screenHeight))
		return;

	_pScreen = HAPI->GetScreenPointer();

	float xJump = screenWidth / 50.f;
	float yJump = screenHeight / 33.f;

	//For loop should be 2 extra than the x/yJump to make up for outer ring
	for(int curPointY = 0; curPointY <= 35; curPointY++){
		for(int curPointX = 0; curPointX <= 52; curPointX++){
			_gridPoints.push_back(Point(curPointX * xJump, curPointY * yJump));
		}
	}

	_maxPointChange = 20;

}


Draw::~Draw(void)
{
}

int Draw::getWidth() const{
	return _screenWidth;
}

int Draw::getHeight() const{
	return _screenHeight;
}

int Draw::getScreenBoundry() const{
	return _screenBoundry;
}

int Draw::getScreenLines() const{
	return _screenLines;
}

HAPI_TColour Draw::getPixelCol(int posX, int posY) const{
	int offSet = ((posY * _screenWidth) + posX) * 4;
	HAPI_TColour pixelCol;
	pixelCol.blue = _pScreen[offSet++];
	pixelCol.green = _pScreen[offSet++];
	pixelCol.red = _pScreen[offSet++];
	pixelCol.alpha = _pScreen[offSet++];
	return pixelCol;
}

float Draw::getGridX() const{
	return _gridX;
}

float Draw::getGridY() const{
	return _gridY;
}

float Draw::getLastGridX() const{
	return _lastGridX;
}

float Draw::getLastGridY() const{
	return _lastGridY;
}

bool Draw::setPixel(int posX, int posY, int R, int G, int B){

	if(posX < 0 || posX > _screenWidth - 1 || posY < 0 || posY > _screenHeight - 1)
		return false;

	int offSet = ((posY * _screenWidth) + posX) * 4;

	_pScreen[offSet++] = B;
	_pScreen[offSet++] = G;
	_pScreen[offSet] = R;

	return true;
}

bool Draw::setScreenCol(int R, int G, int B){
	int screenSize = (_screenWidth * _screenHeight) * 4;
	
	for(int i = 0; i < screenSize; i++){
		_pScreen[i++] = B;
		_pScreen[i++] = G;
		_pScreen[i++] = R;
	}

	return true;
}

void Draw::changeStatePtr(std::shared_ptr<GameState> gameState){
	_gameState = gameState;
}

bool Draw::drawLine(int startX, int startY, int endX, int endY, HAPI_TColour lineCol){

	if(startX == endX && startY == endY)
		return true;

	//
	// Using algo from: http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Simplification
	// I had implemented it myself as shown in comments under the function. However, I found when
	// I started the grid warping, that the game was hanging. Probably due to this gunction I wrote
	// so, my best guess is that I needed to add something to break from the while(true).

	// However being lazy, I did a Google and came over this which is what I'm using:
	//	http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B

	const bool steep = (endY - startY > endX - startX);
	if(steep)
	{
		std::swap(startX, startY);
		std::swap(endX, endY);
	}
 
	if(startX > endX)
	{
		std::swap(startX, endX);
		std::swap(startY, endY);
	}
 
	const float dx = static_cast<float>(endX - startX);
	const float dy = static_cast<float>(endY - startY);
 
	float error = dx / 2.0f;
	const int ystep = (startY < endY) ? 1 : -1;
	int y = startY;
 
	const int maxX = endX;
 
	for(int x = startX; x < maxX; x++)
	{
		if(steep)
                {
						setPixel(y, x, lineCol.red, lineCol.green, lineCol.blue);
                }
		else
                {
						setPixel(x, y, lineCol.red, lineCol.green, lineCol.blue);
                }
 
                error -= dy;
	        if(error < 0)
	        {
		        y += ystep;
		        error += dx;
	        }
	}

	/*
	int curX = startX;
	int curY = startY;
	int offset = 0;

	int dX = endX - startX;
	int dY = endY - startY;
	int err = dX - dY;

	int modX = 0;
	int modY = 0;

	if(startX < endX){
		modX = 1;
	} else {
		modX = -1;
	}

	if(startY < endY){
		modY = 1;
	} else {
		modY = -1;
	}

	while(true){
		//offset = ((curY * _screenWidth) + curX) * 4;
		//_pScreen[offset++] = lineCol.blue;
		//_pScreen[offset++] = lineCol.green;
		//_pScreen[offset++] = lineCol.red;

		setPixel(curX, curY, lineCol.red, lineCol.green, lineCol.blue);

		if(curX == endX && curY == endY){
			break;
		}

		int err2 = 2*err;

		if(err2 > -dY){
			err -= dY;
			curX += modX;
		}

		if(err2 < dX){
			err += dX;
			curY += modY;
		}
	}*/

	return true;
	

}

//bool Draw::drawGridBox(std::shared_ptr<GameObject> Geo){
//
//	int boundrySize = _screenBoundry;
//	int gridLines = _screenLines;
//
//
//	//Draw Lines (Grid) - hard coded a deep blue
//	for(int startX = (_screenWidth / boundrySize); startX < _screenWidth - (_screenWidth / boundrySize); /* */){
//		drawLine(startX, _screenHeight / boundrySize, startX, _screenHeight - _screenHeight / boundrySize);
//		startX += (_screenWidth / gridLines);
//	}
//
//	for(int startY = (_screenHeight / boundrySize); startY < _screenHeight - (_screenHeight / boundrySize); /* */){
//		drawLine(_screenWidth / boundrySize, startY, _screenWidth - _screenWidth / boundrySize, startY);
//		startY += (_screenHeight / gridLines);
//	}
//
//	//Draw Lines (Box) - white
//	drawLine(_screenWidth / boundrySize, _screenHeight / boundrySize, _screenWidth / boundrySize, _screenHeight - (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
//	drawLine(_screenWidth - _screenWidth / boundrySize, _screenHeight / boundrySize, _screenWidth - _screenWidth / boundrySize, _screenHeight - (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
//	drawLine(_screenWidth / boundrySize, _screenHeight / boundrySize, _screenWidth - _screenWidth / boundrySize, (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
//	drawLine(_screenWidth / boundrySize, _screenHeight - _screenHeight / boundrySize, _screenWidth - _screenWidth / boundrySize, _screenHeight - (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
//
//
//
//
//	return true;
//
//}

void Draw::distortGrid(std::shared_ptr<GameObject> &entity){

	int distortAmount = 5;

	float entityLeft = entity->getX() - getGridX();
	float entityTop = entity->getY() - getGridY();
	float entityRight = entityLeft + entity->getWidth();
	float entityBottom = entityTop + entity->getHeight();

	for(Point &point : _gridPoints){
		if(point.xPos > entityLeft	&&
			point.xPos < entityRight &&
			point.yPos > entityTop	&&
			point.yPos < entityBottom){

				float angle = atan2(point.yPos - entity->getY(), point.xPos - entity->getX());

				float newX = point.xPos + cosf(angle) * distortAmount;
				float newY = point.yPos + sinf(angle) * distortAmount;

				if( newX > point.xReturn - _maxPointChange && newX < point.xReturn + _maxPointChange ){
					point.xPos = newX;
				}

				if( newY > point.yReturn - _maxPointChange && newY < point.yReturn + _maxPointChange ){
					point.yPos = newY;
				}
		}
	}


}

void Draw::updateGrid(const float &deltaTime){

	int returnModifier = 20;

	for(Point &p : _gridPoints){
		//Horizontal return
		if(p.xPos != p.xReturn){
			if(p.xPos < p.xReturn){
				float returnSpeed = (p.xReturn - p.xPos) / returnModifier;
				if(p.xReturn - p.xPos < 0.5){
					p.xPos = p.xReturn;
				} else {
					p.xPos += returnSpeed * deltaTime;
				}
			} else {
				float returnSpeed = (p.xPos - p.xReturn) / returnModifier;
				if(p.xReturn - p.xPos < 0.5){
					p.xPos = p.xReturn;
				} else {
					p.xPos -= returnSpeed * deltaTime;
				}
			}
		}

		//Vertical return
		if(p.yPos != p.yReturn){
			if(p.yPos < p.yReturn){
				float returnSpeed = (p.yReturn - p.yPos) / returnModifier;
				if(p.yReturn - p.yPos < 0.5){
					p.yPos = p.yReturn;
				} else {
					p.yPos += returnSpeed * deltaTime;
				}
			} else {
				float returnSpeed = (p.yPos - p.yReturn) / returnModifier;
				if(p.yPos - p.yReturn < 0.5){
					p.yPos = p.yReturn;
				} else {
					p.yPos -= returnSpeed * deltaTime;
				}
			}
		}
	}
}

bool Draw::drawGridBox(std::shared_ptr<GameObject> Geo){

	/*
		Uses values from the _gridPoint vectors to draw the grid point to point.
		Got a 5 fps increase when drawing grid alone, also needed to do this to
		get the grid warp working.
	*/

	int boundTop =  static_cast<int>(floor(0.5 + _gridY));
	int boundLeft = static_cast<int>(floor(0.5 + _gridX));
	int boundRight = static_cast<int>(floor(0.5 + boundLeft + _screenWidth));
	int boundBottom = static_cast<int>(floor(0.5 + boundTop + _screenHeight));

	for(int pointY = 0; pointY < 33; pointY++){
		for(int pointX = 0; pointX < 50; pointX++){

			int arrayOffset = pointX + (pointY * 53);

			int startX = boundLeft + static_cast<int>(floor(0.5 + _gridPoints[arrayOffset].xPos));
			int startY = boundTop + static_cast<int>(floor(0.5 + _gridPoints[arrayOffset].yPos));
			int endX = boundLeft + static_cast<int>(floor(0.5 + _gridPoints[arrayOffset + 1].xPos));
			int endY = boundTop + static_cast<int>(floor(0.5 + _gridPoints[pointX + ((pointY + 1) * 53)].yPos));

			if(endX > boundRight)
				endX = boundRight;
			
			if(endY > boundBottom)
				endY = boundBottom;

			//HAPI->DebugText("Sx: " + std::to_string(startX) +
			//				"Sy: " + std::to_string(startY) +
			//				"Ex: " + std::to_string(endX) +
			//				"Ey: " + std::to_string(endY));

			HAPI_TColour lineColour(68,76,102);
			//if(_gridPoints[arrayOffset].xPos != _gridPoints[arrayOffset].xReturn ||
			//	_gridPoints[arrayOffset].yPos != _gridPoints[arrayOffset].yReturn){
			//		//lineColour = HAPI_TColour(76, 109, 206);

			//		//int randCol = rand() % 195 + 30;
			//		//lineColour = HAPI_TColour(randCol - 30, randCol, randCol + 30);

			//		//lineColour = HAPI_TColour(rand() % 255, rand() % 255,rand() % 255);
			//}

			//Horizontal line
			drawLine(startX, startY, endX, startY, lineColour);
			//Verticle line
			drawLine(startX, startY, startX, endY, lineColour);

			int b = 1;
		}
	}

	//Draw Lines (Box) - white
	drawLine(boundLeft, boundTop, boundRight, boundTop, HAPI_TColour(255, 255, 255));		//TL -> TR
	drawLine(boundLeft, boundTop, boundLeft, boundBottom, HAPI_TColour(255, 255, 255));		//TL -> BR
	drawLine(boundLeft, boundBottom, boundRight, boundBottom, HAPI_TColour(255, 255, 255)); //BL -> BR
	drawLine(boundRight, boundTop, boundRight, boundBottom, HAPI_TColour(255, 255, 255));	//BR -> TR

	return true;

}

//bool Draw::drawGridBox(std::shared_ptr<GameObject> Geo){
//
//	//int boundrySize = _screenBoundry;
//	//int gridLines = _screenLines;
//
//	int boundrySize = _screenBoundry;
//	int gridLinesH = 50;
//	int gridLinesV = 33;
//
//	int boundTop =  _gridY;
//	int boundLeft = _gridX;
//	int boundRight = boundLeft + _screenWidth;
//	int boundBottom = boundTop + _screenHeight;
//
//	//Draw Lines (Grid) - hard coded a deep blue
//	for(int startX = boundLeft; startX < boundRight; /* */){
//		drawLine(startX, boundTop, startX, boundBottom);
//		startX += (boundRight - boundLeft) / gridLinesH;
//	}
//
//	for(int startY = boundTop; startY < boundBottom; /* */){
//		drawLine(boundLeft, startY, boundRight, startY);
//		startY += (boundBottom - boundTop) / gridLinesV;
//	}
//
//	//Draw Lines (Box) - white
//	drawLine(boundLeft, boundTop, boundRight, boundTop, HAPI_TColour(255, 255, 255));		//TL -> TR
//	drawLine(boundLeft, boundTop, boundLeft, boundBottom, HAPI_TColour(255, 255, 255));		//TL -> BR
//	drawLine(boundLeft, boundBottom, boundRight, boundBottom, HAPI_TColour(255, 255, 255)); //BL -> BR
//	drawLine(boundRight, boundTop, boundRight, boundBottom, HAPI_TColour(255, 255, 255));	//BR -> TR
//
//	return true;
//
//}

bool Draw::drawGridBox(int boundrySize, int gridLines){

	//Draw Lines (Grid) - hard coded a deep blue
	for(int startX = (_screenWidth / boundrySize); startX < _screenWidth - (_screenWidth / boundrySize); /* */){
		drawLine(startX, _screenHeight / boundrySize, startX, _screenHeight - _screenHeight / boundrySize);
		startX += (_screenWidth / gridLines);
	}

	for(int startY = (_screenHeight / boundrySize); startY < _screenHeight - (_screenHeight / boundrySize); /* */){
		drawLine(_screenWidth / boundrySize, startY, _screenWidth - _screenWidth / boundrySize, startY);
		startY += (_screenHeight / gridLines);
	}

	//Draw Lines (Box) - white
	drawLine(_screenWidth / boundrySize, _screenHeight / boundrySize, _screenWidth / boundrySize, _screenHeight - (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
	drawLine(_screenWidth - _screenWidth / boundrySize, _screenHeight / boundrySize, _screenWidth - _screenWidth / boundrySize, _screenHeight - (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
	drawLine(_screenWidth / boundrySize, _screenHeight / boundrySize, _screenWidth - _screenWidth / boundrySize, (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));
	drawLine(_screenWidth / boundrySize, _screenHeight - _screenHeight / boundrySize, _screenWidth - _screenWidth / boundrySize, _screenHeight - (_screenHeight / boundrySize), HAPI_TColour(255, 255, 255));

	return true;

}

void Draw::updateParallax(std::shared_ptr<GameObject> Geo){
	_lastGridX = _gridX;
	_lastGridY = _gridY;

	_gridX = ((Geo->getX() - (_screenWidth / 2)) * -0.4f);
	_gridY = ((Geo->getY() - (_screenHeight / 2)) * -0.4f);

}

void Draw::setupParallax(std::shared_ptr<GameObject> Geo){
	_gridX = Geo->getX() - (_screenWidth / 2);
	_gridY = Geo->getY() - (_screenHeight / 2);
}

//A render that does a memcpy of textureWidth to screen.
//DOES NOT: Handle alpha/transparency
//BUG: Bit buggy... Not sure what causes it
void Draw::speedRender(float drawPosX, float drawPosY, int drawWidth, int drawHeight, BYTE* textureData){
		//if(_textureData != 0 && &screen != 0){

	float posX = drawPosX;
	float posY = drawPosY;

	int textureWidth = drawWidth;
	int textureHeight = drawHeight;	

	int screenWidth = _screenWidth;
	int screenHeight = _screenHeight;

		if( (posX + textureWidth > 0 && posX < screenWidth) && (posY + textureHeight > 0 && posY < screenHeight) ){
			if(textureWidth == 32)
				int b = 1;

			if(posX + textureWidth > screenWidth)
				textureWidth -= static_cast<int>((posX + textureWidth) - screenWidth); 

			if(posY + textureHeight > screenHeight)
				textureHeight -= static_cast<int>((posY + textureHeight) - screenHeight); 

			int maxBytes = (drawWidth * drawHeight) * 4;

			int yCount = 0;
			for(int curByte = 0; curByte < maxBytes; curByte += drawWidth * 4){
				
				int screenOffset = static_cast<int>(posX + (( (posY + yCount) * getWidth() )) * 4);

				memcpy(_pScreen + screenOffset, textureData + curByte, textureWidth * 4);
				
				if(yCount != textureHeight - 1){
					yCount++;
				} else {
					//Exit early.
					return;
				}

			}
		
		}
}


//A simple render function when data is passed in. (Main use for menu background/art)
void Draw::Render(float drawPosX, float drawPosY, int drawWidth, int drawHeight, BYTE* textureData){
		//if(_textureData != 0 && &screen != 0){

	int posX = static_cast<int>(floor(0.5 + drawPosX));
	int posY = static_cast<int>(floor(0.5 + drawPosY));
	int textureWidth = drawWidth;
	int textureHeight = drawHeight;	

	int curX = posX;
	int curY = posY;

	int screenWidth = _screenWidth;
	int screenHeight = _screenHeight;

		if( (posX + textureWidth > 0 && posX < screenWidth) && (posY + textureHeight > 0 && posY < screenHeight) ){

			int maxBytes = (textureWidth * textureHeight) * 4;

			for(int curByte = 0; curByte < maxBytes; curByte += 4){

				//Check to see if this current pixel is out of any bounds, if it is, we'll skip it.
				if( (curX >= 0) && (curY >= 0) && (curY < screenHeight) && (curX < screenWidth) ){

					HAPI_TColour backgroundCol = getPixelCol(curX, curY);
					HAPI_TColour textureCol(textureData[curByte+2], textureData[curByte+1], textureData[curByte], textureData[curByte + 3]);

						float alpha = textureCol.alpha / 255.0f; //Use for float calc

						if(alpha == 255){
							setPixel(curX, curY, textureCol.red, textureCol.green, textureCol.blue);
						} else if(alpha == 0){
							/* DO NOTHING */
						}else {
							
							//Blending from: http://stackoverflow.com/questions/5149722/get-pixel-color-after-alpha-blend
							textureCol.red =  static_cast<BYTE>((textureCol.red * alpha) + (backgroundCol.red * (1.0f - alpha)));
							textureCol.green =  static_cast<BYTE>((textureCol.green * alpha) + (backgroundCol.green * (1.0f - alpha)));
							textureCol.blue =  static_cast<BYTE>((textureCol.blue * alpha) + (backgroundCol.blue * (1.0f - alpha)));

							setPixel(curX, curY, textureCol.red, textureCol.green, textureCol.blue);
						}
						
				}	
				curX++;	

				//If the current X is at the end of the texture, reset X and increase Y.
				if(curX == (posX + textureWidth)){
					curX = posX;
					curY++;
				}

			}
		
		}
}

void Draw::Render(float drawPosX, float drawPosY, int drawWidth, int drawHeight, int assetID, float entityAngle, int frameNumber, bool floatCalc){
	//if(_textureData != 0 && &screen != 0){

	float posX = drawPosX;
	float posY = drawPosY;
	int textureWidth = drawWidth;
	int textureHeight = drawHeight;
	BYTE * entityTexture/* = _gameState->getAsset(assetID)->getTexture()*/;

	//int frameNum = _gameState->getAsset(assetID)->getMaxFrame();
	if(_gameState->getAsset(assetID)->getMaxFrame() != 0){
		//int frameCalc = frameNumber % _gameState->getAsset(assetID)->getMaxFrame();
		entityTexture = _gameState->getAsset(assetID)->getTexture(frameNumber);
	} else {
		entityTexture = _gameState->getAsset(assetID)->getTexture();;
	}

	

		int curX = static_cast<int>(floor(posX + 0.5));
		int curY = static_cast<int>(floor(posY + 0.5));

		int floorInitPosX = static_cast<int>(floor(posX + 0.5));
		int floorInitPosY = static_cast<int>(floor(posY + 0.5));

		int screenWidth = _screenWidth;
		int screenHeight = _screenHeight;

		if( (floorInitPosX + textureWidth > 0 && floorInitPosX < screenWidth) && (floorInitPosY + textureHeight > 0 && floorInitPosY < screenHeight) ){

			int midX = floorInitPosX + (textureWidth / 2);
			int midY = floorInitPosY + (textureHeight / 2);

			int rotX = curX;
			int rotY = curY;

			int maxBytes = (textureWidth * textureHeight) * 4;

			for(int curByte = 0; curByte < maxBytes; curByte += 4){

				rotX = curX;
				rotY = curY;

				//HAPI->DebugText(std::to_string(entityAngle));

				if(entityAngle != 0){
					Rotate(entityAngle, rotX, rotY, midX, midY);
				}

				//Check to see if this current pixel is out of any bounds, if it is, we'll skip it.
				if( !(rotX < 0) && !(rotY < 0) && !(rotY > screenHeight - 1) && !(rotX > screenWidth - 1) ){

					HAPI_TColour backgroundCol = getPixelCol(rotX, rotY);
					HAPI_TColour textureCol(entityTexture[curByte+2], entityTexture[curByte+1], entityTexture[curByte], entityTexture[curByte + 3]);

					if(floatCalc){

						float alpha = textureCol.alpha / 255.0f; //Use for float calc

						if(alpha == 255){
							setPixel(rotX, rotY, textureCol.red, textureCol.green, textureCol.blue);
						} else if(alpha == 0){
							/* DO NOTHING */
						}else {
							/*
							////////////////////////////////////////////////////
							// **************** TEST RESULTS **************** //
							//				   #ENTITIES : FPS				  //
							//________________________________________________//
							//	Float:				|	Bit Shift:			  //
							//	25: 145				|	25: 147				  //
							//	45: 140				|	45: 142				  //
							//	69: 134				|	69: 137				  //
							//	89: 131				|	89: 134				  //
							//	109: 126			|	109: 129			  //
							//	129: 119			|	129: 124			  //
							//	153: 112			|	153: 119			  //
							////////////////////////////////////////////////////
							*/
							
							//Blending from: http://stackoverflow.com/questions/5149722/get-pixel-color-after-alpha-blend
							textureCol.red =  static_cast<BYTE>((textureCol.red * alpha) + (backgroundCol.red * (1.0f - alpha)));
							textureCol.green =  static_cast<BYTE>((textureCol.green * alpha) + (backgroundCol.green * (1.0f - alpha)));
							textureCol.blue =  static_cast<BYTE>((textureCol.blue * alpha) + (backgroundCol.blue * (1.0f - alpha)));

							setPixel(rotX, rotY, textureCol.red, textureCol.green, textureCol.blue);
						}
					} else {
						
						int alpha = textureCol.alpha / 255;	//Use for bitshift

						if(alpha == 255){
							setPixel(rotX, rotY, textureCol.red, textureCol.green, textureCol.blue);
						} else if(alpha == 0){
							/* DO NOTHING */
						}else {

							//Bitshift calc: Result = Destination+(Alpha*(Source-Destination))>>8 -- From https://scm-intranet.tees.ac.uk/users/u0018197/Downloads/GEC/W4%20-%20GEC.pdf
							textureCol.red = textureCol.red + ((alpha * (backgroundCol.red - textureCol.red)) >> 8);
							textureCol.blue = textureCol.blue + ((alpha * (backgroundCol.blue - textureCol.blue)) >> 8);
							textureCol.green = textureCol.green + ((alpha * (backgroundCol.green - textureCol.green)) >> 8);

							setPixel(rotX, rotY, textureCol.red, textureCol.green, textureCol.blue);
						}
					}

				}


				curX++;		

				//If the current X is at the end of the texture, reset X and increase Y.
				if(curX == (floorInitPosX + textureWidth)){
					curX = floorInitPosX;
					curY++;
				}


			}
		
		}
	//}
}


void Draw::Rotate(const double angle, int &posX, int &posY, const int midX, const int midY){
	int newX, newY;

	posX -= midX;
	posY -= midY;

	newX = static_cast<int>( floor( 0.5 + ((posX * cos(angle)) - (posY * sin(angle)))) );
	newY = static_cast<int>( floor( 0.5 + ((posX * sin(angle)) + (posY * cos(angle)))) );

	posX = newX + midX;
	posY = newY + midY;
	//HAPI->DebugText("PosX: " + std::to_string(posX) + " - PosY: " + std::to_string(posY));
}