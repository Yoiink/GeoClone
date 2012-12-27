#pragma once
#include <vector>
#include "menustate.h"

class Asset;

class GameOverMenu :
	public MenuState
{
public:
	GameOverMenu(std::shared_ptr<SoundManager> &soundManager);
	~GameOverMenu(void);

	void update(std::shared_ptr<Draw> &renderer);
	void changeItem(int change);
	void selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld);
	bool setupAssets();

	void setHighscore(std::vector<std::string> values);

private:
	std::vector<std::string> _menuItems;
	std::vector<std::string> _highscoreValues;
	std::vector<std::shared_ptr<Asset>> _menuAssets;
	int _startX, _startY, _selectedItem;
};

