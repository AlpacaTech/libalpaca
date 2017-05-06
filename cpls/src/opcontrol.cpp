#include "main.h"

void operatorControl() {
	sensors::reset();
	while (1) {
		drive::tank();
		delay(50);
	}
}
