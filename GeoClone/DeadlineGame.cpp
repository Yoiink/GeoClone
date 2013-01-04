#include "DeadlineGame.h"
//#include "Enemy.h"
#include "EnemyPurple.h"
#include "EnemyBlue.h"
#include "SoundManager.h"


DeadlineGame::DeadlineGame(void) : _spawnMode(0), _timeLastSpawn(0), _spawnComplete(true), _spawnWave(0), _spawnCooldown(3000), _gameScore(0),
	_gameTimer(180), _timeCheck(0), _lastTick(0), _bgPosX(-1024), _bgPosY(-530), _highscoreFile("deadlineScore")
{
}


DeadlineGame::~DeadlineGame(void)
{
}

bool DeadlineGame::loadAssets(){

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/bullet.png", LOAD_IMAGE, "bullet", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_purple.png", LOAD_IMAGE, "particle_purple", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_blue.png", LOAD_IMAGE, "particle_blue", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_green.png", LOAD_IMAGE, "particle_green", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_trail.png", LOAD_IMAGE, "particle_trail", _gameAssets.size() - 1)))
		return false;
	if(!_gameAssets.back()->loadAnimation(32, 4, 4))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_bullet.png", LOAD_IMAGE, "particle_bullet", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/particle_geodeath.png", LOAD_IMAGE, "particle_geodeath", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/Geo.png", LOAD_IMAGE, "geo", _gameAssets.size() - 1)))
		return false;

	//if(!(_gameAssets.back()->Load("GeoAnimate.png", LOAD_IMAGE, "geo", _gameAssets.size() - 1)))
	//	return false;

	//if(!_gameAssets.back()->loadAnimation(6, 32, 32))
	//	return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_purple.png", LOAD_IMAGE, "enemy_purple", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_purple_mini.png", LOAD_IMAGE, "enemy_purple_mini", _gameAssets.size() - 1)))
		return false;

	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/enemy_blue.png", LOAD_IMAGE, "enemy_blue", _gameAssets.size() - 1)))
		return false;


	_gameAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_gameAssets.back()->Load("images/bg_parallax.png", LOAD_IMAGE, "enemy_purple", _gameAssets.size() - 1)))
		return false;

	return true;
}

std::shared_ptr<Asset> DeadlineGame::getAsset(int assetID) const{
	return _gameAssets.at(assetID);
}

void DeadlineGame::resetScore(){
	_gameScore = 0;
}

//Change this to a bool? If there's a problem we're still setting the ID.
int DeadlineGame::getAssetID(std::string assetName) const{
	for(std::shared_ptr<Asset> curAsset : _gameAssets){
		if(curAsset->getName() == assetName){
			return curAsset->getID();
		}
	}
	return 0;
}

unsigned long int DeadlineGame::getHighscore() const{
	return _gameScore;
}

std::string DeadlineGame::getHighscoreFile() const{
	return _highscoreFile;
}

void DeadlineGame::spawnWaves(std::list<std::shared_ptr<GameObject>> &entityList, std::shared_ptr<Draw> &screen, std::shared_ptr<GameObject> &Geo, std::shared_ptr<SoundManager> &sound){

	_currentTime = HAPI->GetTime();

	if(_spawnCooldown < _currentTime){
		if(_spawnComplete){
			_spawnMode = rand() % 5;
			//_spawnMode = -2;
			_spawnComplete = false;
			_timeLastSpawn = _currentTime;
		}

		//Calculate the corners
		float playLeft = screen->getGridX() + 10;
		float playTop = screen->getGridY() + 10;
		float playRight = screen->getGridX() + screen->getWidth() - 40;
		float playBottom = screen->getGridY() + screen->getHeight() - 40;

		//if(_spawnMode == -2){
		//	int maxEnemies = 16;
		//	
		//	for(int enemyCount = 0; enemyCount < maxEnemies; enemyCount++){
		//		float angle = (enemyCount * (360.0f / maxEnemies));
		//		float xAdd = 1*cos(angle);
		//		float yAdd = 1*sin(angle);
		//		int spawnDistance = 300;

		//		float calcSpawnX = Geo->getX() + (xAdd * spawnDistance);
		//		float calcSpawnY = Geo->getY() + (yAdd * spawnDistance);

		//		if(calcSpawnX < playLeft)
		//			calcSpawnX = playLeft + 10;
		//		

		//		if(calcSpawnY < playTop)
		//			calcSpawnY = playTop + 10;
		//		

		//		if(calcSpawnX > playRight)
		//			calcSpawnX = playRight - 40;

		//		if(calcSpawnY > playBottom)
		//			calcSpawnY = playBottom - 40;

		//		entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(calcSpawnX, calcSpawnY, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
		//		sound->playAudio(PURPLE_SPAWN);

		//		_spawnCooldown = _currentTime + 1000;

		//	}
		//}

		if(_spawnMode <= 3){ //NORMAL SPAWN
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
					_spawnCooldown = _currentTime + 5000;
				}
				_spawnWave++;
			}
		} else if(_spawnMode > 3){ //SPECIAL SPAWN -- Box -- Set to 4

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
				}
				entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxLeft, boxTop + rowGap * rowCount, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
				entityList.push_front(std::shared_ptr<Enemy>(new EnemyPurple(boxRight, boxTop + rowGap * rowCount, getAssetID("enemy_purple"), getAssetID("particle_purple"))));
			}
				_spawnComplete = true;
				_spawnWave = 0;
				_spawnCooldown = _currentTime + 10000;
		}
	}
}

bool DeadlineGame::renderHUD(Draw &screen) const{
	HAPI->RenderText(screen.getWidth() / screen.getScreenBoundry() + 30, 20, HAPI_TColour(0, 255, 0), "SCORE");
	HAPI->ChangeFont("Tahoma", 30, 100);

	//Format to score with comma
	std::string currentScoreStr = std::to_string(_gameScore);

	for(size_t commaIndex = 3; commaIndex < currentScoreStr.length(); commaIndex += 4){
		currentScoreStr.insert(currentScoreStr.length() - commaIndex, ",");
	}

	HAPI->RenderText(screen.getWidth() / screen.getScreenBoundry() + 30, 40, HAPI_TColour(0, 255, 0), currentScoreStr);

	//Draw game counter (unique to Deadline)
	HAPI->RenderText(screen.getWidth() / 2, 40, HAPI_TColour(0, 255, 0), std::to_string(_gameTimer));

	HAPI->ChangeFont("Tahoma", 24, 100);
	return true;
}



bool DeadlineGame::addScore(int entityID){
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
	}

	return true;
}

void DeadlineGame::update(std::shared_ptr<GameObject> Geo){

	if(_gameTimer == 0){
		Geo->setIsAlive(false);
	}

	//Also going to use this to update the countdown
	if(_timeCheck >= _lastTick + 1000){
		_gameTimer -= 1;
		_lastTick = HAPI->GetTime();
	} else {
		_timeCheck = HAPI->GetTime();
	}
}