#include "main.h"
#include "lemlib/api.hpp"
#include "helpers.hpp"
#include "hardware.hpp"


void initialize()
{
    pros::lcd::initialize();
    chassis.calibrate();
}

void disabled()
{
}

void competition_initialize() {}

pros::Controller controller(pros::E_CONTROLLER_MASTER);

ASSET(auton_txt);

void autonomous()
{
    chassis.setPose(-59.159, -17.598, 88.701);
    chassis.follow(auton_txt, 15, 2000);
}

void opcontrol()
{
    static bool descoreExtended = true;
    static bool lipExtended = false;
    static bool midlvl = false;
    static bool r2Held = false;
    static bool l1Held = false;
    static bool l2Held = false;

    while (true)
    {
        pros::lcd::print(0, "X: %.2f in", chassis.getPose().x);
        pros::lcd::print(1, "Y: %.2f in", chassis.getPose().y);
        pros::lcd::print(2, "Theta: %.1f deg", chassis.getPose().theta);

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.curvature(leftY, rightX);

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
            r2Held = true;
        if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_R2))
            r2Held = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
            l1Held = true;
        if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L1))
            l1Held = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
            l2Held = true;
        if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L2))
            l2Held = false;

        if (r2Held)
        {
            scoreMidHigh();
        }
        else if (l1Held)
        {
            scoreLow();
        }
        else if (l2Held)
        {
            scoring_second_stage.move(0);
            intake(-127, -127, 127);
        }
        else
        {
            stopScoreMidHigh();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        {
            descoreExtended = !descoreExtended;
            descore.set_value(descoreExtended);
        }

        // Solenoid 3 toggle with B
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
        {
            lipExtended = !lipExtended;
            lip.set_value(lipExtended);
            // autonomous();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
        {
            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(180, 10000);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
        {
            autonomous();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        {
            midlvl = !midlvl;
            midhigh.set_value(midlvl);
        }

        
        pros::delay(10);
    }
}