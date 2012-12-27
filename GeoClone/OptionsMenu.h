#pragma once
#include "menustate.h"
#include <vector>

class OptionsMenu :
	public MenuState
{
public:
	OptionsMenu(std::shared_ptr<SoundManager> &soundManager);
	~OptionsMenu(void);

	void update(std::shared_ptr<Draw> &renderer);
	void changeItem(int change);
	void selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld);

private:
	std::vector<std::string> _menuItems;
	int _startX, _startY, _selectedItem;

};

