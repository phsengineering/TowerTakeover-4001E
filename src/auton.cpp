#include "okapi/api.hpp"
using namespace okapi;

//const int[] DRIVE_MOTOR_LEFT = [3, 4];
//const int[] DRIVE_MOTOR_RIGHT = [1, 2];
const auto WHEEL_DIAMETER = 3.25_in;
const auto CHASSIS_WIDTH = 13.25_in;
auto chassis = ChassisControllerFactory::create(
  {3, 4}, {1, 2},
  AbstractMotor::gearset::red,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);


void autonhandler() {
  chassis.moveDistance(1000)
}
