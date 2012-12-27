#include "World.h"
#include "Draw.h"
#include "GameObject.h"
#include "Player.h"
#include "ControlInput.h"
#include "Bullet.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "SoundManager.h"
#include "Enemy.h"

#include "ParticleEmitter.h"

//Game Modes
#include "EvolvedGame.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <iostream>


World::World(int screenWidth, int screenHeight) :  _gameMode(NULL), _render(new Draw(_gameMode, screenWidth, screenHeight, 8, 30)), _controllers(new ControlInput),
												   _soundManager(new SoundManager())
{
	_gameMenu.reset(new MainMenu(_soundManager));
	_currentTime = 0;
	_nextShot = 0;
	_lastTime = 0;
	_deltaTime = 0;
	_movementInput = false;
	_inMenues = true;
}


World::~World(void)
{
}

void World::restartWorld(){
	_gameMode.reset(new EvolvedGame);

	if(!_entityList.empty()){
		_entityList.clear();
	}

	setupWorld();
}

void World::loadMode(int gameID){
	if(!_entityList.empty()){
		_entityList.clear();
	}

	if(gameID == EVOLVED_GAME){
		_soundManager->playAudio(EVOLVED_MUSIC);
		_gameMode.reset(new EvolvedGame);
	} else if(gameID == DEADLINE_GAME){
		//Nothing yet.
	}

	_render->changeStatePtr(_gameMode);
}

float World::translateToGridX(float posX){
	return (posX - _render->getGridX());
}

float World::translateToGridY(float posY){
	return (posY - _render->getGridY());
}

void World::translateToGrid(float& posX, float& posY){
	posX = posX - _render->getGridX();
	posY = posY - _render->getGridX();
}

bool World::getGraphicsSettings(){
	return _graphicsToggle;
}

void World::setGraphicsSettings(bool highGraphics){
	_graphicsToggle = highGraphics;
}


std::vector<std::string> World::readHighscore(){
	std::ifstream inScoreFile;
	std::vector<std::string> fileLines;
	std::string currentLine;

	//Open file, read data into string vector
	inScoreFile.open("highscore.txt", std::ios::out);
	if(inScoreFile.is_open()){
		while(!inScoreFile.eof() && fileLines.size() < 5){ //Only want to display top 5 highscores.
			std::getline(inScoreFile, currentLine);

				fileLines.push_back(currentLine);
		}

		inScoreFile.close();

	} else {
		//Highscore file should have been made if we're trying to read it..
		fileLines.push_back("NO HIGHSCORES");
	}

	return fileLines;

}

void World::writeHighscore(unsigned long int score){
	std::ifstream inScoreFile;
	std::ofstream outScoreFile;
	std::vector<std::string> fileLines;
	std::string currentLine;
	bool scoreAdded = false;

	//Open file, read data into string vector
	inScoreFile.open("highscore.txt", std::ios::out);
	if(inScoreFile.is_open()){
		while(!inScoreFile.eof()){
			std::getline(inScoreFile, currentLine);

			//Check if score is higher than the current value, if it is, insert it first.
			if(currentLine != ""){
				if(score > std::stoul(currentLine) && !scoreAdded){
					fileLines.push_back(std::to_string(score));
					scoreAdded = true;
				}
				fileLines.push_back(currentLine);
			}
		}

		if(!scoreAdded){
			fileLines.push_back(std::to_string(score));
		}

		inScoreFile.close();

	} else {
		//Problem opening file, do most likely doesnt exist.
		//Add our score to the list so ofstream can write some data
		fileLines.push_back(std::to_string(score));
	}

	//Now use the string vector to write the fata out again
	outScoreFile.open("highscore.txt", std::ios::out | std::ios::trunc);
	if(outScoreFile.is_open()){
		for(std::string line : fileLines){
			outScoreFile << line << "\n";
		}

		outScoreFile.close();
	} else {
		//Unable to open
	}


}

