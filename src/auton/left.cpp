#include "../hardware.hpp"
#include "../helpers.hpp"
#include "auton/autons.hpp"

#include "lemlib/api.hpp"

void left_side_auton() {
	/* CODEGEN EXPORT: LemLib */

chassis.setPose(-48.000000, 18.000000, 0.000000);

chassis.moveToPoint(-48.0, 24.0, 552);
pros::delay(50);
chassis.moveToPoint(-48.0, 48.0, 1104);
chassis.waitUntil(8.64);
intake(-127, -127);
setMatchLoader(true);
chassis.waitUntilDone();
pros::delay(50);
chassis.turnToHeading(271.050137, 860);
chassis.moveToPoint(-56.639158, 48.158359, 663);
pros::delay(50);
chassis.turnToHeading(269.409343, 500);
chassis.moveToPoint(-61.000585, 48.113396, 500);
pros::delay(2000);
chassis.turnToHeading(270.20303, 500);
chassis.moveToPoint(-29.0, 48.0, 1293, {.forwards = false});
descore.set_value(false);

// Estimated total time: 6.23 s

}
