#include "main.h"
#include "lemlib/api.hpp"
#include "helpers.hpp"
#include "hardware.hpp"

void initialize()
{
    static pros::ADILed led ('H', 10);
    led.set_all(0x000080);
    // pros::lcd::initialize();
    chassis.calibrate();
}

void disabled()
{
      static pros::ADILed led ('H', 10);
          led.set_all(0x000080);

}

void competition_initialize() {}

pros::Controller controller(pros::E_CONTROLLER_MASTER);

void autonomous()
{
/* CODEGEN EXPORT: LemLib */

chassis.setPose(-62.880000, -16.800000, 90.000000);

chassis.moveToPoint(-40.56, -16.8, 1371);
pros::delay(50);
chassis.turnToHeading(113.498566, 797);
chassis.moveToPoint(-24.0, -24.0, 1254);
chassis.waitUntil(5.39496);
intake(-127, -127, 127);
chassis.waitUntil(13.550308);
setLip(true);
chassis.waitUntilDone();
pros::delay(1500);
chassis.turnToHeading(45.0, 994);
chassis.moveToPoint(-13.349747, -13.349747, 1163);
chassis.waitUntil(8.023323);
setLip(false);
stopScoreMidHigh();
chassis.waitUntil(15.061732);
scoreLow();
chassis.waitUntilDone();
pros::delay(2000);
chassis.moveToPoint(-48.72, -48.24, 2020, {.forwards = false});
chassis.waitUntil(44.553827);
setLip(true);
intake(-127, -127, 127);
chassis.waitUntilDone();
pros::delay(50);
chassis.turnToHeading(270.590657, 1287);
chassis.moveToPoint(-56.639158, -48.158359, 956);
pros::delay(50);
chassis.moveToPoint(-59.000691, -48.134013, 805);
pros::delay(2000);
chassis.turnToHeading(269.786562, 778);
chassis.moveToPoint(-45.839437, -48.084985, 1102, {.forwards = false});
pros::delay(50);
chassis.swingToHeading(270.002643, DriveSide::RIGHT, 743, {.minSpeed = 40, .earlyExitRange = 7.0});
chassis.turnToHeading(89.776848, 1470);
chassis.moveToPoint(-30.999947, -48.027239, 1156);
chassis.waitUntil(5.260211);
setLip(false);
stopScoreMidHigh();
chassis.waitUntilDone();
setMidhigh(false);
scoreMidHigh();
pros::delay(3000);
chassis.turnToHeading(270.736119, 1466);
chassis.moveToPoint(-33.12, -48.0, 804);

// Estimated total time: 18.08 s

}

