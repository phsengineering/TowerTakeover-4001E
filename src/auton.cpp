/*

Hello Gabe,

Today I attempted to do auton and made some progress. Right now it drives forward while intaking, picks up 5 cubes then drives back and hits the wall.
It's only using autoDrive(number of milliseconds) to move forward and back so right now it's an open loop system with no encoder read-outs or detection of anything.

This is obviously going to have to change in order to have a fully robust auton. Ethan said I should try the Okapi Library because it helps to make the bot
perform turns in degrees and other closed loop functions. I tried the turning and drive forward [certain distance and angle] but the bot just spun forever and
tried to fix but couldn't get it to work by end of club.

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

void driveEncoderInches (int inches, int speed) {
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

void turnEncoderTicks (double ticks, int speed) {

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

void autonhandler() {

//  turnEncoderTicks(2.5, 75);  //turn using encoder values testing


//driveEncoderInches(-10, 200);
//pros::delay(1000);
//driveEncoderInches(10, 200);

    trayHandler(120); //flip out
    pros::delay(500);
    trayHandler(0);

    intakeHandler(170); //start intake
    autoDrive(200); // drive to pick up cubes
    pros::delay(3350);

    autoDrive(0); //stop for a little
    pros::delay(200);
    intakeHandler(0); //stop intake

    autoDrive(-200); //backwards drive
    pros::delay(3750);
    autoDrive(0); //stop

    turnEncoderTicks(2.5, 75);  //turn using encoder values

    autoDrive(100); // drive forward to stacking area
    pros::delay(2000);
    autoDrive(0); //stop drive

    trayHandler(130); // deploy lift to stack cubes
    pros::delay(2000);
    trayHandler(-120); //retract lift while moving backwards
    autoDrive(-100);

    pros::delay(500);
    trayHandler(0); //stop lift

    pros::delay(2000);
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
