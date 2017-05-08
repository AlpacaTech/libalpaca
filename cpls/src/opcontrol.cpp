#include "main.h"

void operatorControl() {
	sensors::reset();
	rerun::record();

	while (true) {
		drive::tank();
		debug::debug();
		delay(50);
	}

	rerun::stop();
}
