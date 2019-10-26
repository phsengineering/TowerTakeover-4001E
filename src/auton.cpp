#include "main.h"
#include "subsystems.hpp"
void autonhandler() {
  autoDrive(-200);
  pros::delay(3000);
  autoDrive(0);
  pros::delay(100);
  autoDrive(200);
  pros::delay(1000);
  autoDrive(0);
  lift.move_velocity(80);
  pros::delay(500);
  lift.move_velocity(0);
}
