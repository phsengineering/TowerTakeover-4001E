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
  const int autoCount = 10;
  const char* autoNames[autoCount] = {
    "Auton test",
    "RED protecc",
    "BLUE protecc",
    "RED Back",
    "BLUE Back",
    "RED 5",
		"BLUE 5",
		"progskill",
    "RED back 6",
    "BLUE back 6"
  };

  lcd::set_text(0, "Select an Auton");
  lcd::print(2, "%s", autoNames[auton]);

  while(1){
    if(choose.get_new_press()) {
      auton++;
      if(auton == autoCount)
        auton = 0;

      lcd::print(2, "%s", autoNames[auton]);
			lcd::print(3, "%d", auton);
    }

    delay(50);
  }
}

void autonomous() {
	autonhandler(auton);
}
void opcontrol() {
autonhandler(0);
}
