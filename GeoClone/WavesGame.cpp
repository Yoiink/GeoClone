#include "WavesGame.h"
//#include "Enemy.h"
#include "EnemyPurple.h"
#include "EnemyBlue.h"
#include "EnemyOrange.h"
#include "SoundManager.h"


WavesGame::WavesGame(void) : _spawnMode(0), _timeLastSpawn(0), _spawnComplete(true), _spawnWave(0), _spawnCooldown(3000),
	_gameScore(0), _bgPosX(-1024), _bgPosY(-530), _highscoreFile("wavesScore"), _timePlayed(0)
{
	_startTime = HAPI->GetTime();
}


WavesGame::~WavesGame(void)
{
}

bool WavesGame::loadAssets(){

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

std::shared_ptr<Asset> WavesGame::getAsset(int assetID) const{
	return _gameAssets.at(assetID);
}

void WavesGame::resetScore(){
	_gameScore = 0;
}

//Change this to a bool? If there's a problem we're still setting the ID.
int WavesGame::getAssetID(std::string assetName) const{
	for(std::shared_ptr<Asset> curAsset : _gameAssets){
		if(curAsset->getName() == assetName){
			return curAsset->getID();
		}
	}
	return 0;
}

unsigned long int WavesGame::getHighscore() const{
	return _gameScore;
}

std::string WavesGame::getHighscoreFile() const{
	return _highscoreFile;
}

bool WavesGame::isGameOver(std::list<std::shared_ptr<GameObject>> &entityList){
	//If geo died then he is dead since no lives/game timer in this mode.
	return true;
}

void WavesGame::spawnWaves(std::list<std::shared_ptr<GameObject>> &entityList, std::shared_ptr<Draw> &screen, std::shared_ptr<GameObject> &Geo, std::shared_ptr<SoundManager> &sound){

	_currentTime = HAPI->GetTime();
	_timePlayed = _currentTime - _startTime;

	int waveSpeed = 3000;

	if(_timePlayed < 15000){
		waveSpeed = 3000;
	} else if(_timePlayed > 15000 && _timePlayed <= 30000){
		waveSpeed = 2000;
	} else if(_timePlayed > 30000 && _timePlayed <= 60000){
		waveSpeed = 1000;
	} else if(_timePlayed > 60000 && _timePlayed <= 120000){
		waveSpeed = 500;
	} else {
		waveSpeed = 100;
	}

	if(_spawnCooldown < _currentTime){
		if(_spawnComplete){
			_spawnMode = rand() % 15;
			_spawnComplete = false;
			_timeLastSpawn = _currentTime;
		}

		//Calculate the corners
		float playLeft = screen->getGridX() + 10;
		float playTop = screen->getGridY() + 10;
		float playRight = screen->getGridX() + screen->getWidth() - 40;
		float playBottom = screen->getGridY() + screen->getHeight() - 40;

		HAPI->RenderText(0, 300, HAPI_TColour(), std::to_string(playLeft));


		if(!_spawnComplete){ //Spawn orange from wall
			int enemiesToSpawn = 14;
			int wallSelect = rand() % 4;
			float enemyOffset = 0;

			switch(wallSelect){
			case 0: //LEFT WALL
				enemyOffset = screen->getHeight() / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playLeft, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionX(1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			case 1: //RIGHT WALL
				enemyOffset = screen->getHeight() / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn; enemyCounter++){
					//Random between blue spawn/purple spawn
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playRight, playTop + (enemyCounter * enemyOffset), getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionX(-1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			case 2: //TOP WALL
				enemyOffset = screen->getWidth() / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn + 4; enemyCounter++){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playLeft + (enemyCounter * enemyOffset), playTop, getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionY(1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			case 3: //BOTTOM WALL
				enemyOffset = screen->getWidth() / enemiesToSpawn;
				for(int enemyCounter = 0; enemyCounter < enemiesToSpawn + 4; enemyCounter++){
						entityList.push_front(std::shared_ptr<Enemy>(new EnemyOrange(playLeft + (enemyCounter * enemyOffset), playBottom, getAssetID("enemy_orange"), getAssetID("particle_orange"))));
						entityList.front()->setDirectionY(-1);
				}
				sound->playAudio(ORANGE_SPAWN);
				break;
			}

			_spawnComplete = true;
			_spawnWave = 0;
			_spawnCooldown = _currentTime + waveSpeed;
		}

		if(_timePlayed > 30000){
			int amountToSpawn = 1;

			if(_timePlayed <= 60000){
				amountToSpawn = 1;
			} else if(_timePlayed > 60000 && _timePlayed <= 70000){
				amountToSpawn = 2;
			} else if(_timePlayed > 70000 && _timePlayed <= 80000){
				amountToSpawn = 3;
			} else if(_timePlayed > 80000 && _timePlayed <= 100000){
				amountToSpawn = 4;
			} else {
				amountToSpawn = 5;
			}

			for(int curSpawn = 0; curSpawn < amountToSpawn; curSpawn++){

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
			}

		}
	}
}

bool WavesGame::renderHUD(Draw &screen) const{
	HAPI->RenderText(screen.getWidth() / screen.getScreenBoundry() + 30, 20, HAPI_TColour(0, 255, 0), "SCORE");
	HAPI->ChangeFont("Tahoma", 30, 100);

	//Format to score with comma
	std::string currentScoreStr = std::to_string(_gameScore);

	for(size_t commaIndex = 3; commaIndex < currentScoreStr.length(); commaIndex += 4){
		currentScoreStr.insert(currentScoreStr.length() - commaIndex, ",");
	}

	//Display score
	HAPI->RenderText(screen.getWidth() / screen.getScreenBoundry() + 30, 40, HAPI_TColour(0, 255, 0), currentScoreStr);
	HAPI->ChangeFont("Tahoma", 24, 100);
	return true;
}



bool WavesGame::addScore(int entityID){
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

void WavesGame::update(std::shared_ptr<GameObject> Geo){

}