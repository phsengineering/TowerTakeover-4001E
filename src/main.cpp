#include "main.h"
#include "subsystems.hpp"
#include <sstream>
using namespace pros;

  pros::ADIDigitalIn limit('H');

int autonomousPreSet = 0;
int state = 0;

int ledState = 1;
int buttonState;             // the current reading from the input pin
int lastButtonState = 0;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


void initialize() {
  delay(200);
	pros::lcd::initialize();
}

void disabled() {}


//autonomousPreSet++;

void competition_initialize() {

  while (1 == 1) {

    if(limit.get_value() == 1) {
        autonomousPreSet++;

        if (autonomousPreSet == 8) {
          autonomousPreSet = 0;
        } else {
         std::string autons[8] = {"front blue (3 cube)", "front red (3 cube)", "back blue (5 cube)", "back red (5 cube)", "back blue (6 cube)", "back red (6 cube)", "blue back prog skills", "red back prog skills"};
         std::cout << autons[0];

         for (int i = 0; i < 10; i++) {
          lcd::print(i, "%s", autons[autonomousPreSet]);
         }
      }


    }
        pros::delay(200);

   }

}

void autonomous() {
	autonhandler(autonomousPreSet);
}

 void opcontrol() {

	pros::Controller mainController = Controller(E_CONTROLLER_MASTER);
	pros::lcd::initialize();
	lift.set_brake_mode(MOTOR_BRAKE_COAST);
  lift.move_absolute(-10,-100);
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
		} else if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
      intakeHandler(-200);
    } else if(mainController.get_digital(E_CONTROLLER_DIGITAL_UP)) {
      liftHandler(50);
      pros::delay(100);
      liftHandler(0);
    } else if (mainController.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
      liftHandler(-50);
      pros::delay(100);
      liftHandler(0);
    }
		else {
			intakeHandler(0);
		}

//Lift MACROS--------------------------------
	if(mainController.get_digital(DIGITAL_L1)){ //mid tower
    lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
		tray.move_absolute(750, 80);
		delay(100);
		lift.move_absolute(300, -80);
	}

	if(mainController.get_digital(DIGITAL_L2)){ //low tower
    lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
		tray.move_absolute(815, 80);
		delay(100);
		lift.move_absolute(230, -80);
    delay(100);
    tray.move_absolute(800, 80);
		delay(100);
		lift.move_absolute(215, -80);
	}

	if(mainController.get_digital(DIGITAL_A)){ //resting position
		tray.move_absolute(0, -50);
		lift.move_absolute(-10, -100);
    lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
	}
	if (mainController.get_digital(DIGITAL_Y)) {
    intakeHandler(-200);

   tray.move_absolute(750, 100);
   lift.move_absolute(200, 200);

   pros::delay(700);
   pros::delay(500);
   lift.move_absolute(-10, -100);
   trayHandler(-150);
    pros::delay(500);
    liftHandler(0);
    trayHandler(0);

    lift.set_brake_mode(MOTOR_BRAKE_COAST);
	}
  if (mainController.get_digital(DIGITAL_LEFT)) {
     autonhandler(autonomousPreSet);
  }

  // macro brake brake
  //go home coast
  // macro -5
/*
	if (mainController.get_digital(DIGITAL_LEFT)) {
			tray.move_absolute(800, 100);
	}
	*/


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
		} else if(mainController.get_digital(E_CONTROLLER_DIGITAL_B)) {
			// macro down
		}
	}
 }
