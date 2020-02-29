#include "subsystems.hpp"
using namespace pros;

//Drivetrain
Motor driveRF(19, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveRB(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLF(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor driveLB(16, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor intakeR(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor intakeL(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(8, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
bool debug = false;

//Broken ports: 13, 10, 9, 7, 5, 21, 1?, 4?, 2

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

int right;
int left;


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
