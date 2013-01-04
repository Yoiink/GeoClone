#pragma once

#include "Asset.h"
#include "GameObject.h"
#include "Draw.h"
#include <list>
#include <memory>

class SoundManager;

class GameState
{
public:
	GameState(void);
	~GameState(void);

	virtual bool loadAssets() = 0;
	virtual void spawnWaves(std::list<std::shared_ptr<GameObject>> &entityList, std::shared_ptr<Draw> &screen, std::shared_ptr<GameObject> &Geo, std::shared_ptr<SoundManager> &sound) = 0;

	virtual std::shared_ptr<Asset> getAsset(int assetID) const = 0;
	virtual int getAssetID(std::string assetName) const = 0;
	virtual unsigned long int getHighscore() const = 0;
	virtual std::string getHighscoreFile() const = 0;


	virtual bool isGameOver(std::list<std::shared_ptr<GameObject>> &entityList) = 0;
	virtual void resetScore() = 0;
	virtual bool addScore(int entityID) = 0;
	virtual bool renderHUD(Draw &screen) const = 0;
	virtual void update(std::shared_ptr<GameObject> Geo) = 0;

};

