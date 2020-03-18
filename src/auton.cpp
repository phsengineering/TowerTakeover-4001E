#include "main.h"
#include "subsystems.hpp"
using namespace okapi;
std::shared_ptr<okapi::OdomChassisController> chassis = ChassisControllerBuilder()
.withMotors({-15, -16}, {19, 20}) // pass motors to odomchassiscontroller builder
.withGains(
         { 0.0017, 0.0000, 0.00025 }, // Distance controller gains
         { 0.000, 0.0000, 0.0000 }, // Turn controller gains
         { 0.0001, 0.000, 0.0000 }  // Angle controller gains
     )
.withDimensions(AbstractMotor::gearset::green, {{3.25_in, 10.5_in}, imev5GreenTPR}) //pass chassis dimensions. 2.75" tracking wheels, 4.25" distance and 4.375" b/w mid and middle wheel
.withOdometry() // use the same scales as the chassis (above)
.withLogger(std::make_shared<Logger>(
    TimeUtilFactory::createDefault().getTimer(),
    "/ser/sout", // Output to the PROS terminal
    Logger::LogLevel::debug // Show all feedback
))
.withMaxVelocity(100) //cap velocity at 300 to reduce jerk and cut down on PID correction time
.buildOdometry(); // build an odometry chassis

void pidtest(){
  chassis->moveDistance(-16.25_in);
}

void autonhandler(int auton) { //check global integer auton
   switch(auton) {
      case 0:
        pidtest(); //testing auton

   }
}
