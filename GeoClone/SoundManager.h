#pragma once

#include "fmod.hpp"
#include <string>
#include <vector>

enum SoundID{EVOLVED_MUSIC, MAIN_MENU_MUSIC, DEADLINE_MUSIC, MAIN_MENU_NAV_SOUND, BULLET_SOUND, ENEMY_EXPLODE, BLUE_SPAWN, GREEN_SPAWN, PURPLE_SPAWN };

class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	void playAudio(int audioID);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
	void stopSound();

	void update();

private:
	FMOD::Sound* loadSound(std::string assetName, bool isMusic = false);

	std::vector<FMOD::Sound*> _sounds;
	FMOD::System     *_system;			//handle to FMOD engine
	//FMOD::Sound      *_gameMusic;		//Game music (loop)
	//FMOD::Sound		 *_soundEffect;		//Sounds like bullet/UI e.t.c.
	FMOD::Channel    *_musicChannel;	//Music's channel
	FMOD::Channel    *_soundChannel;	//Sound channel
};

