#include "orderSystem.h"
#include <stdio.h>


//Arrays of orders. 0 equals no order, 1 for order
int ordersUp[4] = {0,0,0,0};
int ordersDown[4] = {0,0,0,0};
elev_motor_direction_t previousDirection = DIRN_STOP;

int isOrdersBelow(int floor){
	for(int i = 0; i < floor; i++){
		if (ordersUp[i] || ordersDown[i]) 
			return 1;
	}
	return 0;
}
int isOrdersAbove(int floor){
	for(int i = floor+1; i < 4;i++){
		if(ordersUp[i] || ordersDown[i])
			return 1;
	}
	return 0;
}

void storePreviousDirection(elev_motor_direction_t direction) {
	previousDirection = direction;
}


elev_motor_direction_t getDirection(int currentFloor, int previousFloor, elev_motor_direction_t elevatorDirection){
	//Dersom heisen er stoppet mellom etasjer (nødstopp)
	if(currentFloor == -1){ 
		if(elevatorDirection == DIRN_STOP){
			if(isOrdersAbove(previousFloor) || (previousDirection == DIRN_DOWN && (ordersDown[previousFloor] || ordersUp[previousFloor])))
				return DIRN_UP;
			if(isOrdersBelow(previousFloor) || (previousDirection == DIRN_UP && (ordersDown[previousFloor] || ordersUp[previousFloor])))
				return DIRN_DOWN;
		}
	}
	if(elevatorDirection == DIRN_UP && ordersUp[currentFloor]){
		ordersUp[currentFloor] = 0;
		ordersDown[currentFloor]=0;
		return DIRN_STOP;
	} else if(elevatorDirection == DIRN_DOWN && ordersDown[currentFloor]){ 
		ordersDown[currentFloor]=0;
		ordersUp[currentFloor] = 0;
		return DIRN_STOP;
	} else if((currentFloor == 0 || currentFloor == 3) && (ordersUp[currentFloor] || ordersDown[currentFloor])){
		ordersUp[currentFloor] = 0;
		ordersDown[currentFloor] = 0;
		return DIRN_STOP;
	} 
	else if (isOrdersBelow(currentFloor) && elevatorDirection == DIRN_DOWN)
		return DIRN_DOWN;
	else if(isOrdersAbove(currentFloor) && elevatorDirection == DIRN_UP) 
		return DIRN_UP;
	else if(isOrdersAbove(currentFloor) && elevatorDirection == DIRN_DOWN)
		return DIRN_UP;
	else if(isOrdersBelow(currentFloor) && elevatorDirection == DIRN_UP)
		return DIRN_DOWN;
	else if (isOrdersAbove(currentFloor) && elevatorDirection == DIRN_STOP)
		return DIRN_UP;
	else if (isOrdersBelow(currentFloor) && elevatorDirection == DIRN_STOP)
		return DIRN_DOWN; 

	return DIRN_STOP;
}



void insertElevatorOrder(int previousFloor, int orderedFloor, int currentFloor, elev_motor_direction_t direction, elev_button_type_t panelType){
	printf("currentFloor: %d, previousFloor: %d\n",currentFloor,previousFloor);
	if(panelType == BUTTON_COMMAND){
		if(previousFloor < orderedFloor)
			ordersUp[orderedFloor] = 1;
		else if (previousFloor > orderedFloor)
			ordersDown[orderedFloor] = 1;
		else if(currentFloor == -1 && direction == DIRN_DOWN)
				ordersUp[orderedFloor] = 1;
		else if(currentFloor == -1 && direction == DIRN_DOWN)
				ordersDown[orderedFloor] = 1;
	}

	if(currentFloor != orderedFloor){
		if(panelType == BUTTON_CALL_DOWN)
			ordersDown[orderedFloor] = 1;
		else
			ordersUp[orderedFloor] = 1;
	}

}

void printOrders() {
	printf("Orders up: ");
	for(int i = 0; i < 4; i++){
		printf("%d ", ordersUp[i]);
	}
	printf("Orders down: ");
	for(int i = 0; i < 4; i++){
		printf("%d ", ordersDown[i]);
	}
	printf("\n");
}

void deleteAllOrders(){
	for(int i = 0; i < 4; i++){
		ordersUp[i] = 0;
		ordersDown[i] = 0;
	}
}
