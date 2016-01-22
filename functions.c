#include "functions.h"
#include <time.h>

time_t start,end;

void initElevator(){
	if(elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(DIRN_DOWN);
		while(elev_get_floor_sensor_signal() == -1);
		elev_set_motor_direction(DIRN_STOP);	
	}
}

void updateFloorLight() {
	int currentFloor = elev_get_floor_sensor_signal();
	if (currentFloor != -1) {
		elev_set_floor_indicator(currentFloor);
	} 
}

void turnOffBtnLights() {
	for (int i = 0; i < 4; i++) {
		setBtnLight(BUTTON_COMMAND, i, 0);
		setBtnLight(BUTTON_CALL_DOWN, i, 0);
		setBtnLight(BUTTON_CALL_UP, i, 0);
	}
}

void setBtnLight(elev_button_type_t panelType, int btn, int toggleLight) {
	if(((panelType == BUTTON_CALL_DOWN) && (btn > 0)) || ((panelType == BUTTON_CALL_UP) && (btn < 3)))
		elev_set_button_lamp(panelType, btn, toggleLight);
	else if (panelType == BUTTON_COMMAND) 
		elev_set_button_lamp(panelType,btn,toggleLight);
}


void startTimer(){
	start = clock();
}

int getTime() {
	end = clock();
	return (end - start) / CLOCKS_PER_SEC;
}