#include "SelectMenu.h"
#include "OptionsMenu.h"
#include <HAPI_lib.h>

#include "World.h"
#include "Asset.h"
#include "Draw.h"
#include "SoundManager.h"

SelectMenu::SelectMenu(std::shared_ptr<SoundManager> &soundManager) :
	MenuState(soundManager)
{
	//Spaces to align text, may be quicker than calculating their positions...
	_menuItems.push_back("     Evolved");
	_menuItems.push_back("   Deadline");
	_menuItems.push_back("      Waves");
	_menuItems.push_back("Not Available");
	_startX = 0;
	_startY = 0;
	_selectedItem = 0;
}


SelectMenu::~SelectMenu(void)
{
}

void SelectMenu::update(std::shared_ptr<Draw> &renderer){

	//Load assets if needed
	if(_menuAssets.size() == 0){
		//As this is true, it means we can use it as a constructor for startX and startY now we have access to Draw
		_startX = (renderer->getWidth() / 2) - 325;
		_startY = (renderer->getHeight() / 2) - 75;

		if(!setupAssets()){				//If there are any issues, close the game.
			HAPI->Close();
			return;
		}
	}

	//Rendering the background will "clear" the screen
	renderer->speedRender(0, 0, _menuAssets[0]->getWidth(), _menuAssets[0]->getHeight(), _menuAssets[0]->getTexture());

	HAPI->ChangeFont("Tahoma", 30, 1000);

	int xModifier = 0;
	int yModifier = 0;
	for(size_t curItem = 0; curItem < _menuItems.size(); curItem++){
		if(curItem == _selectedItem){
			HAPI->RenderText(_startX + xModifier, _startY + ((static_cast<int>(curItem) / 2) * 220), HAPI_TColour(180, 255, 0), _menuItems[curItem]);
			renderer->Render(_startX + xModifier - (_menuAssets[1]->getWidth() / 2) + 80.f, 
							_startY + ((static_cast<int>(curItem)  / 2) * 220) - (_menuAssets[1]->getHeight() / 2) + 18.f,
							_menuAssets[1]->getWidth(), _menuAssets[1]->getHeight(), _menuAssets[1]->getTexture());
		} else {
			HAPI->RenderText(_startX + xModifier, _startY + ((static_cast<int>(curItem)  / 2) * 220), HAPI_TColour(0, 255, 0), _menuItems[curItem]);
			renderer->Render(_startX + xModifier - (_menuAssets[2]->getWidth() / 2) + 80.f, 
							_startY + ((static_cast<int>(curItem)  / 2) * 220) - (_menuAssets[2]->getHeight() / 2) + 18.f,
							_menuAssets[2]->getWidth(), _menuAssets[2]->getHeight(), _menuAssets[2]->getTexture());
		}
		
		if(xModifier == 0){
			xModifier = 500;
		} else if(xModifier == 500) {
			xModifier = 0;
		}
	}

	//Smaller font for sub menu info
	HAPI->ChangeFont("Tahoma", 20, 800);

	//Render the UP/Down/Left/Right
	HAPI->RenderText(_startX + 240, _startY + 375, HAPI_TColour(0, 255, 0), "Navigate");
	renderer->Render(_startX + 180.f, _startY + 370.f, _menuAssets[3]->getWidth(), _menuAssets[3]->getHeight(), _menuAssets[3]->getTexture());
	//renderer->Render(_startX + 180.f, _startY + 370.f, _menuAssets[4]->getWidth(), _menuAssets[4]->getHeight(), _menuAssets[4]->getTexture());

	//Render the A select
	HAPI->RenderText(_startX + 380, _startY + 375, HAPI_TColour(0, 255, 0), "Select");
	renderer->Render(_startX + 340.f, _startY + 370.f, _menuAssets[5]->getWidth(), _menuAssets[5]->getHeight(), _menuAssets[5]->getTexture());

	//Restore font size to 14 (for FPS and such)
	HAPI->ChangeFont("Tahoma", 14, 800);
}

void SelectMenu::changeItem(int change){
	_selectedItem += change;

	if(_selectedItem < 0)
		_selectedItem =  static_cast<int>(_menuItems.size() - 1);

	if(static_cast<size_t>(_selectedItem) > _menuItems.size() - 1){
		_selectedItem = 0;
	}

	MenuState::getSoundManager()->playAudio(MAIN_MENU_NAV_SOUND);
}

void SelectMenu::selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld){
	switch(_selectedItem){
		case 0:
			MenuState::getSoundManager()->stopMusic();
			gameWorld->loadMode(EVOLVED_GAME);
			if(!gameWorld->setupWorld()){
				HAPI->Close();
				return;
			}
			inMenues = false;
			break;
		case 1:
			MenuState::getSoundManager()->stopMusic();
			gameWorld->loadMode(DEADLINE_GAME);
			if(!gameWorld->setupWorld()){
				HAPI->Close();
				return;
			}
			inMenues = false;
			break;
		case 2:
			MenuState::getSoundManager()->stopMusic();
			gameWorld->loadMode(WAVES_GAME);
			if(!gameWorld->setupWorld()){
				HAPI->Close();
				return;
			}
			inMenues = false;
			break;
		case 3:
			//HAPI->Close();
			break;
	}
}

bool SelectMenu::setupAssets(){
	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/select_menu_bg.png", LOAD_IMAGE, "menu_background", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/select_menu_active.png", LOAD_IMAGE, "menu_active", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/select_menu_nonactive.png", LOAD_IMAGE, "menu_nonactive", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/nav_updown.png", LOAD_IMAGE, "nav_updown", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/nav_leftright.png", LOAD_IMAGE, "nav_leftright", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/controller/facebutton_a.png", LOAD_IMAGE, "controller_a", static_cast<int>(_menuAssets.size() - 1))))
		return false;

	return true;
}