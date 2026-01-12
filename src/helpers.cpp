#include "helpers.hpp"
#include "hardware.hpp"

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

void setMidhigh(bool extended)
{
    midhigh.set_value(extended);
}

void setLip(bool extended)
{
    lip.set_value(extended);
}

bool toggleMidhigh()
{
    static bool midhighExtended = false;
    midhighExtended = !midhighExtended;
    setMidhigh(midhighExtended);
    return midhighExtended;
}

bool toggleLip()
{
    static bool lipExtended = false;
    lipExtended = !lipExtended;
    setLip(lipExtended);
    return lipExtended;
}
