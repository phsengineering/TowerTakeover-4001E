/*
Here's a doc on Okapi auton:
https://pros.cs.purdue.edu/v5/okapi/tutorials/walkthrough/autonomous-movement-basic.html

Okapi commands I found:

chassis.moveDistance(2_ft);
chassis.turnAngle(90_deg);


Not specifically related to Okapi but for motor encoders:

1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears This is what we have
300 ticks/rev with 6:1 gears


hope this helps,
luke
*/

#include "main.h"
#include "subsystems.hpp"


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

void autoDriveSlightLeft (int speed, double offset) { //auto drive but turns slightly to the left
  double faster = offset * speed;
  driveLF.move_velocity(speed);
  driveLB.move_velocity(speed);
  driveRF.move_velocity(faster);
  driveRB.move_velocity(faster);
}

void autonhandler() { // auton main

//  turnEncoderTicks(3.5, 125);  //turn using encoder values testing

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
    /*
    autoDriveSlightLeft(200, 1.1); // drive forward to recenter
    pros::delay(1000);
    autoDrive(-200); // drive back into wall
    pros::delay(1000);
    */
    /*

    intakeHandler(140); //start intake
    autoDriveSlightLeft(200, 1.1); // drive forward to recenter
    pros::delay(1000);
    autoDrive(-200); // drive back into wall
    pros::delay(200);
    autoDrive(200);
    pros::delay(200);
    autoDrive(-200);
    pros::delay(1000);

    */

    autoDriveSlightLeft(200, 1.03); // drive to pick up cubes

    pros::delay(3600);
    liftHandler(0);
    trayHandler(0);
    pros::delay(150);
    intakeHandler(0);

    autoDrive(-200); //backwards drive
    pros::delay(3500);
    autoDrive(0); //stop

    turnEncoderTicks(3.3, 125);  //turn using encoder values

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
}



/*  OLD TURNING SYSTEM

  driveRF.move_velocity(200); //use rigt front wheel drive to turn against wall
  driveLB.move_velocity(-200);
  pros::delay(1500);
  driveRF.move_velocity(0); //stop turns
  driveLB.move_velocity(0);

*/

//Before Arjun bestowed his wisdom upon us

/*int highTolerance = ticks + 5;
int lowTolerance = ticks - 5;

driveRF.move_absolute(ticks, speed);

while (!((driveRF.get_position() < highTolerance) && (driveRF.get_position() > lowTolerance))) {
    pros::delay(2);
}

driveRF.tare_position();

*/
