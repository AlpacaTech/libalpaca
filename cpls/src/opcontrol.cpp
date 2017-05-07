#include "main.h"

void operatorControl() {
	sensors::reset();
	rerun::record();
	while (1) {
		drive::tank();
		delay(50);
	}
	rerun::stop();
}
