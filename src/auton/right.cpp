#include "../hardware.hpp"
#include "../helpers.hpp"
#include "auton/autons.hpp"

#include "lemlib/api.hpp"

void right_side_auton() {
	/* CODEGEN EXPORT: LemLib */

	chassis.setPose(-48.000000, -12.000000, 180.000000);

	chassis.moveToPoint(-48.0, -48.0, 2000, {.maxSpeed = 100});
	chassis.waitUntil(20.307692);
	setMatchLoader(true);
	descore.set_value(false);
	intake(127, 127);
	chassis.waitUntilDone();
	pros::delay(50);
	chassis.turnToHeading(268.090848, 1356, {.maxSpeed = 100});
	chassis.moveToPoint(-55.2, -48.24, 1105, {.maxSpeed = 100});
	pros::delay(50);
	chassis.turnToHeading(270.818455, 1000, {.maxSpeed = 100});
	chassis.moveToPoint(-62, -48.157127, 1043, {.maxSpeed = 127});
	pros::delay(3000);
	chassis.turnToHeading(269.718678, 1000, {.maxSpeed = 100});
	chassis.moveToPoint(-29.0, -50.0, 1793, {.forwards = false, .maxSpeed = 127});
	chassis.waitUntilDone();
	descore.set_value(true);
	scoreHigh();
	pros::delay(3000);

	chassis.moveToPoint(-35.0, -50.0, 750, {.forwards = false, .maxSpeed = 100});
	descore.set_value(false);
	chassis.moveToPoint(
	    -28.0, -50.0, 1500,
	    {
	        .forwards = false,
	        .maxSpeed = 127,
	        .minSpeed = 127,
	    }
	);

	// Estimated total time: 9.22 s
}
