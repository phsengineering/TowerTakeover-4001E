#include "main.cpp"


Motor rightFrontDrive(19, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor rightBackDrive(20, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_ROTATIONS);
Motor leftFrontDrive(15, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor leftBackDrive(16, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_ROTATIONS);
Motor tray(12, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor lift(4, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
Motor rightIntake(21, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor leftIntake(11, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

//Broken ports: 13, 10, 9, 7, 5, 21, 1?, 4?, 2

void drive(int analogY, int analogX) {
  analogY = analogY * (12000 / 127);
  analogX = analogX * (12000 / 127);

  rightFrontDrive.move_voltage(analogY + analogX);
  rightBackDrive.move_voltage(analogY + analogX);
  leftFrontDrive.move_voltage(analogY - analogX);
  leftBackDrive.move_voltage(analogY - analogX);
}

void intakeHandler(int speed) {
  rightIntake.move_velocity(speed);
  leftIntake.move_velocity(speed);
}

void trayHandler(int speed) {
  tray.move_velocity(speed);
}

void liftHandler(int speed) {
  lift.move_velocity(speed);
}

void autoDrive (int speed) {
  rightFrontDrive.move_velocity(speed);
  rightBackDrive.move_velocity(speed);
  leftFrontDrive.move_velocity(speed);
  leftBackDrive.move_velocity(speed);
}
