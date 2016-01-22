#include "elev.h"
#include <stdio.h>
#include "functions.h"
#include "inputManager.h"


int main() {
	// Initialize hardware
	if (!elev_init()) {
		printf("Unable to initialize elevator hardware!\n");
		return 1;
	}
	
	initElevator();

	while(1) {
		checkInputs();
		updateFloorLight();
	}

    return 0;
}
