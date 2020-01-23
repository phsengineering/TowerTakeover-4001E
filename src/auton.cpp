#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

int frontBlue = 0;
int frontRed = 0;
int backBlue = 0;
int backRed = 1;

auto myChassis = ChassisControllerFactory::create(
  {19, 20}, // Left motors
  {15, 16},   // Right motors
  AbstractMotor::gearset::green, // Torque gearset
  {3.25_in, 8_in} //wheels, wheelbase width
);

auto profileController = AsyncControllerFactory::motionProfile(
  2.5,  // Maximum linear velocity of the Chassis in m/s
   2.0,  // Maximum li..0;p6-9,.near acceleration of the Chassis in m/s/s
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
  lift.move_absolute(650, -100);

  pros::delay(700);
  intakeHandler(0);
  pros::delay(600);
  liftHandler(-130);
  pros::delay(750);
  trayHandler(-150);

  autoDrive(-200);
  pros::delay(750);
  intakeHandler(175);
  trayHandler(0);

  myChassis.moveDistance(1.71_in);
  myChassis.waitUntilSettled();

  if (backBlue == 1) {
  pros::delay(150);
  intakeHandler(10);
  pros::delay(850);
} else {
  pros::delay(400);
  intakeHandler(5);
  pros::delay(600);
}
  myChassis.moveDistance(-1.53_in); //-1.55
  myChassis.waitUntilSettled();
  myChassis.stop();
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
  intakeHandler(0);
  pros::delay(400);

  if (backBlue == 1) {
  myChassis.turnAngle(20.85_deg); //   21.2_deg
  } else {
  myChassis.turnAngle(-20.55_deg); //   21.2_deg
  }
  myChassis.waitUntilSettled();
  myChassis.stop();

  autoDrive(150); // drive forward to stacking area
  intakeHandler(-32);
  pros::delay(1200);

  autoDrive(250); // jerk forward to better stack cubes
  pros::delay(100);
  autoDrive(0); //stop drive

  trayHandler(210); // deploy tray to stack cubes
  pros::delay(400);
  intakeHandler(-55);
  pros::delay(1000);
  autoDrive(-60);
  intakeHandler(-70);
  trayHandler(-200);
  pros::delay(700);

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
  pros::delay(2000);

  if (frontRed == 1) {
  autoDriveSlightLeft(120, 1.9);
  } else {
  autoDriveSlightRight(120, 1.9);
  }

  pros::delay(2000);
  intakeHandler(0);
  autoDrive(0);

  if (frontRed == 1) {
  myChassis.turnAngle(21.25);
  } else {
  myChassis.turnAngle(-21.25);
  }

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
