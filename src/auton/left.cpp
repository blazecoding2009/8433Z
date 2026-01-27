#include "../hardware.hpp"
#include "../helpers.hpp"
#include "auton/autons.hpp"

#include "lemlib/api.hpp"

void left_side_auton() {
	/* CODEGEN EXPORT: LemLib */

	chassis.setPose(-62.880000, 16.800000, 90.000000);

	chassis.moveToPoint(-41.76, 16.8, 1339);
	pros::delay(50);
	chassis.turnToHeading(356.308614, 1131);
	chassis.moveToPoint(-42.24, 24.24, 937);
	pros::delay(50);
	chassis.turnToHeading(90.753848, 1134);
	chassis.moveToPoint(-24.0, 24.0, 1259);
	chassis.waitUntil(2.889935);
	intake(-127, -127, 127);
	chassis.waitUntil(12.777202);
	setLip(true);
	chassis.waitUntilDone();
	pros::delay(1500);
	chassis.turnToHeading(135.0, 839);
	chassis.moveToPoint(-13.349747, 13.349747, 1163);
	chassis.waitUntil(8.023323);
	setLip(false);
	stopScoreMidHigh();
	chassis.waitUntil(15.061732);
	setMidhigh(true);
	scoreHigh();
	chassis.waitUntilDone();
	pros::delay(2000);
	chassis.moveToPoint(-48.72, 48.24, 2020, {.forwards = false});
	chassis.waitUntil(44.553827);
	setLip(true);
	intake(-127, -127, 127);
	chassis.waitUntilDone();
	pros::delay(50);
	chassis.turnToHeading(269.409343, 1287);
	chassis.moveToPoint(-56.639158, 48.158359, 956);
	pros::delay(50);
	chassis.moveToPoint(-59.000691, 48.134013, 805);
	pros::delay(2000);
	chassis.turnToHeading(270.213438, 778);
	chassis.moveToPoint(-45.839437, 48.084985, 1102, {.forwards = false});
	pros::delay(50);
	chassis.swingToHeading(
	    269.997357, DriveSide::RIGHT, 743, {.minSpeed = 40, .earlyExitRange = 7.0}
	);
	chassis.turnToHeading(90.223152, 1470);
	chassis.moveToPoint(-30.999947, 48.027239, 1156);
	chassis.waitUntil(5.260211);
	setLip(false);
	stopScoreMidHigh();
	chassis.waitUntilDone();
	setMidhigh(false);
	scoreMid();
	pros::delay(3000);
	chassis.turnToHeading(89.263881, 778);
	chassis.moveToPoint(-33.12, 48.0, 804, {.forwards = false});

	// Estimated total time: 18.69 s
}
