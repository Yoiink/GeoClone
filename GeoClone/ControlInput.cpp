#include "ControlInput.h"


ControlInput::ControlInput(void)
{
	usingXboxController = true;
}


ControlInput::~ControlInput(void)
{
}

void ControlInput::updateControllers(){

	//Check to see if the Xbox controller is plugged in or not.
	if(usingXboxController){
		if(!HAPI->GetControllerData(0, &controllerData)){ //Check controller data, if false, run if statement.
			HAPI_UserResponse keepController;
			HAPI->UserMessage("You have unplugged your controller. Would you like to continue using a controller?", "Controller Unplugged!", eButtonTypeYesNo, &keepController);
			if(keepController == eUserResponseYes){
				HAPI_UserResponse keepChecking = keepController;
				while( (!HAPI->GetControllerData(0, &controllerData)) && (keepChecking = eUserResponseYes)){
					HAPI->UserMessage("Still can't detect your controller. Try again?", "Controller Unplugged!", eButtonTypeYesNo, &keepChecking);
					if(keepChecking = eUserResponseNo){
						usingXboxController = false;
						break;
					}
				}
			} else {
				usingXboxController = false;
			}
		}
	}

	//Hard coded 4, don't really like this. -- Maybe 4 player support in future...
	//for(int curPlayer = 0; curPlayer < 4; curPlayer++){
	//	HAPI->GetControllerData(curPlayer, &(*controllerData[curPlayer]));
	//}

	//Stick with one player for now.
	HAPI->GetControllerData(0, &controllerData);
	HAPI->GetKeyboardData(&_keyboardData);
	HAPI->GetMouseData(&_mouseData);
}

HAPI_TControllerData ControlInput::getXbox(int playerNumber) const{
	return controllerData;
}

HAPI_TKeyboardData ControlInput::getKeyboard() const{
	return _keyboardData;
}

HAPI_TMouseData ControlInput::getMouse() const{
	return _mouseData;
}