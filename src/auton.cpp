#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;


/*
 autonomous preset:
 0 -> frontBlue
 1 -> frontRed
 2 -> backBlue
 3 -> backRed
*/

int frontBlue = 0;
int frontRed = 0;

int backBlue = 1;
int backRed = 0;
auto myChassis = ChassisControllerBuilder()
    .withMotors({19, 20}, {15, 16}) // pass motors to odomchassiscontroller builder
    .withGains(
         { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
         { 0.0061, 0.00057, 0.000212 }, // Turn controller gains
         { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
     )

    //.withSensors({'E', 'F', true}, {'A', 'B', false}, {'C', 'D', true}) //pass sensors for left, right, middle
    .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 8_in}, imev5GreenTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
    .withLogger(std::make_shared<Logger>(
        TimeUtilFactory::createDefault().getTimer(),
        "/ser/sout", // Output to the PROS terminal
        Logger::LogLevel::debug // Show all feedback
    ))
    //.withMaxVelocity(300) //cap velocity at 300 to reduce jerk and cut down on PID correction time
    .build(); // build an odometry chassis

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

void stopAll () {
  myChassis->stop();
  driveLF.move_velocity(0);
  driveLB.move_velocity(0);
  driveRB.move_velocity(0);
  driveRF.move_velocity(0);
}

int autonomousPreSet = 0;

void autonhandler() { // auton main

  if (autonomousPreSet == 2 || autonomousPreSet == 3) {  //back blue or back red

  //Back Auton
  intakeHandler(-200);
  trayHandler(120);

  tray.move_absolute(750, 100);
  delay(100);
  lift.move_absolute(250, -100);

  pros::delay(700);
  intakeHandler(0);
  pros::delay(600);
  liftHandler(-130);
  pros::delay(750);
  trayHandler(-150);

  autoDrive(-200);
  pros::delay(500);
  intakeHandler(300);
  trayHandler(0);
  liftHandler(0);

  myChassis->setMaxVelocity(375);

  myChassis->moveDistance(1.69_in);
  myChassis->waitUntilSettled();

  pros::delay(400);
  autoDrive(-100);
  intakeHandler(0);
  pros::delay(600);
  autoDrive(0);

  myChassis->setMaxVelocity(190);

if (autonomousPreSet == 2) { // back blue
myChassis->turnAngle(-14.5_deg); //   21.2_deg
} else {
myChassis->turnAngle(14.5_deg); //   21.2_deg
}

myChassis->waitUntilSettled();
stopAll();

pros::delay(200);

  myChassis->setMaxVelocity(375);
  intakeHandler(75);

myChassis->moveDistance(1.1_in); //-1->55
myChassis->waitUntilSettled();
stopAll();
intakeHandler(125);
pros::delay(500);


  myChassis->moveDistance(-1.3_in); //-1->55
  myChassis->waitUntilSettled();
  stopAll();
  intakeHandler(0);
  pros::delay(500);

  myChassis->setMaxVelocity(182);

  if (autonomousPreSet == 2) { // back blue
  myChassis->turnAngle(-20.75_deg); //   21.2_deg
  } else {
  myChassis->turnAngle(20.75_deg); //   21.2_deg
  }
  myChassis->waitUntilSettled();
  myChassis->stop();

  pros::delay(250);

  autoDrive(400); // drive forward to stacking area
  pros::delay(1300);

  autoDrive(200);
  pros::delay(600);
  autoDrive(0);
  intakeHandler(-30);
  pros::delay(250);



  trayHandler(210); // deploy tray to stack cubes
  liftHandler(-200);
  pros::delay(500);
  intakeHandler(-250);
  pros::delay(1250);
  autoDrive(-100);
  intakeHandler(-200);
  trayHandler(-200);
  pros::delay(700);

  autoDrive(-200);
  liftHandler(0);

  pros::delay(1500);
  autoDrive(0); // stop all & win auton
  } else {



  intakeHandler(-200);
  trayHandler(120);

  tray.move_absolute(750, 100);
  delay(100);
 lift.move_absolute(180, -100);

  pros::delay(700);
  intakeHandler(0);
  pros::delay(600);
 liftHandler(-130);
  pros::delay(750);
  trayHandler(-150);



  autoDrive(-200);
  pros::delay(500);
  intakeHandler(95);
  trayHandler(0);

  autoDrive(0);
  pros::delay(500);

  myChassis->setMaxVelocity(300);

  myChassis->moveDistance(1.51_in);
  myChassis->waitUntilSettled();

  pros::delay(200);
  intakeHandler(0);
  autoDrive(0);

    myChassis->setMaxVelocity(250);

    if (autonomousPreSet == 1) {
      myChassis->turnAngle(18.5_deg);
    } else {
      myChassis->turnAngle(-18.5_deg);
    }
  myChassis->waitUntilSettled();
  pros::delay(500);
  intakeHandler(95);

    myChassis->setMaxVelocity(300);

  myChassis->moveDistance(1.55_in);
  myChassis->waitUntilSettled();

  pros::delay(500);
  autoDrive(0);
  intakeHandler(0);

  pros::delay(500);

    myChassis->setMaxVelocity(150);

  if (autonomousPreSet == 1) {
  myChassis->turnAngle(17);
  } else {
  myChassis->turnAngle(-17);
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

}
