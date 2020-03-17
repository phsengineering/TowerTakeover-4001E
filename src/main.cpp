#include <sstream>
#include "main.h"
#include "subsystems.hpp"

using namespace pros;
int auton = 0;
void initialize() {
  delay(200);
	pros::lcd::initialize();

}
void competition_initialize(){

}

void autonomous() {

}
void opcontrol() {
autonhandler(0);
}
