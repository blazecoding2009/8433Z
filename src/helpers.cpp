#include "helpers.hpp"
#include "hardware.hpp"

namespace {
constexpr int kFullPower = 127;
bool s_midhighExtended = false;
}

void intake(int intakePower, int midPower, int firstStagePower)
{
    intake_motor.move(intakePower);
    mid.move(midPower);
    scoring_motor.move(firstStagePower);
}

void stopIntake()
{
    intake(0, 0, 0);
}

void scoreHigh()
{
    intake(kFullPower, kFullPower, kFullPower);
    scoring_motor.move(kFullPower);
}

void scoreMid()
{
    intake(kFullPower, kFullPower, kFullPower);
    scoring_motor.move(-kFullPower);
}

void stopScoreMidHigh()
{
    scoring_motor.move(0);
    stopIntake();
}

void scoreLow()
{
    intake(-kFullPower, -kFullPower, -kFullPower);
    scoring_motor.move(-kFullPower);
}

void setMidhigh(bool extended)
{
    s_midhighExtended = extended;
    midhigh.set_value(extended);
}

void setLip(bool extended)
{
    lip.set_value(extended);
}

bool toggleMidhigh()
{
    s_midhighExtended = !s_midhighExtended;
    setMidhigh(s_midhighExtended);
    return s_midhighExtended;
}

bool toggleLip()
{
    static bool lipExtended = false;
    lipExtended = !lipExtended;
    setLip(lipExtended);
    return lipExtended;
}