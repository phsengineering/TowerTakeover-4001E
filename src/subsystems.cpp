#include "subsystems.hpp"
using namespace pros;

//Drivetrain
Motor driveRF(19, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(16, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeL(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(6, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
bool debug = false;


void drive(int y, int r)
{
    //Scale up y and r from 127 to 12000
    y *= 12000.0 / 127.0;
    r *= 12000.0 / 127.0; //double check math

    driveLF.move_voltage(y + r);
    driveLB.move_voltage(y + r);
    driveRF.move_voltage(y - r);
    driveRB.move_voltage(y - r);
}
void intakeHandler(int speed) {
    intakeR.move_velocity(speed);
    intakeL.move_velocity(speed);
}
void trayHandler(int trayPos) {
  tray.move_velocity(trayPos);
}
void liftHandler(int liftInput) {
  lift.move_velocity(liftInput);
}
void autoDrive(int x) {
  driveLB.move_velocity(x);
  driveLF.move_velocity(x);
  driveRB.move_velocity(x);
  driveRF.move_velocity(x);
}
void driveVel(int updateSpeed) {
  driveLF.move_velocity(updateSpeed);
  driveLB.move_velocity(updateSpeed);
  driveRB.move_velocity(updateSpeed);
  driveRF.move_velocity(updateSpeed);
}


// void clearDrive() {
//   driveLF.tare_position();
//   driveLB.tare_position();
//   driveRB.tare_position();
//   driveRF.tare_position();
// }
// double obtainPositionF() {
//   double left = lEncoder.get_value();
//   double right = rEncoder.get_value();
//   return ((left+right)/2);
// }
// void smartDrive(int speed, double fPoint) { //PROPERTY OF 4001A
//   clearDrive();
//   if(speed > 0) {
//     int updateSpeed = 0;
//     clearDrive();
//     while(obtainPositionF() < fPoint/2.0) {
//       if(debug) {
//         printf("1 update speed: %f\n", updateSpeed);
//       }
//       if(driveLB.get_actual_velocity() < 0 || driveRB.get_actual_velocity() < 0) {
//         driveVel(0);
//       }
//       if(updateSpeed < speed) {
//         updateSpeed+=30;
//       }
//       intakeHandler(190);
//       if(debug) {
//         printf("Obtain position: %d\n", obtainPositionF());
//       }
//       driveVel(updateSpeed);
//       pros::delay(75);
//     }
//     while(obtainPositionF() < fPoint) {
//       if(debug) {
//         printf("2 update speed: %f\n", updateSpeed);
//       }
//       if(driveLB.get_actual_velocity() < 0 || driveRB.get_actual_velocity() < 0) {
//         driveVel(0);
//       }
//       if(updateSpeed > 0) {
//         updateSpeed-=30;
//       }
//       if(updateSpeed == 0) {
//         break;
//       }
//       driveVel(updateSpeed);
//       puts(std::to_string(updateSpeed).c_str());
//       if(debug) {
//         printf("Obtain position: %d\n", obtainPositionF());
//       }
//       pros::delay(75);
//     }
//     part++;
//     driveVel(0);
//     if(updateSpeed == 0) {
//       intakeHandler(0);
//     }
//   }
//   else {
//     int updateSpeed = 0;
//     while(obtainPositionF() > fPoint/2.0) {
//       if(debug) {
//         printf("3 update speed: %f\n", updateSpeed);
//       }
//       if(driveLB.get_actual_velocity() > 0 || driveRB.get_actual_velocity() > 0) {
//         driveVel(0);
//       }
//       if(updateSpeed > speed) {
//         updateSpeed-=10;
//       }
//       intakeHandler(100);
//       driveVel(updateSpeed);
//       if(debug) {
//         printf("Obtain position: %d\n", obtainPositionF());
//       }
//       pros::delay(75);
//     }
//     while(obtainPositionF() > fPoint) {
//       if(debug) {
//         printf("4 update speed: %f\n", updateSpeed);
//       }
//       if(driveLB.get_actual_velocity() > 0 || driveRB.get_actual_velocity() > 0) {
//         driveVel(0);
//       }
//       if(updateSpeed < 0) {
//         updateSpeed+=5;
//       }
//       driveVel(updateSpeed);
//       if(debug) {
//         printf("Obtain position: %d\n", obtainPositionF());
//       }
//       pros::delay(75);
//     }
//     part++;
//     driveVel(0);
//     if(updateSpeed == 0) {
//       intakeHandler(0);
//     }
//   }
// }
