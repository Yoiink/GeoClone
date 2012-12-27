#include "SoundManager.h"


SoundManager::SoundManager(void)
{
	FMOD::System_Create(&_system);
	_system->init(32, FMOD_INIT_NORMAL, 0);

	//channel->setFrequency(48000); // 100 to 705600, -100 to -705600 (Really want a max of 70560)
}


SoundManager::~SoundManager(void)
{
	//I think FMOD must manage deletion, get errors if I try to. 
	//delete _soundChannel;
	//delete _musicChannel;
	//delete _gameMusic;
	//delete _soundEffect;
	//delete _system;
}


void SoundManager::playAudio(int audioID){

	switch(audioID){
	case EVOLVED_MUSIC:
		//loadSound("sounds/evolved.mp3", true);
		break;
	case MAIN_MENU_MUSIC:
		loadSound("sounds/main_menu_music.ogg", true);
		break;
	case MAIN_MENU_NAV_SOUND:
		//loadSound("sounds/menu_nav_sound.mp3");
		break;
	case BULLET_SOUND:
		loadSound("sounds/fire_normal.wav");
		break;
	case ENEMY_EXPLODE:
		loadSound("sounds/enemy_explode.ogg");
		break;
	case BLUE_SPAWN:
		loadSound("sounds/enemy_blue_spawn.ogg");
		break;
	case GREEN_SPAWN:
		loadSound("sounds/enemy_green_spawn.ogg");
		break;
	case PURPLE_SPAWN:
		loadSound("sounds/enemy_purple_spawn.ogg");
		break;
	}
}

void SoundManager::loadSound(std::string assetName, bool isMusic){
	bool audioPlaying;
	if(isMusic){
		_musicChannel->isPlaying(&audioPlaying);
		if(!audioPlaying){
			_system->createSound(assetName.c_str(), FMOD_HARDWARE, 0, &_gameMusic);
			_gameMusic->setMode(FMOD_LOOP_NORMAL);
			_system->playSound(FMOD_CHANNEL_FREE, _gameMusic, false, &_musicChannel);
			_musicChannel->setVolume(1);
			
		}
	} else {
		/* No need to do the check, FMOD will handle adding sounds to new channels */
		//_soundChannel->isPlaying(&audioPlaying);
		//if(!audioPlaying){
			_system->createSound(assetName.c_str(), FMOD_HARDWARE, 0, &_soundEffect);
			_system->playSound(FMOD_CHANNEL_FREE, _soundEffect, false, &_soundChannel);
			_soundChannel->setVolume(0.5);
		//}
	}


}

void SoundManager::stopMusic(){
	_musicChannel->stop();
}

void SoundManager::stopSound(){
	_soundChannel->stop();
}

void SoundManager::update(){
	_system->update();
}

void SoundManager::pauseMusic(){
	_musicChannel->setPaused(true);
}

void SoundManager::resumeMusic(){
	_musicChannel->setPaused(false);
}