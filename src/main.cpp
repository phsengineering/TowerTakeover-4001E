#include "main.h"
#include "subsystems.hpp"
#include <sstream>
using namespace pros;
void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autonhandler();
}

 void opcontrol() {
	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
	pros::lcd::initialize();
	lift.set_brake_mode(MOTOR_BRAKE_HOLD);
	tray.set_brake_mode(MOTOR_BRAKE_COAST);
	while(true) {
		//Drive

		/*
		std::cout << "RF Motor Position: " << driveRF.get_position();
		std::cout << "LF Motor Position: " << driveLF.get_position();
		std::cout << "RB Motor Position: " << driveRB.get_position();
		std::cout << "LB Motor Position: " << driveLB.get_position();
		*/
printf("Left encoder front: %d\n", driveLF.get_position());
		int y = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
		int r = mainController.get_analog(E_CONTROLLER_ANALOG_LEFT_X);

		//Make r half as sensitive if not going forward or backward
		if(std::abs(y) < 16)
		{
			r = 127.0 * std::copysign(std::pow(std::abs(r / 127.0), 1.4 ), r);
		}
		drive(y, r);
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			intakeHandler(195);
		}
		else if (mainController.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			intakeHandler(-110);
		}
		else {
			intakeHandler(0);
		}

//TRAY MACROS--------------------------------
	if(mainController.get_digital(DIGITAL_L1)){ //mid tower
		tray.move_absolute(750, 100);
		delay(100);
		lift.move_absolute(575, -80);
	}

	if(mainController.get_digital(DIGITAL_L2)){ //low tower
		tray.move_absolute(800, 100);
		delay(100);
		lift.move_absolute(400, -80);
	}

	if(mainController.get_digital(DIGITAL_A)){ //resting position
		tray.move_absolute(0, -100);
		lift.move_absolute(0, -80);
	}

	if (mainController.get_digital(DIGITAL_Y)) {
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
		pros::delay(500);

		tray.move_absolute(0, -100);
		lift.move_absolute(0, -80);
		intakeHandler(0);
	}

	/*
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			lift.set_brake_mode(MOTOR_BRAKE_HOLD);
			liftHandler(130);

		}
		else if(mainController.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			liftHandler(-130);
		} else if (mainController.get_digital(E_CONTROLLER_DIGITAL_L1)) {

		}
		else {
			liftHandler(0);
		}
*/

		int trayPos = mainController.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		trayHandler(trayPos);
		if(mainController.get_digital(E_CONTROLLER_DIGITAL_X)) { // lift cube macro (yes it's time based, i know, it sucks)
			liftHandler(130);
			pros::delay(500);
			trayHandler(130);
			pros::delay(1000);
			trayHandler(0);
			liftHandler(0);
			lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		} else if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
			// macro down
		}
	}
 }
