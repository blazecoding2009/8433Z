#include "hardware.hpp"

pros::MotorGroup right_motors({11,12,13}, pros::MotorGearset::blue);
pros::MotorGroup left_motors({-14,-15,-16}, pros::MotorGearset::blue);
pros::Motor intake_motor(1, pros::MotorGearset::blue);
pros::Motor mid(2, pros::MotorGearset::blue);
pros::Motor scoring_motor(3, pros::MotorGearset::blue);

pros::Imu imu(13);

pros::Rotation vertical_encoder(-5);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, .75);

pros::Rotation horizontal_encoder(6);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -6);

pros::ADIDigitalOut midhigh('A');
pros::ADIDigitalOut descore('B');
pros::ADIDigitalOut lip('C');

const int MOTOR_TEETH = 36;
const int WHEEL_TEETH = 60;
const int MOTOR_CARTRIDGE_RPM_BLUE = 600;
const int DRIVETRAIN_RPM = MOTOR_CARTRIDGE_RPM_BLUE * MOTOR_TEETH / WHEEL_TEETH;

lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 10.5, lemlib::Omniwheel::NEW_325, DRIVETRAIN_RPM, 2);
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, nullptr, nullptr, &imu);

lemlib::ControllerSettings lateral_controller(10, 0, 3, 0, 1, 100, 3, 250, 0);
lemlib::ControllerSettings angular_controller(8, 0, 15, 0, 0, 0, 0, 0, 0);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
