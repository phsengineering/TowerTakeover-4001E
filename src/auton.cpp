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

auto profileController = AsyncControllerFactory::motionProfile(
  2.5,  // Maximum linear velocity of the Chassis in m/s
  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
  myChassis // Chassis Controller
);

void autonhandler() { // auton main
//Normal Flipout
  intakeHandler(-200);
  trayHandler(120);

  tray.move_absolute(750, 100);
  delay(100);
  lift.move_absolute(675, -100);

  pros::delay(700);
  intakeHandler(0);
  pros::delay(600);
  trayHandler(-150);
  liftHandler(-130);
  pros::delay(750);
  trayHandler(0);
//Normal Flipout



//2 Movement Flipout
/*
intakeHandler(-200);

tray.move_absolute(800, 100);

lift.move_absolute(200, -80);
pros::delay(500);
lift.move_absolute(0, 100);
pros::delay(500);
lift.move_absolute(500, -80);
pros::delay(1000);
lift.move_absolute(0, -80);
pros::delay(500);
lift.move_absolute(0, -80);
tray.move_absolute(0, 100);

pros::delay(10);
intakeHandler(140);
*/
//2 Movement Flipout





//  myChassis.setMaxVelocity(200);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(200);

  myChassis.moveDistance(1.73_in);
  myChassis.waitUntilSettled();

  liftHandler(0);

  /*
  // Path Testing
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{0.139166_ft, 0.139166_ft, 0_deg}}, "A");
  profileController.setTarget("A");
  profileController.waitUntilSettled();
  */

  pros::delay(1000);
  intakeHandler(0);
  myChassis.moveDistance(-1.56_in);
  myChassis.waitUntilSettled();
  myChassis.stop();
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
  pros::delay(500);

  myChassis.turnAngle(20.9_deg); //   21.2_deg
  myChassis.waitUntilSettled();
  myChassis.stop();

  autoDrive(150); // drive forward to stacking area
  intakeHandler(-35);
  pros::delay(1000);

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
}