void opcontrol()
{
    static bool descoreExtended = true;
    static bool r2Held = false;
    static bool l1Held = false;
    static bool l2Held = false;

    while (true)
    {
        // pros::lcd::print(0, "X: %.2f in", chassis.getPose().x);
        // pros::lcd::print(1, "Y: %.2f in", chassis.getPose().y);
        // pros::lcd::print(2, "Theta: %.1f deg", chassis.getPose().theta);

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.curvature(leftY, rightX);

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
            r2Held = true;
        if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_R2))
            r2Held = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1))
            l1Held = true;
        if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L1))
            l1Held = false;
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2))
            l2Held = true;
        if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L2))
            l2Held = false;

        if (r2Held)
        {
            scoreMidHigh();
        }
        else if (l1Held)
        {
            scoreLow();
        }
        else if (l2Held)
        {
            scoring_second_stage.move(0);
            intake(-127, -127, 127);
        }
        else
        {
            stopScoreMidHigh();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
        {
            descoreExtended = !descoreExtended;
            descore.set_value(descoreExtended);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
        {
            toggleLip();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
        {
            chassis.setPose(0, 0, 0);
            chassis.turnToHeading(90, 10000, {.maxSpeed = 127});
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
        {
            autonomous();
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
        {
            toggleMidhigh();
        }

        pros::delay(10);
    }
}

//////////////////////
#include <cmath>
#include <cstdio>
#include <cstring>

// Move/turn commands are generated from your current Export templates for this style.
// Define these macros to match your project (optional):
//   CAL_SET_PROFILE(name)         -> set drive profile
//   CAL_SET_DRIVE_CAP(volts)       -> set max drive voltage
//   CAL_SET_TURN_CAP(volts)        -> set max turn voltage
//   CAL_GET_POSE_X(), _Y(), _H()   -> return odom pose (in, in, deg)
//   CAL_SET_POSE(x, y, heading)    -> reset odom pose (if available)
#ifndef CAL_SET_PROFILE
#define CAL_SET_PROFILE(name) ((void)(name))
#endif
#ifndef CAL_SET_DRIVE_CAP
#define CAL_SET_DRIVE_CAP(volts) ((void)(volts))
#endif
#ifndef CAL_SET_TURN_CAP
#define CAL_SET_TURN_CAP(volts) ((void)(volts))
#endif
#ifndef CAL_GET_POSE_X
#define CAL_GET_POSE_X() 0.0
#endif
#ifndef CAL_GET_POSE_Y
#define CAL_GET_POSE_Y() 0.0
#endif
#ifndef CAL_GET_POSE_H
#define CAL_GET_POSE_H() 0.0
#endif
#ifndef CAL_SET_POSE
#define CAL_SET_POSE(x, y, heading) ((void)(x), (void)(y), (void)(heading))
#endif

// Auton selector hint:
//   Add {CAL_AUTON_NAME, calibration_tests_auton} to your auton list, or call calibration_tests_auton() in autonomous().
static const char* CAL_AUTON_NAME = "Calibration Tests";
static const bool CAL_HAS_SETPOS = true;
static const double CAL_PI = 3.141592653589793;
static double cal_last_target_x = 0.0;
static double cal_last_target_y = 0.0;
static double cal_last_target_heading = 0.0;
static int cal_last_timeout_ms = 0;
static double cal_drive_settle_err = 1.0;
static double cal_turn_settle_err = 1.0;
static int cal_drive_settle_time_ms = 120;
static int cal_turn_settle_time_ms = 120;
void cal_set_profile(const char* profile) { CAL_SET_PROFILE(profile); }
void cal_set_drive_cap(double volts) { CAL_SET_DRIVE_CAP(volts); }
void cal_set_turn_cap(double volts) { CAL_SET_TURN_CAP(volts); }
double cal_get_pose_x_in() { return CAL_GET_POSE_X(); }
double cal_get_pose_y_in() { return CAL_GET_POSE_Y(); }
double cal_get_heading_deg() { return CAL_GET_POSE_H(); }
void cal_set_pose(double x_in, double y_in, double heading_deg) {
  chassis.setPose(x_in, y_in, heading_deg);
}
static double cal_wrap_deg(double deg) {
  double out = std::fmod(deg, 360.0);
  if (out < 0) out += 360.0;
  return out;
}
static double cal_angle_error_deg(double target_deg, double current_deg) {
  double diff = std::fmod(target_deg - current_deg + 540.0, 360.0) - 180.0;
  return std::fabs(diff);
}
static int cal_drive_timeout_ms(double dist_in, double cap_frac) {
  double cap = cap_frac < 0.2 ? 0.2 : cap_frac;
  double ms = 500.0 + (std::fabs(dist_in) * 75.0) / cap;
  return (int)std::ceil(ms);
}
static int cal_turn_timeout_ms(double angle_deg, double cap_frac) {
  double cap = cap_frac < 0.2 ? 0.2 : cap_frac;
  double ms = 500.0 + (std::fabs(angle_deg) * 12.0) / cap;
  return (int)std::ceil(ms);
}
static double cal_drive_error_in(double target_x, double target_y) {
  double dx = cal_get_pose_x_in() - target_x;
  double dy = cal_get_pose_y_in() - target_y;
  return std::sqrt(dx * dx + dy * dy);
}
static double cal_turn_error_deg(double target_deg) {
  return cal_angle_error_deg(target_deg, cal_get_heading_deg());
}
static int cal_measure_settle_ms_drive(double target_x, double target_y, int start_ms, double err_in, int hold_ms, int max_ms) {
  int inside_ms = 0;
  while (inside_ms < hold_ms && (pros::millis() - start_ms) < max_ms) {
    double err = cal_drive_error_in(target_x, target_y);
    if (err <= err_in) inside_ms += 10; else inside_ms = 0;
    pros::delay(10);
  }
  return pros::millis() - start_ms;
}
static int cal_measure_settle_ms_turn(double target_deg, int start_ms, double err_deg, int hold_ms, int max_ms) {
  int inside_ms = 0;
  while (inside_ms < hold_ms && (pros::millis() - start_ms) < max_ms) {
    double err = cal_angle_error_deg(target_deg, cal_get_heading_deg());
    if (err <= err_deg) inside_ms += 10; else inside_ms = 0;
    pros::delay(10);
  }
  return pros::millis() - start_ms;
}
void cal_drive_to(double dist_in, double cap_frac) {
  double heading_deg = cal_get_heading_deg();
  double x_in = cal_get_pose_x_in();
  double y_in = cal_get_pose_y_in();
  double delta_deg = 0.0;
  if (CAL_HAS_SETPOS) {
    cal_set_pose(0.0, 0.0, 0.0);
    heading_deg = 0.0;
    x_in = dist_in;
    y_in = 0.0;
  } else {
    double rad = heading_deg * (CAL_PI / 180.0);
    x_in = x_in + dist_in * std::cos(rad);
    y_in = y_in + dist_in * std::sin(rad);
  }
  cal_last_target_x = x_in;
  cal_last_target_y = y_in;
  cal_last_target_heading = heading_deg;
  const bool forwards = dist_in >= 0.0;
  const double drive_max_v = cap_frac * 12.0;
  const double heading_max_v = cap_frac * 12.0;
  const double drive_settle_err = cal_drive_settle_err;
  const int drive_settle_time = cal_drive_settle_time_ms;
  int timeout_ms = cal_drive_timeout_ms(dist_in, cap_frac);
  cal_last_timeout_ms = timeout_ms;
  // Template: move
  chassis.moveToPoint(x_in, y_in, timeout_ms, {.forwards = forwards, .minSpeed = 0, .earlyExitRange = 0});
}
void cal_turn_to(double heading_deg, double cap_frac) {
  double delta_deg = heading_deg;
  double turn_mag = std::fabs(delta_deg);
  turn_mag = cal_angle_error_deg(heading_deg, cal_get_heading_deg());
  cal_last_target_heading = heading_deg;
  const double turn_max_v = cap_frac * 12.0;
  const double turn_settle_err = cal_turn_settle_err;
  const int turn_settle_time = cal_turn_settle_time_ms;
  int timeout_ms = cal_turn_timeout_ms(turn_mag, cap_frac);
  cal_last_timeout_ms = timeout_ms;
  // Template: turn_global
  chassis.turnToHeading(heading_deg, timeout_ms, {.minSpeed = 0, .earlyExitRange = 0});
}
static void cal_log(const char* move_type, const char* profile, double cap_frac,
                   double magnitude, double final_err, int settle_ms) {
  printf("{\"move_type\":\"%s\",\"profile\":\"%s\",\"cap_frac\":%.2f,",
         move_type, profile, cap_frac);
  if (std::strcmp(move_type, "drive") == 0) {
    printf("\"distance_in\":%.2f,", magnitude);
  } else {
    printf("\"angle_deg\":%.2f,", magnitude);
  }
  printf("\"final_err\":%.3f,\"settle_ms\":%d}\n", final_err, settle_ms);
}

void run_calibration_tests() {
  const char* profiles[] = {"precise", "normal", "fast"};
  const double caps[] = {0.50, 0.75, 1.00};
  const double drive_in[] = {6.00, 24.00, 48.00};
  const double turn_deg[] = {15.00, 45.00, 90.00};
  const int repeats = 6;
  const double drive_settle_err = 1.0;
  const double turn_settle_err = 1.0;
  const int settle_hold_ms = 120;
  cal_drive_settle_err = drive_settle_err;
  cal_turn_settle_err = turn_settle_err;
  cal_drive_settle_time_ms = settle_hold_ms;
  cal_turn_settle_time_ms = settle_hold_ms;
  const int profile_count = sizeof(profiles) / sizeof(profiles[0]);
  const int cap_count = sizeof(caps) / sizeof(caps[0]);
  const int drive_count = sizeof(drive_in) / sizeof(drive_in[0]);
  const int turn_count = sizeof(turn_deg) / sizeof(turn_deg[0]);

  for (int p = 0; p < profile_count; ++p) {
    cal_set_profile(profiles[p]);
    for (int c = 0; c < cap_count; ++c) {
      const double cap_frac = caps[c];
      const double cap_v = cap_frac * 12.0;
      for (int r = 0; r < repeats; ++r) {
        for (int i = 0; i < drive_count; ++i) {
          const double dist = drive_in[i];
          cal_set_drive_cap(cap_v);
          const int t0 = pros::millis();
          cal_drive_to(dist, cap_frac);
          const double tx = cal_last_target_x;
          const double ty = cal_last_target_y;
          const int settle_ms = cal_measure_settle_ms_drive(tx, ty, t0, drive_settle_err, settle_hold_ms, cal_last_timeout_ms + 1000);
          const double err = cal_drive_error_in(tx, ty);
          cal_log("drive", profiles[p], cap_frac, dist, err, settle_ms);
          pros::delay(120);
        }
        for (int i = 0; i < turn_count; ++i) {
          const double ang = turn_deg[i];
          if (CAL_HAS_SETPOS) {
            cal_set_pose(0.0, 0.0, 0.0);
          }
          cal_set_turn_cap(cap_v);
          const int t0 = pros::millis();
          cal_turn_to(ang, cap_frac);
          const double th = cal_last_target_heading;
          const int settle_ms = cal_measure_settle_ms_turn(th, t0, turn_settle_err, settle_hold_ms, cal_last_timeout_ms + 1000);
          const double err = cal_turn_error_deg(th);
          cal_log("turn", profiles[p], cap_frac, ang, err, settle_ms);
          pros::delay(120);
        }
      }
    }
  }
}

void run_calib_auto() {
  run_calibration_tests();
}
