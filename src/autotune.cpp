#include "autotune.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <numeric>
#include <vector>

#include "hardware.hpp"

namespace autotune {
namespace {
constexpr float kPi = 3.14159265359f;

PIDAutotuneResult runRelayAutotune(const PIDAutotuneConfig& config,
                                   const std::function<float()>& computeError,
                                   const std::function<void(int)>& applyPower) {
    PIDAutotuneResult result;
    const int relayHigh = std::clamp(static_cast<int>(std::round(config.relayAmplitude)), -127, 127);
    const int relayLow = -relayHigh;

    auto stopDrive = [&applyPower]() { applyPower(0); };

    bool driveHigh = true;
    applyPower(relayHigh);

    float lastError = computeError();
    float maxError = std::numeric_limits<float>::lowest();
    float minError = std::numeric_limits<float>::max();
    uint32_t startTime = pros::millis();
    uint32_t lastZeroCross = 0;
    std::vector<float> periods;

    while ((pros::millis() - startTime) < static_cast<uint32_t>(config.maxDurationMs) &&
           static_cast<int>(periods.size()) < config.maxCycles) {
        float error = computeError();
        maxError = std::max(maxError, error);
        minError = std::min(minError, error);

        if (driveHigh && error < -config.hysteresis) {
            driveHigh = false;
            applyPower(relayLow);
        } else if (!driveHigh && error > config.hysteresis) {
            driveHigh = true;
            applyPower(relayHigh);
        }

        if ((error > 0 && lastError <= 0) || (error < 0 && lastError >= 0)) {
            uint32_t now = pros::millis();
            if (lastZeroCross != 0) {
                periods.push_back(static_cast<float>(now - lastZeroCross));
            }
            lastZeroCross = now;
        }

        lastError = error;
        pros::delay(config.sampleTimeMs);
    }

    stopDrive();

    if (periods.size() < 2) {
        result.message = "Insufficient oscillations captured. Increase relay amplitude or duration.";
        return result;
    }

    float amplitude = (maxError - minError) / 2.0f;
    if (amplitude < config.minAmplitude) {
        result.message = "Oscillation amplitude too small for reliable tuning.";
        return result;
    }

    size_t samplesToUse = std::min(periods.size(), static_cast<size_t>(config.maxCycles));
    float periodSum = std::accumulate(periods.end() - samplesToUse, periods.end(), 0.0f);
    float avgPeriodMs = periodSum / static_cast<float>(samplesToUse);
    if (avgPeriodMs <= 0) {
        result.message = "Measured oscillation period invalid.";
        return result;
    }

    float Ku = (4.0f * std::abs(static_cast<float>(relayHigh))) / (kPi * amplitude);
    float Tu = avgPeriodMs / 1000.0f; // convert to seconds
    if (Tu <= 0) {
        result.message = "Oscillation period too small.";
        return result;
    }

    result.success = true;
    result.Ku = Ku;
    result.Tu = Tu;
    result.amplitude = amplitude;
    result.cyclesCaptured = static_cast<int>(periods.size());
    result.kP = 0.6f * Ku;
    result.kI = 1.2f * Ku / Tu;
    result.kD = 0.075f * Ku * Tu;
    result.message = "Autotune complete";

    return result;
}

float degToRad(float deg) { return deg * kPi / 180.0f; }

float wrapAngle(float angle) {
    while (angle > 180.0f) angle -= 360.0f;
    while (angle < -180.0f) angle += 360.0f;
    return angle;
}

PIDAutotuneConfig defaultLinearConfig() {
    PIDAutotuneConfig cfg;
    cfg.target = 24.0f;
    cfg.relayAmplitude = 127.0f;
    cfg.hysteresis = 0.5f;
    cfg.minAmplitude = 0.25f;
    cfg.maxCycles = 6;
    cfg.maxDurationMs = 20000;
    cfg.sampleTimeMs = 10;
    return cfg;
}

PIDAutotuneConfig defaultAngularConfig() {
    PIDAutotuneConfig cfg;
    cfg.target = 90.0f;
    cfg.relayAmplitude = 127.0f;
    cfg.hysteresis = 2.0f;
    cfg.minAmplitude = 1.0f;
    cfg.maxCycles = 6;
    cfg.maxDurationMs = 25000;
    cfg.sampleTimeMs = 10;
    return cfg;
}

} // namespace

PIDAutotuneResult autotuneLinear(const PIDAutotuneConfig& config) {
    lemlib::Pose startPose = chassis.getPose();
    float headingRad = degToRad(startPose.theta);

    auto errorFn = [startPose, headingRad, target = config.target]() {
        lemlib::Pose pose = chassis.getPose();
        float dx = pose.x - startPose.x;
        float dy = pose.y - startPose.y;
        float forward = dx * std::cos(headingRad) + dy * std::sin(headingRad);
        return target - forward;
    };

    auto driveFn = [](int power) {
        int clipped = std::clamp(power, -127, 127);
        left_motors.move(clipped);
        right_motors.move(clipped);
    };

    return runRelayAutotune(config, errorFn, driveFn);
}

PIDAutotuneResult autotuneLinear() {
    return autotuneLinear(defaultLinearConfig());
}

PIDAutotuneResult autotuneAngular(const PIDAutotuneConfig& config) {
    lemlib::Pose startPose = chassis.getPose();
    float targetHeading = wrapAngle(startPose.theta + config.target);

    auto errorFn = [targetHeading]() {
        lemlib::Pose pose = chassis.getPose();
        float delta = wrapAngle(targetHeading - pose.theta);
        return delta;
    };

    auto driveFn = [](int power) {
        int clipped = std::clamp(power, -127, 127);
        left_motors.move(-clipped);
        right_motors.move(clipped);
    };

    return runRelayAutotune(config, errorFn, driveFn);
}

PIDAutotuneResult autotuneAngular() {
    return autotuneAngular(defaultAngularConfig());
}

} // namespace autotune
