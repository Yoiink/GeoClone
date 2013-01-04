#include "OptionsMenu.h"
#include <HAPI_lib.h>
#include "MainMenu.h"

#include "World.h"
#include "Asset.h"
#include "Draw.h"
#include "SoundManager.h"

OptionsMenu::OptionsMenu(std::shared_ptr<SoundManager> &soundManager) :
	MenuState(soundManager)
{
	_menuItems.push_back("Awful Graphics");
	_menuItems.push_back("         Back");
	_startX = 400;
	_startY = 200;
	_selectedItem = 0;
}


OptionsMenu::~OptionsMenu(void)
{
}


void OptionsMenu::update(std::shared_ptr<Draw> &renderer){
	//Load assets if needed
	if(_menuAssets.size() == 0){
		//As this is true, it means we can use it as a constructor for startX and startY now we have access to Draw
		_startX = (renderer->getWidth() / 2) - 120;
		_startY = (renderer->getHeight() / 2) - 50;

		if(!setupAssets()){				//If there are any issues, close the game.
			HAPI->Close();
			return;
		}
	}

	//Rendering the background will "clear" the screen
	renderer->speedRender(0, 0, _menuAssets[0]->getWidth(), _menuAssets[0]->getHeight(), _menuAssets[0]->getTexture());

	HAPI->ChangeFont("Tahoma", 30, 1000);
	for(size_t curItem = 0; curItem < _menuItems.size(); curItem++){
		if(curItem == _selectedItem){
			HAPI->RenderText(_startX, _startY + (static_cast<int>(curItem) * 80), HAPI_TColour(180, 255, 0), _menuItems[curItem]);
			renderer->Render(_startX - (_menuAssets[1]->getWidth() / 2) + 80.f, 
							_startY + (static_cast<int>(curItem) * 80) - (_menuAssets[1]->getHeight() / 2) + 18.f,
							_menuAssets[1]->getWidth(), _menuAssets[1]->getHeight(), _menuAssets[1]->getTexture());
		} else {
			HAPI->RenderText(_startX, _startY + (static_cast<int>(curItem) * 80), HAPI_TColour(0, 255, 0), _menuItems[curItem]);
			renderer->Render(_startX - (_menuAssets[2]->getWidth() / 2) + 80.f, 
							_startY + (static_cast<int>(curItem) * 80) - (_menuAssets[2]->getHeight() / 2) + 18.f,
							_menuAssets[2]->getWidth(), _menuAssets[2]->getHeight(), _menuAssets[2]->getTexture());
		}
	}

	//Smaller font for sub menu info
	HAPI->ChangeFont("Tahoma", 20, 800);

	//Render the UP/Down
	HAPI->RenderText(_startX - 20, _startY + 345, HAPI_TColour(0, 255, 0), "Navigate");
	renderer->Render(_startX - 80.f, _startY + 340.f, _menuAssets[3]->getWidth(), _menuAssets[3]->getHeight(), _menuAssets[3]->getTexture());

	//Render the A Select
	HAPI->RenderText(_startX + 140, _startY + 345, HAPI_TColour(0, 255, 0), "Select");
	renderer->Render(_startX + 100.f, _startY + 340.f, _menuAssets[4]->getWidth(), _menuAssets[4]->getHeight(), _menuAssets[4]->getTexture());

	//Restore font size to 14 (for FPS and such)
	HAPI->ChangeFont("Tahoma", 14, 800);
}

void OptionsMenu::changeItem(int change){
	_selectedItem += change;

	if(_selectedItem < 0)
		_selectedItem =  static_cast<int>(_menuItems.size() - 1);

	if(static_cast<size_t>(_selectedItem) > _menuItems.size() - 1){
		_selectedItem = 0;
	}

	MenuState::getSoundManager()->playAudio(MAIN_MENU_NAV_SOUND);
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

bool OptionsMenu::setupAssets(){
	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/main_menu_bg.png", LOAD_IMAGE, "menu_background", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/main_menu_active.png", LOAD_IMAGE, "menu_active", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/main_menu_nonactive.png", LOAD_IMAGE, "menu_nonactive", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/nav_updown.png", LOAD_IMAGE, "nav_updown", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/controller/facebutton_a.png", LOAD_IMAGE, "controller_a", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	return true;
}