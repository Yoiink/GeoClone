#include "EvolvedGame.h"
//#include "Enemy.h"
#include "EnemyPurple.h"
#include "EnemyBlue.h"
#include "EnemyOrange.h"
#include "SoundManager.h"


EvolvedGame::EvolvedGame(void) : _spawnMode(0), _timeLastSpawn(0), _spawnComplete(true), _spawnWave(0), _spawnCooldown(3000),
	_gameScore(0), _bgPosX(-1024), _bgPosY(-530), _highscoreFile("evolvedScore"), _livesLeft(3)
{
}


EvolvedGame::~EvolvedGame(void)
{
}

bool EvolvedGame::loadAssets(){

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/bullet.png", LOAD_IMAGE, "bullet", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_purple.png", LOAD_IMAGE, "particle_purple", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_blue.png", LOAD_IMAGE, "particle_blue", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_green.png", LOAD_IMAGE, "particle_green", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_trail.png", LOAD_IMAGE, "particle_trail", static_cast<int>(_gameAssets.size() - 1))))
		return false;
	if(!_gameAssets.back()->loadAnimation(32, 4, 4))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_bullet.png", LOAD_IMAGE, "particle_bullet", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_geodeath.png", LOAD_IMAGE, "particle_geodeath", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/Geo.png", LOAD_IMAGE, "geo", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	//if(!(_gameAssets.back()->Load("GeoAnimate.png", LOAD_IMAGE, "geo", static_cast<int>(_gameAssets.size() - 1))))
	//	return false;

	//if(!_gameAssets.back()->loadAnimation(6, 32, 32))
	//	return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_purple.png", LOAD_IMAGE, "enemy_purple", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_purple_mini.png", LOAD_IMAGE, "enemy_purple_mini", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_blue.png", LOAD_IMAGE, "enemy_blue", static_cast<int>(_gameAssets.size() - 1))))
		return false;


	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/bg_parallax.png", LOAD_IMAGE, "enemy_purple", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_orange.png", LOAD_IMAGE, "enemy_orange", static_cast<int>(_gameAssets.size() - 1))))
		return false;

	return true;
}

std::shared_ptr<Asset> EvolvedGame::getAsset(int assetID) const{
	return _gameAssets.at(assetID);
}

void EvolvedGame::resetScore(){
	_gameScore = 0;
}

//Change this to a bool? If there's a problem we're still setting the ID.
int EvolvedGame::getAssetID(std::string assetName) const{
	for(std::shared_ptr<Asset> curAsset : _gameAssets){
		if(curAsset->getName() == assetName){
			return curAsset->getID();
		}
	}
	return 0;
}

unsigned long int EvolvedGame::getHighscore() const{
	return _gameScore;
}

std::string EvolvedGame::getHighscoreFile() const{
	return _highscoreFile;
}

bool EvolvedGame::isGameOver(std::list<std::shared_ptr<GameObject>> &entityList){
	if(_livesLeft > 0){
		_livesLeft--;

		//Remove all enemies
		entityList.remove_if([&](std::shared_ptr<GameObject> entity) -> bool{
				if(entity->getObjectSide() == ENEMY){
					return true;
				} else {
					return false;
				}
			}
		);

		//Reset the spawn wave
		_spawnComplete = true;

		//Set spawn cooldown to two seconds to allow player timen to recover.
		_spawnCooldown = HAPI->GetTime() + 2000;

		return false;
	}
	return true;
}

