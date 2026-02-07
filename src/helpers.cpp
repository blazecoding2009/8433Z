#include "helpers.hpp"
#include "hardware.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>

namespace {
constexpr int kFullPower = 127;
bool s_midhighExtended = false;
constexpr float kMmToIn = 0.039370079f;
constexpr int kMaxValidDistanceMm = 4000;
constexpr int kDistanceToleranceMm = 5;
constexpr int kMinCreepSpeed = 10;
}

void intake(int intakePower, int midPower)
{
    intake_motor.move(intakePower);
    mid.move(midPower);
}

void stopIntake()
{
    intake(0, 0);
}

void scoreHigh()
{
    intake(kFullPower, kFullPower);
    scoring_motor.move(kFullPower);
}

void scoreMid()
{
    intake(kFullPower, kFullPower);
    scoring_motor.move(-kFullPower);
}

void stopScore()
{
    scoring_motor.move(0);
    stopIntake();
}

void scoreLow()
{
    intake(-kFullPower, -kFullPower);
    scoring_motor.move(-kFullPower);
}

void setMidhigh(bool extended)
{
    s_midhighExtended = extended;
    midhigh.set_value(extended);
}

bool toggleMidhigh()
{
    s_midhighExtended = !s_midhighExtended;
    setMidhigh(s_midhighExtended);
    return s_midhighExtended;
}

void setMatchLoader(bool extended)
{
    match_loader.set_value(extended);
}

bool toggleMatchLoader()
{
    static bool loaderExtended = false;
    loaderExtended = !loaderExtended;
    setMatchLoader(loaderExtended);
    return loaderExtended;
}

float getFrontDistanceInches()
{
    const int readingMm = front_distance_sensor.get_distance();
    if (readingMm <= 0 || readingMm > kMaxValidDistanceMm)
        return std::numeric_limits<float>::quiet_NaN();
    return readingMm * kMmToIn;
}

bool driveToFrontDistanceMm(int targetDistanceMm, int maxSpeed, int slowRangeMm, int timeoutMs)
{
    const uint32_t start = pros::millis();

    auto drive = [](int velocity) {
        left_motors.move_velocity(velocity);
        right_motors.move_velocity(velocity);
    };

    while (pros::millis() - start < static_cast<uint32_t>(timeoutMs))
    {
        const int readingMm = front_distance_sensor.get_distance();
        if (readingMm <= 0 || readingMm > kMaxValidDistanceMm)
            break;

        const int error = readingMm - targetDistanceMm;
        if (std::abs(error) <= kDistanceToleranceMm)
        {
            drive(0);
            return true;
        }

        int commanded = maxSpeed;
        const int absError = std::abs(error);
        if (absError < slowRangeMm)
        {
            commanded = std::max(kMinCreepSpeed, maxSpeed * absError / std::max(1, slowRangeMm));
        }

        commanded *= (error > 0 ? 1 : -1);
        drive(commanded);
        pros::delay(10);
    }

    drive(0);
    return false;
}

bool syncPoseFromFrontWall(float wallCoordinateInches, bool alignAlongY, bool facingPositiveAxis,
                           float sensorOffsetInches)
{
    const int readingMm = front_distance_sensor.get_distance();
    if (readingMm <= 0 || readingMm > kMaxValidDistanceMm)
        return false;

    const float distanceInches = readingMm * kMmToIn;
    const float offsetFromCenter = distanceInches + sensorOffsetInches;
    const float signedOffset = facingPositiveAxis ? -offsetFromCenter : offsetFromCenter;

    auto currentPose = chassis.getPose();
    if (alignAlongY)
    {
        const float newY = wallCoordinateInches + signedOffset;
        chassis.setPose(currentPose.x, newY, currentPose.theta);
    }
    else
    {
        const float newX = wallCoordinateInches + signedOffset;
        chassis.setPose(newX, currentPose.y, currentPose.theta);
    }

    return true;
}