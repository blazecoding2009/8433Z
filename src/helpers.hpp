#pragma once

constexpr float FRONT_SENSOR_OFFSET_IN = 6.0f; // update to real sensor offset once measured

void intake(int intakePower, int midPower);
void stopIntake();
void scoreHigh();
void scoreMid();
void stopScore();
void scoreLow();
void setMidhigh(bool extended);
bool toggleMidhigh();
void setMatchLoader(bool extended);
bool toggleMatchLoader();
float getFrontDistanceInches();
bool driveToFrontDistanceMm(int targetDistanceMm, int maxSpeed = 80, int slowRangeMm = 120, int timeoutMs = 3000);
bool syncPoseFromFrontWall(float wallCoordinateInches, bool alignAlongY = true,
						   bool facingPositiveAxis = true, float sensorOffsetInches = FRONT_SENSOR_OFFSET_IN);
