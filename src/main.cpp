#include "main.h"
#include "subsystems.hpp"

using namespace pros;

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}

void competition_initialize() {}

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
