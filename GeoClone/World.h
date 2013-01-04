#pragma once

#include <memory>
#include <list>
#include <vector>
//#include <vector>

class Draw;
class GameState;
class GameObject;
class ControlInput;
class ParticleEmitter;
class MenuState;
class SoundManager;

enum GameMode{EVOLVED_GAME, DEADLINE_GAME};

class World : public std::enable_shared_from_this<World>	//Allows the use of shared_from_this() to replace the "this" pointer as a shared_ptr
{
public:
	World(int screenWidth, int screenHeight);
	~World(void);

	bool setupWorld();
	void restartWorld();
	void loadMode(int gameID);
	void update();

	float translateToGridX(float posX);
	float translateToGridY(float posY);
	void translateToGrid(float& posX, float& posY);

	bool getGraphicsSettings();
	void setGraphicsSettings(bool highGraphics);

	std::vector<std::string> readHighscore(std::string fileName);
	void writeHighscore(unsigned long int score, std::string fileName);


private:
	std::shared_ptr<MenuState> _gameMenu;
	std::shared_ptr<GameState> _gameMode;
	std::shared_ptr<Draw> _render;
	std::list<std::shared_ptr<GameObject>> _entityList;
	std::shared_ptr<ControlInput> _controllers;
	std::list<std::shared_ptr<ParticleEmitter>> _emitterList;
	std::shared_ptr<SoundManager> _soundManager;

	std::shared_ptr<GameObject> _Geo;

	unsigned int _currentTime, _nextShot, _lastTime;
	float _deltaTime;
	bool _movementInput, _graphicsToggle, _inMenues;

};

