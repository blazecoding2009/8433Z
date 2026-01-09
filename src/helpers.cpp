#include "helpers.hpp"
#include "main.h"

extern pros::Motor intake_motor;
extern pros::Motor mid;
extern pros::Motor scoring_first_stage;
extern pros::Motor scoring_second_stage;

void intake(int intakePower, int midPower, int firstStagePower)
{
    intake_motor.move(intakePower);
    mid.move(midPower);
    scoring_first_stage.move(firstStagePower);
}

void stopIntake()
{
    intake(0, 0, 0);
}

void scoreMidHigh()
{
    scoring_second_stage.move(127);
    intake(-127, -127, 127);
}

void stopScoreMidHigh()
{
    scoring_second_stage.move(0);
    stopIntake();
}

void scoreLow()
{
    scoring_second_stage.move(0);
    intake(127, 127, -127);
}
