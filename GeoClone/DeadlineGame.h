#pragma once

#include "GameState.h"
#include "Asset.h"
#include "GameObject.h"
//#include <list>
#include <vector>

class DeadlineGame : public GameState
{
public:
	DeadlineGame(void);
	~DeadlineGame(void);

	bool loadAssets();
	void spawnWaves(std::list<std::shared_ptr<GameObject>> &entityList, std::shared_ptr<Draw> &screen, std::shared_ptr<GameObject> &Geo, std::shared_ptr<SoundManager> &sound);

	//Getters
	std::shared_ptr<Asset> getAsset(int assetID) const;
	int getAssetID(std::string assetName) const;
	unsigned long int getHighscore() const;
	std::string getHighscoreFile() const;

	bool renderHUD(Draw &screen) const;
	void resetScore();

	//Set
	bool addScore(int entityID);

	void update(std::shared_ptr<GameObject> Geo);

private:
	std::vector<std::shared_ptr<Asset>> _gameAssets;

	int _spawnMode, _timeLastSpawn, _currentTime, _spawnWave, _spawnCooldown, _bgPosX, _bgPosY, _gameTimer, _timeCheck, _lastTick;
	std::string _highscoreFile;
	unsigned long int _gameScore;	//Still a limit of 4,294,967,295
	bool _spawnComplete;
	
};

