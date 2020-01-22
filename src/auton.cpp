#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

int frontBlue = 0;
int frontRed = 0;
int backBlue = 1;
int backRed = 0;

auto myChassis = ChassisControllerFactory::create(
  {19, 20}, // Left motors
  {15, 16},   // Right motors
  AbstractMotor::gearset::green, // Torque gearset
  {3.25_in, 8_in} //wheels, wheelbase width
);

auto profileController = AsyncControllerFactory::motionProfile(
  2.5,  // Maximum linear velocity of the Chassis in m/s
  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
  myChassis // Chassis Controller
);


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

void autonhandler() { // auton main

  if (backBlue == 1 || backRed == 1) {

  //Back Auton
  intakeHandler(-200);
  trayHandler(120);

  tray.move_absolute(750, 100);
  delay(100);
  lift.move_absolute(600, -100);

  pros::delay(700);
  intakeHandler(0);
  pros::delay(600);
  liftHandler(-130);
  pros::delay(750);
  trayHandler(-150);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(175);
  trayHandler(0);

  myChassis.moveDistance(1.69_in);
  myChassis.waitUntilSettled();

  liftHandler(0);

  pros::delay(200);
  intakeHandler(0);
  pros::delay(800);
  myChassis.moveDistance(-1.55_in);
  myChassis.waitUntilSettled();
  myChassis.stop();
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
  pros::delay(400);


  if (backBlue == 1) {
  myChassis.turnAngle(20.9_deg); //   21.2_deg
  } else {
  myChassis.turnAngle(-20.9_deg); //   21.2_deg
  }
  myChassis.waitUntilSettled();
  myChassis.stop();

  autoDrive(150); // drive forward to stacking area
  intakeHandler(-35);
  pros::delay(1150);

  autoDrive(250); // jerk forward to better stack cubes
  pros::delay(100);
  autoDrive(0); //stop drive

  trayHandler(210); // deploy tray to stack cubes
  pros::delay(400);
  intakeHandler(-50);
  pros::delay(1000);
  autoDrive(-60);
  intakeHandler(-65);
  pros::delay(700);
  trayHandler(-70);

  trayHandler(0); //stop lift
  autoDrive(-200);
  pros::delay(250);
  intakeHandler(0);

  pros::delay(1500);
  autoDrive(0); // stop all & win auton
  } else {

  //Font Auton
  intakeHandler(-200);
  trayHandler(120);

  tray.move_absolute(750, 100);
  delay(100);
  lift.move_absolute(600, -100);

  pros::delay(700);
  intakeHandler(0);
  pros::delay(600);
  liftHandler(-130);
  pros::delay(750);
  trayHandler(-150);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(200);
  trayHandler(0);

  autoDrive(0);
  pros::delay(1000);

  if (frontRed == 1) {
  autoDriveSlightLeft(120, 1.9);
  } else {
  autoDriveSlightRight(120, 1.9);
  }

  pros::delay(2000);
  intakeHandler(0);
  autoDrive(0);

  myChassis.turnAngle(21.25);
  pros::delay(1000);
  autoDrive(150);
  intakeHandler(-25);
  pros::delay(1500);

  autoDrive(0); //stop drive

  trayHandler(210); // deploy tray to stack cubes
  pros::delay(400);
  intakeHandler(-50);
  pros::delay(1000);
  autoDrive(-60);
  intakeHandler(-65);
  pros::delay(700);
  trayHandler(-70);

  trayHandler(0); //stop lift
  autoDrive(-200);
  pros::delay(250);
  intakeHandler(0);

  autoDrive(-250);

  tray.move_absolute(0, -100);
  lift.move_absolute(0, -80);
  pros::delay(2000);

  autoDrive(0); // stop all & win auton
  }
}
