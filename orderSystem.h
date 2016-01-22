#ifndef ORDERSYSTEM_H
#define ORDERSYSTEM_H
#include "elev.h"

//Gir neste retning heisen skal kjøre
elev_motor_direction_t getDirection(int currentFloor, int previousFloor, elev_motor_direction_t elevatorDirection);

//Legger til en ny bestilling
void insertElevatorOrder(int previousFloor, int orderedFloor, int currentFloor, elev_motor_direction_t direction, elev_button_type_t panelType);

//Fjerner alle bestillinger
void deleteAllOrders();

int isOrdersBelow(int floor);
int isOrdersAbove(int floor);
void storePreviousDirection(elev_motor_direction_t direction);

void printOrders();
#endif