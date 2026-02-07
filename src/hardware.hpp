#pragma once

#include "main.h"
#include "lemlib/api.hpp"

extern pros::MotorGroup right_motors;
extern pros::MotorGroup left_motors;
extern pros::Motor intake_motor;
extern pros::Motor mid;
extern pros::Motor scoring_motor;
extern pros::Distance front_distance_sensor;

extern pros::Imu imu;
extern pros::Rotation vertical_encoder;
extern pros::Rotation horizontal_encoder;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::TrackingWheel horizontal_tracking_wheel;

extern pros::ADIDigitalOut midhigh;
extern pros::ADIDigitalOut descore;
extern pros::ADIDigitalOut match_loader;

extern const int MOTOR_TEETH;
extern const int WHEEL_TEETH;
extern const int MOTOR_CARTRIDGE_RPM_BLUE;
extern const int DRIVETRAIN_RPM;

extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;
