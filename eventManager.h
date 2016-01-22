#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "elev.h"

void fsmEvBtnPressed(int currentFloor,int orderedFloor,elev_button_type_t panelType);
void fsmEvStopBtnPressed();
void fsmEvStopBtnReleased();
void fsmEvFloorSignal(int currentFloor);

#endif