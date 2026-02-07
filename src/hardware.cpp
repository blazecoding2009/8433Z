#include "hardware.hpp"

pros::MotorGroup right_motors({11,12,13}, pros::MotorGearset::blue);
pros::MotorGroup left_motors({-14,-15,-16}, pros::MotorGearset::blue);
pros::Motor intake_motor(-1, pros::MotorGearset::blue);
pros::Motor mid(-2, pros::MotorGearset::blue);
pros::Motor scoring_motor(3, pros::MotorGearset::blue);
pros::Distance front_distance_sensor(8);

pros::Imu imu(4);

pros::Rotation vertical_encoder(-17);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, .75);

pros::Rotation horizontal_encoder(6);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, -6);

pros::ADIDigitalOut midhigh('C');
pros::ADIDigitalOut descore('B');
pros::ADIDigitalOut match_loader('A');

const int MOTOR_TEETH = 36;
const int WHEEL_TEETH = 60;
const int MOTOR_CARTRIDGE_RPM_BLUE = 600;
const int DRIVETRAIN_RPM = MOTOR_CARTRIDGE_RPM_BLUE * MOTOR_TEETH / WHEEL_TEETH;

lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 10.5, lemlib::Omniwheel::NEW_325, DRIVETRAIN_RPM, 2);
lemlib::OdomSensors sensors(&vertical_tracking_wheel, nullptr, nullptr, nullptr, &imu);

lemlib::ControllerSettings lateral_controller(15, 0, 6, 0, 1, 250, 3, 400, 0);
lemlib::ControllerSettings angular_controller(8, 0, 16, 0, 1, 150, 3, 350, 0);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);
