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
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears


hope this helps,
luke
*/

#include "main.h"
#include "subsystems.hpp"

#include "okapi/api.hpp"

using namespace okapi;

const int DRIVE_MOTOR_RIGHT = 20; // need to figure out how to assign 2 motors to right and left
const int DRIVE_MOTOR_LEFT = 16;

const auto WHEEL_DIAMETER = 3.25_in;
const auto CHASSIS_WIDTH = 15_in;

auto chassis = ChassisControllerFactory::create(DRIVE_MOTOR_LEFT, DRIVE_MOTOR_RIGHT);

void autonhandler() {

  liftHandler(120); //flip out
  pros::delay(500);
  liftHandler(0);

    intakeHandler(180); //start intake
    autoDrive(200); // drive to pick up cubes
    pros::delay(3350);

    autoDrive(0); //stop for a little
    pros::delay(200);
    intakeHandler(0); //stop intake

    autoDrive(-200); //backwards drive
    pros:delay(3750);
    autoDrive(0); //stop

}
