#pragma once
#include <vector>
#include "menustate.h"

class Asset;

class PauseMenu :
	public MenuState
{
public:
	PauseMenu(std::shared_ptr<SoundManager> &soundManager);
	~PauseMenu(void);

	void update(std::shared_ptr<Draw> &renderer);
	void changeItem(int change);
	void selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld);
	bool setupAssets();

private:
	std::vector<std::string> _menuItems;
	std::vector<std::shared_ptr<Asset>> _menuAssets;
	int _startX, _startY, _selectedItem;
};

