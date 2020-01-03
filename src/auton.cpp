/*
Here's a doc on Okapi auton:
https://pros.cs.purdue.edu/v5/okapi/tutorials/walkthrough/autonomous-movement-basic.html

Not specifically related to Okapi but for motor encoders:

1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears This is what we have
300 ticks/rev with 6:1 gears

hope this helps,
luke
*/
#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

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

auto myChassis = ChassisControllerFactory::create(
  {19, 20}, // Left motors
  {15, 16},   // Right motors
  AbstractMotor::gearset::green, // Torque gearset
  {3.25_in, 8_in} //wheels, wheelbase width
);


void autonhandler() { // auton main

//myChassis.turnAngle(20.8_deg);

  pros::delay(100);
  intakeHandler(120); //start intake
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

//driveRightTest(4.9, 175);

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

/*
// 1 cube drive forward/back

  autoDrive(-200);
  pros::delay(1150);
  autoDrive(0);
  pros::delay(100);
  autoDrive(200);
  pros::delay(2000);
  autoDrive(0);
  intakeHandler(-170); //flip out
  trayHandler(120);
  liftHandler(150);
  pros::delay(800);
  trayHandler(-150);
  liftHandler(-150);
  pros::delay(1000);
  liftHandler(-130);
  pros::delay(500);
  intakeHandler(0);

  // 5 cube attempt (Worked once)
    intakeHandler(-170); //flip out
    trayHandler(120);
    liftHandler(150);
    pros::delay(800);
    trayHandler(-150);
    liftHandler(-150);
    pros::delay(1000);
    liftHandler(-130);
    pros::delay(500);

    intakeHandler(140); //start intake

    autoDrive(200);
    pros::delay(1250);
    autoDrive(-200);
    pros::delay(1500);
    autoDrive(0);
    delay(200);

    //autoDriveSlightLeft(200, 1.03); // blue side
    autoDriveSlightRight(200, 1.03);  //red side

    pros::delay(3600);
    liftHandler(0);
    trayHandler(0);
    pros::delay(150);
    intakeHandler(0);

    autoDrive(-200); //backwards drive
    pros::delay(3500);
    autoDrive(0); //stop

    //turnEncoderTicks(5.3, 125);  //blue side
    turnEncoderTicksRed(5, 125); //red side

    autoDrive(150); // drive forward to stacking area
    intakeHandler(-20);
    pros::delay(1500);
    autoDrive(0); //stop drive

    trayHandler(180); // deploy tray to stack cubes
    pros::delay(450);
    intakeHandler(0);
    pros::delay(1700);
    trayHandler(-70); //retract lift while moving backwards

    pros::delay(500);
    trayHandler(0); //stop lift
    autoDrive(-100);

    pros::delay(1000);
    autoDrive(0); // stop all & win auton
*/
}
