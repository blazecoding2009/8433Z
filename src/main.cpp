#include <optional>

#include "autotune.hpp"
#include "lemlib/api.hpp"
#include "main.h"
#include "robodash/api.h"

#include "auton/autons.hpp"
#include "hardware.hpp"
#include "helpers.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

namespace {
void printAutotuneResult(const char* label, const autotune::PIDAutotuneResult& result)
{
	if (result.success)
	{
		pros::lcd::print(0, "%s OK", label);
		pros::lcd::print(1, "kP %.2f kI %.2f", result.kP, result.kI);
		pros::lcd::print(2, "kD %.2f Ku %.2f", result.kD, result.Ku);
		pros::lcd::print(3, "Tu %.2fs Amp %.2f", result.Tu, result.amplitude);
	}
	else
	{
		pros::lcd::print(0, "%s FAIL", label);
		pros::lcd::print(1, "%s", result.message.c_str());
		pros::lcd::print(2, " ");
		pros::lcd::print(3, " ");
	}
}

void runAutotuneRoutine()
{
	pros::lcd::clear();
	pros::lcd::print(0, "Running autotune...");
	controller.rumble(".");

	auto linearResult = autotune::autotuneLinear();
	printAutotuneResult("Linear", linearResult);

	auto angularResult = autotune::autotuneAngular();
	printAutotuneResult("Angular", angularResult);

	controller.rumble(linearResult.success && angularResult.success ? "-" : ".. ");
}
} // namespace

void move_forward_auton()
{
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0, 4, 1000, {.maxSpeed = 60});
	chassis.waitUntilDone();
}

rd::Selector selector({
    {"Right Side", &right_side_auton, "", 180},
    {"move fwd", &move_forward_auton, "", 0},
    {"Skills", &skills_auton, "", 360},
});

rd::Console console;

void initialize() {
	    // pros::lcd::initialize(); // initialize brain screen

	chassis.calibrate();

	// pros::Task screen_task([&]() {
    //     while (true) {
    //         // print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    //         // delay to save resources
    //         pros::delay(20);
    //     }
    // });

	selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
		if (routine == std::nullopt) {
			console.printf("No routine selected\n");
		} else {
			console.printf("Selected Routine: %s\n", routine.value().name.c_str());
		}
	});
}

void disabled() {
}

void competition_initialize() { selector.focus(); }

void autonomous() { 
	//right_side_auton(); 
	// skills_auton();
	selector.get_auton();
}

void opcontrol() {
	static bool descoreExtended = true;
	static bool matchLoaderExtended = false;
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

		if (l2Held) {
			scoreHigh();
		} else if (l1Held) {
			scoreMid();
		} else if (r1Held) {
			scoreLow();
		} else if (r2Held) {
			scoring_motor.move(0);
			intake(127, 127);
		} else {
			stopScore();
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			descoreExtended = !descoreExtended;
			descore.set_value(descoreExtended);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			matchLoaderExtended = !matchLoaderExtended;
			setMatchLoader(matchLoaderExtended);
		}

		// if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
		// 	chassis.setPose(0, 0, 180);
		// 	chassis.moveToPoint(0, -48, 10000);		
		// 	}

		// if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
		// 	rightside();
		// }



		pros::delay(10);
	}
}
