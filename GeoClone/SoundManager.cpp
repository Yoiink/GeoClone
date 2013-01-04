#include "SoundManager.h"
#include <HAPI_lib.h>

SoundManager::SoundManager(void)
{
	FMOD::System_Create(&_system);
	_system->init(32, FMOD_INIT_NORMAL, 0);

	//channel->setFrequency(48000); // 100 to 705600, -100 to -705600 (Really want a max of 70560)

	_sounds.push_back(loadSound("sounds/evolved.mp3", true));
	_sounds.push_back(loadSound("sounds/main_menu_music.ogg", true));
	_sounds.push_back(loadSound("sounds/deadline.ogg", true));
	_sounds.push_back(loadSound("sounds/waves.ogg", true));
	_sounds.push_back(loadSound("sounds/menu_nav_sound.mp3"));
	_sounds.push_back(loadSound("sounds/fire_normal.wav"));
	_sounds.push_back(loadSound("sounds/enemy_explode.ogg"));
	_sounds.push_back(loadSound("sounds/enemy_blue_spawn.ogg"));
	_sounds.push_back(loadSound("sounds/enemy_green_spawn.ogg"));
	_sounds.push_back(loadSound("sounds/enemy_purple_spawn.ogg"));
	_sounds.push_back(loadSound("sounds/enemy_orange_spawn.ogg"));

}


SoundManager::~SoundManager(void)
{
	//Release all the sounds we loaded.
	for(FMOD::Sound *sound : _sounds){
		sound->release();
	}

}


void SoundManager::playAudio(int audioID){

	if(audioID == MAIN_MENU_MUSIC || audioID == EVOLVED_MUSIC || audioID == DEADLINE_MUSIC || audioID == WAVES_MUSIC){
		bool isPlaying = false;
		if(_musicChannel->isPlaying(&isPlaying)){
			_musicChannel->setVolume(1);
			_system->playSound(FMOD_CHANNEL_FREE, _sounds.at(audioID), false, &_musicChannel);
		}
	} else {
		_soundChannel->setVolume(0.5);
		_system->playSound(FMOD_CHANNEL_FREE, _sounds.at(audioID), false, &_soundChannel);
	}
}

FMOD::Sound*  SoundManager::loadSound(std::string assetName, bool isMusic){

	FMOD::Sound* loadSound = new FMOD::Sound(*loadSound);
	FMOD_RESULT result;
	if(isMusic){
		result = _system->createSound(assetName.c_str(), FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &loadSound);
	} else {
		result = _system->createSound(assetName.c_str(), FMOD_HARDWARE, 0, &loadSound);
	}
	
	if(result != FMOD_OK){
		HAPI->UserMessage("Unable to load file " + assetName + ". GeoClone will now close.", "Unable to load sound", eButtonTypeOk);
		HAPI->Close();
	}

	return loadSound;
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