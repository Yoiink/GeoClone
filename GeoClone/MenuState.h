#pragma once
#include <memory>
#include <vector>
class World;
class Draw;
class SoundManager;

class MenuState
{
public:
	MenuState(std::shared_ptr<SoundManager> &soundManager);
	~MenuState(void);

	virtual void update(std::shared_ptr<Draw> &renderer) = 0;
	virtual void changeItem(int change) = 0;
	virtual void selectedItem(bool &inMenues, std::shared_ptr<MenuState> &gameMenu, std::shared_ptr<World> gameWorld) = 0;
	virtual void setHighscore(std::vector<std::string> values){
		//Do nothing.
	};

	std::shared_ptr<SoundManager> getSoundManager(){
		return _soundManager;
	}

private:
	std::shared_ptr<SoundManager> _soundManager;

};

