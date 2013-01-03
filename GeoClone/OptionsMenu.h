#pragma once
#include "menustate.h"
#include <vector>
#include <memory>

class Asset;
class SoundManager;

class OptionsMenu :
	public MenuState
{
public:
	OptionsMenu(std::shared_ptr<SoundManager> &soundManager);
	~OptionsMenu(void);

	void update(std::shared_ptr<Draw> &renderer);
	void changeItem(int change);
	void selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld);
	bool setupAssets();

private:
	std::vector<std::string> _menuItems;
	std::vector<std::shared_ptr<Asset>> _menuAssets;
	int _startX, _startY, _selectedItem;
};

