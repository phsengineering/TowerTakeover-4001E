#include "main.h"
#include "subsystems.hpp"
#include "okapi/api.hpp"

using namespace okapi;

auto myChassis = ChassisControllerBuilder()
    .withMotors({19, 20}, {15, 16}) // pass motors to odomchassiscontroller builder
    .withGains(
         { 0.00345, 0.00002, 0.00009 }, // Distance controller gains
         { 0.0061, 0.00057, 0.000212 }, // Turn controller gains
         { 0.00022, 0.0001, 0.00003 }  // Angle controller gains
     )

    .withDimensions(AbstractMotor::gearset::green, {{3.25_in, 8_in}, imev5GreenTPR})

  .withOdometry()
  .buildOdometry();


void autonHandler () {
  myChassis->moveDistance(10_in);
}
