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

rd::Selector selector({
    {"Left Side", &left_side_auton, "", 0},
    {"Right Side", &right_side_auton, "", 180},
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

void autonomous() { right_side_auton(); }


void rightside(){
	// set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
	scoreHigh();  // intake
	//queue balls (intake)
	chassis.moveToPose(12, 37, 24, 2000, {.maxSpeed = 60});
	chassis.turnToHeading(114, 1000);
	match_loader.set_value(true);
	chassis.moveToPoint(36, 10, 2000);
	chassis.turnToHeading(180,  2000);
	descore.set_value(false);
	chassis.moveToPose(36,-20,180,1500, {.maxSpeed = 150});
	chassis.moveToPose(36.73, 30, 180,  1500, {.forwards = false, .minSpeed = 60}, false);
	scoreHigh();  // intake
	pros::delay(3000);
	descore.set_value(true);
	chassis.moveToPoint(36.73, 17, 1000, {.minSpeed = 60}, false);
	chassis.turnToHeading(130, 1000);
	chassis.moveToPoint(28, 22, 1000, {.forwards = false});
	chassis.turnToHeading(180, 1000);
	chassis.moveToPoint(28, 45, 3000, {.forwards=false,.maxSpeed = 60}, false);
}

void leftside(){
	chassis.setPose(0, 0, 0);

	scoreHigh();
	chassis.moveToPose( -12, 37, -21, 2000, {.minSpeed = 50}, false);
	pros::delay(300);
	chassis.turnToHeading(-131, 1000); // fix
	chassis.moveToPose(7, 44, -131, 1600,{.forwards=false}, false);
	scoreHigh();
	pros::delay(400);
	scoreHigh();
	pros::delay(200);
	chassis.moveToPoint(-34, 8, 2000);
	chassis.turnToHeading(180, 1000);
	match_loader.set_value(true);
	chassis.moveToPoint(-34, -20, 1700, {.maxSpeed = 40});
	chassis.moveToPoint(-34, 30, 1000, {.forwards=false,.maxSpeed = 80}, false);
	scoreHigh();
	pros::delay(2000);
	descore.set_value(false);
	chassis.moveToPoint(-36, 17, 1000, {.minSpeed = 60}, false);
	chassis.moveToPoint(-36, 40, 1000, {.forwards=false,.minSpeed = 200}, false);
}

void soloAWP(){
	// set position to x:0, y:0, heading:0
    chassis.setPose(-1, -1.5, -90);
   
	scoreHigh();

	chassis.moveToPoint(-34, 5, 1000);
	chassis.turnToHeading(180, 1000);
	descore.set_value(true);
	chassis.moveToPoint(-34, -20, 1300, {.maxSpeed = 50, .minSpeed = 50});
	chassis.moveToPoint(-34, 30, 1000, {.forwards=false,.minSpeed = 80});
	pros::delay(800);
	scoreHigh();
	pros::delay(1500);
	descore.set_value(false);

	chassis.moveToPoint(-34, 17, 1000, {.minSpeed = 60}, false);

	chassis.turnToHeading(90, 700, {}, false);
	scoreHigh();
	chassis.moveToPose( -15.5, 34, -21, 2000, {.minSpeed = 70}, false);
	pros::delay(300);
	chassis.turnToHeading(-131, 700); 
	chassis.moveToPose(10, 47, -131, 1000,{.forwards=false, .minSpeed = 100}, false);
	scoreHigh();
	pros::delay(700);

	scoreHigh();
	chassis.moveToPose(52, 34, 90, 1000, {.minSpeed = 80}, false);

	chassis.moveToPoint(64, 10, 1000, {.minSpeed = 70});
	chassis.turnToHeading(180, 1000);

	chassis.moveToPoint(64, 30, 1000, {.forwards = false, .minSpeed = 80});
	pros::delay(700);
	scoreHigh();
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

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			chassis.setPose(0, 0, 180);
			chassis.moveToPoint(0, -48, 10000);		
			}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			rightside();
		}



		pros::delay(10);
	}
}
