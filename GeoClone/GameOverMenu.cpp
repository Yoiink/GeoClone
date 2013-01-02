#include "GameOverMenu.h"
#include "MainMenu.h"
#include "SelectMenu.h"
#include <HAPI_lib.h>

#include "World.h"
#include "Asset.h"
#include "Draw.h"
#include "SoundManager.h"

GameOverMenu::GameOverMenu(std::shared_ptr<SoundManager> &soundManager) :
	MenuState(soundManager)
{
	//Spaces to align text, may be quicker than calculating their positions...
	_menuItems.push_back(" Play Again");
	_menuItems.push_back("Select Mode");
	_menuItems.push_back(" Main Menu");
	_startX = 400;
	_startY = 200;
	_selectedItem = 0;
	MenuState::getSoundManager()->stopMusic();
}


GameOverMenu::~GameOverMenu(void)
{
}

void GameOverMenu::setHighscore(std::vector<std::string> values){
	_highscoreValues = values;
}

void GameOverMenu::update(std::shared_ptr<Draw> &renderer){

	//Load assets if needed
	if(_menuAssets.size() == 0){
		//As this is true, it means we can use it as a constructor for startX and startY now we have access to Draw
		_startX = (renderer->getWidth() / 2) - 80;
		_startY = (renderer->getHeight() / 2) - 50;

		if(!setupAssets()){				//If there are any issues, close the game.
			HAPI->Close();
			return;
		}
	}

	//Rendering the background will "clear" the screen
	renderer->speedRender(0, 0, _menuAssets[0]->getWidth(), _menuAssets[0]->getHeight(), _menuAssets[0]->getTexture());

	//Write menu items
	HAPI->ChangeFont("Tahoma", 30, 1000);
	for(size_t curItem = 0; curItem < _menuItems.size(); curItem++){
		if(curItem == _selectedItem){
			HAPI->RenderText(_startX, _startY + (curItem * 80), HAPI_TColour(180, 255, 0), _menuItems[curItem]);
			renderer->Render(_startX - (_menuAssets[1]->getWidth() / 2) + 80.f, 
							_startY + (curItem * 80) - (_menuAssets[1]->getHeight() / 2) + 18.f,
							_menuAssets[1]->getWidth(), _menuAssets[1]->getHeight(), _menuAssets[1]->getTexture());
		} else {
			HAPI->RenderText(_startX, _startY + (curItem * 80), HAPI_TColour(0, 255, 0), _menuItems[curItem]);
			renderer->Render(_startX - (_menuAssets[2]->getWidth() / 2) + 80.f, 
							_startY + (curItem * 80) - (_menuAssets[2]->getHeight() / 2) + 18.f,
							_menuAssets[2]->getWidth(), _menuAssets[2]->getHeight(), _menuAssets[2]->getTexture());
		}
	}

	
	//Write highscore values
	HAPI->RenderText(renderer->getWidth() - 300, _startY - 40, HAPI_TColour(180, 255, 0), "Highscores");
	HAPI->ChangeFont("Tahoma", 24, 800);
	for(size_t curItem = 0; curItem < _highscoreValues.size(); curItem++){
		HAPI->RenderText(renderer->getWidth() - 300, _startY + (curItem * 20), HAPI_TColour(180, 255, 0), _highscoreValues[curItem]);
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

void GameOverMenu::changeItem(int change){
	_selectedItem += change;

	if(_selectedItem < 0)
		_selectedItem =  _menuItems.size() - 1;

	if(static_cast<size_t>(_selectedItem) > _menuItems.size() - 1){
		_selectedItem = 0;
	}

	MenuState::getSoundManager()->playAudio(MAIN_MENU_NAV_SOUND);
}

void GameOverMenu::selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld){
	switch(_selectedItem){
		case 0:
			inMenues = false;
			gameWorld->restartWorld();
			break;
		case 1:
			MenuState::getSoundManager()->playAudio(MAIN_MENU_MUSIC);
			gameMenu.reset(new SelectMenu(MenuState::getSoundManager()));
			break;
		case 2:
			//MenuState::getSoundManager()->stopMusic();
			MenuState::getSoundManager()->stopMusic();
			gameMenu.reset(new MainMenu(MenuState::getSoundManager()));
			break;
	}
}

bool GameOverMenu::setupAssets(){
	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/main_menu_bg.png", LOAD_IMAGE, "menu_background", _menuAssets.size() - 1)))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/main_menu_active.png", LOAD_IMAGE, "menu_active", _menuAssets.size() - 1)))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/main_menu_nonactive.png", LOAD_IMAGE, "menu_nonactive", _menuAssets.size() - 1)))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/nav_updown.png", LOAD_IMAGE, "nav_updown", _menuAssets.size() - 1)))
		return false;

	_menuAssets.push_back(std::shared_ptr<Asset>(new Asset()));
	if(!(_menuAssets.back()->Load("images/controller/facebutton_a.png", LOAD_IMAGE, "controller_a", _menuAssets.size() - 1)))
		return false;

	return true;
}