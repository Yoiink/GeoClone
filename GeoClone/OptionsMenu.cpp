#include "OptionsMenu.h"
#include <HAPI_lib.h>
#include "MainMenu.h"

OptionsMenu::OptionsMenu(std::shared_ptr<SoundManager> &soundManager) :
	MenuState(soundManager)
{
	_menuItems.push_back("Awful graphics");
	_menuItems.push_back("Back");
	_startX = 400;
	_startY = 200;
	_selectedItem = 0;
}


OptionsMenu::~OptionsMenu(void)
{
}


void OptionsMenu::update(std::shared_ptr<Draw> &renderer){
	HAPI->ChangeFont("Tahoma", 30, 1000);
	for(size_t curItem = 0; curItem < _menuItems.size(); curItem++){
		if(curItem == _selectedItem){
			HAPI->RenderText(_startX, _startY + (curItem * 30), HAPI_TColour(180, 255, 0), _menuItems[curItem]);
		} else {
			HAPI->RenderText(_startX, _startY + (curItem * 30), HAPI_TColour(0, 255, 0), _menuItems[curItem]);
		}
	}
	HAPI->ChangeFont("Tahoma", 14, 800);
}

void OptionsMenu::changeItem(int change){
	_selectedItem += change;

	if(_selectedItem < 0)
		_selectedItem =  _menuItems.size() - 1;

	if(static_cast<size_t>(_selectedItem) > _menuItems.size() - 1){
		_selectedItem = 0;
	}
}

void OptionsMenu::selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld){
	switch(_selectedItem){
		case 0:
			//gameMenu.reset(new MainMenu());
			break;
		case 1:
			gameMenu.reset(new MainMenu(MenuState::getSoundManager()));
			break;
	}
}