void EvolvedGame::spawnWaves(std::list<std::shared_ptr<GameObject>> &entityList, std::shared_ptr<Draw> &screen, std::shared_ptr<GameObject> &Geo, std::shared_ptr<SoundManager> &sound){

	_currentTime = HAPI->GetTime();

	if(_spawnCooldown < _currentTime){
		if(_spawnComplete){
			_spawnMode = rand() % 15;
			//_spawnMode = -2;
			_spawnComplete = false;
			_timeLastSpawn = _currentTime;
		}

		//Calculate the corners
		float playLeft = screen->getGridX() + 10;
		float playTop = screen->getGridY() + 10;
		float playRight = screen->getGridX() + screen->getWidth() - 40;
		float playBottom = screen->getGridY() + screen->getHeight() - 40;

		if(_spawnMode <= 3){ //Spawn from corners and 4 random spawns
			if(_timeLastSpawn <= _currentTime){
				if(_spawnWave < 5){
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(playLeft, playTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					sound->playAudio(PURPLE_SPAWN);

					entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(playRight, playTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					sound->playAudio(BLUE_SPAWN);

					//entityList.push_front(std::shared_ptr<Enemy>(new Enemy(32, 32, playLeft, playBottom, 2, ENEMY_PURPLE, getAssetID("enemy_purple"))));
					//entityList.front()->setDeathTexture(getAssetID("particle_purple"));
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(playLeft, playBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					sound->playAudio(PURPLE_SPAWN);

					entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(playRight, playBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					sound->playAudio(BLUE_SPAWN);

					_timeLastSpawn = _currentTime + 1000;
				} else {
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(rand() % static_cast<int>(playRight) + playLeft , rand() % static_cast<int>(playBottom) + playTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					sound->playAudio(BLUE_SPAWN);

					entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(rand() % static_cast<int>(playRight) + playLeft, rand() % static_cast<int>(playBottom) + playTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					sound->playAudio(PURPLE_SPAWN);

					entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(rand() % static_cast<int>(playRight) + playLeft , rand() % static_cast<int>(playBottom) + playTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					sound->playAudio(BLUE_SPAWN);

					entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(rand() % static_cast<int>(playRight) + playLeft, rand() % static_cast<int>(playBottom) + playTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					sound->playAudio(PURPLE_SPAWN);

					_spawnComplete = true;
					_spawnWave = 0;
					_spawnCooldown = _currentTime + 3000;
				}
				_spawnWave++;
			}
		} else if(_spawnMode >= 4 && _spawnMode <= 5){ //Spawns a box around the player

			float boxLeft = Geo->getX() - 400;
			float boxRight = Geo->getX() + 400;
			float boxTop  = Geo->getY() - 200;
			float boxBottom = Geo->getY() + 200;
			float rowGap = 0;

			if(boxLeft < playLeft)
				boxLeft = playLeft + 30;

			if(boxRight > playRight)
				boxRight = playRight - 30;

			if(boxTop < playTop)
				boxTop = playTop + 30;

			if(boxBottom > playBottom)
				boxBottom = playBottom - 30;

			rowGap = (boxBottom - boxTop) / 5;

			//Random between blue spawn/purple spawn
			if(rand() % 100 > 50){

				for(int rowCount = 1; rowCount < 6; rowCount++){
					if(rowCount == 1){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxLeft, boxTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxLeft + 200, boxTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(Geo->getX(), boxTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxRight, boxTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxRight - 200, boxTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					} else if(rowCount == 5){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxLeft, boxBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxLeft + 200, boxBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(Geo->getX(), boxBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxRight, boxBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxRight - 200, boxBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					} else {
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxLeft, boxTop + rowGap * rowCount, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxRight, boxTop + rowGap * rowCount, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					}
				}

			} else {
				for(int rowCount = 1; rowCount < 6; rowCount++){
					if(rowCount == 1){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxLeft, boxTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxLeft + 200, boxTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(Geo->getX(), boxTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxRight, boxTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxRight - 200, boxTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					} else if(rowCount == 5){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxLeft, boxBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxLeft + 200, boxBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(Geo->getX(), boxBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxRight, boxBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxRight - 200, boxBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					} else {
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxLeft, boxTop + rowGap * rowCount, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(boxRight, boxTop + rowGap * rowCount, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					}
				}
			}

			_spawnComplete = true;
			_spawnWave = 0;
			_spawnCooldown = _currentTime + 6000;
		} else if(_spawnMode >= 6 && _spawnMode <= 8){  //Spawns a circle around the player 
			int maxEnemies = 16;
			
			for(int enemyCount = 0; enemyCount < maxEnemies; enemyCount++){
				float angle = (enemyCount * (360.0f / maxEnemies));
				float xAdd = 1*cos(angle);
				float yAdd = 1*sin(angle);
				int spawnDistance = 300;

				float calcSpawnX = Geo->getX() + (xAdd * spawnDistance);
				float calcSpawnY = Geo->getY() + (yAdd * spawnDistance);

				if(calcSpawnX < playLeft)
					calcSpawnX = playLeft + 10;
				

				if(calcSpawnY < playTop)
					calcSpawnY = playTop + 10;
				

				if(calcSpawnX > playRight)
					calcSpawnX = playRight - 40;

				if(calcSpawnY > playBottom)
					calcSpawnY = playBottom - 40;

				//Random between blue spawn/purple spawn
				if(rand() % 100 > 50){
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(calcSpawnX, calcSpawnY, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					sound->playAudio(PURPLE_SPAWN);
				} else {
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(calcSpawnX, calcSpawnY, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					sound->playAudio(BLUE_SPAWN);
				}

			}
				
			_spawnComplete = true;
			_spawnWave = 0;
			_spawnCooldown = _currentTime + 1000;

		} else if(_spawnMode >= 9 && _spawnMode <= 10){ //Spawn 20 random enemies randomly every 100 milliseconds
			if(_spawnWave != 20){

				float xPos = rand() % static_cast<int>(playRight) + playLeft;
				float yPos = rand() % static_cast<int>(playBottom) + playTop;

				//Random between blue spawn/purple spawn
				if(rand() % 100 > 50){
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(xPos, yPos, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
					sound->playAudio(PURPLE_SPAWN);
				} else {
					entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(xPos, yPos, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
					sound->playAudio(BLUE_SPAWN);
				}

				_spawnWave++;
				_spawnCooldown = _currentTime + 100;
			} else {
				_spawnComplete = true;
				_spawnWave = 0;
				_spawnCooldown = _currentTime + 5000;
			}
		} else if(_spawnMode >= 11 && _spawnMode <= 12){ //Spawn random enemies from a random wall (Blue / Purple)
			int enemiesToSpawn = 10;
			int wallSelect = rand() % 4;
			float enemyOffset = 0;

			switch(wallSelect){
			case 0: //LEFT WALL
				enemyOffset = ((playTop + 20) + (playBottom - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
					//Random between blue spawn/purple spawn
					if(rand() % 100 > 50){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(playLeft, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						sound->playAudio(PURPLE_SPAWN);
					} else {
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(playLeft, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						sound->playAudio(BLUE_SPAWN);
					}
				}
				break;
			case 1: //RIGHT WALL
				enemyOffset = ((playTop + 20) + (playBottom - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
					//Random between blue spawn/purple spawn
					if(rand() % 100 > 50){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(playRight, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						sound->playAudio(PURPLE_SPAWN);
					} else {
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(playRight, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						sound->playAudio(BLUE_SPAWN);
					}
				}
				break;
			case 2: //TOP WALL
				enemyOffset = ((playLeft + 20) + (playRight - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
					//Random between blue spawn/purple spawn
					if(rand() % 100 > 50){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(playLeft + (enemyCounter * enemyOffset), playTop, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						sound->playAudio(PURPLE_SPAWN);
					} else {
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(playLeft + (enemyCounter * enemyOffset), playTop, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						sound->playAudio(BLUE_SPAWN);
					}
				}
				break;
			case 3: //BOTTOM WALL
				enemyOffset = ((playLeft + 20) + (playRight - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
					//Random between blue spawn/purple spawn
					if(rand() % 100 > 50){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(playLeft + (enemyCounter * enemyOffset), playBottom, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
						sound->playAudio(PURPLE_SPAWN);
					} else {
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyBlue(playLeft + (enemyCounter * enemyOffset), playBottom, getAssetID("enemy_blue"), getAssetID("particle_blue"))));
						sound->playAudio(BLUE_SPAWN);
					}
				}
				break;
			}

			_spawnComplete = true;
			_spawnWave = 0;
			_spawnCooldown = _currentTime + 5000;

		} else if(_spawnMode >= 13){ //Spawn orange from wall
			int enemiesToSpawn = 10;
			int wallSelect = rand() % 4;
			float enemyOffset = 0;

			switch(wallSelect){
			case 0: //LEFT WALL
				enemyOffset = ((playTop + 20) + (playBottom - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playLeft, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionX(1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			case 1: //RIGHT WALL
				enemyOffset = ((playTop + 20) + (playBottom - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
					//Random between blue spawn/purple spawn
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playRight, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionX(-1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			case 2: //TOP WALL
				enemyOffset = ((playLeft + 20) + (playRight - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playLeft + (enemyCounter * enemyOffset), playTop, getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionY(1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			case 3: //BOTTOM WALL
				enemyOffset = ((playLeft + 20) + (playRight - 20)) / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playLeft + (enemyCounter * enemyOffset), playBottom, getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionY(-1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			}

			_spawnComplete = true;
			_spawnWave = 0;
			_spawnCooldown = _currentTime + 1000;


		}
	}
}

bool EvolvedGame::renderHUD(Draw &screen) const{
	HAPI->RenderText(screen.getWidth() / screen.getScreenBoundry() + 30, 20, HAPI_TColour(0, 255, 0), "SCORE");
	HAPI->ChangeFont("Tahoma", 30, 100);

	//Format to score with comma
	std::string currentScoreStr = std::to_string(_gameScore);

	for(size_t commaIndex = 3; commaIndex < currentScoreStr.length(); commaIndex += 4){
		currentScoreStr.insert(currentScoreStr.length() - commaIndex, ",");
	}

	//Display lives left
	HAPI->RenderText(screen.getWidth() - 200, 40, HAPI_TColour(0, 255, 0), "Lives: " + std::to_string(_livesLeft));

	//Display score
	HAPI->RenderText(screen.getWidth() / screen.getScreenBoundry() + 30, 40, HAPI_TColour(0, 255, 0), currentScoreStr);
	HAPI->ChangeFont("Tahoma", 24, 100);
	return true;
}



bool EvolvedGame::addScore(int entityID){
	switch(entityID){
	case ENEMY_BLUE:
		_gameScore += 100;
		break;
	case ENEMY_PURPLE:
		_gameScore += 200;
		break;
	case ENEMY_PURPLE_MINI:
		_gameScore += 25;
		break;
	case ENEMY_ORANGE:
		_gameScore += 500;
		break;
	}

	return true;
}

void EvolvedGame::update(std::shared_ptr<GameObject> Geo){

}