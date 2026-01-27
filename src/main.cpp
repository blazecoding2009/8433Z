#include <optional>

#include "lemlib/api.hpp"
#include "main.h"
#include "robodash/api.h"

#include "auton/autons.hpp"
#include "hardware.hpp"
#include "helpers.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

rd::Selector selector({
    {"Left Side", &left_side_auton, "", 0},
    {"Right Side", &right_side_auton, "", 180},
    {"Skills", &skills_auton, "", 360},
});

rd::Console console;

void initialize() {
	static pros::adi::Led led('H', 10);
	led.set_all(0x000080);
	chassis.calibrate();

	selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
		if (routine == std::nullopt) {
			console.printf("No routine selected\n");
		} else {
			console.printf("Selected Routine: %s\n", routine.value().name.c_str());
		}
	});
}

void disabled() {
	static pros::adi::Led led('H', 10);
	led.set_all(0x000080);
}

void competition_initialize() { selector.focus(); }

void autonomous() { selector.run_auton(); }

void opcontrol() {
	static bool descoreExtended = true;
	static bool lipExtended = false;
	static bool r2Held = false;
	static bool r1Held = false;
	static bool l1Held = false;
	static bool l2Held = false;

	while (true) {
		int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		chassis.curvature(leftY, rightX);

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) r2Held = true;
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_R2)) r2Held = false;
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) r1Held = true;
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_R1)) r1Held = false;
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) l1Held = true;
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L1)) l1Held = false;
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) l2Held = true;
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L2)) l2Held = false;

		if (r2Held) {
			scoreHigh();
		} else if (r1Held) {
			scoreMid();
		} else if (l1Held) {
			scoreLow();
		} else if (l2Held) {
			scoring_motor.move(0);
			intake(-127, -127, 127);
		} else {
			stopScoreMidHigh();
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			descoreExtended = !descoreExtended;
			descore.set_value(descoreExtended);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			lipExtended = !lipExtended;
			setLip(lipExtended);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			// chassis.setPose(0, 0, 0);
			// chassis.turnToHeading(90, 10000, {.maxSpeed = 127});
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			autonomous();
		}

		pros::delay(10);
	}
}