bool World::setupWorld(){

	if(!_gameMode->loadAssets())
		return false;

	//_render->setupAssetPointer(_gameMode->getGameAssetsPtr());
	//_render->changeStatePtr(_gameMode);

	//Load Geo
	//_entityList.push_front(std::shared_ptr<GameObject>(new GameObject(32.f, 32.f, _render->getWidth() / 2, _render->getHeight() / 2)));
	_entityList.push_front(std::shared_ptr<GameObject>(new Player(_render->getWidth() / 2.f, _render->getHeight() / 2.f)));
	_Geo = _entityList.front();
	_Geo->setTexture(_gameMode->getAssetID("geo"));
	_Geo->setMaxFrame(_gameMode->getAsset(_Geo->getAssetID())->getMaxFrame());
	_Geo->setDeathTexture(_gameMode->getAssetID("particle_geodeath"));

	//Setup the parallax grid
	_render->setupParallax(_Geo);

	return true;
}

void World::update(){

	if(_inMenues){
		_controllers->updateControllers();
		HAPI_TControllerData playerOne = _controllers->getXbox();
		HAPI_TKeyboardData keyboardData = _controllers->getKeyboard();

		if(playerOne.digitalButtons[HK_DIGITAL_DPAD_UP] || playerOne.digitalButtons[HK_DIGITAL_DPAD_DOWN]){
			int changeDirection = 0;

			if(playerOne.digitalButtons[HK_DIGITAL_DPAD_UP])
				changeDirection -= 1;

			if(playerOne.digitalButtons[HK_DIGITAL_DPAD_DOWN])
				changeDirection += 1;

			//Borrow the nextShot variable (normally used for bullets) to create a cooldown on the menu selection.
			if(HAPI->GetTime() > _nextShot){
				_gameMenu->changeItem(changeDirection);
				_nextShot = HAPI->GetTime() + 200;
			}
		}

		if(playerOne.digitalButtons[HK_DIGITAL_A]){
			//Borrow the nextShot variable (normally used for bullets) to create a cooldown on the menu selection.
			if(HAPI->GetTime() > _nextShot){
				_gameMenu->selectedItem(_inMenues, _gameMenu, shared_from_this());
				_currentTime = HAPI->GetTime();
				_nextShot = HAPI->GetTime() + 200;
			}
		}
		

		_gameMenu->update(_render);

	} else {

		//Update time
		_lastTime = _currentTime;
		_currentTime = HAPI->GetTime();

		_deltaTime = (_currentTime - _lastTime) / 10.0f;

		_controllers->updateControllers();

#pragma region PCInput

		HAPI_TControllerData playerOne = _controllers->getXbox();
		HAPI_TKeyboardData keyboardData = _controllers->getKeyboard();
		HAPI_TMouseData mouseData = _controllers->getMouse();

		//Mouse Input
		if(mouseData.leftButtonDown){
			if(_currentTime > _nextShot){

				//HAPI->PlayASound(_gameMode->getFireSoundAsset()->getSound());
				HAPI->PlayASound(_gameMode->getAsset(_gameMode->getAssetID("fire_normal"))->getSound());

				//Calc angle, need to do X - shipX as that is the object we want the angle from.
				float angle = static_cast<float>(floor(0.5 + (atan2( mouseData.y - _Geo->getY(), mouseData.x - _Geo->getX() ))));

				float bulletX = _Geo->getX() + (_Geo->getWidth() / 2) - 8;
				float bulletY = _Geo->getY() + (_Geo->getHeight() / 2) - 8;

				_entityList.push_front(std::shared_ptr<Bullet>(new Bullet(16,16, bulletX, bulletY, 1.f*cosf(angle), 1.f*sinf(angle), _Geo->getSpeed(), angle + 1.5f) ));
				_entityList.front()->setTexture(_gameMode->getAssetID("bullet"));

				_nextShot = _currentTime + 210;

			}
		}

		//Keyboard WASD
		//Offset X/Y
		if(keyboardData.scanCode['W'] || keyboardData.scanCode['S']|| keyboardData.scanCode['A']|| keyboardData.scanCode['D']){

			int modX = 0;
			int modY = 0;

			//W
			if(keyboardData.scanCode['W']){
				modY -= 3;
			}

			//S
			if(keyboardData.scanCode['S']){
				modY += 3;
			}

			//A
			if(keyboardData.scanCode['A']){
				modX -= 3;
			}

			//D
			if(keyboardData.scanCode['D']){
				modX += 3;
			}

			float newX = _Geo->getX() + modX * _deltaTime;
			float newY = _Geo->getY() + modY * _deltaTime;
			_Geo->setAngle(static_cast<float>(floor(0.5 + atan2(modY, modX))));


			//if( (newX > _render->getWidth() / _render->getScreenBoundry()) && (newX < _render->getWidth() - (_render->getWidth() / _render->getScreenBoundry()) - Geo->getTextureWidth() ) ){
			if( (newX > _render->getGridX()) && (newX < (_render->getGridX() + _render->getWidth() - _Geo->getWidth()) )){
				_Geo->setX(newX);
			}
			//}

			//if( (newY > _render->getHeight() / _render->getScreenBoundry()) && (newY < _render->getHeight() - (_render->getHeight() / _render->getScreenBoundry()) - Geo->getTextureHeight() ) ){
			if ( (newY > _render->getGridY()) && (newY < (_render->getGridY() + _render->getHeight() - _Geo->getHeight()) )){
				_Geo->setY(newY);
			}
			//}

			//Currently sets speed, however if the play moves right, the bullet still goes fast when shot left, this shouldn't happen.
			float speedX = abs(modX / 3.0f * 10.0f);
			float speedY = abs(modY / 3.0f * 10.0f);

			float calculatedSpeed = speedX + speedY;

			if(calculatedSpeed > 10){
				calculatedSpeed = 10;
			}

			_Geo->setSpeed(calculatedSpeed);
			_movementInput = true;

		}

		//Keyboard input, more info (VKeys): http://www.siongboon.com/projects/2007-12-08_ascii_code/index.htm
		if(keyboardData.scanCode['P']){
			//DO PAUSE
		}

#pragma endregion mouse and keyboard input

#pragma region XboxInput

		//Left Stick
		//Offset X/Y
		if(playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE || playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE ||
			playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE || playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE ){

				//Give Geo an angle so it can be rendered correctly later.
				float angle = atan2( ((playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] * -1) - _Geo->getY()), playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] - _Geo->getX());
				_Geo->setAngle(angle);

				float newX = (_Geo->getX() + ((playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] / 10000.0f) * _deltaTime));
				float newY = (_Geo->getY() + (((playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] / 10000.0f) * -1) * _deltaTime));



				//if( (newX > _render->getWidth() / _render->getScreenBoundry()) && (newX < _render->getWidth() - (_render->getWidth() / _render->getScreenBoundry()) - Geo->getTextureWidth() ) ){
				if( (newX > _render->getGridX() + 5) && (newX < (_render->getGridX() + _render->getWidth() - (_Geo->getWidth() + 5)) )){
					_Geo->setX(newX);
					_Geo->setDirectionX(1*cos(angle));
				}
				//}

				//if( (newY > _render->getHeight() / _render->getScreenBoundry()) && (newY < _render->getHeight() - (_render->getHeight() / _render->getScreenBoundry()) - Geo->getTextureHeight() ) ){
				if ( (newY > _render->getGridY() + 5) && (newY < (_render->getGridY() + _render->getHeight() - (_Geo->getHeight() + 5)) )){
					_Geo->setY(newY);
					_Geo->setDirectionY(1*sin(angle));
				}
				//}

				//Create the Geo Trail
				_emitterList.push_back(std::shared_ptr<ParticleEmitter>(new ParticleEmitter(_Geo->getX() + _Geo->getWidth() / 2, _Geo->getY() + _Geo->getHeight() / 2, 1, _gameMode->getAssetID("particle_trail"), angle - static_cast<float>(floor(0.5 + M_PI)))));


				//Currently sets speed, however if the play moves right, the bullet still goes fast when shot left, this shouldn't happen.
				float speedX = abs((playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] / 32767.0f) * 10);
				float speedY = abs(((playerOne.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] / 32767.0f) * -1) * 10);


				float calculatedSpeed = speedX + speedY;

				if(calculatedSpeed > 10){
					calculatedSpeed = 10;
				}

				_Geo->setSpeed(calculatedSpeed);
				_movementInput = true;

		} 

		if(!_movementInput){
			_Geo->setSpeed(3);
		}

		_movementInput = false;

		//Right Stick
		if(playerOne.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE || playerOne.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE ||
			playerOne.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE || playerOne.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE ){

				if(_currentTime > _nextShot){

					//HAPI->PlayASound(_gameMode->getAsset(_gameMode->getAssetID("bullet"))->getSound());
					_soundManager->playAudio(BULLET_SOUND);

					//Calc angle, need to do X - shipX as that is the object we want the angle from.
					float angle = atan2( (playerOne.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] - _Geo->getX()) * -1, playerOne.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] - _Geo->getY());

					//Remove 5 degrees from shooting angle, as we shoot 3 bullets, we want to spray like \|/ so start 5 degrees less
					angle -= static_cast<float>(floor( 0.5 + (5 * M_PI / 180.0)));

					float bulletX = _Geo->getX() + (_Geo->getWidth() / 2) - 8;
					float bulletY = _Geo->getY() + (_Geo->getHeight() / 2) - 8;

					for(int curBullet = 0; curBullet < 3; curBullet++){
						_entityList.push_front(std::shared_ptr<Bullet>(new Bullet(16,16, bulletX, bulletY, 
							1*cosf(angle + ((curBullet * 5) * static_cast<float>(M_PI) / 180.f)),
							1*sinf(angle + ((curBullet * 5) * static_cast<float>(M_PI) / 180.f)),
							_Geo->getSpeed() + rand() % 3, angle + 1.5f) ));

						_entityList.front()->setTexture(_gameMode->getAssetID("bullet"));
						_entityList.front()->setDeathTexture(_gameMode->getAssetID("particle_bullet"));
					}

					_nextShot = _currentTime + 100;

				}

				//Dbug
				//std::string debugStick = "Thumb X: " + std::to_string(playerOne->analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X]) 
				//						+ " Thumb Y: " + std::to_string(playerOne->analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y])
				//						+ " Calced Angle: " + std::to_string(angle);
				//HAPI->RenderText(0, (screenHeight - 75), HAPI_TColour(255, 0, 0), debugStick);

		}

		if(playerOne.digitalButtons[HK_DIGITAL_START]){
			_inMenues = true;
			_gameMenu.reset(new PauseMenu(_soundManager));
		}


		if(playerOne.digitalButtons[HK_DIGITAL_RIGHT_SHOULDER]){
			setGraphicsSettings(!getGraphicsSettings());
		}


		//Test setting channel frequency
		//if(playerOne->digitalButtons[HK_DIGITAL_Y]){
		//			channel->setFrequency(60000);
		//} else if(playerOne->digitalButtons[HK_DIGITAL_A]){
		//			channel->setFrequency(30000);
		//} else if(playerOne->digitalButtons[HK_DIGITAL_X]){
		//			channel->setFrequency(48000);
		//}

