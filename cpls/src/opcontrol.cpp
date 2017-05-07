#include "main.h"

void operatorControl() {
	pid::enabled[0] = false;
	pid::enabled[1] = false;

	motor* bob = motors::init(2, 1, 127, .8);
	bob->set(127);
	delay(1000);
	bob->set(0);
	sensors::reset();
	rerun::record();

	while (true) {
		drive::tank();
		delay(50);
	}

	rerun::stop();
}
