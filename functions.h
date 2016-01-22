#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "elev.h"

//Kjører ned til en etasje er nådd
void initElevator();

//Setter etasjelys til den sist besøkte etasjen
void updateFloorLight();

//Skrur av alle knappelys
void turnOffBtnLights(); 

//Setter et spesifisert knappelys på eller av
void setBtnLight(elev_button_type_t panelType, int btn, int toggleLight);

void startTimer();

//Returnerer tiden siden sist kall på startTimer()
int getTime();

#endif