#pragma endregion LS/RS Analog input + Buttons

		//Update sound system
		_soundManager->update();

		//See if we need to spawn anything
		_gameMode->spawnWaves(_entityList, _render, _Geo, _soundManager);

		//currentMode->updateParallax(Geo);

		//int changeInX = 0;
		//int changeInY = 0;

		_render->updateParallax(_Geo);

		//Clear screen - Default black
		_render->setScreenCol();

		//Draw the screen gridbox
		_render->updateGrid(_deltaTime);
		_render->drawGridBox(_Geo);

		//currentMode->renderParallax(screen);

		//Update emitters and render -- Do this BEFORE entities or particles will appear over them
		for(std::shared_ptr<ParticleEmitter> emitter : _emitterList){
			emitter->update(_deltaTime);

			for(int particle = 0; particle < emitter->getAmountParticles(); particle++){
				std::shared_ptr<GameObject> entity = emitter->getParticle(particle);
				_render->Render(entity->getX(), entity->getY(), 
					entity->getWidth(), entity->getHeight(), 
					entity->getAssetID(), entity->getAngle(), 
					entity->getFrame());
			}
		}

		//Delete any emitters
		_emitterList.remove_if([&](std::shared_ptr<ParticleEmitter> emitter) -> bool{
			return !emitter->getAlive();
		}
		);

		//Causes quite a significant drop in FPS - Fixes the Parallax issue though...
		float changeInGridX = _render->getGridX() - _render->getLastGridX();
		float changeInGridY = _render->getGridY() - _render->getLastGridY();

		//Loop over and Update/Chase, Check Collision.
		for(std::shared_ptr<GameObject> entity : _entityList){

			entity->setX(entity->getX() + changeInGridX);
			entity->setY(entity->getY() + changeInGridY);

			entity->Update(_deltaTime);
			entity->Chase(_Geo, _deltaTime);
			_render->distortGrid(entity);

			for(std::shared_ptr<GameObject> checkAgainst : _entityList){
				if(entity != checkAgainst){
					entity->CheckCollision(checkAgainst);
					
				}
			}

			//Render entity if it's alive
			if(entity->getAlive()){
				_render->Render(entity->getX(), entity->getY(), 
					entity->getWidth(), entity->getHeight(), 
					entity->getAssetID(), entity->getAngle(), 
					entity->getFrame(),
					getGraphicsSettings());
			}

		}

		//Check if player has died
		if(!_Geo->getAlive()){
			_inMenues = true;
			writeHighscore(_gameMode->getHighscore());
			_gameMenu.reset(new GameOverMenu(_soundManager));
			_gameMenu->setHighscore(readHighscore());
		}

		//Remove any entity that has gone out of bounds or is marked as dead (getAlive())
		_entityList.remove_if([&](std::shared_ptr<GameObject> entity) -> bool{
			if(entity->getX() < _render->getGridX() || entity->getX() > (( _render->getGridX() +  _render->getWidth()) - entity->getWidth()) 
				|| entity->getY() <  _render->getGridY() || entity->getY() > ( _render->getGridY() +  _render->getHeight()) - entity->getHeight()
				|| entity->getAlive() == false){
					_gameMode->addScore(entity->getObjectType());
					_emitterList.push_back(std::shared_ptr<ParticleEmitter>(new ParticleEmitter(entity->getX(), entity->getY(), 0, entity->getDeathAssetID())));

					if(entity->getObjectSide() == ENEMY){
						_soundManager->playAudio(ENEMY_EXPLODE);
					}

					//If the entity is of type ENEMY_PURPLE then spawn little purple enemies
					if(entity->getObjectType() == ENEMY_PURPLE){
						//Could have a for loop here and calculate using cos/sin but it's probably cheaper just to have 3 of the same lines
						_entityList.push_front(std::shared_ptr<Enemy>(new Enemy(8, 8, entity->getX() + 16.f, entity->getY() - 16.f, 2, ENEMY_PURPLE_MINI, _gameMode->getAssetID("enemy_purple_mini"), _gameMode->getAssetID("particle_purple"))));

						_entityList.push_front(std::shared_ptr<Enemy>(new Enemy(8, 8, entity->getX(), entity->getY() + 32.f, 2, ENEMY_PURPLE_MINI, _gameMode->getAssetID("enemy_purple_mini"), _gameMode->getAssetID("particle_purple"))));

						_entityList.push_front(std::shared_ptr<Enemy>(new Enemy(8, 8, entity->getX() + 32.f, entity->getY() + 32.f, 2, ENEMY_PURPLE_MINI, _gameMode->getAssetID("enemy_purple_mini"), _gameMode->getAssetID("particle_purple"))));

					}

					return true;
			} else {
				return false;	
			}
		}
		);

		_render->drawLine(0, 0, 400, 400);


		//Render game score/hud
		_gameMode->renderHUD(*_render);

		//HAPI->DebugText("Num Entities: " + std::to_string(_entityList.size()));
		HAPI->RenderText(0, 30, HAPI_TColour(), "dT: " + std::to_string(_deltaTime));

	}


}