#include "inputManager.h"
#include "elev.h"
#include "eventManager.h"
#include "functions.h"
#include "orderSystem.h"

int stopBtnPressed = 0; 
int buttonStates[3][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}}; 


int getButtonSignal(elev_button_type_t panelType, int orderedFloor){
	if(panelType == BUTTON_CALL_UP && orderedFloor < 3)
		return elev_get_button_signal(panelType,orderedFloor);
	else if(panelType == BUTTON_CALL_DOWN && orderedFloor > 0)
		return elev_get_button_signal(panelType,orderedFloor);
	else if(panelType == BUTTON_COMMAND)
		return elev_get_button_signal(panelType,orderedFloor);
	else
		return 0;
}

void checkInputs() {
	int currentFloor = elev_get_floor_sensor_signal();

	//Stoppknappen trykket for første gang
	if(stopBtnPressed == 0 && elev_get_stop_signal() == 1){
		stopBtnPressed = 1;
		fsmEvStopBtnPressed();
	}

	//Stoppknappen sluppet
	else if (stopBtnPressed == 1 && elev_get_stop_signal() == 0){
		stopBtnPressed = 0;
		fsmEvStopBtnReleased();
	}

	if(stopBtnPressed == 0){
		//Sjekker alle panelknapper
		for(elev_button_type_t panelType = BUTTON_CALL_UP; panelType <= BUTTON_COMMAND; panelType++){
			for(int orderedFloor = 0; orderedFloor < 4; orderedFloor++){
				if(getButtonSignal(panelType, orderedFloor) && !buttonStates[panelType][orderedFloor]){
					buttonStates[panelType][orderedFloor] = 1;
					fsmEvBtnPressed(currentFloor,orderedFloor, panelType);
				}
				else if(!getButtonSignal(panelType, orderedFloor) && buttonStates[panelType][orderedFloor]){
					buttonStates[panelType][orderedFloor] = 0;
				}
			}
		}
		
		if(currentFloor != -1) {
			fsmEvFloorSignal(currentFloor);
		}
	}
}
