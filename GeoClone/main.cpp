#include <HAPI_lib.h>
#include <list>
#include <chrono>
#include <functional>
#include <memory>

#include "World.h"

void HAPI_Main(){

	HAPI->SetShowFPS(true, 0, 0);

	std::shared_ptr<World> gameWorld(new World(1280, 720));


	while(HAPI->Update()){
		gameWorld->update();
	}

	HAPI->Close();

}