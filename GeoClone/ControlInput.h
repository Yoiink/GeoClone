#pragma once

#include <HAPI_lib.h>
#include <memory>

class Player;

class ControlInput
{
public:
	ControlInput(void);
	~ControlInput(void);

	void updateControllers();

	HAPI_TControllerData getXbox(int playerNumber = 0) const;
	HAPI_TKeyboardData getKeyboard() const;
	HAPI_TMouseData getMouse() const;
	bool usingXbox() const;

private:
	//std::shared_ptr<HAPI_TControllerData> controllerData;	//Xbox Data
	//std::shared_ptr<HAPI_TKeyboardData> _keyboardData;		//Keyboard Data
	//std::shared_ptr<HAPI_TMouseData> _mouseData;			//Mouse Data

	HAPI_TControllerData controllerData;	//Xbox Data
	HAPI_TKeyboardData _keyboardData;		//Keyboard Data
	HAPI_TMouseData _mouseData;			//Mouse Data

	bool _usingXboxController;
};

