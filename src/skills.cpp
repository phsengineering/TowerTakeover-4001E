#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"
#include "auton.cpp"

using namespace okapi;

void skills(int run) { // auton main

  intakeHandler(-200);

 tray.move_absolute(750, 100);
 lift.move_absolute(200, 200);

 pros::delay(700);
 pros::delay(500);
 liftHandler(-200);
  trayHandler(-150);
  pros::delay(50);
  intakeHandler(100);
  pros::delay(700);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(300);
  trayHandler(0);
  liftHandler(0);

myChassis.setMaxVelocity(325);



  pros::delay(100);
  intakeHandler(300); //start intake
  myChassis.moveDistance(1.69_in);
  myChassis.waitUntilSettled();
  pros::delay(500);
  intakeHandler(0);
  pros::delay(500);
  myChassis.moveDistance(-1.5_in);
  myChassis.waitUntilSettled();
  myChassis.stop();
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
  pros::delay(1000);

  myChassis.setMaxVelocity(120);
  myChassis.turnAngle(21.1_deg);
  myChassis.waitUntilSettled();
  myChassis.stop();


  autoDrive(150); // drive forward to stacking area
  intakeHandler(-7);
  pros::delay(2000);
  autoDrive(0); //stop drive

  trayHandler(175); // deploy tray to stack cubes
  intakeHandler(-20);
  liftHandler(-200);
  pros::delay(1850);
  autoDrive(-150);
  pros::delay(700);
  trayHandler(-200);

  myChassis.moveDistance(-1.5_in); // drive backwards from stacking area
  myChassis.waitUntilSettled();
  myChassis.stop();
  liftHandler(0);
  liftHandler(0);

  pros::delay(1000);

  myChassis.setMaxVelocity(120); // turn towards red side to get cube
  myChassis.turnAngle(-21.1_deg);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  myChassis.moveDistance(1.7_in); // drive forward and intake cube
  intakeHandler(100);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(500);

  intakeHandler(0);
  tray.move_absolute(750, 80); // tray macro for mid tower
  delay(100);
  lift.move_absolute(300, -80);

  pros::delay(1000);

  intakeHandler(-100); // get cube in tower by de-intaking

  myChassis.moveDistance(-2_in); // drive backwards from tower into wall to align
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  myChassis.moveDistance(0.8_in); // move forwards from wall
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  myChassis.setMaxVelocity(120); // turn turn towards protected area to get tower
  myChassis.turnAngle(19_deg);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

  myChassis.moveDistance(0.8_in); // move forward to tower
  intakeHandler(100);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(500);

  intakeHandler(0);
  tray.move_absolute(800, 80); // macro for lower tower
  delay(100);
  lift.move_absolute(215, -80);

  pros::delay(1000);

  intakeHandler(-100); // score cube in tower by de-intaking

  pros::delay(1000);
  autoDrive(-200); // drive backwards to get away from tower
  pros::delay(2000);
  autoDrive(0);

}
