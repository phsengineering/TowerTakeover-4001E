#include "main.h"
#include "subsystems.hpp"
#include <iostream>
#include <string>

using namespace pros;

pros::ADIDigitalIn limit('H');

int current;
int first = 0;

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}

void competition_initialize() {

	std::string autons[8] =
  {
   "Blue Protect [3 Cube]",
   "Red Protect [3 cube]",
   "Blue Unprotected [5 Cube]",
   "Red Unprotected [5 Cube]",
   "Blue Unprotected [6 Cube]",
   "Red Unprotected [6 cube]",
   "Blue Unprotected Programming Skills [20 Point]",
   "Red Unprotected Programming Skills [20 Point]"
  };
  //cout << "Select an Autonomous Program"; // replace with pros lcd print
  while (true) {

		if(limit.get_value() == 1) {
    	if (first == 0) {
				for (int i = 0; i < 10; i++) {
			 	lcd::print(i, "%s", autons[0]);
			}
      	first = 1;
    	} else {
      	current += 1;
      	if (current == 8) {
        	current = 0;
      	}
				for (int i = 0; i < 10; i++) {
				 	lcd::print(i, "%s", autons[current]);
				}
    }
  }
	pros::delay(200);
}


}

void autonomous() {}

void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
	while(true) {

		/////////////Drive//////////////////
		int analogY = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y); // get Y value from left analog stick
		int analogX = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X); // get X value from left analog stick
		if(std::abs(analogY) < 16)
		{
			analogX = 127.0 * std::copysign(std::pow(std::abs(analogX / 127.0), 1.4 ), analogX); // make turning less sensitive than driving forward or backwards
		}
		drive(analogY, analogX); // actual drive with these paramaters
		/////////End of Drive///////////////



		////////////Tray///////////////////
		int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		trayHandler(trayPos);
		///////End of Tray/////////////////



		////////////Intake//////////////////
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			intakeHandler(200);
		} else if (mainController.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			intakeHandler(-110);
		} else if (mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
			intakeHandler(-200);
		}
		////////End of Intake///////////////



		////////////Lift////////////////////
		if(mainController.get_digital(DIGITAL_L1)){ //mid tower
			lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
			lift.move_absolute(300, -80);
		}
		if (mainController.get_digital(DIGITAL_L2)) { //low tower
			lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
			lift.move_absolute(220, -80);
		}
		if (mainController.get_digital(DIGITAL_A)) { //resting position
			lift.set_brake_mode(MOTOR_BRAKE_COAST);
			lift.move_absolute(-10, -100);
		}
		////////////End Of Lift/////////////



		////////////Flipout/////////////////
		if (mainController.get_digital(DIGITAL_Y)) {
    	intakeHandler(-200);
    	tray.move_absolute(750, 100);
    	lift.move_absolute(200, 200);
    	pros::delay(1200);
    	lift.move_absolute(-10, -100);
    	trayHandler(-150);
    	pros::delay(500);
    	liftHandler(0);
    	trayHandler(0);
		}
		///////End of Flipout///////////////


	}
}





Motor rightFrontDrive(19, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor rightBackDrive(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor leftFrontDrive(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor leftBackDrive(16, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(4, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
Motor rightIntake(21, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor leftIntake(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

//Broken ports: 13, 10, 9, 7, 5, 21, 1?, 4?, 2

void drive(int analogY, int analogX) {
  analogY = analogY * (12000 / 127);
  analogX = analogX * (12000 / 127);

  rightFrontDrive.move_voltage(analogY + analogX);
  rightBackDrive.move_voltage(analogY + analogX);
  leftFrontDrive.move_voltage(analogY - analogX);
  leftBackDrive.move_voltage(analogY - analogX);
}

void intakeHandler(int speed) {
  rightIntake.move_velocity(speed);
  leftIntake.move_velocity(speed);
}

void trayHandler(int speed) {
  tray.move_velocity(speed);
}

void liftHandler(int speed) {
  lift.move_velocity(speed);
}

void autoDrive (int speed) {
  rightFrontDrive.move_velocity(speed);
  rightBackDrive.move_velocity(speed);
  leftFrontDrive.move_velocity(speed);
  leftBackDrive.move_velocity(speed);
}
