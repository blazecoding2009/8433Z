#pragma once

#include <string>

namespace autotune {

struct PIDAutotuneResult {
    bool success = false;
    float kP = 0.0f;
    float kI = 0.0f;
    float kD = 0.0f;
    float Ku = 0.0f;
    float Tu = 0.0f;
    float amplitude = 0.0f;
    int cyclesCaptured = 0;
    std::string message;
};

struct PIDAutotuneConfig {
    float target = 24.0f;          // inches for linear, degrees for angular
    float relayAmplitude = 80.0f;  // motor command magnitude (0-127)
    float hysteresis = 1.0f;       // tolerance band that triggers relay flip
    float minAmplitude = 0.25f;    // required oscillation amplitude in process variable
    int maxCycles = 6;             // number of oscillation periods to capture
    int maxDurationMs = 20000;     // safety timeout
    int sampleTimeMs = 10;         // loop delay
};

PIDAutotuneResult autotuneLinear(const PIDAutotuneConfig& config);
PIDAutotuneResult autotuneLinear();
PIDAutotuneResult autotuneAngular(const PIDAutotuneConfig& config);
PIDAutotuneResult autotuneAngular();

} // namespace autotune
