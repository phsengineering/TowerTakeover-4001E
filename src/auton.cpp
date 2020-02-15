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
   2.0,  // Maximum li..0;p6-9,.near acceleration of the Chassis in m/s/s
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
  myChassis // Chassis Controller
);


/*
0 -> front blue (3 cube)
1 -> front red (3 cube)
2 -> back blue (5 cube)
3 -> back red (5 cube)
4 -> back blue (6 cube)
5 -> back red (6 cube)
6 -> prog skills
*/

void autonhandler(int autonomousPreSet) { // auton main


  if (autonomousPreSet == 0 || autonomousPreSet == 1) { // front blue & red

    intakeHandler(-200);

    tray.move_absolute(750, 100);
    lift.move_absolute(200, 200);

    pros::delay(700);
    pros::delay(500);
    liftHandler(-200);
    trayHandler(-150);
    pros::delay(50);
    intakeHandler(95);
    pros::delay(700);

    autoDrive(-200);
    pros::delay(500);
    intakeHandler(150);
    trayHandler(0);
    liftHandler(0);
    pros::delay(300);
    autoDrive(0);
    pros::delay(200);

    myChassis.setMaxVelocity(300);

    myChassis.moveDistance(1.51_in);
    myChassis.waitUntilSettled();

    pros::delay(200);
    intakeHandler(0);
    autoDrive(0);

    myChassis.setMaxVelocity(250);

    if (autonomousPreSet == 1) { // front red
      myChassis.turnAngle(18.5_deg);
    } else { // front blue
      myChassis.turnAngle(-18.5_deg);
    }
    myChassis.waitUntilSettled();
    pros::delay(500);
    intakeHandler(95);

    myChassis.setMaxVelocity(300);

    myChassis.moveDistance(1.55_in);
    myChassis.waitUntilSettled();

    pros::delay(500);
    autoDrive(0);
    intakeHandler(0);

    pros::delay(500);

    myChassis.setMaxVelocity(150);

    if (autonomousPreSet == 1) {  //front red
      myChassis.turnAngle(17);
    } else { // front blue
      myChassis.turnAngle(-17);
    }

    autoDrive(0);

    pros::delay(500);

    autoDrive(150);
    intakeHandler(-45);
    pros::delay(750);

    autoDrive(0); //stop drive
    intakeHandler(0);

    pros::delay(1000);
    autoDrive(0);
    intakeHandler(-30);
    pros::delay(500);



    trayHandler(210); // deploy tray to stack cubes
    pros::delay(400);
    intakeHandler(-50);
    pros::delay(350);
    intakeHandler(-250);
    pros::delay(500);
    autoDrive(-100);
    pros::delay(500);
    intakeHandler(-200);
    trayHandler(-200);
    pros::delay(700);

    autoDrive(-200);

    tray.move_absolute(0, -100);
    lift.move_absolute(0, -80);
    pros::delay(2000);

    autoDrive(0); // stop all & win auton

  }



  if (autonomousPreSet == 2 || autonomousPreSet == 3) { // back blue & red (5 cube)
    intakeHandler(-200);

tray.move_absolute(750, 100);
lift.move_absolute(200, 200);

pros::delay(700);
pros::delay(500);
liftHandler(-200);
trayHandler(-150);
pros::delay(50);
intakeHandler(95);
pros::delay(700);

autoDrive(-200);
pros::delay(500);
intakeHandler(150);
trayHandler(0);
liftHandler(0);


myChassis.moveDistance(1.67_in);
myChassis.waitUntilSettled();

if (autonomousPreSet == 2) { // back blue
pros::delay(200);
intakeHandler(75);
pros::delay(600);
} else {  // back red
pros::delay(200);
intakeHandler(75);
pros::delay(600);
}

intakeHandler(0);
myChassis.moveDistance(-1.53_in); //-1.55
myChassis.waitUntilSettled();
myChassis.stop();
driveLF.move_velocity(0);
driveLB.move_velocity(0);
driveRB.move_velocity(0);
driveRF.move_velocity(0);
intakeHandler(0);
pros::delay(400);

if (autonomousPreSet == 2) { // back blue
myChassis.turnAngle(20.85_deg); //   21.2_deg
} else { // back red
myChassis.turnAngle(-20.59_deg); //   21.2_deg
}
myChassis.waitUntilSettled();
myChassis.stop();

autoDrive(150); // drive forward to stacking area
intakeHandler(-25);
pros::delay(1450);

autoDrive(250); // jerk forward to better stack cubes
pros::delay(100);
autoDrive(0); //stop drive

trayHandler(210); // deploy tray to stack cubes
pros::delay(400);
intakeHandler(-65);
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

  }


if (autonomousPreSet == 4 || autonomousPreSet == 5) { // back blue & red (6 cube)
  intakeHandler(-200);

  tray.move_absolute(750, 100);
  lift.move_absolute(200, 200);

  pros::delay(700);
  pros::delay(500);
  liftHandler(-200);
  trayHandler(-150);
  pros::delay(50);
  intakeHandler(95);
  pros::delay(700);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(150);
  trayHandler(0);
  liftHandler(0);


  myChassis.moveDistance(1.67_in);
  myChassis.waitUntilSettled();

  intakeHandler(0);

  myChassis.resetSensors();
  pros::delay(300);


  if (autonomousPreSet == 4) { // back blue
  myChassis.turnAngle(-3.9_deg);
} else { // back red
  myChassis.turnAngle(3.9_deg);
  }
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(300);

  myChassis.moveDistance(1.48_in);
  myChassis.waitUntilSettled();

  intakeHandler(200);
  pros::delay(750);
  intakeHandler(0);

  pros::delay(200);
  myChassis.resetSensors();



  intakeHandler(0);

  pros::delay(350);

  if (autonomousPreSet == 4) { // back blue
  myChassis.turnAngle(-21.22_deg);
} else { // back red
  myChassis.turnAngle(21.22_deg);
  }
  myChassis.waitUntilSettled();
  myChassis.stop();

  myChassis.resetSensors();

  autoDrive(400);
  intakeHandler(-20);
  pros::delay(1500);

  autoDrive(250);
  pros::delay(100);
  autoDrive(0);

  trayHandler(210);
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
  autoDrive(0);

}



if (autonomousPreSet == 6 || autonomousPreSet == 7) { //skilzz


  intakeHandler(-200);

tray.move_absolute(750, 100);
lift.move_absolute(200, 200);

pros::delay(700);
pros::delay(500);
liftHandler(-200);
trayHandler(-150);
pros::delay(50);
intakeHandler(95);
pros::delay(700);

autoDrive(-200);
pros::delay(500);
intakeHandler(150);
trayHandler(0);
liftHandler(0);


myChassis.moveDistance(1.67_in);
myChassis.waitUntilSettled();

if (autonomousPreSet == 6) { // back blue
pros::delay(150);
intakeHandler(0);
pros::delay(850);
} else {  // back red
pros::delay(400);
intakeHandler(0);
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

if (autonomousPreSet == 6) { // back blue
myChassis.turnAngle(20.85_deg); //   21.2_deg
} else {
myChassis.turnAngle(-20.6_deg); //   21.2_deg
}
myChassis.waitUntilSettled();
myChassis.stop();

autoDrive(150); // drive forward to stacking area
intakeHandler(-20);
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




  myChassis.resetSensors();
  myChassis.moveDistance(-1_in); // drive backwards from stacking area
  myChassis.waitUntilSettled();
  myChassis.stop();
  liftHandler(0);
   trayHandler(-150);

  pros::delay(1000);

    myChassis.resetSensors();
  myChassis.setMaxVelocity(120);
  myChassis.turnAngle(16_deg);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

    myChassis.resetSensors();
  lift.move_absolute(300, -80);
  tray.move_absolute(-5, -80);
  autoDrive(350);
  pros::delay(2000);


  // working above ^^

  autoDrive(0);
  pros::delay(500);
    myChassis.resetSensors();

  myChassis.setMaxVelocity(325);
  lift.move_absolute(-110, -100);
  myChassis.moveDistance(-1.2_in); // drive backwards from stacking area
  myChassis.waitUntilSettled();
  myChassis.stop();


  myChassis.resetSensors();

  myChassis.setMaxVelocity(120); // turn towards red side to get cube
  intakeHandler(0);
  myChassis.turnAngle(21.3_deg);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1000);

    myChassis.resetSensors();

  myChassis.setMaxVelocity(325);
  myChassis.moveDistance(1.5_in); // drive forward and intake cube
  intakeHandler(100);
  myChassis.waitUntilSettled();
  myChassis.stop();

  pros::delay(1500);

  intakeHandler(0);
    myChassis.resetSensors();
  lift.move_absolute(300, -80);

  pros::delay(1000);

  intakeHandler(-100); // get cube in tower by de-intaking

}

}
