#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

auto myChassis = ChassisControllerFactory::create(
  {19, 20}, // Left motors
  {15, 16},   // Right motors
  AbstractMotor::gearset::green, // Torque gearset
  {3.25_in, 8_in} //wheels, wheelbase width
);

void autonhandler() { // auton main

  pros::delay(100);
  intakeHandler(200); //start intake
  myChassis.moveDistance(1.65_in);
  myChassis.waitUntilSettled();
  pros::delay(1000);
  intakeHandler(0);
  myChassis.moveDistance(-1.5_in);
  myChassis.waitUntilSettled();
  myChassis.stop();
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
  pros::delay(400);

  myChassis.setMaxVelocity(100);
  myChassis.turnAngle(21_deg);
  myChassis.waitUntilSettled();
  myChassis.stop();

  autoDrive(150); // drive forward to stacking area
  intakeHandler(-35);
  pros::delay(1100);
  autoDrive(0); //stop drive

  trayHandler(210); // deploy tray to stack cubes
  pros::delay(450);
  intakeHandler(-30);
  pros::delay(1000);
  autoDrive(-50);
  intakeHandler(-50);
  pros::delay(700);
  trayHandler(-70);

  trayHandler(0); //stop lift
  autoDrive(-200);
  pros::delay(250);
  intakeHandler(0);

  pros::delay(1500);
  autoDrive(0); // stop all & win auton
}









void driveEncoderTicks (int ticks, int speed) { //drive in ticks

  while (driveRF.get_position() < ticks) {
    driveRB.move_velocity(speed);
    driveRF.move_velocity(speed);
    driveLB.move_velocity(speed);
    driveLF.move_velocity(speed);
  }

  driveRF.move_velocity(0);
  driveRB.move_velocity(0);
  driveLB.move_velocity(0);
  driveLF.move_velocity(0);
}

void driveRightTest (double ticks, int speed) { //drive in ticks

  while (driveRF.get_position() < ticks) {
    driveRB.move_velocity(speed);
    driveRF.move_velocity(speed);
    driveLB.move_velocity(-speed/4);
    driveLF.move_velocity(-speed/4);
  }

  driveRF.move_velocity(0);
  driveRB.move_velocity(0);
  driveLB.move_velocity(0);
  driveLF.move_velocity(0);
}

void driveEncoderInches (int inches, int speed) { // drive in inches?
  int ticks = inches*88;
  int highTolerance = ticks + 5;
  int lowTolerance = ticks - 5;

  while (driveRF.get_position() < ticks) {
    driveRB.move_velocity(speed);
    driveRF.move_velocity(speed);
    driveLB.move_velocity(speed);
    driveLF.move_velocity(speed);
  }

  driveRF.move_velocity(0);
  driveRB.move_velocity(0);
  driveLB.move_velocity(0);
  driveLF.move_velocity(0);
}

void turnEncoderTicks (double ticks, int speed) { //turn in ticks

  while(driveRF.get_position() < ticks) {
    driveLF.move_velocity(-speed);
    driveLB.move_velocity(-speed);
    driveRB.move_velocity(speed);
    driveRF.move_velocity(speed);
  }
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}

void turnEncoderTicksRed (double ticks, int speed) { //turn in ticks

  while(driveLF.get_position() < ticks) {
    driveLF.move_velocity(speed);
    driveLB.move_velocity(speed);
    driveRB.move_velocity(-speed);
    driveRF.move_velocity(-speed);
  }
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}

void autoDriveSlightLeft (int speed, double offset) { //auto drive but turns slightly to the left
  double faster = offset * speed;
  driveLF.move_velocity(speed);
  driveLB.move_velocity(speed);
  driveRF.move_velocity(faster);
  driveRB.move_velocity(faster);
}

void autoDriveSlightRight (int speed, double offset) { //auto drive but turns slightly to the left
  double faster = offset * speed;
  driveLF.move_velocity(faster);
  driveLB.move_velocity(faster);
  driveRF.move_velocity(speed);
  driveRB.move_velocity(speed);
}
