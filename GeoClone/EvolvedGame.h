#pragma once

#include "GameState.h"
#include "Asset.h"
#include "GameObject.h"
//#include <list>
#include <vector>

class EvolvedGame : public GameState
{
public:
	EvolvedGame(void);
	~EvolvedGame(void);

	bool loadAssets();
	void spawnWaves(std::list<std::shared_ptr<GameObject>> &entityList, std::shared_ptr<Draw> &screen, std::shared_ptr<GameObject> &Geo, std::shared_ptr<SoundManager> &sound);

	//Getters
	std::shared_ptr<Asset> getAsset(int assetID) const;
	int getAssetID(std::string assetName) const;
	unsigned long int getHighscore() const;

	bool renderHUD(Draw &screen) const;
	void resetScore();

	//Set
	bool addScore(int entityID);

	void updateParallax(std::shared_ptr<GameObject> Geo);

private:
	//std::shared_ptr<Asset> _bulletAsset, _geoAsset, _enemyPurpleAsset, _fireSoundAsset, _bgParallax;

	std::vector<std::shared_ptr<Asset>> _gameAssets;

	int _spawnMode, _timeLastSpawn, _currentTime, _spawnWave, _spawnCooldown, _bgPosX, _bgPosY;
	unsigned long int _gameScore;	//Still a limit of 4,294,967,295
	bool _spawnComplete;
	
};

