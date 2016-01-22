#include "eventManager.h"
#include "elev.h"
#include <stdio.h>
#include "orderSystem.h"
#include "functions.h"

typedef enum {
	stateIdle,
	stateMoving,
	stateDoorOpen
} TState;

TState currentState = stateIdle;
elev_motor_direction_t direction = DIRN_STOP;
int previousFloor = -1;

void fsmEvBtnPressed(int currentFloor,int orderedFloor,elev_button_type_t panelType) {
	insertElevatorOrder(previousFloor, orderedFloor,elev_get_floor_sensor_signal(), direction, panelType);

	if(currentFloor != orderedFloor){
		setBtnLight(panelType, orderedFloor, 1);
	}

	switch(currentState){
		case stateIdle:
			direction = getDirection(currentFloor,previousFloor, direction);
			elev_set_motor_direction(direction);
			if(direction == DIRN_STOP) {
				startTimer();
				elev_set_door_open_lamp(1);
				currentState = stateDoorOpen;
			} else {
				currentState = stateMoving;
			}
			break;
		case stateDoorOpen:
			if(currentFloor == orderedFloor) {
				startTimer();
			}
		default:
			break;		
	}
	printOrders();
}

void fsmEvStopBtnPressed() {
	elev_set_stop_lamp(1);
	turnOffBtnLights();
	storePreviousDirection(direction);
	elev_set_motor_direction(DIRN_STOP);
	direction = DIRN_STOP;

	if(elev_get_floor_sensor_signal() != -1){
		elev_set_door_open_lamp(1);
		startTimer();
	}
}

void fsmEvStopBtnReleased() {
	elev_set_stop_lamp(0);
	deleteAllOrders();

	if (elev_get_floor_sensor_signal() != -1)
		currentState = stateDoorOpen;
	else 
		currentState = stateIdle;
}


void fsmEvFloorSignal(int currentFloor) {
	previousFloor = currentFloor;
	elev_motor_direction_t currentDirection;
	switch(currentState){
		case stateMoving:
			currentDirection = getDirection(currentFloor, previousFloor, direction);
			elev_set_motor_direction(currentDirection);
			if(currentDirection == DIRN_STOP) {
				elev_set_door_open_lamp(1);
				setBtnLight(BUTTON_COMMAND, currentFloor, 0);
				setBtnLight(BUTTON_CALL_UP, currentFloor, 0);
				setBtnLight(BUTTON_CALL_DOWN, currentFloor, 0);
				startTimer();
				currentState = stateDoorOpen;
			}
			break;

		case stateDoorOpen:
			if(getTime() > 3){
				elev_set_door_open_lamp(0);
				direction = getDirection(currentFloor, previousFloor, direction);
				elev_set_motor_direction(direction);
				if(direction == DIRN_STOP)
					currentState = stateIdle;
				else
					currentState = stateMoving;
			}
			break;
		default:	
			break;
	}
}
